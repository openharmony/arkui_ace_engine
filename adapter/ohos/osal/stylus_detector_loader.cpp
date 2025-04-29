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

#include "core/common/stylus/stylus_detector_loader.h"

#include <dlfcn.h>

#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace {
namespace {
#if (defined(__aarch64__) || defined(__x86_64__))
const std::string STYLUS_CLIENT_SO_PATH = "/system/lib64/libstylus_innerapi.z.so";
#else
const std::string STYLUS_CLIENT_SO_PATH = "/system/lib/libstylus_innerapi.z.so";
#endif
} // namespace
std::shared_ptr<StylusDetectorLoader> StylusDetectorLoader::Load()
{
    auto engLib(std::make_shared<StylusDetectorLoader>());
    auto ret = engLib->Init();
    if (!ret) {
        LOGD("Stylus detector loader instance init failed.");
        return nullptr;
    }
    return engLib;
}

StylusDetectorLoader::~StylusDetectorLoader()
{
    Close();
}

bool StylusDetectorLoader::Init()
{
    if (stylusSoLoaded_ && libraryHandle_ != nullptr && createStylusDetectorInstance_ != nullptr &&
        destroyStylusDetectorInstance_ != nullptr) {
        return true;
    }
    libraryHandle_ = dlopen(STYLUS_CLIENT_SO_PATH.c_str(), RTLD_LAZY);
    if (libraryHandle_ == nullptr) {
        return false;
    }
    createStylusDetectorInstance_ =
        (StylusDetectorInterface* (*)()) dlsym(libraryHandle_, "CreateStylusDetectorInstance");
    destroyStylusDetectorInstance_ =
        (void (*)(StylusDetectorInterface*))dlsym(libraryHandle_, "DestroyStylusDetectorInstance");
    if (createStylusDetectorInstance_ == nullptr || destroyStylusDetectorInstance_ == nullptr) {
        TAG_LOGI(AceLogTag::ACE_STYLUS, "Stylus detector loader instance loading failed.");
        Close();
        return false;
    }
    stylusSoLoaded_ = true;
    return true;
}

StylusDetectorInstance StylusDetectorLoader::CreateStylusDetector()
{
    if (!createStylusDetectorInstance_ || !destroyStylusDetectorInstance_) {
        return nullptr;
    }

    return { createStylusDetectorInstance_(), [lib = shared_from_this(), destroy = destroyStylusDetectorInstance_](
                                                  StylusDetectorInterface* e) { destroy(e); } };
}

void StylusDetectorLoader::Close()
{
    if (libraryHandle_ != nullptr) {
        dlclose(libraryHandle_);
    }
    stylusSoLoaded_ = false;
    libraryHandle_ = nullptr;
    createStylusDetectorInstance_ = nullptr;
    destroyStylusDetectorInstance_ = nullptr;
}

} // namespace OHOS::Ace