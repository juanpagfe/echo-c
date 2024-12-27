# echo-c

This repository contains an implementation of an ECHO server for learning purposes, based on [RFC 862](https://www.ietf.org/rfc/rfc862.txt).

## Description

The project implements an ECHO server that listens for client connections and sends back any data received. This is a simple implementation useful for learning about socket programming and network protocols in C.

## Features

- Simple ECHO server
- Supports TCP/IP communication
- Implements [RFC 862](https://www.ietf.org/rfc/rfc862.txt)

## Requirements

- make

## Build

Clone the repository:

```bash
git clone https://github.com/juanpagfe/echo-c.git
cd echo-c
make
# The program will be in the build directory
cd build
```

## Usage

Print help to understand the process:
```bash
./echo --help
Usage: echo [options]
Options:
  -h, --help    Show this help message
  -p, --port    Port the program will use to serve. (Default: 7. Needs superuser permissions in most systems)
```

Run the program:
```bash
./echo -p 8181
Listening on port = 8181
```

## Test

In a different terminal, you can test the server using telnet:

```bash
telnet localhost 8181
~ ❯ telnet localhost 8181
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Hello World!
Hello World!
```
