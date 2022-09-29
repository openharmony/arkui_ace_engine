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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H

#include <optional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
struct DirtySwapConfig {
    bool frameSizeChange = false;
    bool frameOffsetChange = false;
    bool contentSizeChange = false;
    bool contentOffsetChange = false;
    bool skipMeasure = false;
    bool skipLayout = false;
};

// Pattern is the base class for different measure, layout and paint behavior.
class Pattern : public virtual AceType {
    DECLARE_ACE_TYPE(Pattern, AceType);

public:
    Pattern() = default;
    ~Pattern() override = default;

    // atomic node is like button, image, custom node and so on.
    // In ets UI compiler, the atomic node does not Add Pop function, only have Create function.
    virtual bool IsAtomicNode() const
    {
        return true;
    }

    virtual std::optional<std::string> GetSurfaceNodeName() const
    {
        return std::nullopt;
    }

    void DetachFromFrameNode(FrameNode* frameNode)
    {
        OnDetachFromFrameNode(frameNode);
        frameNode_.Reset();
    }

    void AttachToFrameNode(const WeakPtr<FrameNode>& frameNode)
    {
        if (frameNode_ == frameNode) {
            return;
        }
        frameNode_ = frameNode;
        OnAttachToFrameNode();
    }

    virtual RefPtr<PaintProperty> CreatePaintProperty()
    {
        return MakeRefPtr<PaintProperty>();
    }

    virtual RefPtr<LayoutProperty> CreateLayoutProperty()
    {
        return MakeRefPtr<LayoutProperty>();
    }

    virtual RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm()
    {
        return MakeRefPtr<BoxLayoutAlgorithm>();
    }

    virtual RefPtr<NodePaintMethod> CreateNodePaintMethod()
    {
        return nullptr;
    }

    virtual RefPtr<EventHub> CreateEventHub()
    {
        return MakeRefPtr<EventHub>();
    }

    virtual void OnContextAttached() {}

    virtual void OnModifyDone() {}

    virtual void OnMountToParentDone() {}

    virtual bool IsRootPattern() const
    {
        return false;
    }

    virtual bool IsMeasureBoundary() const
    {
        return false;
    }

    virtual bool IsRenderBoundary() const
    {
        return true;
    }

    // TODO: for temp use, need to delete this.
    virtual bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& /*dirty*/, bool /*skipMeasure*/, bool /*skipLayout*/)
    {
        return false;
    }

    // Called on main thread to check if need rerender of the content.
    virtual bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& /*dirty*/, const DirtySwapConfig& /*changeConfig*/)
    {
        return false;
    }

    std::optional<SizeF> GetHostFrameSize() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetMarginFrameSize();
    }

    std::optional<OffsetF> GetHostFrameOffset() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetFrameOffset();
    }

    std::optional<OffsetF> GetHostFrameGlobalOffset() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetFrameOffset() + frameNode->GetGeometryNode()->GetParentGlobalOffset();
    }

    std::optional<SizeF> GetHostContentSize() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        const auto& content = frameNode->GetGeometryNode()->GetContent();
        if (!content) {
            return std::nullopt;
        }
        return content->GetRect().GetSize();
    }

    RefPtr<FrameNode> GetHost() const
    {
        return frameNode_.Upgrade();
    }

    template<typename T>
    RefPtr<T> GetLayoutProperty() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return DynamicCast<T>(host->GetLayoutProperty<T>());
    }

    template<typename T>
    RefPtr<T> GetPaintProperty() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return DynamicCast<T>(host->GetPaintProperty<T>());
    }

    template<typename T>
    RefPtr<T> GetEventHub() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        return DynamicCast<T>(host->GetEventHub<T>());
    }

    virtual void OnInActive() {}
    virtual void OnActive() {}

    // Called before frameNode CreateLayoutWrapper.
    virtual void BeforeCreateLayoutWrapper() {}
    // Called before frameNode CreatePaintWrapper.
    virtual void BeforeCreatePaintWrapper() {}

    virtual FocusType GetFocusType()
    {
        return FocusType::DISABLE;
    }
    virtual bool GetFocusable()
    {
        return false;
    }

protected:
    virtual void OnAttachToFrameNode() {}
    virtual void OnDetachFromFrameNode(FrameNode* frameNode) {}

private:
    WeakPtr<FrameNode> frameNode_;

    ACE_DISALLOW_COPY_AND_MOVE(Pattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H
