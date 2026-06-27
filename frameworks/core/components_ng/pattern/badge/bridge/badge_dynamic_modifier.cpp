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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/badge/bridge/badge_custom_modifier.h"
#include "core/components_ng/pattern/badge/badge_data.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
namespace {

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetBadgeBaseParam(BadgeParameters& badgeParameters, const ArkUIBadgeParam& style)
{
    badgeParameters.isPositionXy = style.isPositionXy;
    if (style.isPositionXy) {
        badgeParameters.badgePositionX =
            Dimension(style.positionX.value, static_cast<DimensionUnit>(style.positionX.units));
        badgeParameters.badgePositionY =
            Dimension(style.positionY.value, static_cast<DimensionUnit>(style.positionY.units));
    } else {
        badgeParameters.badgePosition = style.position;
    }
    badgeParameters.badgeColor = Color(style.badgeColor);
    badgeParameters.badgeTextColor = Color(style.textColor);
    badgeParameters.badgeBorderColor = Color(style.borderColor);
    badgeParameters.badgeOuterBorderColor = Color(style.outerBorderColor);
    badgeParameters.badgeFontWeight = static_cast<FontWeight>(style.fontWeight);
    badgeParameters.badgeFontSize = Dimension(style.fontSize.value, static_cast<DimensionUnit>(style.fontSize.units));
    badgeParameters.badgeCircleSize =
        Dimension(style.badgeSize.value, static_cast<DimensionUnit>(style.badgeSize.units));
    badgeParameters.badgeBorderWidth =
        Dimension(style.borderWidth.value, static_cast<DimensionUnit>(style.borderWidth.units));
    badgeParameters.badgeOuterBorderWidth =
        Dimension(style.outerBorderWidth.value, static_cast<DimensionUnit>(style.outerBorderWidth.units));
    badgeParameters.isEnableAutoAvoidance = style.enableAutoAvoidance;
}

void SetBadgePositionParam(BadgeParameters& badgeParameters, const ArkUIBadgeJSParam& JSParam)
{
    badgeParameters.isPositionXy = JSParam.isPositionXy;
    if (JSParam.isPositionXy) {
        badgeParameters.badgePositionX =
            Dimension(JSParam.positionX.value, static_cast<DimensionUnit>(JSParam.positionX.units));
        badgeParameters.badgePositionY =
            Dimension(JSParam.positionY.value, static_cast<DimensionUnit>(JSParam.positionY.units));
    } else {
        badgeParameters.badgePosition = JSParam.position;
    }
}

void SetBadgeStyleParam(
    BadgeParameters& badgeParameters, const ArkUIBadgeJSParam& JSParam)
{
    if (JSParam.hasBadgeColor) {
        badgeParameters.badgeColor = Color(JSParam.badgeColor);
    }
    if (JSParam.hasTextColor) {
        badgeParameters.badgeTextColor = Color(JSParam.textColor);
    }
    if (JSParam.hasBorderColor) {
        badgeParameters.badgeBorderColor = Color(JSParam.borderColor);
    }
    if (JSParam.hasOuterBorderColor) {
        badgeParameters.badgeOuterBorderColor = Color(JSParam.outerBorderColor);
    }
    if (JSParam.hasFontWeight) {
        badgeParameters.badgeFontWeight = static_cast<FontWeight>(JSParam.fontWeight);
    }
    if (JSParam.hasFontSize) {
        badgeParameters.badgeFontSize =
            Dimension(JSParam.fontSize.value, static_cast<DimensionUnit>(JSParam.fontSize.units));
    }
    if (JSParam.hasBadgeSize) {
        badgeParameters.badgeCircleSize =
            Dimension(JSParam.badgeSize.value, static_cast<DimensionUnit>(JSParam.badgeSize.units));
    }
    if (JSParam.hasBorderWidth) {
        badgeParameters.badgeBorderWidth =
            Dimension(JSParam.borderWidth.value, static_cast<DimensionUnit>(JSParam.borderWidth.units));
    }
    if (JSParam.hasOuterBorderWidth) {
        badgeParameters.badgeOuterBorderWidth =
            Dimension(JSParam.outerBorderWidth.value, static_cast<DimensionUnit>(JSParam.outerBorderWidth.units));
    }
    if (JSParam.hasEnableAutoAvoidance) {
        badgeParameters.isEnableAutoAvoidance = JSParam.enableAutoAvoidance;
    }
}

void SetBadgeResObjParam(BadgeParameters& badgeParameters, const ArkUIBadgeJSParam& JSParam)
{
    if (JSParam.resourceBadgeValueObject != nullptr) {
        badgeParameters.resourceBadgeValueObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceBadgeValueObject));
    }
    if (JSParam.resourceColorObject != nullptr) {
        badgeParameters.resourceColorObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceColorObject));
    }
    if (JSParam.resourceBadgeColorObject != nullptr) {
        badgeParameters.resourceBadgeColorObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceBadgeColorObject));
    }
    if (JSParam.resourceBorderColorObject != nullptr) {
        badgeParameters.resourceBorderColorObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceBorderColorObject));
    }
    if (JSParam.resourceOuterBorderColorObject != nullptr) {
        badgeParameters.resourceOuterBorderColorObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceOuterBorderColorObject));
    }
    if (JSParam.resourceFontWeightObject != nullptr) {
        badgeParameters.resourceFontWeightObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceFontWeightObject));
    }
    if (JSParam.resourceBadgeSizeObject != nullptr) {
        badgeParameters.resourceBadgeSizeObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceBadgeSizeObject));
    }
    if (JSParam.resourceFontSizeObject != nullptr) {
        badgeParameters.resourceFontSizeObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceFontSizeObject));
    }
    if (JSParam.resourceBadgePositionXObject != nullptr) {
        badgeParameters.resourceBadgePositionXObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceBadgePositionXObject));
    }
    if (JSParam.resourceBadgePositionYObject != nullptr) {
        badgeParameters.resourceBadgePositionYObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceBadgePositionYObject));
    }
    if (JSParam.resourceBorderWidthObject != nullptr) {
        badgeParameters.resourceBorderWidthObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceBorderWidthObject));
    }
    if (JSParam.resourceOuterBorderWidthObject != nullptr) {
        badgeParameters.resourceOuterBorderWidthObject =
            AceType::Claim(reinterpret_cast<ResourceObject*>(JSParam.resourceOuterBorderWidthObject));
    }
}

static void SetBadgeJSParam(
    BadgeParameters& badgeParameters, const ArkUIBadgeJSParam& JSParam)
{
    if (JSParam.hasBadgeValue && JSParam.badgeValue != nullptr) {
        badgeParameters.badgeValue = std::string(JSParam.badgeValue);
    }
    if (JSParam.hasBadgeCount) {
        badgeParameters.badgeCount = JSParam.badgeCount;
    }
    if (JSParam.hasBadgeMaxCount) {
        badgeParameters.badgeMaxCount = JSParam.badgeMaxCount;
    }
    badgeParameters.badgePositionXByUser = JSParam.badgePositionXByUser;
    badgeParameters.badgePositionYByUser = JSParam.badgePositionYByUser;
    badgeParameters.badgeTextColorByUser = JSParam.badgeTextColorByUser;
    badgeParameters.badgeFontSizeByUser = JSParam.badgeFontSizeByUser;
    badgeParameters.badgeCircleSizeByUser = JSParam.badgeCircleSizeByUser;
    badgeParameters.badgeColorByUser = JSParam.badgeColorByUser;
    badgeParameters.badgeBorderWidthByUser = JSParam.badgeBorderWidthByUser;
    badgeParameters.badgeBorderColorByUser = JSParam.badgeBorderColorByUser;
    badgeParameters.badgeOuterBorderWidthByUser = JSParam.badgeOuterBorderWidthByUser;
    badgeParameters.badgeOuterBorderColorByUser = JSParam.badgeOuterBorderColorByUser;
    if (JSParam.hasPosition) {
        SetBadgePositionParam(badgeParameters, JSParam);
    }
    SetBadgeStyleParam(badgeParameters, JSParam);
    SetBadgeResObjParam(badgeParameters, JSParam);
}

void CreateBadge(const ArkUIBadgeJSParam* badgeJSParam)
{
    CHECK_NULL_VOID(badgeJSParam);
    BadgeParameters badgeParameters;
    SetBadgeJSParam(badgeParameters, *badgeJSParam);

    bool isDefaultFontSize = badgeJSParam->hasFontSize ? badgeJSParam->isDefaultFontSize : true;
    bool isDefaultBadgeSize = badgeJSParam->hasBadgeSize ? badgeJSParam->isDefaultBadgeSize : true;
    BadgeModelNG::CreateModel(badgeParameters, isDefaultFontSize, isDefaultBadgeSize);
}

void SetBadgeParamWithNumber(ArkUINodeHandle node, const struct ArkUIBadgeParam* style, ArkUI_Int32 count,
    ArkUI_Bool countHasValue, ArkUI_Int32 maxCount)
{
    CHECK_NULL_VOID(style);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    BadgeParameters badgeParameters;
    SetBadgeBaseParam(badgeParameters, *style);
    if (countHasValue) {
        badgeParameters.badgeCount = count;
    } else {
        badgeParameters.badgeCount = std::optional<int>();
    }
    badgeParameters.badgeMaxCount = maxCount;
    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, style->isDefaultFontSize, style->isDefaultBadgeSize);
}

void SetBadgeParamWithString(ArkUINodeHandle node, const struct ArkUIBadgeParam* style, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(style);
    CHECK_NULL_VOID(value);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    BadgeParameters badgeParameters;
    SetBadgeBaseParam(badgeParameters, *style);
    badgeParameters.badgeValue = std::string(value);
    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, style->isDefaultFontSize, style->isDefaultBadgeSize);
}

ArkUINodeHandle CreateBadgeFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = BadgeModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetBadgeParam(NG::FrameNode* frameNode, BadgeParameters& badgeParameters, bool isDefaultFontSize,
    bool isDefaultBadgeSize)
{
    CHECK_NULL_VOID(frameNode);
    BadgeModelNG::SetBadgeParam(frameNode, badgeParameters, isDefaultFontSize, isDefaultBadgeSize);
}

void UpdateBadgeColor(const RefPtr<BadgePattern>& badgePattern, const Color& badgeColor, bool isFirstLoad)
{
    CHECK_NULL_VOID(badgePattern);
    badgePattern->UpdateBadgeColor(badgeColor, isFirstLoad);
}

void UpdateColor(const RefPtr<BadgePattern>& badgePattern, const Color& color, bool isFirstLoad)
{
    CHECK_NULL_VOID(badgePattern);
    badgePattern->UpdateColor(color, isFirstLoad);
}
} // namespace

namespace NodeModifier {
const ArkUIBadgeModifier* GetBadgeDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIBadgeModifier modifier = {
        .setBadgeParameters = nullptr,
        .setBadgeValue = nullptr,
        .setBadgeCount = nullptr,
        .setBadgeMaxCount = nullptr,
        .setBadgeFontWeight = nullptr,
        .setBadgeParamWithNumber = SetBadgeParamWithNumber,
        .setBadgeParamWithString = SetBadgeParamWithString,
        .createBadgeFrameNode = CreateBadgeFrameNode,
        .createBadge = CreateBadge,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}
const ArkUIBadgeCustomModifier* GetBadgeCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIBadgeCustomModifier modifier = {
        .setBadgeParam = SetBadgeParam,
        .updateBadgeColor = UpdateBadgeColor,
        .updateColor = UpdateColor,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
