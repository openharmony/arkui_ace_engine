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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_UTILS_INTERNAL_DRAG_ACTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_UTILS_INTERNAL_DRAG_ACTION_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <mutex>
#include <pthread.h>
#include <string>
#include <vector>

#include "base/geometry/dimension_offset.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/gestures/drag_event.h"

namespace OHOS::Ace::NG {

enum class DragAdapterState { INIT, PENDING, SENDING, REJECT, SUCCESS };

enum class DragAdapterStatus { UNKNOWN = -1, STARTED, ENDED };
struct ArkUIInternalDragAndDropInfo {
    OHOS::Ace::NG::DragEvent dragEvent;
    DragAdapterStatus dragStatus;
};

struct ArkUIInteralDragAction {
    int32_t instanceId;
    int32_t pointer;
    void** pixelMapArray;
    int32_t size;
    int32_t x;
    int32_t y;
    void* data;
    int32_t displayId = 0;
    OHOS::Ace::NG::ArkUIInternalDragAndDropInfo* dropInfo;
    OHOS::Ace::NG::DragPreviewOption previewOption;
    DragAdapterState dragState = DragAdapterState::INIT;
    RefPtr<OHOS::Ace::UnifiedData> unifiedData;
    std::string extraParams;
    int32_t sourceType = 0;
    float dipScale = 0.0;
    void* userData;
    std::function<void(const OHOS::Ace::DragNotifyMsg& info, int32_t status)> callback;
    float windowScale = 1.0f;
    std::mutex mutex;
    std::mutex dragStateMutex;
    std::vector<RefPtr<PixelMap>> pixelMapList;
    bool hasHandle = false;
    float touchPointX = 0.0;
    float touchPointY = 0.0;
    bool hasTouchPoint = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_UTILS_INTERNAL_DRAG_ACTION_H