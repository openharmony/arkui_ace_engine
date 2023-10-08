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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIVIDER_DIVIDER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIVIDER_DIVIDER_PATTERN_H

#include "core/components_ng/pattern/divider/divider_layout_algorithm.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_modifier.h"
#include "core/components_ng/pattern/divider/divider_paint_method.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class DividerPattern : public Pattern {
    DECLARE_ACE_TYPE(DividerPattern, Pattern);

public:
    DividerPattern() = default;
    ~DividerPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!dividerModifier_) {
            dividerModifier_ = AceType::MakeRefPtr<DividerModifier>();
        }
        return MakeRefPtr<DividerPaintMethod>(
            constrainStrokeWidth_, dividerLength_, vertical_, strokeWidthLimitation_, dividerModifier_);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<DividerLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<DividerLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<DividerRenderProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false, FocusStyleType::OUTER_BORDER };
    }

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    float constrainStrokeWidth_ = 0;
    float dividerLength_ = 0;
    bool vertical_ = false;
    bool strokeWidthLimitation_ = true;
    RefPtr<DividerModifier> dividerModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(DividerPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIVIDER_DIVIDER_PATTERN_H
