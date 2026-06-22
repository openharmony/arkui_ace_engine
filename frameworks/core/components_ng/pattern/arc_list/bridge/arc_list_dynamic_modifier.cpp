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
#include "core/components_ng/pattern/arc_list/arc_list_model_ng.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_model_ng.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/arc_list/bridge/arc_list_custom_modifier.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t OPTIONAL_FIELD_COUNT = 2;

// ---- bridge functions ----

RefPtr<Pattern> CreateArcListPattern()
{
    return AceType::MakeRefPtr<ArcListPattern>();
}

void AddHeader(FrameNode* frameNode, FrameNode* headerNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(headerNode);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    if (pattern) {
        pattern->AddHeader(AceType::Claim(headerNode));
    }
}

RefPtr<FrameNode> GetHeader(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    return pattern ? pattern->GetHeader() : nullptr;
}

void ResetHeader(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    if (pattern) {
        pattern->ResetHeader();
    }
}

#ifdef SUPPORT_DIGITAL_CROWN
void SetDigitalCrownSensitivityBridge(FrameNode* frameNode, CrownSensitivity sensitivity)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    if (pattern) {
        pattern->SetDigitalCrownSensitivity(sensitivity);
    }
}

CrownSensitivity GetDigitalCrownSensitivityBridge(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, CrownSensitivity::MEDIUM);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    return pattern ? pattern->GetDigitalCrownSensitivity() : CrownSensitivity::MEDIUM;
}
#endif

RefPtr<Pattern> CreateArcListItemPattern(void* builder, int32_t style)
{
    return AceType::MakeRefPtr<ArcListItemPattern>(
        builder ? AceType::Claim(reinterpret_cast<ShallowBuilder*>(builder)) : nullptr,
        static_cast<V2::ListItemStyle>(style));
}

void SetAutoScaleBridge(FrameNode* frameNode, bool autoScale)
{
    ArcListItemModelNG::SetAutoScale(frameNode, autoScale);
}

void ResetAutoScaleBridge(FrameNode* frameNode)
{
    ArcListItemModelNG::ResetAutoScale(frameNode);
}

// ---- C API modifier functions ----

void SetAutoScale(ArkUINodeHandle node, ArkUI_Bool autoScale)
{
    CHECK_NULL_VOID(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ArcListItemModelNG::SetAutoScale(frameNode, autoScale);
}

ArkUI_Bool GetAutoScale(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, true);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    return ArcListItemModelNG::GetAutoScale(frameNode);
}

void ResetAutoScale(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ArcListItemModelNG::SetAutoScale(frameNode, true);
}

void SetDigitalCrownSensitivity(ArkUINodeHandle node, ArkUI_Int32 sensitivity)
{
#ifdef SUPPORT_DIGITAL_CROWN
    CHECK_NULL_VOID(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ArcListModelNG::SetDigitalCrownSensitivity(frameNode, static_cast<CrownSensitivity>(sensitivity));
#endif
}

ArkUI_Int32 GetDigitalCrownSensitivity(ArkUINodeHandle node)
{
#ifdef SUPPORT_DIGITAL_CROWN
    CHECK_NULL_RETURN(node, static_cast<ArkUI_Int32>(CrownSensitivity::MEDIUM));
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    return static_cast<ArkUI_Int32>(ArcListModelNG::GetDigitalCrownSensitivity(frameNode));
#else
    return static_cast<ArkUI_Int32>(CrownSensitivity::MEDIUM);
#endif
}

void ResetDigitalCrownSensitivity(ArkUINodeHandle node)
{
#ifdef SUPPORT_DIGITAL_CROWN
    CHECK_NULL_VOID(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ArcListModelNG::ResetDigitalCrownSensitivity(frameNode);
#endif
}

void SetArcListHeader(ArkUINodeHandle node, ArkUINodeHandle header)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(header);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* headerNode = reinterpret_cast<FrameNode*>(header);
    ArcListModelNG::SetHeader(frameNode, headerNode);
}

ArkUINodeHandle GetArcListHeader(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto header = ArcListModelNG::GetHeader(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(header));
}

void ResetArcListHeader(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ArcListModelNG::ResetHeader(frameNode);
}

} // namespace

namespace NodeModifier {

const ArkUIArcListCustomModifier* GetArcListCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIArcListCustomModifier modifier = {
        .createArcListPattern = CreateArcListPattern,
        .addHeader = AddHeader,
        .getHeader = GetHeader,
        .resetHeader = ResetHeader,
#ifdef SUPPORT_DIGITAL_CROWN
        .setDigitalCrownSensitivity = SetDigitalCrownSensitivityBridge,
#else
        .setDigitalCrownSensitivity = nullptr,
#endif
#ifdef SUPPORT_DIGITAL_CROWN
        .getDigitalCrownSensitivity = GetDigitalCrownSensitivityBridge,
#else
        .getDigitalCrownSensitivity = nullptr,
#endif
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, OPTIONAL_FIELD_COUNT, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIArcListItemCustomModifier* GetArcListItemCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIArcListItemCustomModifier modifier = {
        .createArcListItemPattern = CreateArcListItemPattern,
        .setAutoScale = SetAutoScaleBridge,
        .resetAutoScale = ResetAutoScaleBridge,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIArcListModifier* GetArcListDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIArcListModifier modifier = {
        .setDigitalCrownSensitivity = SetDigitalCrownSensitivity,
        .getDigitalCrownSensitivity = GetDigitalCrownSensitivity,
        .resetDigitalCrownSensitivity = ResetDigitalCrownSensitivity,
        .setArcListHeader = SetArcListHeader,
        .getArcListHeader = GetArcListHeader,
        .resetArcListHeader = ResetArcListHeader,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIArcListItemModifier* GetArcListItemDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIArcListItemModifier modifier = {
        .setAutoScale = SetAutoScale,
        .getAutoScale = GetAutoScale,
        .resetAutoScale = ResetAutoScale,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
