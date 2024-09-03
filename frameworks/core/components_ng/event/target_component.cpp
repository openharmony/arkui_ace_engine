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
#include "core/components_ng/event/target_component.h"

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

void TargetComponent::SetNode(const WeakPtr<UINode>& uiNode)
{
    node_ = uiNode;
}

void TargetComponent::SetNodeLinkGesture(const RefPtr<NGGestureRecognizer>& nodeLinkGesture)
{
    nodeLinkGesture_ = nodeLinkGesture;
}

void TargetComponent::SetNodeGesture(const RefPtr<NGGestureRecognizer>& nodeGesture)
{
    nodeGesture_ = nodeGesture;
}

WeakPtr<UINode> TargetComponent::GetUINode()
{
    return node_;
}

void TargetComponent::AddChild(const RefPtr<TargetComponent>& child)
{
    targetComponentChildren_.emplace_back(child);
}

void TargetComponent::AddPath(int32_t pathId)
{
    path_.emplace(pathId);
}

void TargetComponent::SetSourceType(SourceType sourceType)
{
    sourceType_ = sourceType;
}

void TargetComponent::SetOnGestureJudgeBegin(GestureJudgeFunc&& onGestureJudgeBegin)
{
    onGestureJudgeBegin_ = std::move(onGestureJudgeBegin);
}

void TargetComponent::SetOnGestureJudgeNativeBegin(GestureJudgeFunc&& onGestureJudgeBegin)
{
    onGestureJudgeNativeBegin_ = std::move(onGestureJudgeBegin);
}

void TargetComponent::SetOnGestureRecognizerJudgeBegin(GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc)
{
    gestureRecognizerJudgeFunc_ = std::move(gestureRecognizerJudgeFunc);
}

GestureRecognizerJudgeFunc TargetComponent::GetOnGestureRecognizerJudgeBegin() const
{
    return gestureRecognizerJudgeFunc_;
}
} // namespace OHOS::Ace::NG
