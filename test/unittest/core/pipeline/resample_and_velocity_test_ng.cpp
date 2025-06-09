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

double GetStdDev(const std::vector<TouchEvent>& diff)
{
    double xAccumulate = 0;
    double yAccumulate = 0;
    for (auto& item : diff) {
        xAccumulate += item.x;
        yAccumulate += item.y;
    }
    double xMean = xAccumulate / diff.size();
    double yMean = yAccumulate / diff.size();

    xAccumulate = 0;
    yAccumulate = 0;
    for (auto& item : diff) {
        xAccumulate += std::pow(item.x - xMean, 2);
        yAccumulate += std::pow(item.y - yMean, 2);
    }
    return std::sqrt((xAccumulate + yAccumulate) / diff.size());
}

// using Parabola
double SmoothBy2ndOrderDiff(const std::vector<TouchEvent>& events)
{
    auto diff = Get2ndOrderDiff(events);
    return GetStdDev(diff);
}

// using linear
double Monotonicity(const std::vector<TouchEvent>& events)
{
    auto diff = Get1stOrderDiff(events);
    if (diff.empty()) {
        return 0.0;
    }
    PointerEvent& sign = diff[0];
    for (auto& item : diff) {
        if (item.x * sign.x < 0 || item.y * sign.y < 0) {
            ADD_FAILURE();
        }
    }
    return 0.0;
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
    double stddevOfAcc;          // evaluate smooth
    double stddevAgainstPhy;     // evaluate accuracy
    double stddevOfUniformSpeed; // evalueate stability
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
    void TestFastFlick(int32_t vsyncPeriod, TestResult& result);
    void TestDeceleratingSlide(int32_t vsyncPeriod, TestResult& result);
    void TestConstantSpeedSlide(int32_t vsyncPeriod, TestResult& result);
    void TestSlowConstantSpeedSlide(int32_t vsyncPeriod, TestResult& result);

    static constexpr uint32_t TP_RATE = 140;
    static constexpr double NOISE_STD_DEV = 0.7;
    static constexpr float NEAR_ZERO_DEV = 0.001;

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
    pipeline_->touchEvents_.clear();
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

// Generate a touch sequence with specific duration
void ResampleTestNg::GenerateTouchEvents(uint32_t duration)
{
    std::vector<TouchEvent> events;
    uint32_t samplingRate = TP_RATE;
    std::chrono::microseconds dt(1000000 / samplingRate);
    std::chrono::microseconds deltaT(0);
    std::chrono::milliseconds durationMs(duration);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> noise(0.0, NOISE_STD_DEV);

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
    } while (deltaT <= durationMs);
}

void ResampleTestNg::RunVsync(int32_t vsyncHz)
{
    std::chrono::microseconds vsyncPeriod(1000000 / vsyncHz);
    constexpr int64_t delay = 2000000; // simulate the 2ms delay between vsync and sensor time of event
    int32_t i = 0;
    auto vsyncTime = nowTime_;
    int32_t cnt = 0;
    events_.clear();
    pipeline_->touchEvents_.clear();
    while (i < oriEvents_.size()) {
        while (i < oriEvents_.size() && oriEvents_[i].time < vsyncTime) {
            pipeline_->touchEvents_.emplace_back(oriEvents_[i]);
            i++;
        }
        int64_t vsynTimeNs = vsyncTime.time_since_epoch().count();
        pipeline_->SetVsyncTime(vsynTimeNs + delay);
        pipeline_->FlushTouchEvents();
        pipeline_->resampleTimeStamp_ = vsynTimeNs + delay + 1000000; // instead of mock FlushVsync
        vsyncTime += vsyncPeriod;
        ++cnt;
    }
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
        double dx = events_[i].x - base.x;
        double dy = events_[i].y - base.y;
        variance += dx * dx + dy * dy;
    }
    return variance / events_.size();
}

void ResampleTestNg::TestFastFlick(int32_t vsyncPeriod, TestResult& result)
{
    constexpr int32_t repeatTimes = 1;
    double accumulateVar = 0;
    double accumulateSmooth = 0;
    SetGenerator([](double t) { return CalculateParabola(-0.0005, 0.8, 0, t, M_PI / 3); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(500);
        RunVsync(vsyncPeriod);
        accumulateVar += GetCoordsDiffAgainstPhy();
        accumulateSmooth += SmoothBy2ndOrderDiff(events_);
    }
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes);
    result.stddevOfAcc = accumulateSmooth / repeatTimes;
}

/**
 * @tc.name: ResampleTestFastFlick
 * @tc.desc: Construct touch events and test resample sequence.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTestFastFlick, TestSize.Level1)
{
    TestResult result { 0 };
    pipeline_->touchAccelarate_ = true;
    TestFastFlick(60, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.146);
    EXPECT_LT(result.stddevOfAcc, 0.537);
    TestFastFlick(140, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.226);
    EXPECT_LT(result.stddevOfAcc, 3.956);

    pipeline_->touchAccelarate_ = false;
    TestFastFlick(60, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.212);
    EXPECT_LT(result.stddevOfAcc, 1.634);
    TestFastFlick(140, result);
    EXPECT_LT(result.stddevAgainstPhy, NEAR_ZERO_DEV);
    EXPECT_LT(result.stddevOfAcc, 0.288);
}

void ResampleTestNg::TestDeceleratingSlide(int32_t vsyncPeriod, TestResult& result)
{
    constexpr int32_t repeatTimes = 1;
    double accumulateVar = 0;
    double accumulateSmooth = 0;
    SetGenerator([](double t) { return CalculateParabola(-0.0001, 0.3, 0, t, M_PI / 6); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(500);
        RunVsync(60);
        accumulateVar += GetCoordsDiffAgainstPhy();
        accumulateSmooth += SmoothBy2ndOrderDiff(events_);
    }
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes);
    result.stddevOfAcc = accumulateSmooth / repeatTimes;
}

/**
 * @tc.name: ResampleTestDeceleratingSlide
 * @tc.desc: Construct touch events and test resample sequence.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTestDeceleratingSlide, TestSize.Level1)
{
    TestResult result { 0 };
    pipeline_->touchAccelarate_ = true;
    TestDeceleratingSlide(60, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.065);
    EXPECT_LT(result.stddevOfAcc, 0.357);
    TestDeceleratingSlide(140, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.065);
    EXPECT_LT(result.stddevOfAcc, 0.357);

    pipeline_->touchAccelarate_ = false;
    TestDeceleratingSlide(60, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.098);
    EXPECT_LT(result.stddevOfAcc, 0.625);
    TestDeceleratingSlide(140, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.098);
    EXPECT_LT(result.stddevOfAcc, 0.625);
}

void ResampleTestNg::TestConstantSpeedSlide(int32_t vsyncPeriod, TestResult& result)
{
    constexpr int32_t repeatTimes = 1;
    double accumulateVar = 0;
    double accumulateSmooth = 0;
    pipeline_->touchAccelarate_ = false;
    SetGenerator([](double t) { return CalculateParabola(0, 0.2, 0, t, 0); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(1000);
        RunVsync(60);
        accumulateVar += GetCoordsDiffAgainstPhy();
        accumulateSmooth += Monotonicity(events_);
    }
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes);
    result.stddevOfUniformSpeed = accumulateSmooth / repeatTimes;
}

/**
 * @tc.name: ResampleTestConstantSpeedSlide
 * @tc.desc: Construct touch events and test resample sequence.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTestConstantSpeedSlide, TestSize.Level1)
{
    TestResult result { 0 };
    pipeline_->touchAccelarate_ = true;
    TestConstantSpeedSlide(60, result);
    EXPECT_LT(result.stddevAgainstPhy, NEAR_ZERO_DEV);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.656);
    TestConstantSpeedSlide(140, result);
    EXPECT_LT(result.stddevAgainstPhy, NEAR_ZERO_DEV);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.656);

    pipeline_->touchAccelarate_ = false;
    TestConstantSpeedSlide(60, result);
    EXPECT_LT(result.stddevAgainstPhy, NEAR_ZERO_DEV);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.656);
    TestConstantSpeedSlide(140, result);
    EXPECT_LT(result.stddevAgainstPhy, NEAR_ZERO_DEV);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.656);
}

void ResampleTestNg::TestSlowConstantSpeedSlide(int32_t vsyncPeriod, TestResult& result)
{
    constexpr int32_t repeatTimes = 1;
    double accumulateVar = 0;
    double accumulateSmooth = 0;
    SetGenerator([](double t) { return CalculateParabola(0, 0.05, 0, t, 0); });
    for (int32_t i = 0; i < repeatTimes; ++i) {
        GenerateTouchEvents(1000);
        RunVsync(60);
        accumulateVar += GetCoordsDiffAgainstPhy();
        accumulateSmooth += Monotonicity(events_);
    }
    result.stddevAgainstPhy = std::sqrt(accumulateVar / repeatTimes);
    result.stddevOfUniformSpeed = accumulateSmooth / repeatTimes;
}

/**
 * @tc.name: ResampleTestSlowConstantSpeedSlide
 * @tc.desc: Construct touch events and test resample sequence.
 * @tc.type: FUNC
 */
HWTEST_F(ResampleTestNg, ResampleTestSlowConstantSpeedSlide, TestSize.Level1)
{
    TestResult result { 0 };
    pipeline_->touchAccelarate_ = true;
    TestSlowConstantSpeedSlide(60, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.013);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.086);
    TestSlowConstantSpeedSlide(140, result);
    EXPECT_LT(result.stddevAgainstPhy, 0.013);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.086);

    pipeline_->touchAccelarate_ = false;
    TestSlowConstantSpeedSlide(60, result);
    EXPECT_LT(result.stddevAgainstPhy, NEAR_ZERO_DEV);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.164);
    TestSlowConstantSpeedSlide(140, result);
    EXPECT_LT(result.stddevAgainstPhy, NEAR_ZERO_DEV);
    EXPECT_LT(result.stddevOfUniformSpeed, 0.164);
}

HWTEST_F(ResampleTestNg, ResampleTestRealData01, TestSize.Level1)
{
    pipeline_->touchAccelarate_ = true;
    std::vector<TouchEvent> events;

    TouchEvent event;
    int64_t sinceEpoch = 343641809000; // real trace data
    std::chrono::microseconds us_since_epoch(sinceEpoch);
    TimeStamp stamp(us_since_epoch);
    nowTime_ = stamp;
    event.SetId(0.0).SetX(0.0).SetY(0.0).SetType(TouchType::DOWN).SetTime(stamp);
    oriEvents_.clear();
    oriEvents_.emplace_back(event);

    event.SetType(TouchType::MOVE);
    // real trace data
    std::vector<std::vector<int64_t>> logPoints {
        { 343641816000, 1735, 300 },
        { 343641823000, 1736, 300 },
        { 343641830000, 1738, 300 },
        { 343641837000, 1739, 300 },
        { 343641844000, 1740, 300 },
        { 343641851000, 1742, 300 },
        { 343641858000, 1743, 300 },
        { 343641865000, 1745, 300 },
        { 343641872000, 1746, 300 },
        { 343641879000, 1747, 300 },
        { 343641886000, 1749, 300 },
        { 343641893000, 1750, 300 },
        { 343641900000, 1752, 300 },
        { 343641907000, 1753, 300 },
        { 343641914000, 1754, 300 },
        { 343641921000, 1756, 300 },
        { 343641928000, 1757, 300 },
        { 343641935000, 1759, 300 },
        { 343641942000, 1760, 300 },
        { 343641949000, 1761, 300 },
        { 343641958000, 1763, 300 },
        { 343641963000, 1764, 300 }
    };
    for (const auto& item : logPoints) {
        std::chrono::microseconds msEpoch(item[0]);
        TimeStamp t(msEpoch);
        event.SetX(item[1]).SetY(item[2]).SetTime(t);
        oriEvents_.emplace_back(event);
    }
    events_.clear();
    pipeline_->touchEvents_.clear();

    // real trace data
    std::vector<int64_t> vsyncTime {
        343641803424377,
        343641820086409,
        343641836748819,
        343641853410582,
        343641870072479,
        343641886735032,
        343641903397442,
        343641920059816,
        343641936722405,
        343641953686073,
        343641970348577,
        343641987010997,
        343642003671915
    };
    int32_t vsyncIdx = 0;
    int32_t i = 0;
    while (i < oriEvents_.size()) {
        std::chrono::nanoseconds nsEpoch(vsyncTime[vsyncIdx]);
        TimeStamp t(nsEpoch);
        while (i < oriEvents_.size() && oriEvents_[i].time < t) {
            pipeline_->touchEvents_.emplace_back(oriEvents_[i]);
            i++;
        }
        pipeline_->SetVsyncTime(vsyncTime[vsyncIdx]);
        pipeline_->FlushTouchEvents();
        ++vsyncIdx;
    }
    Monotonicity(events_);
}
} // namespace NG
} // namespace OHOS::Ace