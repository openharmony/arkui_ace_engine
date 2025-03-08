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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H

#include <utility>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/slider/slider_content_modifier.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_tip_modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paragraph.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SliderPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SliderPaintMethod, NodePaintMethod)

public:
    struct TipParameters {
        bool isDrawTip_ = false;
        OffsetF bubbleVertex_;
        OffsetF sliderGlobalOffset_;
    };
    explicit SliderPaintMethod(const RefPtr<SliderContentModifier>& sliderContentModifier,
        const SliderContentModifier::Parameters& parameters, float sliderLength, float borderBlank,
        const RefPtr<SliderTipModifier>& sliderTipModifier, const TipParameters& tipParameters,
        TextDirection textDirection)
        : sliderContentModifier_(sliderContentModifier), parameters_(parameters), sliderTipModifier_(sliderTipModifier),
          tipParameters_(tipParameters), textDirection_(textDirection)
    {}
    ~SliderPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(sliderContentModifier_, nullptr);
        return sliderContentModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(sliderTipModifier_, nullptr);
        return sliderTipModifier_;
    }

    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

private:
    void UpdateBorderRadius(RefPtr<SliderPaintProperty>& paintProperty);
    void SetAttrParameters();
    RefPtr<SliderContentModifier> sliderContentModifier_;
    SliderContentModifier::Parameters parameters_;

    RefPtr<SliderTipModifier> sliderTipModifier_;
    TipParameters tipParameters_;
    TextDirection textDirection_;
    ACE_DISALLOW_COPY_AND_MOVE(SliderPaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H
