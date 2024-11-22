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

#include "core/components_ng/pattern/relative_container/relative_container_layout_algorithm.h"

#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_BIAS = 0.5f;
constexpr float HALF_MULTIPLY = 0.5f;
constexpr float DEFAULT_WEIGHT = 0.0f;
const std::string CONCAT_ID_PREFIX = "@concat";
inline bool IsAnchorContainer(const std::string& anchor)
{
    return anchor == "__container__";
}

std::string GetOrCreateNodeInspectorId(const RefPtr<FrameNode>& node)
{
    auto inspectorId = node->GetInspectorIdValue("");
    if (!node->HasInspectorId()) {
        inspectorId = CONCAT_ID_PREFIX + node->GetTag() + std::to_string(node->GetId());
    }
    return inspectorId;
}

void ResetChildAlignRulesChanged(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RelativeContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetChildAlignRulesChanged(false);
}
} // namespace

void RelativeContainerLayoutAlgorithm::UpdateTwoAlignValues(
    TwoAlignedValues& twoAlignedValues, AlignRule alignRule, LineDirection direction)
{
    if (twoAlignedValues.first.has_value() && twoAlignedValues.second.has_value()) {
        return;
    }

    auto result = (direction == LineDirection::HORIZONTAL) ? GetHorizontalAnchorValueByAlignRule(alignRule)
                                                           : GetVerticalAnchorValueByAlignRule(alignRule);

    if (!twoAlignedValues.first.has_value()) {
        twoAlignedValues.first = result;
        return;
    }
    if (!twoAlignedValues.second.has_value()) {
        twoAlignedValues.second = result;
    }
}

bool RelativeContainerLayoutAlgorithm::TopologicalResultHit(LayoutWrapper* layoutWrapper)
{
    auto node = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto pattern = node->GetPattern<RelativeContainerPattern>();
    CHECK_NULL_RETURN(pattern, false);
    if (pattern->GetChildAlignRulesChanged() || renderList_.size() != idNodeMap_.size()) {
        return false;
    }
    auto cache = std::move(pattern->GetTopologicalResultCache());
    if (!cache.has_value()) {
        return false;
    }
    renderList_ = std::move(cache.value());
    for (const auto& childId : renderList_) {
        if (idNodeMap_.find(childId) == idNodeMap_.end()) {
            return false;
        }
    }
    return true;
}

void RelativeContainerLayoutAlgorithm::Initialize(LayoutWrapper* layoutWrapper)
{
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    idNodeMap_.clear();
    reliedOnMap_.clear();
    recordOffsetMap_.clear();
    incomingDegreeMap_.clear();
    horizontalChainNodeMap_.clear();
    verticalChainNodeMap_.clear();
    renderList_.clear();
    auto layoutConstraint = relativeContainerLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint.has_value());
    bool idealWidthValid = layoutConstraint.value().selfIdealSize.Width().has_value();
    bool idealHeightValid = layoutConstraint.value().selfIdealSize.Height().has_value();
    auto idealSize = CreateIdealSizeByPercentRef(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    if (!idealWidthValid) {
        idealSize.SetWidth(
            std::min(idealSize.Width().value_or(Infinity<float>()), layoutConstraint.value().maxSize.Width()));
        idealSize.SetWidth(std::max(idealSize.Width().value_or(0.0f), layoutConstraint.value().minSize.Width()));
    }
    if (!idealHeightValid) {
        idealSize.SetHeight(
            std::min(idealSize.Height().value_or(Infinity<float>()), layoutConstraint.value().maxSize.Height()));
        idealSize.SetHeight(std::max(idealSize.Height().value_or(0.0f), layoutConstraint.value().minSize.Height()));
    }
    containerSizeWithoutPaddingBorder_ = idealSize.ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(containerSizeWithoutPaddingBorder_);
    if (relativeContainerLayoutProperty->GetPaddingProperty() ||
        relativeContainerLayoutProperty->GetBorderWidthProperty()) {
        padding_ = relativeContainerLayoutProperty->CreatePaddingAndBorder();
        MinusPaddingToSize(padding_, containerSizeWithoutPaddingBorder_);
    }
}

void RelativeContainerLayoutAlgorithm::DetermineTopologicalOrder(LayoutWrapper* layoutWrapper)
{
    CollectNodesById(layoutWrapper);
    CheckChain(layoutWrapper);
    if (TopologicalResultHit(layoutWrapper)) {
        return;
    }
    GetDependencyRelationship();
    if (!PreTopologicalLoopDetection(layoutWrapper)) {
        auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(relativeContainerLayoutProperty);
        const auto& childrenWrappers = layoutWrapper->GetAllChildrenWithBuild();
        auto constraint = relativeContainerLayoutProperty->CreateChildConstraint();
        for (const auto& childrenWrapper : childrenWrappers) {
            childrenWrapper->SetActive(false);
            constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
            childrenWrapper->Measure(constraint);
            constraint.Reset();
        }
        return;
    }
    TopologicalSort(renderList_);
}

void RelativeContainerLayoutAlgorithm::UpdateSizeWhenChildrenEmpty(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    const auto& layoutConstraint = relativeContainerLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint.has_value());
    auto idealSize =
        CreateIdealSizeByPercentRef(layoutConstraint.value(), Axis::FREE, MeasureType::MATCH_PARENT).ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize.IsPositive() ? idealSize : SizeF(0.0f, 0.0f));
    const auto& calcLayoutConstraint = relativeContainerLayoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(calcLayoutConstraint);
    auto selfIdealSize = calcLayoutConstraint->selfIdealSize;
    CHECK_NULL_VOID(selfIdealSize.has_value());
    padding_ = relativeContainerLayoutProperty->CreatePaddingAndBorder();
    if (selfIdealSize->IsWidthDimensionUnitAuto()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(
            SizeF(padding_.Width(), layoutWrapper->GetGeometryNode()->GetFrameSize().Height()));
    }
    if (selfIdealSize->IsHeightDimensionUnitAuto()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(
            SizeF(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), padding_.Height()));
    }
}

void RelativeContainerLayoutAlgorithm::CalcHorizontalGuideline(
    std::optional<CalcSize>& selfIdealSize, float containerHeight, const GuidelineInfo& guidelineInfo)
{
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    bool heightAuto = selfIdealSize->IsHeightDimensionUnitAuto();
    if (guidelineInfo.start.has_value()) {
        if ((guidelineInfo.start.value().Unit() == DimensionUnit::PERCENT) && heightAuto) {
            guidelines_[guidelineInfo.id] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
        } else {
            auto start = ConvertToPx(guidelineInfo.start.value(), scaleProperty, containerHeight);
            guidelines_[guidelineInfo.id] = std::make_pair(LineDirection::HORIZONTAL, start.value_or(0.0f));
        }
    } else if (guidelineInfo.end.has_value()) {
        if (heightAuto) {
            guidelines_[guidelineInfo.id] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
        } else {
            auto end = ConvertToPx(guidelineInfo.end.value(), scaleProperty, containerHeight);
            guidelines_[guidelineInfo.id] =
                std::make_pair(LineDirection::HORIZONTAL, (containerHeight - end.value_or(0.0f)));
        }
    }
}

void RelativeContainerLayoutAlgorithm::CalcVerticalGuideline(
    std::optional<CalcSize>& selfIdealSize, float containerWidth, const GuidelineInfo& guidelineInfo)
{
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    bool widthAuto = selfIdealSize->IsWidthDimensionUnitAuto();
    if (guidelineInfo.start.has_value()) {
        if ((guidelineInfo.start.value().Unit() == DimensionUnit::PERCENT) && widthAuto) {
            guidelines_[guidelineInfo.id] = std::make_pair(LineDirection::VERTICAL, 0.0f);
        } else {
            auto start = ConvertToPx(guidelineInfo.start.value(), scaleProperty, containerWidth);
            guidelines_[guidelineInfo.id] = std::make_pair(LineDirection::VERTICAL, start.value_or(0.0f));
        }
    } else if (guidelineInfo.end.has_value()) {
        if (widthAuto) {
            guidelines_[guidelineInfo.id] = std::make_pair(LineDirection::VERTICAL, 0.0f);
        } else {
            auto end = ConvertToPx(guidelineInfo.end.value(), scaleProperty, containerWidth);
            guidelines_[guidelineInfo.id] =
                std::make_pair(LineDirection::VERTICAL, (containerWidth - end.value_or(0.0f)));
        }
    }
}

void RelativeContainerLayoutAlgorithm::CalcBarrier(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(versionGreatorOrEqualToEleven_);
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = DynamicCast<RelativeContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    barriers_.clear();
    if (!layoutProperty->HasBarrier()) {
        return;
    }

    for (const auto& barrierInfo : layoutProperty->GetBarrierValue()) {
        if (barrierInfo.id.empty() || IsGuideline(barrierInfo.id) ||
            (idNodeMap_.find(barrierInfo.id) != idNodeMap_.end())) {
            continue;
        }
        auto barrierDirection = BarrierDirectionRtl(barrierInfo.direction);
        barriers_[barrierInfo.id] = std::make_pair(barrierDirection, barrierInfo.referencedId);
    }
}

void RelativeContainerLayoutAlgorithm::CalcGuideline(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(versionGreatorOrEqualToEleven_);
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = DynamicCast<RelativeContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(calcLayoutConstraint);
    auto calcSelfIdealSize = calcLayoutConstraint->selfIdealSize;
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto selfIdealSize = layoutConstraint->selfIdealSize;

    guidelines_.clear();
    if (!layoutProperty->HasGuideline()) {
        return;
    }

    for (const auto& guidelineInfo : layoutProperty->GetGuidelineValue()) {
        if (guidelineInfo.id.empty() || (idNodeMap_.find(guidelineInfo.id) != idNodeMap_.end())) {
            continue;
        }
        if (guidelineInfo.direction == LineDirection::HORIZONTAL) {
            CalcHorizontalGuideline(calcSelfIdealSize, selfIdealSize.Height().value_or(0), guidelineInfo);
        } else {
            CalcVerticalGuideline(calcSelfIdealSize, selfIdealSize.Width().value_or(0), guidelineInfo);
        }
    }

    for (const auto& guideline : guidelines_) {
        if (guideline.second.first == LineDirection::HORIZONTAL) {
            recordOffsetMap_[guideline.first] = OffsetF(0.0f, guideline.second.second);
        } else {
            recordOffsetMap_[guideline.first] = OffsetF(guideline.second.second, 0.0f);
        }
    }
}

bool RelativeContainerLayoutAlgorithm::IsGuideline(const std::string& id)
{
    CHECK_NULL_RETURN(versionGreatorOrEqualToEleven_, false);
    CHECK_NULL_RETURN(!guidelines_.empty(), false);
    if (guidelines_.find(id) == guidelines_.end()) {
        return false;
    }

    return true;
}

bool RelativeContainerLayoutAlgorithm::IsBarrier(const std::string& id)
{
    CHECK_NULL_RETURN(versionGreatorOrEqualToEleven_, false);
    CHECK_NULL_RETURN(!barriers_.empty(), false);

    if (barriers_.find(id) == barriers_.end()) {
        return false;
    }

    return true;
}

RelativeContainerLayoutAlgorithm::BarrierRect RelativeContainerLayoutAlgorithm::GetBarrierRectByReferencedIds(
    const std::vector<std::string>& referencedIds)
{
    BarrierRect barrierRect;
    for (const auto& nodeName : referencedIds) {
        if (IsGuideline(nodeName)) {
            if (guidelines_[nodeName].first == LineDirection::VERTICAL) {
                barrierRect.minLeft = std::min(barrierRect.minLeft, recordOffsetMap_[nodeName].GetX());
                barrierRect.maxRight = std::max(barrierRect.maxRight, recordOffsetMap_[nodeName].GetX());
            } else {
                barrierRect.minTop = std::min(barrierRect.minTop, recordOffsetMap_[nodeName].GetY());
                barrierRect.maxBottom = std::max(barrierRect.maxBottom, recordOffsetMap_[nodeName].GetY());
            }
            continue;
        }

        if (IsBarrier(nodeName)) {
            switch (barriers_[nodeName].first) {
                case BarrierDirection::LEFT:
                    barrierRect.minLeft = std::min(barrierRect.minLeft, recordOffsetMap_[nodeName].GetX());
                    break;
                case BarrierDirection::RIGHT:
                    barrierRect.maxRight = std::max(barrierRect.maxRight, recordOffsetMap_[nodeName].GetX());
                    break;
                case BarrierDirection::TOP:
                    barrierRect.minTop = std::min(barrierRect.minTop, recordOffsetMap_[nodeName].GetY());
                    break;
                case BarrierDirection::BOTTOM:
                    barrierRect.maxBottom = std::max(barrierRect.maxBottom, recordOffsetMap_[nodeName].GetY());
                    break;
                default:
                    break;
            }
            continue;
        }
        auto it = idNodeMap_.find(nodeName);
        if (it == idNodeMap_.end()) {
            continue;
        }

        auto childWrapper = it->second.layoutWrapper;
        if (childWrapper->GetLayoutProperty()->GetVisibility() == VisibleType::GONE) {
            continue;
        }
        auto& recordOffset = recordOffsetMap_[nodeName];
        barrierRect.minLeft = std::min(barrierRect.minLeft, recordOffset.GetX());
        barrierRect.minTop = std::min(barrierRect.minTop, recordOffset.GetY());
        barrierRect.maxRight = std::max(
            barrierRect.maxRight, recordOffset.GetX() + childWrapper->GetGeometryNode()->GetMarginFrameSize().Width());
        barrierRect.maxBottom = std::max(barrierRect.maxBottom,
            recordOffset.GetY() + childWrapper->GetGeometryNode()->GetMarginFrameSize().Height());
    }
    return barrierRect;
}

void RelativeContainerLayoutAlgorithm::MeasureBarrier(const std::string& barrierName)
{
    BarrierRect barrierRect = GetBarrierRectByReferencedIds(barriers_[barrierName].second);
    switch (barriers_[barrierName].first) {
        case BarrierDirection::LEFT:
            recordOffsetMap_[barrierName] = OffsetF(barrierRect.minLeft, 0.0f);
            break;
        case BarrierDirection::RIGHT:
            recordOffsetMap_[barrierName] = OffsetF(barrierRect.maxRight, 0.0f);
            break;
        case BarrierDirection::TOP:
            recordOffsetMap_[barrierName] = OffsetF(0.0f, barrierRect.minTop);
            break;
        case BarrierDirection::BOTTOM:
            recordOffsetMap_[barrierName] = OffsetF(0.0f, barrierRect.maxBottom);
            break;
        default:
            break;
    }
}

void RelativeContainerLayoutAlgorithm::CheckNodeInHorizontalChain(std::string& currentNode,
    AlignRulesItem& currentAlignRules, std::vector<std::string>& chainNodes,
    AlignRule& rightAnchor, float& totalChainWeight)
{
    std::string nextNode = rightAnchor.anchor;
    while (idNodeMap_.find(nextNode) != idNodeMap_.end()) {
        if (currentAlignRules[AlignDirection::RIGHT].horizontal != HorizontalAlign::START) {
            break;
        }
        CHECK_NULL_BREAK(idNodeMap_.find(nextNode) != idNodeMap_.end());
        auto nextNodeWrapper = idNodeMap_[nextNode].layoutWrapper;
        const auto& nextNodeFlexItem = nextNodeWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!nextNodeFlexItem) {
            break;
        }
        AlignRulesItem nextNodeAlignRules = nextNodeFlexItem->GetAlignRulesValue();
        if (nextNodeAlignRules.find(AlignDirection::LEFT) == nextNodeAlignRules.end() ||
            nextNodeAlignRules.find(AlignDirection::RIGHT) == nextNodeAlignRules.end()) {
            break;
        }
        if (nextNodeAlignRules[AlignDirection::LEFT].anchor != currentNode ||
            nextNodeAlignRules[AlignDirection::LEFT].horizontal != HorizontalAlign::END) {
            break;
        }
        chainNodes.emplace_back(nextNode);
        bool childGone = nextNodeWrapper->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) ==
                         VisibleType::GONE;
        float childLayoutWeight = DEFAULT_WEIGHT;
        if (!childGone) {
            childLayoutWeight = nextNodeFlexItem->GetChainWeight()->first.value_or(0.0f);
            if (GreatNotEqual(childLayoutWeight, 0.0f)) {
                isChainWeightMode_ = true;
                totalChainWeight += childLayoutWeight;
            }
        }
        currentNode = nextNode;
        currentAlignRules = nextNodeAlignRules;
        nextNode = nextNodeAlignRules[AlignDirection::RIGHT].anchor;
        rightAnchor = nextNodeAlignRules[AlignDirection::RIGHT];
    }
}

void RelativeContainerLayoutAlgorithm::CheckHorizontalChain(const ChildMeasureWrapper& measureParam)
{
    auto childWrapper = measureParam.layoutWrapper;
    auto childHostNode = childWrapper->GetHostNode();
    const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
    AlignRulesItem currentAlignRules = flexItem->GetAlignRulesValue();
    ChainInfo chainInfo = flexItem->GetHorizontalChainStyleValue();
    CHECK_NULL_VOID(chainInfo.direction.has_value());
    CHECK_NULL_VOID(chainInfo.style.has_value());
    BiasPair bias(0.5f, 0.5f);
    float totalChainWeight = DEFAULT_WEIGHT;
    if (flexItem->HasBias()) {
        bias = flexItem->GetBiasValue();
    }
    if (currentAlignRules.find(AlignDirection::LEFT) == currentAlignRules.end() ||
        currentAlignRules.find(AlignDirection::RIGHT) == currentAlignRules.end()) {
        return;
    }
    AlignRule leftAnchor = currentAlignRules[AlignDirection::LEFT];
    CHECK_NULL_VOID(IsAnchorLegal(leftAnchor.anchor));
    AlignRule rightAnchor = currentAlignRules[AlignDirection::RIGHT];
    std::string currentNode = measureParam.id;
    std::vector<std::string> chainNodes;
    chainNodes.emplace_back(currentNode);
    if (childWrapper->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::GONE) {
        float childLayoutWeight = flexItem->GetChainWeight()->first.value_or(DEFAULT_WEIGHT);
        isChainWeightMode_ += GreatNotEqual(childLayoutWeight, DEFAULT_WEIGHT);
        totalChainWeight += std::max(childLayoutWeight, DEFAULT_WEIGHT);
    }
    CheckNodeInHorizontalChain(currentNode, currentAlignRules, chainNodes, rightAnchor, totalChainWeight);
    CHECK_NULL_VOID(IsAnchorLegal(rightAnchor.anchor) && chainNodes.size() > 1);
    if (IsAnchorContainer(leftAnchor.anchor) || IsAnchorContainer(rightAnchor.anchor)) {
        isHorizontalRelyOnContainer_ = true;
    }
    ChainParam chainParam;
    chainParam.ids = chainNodes;
    chainParam.anchorHead = leftAnchor;
    chainParam.anchorTail = rightAnchor;
    chainParam.chainStyle = chainInfo.style.value();
    chainParam.bias = bias;
    chainParam.totalChainWeight = totalChainWeight;
    for (const auto& id : chainParam.ids) {
        chainParam.itemSize[id] = std::nullopt;
        horizontalChainNodeMap_[id] = measureParam.id;
    }
    horizontalChains_[measureParam.id] = chainParam;
}

void RelativeContainerLayoutAlgorithm::CheckNodeInVerticalChain(std::string& currentNode,
    AlignRulesItem& currentAlignRules, std::vector<std::string>& chainNodes,
    AlignRule& bottomAnchor, float& totalChainWeight)
{
    std::string nextNode = bottomAnchor.anchor;
    while (idNodeMap_.find(nextNode) != idNodeMap_.end()) {
        if (currentAlignRules[AlignDirection::BOTTOM].vertical != VerticalAlign::TOP) {
            break;
        }
        CHECK_NULL_BREAK(idNodeMap_.find(nextNode) != idNodeMap_.end());
        auto nextNodeWrapper = idNodeMap_[nextNode].layoutWrapper;
        const auto& nextNodeFlexItem = nextNodeWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!nextNodeFlexItem) {
            break;
        }
        AlignRulesItem nextNodeAlignRules = nextNodeFlexItem->GetAlignRulesValue();
        if (nextNodeAlignRules.find(AlignDirection::TOP) == nextNodeAlignRules.end() ||
            nextNodeAlignRules.find(AlignDirection::BOTTOM) == nextNodeAlignRules.end()) {
            break;
        }
        if (nextNodeAlignRules[AlignDirection::TOP].anchor != currentNode ||
            nextNodeAlignRules[AlignDirection::TOP].vertical != VerticalAlign::BOTTOM) {
            break;
        }
        chainNodes.emplace_back(nextNode);
        bool childGone = nextNodeWrapper->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) ==
                         VisibleType::GONE;
        float childLayoutWeight = DEFAULT_WEIGHT;
        if (!childGone) {
            childLayoutWeight = nextNodeFlexItem->GetChainWeight()->second.value_or(0.0f);
            if (GreatNotEqual(childLayoutWeight, 0.0f)) {
                isChainWeightMode_ = true;
                totalChainWeight += childLayoutWeight;
            }
        }
        currentNode = nextNode;
        currentAlignRules = nextNodeAlignRules;
        nextNode = nextNodeAlignRules[AlignDirection::BOTTOM].anchor;
        bottomAnchor = nextNodeAlignRules[AlignDirection::BOTTOM];
    }
}

void RelativeContainerLayoutAlgorithm::CheckVerticalChain(const ChildMeasureWrapper& measureParam)
{
    auto childWrapper = measureParam.layoutWrapper;
    auto childHostNode = childWrapper->GetHostNode();
    const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
    AlignRulesItem currentAlignRules = flexItem->GetAlignRulesValue();
    ChainInfo chainInfo = flexItem->GetVerticalChainStyleValue();
    BiasPair bias(0.5f, 0.5f);
    float totalChainWeight = DEFAULT_WEIGHT;
    CHECK_NULL_VOID(chainInfo.direction.has_value());
    CHECK_NULL_VOID(chainInfo.style.has_value());
    if (flexItem->HasBias()) {
        bias = flexItem->GetBiasValue();
    }
    if (currentAlignRules.find(AlignDirection::TOP) == currentAlignRules.end() ||
        currentAlignRules.find(AlignDirection::BOTTOM) == currentAlignRules.end()) {
        return;
    }
    AlignRule topAnchor = currentAlignRules[AlignDirection::TOP];
    CHECK_NULL_VOID(IsAnchorLegal(topAnchor.anchor));
    AlignRule bottomAnchor = currentAlignRules[AlignDirection::BOTTOM];
    std::string currentNode = measureParam.id;
    std::vector<std::string> chainNodes;
    chainNodes.emplace_back(currentNode);
    if (childWrapper->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::GONE) {
        float childLayoutWeight = flexItem->GetChainWeight()->second.value_or(DEFAULT_WEIGHT);
        isChainWeightMode_ += GreatNotEqual(childLayoutWeight, DEFAULT_WEIGHT);
        totalChainWeight += std::max(childLayoutWeight, DEFAULT_WEIGHT);
    }
    CheckNodeInVerticalChain(currentNode, currentAlignRules, chainNodes, bottomAnchor, totalChainWeight);
    CHECK_NULL_VOID(IsAnchorLegal(bottomAnchor.anchor) && chainNodes.size() > 1);
    if (IsAnchorContainer(topAnchor.anchor) || IsAnchorContainer(bottomAnchor.anchor)) {
        isVerticalRelyOnContainer_ = true;
    }
    ChainParam chainParam;
    chainParam.ids = chainNodes;
    chainParam.anchorHead = topAnchor;
    chainParam.anchorTail = bottomAnchor;
    chainParam.chainStyle = chainInfo.style.value();
    chainParam.bias = bias;
    chainParam.totalChainWeight = totalChainWeight;
    for (const auto& id : chainParam.ids) {
        chainParam.itemSize[id] = std::nullopt;
        verticalChainNodeMap_[id] = measureParam.id;
    }
    verticalChains_[measureParam.id] = chainParam;
}

void RelativeContainerLayoutAlgorithm::CheckChain(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(versionGreatorOrEqualToEleven_);
    horizontalChains_.clear();
    verticalChains_.clear();
    for (const auto& mapItem : idNodeMap_) {
        auto childWrapper = mapItem.second.layoutWrapper;
        auto childLayoutProperty = childWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(childLayoutProperty);
        const auto& flexItem = childLayoutProperty->GetFlexItemProperty();
        if (!flexItem || !flexItem->HasAlignRules()) {
            continue;
        }

        std::string chainName;
        if (flexItem->HasHorizontalChainStyle() && !IsNodeInHorizontalChain(mapItem.first, chainName)) {
            CheckHorizontalChain(mapItem.second);
        }

        if (flexItem->HasVerticalChainStyle() && !IsNodeInVerticalChain(mapItem.first, chainName)) {
            CheckVerticalChain(mapItem.second);
        }
    }
}

void RelativeContainerLayoutAlgorithm::RecordSizeInChain(const std::string& nodeName)
{
    CHECK_NULL_VOID(versionGreatorOrEqualToEleven_);
    CHECK_NULL_VOID(idNodeMap_.find(nodeName) != idNodeMap_.end());
    auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
    CHECK_NULL_VOID(childWrapper);
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    const auto& flexItem = childLayoutProperty->GetFlexItemProperty();
    std::string chainName;
    if (IsNodeInHorizontalChain(nodeName, chainName) &&
        !GreatNotEqual(flexItem->GetChainWeight()->first.value_or(0.0f), 0.0f)) {
        horizontalChains_[chainName].itemSize[nodeName] =
            childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
        horizontalChains_[chainName].remainingSpace -=  childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    }
    if (IsNodeInVerticalChain(nodeName, chainName) &&
        !GreatNotEqual(flexItem->GetChainWeight()->second.value_or(0.0f), 0.0f)) {
        verticalChains_[chainName].itemSize[nodeName] =
            childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
        verticalChains_[chainName].remainingSpace -=  childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    }
}

bool RelativeContainerLayoutAlgorithm::IsNodeInHorizontalChain(const std::string& nodeName, std::string& chainName)
{
    CHECK_NULL_RETURN(versionGreatorOrEqualToEleven_, false);
    CHECK_NULL_RETURN(!horizontalChains_.empty(), false);
    auto it = horizontalChainNodeMap_.find(nodeName);
    if (it != horizontalChainNodeMap_.end()) {
        chainName = it->second;
        return true;
    }
    return false;
}
bool RelativeContainerLayoutAlgorithm::IsNodeInVerticalChain(const std::string& nodeName, std::string& chainName)
{
    CHECK_NULL_RETURN(versionGreatorOrEqualToEleven_, false);
    CHECK_NULL_RETURN(!verticalChains_.empty(), false);
    auto it = verticalChainNodeMap_.find(nodeName);
    if (it != verticalChainNodeMap_.end()) {
        chainName = it->second;
        return true;
    }
    return false;
}

float RelativeContainerLayoutAlgorithm::GetHorizontalAnchorValueByAlignRule(AlignRule& alignRule)
{
    if (IsGuidelineOrBarrier(alignRule.anchor)) {
        return recordOffsetMap_[alignRule.anchor].GetX();
    }
    bool anchorIsContainer = IsAnchorContainer(alignRule.anchor);
    float anchorWidth = 0.0f;
    if (anchorIsContainer) {
        anchorWidth = containerSizeWithoutPaddingBorder_.Width();
    } else {
        anchorWidth = versionGreatorOrEqualToEleven_
                          ? idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetFrameSize().Width()
                          : idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    }

    std::optional<float> marginLeft;
    if (!anchorIsContainer && versionGreatorOrEqualToEleven_) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor].layoutWrapper;
        if (anchorWrapper->GetGeometryNode()->GetMargin()) {
            marginLeft = anchorWrapper->GetGeometryNode()->GetMargin()->left;
        }
    }

    float offsetX = 0.0f;
    switch (alignRule.horizontal) {
        case HorizontalAlign::START:
            offsetX = 0.0f;
            break;
        case HorizontalAlign::CENTER:
            offsetX = anchorWidth * HALF_MULTIPLY;
            break;
        case HorizontalAlign::END:
            offsetX = anchorWidth;
            break;
        default:
            break;
    }

    offsetX += anchorIsContainer ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX() + marginLeft.value_or(0);
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::GetVerticalAnchorValueByAlignRule(AlignRule& alignRule)
{
    if (IsGuidelineOrBarrier(alignRule.anchor)) {
        return recordOffsetMap_[alignRule.anchor].GetY();
    }
    bool anchorIsContainer = IsAnchorContainer(alignRule.anchor);
    float anchorHeight = 0.0f;
    if (anchorIsContainer) {
        anchorHeight = containerSizeWithoutPaddingBorder_.Height();
    } else {
        anchorHeight =
            versionGreatorOrEqualToEleven_
                ? idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetFrameSize().Height()
                : idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    }

    std::optional<float> marginTop;
    if (!anchorIsContainer && versionGreatorOrEqualToEleven_) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor].layoutWrapper;
        if (anchorWrapper->GetGeometryNode()->GetMargin()) {
            marginTop = anchorWrapper->GetGeometryNode()->GetMargin()->top;
        }
    }

    float offsetY = 0.0f;
    switch (alignRule.vertical) {
        case VerticalAlign::TOP:
            offsetY = 0.0f;
            break;
        case VerticalAlign::CENTER:
            offsetY = anchorHeight * HALF_MULTIPLY;
            break;
        case VerticalAlign::BOTTOM:
            offsetY = anchorHeight;
            break;
        default:
            break;
    }

    offsetY += anchorIsContainer ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY() + marginTop.value_or(0);
    return offsetY;
}

std::pair<float, float> RelativeContainerLayoutAlgorithm::CalcOffsetInChainGetStart(const float& anchorDistance,
    const float& contentSize, int32_t itemCount, const ChainParam& chainParam, LineDirection direction)
{
    float spaceSize = 0.0f;
    float start = 0.0f;
    float bias = (direction == LineDirection::HORIZONTAL) ? chainParam.bias.first : chainParam.bias.second;
    if (GreatOrEqual(anchorDistance, contentSize)) {
        switch (chainParam.chainStyle) {
            case ChainStyle::SPREAD:
                spaceSize = (anchorDistance - contentSize) / (itemCount + 1);
                start = spaceSize;
                break;
            case ChainStyle::SPREAD_INSIDE:
                spaceSize = anchorDistance - contentSize;
                spaceSize = GreatNotEqual(itemCount, 1) ? spaceSize / (itemCount - 1) : spaceSize;
                break;
            case ChainStyle::PACKED:
                spaceSize = 0.0f;
                start = (anchorDistance - contentSize) * bias;
                break;
            default:
                break;
        }
    } else {
        switch (chainParam.chainStyle) {
            case ChainStyle::SPREAD:
            case ChainStyle::SPREAD_INSIDE:
                start = (anchorDistance - contentSize) * HALF_MULTIPLY;
                break;
            case ChainStyle::PACKED:
                start = (anchorDistance - contentSize) * bias;
                break;
            default:
                break;
        }
    }
    return { spaceSize, start };
}

void RelativeContainerLayoutAlgorithm::RecordOffsetInChain(
    float offset, float spaceSize, const std::string& chainName, LineDirection direction)
{
    std::unordered_map<std::string, ChainParam>& chains =
        (direction == LineDirection::HORIZONTAL) ? horizontalChains_ : verticalChains_;

    if (direction == LineDirection::HORIZONTAL) {
        for (const auto& nodeName : chains[chainName].ids) {
            auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
            if (childWrapper->GetLayoutProperty()->GetVisibility() == VisibleType::GONE) {
                continue;
            }
            recordOffsetMap_[nodeName] = OffsetF(offset, recordOffsetMap_[nodeName].GetY());
            offset += chains[chainName].itemSize[nodeName].value() + spaceSize;
        }
    } else {
        for (const auto& nodeName : chains[chainName].ids) {
            auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
            if (childWrapper->GetLayoutProperty()->GetVisibility() == VisibleType::GONE) {
                continue;
            }
            recordOffsetMap_[nodeName] = OffsetF(recordOffsetMap_[nodeName].GetX(), offset);
            offset += chains[chainName].itemSize[nodeName].value() + spaceSize;
        }
    }
}

bool RelativeContainerLayoutAlgorithm::CalcOffsetInChain(const std::string& chainName, LineDirection direction)
{
    float contentSize = 0.0f;
    float anchorDistance = 0.0f;
    float spaceSize = 0.0f;
    float start = 0.0f;
    float end = 0.0f;
    std::unordered_map<std::string, ChainParam>& chains =
        (direction == LineDirection::HORIZONTAL) ? horizontalChains_ : verticalChains_;
    if (chains[chainName].isCalculated) {
        return true;
    }
    auto itemCount = chains[chainName].ids.size();
    for (const auto& itemSize : chains[chainName].itemSize) {
        auto childWrapper = idNodeMap_[itemSize.first].layoutWrapper;
        if (childWrapper->GetLayoutProperty()->GetVisibility() == VisibleType::GONE) {
            itemCount--;
            continue;
        }
        if (!itemSize.second.has_value()) {
            return false;
        }
        contentSize += itemSize.second.value();
    }

    if (direction == LineDirection::HORIZONTAL) {
        start = GetHorizontalAnchorValueByAlignRule(chains[chainName].anchorHead);
        end = GetHorizontalAnchorValueByAlignRule(chains[chainName].anchorTail);
    } else {
        start = GetVerticalAnchorValueByAlignRule(chains[chainName].anchorHead);
        end = GetVerticalAnchorValueByAlignRule(chains[chainName].anchorTail);
    }
    anchorDistance = end - start;
    std::pair<float, float> spaceSizeAndStart =
        CalcOffsetInChainGetStart(anchorDistance, contentSize, itemCount, chains[chainName], direction);
    spaceSize = spaceSizeAndStart.first;
    start += spaceSizeAndStart.second;
    RecordOffsetInChain(start, spaceSize, chainName, direction);
    chains[chainName].isCalculated = true;
    return true;
}

void RelativeContainerLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    std::lock_guard<std::mutex> lock(relativeContainerMutex_);
    CHECK_NULL_VOID(layoutWrapper);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RelativeContainerPattern>();
    CHECK_NULL_VOID(pattern);
    versionGreatorOrEqualToEleven_ = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN);
    if (layoutWrapper->GetAllChildrenWithBuild().empty()) {
        UpdateSizeWhenChildrenEmpty(layoutWrapper);
        ResetChildAlignRulesChanged(layoutWrapper);
        return;
    }
    Initialize(layoutWrapper);
    DetermineTopologicalOrder(layoutWrapper);
    if (SystemProperties::GetDebugEnabled()) {
        pattern->SetTopologicalResult(RelativeContainerPattern::TopoListToString(renderList_));
    }

    MeasureChild(layoutWrapper);
    MeasureChainWeight(layoutWrapper);
    MeasureSelf(layoutWrapper);
    AdjustOffsetRtl(layoutWrapper);
    pattern->SetTopologicalResultCache(std::move(renderList_));
    ResetChildAlignRulesChanged(layoutWrapper);
}

void RelativeContainerLayoutAlgorithm::MeasureChainWeight(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(isChainWeightMode_);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    for (const auto& nodeName : renderList_) {
        auto it = idNodeMap_.find(nodeName);
        if (it == idNodeMap_.end()) {
            ACE_LAYOUT_SCOPED_TRACE("%s is not found in idNodeMap of relativeContainer:%d", nodeName.c_str(),
                layoutWrapper->GetHostNode() ? layoutWrapper->GetHostNode()->GetId() : -1);
            continue;
        }
        auto childWrapper = it->second.layoutWrapper;
        auto childConstraint = relativeContainerLayoutProperty->CreateChildConstraint();
        if (!childWrapper->IsActive()||!childWrapper->GetLayoutProperty() ||
            !childWrapper->GetLayoutProperty()->GetFlexItemProperty()) {
            continue;
        }
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        std::string chainName;
        if (!flexItem->HasAlignRules()) {
            continue;
        }
        if (!(IsNodeInHorizontalChain(nodeName, chainName) || IsNodeInVerticalChain(nodeName, chainName))) {
            flexItem->ClearAlignValue();
            CalcSizeParam(layoutWrapper, nodeName);
            CalcOffsetParam(layoutWrapper, nodeName);
            continue;
        }
        if (IsNodeInHorizontalChain(nodeName, chainName) && HasWeight(flexItem, LineDirection::HORIZONTAL)) {
            CalcChainWeightSize(flexItem, childConstraint, chainName, LineDirection::HORIZONTAL);
        }
        if (IsNodeInVerticalChain(nodeName, chainName) && HasWeight(flexItem, LineDirection::VERTICAL)) {
            CalcChainWeightSize(flexItem, childConstraint, chainName, LineDirection::VERTICAL);
        }
        childWrapper->Measure(childConstraint);
        if (IsNodeInHorizontalChain(nodeName, chainName)) {
            horizontalChains_[chainName].itemSize[nodeName] =
                childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
        }
        if (IsNodeInVerticalChain(nodeName, chainName)) {
            verticalChains_[chainName].itemSize[nodeName] =
                childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
        }
        CalcOffsetParam(layoutWrapper, nodeName);
    }
}

void RelativeContainerLayoutAlgorithm::InitRemainingSpace(const std::string & chainName, LineDirection direction)
{
    std::unordered_map<std::string, ChainParam> &chains =
        (direction == LineDirection::HORIZONTAL) ? horizontalChains_ : verticalChains_;
    CHECK_NULL_VOID(!chains[chainName].isWeightCalculated);
    float start = 0.0f;
    float end = 0.0f;
    if (direction == LineDirection::HORIZONTAL) {
        start = GetHorizontalAnchorValueByAlignRule(chains[chainName].anchorHead);
        end = GetHorizontalAnchorValueByAlignRule(chains[chainName].anchorTail);
    } else {
        start = GetVerticalAnchorValueByAlignRule(chains[chainName].anchorHead);
        end = GetVerticalAnchorValueByAlignRule(chains[chainName].anchorTail);
    }
    chains[chainName].remainingSpace += end - start;
    chains[chainName].isWeightCalculated = true;
}

bool RelativeContainerLayoutAlgorithm::HasWeight(
    const std::unique_ptr<FlexItemProperty>& flexItem, LineDirection direction)
{
    if (direction == LineDirection::HORIZONTAL) {
        return GreatNotEqual(flexItem->GetChainWeight()->first.value_or(DEFAULT_WEIGHT), DEFAULT_WEIGHT);
    } else {
        return GreatNotEqual(flexItem->GetChainWeight()->second.value_or(DEFAULT_WEIGHT), DEFAULT_WEIGHT);
    }
}

void RelativeContainerLayoutAlgorithm::CalcChainWeightSize(
    const std::unique_ptr<FlexItemProperty>& flexItem, LayoutConstraintF& childConstraint,
    const std::string & chainName, LineDirection direction)
{
    std::optional<float> childIdealSize;
    std::unordered_map<std::string, ChainParam> &chains =
        (direction == LineDirection::HORIZONTAL) ? horizontalChains_ : verticalChains_;
    if (!chains[chainName].isWeightCalculated) {
        InitRemainingSpace(chainName, direction);
    }
    if (chains[chainName].remainingSpace <= DEFAULT_WEIGHT) {
        (direction == LineDirection::HORIZONTAL) ?
        childConstraint.selfIdealSize.SetWidth(0.0f) : childConstraint.selfIdealSize.SetHeight(0.0f);
    } else {
        auto chainWeight = (direction == LineDirection::HORIZONTAL) ?
            flexItem->GetChainWeight()->first.value_or(DEFAULT_WEIGHT) :
            flexItem->GetChainWeight()->second.value_or(DEFAULT_WEIGHT);
        childIdealSize = chains[chainName].remainingSpace * chainWeight / chains[chainName].totalChainWeight;
        (direction == LineDirection::HORIZONTAL) ?
        childConstraint.selfIdealSize.SetWidth(childIdealSize.value()) :
        childConstraint.selfIdealSize.SetHeight(childIdealSize.value());
    }
}

void RelativeContainerLayoutAlgorithm::MeasureChild(LayoutWrapper* layoutWrapper)
{
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    for (const auto& nodeName : renderList_) {
        if (IsBarrier(nodeName)) {
            MeasureBarrier(nodeName);
        }
        auto it = idNodeMap_.find(nodeName);
        if (it == idNodeMap_.end()) {
            ACE_LAYOUT_SCOPED_TRACE("Id %s not in map", nodeName.c_str());
            continue;
        }
        auto childWrapper = it->second.layoutWrapper;
        auto childConstraint = relativeContainerLayoutProperty->CreateChildConstraint();
        if (!childWrapper->IsActive()) {
            childWrapper->Measure(childConstraint);
            continue;
        }
        if (!childWrapper->GetLayoutProperty() || !childWrapper->GetLayoutProperty()->GetFlexItemProperty()) {
            childWrapper->Measure(childConstraint);
            recordOffsetMap_[nodeName] = OffsetF(0.0f, 0.0f);
            continue;
        }
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!flexItem->HasAlignRules()) {
            childWrapper->Measure(childConstraint);
            recordOffsetMap_[nodeName] = OffsetF(0.0f, 0.0f);
            continue;
        }
        flexItem->ClearAlignValue();
        auto alignRules = flexItem->GetAlignRulesValue();
        auto frameNode = childWrapper->GetHostNode();
        if (!alignRules.empty() && frameNode && frameNode->GetLayoutProperty()) {
            // when child has alignRules and position, the position property do not work.
            frameNode->GetLayoutProperty()->SetUsingPosition(false);
        }
        CalcSizeParam(layoutWrapper, nodeName);
        CalcOffsetParam(layoutWrapper, nodeName);
    }
}

void RelativeContainerLayoutAlgorithm::MeasureSelf(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(versionGreatorOrEqualToEleven_);
    CHECK_NULL_VOID(layoutWrapper);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    const auto& calcLayoutConstraint = relativeContainerLayoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(calcLayoutConstraint);
    auto selfIdealSize = calcLayoutConstraint->selfIdealSize;
    CHECK_NULL_VOID(selfIdealSize.has_value());
    CHECK_NULL_VOID(selfIdealSize->IsDimensionUnitAuto());
    RectF relativeContainerRect(0, 0, 0, 0);
    for (const auto& nodeName : renderList_) {
        auto it = idNodeMap_.find(nodeName);
        if (it == idNodeMap_.end()) {
            continue;
        }
        auto childWrapper = it->second.layoutWrapper;
        if (childWrapper->GetLayoutProperty()->GetVisibility() == VisibleType::GONE) {
            continue;
        }
        RectF tempRect(recordOffsetMap_[nodeName].GetX(), recordOffsetMap_[nodeName].GetY(),
            childWrapper->GetGeometryNode()->GetMarginFrameSize().Width(),
            childWrapper->GetGeometryNode()->GetMarginFrameSize().Height());
        relativeContainerRect = relativeContainerRect.CombineRectT(tempRect);
    }

    relativeContainerRect =
        relativeContainerRect.IntersectRectT(RectF(0.0f, 0.0f, Infinity<float>(), Infinity<float>()));
    if (selfIdealSize->IsWidthDimensionUnitAuto() && !isHorizontalRelyOnContainer_) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(relativeContainerRect.Width() + padding_.Width(),
            layoutWrapper->GetGeometryNode()->GetFrameSize().Height()));
    }
    if (selfIdealSize->IsHeightDimensionUnitAuto() && !isVerticalRelyOnContainer_) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(),
            relativeContainerRect.Height() + padding_.Height()));
    }
}

void RelativeContainerLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    auto left = padding_.left.value_or(0);
    auto top = padding_.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto textDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    for (auto&& childWrapper : layoutWrapper->GetAllChildrenWithBuild()) {
        auto nodeName = GetOrCreateNodeInspectorId(childWrapper->GetHostNode());
        if (!childWrapper->GetLayoutProperty()->GetFlexItemProperty() && (textDirection != TextDirection::RTL)) {
            childWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, 0.0f) + paddingOffset);
            childWrapper->Layout();
            continue;
        }
        auto it = recordOffsetMap_.find(nodeName);
        if (it == recordOffsetMap_.end()) {
            continue;
        }
        if (it == recordOffsetMap_.end()) {
            childWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, 0.0f) + paddingOffset);
            childWrapper->Layout();
            continue;
        }
        auto curOffset = it->second;
        childWrapper->GetGeometryNode()->SetMarginFrameOffset(curOffset + paddingOffset);
        childWrapper->Layout();
    }
}

void RelativeContainerLayoutAlgorithm::CollectNodesById(LayoutWrapper* layoutWrapper)
{
    idNodeMap_.clear();
    const auto& childrenWrappers = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& childWrapper : childrenWrappers) {
        if (!childWrapper) {
            continue;
        }
        auto childHostNode = childWrapper->GetHostNode();
        if (!childHostNode) {
            continue;
        }
        childWrapper->SetActive();
        ChildMeasureWrapper childMeasureWrapper = { .layoutWrapper = childWrapper,
            .id = GetOrCreateNodeInspectorId(childHostNode) };
        idNodeMap_.emplace(childMeasureWrapper.id, childMeasureWrapper);
    }
    CalcGuideline(layoutWrapper);
    CalcBarrier(layoutWrapper);
}

void RelativeContainerLayoutAlgorithm::GetDependencyRelationshipInChain(
    const std::string& anchor, const std::string& nodeName)
{
    if (IsAnchorContainer(anchor) || IsGuideline(anchor)) {
        return;
    }
    if (IsBarrier(anchor) || idNodeMap_.find(anchor) != idNodeMap_.end()) {
        InsertToReliedOnMap(anchor, nodeName);
    }
}

void RelativeContainerLayoutAlgorithm::GetDependencyRelationshipInBarrier()
{
    CHECK_NULL_VOID(versionGreatorOrEqualToEleven_);
    for (const auto& barrier : barriers_) {
        for (const auto& nodeName : barrier.second.second) {
            InsertToReliedOnMap(nodeName, barrier.first);
        }
    }
}

bool RelativeContainerLayoutAlgorithm::IsAlignRuleInChain(const AlignDirection& direction, const std::string& nodeName)
{
    CHECK_NULL_RETURN(versionGreatorOrEqualToEleven_, false);
    std::string chainName;
    if ((direction == AlignDirection::LEFT || direction == AlignDirection::RIGHT) &&
        IsNodeInHorizontalChain(nodeName, chainName)) {
        GetDependencyRelationshipInChain(horizontalChains_[chainName].anchorHead.anchor, nodeName);
        GetDependencyRelationshipInChain(horizontalChains_[chainName].anchorTail.anchor, nodeName);
        return true;
    }
    if ((direction == AlignDirection::TOP || direction == AlignDirection::BOTTOM) &&
        IsNodeInVerticalChain(nodeName, chainName)) {
        GetDependencyRelationshipInChain(verticalChains_[chainName].anchorHead.anchor, nodeName);
        GetDependencyRelationshipInChain(verticalChains_[chainName].anchorTail.anchor, nodeName);
        return true;
    }
    return false;
}

void RelativeContainerLayoutAlgorithm::InsertToReliedOnMap(const std::string& anchorName, const std::string& nodeName)
{
    auto iter = reliedOnMap_.find(anchorName);
    if (iter == reliedOnMap_.end()) {
        std::set<std::string> reliedList;
        reliedList.insert(nodeName);
        reliedOnMap_[anchorName] = reliedList;
        return;
    }
    iter->second.insert(nodeName);
}

void RelativeContainerLayoutAlgorithm::GetDependencyRelationship()
{
    for (const auto& mapItem : idNodeMap_) {
        auto childWrapper = mapItem.second.layoutWrapper;
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        auto childHostNode = childWrapper->GetHostNode();
        if (!flexItem || !flexItem->HasAlignRules()) {
            continue;
        }
        for (const auto& alignRule : flexItem->GetAlignRulesValue()) {
            if (IsAlignRuleInChain(alignRule.first, mapItem.first)) {
                continue;
            }

            if (IsBarrier(alignRule.second.anchor)) {
                InsertToReliedOnMap(alignRule.second.anchor, mapItem.second.id);
                continue;
            }

            if (IsAnchorContainer(alignRule.second.anchor) || IsGuideline(alignRule.second.anchor)) {
                if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE) {
                    isHorizontalRelyOnContainer_ = true;
                } else if (static_cast<uint32_t>(alignRule.first) < VERTICAL_DIRECTION_RANGE) {
                    isVerticalRelyOnContainer_ = true;
                }
                continue;
            }
            auto it = idNodeMap_.find(alignRule.second.anchor);
            if (it == idNodeMap_.end()) {
                continue;
            }

            if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                auto anchorChildWrapper = it->second.layoutWrapper;
                auto anchorChildLayoutProp = anchorChildWrapper->GetLayoutProperty();
                auto anchorChildVisibility = anchorChildLayoutProp->GetVisibility();
                if (anchorChildVisibility == VisibleType::GONE) {
                    childWrapper->SetActive(false);
                }
            }
            // if a is the anchor of b, then reliedOnMap should place <a, [b]> for the first appearance
            // of key a. Otherwise b will be inserted into the existing value list
            InsertToReliedOnMap(alignRule.second.anchor, mapItem.second.id);
        }
    }
    GetDependencyRelationshipInBarrier();
}

void RelativeContainerLayoutAlgorithm::PreTopologicalLoopDetectionGetAnchorSet(
    const std::string& nodeName, const AlignRulesItem& alignRulesItem, std::set<std::string>& anchorSet)
{
    for (const auto& alignRule : alignRulesItem) {
        std::string anchor = alignRule.second.anchor;
        std::string chainName;
        if (IsNodeInHorizontalChain(nodeName, chainName)) {
            if (alignRule.first == AlignDirection::LEFT) {
                anchor = horizontalChains_[chainName].anchorHead.anchor;
            } else if (alignRule.first == AlignDirection::RIGHT) {
                anchor = horizontalChains_[chainName].anchorTail.anchor;
            }
        }
        if (IsNodeInVerticalChain(nodeName, chainName)) {
            if (alignRule.first == AlignDirection::TOP) {
                anchor = verticalChains_[chainName].anchorHead.anchor;
            } else if (alignRule.first == AlignDirection::BOTTOM) {
                anchor = verticalChains_[chainName].anchorTail.anchor;
            }
        }

        if (IsBarrier(anchor)) {
            anchorSet.insert(anchor);
            continue;
        }

        if (IsAnchorContainer(anchor) || IsGuideline(anchor) || idNodeMap_.find(anchor) == idNodeMap_.end()) {
            continue;
        }
        anchorSet.insert(anchor);
    }
}

void RelativeContainerLayoutAlgorithm::UpdateDegreeMapWithBarrier(std::queue<std::string>& layoutQueue)
{
    if (barriers_.empty()) {
        return;
    }
    for (const auto& barrier : barriers_) {
        std::set<std::string> anchorSet;
        for (const auto& nodeName : barrier.second.second) {
            if (IsBarrier(nodeName)) {
                anchorSet.insert(nodeName);
                continue;
            }
            if (IsGuideline(nodeName) || idNodeMap_.find(nodeName) == idNodeMap_.end()) {
                continue;
            }
            anchorSet.insert(nodeName);
        }
        incomingDegreeMap_[barrier.first] = anchorSet.size();
        if (incomingDegreeMap_[barrier.first] == 0) {
            layoutQueue.push(barrier.first);
        }
    }
}

bool RelativeContainerLayoutAlgorithm::PreTopologicalLoopDetection(LayoutWrapper* layoutWrapper)
{
    std::queue<std::string> visitedNode;
    std::queue<std::string> layoutQueue;

    for (const auto& mapItem : idNodeMap_) {
        auto childWrapper = mapItem.second.layoutWrapper;
        auto childHostNode = childWrapper->GetHostNode();
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!flexItem || !flexItem->HasAlignRules()) {
            visitedNode.push(mapItem.first);
            layoutQueue.push(mapItem.second.id);
            continue;
        }
        std::set<std::string> anchorSet;
        PreTopologicalLoopDetectionGetAnchorSet(mapItem.first, flexItem->GetAlignRulesValue(), anchorSet);
        incomingDegreeMap_[mapItem.second.id] = anchorSet.size();
        if (incomingDegreeMap_[mapItem.second.id] == 0) {
            layoutQueue.push(mapItem.second.id);
        }
    }

    UpdateDegreeMapWithBarrier(layoutQueue);

    std::unordered_map<std::string, uint32_t> incomingDegreeMapCopy;
    incomingDegreeMapCopy.insert(incomingDegreeMap_.begin(), incomingDegreeMap_.end());
    while (!layoutQueue.empty()) {
        auto currentNodeInspectorId = layoutQueue.front();
        layoutQueue.pop();
        auto reliedSet = reliedOnMap_[currentNodeInspectorId];
        for (const auto& node : reliedSet) {
            auto it = incomingDegreeMapCopy.find(node);
            if (it == incomingDegreeMapCopy.end() || IsAnchorContainer(node)) {
                continue;
            }
            it->second -= 1;
            if (it->second == 0) {
                layoutQueue.push(node);
            }
        }
        incomingDegreeMapCopy.erase(currentNodeInspectorId);
        visitedNode.push(currentNodeInspectorId);
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern<RelativeContainerPattern>();
    CHECK_NULL_RETURN(pattern, false);
    if (SystemProperties::GetDebugEnabled()) {
        pattern->SetLoopDependentNodes(RelativeContainerPattern::LoopDependentNodesToString(incomingDegreeMapCopy));
    }
    return incomingDegreeMapCopy.empty();
}

void RelativeContainerLayoutAlgorithm::TopologicalSort(std::list<std::string>& renderList)
{
    std::queue<std::string> layoutQueue;
    for (const auto& mapItem : idNodeMap_) {
        auto childWrapper = mapItem.second.layoutWrapper;
        auto childHostNode = childWrapper->GetHostNode();
        const auto& flexItem = childWrapper->GetLayoutProperty()->GetFlexItemProperty();
        if (!flexItem || incomingDegreeMap_[mapItem.second.id] == 0) {
            layoutQueue.push(mapItem.second.id);
        }
    }
    while (!layoutQueue.empty()) {
        auto currentNodeInspectorId = layoutQueue.front();
        layoutQueue.pop();
        // reduce incoming degree of nodes relied on currentNode
        auto reliedList = reliedOnMap_[currentNodeInspectorId];
        for (const auto& node : reliedList) {
            auto it = incomingDegreeMap_.find(node);
            if (it == incomingDegreeMap_.end() || IsAnchorContainer(node)) {
                continue;
            }
            it->second -= 1;
            if (it->second == 0) {
                layoutQueue.push(node);
            }
        }
        renderList.emplace_back(currentNodeInspectorId);
    }
}

void RelativeContainerLayoutAlgorithm::CalcSizeParam(LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    std::string chainName;
    auto it = idNodeMap_.find(nodeName);
    if (it == idNodeMap_.end()) {
        return;
    }
    auto childWrapper = it->second.layoutWrapper;
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    CHECK_NULL_VOID(childWrapper->GetLayoutProperty()->GetFlexItemProperty());
    CHECK_NULL_VOID(childWrapper->GetLayoutProperty()->GetFlexItemProperty()->HasAlignRules());
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(relativeContainerLayoutProperty);
    auto childConstraint = relativeContainerLayoutProperty->CreateChildConstraint();
    auto alignRules = childWrapper->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRulesValue();
    const auto& calcConstraint = childLayoutProperty->GetCalcLayoutConstraint();
    bool horizontalHasIdealSize = false;
    bool verticalHasIdealSize = false;
    if (calcConstraint && calcConstraint->selfIdealSize.has_value() &&
        calcConstraint->selfIdealSize.value().Width().has_value()) {
        horizontalHasIdealSize = true;
    }
    if (calcConstraint && calcConstraint->selfIdealSize.has_value() &&
        calcConstraint->selfIdealSize.value().Height().has_value()) {
        verticalHasIdealSize = true;
    }
    horizontalHasIdealSize = horizontalHasIdealSize && versionGreatorOrEqualToEleven_;
    verticalHasIdealSize = verticalHasIdealSize && versionGreatorOrEqualToEleven_;
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    std::optional<float> childIdealWidth;
    std::optional<float> childIdealHeight;

    for (const auto& alignRule : alignRules) {
        if (!IsAnchorLegal(alignRule.second.anchor)) {
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE) {
            if (!childFlexItemProperty->GetTwoHorizontalDirectionAligned()) {
                CalcHorizontalLayoutParam(alignRule.first, alignRule.second, layoutWrapper, nodeName);
            }
        } else {
            if (!childFlexItemProperty->GetTwoVerticalDirectionAligned()) {
                CalcVerticalLayoutParam(alignRule.first, alignRule.second, layoutWrapper, nodeName);
            }
        }
    }
    if (childFlexItemProperty->GetTwoHorizontalDirectionAligned()) {
        auto checkAlign = AlignDirection::MIDDLE;
        if (childFlexItemProperty->GetAligned(checkAlign)) {
            auto middleValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::LEFT;
            if (childFlexItemProperty->GetAligned(checkAlign)) {
                childIdealWidth = 2.0f * std::max(middleValue - childFlexItemProperty->GetAlignValue(checkAlign), 0.0f);
            } else {
                checkAlign = AlignDirection::RIGHT;
                childIdealWidth = 2.0f * std::max(childFlexItemProperty->GetAlignValue(checkAlign) - middleValue, 0.0f);
            }
        } else {
            childIdealWidth = std::max(childFlexItemProperty->GetAlignValue(AlignDirection::RIGHT) -
                                           childFlexItemProperty->GetAlignValue(AlignDirection::LEFT),
                0.0f);
        }
        if (childIdealWidth.has_value() && LessOrEqual(childIdealWidth.value(), 0.0f) &&
            !IsNodeInHorizontalChain(nodeName, chainName)) {
            childConstraint.selfIdealSize.SetWidth(0.0f);
            childConstraint.selfIdealSize.SetHeight(0.0f);
            childWrapper->Measure(childConstraint);
            RecordSizeInChain(nodeName);
            return;
        }
    }
    if (childFlexItemProperty->GetTwoVerticalDirectionAligned()) {
        auto checkAlign = AlignDirection::CENTER;
        if (childFlexItemProperty->GetAligned(checkAlign)) {
            auto centerValue = childFlexItemProperty->GetAlignValue(checkAlign);
            checkAlign = AlignDirection::TOP;
            if (childFlexItemProperty->GetAligned(checkAlign)) {
                childIdealHeight =
                    2.0f * std::max(centerValue - childFlexItemProperty->GetAlignValue(checkAlign), 0.0f);
            } else {
                checkAlign = AlignDirection::BOTTOM;
                childIdealHeight =
                    2.0f * std::max(childFlexItemProperty->GetAlignValue(checkAlign) - centerValue, 0.0f);
            }
        } else {
            childIdealHeight = std::max(childFlexItemProperty->GetAlignValue(AlignDirection::BOTTOM) -
                                            childFlexItemProperty->GetAlignValue(AlignDirection::TOP),
                0.0f);
        }
        if (childIdealHeight.has_value() && LessOrEqual(childIdealHeight.value(), 0.0f) &&
            !IsNodeInVerticalChain(nodeName, chainName)) {
            childConstraint.selfIdealSize.SetWidth(0.0f);
            childConstraint.selfIdealSize.SetHeight(0.0f);
            childWrapper->Measure(childConstraint);
            RecordSizeInChain(nodeName);
            return;
        }
    }

    // for api 11 or larger, alignRules will not effect child component size as described in doc
    if (horizontalHasIdealSize && verticalHasIdealSize) {
        childWrapper->Measure(childConstraint);
        RecordSizeInChain(nodeName);
        return;
    }

    if (childIdealWidth.has_value() && !horizontalHasIdealSize && !IsNodeInHorizontalChain(nodeName, chainName)) {
        childConstraint.selfIdealSize.SetWidth(childIdealWidth.value());
    }
    if (childIdealHeight.has_value() && !verticalHasIdealSize && !IsNodeInVerticalChain(nodeName, chainName)) {
        childConstraint.selfIdealSize.SetHeight(childIdealHeight.value());
    }
    childWrapper->Measure(childConstraint);
    RecordSizeInChain(nodeName);
}

void RelativeContainerLayoutAlgorithm::CalcOffsetParam(LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
    auto alignRules = childWrapper->GetLayoutProperty()->GetFlexItemProperty()->GetAlignRulesValue();
    float offsetX = 0.0f;
    bool offsetXCalculated = false;
    float offsetY = 0.0f;
    bool offsetYCalculated = false;
    std::string chainName;
    if (IsNodeInHorizontalChain(nodeName, chainName)) {
        if (CalcOffsetInChain(chainName, LineDirection::HORIZONTAL)) {
            offsetX = recordOffsetMap_[nodeName].GetX();
        }
        offsetXCalculated = true;
    }
    if (IsNodeInVerticalChain(nodeName, chainName)) {
        if (CalcOffsetInChain(chainName, LineDirection::VERTICAL)) {
            offsetY = recordOffsetMap_[nodeName].GetY();
        }
        offsetYCalculated = true;
    }

    for (const auto& alignRule : alignRules) {
        if (!IsAnchorLegal(alignRule.second.anchor)) {
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE) {
            if (!offsetXCalculated) {
                offsetX = CalcHorizontalOffset(
                    alignRule.first, alignRule.second, containerSizeWithoutPaddingBorder_.Width(), nodeName);
                offsetXCalculated = true;
            }
        } else {
            if (!offsetYCalculated) {
                offsetY = CalcVerticalOffset(
                    alignRule.first, alignRule.second, containerSizeWithoutPaddingBorder_.Height(), nodeName);
                offsetYCalculated = true;
            }
        }
    }
    recordOffsetMap_[nodeName] = OffsetF(offsetX, offsetY) + CalcBias(nodeName);
}

bool RelativeContainerLayoutAlgorithm::IsValidBias(float bias)
{
    return GreatOrEqual(bias, 0.0f);
}

void RelativeContainerLayoutAlgorithm::CalcBiasTowDirection(
    std::pair<TwoAlignedValues, TwoAlignedValues>& alignedValuesOnTwoDirections, ChildIdealSize& childIdealSize,
    BiasPair& biasPair, float& horizontalOffset, float& verticalOffset)
{
    auto horizontalValues = alignedValuesOnTwoDirections.first;
    auto verticalValues = alignedValuesOnTwoDirections.second;
    auto biasX = biasPair.first;
    auto biasY = biasPair.second;
    if (horizontalValues.first.has_value() && horizontalValues.second.has_value() && childIdealSize.first.has_value()) {
        auto alignDiff = std::abs(horizontalValues.first.value() - horizontalValues.second.value());
        horizontalOffset = (alignDiff - childIdealSize.first.value()) * (IsValidBias(biasX) ? biasX : DEFAULT_BIAS);
    }
    if (verticalValues.first.has_value() && verticalValues.second.has_value() && childIdealSize.second.has_value()) {
        auto alignDiff = std::abs(verticalValues.first.value() - verticalValues.second.value());
        verticalOffset = (alignDiff - childIdealSize.second.value()) * (IsValidBias(biasY) ? biasY : DEFAULT_BIAS);
    }
}

OffsetF RelativeContainerLayoutAlgorithm::CalcBias(const std::string& nodeName)
{
    OffsetF emptyBiasOffset;
    std::string chainName;
    CHECK_NULL_RETURN(versionGreatorOrEqualToEleven_, emptyBiasOffset);
    if (IsNodeInHorizontalChain(nodeName, chainName) && IsNodeInVerticalChain(nodeName, chainName)) {
        return emptyBiasOffset;
    }
    auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
    auto layoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, emptyBiasOffset);
    const auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
    CHECK_NULL_RETURN(flexItemProperty, emptyBiasOffset);
    CHECK_NULL_RETURN(flexItemProperty->HasBias(), emptyBiasOffset);
    auto biasPair = flexItemProperty->GetBiasValue();
    CHECK_NULL_RETURN(flexItemProperty->HasAlignRules(), emptyBiasOffset);
    auto alignRules = flexItemProperty->GetAlignRulesValue();
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ChildIdealSize childIdealSize;
    if (calcLayoutConstraint && calcLayoutConstraint->selfIdealSize.has_value() &&
        calcLayoutConstraint->selfIdealSize.value().Width().has_value()) {
        childIdealSize.first = childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    }

    if (calcLayoutConstraint && calcLayoutConstraint->selfIdealSize.has_value() &&
        calcLayoutConstraint->selfIdealSize.value().Height().has_value()) {
        childIdealSize.second = childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    }
    if (!childIdealSize.first.has_value() && !childIdealSize.second.has_value()) {
        return OffsetF(0.0f, 0.0f);
    }
    auto alignedValuesOnTwoDirections = GetFirstTwoAlignValues(childWrapper, flexItemProperty, childIdealSize);
    auto horizontalOffset = 0.0f;
    auto verticalOffset = 0.0f;
    CalcBiasTowDirection(alignedValuesOnTwoDirections, childIdealSize, biasPair, horizontalOffset, verticalOffset);
    horizontalOffset = (IsNodeInHorizontalChain(nodeName, chainName)) ? 0.0f : horizontalOffset;
    verticalOffset = ((IsNodeInVerticalChain(nodeName, chainName))) ? 0.0f : verticalOffset;
    return OffsetF(horizontalOffset, verticalOffset);
}

std::pair<TwoAlignedValues, TwoAlignedValues> RelativeContainerLayoutAlgorithm::GetFirstTwoAlignValues(
    const RefPtr<LayoutWrapper>& childWrapper, const std::unique_ptr<FlexItemProperty>& flexItemProperty,
    const ChildIdealSize& childIdealSize)
{
    CHECK_NULL_RETURN(flexItemProperty, {});
    CHECK_NULL_RETURN(flexItemProperty->HasAlignRules(), {});
    auto alignRules = flexItemProperty->GetAlignRulesValue();
    TwoAlignedValues horizontalValues;
    TwoAlignedValues verticalValues;
    for (const auto& alignRule : alignRules) {
        bool horizontalCheckTwoSidesAligned = horizontalValues.first.has_value() && horizontalValues.second.has_value();
        bool verticalCheckTwoSidesAligned = verticalValues.second.has_value() && verticalValues.second.has_value();
        if (horizontalCheckTwoSidesAligned && verticalCheckTwoSidesAligned) {
            break;
        }
        if (!IsAnchorLegal(alignRule.second.anchor)) {
            continue;
        }
        if (static_cast<uint32_t>(alignRule.first) < HORIZONTAL_DIRECTION_RANGE && !horizontalCheckTwoSidesAligned &&
            childIdealSize.first.has_value()) {
            UpdateTwoAlignValues(horizontalValues, alignRule.second, LineDirection::HORIZONTAL);
        } else if (static_cast<uint32_t>(alignRule.first) >= HORIZONTAL_DIRECTION_RANGE &&
                   !verticalCheckTwoSidesAligned && childIdealSize.second.has_value()) {
            UpdateTwoAlignValues(verticalValues, alignRule.second, LineDirection::VERTICAL);
        }
    }
    return { horizontalValues, verticalValues };
}

void RelativeContainerLayoutAlgorithm::CalcHorizontalLayoutParam(AlignDirection alignDirection,
    const AlignRule& alignRule, LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto it = idNodeMap_.find(nodeName);
    if (it == idNodeMap_.end()) {
        return;
    }
    auto childWrapper = it->second.layoutWrapper;
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    if (IsGuideline(alignRule.anchor)) {
        if (guidelines_[alignRule.anchor].first == LineDirection::VERTICAL) {
            childFlexItemProperty->SetAlignValue(alignDirection, recordOffsetMap_[alignRule.anchor].GetX());
        } else {
            childFlexItemProperty->SetAlignValue(alignDirection, 0.0f);
        }
        return;
    }

    if (IsBarrier(alignRule.anchor)) {
        if (barriers_[alignRule.anchor].first == BarrierDirection::LEFT ||
            barriers_[alignRule.anchor].first == BarrierDirection::RIGHT) {
            childFlexItemProperty->SetAlignValue(alignDirection, recordOffsetMap_[alignRule.anchor].GetX());
        } else {
            childFlexItemProperty->SetAlignValue(alignDirection, 0.0f);
        }
        return;
    }

    switch (alignRule.horizontal) {
        case HorizontalAlign::START:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX());
            break;
        case HorizontalAlign::CENTER:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? containerSizeWithoutPaddingBorder_.Width() * HALF_MULTIPLY
                    : idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width() *
                              HALF_MULTIPLY +
                          recordOffsetMap_[alignRule.anchor].GetX());
            break;
        case HorizontalAlign::END:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? containerSizeWithoutPaddingBorder_.Width()
                    : idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width() +
                          recordOffsetMap_[alignRule.anchor].GetX());
            break;
        default:
            break;
    }
}

void RelativeContainerLayoutAlgorithm::CalcVerticalLayoutParam(AlignDirection alignDirection,
    const AlignRule& alignRule, LayoutWrapper* layoutWrapper, const std::string& nodeName)
{
    auto it = idNodeMap_.find(nodeName);
    if (it == idNodeMap_.end()) {
        return;
    }
    auto childWrapper = it->second.layoutWrapper;
    auto childLayoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    if (IsGuideline(alignRule.anchor)) {
        if (guidelines_[alignRule.anchor].first == LineDirection::HORIZONTAL) {
            childFlexItemProperty->SetAlignValue(alignDirection, recordOffsetMap_[alignRule.anchor].GetY());
        } else {
            childFlexItemProperty->SetAlignValue(alignDirection, 0.0f);
        }
        return;
    }

    if (IsBarrier(alignRule.anchor)) {
        if (barriers_[alignRule.anchor].first == BarrierDirection::TOP ||
            barriers_[alignRule.anchor].first == BarrierDirection::BOTTOM) {
            childFlexItemProperty->SetAlignValue(alignDirection, recordOffsetMap_[alignRule.anchor].GetY());
        } else {
            childFlexItemProperty->SetAlignValue(alignDirection, 0.0f);
        }
        return;
    }

    switch (alignRule.vertical) {
        case VerticalAlign::TOP:
            childFlexItemProperty->SetAlignValue(
                alignDirection, IsAnchorContainer(alignRule.anchor) ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY());
            break;
        case VerticalAlign::CENTER:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? containerSizeWithoutPaddingBorder_.Height() * HALF_MULTIPLY
                    : idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Height() *
                              HALF_MULTIPLY +
                          recordOffsetMap_[alignRule.anchor].GetY());
            break;
        case VerticalAlign::BOTTOM:
            childFlexItemProperty->SetAlignValue(alignDirection,
                IsAnchorContainer(alignRule.anchor)
                    ? containerSizeWithoutPaddingBorder_.Height()
                    : idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Height() +
                          recordOffsetMap_[alignRule.anchor].GetY());
            break;
        default:
            break;
    }
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffsetAlignLeft(
    const HorizontalAlign& alignRule, float& anchorWidth)
{
    float offsetX = 0.0f;
    switch (alignRule) {
        case HorizontalAlign::START:
            offsetX = 0.0f;
            break;
        case HorizontalAlign::CENTER:
            offsetX = anchorWidth * HALF_MULTIPLY;
            break;
        case HorizontalAlign::END:
            offsetX = anchorWidth;
            break;
        default:
            break;
    }
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffsetAlignMiddle(
    const HorizontalAlign& alignRule, float& anchorWidth, float& flexItemWidth)
{
    float offsetX = 0.0f;
    switch (alignRule) {
        case HorizontalAlign::START:
            offsetX = (-1) * flexItemWidth * HALF_MULTIPLY;
            break;
        case HorizontalAlign::CENTER:
            offsetX = (anchorWidth - flexItemWidth) * HALF_MULTIPLY;
            break;
        case HorizontalAlign::END:
            offsetX = anchorWidth - flexItemWidth * HALF_MULTIPLY;
            break;
        default:
            break;
    }
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffsetAlignRight(
    const HorizontalAlign& alignRule, float& anchorWidth, float& flexItemWidth)
{
    float offsetX = 0.0f;
    switch (alignRule) {
        case HorizontalAlign::START:
            offsetX = (-1) * flexItemWidth;
            break;
        case HorizontalAlign::CENTER:
            offsetX = anchorWidth * HALF_MULTIPLY - flexItemWidth;
            break;
        case HorizontalAlign::END:
            offsetX = anchorWidth - flexItemWidth;
            break;
        default:
            break;
    }
    return offsetX;
}

bool RelativeContainerLayoutAlgorithm::IsGuidelineOrBarrier(const std::string& id)
{
    return IsGuideline(id) || IsBarrier(id);
}

std::optional<float> RelativeContainerLayoutAlgorithm::GetOriginMarginLeft(
    TextDirection textDirection, const std::unique_ptr<MarginPropertyF>& marginProp)
{
    CHECK_NULL_RETURN(marginProp, 0);
    return textDirection != TextDirection::RTL ? marginProp->left : marginProp->right;
}

float RelativeContainerLayoutAlgorithm::CalcHorizontalOffset(
    AlignDirection alignDirection, const AlignRule& alignRule, float containerWidth, const std::string& nodeName)
{
    float offsetX = 0.0f;
    CHECK_NULL_RETURN(idNodeMap_.find(nodeName) != idNodeMap_.end(), offsetX);
    auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
    bool anchorIsContainer = IsAnchorContainer(alignRule.anchor);
    float flexItemWidth = childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    float anchorWidth = CalcAnchorWidth(anchorIsContainer, containerWidth, alignRule.anchor);
    std::optional<float> marginLeft;
    if (!anchorIsContainer && !IsGuidelineOrBarrier(alignRule.anchor)) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor].layoutWrapper;
        auto textDirection = anchorWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
        marginLeft = GetOriginMarginLeft(textDirection, anchorWrapper->GetGeometryNode()->GetMargin());
    }
    switch (alignDirection) {
        case AlignDirection::LEFT:
            offsetX = CalcHorizontalOffsetAlignLeft(alignRule.horizontal, anchorWidth);
            break;
        case AlignDirection::MIDDLE:
            offsetX = CalcHorizontalOffsetAlignMiddle(alignRule.horizontal, anchorWidth, flexItemWidth);
            break;
        case AlignDirection::RIGHT:
            offsetX = CalcHorizontalOffsetAlignRight(alignRule.horizontal, anchorWidth, flexItemWidth);
            break;
        default:
            break;
    }

    if (!versionGreatorOrEqualToEleven_) {
        offsetX += anchorIsContainer ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX();
    } else {
        offsetX += anchorIsContainer ? 0.0f : recordOffsetMap_[alignRule.anchor].GetX() + marginLeft.value_or(0);
    }
    return offsetX;
}

float RelativeContainerLayoutAlgorithm::CalcAnchorWidth(
    bool anchorIsContainer, float containerWidth, const std::string& anchor)
{
    if (!versionGreatorOrEqualToEleven_) {
        return anchorIsContainer
                          ? containerWidth
                          : idNodeMap_[anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    }
    if (IsGuidelineOrBarrier(anchor)) {
        return 0;
    } else if (anchorIsContainer) {
        return containerWidth;
    }
    return idNodeMap_[anchor].layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffsetAlignTop(const VerticalAlign& alignRule, float& anchorHeight)
{
    float offsetY = 0.0f;
    switch (alignRule) {
        case VerticalAlign::TOP:
            offsetY = 0.0f;
            break;
        case VerticalAlign::CENTER:
            offsetY = anchorHeight * HALF_MULTIPLY;
            break;
        case VerticalAlign::BOTTOM:
            offsetY = anchorHeight;
            break;
        default:
            break;
    }
    return offsetY;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffsetAlignCenter(
    const VerticalAlign& alignRule, float& anchorHeight, float& flexItemHeight)
{
    float offsetY = 0.0f;
    switch (alignRule) {
        case VerticalAlign::TOP:
            offsetY = (-1) * flexItemHeight * HALF_MULTIPLY;
            break;
        case VerticalAlign::CENTER:
            offsetY = (anchorHeight - flexItemHeight) * HALF_MULTIPLY;
            break;
        case VerticalAlign::BOTTOM:
            offsetY = anchorHeight - flexItemHeight * HALF_MULTIPLY;
            break;
        default:
            break;
    }
    return offsetY;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffsetAlignBottom(
    const VerticalAlign& alignRule, float& anchorHeight, float& flexItemHeight)
{
    float offsetY = 0.0f;
    switch (alignRule) {
        case VerticalAlign::TOP:
            offsetY = (-1) * flexItemHeight;
            break;
        case VerticalAlign::CENTER:
            offsetY = anchorHeight * HALF_MULTIPLY - flexItemHeight;
            break;
        case VerticalAlign::BOTTOM:
            offsetY = anchorHeight - flexItemHeight;
            break;
        default:
            break;
    }
    return offsetY;
}

float RelativeContainerLayoutAlgorithm::CalcVerticalOffset(
    AlignDirection alignDirection, const AlignRule& alignRule, float containerHeight, const std::string& nodeName)
{
    float offsetY = 0.0f;
    CHECK_NULL_RETURN(idNodeMap_.find(nodeName) != idNodeMap_.end(), offsetY);
    auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
    bool anchorIsContainer = IsAnchorContainer(alignRule.anchor);
    float flexItemHeight = childWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    float anchorHeight;
    if (!versionGreatorOrEqualToEleven_) {
        anchorHeight =
            anchorIsContainer
                ? containerHeight
                : idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    } else {
        if (IsGuidelineOrBarrier(alignRule.anchor)) {
            anchorHeight = 0;
        } else if (anchorIsContainer) {
            anchorHeight = containerHeight;
        } else {
            anchorHeight = idNodeMap_[alignRule.anchor].layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
        }
    }
    std::optional<float> marginTop;
    if (!anchorIsContainer && !IsGuidelineOrBarrier(alignRule.anchor)) {
        auto anchorWrapper = idNodeMap_[alignRule.anchor].layoutWrapper;
        if (anchorWrapper->GetGeometryNode()->GetMargin()) {
            marginTop = anchorWrapper->GetGeometryNode()->GetMargin()->top;
        }
    }
    switch (alignDirection) {
        case AlignDirection::TOP:
            offsetY = CalcVerticalOffsetAlignTop(alignRule.vertical, anchorHeight);
            break;
        case AlignDirection::CENTER:
            offsetY = CalcVerticalOffsetAlignCenter(alignRule.vertical, anchorHeight, flexItemHeight);
            break;
        case AlignDirection::BOTTOM:
            offsetY = CalcVerticalOffsetAlignBottom(alignRule.vertical, anchorHeight, flexItemHeight);
            break;
        default:
            break;
    }
    if (!versionGreatorOrEqualToEleven_) {
        offsetY += anchorIsContainer ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY();
    } else {
        offsetY += anchorIsContainer ? 0.0f : recordOffsetMap_[alignRule.anchor].GetY() + marginTop.value_or(0);
    }
    return offsetY;
}

bool RelativeContainerLayoutAlgorithm::IsAnchorLegal(const std::string& anchorName)
{
    if (!IsAnchorContainer(anchorName) && !IsGuidelineOrBarrier(anchorName) &&
        idNodeMap_.find(anchorName) == idNodeMap_.end()) {
        return false;
    }
    return true;
}

BarrierDirection RelativeContainerLayoutAlgorithm::BarrierDirectionRtl(BarrierDirection barrierDirection)
{
    auto barrierDirectionRtl = barrierDirection;
    if (barrierDirection == BarrierDirection::START) {
        barrierDirectionRtl = BarrierDirection::LEFT;
    } else if (barrierDirection == BarrierDirection::END) {
        barrierDirectionRtl = BarrierDirection::RIGHT;
    }
    return barrierDirectionRtl;
}

void RelativeContainerLayoutAlgorithm::AdjustOffsetRtl(LayoutWrapper* layoutWrapper)
{
    auto textDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    if (textDirection != TextDirection::RTL) {
        return;
    }
    auto containerWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    for (const auto& nodeName : renderList_) {
        auto it = idNodeMap_.find(nodeName);
        if (it == idNodeMap_.end()) {
            continue;
        }
        auto childWrapper = idNodeMap_[nodeName].layoutWrapper;
        if (!childWrapper) {
            continue;
        }
        auto oldNodeX = recordOffsetMap_[nodeName].GetX();
        auto oldNodeY = recordOffsetMap_[nodeName].GetY();
        auto nodeWidth = childWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
        auto newNodeX = containerWidth - nodeWidth - oldNodeX - padding_.Width();
        recordOffsetMap_[nodeName] = OffsetF(newNodeX, oldNodeY);
    }
}
} // namespace OHOS::Ace::NG
