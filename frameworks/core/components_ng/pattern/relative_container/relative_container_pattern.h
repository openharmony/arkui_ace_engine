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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_PATTERN_H

#include "base/log/dump_log.h"
#include "core/components_ng/base/distributed_ui.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_algorithm.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_property.h"

namespace OHOS::Ace::NG {

class RelativeContainerPattern : public Pattern {
    DECLARE_ACE_TYPE(RelativeContainerPattern, Pattern);

public:
    RelativeContainerPattern() = default;
    ~RelativeContainerPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<RelativeContainerLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RelativeContainerLayoutProperty>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsNeedPercent() const override
    {
        return true;
    }

    void SetTopologicalResult(const std::string& result)
    {
        topologicalResult_ = result;
    }

    void SetLoopDependentNodes(const std::string& result)
    {
        if (result.empty()) {
            loopDependentNodes_.reset();
            return;
        }
        loopDependentNodes_ = result;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return { true, true, ScopeType::PROJECT_AREA };
    }

    std::optional<std::list<std::string>>&& GetTopologicalResultCache()
    {
        return std::move(topologicalResultList_);
    }

    const std::optional<std::list<std::string>>& GetTopologicalResultCacheCopy()
    {
        return topologicalResultList_;
    }

    void SetTopologicalResultCache(std::list<std::string>&& cache)
    {
        topologicalResultList_ = std::move(cache);
    }

    std::optional<std::string> GetLoopDependentNodes()
    {
        return loopDependentNodes_;
    }

    static std::string TopoListToString(const std::list<std::string>& topoList)
    {
        std::string result = "[";
        for (const auto& nodeName : topoList) {
            result += nodeName + ",";
        }
        if (!topoList.empty()) {
            result = result.substr(0, result.length() - 1);
        }
        result += "]";
        return result;
    }

    static std::string LoopDependentNodesToString(
        const std::optional<std::unordered_map<std::string, uint32_t>>& incomingDegreeMapCopy)
    {
        std::string loopDependentNodes = "";
        if (!incomingDegreeMapCopy.has_value()) {
            return loopDependentNodes;
        }
        for (const auto& node : incomingDegreeMapCopy.value()) {
            loopDependentNodes += node.first + ",";
        }
        return loopDependentNodes;
    }

    void DumpInfo() override
    {
        DumpLog::GetInstance().AddDesc(std::string("topologicalResult:").append(topologicalResult_));
        if (loopDependentNodes_) {
            DumpLog::GetInstance().AddDesc(std::string("loopDependentNodes:").append(loopDependentNodes_.value()));
        }
    }

    bool GetChildAlignRulesChanged()
    {
        return childAlignRulesChanged_;
    }

    void SetChildAlignRulesChanged(bool changed)
    {
        childAlignRulesChanged_ = changed;
    }

    void BeforeCreateLayoutWrapper() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        for (const auto& child : host->GetAllChildrenWithBuild()) {
            auto childNode = AceType::DynamicCast<NG::FrameNode>(child);
            CHECK_NULL_CONTINUE(childNode);
            auto layoutProperty = childNode->GetLayoutProperty();
            CHECK_NULL_CONTINUE(layoutProperty);
            auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
            CHECK_NULL_CONTINUE(flexItemProperty);
            if (flexItemProperty->NeedMarkParentMeasure()) {
                // will be reset when relativeContainer parent measure finish
                childAlignRulesChanged_ = true;
                flexItemProperty->SetMarkParentMeasure(false);
            }
        }
    }

private:
    bool childAlignRulesChanged_ = true;
    std::string topologicalResult_;
    std::optional<std::string> loopDependentNodes_;
    std::optional<std::list<std::string>> topologicalResultList_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_PATTERN_H