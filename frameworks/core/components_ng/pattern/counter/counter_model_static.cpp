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
namespace {
constexpr char16_t SUB[] = u"-";
constexpr char16_t ADD[] = u"+";
} // namespace
RefPtr<FrameNode> CounterModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::COUNTER_ETS_TAG, nodeId);
    auto counterNode = CounterNode::GetOrCreateCounterNode(
        V2::COUNTER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CounterPattern>(); });
    auto counterPattern = counterNode->GetPattern<CounterPattern>();
    CHECK_NULL_RETURN(counterPattern, counterNode);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, counterNode);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    CHECK_NULL_RETURN(counterTheme, counterNode);
    counterNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(counterTheme->GetWidth()), CalcLength(counterTheme->GetHeight())));
    counterNode->GetRenderContext()->SetClipToFrame(true);
    counterNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::CENTER);

    bool hasSubNode = counterPattern->HasSubNode();
    bool hasContentNode = counterPattern->HasContentNode();
    bool hasAddNode = counterPattern->HasAddNode();
    auto subId = counterPattern->GetSubId();
    auto contentId = counterPattern->GetContentId();
    auto addId = counterPattern->GetAddId();
    if (!hasSubNode) {
        auto subNode = CreateButtonChild(subId, SUB, counterTheme);
        subNode->MountToParent(counterNode);
    }
    if (!hasContentNode) {
        auto contentNode = CreateContentNodeChild(contentId, counterTheme);
        contentNode->MountToParent(counterNode);
    }
    if (!hasAddNode) {
        auto addNode = CreateButtonChild(addId, ADD, counterTheme);
        addNode->MountToParent(counterNode);
    }
    return counterNode;
}

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

void CounterModelStatic::SetOnInc(FrameNode* frameNode, CounterModel::CounterEventFunc&& onInc)
{
    CHECK_NULL_VOID(frameNode);
    auto counterPattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(counterPattern);
    auto addId = counterPattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto gestureHub = addNode->GetOrCreateGestureEventHub();
    GestureEventFunc gestureEventFunc = [clickEvent = std::move(onInc)](GestureEvent& /*unused*/) {
        if (clickEvent) {
            clickEvent();
        }
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onInc");
    };
    gestureHub->SetUserOnClick(std::move(gestureEventFunc));
}

void CounterModelStatic::SetOnDec(FrameNode* frameNode, CounterModel::CounterEventFunc&& onDec)
{
    CHECK_NULL_VOID(frameNode);
    auto counterPattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(counterPattern);
    auto subId = counterPattern->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto gestureHub = subNode->GetOrCreateGestureEventHub();
    GestureEventFunc gestureEventFunc = [clickEvent = std::move(onDec)](GestureEvent& /*unused*/) {
        if (clickEvent) {
            clickEvent();
        }
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onDec");
    };
    gestureHub->SetUserOnClick(std::move(gestureEventFunc));
}

RefPtr<FrameNode> CounterModelStatic::CreateButtonChild(
    int32_t id, const std::u16string& symbol, const RefPtr<CounterTheme>& counterTheme)
{
    auto buttonNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, id, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->GetEventHub<ButtonEventHub>()->SetStateEffect(true);
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateType(ButtonType::NORMAL);
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateCreateWithLabel(false);
    buttonNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(counterTheme->GetControlWidth()), CalcLength(counterTheme->GetHeight())));
    buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonNode->GetLayoutProperty()->UpdateBorderWidth(counterTheme->GetBorderWidth());
    buttonNode->GetRenderContext()->UpdateBorderStyle(counterTheme->GetBorderStyle());
    buttonNode->GetRenderContext()->UpdateBorderColor(counterTheme->GetBorderColor());
    buttonNode->MarkModifyDone();

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    if (textLayoutProperty) {
        textLayoutProperty->UpdateContent(symbol);
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    }
    textNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(counterTheme->GetControlWidth()), CalcLength(counterTheme->GetHeight())));
    textNode->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
    textNode->MarkModifyDone();

    textNode->MountToParent(buttonNode);
    return buttonNode;
}

RefPtr<FrameNode> CounterModelStatic::CreateContentNodeChild(
    int32_t contentId, const RefPtr<CounterTheme>& counterTheme)
{
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, contentId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    contentNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::CENTER);
    contentNode->GetLayoutProperty()->UpdateLayoutWeight(1);
    contentNode->GetRenderContext()->SetClipToFrame(true);
    contentNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(counterTheme->GetHeight())));
    contentNode->GetLayoutProperty()->UpdateBorderWidth(counterTheme->GetContentBorderWidth());
    contentNode->GetRenderContext()->UpdateBorderStyle(counterTheme->GetBorderStyle());
    contentNode->GetRenderContext()->UpdateBorderColor(counterTheme->GetBorderColor());
    contentNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    contentNode->MarkModifyDone();
    return contentNode;
}
} // namespace OHOS::Ace::NG
