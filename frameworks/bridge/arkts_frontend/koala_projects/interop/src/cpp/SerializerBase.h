/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <vector>

#include "callback-resource.h"
#include "interop-logging.h"
#include "interop-types.h"
#include "interop-utils.h"
#include "koala-types.h"

#ifdef __arm__
#define KOALA_NO_UNALIGNED_ACCESS 1
#endif

template <typename T>
inline InteropRuntimeType runtimeType(const T& value) = delete;

template <>
inline InteropRuntimeType runtimeType(const InteropCustomObject& value)
{
  return INTEROP_RUNTIME_OBJECT;
}

template <>
inline InteropRuntimeType runtimeType(const InteropMaterialized& value)
{
  return INTEROP_RUNTIME_OBJECT;
}
template <>
inline InteropRuntimeType runtimeType(const InteropObject& value)
{
    return INTEROP_RUNTIME_OBJECT;
}

const uint32_t INITIAL_SERIALIZER_DATA_LENGTH = 256;

class SerializerBase {
private:
    uint8_t* data;
    uint32_t dataLength;
    uint32_t position;
    bool ownData;
    CallbackResourceHolder* resourceHolder;
    void resize(uint32_t newLength) {
        ASSERT(ownData);
        ASSERT(newLength > dataLength);
        auto* newData = reinterpret_cast<uint8_t*>(malloc(newLength));
        if (!newData) {
            INTEROP_FATAL("Cannot allocate memory");
        }
        interop_memcpy(newData, newLength, data, position);
        free(data);
        data = newData;
        dataLength = newLength;
    }
public:
    explicit SerializerBase(CallbackResourceHolder* resourceHolder = nullptr)
        : position(0), ownData(true), resourceHolder(resourceHolder)
    {
        this->dataLength = INITIAL_SERIALIZER_DATA_LENGTH;
        this->data = reinterpret_cast<uint8_t*>(malloc(this->dataLength));
        if (!this->data) {
            INTEROP_FATAL("Cannot allocate memory");
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
                resize((position + more) * 3 / 2 + 2);
            } else {
                INTEROP_FATAL("Buffer overrun: %d > %d\n", position + more, dataLength);
            }
        }
    }

    void writeInt8(InteropInt8 value) {
        check(1);
        *(reinterpret_cast<InteropInt8*>(data + position)) = value;
        position += 1;
    }

    void writeInt32(InteropInt32 value) {
        check(sizeof(value));
#ifdef KOALA_NO_UNALIGNED_ACCESS
        interop_memcpy(data + position, dataLength, &value, sizeof(value));
#else
        *(reinterpret_cast<InteropInt32*>(data + position)) = value;
#endif
        position += sizeof(value);
    }

    void writeInt64(InteropInt64 value) {
        check(sizeof(value));
#ifdef KOALA_NO_UNALIGNED_ACCESS
        interop_memcpy(data + position, dataLength, &value, sizeof(value));
#else
        *(reinterpret_cast<InteropInt64*>(data + position)) = value;
#endif
        position += sizeof(value);
    }

    void writeUInt64(InteropUInt64 value) {
        check(sizeof(value));
#ifdef KOALA_NO_UNALIGNED_ACCESS
        interop_memcpy(data + position, dataLength, &value, sizeof(value));
#else
        *(reinterpret_cast<InteropUInt64*>(data + position)) = value;
#endif
        position += sizeof(value);
    }

    void writeFloat32(InteropFloat32 value) {
        check(sizeof(value));
#ifdef KOALA_NO_UNALIGNED_ACCESS
        interop_memcpy(data + position, dataLength, &value, sizeof(value));
#else
        *(reinterpret_cast<InteropFloat32*>(data + position)) = value;
#endif
        position += sizeof(value);
    }

    void writeFloat64(InteropFloat64 value) {
        check(sizeof(value));
#ifdef KOALA_NO_UNALIGNED_ACCESS
        interop_memcpy(data + position, dataLength, &value, sizeof(value));
#else
        *(reinterpret_cast<InteropFloat64*>(data + position)) = value;
#endif
        position += 8;
    }

    void writePointer(InteropNativePointer value) {
        int64_t value64 = static_cast<int64_t>(reinterpret_cast<uintptr_t>(value));
        check(sizeof(value64));
#ifdef KOALA_NO_UNALIGNED_ACCESS
        interop_memcpy(data + position, dataLength, &value64, sizeof(value64));
#else
        *(reinterpret_cast<int64_t*>(data + position)) = value64;
#endif
        position += sizeof(value64);
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
        interop_strcpy(reinterpret_cast<char*>(data + position), dataLength, value.chars);
        position += value.length + 1;
    }

    void writeBoolean(InteropBoolean value) {
        writeInt8(value);
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
        // Improve: implement
    }

    void writeBuffer(InteropBuffer buffer) {
        writeCallbackResource(buffer.resource);
        writePointer(reinterpret_cast<void*>(buffer.data));
        writeInt64(buffer.length);
    }

    KInteropReturnBuffer toReturnBuffer() {
        if (this->ownData) {
            KInteropReturnBuffer buffer {this->length(), this->release(), [](KNativePointer data, KInt length) { free(data); }};
            // Improve: fix memory issues
            return buffer;
        } else {
            return {this->length(), this->data, nullptr};
        }
    }
};

#endif // _SERIALIZER_BASE_H