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

#include "cj_environment.h"

#include "core/common/environment/environment_proxy.h"
#include "frameworks/base/i18n/localization.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

extern "C" {
NativeOptionBool FfiOHOSAceFrameworkEnvironmentGetAccessibilityEnabled()
{
    NativeOptionBool result {.hasValue = false, .value = false };
#if defined(PREVIEW)
    return result;
#else
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return result;
    }
    auto executor = container->GetTaskExecutor();

    result.hasValue = true;
    std::string val = EnvironmentProxy::GetInstance()->GetEnvironment(executor)->GetAccessibilityEnabled();
#endif
    result.value = val.c_str();
    return result;
}

NativeOptionInt32 FfiOHOSAceFrameworkEnvironmentGetColorMode()
{
    NativeOptionInt32 result {
        .hasValue = true,
        .value = static_cast<int32_t>(SystemProperties::GetColorMode())
    };
    return result;
}

NativeOptionFloat32 FfiOHOSAceFrameworkEnvironmentGetFontScale()
{
    NativeOptionFloat32 result {.hasValue = false, .value = 0.0};

    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return result;
    }
    auto context = container->GetPipelineContext();
    result.hasValue = true;
    result.value = context->GetFontScale();
    return result;
}

NativeOptionFloat32 FfiOHOSAceFrameworkEnvironmentGetFontWeightScale()
{
    NativeOptionFloat32 result {
        .hasValue = true,
        .value = SystemProperties::GetFontWeightScale()
    };
    return result;
}

NativeOptionInt32 FfiOHOSAceFrameworkEnvironmentGetLayoutDirection()
{
    auto isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    NativeOptionInt32 result {
        .hasValue = true,
        .value =  isRTL ? 0 : 1
    };
    return result;
}

NativeOptionCString FfiOHOSAceFrameworkEnvironmentGetLanguageCode()
{
    NativeOptionCString result {.hasValue = false, .value = Utils::MallocCString("").value};
    auto container = Container::Current();
    if (!container) {
        LOGW("Initialize is not complete, cannot get the language");
        return result;
    }
    auto location = Localization::GetInstance();
    auto language = location->GetLanguage();
    result.hasValue = true;
    result.value = Utils::MallocCString(language).value;
    return result;
}
}