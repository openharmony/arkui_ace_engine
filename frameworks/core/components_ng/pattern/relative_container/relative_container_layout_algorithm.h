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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <map>
#include <optional>

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

using AlignRulesItem = std::map<AlignDirection, AlignRule>;
using TwoAlignedValues = std::pair<std::optional<float>, std::optional<float>>;
using ChildIdealSize = TwoAlignedValues;
using GuidelineParams = std::pair<LineDirection, float>;
using BarrierParams = std::pair<BarrierDirection, std::vector<std::string>>;

class ACE_EXPORT RelativeContainerLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(RelativeContainerLayoutAlgorithm, LayoutAlgorithm);

public:
    RelativeContainerLayoutAlgorithm() = default;
    ~RelativeContainerLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    struct BarrierRect
    {
        float minLeft = Infinity<float>();
        float maxRight = 0.0f;
        float minTop = Infinity<float>();
        float maxBottom = 0.0f;
    };

    struct ChainParam
    {
        std::vector<std::string> ids;
        std::map<std::string, std::optional<float>> itemSize;
        AlignRule anchorHead;
        AlignRule anchorTail;
        ChainStyle chainStyle;
        BiasPair bias;
        bool isCalculated = false;
    };

private:
    void DetermineTopologicalOrder(LayoutWrapper* layoutWrapper);
    void MeasureSelf(LayoutWrapper* layoutWrapper);
    void CollectNodesById(LayoutWrapper* layoutWrapper);
    bool IsAlignRuleInChain(const AlignDirection& direction, const std::string& nodeName);
    void InsertToReliedOnMap(const std::string& anchorName, const std::string& nodeName);
    void GetDependencyRelationship();
    void GetDependencyRelationshipInChain(const std::string& anchor, const std::string& nodeName);
    void GetDependencyRelationshipInBarrier();
    void CalcHorizontalGuideline(std::optional<CalcSize>& selfIdealSize, const GuidelineInfo& guidelineInfo);
    void CalcVerticalGuideline(std::optional<CalcSize>& selfIdealSize, const GuidelineInfo& guidelineInfo);
    void CalcGuideline(LayoutWrapper* layoutWrapper);
    void CalcBarrier(LayoutWrapper* layoutWrapper);
    bool IsGuideline(const std::string& id);
    bool IsBarrier(const std::string& id);
    BarrierRect GetBarrierRectByReferencedIds(const std::vector<std::string>& referencedIds);
    void MeasureBarrier(const std::string& barrierName);
    void CheckNodeInHorizontalChain(std::string& currentNode, std::string& nextNode,
        AlignRulesItem& currentAlignRules, std::vector<std::string>& chainNodes, AlignRule& rightAnchor);
    void CheckHorizontalChain(const RefPtr<LayoutWrapper>& childWrapper);
    void CheckNodeInVerticalChain(std::string& currentNode, std::string& nextNode, AlignRulesItem& currentAlignRules,
        std::vector<std::string>& chainNodes, AlignRule& bottomAnchor);
    void CheckVerticalChain(const RefPtr<LayoutWrapper>& childWrapper);
    void CheckChain(LayoutWrapper* layoutWrapper);
    void RecordSizeInChain(const std::string& nodeName);
    bool IsNodeInHorizontalChain(const std::string& nodeName, std::string& chainName);
    bool IsNodeInVerticalChain(const std::string& nodeName, std::string& chainName);
    float GetHorizontalAnchorValueByAlignRule(AlignRule& alignRule);
    float GetVerticalAnchorValueByAlignRule(AlignRule& alignRule);
    std::pair<float, float> CalcOffsetInChainGetStart(const float& anchorDistance, const float& contentSize,
        const ChainParam& chainParam, LineDirection direction);
    bool CalcOffsetInChain(const std::string& chainName, LineDirection direction);
    void PreTopologicalLoopDetectionGetAnchorSet(
        const std::string& nodeName, const AlignRulesItem& alignRulesItem, std::set<std::string>& anchorSet);
    bool PreTopologicalLoopDetection();
    void TopologicalSort(std::list<std::string>& renderList);
    void CalcSizeParam(LayoutWrapper* layoutWrapper, const std::string& nodeName);
    void CalcOffsetParam(LayoutWrapper* layoutWrapper, const std::string& nodeName);
    void CalcHorizontalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
        LayoutWrapper* layoutWrapper, const std::string& nodeName);
    void CalcVerticalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
        LayoutWrapper* layoutWrapper, const std::string& nodeName);
    float CalcHorizontalOffsetAlignLeft(const HorizontalAlign& alignRule, float& anchorWidth);
    float CalcHorizontalOffsetAlignMiddle(const HorizontalAlign& alignRule, float& anchorWidth, float& flexItemWidth);
    float CalcHorizontalOffsetAlignRight(const HorizontalAlign& alignRule, float& anchorWidth, float& flexItemWidth);
    float CalcHorizontalOffset(
        AlignDirection alignDirection, const AlignRule& alignRule, float containerWidth, const std::string& nodeName);
    float CalcVerticalOffsetAlignTop(const VerticalAlign& alignRule, float& anchorHeight);
    float CalcVerticalOffsetAlignCenter(const VerticalAlign& alignRule, float& anchorHeight, float& flexItemHeight);
    float CalcVerticalOffsetAlignBottom(const VerticalAlign& alignRule, float& anchorHeight, float& flexItemHeight);
    float CalcVerticalOffset(
        AlignDirection alignDirection, const AlignRule& alignRule, float containerHeight, const std::string& nodeName);

    bool IsValidBias(float bias);
    void CalcBiasTowDirection(std::pair<TwoAlignedValues, TwoAlignedValues>& alignedValuesOnTwoDirections,
        ChildIdealSize& childIdealSize, BiasPair& biasPair, float& horizontalOffset, float& verticalOffset);
    OffsetF CalcBias(const std::string& nodeName);

    std::pair<TwoAlignedValues, TwoAlignedValues> GetFirstTwoAlignValues(const RefPtr<LayoutWrapper>& childWrapper,
        const std::unique_ptr<FlexItemProperty>& flexItemProperty, const ChildIdealSize& childIdealSize);

    float GetVerticalAlignTopValue(std::string& anchor, std::optional<float>& marginTop);
    float GetVerticalAlignCenterValue(std::string& anchor, std::optional<float>& marginTop);
    float GetVerticalAlignBottomValue(std::string& anchor, std::optional<float>& marginTop);
    float GetHorizontalAlignStartValue(std::string& anchor, std::optional<float>& marginLeft);
    float GetHorizontalAlignCenterValue(std::string& anchor, std::optional<float>& marginLeft);
    float GetHorizontalAlignEndValue(std::string& anchor, std::optional<float>& marginLeft);
    void UpdateVerticalTwoAlignValues(TwoAlignedValues& twoAlignedValues, AlignRule alignRule);
    void UpdateHorizontalTwoAlignValues(TwoAlignedValues& twoAlignedValues, AlignRule alignRule);
    void UpdateSizeWhenChildrenEmpty(LayoutWrapper* layoutWrapper);

    bool isHorizontalRelyOnContainer_ = false;
    bool isVerticalRelyOnContainer_ = false;
    std::list<std::string> renderList_;
    std::map<std::string, RefPtr<LayoutWrapper>> idNodeMap_;
    std::map<std::string, uint32_t> incomingDegreeMap_;
    std::map<std::string, std::set<std::string>> reliedOnMap_;
    std::map<std::string, OffsetF> recordOffsetMap_;
    std::unordered_map<std::string, BarrierParams> barriers_;
    std::unordered_map<std::string, GuidelineParams> guidelines_;
    std::unordered_map<std::string, ChainParam> horizontalChains_;
    std::unordered_map<std::string, ChainParam> verticalChains_;
    std::unordered_map<std::string, std::string> horizontalChainNodeMap_;
    std::unordered_map<std::string, std::string> verticalChainNodeMap_;
    PaddingPropertyF padding_;
    SizeF containerSizeWithoutPaddingBorder_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_ALGORITHM_H