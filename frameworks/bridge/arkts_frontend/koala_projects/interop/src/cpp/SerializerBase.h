/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SERIALIZER_BASE_H
#define _SERIALIZER_BASE_H

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <cassert>
#include <cstddef>
#include <vector>

#include "callback-resource.h"
#include "interop-types.h"
#include "koala-types.h"
#include "securec.h"

#ifdef __arm__
#define KOALA_NO_UNALIGNED_ACCESS 1
#endif

template <typename T>
inline InteropRuntimeType runtimeType(const T& value) = delete;

template <>
inline InteropRuntimeType runtimeType(const InteropCustomObject& value) {
  return INTEROP_RUNTIME_OBJECT;
}

template <>
inline InteropRuntimeType runtimeType(const InteropMaterialized& value) {
  return INTEROP_RUNTIME_OBJECT;
}

static const std::size_t buffer_size = 1024 * 1024; // 1 MB
static std::size_t offset = 0;
alignas(std::max_align_t) static char buffer[buffer_size];

template <typename T, std::size_t size>
T* allocArray(const std::array<T, size>& ref) {
  std::size_t space = sizeof(buffer) - offset;
  void* ptr = buffer + offset;
  void* aligned_ptr = std::align(alignof(T), sizeof(T) * size, ptr, space);
  assert(aligned_ptr != nullptr && "Insufficient space or alignment failed!");
  offset = (char*)aligned_ptr + sizeof(T) * size - buffer;
  T* array = reinterpret_cast<T*>(aligned_ptr);
  for (size_t i = 0; i < size; ++i) {
    new (&array[i]) T(ref[i]);
  }
  return array;
}

class SerializerBase {
private:
    uint8_t* data;
    uint32_t dataLength;
    uint32_t position;
    bool ownData;
    CallbackResourceHolder* resourceHolder;
    void resize(uint32_t newLength) {
        assert(ownData);
        assert(newLength > dataLength);
        auto* newData = reinterpret_cast<uint8_t*>(malloc(newLength));
        if (newData == NULL) {
            return;
        }
        if (data == NULL || memcpy_s(newData, newLength, data, position) != 0) {
            free(newData);
            return;
        }
        free(data);
        data = newData;
    }
public:
    SerializerBase(CallbackResourceHolder* resourceHolder = nullptr):
        position(0), ownData(true), resourceHolder(resourceHolder) {
        this->dataLength = 256;
        auto newData = malloc(this->dataLength);
        if (newData) {
            this->data = reinterpret_cast<uint8_t*>(newData);
        } else {
            this->data = nullptr;
        }
    }

    SerializerBase(uint8_t* data, uint32_t dataLength, CallbackResourceHolder* resourceHolder = nullptr):
        data(data), dataLength(dataLength), position(0), ownData(false), resourceHolder(resourceHolder) {
    }

    SerializerBase(KSerializerBuffer data, uint32_t dataLength, CallbackResourceHolder* resourceHolder = nullptr):
        data(reinterpret_cast<uint8_t*>(data)), dataLength(dataLength), position(0), ownData(false), resourceHolder(resourceHolder) {
    }

    virtual ~SerializerBase() {
        if (ownData) {
            free(data);
        }
    }

    SerializerBase(const SerializerBase&) = delete;
    SerializerBase& operator=(const SerializerBase&) = delete;

    void* release() {
        ownData = false;
        return data;
    }
    int length() {
        return position;
    }

    inline void check(int more) {
        if (position + more > dataLength) {
            if (ownData) {
                resize(dataLength * 3 / 2 + 2);
            } else {
                fprintf(stderr, "Buffer overrun: %d > %d\n", position + more, dataLength);
                assert(false);
            }
        }
    }

    void writeInt8(InteropInt8 value) {
        check(1);
        *((InteropInt8*)(data + position)) = value;
        position += 1;
    }

    void writeInt32(InteropInt32 value) {
        check(4);
#ifdef KOALA_NO_UNALIGNED_ACCESS
        memcpy(data + position, &value, 4);
#else
        *((InteropInt32*)(data + position)) = value;
#endif
        position += 4;
    }

    void writeInt64(InteropInt64 value) {
        check(8);
#ifdef KOALA_NO_UNALIGNED_ACCESS
        memcpy(data + position, &value, 8);
#else
        *((InteropInt64*)(data + position)) = value;
#endif
        position += 8;
    }

    void writeUInt64(InteropUInt64 value) {
        check(8);
#ifdef KOALA_NO_UNALIGNED_ACCESS
        memcpy(data + position, &value, 8);
#else
        *((InteropUInt64*)(data + position)) = value;
#endif
        position += 8;
    }

    void writeFloat32(InteropFloat32 value) {
        check(4);
#ifdef KOALA_NO_UNALIGNED_ACCESS
        memcpy(data + position, &value, 4);
#else
        *((InteropFloat32*)(data + position)) = value;
#endif
        position += 4;
    }

    void writePointer(InteropNativePointer value) {
        check(8);
        int64_t value64 = static_cast<int64_t>(reinterpret_cast<uintptr_t>(value));
#ifdef KOALA_NO_UNALIGNED_ACCESS
        if (memcpy_s(data + position, 8, &value64, 8) != 0) {
            return;
        }
#else
        *((int64_t*)(data + position)) = value64;
#endif
        position += 8;
    }

    void writeFunction(InteropFunction value) {
        // TODO: ignored, remove!
        writeInt32(0x666);
    }

    void writeNumber(InteropNumber value) {
        writeInt8(value.tag);
        if (value.tag == InteropTag::INTEROP_TAG_INT32) {
            writeInt32(value.i32);
        } else if (value.tag == InteropTag::INTEROP_TAG_FLOAT32) {
            writeFloat32(value.f32);
        } else {
            INTEROP_FATAL("Unknown tag number");
        }
    }

    void writeString(InteropString value) {
        writeInt32(value.length + 1);
        check(value.length + 1);
        strcpy((char*)(data + position), value.chars);
        position += value.length + 1;
    }

    void writeBoolean(InteropBoolean value) {
        writeInt8(value);
    }

    void writeLength(InteropLength value) {
        InteropRuntimeType tag = (InteropRuntimeType) value.type;
        writeInt8(tag);
        switch (tag) {
            case INTEROP_RUNTIME_NUMBER:
                writeFloat32(value.value);
                break;
            case INTEROP_RUNTIME_OBJECT:
                writeInt32(value.resource);
                break;
            case INTEROP_RUNTIME_STRING: {
                char buf[64];
                std::string suffix;
                switch (value.unit) {
                    case 0: suffix = "px"; break;
                    case 1: suffix = "vp"; break;
                    case 2: suffix = "fp"; break;
                    case 3: suffix = "%"; break;
                    case 4: suffix = "lpx"; break;
                }
                snprintf(buf, 64, "%.8f%s", value.value, suffix.c_str());
                InteropString str =  { buf, (InteropInt32) strlen(buf) };
                writeString(str);
                break;
            }
            default:
                break;
        }
    }

    void writeCallbackResource(const InteropCallbackResource resource) {
        writeInt32(resource.resourceId);
        writePointer(reinterpret_cast<void*>(resource.hold));
        writePointer(reinterpret_cast<void*>(resource.release));
        if (this->resourceHolder != nullptr) {
            this->resourceHolder->holdCallbackResource(&resource);
        }
    }

    void writeObject(InteropObject any) {
        writeCallbackResource(any.resource);
    }

    void writeCustomObject(std::string type, InteropCustomObject value) {
        // TODO implement
    }

    void writeBuffer(InteropBuffer buffer) {
        writeCallbackResource(buffer.resource);
        writePointer((void*)buffer.data);
        writeInt64(buffer.length);
    }

    KInteropReturnBuffer toReturnBuffer() {
        if (this->ownData) {
            KInteropReturnBuffer buffer {this->length(), this->release(), [](KNativePointer data, KInt length) { free(data); }};
            // TODO fix memory issues
            return buffer;
        } else {
            return {this->length(), this->data, nullptr};
        }
    }
};

#endif // _SERIALIZER_BASE_H