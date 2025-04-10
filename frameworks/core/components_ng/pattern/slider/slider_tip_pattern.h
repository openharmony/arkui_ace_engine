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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_TIP_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_TIP_PATTERN_H

#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "base/geometry/offset.h"
#include "core/components_ng/pattern/slider/slider_tip_layout_algorithm.h"

namespace OHOS::Ace::NG {
class SliderTipPattern : public Pattern {
    DECLARE_ACE_TYPE(SliderTipPattern, Pattern);

public:
    SliderTipPattern() = default;
    explicit SliderTipPattern(const RefPtr<SliderPattern> sliderPattern) : sliderPattern_(sliderPattern) {}
    ~SliderTipPattern() override = default;
    RefPtr<SliderPattern> sliderPattern_;
    RefPtr<SliderTipModifier> sliderTipModifier_;
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SliderTipLayoutAlgorithm>(sliderPattern_);
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_TIP_PATTERN_H