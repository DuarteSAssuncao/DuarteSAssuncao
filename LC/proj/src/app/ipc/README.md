# Rakoon - IPC (Inter-Process Communication)
This directory contains all files that allow the creation and interaction with windows created by any process.

### How does it work?
The server uses a Unix Domain Socket to connect to other processes. The first process it connects to is the "middleman", which is more of an auxiliary socket which might be deleted in future versions, so I won't even mention it in this introduction. With that said, we can say that the client can start creating a window by simply connecting to the server's socket and sending initial window attributes, at which point the server will start sending events and receiving requests.

Requests/events are sent using a fixed-size structure (rakoon_msg_t) that specifies the type of request/event and contains a buffer for aditional data that the request/event may need.

The server checks for requests (e.g. refresh/resize window) at a certain frequency (<=60Hz) due to the way it was designed. The sending of events is not necessarily restricted by this frequency, but may be for performance/modularity.

Almost nothing is documented right now, but that's because everything is pretty prone to change. In any case, here are some notes for anyone (probably myself) reading:

### Why use sockets to pass window buffers instead of shared memory?
This project was made for Minix 3, along with a library (LCF) that comes with restrictions. If you try to create shared memory with sys/shm.h, you will be denied permission, and using sys/mman.h leads to errors or duplicated memory. Of course, using sockets affects performance, but I didn't want to back down so here we are :p

### Why use a "middleman"?
Right now, I think its only practical purpose is to refresh the window buffer, since it's almost always ready for a request. Leaving this to the client is tricky because I would have to either block the client/server until the other end is ready for the operation, or *somehow* synchronize them.

Other than that, simple requests are probably not worth passing through a middleman, but a while back I thought that poll() with multiple file descriptors was lagging the server and I haven't changed it back since.