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

#include "core/components_ng/pattern/grid/grid_view.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void GridView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridPattern>(); });
    stack->Push(frameNode);
}

void GridView::SetColumnsTemplate(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, value);
}

void GridView::SetRowsTemplate(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, value);
}

} // namespace OHOS::Ace::NG
