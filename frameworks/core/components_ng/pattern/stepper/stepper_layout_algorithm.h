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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT StepperLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(StepperLayoutAlgorithm, LayoutAlgorithm);

public:
    explicit StepperLayoutAlgorithm(bool layoutLeftButton) : layoutLeftButton_(layoutLeftButton) {};
    ~StepperLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void MeasureSwiper(LayoutWrapper* layoutWrapper, LayoutConstraintF swiperLayoutConstraint, float rightButtonHeight,
        float leftButtonHeight);
    void MeasureLeftButton(LayoutWrapper* layoutWrapper, LayoutConstraintF buttonLayoutConstraint);
    void MeasureRightButton(LayoutWrapper* layoutWrapper, LayoutConstraintF buttonLayoutConstraint);
    void MeasureText(
        const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& buttonLayoutConstraint, bool isLeft);
    static LayoutConstraintF CreateButtonLayoutConstraint(const LayoutConstraintF& childLayoutConstraint, bool isLeft);
    void LayoutSwiper(LayoutWrapper* layoutWrapper);
    void LayoutLeftButton(LayoutWrapper* layoutWrapper);
    void LayoutRightButton(LayoutWrapper* layoutWrapper);
    float CaluateButtonHeight(LayoutWrapper* layoutWrapper, bool isRight);
    void SuitAgeLayoutButton(
        LayoutWrapper* layoutWrapper, float rightButtonHeight, float leftButtonHeight, bool isRight);
    bool layoutLeftButton_ = true;
    bool isLoadingButton_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(StepperLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_ALGORITHM_H
