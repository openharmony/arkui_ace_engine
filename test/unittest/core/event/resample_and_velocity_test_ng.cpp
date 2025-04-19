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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <fstream>
#include <random>

#define private public
#define protected public

#include "core/components_ng/event/touch_event.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;
using OHOS::Ace::TimeStamp;

namespace OHOS::Ace {

int64_t GetDeltaT(TimeStamp time, TimeStamp base)
{
    auto deltaT = time - base;
    return std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count();
}

void GenerateCSV(const std::string& fileName, TimeStamp baseTime,
                 const std::vector<TouchEvent>& tp, 
                 const std::vector<TouchEvent>& common, 
                 const std::vector<TouchEvent>& accelarate)
{
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Cannot open the file: " << fileName << std::endl;
        return;
    }

    // write head
    file << "TpTime,TpDisplacement,"
         << "CommonTime,CommonDisplacement,"
         << "AccelarateTime,AccelarateDisplacement\n";
    size_t maxSize = std::max({tp.size(), common.size(), accelarate.size()});

    // write data
    for (size_t i = 0; i < maxSize; ++i) {
        if (i < tp.size()) {
            double d = std::sqrt(tp[i].x * tp[i].x + tp[i].y * tp[i].y);
            file << GetDeltaT(tp[i].time, baseTime) << "," << d;
        } else {
            file << ",";
        }

        if (i < common.size()) {
            double d = std::sqrt(common[i].x * common[i].x + common[i].y * common[i].y);
            file << "," << GetDeltaT(common[i].time, baseTime) << "," << d;
        } else {
            file << ",,";
        }

        if (i < accelarate.size()) {
            double d = std::sqrt(accelarate[i].x * accelarate[i].x + accelarate[i].y * accelarate[i].y);
            file << "," << GetDeltaT(accelarate[i].time, baseTime) << "," << d << "\n";
        } else {
            file << ",,\n";
        }
    }
    file.close();
}

class MockEventManager : public EventManager {
    DECLARE_ACE_TYPE(MockEventManager, OHOS::Ace::EventManager);

public:
    MockEventManager() = default;
    ~MockEventManager() override = default;

    MOCK_METHOD(bool, DispatchTouchEvent, (const TouchEvent&, bool));
};

using NiceEventManager = NiceMock<MockEventManager>;

namespace NG {
enum TestTouchTrackingMode {
    FAST_FLICK,
    DECELARATING,
    CONSTANT_SPEED,
    SLOW_CONSTANT_SPEED,
};

class ResampleTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    static bool TestOnTouchEvent(const TouchEvent& event, bool sendOnTouch);
    static vector<TouchEvent> events_;
    static vector<TouchEvent> oriEvents_;
    static RefPtr<PipelineContext> pipeline_;

    void SetUp() override;
    void TearDown() override;

    /* simulate functions */
    void GenerateTouchEvents(double a, double b, double c, uint32_t duration, double angle);
    void RunVsync(int32_t vsyncPeriodMs);
    TouchEvent GetPhysicPoint(TimeStamp time);
    TouchEvent GetOriginPoint(TimeStamp time);

    /* test functions */
    double GetTouchEventsCoordVariance();
    double GetTouchEventsSmothDiff();
    double CompareAccelarate(TestTouchTrackingMode mode, int32_t frameRate);

    static constexpr uint32_t TP_RATE = 140;

    TimeStamp nowTime_;
};

std::vector<TouchEvent> ResampleTestNg::events_;
std::vector<TouchEvent> ResampleTestNg::oriEvents_;
std::vector<double> coefs_;
RefPtr<PipelineContext> ResampleTestNg::pipeline_;

void ResampleTestNg::SetUpTestSuite()
{
    pipeline_ = AceType::MakeRefPtr<PipelineContext>();
    pipeline_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto mockEventManager = AceType::MakeRefPtr<NiceEventManager>();
    pipeline_->eventManager_ = mockEventManager;
    ON_CALL((*mockEventManager), DispatchTouchEvent(testing::_, testing::_)).WillByDefault(testing::Invoke([](const TouchEvent& event, bool sendOnTouch) {
            return TestOnTouchEvent(event, sendOnTouch);
        }));
}

void ResampleTestNg::TearDownTestSuite()
{
    pipeline_ = nullptr;
}

void ResampleTestNg::SetUp()
{
    nowTime_ = std::chrono::high_resolution_clock::now();
}

void ResampleTestNg::TearDown()
{
    events_.clear();
    oriEvents_.clear();
}

TouchEvent ResampleTestNg::GetPhysicPoint(TimeStamp time)
{
    auto deltaT = time - nowTime_;
    int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count();
    double d = coefs_[0] * t * t + coefs_[1] * t + coefs_[2];
    TouchEvent event;
    double cosTheta = std::cos(coefs_[3]);
    double sinTheta = std::sin(coefs_[3]);
    event.SetX(d * cosTheta);
    event.SetY(d * sinTheta);
    return event;
}

TouchEvent ResampleTestNg::GetOriginPoint(TimeStamp time)
{
    auto deltaT = time - nowTime_;
    int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count();
    return oriEvents_[t * TP_RATE / 1000];
}

void ResampleTestNg::GenerateTouchEvents(double a, double b, double c, uint32_t duration, double angle) {
    coefs_.assign({a, b, c, angle});
    std::vector<TouchEvent> events;
    uint32_t samplingRate = TP_RATE;
    std::chrono::microseconds dt(1000000 / samplingRate);
    std::chrono::microseconds deltaT(0);
    std::chrono::milliseconds durationMs(duration);
    double cosTheta = std::cos(angle);
    double sinTheta = std::sin(angle);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noise(0.0, 0.7);

    // touch down
    TouchEvent event;
    event.SetId(0.0)
        .SetX(0.0)
        .SetY(0.0)
        .SetType(TouchType::DOWN)
        .SetTime(nowTime_);
    oriEvents_.emplace_back(event);

    event.SetType(TouchType::MOVE);
    do {
        deltaT += dt;
        double t = deltaT.count() / 1000;
        double d = a * t * t + b * t + c;
        event.SetX(d * cosTheta + noise(gen));
        event.SetY(d * sinTheta + noise(gen));
        event.SetTime(deltaT + nowTime_);
        oriEvents_.emplace_back(event);
    } while (deltaT < durationMs);
}

void ResampleTestNg::RunVsync(int32_t vsyncPeriodUs)
{
    std::chrono::microseconds vsyncPeriod(1000000 / vsyncPeriodUs);
    constexpr int64_t delay = 3000000; // simulate the 3ms delay between vsync and driver time of event
    int32_t i = 0;
    auto vsyncTime = nowTime_;
    while (i < oriEvents_.size()) {
        while (i < oriEvents_.size() && oriEvents_[i].time < vsyncTime) {
            pipeline_->touchEvents_.emplace_back(oriEvents_[i]);
            i++;
        }
        int64_t vsynTimeNs = vsyncTime.time_since_epoch().count();
        pipeline_->SetVsyncTime(vsynTimeNs + delay);
        pipeline_->FlushTouchEvents();
        vsyncTime += vsyncPeriod;
    }
}

bool ResampleTestNg::TestOnTouchEvent(const TouchEvent& event, bool sendOnTouch)
{
    events_.emplace_back(event);
    return true;
}

double ResampleTestNg::GetTouchEventsCoordVariance()
{
    double variance = 0;
    for (int32_t i = 0; i < events_.size(); ++i) {
        // auto base = GetPhysicPoint(events_[i].time);
        auto base = GetOriginPoint(events_[i].time);
        double dx = events_[i].x - base.x;
        double dy = events_[i].y - base.y;
        variance += dx * dx + dy * dy;
    }
    return variance / events_.size();
}

double ResampleTestNg::GetTouchEventsSmothDiff()
{
    return 0.0f;
}

double ResampleTestNg::CompareAccelarate(TestTouchTrackingMode mode, int32_t frameRate)
{
    switch (mode) {
        case FAST_FLICK:
            GenerateTouchEvents(-0.0005, 0.8, 0, 500, 0);
            break;
        case DECELARATING:
            GenerateTouchEvents(-0.0001, 0.3, 0, 800, M_PI / 6);
            break;
        case CONSTANT_SPEED:
            GenerateTouchEvents(0, 0.2, 0, 1000, M_PI / 4);
            break;
        case SLOW_CONSTANT_SPEED:
            GenerateTouchEvents(0, 0.05, 0, 1000, M_PI / 3);
            break;
    }
    pipeline_->touchAccelarate_ = false;
    RunVsync(frameRate);
    auto commonEvents = events_;
    events_.clear();
    pipeline_->touchAccelarate_ = true;
    RunVsync(frameRate);
    // double accelarateVar = GetTouchEventsCoordVariance();
    GenerateCSV("/data/log/faultlog/resample.csv", nowTime_, oriEvents_, commonEvents, events_);

    return 0.0;
}

/**
 * @tc.name: ResampleTest60HzCommon
 * @tc.desc: Construct touch events and test resample sequence in 60Hz vsync.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTest60HzFastFlick, TestSize.Level1)
{
    constexpr int32_t repeatTimes = 1;
    int32_t failTimes = 0;
    double accumulateVar = 0;
    for (int32_t i = 0; i < repeatTimes; ++i) {
        accumulateVar += CompareAccelarate(FAST_FLICK, 60);
        if (accumulateVar < 0) {
            ++failTimes;
        }
    }
}
}
}