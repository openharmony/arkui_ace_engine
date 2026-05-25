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

#include "interfaces/native/node/node_model.h"
#include "ui/base/utils/utils.h"

#include "base/log/log_wrapper.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"

namespace OHOS::Ace {
namespace NG {
namespace {
constexpr int32_t DEFAULT_STICKY_STYLE = static_cast<int32_t>(StickyStyle::NONE);

RefPtr<UINode> ClaimHeaderFooterNode(ArkUINodeHandle edge)
{
    auto* rawNode = reinterpret_cast<UINode*>(edge);
    CHECK_NULL_RETURN(rawNode, nullptr);
    auto node = AceType::Claim(rawNode);
    if (!HeaderFooterUtils::GetHeaderFooterFrameNode(node)) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects invalid header / footer node");
        return nullptr;
    }
    return node;
}

void Create()
{
    LazyColumnLayoutModel::Create();
}

void SetSpace(ArkUINodeHandle node, const struct ArkUIResourceLength* space)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(space->unit);
    Dimension dim;
    if (unitEnum == DimensionUnit::CALC) {
        dim = CalcDimension(space->string, DimensionUnit::CALC);
    } else {
        dim = CalcDimension(space->value, unitEnum);
    }
    if (LessOrEqual(dim.Value(), 0.0)) {
        dim = 0.0_vp;
    }
    LazyColumnLayoutModel::SetSpace(frameNode, dim);
}

void ResetSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyColumnLayoutModel::SetSpace(frameNode, 0.0_vp);
}

void SetAlignItems(ArkUINodeHandle node, int32_t align)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyColumnLayoutModel::SetAlignItems(frameNode, static_cast<HorizontalAlign>(align));
}

void ResetAlignItems(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyColumnLayoutModel::SetAlignItems(frameNode, HorizontalAlign::CENTER);
}

void SetOnVisibleIndexesChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onVisibleIndexesChange = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(extraParam);
        LazyColumnLayoutModel::SetOnVisibleIndexesChange(frameNode, std::move(*onVisibleIndexesChange));
    } else {
        LazyColumnLayoutModel::SetOnVisibleIndexesChange(frameNode, nullptr);
    }
}

void ResetOnVisibleIndexesChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyColumnLayoutModel::SetOnVisibleIndexesChange(frameNode, nullptr);
}

void SetSticky(ArkUINodeHandle node, int32_t stickyStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (stickyStyle < static_cast<int32_t>(StickyStyle::NONE) ||
        stickyStyle > static_cast<int32_t>(StickyStyle::BOTH)) {
        stickyStyle = DEFAULT_STICKY_STYLE;
    }
    LazyColumnLayoutModel::SetSticky(frameNode, static_cast<StickyStyle>(stickyStyle));
}

void ResetSticky(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyColumnLayoutModel::SetSticky(frameNode, StickyStyle::NONE);
}

void SetHeader(ArkUINodeHandle node, ArkUINodeHandle header)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto headerNode = ClaimHeaderFooterNode(header);
    CHECK_NULL_VOID(headerNode);
    if (AceType::RawPtr(headerNode) == static_cast<UINode*>(frameNode)) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects itself as header node");
        return;
    }
    LazyColumnLayoutModel::SetHeader(frameNode, headerNode);
}

void ResetHeader(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyColumnLayoutModel::RemoveHeader(frameNode);
}

void SetFooter(ArkUINodeHandle node, ArkUINodeHandle footer)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto footerNode = ClaimHeaderFooterNode(footer);
    CHECK_NULL_VOID(footerNode);
    if (AceType::RawPtr(footerNode) == static_cast<UINode*>(frameNode)) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects itself as footer node");
        return;
    }
    LazyColumnLayoutModel::SetFooter(frameNode, footerNode);
}

void ResetFooter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyColumnLayoutModel::RemoveFooter(frameNode);
}
} // namespace
namespace NodeModifier {
const ArkUILazyColumnLayoutModifier* GetLazyColumnLayoutDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILazyColumnLayoutModifier modifier = {
        .create = Create,
        .setSpace = SetSpace,
        .resetSpace = ResetSpace,
        .setAlignItems = SetAlignItems,
        .resetAlignItems = ResetAlignItems,
        .setSticky = SetSticky,
        .resetSticky = ResetSticky,
        .setHeader = SetHeader,
        .resetHeader = ResetHeader,
        .setFooter = SetFooter,
        .resetFooter = ResetFooter,
        .setOnVisibleIndexesChange = SetOnVisibleIndexesChange,
        .resetOnVisibleIndexesChange = ResetOnVisibleIndexesChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace NG
} // namespace OHOS::Ace
