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

#define private public
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "nweb_helper.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/web/ani/web_model_static.h"
#define protected public
#include "core/components_ng/pattern/web/ani/web_pattern_static.h"
#undef protected
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
std::string OHOS::Ace::SystemProperties::GetWebDebugRenderMode()
{
    return "async";
}

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_MINFONT_SIZE = 8;
constexpr int32_t DEFAULT_DEFAULTFONT_SIZE = 16;
constexpr int32_t DEFAULT_DEFAULTFIXEDFONT_SIZE = 13;
constexpr int32_t DEFAULT_MINLOGICALFONT_SIZE = 8;
class MockBaseEventInfo : public BaseEventInfo {
public:
    MockBaseEventInfo() : BaseEventInfo("MockEvent") {}
};

class WebModelStaticTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebModelStaticTest::SetUpTestCase() {}
void WebModelStaticTest::TearDownTestCase() {}
void WebModelStaticTest::SetUp() {}
void WebModelStaticTest::TearDown() {}

/**
 * @tc.name: WebFrameNodeCreator001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, CreateFrameNode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    SetWebIdCallback setWebIdCallback = [](int32_t) {};
    SetHapPathCallback setHapPathCallback = [](const std::string&) {};
    auto renderExitedId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    std::optional<BlurOnKeyboardHideMode> keyBoardMode;

    WebModelStatic::SetWebIdCallback(AccessibilityManager::RawPtr(frameNode), std::move(setWebIdCallback));
    WebModelStatic::SetHapPathCallback(AccessibilityManager::RawPtr(frameNode), std::move(setHapPathCallback));
    WebModelStatic::SetWebSrc(AccessibilityManager::RawPtr(frameNode), "www.example.com");
    WebModelStatic::SetRenderMode(AccessibilityManager::RawPtr(frameNode), RenderMode::ASYNC_RENDER);
    WebModelStatic::SetIncognitoMode(AccessibilityManager::RawPtr(frameNode), true);
    WebModelStatic::SetMultiWindowAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    WebModelStatic::SetWebCursiveFont(AccessibilityManager::RawPtr(frameNode), "test");
    WebModelStatic::SetWebFantasyFont(AccessibilityManager::RawPtr(frameNode), "test");
    WebModelStatic::SetWebSansSerifFont(AccessibilityManager::RawPtr(frameNode), "test");
    WebModelStatic::SetWebSerifFont(AccessibilityManager::RawPtr(frameNode), "test");
    WebModelStatic::SetWebStandardFont(AccessibilityManager::RawPtr(frameNode), "test");
    WebModelStatic::SetDefaultFixedFontSize(AccessibilityManager::RawPtr(frameNode), 0);
    WebModelStatic::SetDefaultFontSize(AccessibilityManager::RawPtr(frameNode), 0);
    WebModelStatic::SetMinFontSize(AccessibilityManager::RawPtr(frameNode), 0);
    WebModelStatic::SetMinLogicalFontSize(AccessibilityManager::RawPtr(frameNode), 0);
    WebModelStatic::SetWebFixedFont(AccessibilityManager::RawPtr(frameNode), "test");
    WebModelStatic::SetBlockNetwork(AccessibilityManager::RawPtr(frameNode), true);
    WebModelStatic::SetPageVisibleId(AccessibilityManager::RawPtr(frameNode), std::move(renderExitedId));
    WebModelStatic::SetOnDataResubmitted(AccessibilityManager::RawPtr(frameNode), std::move(renderExitedId));
    WebModelStatic::SetOnDataResubmitted(AccessibilityManager::RawPtr(frameNode), std::move(renderExitedId));
    WebModelStatic::SetFaviconReceivedId(AccessibilityManager::RawPtr(frameNode), std::move(renderExitedId));
    WebModelStatic::SetTouchIconUrlId(AccessibilityManager::RawPtr(frameNode), std::move(renderExitedId));
    WebModelStatic::SetDarkMode(AccessibilityManager::RawPtr(frameNode), WebDarkMode::On);
    WebModelStatic::SetForceDarkAccess(AccessibilityManager::RawPtr(frameNode), true);
    WebModelStatic::SetAllowWindowOpenMethod(AccessibilityManager::RawPtr(frameNode), true);
    WebModelStatic::SetUserAgent(AccessibilityManager::RawPtr(frameNode), "123");
    WebModelStatic::NotifyPopupWindowResultStatic(-1, true);
    WebModelStatic::NotifyPopupWindowResultStatic(1, true);
    WebModelStatic::SetBlurOnKeyboardHideMode(AccessibilityManager::RawPtr(frameNode), keyBoardMode);
    WebModelStatic::SetPopup(AccessibilityManager::RawPtr(frameNode), true, 0);
    keyBoardMode = BlurOnKeyboardHideMode::BLUR;
    WebModelStatic::SetBlurOnKeyboardHideMode(AccessibilityManager::RawPtr(frameNode), keyBoardMode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    auto webSrc = webPatternStatic->GetWebSrc();
    EXPECT_EQ(webSrc.has_value(), true);
    EXPECT_EQ(webSrc.value(), "www.example.com");
#endif
}

/**
 * @tc.name: SetJsEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetJsEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    WebModelStatic::SetJsEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckJsEnabled(true), true);
#endif
}

/**
 * @tc.name: SetFileAccessEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetFileAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetFileAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckFileAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetDomStorageAccessEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetDomStorageAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetDomStorageAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckDomStorageAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetMixedMode002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetMixedMode002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    std::optional<MixedModeContent> mixedContentMode;
    WebModelStatic::SetMixedMode(AccessibilityManager::RawPtr(frameNode), mixedContentMode);

    mixedContentMode = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
    WebModelStatic::SetMixedMode(AccessibilityManager::RawPtr(frameNode), mixedContentMode);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->GetMixedMode(), MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
#endif
}

/**
 * @tc.name: SetZoomAccessEnabled002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetZoomAccessEnabled002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetZoomAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckZoomAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetCacheMode001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetCacheMode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    std::optional<WebCacheMode> cacheMode;
    WebModelStatic::SetCacheMode(AccessibilityManager::RawPtr(frameNode), cacheMode);

    cacheMode = WebCacheMode::DEFAULT;
    WebModelStatic::SetCacheMode(AccessibilityManager::RawPtr(frameNode), cacheMode);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->GetCacheMode(), WebCacheMode::DEFAULT);
#endif
}

/**
 * @tc.name: SetDarkMode001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetDarkMode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    std::optional<WebDarkMode> mode;
    WebModelStatic::SetDarkMode(AccessibilityManager::RawPtr(frameNode), mode);

    mode = WebDarkMode::Auto;
    WebModelStatic::SetDarkMode(AccessibilityManager::RawPtr(frameNode), mode);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->GetDarkMode(), WebDarkMode::Auto);
#endif
}

/**
 * @tc.name: SetAllowWindowOpenMethod001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetAllowWindowOpenMethod001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetAllowWindowOpenMethod(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckAllowWindowOpenMethod(true), true);
#endif
}

/**
 * @tc.name: SetMultiWindowAccessEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetMultiWindowAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetMultiWindowAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckMultiWindowAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetKeyboardAvoidMode012
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetKeyboardAvoidMode012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    std::optional<WebKeyboardAvoidMode> mode;
    WebModelStatic::SetKeyboardAvoidMode(AccessibilityManager::RawPtr(frameNode), mode);

    mode = WebKeyboardAvoidMode::RESIZE_CONTENT;
    WebModelStatic::SetKeyboardAvoidMode(AccessibilityManager::RawPtr(frameNode), mode);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckKeyboardAvoidMode(WebKeyboardAvoidMode::RESIZE_CONTENT),
              true);
#endif
}

/**
 * @tc.name: SetOnControllerAttached010
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnControllerAttached010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount]() {
        callCount++;
        return;
    };
    WebModelStatic::SetOnControllerAttached(AccessibilityManager::RawPtr(frameNode), callback);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    webPatternStatic->onControllerAttachedCallback_();
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetVerticalScrollBarAccessEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetVerticalScrollBarAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetVerticalScrollBarAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckVerticalScrollBarAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetHorizontalScrollBarAccessEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetHorizontalScrollBarAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetHorizontalScrollBarAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckHorizontalScrollBarAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetTextZoomRatio002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetTextZoomRatio002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetTextZoomRatio(AccessibilityManager::RawPtr(frameNode), 100);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckTextZoomRatio(100), true);
#endif
}

/**
 * @tc.name: InitialScale001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, InitialScale001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::InitialScale(AccessibilityManager::RawPtr(frameNode), 100.0f);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckInitialScale(100.0f), true);
#endif
}
/**
 * @tc.name: SetOnScroll001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnScroll001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto jsCallback = [&callbackCalled](const BaseEventInfo* info) { callbackCalled = true; };
    WebModelStatic::SetScrollId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnScrollEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetOverScrollId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnOverScrollEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetScaleChangeId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnScaleChangeEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetOnRequestFocus(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnRequestFocusEvent(mockEventInfo);

    callbackCalled = false;
    WebModelStatic::SetOnContextMenuHide(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnContextMenuHideEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetGeolocationAccessEnabled002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetGeolocationAccessEnabled002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetGeolocationAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckGeolocationAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetDatabaseAccessEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetDatabaseAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetDatabaseAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckDatabaseAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetOverviewModeAccessEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOverviewModeAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetOverviewModeAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckOverviewModeAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetForceDarkAccess001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetForceDarkAccess001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetForceDarkAccess(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckForceDarkAccess(true), true);
#endif
}

/**
 * @tc.name: SetPinchSmoothModeEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetPinchSmoothModeEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetPinchSmoothModeEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckPinchSmoothModeEnabled(true), true);
#endif
}

/**
 * @tc.name: SetMetaViewport023
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetMetaViewport023, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetMetaViewport(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckMetaViewport(true), true);
#endif
}

/**
 * @tc.name: SetEnableFollowSystemFontWeight002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetEnableFollowSystemFontWeight002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetEnableFollowSystemFontWeight(AccessibilityManager::RawPtr(frameNode), false);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckEnableFollowSystemFontWeight(false), false);
#endif
}

/**
 * @tc.name: SetNativeEmbedModeEnabled008
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNativeEmbedModeEnabled008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetNativeEmbedModeEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckNativeEmbedModeEnabled(true), true);
#endif
}

/**
 * @tc.name: SetMinFontSize001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetMinFontSize001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetMinFontSize(AccessibilityManager::RawPtr(frameNode), DEFAULT_MINFONT_SIZE);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckMinFontSize(DEFAULT_MINFONT_SIZE), true);
#endif
}

/**
 * @tc.name: SetDefaultFontSize001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetDefaultFontSize001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetDefaultFontSize(AccessibilityManager::RawPtr(frameNode), DEFAULT_DEFAULTFONT_SIZE);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckDefaultFontSize(DEFAULT_DEFAULTFONT_SIZE), true);
#endif
}

/**
 * @tc.name: SetDefaultFixedFontSize001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetDefaultFixedFontSize001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetDefaultFixedFontSize(AccessibilityManager::RawPtr(frameNode), DEFAULT_DEFAULTFIXEDFONT_SIZE);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckDefaultFixedFontSize(DEFAULT_DEFAULTFIXEDFONT_SIZE),
              true);
#endif
}

/**
 * @tc.name: SetWebSansSerifFont001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWebSansSerifFont001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetWebSansSerifFont(AccessibilityManager::RawPtr(frameNode), "test");
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckWebSansSerifFont("test"), true);
#endif
}

/**
 * @tc.name: SetWebSerifFont001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWebSerifFont001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetWebSerifFont(AccessibilityManager::RawPtr(frameNode), "test");
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckWebSerifFont("test"), true);
#endif
}

/**
 * @tc.name: SetWebStandardFont001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWebStandardFont001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetWebStandardFont(AccessibilityManager::RawPtr(frameNode), "test");
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckWebStandardFont("test"), true);
#endif
}

/**
 * @tc.name: SetMinLogicalFontSize001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
 HWTEST_F(WebModelStaticTest, SetMinLogicalFontSize001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetMinLogicalFontSize(AccessibilityManager::RawPtr(frameNode), DEFAULT_MINLOGICALFONT_SIZE);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckMinLogicalFontSize(DEFAULT_MINLOGICALFONT_SIZE), true);
#endif
}

/**
 * @tc.name: SetWebCursiveFont001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWebCursiveFont001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetWebCursiveFont(AccessibilityManager::RawPtr(frameNode), "test");
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckWebCursiveFont("test"), true);
#endif
}

/**
 * @tc.name: SetWebFantasyFont001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWebFantasyFont001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetWebFantasyFont(AccessibilityManager::RawPtr(frameNode), "test");
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckWebFantasyFont("test"), true);
#endif
}


/**
 * @tc.name: SetWebFixedFont001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWebFixedFont001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetWebFixedFont(AccessibilityManager::RawPtr(frameNode), "test");
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckWebFixedFont("test"), true);
#endif
}

/**
 * @tc.name: SetLayoutMode020
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetLayoutMode020, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetLayoutMode(AccessibilityManager::RawPtr(frameNode), WebLayoutMode::FIT_CONTENT);
    EXPECT_EQ(webPatternStatic->layoutMode_, WebLayoutMode::FIT_CONTENT);
#endif
}

/**
 * @tc.name: SetNativeEmbedLifecycleChangeId018
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNativeEmbedLifecycleChangeId018, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto NativeEmbedLifecycleChangeId = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetNativeEmbedLifecycleChangeId(
        AccessibilityManager::RawPtr(frameNode), std::move(NativeEmbedLifecycleChangeId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnNativeEmbedLifecycleChangeEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: RegisterNativeEmbedRule009
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, RegisterNativeEmbedRule009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::RegisterNativeEmbedRule(AccessibilityManager::RawPtr(frameNode), "test", "111");
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckNativeEmbedRuleTag("test"), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckNativeEmbedRuleType("111"), true);
#endif
}

/**
 * @tc.name: SetNativeEmbedOptions001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNativeEmbedOptions001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetNativeEmbedOptions(AccessibilityManager::RawPtr(frameNode), false);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckIntrinsicSizeEnabled(false), false);
#endif
}

/**
 * @tc.name: SetFirstContentfulPaintId002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetFirstContentfulPaintId002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto callback = [&callbackCalled](const std::shared_ptr<BaseEventInfo> info) { callbackCalled = true; };
    WebModelStatic::SetFirstContentfulPaintId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnFirstContentfulPaintEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetOnLoadIntercept006
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnLoadIntercept006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto callback = [&callbackCalled](const std::shared_ptr<BaseEventInfo> info) { callbackCalled = true; };
    WebModelStatic::SetAudioStateChangedId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnAudioStateChangedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetOnFullScreenExit001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnFullScreenExit001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto callback = [&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        EXPECT_TRUE(info != nullptr);
    };
    WebModelStatic::SetOnFullScreenExit(AccessibilityManager::RawPtr(frameNode), callback);

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnFullScreenExitEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);


#endif
}

/**
 * @tc.name: SetImageAccessEnabled002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetImageAccessEnabled002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetImageAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckImageAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetOnLineImageAccessEnabled002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnLineImageAccessEnabled002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetOnLineImageAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckOnLineImageAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetMediaPlayGestureAccess002
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetMediaPlayGestureAccess002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetMediaPlayGestureAccess(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckMediaPlayGestureAccess(true), true);
#endif
}

/**
 * @tc.name: SetMediaOptions001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetMediaOptions001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    std::optional<int32_t> resumeInterval;
    WebModelStatic::SetAudioResumeInterval(AccessibilityManager::RawPtr(frameNode), resumeInterval);

    resumeInterval = 0;
    WebModelStatic::SetAudioResumeInterval(AccessibilityManager::RawPtr(frameNode), resumeInterval);

    std::optional<bool> audioExclusive;
    WebModelStatic::SetAudioExclusive(AccessibilityManager::RawPtr(frameNode), audioExclusive);
    audioExclusive = true;
    WebModelStatic::SetAudioExclusive(AccessibilityManager::RawPtr(frameNode), audioExclusive);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckAudioResumeInterval(0), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckAudioExclusive(true), true);
#endif
}

/**
 * @tc.name: SetRenderProcessNotRespondingId003
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetRenderProcessNotRespondingId003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    int callCount = 0;
    auto renderProcessNotRespondingId = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetRenderProcessNotRespondingId(AccessibilityManager::RawPtr(frameNode),
        renderProcessNotRespondingId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnRenderProcessNotRespondingEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnPageStartedEvent001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnPageStartedEvent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    WebModelStatic::SetWebController(AccessibilityManager::RawPtr(frameNode), controller);
    SetWebIdCallback setWebIdCallback = [](int32_t) {};
    SetHapPathCallback setHapPathCallback = [](const std::string&) {};
    WebModelStatic::SetWebSrc(AccessibilityManager::RawPtr(frameNode), "page/index");
    WebModelStatic::SetWebIdCallback(AccessibilityManager::RawPtr(frameNode), std::move(setWebIdCallback));
    WebModelStatic::SetHapPathCallback(AccessibilityManager::RawPtr(frameNode), std::move(setHapPathCallback));

    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    auto webSrc = webPatternStatic->GetWebSrc();
    EXPECT_EQ(webSrc.has_value(), true);
    EXPECT_EQ(webSrc.value(), "page/index");
    WebModelStatic::SetOnPageStart(AccessibilityManager::RawPtr(frameNode),
        [&callbackCalled](const BaseEventInfo* info) { callbackCalled = true; });
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnPageStartedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetOnPageFinish(AccessibilityManager::RawPtr(frameNode),
        [&callbackCalled](const BaseEventInfo* info) { callbackCalled = true; });
    webEventHub->FireOnPageFinishedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
    auto onProgressChangeImpl = [](const BaseEventInfo* info) {};
    WebModelStatic::SetOnProgressChange(nullptr, onProgressChangeImpl);
    WebModelStatic::SetOnProgressChange(AccessibilityManager::RawPtr(frameNode), onProgressChangeImpl);
    auto titleReceiveEventId = [](const BaseEventInfo* info) {};
    WebModelStatic::SetOnTitleReceive(AccessibilityManager::RawPtr(frameNode), titleReceiveEventId);
    auto geolocationShowEventId = [](const BaseEventInfo* info) {};
    WebModelStatic::SetOnGeolocationShow(AccessibilityManager::RawPtr(frameNode), geolocationShowEventId);
#endif
}

/**
 * @tc.name: SetOnDownloadStart001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnDownloadStart001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    WebModelStatic::SetOnDownloadStart(AccessibilityManager::RawPtr(frameNode),
        [&callbackCalled](const BaseEventInfo* info) { callbackCalled = true; });
    webEventHub->FireOnDownloadStartEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

#endif
}

/**
 * @tc.name: SetCopyOptionMode008
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetCopyOptionMode008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    std::optional<CopyOptions> mode;
    WebModelStatic::SetCopyOptionMode(AccessibilityManager::RawPtr(frameNode), mode);

    mode = CopyOptions::Local;
    WebModelStatic::SetCopyOptionMode(AccessibilityManager::RawPtr(frameNode), mode);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckCopyOptionMode(2), true);
#endif
}

/**
 * @tc.name: SetOnRenderExited001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnRenderExited001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto jsCallback = [&callbackCalled](const BaseEventInfo* info) { callbackCalled = true; };
    WebModelStatic::SetRenderExitedId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnRenderExitedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetResourceLoadId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnResourceLoadEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetRefreshAccessedHistoryId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnRefreshAccessedHistoryEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetSearchResultReceiveEventId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnSearchResultReceiveEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetRenderProcessRespondingId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    webEventHub->FireOnRenderProcessRespondingEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetOnPageVisible001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnPageVisible001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto jsCallback = [&callbackCalled](const std::shared_ptr<BaseEventInfo> info) { callbackCalled = true; };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    WebModelStatic::SetPageVisibleId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnPageVisibleEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetNavigationEntryCommittedId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnNavigationEntryCommittedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    WebModelStatic::SetTouchIconUrlId(AccessibilityManager::RawPtr(frameNode), jsCallback);
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnTouchIconUrlEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentStart024
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, JavaScriptOnDocumentStart024, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    ScriptItems scriptItems;
    WebModelStatic::JavaScriptOnDocumentStart(AccessibilityManager::RawPtr(frameNode), scriptItems);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_NE(webPatternStatic->onDocumentStartScriptItems_, std::nullopt);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEnd025
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, JavaScriptOnDocumentEnd025, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    ScriptItems scriptItemsEnd;
    WebModelStatic::JavaScriptOnDocumentEnd(AccessibilityManager::RawPtr(frameNode), scriptItemsEnd);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_NE(webPatternStatic->onDocumentEndScriptItems_, std::nullopt);
#endif
}

/**
 * @tc.name: SetBlockNetwork001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetBlockNetwork001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    WebModelStatic::SetBlockNetwork(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckBlockNetwork(true), true);
#endif
}

/**
 * @tc.name: SetOverScrollMode007
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOverScrollMode007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);

    std::optional<OverScrollMode> mode;
    WebModelStatic::SetOverScrollMode(AccessibilityManager::RawPtr(frameNode), mode);

    mode = OverScrollMode::ALWAYS;
    WebModelStatic::SetOverScrollMode(AccessibilityManager::RawPtr(frameNode), mode);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckOverScrollMode(OverScrollMode::ALWAYS), true);
#endif
}

/**
 * @tc.name: SetNativeEmbedGestureEventId019
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNativeEmbedGestureEventId019, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    int callCount = 0;
    auto NativeEmbedGestureEventId = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetNativeEmbedGestureEventId(AccessibilityManager::RawPtr(frameNode), NativeEmbedGestureEventId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnNativeEmbedGestureEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetPermissionRequestEventId028
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetPermissionRequestEventId028, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    bool callbackCalled = false;
    WebModelStatic::SetPermissionRequestEventId(AccessibilityManager::RawPtr(frameNode),
        [&callbackCalled](const BaseEventInfo* info) { callbackCalled = true; });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnPermissionRequestEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetScreenCaptureRequestEventId009
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetScreenCaptureRequestEventId009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    int callCount = 0;
    auto screenCaptureRequestEventId = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetScreenCaptureRequestEventId(AccessibilityManager::RawPtr(frameNode),
        screenCaptureRequestEventId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnScreenCaptureRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetWindowNewEvent005
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWindowNewEvent005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    WebModelStatic::SetWindowNewEvent(AccessibilityManager::RawPtr(frameNode),
        [&callbackCalled](const std::shared_ptr<BaseEventInfo> info) { callbackCalled = true; });
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnWindowNewEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetOnFullScreenEnter002
 * @tc.desc: SetOnFullScreenEnter
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnFullScreenEnter002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    bool callbackCalled = false;
    WebModelStatic::SetOnFullScreenEnter(
        AccessibilityManager::RawPtr(frameNode), [&callbackCalled](const BaseEventInfo* info) {
            callbackCalled = true;
            EXPECT_TRUE(info != nullptr);
        });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnFullScreenEnterEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetWindowExitEventId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWindowExitEventId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto callback = [&callbackCalled](const BaseEventInfo* info) { callbackCalled = true; };
    WebModelStatic::SetWindowExitEventId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnWindowExitEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetSharedRenderProcessToken001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetSharedRenderProcessToken001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    std::optional<std::string> sharedRenderProcessToken = "token";
    WebModelStatic::SetSharedRenderProcessToken(AccessibilityManager::RawPtr(frameNode), sharedRenderProcessToken);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_EQ(webPatternStatic->GetSharedRenderProcessToken(), "token");
#endif
}

/**
 * @tc.name: SetOverlayScrollbarEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOverlayScrollbarEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    WebModelStatic::SetOverlayScrollbarEnabled(AccessibilityManager::RawPtr(frameNode), true);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckOverlayScrollbarEnabled(true), true);
#endif
}

/**
 * @tc.name: SetTextAutosizing001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetTextAutosizing001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    WebModelStatic::SetTextAutosizing(AccessibilityManager::RawPtr(frameNode), true);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckTextAutosizing(true), true);
#endif
}

/**
 * @tc.name: SetWebMediaAVSessionEnabled001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetWebMediaAVSessionEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    std::optional<bool> enable;
    WebModelStatic::SetWebMediaAVSessionEnabled(AccessibilityManager::RawPtr(frameNode), enable);

    enable = true;
    WebModelStatic::SetWebMediaAVSessionEnabled(AccessibilityManager::RawPtr(frameNode), enable);
#endif
}

/**
 * @tc.name: SetDefaultTextEncodingFormat001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetDefaultTextEncodingFormat001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    std::string textEncodingFormat;
    WebModelStatic::SetDefaultTextEncodingFormat(AccessibilityManager::RawPtr(frameNode), textEncodingFormat);

    textEncodingFormat = "format";
    WebModelStatic::SetDefaultTextEncodingFormat(AccessibilityManager::RawPtr(frameNode), textEncodingFormat);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckDefaultTextEncodingFormat("format"), true);
#endif
}

/**
 * @tc.name: SetNativeVideoPlayerConfig001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNativeVideoPlayerConfig001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    WebModelStatic::SetNativeVideoPlayerConfig(AccessibilityManager::RawPtr(frameNode), true, true);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_EQ(webPatternStatic->GetOrCreateWebProperty()->CheckNativeVideoPlayerConfig(
              std::make_tuple(true, true)), true);
#endif
}

/**
 * @tc.name: SetNestedScrollExt001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNestedScrollExt001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    NestedScrollOptionsExt nestedOpt;
    WebModelStatic::SetNestedScrollExt(AccessibilityManager::RawPtr(frameNode), nestedOpt);

    nestedOpt.scrollUp = NestedScrollMode::SELF_FIRST;
    WebModelStatic::SetNestedScrollExt(AccessibilityManager::RawPtr(frameNode), nestedOpt);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_EQ(webPatternStatic->nestedScroll_.scrollUp, NestedScrollMode::SELF_FIRST);
#endif
}

/**
 * @tc.name: SetSelectionMenuOptions001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetSelectionMenuOptions001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    WebMenuOptionsParam webMenuOption = {};
    MenuOptionsParam menuOptionsParam = {};
    menuOptionsParam.id = "test";
    webMenuOption.menuOption.push_back(menuOptionsParam);
    WebModelStatic::SetSelectionMenuOptions(AccessibilityManager::RawPtr(frameNode), webMenuOption);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_FALSE(webPatternStatic->menuOptionParam_.empty());
    EXPECT_EQ(webPatternStatic->menuOptionParam_.size(), 1);
    EXPECT_EQ(webPatternStatic->menuOptionParam_[0].id, "test");
#endif
}

/**
 * @tc.name: SetEditMenuOptions001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetEditMenuOptions001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    int callCount = 0;
    auto onCreateMenuCallback =
        [](const std::vector<OHOS::Ace::NG::MenuItemParam>& /*items*/) -> std::vector<OHOS::Ace::NG::MenuOptionsParam> {
        return {};
    };
    auto onMenuItemClick = [&callCount](const OHOS::Ace::NG::MenuItemParam& /*item*/) -> bool {
        callCount++;
        return false;
    };
    WebModelStatic::SetEditMenuOptions(AccessibilityManager::RawPtr(frameNode), onCreateMenuCallback, onMenuItemClick);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    webPatternStatic->onMenuItemClick_({});
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetNewDragStyle001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNewDragStyle001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    WebModelStatic::SetNewDragStyle(AccessibilityManager::RawPtr(frameNode), true);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    EXPECT_EQ(webPatternStatic->IsNewDragStyle(), true);
#endif
}

/**
 * @tc.name: SetPreviewSelectionMenu001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetPreviewSelectionMenu001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    WebElementType type = WebElementType::IMAGE;
    ResponseType responseType = ResponseType::RIGHT_CLICK;
    MenuParam menuParam;

    menuParam.previewMode = MenuPreviewMode::NONE;
    menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    menuParam.isShow = true;
    auto param = std::make_shared<WebPreviewSelectionMenuParam>(type, responseType, nullptr,
        nullptr, menuParam);
    WebModelStatic::SetPreviewSelectionMenu(AccessibilityManager::RawPtr(frameNode), param);
    auto webPatternStatic = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPatternStatic>();
    ASSERT_NE(webPatternStatic, nullptr);
    auto result = webPatternStatic->GetPreviewSelectionMenuParams(type, responseType);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, type);
    EXPECT_EQ(result->responseType, responseType);
    EXPECT_EQ(result->menuBuilder, nullptr);
    EXPECT_EQ(result->previewBuilder, nullptr);
    EXPECT_EQ(result->menuParam.menuBindType, MenuBindingType::RIGHT_CLICK);
#endif
}

/**
 * @tc.name: SetOnGeolocationHide001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnGeolocationHide001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto callback = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetOnGeolocationHide(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnGeolocationHideEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnCommonDialog001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnCommonDialog001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnCommonDialog(AccessibilityManager::RawPtr(frameNode), callback,
        DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto result = webEventHub->FireOnCommonDialogEvent(mockEventInfo, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);
    EXPECT_TRUE(result);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnErrorReceive001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnErrorReceive001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetOnErrorReceive(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnErrorReceiveEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnHttpErrorReceive001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnHttpErrorReceive001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetOnHttpErrorReceive(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnHttpErrorReceiveEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnUrlLoadIntercept001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnUrlLoadIntercept001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnUrlLoadIntercept(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnUrlLoadInterceptEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnFileSelectorShow001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnFileSelectorShow001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnFileSelectorShow(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnFileSelectorShowEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnHttpAuthRequest001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnHttpAuthRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnHttpAuthRequest(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnHttpAuthRequestEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnInterceptRequest001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnInterceptRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return nullptr;
    };
    WebModelStatic::SetOnInterceptRequest(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnInterceptRequestEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnContextMenuHide001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnContextMenuHide001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnContextMenuHide(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnContextMenuHideEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnSslErrorRequest001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnSslErrorRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnSslErrorRequest(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnSslErrorRequestEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnAllSslErrorRequest001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnAllSslErrorRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnAllSslErrorRequest(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnAllSslErrorRequestEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnSslSelectCertRequest001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnSslSelectCertRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnSslSelectCertRequest(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnSslSelectCertRequestEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnInterceptKeyEventCallback001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnInterceptKeyEventCallback001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const KeyEventInfo& keyEventInfo) -> bool {
        return true;
    };
    WebModelStatic::SetOnInterceptKeyEventCallback(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto interceptKeyEventCallback = webEventHub->GetOnPreKeyEvent();
    ASSERT_NE(interceptKeyEventCallback, nullptr);
#endif
}

/**
 * @tc.name: SetFirstMeaningfulPaintId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetFirstMeaningfulPaintId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto callback = [&callbackCalled](const std::shared_ptr<BaseEventInfo>& info) {
        callbackCalled = true;
    };
    WebModelStatic::SetFirstMeaningfulPaintId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->propOnFirstMeaningfulPaintEvent_(nullptr);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetLargestContentfulPaintId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetLargestContentfulPaintId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto callback = [&callbackCalled](const std::shared_ptr<BaseEventInfo>& info) {
        callbackCalled = true;
    };
    WebModelStatic::SetLargestContentfulPaintId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->propOnLargestContentfulPaintEvent_(nullptr);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetOnLoadIntercept001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnLoadIntercept001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnLoadIntercept(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnLoadInterceptEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetSafeBrowsingCheckResultId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetSafeBrowsingCheckResultId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto callback = [&callbackCalled](const std::shared_ptr<BaseEventInfo> info) {
        callbackCalled = true;
    };
    WebModelStatic::SetSafeBrowsingCheckResultId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnSafeBrowsingCheckResultEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetIntelligentTrackingPreventionResultId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetIntelligentTrackingPreventionResultId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    bool callbackCalled = false;
    auto callback = [&callbackCalled](const std::shared_ptr<BaseEventInfo>& info) {
        callbackCalled = true;
    };
    WebModelStatic::SetIntelligentTrackingPreventionResultId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->propOnIntelligentTrackingPreventionResultEvent_(nullptr);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetNativeEmbedVisibilityChangeId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetNativeEmbedVisibilityChangeId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) { callCount++; };
    WebModelStatic::SetNativeEmbedVisibilityChangeId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnNativeEmbedVisibilityChangeEvent(std::make_shared<NativeEmbedVisibilityInfo>(
        true, "embed_id"));
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnOverrideUrlLoading001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnOverrideUrlLoading001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
        return true;
    };
    WebModelStatic::SetOnOverrideUrlLoading(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnOverrideUrlLoadingEvent(mockEventInfo);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetViewportFitChangedId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetViewportFitChangedId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
    };
    WebModelStatic::SetViewportFitChangedId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->propOnViewportFitChangedEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnInterceptKeyboardAttach001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetOnInterceptKeyboardAttach001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> WebKeyboardOption {
        callCount++;
        return { };
    };
    WebModelStatic::SetOnInterceptKeyboardAttach(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    ASSERT_NE(frameNode->GetEventHub(), nullptr);
    webEventHub->propOnInterceptKeyboardAttachEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}
/**
 * @tc.name: SetAdsBlockedEventId001
 * @tc.desc: Test web_model_static.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelStaticTest, SetAdsBlockedEventId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = WebModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) {
        callCount++;
    };
    WebModelStatic::SetAdsBlockedEventId(AccessibilityManager::RawPtr(frameNode), callback);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->propOnAdsBlockedEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}
} // namespace OHOS::Ace::NG
