#include "file_process_buffer.hpp"

void FileProcessBuffer::addFile(const std::filesystem::path& filePath) {
    std::lock_guard<std::mutex> lock(processBufferMutex);
    m_fileBuffer.push_back(filePath);
    processBufferCv.notify_one();
}

std::filesystem::path FileProcessBuffer::getFile() {
    std::unique_lock<std::mutex> lock(processBufferMutex);
    processBufferCv.wait(lock, [this] { return !m_fileBuffer.empty(); });
    std::filesystem::path filePath = m_fileBuffer.front();
    m_fileBuffer.pop_front();
    return filePath;
}