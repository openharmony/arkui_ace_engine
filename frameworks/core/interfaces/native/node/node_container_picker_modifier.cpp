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
#include "core/interfaces/native/node/node_container_picker_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"
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

void SetContainerPickerSelectionIndicator(ArkUINodeHandle node, ArkUI_Bool* isHasValue,
    const struct ArkUIPickerIndicatorStyle* pickerIndicatorStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerIndicatorStyle indicatorStyle;
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

    AddRadiusResource(pickerIndicatorStyle, indicatorStyle);
    ContainerPickerModel::SetIndicatorStyle(frameNode, indicatorStyle);
}

void ResetContainerPickerSelectionIndicator(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerIndicatorStyle indicatorStyle;
    ContainerPickerModel::SetIndicatorStyle(frameNode, indicatorStyle);
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
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);  // don't move this line

    return &modifier;
}
}  // namespace NodeModifier
}  // namespace OHOS::Ace::NG
