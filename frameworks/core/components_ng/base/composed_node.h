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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_COMPOSED_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_COMPOSED_NODE_H

#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/element_node.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

// ComposedNode just maintain a child element may have render node.
class ACE_EXPORT ComposedNode : public ElementNode {
    DECLARE_ACE_TYPE(ComposedNode, ElementNode);

public:
    using RenderResult = std::pair<RefPtr<NG::ElementNode>, std::list<CancelableCallback<void()>>>;
    using RenderFunction = std::function<RenderResult()>;
    using AppearFunction = std::function<void()>;
    using UpdateJsViewFunction = std::function<void(WeakPtr<ComposedNode>)>;
    using ApplyFunction = std::function<void(const RefPtr<FrameNode>&)>;

    ComposedNode(const std::string& tag, std::string id);
    ~ComposedNode() override;

    const std::string& GetId() const
    {
        return id_;
    }

    void SetRenderFunction(RenderFunction&& func)
    {
        renderFunction_ = std::move(func);
    }

    void SetAppearFunction(AppearFunction&& func)
    {
        appearFunction_ = std::move(func);
    }

    void SetUpdateJsViewFunction(UpdateJsViewFunction&& func)
    {
        UpdateJsViewFunction_ = std::move(func);
    }

    bool HasRenderFunction()
    {
        return static_cast<bool>(renderFunction_);
    }

    // called by view in js thread
    void MarkNeedRebuild();

    // called by pipeline in js thread
    void Rebuild();

protected:
    void OnMounted() override;
    void OnChildAdded(const RefPtr<ElementNode>& child) override;
    void OnContextAttached() override;
    void DumpInfo() override;

    int32_t CountRenderNode() const override
    {
        return countRenderNode_;
    }

    std::string id_;
    std::string name_;

private:
    void BuildChildren(const RefPtr<ElementNode>& child);
    void FlushBuildTask(const RenderResult& renderResult);

    RenderFunction renderFunction_;
    AppearFunction appearFunction_;
    ApplyFunction applyFunction_;
    UpdateJsViewFunction UpdateJsViewFunction_;

    int32_t countRenderNode_ = -1;
    bool needRebuild_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_COMPOSED_NODE_H
