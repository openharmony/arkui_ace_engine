/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <string>
#include <vector>
#include "custom/shader_input_buffer.h"

namespace OHOS::Render3D {
bool ShaderInputBuffer::Alloc(uint32_t floatlength)
{
    if (floatlength > max) {
        return false;
    }
    if (IsValid() && (floatSize == floatlength)) {
        return true;
    }
    Delete();
    buffer = new float[floatlength];
    floatSize = floatlength;
    return true;
}
const float* ShaderInputBuffer::Map(uint32_t floatlength) const
{
    if (!IsValid()) {
        return nullptr;
    }
    if (floatlength > floatSize) {
        return nullptr;
    }
    return buffer;
}
uint32_t ShaderInputBuffer::FloatSize() const
{
    return floatSize;
}
uint32_t ShaderInputBuffer::ByteSize() const
{
    return floatSize * floatToByte;
}
void ShaderInputBuffer::Delete()
{
    if (IsValid()) {
        delete[] buffer;
    }
    buffer = nullptr;
    floatSize = 0u;
}
void ShaderInputBuffer::Update(float *buf, uint32_t size)
{
    if (!Map(size)) {
        return;
    }
}
void ShaderInputBuffer::Update(float value, uint32_t index)
{
    if (index >= floatSize) {
        return;
    }
    buffer[index] = value;
}
bool ShaderInputBuffer::IsValid() const
{
    return buffer && floatSize;
}
ShaderInputBuffer::~ShaderInputBuffer()
{
    Delete();
}
} // namespace OHOS::Render3D