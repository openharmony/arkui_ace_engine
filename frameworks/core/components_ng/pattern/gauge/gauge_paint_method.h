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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_METHOD_H

#include "core/components_ng/pattern/gauge/gauge_modifier.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT GaugePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(GaugePaintMethod, NodePaintMethod)
public:
    GaugePaintMethod() = default;
    ~GaugePaintMethod() override = default;

    GaugePaintMethod(
        const WeakPtr<OHOS::Ace::NG::Pattern>& pattern, const RefPtr<GaugeModifier>& gaugeModifier)
        : pattern_(pattern), gaugeModifier_(gaugeModifier)
    {}

    void UpdateForegroundModifier(PaintWrapper* paintWrapper) override;
    RefPtr<Modifier> GetForegroundModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(gaugeModifier_, nullptr);
        return gaugeModifier_;
    }

private:
    WeakPtr<Pattern> pattern_;
    RefPtr<GaugeModifier> gaugeModifier_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_METHOD_H

