/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "ace_forward_compatibility.h"

#include <unordered_set>
#ifdef OHOS_PLATFORM
#include "parameters.h"
#include "base/log/log_wrapper.h"
#else
#define LOGD(fmt, ...) ((void)0)
#define LOGI(fmt, ...) ((void)0)
#endif

namespace OHOS {
namespace Ace {
namespace {
    constexpr uint32_t ARKUI_NEW_PIPELINE_MIN_VERSION = 9;
#if defined(WINDOWS_PLATFORM)
    constexpr char ARKUI_LIB_NAME[] = "libace.dll";
#elif defined(MAC_PLATFORM)
    constexpr char ARKUI_LIB_NAME[] = "libace.dylib";
#elif defined(LINUX_PLATFORM)
    constexpr char ARKUI_LIB_NAME[] = "libace.so";
#else
    constexpr char ARKUI_LIB_NAME_COMPATIBLE[] = "libace_compatible.z.so";
    constexpr char ARKUI_LIB_NAME[] = "libace.z.so";
#endif
    const std::unordered_set<std::string> FORCE_OLD_PIPELINE {
        "com.ohos.launcher",
        "com.ohos.sceneboard"
    };
} // namespace

bool AceForwardCompatibility::isForceOldPipeline_ = true;
bool AceForwardCompatibility::isNewPipeline_ = true;
bool AceForwardCompatibility::isNewAppspawn_ = true;
bool AceForwardCompatibility::isInited_ = false;

void AceForwardCompatibility::Init(const std::string& bundleName, const uint32_t apiCompatibleVersion, bool forceFullUpdate)
{
    if (FORCE_OLD_PIPELINE.find(bundleName) != FORCE_OLD_PIPELINE.end()) {
        LOGD("AceForwardCompatibility [%{public}s] forced old pipeline", bundleName.c_str());
        isForceOldPipeline_ = true;
    } else {
        LOGD("AceForwardCompatibility [%{public}s] forced old pipeline with param", bundleName.c_str());
#ifdef OHOS_PLATFORM
        isForceOldPipeline_ = OHOS::system::GetBoolParameter("persist.arkui.libace.og", true);
#else
        isForceOldPipeline_ = true;
#endif
    }

    isNewPipeline_ = !isForceOldPipeline_
                     && (apiCompatibleVersion >= ARKUI_NEW_PIPELINE_MIN_VERSION)
                     && !forceFullUpdate;
    isInited_ = true;
    LOGI("AceForwardCompatibility [%{public}s] force:%{public}d newpipe:%{public}d",
         bundleName.c_str(), isForceOldPipeline_, isNewPipeline_);
}

bool AceForwardCompatibility::IsForceOldPipeline()
{
    if (isInited_) {
        return isForceOldPipeline_;
    }
#ifdef OHOS_PLATFORM
    return OHOS::system::GetBoolParameter("persist.arkui.libace.og", true);
#else
    return true;
#endif
}

bool AceForwardCompatibility::IsNewPipeline()
{
    if (isInited_) {
        return isNewPipeline_;
    }
    isNewAppspawn_ = !IsForceOldPipeline();
    return !IsForceOldPipeline();
}

const char* AceForwardCompatibility::GetAceLibName()
{
    const char* libName;
    if (IsNewPipeline()) {
        libName = ARKUI_LIB_NAME;
    } else {
        libName = ARKUI_LIB_NAME_COMPATIBLE;
    }
    LOGD("AceForwardCompatibility cur libName [%{public}s]", libName);
    return libName;
}

bool AceForwardCompatibility::PipelineChanged()
{
    return isNewPipeline_ != isNewAppspawn_;
}
} // namespace Ace
} // namespace OHOS
