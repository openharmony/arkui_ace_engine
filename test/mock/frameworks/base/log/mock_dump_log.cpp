/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

namespace OHOS::Ace {
SINGLETON_INSTANCE_IMPL(DumpLog);

DumpLog::DumpLog() = default;
DumpLog::~DumpLog() = default;

void DumpLog::Print(const std::string& content)
{
    (void)content;
}

void DumpLog::Print(int32_t depth, const std::string& content)
{
    (void)depth;
    (void)content;
}

bool DumpLog::OutPutBySize()
{
    return true;
}

void DumpLog::OutPutDefault() {}
void DumpLog::OutPutByCompress() {}

void DumpLog::PrintEndDumpInfoNG(bool isElement)
{
    (void)isElement;
}
} // namespace OHOS::Ace
