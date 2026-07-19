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

#include "ashmem.h"

#include <memory>

namespace OHOS {
sptr<Ashmem> Ashmem::CreateAshmem(const char *name, int32_t size)
{
    return sptr<Ashmem>(new Ashmem(0, size));
}

Ashmem::Ashmem(int fd, int32_t size)
{
    size_ = size;
}

Ashmem::~Ashmem() = default;

void Ashmem::CloseAshmem() {}
void Ashmem::UnmapAshmem() {}
bool Ashmem::MapReadAndWriteAshmem()
{
    return true;
}

bool Ashmem::WriteToAshmem(const void *data, int32_t size, int32_t offset)
{
    return true;
}

bool Ashmem::MapReadOnlyAshmem()
{
    return true;
}

int32_t Ashmem::GetAshmemSize() const
{
    return size_;
}

const void* Ashmem::ReadFromAshmem(int32_t size, int32_t offset) const
{
    return nullptr;
}
}
