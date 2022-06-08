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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_ELEMENT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_ELEMENT_NODE_H

#include <list>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/pipeline_ng/ui_node_id.h"

namespace OHOS::Ace::NG {
class PipelineContext;
// If no insertion location is specified, new child will be added to the end of children list by default.
constexpr int32_t DEFAULT_ELEMENT_SLOT = -1;
// ElementNode is the key class in the UI framework, which presents a basic logic
// unit to construct a view hierarchy.
// There are two types inherited element: FrameNode and ComposedNode.
class ACE_EXPORT ElementNode : public UiNodeId {
    DECLARE_ACE_TYPE(ElementNode, UiNodeId);

public:
    explicit ElementNode(const std::string& tag) : tag_(tag) {}
    ~ElementNode() override;

    void AddChild(const RefPtr<ElementNode>& child, int32_t slot = DEFAULT_ELEMENT_SLOT);
    void RemoveChild(const RefPtr<ElementNode>& child);
    RefPtr<ElementNode> GetChildBySlot(int32_t slot);

    // first build process.
    void MountToParent(const RefPtr<ElementNode>& parent, int32_t slot = DEFAULT_ELEMENT_SLOT);

    void SetPipelineContext(const RefPtr<PipelineContext>& context);

    void AttachContextrecursively(const RefPtr<PipelineContext>& context);

    const std::list<RefPtr<ElementNode>>& GetElementChildren() const;

    const WeakPtr<PipelineContext>& GetContext() const
    {
        return context_;
    }

    void SetSlot(int32_t slot)
    {
        slot_ = slot;
    }

    int32_t GetSlot() const
    {
        return slot_;
    }

    virtual int32_t CountRenderNode() const = 0;

    const WeakPtr<ElementNode>& GetElementParent() const
    {
        return elementParent_;
    }

    void SetElementParent(const WeakPtr<ElementNode>& parent)
    {
        elementParent_ = parent;
    }

    inline RefPtr<ElementNode> GetFirstElementChild() const
    {
        if (elementChildren_.empty()) {
            return nullptr;
        }
        return elementChildren_.front();
    }

    inline RefPtr<ElementNode> GetLastElementChild() const
    {
        if (elementChildren_.empty()) {
            return nullptr;
        }
        return elementChildren_.back();
    }

    enum class ElementType {
        BASE_ELEMENT,
        RENDER_ELEMENT,
        COMPOSED_ELEMENT,
    };

    ElementType GetType() const
    {
        return type_;
    }

    const std::string& GetTag() const
    {
        return tag_;
    }

    // dfx info.
    virtual void DumpTree(int32_t depth);

    void SetDepth(int32_t depth)
    {
        depth_ = depth;
        for (auto& child : elementChildren_) {
            child->SetDepth(depth_ + 1);
        }
        OnDepthUpdate();
    }

    int32_t GetDepth() const
    {
        return depth_;
    }

    // Called after mount to parent.
    virtual void OnMounted() {}

protected:
    // Added to parent.
    virtual void OnChildAdded(const RefPtr<ElementNode>& child) {}
    // Detached from element tree.
    virtual void OnDetached() {}

    virtual void OnContextAttached() {}

    // dump self info.
    virtual void DumpInfo() {}

    virtual void OnDepthUpdate() {}

    std::list<RefPtr<ElementNode>> elementChildren_;
    WeakPtr<PipelineContext> context_;
    WeakPtr<ElementNode> elementParent_;
    ElementType type_ = ElementType::BASE_ELEMENT;

private:
    void DetachChild(const RefPtr<ElementNode>& child);
    inline void DoUpdateChild(
        const RefPtr<ElementNode>& child, const RefPtr<ElementNode>& newchild, int32_t slot, int32_t renderSlot);

    std::string tag_ = "ElementNode";
    int32_t depth_ = 0;
    int32_t slot_ = DEFAULT_ELEMENT_SLOT;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_ELEMENT_NODE_H
