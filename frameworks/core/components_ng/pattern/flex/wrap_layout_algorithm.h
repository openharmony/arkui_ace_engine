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

#include <string>

#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_styles.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {

struct ContentInfo {
    ContentInfo(float main, float cross, int32_t total, const std::list<RefPtr<LayoutWrapper>>& nodeList)
        : mainLength(main), crossLength(cross), count(total), itemList(nodeList)
    {}

    float mainLength = 0.0f;
    float crossLength = 0.0f;
    int32_t count = 0;
    std::list<RefPtr<LayoutWrapper>> itemList;
    float spaceBetween = 0.0f;
    float maxBaselineDistance = 0.0f;

    std::string ToString() const
    {
        std::string result;
        result.append("main length: ");
        result.append(std::to_string(mainLength));
        result.append(", cross length: ");
        result.append(std::to_string(crossLength));
        result.append(", space between: ");
        result.append(std::to_string(spaceBetween));
        result.append(", child count ");
        result.append(std::to_string(count));
        result.append(", max baseline distance ");
        result.append(std::to_string(maxBaselineDistance));
        return result;
    }
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
    void LayoutWholeWrap(
        OffsetF& startPosition, OffsetF& spaceBetweenContentsOnCrossAxis, LayoutWrapper* layoutWrapper);
    void LayoutWholeColumnWrap(
        OffsetF& startPosition, OffsetF& spaceBetweenContentsOnCrossAxis, LayoutWrapper* layoutWrapper);
    void UpdateStartPositionByAlign(OffsetF& startPosition, float crossAxisRemainSpace,
        OffsetF& spaceBetweenContentsOnCrossAxis, int32_t contentNum);
    void TraverseColumnContent(const OffsetF& startPosition, const OffsetF& spaceBetweenContentsOnCrossAxis);
    void AddPaddingToStartPositionForColumn(OffsetF& startPosition) const;
    void LayoutColumnContent(const ContentInfo& content, const OffsetF& position);

    float GetItemMainAxisLength(const RefPtr<GeometryNode>& item) const;
    float GetItemCrossAxisLength(const RefPtr<GeometryNode>& item) const;
    float GetMainAxisLengthOfSize(const SizeF& size) const;
    float GetCrossAxisLengthOfSize(const SizeF& size) const;
    float GetMainAxisOffset(const OffsetF& offset) const;
    float GetCrossAxisOffset(const OffsetF& offset) const;
    SizeF GetMainAxisRemainSpace(float totalMainLength) const;
    SizeF GetCrossAxisRemainSpace(float totalCrossLength) const;

    void CalcItemMainAxisStartAndSpaceBetween(
        OffsetF& startPosition, OffsetF& spaceBetweenItemsOnMainAxis, const ContentInfo& content);
    float CalcItemCrossAxisOffset(
        const ContentInfo& content, const OffsetF& contentOffset, const RefPtr<GeometryNode>& node);

    void StretchItemsInContent(LayoutWrapper* layoutWrapper, const ContentInfo& content);
    void TraverseContent(const OffsetF& startPosition, const OffsetF& spaceBetweenContentsOnCrossAxis);
    OffsetF GetItemMainOffset(float mainSpace) const;
    void LayoutContent(const ContentInfo& content, const OffsetF& position);

    void AddExtraSpaceToStartPosition(OffsetF& startPosition, float extraSpace, bool onMainAxis) const;
    void AddPaddingToStartPosition(OffsetF& startPosition) const;
    void GetFlexItemProperties(const ContentInfo& content, FlexItemProperties& flexItemProperties);
    void CalcFlexGrowLayout(
        const RefPtr<LayoutWrapper>& itemWrapper, const FlexItemProperties& flexItemProperties, float remainSpace);

    void UpdatePercentSensitive(LayoutWrapper *layoutWrapper);
    WrapDirection direction_ = WrapDirection::VERTICAL;
    WrapAlignment alignment_ = WrapAlignment::START;
    WrapAlignment mainAlignment_ = WrapAlignment::START;
    WrapAlignment crossAlignment_ = WrapAlignment::START;
    TextDirection textDir_ = TextDirection::LTR;

    bool isHorizontal_ = true;
    bool isReverse_ = false;
    bool isColumnReverse_ = false;
    bool isRightDirection_ = false;
    bool isDialogStretch_ = false;
    bool isPixelRoundAfterMeasure_ = false;
    float totalMainLength_ = 0.0f;
    float totalCrossLength_ = 0.0f;
    Dimension spacing_;
    Dimension contentSpace_;
    SizeF constraintMaxSize_;
    PaddingPropertyF padding_;
    SizeF frameSize_;
    OffsetF frameOffset_;
    bool hasIdealWidth_ = false;
    bool hasIdealHeight_ = false;

    // Should be clear after Layout.
    std::list<ContentInfo> contentList_;

    float mainLengthLimit_ = 0.0f;
    float crossLengthLimit_ = 0.0f;
    float currentMainLength_ = 0.0f;
    std::list<RefPtr<LayoutWrapper>> outOfLayoutChildren_;

    ACE_DISALLOW_COPY_AND_MOVE(WrapLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WRAP_WRAP_LAYOUT_ALGORITHM_H
