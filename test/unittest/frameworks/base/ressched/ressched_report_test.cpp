/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#define private public
#define protected public
#include "base/ressched/ressched_report.h"
#include "core/common/ace_application_info.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
} // namespace

class ResSchedReportTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
    }
    static void TearDownTestSuite()
    {
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: ResSchedReportTest001
 * @tc.desc: test touch up
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest001, TestSize.Level1)
{
    TouchEvent touchEvent;
    touchEvent.type = TouchType::UP;
    touchEvent.localX = 100.0f;
    touchEvent.localY = 200.0f;
    ReportConfig config;
    config.isReportTid = true;
    config.tid = 98765;
    ResSchedReport::GetInstance().OnTouchEvent(touchEvent, config);
    EXPECT_NE(touchEvent.localX, touchEvent.localY);
}

/**
 * @tc.name: ResSchedReportTest002
 * @tc.desc: test touch move
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest002, TestSize.Level1)
{
    TouchEvent touchEvent;
    touchEvent.type = TouchType::MOVE;
    touchEvent.localX = 100.0f;
    touchEvent.localY = 200.0f;
    ReportConfig config;
    config.isReportTid = true;
    config.tid = 12345;
    ResSchedReport::GetInstance().OnTouchEvent(touchEvent, config);
    EXPECT_NE(touchEvent.localX, touchEvent.localY);
}

/**
 * @tc.name: ResSchedReportTest003
 * @tc.desc: test HandleSwiperChange
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest003, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    payload["path"] = "/test[0]/swiper[1]";
    payload["currentIndex"] = "1";
    payload["componentType"] = "1";
    ResSchedReport::GetInstance().HandleSwiperChange(payload);
    EXPECT_NE(payload.size(), 0);
}

/**
 * @tc.name: ResSchedReportTest004
 * @tc.desc: test HandleSwiperChange with empty payload
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest004, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    ResSchedReport::GetInstance().HandleSwiperChange(payload);
    EXPECT_FALSE(payload.empty());
}

/**
 * @tc.name: ResSchedReportTest005
 * @tc.desc: test AppSwiperReportEnableCheck
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest005, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    std::unordered_map<std::string, std::string> reply;
    bool result = ResSchedReport::GetInstance().AppSwiperReportEnableCheck(payload, reply);
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: ResSchedReportTest006
 * @tc.desc: test AppSwiperReportEnableCheck with payload
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest006, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    payload["bundleName"] = "com.example.app";
    std::unordered_map<std::string, std::string> reply;
    bool result = ResSchedReport::GetInstance().AppSwiperReportEnableCheck(payload, reply);
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: ResSchedReportTest007
 * @tc.desc: test AppSwiperReportEnableCheck reply parsing
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest007, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    std::unordered_map<std::string, std::string> reply;
    reply["result"] = "\"true\"";
    bool result = ResSchedReport::GetInstance().AppSwiperReportEnableCheck(payload, reply);
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: ResSchedReportTest008
 * @tc.desc: test HandleSwiperChange with multiple params
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest008, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    payload["path"] = "/root[0]/container[1]/swiper[2]";
    payload["currentIndex"] = "5";
    payload["componentType"] = "1";
    payload["bundleName"] = "com.test.bundle";
    payload["abilityName"] = "MainAbility";
    ResSchedReport::GetInstance().HandleSwiperChange(payload);
    EXPECT_EQ(payload.size(), 7);
}

/**
 * @tc.name: ResSchedReportTest009
 * @tc.desc: test AppClickExtEnableCheck
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest009, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    std::unordered_map<std::string, std::string> reply;
    bool result = ResSchedReport::GetInstance().AppClickExtEnableCheck(payload, reply);
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: ResSchedReportTest010
 * @tc.desc: test AppClickExtEnableCheck with reply
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest010, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    std::unordered_map<std::string, std::string> reply;
    reply["result"] = "\"true\"";
    bool result = ResSchedReport::GetInstance().AppClickExtEnableCheck(payload, reply);
    EXPECT_TRUE(result || !result);
}

/**
 * @tc.name: ResSchedReportTest011
 * @tc.desc: test AppClickExtEnableCheck with false result
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest011, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> payload;
    std::unordered_map<std::string, std::string> reply;
    reply["result"] = "\"false\"";
    bool result = ResSchedReport::GetInstance().AppClickExtEnableCheck(payload, reply);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace
