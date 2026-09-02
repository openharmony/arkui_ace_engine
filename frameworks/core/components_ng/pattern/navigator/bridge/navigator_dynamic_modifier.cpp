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

#include "ui/base/utils/utils.h"
#include "core/common/container.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigator/navigator_model_impl.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "core/interfaces/native/node/navigator_modifier.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
Framework::NavigatorModelImpl* GetNavigatorModelImpl()
{
    static Framework::NavigatorModelImpl instance;
    return &instance;
}
} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetTarget(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string uri = value;
    NavigatorModelNG::SetUri(frameNode, uri);
}

void ResetTarget(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetUri(frameNode, "");
}

void SetType(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto barMode = static_cast<OHOS::Ace::NavigatorType>(value);
    NavigatorModelNG::SetType(frameNode, barMode);
}

void ResetType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetType(frameNode, OHOS::Ace::NavigatorType::PUSH);
}

void SetActive(ArkUINodeHandle node, ArkUI_Bool active)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetActive(frameNode, active);
}

void ResetActive(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetActive(frameNode, false);
}

void SetParams(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string args = value;
    NavigatorModelNG::SetParams(frameNode, args);
}

void ResetParams(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetParams(frameNode, "");
}

void SetIsDefSize(ArkUI_Bool isWidth) {}
} // namespace


#ifndef CROSS_PLATFORM
void SetTargetImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    GetNavigatorModelImpl()->SetUri(value);
}

void ResetTargetImpl(ArkUINodeHandle node)
{
    GetNavigatorModelImpl()->SetUri("");
}

void SetTypeImpl(ArkUINodeHandle node, int32_t value)
{
    GetNavigatorModelImpl()->SetType(static_cast<NavigatorType>(value));
}

void ResetTypeImpl(ArkUINodeHandle node)
{
    GetNavigatorModelImpl()->SetType(NavigatorType::PUSH);
}

void SetActiveImpl(ArkUINodeHandle node, ArkUI_Bool active)
{
    GetNavigatorModelImpl()->SetActive(active);
}

void ResetActiveImpl(ArkUINodeHandle node)
{
    GetNavigatorModelImpl()->SetActive(false);
}

void SetParamsImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    GetNavigatorModelImpl()->SetParams(value);
}

void ResetParamsImpl(ArkUINodeHandle node)
{
    GetNavigatorModelImpl()->SetParams("");
}

void SetIsDefSizeImpl(ArkUI_Bool isWidth)
{
    if (isWidth) {
        GetNavigatorModelImpl()->SetIsDefWidth(true);
    } else {
        GetNavigatorModelImpl()->SetIsDefHeight(true);
    }
}
#endif

namespace NodeModifier {
const ArkUINavigatorModifier* GetNavigatorModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUINavigatorModifier modifier = {
            .setTarget = SetTargetImpl,
            .resetTarget = ResetTargetImpl,
            .setType = SetTypeImpl,
            .resetType = ResetTypeImpl,
            .setActive = SetActiveImpl,
            .resetActive = ResetActiveImpl,
            .setParams = SetParamsImpl,
            .resetParams = ResetParamsImpl,
            .setIsDefSize = SetIsDefSizeImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINavigatorModifier modifier = {
        .setTarget = SetTarget,
        .resetTarget = ResetTarget,
        .setType = SetType,
        .resetType = ResetType,
        .setActive = SetActive,
        .resetActive = ResetActive,
        .setParams = SetParams,
        .resetParams = ResetParams,
        .setIsDefSize = SetIsDefSize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUINavigatorModifier* GetCJUINavigatorModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUINavigatorModifier modifier = {
        .setTarget = SetTarget,
        .resetTarget = ResetTarget,
        .setType = SetType,
        .resetType = ResetType,
        .setActive = SetActive,
        .resetActive = ResetActive,
        .setParams = SetParams,
        .resetParams = ResetParams,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
}
