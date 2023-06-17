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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRIF_GRID_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRIF_GRID_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridView {
public:
    static void Create();
    static void SetColumnsTemplate(const std::string& value);
    static void SetRowsTemplate(const std::string& value);
    static void SetColumnsGap(const Dimension& value);
    static void SetRowsGap(const Dimension& value);
    static void SetScrollBarMode(DisplayMode value);
    static void SetScrollBarColor(const Color& value);
    static void SetScrollBarWidth(const Dimension& value);
    static void SetCachedCount(int32_t value);
    static void SetLayoutDirection(FlexDirection value);
    static void SetMaxCount(int32_t value);
    static void SetMinCount(int32_t value);
    static void SetCellLength(int32_t value);
    static void SetEditable(bool value);
    static void SetMultiSelectable(bool value);
    static void SetSupportAnimation(bool value);
    static void SetOnScrollToIndex(ScrollToIndexFunc&& value);
    static void SetOnScrollBarUpdate(ScrollBarUpdateFunc&& value);
    static void SetOnItemDragStart(ItemDragStartFunc&& value);
    static void SetOnItemDragEnter(ItemDragEnterFunc&& value);
    static void SetOnItemDragMove(ItemDragMoveFunc&& value);
    static void SetOnItemDragLeave(ItemDragLeaveFunc&& value);
    static void SetOnItemDrop(ItemDropFunc&& value);

private:
    static void AddDragFrameNodeToManager();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRIF_GRID_VIEW_H
