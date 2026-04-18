# TCP Client-Server File Processing System

## Overview
A multi-threaded TCP client-server application in C that transfers text files in 1KB chunks.  
Server converts text to UPPERCASE and sends it back to client.

## Features
- Multi-client support using pthreads
- TCP socket communication
- File streaming (1KB chunks)
- Server-side text transformation (lowercase → uppercase)
- Graceful connection termination

## Project Structure
client/
server/
data/

## Build

```bash
make


## Run Server
./server/bin/server <port>

## Run Client
./client/bin/client <server_ip> <port>

## Example Run (Same Machine)

> You can also run the client and server on different machines, as long as both are connected to the same network.

### Step 1: Start the Server
Open a terminal and run:
```bash
./server/bin/server 9898
```

### Step 2: Start the Client
Open another terminal and run:
```bash
./client/bin/client 127.0.0.1 9898

To clean all generated build artifacts, run:
make clean
```

### Notes
- Use `127.0.0.1` when both client and server are running on the same machine.
- If running on different machines, replace `127.0.0.1` with the server’s actual IP address.
- Ensure the chosen port (e.g., `9898`) is open and not blocked by firewall.
```
