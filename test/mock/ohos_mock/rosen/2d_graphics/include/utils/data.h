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

#ifndef DATA_H
#define DATA_H

#include <memory>

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Data {
public:
    Data() noexcept;
    virtual ~Data() {};
    bool BuildFromMalloc(const void* data, size_t length);
    bool BuildWithCopy(const void* data, size_t length);
    typedef void (*DataReleaseProc)(const void* ptr, void* context);
    bool BuildWithProc(const void* ptr, size_t length, DataReleaseProc proc, void* ctx);
    bool BuildWithoutCopy(const void* data, size_t length);
    bool BuildUninitialized(size_t length);
    bool BuildEmpty();
    void* WritableData();
    size_t GetSize() const;
    const void* GetData() const;
    static std::shared_ptr<Data> MakeFromFileName(const char path[]);
    std::shared_ptr<Data> Serialize() const;
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
