/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_PATTERN_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class NodeContainerPattern : virtual public Pattern {
    DECLARE_ACE_TYPE(NodeContainerPattern, Pattern);

public:
    NodeContainerPattern() = default;
    ~NodeContainerPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearLayoutProperty>(true);
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<LinearLayoutAlgorithm>();
    }

    void RemakeNode();

    void BindController(std::function<void()>&& resetFunc)
    {
        resetFunc_ = std::move(resetFunc);
    }

    void ResetController() const
    {
        CHECK_NULL_VOID(resetFunc_);
        resetFunc_();
    }

    void SetMakeFunction(std::function<RefPtr<UINode>()>&& makeFunc)
    {
        makeFunc_ = std::move(makeFunc);
    }

    RefPtr<UINode> FireMakeFunction() const
    {
        CHECK_NULL_RETURN(makeFunc_, nullptr);
        return makeFunc_();
    }

    void SetOnResize(std::function<void(const SizeF& size)>&& resizeFunc)
    {
        resizeFunc_ = std::move(resizeFunc);
    }

    void FireOnResize(const SizeF& size) const
    {
        CHECK_NULL_VOID(resizeFunc_);
        resizeFunc_(size);
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
private:
    std::function<void()> resetFunc_;
    std::function<RefPtr<UINode>()> makeFunc_;
    std::function<void(const SizeF& size)> resizeFunc_;

    ACE_DISALLOW_COPY_AND_MOVE(NodeContainerPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_PATTERN_H
