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
#include "hilog/log.h"
#ifdef OHOS_PLATFORM
#include "parameters.h"
#endif

namespace OHOS {
namespace Ace {
namespace {
    constexpr OHOS::HiviewDFX::HiLogLabel ACE_COMPATIBLITY_LABEL = { LOG_CORE, 0xD003900, "ACE_COMPATIBLITY" };
    constexpr uint32_t ARKUI_NEW_PIPELINE_MIN_VERSION = 9;
#if defined(WINDOWS_PLATFORM)
    constexpr char ARKUI_LIB_NAME_COMPATIBLE[] = "libace_compatible.dll";
    constexpr char ARKUI_LIB_NAME[] = "libace.dll";
#elif defined(MAC_PLATFORM)
    constexpr char ARKUI_LIB_NAME_COMPATIBLE[] = "libace_compatible.dylib";
    constexpr char ARKUI_LIB_NAME[] = "libace.dylib";
#elif defined(LINUX_PLATFORM)
    constexpr char ARKUI_LIB_NAME_COMPATIBLE[] = "libace_compatible.so";
    constexpr char ARKUI_LIB_NAME[] = "libace.so";
#else
    constexpr char ARKUI_LIB_NAME_COMPATIBLE[] = "libace_compatible.z.so";
    constexpr char ARKUI_LIB_NAME[] = "libace.z.so";
#endif

#define LOGD(fmt, ...)            \
    (void)OHOS::HiviewDFX::HiLog::Debug(ACE_COMPATIBLITY_LABEL, "[%{public}d]" fmt, __LINE__, ##__VA_ARGS__)

#define LOGI(fmt, ...)            \
    (void)OHOS::HiviewDFX::HiLog::Info(ACE_COMPATIBLITY_LABEL, "[%{public}d]" fmt, __LINE__, ##__VA_ARGS__)
} // namespace

void AceForwardCompatibility::Init(const std::string& bundleName, const uint32_t apiCompatibleVersion, bool deprecated)
{
#ifdef OHOS_PLATFORM
    isForceOldPipeline_ = OHOS::system::GetBoolParameter("persist.arkui.libace.og", true);
#else
    isForceOldPipeline_ = true;
#endif

    isNewPipeline_ = (apiCompatibleVersion >= ARKUI_NEW_PIPELINE_MIN_VERSION) && !deprecated;
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
        return isNewPipeline_ && !isForceOldPipeline_;
    }
    isNewAppspawn_ = !IsForceOldPipeline();
    return !IsForceOldPipeline();
}

bool AceForwardCompatibility::IsUseNG()
{
    return isNewPipeline_;
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
    return (isNewPipeline_ && !isForceOldPipeline_) != isNewAppspawn_;
}
} // namespace Ace
} // namespace OHOS
