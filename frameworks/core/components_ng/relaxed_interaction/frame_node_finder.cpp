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
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/common/event_manager.h"

namespace OHOS::Ace::NG {

std::string ComponentUtils::ToString(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    if (!gestureRecognizer) {
        return "NGGestureRecognizer{nullptr}";
    }
    auto currentNode = gestureRecognizer->GetAttachedNode().Upgrade();
    if (!currentNode) {
        return "NGGestureRecognizer{frameNode=nullptr}";
    }
    auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(gestureRecognizer);
    std::ostringstream buffer;
    buffer  << "NGGestureRecognizer{frameNode=" << currentNode->ToString()
            << ", frameNode.tag=" << currentNode->GetTag()
            << ", frameNode.axis=" << static_cast<int32_t>(GetAxis(currentNode))
            << ", isPan=" << (AceType::InstanceOf<PanRecognizer>(gestureRecognizer) ? "Y" : "N")
            << ", groupRecognizer.valid=" << (bool)recognizerGroup
            << ", groupRecognizer.size="
            << (recognizerGroup ? std::to_string(recognizerGroup->GetGroupRecognizer().size()) : "N/A")
            << "}";
    return buffer.str();
}

Axis ComponentUtils::GetAxis(const RefPtr<FrameNode>& frameNode)
{
    if (!frameNode) {
        return Axis::NONE;
    }
    auto pattern = frameNode->GetPattern();
    if (!pattern) {
        return Axis::NONE;
    }
    auto scrollablePattern = AceType::DynamicCast<ScrollablePattern>(pattern);
    if (scrollablePattern) {
        return scrollablePattern->GetAxis();
    }
    return Axis::NONE;
}

bool ClickRecognizerPred::operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(gestureRecognizer);
    if (!clickRecognizer) {
        return false;
    }
    return clickRecognizer->GetCount() == 1;
}

bool ContentSwitchRecognizerPred::operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    if (!AceType::InstanceOf<PanRecognizer>(gestureRecognizer)) {
        return false;
    }

    std::set<std::string> tags = {
        V2::SWIPER_ETS_TAG,
        V2::TABS_ETS_TAG,
    };
    auto currentNode = gestureRecognizer->GetAttachedNode().Upgrade();
    if (!currentNode) {
        return false;
    }
    return tags.count(currentNode->GetTag());
}

bool ScrollRecognizerPred::operator()(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    if (!AceType::InstanceOf<PanRecognizer>(gestureRecognizer)) {
        return false;
    }

    auto currentNode = gestureRecognizer->GetAttachedNode().Upgrade();
    if (!currentNode) {
        return false;
    }

    const std::set<std::string> tags = {
        V2::SCROLL_ETS_TAG,
        V2::LIST_ETS_TAG,
    };
    if (tags.count(currentNode->GetTag()) == 0) {
        return false;
    }

    if (direction_ == RelaxedScrollDirection::FORWARD || direction_ == RelaxedScrollDirection::BACKWARD) {
        return true;
    }

    auto axis = ComponentUtils::GetAxis(currentNode);
    if (axis == Axis::FREE) {
        return true;
    }
    if (direction_ == RelaxedScrollDirection::LEFT || direction_ == RelaxedScrollDirection::RIGHT) {
        return axis == Axis::HORIZONTAL;
    }
    if (direction_ == RelaxedScrollDirection::UP || direction_ == RelaxedScrollDirection::DOWN) {
        return axis == Axis::VERTICAL;
    }
    return false;
}

FrameNodeFinder::FrameNodeFinder(WeakPtr<PipelineContext> context, GestureRecognizerPred pred)
    : context_(context), pred_(pred) {}

FrameNodeMatch FrameNodeFinder::FindAt(float x, float y)
{
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Pipeline context is null, cannot query FrameNode");
        return {};
    }

    auto rootNode = context->GetRootElement();
    if (!rootNode) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Root node is null, cannot query FrameNode at coordinates");
        return {};
    }
    auto result = FindAt(rootNode, x, y);
    return result;
}

FrameNodeMatch FrameNodeFinder::FindAt(const RefPtr<UINode>& rootNode, float x, float y)
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

FrameNodeMatch FrameNodeFinder::Find(const TouchTestResult& touchTestResult)
{
    if (touchTestResult.empty()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "touchTestResult is empty");
        return {};
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
        if (result) {
            return result;
        }
    }

    return {};
}

FrameNodeMatch FrameNodeFinder::FindLeaf(
    const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    if (!gestureRecognizer) {
        return {};
    }

    auto currentNode = gestureRecognizer->GetAttachedNode().Upgrade();
    auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(gestureRecognizer);
    if (!recognizerGroup || recognizerGroup->GetGroupRecognizer().empty()) {
        if (Test(gestureRecognizer)) {
            return gestureRecognizer;
        }
        return {};
    }

    for (const auto& childRecognizer : recognizerGroup->GetGroupRecognizer()) {
        auto childGestureRecognirozer = AceType::DynamicCast<NGGestureRecognizer>(childRecognizer);
        if (!childGestureRecognirozer) {
            continue;
        }
        auto childResult = FindLeaf(childGestureRecognirozer);
        if (childResult) {
            return childResult;
        }
    }

    return {};
}

bool FrameNodeFinder::Test(const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    auto ret = pred_(gestureRecognizer);
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "Test [%{public}s] for %{public}s",
            ret ? "  PASS" : "NOPASS", ComponentUtils::ToString(gestureRecognizer).c_str());
    }
    return ret;
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
    if (!ref) {
        return;
    }
    ref->CleanGestureStateVoluntarily(touchId);
    ref->CleanGestureScope(touchId);
    CleanFrameNodes(relaxedInteractionFrameNodes);
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
        if (!group) {
            continue;
        }
        auto groupRecognizers = group->GetGroupRecognizer();
        GetFrameNodes(frameNodes, groupRecognizers);
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
        if (!gestureEventHub) {
            continue;
        }
        gestureEventHub->CleanExternalRecognizers();
        gestureEventHub->CleanInnerRecognizer();
        gestureEventHub->CleanNodeRecognizer();
    }
}

} // namespace OHOS::Ace::NG