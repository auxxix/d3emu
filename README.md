d3emu depends on the protobuf library. Blizzard uses an older version of protobuf (2.3). As of right now, that version is still available for download at http://code.google.com/p/protobuf/downloads/list

If you're using the Xcode project, the header paths are all relative, and it assumes you installed the protobuf library to /usr/local/lib and /usr/local/include.
