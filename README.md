# ⚡ UDP Server and Client in (pure) C
A very simple server and client written in pure C that communicate using the User Datagram Protocol.
This was made as an implementation of Datagram Sockets as part of CS206.

# Technologies
- C

# Features
- Send messages over the Internet using UDP
- Customizable port numbers as per usage

# Learning Outcomes
Over the course of this project, I learnt:

 1. the usage of `getaddrinfo()` and how it fills the required `struct addrinfo` for us
 2. the essential `socket()`
 3. the workflow of `socket()`, `bind()` and then `recvfrom()` for the server
 4. the workflow of `socket()` and then `sendto()`
 5. handling errors using `perror()`

# How do you run it?
1. Clone the repository (make sure you are on a Linux machine)
2. Run `gcc listen.c -o listen.out`
3. Run `gcc talk.c -o talk.out`
4. Run both the executables on different instances of a terminal with a message as an argument for `./talk.out`

# Preview
![UDP Server](https://github.com/user-attachments/assets/130a60f5-a03b-434f-85fd-ef0f1a94a31c)

