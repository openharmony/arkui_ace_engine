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
#include "ui/base/utils/utils.h"

#define private public
#define protected public

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/utils/system_properties.h"
#include "frameworks/core/event/coasting_axis_event_generator.h"
#undef private
#undef protected

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_constants.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t MAX_DIFF_VSYNC_TIME = 100 * 1000 * 1000; // max 100 ms
constexpr uint32_t MIN_DIFF_VSYNC_TIME = 1000 * 1000;       // min 1 ms

struct CoastingAxisEventGeneratorTestCase {
    double verticalAxis = 0.0;
    double horizontalAxis = 0.0;
    SourceType sourceType = SourceType::MOUSE;
    SourceTool sourceTool = SourceTool::TOUCHPAD;
    AxisAction action = AxisAction::UPDATE;
    CoastingAxisPhase phase = CoastingAxisPhase::NONE;
    CoastingAxisPhase expectPhase = CoastingAxisPhase::NONE;
    double expectPos = 0.0;
    double delta = 50.0;
    bool axisResultEmpty = true;
};
} // namespace

class CoastingAxisEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

protected:
    static testing::AssertionResult CheckCoastingAxisEventPos(int32_t caseNum, double currentPos, double expectPos);
    static testing::AssertionResult CheckCoastingAxisEventPhase(
        int32_t caseNum, CoastingAxisPhase currentPhase, CoastingAxisPhase expectPhase);

    RefPtr<CoastingAxisEventGenerator> generator_;
    RefPtr<FrameNode> node_;
    TimeStamp curTimeStamp_;
};

void CoastingAxisEventTestNg::SetUpTestSuite()
{
    // do nothing
    GTEST_LOG_(INFO) << "CoastingAxisEventTestNg SetUpTestSuite";
}

void CoastingAxisEventTestNg::TearDownTestSuite()
{
    // do nothing
    GTEST_LOG_(INFO) << "CoastingAxisEventTestNg TearDownTestSuite";
}

void CoastingAxisEventTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    node_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>());
    generator_ = AceType::MakeRefPtr<CoastingAxisEventGenerator>();
    generator_->SetAxisToTouchConverter([](const AxisEvent& event) {
        auto pipe = MockPipelineContext::GetCurrent();
        CHECK_NULL_RETURN(pipe, TouchEvent());
        auto eventMgr = pipe->GetEventManager();
        return eventMgr->ConvertAxisEventToTouchEvent(event);
    });
    auto now = std::chrono::system_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    curTimeStamp_ = TimeStamp(microseconds);
    SystemProperties::isVelocityWithoutUpPoint_ = false;
}

void CoastingAxisEventTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    SystemProperties::isVelocityWithoutUpPoint_ = true;
}

testing::AssertionResult CoastingAxisEventTestNg::CheckCoastingAxisEventPos(
    int32_t caseNum, double currentPos, double expectPos)
{
    if (currentPos == expectPos) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "TestCaseNum: " << caseNum << ", actual pos: " << currentPos
                                       << ", expect pos: " << expectPos;
}

testing::AssertionResult CoastingAxisEventTestNg::CheckCoastingAxisEventPhase(
    int32_t caseNum, CoastingAxisPhase currentPhase, CoastingAxisPhase expectPhase)
{
    if (currentPhase == expectPhase) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "TestCaseNum: " << caseNum
                                       << ", actual phase: " << static_cast<int32_t>(currentPhase)
                                       << ", expect phase: " << static_cast<int32_t>(expectPhase);
}

const static std::vector<CoastingAxisEventGeneratorTestCase> coastingAxisEventGeneratorTestCases = {
    {
        .sourceType = SourceType::NONE,
    },
    { .sourceTool = SourceTool::MOUSE },
    { .sourceTool = SourceTool::UNKNOWN },
    { .sourceTool = SourceTool::MOUSE, .phase = CoastingAxisPhase::UPDATE },
    { .verticalAxis = 10, .action = AxisAction::BEGIN },
    { .verticalAxis = 10, .expectPos = 10 },
    { .verticalAxis = 30, .horizontalAxis = 40, .expectPos = 50 },
    { .verticalAxis = 10, .action = AxisAction::END, .expectPos = 0 },
    { .verticalAxis = 10, .action = AxisAction::NONE, .expectPos = 0 },
    { .verticalAxis = 10, .action = AxisAction::END, .delta = 10, .expectPos = 0 },
    { .verticalAxis = 10,
        .action = AxisAction::END,
        .axisResultEmpty = false,
        .expectPhase = CoastingAxisPhase::BEGIN,
        .expectPos = -50 },
    { .horizontalAxis = 10, .action = AxisAction::END, .expectPhase = CoastingAxisPhase::NONE, .expectPos = 0 },
    { .action = AxisAction::END, .expectPhase = CoastingAxisPhase::NONE, .expectPos = 0 },
    { .horizontalAxis = 10,
        .verticalAxis = 10,
        .action = AxisAction::END,
        .expectPhase = CoastingAxisPhase::NONE,
        .expectPos = 0 },
};

/**
 * @tc.name: CoastingAxisEventTestNg001
 * @tc.desc: Create CoastingAxisEventGenerator and output current offset
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg001, TestSize.Level1)
{
    ASSERT_NE(node_, nullptr);
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    int32_t caseNum = 0;
    for (auto& testCase : coastingAxisEventGeneratorTestCases) {
        generator_->ResetState();
        generator_->animationHandler_->ResetHandler();
        /**
         * @tc.steps: step1. Create AxisEvent and set action and sourceType
         */
        AxisEvent axisEvent;
        axisEvent.verticalAxis = testCase.verticalAxis;
        axisEvent.horizontalAxis = testCase.horizontalAxis;
        axisEvent.sourceType = testCase.sourceType;
        axisEvent.sourceTool = testCase.sourceTool;
        axisEvent.action = testCase.action;
        axisEvent.time = curTimeStamp_;
        generator_->animationHandler_->phase_ = testCase.phase;
        if (testCase.action == AxisAction::END) {
            generator_->HandleAxisBeginEvent(axisEvent);
            axisEvent.time = curTimeStamp_ + std::chrono::milliseconds(100);
            axisEvent.verticalAxis = testCase.verticalAxis + testCase.delta;
        }
        if (!testCase.axisResultEmpty) {
            auto target = AceType::MakeRefPtr<AxisEventTarget>();
            generator_->axisResult_.push_back(target);
        }
        generator_->NotifyAxisEvent(axisEvent, node_);
        EXPECT_TRUE(CoastingAxisEventTestNg::CheckCoastingAxisEventPos(
            caseNum, generator_->velocityTracker_.GetMainAxisPos(), testCase.expectPos));
        EXPECT_TRUE(CoastingAxisEventTestNg::CheckCoastingAxisEventPhase(
            caseNum, generator_->animationHandler_->phase_, testCase.expectPhase));
        caseNum++;
    }
}

/**
 * @tc.name: CoastingAxisEventTestNg002
 * @tc.desc: Test GetMainOffset for all axis_ branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg002, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    Offset offset(3.0, 4.0);

    // Axis::FREE
    generator_->axis_ = Axis::FREE;
    EXPECT_EQ(generator_->GetMainOffset(offset), 5.0);

    // Axis::HORIZONTAL
    generator_->axis_ = Axis::HORIZONTAL;
    EXPECT_EQ(generator_->GetMainOffset(offset), 3.0);

    // Axis::VERTICAL
    generator_->axis_ = Axis::VERTICAL;
    EXPECT_EQ(generator_->GetMainOffset(offset), 4.0);

    // default
    generator_->axis_ = static_cast<Axis>(999);
    EXPECT_EQ(generator_->GetMainOffset(offset), 0.0);
}

/**
 * @tc.name: CoastingAxisEventTestNg003
 * @tc.desc: test DispatchCoastingAxisEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg003, TestSize.Level1)
{
    ASSERT_NE(node_, nullptr);
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);

    generator_->axisResult_.clear();
    generator_->animationHandler_->DispatchCoastingAxisEvent(CoastingAxisPhase::BEGIN, 1.0f, 2.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());

    auto targetTrue = AceType::MakeRefPtr<AxisEventTarget>();
    targetTrue->SetOnCoastingAxisCallback(nullptr);
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(targetTrue);
    generator_->animationHandler_->DispatchCoastingAxisEvent(CoastingAxisPhase::END, 5.0f, 6.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    bool callbackCalled1 = false;
    targetTrue->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        callbackCalled1 = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::UPDATE);
        EXPECT_EQ(info.GetHorizontalAxis(), 3.0f);
        EXPECT_EQ(info.GetVerticalAxis(), 4.0f);
        info.SetStopPropagation(true);
    });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(targetTrue);
    generator_->animationHandler_->DispatchCoastingAxisEvent(CoastingAxisPhase::UPDATE, 3.0f, 4.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(callbackCalled1);

    auto targetFalse = AceType::MakeRefPtr<AxisEventTarget>();
    bool callbackCalled2 = false;
    targetFalse->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        callbackCalled2 = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::END);
        info.SetStopPropagation(false);
    });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(targetFalse);
    generator_->animationHandler_->DispatchCoastingAxisEvent(CoastingAxisPhase::END, 5.0f, 6.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(callbackCalled2);
}

/**
 * @tc.name: CoastingAxisEventTestNg004
 * @tc.desc: test DispatchCoastingAxisEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg004, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    auto targetFirst = AceType::MakeRefPtr<AxisEventTarget>();
    auto targetSecond = AceType::MakeRefPtr<AxisEventTarget>();
    bool firstCalled = false;
    bool secondCalled = false;
    targetFirst->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        firstCalled = true;
        info.SetStopPropagation(true);
    });
    targetSecond->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) { secondCalled = true; });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(targetFirst);
    generator_->axisResult_.push_back(targetSecond);
    generator_->animationHandler_->DispatchCoastingAxisEvent(CoastingAxisPhase::UPDATE, 7.0f, 8.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(firstCalled);
    EXPECT_FALSE(secondCalled);
}

/**
 * @tc.name: CoastingAxisEventTestNg005
 * @tc.desc: test DispatchCoastingAxisEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg005, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    auto targetFirst = AceType::MakeRefPtr<AxisEventTarget>();
    auto targetSecond = AceType::MakeRefPtr<AxisEventTarget>();
    bool firstCalled = false;
    bool secondCalled = false;
    targetFirst->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        firstCalled = true;
        info.SetStopPropagation(false);
    });
    targetSecond->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) { secondCalled = true; });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(targetFirst);
    generator_->axisResult_.push_back(targetSecond);
    generator_->animationHandler_->DispatchCoastingAxisEvent(CoastingAxisPhase::UPDATE, 9.0f, 10.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(firstCalled);
    EXPECT_TRUE(secondCalled);
}

/**
 * @tc.name: CoastingAxisEventTestNg006
 * @tc.desc: test DispatchCoastingAxisUpdateEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg006, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    generator_->touchId_ = node_->GetId();
    generator_->animationHandler_->DispatchCoastingAxisUpdateEvent(CoastingAxisPhase::UPDATE, 1.0f, 2.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(generator_->axisResult_.empty());
}

/**
 * @tc.name: CoastingAxisEventTestNg007
 * @tc.desc: test DispatchCoastingAxisUpdateEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg007, TestSize.Level1)
{
    ASSERT_NE(node_, nullptr);
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    generator_->touchId_ = node_->GetId();
    auto targetTrue = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId());
    bool calledTrue = false;
    targetTrue->SetOnCoastingAxisCallback([&calledTrue](CoastingAxisInfo& info) {
        calledTrue = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::END);
        info.SetStopPropagation(true);
    });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(nullptr);
    generator_->axisResult_.push_back(targetTrue);
    generator_->animationHandler_->phase_ = CoastingAxisPhase::UPDATE;
    generator_->animationHandler_->DispatchCoastingAxisUpdateEvent(CoastingAxisPhase::UPDATE, 3.0f, 4.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(calledTrue);
    EXPECT_TRUE(generator_->axisResult_.empty());
}

/**
 * @tc.name: CoastingAxisEventTestNg008
 * @tc.desc: test DispatchCoastingAxisUpdateEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg008, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    generator_->touchId_ = node_->GetId();
    auto target = AceType::MakeRefPtr<AxisEventTarget>();
    bool calledFalse = false;
    target->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        calledFalse = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::UPDATE);
        info.SetStopPropagation(false);
    });
    auto targetFalse = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId());
    bool calledFalse1 = false;
    targetFalse->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        calledFalse1 = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::END);
        info.SetStopPropagation(false);
    });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(target);
    generator_->axisResult_.push_back(nullptr);
    generator_->axisResult_.push_back(targetFalse);
    generator_->animationHandler_->DispatchCoastingAxisUpdateEvent(CoastingAxisPhase::UPDATE, 5.0f, 6.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(calledFalse);
    EXPECT_TRUE(calledFalse1);
    EXPECT_EQ(generator_->axisResult_.size(), 3);
}

/**
 * @tc.name: CoastingAxisEventTestNg009
 * @tc.desc: test DispatchCoastingAxisUpdateEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg009, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    generator_->touchId_ = node_->GetId();
    auto targetA = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId() + 2);
    auto targetB = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId() + 3);
    bool calledA = false;
    bool calledB = false;
    targetA->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        calledA = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::UPDATE);
        info.SetStopPropagation(true);
    });
    targetB->SetOnCoastingAxisCallback([&](CoastingAxisInfo& info) {
        calledB = true;
        info.SetStopPropagation(false);
    });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(targetA);
    generator_->axisResult_.push_back(targetB);
    generator_->animationHandler_->DispatchCoastingAxisUpdateEvent(CoastingAxisPhase::UPDATE, 7.0f, 8.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(calledA);
    EXPECT_FALSE(calledB);
    EXPECT_EQ(generator_->axisResult_.size(), 2);
}

/**
 * @tc.name: CoastingAxisEventTestNg010
 * @tc.desc: test DispatchCoastingAxisUpdateEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg010, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    generator_->touchId_ = node_->GetId();
    auto target = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId() + 1);
    auto target1 = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId());
    bool called = false;
    bool called1 = false;
    target->SetOnCoastingAxisCallback([&called](CoastingAxisInfo& info) {
        called = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::UPDATE);
        info.SetStopPropagation(true);
    });
    target1->SetOnCoastingAxisCallback([&called1](CoastingAxisInfo& info) {
        called1 = true;
        info.SetStopPropagation(false);
    });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(target);
    generator_->axisResult_.push_back(target1);
    generator_->animationHandler_->DispatchCoastingAxisUpdateEvent(CoastingAxisPhase::UPDATE, 9.0f, 10.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(called);
    EXPECT_FALSE(called1);
    EXPECT_EQ(generator_->axisResult_.size(), 1);
}

/**
 * @tc.name: CoastingAxisEventTestNg011
 * @tc.desc: test DispatchCoastingAxisUpdateEvent for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg011, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    generator_->touchId_ = node_->GetId();
    auto target = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId() + 1);
    auto target1 = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId());
    auto target2 = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId() + 2);
    bool called = false;
    bool called1 = false;
    bool called2 = false;
    target->SetOnCoastingAxisCallback([&called](CoastingAxisInfo& info) {
        called = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::UPDATE);
        info.SetStopPropagation(false);
    });
    target1->SetOnCoastingAxisCallback([&called1](CoastingAxisInfo& info) {
        called1 = true;
        EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::END);
        info.SetStopPropagation(true);
    });
    target2->SetOnCoastingAxisCallback([&called2](CoastingAxisInfo& info) {
        called2 = true;
        info.SetStopPropagation(true);
    });
    generator_->axisResult_.clear();
    generator_->axisResult_.push_back(target);
    generator_->axisResult_.push_back(target1);
    generator_->axisResult_.push_back(target2);
    generator_->animationHandler_->DispatchCoastingAxisUpdateEvent(CoastingAxisPhase::UPDATE, 9.0f, 10.0f,
        std::chrono::duration_cast<std::chrono::microseconds>(curTimeStamp_.time_since_epoch()).count());
    EXPECT_TRUE(called);
    EXPECT_TRUE(called1);
    EXPECT_FALSE(called2);
    EXPECT_EQ(generator_->axisResult_.size(), 1);
}

/**
 * @tc.name: CoastingAxisEventTestNg012
 * @tc.desc: test StopFrictionAnimation for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg012, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    auto& handler = *generator_->animationHandler_;

    std::vector<CoastingAxisEventGenerator::StopReason> updateReasons = {
        CoastingAxisEventGenerator::StopReason::MOUSE_INTERRUPT,
        CoastingAxisEventGenerator::StopReason::TOUCH_INTERRUPT,
        CoastingAxisEventGenerator::StopReason::VELOCITY_THRESHOLD,
        CoastingAxisEventGenerator::StopReason::POSITION_TARGET_REACHED
    };

    for (const auto& reason : updateReasons) {
        handler.phase_ = CoastingAxisPhase::UPDATE;
        handler.StopFrictionAnimation(reason);
        EXPECT_EQ(handler.phase_, CoastingAxisPhase::NONE);
    }

    std::vector<CoastingAxisEventGenerator::StopReason> endReasons = {
        CoastingAxisEventGenerator::StopReason::TOUCHPAD_OR_MOUSEWHEEL,
        static_cast<CoastingAxisEventGenerator::StopReason>(999)
    };

    for (const auto& reason : endReasons) {
        handler.phase_ = CoastingAxisPhase::END;
        handler.StopFrictionAnimation(reason);
        EXPECT_EQ(handler.phase_, CoastingAxisPhase::NONE);
    }

    handler.phase_ = CoastingAxisPhase::BEGIN;
    auto target = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId());
    generator_->axisResult_.push_back(target);

    int32_t called = 0;
    target->SetOnCoastingAxisCallback([&called](CoastingAxisInfo& info) {
        called++;
        if (called == 1) {
            EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::BEGIN);
        } else if (called == 2) {
            EXPECT_EQ(info.GetPhase(), CoastingAxisPhase::END);
        }
        info.SetStopPropagation(false);
    });

    handler.StopFrictionAnimation(CoastingAxisEventGenerator::StopReason::MOUSE_INTERRUPT);
    EXPECT_EQ(called, 2);
}

/**
 * @tc.name: CoastingAxisEventTestNg013
 * @tc.desc: test UpdateAnimationFrame for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg013, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    generator_->animationHandler_->finalPosition_ = 100.0;
    generator_->animationHandler_->phase_ = CoastingAxisPhase::END;
    generator_->animationHandler_->UpdateAnimationFrame(100);
    EXPECT_EQ(generator_->animationHandler_->phase_, CoastingAxisPhase::NONE);
    generator_->animationHandler_->finalPosition_ = 0.0;
    auto target = AceType::MakeRefPtr<AxisEventTarget>();
    generator_->axisResult_.push_back(target);
    int32_t called = 0;
    target->SetOnCoastingAxisCallback([&called](CoastingAxisInfo& info) {
        called++;
        info.SetStopPropagation(false);
    });
    generator_->animationHandler_->lastVsyncTime_ = 0;
    MockPipelineContext::GetCurrent()->vsyncTime_ = MIN_DIFF_VSYNC_TIME - 1;
    generator_->animationHandler_->phase_ = CoastingAxisPhase::END;
    generator_->animationHandler_->UpdateAnimationFrame(100);
    EXPECT_EQ(called, 0);

    generator_->animationHandler_->lastVsyncTime_ = 0;
    MockPipelineContext::GetCurrent()->vsyncTime_ = MAX_DIFF_VSYNC_TIME + 1;
    generator_->animationHandler_->phase_ = CoastingAxisPhase::END;
    generator_->animationHandler_->UpdateAnimationFrame(100);
    EXPECT_EQ(called, 0);

    generator_->animationHandler_->lastVsyncTime_ = 0;
    MockPipelineContext::GetCurrent()->vsyncTime_ = MAX_DIFF_VSYNC_TIME / 2;
    generator_->animationHandler_->phase_ = CoastingAxisPhase::END;
    generator_->animationHandler_->UpdateAnimationFrame(100);
    EXPECT_EQ(called, 1);
    EXPECT_EQ(generator_->animationHandler_->phase_, CoastingAxisPhase::NONE);
    EXPECT_TRUE(generator_->axisResult_.empty());

    generator_->axisResult_.push_back(target);
    generator_->animationHandler_->lastVsyncTime_ = 0;
    MockPipelineContext::GetCurrent()->vsyncTime_ = MAX_DIFF_VSYNC_TIME / 2;
    generator_->animationHandler_->phase_ = CoastingAxisPhase::UPDATE;
    generator_->animationHandler_->lastPosition_ = 0;
    generator_->animationHandler_->UpdateAnimationFrame(100);
    EXPECT_EQ(called, 2);

    generator_->animationHandler_->lastVsyncTime_ = 0;
    MockPipelineContext::GetCurrent()->vsyncTime_ = MAX_DIFF_VSYNC_TIME / 2;
    generator_->animationHandler_->phase_ = CoastingAxisPhase::BEGIN;
    generator_->animationHandler_->lastPosition_ = 0;
    generator_->animationHandler_->UpdateAnimationFrame(100);
    EXPECT_EQ(called, 3);
    EXPECT_EQ(generator_->animationHandler_->phase_, CoastingAxisPhase::UPDATE);
}

/**
 * @tc.name: CoastingAxisEventTestNg014
 * @tc.desc: test CalculateFinalPosition for all phase branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg014, TestSize.Level1)
{
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    auto& handler = *generator_->animationHandler_;

    generator_->mainVelocity_ = 100.0;
    generator_->originVelocity_ = 0.0;
    generator_->velocityTracker_.velocity_.SetOffsetPerSecond({ 25.0, 30.0 });
    handler.CalculateFinalPosition();
    EXPECT_EQ(handler.velocityRatioX_, 0.0);
    EXPECT_EQ(handler.velocityRatioY_, 0.0);

    generator_->mainVelocity_ = 100.0;
    generator_->originVelocity_ = 50.0;
    generator_->axisDirection_ = Offset(1.0, 1.0);
    generator_->velocityTracker_.velocity_.SetOffsetPerSecond({ 25.0, 30.0 });
    handler.CalculateFinalPosition();
    EXPECT_GT(handler.velocityRatioX_, 0.0);
    EXPECT_GT(handler.velocityRatioY_, 0.0);

    generator_->mainVelocity_ = 100.0;
    generator_->originVelocity_ = 50.0;
    generator_->axisDirection_ = Offset(-1.0, -1.0);
    generator_->velocityTracker_.velocity_.SetOffsetPerSecond({ 25.0, 30.0 });
    handler.CalculateFinalPosition();
    EXPECT_LT(handler.velocityRatioX_, 0.0);
    EXPECT_LT(handler.velocityRatioY_, 0.0);

    generator_->mainVelocity_ = 100.0;
    generator_->originVelocity_ = 50.0;
    generator_->axisDirection_ = Offset(1.0, 1.0);
    generator_->velocityTracker_.velocity_.SetOffsetPerSecond({ -25.0, -30.0 });
    handler.CalculateFinalPosition();
    EXPECT_GT(handler.velocityRatioX_, 0.0);
    EXPECT_GT(handler.velocityRatioY_, 0.0);

    generator_->mainVelocity_ = 100.0;
    generator_->originVelocity_ = 50.0;
    generator_->axisDirection_ = Offset(-1.0, -1.0);
    generator_->velocityTracker_.velocity_.SetOffsetPerSecond({ -25.0, -30.0 });
    handler.CalculateFinalPosition();
    EXPECT_LT(handler.velocityRatioX_, 0.0);
    EXPECT_LT(handler.velocityRatioY_, 0.0);

    generator_->mainVelocity_ = 100.0;
    generator_->originVelocity_ = 50.0;
    generator_->axisDirection_ = Offset(1.0, 1.0);
    generator_->velocityTracker_.velocity_.SetOffsetPerSecond({ 0.0, 0.0 });
    handler.CalculateFinalPosition();
    EXPECT_EQ(handler.velocityRatioX_, 0.0);
    EXPECT_EQ(handler.velocityRatioY_, 0.0);
}

/**
 * @tc.name: CoastingAxisEventTestNg015
 * @tc.desc: test NotifyTouchTestResult for all branches
 * @tc.type: FUNC
 */
HWTEST_F(CoastingAxisEventTestNg, CoastingAxisEventTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: init.
     */
    ASSERT_NE(generator_, nullptr);
    ASSERT_NE(generator_->animationHandler_, nullptr);
    ASSERT_NE(node_, nullptr);
    OHOS::Ace::ElementRegister::GetInstance()->AddUINode(node_);
    generator_->animationHandler_->phase_ = CoastingAxisPhase::BEGIN;
    generator_->axisResult_.clear();
    /**
     * @tc.steps: id match.
     */
    auto axisTarget1 = AceType::MakeRefPtr<AxisEventTarget>(node_->GetTag(), node_->GetId());
    generator_->axisResult_.push_back(axisTarget1);
    auto touchEventActuator = AceType::MakeRefPtr<TouchEventActuator>();
    touchEventActuator->SetNodeId(node_->GetId());
    TouchTestResult touchTestResult;
    touchTestResult.emplace_back(touchEventActuator);
    generator_->NotifyTouchTestResult(touchTestResult, PointF(0, 0));
    EXPECT_EQ(generator_->touchId_, node_->GetId());
    /**
     * @tc.steps: id not match, region match.
     */
    generator_->touchId_ = -1;
    touchEventActuator->nodeId_ = node_->GetId() + 1;
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    mockRenderContext->rect_ = RectF(0, 0, 100, 100);
    node_->renderContext_ = mockRenderContext;
    generator_->NotifyTouchTestResult(touchTestResult, PointF(10, 10));
    EXPECT_EQ(generator_->touchId_, node_->GetId());
    /**
     * @tc.steps: id and region not match.
     */
    touchEventActuator->nodeId_ = node_->GetId() + 2;
    generator_->NotifyTouchTestResult(touchTestResult, PointF(999, 999));
    EXPECT_EQ(generator_->touchId_, -1);
    /**
     * @tc.steps: axisResult_ empty.
     */
    generator_->axisResult_.clear();
    touchTestResult.emplace_back(touchEventActuator);
    generator_->NotifyTouchTestResult(touchTestResult, PointF(0, 0));
    EXPECT_EQ(generator_->touchId_, -1);
}
} // namespace OHOS::Ace::NG
