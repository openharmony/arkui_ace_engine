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

#if !defined(_WIN32) && !defined(PREVIEW)
#include <mutex>

#include "base/log/log_wrapper.h"
#include "core/common/extra_modules/extra_modules_manager.h"
#include "interfaces/inner_api/ace/utils.h"
#endif

#include "core/components/common/properties/os_content.h"

namespace OHOS::Ace {

#if defined(_WIN32) || defined(PREVIEW)
bool OsContent::CallSendAction(const std::string&, const std::string&, const std::string&)
{
    return false;
}
#else
const char OS_CONTENT_MODULE_NAME[] = "os_content";
const char OS_CONTENT_SEND_ACTION_FUNC_NAME[] = "SendAction";

namespace {
using SendActionFunc = void (*)(const std::string&, const std::string&, const std::string&);

template<typename FuncType, const char* FuncName>
FuncType GetOrCreateFunc()
{
    static bool isLoaded = false;
    static FuncType loadedFunc = nullptr;
    static std::mutex osContentMutex;
    if (isLoaded) {
        return loadedFunc;
    }
    std::lock_guard<std::mutex> lock(osContentMutex);
    if (isLoaded) {
        return loadedFunc;
    }
    void* funcPtr = nullptr;
    auto& extraModuleManager = ExtraModulesManager::GetInstance();
    ErrCode errCode =
        extraModuleManager.GetCapability(OS_CONTENT_MODULE_NAME, FuncName, &funcPtr);
    if (errCode == ErrCode::SUCCESS) {
        loadedFunc = reinterpret_cast<FuncType>(funcPtr);
    } else if (errCode == ErrCode::SYMBOL_NOT_FOUND) {
        extraModuleManager.UnloadModule(OS_CONTENT_MODULE_NAME);
        LOGE("Failed to load symbol: %{public}s from nodule %{public}s",
            FuncName, OS_CONTENT_MODULE_NAME);
    } else {
        LOGE("Failed to load module: %{public}s", OS_CONTENT_MODULE_NAME);
    }
    isLoaded = true;
    return loadedFunc;
}
} // namespace

bool OsContent::CallSendAction(const std::string& scenario, const std::string& action,
    const std::string& jsonParams)
{
    auto sendActionFunc = GetOrCreateFunc<SendActionFunc, OS_CONTENT_SEND_ACTION_FUNC_NAME>();
    if (sendActionFunc) {
        sendActionFunc(scenario, action, jsonParams);
        return true;
    }
    LOGD("CallSendAction for [%{public}s], %{public}s]]", scenario.c_str(), action.c_str());
    return false;
}
#endif
} // namespace OHOS::Ace
