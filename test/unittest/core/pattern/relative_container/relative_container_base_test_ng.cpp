/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "relative_container_base_test_ng.h"

namespace OHOS::Ace::NG {
void RelativeContainerBaseTestNG::AddAlignRule(std::map<AlignDirection, AlignRule>& alignRules,
    const AlignDirection& direction, const std::string& id, const HorizontalAlign& horizontalRule)
{
    AlignRule alignRule = { .anchor = id, .horizontal = horizontalRule };
    alignRules[direction] = alignRule;
}

void RelativeContainerBaseTestNG::AddAlignRule(std::map<AlignDirection, AlignRule>& alignRules,
    const AlignDirection& direction, const std::string& id, const VerticalAlign& verticalRule)
{
    AlignRule alignRule = { .anchor = id, .vertical = verticalRule };
    alignRules[direction] = alignRule;
}

RefPtr<FrameNode> RelativeContainerBaseTestNG::CreateRelativeContainer(
    const std::function<void(RelativeContainerModelNG)>& callback)
{
    RelativeContainerModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

string RelativeContainerBaseTestNG::PrintReliedOnMap(
    unordered_map<string, set<string>>& reliedOnMap, const string& anchor)
{
    string res;
    auto iter = reliedOnMap.find(anchor);
    if (iter != reliedOnMap.end()) {
        res += "[";
        auto& reliedList = reliedOnMap[anchor];
        for (auto it = reliedList.begin(); it != reliedList.end(); ++it) {
            res += *it;
            if (std::next(it) != reliedList.end()) {
                res += ", ";
            }
        }
        res += "]";
    } else {
        res = "Doesn't exist";
    }
    return res;
}

void RelativeContainerBaseTestNG::PrepareMeasureChild(
    LayoutWrapper* layoutWrapper, RelativeContainerLayoutAlgorithm& layoutAlgorithm)
{
    layoutAlgorithm.Initialize(layoutWrapper);
    // create idNodeMap_
    layoutAlgorithm.CollectNodesById(layoutWrapper);
    // create reliedOnMap_
    layoutAlgorithm.GetDependencyRelationship();
    // create incomingDegreeMap_
    layoutAlgorithm.PreTopologicalLoopDetection(layoutWrapper);
    // create renderList_
    layoutAlgorithm.TopologicalSort(layoutAlgorithm.renderList_);
}

void RelativeContainerBaseTestNG::AddGuidelineStart(
    std::vector<GuidelineInfo>& guidelineInfos, std::string id, LineDirection direction, std::optional<Dimension> start)
{
    GuidelineInfo info = { .id = id, .direction = direction, .start = start };
    guidelineInfos.emplace_back(info);
};

void RelativeContainerBaseTestNG::AddGuidelineEnd(
    std::vector<GuidelineInfo>& guidelineInfos, std::string id, LineDirection direction, std::optional<Dimension> end)
{
    GuidelineInfo info = { .id = id, .direction = direction, .end = end };
    guidelineInfos.emplace_back(info);
};
} // namespace OHOS::Ace::NG
