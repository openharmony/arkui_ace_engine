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

#include "core/components_ng/pattern/counter/counter_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void CounterModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto counterNode = CounterNode::GetOrCreateCounterNode(
        V2::COUNTER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CounterPattern>(); });
    auto counterPattern = counterNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(counterPattern);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    CHECK_NULL_VOID(counterTheme);
    counterNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(counterTheme->GetWidth()), CalcLength(counterTheme->GetHeight())));
    counterNode->GetLayoutProperty()->UpdateBorderWidth(counterTheme->GetBorderWidth());
    counterNode->GetRenderContext()->UpdateBorderRadius(counterTheme->GetBorderRadius());
    counterNode->GetRenderContext()->UpdateBorderStyle(counterTheme->GetBorderStyle());
    counterNode->GetRenderContext()->UpdateBorderColor(counterTheme->GetBorderColor());
    counterNode->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);
    counterNode->GetRenderContext()->SetClipToFrame(true);
    counterNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::CENTER);

    bool hasSubNode = counterPattern->HasSubNode();
    bool hasContentNode = counterPattern->HasContentNode();
    bool hasAddNode = counterPattern->HasAddNode();
    auto subId = counterPattern->GetSubId();
    auto contentId = counterPattern->GetContentId();
    auto addId = counterPattern->GetAddId();
    if (!hasSubNode) {
        auto subNode = CreateButtonChild(subId, "-", counterTheme);
        subNode->MountToParent(counterNode);
    }
    if (!hasContentNode) {
        auto contentNode = CreateContentNodeChild(contentId, counterTheme);
        contentNode->MountToParent(counterNode);
    }
    if (!hasAddNode) {
        auto addNode = CreateButtonChild(addId, "+", counterTheme);
        addNode->MountToParent(counterNode);
    }

    stack->Push(counterNode);
}

RefPtr<FrameNode> CounterModelNG::CreateButtonChild(
    int32_t id, const std::string& symbol, const RefPtr<CounterTheme>& counterTheme)
{
    auto buttonNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, id, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->GetEventHub<ButtonEventHub>()->SetStateEffect(true);
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateType(ButtonType::NORMAL);
    buttonNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(counterTheme->GetControlWidth()), CalcLength(counterTheme->GetHeight())));
    buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonNode->MarkModifyDone();

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(symbol);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextColor(Color::BLACK);
    textNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(counterTheme->GetControlWidth()), CalcLength(counterTheme->GetHeight())));
    textNode->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
    textNode->MarkModifyDone();

    textNode->MountToParent(buttonNode);
    return buttonNode;
}

RefPtr<FrameNode> CounterModelNG::CreateContentNodeChild(int32_t contentId, const RefPtr<CounterTheme>& counterTheme)
{
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, contentId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    contentNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::CENTER);
    contentNode->GetLayoutProperty()->UpdateLayoutWeight(1);
    contentNode->GetLayoutProperty()->UpdateBorderWidth(counterTheme->GetBorderWidth());
    contentNode->GetRenderContext()->UpdateBorderStyle(counterTheme->GetBorderStyle());
    contentNode->GetRenderContext()->UpdateBorderColor(counterTheme->GetBorderColor());
    contentNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    contentNode->MarkModifyDone();
    return contentNode;
}

void CounterModelNG::SetOnInc(CounterEventFunc&& onInc)
{
    CHECK_NULL_VOID(onInc);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto gestureHub = addNode->GetOrCreateGestureEventHub();
    GestureEventFunc gestureEventFunc = [clickEvent = std::move(onInc)](GestureEvent& /*unused*/) { clickEvent(); };
    gestureHub->SetClickEvent(std::move(gestureEventFunc));
}
void CounterModelNG::SetOnDec(CounterEventFunc&& onDec)
{
    CHECK_NULL_VOID(onDec);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto gestureHub = subNode->GetOrCreateGestureEventHub();
    GestureEventFunc gestureEventFunc = [clickEvent = std::move(onDec)](GestureEvent& /*unused*/) { clickEvent(); };
    gestureHub->SetClickEvent(std::move(gestureEventFunc));
}

void CounterModelNG::SetHeight(const Dimension& value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));

    int32_t subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto subLayoutProperty = subNode->GetLayoutProperty();
    subLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(value), CalcLength(value)));

    int32_t addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto addLayoutProperty = addNode->GetLayoutProperty();
    addLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(value), CalcLength(value)));
}
void CounterModelNG::SetWidth(const Dimension& value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(value), std::nullopt));
}
void CounterModelNG::SetControlWidth(const Dimension& value)
{
    LOGE("no support SetControlWidth");
}
void CounterModelNG::SetStateChange(bool value)
{
    LOGE("no support SetStateChange");
}
void CounterModelNG::SetBackgroundColor(const Color& value)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundColor, value);
}

} // namespace OHOS::Ace::NG