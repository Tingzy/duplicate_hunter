Learning project. Duplicate Hunter.
Learning topic: Concurrency.

**** Idea ****
FileReader: reads the path and produce the lists of files in the path.
FileComparator: reads the buffer and check if the files are unique.
FileProcessBuffer: the shared buffer for the FIleReader threads.
FileCompareBuffer: the shared buffer for the FileComparator threads.
FileReader runs first, because FileComparator can only check uniqueness of files when the file list is complete.
FileReader: 1 thread reading from the dir and add to a deque, while other threads hash and put the hashed file to FileCompareBuffer.
FileComparator runs on multiple thread. Each pop 1 elements from the map, check uniqueness, return result.

**** Build ****
On Windows:
Install cmake 
cmake -B build -S. -DCMAKE_TOOLCHAIN_FILE=".\cmake\toolchains\native-windows.cmake"
cmake --build build --config Release

On Linux:
Install cmake 
cmake -B build -S. -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchains/native-linux.cmake
cmake --build build --config Release

**** Run application ****
    .\dupHunter_app.exe <directory>