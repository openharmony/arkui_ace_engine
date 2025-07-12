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

#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char16_t SUB[] = u"-";
constexpr char16_t ADD[] = u"+";
} // namespace
void CounterModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::COUNTER_ETS_TAG, nodeId);
    auto counterNode = CounterNode::GetOrCreateCounterNode(
        V2::COUNTER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CounterPattern>(); });
    auto counterPattern = counterNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(counterPattern);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto counterTheme = pipeline->GetTheme<CounterTheme>();
    CHECK_NULL_VOID(counterTheme);
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
    stack->Push(counterNode);
}

RefPtr<FrameNode> CounterModelNG::CreateButtonChild(
    int32_t id, const std::u16string& symbol, const RefPtr<CounterTheme>& counterTheme)
{
    auto buttonNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, id, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->GetOrCreateEventHub<ButtonEventHub>()->SetStateEffect(true);
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

RefPtr<FrameNode> CounterModelNG::CreateContentNodeChild(int32_t contentId, const RefPtr<CounterTheme>& counterTheme)
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

void CounterModelNG::SetEnableDec(bool enableDec)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto eventHub = subNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(enableDec);
    if (!eventHub->IsEnabled()) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto counterTheme = pipeline->GetTheme<CounterTheme>(frameNode->GetThemeScopeId());
        CHECK_NULL_VOID(counterTheme);
        subNode->GetRenderContext()->UpdateOpacity(counterTheme->GetAlphaDisabled());
    } else {
        subNode->GetRenderContext()->UpdateOpacity(1.0);
    }
}

void CounterModelNG::SetEnableInc(bool enableInc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto eventHub = addNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(enableInc);
    if (!eventHub->IsEnabled()) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto counterTheme = pipeline->GetTheme<CounterTheme>(frameNode->GetThemeScopeId());
        CHECK_NULL_VOID(counterTheme);
        addNode->GetRenderContext()->UpdateOpacity(counterTheme->GetAlphaDisabled());
    } else {
        addNode->GetRenderContext()->UpdateOpacity(1.0);
    }
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
    GestureEventFunc gestureEventFunc = [clickEvent = std::move(onInc)](GestureEvent& /*unused*/) {
                        clickEvent();
                        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onInc");
                    };
    gestureHub->SetUserOnClick(std::move(gestureEventFunc));
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
    GestureEventFunc gestureEventFunc = [clickEvent = std::move(onDec)](GestureEvent& /*unused*/) {
                        clickEvent();
                        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onDec");
                    };
    gestureHub->SetUserOnClick(std::move(gestureEventFunc));
}

void CounterModelNG::SetHeight(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));

    int32_t subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto subLayoutProperty = subNode->GetLayoutProperty();
    subLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));
    auto subTextNode = AceType::DynamicCast<FrameNode>(subNode->GetFirstChild());
    CHECK_NULL_VOID(subTextNode);
    auto subTextLayoutProperty = subTextNode->GetLayoutProperty();
    subTextLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));

    int32_t contentId = frameNode->GetPattern<CounterPattern>()->GetContentId();
    auto contentNode =
        AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(contentId)));
    CHECK_NULL_VOID(contentNode);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    contentLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));

    int32_t addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto addLayoutProperty = addNode->GetLayoutProperty();
    addLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));
    auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetFirstChild());
    CHECK_NULL_VOID(addTextNode);
    auto addTextLayoutProperty = addTextNode->GetLayoutProperty();
    addTextLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));
}

void CounterModelNG::SetWidth(const Dimension& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(value), std::nullopt));
}

void CounterModelNG::SetControlWidth(const Dimension& value) {}

void CounterModelNG::SetStateChange(bool value) {}

void CounterModelNG::SetBackgroundColor(const Color& value)
{
    ACE_UPDATE_RENDER_CONTEXT(BackgroundColor, value);
}

void CounterModelNG::SetEnableDec(FrameNode* frameNode, bool enableDec)
{
    CHECK_NULL_VOID(frameNode);
    auto subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto eventHub = subNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(enableDec);
    if (!eventHub->IsEnabled()) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto counterTheme = pipeline->GetTheme<CounterTheme>(frameNode->GetThemeScopeId());
        CHECK_NULL_VOID(counterTheme);
        subNode->GetRenderContext()->UpdateOpacity(counterTheme->GetAlphaDisabled());
    } else {
        subNode->GetRenderContext()->UpdateOpacity(1.0);
    }
}

void CounterModelNG::SetEnableInc(FrameNode* frameNode, bool enableInc)
{
    CHECK_NULL_VOID(frameNode);
    auto addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto eventHub = addNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(enableInc);
    if (!eventHub->IsEnabled()) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto counterTheme = pipeline->GetTheme<CounterTheme>(frameNode->GetThemeScopeId());
        CHECK_NULL_VOID(counterTheme);
        addNode->GetRenderContext()->UpdateOpacity(counterTheme->GetAlphaDisabled());
    } else {
        addNode->GetRenderContext()->UpdateOpacity(1.0);
    }
}
void CounterModelNG::SetHeight(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));

    int32_t subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto subLayoutProperty = subNode->GetLayoutProperty();
    subLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));
    auto subTextNode = AceType::DynamicCast<FrameNode>(subNode->GetFirstChild());
    CHECK_NULL_VOID(subTextNode);
    auto subTextLayoutProperty = subTextNode->GetLayoutProperty();
    subTextLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));

    int32_t contentId = frameNode->GetPattern<CounterPattern>()->GetContentId();
    auto contentNode =
        AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(contentId)));
    CHECK_NULL_VOID(contentNode);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    contentLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));

    int32_t addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto addLayoutProperty = addNode->GetLayoutProperty();
    addLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));
    auto addTextNode = AceType::DynamicCast<FrameNode>(addNode->GetFirstChild());
    CHECK_NULL_VOID(addTextNode);
    auto addTextLayoutProperty = addTextNode->GetLayoutProperty();
    addTextLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(value)));
}

void CounterModelNG::SetWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(value), std::nullopt));
}

void CounterModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundColor, value, frameNode);
}

void CounterModelNG::ResetBackgroundColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, BackgroundColor, frameNode);
}

void CounterModelNG::SetOnInc(FrameNode* frameNode, CounterEventFunc&& onInc)
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

void CounterModelNG::SetOnDec(FrameNode* frameNode, CounterEventFunc&& onDec)
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

void CounterModelNG::CreateWithResourceObj(JsCounterResourceType jsResourceType, const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, jsResourceType, resObj);
}

void CounterModelNG::CreateWithResourceObj(
    FrameNode* frameNode, JsCounterResourceType jsResourceType, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);
    switch (jsResourceType) {
        case JsCounterResourceType::Height:
            HandleHeightResource(frameNode, resObj);
            break;
        case JsCounterResourceType::Width:
            HandleWidthResource(frameNode, resObj);
            break;
        case JsCounterResourceType::BackgroundColor:
            HandleBackgroundColorResource(frameNode, resObj);
            break;
        default:
            break;
    }
}

void CounterModelNG::HandleHeightResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "counter.height";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        Dimension height;
        if (!ResourceParseUtils::ConvertFromResObjNG(resObj, height)) {
            return;
        }
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        if (pipelineContext->IsSystmColorChange()) {
            if (!LessNotEqual(height.Value(), 0.0)) {
                SetHeight(AceType::RawPtr(frameNode), height);
            }
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void CounterModelNG::HandleWidthResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "counter.width";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        Dimension width;
        if (!ResourceParseUtils::ConvertFromResObjNG(resObj, width)) {
            return;
        }
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        if (pipelineContext->IsSystmColorChange()) {
            if (!LessNotEqual(width.Value(), 0.0)) {
                SetWidth(AceType::RawPtr(frameNode), width);
            }
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void CounterModelNG::HandleBackgroundColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<CounterPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "counter.backgroundColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        Color color;
        if (ResourceParseUtils::ParseResColor(resObj, color)) {
            auto frameNode = pattern->GetHost();
            CHECK_NULL_VOID(frameNode);
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            if (pipelineContext->IsSystmColorChange()) {
                SetBackgroundColor(AceType::RawPtr(frameNode), color);
            }
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}
} // namespace OHOS::Ace::NG
