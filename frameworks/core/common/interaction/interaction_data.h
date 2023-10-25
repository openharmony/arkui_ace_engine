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
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace {
enum class DragCursorStyleCore {
    DEFAULT = 0,
    FORBIDDEN,
    COPY,
    MOVE
};

struct ShadowInfoCore {
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
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
    ShadowInfoCore shadowInfo;
    std::vector<uint8_t> buffer;
    std::string udKey;
    std::string filterInfo;
    std::string extraInfo;
    int32_t sourceType = -1;
    int32_t dragNum = -1;
    int32_t pointerId = -1;
    int32_t displayX = -1;
    int32_t displayY = -1;
    int32_t displayId = -1;
    bool hasCanceledAnimation = false;
};

struct DragNotifyMsg {
    int32_t displayX = -1;
    int32_t displayY = -1;
    int32_t targetPid = -1;
#ifdef ENABLE_DRAG_FRAMEWORK
    DragRet result { DragRet::DRAG_FAIL };
#endif
};

struct DragDropRet {
#ifdef ENABLE_DRAG_FRAMEWORK
    DragRet result { DragRet::DRAG_FAIL };
#endif
    bool hasCustomAnimation = false;
    int32_t windowId = -1;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INTERACTION_DATA_H