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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_ITEM_MEASURER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_LAYOUT_ITEM_MEASURER_H
#include <utility>

#include "base/geometry/axis.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
namespace OHOS::Ace::NG {
class FrameNode;
class Measurer : public AceType {
    DECLARE_ACE_TYPE(Measurer, AceType);

public:
    virtual float Measure(FrameNode* item, int32_t index, float crossLen) const = 0;
};

class FlowItemMeasurer : public Measurer {
    DECLARE_ACE_TYPE(FlowItemMeasurer, Measurer);

public:
    FlowItemMeasurer(std::function<float(int32_t)> getUserDefHeight, Axis axis, float containerMainLen,
        const RefPtr<WaterFlowLayoutProperty>& props)
        : getUserDefHeight_(std::move(getUserDefHeight)), axis_(axis), containerMainLen_(containerMainLen),
          props_(props)
    {}
    float Measure(FrameNode* item, int32_t index, float crossLen) const override;

private:
    const std::function<float(int32_t)> getUserDefHeight_;
    const Axis axis_;
    const float containerMainLen_;
    const RefPtr<WaterFlowLayoutProperty> props_;
};
} // namespace OHOS::Ace::NG
#endif
