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

#include <ani.h>
#include <array>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <future>
#include <thread>
#include <map>
#include <string>
#include "frameworks/base/perfmonitor/perf_monitor.h"

static void performanceMonitor_begin([[maybe_unused]] ani_env *env, ani_string scene,
    ani_int startInputType, ani_string note)
{
    ani_size  strSize;
    env->String_GetUTF8Size(scene, &strSize);
    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();
    ani_size bytes_written = 0;
    env->String_GetUTF8(scene, utf8Buffer, strSize + 1, &bytes_written);
    utf8Buffer[bytes_written] = '\0';
    std::string sceneId = std::string(utf8Buffer);

    ani_size  strSize2;
    env->String_GetUTF8Size(note, &strSize2);
    std::vector<char> buffer2(strSize2 + 1);
    char* utf8Buffer2 = buffer2.data();
    ani_size bytes_written2 = 0;
    env->String_GetUTF8(note, utf8Buffer2, strSize2 + 1, &bytes_written2);
    utf8Buffer2[bytes_written2] = '\0';
    std::string noteStr = std::string(utf8Buffer2);

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/performanceMonitor/performanceMonitor;", &ns)) {
        return ;
    }

    ani_enum enumType;
    if (ANI_OK != env->FindEnum("Lperf_monitor_ani/#PerfActionType;", &enumType)) {
        std::cerr << "Find Enum Faild" << std::endl;
    }
    ani_enum_item enumItem;
    if (ANI_OK != env->Enum_GetEnumItemByIndex(enumType, startInputType, &enumItem)) {
        std::cerr << "Enum_GetEnumItemByIndex FAILD" << std::endl;
    }
    ani_int intValue;
    if (ANI_OK != env->EnumItem_GetValue_Int(enumItem, &intValue)) {
        std::cerr << "Enum_GetEnumItemByIndex FAILD" << std::endl;
    }

    OHOS::Ace::PerfMonitor* pMonitor = nullptr;
    pMonitor = OHOS::Ace::PerfMonitor::GetPerfMonitor();
    if (pMonitor != nullptr) {
        pMonitor->OHOS::Ace::PerfMonitor::Start(sceneId, static_cast<OHOS::Ace::PerfActionType>(intValue), noteStr);
    }
}

static void performanceMonitor_end([[maybe_unused]] ani_env *env, ani_string scene)
{
    ani_size  strSize;
    env->String_GetUTF8Size(scene, &strSize);
    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();
    ani_size bytes_written = 0;
    env->String_GetUTF8(scene, utf8Buffer, strSize + 1, &bytes_written);
    utf8Buffer[bytes_written] = '\0';
    std::string sceneId = std::string(utf8Buffer);

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/performanceMonitor/performanceMonitor;", &ns)) {
        return ;
    }

    OHOS::Ace::PerfMonitor* pMonitor = nullptr;
    pMonitor = OHOS::Ace::PerfMonitor::GetPerfMonitor();
    if (pMonitor != nullptr) {
        pMonitor->OHOS::Ace::PerfMonitor::End(sceneId, true);
    }
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        std::cerr << "Unsupported ANI_VERSION_1" << std::endl;
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/performanceMonitor/performanceMonitor;", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"performanceMonitor_begin", nullptr, reinterpret_cast<void *>(performanceMonitor_begin)},
        ani_native_function {"performanceMonitor_end", nullptr, reinterpret_cast<void *>(performanceMonitor_end)},
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
