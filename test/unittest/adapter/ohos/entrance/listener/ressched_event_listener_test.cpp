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
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
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
        ResschedEventListener::GetInstance()->UnRegisterToRSS(windowId);
    }
};

/**
 * @tc.name: OnComponentPreMake001
 * @tc.desc: Test OnComponentPreMake when conext is nullptr return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake001, TestSize.Level1)
{
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;
    
    std::unordered_map<std::string, std::string>& extInfo;
    extInfo["windowId"] = 10;
    extInfo["pageName"] = "pageName";
    uint32_t swiperType = 21;

    ResschedEventListener::GetInstance()->OnReceiveEvent(swiperType, extInfo);
    EXPECT_NE(listener_->containerMap_.empty(), false);

    MockPipelineContext::pipeline_ = pipeline_bak;
}

/**
 * @tc.name: OnComponentPreMake001
 * @tc.desc: Test OnComponentPreMake when pageName page not match
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake002, TestSize.Level1)
{
    std::unordered_map<std::string, std::string>& extInfo;
    extInfo["windowId"] = 10;
    extInfo["pageName"] = "pageName";
    uint32_t swiperType = 21;

    ResschedEventListener::GetInstance()->OnReceiveEvent(swiperType, extInfo);
    EXPECT_NE(listener_->containerMap_.empty(), false);
}

/**
 * @tc.name: OnComponentPreMake001
 * @tc.desc: Test OnComponentPreMake when pageName page match
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake003, TestSize.Level1)
{
    std::unordered_map<std::string, std::string>& extInfo;
    extInfo["windowId"] = 10;
    extInfo["pageName"] = "";
    uint32_t swiperType = 21;

    ResschedEventListener::GetInstance()->OnReceiveEvent(swiperType, extInfo);
    EXPECT_NE(listener_->containerMap_.empty(), false);
}
}