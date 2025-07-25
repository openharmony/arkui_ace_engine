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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INTERACTION_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INTERACTION_DATA_H

#include "base/image/pixel_map.h"
#include "core/gestures/drag_event.h"

namespace OHOS::Ace {
constexpr float PERCISION { 1E-6 };
enum class DragCursorStyleCore {
    DEFAULT = 0,
    FORBIDDEN,
    COPY,
    MOVE
};

struct ShadowInfoCore {
    RefPtr<PixelMap> pixelMap;
    int32_t x = -1;
    int32_t y = -1;
};

struct ShadowOffsetData {
    int32_t offsetX = -1;
    int32_t offsetY = -1;
    int32_t width = -1;
    int32_t height = -1;
};

struct DragDataCore {
    std::vector<ShadowInfoCore> shadowInfos;
    std::vector<uint8_t> buffer;
    std::string udKey;
    std::string extraInfo;
    std::string filterInfo;
    int32_t sourceType = -1;
    int32_t dragNum = -1;
    int32_t pointerId = -1;
    int32_t displayX = -1;
    int32_t displayY = -1;
    int32_t displayId = -1;
    int32_t mainWindow = -1;
    bool hasCanceledAnimation = false;
    bool hasCoordinateCorrected = false;
    std::map<std::string, int64_t> summarys;
    bool isDragDelay = false;
    std::map<std::string, int64_t> detailedSummarys;
    std::map<std::string, std::vector<int32_t>> summaryFormat;
    int32_t version { 0 };
    int64_t totalSize { -1 };
};

struct DragBundleInfo {
    std::string bundleName;
    bool isRemoteDev { false };
};

struct DragNotifyMsg {
    int32_t displayX = -1;
    int32_t displayY = -1;
    int32_t targetPid = -1;
    DragRet result { DragRet::DRAG_FAIL };
    DragBehavior dragBehavior { DragBehavior::UNKNOWN };
    bool isInnerAndOuterTriggerBothNeeded = true;
};

struct DragDropRet {
    DragRet result { DragRet::DRAG_FAIL };
    bool hasCustomAnimation = false;
    int32_t mainWindow = -1;
    DragBehavior dragBehavior { DragBehavior::UNKNOWN };
};

enum class DragState {
    ERROR = 0,
    START,
    STOP,
    CANCEL,
    MOTION_DRAGGING
};

enum class PreviewType {
    FOREGROUND_COLOR = 0,
    OPACITY = 1,
    RADIUS = 2,
    SCALE = 3
};

struct PreviewStyle {
    std::vector<PreviewType> types;
    uint32_t foregroundColor = 0;
    int32_t opacity = -1;
    int32_t radius = -1;
    float scale = -1;

    bool operator == (const PreviewStyle &other) const
    {
        return types == other.types && foregroundColor == other.foregroundColor && opacity == other.opacity &&
               radius == other.radius && fabsf(scale - other.scale) < PERCISION;
    }

    bool operator!=(const PreviewStyle &other) const
    {
        return !(*this == other);
    }
};

struct PreviewAnimation {
    int32_t duration = -1;
    std::string curveName;
    std::vector<float> curve;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INTERACTION_DATA_H