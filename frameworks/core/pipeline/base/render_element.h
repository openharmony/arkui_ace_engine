/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RENDER_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RENDER_ELEMENT_H

#include "base/utils/macros.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

// RenderElement will have a RenderNode and displays in the screen.
class ACE_EXPORT RenderElement : public Element {
    DECLARE_ACE_TYPE(RenderElement, Element);

public:
    RenderElement();
    ~RenderElement() override;

    void Prepare(const WeakPtr<Element>& parent) override;
    void Update() override;
    void Detached() override;
    void Deactivate() override;

    RefPtr<RenderNode> GetRenderNode() const override
    {
        return renderNode_;
    }

    void SetRenderNode(RefPtr<RenderNode> renderNode)
    {
        if (renderNode && !renderNode_) {
            renderNode_ = renderNode;
        }
    }

    void SetAccessibilityNodeById(const ComposeId& id);

protected:
    virtual RefPtr<RenderNode> CreateRenderNode();
    virtual RefPtr<RenderNode> GetCachedRenderNode()
    {
        return nullptr;
    }
    void Apply(const RefPtr<Element>& child) override;

    RefPtr<RenderNode> renderNode_;

private:
    void SetAccessibilityNode(const WeakPtr<Element>& parent);
    void UpdateAccessibilityNode();

    ComposeId composeId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RENDER_ELEMENT_H
