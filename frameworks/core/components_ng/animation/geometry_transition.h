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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_GEOMETRY_TRANSITION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_GEOMETRY_TRANSITION_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components/common/properties/animation_option.h"

namespace OHOS::Ace::NG {
class FrameNode;
class LayoutWrapper;
class LayoutProperty;

class GeometryTransition : public AceType {
    DECLARE_ACE_TYPE(GeometryTransition, AceType);

public:
    explicit GeometryTransition(const std::string& id,
        bool followWithoutTransition = false, bool doRegisterSharedTransition = true);
    ~GeometryTransition() override = default;

    bool IsNodeInAndActive(const WeakPtr<FrameNode>& frameNode) const;
    bool IsNodeOutAndActive(const WeakPtr<FrameNode>& frameNode) const;
    bool IsRunning(const WeakPtr<FrameNode>& frameNode) const;
    bool IsInAndOutEmpty() const;
    bool IsInAndOutValid() const;
    std::string ToString() const;
    std::string GetId() const
    {
        return id_;
    }
    
    bool GetFollowWithoutTransition() const
    {
        return followWithoutTransition_;
    }

    bool GetDoRegisterSharedTransition() const
    {
        return doRegisterSharedTransition_;
    }

    void Build(const WeakPtr<FrameNode>& frameNode, bool isNodeIn);
    bool Update(const WeakPtr<FrameNode>& which, const WeakPtr<FrameNode>& value);
    void OnReSync(const WeakPtr<FrameNode>& trigger = nullptr, const AnimationOption& option = AnimationOption());
    bool OnAdditionalLayout(const WeakPtr<FrameNode>& frameNode);
    bool OnFollowWithoutTransition(std::optional<bool> direction = std::nullopt);
    void WillLayout(const RefPtr<LayoutWrapper>& layoutWrapper);
    void DidLayout(const RefPtr<LayoutWrapper>& layoutWrapper);

private:
    enum class State {
        IDLE,
        ACTIVE,
        IDENTITY,
    };

    bool IsNodeInAndIdentity(const WeakPtr<FrameNode>& frameNode) const;
    void SwapInAndOut(bool condition);
    std::pair<RefPtr<FrameNode>, RefPtr<FrameNode>> GetMatchedPair(bool isNodeIn) const;
    void RecordOutNodeFrame();
    void MarkLayoutDirty(const RefPtr<FrameNode>& node, int32_t layoutPriority = 0);
    void ModifyLayoutConstraint(const RefPtr<LayoutWrapper>& layoutWrapper, bool isNodeIn);
    void SyncGeometry(bool isNodeIn);
    bool IsParent(const WeakPtr<FrameNode>& parent, const WeakPtr<FrameNode>& child) const;
    void RecordAnimationOption(const WeakPtr<FrameNode>& trigger, const AnimationOption& option);
    RectF GetNodeAbsFrameRect(const RefPtr<FrameNode>& node, std::optional<OffsetF> parentPos = std::nullopt) const;
    void AnimateWithSandBox(const OffsetF& inNodeParentPos, bool inNodeParentHasScales,
        const std::function<void()>& propertyCallback, const AnimationOption& option);
    void SyncGeometryPropertiesAfterLayout(const RefPtr<FrameNode>& syncNode);

    static constexpr int32_t RESYNC_DURATION = 1;
    std::string id_;
    WeakPtr<FrameNode> inNode_;
    WeakPtr<FrameNode> outNode_;
    State state_ = State::IDLE;
    bool hasInAnim_ = false;
    bool hasOutAnim_ = false;
    bool isSynced_ = false;
    SizeF inNodeActiveFrameSize_;
    std::optional<RectF> inNodeAbsRect_;
    std::optional<RectF> outNodeTargetAbsRect_;
    OffsetF outNodePos_;
    SizeF outNodeSize_;
    OffsetF outNodeParentPos_;
    bool outNodeParentHasScales_ = false;
    RefPtr<FrameNode> holder_;
    bool followWithoutTransition_ = false;
    bool doRegisterSharedTransition_ = true;
    // static node means the node on the tree without transition
    std::optional<RectF> staticNodeAbsRect_;
    RefPtr<LayoutProperty> layoutPropertyIn_;
    RefPtr<LayoutProperty> layoutPropertyOut_;
    AnimationOption animationOption_;

    ACE_DISALLOW_COPY_AND_MOVE(GeometryTransition);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_GEOMETRY_TRANSITION_H