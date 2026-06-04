*This project has been created as part of the 42 curriculum by wiaon-in.*

# Minitalk

## Description

Minitalk is a small client–server data-exchange program that communicates
**exclusively through UNIX signals**. The only two signals used are `SIGUSR1`
and `SIGUSR2`, which encode each transmitted byte one bit at a time
(`SIGUSR1` → bit `0`, `SIGUSR2` → bit `1`, MSB-first).

- The **server** is started first and prints its PID.
- The **client** takes the server PID and a string, then transmits that string
  bit by bit. The server reconstructs each byte and prints it immediately.
- The server keeps running and can receive messages from several clients in a
  row without restarting.

### Bonus

- **Acknowledgement** — the server replies with a signal after every bit it
  receives, so the client advances in lock-step (fast and lossless). When the
  message terminator is received the server replies with `SIGUSR2`, and the
  client prints `Message delivered!`.
- **Unicode** — because the string is sent byte by byte, multi-byte UTF-8
  characters (e.g. `é`, `☃`, ภาษาไทย) are preserved transparently.

## Instructions

Compilation (requires `cc`, GNU `make`, a Linux environment):

```sh
make            # builds the mandatory binaries: server and client
make bonus      # builds the bonus binaries (same names: server, client)
make clean      # removes object files
make fclean     # removes objects + binaries + libft.a
make re         # fclean + all
```

Usage:

```sh
./server                       # prints e.g. "Server PID: 12345"
./client 12345 "Hello, World!" # sends the string to that server
```

The server then prints `Hello, World!`. Run the client again with the same PID
to send more messages — the server does not need to restart.

### Testing

A three-tier test harness is provided (run inside WSL on Windows):

```sh
bash test_minitalk.sh
```

It covers NORMAL (build, no-relink, norminette, happy path), EXTREME (empty /
single-char / long / special-character messages, 100-chars-under-1-second
timing), and HARDCORE (valgrind leak check, 20-message stress, bonus ack +
unicode round-trip).

## Technical choices

- **No global in the server.** The mandatory and bonus servers reconstruct the
  current byte with `static` local variables inside the signal handler, so no
  global variable is needed.
- **One global in the bonus client.** `g_ack` (a `volatile sig_atomic_t`) is the
  single permitted global; it lets the acknowledgement handler tell the main
  send loop that the server is ready for the next bit.
- **`sigaction` over `signal`** for reliable, well-defined handler behaviour; the
  bonus server uses `SA_SIGINFO` to read the client's PID from `siginfo_t->si_pid`
  in order to acknowledge it.
- **Message framing.** The client always sends a trailing `'\0'`; the server uses
  it as the end-of-message marker (prints a newline / sends the final ack).

## Resources

- `man 2 signal`, `man 2 sigaction`, `man 2 kill`, `man 7 signal` — signal API
  and the list of async-signal-safe functions.
- 42 subject *Minitalk* (v5.0) — project requirements.
- Beej's Guide / various articles on bit manipulation and inter-process
  signalling.

### Use of AI

AI (Claude Code) was used to: scaffold the project structure by reusing the
existing `libft`, draft the signal protocol and the bonus acknowledgement
hand-shake, generate the three-tier test harness, and review the code for
norminette compliance and the signal-handler safety of `ft_printf`. All
generated code was read, understood, and verified by running norminette,
valgrind, and the functional tests before being kept.
