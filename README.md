![Norminette](https://github.com/ArthurOberon/Push_swap/actions/workflows/norminette.yml/badge.svg) ![Makefile](https://github.com/ArthurOberon/Push_swap/actions/workflows/makefile.yml/badge.svg)

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

* When the client or the server sending a signal, they can only use SIGUSR1 and SIGUSR2.
```
SIGUSR1 = 0
SIGUSR2 = 1
```
* To send a character, it use shift bit and mask (of 8 bits) :
```
if (character & (0b10000000 >> i++))
	(kill(pid, SIGUSR2) 	// send 1
else
	(kill(pid, SIGUSR1) 	// send 0
```
* The `&` is a `AND`, his truth table is :

| A | B | Y |
|---|---|---|
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

### For example

There a example a full character (in this example 'P') it will look like this :

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   |   |   |   |   |   |   |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL| 0 |   |   |   |   |   |   |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   | 1 |   |   |   |   |   |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   |   | 0 |   |   |   |   |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
|SEND SIGNAL|   |   |   | 1 |   |   |   |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
|SEND SIGNAL|   |   |   |   | 0 |   |   |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
|SEND SIGNAL|   |   |   |   |   | 0 |   |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
|SEND SIGNAL|   |   |   |   |   |   | 0 |   |

`i++` (Shift bit the mask by one)

|BINARY		|128|64 |32 |16 | 8 | 4 | 2 | 1 |
|-----------|---|---|---|---|---|---|---|---|
|Character	| 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
|MASK (I)	| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
|SEND SIGNAL|   |   |   |   |   |   |   | 0 |

* After each bit send , the client wait a signal from the server before sending a new one.
* After each bit receive, the server send a signal before to wait to receive a new one.

## Server

* At the start, the server get his pid if the function `getpid()` and print it :
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

* At the start, the client, take the length of the message, and send it (with a mask of 32 bits) :
```
if (size & (0b10000000000000000000000000000000 >> i++))
	kill(pid, SIGUSR2)
else
	kill(pid, SIGUSR1)
```

* Then it send the message himself, characters by characters, bits by bits (using the mask system explained above).

### Author
* **[Arthur Obéron](https://github.com/ArthurOberon)**

### Thanks to :
* **Johanne Vigny**
