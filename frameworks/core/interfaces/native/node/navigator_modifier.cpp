/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/navigator_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
void SetTarget(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string uri = value;
    NavigatorModelNG::SetUri(frameNode, uri);
}

void ResetTarget(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetUri(frameNode, "");
}

void SetType(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto barMode = static_cast<OHOS::Ace::NavigatorType>(value);
    NavigatorModelNG::SetType(frameNode, barMode);
}

void ResetType(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetType(frameNode, OHOS::Ace::NavigatorType::PUSH);
}

void SetActive(NodeHandle node, bool active)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetActive(frameNode, active);
}

void ResetActive(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetActive(frameNode, false);
}

void SetParams(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string args = value;
    NavigatorModelNG::SetParams(frameNode, args);
}

void ResetParams(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetParams(frameNode, "");
}

ArkUINavigatorModifierAPI GetNavigatorModifier()
{
    static const ArkUINavigatorModifierAPI modifier = {SetTarget, ResetTarget, SetType, ResetType, SetActive,
        ResetActive, SetParams, ResetParams };

    return modifier;
}
} // namespace OHOS::Ace::NG