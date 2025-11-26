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

#include <gmock/gmock.h>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/pattern/web/web_data_detector_adapter.h"
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/ani/web_model_static.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
    void DialogTheme::Builder::ParseNewPattern(const RefPtr<ThemeConstants>& themeConstants,
        const RefPtr<DialogTheme>& theme) const{};
    void DialogTheme::Builder::ParsePattern(const RefPtr<ThemeConstants>& themeConstants,
        const RefPtr<DialogTheme>& theme) const{};
}

namespace OHOS::Ace::NG {
namespace {
RefPtr<WebPattern> g_webPattern = nullptr;
const std::string ALL_TEXT_DETECT_TYPES = "phoneNum,url,email,location,datetime";
}
class WebPatternTestNgPartOne : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternTestNgPartOne::SetUpTestCase() {}
void WebPatternTestNgPartOne::TearDownTestCase() {}
void WebPatternTestNgPartOne::SetUp() {}
void WebPatternTestNgPartOne::TearDown() {}

/**
 * @tc.name: InitSelectDataDetector_001
 * @tc.desc: InitSelectDataDetector.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, InitSelectDataDetector_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    bool ret = webPattern->GetDataDetectorEnable();
    ASSERT_EQ(ret, false);
    webPattern->GetDataDetectorAdapter();
    webPattern->InitSelectDataDetector();
    TextDetectConfig config;
    webPattern->UpdateEnableSelectedDataDetector(true);
    webPattern->UpdateSelectedDataDetectorConfig(config);
    ret = webPattern->GetDataDetectorEnable();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: SetSelectedDataDetectorConfig_001
 * @tc.desc: Test SetSelectedDataDetectorConfig with all branches.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, SetSelectedDataDetectorConfig_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    adapter->aiSupportStatus_ = AISupportStatus::SUPPORTED;

    adapter->SetSelectDataDetectorEnable(true);
    EXPECT_EQ(adapter->selectConfig_.enable, true);
    TextDetectConfig emptyConfig;
    emptyConfig.types = "";
    adapter->selectConfig_.useDDtypes = true;
    adapter->SetSelectedDataDetectorConfig(emptyConfig, false);
    EXPECT_FALSE(adapter->selectConfig_.useDDtypes);
    EXPECT_EQ(adapter->selectConfig_.types, ALL_TEXT_DETECT_TYPES);

    adapter->selectConfig_.useDDtypes = true;
    adapter->SetSelectedDataDetectorConfig(emptyConfig, true);
    EXPECT_TRUE(adapter->selectConfig_.useDDtypes);
    EXPECT_EQ(adapter->selectConfig_.types, ALL_TEXT_DETECT_TYPES);

    TextDetectConfig customConfig;
    customConfig.types = "email,location";
    adapter->selectConfig_.useDDtypes = true;
    adapter->SetSelectedDataDetectorConfig(customConfig, false);
    EXPECT_FALSE(adapter->selectConfig_.useDDtypes);
    EXPECT_EQ(adapter->selectConfig_.types, "email,location");

    customConfig.types = "phoneNum,url";
    adapter->selectConfig_.useDDtypes = true;
    adapter->SetSelectedDataDetectorConfig(customConfig, true);
    EXPECT_TRUE(adapter->selectConfig_.useDDtypes);
    EXPECT_EQ(adapter->selectConfig_.types, "phoneNum,url");
#endif
}

/**
 * @tc.name: GetSelectDataDetectorTypes_001
 * @tc.desc: Test GetSelectDataDetectorTypes with all branches.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, GetSelectDataDetectorTypes_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    adapter->aiSupportStatus_ = AISupportStatus::SUPPORTED;

    adapter->selectConfig_.enable = false;
    EXPECT_EQ(adapter->GetSelectDataDetectorTypes(), "");

    adapter->selectConfig_.enable = true;
    adapter->config_.enable = false;
    adapter->selectConfig_.types = "phoneNum,url";
    EXPECT_EQ(adapter->GetSelectDataDetectorTypes(), "phoneNum,url");

    adapter->selectConfig_.enable = true;
    adapter->config_.enable = true;
    adapter->selectConfig_.useDDtypes = false;
    adapter->selectConfig_.types = "phoneNum,url";
    EXPECT_EQ(adapter->GetSelectDataDetectorTypes(), "phoneNum,url");
    adapter->selectConfig_.useDDtypes = true;
#endif
}

/**
 * @tc.name: GetSelectDataDetectorTypes_002
 * @tc.desc: Test GetSelectDataDetectorTypes with different types input.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, GetSelectDataDetectorTypes_002, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto adapter = AceType::MakeRefPtr<WebDataDetectorAdapter>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)), 0);
    adapter->aiSupportStatus_ = AISupportStatus::SUPPORTED;

    adapter->config_.enable = true;
    adapter->selectConfig_.enable = true;
    adapter->selectConfig_.useDDtypes = true;
    adapter->config_.types = "email,location";
    EXPECT_EQ(adapter->GetSelectDataDetectorTypes(), "email,location");
    adapter->config_.types = "";
    EXPECT_EQ(adapter->GetSelectDataDetectorTypes(), ALL_TEXT_DETECT_TYPES);
#endif
}

/**
 * @tc.name: FilterAndMapTypes_001
 * @tc.desc: Test FilterAndMapTypes with multiple input scenarios in one test.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, FilterAndMapTypes_001, TestSize.Level0)
{
    std::string input1 = "";
    std::string expected1 = "";
    std::string result1 = WebDataDetectorAdapter::FilterAndMapTypes(input1);
    EXPECT_EQ(result1, expected1);

    std::string input2 = "phoneNum";
    std::string expected2 = "phoneNum";
    std::string result2 = WebDataDetectorAdapter::FilterAndMapTypes(input2);
    EXPECT_EQ(result2, expected2);

    std::string input3 = "invalidType";
    std::string expected3 = "";
    std::string result3 = WebDataDetectorAdapter::FilterAndMapTypes(input3);
    EXPECT_EQ(result3, expected3);

    std::string input4 = "phoneNum,phoneNum";
    std::string expected4 = "phoneNum";
    std::string result4 = WebDataDetectorAdapter::FilterAndMapTypes(input4);
    EXPECT_EQ(result4, expected4);

    std::string input5 = "phoneNum,url,email";
    std::string expected5 = "phoneNum,url,email";
    std::string result5 = WebDataDetectorAdapter::FilterAndMapTypes(input5);
    EXPECT_EQ(result5, expected5);
}

/**
 * @tc.name: SetEnableSelectedDataDetector001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, SetEnableSelectedDataDetector001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WebModelNG webModelNG;
    webModelNG.SetEnableSelectedDataDetector(true);
    EXPECT_TRUE(webPattern->GetOrCreateWebProperty()->CheckEnableSelectedDataDetector(true));
    webModelNG.SetEnableSelectedDataDetector(AccessibilityManager::RawPtr(frameNode), false);
    EXPECT_TRUE(webPattern->GetOrCreateWebProperty()->CheckEnableSelectedDataDetector(false));
#endif
}

/**
 * @tc.name: SetZoomControlAccess001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, SetZoomControlAccess001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetZoomControlAccess(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckZoomControlAccess(true), true);
    webModelNG.SetZoomControlAccess(false);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckZoomControlAccess(false), true);
#endif
}

/**
 * @tc.name: OnZoomControlAccessUpdate_001
 * @tc.desc: OnZoomControlAccessUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, OnZoomControlAccessUpdate_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->OnZoomControlAccessUpdate(true);
#endif
}

/**
 * @tc.name: OnZoomControlAccessUpdate_002
 * @tc.desc: OnZoomControlAccessUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, OnZoomControlAccessUpdate_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    webPattern->OnZoomControlAccessUpdate(true);
#endif
}


/**
 * @tc.name: OnStatusBarClick
 * @tc.desc: OnStatusBarClick.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNgPartOne, OnStatusBarClick, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->isBackToTopRunning_ = true;
    webPattern->OnStatusBarClick();
    EXPECT_TRUE(!webPattern->isBackToTopRunning_);
#endif
}
}