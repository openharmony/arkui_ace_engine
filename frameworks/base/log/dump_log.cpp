/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"

#include <string>

namespace OHOS::Ace {

DumpLog::DumpLog() = default;
DumpLog::~DumpLog() = default;

void DumpLog::Print(int32_t depth, const std::string& className, int32_t childSize)
{
    std::string space = "  ";
    for (int32_t i = 0; i < depth; ++i) {
        fwrite(space.c_str(), 1, space.length(), dumpFile_.get());
    }
    fwrite(space.c_str(), 1, space.length(), dumpFile_.get());
    std::string data = "|-> ";
    data.append(className);
    data.append(" childSize:" + std::to_string(childSize));
    data.append("\n");
    fwrite(data.c_str(), 1, data.length(), dumpFile_.get());

    for (auto& desc : description_) {
        for (int32_t i = 0; i < depth; ++i) {
            fwrite(space.c_str(), 1, space.length(), dumpFile_.get());
        }
        std::string data = "";
        if (childSize == 0) {
            data = "      ";
        } else {
            data = "    | ";
        }
        data.append(desc);
        fwrite(data.c_str(), 1, data.length(), dumpFile_.get());
    }
    description_.clear();
    description_.shrink_to_fit();
}

void DumpLog::Print(const std::string& content)
{
    Print(0, content);
}

void DumpLog::Print(int32_t depth, const std::string& content)
{
    std::string space = " ";
    for (int32_t i = 0; i < depth; ++i) {
        fwrite(space.c_str(), 1, space.length(), dumpFile_.get());
    }

    std::string data = content + "\n";
    fwrite(data.c_str(), 1, data.length(), dumpFile_.get());
}

void DumpLog::Reset()
{
    dumpFile_.reset();
}

} // namespace OHOS::Ace