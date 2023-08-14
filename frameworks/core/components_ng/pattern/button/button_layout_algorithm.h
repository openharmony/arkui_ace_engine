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

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ButtonLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(ButtonLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    ButtonLayoutAlgorithm() = default;

    ~ButtonLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void OnReset() override {}

private:
    std::optional<SizeF> HandleLabelCircleButtonConstraint(LayoutWrapper* layoutWrapper);
    void HandleChildLayoutConstraint(LayoutWrapper* layoutWrapper, LayoutConstraintF& layoutConstraint);
    void HandleAdaptiveText(LayoutWrapper* layoutWrapper, LayoutConstraintF& layoutConstraint);
    void HandleBorderRadius(LayoutWrapper* layoutWrapper);
    void PerformMeasureSelf(LayoutWrapper* layoutWrapper);
    void HandleLabelCircleButtonFrameSize(const LayoutConstraintF& layoutConstraint, SizeF& frameSize);
    void MeasureCircleButton(LayoutWrapper* layoutWrapper);
    Dimension GetFirstValidRadius(const BorderRadiusProperty& borderRadius);

    SizeF childSize_;
    bool isNeedToSetDefaultHeight_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ButtonLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_LAYOUT_ALGORITHM_H
