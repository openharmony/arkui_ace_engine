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

#include "core/common/transform/input_compatible_manager.h"

#include <dlfcn.h>

#include "base/log/log.h"
#include "base/utils/time_util.h"
#include "frameworks/core/common/ace_application_info.h"
#include "frameworks/core/event/event_info_convertor.h"

namespace OHOS::Ace {
namespace {
#if (defined(__aarch64__) || defined(__x86_64__))
const std::string TRANSFORM_SO_PATH = "/system/lib64/libtransform_interaction_ext.z.so";
#else
const std::string TRANSFORM_SO_PATH = "/system/lib/libtransform_interaction_ext.z.so";
#endif
constexpr int64_t LOG_DURATION = 5000;
constexpr int64_t TRANSLATE_NS_TO_MS = 1000000;
} // namespace

InputCompatibleManager& InputCompatibleManager::GetInstance()
{
    static InputCompatibleManager instance;
    return instance;
}

InputCompatibleManager::~InputCompatibleManager()
{
    UnloadProductCompatiblePolicy();
}

void InputCompatibleManager::LoadProductCompatiblePolicy()
{
    if (transformSoLoaded_ && libraryHandle_ != nullptr && productPolicy_ != nullptr) {
        return;
    }
    libraryHandle_ = dlopen(TRANSFORM_SO_PATH.c_str(), RTLD_LAZY);
    if (libraryHandle_ == nullptr) {
        const char* error = dlerror();
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "AceTransform load failed: %{public}s", error);
        return;
    }
    auto getInputCompatiblePolicyInstance =
        (Kit::InputCompatiblePolicy* (*)()) dlsym(libraryHandle_, "GetInputCompatiblePolicyInstance");
    if (getInputCompatiblePolicyInstance == nullptr) {
        const char* error = dlerror();
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "AceTransform load failed: %{public}s", error);
        Close();
        return;
    }
    productPolicy_ = getInputCompatiblePolicyInstance();
    transformSoLoaded_ = true;
    Close();
    return;
}

void InputCompatibleManager::UnloadProductCompatiblePolicy()
{
    Close();
    libraryHandle_ = nullptr;
    productPolicy_ = nullptr;
    transformSoLoaded_ = false;
}

void InputCompatibleManager::Close()
{
    if (libraryHandle_ != nullptr) {
        dlclose(libraryHandle_);
    }
}

bool InputCompatibleManager::IsCompatibleConvertingEnabledFor(Kit::InputCompatibleSource source)
{
    static std::unordered_map<Kit::InputCompatibleSource, bool> convertingEnabledResult;
    static bool transformEnable = SystemProperties::GetTransformEnabled();
    static bool mouseTransEnabled = SystemProperties::GetCompatibleInputTransEnabled();
    static int64_t lastLogTimeStamp = GetSysTimestamp();

    if (convertingEnabledResult.find(source) != convertingEnabledResult.end()) {
        auto currentTime = GetSysTimestamp();
        if ((currentTime - lastLogTimeStamp) >= LOG_DURATION * TRANSLATE_NS_TO_MS) {
            TAG_LOGI(AceLogTag::ACE_UIEVENT,
                "IsCompatibleConvertingEnabledFor get result successfully \n "
                "transformEnable is %{public}d, mousetransEnable is %{public}d \n"
                "result is %{public}d.",
                transformEnable, mouseTransEnabled, convertingEnabledResult[source]);
            lastLogTimeStamp = currentTime;
        }
        return convertingEnabledResult[source];
    }

    if (!transformEnable || !mouseTransEnabled) {
        convertingEnabledResult[source] = false;
        AceApplicationInfo::GetInstance().SetMouseTransformEnable(convertingEnabledResult[source]);
        return convertingEnabledResult[source];
    }
    if (productPolicy_) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "Load So successfully");
        convertingEnabledResult[source] = productPolicy_->IsInputCompatibleConvertingNeeded(source);
        AceApplicationInfo::GetInstance().SetMouseTransformEnable(convertingEnabledResult[source]);
        return convertingEnabledResult[source];
    }

    convertingEnabledResult[source] = NG::EventInfoConvertor::IfNeedMouseTransform();
    AceApplicationInfo::GetInstance().SetMouseTransformEnable(convertingEnabledResult[source]);
    return convertingEnabledResult[source];
}
} // namespace OHOS::Ace
