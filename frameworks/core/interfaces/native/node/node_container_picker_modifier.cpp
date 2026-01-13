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

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_container_picker_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
enum GetValueArrayIndex {
    GETTOPLEFT,
    GETTOPRIGHT,
    GETBOTTOMLEFT,
    GETBOTTOMRIGHT,
};
enum ValueArrayIndex {
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT,
};

void SetContainerPickerCanLoop(ArkUINodeHandle node, int isLoop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetCanLoop(frameNode, isLoop);
}

void ResetContainerPickerCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetCanLoop(frameNode, true);
}

void SetContainerPickerOnChangeEvt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = reinterpret_cast<std::function<void(const double)>*>(callback);
    ContainerPickerModel::SetOnChange(frameNode, std::move(*onChange));
}

void ResetContainerPickerOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetOnChange(frameNode, nullptr);
}

void SetContainerPickerOnScrollStopEvt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollStop = reinterpret_cast<std::function<void(const double)>*>(callback);
    ContainerPickerModel::SetOnScrollStop(frameNode, std::move(*onScrollStop));
}

void ResetContainerPickerOnScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetOnScrollStop(frameNode, nullptr);
}

void SetContainerPickerEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Bool enableHapticFeedback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetEnableHapticFeedback(frameNode, enableHapticFeedback);
}

void ResetContainerPickerEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetEnableHapticFeedback(frameNode, true);
}

#define CONTAINER_PICKER_ADD_RADIUS_RESOURCE(radiusProp, propName, dimensionMember) \
    auto propName##Update = [](const RefPtr<ResourceObject>& obj, BorderRadiusProperty& prop) { \
        CalcDimension dim; \
        ResourceParseUtils::ParseResDimensionVp(obj, dim); \
        prop.dimensionMember = dim; \
    }; \
    const std::string resourceKey = std::string("borderRadius.") + #dimensionMember; \
    (radiusProp)->AddResource(resourceKey, propName##ResObj, std::move(propName##Update))

void AddRadiusResource(const struct ArkUIPickerIndicatorStyle* pickerIndicatorStyle,
    PickerIndicatorStyle& indicatorStyle)
{
    auto* topLeftResPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->topLeftRawPtr);
    auto topLeftResObj = AceType::Claim(topLeftResPtr);
    auto* topRightResPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->topRightRawPtr);
    auto topRightResObj = AceType::Claim(topRightResPtr);
    auto* bottomLeftResPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->bottomLeftRawPtr);
    auto bottomLeftResObj = AceType::Claim(bottomLeftResPtr);
    auto* bottomRightResPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->bottomRightRawPtr);
    auto bottomRightResObj = AceType::Claim(bottomRightResPtr);
    if (topLeftResObj) {
        CONTAINER_PICKER_ADD_RADIUS_RESOURCE(indicatorStyle.borderRadius, topLeft, radiusTopLeft);
    }
    if (topRightResObj) {
        CONTAINER_PICKER_ADD_RADIUS_RESOURCE(indicatorStyle.borderRadius, topRight, radiusTopRight);
    }
    if (bottomLeftResObj) {
        CONTAINER_PICKER_ADD_RADIUS_RESOURCE(indicatorStyle.borderRadius, bottomLeft, radiusBottomLeft);
    }
    if (bottomRightResObj) {
        CONTAINER_PICKER_ADD_RADIUS_RESOURCE(indicatorStyle.borderRadius, bottomRight, radiusBottomRight);
    }
}
void PickerRegisterResourceObj(FrameNode* frameNode, const struct ArkUIPickerIndicatorStyle* pickerIndicatorStyle,
    PickerIndicatorStyle& indicatorStyle)
{
    if (!SystemProperties::ConfigChangePerform() || !pickerIndicatorStyle) {
        return;
    }

    if (!pickerIndicatorStyle->isDefaultDividerWidth) {
        auto* strokeWidthPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->strokeWidthRawPtr);
        auto strokeWidthResObj = AceType::Claim(strokeWidthPtr);
        ContainerPickerModel::ProcessResourceObj(frameNode, "containerPicker.strokeWidth", strokeWidthResObj);
    }

    if (!pickerIndicatorStyle->isDefaultDividerColor) {
        auto* dividerColorPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->dividerColorRawPtr);
        auto dividerColorResObj = AceType::Claim(dividerColorPtr);
        ContainerPickerModel::ProcessResourceObj(frameNode, "containerPicker.dividerColor", dividerColorResObj);
    }

    if (!pickerIndicatorStyle->isDefaultStartMargin) {
        auto* startMarginPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->startMarginRawPtr);
        auto startMarginResObj = AceType::Claim(startMarginPtr);
        ContainerPickerModel::ProcessResourceObj(frameNode, "containerPicker.startMargin", startMarginResObj);
    }

    if (!pickerIndicatorStyle->isDefaultEndMargin) {
        auto* endMarginPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->endMarginRawPtr);
        auto endMarginResObj = AceType::Claim(endMarginPtr);
        ContainerPickerModel::ProcessResourceObj(frameNode, "containerPicker.endMargin", endMarginResObj);
    }

    if (!pickerIndicatorStyle->isDefaultBackgroundColor) {
        auto* bgColorPtr = reinterpret_cast<ResourceObject*>(pickerIndicatorStyle->backgroundColorRawPtr);
        auto bgColorResObj = AceType::Claim(bgColorPtr);
        ContainerPickerModel::ProcessResourceObj(frameNode, "containerPicker.backgroundColor", bgColorResObj);
    }

    if (!pickerIndicatorStyle->isDefaultBorderRadius) {
        AddRadiusResource(pickerIndicatorStyle, indicatorStyle);
        RefPtr<ResourceObject> radiusResObj = AceType::MakeRefPtr<ResourceObject>();
        ContainerPickerModel::ProcessResourceObj(frameNode, "containerPicker.borderRadius", radiusResObj);
    }
}

void SetContainerPickerSelectionIndicator(ArkUINodeHandle node, ArkUI_Bool* isHasValue,
    const struct ArkUIPickerIndicatorStyle* pickerIndicatorStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerIndicatorStyle);
    PickerIndicatorStyle indicatorStyle;
    indicatorStyle.isDefaultDividerWidth = pickerIndicatorStyle->isDefaultDividerWidth;
    indicatorStyle.isDefaultDividerColor = pickerIndicatorStyle->isDefaultDividerColor;
    indicatorStyle.isDefaultStartMargin = pickerIndicatorStyle->isDefaultStartMargin;
    indicatorStyle.isDefaultEndMargin = pickerIndicatorStyle->isDefaultEndMargin;
    indicatorStyle.isDefaultBackgroundColor = pickerIndicatorStyle->isDefaultBackgroundColor;
    indicatorStyle.isDefaultBorderRadius = pickerIndicatorStyle->isDefaultBorderRadius;

    indicatorStyle.type = pickerIndicatorStyle->type;
    indicatorStyle.strokeWidth = Dimension(pickerIndicatorStyle->strokeWidthValue,
        static_cast<DimensionUnit>(pickerIndicatorStyle->strokeWidthUnit));
    indicatorStyle.startMargin = Dimension(pickerIndicatorStyle->startMarginValue,
        static_cast<DimensionUnit>(pickerIndicatorStyle->startMarginUnit));
    indicatorStyle.endMargin = Dimension(pickerIndicatorStyle->endMarginValue,
        static_cast<DimensionUnit>(pickerIndicatorStyle->endMarginUnit));
    indicatorStyle.dividerColor = Color(pickerIndicatorStyle->dividerColor);

    indicatorStyle.backgroundColor = Color(pickerIndicatorStyle->backgroundColor);
    indicatorStyle.borderRadius = BorderRadiusProperty(DEFAULT_RADIUS);
    if (isHasValue[GETTOPLEFT]) {
        indicatorStyle.borderRadius->radiusTopLeft = Dimension(pickerIndicatorStyle->values[TOPLEFT],
            static_cast<DimensionUnit>(pickerIndicatorStyle->units[TOPLEFT]));
    }
    if (isHasValue[GETTOPRIGHT]) {
        indicatorStyle.borderRadius->radiusTopRight = Dimension(pickerIndicatorStyle->values[TOPRIGHT],
            static_cast<DimensionUnit>(pickerIndicatorStyle->units[TOPRIGHT]));
    }
    if (isHasValue[GETBOTTOMLEFT]) {
        indicatorStyle.borderRadius->radiusBottomLeft = Dimension(pickerIndicatorStyle->values[BOTTOMLEFT],
            static_cast<DimensionUnit>(pickerIndicatorStyle->units[BOTTOMLEFT]));
    }
    if (isHasValue[GETBOTTOMRIGHT]) {
        indicatorStyle.borderRadius->radiusBottomRight = Dimension(pickerIndicatorStyle->values[BOTTOMRIGHT],
            static_cast<DimensionUnit>(pickerIndicatorStyle->units[BOTTOMRIGHT]));
    }
    PickerRegisterResourceObj(frameNode, pickerIndicatorStyle, indicatorStyle);
    ContainerPickerModel::SetIndicatorStyle(frameNode, indicatorStyle);
}

void ResetContainerPickerSelectionIndicator(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<ContainerPickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    PickerIndicatorStyle indicatorStyle;
    indicatorStyle.strokeWidth = pickerTheme->GetStrokeWidth();
    indicatorStyle.dividerColor = pickerTheme->GetIndicatorDividerColor();
    indicatorStyle.startMargin = Dimension();
    indicatorStyle.endMargin = Dimension();
    indicatorStyle.backgroundColor = pickerTheme->GetIndicatorBackgroundColor();
    indicatorStyle.borderRadius = NG::BorderRadiusProperty(pickerTheme->GetIndicatorBackgroundRadius());
    ContainerPickerModel::SetIndicatorStyle(frameNode, indicatorStyle);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("containerPicker.strokeWidth");
        pattern->UnRegisterResource("containerPicker.dividerColor");
        pattern->UnRegisterResource("containerPicker.startMargin");
        pattern->UnRegisterResource("containerPicker.endMargin");
        pattern->UnRegisterResource("containerPicker.backgroundColor");
        pattern->UnRegisterResource("containerPicker.borderRadius");
    }
}

void SetContainerPickerSelectedIndex(ArkUINodeHandle node, int index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetSelectedIndex(frameNode, index);
}

void ResetContainerPickerSelectedIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetSelectedIndex(frameNode, 0);
}

void SetContainerPickerIndicator(ArkUINodeHandle node, const struct ArkUI_PickerIndicatorStyle* pickerIndicatorStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerIndicatorStyle indicatorStyle;
    indicatorStyle.type = pickerIndicatorStyle->type;
    if (indicatorStyle.type == static_cast<int32_t>(PickerIndicatorType::DIVIDER)) {
        indicatorStyle.strokeWidth = Dimension(pickerIndicatorStyle->strokeWidth, DimensionUnit::VP);
        indicatorStyle.dividerColor = Color(pickerIndicatorStyle->dividerColor);
        indicatorStyle.startMargin = Dimension(pickerIndicatorStyle->startMargin, DimensionUnit::VP);
        indicatorStyle.endMargin = Dimension(pickerIndicatorStyle->endMargin, DimensionUnit::VP);
    } else if (indicatorStyle.type == static_cast<int32_t>(PickerIndicatorType::BACKGROUND)) {
        indicatorStyle.backgroundColor = Color(pickerIndicatorStyle->backgroundColor);
        BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = Dimension(pickerIndicatorStyle->topLeftRadius, DimensionUnit::VP);
        borderRadius.radiusTopRight = Dimension(pickerIndicatorStyle->topRightRadius, DimensionUnit::VP);
        borderRadius.radiusBottomLeft = Dimension(pickerIndicatorStyle->bottomLeftRadius, DimensionUnit::VP);
        borderRadius.radiusBottomRight = Dimension(pickerIndicatorStyle->bottomRightRadius, DimensionUnit::VP);
        indicatorStyle.borderRadius = borderRadius;
    }
    ContainerPickerModel::SetIndicatorStyle(frameNode, indicatorStyle);
}

void ResetContainerPickerIndicator(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerIndicatorStyle indicatorStyle;
    indicatorStyle.type = 0;
    ContainerPickerModel::SetIndicatorStyle(frameNode, indicatorStyle);
}

int32_t GetContainerPickerSelectedIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return ContainerPickerModel::GetSelectedIndex(frameNode);
}

ArkUI_Bool GetContainerPickerEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return ContainerPickerModel::GetEnableHapticFeedback(frameNode);
}

ArkUI_Bool GetContainerPickerCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return ContainerPickerModel::GetCanLoop(frameNode);
}

ArkUI_PickerIndicatorStyle GetContainerPickerIndicator(ArkUINodeHandle node)
{
    ArkUI_PickerIndicatorStyle indicatorStyle;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, indicatorStyle);
    auto style = ContainerPickerModel::GetIndicatorStyle(frameNode);
    indicatorStyle.type = static_cast<uint32_t>(style.type);
    if (style.type == static_cast<int32_t>(PickerIndicatorType::DIVIDER)) {
        indicatorStyle.strokeWidth = style.strokeWidth->Value();
        indicatorStyle.dividerColor = style.dividerColor->GetValue();
        indicatorStyle.startMargin = style.startMargin->Value();
        indicatorStyle.endMargin = style.endMargin->Value();
    } else if (style.type == static_cast<int32_t>(PickerIndicatorType::BACKGROUND)) {
        indicatorStyle.backgroundColor = style.backgroundColor->GetValue();
        indicatorStyle.topLeftRadius = style.borderRadius->radiusTopLeft->Value();
        indicatorStyle.topRightRadius = style.borderRadius->radiusTopRight->Value();
        indicatorStyle.bottomLeftRadius = style.borderRadius->radiusBottomLeft->Value();
        indicatorStyle.bottomRightRadius = style.borderRadius->radiusBottomRight->Value();
    }
    return indicatorStyle;
}
}  // namespace

namespace NodeModifier {
const ArkUIContainerPickerModifier* GetContainerPickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();  // don't move this line
    static const ArkUIContainerPickerModifier modifier = {
        .setContainerPickerOnChange = SetContainerPickerOnChangeEvt,
        .resetContainerPickerOnChange = ResetContainerPickerOnChange,
        .setContainerPickerOnScrollStop = SetContainerPickerOnScrollStopEvt,
        .resetContainerPickerOnScrollStop = ResetContainerPickerOnScrollStop,
        .setContainerPickerEnableHapticFeedback = SetContainerPickerEnableHapticFeedback,
        .resetContainerPickerEnableHapticFeedback = ResetContainerPickerEnableHapticFeedback,
        .setContainerPickerCanLoop = SetContainerPickerCanLoop,
        .resetContainerPickerCanLoop = ResetContainerPickerCanLoop,
        .setContainerPickerSelectionIndicator = SetContainerPickerSelectionIndicator,
        .resetContainerPickerSelectionIndicator = ResetContainerPickerSelectionIndicator,
        .setContainerPickerSelectedIndex = SetContainerPickerSelectedIndex,
        .resetContainerPickerSelectedIndex = ResetContainerPickerSelectedIndex,
        .setContainerPickerIndicator = SetContainerPickerIndicator,
        .resetContainerPickerIndicator = ResetContainerPickerIndicator,
        .getContainerPickerSelectedIndex = GetContainerPickerSelectedIndex,
        .getContainerPickerEnableHapticFeedback = GetContainerPickerEnableHapticFeedback,
        .getContainerPickerCanLoop = GetContainerPickerCanLoop,
        .getContainerPickerIndicator = GetContainerPickerIndicator,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);  // don't move this line

    return &modifier;
}

void SetPickerOnChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto callback = [extraParam](const double selectedIndex) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_CONTAINER_PICKER_CHANGE;
        event.mixedEvent.numberData[0].i32 = selectedIndex;
        SendArkUISyncEvent(&event);
    };
    ContainerPickerModel::SetOnChange(frameNode, std::move(callback));
}

void SetPickerOnScrollStop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto callback = [extraParam](const double selectedIndex) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_CONTAINER_PICKER_SCROLL_STOP;
        event.mixedEvent.numberData[0].i32 = selectedIndex;
        SendArkUISyncEvent(&event);
    };
    ContainerPickerModel::SetOnScrollStop(frameNode, std::move(callback));
}

void ResetPickerOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetOnChange(frameNode, nullptr);
}

void ResetPickerOnScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ContainerPickerModel::SetOnScrollStop(frameNode, nullptr);
}
}  // namespace NodeModifier
}  // namespace OHOS::Ace::NG
