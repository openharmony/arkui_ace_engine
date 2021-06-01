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

#include "base/log/ace_trace.h"

#include <atomic>
#include <mutex>
#include <string>
#include <vector>

#include <pthread.h>

#include "bytrace.h"

#include "base/log/log.h"
#include "base/utils/macros.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace {
namespace {

pthread_key_t g_threadLocalKey;

bool InitThreadLocalData()
{
    static std::once_flag onceFlag;
    static bool initialized = false;
    std::call_once(onceFlag, []() {
        auto retVal = pthread_key_create(&g_threadLocalKey, [](void* ptr) {
            if (ptr != nullptr) {
                delete reinterpret_cast<std::vector<std::string>*>(ptr);
            }
        });
        if (retVal == 0) {
            initialized = true;
        }
    });
    return initialized;
}

bool PushString(const std::string& str)
{
    auto vector = reinterpret_cast<std::vector<std::string>*>(pthread_getspecific(g_threadLocalKey));
    if (vector == nullptr) {
        vector = new std::vector<std::string>();
        if (pthread_setspecific(g_threadLocalKey, vector) != 0) {
            delete vector;
            return false;
        }
    }
    vector->emplace_back(str);
    return true;
}

bool PopString(std::string& str)
{
    auto vector = reinterpret_cast<std::vector<std::string>*>(pthread_getspecific(g_threadLocalKey));
    if (vector == nullptr || vector->empty()) {
        return false;
    }
    str = std::move(vector->back());
    vector->pop_back();
    return true;
}

} // namespace

bool AceTraceEnabled()
{
    return SystemProperties::GetTraceEnabled();
}

void AceTraceBegin(const char* name)
{
    if (name == nullptr) {
        return;
    }

    if (InitThreadLocalData()) {
        std::string nameStr(name);
        if (PushString(nameStr)) {
            StartTrace(BYTRACE_TAG_ACE, nameStr);
        } else {
            LOGW("Failed push current tag name");
        }
    } else {
        LOGW("Failed to initialized local thread data");
    }
}

void AceTraceEnd()
{
    if (InitThreadLocalData()) {
        std::string nameStr;
        if (PopString(nameStr)) {
            FinishTrace(BYTRACE_TAG_ACE, nameStr);
        } else {
            LOGW("Failed pop last tag name");
        }
    } else {
        LOGW("Failed to initialized local thread data");
    }
}

} // namespace OHOS::Ace
