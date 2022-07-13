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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_property.h"

namespace OHOS::Ace::NG {
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

    void DetachFromFrameNode()
    {
        frameNode_.Reset();
        OnDetachFromFrameNode();
    }

    void AttachToFrameNode(const WeakPtr<FrameNode>& frameNode)
    {
        if (frameNode_ == frameNode) {
            return;
        }
        frameNode_ = frameNode;
        OnAttachToFrameNode();
    }

    virtual RefPtr<RenderProperty> CreateRenderProperty()
    {
        return MakeRefPtr<RenderProperty>();
    }

    virtual RefPtr<LayoutProperty> CreateLayoutProperty()
    {
        return MakeRefPtr<LayoutProperty>();
    }

    virtual RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm()
    {
        return MakeRefPtr<BoxLayoutAlgorithm>();
    }

    virtual RenderWrapper::ContentPaintImpl CreateContentPaintImpl()
    {
        return nullptr;
    }

    virtual RefPtr<EventHub> CreateEventHub()
    {
        return MakeRefPtr<EventHub>();
    }

    virtual void OnContextAttached() {}

    virtual void OnModifyDone() {}

    virtual RefPtr<LayoutWrapper> AdjustChildLayoutWrapper(
        const RefPtr<LayoutWrapper>& self, const RefPtr<LayoutWrapper>& child)
    {
        return self;
    }

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

    // Called on main thread to check if need rerender of the content.
    virtual bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
    {
        return false;
    }

    std::optional<SizeF> GetHostFrameSize() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetFrameSize();
    }

    std::optional<OffsetF> GetHostFrameOffset() const
    {
        auto frameNode = frameNode_.Upgrade();
        if (!frameNode) {
            return std::nullopt;
        }
        return frameNode->GetGeometryNode()->GetFrameOffset();
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

    virtual void OnInActive() {}
    virtual void OnActive() {}

protected:
    virtual void OnAttachToFrameNode() {}
    virtual void OnDetachFromFrameNode() {}

    WeakPtr<FrameNode> frameNode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H
