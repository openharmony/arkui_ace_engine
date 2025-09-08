/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_LAYOUT_ALGORITHM_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ButtonLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(ButtonLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    ButtonLayoutAlgorithm() = default;

    ~ButtonLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void OnReset() override {}

private:
    void HandleAdaptiveText(LayoutWrapper* layoutWrapper, LayoutConstraintF& layoutConstraint);
    void PerformMeasureSelf(LayoutWrapper* layoutWrapper);
    bool NeedAgingMeasure(LayoutWrapper* layoutWrapper);
    static bool IsAging(LayoutWrapper* layoutWrapper);
    static void HandleChildLayoutConstraint(LayoutWrapper* layoutWrapper, LayoutConstraintF& layoutConstraint);
    static std::optional<SizeF> HandleLabelCircleButtonConstraint(LayoutWrapper* layoutWrapper);
    static void HandleBorderRadius(LayoutWrapper* layoutWrapper);
    static void HandleLabelCircleButtonFrameSize(
        const LayoutConstraintF& layoutConstraint, SizeF& frameSize, const float& defaultHeight);
    static void MeasureCircleButton(LayoutWrapper* layoutWrapper);
    static Dimension GetFirstValidRadius(const BorderRadiusProperty& borderRadius);
    static float GetDefaultHeight(LayoutWrapper* layoutWrapper);
    static float GetDefaultBorderRadius(LayoutWrapper* layoutWrapper);
    bool ProcessLayoutPolicyIsNotNoMatch(std::optional<NG::LayoutPolicyProperty> layoutPolicy);
    SizeF childSize_;

    ACE_DISALLOW_COPY_AND_MOVE(ButtonLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_LAYOUT_ALGORITHM_H
