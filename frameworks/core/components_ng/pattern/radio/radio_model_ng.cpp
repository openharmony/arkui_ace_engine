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

#include "core/components_ng/pattern/radio/radio_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"

namespace OHOS::Ace::NG {

void RadioModelNG::Create(const std::optional<std::string>& value, const std::optional<std::string>& group,
    const std::optional<int32_t>& indicator)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::RADIO_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RADIO_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (value.has_value()) {
        eventHub->SetValue(value.value());
    }
    if (group.has_value()) {
        eventHub->SetGroup(group.value());
    }
    if (indicator.has_value()) {
        SetRadioIndicator(indicator.value());
    }
    auto props = frameNode->GetPaintPropertyPtr<RadioPaintProperty>();
    if (props) {
        props->ResetRadioCheckedBackgroundColorSetByUser();
        props->ResetRadioUncheckedBorderColorSetByUser();
        props->ResetRadioIndicatorColorSetByUser();
    }
}

RefPtr<FrameNode> RadioModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::RADIO_ETS_TAG, nodeId, AceType::MakeRefPtr<RadioPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

void RadioModelNG::SetBuilder(std::function<void()>&& buildFunc)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(radioPattern);
    radioPattern->SetBuilder(std::move(buildFunc));
}

void RadioModelNG::SetRadioIndicator(int32_t indicator)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicator, indicator);
}

void RadioModelNG::SetChecked(bool isChecked)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    TAG_LOGD(
        AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d set checked %{public}d", frameNode->GetId(), isChecked);
    auto eventHub = frameNode->GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isChecked);

    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioCheck, isChecked);
}

void RadioModelNG::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void RadioModelNG::SetOnChange(FrameNode* frameNode, ChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void RadioModelNG::SetWidth(const Dimension& width)
{
    NG::ViewAbstract::SetWidth(NG::CalcLength(width));
}

void RadioModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
}

void RadioModelNG::SetPadding(const NG::PaddingPropertyF& /*args*/, const NG::PaddingProperty& newArgs)
{
    NG::ViewAbstract::SetPadding(newArgs);
}

void RadioModelNG::SetCheckedBackgroundColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColor, color);
}

void RadioModelNG::SetCheckedBackgroundColorSetByUser(bool flag)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColorSetByUser, flag);
}

void RadioModelNG::SetUncheckedBorderColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColor, color);
}

void RadioModelNG::SetUncheckedBorderColorSetByUser(bool flag)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColorSetByUser, flag);
}

void RadioModelNG::SetIndicatorColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColor, color);
}

void RadioModelNG::SetIndicatorColorSetByUser(bool flag)
{
    ACE_UPDATE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColorSetByUser, flag);
}

void RadioModelNG::SetOnChangeEvent(ChangeEvent&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

void RadioModelNG::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(responseRegion);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

void RadioModelNG::SetHoverEffect(HoverEffectType hoverEffect)
{
    NG::ViewAbstract::SetHoverEffect(hoverEffect);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShowHoverEffect(hoverEffect != HoverEffectType::NONE);
}

void RadioModelNG::SetChecked(FrameNode* frameNode, bool isChecked)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<RadioEventHub>();
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT,
        "radio frame node %{public}d set checked %{public}d", frameNode->GetId(), isChecked);
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isChecked);
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheck, isChecked, frameNode);
}

void RadioModelNG::SetCheckedBackgroundColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColor, color, frameNode);
}

void RadioModelNG::SetCheckedBackgroundColorSetByUser(FrameNode* frameNode, bool flag)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioCheckedBackgroundColorSetByUser, flag, frameNode);
}

void RadioModelNG::SetUncheckedBorderColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColor, color, frameNode);
}

void RadioModelNG::SetUncheckedBorderColorSetByUser(FrameNode* frameNode, bool flag)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioUncheckedBorderColorSetByUser, flag, frameNode);
}

void RadioModelNG::SetIndicatorColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColor, color, frameNode);
}

void RadioModelNG::SetIndicatorColorSetByUser(FrameNode* frameNode, bool flag)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicatorColorSetByUser, flag, frameNode);
}

void RadioModelNG::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    NG::ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
}

void RadioModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
}

void RadioModelNG::SetHoverEffect(FrameNode* frameNode, HoverEffectType hoverEffect)
{
    NG::ViewAbstract::SetHoverEffect(frameNode, hoverEffect);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShowHoverEffect(hoverEffect != HoverEffectType::NONE);
}

void RadioModelNG::SetPadding(FrameNode* frameNode, const NG::PaddingProperty& newArgs)
{
    NG::ViewAbstract::SetPadding(frameNode, newArgs);
}

void RadioModelNG::SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(frameNode, responseRegion);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

void RadioModelNG::SetBuilderFunc(FrameNode* frameNode, NG::RadioMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void RadioModelNG::SetChangeValue(FrameNode* frameNode, bool value)
{
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetRadioChecked(value);
}

bool RadioModelNG::GetChecked(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(RadioPaintProperty, RadioCheck, value, frameNode, value);
    return value;
}

Color RadioModelNG::GetCheckedBackgroundColor(FrameNode* frameNode)
{
    Color color(0xFF007DFF);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        RadioPaintProperty, RadioCheckedBackgroundColor, color, frameNode, color);
    return color;
}

Color RadioModelNG::GetUncheckedBorderColor(FrameNode* frameNode)
{
    Color color(0xFF182431);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        RadioPaintProperty, RadioUncheckedBorderColor, color, frameNode, color);
    return color;
}

Color RadioModelNG::GetIndicatorColor(FrameNode* frameNode)
{
    Color color(0xFFFFFFFF);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(RadioPaintProperty, RadioIndicatorColor, color, frameNode, color);
    return color;
}

void RadioModelNG::SetRadioValue(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!value.empty()) {
        eventHub->SetValue(value);
    }
}

std::string RadioModelNG::GetRadioValue(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    return eventHub->GetValue();
}

void RadioModelNG::SetRadioGroup(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!value.empty()) {
        eventHub->SetGroup(value);
    }
}

std::string RadioModelNG::GetRadioGroup(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    return eventHub->GetGroup();
}

void RadioModelNG::SetRadioOptions(FrameNode* frameNode, const std::string& value,
    const std::string& group, int32_t indicator)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(value);
    eventHub->SetGroup(group);
    ACE_UPDATE_NODE_PAINT_PROPERTY(RadioPaintProperty, RadioIndicator, indicator, frameNode);
}

void RadioModelNG::CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj,
    const RadioColorType radioColorType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithColorResourceObj(frameNode, resObj, radioColorType);
}

void RadioModelNG::CreateWithColorResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj,
    const RadioColorType radioColorType)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "radio" + ColorTypeToString(radioColorType);
    if (resObj) {
        auto&& updateFunc = [radioColorType, weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
            const RefPtr<ResourceObject>& resObj) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            Color result;
            if (ResourceParseUtils::ParseResColor(resObj, result)) {
                pattern->UpdateRadioComponentColor(result, radioColorType);
            }
        };
        pattern->AddResObj(key, resObj, std::move(updateFunc));
    } else {
        pattern->RemoveResObj(key);
    }
}

std::string RadioModelNG::ColorTypeToString(const RadioColorType radioColorType)
{
    switch (radioColorType) {
        case RadioColorType::CHECKED_BACKGROUND_COLOR:
            return "CheckedBackgroundColor";
        case RadioColorType::UNCHECKED_BORDER_COLOR:
            return "UncheckedBorderColor";
        case RadioColorType::INDICATOR_COLOR:
            return "IndicatorColor";
        default:
            return "";
    }
    return "Unknown";
}

void RadioModelNG::SetIsUserSetMargin(bool isUserSet)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetIsUserSetMargin(frameNode, isUserSet);
}

void RadioModelNG::SetIsUserSetMargin(FrameNode* frameNode, bool isUserSet)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    pattern->SetIsUserSetMargin(isUserSet);
}

void RadioModelNG::SetUncheckedBorderColorByJSRadioTheme(bool flag)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetUncheckedBorderColorByJSRadioTheme(flag);
}

void RadioModelNG::SetIndicatorColorByJSRadioTheme(bool flag)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIndicatorColorByJSRadioTheme(flag);
}
} // namespace OHOS::Ace::NG
