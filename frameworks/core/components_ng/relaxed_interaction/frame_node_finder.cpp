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
#include "base/memory/ace_type.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/common/event_manager.h"

namespace OHOS::Ace::NG {

bool PanRecognizerPred::operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    return AceType::InstanceOf<PanRecognizer>(gestureRecognizer);
}

bool ClickRecognizerPred::operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    return AceType::InstanceOf<ClickRecognizer>(gestureRecognizer);
}


FrameNodeFinder::FrameNodeFinder(WeakPtr<PipelineContext> context)
    : context_(context), pred_(PanRecognizerPred()) {}

FrameNodeFinder::FrameNodeFinder(WeakPtr<PipelineContext> context, GestureRecognizerPred pred)
    : context_(context), pred_(pred) {}

std::pair<RefPtr<FrameNode>, GestureEventFunc> FrameNodeFinder::FindAt(float x, float y)
{
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Pipeline context is null, cannot query FrameNode");
        return std::make_pair(nullptr, nullptr);
    }

    auto rootNode = context->GetRootElement();
    if (!rootNode) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Root node is null, cannot query FrameNode at coordinates");
        return std::make_pair(nullptr, nullptr);
    }
    return FindAt(rootNode, x, y);
}

std::pair<RefPtr<FrameNode>, GestureEventFunc> FrameNodeFinder::FindAt(const RefPtr<UINode>& rootNode, float x, float y)
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
    auto result = Find(touchTestResult);
    CleanResult(touchTestResult, touchPoint.id);
    return result;
}

std::pair<RefPtr<FrameNode>, GestureEventFunc> FrameNodeFinder::Find(const TouchTestResult& touchTestResult)
{
    if (touchTestResult.empty()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "touchTestResult is empty");
        return std::make_pair(nullptr, nullptr);
    }

    for (const auto& recognizer : touchTestResult) {
        if (!recognizer) {
            continue;
        }

        auto gestureRecognizer = AceType::DynamicCast<NGGestureRecognizer>(recognizer);
        if (!gestureRecognizer) {
            continue;
        }

        auto result = FindLeaf(gestureRecognizer);
        if (result.first) {
            return result;
        }
    }

    return std::make_pair(nullptr, nullptr);
}

std::pair<RefPtr<FrameNode>, GestureEventFunc> FrameNodeFinder::FindLeaf(
    const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    if (!gestureRecognizer) {
        return std::make_pair(nullptr, nullptr);
    }

    // Get attached node of current recognizer
    auto currentNode = gestureRecognizer->GetAttachedNode().Upgrade();
    auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(gestureRecognizer);
    auto ret = pred_(gestureRecognizer);
    if ((!recognizerGroup || recognizerGroup->GetGroupRecognizer().empty()) && ret) {
        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(gestureRecognizer);
        if (clickRecognizer) {
            return std::make_pair(currentNode, clickRecognizer->GetTapActionFunc());
        }
        return std::make_pair(currentNode, nullptr);
    }

    // Recursively find leaf node - prioritize child recognizers
    for (const auto& childRecognizer : recognizerGroup->GetGroupRecognizer()) {
        auto childGestureRecognirozer = AceType::DynamicCast<NGGestureRecognizer>(childRecognizer);
        if (!childGestureRecognirozer) {
            continue;
        }
        auto childResult = FindLeaf(childGestureRecognirozer);
        if (childResult.first) {
            currentNode = childResult.first;
            break;
        }
    }
    return std::make_pair(currentNode, nullptr);
}

void FrameNodeFinder::CleanResult(const TouchTestResult& touchTestResult, int32_t touchId)
{
    std::list<RefPtr<NG::NGGestureRecognizer>> hitTestRecognizers;
    for (const auto& item : touchTestResult) {
        auto recognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(item);
        if (recognizer) {
            hitTestRecognizers.emplace_back(recognizer);
        }
    }
    std::set<WeakPtr<NG::FrameNode>> relaxedInteractionFrameNodes;
    GetFrameNodes(relaxedInteractionFrameNodes, hitTestRecognizers);

    auto context = context_.Upgrade();
    auto eventManager = context->GetEventManager();
    auto ref = eventManager->GetGestureRefereeNG(nullptr);
    if (ref) {
        ref->CleanGestureStateVoluntarily(touchId);
        ref->CleanGestureScope(touchId);
        CleanFrameNodes(relaxedInteractionFrameNodes);
    }
}

void FrameNodeFinder::GetFrameNodes(std::set<WeakPtr<NG::FrameNode>>& frameNodes,
    const std::list<RefPtr<NG::NGGestureRecognizer>>& touchTestResults)
{
    if (touchTestResults.empty()) {
        return;
    }
    for (const auto& item : touchTestResults) {
        auto node = item->GetAttachedNode().Upgrade();
        if (node) {
            frameNodes.emplace(node);
        }
        auto group = AceType::DynamicCast<NG::RecognizerGroup>(item);
        if (group) {
            auto groupRecognizers = group->GetGroupRecognizer();
            GetFrameNodes(frameNodes, groupRecognizers);
        }
    }
}

void FrameNodeFinder::CleanFrameNodes(std::set<WeakPtr<NG::FrameNode>>& frameNodes)
{
    for (const auto& item : frameNodes) {
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
}

} // namespace OHOS::Ace::NG