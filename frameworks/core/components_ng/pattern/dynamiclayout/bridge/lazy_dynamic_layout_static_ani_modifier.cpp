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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_static.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/interfaces/ani/ani_api.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"

namespace OHOS::Ace::NG {

ArkUINodeHandle LazyDynamicLayoutConstructImpl(ArkUI_Int32 id, ArkUI_Int32 flags)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

bool SetLazyDynamicLayoutOptionsImpl(ArkUINodeHandle node, const ArkUILazyCustomLayoutAlgorithm& algorithm)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto customParams = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    customParams->SetAxis(static_cast<Axis>(algorithm.axis));
    if (algorithm.onMeasureFunc) {
        auto onMeasureFunc = [fn = algorithm.onMeasureFunc](LayoutWrapper* layoutWrapper) {
            CHECK_NULL_VOID(layoutWrapper);
            const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
            CHECK_NULL_VOID(layoutProperty);
            auto layoutConstraint = layoutProperty->GetLayoutConstraint().value_or(
                OHOS::Ace::NG::LayoutConstraintF());
            auto axis = layoutConstraint.viewPosRef.has_value() ?
                layoutConstraint.viewPosRef.value().axis : Axis::VERTICAL;
            auto geometry = layoutWrapper->GetGeometryNode();
            CHECK_NULL_VOID(geometry);
            auto mainSize = geometry->GetPaddingSize().MainSize(static_cast<Axis>(axis));
            fn(layoutConstraint, mainSize);
        };
        customParams->SetOnMeasureSize(std::move(onMeasureFunc));
    }
    if (algorithm.onPlaceChildrenFunc) {
        auto onPlaceChildrenFunc = [fn = algorithm.onPlaceChildrenFunc](LayoutWrapper* layoutWrapper) {
            CHECK_NULL_VOID(layoutWrapper);
            auto rect = layoutWrapper->GetGeometryNode()->GetFrameRect();
            OHOS::Ace::NG::OffsetF offset(rect.GetX(), rect.GetY());
            fn(offset);
        };
        customParams->SetOnPlaceChildren(std::move(onPlaceChildrenFunc));
    }
    LazyDynamicLayoutModelStatic::SetParams(frameNode, customParams);
    return true;
}

bool SetOnVisibleIndexesChangeImpl(ArkUINodeHandle node, std::function<void(const std::vector<int32_t>&)>&& callback)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    if (callback) {
        LazyDynamicLayoutModelStatic::SetOnVisibleIndexesChange(frameNode, std::move(callback));
    } else {
        LazyDynamicLayoutModelStatic::SetOnVisibleIndexesChange(frameNode, nullptr);
    }
    return true;
}

bool SetAdjustedOffsetImpl(ArkUINodeHandle node, ani_float offset)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    LazyDynamicLayoutModelStatic::SetAdjustedOffset(frameNode, static_cast<float>(offset));
    return true;
}

bool SetInActiveChildrenImpl(ArkUINodeHandle node, const std::vector<int32_t>& children)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    LazyDynamicLayoutModelStatic::SetInActiveChildren(frameNode, children);
    return true;
}

const ArkUIAniLazyDynamicLayoutModifier* GetArkUIAniLazyDynamicLayoutModifier()
{
    static const ArkUIAniLazyDynamicLayoutModifier impl = {
        .construct = OHOS::Ace::NG::LazyDynamicLayoutConstructImpl,
        .setLazyDynamicLayoutOptions = OHOS::Ace::NG::SetLazyDynamicLayoutOptionsImpl,
        .setOnVisibleIndexesChange = OHOS::Ace::NG::SetOnVisibleIndexesChangeImpl,
        .setAdjustedOffset = OHOS::Ace::NG::SetAdjustedOffsetImpl,
        .setInActiveChildren = OHOS::Ace::NG::SetInActiveChildrenImpl,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG