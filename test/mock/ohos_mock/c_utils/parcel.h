/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_UTILS_PARCEL_H
#define OHOS_UTILS_PARCEL_H

#include <string>
#include <vector>

#include "refbase.h"

namespace OHOS {
typedef uint64_t binder_size_t;

class Parcel;
class Parcelable {
public:
    virtual ~Parcelable() = default;

    Parcelable() : asRemote_(false), behavior_(0) {}
    explicit Parcelable(bool asRemote) : asRemote_(asRemote), behavior_(0) {}
    virtual bool Marshalling(Parcel& parcel) const = 0;
    enum BehaviorFlag { IPC = 0x01, RPC = 0x02, HOLD_OBJECT = 0x10 };

    inline void SetBehavior(BehaviorFlag b) const
    {
        behavior_ |= static_cast<uint8_t>(b);
    }

    inline void ClearBehavior(BehaviorFlag b) const
    {
        behavior_ &= static_cast<uint8_t>(~b);
    }

    inline bool TestBehavior(BehaviorFlag b) const
    {
        return behavior_ & (static_cast<uint8_t>(b));
    }

public:
    bool asRemote_;
    mutable uint8_t behavior_;
};

class Allocator {
public:
    virtual ~Allocator() = default;

    virtual void* Realloc(void* data, size_t newSize) = 0;

    virtual void* Alloc(size_t size) = 0;

    virtual void Dealloc(void* data) = 0;
};

class DefaultAllocator : public Allocator {
public:
    void* Realloc(void* data, size_t newSize) override
    {
        return realloc(data, newSize);
    }

    void* Alloc(size_t size) override
    {
        return malloc(size);
    }

    void Dealloc(void* data) override
    {
        free(data);
    }
};

class Parcel {
public:
    Parcel()
        : data_(nullptr), readCursor_(0), writeCursor_(0), dataSize_(0), dataCapacity_(0), maxDataCapacity_(0),
          objectOffsets_(nullptr), nextObjectIdx_(0), objectCursor_(0), objectsCapacity_(0), allocator_(nullptr),
          writable_(true)
    {}

    explicit Parcel(Allocator* allocator)
        : data_(nullptr), readCursor_(0), writeCursor_(0), dataSize_(0), dataCapacity_(0), maxDataCapacity_(0),
          objectOffsets_(nullptr), nextObjectIdx_(0), objectCursor_(0), objectsCapacity_(0), allocator_(allocator),
          writable_(true)
    {}

    virtual ~Parcel() {}

    size_t GetDataSize() const
    {
        return dataSize_;
    }

    uintptr_t GetData() const
    {
        return reinterpret_cast<uintptr_t>(data_);
    }

    binder_size_t GetObjectOffsets() const
    {
        return objectOffsets_ ? *objectOffsets_ : 0;
    }

    size_t GetOffsetsSize() const
    {
        return objectsCapacity_;
    }

    size_t GetWritableBytes() const
    {
        return dataCapacity_ - writeCursor_;
    }

    size_t GetReadableBytes() const
    {
        return dataSize_ - readCursor_;
    }

    size_t GetDataCapacity() const
    {
        return dataCapacity_;
    }

    size_t GetMaxCapacity() const
    {
        return maxDataCapacity_;
    }

    bool SetDataCapacity(size_t newCapacity)
    {
        return true;
    }

    bool SetDataSize(size_t dataSize)
    {
        dataSize_ = dataSize;
        return true;
    }

    bool SetMaxCapacity(size_t maxCapacity)
    {
        maxDataCapacity_ = maxCapacity;
        return true;
    }

    bool WriteBool(bool value)
    {
        (void)value;
        return true;
    }

    bool WriteInt8(int8_t value)
    {
        (void)value;
        return true;
    }

    bool WriteInt16(int16_t value)
    {
        (void)value;
        return true;
    }

    bool WriteInt32(int32_t value)
    {
        (void)value;
        return true;
    }

    bool WriteInt64(int64_t value)
    {
        (void)value;
        return true;
    }

    bool WriteUint8(uint8_t value)
    {
        (void)value;
        return true;
    }

    bool WriteUint16(uint16_t value)
    {
        (void)value;
        return true;
    }

    bool WriteUint32(uint32_t value)
    {
        (void)value;
        return true;
    }

    bool WriteUint64(uint64_t value)
    {
        (void)value;
        return true;
    }

    bool WriteFloat(float value)
    {
        (void)value;
        return true;
    }

    bool WriteDouble(double value)
    {
        (void)value;
        return true;
    }

    bool WritePointer(uintptr_t value)
    {
        (void)value;
        return true;
    }

    bool WriteBuffer(const void* data, size_t size)
    {
        (void)data;
        (void)size;
        return true;
    }

    bool WriteBufferAddTerminator(const void* data, size_t size, size_t typeSize)
    {
        (void)data;
        (void)size;
        (void)typeSize;
        return true;
    }

    bool WriteUnpadBuffer(const void* data, size_t size)
    {
        (void)data;
        (void)size;
        return true;
    }

    bool WriteCString(const char* value)
    {
        (void)value;
        return true;
    }

    bool WriteString(const std::string& value)
    {
        (void)value;
        return true;
    }

    bool WriteString16(const std::u16string& value)
    {
        (void)value;
        return true;
    }

    bool WriteString16WithLength(const char16_t* value, size_t len)
    {
        (void)value;
        (void)len;
        return true;
    }

    bool WriteString8WithLength(const char* value, size_t len)
    {
        (void)value;
        (void)len;
        return true;
    }

    bool WriteParcelable(const Parcelable* object)
    {
        (void)object;
        return true;
    }

    bool WriteStrongParcelable(const sptr<Parcelable>& object)
    {
        (void)object;
        return true;
    }

    bool WriteRemoteObject(const Parcelable* object)
    {
        (void)object;
        return true;
    }

    template<typename T>
    bool WriteObject(const sptr<T>& object);

    bool ParseFrom(uintptr_t data, size_t size)
    {
        (void)data;
        (void)size;
        return true;
    }

    bool ReadBool()
    {
        return false;
    }

    int8_t ReadInt8()
    {
        return 0;
    }

    int16_t ReadInt16()
    {
        return 0;
    }

    int32_t ReadInt32()
    {
        return 0;
    }

    int64_t ReadInt64()
    {
        return 0;
    }

    uint8_t ReadUint8()
    {
        return 0;
    }

    uint16_t ReadUint16()
    {
        return 0;
    }

    uint32_t ReadUint32()
    {
        return 0;
    }

    uint64_t ReadUint64()
    {
        return 0;
    }

    float ReadFloat()
    {
        return 0.0f;
    }

    double ReadDouble()
    {
        return 0.0;
    }

    uintptr_t ReadPointer()
    {
        return 0;
    }

    bool ReadBool(bool& value)
    {
        value = false;
        return true;
    }

    bool ReadInt8(int8_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadInt16(int16_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadInt32(int32_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadInt64(int64_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadUint8(uint8_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadUint16(uint16_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadUint32(uint32_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadUint64(uint64_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadFloat(float& value)
    {
        value = 0.0f;
        return true;
    }

    bool ReadDouble(double& value)
    {
        value = 0.0;
        return true;
    }

    const uint8_t* ReadBuffer(size_t length)
    {
        (void)length;
        return nullptr;
    }

    const uint8_t* ReadBuffer(size_t length, bool isValidate)
    {
        (void)length;
        (void)isValidate;
        return nullptr;
    }

    const uint8_t* ReadUnpadBuffer(size_t length)
    {
        (void)length;
        return nullptr;
    }

    void SkipBytes(size_t bytes)
    {
        (void)bytes;
    }

    const char* ReadCString()
    {
        return nullptr;
    }

    const std::string ReadString()
    {
        return std::string();
    }

    bool ReadString(std::string& value)
    {
        value.clear();
        return true;
    }

    const std::u16string ReadString16()
    {
        return std::u16string();
    }

    bool ReadString16(std::u16string& value)
    {
        value.clear();
        return true;
    }

    const std::u16string ReadString16WithLength(int32_t& len)
    {
        len = 0;
        return std::u16string();
    }

    const std::string ReadString8WithLength(int32_t& len)
    {
        len = 0;
        return std::string();
    }

    bool RewindRead(size_t newPosition)
    {
        (void)newPosition;
        readCursor_ = newPosition;
        return true;
    }

    bool RewindWrite(size_t offsets)
    {
        (void)offsets;
        writeCursor_ = offsets;
        return true;
    }

    size_t GetReadPosition()
    {
        return readCursor_;
    }

    size_t GetWritePosition()
    {
        return writeCursor_;
    }

    template<typename T>
    T* ReadParcelable();

    template<typename T>
    sptr<T> ReadStrongParcelable();

    bool CheckOffsets()
    {
        return true;
    }

    template<typename T>
    sptr<T> ReadObject();

    bool SetAllocator(Allocator* allocator)
    {
        allocator_ = allocator;
        return true;
    }

    void InjectOffsets(binder_size_t offsets, size_t offsetSize)
    {
        (void)offsets;
        (void)offsetSize;
    }

    void FlushBuffer() {}

    template<typename T1, typename T2>
    bool WriteVector(const std::vector<T1>& val, bool (Parcel::*Write)(T2))
    {
        (void)val;
        (void)Write;
        return true;
    }

    template<typename Type, typename T1, typename T2>
    bool WriteFixedAlignVector(const std::vector<T1>& originVal, bool (Parcel::*SpecialWrite)(T2))
    {
        (void)originVal;
        (void)SpecialWrite;
        return true;
    }

    bool WriteBoolVector(const std::vector<bool>& val)
    {
        (void)val;
        return true;
    }

    bool WriteInt8Vector(const std::vector<int8_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteInt16Vector(const std::vector<int16_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteInt32Vector(const std::vector<int32_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteInt64Vector(const std::vector<int64_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteUInt8Vector(const std::vector<uint8_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteUInt16Vector(const std::vector<uint16_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteUInt32Vector(const std::vector<uint32_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteUInt64Vector(const std::vector<uint64_t>& val)
    {
        (void)val;
        return true;
    }

    bool WriteFloatVector(const std::vector<float>& val)
    {
        (void)val;
        return true;
    }

    bool WriteDoubleVector(const std::vector<double>& val)
    {
        (void)val;
        return true;
    }

    bool WriteStringVector(const std::vector<std::string>& val)
    {
        (void)val;
        return true;
    }

    bool WriteString16Vector(const std::vector<std::u16string>& val)
    {
        (void)val;
        return true;
    }

    template<typename T>
    bool ReadVector(std::vector<T>* val, bool (Parcel::*Read)(T&))
    {
        (void)val;
        (void)Read;
        return true;
    }

    template<typename Type, typename T1, typename T2>
    bool ReadFixedAlignVector(std::vector<T1>* val, bool (Parcel::*SpecialRead)(T2&))
    {
        (void)val;
        (void)SpecialRead;
        return true;
    }

    bool ReadBoolVector(std::vector<bool>* val)
    {
        (void)val;
        return true;
    }

    bool ReadInt8Vector(std::vector<int8_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadInt16Vector(std::vector<int16_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadInt32Vector(std::vector<int32_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadInt64Vector(std::vector<int64_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadUInt8Vector(std::vector<uint8_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadUInt16Vector(std::vector<uint16_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadUInt32Vector(std::vector<uint32_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadUInt64Vector(std::vector<uint64_t>* val)
    {
        (void)val;
        return true;
    }

    bool ReadFloatVector(std::vector<float>* val)
    {
        (void)val;
        return true;
    }

    bool ReadDoubleVector(std::vector<double>* val)
    {
        (void)val;
        return true;
    }

    bool ReadStringVector(std::vector<std::string>* val)
    {
        (void)val;
        return true;
    }

    bool ReadString16Vector(std::vector<std::u16string>* val)
    {
        (void)val;
        return true;
    }

    bool WriteBoolUnaligned(bool value)
    {
        (void)value;
        return true;
    }

    bool WriteInt8Unaligned(int8_t value)
    {
        (void)value;
        return true;
    }

    bool WriteInt16Unaligned(int16_t value)
    {
        (void)value;
        return true;
    }

    bool WriteUint8Unaligned(uint8_t value)
    {
        (void)value;
        return true;
    }

    bool WriteUint16Unaligned(uint16_t value)
    {
        (void)value;
        return true;
    }

    bool ReadBoolUnaligned()
    {
        return true;
    }

    bool ReadInt8Unaligned(int8_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadInt16Unaligned(int16_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadUint8Unaligned(uint8_t& value)
    {
        value = 0;
        return true;
    }

    bool ReadUint16Unaligned(uint16_t& value)
    {
        value = 0;
        return true;
    }

protected:
    bool WriteObjectOffset(binder_size_t offset)
    {
        (void)offset;
        return true;
    }

    bool EnsureObjectsCapacity()
    {
        return true;
    }

private:
    template<typename T>
    bool Write(T value)
    {
        (void)value;
        return true;
    }

    template<typename T>
    bool Read(T& value)
    {
        value = T();
        return true;
    }

    template<typename T>
    T Read()
    {
        return T();
    }

    template<typename T>
    bool ReadPadded(T& value)
    {
        value = T();
        return true;
    }

    inline size_t GetPadSize(size_t size)
    {
        const size_t SIZE_OFFSET = 3;
        return (((size + SIZE_OFFSET) & (~SIZE_OFFSET)) - size);
    }

    size_t CalcNewCapacity(size_t minCapacity)
    {
        (void)minCapacity;
        return 0;
    }

    bool WriteDataBytes(const void* data, size_t size)
    {
        (void)data;
        (void)size;
        return true;
    }

    void WritePadBytes(size_t padded)
    {
        (void)padded;
    }

    bool EnsureWritableCapacity(size_t desireCapacity)
    {
        (void)desireCapacity;
        return true;
    }

    bool WriteParcelableOffset(size_t offset)
    {
        (void)offset;
        return true;
    }

    const uint8_t* BasicReadBuffer(size_t length)
    {
        (void)length;
        return nullptr;
    }

    bool IsReadObjectData(const size_t nextObj, const size_t upperBound)
    {
        (void)nextObj;
        (void)upperBound;
        return true;
    }

    bool ValidateReadData(size_t upperBound)
    {
        (void)upperBound;
        return true;
    }

    void ClearObjects() {}

private:
    uint8_t* data_;
    size_t readCursor_;
    size_t writeCursor_;
    size_t dataSize_;
    size_t dataCapacity_;
    size_t maxDataCapacity_;
    binder_size_t* objectOffsets_;
    size_t nextObjectIdx_;
    size_t objectCursor_;
    size_t objectsCapacity_;
    Allocator* allocator_;
    std::vector<sptr<Parcelable>> objectHolder_;
    bool writable_;
};

template<typename T>
bool Parcel::WriteObject(const sptr<T>& object)
{
    if (object == nullptr) {
        return T::Marshalling(*this, object);
    }
    return WriteRemoteObject(object.GetRefPtr());
}

template<typename T>
sptr<T> Parcel::ReadObject()
{
    if (!this->CheckOffsets()) {
        return nullptr;
    }
    sptr<T> res(T::Unmarshalling(*this));
    return res;
}

template<typename T>
T* Parcel::ReadParcelable()
{
    int32_t size = this->ReadInt32();
    if (size == 0) {
        return nullptr;
    }
    return T::Unmarshalling(*this);
}

template<typename T>
sptr<T> Parcel::ReadStrongParcelable()
{
    int32_t size = this->ReadInt32();
    if (size == 0) {
        return nullptr;
    }
    sptr<T> res(T::Unmarshalling(*this));
    return res;
}

} // namespace OHOS
#endif
