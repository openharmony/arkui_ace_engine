/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "grid_item_utils_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

void InitDragManager(const RefPtr<FrameNode>& frameNode, RefPtr<ForEachBaseNode> forEach)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitDragManager(forEach);
}

void DeInitDragManager(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->DeInitDragManager();
}

bool IsSelected(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSelected();
}

bool IsGridItemPattern(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<GridItemPattern>(pattern);
}

namespace NodeModifier {
const GridItemCustomModifier* GetGridItemCustomDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const GridItemCustomModifier modifier = {
        .initDragManager = InitDragManager,
        .deInitDragManager = DeInitDragManager,
        .isSelected = IsSelected,
        .isGridItemPattern = IsGridItemPattern,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG