D3Emu is a multi-platform Diablo III server emulator written in a mix of languages. The core portion of the server is written in C++, but there is a new GUI-based server (in xcode/d3emu-cocoa) written using Objective-C++ and Cocoa libraries.

D3Emu depends on the following packages:
* [protobuf](http://code.google.com/p/protobuf/downloads/list)
* [boost 1.47.0](http://boost.org)

D3Emu mu depends on the protobuf library. Blizzard uses an older version of protobuf (2.3). As of right now, that version is still available for download at http://code.google.com/p/protobuf/downloads/list

If you're using the Xcode project, the header paths are all relative, and it assumes you installed the protobuf library to /usr/local/lib and /usr/local/include.

I am currently working on a GUI-based implementation of d3emu for Mac using Cocoa. It's currently in an infant stage, but I expect to make some headway soon. I am more or less creating it to help aid in understanding communication between the client and server.
