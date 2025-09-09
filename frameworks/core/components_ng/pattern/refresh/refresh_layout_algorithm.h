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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_LAYOUT_ALGORITHM_H

#include <string>
#include <utility>

#include "frameworks/core/components_ng/layout/box_layout_algorithm.h"
#include "frameworks/core/components_ng/layout/layout_wrapper.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RefreshLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(RefreshLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    RefreshLayoutAlgorithm();
    ~RefreshLayoutAlgorithm() override = default;
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetCustomBuilderIndex(int32_t index)
    {
        customBuilderIndex_ = index;
    }

    void SetCustomBuilderOffset(float offset)
    {
        customBuilderOffset_ = offset;
    }

    void SetScrollOffset(float offset)
    {
        scrollOffset_ = offset;
    }

    void SetBuilderMeasureBaseHeight(float builderBaseHeight)
    {
        builderBaseHeight_ = builderBaseHeight;
    }

    void SetIsHighVersion(bool value)
    {
        isHighVersion_ = value;
    }

private:
    bool HasCustomBuilderIndex() const
    {
        return customBuilderIndex_.has_value();
    }
    OptionalSizeF CalculateBuilderSize(
        RefPtr<LayoutWrapper> childLayoutWrapper, LayoutConstraintF& constraint, float customBaseHeight);
    void PerformLayout(LayoutWrapper* layoutWrapper);
    void UpdateChildPosition(LayoutWrapper* layoutWrapper, int32_t index, OffsetF& paddingOffsetChild);

    float builderBaseHeight_ = 0.0f;
    float customBuilderOffset_ = 0.0f;
    float scrollOffset_ = 0.0f;
    bool isHighVersion_ = true;
    std::optional<int32_t> customBuilderIndex_;
    ACE_DISALLOW_COPY_AND_MOVE(RefreshLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_LAYOUT_ALGORITHM_H
