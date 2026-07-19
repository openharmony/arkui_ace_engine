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
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_pattern.h"

#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model_static.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/lazy_grid_layout/bridge/lazy_grid_layout_custom_modifier.h"

namespace OHOS::Ace::NG {
namespace {
const std::string DEFAULT_COLUMNS_TEMPLATE = "1fr";
constexpr Dimension DEFAULT_COLUMNS_GAP = 0.0_fp;
constexpr Dimension DEFAULT_ROWS_GAP = 0.0_fp;
constexpr int32_t STICKY_STYLE_NONE = 0;
constexpr int32_t STICKY_STYLE_BOTH = 3;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
}

void Create()
{
    LazyVGridLayoutModel::Create();
}

void SetLazyGridLayoutColumnsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(columnsGap->unit);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(columnsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(columnsGap->value, unitEnum);
    }
    if (LessOrEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    LazyGridLayoutModel::SetColumnGap(frameNode, gap);
}

void ResetLazyGridLayoutColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModel::SetColumnGap(frameNode, DEFAULT_COLUMNS_GAP);
}

void SetLazyGridLayoutRowsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(rowsGap->unit);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(rowsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(rowsGap->value, unitEnum);
    }
    if (LessOrEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    LazyGridLayoutModel::SetRowGap(frameNode, gap);
}

void ResetLazyGridLayoutRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModel::SetRowGap(frameNode, DEFAULT_ROWS_GAP);
}

void SetLazyGridLayoutColumnsTemplate(ArkUINodeHandle node, const char* columnsTemplate)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LazyVGridLayoutModel::SetColumnsTemplate(frameNode, std::string(columnsTemplate));
}

void ResetLazyGridLayoutColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyVGridLayoutModel::SetColumnsTemplate(frameNode, DEFAULT_COLUMNS_TEMPLATE);
}

void SetLazyGridLayoutSticky(ArkUINodeHandle node, ArkUI_Int32 stickyStyle)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    int32_t normalized = stickyStyle;
    if (normalized < STICKY_STYLE_NONE || normalized > STICKY_STYLE_BOTH) {
        normalized = STICKY_STYLE_NONE;
    }
    LazyGridLayoutModelStatic::SetSticky(frameNode, std::optional<int32_t>(normalized));
}

void ResetLazyGridLayoutSticky(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModelStatic::SetSticky(frameNode, std::nullopt);
}

void SetLazyGridLayoutHeader(ArkUINodeHandle node, ArkUINodeHandle header)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* headerNode = reinterpret_cast<UINode*>(header);
    LazyGridLayoutModelStatic::SetHeader(frameNode, AceType::Claim<UINode>(headerNode));
}

void ResetLazyGridLayoutHeader(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModelStatic::RemoveHeader(frameNode);
}

void SetLazyGridLayoutFooter(ArkUINodeHandle node, ArkUINodeHandle footer)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* footerNode = reinterpret_cast<UINode*>(footer);
    LazyGridLayoutModelStatic::SetFooter(frameNode, AceType::Claim<UINode>(footerNode));
}

void ResetLazyGridLayoutFooter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModelStatic::RemoveFooter(frameNode);
}

void SetLazyGridLayoutOnVisibleIndexesChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // extraParam is a heap-owned unique_ptr<std::function<void(int32_t, int32_t)>> handed off from the bridge
    // (see bridge code that calls callback.release()). The Pattern takes ownership here.
    using CallbackPtr = std::unique_ptr<std::function<void(int32_t, int32_t)>>;
    CallbackPtr callback(static_cast<std::function<void(int32_t, int32_t)>*>(extraParam));
    if (!callback) {
        LazyGridLayoutModelStatic::SetOnVisibleIndexesChange(frameNode, nullptr);
        return;
    }
    LazyGridLayoutModelStatic::SetOnVisibleIndexesChange(frameNode, std::move(*callback));
}

void ResetLazyGridLayoutOnVisibleIndexesChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyGridLayoutModelStatic::SetOnVisibleIndexesChange(frameNode, nullptr);
}

void* GetLazyGridLayoutPattern()
{
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    pattern->IncRefCount();
    return AceType::RawPtr(pattern);
}

const ArkUILazyGridLayoutModifier* GetLazyGridLayoutDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILazyGridLayoutModifier modifier = {
        .create = Create,
        .setColumnsGap = SetLazyGridLayoutColumnsGap,
        .resetColumnsGap = ResetLazyGridLayoutColumnsGap,
        .setRowsGap = SetLazyGridLayoutRowsGap,
        .resetRowsGap = ResetLazyGridLayoutRowsGap,
        .setColumnsTemplate = SetLazyGridLayoutColumnsTemplate,
        .resetColumnsTemplate = ResetLazyGridLayoutColumnsTemplate,
        .setSticky = SetLazyGridLayoutSticky,
        .resetSticky = ResetLazyGridLayoutSticky,
        .setHeader = SetLazyGridLayoutHeader,
        .resetHeader = ResetLazyGridLayoutHeader,
        .setFooter = SetLazyGridLayoutFooter,
        .resetFooter = ResetLazyGridLayoutFooter,
        .setOnVisibleIndexesChange = SetLazyGridLayoutOnVisibleIndexesChange,
        .resetOnVisibleIndexesChange = ResetLazyGridLayoutOnVisibleIndexesChange
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUILazyGridLayoutCustomModifier* GetLazyGridLayoutCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILazyGridLayoutCustomModifier modifier = {
        .getLazyGridLayoutPattern = GetLazyGridLayoutPattern,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG
