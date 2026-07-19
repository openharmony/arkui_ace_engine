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
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_model_ng.h"
#include "core/interfaces/native/node/node_arc_list_item_modifier.h"

namespace OHOS::Ace::NG {
namespace {

// ---- bridge stubs ----

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

// ---- C API modifier stubs ----

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

} // namespace

namespace NodeModifier {
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

const ArkUIArcListItemModifier* GetArcListItemModifier()
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
