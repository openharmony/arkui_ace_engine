/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> g_frameNode = nullptr;
RefPtr<WebPattern> g_webPattern = nullptr;
} // namespace

class WebPatternEventTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternEventTest::SetUpTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string src = "web_pattern_event_test";
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();

    EXPECT_NE(webController, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    g_frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(g_frameNode);

    g_webPattern = g_frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(g_webPattern);
    g_webPattern->SetWebSrc(src);
    g_webPattern->SetWebController(webController);
#endif
}

void WebPatternEventTest::TearDownTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    g_frameNode = nullptr;
    g_webPattern = nullptr;
#endif
}

void WebPatternEventTest::SetUp() {}
void WebPatternEventTest::TearDown() {}

/**
 * @tc.name: WebPatternTestNg_001
 * @tc.desc: Test MouseEvent function normal condition.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebPatternTestNg_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->AttachToFrameNode(g_frameNode);
    g_webPattern->OnAttachToFrameNode();
    g_webPattern->OnModifyDone();
    g_webPattern->InitEvent();
    EXPECT_TRUE(g_webPattern->touchEvent_ != nullptr && g_webPattern->mouseEvent_ != nullptr);
    g_webPattern->InitEvent();

    MouseInfo info;
    info.SetAction(MouseAction::RELEASE);
    g_webPattern->HandleMouseEvent(info);
    info.SetButton(MouseButton::RIGHT_BUTTON);
    g_webPattern->HandleDoubleClickEvent(info);
    info.SetButton(MouseButton::LEFT_BUTTON);
    g_webPattern->HandleDoubleClickEvent(info);
    info.SetAction(MouseAction::PRESS);

    Offset localLocation;
    int64_t timeStamp = 0;
    std::chrono::milliseconds millisec(timeStamp);
    TimeStamp time(millisec);
    info.SetLocalLocation(localLocation);
    info.SetTimeStamp(time);
    EXPECT_TRUE(g_webPattern->mouseClickQueue_.empty());
    g_webPattern->HandleDoubleClickEvent(info);
    EXPECT_FALSE(g_webPattern->mouseClickQueue_.empty());
    EXPECT_EQ(g_webPattern->mouseClickQueue_.size(), 1);
    g_webPattern->HandleDoubleClickEvent(info);
    EXPECT_NE(g_webPattern->mouseClickQueue_.size(), 1);
    g_webPattern->HandleDoubleClickEvent(info);
#endif
}

/**
 * @tc.name: WebPatternTestNg_002
 * @tc.desc: Test MouseEvent function abnormal condition.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebPatternTestNg_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MouseInfo info;
    g_webPattern->WebOnMouseEvent(info);
    g_webPattern->HandleDoubleClickEvent(info);
    g_webPattern->HandleFocusEvent();
    BlurReason blurReason = BlurReason::FOCUS_SWITCH;
    g_webPattern->HandleBlurEvent(blurReason);
    KeyEvent keyEvent;
    g_webPattern->WebOnKeyEvent(keyEvent);
    EXPECT_FALSE(g_webPattern->isTouchUpEvent_);
#endif
}

/**
 * @tc.name: WebPatternTestNg_003
 * @tc.desc: Test Focus function normal condition.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebPatternTestNg_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->OnModifyDone();
    auto host = g_webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto eventHub = host->GetOrCreateEventHub<WebEventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    EXPECT_NE(focusHub, nullptr);
    g_webPattern->InitFocusEvent(focusHub);

    g_webPattern->needOnFocus_ = false;
    EXPECT_FALSE(g_webPattern->needOnFocus_);
    g_webPattern->HandleFocusEvent();
    EXPECT_TRUE(g_webPattern->needOnFocus_);
    g_webPattern->HandleFocusEvent();
    BlurReason blurReason = BlurReason::FOCUS_SWITCH;
    g_webPattern->selectPopupMenuShowing_ = true;
    g_webPattern->HandleBlurEvent(blurReason);

    KeyEvent keyEvent;
    g_webPattern->HandleKeyEvent(keyEvent);
#endif
}

/**
 * @tc.name: WebPatternTestNg_004
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebPatternTestNg_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper;
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(g_frameNode, geometryNode, g_frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    bool result;
    DirtySwapConfig config;
    result = g_webPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    config.contentSizeChange = true;
    SizeF size(Size::INFINITE_SIZE, Size::INFINITE_SIZE);
    geometryNode->SetContentSize(size);
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(g_frameNode, geometryNode, g_frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    result = g_webPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    size.Reset();
    geometryNode->SetContentSize(size);
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(g_frameNode, geometryNode, g_frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    result = g_webPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    const float widthAndHight = 60.0;
    size.SetWidth(widthAndHight);
    size.SetHeight(widthAndHight);
    geometryNode->SetContentSize(size);
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(g_frameNode, geometryNode, g_frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    g_webPattern->isUrlLoaded_ = false;
    result = g_webPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    g_webPattern->isUrlLoaded_ = true;
    g_webPattern->webSrc_ = std::nullopt;
    result = g_webPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
#endif
}
} // namespace OHOS::Ace::NG
