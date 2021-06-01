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
    if (hitTestResult.empty()) {
        LOGI("hit test result is empty");
    }
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
        if (point.type == TouchType::UP) {
            GestureReferee::GetInstance().AdjudicateGestureSequence(point.id);
        } else if (point.type == TouchType::CANCEL) {
            GestureReferee::GetInstance().CleanGestureScope(point.id);
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
    MouseTestResult hitTestResult;

    const Point point { event.x, event.y };
    // For root node, the parent local point is the same as global point.
    renderNode->MouseTest(point, point, hitTestResult);
    if (hitTestResult.empty()) {
        LOGI("mouse test result is empty");
    }
    mouseTestResults_[event.GetId()] = std::move(hitTestResult);
}

void EventManager::MouseHoverTest(const MouseEvent& event, const RefPtr<RenderNode>& renderNode)
{
    if (!renderNode) {
        LOGW("renderNode is null.");
        return;
    }
    const Point point { event.x, event.y };
    renderNode->MouseHoverTest(point);
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
    const auto iter = mouseTestResults_.find(event.GetId());
    if (iter != mouseTestResults_.end()) {
        // If one mouse recognizer has already been won, other mouse recognizers will still be affected by
        // the event, each recognizer needs to filter the extra events by itself.
        for (const auto& entry : iter->second) {
            entry->HandleEvent(event);
        }

        return true;
    }

    LOGI("the %{public}d mouse test result does not exist!", event.GetId());
    return false;
}

} // namespace OHOS::Ace
