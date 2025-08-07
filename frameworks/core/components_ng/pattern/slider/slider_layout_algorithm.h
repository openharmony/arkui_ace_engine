/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_model.h"

namespace OHOS::Ace::NG {

// SliderLayoutAlgorithm acts as the underlying slider layout.
class ACE_EXPORT SliderLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SliderLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    explicit SliderLayoutAlgorithm() = default;
    ~SliderLayoutAlgorithm() override = default;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void CalculateBlockOffset(
        LayoutWrapper* layoutWrapper, const RectF& contentRect, float selectOffset, Axis axis, bool reverse);
    void CalculatePrefixOffset(
        LayoutWrapper* layoutWrapper, const RectF& contentRect, float borderBlank, Axis axis, bool reverse);
    void CalculateSuffixOffset(
        LayoutWrapper* layoutWrapper, const RectF& contentRect, float borderBlank, Axis axis, bool reverse);
    SizeF CalculateHotSize(LayoutWrapper* layoutWrapper, const SizeF& blockSize, float themeBlockHotSize);
    void GetStyleThemeValue(LayoutWrapper* layoutWrapper, Dimension& themeTrackThickness, Dimension& themeBlockSize,
        Dimension& hotBlockShadowWidth, Dimension& themeBlockHotSize);
    float CalculateSliderWidth(
        float width, float height, Axis direction, const Dimension& hotBlockShadowWidth, SliderModel::SliderMode mode);
    float CalculateSliderLength(float width, float height, Axis direction, SliderModel::SliderMode mode, bool Ends);
    void SetChildConstraint(RefPtr<LayoutWrapper> child, float maxWidth, float maxHeight);
    std::optional<NG::LayoutPolicyProperty> GetLayoutPolicy(LayoutWrapper* layoutWrapper);
    
private:
    float trackThickness_ = 0.0f;
    SizeF blockSize_;
    SizeF blockHotSize_;
    float maxWidth = 0.0f;
    float maxHeight = 0.0f;
    float langRatio = 0.1;
    float shortRatio = 0.7;

    ACE_DISALLOW_COPY_AND_MOVE(SliderLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_LAYOUT_ALGORITHM_H
