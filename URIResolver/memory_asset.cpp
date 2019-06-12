#include "memory_asset.h"

#include <cstring>

PXR_NAMESPACE_OPEN_SCOPE

MemoryAsset::MemoryAsset(const char* raw, size_t size) : data_size(size) {
    if (size > 0) {
        auto* d = static_cast<char*>(malloc(data_size));
        memcpy(d, raw, data_size);
        data.reset(d, [](char* p) { free(p); });
    }
}

size_t MemoryAsset::GetSize() { return data_size; }

std::shared_ptr<const char> MemoryAsset::GetBuffer() { return data; }

size_t MemoryAsset::Read(void* buffer, size_t count, size_t offset) {
    if (data == nullptr || offset >= data_size) { return 0; }
    const auto copied = std::min(data_size - offset, count);
    memcpy(buffer, data.get() + offset, copied);
    return copied;
}

std::pair<FILE*, size_t> MemoryAsset::GetFileUnsafe() { return {0, 0}; }

PXR_NAMESPACE_CLOSE_SCOPE
