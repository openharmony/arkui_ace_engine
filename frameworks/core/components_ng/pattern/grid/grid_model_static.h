/*
* Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_STATIC_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_model.h"
 
namespace OHOS::Ace::NG {

class ACE_EXPORT GridModelStatic {
public:
    static void SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& scrollBarMode);
    static void SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& scrollBarWidth);
    static void SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& scrollBarColor);
    static void SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& layoutDirection);
    static void SetFriction(FrameNode* frameNode, const std::optional<double>& value);
    static void SetAlignItems(FrameNode* frameNode, const std::optional<GridItemAlignment>& itemAlign);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop);
    static void SetColumnsGap(FrameNode* frameNode, const std::optional<Dimension>& columnsGap);
    static void SetRowsGap(FrameNode* frameNode, const std::optional<Dimension>& rowsGap);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_STATIC_H
