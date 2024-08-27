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

#include "core/components_ng/pattern/navigator/navigator_model_ng.h"

namespace OHOS::Ace::NG {
void SetTarget(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string uri = value;
    NavigatorModelNG::SetUri(frameNode, uri);
}

void ResetTarget(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetUri(frameNode, "");
}

void SetType(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto barMode = static_cast<OHOS::Ace::NavigatorType>(value);
    NavigatorModelNG::SetType(frameNode, barMode);
}

void ResetType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetType(frameNode, OHOS::Ace::NavigatorType::PUSH);
}

void SetActive(ArkUINodeHandle node, ArkUI_Bool active)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetActive(frameNode, active);
}

void ResetActive(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetActive(frameNode, false);
}

void SetParams(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string args = value;
    NavigatorModelNG::SetParams(frameNode, args);
}

void ResetParams(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetParams(frameNode, "");
}

namespace NodeModifier {
const ArkUINavigatorModifier* GetNavigatorModifier()
{
    static const ArkUINavigatorModifier modifier = {SetTarget, ResetTarget, SetType, ResetType, SetActive,
        ResetActive, SetParams, ResetParams };

    return &modifier;
}

const CJUINavigatorModifier* GetCJUINavigatorModifier()
{
    static const CJUINavigatorModifier modifier = {SetTarget, ResetTarget, SetType, ResetType, SetActive,
        ResetActive, SetParams, ResetParams };

    return &modifier;
}
}
} // namespace OHOS::Ace::NG