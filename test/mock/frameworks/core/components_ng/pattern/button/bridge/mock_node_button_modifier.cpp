/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/system_properties.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/layout/common_text_constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/input_event_hub.h"
#include "core/components_ng/pattern/button/bridge/button_custom_modifier.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_model_impl.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/core/components/button/button_theme.h"

namespace OHOS::Ace {
ButtonModel* ButtonModel::GetInstance()
{
    static NG::ButtonModelNG instance;
    return &instance;
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
const char BUTTON_ETS_TAG[] = "Button";
constexpr int32_t ERROR_INT_CODE = -1;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

RefPtr<ButtonPattern> GetButtonPattern(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ButtonPattern>(frameNode->GetPattern());
}

RefPtr<ButtonLayoutProperty> GetButtonLayoutProperty(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetLayoutProperty<ButtonLayoutProperty>();
}

RefPtr<ToggleButtonPattern> GetToggleButtonPattern(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
}

ArkUINodeHandle CreateButtonFrameNodeForCustom(ArkUI_Int32 nodeId)
{
    auto frameNode = ButtonModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    AceType::RawPtr(frameNode)->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle CreateFrameNodeForCustom(ArkUI_Int32 nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(BUTTON_ETS_TAG, nodeId, AceType::MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void* CreateButtonPatternForCustom()
{
    auto pattern = AceType::MakeRefPtr<ButtonPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    AceType::RawPtr(pattern)->IncRefCount();
    return AceType::RawPtr(pattern);
}

void* CreateToggleButtonPatternForCustom()
{
    auto pattern = AceType::MakeRefPtr<ToggleButtonPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    AceType::RawPtr(pattern)->IncRefCount();
    return AceType::RawPtr(pattern);
}

void SetComponentButtonTypeForCustom(ArkUINodeHandle node, OHOS::Ace::ComponentButtonType buttonType)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->setComponentButtonType(buttonType);
}

void SetSkipColorConfigurationUpdateForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetSkipColorConfigurationUpdate();
}

void SetClickedColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetClickedColor(color);
}

void SetBlendColorForCustom(ArkUINodeHandle node, const Color& clickColor, const Color& hoverColor)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetBlendColor(clickColor, hoverColor);
}

void SetBlendColorWithOptionalForCustom(
    ArkUINodeHandle node, const std::optional<Color>& clickColor, const std::optional<Color>& hoverColor)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetBlendColor(clickColor, hoverColor);
}

void SetFocusBorderColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetFocusBorderColor(color);
}

void SetFocusBorderWidthForCustom(ArkUINodeHandle node, const Dimension& width)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetFocusBorderWidth(width);
}

void SetApplyShadowForCustom(ArkUINodeHandle node, bool shadow)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetApplyShadow(shadow);
}

void HandleButtonBackgroundColorForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->HandleBackgroundColor();
}

void SetNavigationFocusBlendBgColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetNavigationFocusBlendBgColor(color);
}

void SetNavMenuItemNeedFocusForCustom(ArkUINodeHandle node, bool needFocus)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetNavMenuItemNeedFocus(needFocus);
}

void SetHasCustomPaddingForCustom(ArkUINodeHandle node, bool hasCustomPadding)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetHasCustomPadding(hasCustomPadding);
}

bool IsToggleButtonPatternForCustom(ArkUINodeHandle node)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    return AceType::InstanceOf<ToggleButtonPattern>(pattern);
}

bool IsButtonPatternForCustom(ArkUINodeHandle node)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    return AceType::InstanceOf<ButtonPattern>(pattern);
}

bool IsButtonLayoutPropertyForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return AceType::InstanceOf<ButtonLayoutProperty>(layoutProperty);
}

void SetToggleBackgroundColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetBackgroundColor(frameNode, color);
}

void SetToggleBackgroundColorWithFlagForCustom(ArkUINodeHandle node, const Color& color, bool flag)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetBackgroundColor(frameNode, color, flag);
}

void SetButtonBorderRadiusForCustom(ArkUINodeHandle node, const std::optional<Dimension>& topLeft,
    const std::optional<Dimension>& topRight, const std::optional<Dimension>& bottomLeft,
    const std::optional<Dimension>& bottomRight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetBorderRadius(frameNode, topLeft, topRight, bottomLeft, bottomRight);
}

void SetToggleBuilderFuncForCustom(ArkUINodeHandle node, void* callback)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    if (callback) {
        auto makeFunc = reinterpret_cast<SwitchMakeCallback*>(callback);
        pattern->SetToggleBuilderFunc(std::move(*makeFunc));
        return;
    }
    pattern->SetToggleBuilderFunc(nullptr);
}

void SetToggleButtonPressForCustom(ArkUINodeHandle node, bool value)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetButtonPress(value);
}

void RemoveHoverListenerForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    inputHub->RemoveOnHoverEvent(pattern->GetHoverListener());
}

void SetButtonHoverForCustom(ArkUINodeHandle node, bool isHover)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetInHover(isHover);
}

bool GetButtonHoverForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetIsInHover();
}

void SetButtonLocalLocationForCustom(ArkUINodeHandle node, const Offset& localLocation)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetLocalLocation(localLocation);
}

const Offset& GetButtonLocalLocationForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    static const Offset defaultOffset;
    CHECK_NULL_RETURN(pattern, defaultOffset);
    return pattern->GetLocalLocation();
}

void UpdateTypeToLayoutPropForCustom(ArkUINodeHandle node, OHOS::Ace::ButtonType type)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateType(type);
}

void SetStateEffectToEventHubForCustom(ArkUINodeHandle node, bool stateEffect)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetStateEffect(stateEffect);
}

bool GetStateEffectFromEventHubForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, true);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return eventHub->GetStateEffect();
}

void UpdateBackgroundColorFlagByUserToLayoutPropForCustom(ArkUINodeHandle node, bool value)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateBackgroundColorFlagByUser(value);
}

void UpdateLabelToLayoutPropForCustom(ArkUINodeHandle node, const std::string& label)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateLabel(label);
}

void UpdateFontSizeToLayoutPropForCustom(ArkUINodeHandle node, const Dimension& fontSize)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontSize(fontSize);
}

void UpdateFontColorToLayoutPropForCustom(ArkUINodeHandle node, const Color& color)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontColor(color);
}

void UpdateFontWeightToLayoutPropForCustom(ArkUINodeHandle node, FontWeight fontWeight)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontWeight(fontWeight);
}

void UpdateFontColorFlagByUserToLayoutPropForCustom(ArkUINodeHandle node, bool value)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontColorFlagByUser(value);
}

void UpdateFontStyleToLayoutPropForCustom(ArkUINodeHandle node, FontStyle fontStyle)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontStyle(fontStyle);
}

void UpdateFontFamilyToLayoutPropForCustom(ArkUINodeHandle node, const std::vector<std::string>& fontFamily)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontFamily(fontFamily);
}

void UpdateButtonStyleToLayoutPropForCustom(ArkUINodeHandle node, ButtonStyleMode buttonStyle)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateButtonStyle(buttonStyle);
}

void UpdateButtonRoleToLayoutPropForCustom(ArkUINodeHandle node, ButtonRole buttonRole)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateButtonRole(buttonRole);
}

void UpdateControlSizeToLayoutPropForCustom(ArkUINodeHandle node, ControlSize controlSize)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateControlSize(controlSize);
}

const std::optional<ButtonStyleMode>& GetButtonStyleFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<ButtonStyleMode> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetButtonStyle();
}

const std::optional<ButtonRole>& GetButtonRoleFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<ButtonRole> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetButtonRole();
}

void UpdateAutoDisableToLayoutPropForCustom(ArkUINodeHandle node, bool autoDisable)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAutoDisable(autoDisable);
}

const std::optional<bool>& GetAutoDisableFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<bool> emptyValue = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, emptyValue);
    return layoutProperty->GetAutoDisable();
}

bool HasFontColorFromLayoutPropForCustom(ArkUINodeHandle node)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->HasFontColor();
}

void UpdateCreateWithLabelToLayoutPropForCustom(ArkUINodeHandle node, bool createWithLabel)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCreateWithLabel(createWithLabel);
}

void UpdateBorderRadiusToLayoutPropForCustom(ArkUINodeHandle node, const BorderRadiusProperty& borderRadius)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateBorderRadius(borderRadius);
}

void UpdateTextOverflowToLayoutPropForCustom(ArkUINodeHandle node, TextOverflow textOverflow)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateTextOverflow(textOverflow);
}

void UpdateMaxLinesToLayoutPropForCustom(ArkUINodeHandle node, uint32_t maxLines)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMaxLines(maxLines);
}

const std::optional<BorderRadiusProperty>& GetBorderRadiusFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<BorderRadiusProperty> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetBorderRadius();
}

const std::optional<Dimension>& GetFontSizeFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<Dimension> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetFontSize();
}

const std::optional<Color>& GetFontColorFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<Color> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetFontColor();
}

const std::string& GetLabelFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::string emptyString = "";
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, emptyString);
    if (layoutProperty->HasLabel()) {
        return layoutProperty->GetLabelValue();
    }
    return emptyString;
}

void ResetFontSizeToLayoutPropForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, frameNode);
}

void SetFontColorDefaultForCustom(const Color& color)
{
    auto buttonModel = ButtonModel::GetInstance();
    CHECK_NULL_VOID(buttonModel);
    buttonModel->SetFontColorDefault(color);
}

void SetBackgroundColorDefaultForCustom(const Color& color)
{
    auto buttonModel = ButtonModel::GetInstance();
    CHECK_NULL_VOID(buttonModel);
    buttonModel->BackgroundColorDefault(color);
}

void UpdateToggleIsOnToPaintPropForCustom(ArkUINodeHandle node, bool isOn)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ToggleButtonPaintProperty, IsOn, isOn, frameNode);
}

bool GetToggleIsOnFromPaintPropForCustom(ArkUINodeHandle node, bool defaultValue)
{
    bool value = defaultValue;
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(ToggleButtonPaintProperty, IsOn, value, frameNode, value);
    return value;
}

void SetToggleOnChangeToEventHubForCustom(ArkUINodeHandle node, std::function<void(const bool)>&& onChange)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SetToggleOnChangeEventToEventHubForCustom(ArkUINodeHandle node, std::function<void(const bool)>&& onChangeEvent)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

bool IsToggleButtonUseContentModifierForCustom(ArkUINodeHandle node)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->UseContentModifier();
}

int32_t GetToggleButtonBuilderIdForCustom(ArkUINodeHandle node)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_RETURN(pattern, ERROR_INT_CODE);
    return pattern->GetBuilderId();
}

void ResetToggleSelectedColorForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::ResetSelectedColor(frameNode);
}

void SetToggleSelectedColorForCustom(ArkUINodeHandle node, const OHOS::Ace::Color& color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetSelectedColor(frameNode, color);
}

void SetToggleSelectedColorSetByUserForCustom(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetSelectedColorSetByUser(frameNode, isByUser);
}
} // namespace

namespace NodeModifier {

const ArkUIButtonCustomModifier* GetButtonCustomModifier()
{
    static const ArkUIButtonCustomModifier modifier = {
        .createFrameNode = CreateFrameNodeForCustom,
        .createButtonFrameNode = CreateButtonFrameNodeForCustom,
        .createButtonPattern = CreateButtonPatternForCustom,
        .createToggleButtonPattern = CreateToggleButtonPatternForCustom,
        .setComponentButtonType = SetComponentButtonTypeForCustom,
        .setSkipColorConfigurationUpdate = SetSkipColorConfigurationUpdateForCustom,
        .setClickedColor = SetClickedColorForCustom,
        .setBlendColor = SetBlendColorForCustom,
        .setBlendColorWithOptional = SetBlendColorWithOptionalForCustom,
        .setFocusBorderColor = SetFocusBorderColorForCustom,
        .setFocusBorderWidth = SetFocusBorderWidthForCustom,
        .setApplyShadow = SetApplyShadowForCustom,
        .handleButtonBackgroundColor = HandleButtonBackgroundColorForCustom,
        .setNavigationFocusBlendBgColor = SetNavigationFocusBlendBgColorForCustom,
        .setNavMenuItemNeedFocus = SetNavMenuItemNeedFocusForCustom,
        .setHasCustomPadding = SetHasCustomPaddingForCustom,
        .isToggleButtonPattern = IsToggleButtonPatternForCustom,
        .setToggleBackgroundColor = SetToggleBackgroundColorForCustom,
        .setToggleBackgroundColorWithFlag = SetToggleBackgroundColorWithFlagForCustom,
        .setButtonBorderRadius = SetButtonBorderRadiusForCustom,
        .setToggleBuilderFunc = SetToggleBuilderFuncForCustom,
        .setToggleButtonPress = SetToggleButtonPressForCustom,
        .setToggleOnChangeToEventHub = SetToggleOnChangeToEventHubForCustom,
        .setToggleOnChangeEventToEventHub = SetToggleOnChangeEventToEventHubForCustom,
        .isToggleButtonUseContentModifier = IsToggleButtonUseContentModifierForCustom,
        .getToggleButtonBuilderId = GetToggleButtonBuilderIdForCustom,
        .resetToggleSelectedColor = ResetToggleSelectedColorForCustom,
        .setToggleSelectedColor = SetToggleSelectedColorForCustom,
        .setToggleSelectedColorSetByUser = SetToggleSelectedColorSetByUserForCustom,
        .removeHoverListener = RemoveHoverListenerForCustom,
        .setButtonHover = SetButtonHoverForCustom,
        .getButtonHover = GetButtonHoverForCustom,
        .isButtonLayoutProperty = IsButtonLayoutPropertyForCustom,
        .setButtonLocalLocation = SetButtonLocalLocationForCustom,
        .getButtonLocalLocation = GetButtonLocalLocationForCustom,
        .isButtonPattern = IsButtonPatternForCustom,
        .updateToggleIsOnToPaintProp = UpdateToggleIsOnToPaintPropForCustom,
        .getToggleIsOnFromPaintProp = GetToggleIsOnFromPaintPropForCustom,
        .updateTypeToLayoutProp = UpdateTypeToLayoutPropForCustom,
        .setStateEffectToEventHub = SetStateEffectToEventHubForCustom,
        .getStateEffectFromEventHub = GetStateEffectFromEventHubForCustom,
        .updateBackgroundColorFlagByUserToLayoutProp = UpdateBackgroundColorFlagByUserToLayoutPropForCustom,
        .updateLabelToLayoutProp = UpdateLabelToLayoutPropForCustom,
        .updateFontSizeToLayoutProp = UpdateFontSizeToLayoutPropForCustom,
        .updateFontColorToLayoutProp = UpdateFontColorToLayoutPropForCustom,
        .updateFontWeightToLayoutProp = UpdateFontWeightToLayoutPropForCustom,
        .updateFontColorFlagByUserToLayoutProp = UpdateFontColorFlagByUserToLayoutPropForCustom,
        .updateFontStyleToLayoutProp = UpdateFontStyleToLayoutPropForCustom,
        .updateFontFamilyToLayoutProp = UpdateFontFamilyToLayoutPropForCustom,
        .updateButtonStyleToLayoutProp = UpdateButtonStyleToLayoutPropForCustom,
        .updateButtonRoleToLayoutProp = UpdateButtonRoleToLayoutPropForCustom,
        .updateControlSizeToLayoutProp = UpdateControlSizeToLayoutPropForCustom,
        .getButtonStyleFromLayoutProp = GetButtonStyleFromLayoutPropForCustom,
        .getButtonRoleFromLayoutProp = GetButtonRoleFromLayoutPropForCustom,
        .updateAutoDisableToLayoutProp = UpdateAutoDisableToLayoutPropForCustom,
        .getAutoDisableFromLayoutProp = GetAutoDisableFromLayoutPropForCustom,
        .hasFontColorFromLayoutProp = HasFontColorFromLayoutPropForCustom,
        .updateCreateWithLabelToLayoutProp = UpdateCreateWithLabelToLayoutPropForCustom,
        .updateBorderRadiusToLayoutProp = UpdateBorderRadiusToLayoutPropForCustom,
        .updateTextOverflowToLayoutProp = UpdateTextOverflowToLayoutPropForCustom,
        .updateMaxLinesToLayoutProp = UpdateMaxLinesToLayoutPropForCustom,
        .getBorderRadiusFromLayoutProp = GetBorderRadiusFromLayoutPropForCustom,
        .getFontSizeFromLayoutProp = GetFontSizeFromLayoutPropForCustom,
        .getFontColorFromLayoutProp = GetFontColorFromLayoutPropForCustom,
        .getLabelFromLayoutProp = GetLabelFromLayoutPropForCustom,
        .resetFontSizeToLayoutProp = ResetFontSizeToLayoutPropForCustom,
        .setFontColorDefault = SetFontColorDefaultForCustom,
        .setBackgroundColorDefault = SetBackgroundColorDefaultForCustom,
    };
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
