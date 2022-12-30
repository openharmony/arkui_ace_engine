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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_TIP_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_TIP_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/slider/tip_layout_algorithm.h"
#include "core/components_ng/pattern/slider/tip_layout_property.h"
#include "core/components_ng/pattern/slider/tip_paint_method.h"
#include "core/components_ng/pattern/slider/tip_paint_property.h"

namespace OHOS::Ace::NG {
class TipPattern : public Pattern {
    DECLARE_ACE_TYPE(TipPattern, Pattern);

public:
    TipPattern() = default;
    ~TipPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<TipPaintMethod>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TipLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TipLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<TipPaintProperty>();
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(TipPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_TIP_PATTERN_H
