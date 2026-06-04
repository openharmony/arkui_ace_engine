/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <memory>
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
void CreateDynamicLayout(void* params, ArkUI_Int32 type)
{
    static DynamicLayoutModelNG model;
    auto algorithmParams = AceType::Claim(reinterpret_cast<AlgorithmParamBase*>(params));
    model.Create(algorithmParams, static_cast<DynamicLayoutType>(type));
}

void CreateLazyDynamicLayout(void* params, ArkUI_Int32 type)
{
    static LazyDynamicLayoutModelNG model;
    auto lazyCustomParams = AceType::Claim(reinterpret_cast<LazyCustomLayoutAlgorithmParam*>(params));
    model.Create(lazyCustomParams);
}

void SetOnVisibleIndexesChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        std::unique_ptr<OnVisibleIndexesChangeEvent> onVisibleIndexesChange(
            reinterpret_cast<OnVisibleIndexesChangeEvent*>(extraParam));
        LazyDynamicLayoutModelNG::SetOnVisibleIndexesChange(frameNode, std::move(*onVisibleIndexesChange));
    } else {
        LazyDynamicLayoutModelNG::SetOnVisibleIndexesChange(frameNode, nullptr);
    }
}

void ResetOnVisibleIndexesChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyDynamicLayoutModelNG::SetOnVisibleIndexesChange(frameNode, nullptr);
}

void SetAdjustedOffset(ArkUINodeHandle node, ArkUI_Float32 adjustedOffset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LazyDynamicLayoutModelNG::SetAdjustedOffset(frameNode, adjustedOffset);
}

void SetInActiveChildren(ArkUINodeHandle node, const ArkUI_Int32* children, ArkUI_Uint32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<int32_t> inActiveChildren;
    if (children && size > 0) {
        inActiveChildren.assign(children, children + size);
    }
    LazyDynamicLayoutModelNG::SetInActiveChildren(frameNode, inActiveChildren);
}

namespace NodeModifier {
const ArkUIDynamicLayoutModifier* GetDynamicLayoutDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIDynamicLayoutModifier modifier = {
        .createDynamicLayout = CreateDynamicLayout,
        .createLazyDynamicLayout = CreateLazyDynamicLayout,
        .setOnVisibleIndexesChange = SetOnVisibleIndexesChange,
        .resetOnVisibleIndexesChange = ResetOnVisibleIndexesChange,
        .setAdjustedOffset = SetAdjustedOffset,
        .setInActiveChildren = SetInActiveChildren,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}
} // namespace NodeModifier
}