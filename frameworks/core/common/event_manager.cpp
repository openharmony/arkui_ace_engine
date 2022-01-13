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

#include "core/common/event_manager.h"

#include "base/log/ace_trace.h"
#include "core/gestures/gesture_referee.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

void EventManager::TouchTest(
    const TouchPoint& touchPoint, const RefPtr<RenderNode>& renderNode, const TouchRestrict& touchRestrict)
{
    ACE_FUNCTION_TRACE();
    if (!renderNode) {
        LOGW("renderNode is null.");
        return;
    }
    // first clean.
    GestureReferee::GetInstance().CleanGestureScope(touchPoint.id);
    // collect
    TouchTestResult hitTestResult;
    const Point point { touchPoint.x, touchPoint.y };
    // For root node, the parent local point is the same as global point.
    renderNode->TouchTest(point, point, touchRestrict, hitTestResult);
    touchTestResults_[touchPoint.id] = std::move(hitTestResult);
}

bool EventManager::DispatchTouchEvent(const TouchPoint& point)
{
    ACE_FUNCTION_TRACE();
    const auto iter = touchTestResults_.find(point.id);
    if (iter != touchTestResults_.end()) {
        bool dispatchSuccess = true;
        for (auto entry = iter->second.rbegin(); entry != iter->second.rend(); ++entry) {
            if (!(*entry)->DispatchEvent(point)) {
                dispatchSuccess = false;
                break;
            }
        }
        // If one gesture recognizer has already been won, other gesture recognizers will still be affected by
        // the event, each recognizer needs to filter the extra events by itself.
        if (dispatchSuccess) {
            for (const auto& entry : iter->second) {
                if (!entry->HandleEvent(point)) {
                    break;
                }
            }
        }

        if (point.type == TouchType::UP || point.type == TouchType::CANCEL) {
            GestureReferee::GetInstance().CleanGestureScope(point.id);
            touchTestResults_.erase(point.id);
        }
        return true;
    }
    LOGI("the %{public}d touch test result does not exist!", point.id);
    return false;
}

bool EventManager::DispatchKeyEvent(const KeyEvent& event, const RefPtr<FocusNode>& focusNode)
{
    if (!focusNode) {
        LOGW("focusNode is null.");
        return false;
    }
    LOGD("The key code is %{public}d, the key action is %{public}d, the repeat time is %{public}d.", event.code,
        event.action, event.repeatTime);
    if (!focusNode->HandleKeyEvent(event)) {
        LOGD("use platform to handle this event");
        return false;
    }
    return true;
}

void EventManager::MouseTest(const MouseEvent& event, const RefPtr<RenderNode>& renderNode)
{
    if (!renderNode) {
        LOGW("renderNode is null.");
        return;
    }
    const Point point { event.x, event.y };
    MouseHoverTestList hitTestResult;
    WeakPtr<RenderNode> hoverNode = nullptr;
    renderNode->MouseDetect(point, point, hitTestResult, hoverNode);
    if (hitTestResult.empty()) {
        LOGD("mouse hover test result is empty");
    }
    mouseHoverTestResultsPre_ = std::move(mouseHoverTestResults_);
    mouseHoverTestResults_ = std::move(hitTestResult);
    mouseHoverNodePre_ = mouseHoverNode_;
    mouseHoverNode_ = hoverNode;
    LOGI("MouseDetect hit test last/new result size = %{public}zu/%{public}zu", mouseHoverTestResultsPre_.size(),
        mouseHoverTestResults_.size());
}

bool EventManager::DispatchRotationEvent(
    const RotationEvent& event, const RefPtr<RenderNode>& renderNode, const RefPtr<RenderNode>& requestFocusNode)
{
    if (!renderNode) {
        LOGW("renderNode is null.");
        return false;
    }

    if (requestFocusNode && renderNode->RotationMatchTest(requestFocusNode)) {
        LOGD("RotationMatchTest: dispatch rotation to request node.");
        return requestFocusNode->RotationTestForward(event);
    } else {
        LOGD("RotationMatchTest: dispatch rotation to statck render node.");
        return renderNode->RotationTest(event);
    }
}

bool EventManager::DispatchMouseEvent(const MouseEvent& event)
{
    if (event.action == MouseAction::PRESS || event.action == MouseAction::RELEASE ||
        event.action == MouseAction::MOVE) {
        LOGD("RenderBox::HandleMouseEvent, button is %{public}d, action is %{public}d", event.button, event.action);
        for (const auto& wp : mouseHoverTestResults_) {
            auto hoverNode = wp.Upgrade();
            if (hoverNode) {
                if (hoverNode->HandleMouseEvent(event)) {
                    break;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

bool EventManager::DispatchMouseHoverEvent(const MouseEvent& event)
{
    auto hoverNodeCur = mouseHoverNode_.Upgrade();
    auto hoverNodePre = mouseHoverNodePre_.Upgrade();
    if (event.button != MouseButton::NONE_BUTTON) {
        if (event.action == MouseAction::PRESS) {
            if (hoverNodeCur) {
                hoverNodeCur->StopMouseHoverAnimation();
                hoverNodeCur->OnMouseClickDownAnimation();
            }
        } else if (event.action == MouseAction::RELEASE) {
            if (hoverNodeCur) {
                hoverNodeCur->StopMouseHoverAnimation();
                hoverNodeCur->OnMouseClickUpAnimation();
            }
        } else {
            LOGE("Unknow mouse hover event: MouseButton: %{public}d, MouseAction: %{public}d", event.button,
                event.action);
            return false;
        }
    } else {
        if (hoverNodeCur != hoverNodePre) {
            if (hoverNodeCur) {
                hoverNodeCur->AnimateMouseHoverEnter();
            }
            if (hoverNodePre) {
                hoverNodePre->AnimateMouseHoverExit();
            }
        }
        for (const auto& wp : mouseHoverTestResults_) {
            // get all current hover nodes while it's not in previous hover nodes. Thoes nodes are new hoverd
            auto it = std::find(mouseHoverTestResultsPre_.begin(), mouseHoverTestResultsPre_.end(), wp);
            if (it == mouseHoverTestResultsPre_.end()) {
                auto hoverNode = wp.Upgrade();
                if (hoverNode) {
                    hoverNode->HandleMouseHoverEvent(MouseState::HOVER);
                }
            }
        }
        for (const auto& wp : mouseHoverTestResultsPre_) {
            // get all previous hover nodes while it's not in current hover nodes. Those nodes exit hoverd
            auto it = std::find(mouseHoverTestResults_.begin(), mouseHoverTestResults_.end(), wp);
            if (it == mouseHoverTestResults_.end()) {
                auto hoverNode = wp.Upgrade();
                if (hoverNode) {
                    hoverNode->HandleMouseHoverEvent(MouseState::NONE);
                }
            }
        }
    }
    return true;
}

void EventManager::ClearResults()
{
    touchTestResults_.clear();
    mouseTestResults_.clear();
}

} // namespace OHOS::Ace
