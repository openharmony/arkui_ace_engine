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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_LAYOUT_ALGORITHM_H

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LinearSplitLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(LinearSplitLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    explicit LinearSplitLayoutAlgorithm(SplitType splitType, std::vector<float> childrenDragPos, bool isOverParent)
        : splitType_(splitType), childrenDragPos_(std::move(childrenDragPos)), isOverParent_(isOverParent) {};
    ~LinearSplitLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    const std::vector<OffsetF>& GetChildrenOffset() const
    {
        return childrenOffset_;
    }

    float GetSplitLength() const
    {
        return splitLength_;
    }

    std::vector<Rect> GetSplitRects() const
    {
        return splitRects_;
    }

    bool GetIsOverParent() const
    {
        return isOverParent_;
    }

    [[nodiscard]] std::vector<float> GetChildrenDragPos() const
    {
        return childrenDragPos_;
    }

    [[nodiscard]] std::vector<float> GetChildrenConstrains() const
    {
        return childrenConstrains_;
    }

private:
    std::pair<SizeF, SizeF> MeasureChildren(LayoutWrapper* layoutWrapper);
    LayoutConstraintF GetChildConstrain(LayoutWrapper* layoutWrapper, LayoutConstraintF childConstrain,
        const int32_t index);
    void LayoutRowSplit(LayoutWrapper* layoutWrapper, float childOffsetMain, float childOffsetCross);
    void LayoutColumnSplit(LayoutWrapper* layoutWrapper, float childOffsetMain, float childOffsetCross);
    void ColumnSplitChildConstrain(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& item,
        const int32_t index);
    static std::pair<float, float> GetDividerMargin(LayoutWrapper* layoutWrapper);

    SplitType splitType_;
    std::set<RefPtr<LayoutWrapper>> displayNodes_;
    std::vector<OffsetF> childrenOffset_;
    std::vector<Rect> splitRects_;
    std::vector<float> childrenDragPos_;
    std::vector<float> childrenConstrains_;
    float splitLength_ = 0.0f;
    bool isOverParent_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LinearSplitLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_LAYOUT_ALGORITHM_H