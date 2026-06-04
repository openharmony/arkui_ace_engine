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

#include "core/components_ng/gestures/recognizers/recognizer_group.h"

namespace OHOS::Ace::NG {
void NGGestureRecognizer::AboutToAccept() {}

bool NGGestureRecognizer::HandleEvent(const TouchEvent& point)
{
    (void)point;
    return true;
}

bool NGGestureRecognizer::HandleEvent(const AxisEvent& event)
{
    (void)event;
    return true;
}

RefPtr<GestureSnapshot> NGGestureRecognizer::Dump() const
{
    return nullptr;
}

void NGGestureRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    (void)recognizer;
    (void)disposal;
}

void NGGestureRecognizer::UpdateGestureReferee(const WeakPtr<GestureReferee>& gestureReferee)
{
    referee_ = gestureReferee;
}

bool NGGestureRecognizer::SetGestureGroup(const WeakPtr<NGGestureRecognizer>& gestureGroup)
{
    gestureGroup_ = gestureGroup;
    return true;
}

bool NGGestureRecognizer::ShouldResponse()
{
    return true;
}

std::string NGGestureRecognizer::GetGestureInfoString() const
{
    return {};
}


RefPtr<Gesture> NGGestureRecognizer::CreateGestureFromRecognizer() const
{
    return nullptr;
}

RefereeState RecognizerGroup::CheckStates(size_t touchId)
{
    (void)touchId;
    return RefereeState::READY;
}

void RecognizerGroup::UpdateGestureReferee(const WeakPtr<GestureReferee>& gestureReferee)
{
    referee_ = gestureReferee;
}

RefPtr<Gesture> RecognizerGroup::CreateGestureFromRecognizer() const
{
    return nullptr;
}

void RecognizerGroup::OnBeginGestureReferee(int32_t touchId, int32_t originalId, bool needUpdateChild)
{
    (void)touchId;
    (void)originalId;
    (void)needUpdateChild;
}

void RecognizerGroup::OnFinishGestureReferee(int32_t touchId, bool isBlocked)
{
    (void)touchId;
    (void)isBlocked;
}

void RecognizerGroup::AttachFrameNode(const WeakPtr<NG::FrameNode>& node)
{
    TouchEventTarget::AttachFrameNode(node);
}

void RecognizerGroup::OnFlushTouchEventsBegin() {}

void RecognizerGroup::OnFlushTouchEventsEnd() {}

void RecognizerGroup::OnResetStatus() {}

void RecognizerGroup::ForceCleanRecognizerWithGroup()
{
    recognizers_.clear();
}

void RecognizerGroup::CleanRecognizerState() {}

bool RecognizerGroup::IsReady()
{
    return true;
}

std::string RecognizerGroup::GetGestureInfoString() const
{
    return {};
}

void MultiFingersRecognizer::CheckCurrentFingers() const {}

void MultiFingersRecognizer::OnFinishGestureReferee(int32_t touchId, bool isBlocked)
{
    (void)touchId;
    (void)isBlocked;
}

void MultiFingersRecognizer::CleanRecognizerState()
{
    touchPoints_.clear();
    fingersId_.clear();
    fingerList_.clear();
    activeFingers_.clear();
    currentFingers_ = 0;
}

std::string MultiFingersRecognizer::GetGestureInfoString() const
{
    return {};
}
} // namespace OHOS::Ace::NG
