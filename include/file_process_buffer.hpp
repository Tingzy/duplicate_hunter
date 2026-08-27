#pragma once
#include <filesystem>
#include <mutex>
#include <condition_variable>
#include <deque>

class FileProcessBuffer {
public:
    //Constructor.
    FileProcessBuffer() = default;
    //Destructor.
    ~FileProcessBuffer() = default;

    void addFile(const std::filesystem::path& filePath);

    std::filesystem::path getFile();

    //Copy constructor.
    FileProcessBuffer(const FileProcessBuffer&) = delete;

    // Copy assignment operator.
    FileProcessBuffer& operator=(const FileProcessBuffer&) = delete;

    // Move constructor.
    FileProcessBuffer(FileProcessBuffer&&) = delete;

    // Move assignment operator.
    FileProcessBuffer& operator=(FileProcessBuffer&&) = delete;
private:
    // Mutex to protect access to the shared buffer.
    std::mutex processBufferMutex;

    // Condition variable to signal when the buffer is ready for processing.
    std::condition_variable processBufferCv;

    // Deque to store the file paths for processing.
    std::deque<std::filesystem::path> m_fileBuffer;
};