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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_BOX_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_BOX_LAYOUT_ALGORITHM_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace::NG {
// BoxLayout is the class for box type measure, layout.
class ACE_FORCE_EXPORT BoxLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(BoxLayoutAlgorithm, LayoutAlgorithm)
public:
    BoxLayoutAlgorithm() = default;
    ~BoxLayoutAlgorithm() override = default;

    // override measureSelf and measureChildren.
    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    // Called to perform measure current render node.
    static void PerformMeasureSelf(LayoutWrapper* layoutWrapper);

    // Called to perform layout render node.
    static void PerformLayout(LayoutWrapper* layoutWrapper);

    // Called to perform measure current render node.
    static void PerformMeasureSelfWithChildList(
        LayoutWrapper* layoutWrapper, const std::list<RefPtr<LayoutWrapper>>& childList);

    static std::optional<SizeF> PerformMeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);

    void MeasureAdaptiveLayoutChildren(LayoutWrapper* layoutWrapper, SizeF& frameSize);
    
    static Alignment MapLocalizedToAlignment(std::string localizedAlignment);

protected:
    std::list<RefPtr<LayoutWrapper>> layoutPolicyChildren_;

private:
    ACE_DISALLOW_COPY_AND_MOVE(BoxLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_BOX_LAYOUT_ALGORITHM_H
