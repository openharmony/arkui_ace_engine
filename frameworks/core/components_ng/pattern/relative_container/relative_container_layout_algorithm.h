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

constexpr int32_t DIRECTION_RANGE = 3;
class ACE_EXPORT RelativeContainerLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(RelativeContainerLayoutAlgorithm, LayoutAlgorithm);

public:
    RelativeContainerLayoutAlgorithm() = default;
    ~RelativeContainerLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void DetermineTopologicalOrder(LayoutWrapper* layoutWrapper);
    void CollectNodesById(LayoutWrapper* layoutWrapper);
    void GetDependencyRelationship();
    bool PreTopologicalLoopDetection();
    void TopologicalSort(std::list<std::string>& renderList);
    void CalcSizeParam(LayoutWrapper* layoutWrapper, const std::string& nodeName);
    void CalcOffsetParam(LayoutWrapper* layoutWrapper, const std::string& nodeName);
    void CalcHorizontalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
        LayoutWrapper* layoutWrapper, const std::string& nodeName);
    void CalcVerticalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
        LayoutWrapper* layoutWrapper, const std::string& nodeName);
    float CalcHorizontalOffset(
        AlignDirection alignDirection, const AlignRule& alignRule, float containerWidth, const std::string& nodeName);
    float CalcVerticalOffset(
        AlignDirection alignDirection, const AlignRule& alignRule, float containerHeight, const std::string& nodeName);

    std::list<std::string> renderList_;
    std::map<std::string, RefPtr<LayoutWrapper>> idNodeMap_;
    std::map<std::string, uint32_t> incomingDegreeMap_;
    std::map<std::string, std::set<std::string>> reliedOnMap_;
    std::map<std::string, OffsetF> recordOffsetMap_;
    PaddingPropertyF padding_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_ALGORITHM_H