#!/bin/bash
# ============================================================================ #
#  test_minitalk.sh — 3-tier test harness (normal / extreme / hardcore)        #
#  Run inside WSL:  bash test_minitalk.sh                                       #
# ============================================================================ #

cd "$(dirname "$0")" || exit 1

GREEN=$'\033[0;32m'; RED=$'\033[0;31m'; YEL=$'\033[1;33m'; NC=$'\033[0m'
PASS=0; FAIL=0
SRV_OUT=/tmp/mt_srv.out
SRV_PID=""

ok()  { echo "  ${GREEN}ok${NC}  $1"; PASS=$((PASS+1)); }
ko()  { echo "  ${RED}KO${NC}  $1"; FAIL=$((FAIL+1)); }
hdr() { echo; echo "${YEL}== $1 ==${NC}"; }

start_server() {            # start_server <binary>
	: > "$SRV_OUT"
	./"$1" > "$SRV_OUT" 2>&1 &
	SRV_PID=$!
	sleep 0.4
	PID=$(grep -oE '[0-9]+' "$SRV_OUT" | head -1)
}
stop_server() {
	[ -n "$SRV_PID" ] && kill "$SRV_PID" 2>/dev/null
	wait "$SRV_PID" 2>/dev/null
	SRV_PID=""
}
# received text = everything in SRV_OUT after the first (PID) line
recv() { tail -n +2 "$SRV_OUT" | tr -d '\n'; }

expect_recv() {             # expect_recv <label> <sent> <expected>
	: > "$SRV_OUT.tmp"
	start_server "$BIN"
	./client "$PID" "$2" >/dev/null 2>&1
	sleep 0.3
	local got; got=$(recv)
	stop_server
	if [ "$got" = "$3" ]; then ok "$1"; else
		ko "$1 (got '$got' != '$3')"; fi
}

# --------------------------------------------------------------------------- #
hdr "TIER 1 — NORMAL (build / norm / happy path)"

make re >/tmp/mt_build.log 2>&1 && ok "make re builds clean" \
	|| { ko "make re FAILED"; tail -5 /tmp/mt_build.log; }

if make 2>&1 | grep -qi "nothing to be done"; then
	ok "no relink on second make"; else ko "second make relinks"; fi

if command -v norminette >/dev/null 2>&1; then NORM="norminette";
elif python3 -m norminette --version >/dev/null 2>&1; then
	NORM="python3 -m norminette";
else NORM="python3.exe -X utf8 -m norminette"; fi
if PYTHONUTF8=1 $NORM *.c *.h 2>&1 | grep -qE ": Error|ERROR"; then
	ko "norminette has errors"; else ok "norminette clean (no errors)"; fi

BIN=server
start_server server
[ -n "$PID" ] && ok "server prints its PID ($PID)" || ko "server PID missing"
./client "$PID" "Hello, World!" >/dev/null 2>&1; sleep 0.3
[ "$(recv)" = "Hello, World!" ] && ok "basic message intact" \
	|| ko "basic message wrong: '$(recv)'"
# several clients in a row, same server
./client "$PID" "AAA" >/dev/null 2>&1; sleep 0.2
./client "$PID" "BBB" >/dev/null 2>&1; sleep 0.3
[ "$(recv)" = "Hello, World!AAABBB" ] && ok "multiple messages, no restart" \
	|| ko "multi-message wrong: '$(recv)'"
stop_server

./client 2>/dev/null; [ $? -eq 1 ] && ok "no-arg client exits 1" \
	|| ko "no-arg client wrong exit"
./client abc "hi" >/dev/null 2>&1; [ $? -eq 1 ] \
	&& ok "invalid PID exits 1" || ko "invalid PID wrong exit"

# --------------------------------------------------------------------------- #
hdr "TIER 2 — EXTREME (weird but valid inputs)"

BIN=server
expect_recv "empty message"          ""        ""
expect_recv "single char"            "x"       "x"
expect_recv "spaces & punctuation"   "a b\tc!" "a b\tc!"
expect_recv "all printable-ish"      "0123456789~|}{" "0123456789~|}{"
expect_recv "quotes and slashes"     'a"b\\c/d' 'a"b\\c/d'

# 64-char message round-trip
LONG=$(printf 'Z%.0s' {1..64})
expect_recv "64-char message"        "$LONG"   "$LONG"

# timing: 100 chars must take < 1 second
MSG=$(printf 'q%.0s' {1..100})
start_server server
T0=$(date +%s.%N)
./client "$PID" "$MSG" >/dev/null 2>&1
sleep 0.05
T1=$(date +%s.%N)
stop_server
ELAPSED=$(echo "$T1 - $T0" | bc)
if (( $(echo "$ELAPSED < 1.0" | bc -l) )); then
	ok "100 chars in ${ELAPSED}s (< 1s)"; else
	ko "100 chars too slow: ${ELAPSED}s"; fi

# --------------------------------------------------------------------------- #
hdr "TIER 3 — HARDCORE (memory + stress + bonus)"

if command -v valgrind >/dev/null 2>&1; then
	start_server server
	valgrind --leak-check=full --error-exitcode=42 \
		./client "$PID" "valgrind run" >/tmp/mt_vg.log 2>&1
	VG=$?
	sleep 0.2
	stop_server
	if [ "$VG" = 42 ]; then ko "client leaks/errors (valgrind)";
		grep -E "definitely lost|Invalid" /tmp/mt_vg.log | head -3
	else ok "client: no leaks / invalid access"; fi
else
	echo "  ${YEL}skip${NC} valgrind not installed"; fi

# stress: 20 messages back-to-back on one server
start_server server
STRESS_OK=1
i=0
while [ $i -lt 20 ]; do
	./client "$PID" "msg$i" >/dev/null 2>&1 || STRESS_OK=0
	i=$((i+1))
done
sleep 0.3
kill -0 "$SRV_PID" 2>/dev/null && SRV_ALIVE=1 || SRV_ALIVE=0
stop_server
[ "$STRESS_OK" = 1 ] && [ "$SRV_ALIVE" = 1 ] \
	&& ok "20 messages stress, server alive" || ko "stress failed"

# ---- BONUS ----
hdr "BONUS (ack + unicode)"
if make bonus >/tmp/mt_bonus.log 2>&1; then
	ok "make bonus builds"
	BIN=server
	start_server server
	OUT=$(./client "$PID" "ack test" 2>&1); sleep 0.3
	echo "$OUT" | grep -qi "delivered" \
		&& ok "client confirms delivery (ack)" \
		|| ko "no delivery confirmation: '$OUT'"
	[ "$(recv)" = "ack test" ] && ok "bonus message intact" \
		|| ko "bonus message wrong: '$(recv)'"
	# unicode round-trip (UTF-8 bytes preserved)
	U="héllo ☃ ทดสอบ"
	./client "$PID" "$U" >/dev/null 2>&1; sleep 0.3
	[ "$(recv)" = "ack test$U" ] && ok "unicode preserved" \
		|| ko "unicode wrong: '$(recv)'"
	stop_server
else
	ko "make bonus FAILED"; tail -5 /tmp/mt_bonus.log; fi

# --------------------------------------------------------------------------- #
echo
echo "=== RESULT: ${GREEN}${PASS} passed${NC}, ${RED}${FAIL} failed${NC} ==="
[ "$FAIL" -eq 0 ] && exit 0 || exit 1
