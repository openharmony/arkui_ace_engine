/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_IMAGE_ANALYZER_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_IMAGE_ANALYZER_INTERFACE_H

#include <functional>
#include <string>

#include "image_analyzer.h"

namespace OHOS::Ace {
class ImageAnalyzerInterface {
public:
    virtual bool IsImageAnalyzerSupported() = 0;
    virtual void BuildNodeFunc(
        void* pixelMap, void* config, ImageAnalyzerInnerConfig* uiConfig, void** overlayData) {};
    virtual void BuildNodeFunc(std::string uri, void* pixelMap, int frameTimestamp, void* config,
        ImageAnalyzerInnerConfig* uiConfig, void** overlayData) {};
    virtual void UpdateImage(
        void** overlayData, void* pixelMap, void* config, ImageAnalyzerInnerConfig* uiConfig) {};
    virtual void UpdateImage(void** overlayData, std::string uri, void* pixelMap, int frameTimestamp,
        void* config, ImageAnalyzerInnerConfig* uiConfig) {};
    virtual void UpdateConfig(void** overlayData, void* config) {};
    virtual void UpdateInnerConfig(void** overlayData, ImageAnalyzerInnerConfig* config) = 0;
    virtual void Release(void** overlayData) = 0;
    virtual void UpdatePressOverlay(void** overlayData, ImageAnalyzerInnerConfig* config) = 0;
    virtual void UpdateOverlayStatus(void** overlayData, ImageAnalyzerInnerConfig* config) = 0;
    virtual void UpdateOverlayActiveStatus(void** overlayData, bool status) = 0;
    virtual void UpdateAIButtonConfig(void** overlayData, AIButtonConfig* config) = 0;
protected:
    virtual ~ImageAnalyzerInterface() {}
}; // namespace OHOS::Ace
}
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_IMAGE_ANALYZER_INTERFACE_H
