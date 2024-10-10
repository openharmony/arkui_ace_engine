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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_PROPERTIES_IMAGE_ANALYZER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_PROPERTIES_IMAGE_ANALYZER_H

#include <array>
#include <cstdint>
#include <functional>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/vector.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "third_party/node/src/js_native_api_types.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace {
enum class ImageAnalyzerState;
using OnAnalyzedCallback = std::optional<std::function<void(ImageAnalyzerState)>>;
using OnTextSelectedCallback = std::function<void()>;
using OnNotifySelectedStatusCallback = std::function<void(bool)>;

enum class ImageAnalyzerType {
    SUBJECT = 0,
    TEXT,
};

enum class ImageAnalyzerHolder {
    IMAGE = 0,
    CANVAS,
    XCOMPONENT,
    VIDEO_CUSTOM,
    VIDEO_DEFAULT,
    WEB,
    OTHERS,
};

enum class ImageAnalyzerState {
    UNSUPPORTED = 0,
    ONGOING,
    STOPPED,
    FINISHED
};

enum class Status {
    SELECTED = 0,
    UNSELECTED,
    MENU_SHOW,
    MENU_HIDE
};

struct TouchInfo {
    TouchPoint touchPoint;
    TouchType touchType = TouchType::CANCEL;
};

struct PixelMapInfo {
    float width = 0.0f;
    float height = 0.0f;
    NG::OffsetF overlayOffset = { 0.0f, 0.0f };
};

struct AIButtonConfig {
    std::vector<float> buttonOffset = {0.0f, 0.0f, 0.0f, 0.0f};
    bool isShow = true;
};

struct ImageAnalyzerConfig {
    NG::MarginProperty aiButtonMargin;
    std::set<ImageAnalyzerType> types;
    std::string tag;
    bool isShowAIButton = true;
};

struct ImageAnalyzerInnerConfig {
    float contentWidth = 0.0f;
    float contentHeight = 0.0f;
    float pixelMapWidth = 0.0f;
    float pixelMapHeight = 0.0f;
    NG::OffsetF overlayOffset = { 0.0f, 0.0f };
    ImageAnalyzerHolder holder = ImageAnalyzerHolder::OTHERS;
    ImageFit imageFit = ImageFit::COVER;
    Matrix4 transformMat = Matrix4::CreateIdentity();
    OnAnalyzedCallback onAnalyzed;
    Status selectedStatus = Status::SELECTED;
    Status menuStatus = Status::MENU_SHOW;
    OnTextSelectedCallback onTextSelected;
    void* pixelmapNapiVal = nullptr;
    OHOS::Ace::TouchInfo touchInfo;
    OnNotifySelectedStatusCallback onNotifySelectedStatus = nullptr;
    bool createAIEngine = false;
    
    void UpdateFromInfo(const PixelMapInfo& info)
    {
        contentWidth = info.width;
        contentHeight = info.height;
        pixelMapWidth = info.width;
        pixelMapHeight = info.height;
        overlayOffset = info.overlayOffset;
    }
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_PROPERTIES_IMAGE_ANALYZER_H