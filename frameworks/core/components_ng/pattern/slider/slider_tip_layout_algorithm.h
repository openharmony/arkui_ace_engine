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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_TIP_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_TIP_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"

namespace OHOS::Ace::NG {

// SliderLayoutAlgorithm acts as the underlying slider layout.
class ACE_EXPORT SliderTipLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SliderTipLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    explicit SliderTipLayoutAlgorithm(const RefPtr<SliderPattern> sliderPattern) : sliderPattern_(sliderPattern) {}
    ~SliderTipLayoutAlgorithm() override = default;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void GetFrameOffset(RefPtr<FrameNode> host, float& xOffset, float& yOffset) const;
    RefPtr<SliderPattern> sliderPattern_;

    ACE_DISALLOW_COPY_AND_MOVE(SliderTipLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_TIP_LAYOUT_ALGORITHM_H
