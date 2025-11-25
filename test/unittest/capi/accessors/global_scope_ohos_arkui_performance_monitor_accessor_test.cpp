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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "frameworks/base/utils/utils.h"
#include "test/mock/base/mock_jank_frame_report.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const std::vector<std::pair<Ark_String, std::string>> testFixtureStringValidValues = {
    { Converter::ArkValue<Ark_String>("abc"), "abc" },
    { Converter::ArkValue<Ark_String>(""), "" },
    { Converter::ArkValue<Ark_String>("xyz"), "xyz" },
};
const std::vector<std::pair<Opt_String, std::string>> testFixtureOptStringValues = {
    { Converter::ArkValue<Opt_String>("abc"), "abc" },
    { Converter::ArkValue<Opt_String>(""), "" },
    { Converter::ArkValue<Opt_String>("xyz"), "xyz" },
    { Converter::ArkValue<Opt_String>(Ark_Empty()), "" },
};
const std::vector<std::pair<Ark_PerfMonitorActionType, PerfActionType>> testFixturePerfActionTypeValues = {
    { Ark_PerfMonitorActionType::ARK_PERF_MONITOR_ACTION_TYPE_FIRST_MOVE, PerfActionType::FIRST_MOVE },
    { Ark_PerfMonitorActionType::ARK_PERF_MONITOR_ACTION_TYPE_LAST_DOWN, PerfActionType::LAST_DOWN },
    { Ark_PerfMonitorActionType::ARK_PERF_MONITOR_ACTION_TYPE_LAST_UP, PerfActionType::LAST_UP },
    { static_cast<Ark_PerfMonitorActionType>(-1), PerfActionType::UNKNOWN_ACTION },
    { static_cast<Ark_PerfMonitorActionType>(INT_MAX), PerfActionType::UNKNOWN_ACTION },
};
const std::vector<std::pair<Ark_PerfMonitorSourceType, PerfSourceType>> testFixturePerfSourceTypeValues = {
    { Ark_PerfMonitorSourceType::ARK_PERF_MONITOR_SOURCE_TYPE_PERF_JOYSTICK_EVENT, PerfSourceType::PERF_JOY_STICK },
    { Ark_PerfMonitorSourceType::ARK_PERF_MONITOR_SOURCE_TYPE_PERF_KEY_EVENT, PerfSourceType::PERF_KEY_EVENT },
    { Ark_PerfMonitorSourceType::ARK_PERF_MONITOR_SOURCE_TYPE_PERF_MOUSE_EVENT, PerfSourceType::PERF_MOUSE_EVENT },
    { Ark_PerfMonitorSourceType::ARK_PERF_MONITOR_SOURCE_TYPE_PERF_TOUCH_EVENT, PerfSourceType::PERF_TOUCH_EVENT },
    { Ark_PerfMonitorSourceType::ARK_PERF_MONITOR_SOURCE_TYPE_PERF_TOUCHPAD_EVENT, PerfSourceType::PERF_TOUCH_PAD },
    { static_cast<Ark_PerfMonitorSourceType>(-1), PerfSourceType::UNKNOWN_SOURCE },
    { static_cast<Ark_PerfMonitorSourceType>(INT_MAX), PerfSourceType::UNKNOWN_SOURCE },
};
const std::vector<std::pair<int64_t, int64_t>> testFixtureNumberValues = {
    { 100, 100 },
    { 0, 0 },
    { -100, -100 },
    { 10001, 10001 },
    { -120002, -120002 },
};
} // namespace

class GlobalScope_ohos_arkui_performanceMonitorAccessorTest
    : public StaticAccessorTest<GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor,
          &GENERATED_ArkUIAccessors::getGlobalScope_ohos_arkui_performanceMonitorAccessor> {
public:
    void SetUp(void) override
    {
        mockPerfMonitor_ = new PerfMonitor();
        ASSERT_NE(mockPerfMonitor_, nullptr);
        PerfMonitor::pMonitor = mockPerfMonitor_;
    }
    void TearDown() override
    {
        StaticAccessorTest::TearDown();
        PerfMonitor::pMonitor = nullptr;
        delete mockPerfMonitor_;
        mockPerfMonitor_ = nullptr;
    }
    PerfMonitor* mockPerfMonitor_ = nullptr;
};

/**
 * @tc.name: beginSceneValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, beginSceneValidValuesTest, TestSize.Level1)
{
    Ark_String initScene;
    Opt_String initNote;
    Ark_PerfMonitorActionType initAction;
    ASSERT_NE(accessor_->begin, nullptr);
    auto holder = PerfMonitorTestHolder::GetInstance();
    // Initial setup
    initScene = std::get<0>(testFixtureStringValidValues[0]);
    initAction = std::get<0>(testFixturePerfActionTypeValues[0]);
    initNote = std::get<0>(testFixtureOptStringValues[0]);
    auto checkValue = [this, &holder, &initScene, &initAction, &initNote](
                          const Ark_String& value, const std::string& expected) {
        Ark_String inputScene = initScene;
        inputScene = value;
        holder->SetUp();
        accessor_->begin(&inputScene, initAction, &initNote);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->scene, expected);
        holder->TearDown();
    };
    for (auto& [value, expected] : testFixtureStringValidValues) {
        checkValue(value, expected);
    }
}

/**
 * @tc.name: beginActionTypeValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, beginActionTypeValuesTest, TestSize.Level1)
{
    Ark_String initScene;
    Opt_String initNote;
    Ark_PerfMonitorActionType initAction;
    ASSERT_NE(accessor_->begin, nullptr);
    auto holder = PerfMonitorTestHolder::GetInstance();
    // Initial setup
    initScene = std::get<0>(testFixtureStringValidValues[0]);
    initAction = std::get<0>(testFixturePerfActionTypeValues[0]);
    initNote = std::get<0>(testFixtureOptStringValues[0]);
    auto checkValue = [this, &holder, &initScene, &initAction, &initNote](
                          const Ark_PerfMonitorActionType& value, const PerfActionType& expected) {
        Ark_PerfMonitorActionType inputAction = initAction;
        inputAction = value;
        holder->SetUp();
        accessor_->begin(&initScene, inputAction, &initNote);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->actionType, expected);
        holder->TearDown();
    };
    for (auto& [value, expected] : testFixturePerfActionTypeValues) {
        checkValue(value, expected);
    }
}

/**
 * @tc.name: beginNoteValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, beginNoteValuesTest, TestSize.Level1)
{
    Ark_String initScene;
    Opt_String initNote;
    Ark_PerfMonitorActionType initAction;
    ASSERT_NE(accessor_->begin, nullptr);
    auto holder = PerfMonitorTestHolder::GetInstance();
    // Initial setup
    initScene = std::get<0>(testFixtureStringValidValues[0]);
    initAction = std::get<0>(testFixturePerfActionTypeValues[0]);
    initNote = std::get<0>(testFixtureOptStringValues[0]);
    auto checkValue = [this, &holder, &initScene, &initAction, &initNote](
                          const Opt_String& value, const std::string& expected) {
        Opt_String inputNote = initNote;
        inputNote = value;
        holder->SetUp();
        accessor_->begin(&initScene, initAction, &inputNote);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->note, expected);
        holder->TearDown();
    };
    for (auto& [value, expected] : testFixtureOptStringValues) {
        checkValue(value, expected);
    }
}

/**
 * @tc.name: endTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, endTest, TestSize.Level1)
{
    Ark_String initScene;
    ASSERT_NE(accessor_->end, nullptr);
    auto holder = PerfMonitorTestHolder::GetInstance();
    // Initial setup
    initScene = std::get<0>(testFixtureStringValidValues[0]);
    auto checkValue = [this, &holder, &initScene](const Ark_String& value, const std::string& expected) {
        Ark_String inputScene = initScene;
        inputScene = value;
        holder->SetUp();
        accessor_->end(&inputScene);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->scene, expected);
        holder->TearDown();
    };
    for (auto& [value, expected] : testFixtureStringValidValues) {
        checkValue(value, expected);
    }
}

/**
 * @tc.name: recordInputEventTimeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, recordInputEventTimeActionValuesTest, TestSize.Level1)
{
    Ark_PerfMonitorActionType initAction;
    Ark_PerfMonitorSourceType initSource;
    Ark_Int64 initTime;
    ASSERT_NE(accessor_->recordInputEventTime, nullptr);
    auto holder = PerfMonitorTestHolder::GetInstance();
    // Initial setup
    initAction = std::get<0>(testFixturePerfActionTypeValues[0]);
    initSource = std::get<0>(testFixturePerfSourceTypeValues[0]);
    initTime = std::get<0>(testFixtureNumberValues[0]);
    auto checkValue = [this, &holder, &initAction, &initSource, &initTime](
                          const Ark_PerfMonitorActionType& value, const PerfActionType& expected) {
        Ark_PerfMonitorActionType inputAction = initAction;
        inputAction = value;
        holder->SetUp();
        accessor_->recordInputEventTime(inputAction, initSource, initTime);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->actionType, expected);
        holder->TearDown();
    };
    for (auto& [value, expected] : testFixturePerfActionTypeValues) {
        checkValue(value, expected);
    }
}

/**
 * @tc.name: recordInputEventTimeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, recordInputEventTimeSourceValuesTest, TestSize.Level1)
{
    Ark_PerfMonitorActionType initAction;
    Ark_PerfMonitorSourceType initSource;
    Ark_Int64 initTime;
    ASSERT_NE(accessor_->recordInputEventTime, nullptr);
    auto holder = PerfMonitorTestHolder::GetInstance();
    // Initial setup
    initAction = std::get<0>(testFixturePerfActionTypeValues[0]);
    initSource = std::get<0>(testFixturePerfSourceTypeValues[0]);
    initTime = std::get<0>(testFixtureNumberValues[0]);
    auto checkValue = [this, &holder, &initAction, &initSource, &initTime](
                          const Ark_PerfMonitorSourceType& value, const PerfSourceType& expected) {
        Ark_PerfMonitorSourceType inputSource = initSource;
        inputSource = value;
        holder->SetUp();
        accessor_->recordInputEventTime(initAction, inputSource, initTime);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->sourceType, expected);
        holder->TearDown();
    };
    for (auto& [value, expected] : testFixturePerfSourceTypeValues) {
        checkValue(value, expected);
    }
}

/**
 * @tc.name: recordInputEventTimeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, recordInputEventTimeValuesTest, TestSize.Level1)
{
    Ark_PerfMonitorActionType initAction;
    Ark_PerfMonitorSourceType initSource;
    Ark_Int64 initTime;
    ASSERT_NE(accessor_->recordInputEventTime, nullptr);
    auto holder = PerfMonitorTestHolder::GetInstance();
    // Initial setup
    initAction = std::get<0>(testFixturePerfActionTypeValues[0]);
    initSource = std::get<0>(testFixturePerfSourceTypeValues[0]);
    initTime = std::get<0>(testFixtureNumberValues[0]);
    auto checkValue = [this, &holder, &initAction, &initSource, &initTime](
                          const Ark_Int64& value, const int64_t& expected) {
        Ark_Int64 inputTime = initTime;
        inputTime = value;
        holder->SetUp();
        accessor_->recordInputEventTime(initAction, initSource, inputTime);
        EXPECT_TRUE(holder->isCalled);
        ASSERT_NE(holder->time, std::nullopt);
        EXPECT_EQ(holder->time.value(), expected);
        holder->TearDown();
    };
    for (auto& [value, expected] : testFixtureNumberValues) {
        checkValue(value, expected);
    }
}
} // namespace OHOS::Ace::NG
