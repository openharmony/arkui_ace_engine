/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_PROPERTIES_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components/scroll/scrollable.h"

namespace OHOS::Ace {

namespace V2 {

enum class ScrollState {
    IDLE = 0,
    SCROLL,
    FLING,
};

enum class ListItemAlign {
    /*
     * display list item at start of cross axis.
     */
    START = 0,

    /*
     * display list item at center of cross axis.
     */
    CENTER,

    /*
     * display list item at center of cross axis.
     */
    END,
};

enum class StickyStyle : uint32_t {
    NONE = 0,
    HEADER = 1,
    FOOTER = 2,
    BOTH = 3,
};

enum class StickyMode {
    NONE = 0,
    NORMAL,
    OPACITY,
};

enum class SwipeEdgeEffect {
    Spring = 0,
    None,
};

struct EditMode {
    enum : uint32_t {
        NONE = 0,
        DELETABLE = (1 << 0),
        MOVABLE = (1 << 1),
        SHAM = (1 << 2), // this enum value [SHAM] is added for inspector use, it works as [NONE]
    };
};

struct ItemDivider final {
    Dimension strokeWidth = 0.0_vp;
    Dimension startMargin = 0.0_vp;
    Dimension endMargin = 0.0_vp;
    Color color = Color::TRANSPARENT;
    bool operator==(const ItemDivider& itemDivider) const
    {
        return (strokeWidth == itemDivider.strokeWidth) && (startMargin == itemDivider.startMargin) &&
               (endMargin == itemDivider.endMargin) && (color == itemDivider.color);
    }
};
} // namespace V2

using OnScrollEvent = std::function<void(Dimension, V2::ScrollState)>;
using OnScrollBeginEvent = std::function<ScrollInfo(Dimension, Dimension)>;
using OnScrollStopEvent = std::function<void()>;
using OnScrollIndexEvent = std::function<void(int32_t, int32_t)>;
using OnReachEvent = std::function<void()>;
using OnItemDeleteEvent = std::function<bool(int32_t)>;
using OnItemMoveEvent = std::function<bool(int32_t, int32_t)>;
using OnItemDragStartFunc = std::function<RefPtr<AceType>(const ItemDragInfo&, int32_t)>;
using OnItemDragEnterFunc = std::function<void(const ItemDragInfo&)>;
using OnItemDragMoveFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t)>;
using OnItemDragLeaveFunc = std::function<void(const ItemDragInfo&, int32_t)>;
using OnItemDropFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)>;
using OnSelectFunc = std::function<void(bool)>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GROUP_COMPONENT_H
