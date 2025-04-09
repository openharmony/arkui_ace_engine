/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef TEST_UNITTEST_CORE_GESTURES_RECOGNIZER_GROUP_TEST_UTILS_H
#define TEST_UNITTEST_CORE_GESTURES_RECOGNIZER_GROUP_TEST_UTILS_H

#include <iostream>
#include "test/unittest/core/gestures/recognizer_test_utils.h"

#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"
#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/components_ng/gestures/recognizers/sequenced_recognizer.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<ClickRecognizer> CreateClickRecognizerWithParam(int32_t fingers, int32_t count)
{
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(fingers, count);
    return clickRecognizer;
}

RefPtr<LongPressRecognizer> CreateLongPressRecognizerWithParam(int32_t duration, int32_t fingers, bool repeat)
{
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(duration, fingers, repeat);
    return longPressRecognizer;
}

RefPtr<PanRecognizer> CreatePanRecognizerWithParam(int32_t fingers, const PanDirection& direction, double distance)
{
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(fingers, direction, distance);
    return panRecognizer;
}

RefPtr<SwipeRecognizer> CreateSwipeRecognizerWithParam(int32_t fingers, const SwipeDirection& direction, double speed)
{
    auto swipeRecognizer = AceType::MakeRefPtr<SwipeRecognizer>(fingers, direction, speed);
    return swipeRecognizer;
}

RefPtr<PinchRecognizer> CreatePinchRecognizerWithParam(int32_t fingers, double distance)
{
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(fingers, distance);
    return pinchRecognizer;
}

RefPtr<RotationRecognizer> CreateRotationRecognizerWithParam(int32_t fingers, double angle)
{
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(fingers, angle);
    return rotationRecognizer;
}

RefPtr<ExclusiveRecognizer> CreateExclusiveRecognizerWithParam(
    const std::vector<RefPtr<NGGestureRecognizer>>& recognizers)
{
    auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    return exclusiveRecognizer;
}

void DispatchSingleClickEvent(const RefPtr<NGGestureRecognizer>& recognizer)
{
    recognizer->BeginReferee(0, true);
    TouchEvent downEvent;
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(downEvent);
    TouchEvent upEvent;
    upEvent.SetId(0).SetType(TouchType::UP).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(upEvent);
}

void DispatchDoubleFingerSingleClickEvent(const RefPtr<NGGestureRecognizer>& recognizer)
{
    recognizer->BeginReferee(0, true);
    recognizer->BeginReferee(1, true);
    TouchEvent downEventOne;
    downEventOne.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventOne);
    TouchEvent downEventTwo;
    downEventTwo.SetId(1).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventTwo);
    TouchEvent upEventOne;
    upEventOne.SetId(0).SetType(TouchType::UP).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(upEventOne);
    TouchEvent upEventTwo;
    upEventTwo.SetId(1).SetType(TouchType::UP).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(upEventTwo);
}

void DispatchPanEvent(const RefPtr<NGGestureRecognizer>& recognizer)
{
    recognizer->BeginReferee(0, true);
    TouchEvent downEventOne;
    downEventOne.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventOne);
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        TouchEvent moveEvent;
        moveEvent.SetId(0).SetType(TouchType::MOVE).SetX(100.0f + static_cast<float>(num) * 10.0f).SetY(100.0f);
        recognizer->HandleEvent(moveEvent);
    }
}

void DispatchSwipeEvent(const RefPtr<NGGestureRecognizer>& recognizer)
{
    recognizer->BeginReferee(0, true);
    TouchEvent downEventOne;
    std::chrono::nanoseconds nanoseconds(1000);
    downEventOne.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetTime(TimeStamp(nanoseconds));
    ;
    recognizer->HandleEvent(downEventOne);
    auto timeStep = 1000 * 1000 * 1000;
    TimeStamp lastTime;
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        TouchEvent moveEvent;
        std::chrono::nanoseconds moveNanoseconds(static_cast<int64_t>(1000 + num * timeStep));
        moveEvent.SetId(0)
            .SetType(TouchType::MOVE)
            .SetX(100.0f + static_cast<float>(num) * 100.0f)
            .SetY(100.0f)
            .SetTime(TimeStamp(moveNanoseconds));
        recognizer->HandleEvent(moveEvent);
        lastTime = TimeStamp(moveNanoseconds);
    }
    TouchEvent upEventOne;
    upEventOne.SetId(0).SetType(TouchType::UP).SetX(600.0f).SetY(100.0f).SetTime(lastTime);
    recognizer->HandleEvent(upEventOne);
}

void DispatchPinchEvent(const RefPtr<NGGestureRecognizer>& recognizer)
{
    recognizer->BeginReferee(0, true);
    recognizer->BeginReferee(1, true);
    TouchEvent downEventOne;
    downEventOne.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventOne);
    TouchEvent downEventTwo;
    downEventTwo.SetId(1).SetType(TouchType::DOWN).SetX(300.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventTwo);
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        TouchEvent moveEventOne;
        moveEventOne.SetId(0).SetType(TouchType::MOVE).SetX(100.0f + static_cast<float>(num) * 10.0f).SetY(100.0f);
        recognizer->HandleEvent(moveEventOne);
        TouchEvent moveEventTwo;
        moveEventTwo.SetId(1).SetType(TouchType::MOVE).SetX(300.0f - static_cast<float>(num) * 10.0f).SetY(100.0f);
        recognizer->HandleEvent(moveEventTwo);
    }
    TouchEvent upEventOne;
    upEventOne.SetId(0).SetType(TouchType::UP).SetX(150.0f).SetY(100.0f);
    recognizer->HandleEvent(upEventOne);
    TouchEvent upEventTwo;
    upEventTwo.SetId(1).SetType(TouchType::UP).SetX(250.0f).SetY(100.0f);
    recognizer->HandleEvent(upEventTwo);
}

void DispatchRotationEvent(const RefPtr<NGGestureRecognizer>& recognizer)
{
    recognizer->BeginReferee(0, true);
    recognizer->BeginReferee(1, true);
    TouchEvent downEventOne;
    downEventOne.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventOne);
    TouchEvent downEventTwo;
    downEventTwo.SetId(1).SetType(TouchType::DOWN).SetX(300.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventTwo);
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        TouchEvent moveEventOne;
        moveEventOne.SetId(0)
            .SetType(TouchType::MOVE)
            .SetX(100.0f + static_cast<float>(num) * 20.0f)
            .SetY(100.0f + static_cast<float>(num) * 20.0f);
        recognizer->HandleEvent(moveEventOne);
        TouchEvent moveEventTwo;
        moveEventTwo.SetId(1)
            .SetType(TouchType::MOVE)
            .SetX(300.0f - static_cast<float>(num) * 20.0f)
            .SetY(100.0f - static_cast<float>(num) * 20.0f);
        recognizer->HandleEvent(moveEventTwo);
    }
    TouchEvent upEventOne;
    upEventOne.SetId(0).SetType(TouchType::UP).SetX(200.0f).SetY(200.0f);
    recognizer->HandleEvent(upEventOne);
    TouchEvent upEventTwo;
    upEventTwo.SetId(1).SetType(TouchType::UP).SetX(200.0f).SetY(0.0f);
    recognizer->HandleEvent(upEventTwo);
}

void DispatchSingleDownSingleMoveEvent(const RefPtr<NGGestureRecognizer>& recognizer)
{
    recognizer->BeginReferee(0, true);
    recognizer->BeginReferee(1, true);
    TouchEvent downEventOne;
    downEventOne.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventOne);
    TouchEvent downEventTwo;
    downEventTwo.SetId(1).SetType(TouchType::DOWN).SetX(300.0f).SetY(100.0f);
    recognizer->HandleEvent(downEventTwo);
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        TouchEvent moveEventTwo;
        moveEventTwo.SetId(1).SetType(TouchType::MOVE).SetX(300.0f + static_cast<float>(num) * 20.0f).SetY(100.0f);
        recognizer->HandleEvent(moveEventTwo);
    }
}

} // namespace

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_GESTURES_RECOGNIZER_GROUP_TEST_UTILS_H