/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_LAYOUT_ALGORITHM_H

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/layout_policy_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SwitchLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SwitchLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    SwitchLayoutAlgorithm() = default;

    ~SwitchLayoutAlgorithm() override = default;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void OnReset() override {}

    float GetHeight() const
    {
        return height_;
    }

    float GetWidth() const
    {
        return width_;
    }

    void LayoutPolicyIsMatchParent(const LayoutConstraintF& contentConstraint,
        std::optional<NG::LayoutPolicyProperty> layoutPolicy, float& frameWidth, float& frameHeight);

    void LayoutPolicyIsFixAtIdelSize(const LayoutConstraintF& contentConstraint,
        std::optional<NG::LayoutPolicyProperty> layoutPolicy, float& frameWidth, float& frameHeight);

    void LayoutPolicyIsWrapContent(const LayoutConstraintF& contentConstraint,
        std::optional<NG::LayoutPolicyProperty> layoutPolicy, float& frameWidth, float& frameHeight);

private:
    void CalcHeightAndWidth(
        const RefPtr<FrameNode>& host, float& height, float& width, float frameHeight, float frameWidth);

    ACE_DISALLOW_COPY_AND_MOVE(SwitchLayoutAlgorithm);
    float width_ = 0.0f;
    float height_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_LAYOUT_ALGORITHM_H
