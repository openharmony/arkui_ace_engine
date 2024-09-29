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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_TARGET_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_TARGET_COMPONENT_H

#include <list>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace::NG {

class UINode;
class NGGestureRecognizer;
using GestureJudgeFunc = std::function<GestureJudgeResult(
    const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info)>;

using GestureRecognizerJudgeFunc = std::function<GestureJudgeResult(const std::shared_ptr<BaseGestureEvent>& info,
    const RefPtr<NGGestureRecognizer>& current, const std::list<RefPtr<NGGestureRecognizer>>& others)>;

class ACE_EXPORT TargetComponent : public virtual AceType {
    DECLARE_ACE_TYPE(TargetComponent, AceType);

public:
    TargetComponent() = default;
    ~TargetComponent() override = default;

    void SetNode(const WeakPtr<UINode>& uiNode);

    void SetNodeLinkGesture(const RefPtr<NGGestureRecognizer>& nodeLinkGesture);

    void SetNodeGesture(const RefPtr<NGGestureRecognizer>& nodeGesture);

    WeakPtr<UINode> GetUINode();

    void AddChild(const RefPtr<TargetComponent>& child);

    void AddPath(int32_t pathId);

    void SetSourceType(SourceType sourceType);

    void SetOnGestureJudgeBegin(GestureJudgeFunc&& onGestureJudgeBegin);

    void SetOnGestureJudgeNativeBegin(GestureJudgeFunc&& onGestureJudgeBegin);

    GestureJudgeFunc GetOnGestureJudgeBeginCallback()
    {
        return onGestureJudgeBegin_;
    }

    GestureJudgeFunc GetOnGestureJudgeNativeBeginCallback()
    {
        return onGestureJudgeNativeBegin_;
    }

    void SetOnGestureRecognizerJudgeBegin(GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc);

    GestureRecognizerJudgeFunc GetOnGestureRecognizerJudgeBegin() const;

    void SetInnerNodeGestureRecognizerJudge()
    {
        isInnerNodeGestureRecognizerJudgeSet_ = true;
    }

    bool IsInnerNodeGestureRecognizerJudgeSet() const
    {
        return isInnerNodeGestureRecognizerJudgeSet_;
    }

private:
    WeakPtr<UINode> node_;
    RefPtr<NGGestureRecognizer> nodeLinkGesture_;
    RefPtr<NGGestureRecognizer> nodeGesture_;
    std::list<RefPtr<TargetComponent>> targetComponentChildren_;
    GestureJudgeFunc onGestureJudgeBegin_;
    GestureJudgeFunc onGestureJudgeNativeBegin_;
    GestureRecognizerJudgeFunc gestureRecognizerJudgeFunc_;
    std::set<int32_t> path_;
    SourceType sourceType_ = SourceType::TOUCH;

    // This parameter determines whether the callback of the inner node is set.
    bool isInnerNodeGestureRecognizerJudgeSet_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_TARGET_COMPONENT_H
