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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RELATIVE_CONTAINER_RENDER_RELATIVE_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RELATIVE_CONTAINER_RENDER_RELATIVE_CONTAINER_H

#include <typeinfo>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/flex/flex_item_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {
using AlignRules = std::map<AlignDirection, AlignRule>;
using AlignRulesMap = std::map<std::string, AlignRules>;
class ACE_EXPORT RenderRelativeContainer : public RenderNode {
    DECLARE_ACE_TYPE(RenderRelativeContainer, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    AlignRulesMap GetAlignRulesMap() const
    {
        return alignRulesMap_;
    }

private:
    void CollectNodesById();
    void GetDependencyRelationship();
    bool PreTopologicalLoopDetection();
    void TopologicalSort(std::list<std::string>& renderList);

    void CalcHorizontalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
        const std::string& nodeName);
    void CalcVerticalLayoutParam(AlignDirection alignDirection, const AlignRule& alignRule,
        const std::string& nodeName);
    void CalcLayoutParam(const std::map<AlignDirection, AlignRule> alignRules, LayoutParam& itemLayout,
        const std::string& nodeName);

    double CalcHorizontalOffset(AlignDirection alignDirection, const AlignRule& alignRule,
        double containerWidth, const std::string& nodeName);
    double CalcVerticalOffset(AlignDirection alignDirection, const AlignRule& alignRule,
        double containerHeight, const std::string& nodeName);

    std::list<std::string> renderList_;
    std::map<std::string, RefPtr<RenderFlexItem>> idNodeMap_;
    std::map<std::string, uint32_t> incomingDegreeMap_;
    // list of nodes that relied on the key node represented by string
    std::map<std::string, std::set<std::string>> reliedOnMap_;
    std::list<std::string> orderedRenderList_;

    AlignRulesMap alignRulesMap_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RELATIVE_CONTAINER_RENDER_RELATIVE_CONTAINER_H
