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

#include "base/memory/memory_monitor.h"
namespace OHOS::Ace {

bool MemoryMonitor::isEnable_ = false;

class MemoryMonitorImpl : public MemoryMonitor {
public:
    void Add(void* ptr) final {}

    void Remove(void* ptr) final {}

    void Update(void* ptr, size_t size, const std::string& typeName) final {}

    void Dump() const final {}
};

MemoryMonitor& MemoryMonitor::GetInstance()
{
    static MemoryMonitorImpl instance;
    return instance;
}

} // namespace OHOS::Ace
