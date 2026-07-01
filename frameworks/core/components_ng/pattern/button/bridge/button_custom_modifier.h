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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BRIDGE_BUTTON_CUSTOM_MODIFIER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BRIDGE_BUTTON_CUSTOM_MODIFIER_H

#include <functional>
#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
class FrameNode;
struct ArkUIButtonCustomModifier {
    ArkUINodeHandle (*createFrameNode)(ArkUI_Int32 nodeId);
    ArkUINodeHandle (*createButtonFrameNode)(ArkUI_Int32 nodeId);
    void* (*createButtonPattern)();
    void* (*createToggleButtonPattern)();
    void (*setComponentButtonType)(ArkUINodeHandle node, OHOS::Ace::ComponentButtonType buttonType);
    void (*setSkipColorConfigurationUpdate)(ArkUINodeHandle node);
    void (*setClickedColor)(ArkUINodeHandle node, const OHOS::Ace::Color& color);
    void (*setBlendColor)(ArkUINodeHandle node, const OHOS::Ace::Color& clickColor, const OHOS::Ace::Color& hoverColor);
    void (*setBlendColorWithOptional)(ArkUINodeHandle node, const std::optional<OHOS::Ace::Color>& clickColor,
        const std::optional<OHOS::Ace::Color>& hoverColor);
    void (*setFocusBorderColor)(ArkUINodeHandle node, const OHOS::Ace::Color& color);
    void (*setFocusBorderWidth)(ArkUINodeHandle node, const OHOS::Ace::Dimension& width);
    void (*setApplyShadow)(ArkUINodeHandle node, bool shadow);
    void (*handleButtonBackgroundColor)(ArkUINodeHandle node);
    void (*setNavigationFocusBlendBgColor)(ArkUINodeHandle node, const OHOS::Ace::Color& color);
    void (*setNavMenuItemNeedFocus)(ArkUINodeHandle node, bool needFocus);
    void (*setHasCustomPadding)(ArkUINodeHandle node, bool hasCustomPadding);
    bool (*isToggleButtonPattern)(ArkUINodeHandle node);
    void (*setToggleBackgroundColor)(ArkUINodeHandle node, const OHOS::Ace::Color& color);
    void (*setToggleBackgroundColorWithFlag)(ArkUINodeHandle node, const OHOS::Ace::Color& color, bool flag);
    void (*setButtonBorderRadius)(ArkUINodeHandle node, const std::optional<OHOS::Ace::Dimension>& topLeft,
        const std::optional<OHOS::Ace::Dimension>& topRight, const std::optional<OHOS::Ace::Dimension>& bottomLeft,
        const std::optional<OHOS::Ace::Dimension>& bottomRight);
    void (*setToggleBuilderFunc)(ArkUINodeHandle node, void* callback);
    void (*setToggleButtonPress)(ArkUINodeHandle node, bool value);
    void (*setToggleOnChangeToEventHub)(ArkUINodeHandle node, std::function<void(const bool)>&& onChange);
    void (*setToggleOnChangeEventToEventHub)(ArkUINodeHandle node, std::function<void(const bool)>&& onChangeEvent);
    bool (*isToggleButtonUseContentModifier)(ArkUINodeHandle node);
    int32_t (*getToggleButtonBuilderId)(ArkUINodeHandle node);
    void (*resetToggleSelectedColor)(ArkUINodeHandle node);
    void (*setToggleSelectedColor)(ArkUINodeHandle node, const OHOS::Ace::Color& color);
    void (*setToggleSelectedColorSetByUser)(ArkUINodeHandle node, bool isByUser);
    void (*removeHoverListener)(ArkUINodeHandle node);
    void (*setButtonHover)(ArkUINodeHandle node, bool isHover);
    bool (*getButtonHover)(ArkUINodeHandle node);
    bool (*isButtonLayoutProperty)(ArkUINodeHandle node);
    void (*setButtonLocalLocation)(ArkUINodeHandle node, const OHOS::Ace::Offset& localLocation);
    const OHOS::Ace::Offset& (*getButtonLocalLocation)(ArkUINodeHandle node);
    bool (*isButtonPattern)(ArkUINodeHandle node);
    void (*updateToggleIsOnToPaintProp)(ArkUINodeHandle node, bool isOn);
    bool (*getToggleIsOnFromPaintProp)(ArkUINodeHandle node, bool defaultValue);
    void (*updateTypeToLayoutProp)(ArkUINodeHandle node, OHOS::Ace::ButtonType type);
    void (*setStateEffectToEventHub)(ArkUINodeHandle node, bool stateEffect);
    bool (*getStateEffectFromEventHub)(ArkUINodeHandle node);
    void (*updateBackgroundColorFlagByUserToLayoutProp)(ArkUINodeHandle node, bool value);
    void (*updateLabelToLayoutProp)(ArkUINodeHandle node, const std::string& label);
    void (*updateFontSizeToLayoutProp)(ArkUINodeHandle node, const OHOS::Ace::Dimension& fontSize);
    void (*updateFontColorToLayoutProp)(ArkUINodeHandle node, const OHOS::Ace::Color& color);
    void (*updateFontWeightToLayoutProp)(ArkUINodeHandle node, OHOS::Ace::FontWeight fontWeight);
    void (*updateFontColorFlagByUserToLayoutProp)(ArkUINodeHandle node, bool value);
    void (*updateFontStyleToLayoutProp)(ArkUINodeHandle node, OHOS::Ace::FontStyle fontStyle);
    void (*updateFontFamilyToLayoutProp)(ArkUINodeHandle node, const std::vector<std::string>& fontFamily);
    void (*updateButtonStyleToLayoutProp)(ArkUINodeHandle node, OHOS::Ace::ButtonStyleMode buttonStyle);
    void (*updateButtonRoleToLayoutProp)(ArkUINodeHandle node, OHOS::Ace::ButtonRole buttonRole);
    void (*updateControlSizeToLayoutProp)(ArkUINodeHandle node, OHOS::Ace::ControlSize controlSize);
    const std::optional<OHOS::Ace::ButtonStyleMode>& (*getButtonStyleFromLayoutProp)(ArkUINodeHandle node);
    const std::optional<OHOS::Ace::ButtonRole>& (*getButtonRoleFromLayoutProp)(ArkUINodeHandle node);
    void (*updateAutoDisableToLayoutProp)(ArkUINodeHandle node, bool autoDisable);
    const std::optional<bool>& (*getAutoDisableFromLayoutProp)(ArkUINodeHandle node);
    bool (*hasFontColorFromLayoutProp)(ArkUINodeHandle node);
    void (*updateCreateWithLabelToLayoutProp)(ArkUINodeHandle node, bool createWithLabel);
    void (*updateBorderRadiusToLayoutProp)(
        ArkUINodeHandle node, const OHOS::Ace::NG::BorderRadiusProperty& borderRadius);
    void (*updateTextOverflowToLayoutProp)(ArkUINodeHandle node, OHOS::Ace::TextOverflow textOverflow);
    void (*updateMaxLinesToLayoutProp)(ArkUINodeHandle node, uint32_t maxLines);
    const std::optional<OHOS::Ace::NG::BorderRadiusProperty>& (*getBorderRadiusFromLayoutProp)(ArkUINodeHandle node);
    const std::optional<OHOS::Ace::Dimension>& (*getFontSizeFromLayoutProp)(ArkUINodeHandle node);
    const std::optional<OHOS::Ace::Color>& (*getFontColorFromLayoutProp)(ArkUINodeHandle node);
    const std::string& (*getLabelFromLayoutProp)(ArkUINodeHandle node);
    void (*resetFontSizeToLayoutProp)(ArkUINodeHandle node);
    void (*setSingleBorderRadius)(const OHOS::Ace::Dimension& radius);
    void (*setLocalizedBorderRadius)(
        const std::optional<OHOS::Ace::Dimension>& radiusTopStart,
        const std::optional<OHOS::Ace::Dimension>& radiusTopEnd,
        const std::optional<OHOS::Ace::Dimension>& radiusBottomStart,
        const std::optional<OHOS::Ace::Dimension>& radiusBottomEnd);
    void (*resetBorderRadius)();
    void (*setFontColorDefault)(const OHOS::Ace::Color& color);
    void (*setBackgroundColorDefault)(const OHOS::Ace::Color& color);
    void (*setBackgroundColorToModelStatic)(FrameNode* frameNode, const std::optional<OHOS::Ace::Color>& color);
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BRIDGE_BUTTON_CUSTOM_MODIFIER_H