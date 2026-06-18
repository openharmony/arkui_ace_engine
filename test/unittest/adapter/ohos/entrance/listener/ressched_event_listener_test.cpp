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
#define private public
#define protected public
#include "adapter/ohos/entrance/listener/ressched_event_listener.h"
#include "base/utils/string_utils.h"
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
 * @tc.name: OnComponentPreMake001
 * @tc.desc: Test OnComponentPreMake with componentType is not exist return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake001, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    EXPECT_EQ(extInfo.find("componentType"), extInfo.end());
}

/**
 * @tc.name: OnComponentPreMake002
 * @tc.desc: Test OnComponentPreMake with componentType is not number return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake002, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "errorType";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto componentTypeStr = extInfo.find("componentType")->second;
    EXPECT_FALSE(StringUtils::IsNumber(componentTypeStr));
}

/**
 * @tc.name: OnComponentPreMake003
 * @tc.desc: Test OnComponentPreMake with index is not exist return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake003, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto componentTypeStr = extInfo.find("componentType")->second;
    EXPECT_TRUE(StringUtils::IsNumber(componentTypeStr));
    EXPECT_EQ(extInfo.find("index"), extInfo.end());
}

/**
 * @tc.name: OnComponentPreMake004
 * @tc.desc: Test OnComponentPreMake with index is not number return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake004, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "errorIndex";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto indexStr = extInfo.find("index")->second;
    EXPECT_FALSE(StringUtils::IsNumber(indexStr));
}

/**
 * @tc.name: OnComponentPreMake005
 * @tc.desc: Test OnComponentPreMake with path is not exist return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake005, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto indexStr = extInfo.find("index")->second;
    EXPECT_TRUE(StringUtils::IsNumber(indexStr));
    EXPECT_EQ(extInfo.find("path"), extInfo.end());
}

/**
 * @tc.name: OnComponentPreMake006
 * @tc.desc: Test OnComponentPreMake with path is empty return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake006, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto pathStr = extInfo.find("path")->second;
    EXPECT_TRUE(pathStr.empty());
}

/**
 * @tc.name: OnComponentPreMake007
 * @tc.desc: Test OnComponentPreMake with path length exceeds the limit return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake007, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    std::ostringstream result;
    for (int i = 0; i <= 12; i++) {
        result << "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    }
    extInfo["path"] = result.str();
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto pathStr = extInfo.find("path")->second;
    EXPECT_TRUE(pathStr.size() > 1024);
}

/**
 * @tc.name: OnComponentPreMake008
 * @tc.desc: Test OnComponentPreMake with pageName is not exist return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake008, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    EXPECT_EQ(extInfo.find("pageName"), extInfo.end());
}

/**
 * @tc.name: OnComponentPreMake009
 * @tc.desc: Test OnComponentPreMake with windowId is not exist return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake009, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    extInfo["pageName"] = "test://helloPage";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto pageNameStr = extInfo.find("pageName")->second;
    EXPECT_FALSE(pageNameStr.empty());
    EXPECT_EQ(extInfo.find("windowId"), extInfo.end());
}

/**
 * @tc.name: OnComponentPreMake010
 * @tc.desc: Test OnComponentPreMake with windowId is not number return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake010, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    extInfo["pageName"] = "test://helloPage";
    extInfo["windowId"] = "errorWindowId";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto windowIdStr = extInfo.find("windowId")->second;
    EXPECT_FALSE(StringUtils::IsNumber(windowIdStr));
}

/**
 * @tc.name: OnComponentPreMake011
 * @tc.desc: Test OnComponentPreMake with windowId is default value return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake011, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    extInfo["pageName"] = "test://helloPage";
    extInfo["windowId"] = "0";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto windowIdStr = extInfo.find("windowId")->second;
    EXPECT_EQ(StringUtils::StringToInt(windowIdStr), 0);
}

/**
 * @tc.name: OnComponentPreMake012
 * @tc.desc: Test OnComponentPreMake with containerId is default value return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake012, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    extInfo["pageName"] = "test://helloPage";
    extInfo["windowId"] = "1";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    auto windowIdStr = extInfo.find("windowId")->second;
    EXPECT_EQ(StringUtils::StringToInt(windowIdStr), 1);
}

/**
 * @tc.name: OnComponentPreMake013
 * @tc.desc: Test OnComponentPreMake with context is nullptr return early
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake013, TestSize.Level1)
{
    RefPtr<NG::MockPipelineContext> pipeline_bak = NG::MockPipelineContext::pipeline_;
    NG::MockPipelineContext::pipeline_ = nullptr;

    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    extInfo["pageName"] = "test://helloPage";
    extInfo["windowId"] = "10";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    EXPECT_FALSE(extInfo.empty());

    NG::MockPipelineContext::pipeline_ = pipeline_bak;
}

/**
 * @tc.name: OnComponentPreMake014
 * @tc.desc: Test OnComponentPreMake with pageInfo is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ResschedEventListenerTest, OnComponentPreMake014, TestSize.Level1)
{
    std::unordered_map<std::string, std::string> extInfo;
    extInfo["componentType"] = "1";
    extInfo["index"] = "1";
    extInfo["path"] = "/root/stage[0]/page[0]/JsView[0]/Navigation[0]/NavigationContent[1]/NavDestination[0]";
    extInfo["pageName"] = "test://helloPage";
    extInfo["windowId"] = "10";
    ResschedEventListener::GetInstance()->OnComponentPreMake(extInfo);
    EXPECT_FALSE(extInfo.empty());
}
}
