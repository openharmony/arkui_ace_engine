/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/relaxed_interaction/frame_node_finder.h"

#include "base/log/log.h"
#include "base/log/log_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/common/event_manager.h"

namespace OHOS::Ace::NG {

FrameNodeFinder::FrameNodeFinder(WeakPtr<PipelineContext> context) : context_(context) {}

RefPtr<FrameNode> FrameNodeFinder::FindAt(float x, float y)
{
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Pipeline context is null, cannot query FrameNode");
        return nullptr;
    }

    auto rootNode = context->GetRootElement();
    if (!rootNode) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Root node is null, cannot query FrameNode at coordinates");
        return nullptr;
    }
    return FindAt(rootNode, x, y);
}

RefPtr<FrameNode> FrameNodeFinder::FindAt(const RefPtr<UINode>& rootNode, float x, float y)
{
    TouchEvent touchPoint;
    touchPoint.x = x;
    touchPoint.y = y;
    touchPoint.id = 0;
    touchPoint.type = TouchType::DOWN;

    TouchRestrict touchRestrict;
    touchRestrict.touchEvent = touchPoint;
    touchRestrict.inputEventType = InputEventType::TOUCH_SCREEN;

    TouchTestResult touchTestResult;
    ResponseLinkResult responseLinkResult;
    NG::PointF globalPoint(x, y);
    NG::PointF parentLocalPoint(x, y);
    NG::PointF parentRevertPoint(x, y);

    rootNode->TouchTest(globalPoint, parentLocalPoint, parentRevertPoint,
        touchRestrict, touchTestResult, touchPoint.id, responseLinkResult);

    // Collect FrameNodes on the touch path
    CollectHittedFrameNodes(touchTestResult);

    auto result = ExtractFrameNodeFromResult(touchTestResult);

    // Clean gesture state
    CleanGestureState(touchPoint.id);

    return result;
}

void FrameNodeFinder::CollectHittedFrameNodes(const TouchTestResult& touchTestResult)
{
    std::list<RefPtr<NG::NGGestureRecognizer>> hitTestRecognizers;
    for (const auto& item : touchTestResult) {
        auto recognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(item);
        if (recognizer) {
            hitTestRecognizers.emplace_back(recognizer);
        }
    }
    SetRelaxedInteractionFrameNode(hitTestRecognizers);
}

void FrameNodeFinder::CleanGestureState(int32_t touchId)
{
    auto context = context_.Upgrade();
    auto eventManager = context->GetEventManager();
    auto ref = eventManager->GetGestureRefereeNG(nullptr);
    if (ref) {
        ref->CleanGestureStateVoluntarily(touchId);
        ref->CleanGestureScope(touchId);
        CleanRelaxedInteractionGestureEventHub();
    }
}

void FrameNodeFinder::SetRelaxedInteractionFrameNode(const std::list<RefPtr<NG::NGGestureRecognizer>>& touchTestResults)
{
    if (touchTestResults.empty()) {
        return;
    }
    for (const auto& item : touchTestResults) {
        auto node = item->GetAttachedNode().Upgrade();
        if (node) {
            relaxedInteractionFrameNodes_.emplace(node);
        }
        auto group = AceType::DynamicCast<NG::RecognizerGroup>(item);
        if (group) {
            auto groupRecognizers = group->GetGroupRecognizer();
            SetRelaxedInteractionFrameNode(groupRecognizers);
        }
    }
}

void FrameNodeFinder::CleanRelaxedInteractionGestureEventHub()
{
    for (const auto& item : relaxedInteractionFrameNodes_) {
        auto frameNode = item.Upgrade();
        if (!frameNode) {
            continue;
        }

        auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
        if (gestureEventHub) {
            gestureEventHub->CleanExternalRecognizers();
            gestureEventHub->CleanInnerRecognizer();
            gestureEventHub->CleanNodeRecognizer();
        }
    }
    relaxedInteractionFrameNodes_.clear();
}

RefPtr<FrameNode> FrameNodeFinder::ExtractFrameNodeFromResult(const TouchTestResult& touchTestResult)
{
    if (touchTestResult.empty()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "touchTestResult is empty");
        return nullptr;
    }

    for (const auto& recognizer : touchTestResult) {
        if (!recognizer) {
            continue;
        }

        auto gestureRecognizer = AceType::DynamicCast<NGGestureRecognizer>(recognizer);
        if (!gestureRecognizer) {
            continue;
        }

        auto frameNode = FindLeafGestureRecognizerNode(gestureRecognizer);
        if (frameNode) {
            return frameNode;
        }
    }

    return nullptr;
}

RefPtr<FrameNode> FrameNodeFinder::FindLeafGestureRecognizerNode(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    if (!gestureRecognizer) {
        return nullptr;
    }

    // Get attached node of current recognizer
    auto currentNode = gestureRecognizer->GetAttachedNode().Upgrade();
    auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(gestureRecognizer);
    if (!recognizerGroup || recognizerGroup->GetGroupRecognizer().empty()) {
        return currentNode;
    }

    // Recursively find leaf node - prioritize child recognizers
    for (const auto& childRecognizer : recognizerGroup->GetGroupRecognizer()) {
        auto childGestureRecognirozer = AceType::DynamicCast<NGGestureRecognizer>(childRecognizer);
        if (!childGestureRecognirozer) {
            continue;
        }
        auto childNode = FindLeafGestureRecognizerNode(childGestureRecognirozer);
        if (childNode) {
            currentNode = childNode;
            break;
        }
    }
    return currentNode;
}

} // namespace OHOS::Ace::NG