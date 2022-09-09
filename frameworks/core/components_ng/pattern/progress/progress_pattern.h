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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_paint_method.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
// ProgressPattern is the base class for text render node to perform paint progress.
class ProgressPattern : public Pattern {
    DECLARE_ACE_TYPE(ProgressPattern, Pattern);

public:
    ProgressPattern() = default;
    ~ProgressPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<ProgressPaintMethod>(
            maxValue_, value_, color_, progressType_, strokeWidth_, scaleWidth_, scaleCount_);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ProgressLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ProgressLayoutAlgorithm>();
    }

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void OnAttachToFrameNode() override;

    double maxValue_;
    double value_;
    Color color_;
    double strokeWidth_;
    double scaleWidth_;
    int32_t scaleCount_;
    ProgressType progressType_;

    ACE_DISALLOW_COPY_AND_MOVE(ProgressPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H
