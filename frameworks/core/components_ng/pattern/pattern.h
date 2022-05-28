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
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_property.h"

namespace OHOS::Ace::NG {

// Pattern is the base class for different measure, layout and paint behavior.
class Pattern : public virtual AceType {
    DECLARE_ACE_TYPE(V2::Pattern, AceType);

public:
    Pattern() = default;
    ~Pattern() override = default;

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

    virtual void OnContextAttached() {}

    // Called to perform update before the render node base update operation.
    virtual void OnUpdateDone() {}

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

    virtual bool IsLayoutBoundary() const
    {
        return true;
    }

    virtual bool IsRenderBoundary() const
    {
        return true;
    }

    virtual void OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty) {}

protected:
    virtual void OnAttachToFrameNode() {}
    virtual void OnDetachFromFrameNode() {}

    WeakPtr<FrameNode> frameNode_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERN_H
