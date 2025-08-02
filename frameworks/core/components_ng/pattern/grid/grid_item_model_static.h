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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_MODEL_STATIC_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_model.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridItemModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetForceRebuild(FrameNode* frameNode, bool value);
    static void SetSelectable(FrameNode* frameNode, bool selectable);
    static void SetSelected(FrameNode* frameNode, bool selected);
    static void SetRowStart(FrameNode* frameNode, int32_t rowStart);
    static void SetRowEnd(FrameNode* frameNode, int32_t rowEnd);
    static void SetColumnStart(FrameNode* frameNode, int32_t columnStart);
    static void SetColumnEnd(FrameNode* frameNode, int32_t columnEnd);
    static void SetGridItemStyle(FrameNode* frameNode, GridItemStyle gridItemStyle);
    static void SetOnSelect(FrameNode* frameNode, SelectFunc&& onSelect);
    static void SetSelectChangeEvent(FrameNode* frameNode, SelectFunc&& changeEvent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_MODEL_STATIC_H
