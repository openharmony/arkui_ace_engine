/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/security_component/security_component_common.h"
#include "core/components_ng/pattern/security_component/security_component_layout_element.h"
#include "core/components_ng/pattern/security_component/security_component_layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SecurityComponentLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SecurityComponentLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    SecurityComponentLayoutAlgorithm() = default;
    ~SecurityComponentLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    RefPtr<LayoutWrapper> GetChildWrapper(LayoutWrapper* layoutWrapper, const std::string& tag);
    void UpdateChildPosition(LayoutWrapper* layoutWrapper, const std::string& tag,
        OffsetF& offset);
    void MeasureButton(LayoutWrapper* layoutWrapper,
        RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty);
    void UpdateHorizontalOffset(OffsetF& offsetIcon, OffsetF& offsetText);
    void UpdateVerticalOffset(OffsetF& offsetIcon, OffsetF& offsetText);
    void InitPadding(RefPtr<SecurityComponentLayoutProperty>& property);
    double ShrinkWidth(double diff);
    double EnlargeWidth(double diff);
    double ShrinkHeight(double diff);
    double EnlargeHeight(double diff);
    void AdaptWidth();
    void AdaptHeight();
    void MeasureIntegralSize();
    void UpdateCircleButtonConstraint();
    void FillBlank();

    double componentWidth_ = 0.0;
    double componentHeight_ = 0.0;
    IconLayoutElement icon_;
    TextLayoutElement text_;
    PaddingLayoutElement left_;
    PaddingLayoutElement top_;
    PaddingLayoutElement right_;
    PaddingLayoutElement bottom_;
    PaddingLayoutElement middle_;

    double idealWidth_ = 0.0;
    double idealHeight_ = 0.0;
    double minWidth_ = 0.0;
    double minHeight_ = 0.0;
    double maxWidth_ = 1000000.0; // Infinity
    double maxHeight_ = 1000000.0; // Infinity

    std::optional<LayoutConstraintF> constraint_;
    bool isNeedReadaptWidth_ = false;
    bool isVertical_ = false;
    bool isNobg_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(SecurityComponentLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LAYOUT_ALGORITHM_H
