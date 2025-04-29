/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include <fstream>
#include <unordered_set>

#include "arkui_log.h"
#ifdef OHOS_PLATFORM
#include "parameters.h"
#endif

namespace OHOS {
namespace Ace {
namespace {
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
const std::unordered_set<std::string> FORCE_OLD_PIPELINE {
    "com.ohos.launcher",
    "com.ohos.sceneboard"
};
#ifdef OHOS_PLATFORM
const std::string KERNEL_TYPE_HM = "hongmeng";
const std::string RECLAIM_FILEPAGE_STRING_FOR_HM = "1";
#endif
const std::string RECLAIM_FILEPAGE_STRING_FOR_LINUX = "file";
} // namespace

void AceForwardCompatibility::Init(const std::string& bundleName, const uint32_t apiCompatibleVersion, bool forceFullUpdate)
{
    if (FORCE_OLD_PIPELINE.find(bundleName) != FORCE_OLD_PIPELINE.end()) {
        isForceOldPipeline_ = true;
    } else {
#ifdef OHOS_PLATFORM
        isForceOldPipeline_ = OHOS::system::GetBoolParameter("persist.arkui.libace.og", true);
#else
        isForceOldPipeline_ = true;
#endif
    }

    isNewPipeline_ = (apiCompatibleVersion >= ARKUI_NEW_PIPELINE_MIN_VERSION) && !forceFullUpdate;
    isInited_ = true;
    LOGI("AceForwardCompatibility [%{public}s] force:%{public}d newpipe:%{public}d", bundleName.c_str(),
        isForceOldPipeline_, isNewPipeline_);
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
    return libName;
}

bool AceForwardCompatibility::PipelineChanged()
{
    return (isNewPipeline_ && !isForceOldPipeline_) != isNewAppspawn_;
}

void AceForwardCompatibility::ReclaimFileCache(int32_t pid)
{
    LOGI("ReclaimFileCache start pid:%{public}d", pid);
    if (pid <= 0) {
        LOGE("get invalid pid:%{public}d", pid);
        return;
    }
    std::string path = "/proc/" + std::to_string(pid) +"/reclaim";
    std::string content = RECLAIM_FILEPAGE_STRING_FOR_LINUX;
#ifdef OHOS_PLATFORM

    if (system::GetParameter("ohos.boot.kernel", "") == KERNEL_TYPE_HM) {
        content = RECLAIM_FILEPAGE_STRING_FOR_HM;
    }
#endif
    std::ofstream outfile(path);
    if (outfile.is_open()) {
        outfile << content;
        outfile.close();
    } else {
        LOGE("ace reclaim exception");
    }
    LOGI("ReclaimFileCache end");
}
} // namespace Ace
} // namespace OHOS
