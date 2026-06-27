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

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_model_ng.h"
#include "core/interfaces/native/node/node_arc_list_modifier.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t OPTIONAL_FIELD_COUNT = 2;

// ---- bridge stubs ----

RefPtr<Pattern> CreateArcListPattern()
{
    return AceType::MakeRefPtr<ArcListPattern>();
}

void AddHeader(FrameNode* frameNode, FrameNode* headerNode)
{
    ArcListModelNG::SetHeader(frameNode, headerNode);
}

RefPtr<FrameNode> GetHeader(FrameNode* frameNode)
{
    return ArcListModelNG::GetHeader(frameNode);
}

void ResetHeader(FrameNode* frameNode)
{
    ArcListModelNG::ResetHeader(frameNode);
}

#ifdef SUPPORT_DIGITAL_CROWN
void SetDigitalCrownSensitivityBridge(FrameNode* frameNode, CrownSensitivity sensitivity)
{
    ArcListModelNG::SetDigitalCrownSensitivity(frameNode, sensitivity);
}

CrownSensitivity GetDigitalCrownSensitivityBridge(FrameNode* frameNode)
{
    return ArcListModelNG::GetDigitalCrownSensitivity(frameNode);
}
#endif

// ---- C API modifier stubs ----

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

const ArkUIArcListModifier* GetArcListModifier()
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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
