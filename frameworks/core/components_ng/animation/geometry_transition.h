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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_GEOMETRY_TRANSITION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_GEOMETRY_TRANSITION_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
class FrameNode;
class LayoutWrapper;

class GeometryTransition : public AceType {
    DECLARE_ACE_TYPE(GeometryTransition, AceType);

public:
    GeometryTransition(const WeakPtr<FrameNode>& frameNode, bool forceOutAnim);
    ~GeometryTransition() override = default;

    bool IsNodeActive(const WeakPtr<FrameNode>& frameNode) const;
    bool IsNodeIdentity(const WeakPtr<FrameNode>& frameNode) const;
    bool IsNodeOutAndIdentity(const WeakPtr<FrameNode>& frameNode) const;
    bool IsNodeInAndActive(const WeakPtr<FrameNode>& frameNode) const;
    bool IsNodeOutAndActive(const WeakPtr<FrameNode>& frameNode) const;
    bool IsNodeInAndIdentity(const WeakPtr<FrameNode>& frameNode) const;

    void Build(const WeakPtr<FrameNode>& frameNode, bool isNodeIn);
    bool Update(const WeakPtr<FrameNode>& which, const WeakPtr<FrameNode>& value);
    void WillLayout(const RefPtr<LayoutWrapper>& layoutWrapper);
    void DidLayout(const WeakPtr<FrameNode>& frameNode);

private:
    enum class State {
        IDLE,
        INITIAL_LAYOUT,
        FINAL_LAYOUT,
    };

    WeakPtr<FrameNode> inNode_;
    WeakPtr<FrameNode> outNode_;
    State state_;
    bool hasInAnim_;
    bool hasOutAnim_;
    bool forceOutAnim_;
    bool forceState_;

    void TryToSetState(bool condition, State state);
    void ModifyLayoutConstraint(const RefPtr<LayoutWrapper>& layoutWrapper, bool isNodeIn);
    void SyncGeometry(bool isNodeIn);

    ACE_DISALLOW_COPY_AND_MOVE(GeometryTransition);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_GEOMETRY_TRANSITION_H