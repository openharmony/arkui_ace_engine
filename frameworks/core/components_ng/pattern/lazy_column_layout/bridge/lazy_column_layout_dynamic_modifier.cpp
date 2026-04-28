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

#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"

namespace OHOS::Ace {
namespace NG {
namespace {
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
    LazyColumnLayoutModel::SetAlignItems(frameNode, HorizontalAlign::START);
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
        .setOnVisibleIndexesChange = SetOnVisibleIndexesChange,
        .resetOnVisibleIndexesChange = ResetOnVisibleIndexesChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace NG
} // namespace OHOS::Ace
