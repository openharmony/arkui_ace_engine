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

#include <fstream>
#include <random>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

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
PointerEvent CalculateParabola(double a, double b, double c, double t, double angle)
{
    double d = a * t * t + b * t + c;
    PointerEvent p;
    p.x = d * std::cos(angle);
    p.y = d * std::sin(angle);
    return p;
}

std::vector<TouchEvent> Get1stOrderDiff(const std::vector<TouchEvent>& events)
{
    std::vector<TouchEvent> diff;
    for (int32_t i = 1; i < events.size(); ++i) {
        TouchEvent p;
        p.x = events[i].x - events[i - 1].x;
        p.y = events[i].y - events[i - 1].y;
        diff.push_back(p);
    }
    return diff;
}

std::vector<TouchEvent> Get2ndOrderDiff(const std::vector<TouchEvent>& events)
{
    std::vector<TouchEvent> diff = Get1stOrderDiff(events);
    return Get1stOrderDiff(diff);
}

bool IsSmoothBy2ndOrderDiff(const std::vector<TouchEvent>& events)
{
    auto diff = Get2ndOrderDiff(events);
    for (int32_t i = 1; i < diff.size(); ++i) {
        if (diff[i].x * diff[i - 1].x < 0 || diff[i].y * diff[i - 1].y < 0) {
            return false;
        }
    }
    return true;
}

double IsSmoothBy1stOrderDiff(const std::vector<TouchEvent>& events)
{
    auto diff = Get1stOrderDiff(events);
    double xAccumulate = 0;
    for (auto& item : diff) {
        xAccumulate += item.x;
    }
    double xMean = xAccumulate / diff.size();

    xAccumulate = 0;
    for (auto& item : diff) {
        xAccumulate += std::pow(item.x - xMean, 2);
    }
    return std::sqrt(xAccumulate / diff.size()) / xMean;
}

int64_t GetDeltaT(TimeStamp time, TimeStamp base)
{
    auto deltaT = time - base;
    return std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count();
}

void GenerateCSV(const std::string& fileName, TimeStamp baseTime, const std::vector<TouchEvent>& tp,
    const std::vector<TouchEvent>& common, const std::vector<TouchEvent>& accelarate)
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
    size_t maxSize = std::max({ tp.size(), common.size(), accelarate.size() });

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

struct TestResult {
    bool isSmooth;
    double stddevAgainstPhy;
    double stddevOfUniformSpeed;
};

class MockEventManager : public EventManager {
    DECLARE_ACE_TYPE(MockEventManager, OHOS::Ace::EventManager);

public:
    MockEventManager() = default;
    ~MockEventManager() override = default;

    MOCK_METHOD(bool, DispatchTouchEvent, (const TouchEvent&, bool));
};

using NiceEventManager = NiceMock<MockEventManager>;

namespace NG {
using Generator = std::function<PointerEvent(double)>;
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
    void SetGenerator(Generator&& f);
    void GenerateTouchEvents(uint32_t duration);
    void RunVsync(int32_t vsyncPeriodMs);
    PointerEvent GetPhysicPoint(TimeStamp time);
    TouchEvent GetOriginPoint(TimeStamp time);

    /* test functions */
    double GetCoordsDiffAgainstPhy();

    static constexpr uint32_t TP_RATE = 6000;
    static constexpr double NOISE_STD_DEV = 0.7;

    TimeStamp nowTime_;
    Generator func_;
};

std::vector<TouchEvent> ResampleTestNg::events_;
std::vector<TouchEvent> ResampleTestNg::oriEvents_;
RefPtr<PipelineContext> ResampleTestNg::pipeline_;

void ResampleTestNg::SetUpTestSuite()
{
    pipeline_ = AceType::MakeRefPtr<PipelineContext>();
    pipeline_->touchAccelarate_ = true;
    pipeline_->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto mockEventManager = AceType::MakeRefPtr<NiceEventManager>();
    pipeline_->eventManager_ = mockEventManager;
    ON_CALL((*mockEventManager), DispatchTouchEvent(testing::_, testing::_))
        .WillByDefault(testing::Invoke(
            [](const TouchEvent& event, bool sendOnTouch) { return TestOnTouchEvent(event, sendOnTouch); }));
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
    func_ = nullptr;
}

PointerEvent ResampleTestNg::GetPhysicPoint(TimeStamp time)
{
    auto deltaT = time - nowTime_;
    int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count();
    return func_(t);
}

TouchEvent ResampleTestNg::GetOriginPoint(TimeStamp time)
{
    auto deltaT = time - nowTime_;
    int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(deltaT).count();
    return oriEvents_[t * TP_RATE / 1000];
}

void ResampleTestNg::SetGenerator(Generator&& f)
{
    func_ = std::move(f);
}

void ResampleTestNg::GenerateTouchEvents(uint32_t duration)
{
    std::vector<TouchEvent> events;
    uint32_t samplingRate = TP_RATE;
    std::chrono::microseconds dt(1000000 / samplingRate);
    std::chrono::microseconds deltaT(0);
    std::chrono::milliseconds durationMs(duration);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noise(0.0, 0.7);

    // touch down
    TouchEvent event;
    event.SetId(0.0).SetX(0.0).SetY(0.0).SetType(TouchType::DOWN).SetTime(nowTime_);
    oriEvents_.clear();
    oriEvents_.emplace_back(event);

    event.SetType(TouchType::MOVE);
    do {
        deltaT += dt;
        double t = deltaT.count() / 1000;
        PointerEvent p = func_(t);
        event.SetX(p.x);
        event.SetY(p.y);
        event.SetTime(deltaT + nowTime_);
        oriEvents_.emplace_back(event);
    } while (deltaT < durationMs);
}

void ResampleTestNg::RunVsync(int32_t vsyncPeriodUs)
{
    std::chrono::microseconds vsyncPeriod(1000000 / vsyncPeriodUs);
    constexpr int64_t delay = 2000000; // simulate the 3ms delay between vsync and sensor time of event
    int32_t i = 0;
    auto vsyncTime = nowTime_;
    int32_t cnt = 0;
    uint64_t microSec = 0;
    while (i < oriEvents_.size()) {
        while (i < oriEvents_.size() && oriEvents_[i].time < vsyncTime) {
            pipeline_->touchEvents_.emplace_back(oriEvents_[i]);
            i++;
        }
        int64_t vsynTimeNs = vsyncTime.time_since_epoch().count();
        pipeline_->SetVsyncTime(vsynTimeNs + delay);
        auto startTime = std::chrono::high_resolution_clock::now();
        pipeline_->FlushTouchEvents();
        auto endTime = std::chrono::high_resolution_clock::now();
        vsyncTime += vsyncPeriod;
        ++cnt;
        microSec += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    }
    std::cout << "lyc " << cnt << " "<< microSec / cnt << std::endl;
}

bool ResampleTestNg::TestOnTouchEvent(const TouchEvent& event, bool sendOnTouch)
{
    events_.emplace_back(event);
    return true;
}

double ResampleTestNg::GetCoordsDiffAgainstPhy()
{
    double variance = 0;
    for (int32_t i = 0; i < events_.size(); ++i) {
        auto base = GetPhysicPoint(events_[i].time);
        // auto base = GetOriginPoint(events_[i].time);
        double dx = events_[i].x - base.x;
        double dy = events_[i].y - base.y;
        variance += dx * dx + dy * dy;
    }
    return variance / events_.size();
}

/**
 * @tc.name: ResampleTest60HzCommon
 * @tc.desc: Construct touch events and test resample sequence in 60Hz vsync.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTest60HzFastFlick, TestSize.Level1)
{
    constexpr int32_t repeatTimes = 10;
    double accumulateVar = 0;
    int32_t smoothCnt = 0;
    SetGenerator([](double t) { return CalculateParabola(-0.0005, 0.8, 0, t, M_PI / 3); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(500);
        RunVsync(30);
        accumulateVar += GetCoordsDiffAgainstPhy();
        smoothCnt += IsSmoothBy2ndOrderDiff(events_) ? 0 : 1;
    }
    TestResult result { 0 };
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes) - NOISE_STD_DEV;
    result.isSmooth = (smoothCnt == 0);

    EXPECT_LT(std::abs(result.stddevAgainstPhy), 0.01);
    EXPECT_LE(result.isSmooth, 0);
}

/**
 * @tc.name: ResampleTest60HzCommon
 * @tc.desc: Construct touch events and test resample sequence in 60Hz vsync.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTest60HzDeceleratingSlide, TestSize.Level1)
{
    constexpr int32_t repeatTimes = 10;
    double accumulateVar = 0;
    int32_t smoothCnt = 0;
    SetGenerator([](double t) { return CalculateParabola(-0.0001, 0.3, 0, t, M_PI / 6); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(800);
        RunVsync(60);
        accumulateVar += GetCoordsDiffAgainstPhy();
        smoothCnt += IsSmoothBy2ndOrderDiff(events_) ? 0 : 1;
    }
    TestResult result { 0 };
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes) - NOISE_STD_DEV;
    result.isSmooth = (smoothCnt == 0);

    EXPECT_LT(std::abs(result.stddevAgainstPhy), 0.01);
    EXPECT_LE(result.isSmooth, 0);
}

/**
 * @tc.name: ResampleTest60HzCommon
 * @tc.desc: Construct touch events and test resample sequence in 60Hz vsync.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTest60HzConstantSpeedSlide, TestSize.Level1)
{
    constexpr int32_t repeatTimes = 10;
    double accumulateVar = 0;
    int32_t smoothCnt = 0;
    double variance = 0;
    SetGenerator([](double t) { return CalculateParabola(0, 0.2, 0, t, 0); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(1000);
        RunVsync(120);
        accumulateVar += GetCoordsDiffAgainstPhy();
        smoothCnt += IsSmoothBy2ndOrderDiff(events_) ? 0 : 1;
        variance += IsSmoothBy1stOrderDiff(events_);
    }
    TestResult result { 0 };
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes) - NOISE_STD_DEV;
    result.isSmooth = (smoothCnt == 0);
    result.stddevOfUniformSpeed = variance / repeatTimes - NOISE_STD_DEV;

    EXPECT_LT(std::abs(result.stddevAgainstPhy), 0.01);
    EXPECT_LE(result.isSmooth, 0);
    EXPECT_LT(std::abs(result.stddevOfUniformSpeed), 0.5);
}

/**
 * @tc.name: ResampleTest60HzCommon
 * @tc.desc: Construct touch events and test resample sequence in 60Hz vsync.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTest60HzSlowConstantSpeedSlide, TestSize.Level1)
{
    constexpr int32_t repeatTimes = 10;
    double accumulateVar = 0;
    int32_t smoothCnt = 0;
    double stddev = 0;
    SetGenerator([](double t) { return CalculateParabola(0, 0.05, 0, t, 0); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(1000);
        RunVsync(120);
        accumulateVar += GetCoordsDiffAgainstPhy();
        smoothCnt += IsSmoothBy2ndOrderDiff(events_) ? 0 : 1;
        stddev += IsSmoothBy1stOrderDiff(events_);
    }
    TestResult result { 0 };
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes) - NOISE_STD_DEV;
    result.isSmooth = (smoothCnt == 0);
    result.stddevOfUniformSpeed = std::sqrt(stddev / repeatTimes) - NOISE_STD_DEV;

    EXPECT_LT(std::abs(result.stddevAgainstPhy), 0.01);
    EXPECT_LE(result.isSmooth, 0);
    EXPECT_LT(std::abs(result.stddevOfUniformSpeed), 0.5);
}
} // namespace NG
} // namespace OHOS::Ace