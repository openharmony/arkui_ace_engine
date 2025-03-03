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

#include "adapter/ohos/osal/thp_extra_manager_impl.h"

#include <dlfcn.h>

#include "adapter/ohos/entrance/utils.h"

namespace OHOS::Ace::NG {
void* THPExtraManagerImpl::lib_ = nullptr;

bool THPExtraManagerImpl::Init()
{
    ThpExtraRunCommand_ = [](const char* command, const char* parameters) -> const char* {
        return "ok";
    };
    if (lib_ == nullptr) {
        lib_ = dlopen("/system/lib64/libthp_extra_innerapi.z.so", RTLD_LAZY);
    }
    if (lib_ == nullptr) {
        LOGI("Failed to open libthp_extra_innerapi.z.so, reason: %{public}s", dlerror());
        return false;
    }
    ThpExtraRunCommand_ = reinterpret_cast<ThpExtraRunCommandFunc>(dlsym(lib_, "ThpExtraRunCommand"));
    if (ThpExtraRunCommand_ == nullptr) {
        ThpExtraRunCommand_ = [](const char* command, const char* parameters) -> const char* {
            return "ok";
        };
        LOGI("Failed to load ThpExtraRunCommand");
        return false;
    }
    auto ThpExtraGetConfigStr = reinterpret_cast<ThpExtraGetConfigStrFunc>(dlsym(lib_, "ThpExtraGetConfigStr"));
    if (ThpExtraGetConfigStr == nullptr) {
        LOGI("Load ThpExtraGetConfigStr failed");
        return false;
    }

    std::string jsonStr = std::string(ThpExtraGetConfigStr());
    if (jsonStr.empty()) {
        return false;
    }
    auto rootJson = JsonUtil::ParseJsonString(jsonStr);
    if (!rootJson || !rootJson->IsValid()) {
        return false;
    }
    auto hotzone = rootJson->GetObject("hotzone");
    if (hotzone == nullptr) {
        return false;
    }
    enable_ = hotzone->GetBool("enable", false);
    height_ = hotzone->GetInt("height");
    width_ = hotzone->GetInt("width");
    if (!enable_) {
        return false;
    }
    return true;
}

const char* THPExtraManagerImpl::ThpExtraRunCommand(const char* command, const char* parameters)
{
    if (ThpExtraRunCommand_) {
        return ThpExtraRunCommand_(command, parameters);
    }
    return "";
}

int32_t THPExtraManagerImpl::GetHeight(void) const
{
    return height_;
}

int32_t THPExtraManagerImpl::GetWidth(void) const
{
    return width_;
}
}  // namespace OHOS::Ace::NG
