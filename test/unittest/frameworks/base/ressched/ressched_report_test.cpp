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
} // namespace OHOS::Ace
