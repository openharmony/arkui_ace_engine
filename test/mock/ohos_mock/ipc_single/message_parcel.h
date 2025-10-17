/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_IPC_MESSAGE_PARCEL_H
#define OHOS_IPC_MESSAGE_PARCEL_H

#include <string>
#include <vector>

#include "ashmem.h"
#include "iremote_object.h"
#include "refbase.h"

namespace OHOS {
class MessageParcel {
public:
    MessageParcel() = default;
    ~MessageParcel() = default;

    bool WriteRemoteObject(const sptr<IRemoteObject> &object)
    {
        return true;
    }

    sptr<IRemoteObject> ReadRemoteObject()
    {
        return sptr<IRemoteObject>(nullptr);
    }

    bool WriteFileDescriptor(int fd)
    {
        return true;
    }

    int ReadFileDescriptor()
    {
        return 0;
    }

    bool ContainFileDescriptors() const
    {
        return 0;
    }

    bool WriteInterfaceToken(std::u16string name)
    {
        if (!name.empty()) {
            interfaceToken_ = name;
            return true;
        }
        return false;
    }

    std::u16string ReadInterfaceToken()
    {
        return interfaceToken_;
    }

    bool WriteRawData(const void *data, size_t size)
    {
        return true;
    }

    const void* ReadRawData(size_t size)
    {
        return nullptr;
    }

    bool RestoreRawData(std::shared_ptr<char> rawData, size_t size)
    {
        return true;
    }

    const void *GetRawData() const
    {
        return nullptr;
    }

    size_t GetRawDataSize() const
    {
        return 0;
    }

    size_t GetRawDataCapacity() const
    {
        return 0;
    }

    void WriteNoException()
    {
        return;
    }

    int32_t ReadException()
    {
        return 0;
    }

    bool WriteAshmem(sptr<Ashmem> ashmem)
    {
        return 0;
    }

    sptr<Ashmem> ReadAshmem()
    {
        return nullptr;
    }

    void ClearFileDescriptor()
    {
        return;
    }

    void SetClearFdFlag()
    {
        needCloseFd_ = true;
    };

    bool Append(MessageParcel& data)
    {
        return true;
    }

    void PrintBuffer(const char *funcName, const size_t lineNum)
    {
        return;
    }

    std::u16string GetInterfaceToken() const
    {
        return std::u16string(u"mockToken");
    }

    bool IsOwner()
    {
        return true;
    }

    // mock functions in parcel.h
    int32_t ReadInt32()
    {
        return 0;
    }

    bool WriteInt32(int32_t value)
    {
        return true;
    }

    const std::string ReadString()
    {
        return std::string("mockString");
    }

    bool ReadStringVector(std::vector<std::string>* val)
    {
        (*val).emplace_back("mockString");
        return true;
    }

    bool ReadInt32Vector(std::vector<int32_t> *val)
    {
        (*val).emplace_back(0);
        return true;
    }

    bool ReadBool()
    {
        return false;
    }

    bool needCloseFd_ = false;
    std::u16string interfaceToken_;
};
} // namespace OHOS
#endif // OHOS_IPC_MESSAGE_PARCEL_H
