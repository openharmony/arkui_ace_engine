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

#include "core/components_ng/pattern/counter/counter_model_static.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
void CounterModelStatic::SetHeight(FrameNode* frameNode, const CalcLength& height)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));

    int32_t subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto subLayoutProperty = subNode->GetLayoutProperty();
    subLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));
    auto subTextNode = AceType::DynamicCast<FrameNode>(subNode->GetFirstChild());
    CHECK_NULL_VOID(subTextNode);
    auto subTextLayoutProperty = subTextNode->GetLayoutProperty();
    subTextLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));

    int32_t contentId = frameNode->GetPattern<CounterPattern>()->GetContentId();
    auto contentNode =
        AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(contentId)));
    CHECK_NULL_VOID(contentNode);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    contentLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));

    int32_t addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto addLayoutProperty = addNode->GetLayoutProperty();
    addLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));
    auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetFirstChild());
    CHECK_NULL_VOID(addTextNode);
    auto addTextLayoutProperty = addTextNode->GetLayoutProperty();
    addTextLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, height));
}

void CounterModelStatic::SetWidth(FrameNode* frameNode, const CalcLength& width)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, std::nullopt));
}

void CounterModelStatic::SetBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    if (color) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, BackgroundColor, frameNode);
    }
}
} // namespace OHOS::Ace::NG
