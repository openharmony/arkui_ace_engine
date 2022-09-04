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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_styles.h"

namespace OHOS::Ace::NG {

//struct FlexMeasureProperty {
//    SizeF realSize;
//    float crossSize = 0.0;
//    float allocatedSize = 0.0;
//    FlexDirection direction;
//    std::list<RefPtr<LayoutWrapper>> relativeNodes;
//    std::list<RefPtr<LayoutWrapper>> weightNodes;
//    std::set<RefPtr<LayoutWrapper>> infinityLayoutNodes;
//    std::map<int32_t, std::list<RefPtr<LayoutWrapper>>> magicNodes;
//    std::map<int32_t, float> magicNodeWeights;
//    float totalFlexWeight = 0;
//    int32_t maxDisplayPriority = 0;
//    FlexLayoutMode layoutMode = FlexLayoutMode::FLEX_ITEM_MODE;
//    float space = 0.0;
//
//};

struct MagicLayoutNode {
    LayoutConstraintF layoutConstraint;
    RefPtr<LayoutWrapper> layoutWrapper;
};


struct BaselineProperties {
    float maxBaselineDistance = 0.0f;
    float maxDistanceAboveBaseline = 0.0f;
    float maxDistanceBelowBaseline = 0.0f;
};

class ACE_EXPORT FlexLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(FlexLayoutAlgorithm, LayoutAlgorithm);

public:
    FlexLayoutAlgorithm() = default;
    ~FlexLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void InitFlexProperties(LayoutWrapper* layoutWrapper);
    void TravelChildrenFlexProps(LayoutWrapper* layoutWrapper);
    void MeasureInWeightMode(LayoutWrapper* layoutWrapper);
    void MeasureInIndexMode(LayoutWrapper* layoutWrapper);
    void MeasureInItemMode(LayoutWrapper* layoutWrapper);
    void MeasureMagicNodes(LayoutWrapper* layoutWrapper, BaselineProperties& baselineProperties);
    void ResizeByItem(const RefPtr<LayoutWrapper>& layoutWrapper, float& allocatedSize);
    float GetMainSize(const RefPtr<LayoutWrapper>& layoutWrapper) const;
    float GetMainSize(const SizeF& size, FlexDirection direction) const;
    float GetCrossSize(const RefPtr<LayoutWrapper>& layoutWrapper) const;
    float GetCrossSize(const SizeF& size, FlexDirection direction) const;
    void RelayoutForStretchMagicNode();
    void CheckSizeValidity(const RefPtr<LayoutWrapper>& layoutWrapper);
    void CheckBaselineProperties(const RefPtr<LayoutWrapper>& layoutWrapper, BaselineProperties& baselineProperties);
    void CalculateSpace(float remainSpace, float& frontSpace, float& betweenSpace) const;
    void PlaceChildren(LayoutWrapper* layoutWrapper, float frontSpace, float betweenSpace, const BaselineProperties& baselineProperties);
    bool IsStartTopLeft(FlexDirection direction, TextDirection textDirection) const;
    FlexAlign GetSelfAlign(const RefPtr<LayoutWrapper>&  layoutWrapper) const;
    TextDirection AdjustTextDirectionByDir() const;
    FlexDirection FlipAxis(FlexDirection direction) const;
    LayoutConstraintF MakeLayoutConstraint(float mainFlexExtent, const LayoutConstraintF& constraint, bool isStretch, bool supportZero = false) const;
    LayoutConstraintF MakeLayoutConstraintWithLimit(float minMainLimit, float maxMainLimit, bool isStretch) const;
    float GetStretchCrossLimit() const;
    OptionalSizeF GetCalcSize(float mainSize, float crossSize);

    OptionalSizeF realSize_;
    float mainSize_ = 0.0f;
    float crossSize_ = 0.0f;
    float selfIdealCrossSize_ = -1.0f;
    float allocatedSize_ = 0.0f;
    float space_ = 0.0f;
    bool isCrossInfinite_ = false;
    bool stretchToParent_ = false;
    float totalFlexWeight_ = 0.0f;
    int32_t maxDisplayPriority_ = 0;
    int32_t validSizeCount_ = 0;
    FlexAlign crossAxisAlign_ = FlexAlign::FLEX_START;
    FlexAlign mainAxisAlign_ = FlexAlign::FLEX_START;

    RefPtr<LayoutWrapper> layoutWrapper_;
    std::list<RefPtr<LayoutWrapper>> weightNodes_;
    std::set<RefPtr<LayoutWrapper>> infinityLayoutNodes_;
    std::map<int32_t, std::list<MagicLayoutNode>> magicNodes_;
    std::map<int32_t, float> magicNodeWeights_;
    FlexLayoutMode layoutMode_ = FlexLayoutMode::FLEX_ITEM_MODE;
    FlexDirection direction_ = FlexDirection::ROW;
    friend class LinearLayoutUtils;

    ACE_DISALLOW_COPY_AND_MOVE(FlexLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_ALGORITHM_H
