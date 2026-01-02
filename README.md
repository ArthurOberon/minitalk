![Norminette](https://github.com/ArthurOberon/minitalk/actions/workflows/norminette.yml/badge.svg)

---

# Minitalk

This project is about create a communication between a server and a client by using signals.

## Usage

To launch the server :
```
./server
```

To launch the client :
```
./client PID "message to send"
```

### Example

On the first shell :
```
./server
Welcome to the Minitalk server. Starting...
Server Started ! You can send a message with the PID 3740619 !
```

On the second shell :
```
./client 3740619 "My message to send"
```

### Compiling

To compile the project :
```
make all
```

To compile only server :
```
make server
```

To compile only client :
```
make client
```

---

# How My Minitalk Work ?

## Signal System

* When the client or the server sending a signal, they can only use `SIGUSR1` and `SIGUSR2`.
```
SIGUSR1 = 0
SIGUSR2 = 1
```
* To send a character, it use bit shifting and mask (of 8 bits) :
```
if (character & (0b10000000 >> i++))
	(kill(pid, SIGUSR2) 	// send 1
else
	(kill(pid, SIGUSR1) 	// send 0
```
* The `&` is the binary operator `AND`, his truth table is :

| A | + | B | = | Y |
|---|---|---|---|---|
| 0 | + | 0 | = | 0 |
| 0 | + | 1 | = | 0 |
| 1 | + | 0 | = | 0 |
| 1 | + | 1 | = | 1 |

* the `>>` is the bit shifting on the right (`<<` is on the left), it shift all the bits by `i`, and the least-significant(s) bit(s) is lost and a 0 is inserted on the other end.
```
1011 >> 1  →  0101
1011 << 1  →  0110
101101 >> 3  →  000101
```

### For example

There a example of the sending processus on a full character (in this example 'P') :

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   |   |   |   |   |   |   |   |

Starting at `i = 0`.

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL| 0 |   |   |   |   |   |   |   |

`i++` (Shift the mask by one bit)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   | 1 |   |   |   |   |   |   |

`i++` (Shift the mask by one bit)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   |   | 0 |   |   |   |   |   |

`i++` (Shift the mask by one bit)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   |   |   | 1 |   |   |   |   |

`i++` (Shift the mask by one bit)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
|SEND SIGNAL|   |   |   |   | 0 |   |   |   |

`i++` (Shift the mask by one bit)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
|SEND SIGNAL|   |   |   |   |   | 0 |   |   |

`i++` (Shift the mask by one bit)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
|SEND SIGNAL|   |   |   |   |   |   | 0 |   |

`i++` (Shift the mask by one bit)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
|SEND SIGNAL|   |   |   |   |   |   |   | 0 |

* After each bit sended, the client wait a signal from the server before sending a new one.
* After each bit received, the server send a signal before to wait to receive a new one.

## Server

* At the start, the server get his pid with the function `getpid()`, and print it :
```
Welcome to the Minitalk server. Starting...
Server Started ! You can send a message with the PID 3740619 !
```

* Then it setup his sigaction (action to do when it receive a signal) :
```
sa.sa_sigaction = &handle_sig;		// Setup the function of the variable sa at handle_sig
sigaction(SIGUSR1, &sa, NULL);		// When receive a signal "SIGUSR1", use the variable sa
sigaction(SIGUSR2, &sa, NULL);		// When receive a signal "SIGUSR2", use the variable sa
```

* Then it receive the size of the message first, and malloc the gobal_variable at the size.

* Then it receive character by character the message, and print it.

## Client

* At the start, the client take the length of the message, and send it (with a mask of 32 bits) :
```
if (size & (0b10000000000000000000000000000000 >> i++))
	kill(pid, SIGUSR2)
else
	kill(pid, SIGUSR1)
```

* Then it send the message himself, character by character, bit by bit (using the mask system explained above).

