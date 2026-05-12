/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_TYPES_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/image/pixel_map.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_constants.h"
#include "ui/base/referenced.h"

namespace OHOS::Ace::NG {

// Touch test information for child touch test callback
struct TouchTestInfo {
    PointF windowPoint;
    PointF currentCmpPoint;
    PointF subCmpPoint;
    RectF subRect;
    std::string id;
};

// Touch test result for child touch test callback
struct TouchResult {
    TouchTestStrategy strategy;
    std::string id;
};

// Callback type for onChildTouchTest
using OnChildTouchTestFunc = std::function<TouchResult(const std::vector<TouchTestInfo>& touchInfo)>;

// Drag drop information for drag preview
struct DragDropInfo {
    RefPtr<UINode> customNode;
    RefPtr<PixelMap> pixelMap;
    std::string extraInfo;
    // The inspectorId acts as a preview surrogate identifier which is used
    // to retrieve a preview image for the item being dragged.
    std::string inspectorId;
    std::function<RefPtr<UINode>()> buildFunc;
    bool onlyForLifting = false;
    bool delayCreating = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_TYPES_H
