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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_LOADER_H

#include <memory>
#include <string>

#include "interfaces/inner_api/ace/stylus/stylus_detector_interface.h"

namespace OHOS::Ace {
using StylusDetectorInstance = std::unique_ptr<StylusDetectorInterface, std::function<void(StylusDetectorInterface*)>>;

class StylusDetectorLoader final : public std::enable_shared_from_this<StylusDetectorLoader> {
public:
    static std::shared_ptr<StylusDetectorLoader> Load();
    StylusDetectorLoader() = default;
    virtual ~StylusDetectorLoader();

    StylusDetectorLoader(const StylusDetectorLoader&) = delete;
    StylusDetectorLoader(StylusDetectorLoader&&) = delete;
    StylusDetectorLoader& operator=(const StylusDetectorLoader&) = delete;
    StylusDetectorLoader& operator=(StylusDetectorLoader&&) = delete;
    StylusDetectorInstance CreateStylusDetector();

private:
    bool Init();
    void Close();

    void* libraryHandle_ = nullptr;
    StylusDetectorInterface* (*createStylusDetectorInstance_)() = nullptr;
    void (*destroyStylusDetectorInstance_)(StylusDetectorInterface*) = nullptr;
    bool stylusSoLoaded_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STYLUS_STYLUS_DETECTOR_DEFAULT_H