/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RectF TabBarLayoutProperty::GetIndicatorRect(int32_t index)
{
    auto node = GetHost();
    CHECK_NULL_RETURN(node, RectF());
    auto pipelineContext = node->GetContext();
    CHECK_NULL_RETURN(pipelineContext, RectF());
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, RectF());
    auto childColumn = DynamicCast<FrameNode>(node->GetChildAtIndex(index));
    CHECK_NULL_RETURN(childColumn && !childColumn->GetChildren().empty(), RectF());
    auto grandChildren = DynamicCast<FrameNode>(childColumn->GetChildren().back());
    CHECK_NULL_RETURN(grandChildren, RectF());
    auto geometryNode = grandChildren->GetGeometryNode();
    RectF indicator = geometryNode->GetFrameRect();

    /* Set indicator at the bottom of columnNode's last child */
    auto childColumnRect = childColumn->GetGeometryNode()->GetFrameRect();
    auto tabBarPattern = node->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(node, RectF());
    indicator.SetLeft(indicator.GetX() + childColumnRect.GetX());
    indicator.SetTop(indicator.Bottom() + childColumnRect.GetY());
    return indicator;
}

} // namespace OHOS::Ace::NG
