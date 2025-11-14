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
#include "list_item_group_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_static.h"
#include "core/components_ng/pattern/list/list_item_group_model_static.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"

namespace OHOS::Ace::NG {
Dimension ConvertLengthToDimension(const ArkUIListItemGroupSpace &src)
{
    auto unit = static_cast<OHOS::Ace::DimensionUnit>(src.unit);
    auto value = src.value;
    if (unit == OHOS::Ace::DimensionUnit::PERCENT) {
        value /= 100.0f;
    }
    return Dimension(value, unit);
}

void SetListItemGroupHeaderContent(ArkUINodeHandle node, ArkUINodeHandle headerPtr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* headerContentPtr = reinterpret_cast<FrameNodePeer*>(headerPtr);
    CHECK_NULL_VOID(headerContentPtr);

    auto headerContentNodePtr = FrameNodePeer::GetFrameNodeByPeer(headerContentPtr);
    CHECK_NULL_VOID(headerContentNodePtr);
    NG::ListItemGroupModelStatic::SetHeader(frameNode, headerContentNodePtr, true);
}

void SetListItemGroupHeader(ArkUINodeHandle node, ArkUINodeHandle headerPtr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto uiNode = AceType::Claim(reinterpret_cast<UINode*>(headerPtr));
    CHECK_NULL_VOID(uiNode);

    NG::ListItemGroupModelStatic::SetHeader(frameNode, uiNode);
}

void ResetListItemGroupHeader(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ListItemGroupModelStatic::SetHeader(frameNode, nullptr);
}

void SetListItemGroupFooterContent(ArkUINodeHandle node, ArkUINodeHandle footerPtr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* footerContentPtr = reinterpret_cast<FrameNodePeer*>(footerPtr);
    CHECK_NULL_VOID(footerContentPtr);

    auto footerContentNodePtr = FrameNodePeer::GetFrameNodeByPeer(footerContentPtr);
    CHECK_NULL_VOID(footerContentNodePtr);
    NG::ListItemGroupModelStatic::SetFooter(frameNode, footerContentNodePtr, true);
}

void SetListItemGroupFooter(ArkUINodeHandle node, ArkUINodeHandle footerPtr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto uiNode = AceType::Claim(reinterpret_cast<UINode*>(footerPtr));
    CHECK_NULL_VOID(uiNode);

    NG::ListItemGroupModelStatic::SetFooter(frameNode, uiNode);
}

void ResetListItemGroupFooter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ListItemGroupModelStatic::SetFooter(frameNode, nullptr);
}

void SetListItemGroupStyle(ArkUINodeHandle node, int32_t style)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto styleValue = V2::ListItemGroupStyle::NONE;
    styleValue = static_cast<V2::ListItemGroupStyle>(style);
    if (styleValue < V2::ListItemGroupStyle::NONE || styleValue > V2::ListItemGroupStyle::CARD) {
        styleValue = V2::ListItemGroupStyle::NONE;
    }
    ListItemGroupModelStatic::SetStyle(frameNode, styleValue);
}

void SetListItemGroupSpace(ArkUINodeHandle node, ArkUIListItemGroupSpace space)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemGroupModelStatic::SetSpace(frameNode, ConvertLengthToDimension(space));
}

const ArkUIAniListItemGroupModifier* GetArkUIAniListItemGroupModifier()
{
    static const ArkUIAniListItemGroupModifier impl = {
        .setListItemGroupHeader = OHOS::Ace::NG::SetListItemGroupHeader,
        .setListItemGroupHeaderContent = OHOS::Ace::NG::SetListItemGroupHeaderContent,
        .resetListItemGroupHeader = OHOS::Ace::NG::ResetListItemGroupHeader,
        .setListItemGroupFooter = OHOS::Ace::NG::SetListItemGroupFooter,
        .setListItemGroupFooterContent = OHOS::Ace::NG::SetListItemGroupFooterContent,
        .resetListItemGroupFooter = OHOS::Ace::NG::ResetListItemGroupFooter,
        .setListItemGroupStyle = OHOS::Ace::NG::SetListItemGroupStyle,
        .setListItemGroupSpace = OHOS::Ace::NG::SetListItemGroupSpace,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
