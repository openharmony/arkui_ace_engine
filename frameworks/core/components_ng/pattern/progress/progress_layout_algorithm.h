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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_LAYOUT_ALGORITHM_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class PipelineContext;

// ProgressLayoutAlgorithm acts as the underlying progress layout.
class ACE_EXPORT ProgressLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(ProgressLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    ProgressLayoutAlgorithm();

    ~ProgressLayoutAlgorithm() override = default;
    
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    double GetMaxValue() const;
    double GetValue() const;
   // double GetCachedValue() const;
    Color GetColor() const;
    ProgressType GetType() const;
    double GetStrokeWidth() const;
    int32_t GetScaleCount() const;
    double GetScaleWidth() const;
    
    


private:

    double maxValue_;
    double value_;
  //  double cachedValue_;
    Color color_;
    ProgressType type_;
    int32_t scaleCount_;
    double strokeWidth_;
    double scaleWidth_;
    ACE_DISALLOW_COPY_AND_MOVE(ProgressLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_LAYOUT_ALGORITHM_H
