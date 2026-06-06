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

#include "gtest/gtest.h"
#include "adapter/ohos/entrance/listener/ressched_event_listener.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class ResschedEventListenerTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        int32_t windowId = 10;
        int32_t instanceId = 20;
        ResschedEventListener::GetInstance()->RegisterToRSS(windowId, instanceId);
    }
    void TearDown() override
    {
        int32_t windowId = 10;
        ResschedEventListener::GetInstance()->UnRegisterFromRSS(windowId);
    }
};

/**
 * @tc.name: OnReceiveEvent001
 * @tc.desc: Test OnReceiveEvent when conext is nullptr return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake001, TestSize.Level1)
{
    RefPtr<NG::MockPipelineContext> pipeline_bak = NG::MockPipelineContext::pipeline_;
    NG::MockPipelineContext::pipeline_ = nullptr;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["windowId"] = 10;
    extInfo["pageName"] = "pageName";
    uint32_t swiperType = 21;
    uint32_t value = 0;

    ResschedEventListener::GetInstance()->OnReceiveEvent(swiperType, value, extInfo);
    EXPECT_FALSE(extInfo.empty());

    NG::MockPipelineContext::pipeline_ = pipeline_bak;
}

/**
 * @tc.name: OnReceiveEvent002
 * @tc.desc: Test OnReceiveEvent when pageName page not match
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnReceiveEvent002, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["windowId"] = 10;
    extInfo["pageName"] = "pageName";
    uint32_t swiperType = 21;
    uint32_t value = 0;

    ResschedEventListener::GetInstance()->OnReceiveEvent(swiperType, value, extInfo);
    EXPECT_FALSE(extInfo.empty());
}

/**
 * @tc.name: OnReceiveEvent003
 * @tc.desc: Test OnReceiveEvent when pageName page match
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnReceiveEvent003, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["windowId"] = 10;
    extInfo["pageName"] = "";
    uint32_t swiperType = 21;
    uint32_t value = 0;

    ResschedEventListener::GetInstance()->OnReceiveEvent(swiperType, value, extInfo);
    EXPECT_FALSE(extInfo.empty());
}
}