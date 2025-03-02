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

#include "item_measurer.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"

namespace OHOS::Ace::NG {
float FlowItemMeasurer::Measure(FrameNode* item, int32_t index, float crossLen) const
{
    auto itemRefPtr = AceType::Claim(item);
    CHECK_NULL_RETURN(item && itemRefPtr, 0.0f);
    float userHeight = getUserDefHeight_ ? getUserDefHeight_(index) : -1.0f;
    if (NonNegative(userHeight)) {
        return userHeight;
    }
    item->Measure(
        WaterFlowLayoutUtils::CreateChildConstraint({ crossLen, containerMainLen_, axis_ }, props_, itemRefPtr));
    return item->GetGeometryNode()->GetMarginFrameSize().MainSize(axis_);
}

float ListItemMeasurer::Measure(FrameNode* item, int32_t index, float crossLen) const
{
    CHECK_NULL_RETURN(item, 0.0f);
    float userHeight = getUserDefHeight_ ? getUserDefHeight_(index) : -1.0f;
    if (NonNegative(userHeight)) {
        return userHeight;
    }
    item->Measure(childConstraint_);
    return item->GetGeometryNode()->GetMarginFrameSize().MainSize(axis_);
}

ListItemMeasurer::ListItemMeasurer(std::function<float(int32_t)> getUserDefHeight, Axis axis, const SizeF& viewport,
    const RefPtr<ListLayoutProperty>& props)
    : Measurer(axis), getUserDefHeight_(std::move(getUserDefHeight))
{
    childConstraint_ = props->CreateChildConstraint();

    childConstraint_.parentIdealSize = OptionalSize(viewport);
    childConstraint_.maxSize.SetMainSize(Infinity<float>(), axis);
    auto crossSize = viewport.CrossSize(axis);
    childConstraint_.maxSize.SetCrossSize(crossSize, axis);
    childConstraint_.percentReference.SetCrossSize(crossSize, axis);
}

RefPtr<Measurer> Measurer::Construct(const RefPtr<LayoutProperty>& props,
    std::function<float(int32_t)> getUserDefHeight, Axis axis, const SizeF& viewport)
{
    if (InstanceOf<WaterFlowLayoutProperty>(props)) {
        return MakeRefPtr<FlowItemMeasurer>(
            std::move(getUserDefHeight), axis, viewport.MainSize(axis), DynamicCast<WaterFlowLayoutProperty>(props));
    }
    if (InstanceOf<ListLayoutProperty>(props)) {
        return MakeRefPtr<ListItemMeasurer>(
            std::move(getUserDefHeight), axis, viewport, DynamicCast<ListLayoutProperty>(props));
    }
    if (InstanceOf<SwiperLayoutProperty>(props)) {
        return MakeRefPtr<SwiperItemMeasurer>(axis, viewport, DynamicCast<SwiperLayoutProperty>(props));
    }
    return nullptr;
}

SwiperItemMeasurer::SwiperItemMeasurer(Axis axis, const SizeF& viewport, const RefPtr<SwiperLayoutProperty>& props)
    : Measurer(axis)
{
    auto host = props->GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    childConstraint_ = SwiperUtils::CreateChildConstraint(props, OptionalSize(viewport), pattern->IsAutoFill());
}

float SwiperItemMeasurer::Measure(FrameNode* item, int32_t index, float crossLen) const
{
    CHECK_NULL_RETURN(item, 0.0f);
    item->Measure(childConstraint_);
    return item->GetGeometryNode()->GetMarginFrameSize().MainSize(axis_);
}
} // namespace OHOS::Ace::NG
