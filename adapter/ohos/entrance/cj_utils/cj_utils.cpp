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

#include "adapter/ohos/entrance/cj_utils/cj_utils.h"

#include <regex>

#include "interfaces/inner_api/ace/utils.h"

#include "base/log/log.h"

namespace OHOS::Ace::CJUtils {
constexpr char CJ_FRONTEND_LIB_NAME[] = "libcj_frontend_ohos.z.so";
constexpr char CJ_FRONTEND_CREATE_FUNC[] = "OHOS_ACE_CreateCJFrontend";
using GetCJFrontendCreateFunc = void* (*)(bool, bool);

void* LoadCjFrontend(bool isNewPipeline, bool isStageModel)
{
    LIBHANDLE handle = LOADLIB(CJ_FRONTEND_LIB_NAME);
    if (handle == nullptr) {
        LOGE("LOADLIB cj frontend lib failed.");
        return nullptr;
    }
    auto createFunc = reinterpret_cast<GetCJFrontendCreateFunc>(LOADSYM(handle, CJ_FRONTEND_CREATE_FUNC));
    if (createFunc == nullptr) {
        LOGE("LOADSYM CJ_FRONTEND_CREATE_FUNC failed");
        FREELIB(handle);
        return nullptr;
    }
    return createFunc(isNewPipeline, isStageModel);
}

bool isCjAbility(const std::string& info)
{
    // in cj application, the srcEntry format should be packageName.AbilityClassName.
    std::string pattern = "^([a-zA-Z0-9_]+\\.)+[a-zA-Z0-9_]+$";
    return std::regex_match(info, std::regex(pattern));
}

bool IsCJFrontendContext(OHOS::AbilityRuntime::Context* context)
{
    LOGD("IsCJFrontendContext start.");
    if (!context) {
        return false;
    }
    auto moduleInfo = context->GetHapModuleInfo();
    if (!moduleInfo) {
        return false;
    }
    auto abilityInfos = moduleInfo->abilityInfos;
    if (abilityInfos.empty()) {
        return false;
    }
    return isCjAbility(abilityInfos.front().srcEntrance);
}
} // namespace OHOS::Ace::CJUtils