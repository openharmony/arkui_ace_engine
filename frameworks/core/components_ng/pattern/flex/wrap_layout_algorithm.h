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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WRAP_WRAP_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WRAP_WRAP_LAYOUT_ALGORITHM_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_styles.h"

namespace OHOS::Ace::NG {

struct ContentInfo {
    ContentInfo(double main, double cross, int32_t total, const std::list<RefPtr<LayoutWrapper>>& nodeList)
        : mainLength(main), crossLength(cross), count(total), itemList(nodeList)
    {}

    float mainLength = 0.0;
    float crossLength = 0.0;
    int32_t count = 0;
    std::list<RefPtr<LayoutWrapper>> itemList;
    float maxBaselineDistance = 0.0;
};

class ACE_EXPORT WrapLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(WrapLayoutAlgorithm, LayoutAlgorithm);

public:
    WrapLayoutAlgorithm() = default;
    explicit WrapLayoutAlgorithm(bool stretch) : isDialogStretch_(stretch) {};
    ~WrapLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void PerformLayoutInitialize(const RefPtr<LayoutProperty>& layoutProp);
    void HandleDialogStretch();
    SizeF GetLeftSize(float crossLength, float mainLeftLength, float crossLeftLength);
    void LayoutWholeWrap(LayoutWrapper* layoutWrapper);
    float GetMainItemLength(const RefPtr<GeometryNode>& item) const;
    float GetCrossItemLength(const RefPtr<GeometryNode>& item) const;
    OffsetF GetContentOffset(float totalCrossLength) const;
    void TraverseContent(const OffsetF& startPosition, const OffsetF& betweenPosition) const;
    OffsetF GetItemMainOffset(float mainSpace) const;
    void PositionedItem(
        float betweenSpace, const ContentInfo& content, const OffsetF& position, float crossSpace) const;

    void HandleStartAlignment(const RefPtr<GeometryNode>& item, const OffsetF& position, float betweenSpace,
        OffsetF& itemPositionOffset) const;
    void HandleCenterAlignment(float totalCrossSpace, const RefPtr<GeometryNode>& item, const OffsetF& position,
        float betweenSpace, OffsetF& itemPositionOffset) const;
    void HandleEndAlignment(float totalCrossSpace, const RefPtr<GeometryNode>& item, const OffsetF& position,
        float betweenSpace, OffsetF& itemPositionOffset) const;
    void HandleBaselineAlignment(float totalCrossSpace, const RefPtr<GeometryNode>& item, const OffsetF& position,
        float betweenSpace, OffsetF& itemPositionOffset) const;
    void PlaceItemAndLog(const RefPtr<GeometryNode>& node, const OffsetF& position, const std::string& align) const;

    WrapDirection direction_ = WrapDirection::VERTICAL;
    WrapAlignment alignment_ = WrapAlignment::START;
    WrapAlignment mainAlignment_ = WrapAlignment::START;
    WrapAlignment crossAlignment_ = WrapAlignment::START;

    bool isDialogStretch_ = false;
    float totalMainLength_ = 0.0f;
    float totalCrossLength_ = 0.0f;
    Dimension spacing_;
    Dimension contentSpace_;

    // Should be clear after Layout.
    std::list<ContentInfo> contentList_;

    float mainLengthLimit_ = 0.0;
    float crossLengthLimit_ = 0.0;
    bool isLeftToRight_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(WrapLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WRAP_WRAP_LAYOUT_ALGORITHM_H
