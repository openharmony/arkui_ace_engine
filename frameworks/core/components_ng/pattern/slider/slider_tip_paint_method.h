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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_TIP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_TIP_H

#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SliderTipPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SliderTipPaintMethod, NodePaintMethod)
public:
    explicit SliderTipPaintMethod(const RefPtr<SliderPattern>& sliderPattern,
        const SliderPaintMethod::TipParameters& tipParameters,
        const RefPtr<SliderTipModifier>& sliderTipModifier, const SliderContentModifier::Parameters& parameters)
        : sliderPattern_(sliderPattern), tipParameters_(tipParameters), sliderTipModifier_(sliderTipModifier),
        parameters_(parameters)
    {}
    ~SliderTipPaintMethod() override = default;
    RefPtr<SliderPattern> sliderPattern_;
    SliderPaintMethod::TipParameters tipParameters_;
    RefPtr<SliderTipModifier> sliderTipModifier_;
    SliderContentModifier::Parameters parameters_;
    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(sliderTipModifier_, nullptr);
        return sliderTipModifier_;
    }
    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;
    ACE_DISALLOW_COPY_AND_MOVE(SliderTipPaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_TIP_H