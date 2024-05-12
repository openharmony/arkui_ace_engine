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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PAINT_METHOD_H

#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/patternlock/patternlock_modifier.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT PatternLockPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(PatternLockPaintMethod, NodePaintMethod)

public:
    PatternLockPaintMethod(const OffsetF& cellCenter, bool isMoveEventValid,
        const std::vector<PatternLockCell>& choosePoint, const RefPtr<PatternLockModifier>& patternlockModifier)
        : cellCenter_(cellCenter), isMoveEventValid_(isMoveEventValid), choosePoint_(choosePoint),
          patternlockModifier_(patternlockModifier)
    {}

    ~PatternLockPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(patternlockModifier_, nullptr);
        return patternlockModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

private:
    void GetThemeProp();

    float sideLength_ = 0.0f;
    float scaleActiveCircleRadius_ = 1.0f;
    float scaleBackgroundCircleRadius_ = 1.0f;
    float scaleWaveCircleRadiusStart_ = 1.0f;
    float scaleWaveCircleRadiusEnd_ = 1.0f;
    float hoverRadiusScale_ = 1.0f;

    Dimension circleRadius_;
    Color regularColor_;
    Color selectedColor_;
    Color activeColor_;
    Color pathColor_;
    Color wrongColor_;
    Color correctColor_;
    Color hoverColor_;
    Color activeCircleColor_;
    Dimension pathStrokeWidth_;
    Dimension activeCircleRadius_;
    Dimension backgroundCircleRadius_;

    OffsetF cellCenter_;
    bool isMoveEventValid_ = false;
    bool enableWaveEffect_ = true;
    std::vector<PatternLockCell> choosePoint_;
    RefPtr<PatternLockModifier> patternlockModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(PatternLockPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PAINT_METHOD_H
