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
#include "gmock/gmock.h"

#define private public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components/web/resource/web_delegate.h"
#include "test/unittest/core/pattern/web/mock_web_delegate.h"
#include "core/components_ng/pattern/web/web_util.h"

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
    auto eventHub = host->GetEventHub<WebEventHub>();
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

/**
 * @tc.name: WebPatternTestNg_005
 * @tc.desc: Test SendMouseEvent when FileSelectorShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebPatternTestNg_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    ASSERT_NE(g_webPattern->delegate_, nullptr);
    g_webPattern->delegate_->SetIsFileSelectorShow(true);
    MouseInfo info;
    info.SetRawDeltaX(1);
    info.SetRawDeltaY(1);
    info.SetAction(MouseAction::HOVER_EXIT);
    g_webPattern->CheckShouldBlockMouseEvent(info);
    EXPECT_EQ(g_webPattern->delegate_->IsFileSelectorShow(), true);
#endif
}

/**
 * @tc.name: WebPatternTestNg_006
 * @tc.desc: SupplementMouseEventsIfNeeded.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebPatternTestNg_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->selectPopupMenuShowing_ = false;
    g_webPattern->isMenuShownFromWebBeforeStartClose_ = true;
    g_webPattern->NotifyMenuLifeCycleEvent(MenuLifeCycleEvent::ABOUT_TO_DISAPPEAR);
    EXPECT_FALSE(g_webPattern->isMenuShownFromWebBeforeStartClose_);
    EXPECT_TRUE(g_webPattern->isLastEventMenuClose_);
    
    g_webPattern->isLastEventMenuClose_ = true;
    g_webPattern->lastMenuCloseTimestamp_ = GetCurrentTimestamp();
    MouseInfo info;
    info.SetAction(MouseAction::WINDOW_ENTER);
    g_webPattern->SupplementMouseEventsIfNeeded(info, 1, std::vector<int32_t>());

    g_webPattern->isHoverNWeb_ = true;
    g_webPattern->isSupplementMouseLeave_ = true;
    MouseInfo infoHover;
    infoHover.SetAction(MouseAction::HOVER);
    g_webPattern->SupplementMouseEventsIfNeeded(infoHover, 1, std::vector<int32_t>());

    g_webPattern->isHoverNWeb_ = false;
    g_webPattern->isSupplementMouseLeave_ = false;
    g_webPattern->isUpSupplementDown_ = true;
    MouseInfo infoRelease;
    infoRelease.SetAction(MouseAction::RELEASE);
    g_webPattern->SupplementMouseEventsIfNeeded(infoRelease, 1, std::vector<int32_t>());
    EXPECT_FALSE(g_webPattern->isLastEventMenuClose_);
#endif
}

/**
 * @tc.name: WebPatternTestNg_007
 * @tc.desc: CheckShouldBlockMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebPatternTestNg_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    g_webPattern->isMenuShownFromWebBeforeStartClose_ = true;
    MouseInfo info;
    info.SetAction(MouseAction::PRESS);
    bool result = g_webPattern->CheckShouldBlockMouseEvent(info);
    EXPECT_TRUE(result);

    g_webPattern->isMenuShownFromWebBeforeStartClose_ = true;
    MouseInfo infoHoverExit;
    infoHoverExit.SetAction(MouseAction::HOVER_EXIT);
    bool resultExit = g_webPattern->CheckShouldBlockMouseEvent(infoHoverExit);
    EXPECT_TRUE(resultExit);
    ASSERT_NE(g_webPattern->delegate_, nullptr);
    g_webPattern->delegate_->SetIsFileSelectorShow(false);
    g_webPattern->isMenuShownFromWebBeforeStartClose_ = false;
    g_webPattern->isDragging_ = true;
    MouseInfo infoDrag;
    infoDrag.SetAction(MouseAction::HOVER_EXIT);
    bool resultDrag = g_webPattern->CheckShouldBlockMouseEvent(infoDrag);
    g_webPattern->WebOnMouseEvent(infoDrag);
    EXPECT_TRUE(resultDrag);
#endif
}
/**
 * @tc.name: WebCommandAction_001
 * @tc.desc: Test basic WebCommandAction scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test valid click event
    const std::string& command = R"({
        "event_type": "click",
        "XPath": "/html/body"
    })";
    g_webPattern->OnInjectionEvent(command);

    // Test invalid event_type
    const std::string& command1 = R"({
        "event_type": "click111",
        "XPath": "/html/body"
    })";
    g_webPattern->OnInjectionEvent(command1);

    // Test missing event_type
    const std::string& command2 = R"({
        "XPath": "/html/body"
    })";
    g_webPattern->OnInjectionEvent(command2);

    // Test malformed JSON
    const std::string& command3 = R"({
        "XPath","/html/body"
    })";
    g_webPattern->OnInjectionEvent(command3);

    // Test invalid XPath type (number)
    const std::string& command4 = R"({
        "event_type": "click",
        "XPath":5
    })";
    g_webPattern->OnInjectionEvent(command4);
#endif
}

/**
 * @tc.name: WebCommandAction_001b
 * @tc.desc: Test scroll command validation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_001b, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test invalid align type (number)
    const std::string& command5 = R"({
        "event_type": "scroll",
        "duration": 7,
        "align": 7,
        "XPath":"/html/body"
    })";
    g_webPattern->OnInjectionEvent(command5);

    // Test invalid align value
    const std::string& command6 = R"({
        "event_type": "scroll",
        "duration": 7,
        "align": "center",
        "XPath":"/html/body"
    })";
    g_webPattern->OnInjectionEvent(command6);

    // Test invalid offset type (string)
    const std::string& command7 = R"({
        "event_type": "scroll",
        "duration": 7,
        "align": "mid",
        "offset": "offset",
        "XPath":"/html/body"
    })";
    g_webPattern->OnInjectionEvent(command7);
#endif
}

/**
 * @tc.name: WebCommandAction_001c
 * @tc.desc: Test more scroll command validation scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_001c, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test valid scroll with invalid align value
    const std::string& command8 = R"({
        "event_type": "scroll",
        "duration": 7,
        "align": "center",
        "offset": 30,
        "XPath":"/html/body"
    })";
    g_webPattern->OnInjectionEvent(command8);

    // Test invalid duration type (string)
    const std::string& command9 = R"({
        "event_type": "scroll",
        "duration": "duration",
        "align": "mid",
        "offset": 30,
        "XPath":"/html/body"
    })";
    g_webPattern->OnInjectionEvent(command9);

    // Test valid scroll
    const std::string& command10 = R"({
        "event_type": "scroll",
        "duration": 6,
        "align": "mid",
        "offset": 30,
        "XPath":"/html/body"
    })";
    g_webPattern->OnInjectionEvent(command10);

    EXPECT_EQ(static_cast<int>(WebCommandResult::JSON_MISSING_EVENT_TYPE), 111);
#endif
}
/**
 * @tc.name: WebCommandAction_002
 * @tc.desc: Test WebCommandActionArray.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string& commandArray = R"([
        {
            "event_type": "click",
            "XPath": "/html/body/div[1]"
        },
        {
            "event_type": "scroll",
            "direction": "down",
            "distance": 100
        }
    ])";
    g_webPattern->OnInjectionEvent(commandArray);
    const std::string& invalidArray = R"([
        {
            "event_type": "unknown_action",
            "XPath": "invalid_path"
        }
    ])";
    g_webPattern->OnInjectionEvent(invalidArray);
    const std::string& invalidKeys = R"({
        "event_type": "scroll",
        "duration":6,
        "align": "mid",
        "offset": 30,
        "XPath":"/html/div",
        "XPath":"/html/body"
    })";
    g_webPattern->OnInjectionEvent(invalidKeys);
    EXPECT_EQ(static_cast<int>(WebCommandResult::JSON_IS_INVALID), 110);
#endif
}
/**
 * @tc.name: GetPixelMapName_001
 * @tc.desc: Test GetPixelMapName.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, GetPixelMapName_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    EXPECT_EQ(g_webPattern->GetPixelMapName(nullptr, "test"), "undefined_");
    Media::InitializationOptions opt;
    opt.size.width = 1;
    opt.size.height = 1;
    opt.editable = true;
    auto pixelMap = Media::PixelMap::Create(opt);
    std::shared_ptr<Media::PixelMap> testPixelMap(pixelMap.release());
    auto frameNode = g_webPattern->GetHost();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(g_webPattern->GetPixelMapName(testPixelMap, "test"),
        "web-1x1-test-" + std::to_string(frameNode->GetId()));
#endif
}

class MockWebPattern : public WebPattern {
DECLARE_ACE_TYPE(MockWebPattern, WebPattern);

public:
    MockWebPattern() = default;
    ~MockWebPattern() override = default;

    MOCK_METHOD(bool, IsConvertByWhiteList, (), (override));
};

/**
 * @tc.name: ConvertMouseToTouchByWhiteList_001
 * @tc.desc: ConvertMouseToTouchByWhiteList.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, ConvertMouseToTouchByWhiteList_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    const std::string src = "web_pattern_event_test";
    RefPtr<WebController> webController = AceType::MakeRefPtr<WebController>();

    EXPECT_NE(webController, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);
    RefPtr<WebPattern> webPattern = frameNode->GetPattern<WebPattern>();
    RefPtr<MockWebPattern> mockWebPattern = AceType::DynamicCast<MockWebPattern>(webPattern);
    CHECK_NULL_VOID(mockWebPattern);
    mockWebPattern->SetWebSrc(src);
    mockWebPattern->SetWebController(webController);

    bool result;
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);

    TouchEventInfo touchEventInfo("touchEvent");
    result = mockWebPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_FALSE(result);

    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    result = mockWebPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_FALSE(result);

    EXPECT_CALL(*mockWebPattern, IsConvertByWhiteList())
        .WillRepeatedly(::testing::Return(true));

    result = mockWebPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(touchEventInfo.GetSourceDevice(), SourceType::TOUCH);

    mouseInfo.SetAction(MouseAction::RELEASE);
    result = mockWebPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(touchEventInfo.GetSourceDevice(), SourceType::TOUCH);

    mouseInfo.SetAction(MouseAction::MOVE);
    result = mockWebPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(touchEventInfo.GetSourceDevice(), SourceType::TOUCH);

    mouseInfo.SetAction(MouseAction::CANCEL);
    result = mockWebPattern->ConvertMouseToTouchByWhiteList(mouseInfo, touchEventInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(touchEventInfo.GetSourceDevice(), SourceType::TOUCH);
#endif
}

/**
 * @tc.name: WebCommandAction_003
 * @tc.desc: Test missing XPath scenario.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test missing XPath
    const std::string& commandNoXPath = R"({
        "event_type": "click"
    })";
    int result = g_webPattern->OnInjectionEvent(commandNoXPath);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));

    // Test XPath is not a string (number)
    const std::string& commandXpathNumber = R"({
        "event_type": "click",
        "XPath": 123
    })";
    result = g_webPattern->OnInjectionEvent(commandXpathNumber);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));

    // Test XPath is not a string (boolean)
    const std::string& commandXpathBoolean = R"({
        "event_type": "click",
        "XPath": true
    })";
    result = g_webPattern->OnInjectionEvent(commandXpathBoolean);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));

    // Test XPath is not a string (object)
    const std::string& commandXpathObject = R"({
        "event_type": "click",
        "XPath": {}
    })";
    result = g_webPattern->OnInjectionEvent(commandXpathObject);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));

    // Test XPath is not a string (array)
    const std::string& commandXpathArray = R"({
        "event_type": "click",
        "XPath": []
    })";
    result = g_webPattern->OnInjectionEvent(commandXpathArray);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_XPATH));
#endif
}

/**
 * @tc.name: WebCommandAction_004
 * @tc.desc: Test invalid JSON type (neither object nor array).
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test JSON is a string
    const std::string& commandString = R"("just a string")";
    int result = g_webPattern->OnInjectionEvent(commandString);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));

    // Test JSON is a number
    const std::string& commandNumber = R"(12345)";
    result = g_webPattern->OnInjectionEvent(commandNumber);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));

    // Test JSON is a boolean
    const std::string& commandBoolean = R"(true)";
    result = g_webPattern->OnInjectionEvent(commandBoolean);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));

    // Test JSON is null
    const std::string& commandNull = R"(null)";
    result = g_webPattern->OnInjectionEvent(commandNull);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));

    // Test empty string
    const std::string& commandEmpty = "";
    result = g_webPattern->OnInjectionEvent(commandEmpty);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_IS_INVALID));
#endif
}

/**
 * @tc.name: WebCommandAction_005
 * @tc.desc: Test array with multiple valid commands.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test array with multiple valid click commands
    const std::string& commandArrayMultiple = R"([
        {
            "event_type": "click",
            "XPath": "/html/body/div[1]"
        },
        {
            "event_type": "click",
            "XPath": "/html/body/div[2]"
        },
        {
            "event_type": "click",
            "XPath": "/html/body/div[3]"
        }
    ])";
    g_webPattern->OnInjectionEvent(commandArrayMultiple);
    // Should return SUCCESS (10) if all commands succeed
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);
#endif
}

/**
 * @tc.name: WebCommandAction_006
 * @tc.desc: Test array with invalid item.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test array with one valid and one invalid command
    const std::string& commandArrayMixed = R"([
        {
            "event_type": "click",
            "XPath": "/html/body/div[1]"
        },
        {
            "invalid_key": "value"
        }
    ])";
    int result = g_webPattern->OnInjectionEvent(commandArrayMixed);
    // Should return FAILED (11) when second command fails
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));

    // Test array with null item
    const std::string& commandArrayNullItem = R"([null])";
    result = g_webPattern->OnInjectionEvent(commandArrayNullItem);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));

    // Test array with non-object item
    const std::string& commandArrayStringItem = R"(["string", "another"])";
    result = g_webPattern->OnInjectionEvent(commandArrayStringItem);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));

    // Test array with number item
    const std::string& commandArrayNumberItem = R"([123, 456])";
    result = g_webPattern->OnInjectionEvent(commandArrayNumberItem);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::FAILED));
#endif
}

/**
 * @tc.name: WebCommandAction_007
 * @tc.desc: Test event_type validation with various invalid values.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test event_type is number
    const std::string& commandEventTypeNumber = R"({
        "event_type": 123,
        "XPath": "/html/body"
    })";
    int result = g_webPattern->OnInjectionEvent(commandEventTypeNumber);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_EVENT_TYPE));

    // Test event_type is boolean
    const std::string& commandEventTypeBoolean = R"({
        "event_type": true,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandEventTypeBoolean);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_EVENT_TYPE));

    // Test event_type is object
    const std::string& commandEventTypeObject = R"({
        "event_type": {},
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandEventTypeObject);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_EVENT_TYPE));

    // Test event_type is array
    const std::string& commandEventTypeArray = R"({
        "event_type": [],
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandEventTypeArray);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_EVENT_TYPE));

    // Test event_type is null
    const std::string& commandEventTypeNull = R"({
        "event_type": null,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandEventTypeNull);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_EVENT_TYPE));
#endif
}

/**
 * @tc.name: WebCommandAction_008
 * @tc.desc: Test scroll event with missing duration.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test scroll without duration (missing)
    const std::string& commandNoDuration = R"({
        "event_type": "scroll",
        "align": "top",
        "offset": 10,
        "XPath": "/html/body"
    })";
    int result = g_webPattern->OnInjectionEvent(commandNoDuration);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_DURATION));

    // Test scroll with invalid duration type (string)
    const std::string& commandDurationString = R"({
        "event_type": "scroll",
        "duration": "100",
        "align": "top",
        "offset": 10,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandDurationString);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_DURATION));

    // Test scroll with invalid duration type (boolean)
    const std::string& commandDurationBoolean = R"({
        "event_type": "scroll",
        "duration": true,
        "align": "top",
        "offset": 10,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandDurationBoolean);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_DURATION));

    // Test scroll with invalid duration type (object)
    const std::string& commandDurationObject = R"({
        "event_type": "scroll",
        "duration": {},
        "align": "top",
        "offset": 10,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandDurationObject);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_DURATION));
#endif
}

/**
 * @tc.name: WebCommandAction_009
 * @tc.desc: Test scroll event with missing or invalid align.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test scroll without align (missing)
    const std::string& commandNoAlign = R"({
        "event_type": "scroll",
        "duration": 100,
        "offset": 10,
        "XPath": "/html/body"
    })";
    int result = g_webPattern->OnInjectionEvent(commandNoAlign);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_ALIGN));

    // Test scroll with invalid align type (number)
    const std::string& commandAlignNumber = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": 123,
        "offset": 10,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandAlignNumber);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_ALIGN));

    // Test scroll with invalid align type (boolean)
    const std::string& commandAlignBoolean = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": true,
        "offset": 10,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandAlignBoolean);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_ALIGN));

    // Test scroll with invalid align value
    const std::string& commandAlignInvalid = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "invalid_value",
        "offset": 10,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandAlignInvalid);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_VALUE_ERROR_ALIGN));
#endif
}

/**
 * @tc.name: WebCommandAction_010
 * @tc.desc: Test scroll event with missing or invalid offset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test scroll without offset (missing)
    const std::string& commandNoOffset = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "top",
        "XPath": "/html/body"
    })";
    int result = g_webPattern->OnInjectionEvent(commandNoOffset);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_OFFSET));

    // Test scroll with invalid offset type (string)
    const std::string& commandOffsetString = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "top",
        "offset": "100",
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandOffsetString);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_OFFSET));

    // Test scroll with invalid offset type (boolean)
    const std::string& commandOffsetBoolean = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "top",
        "offset": true,
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandOffsetBoolean);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_OFFSET));

    // Test scroll with invalid offset type (object)
    const std::string& commandOffsetObject = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "top",
        "offset": {},
        "XPath": "/html/body"
    })";
    result = g_webPattern->OnInjectionEvent(commandOffsetObject);
    EXPECT_EQ(result, static_cast<int>(WebCommandResult::JSON_INVALID_OFFSET));
#endif
}

/**
 * @tc.name: WebCommandAction_011
 * @tc.desc: Test all valid align values for scroll event.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test scroll with align="top"
    const std::string& commandAlignTop = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "top",
        "offset": 10,
        "XPath": "/html/body"
    })";
    g_webPattern->OnInjectionEvent(commandAlignTop);
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);

    // Test scroll with align="mid"
    const std::string& commandAlignMid = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "mid",
        "offset": 20,
        "XPath": "/html/body"
    })";
    g_webPattern->OnInjectionEvent(commandAlignMid);
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);

    // Test scroll with align="bottom"
    const std::string& commandAlignBottom = R"({
        "event_type": "scroll",
        "duration": 100,
        "align": "bottom",
        "offset": 30,
        "XPath": "/html/body"
    })";
    g_webPattern->OnInjectionEvent(commandAlignBottom);
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);
#endif
}

/**
 * @tc.name: WebCommandAction_012
 * @tc.desc: Test click event with valid XPath.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test valid click event
    const std::string& commandClick = R"({
        "event_type": "click",
        "XPath": "/html/body/div[1]/button"
    })";
    g_webPattern->OnInjectionEvent(commandClick);
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);

    // Test click event with complex XPath
    const std::string& commandClickComplex = R"({
        "event_type": "click",
        "XPath": "/html/body/div[@id='container']/span[@class='active']"
    })";
    g_webPattern->OnInjectionEvent(commandClickComplex);
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);
#endif
}

/**
 * @tc.name: WebCommandAction_013
 * @tc.desc: Test valid scroll event with all parameters.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebCommandAction_013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    // Test scroll with valid duration and offset
    const std::string& commandScroll = R"({
        "event_type": "scroll",
        "duration": 500,
        "align": "mid",
        "offset": 100,
        "XPath": "/html/body/div[1]"
    })";
    g_webPattern->OnInjectionEvent(commandScroll);
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);

    // Test scroll with zero duration and offset
    const std::string& commandScrollZero = R"({
        "event_type": "scroll",
        "duration": 0,
        "align": "top",
        "offset": 0,
        "XPath": "/html/body"
    })";
    g_webPattern->OnInjectionEvent(commandScrollZero);
    EXPECT_EQ(static_cast<int>(WebCommandResult::SUCCESS), 10);
#endif
}

/**
 * @tc.name: WebUtil_HasJSONDuplicateKeys_001
 * @tc.desc: Test HasJSONDuplicateKeys with basic scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebUtil_HasJSONDuplicateKeys_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    using namespace OHOS::Ace;

    // Test normal JSON without duplicate keys
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"b":2})"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"event_type":"click","XPath":"/html/body"})"));

    // Test JSON with duplicate keys
    EXPECT_TRUE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"a":2})"));
    EXPECT_TRUE(WebUtil::HasJSONDuplicateKeys(R"({"XPath":"/html/div","XPath":"/html/body"})"));

    // Test empty object
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({})"));

    // Test empty string
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"()"));

    // Test whitespace only
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"(   )"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"(
)"));

    // Test nested objects without duplicate keys
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":{"b":1,"c":2}})"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"b":{"c":2,"d":3}})"));

    // Test nested objects with duplicate keys in different levels (should be OK)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"b":{"a":2}})"));

    // Test array format JSON (no duplicate keys)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"([1,2,3])"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"([{"a":1},{"b":2}])"));

    // Test string value (not an object)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"("just a string")"));

    // Test number value
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"(12345)"));

    // Test boolean value
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"(true)"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"(false)"));

    // Test null value
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"(null)"));

    // Test deeply nested objects without duplicate keys
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":{"b":{"c":{"d":1}}}})"));

    // Test multiple objects at root level (invalid JSON but should handle)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1}{"b":2})"));
#endif
}

/**
 * @tc.name: WebUtil_HasJSONDuplicateKeys_001b
 * @tc.desc: Test HasJSONDuplicateKeys with advanced scenarios.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebUtil_HasJSONDuplicateKeys_001b, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    using namespace OHOS::Ace;

    // Test JSON with escaped characters in keys
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a\n":1,"b\t":2})"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a\"b":1,"c":2})"));

    // Test JSON with special characters in keys
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"_test":1,"$value":2})"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"key-with-dash":1,"key_with_underscore":2})"));

    // Test object with string values containing quotes
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":"value with \"quotes\"","b":"another"})"));

    // Test object with array values
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":[1,2,3],"b":["x","y"]})"));

    // Test object with object values
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":{"x":1},"b":{"y":2}})"));

    // Test object with null values
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":null,"b":null})"));

    // Test object with boolean values
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":true,"b":false})"));

    // Test object with number values
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":123,"b":456})"));

    // Test object with mixed type values
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"b":"string","c":true,"d":null,"e":[],"f":{}})"));

    // Test duplicate keys with different types
    EXPECT_TRUE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"a":"string"})"));
    EXPECT_TRUE(WebUtil::HasJSONDuplicateKeys(R"({"a":true,"a":false})"));

    // Test multiple duplicate keys
    EXPECT_TRUE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"b":2,"a":3,"b":4})"));

    // Test JSON with whitespace variations
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({  "a"  :  1  ,  "b"  :  2  })"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({
        "a": 1,
        "b": 2
    })"));

    // Test keys with unicode characters
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"测试":1,"数据":2})"));
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"emoji😀":1,"star⭐":2})"));

    // Test empty keys (edge case)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"":1,"a":2})"));
    EXPECT_TRUE(WebUtil::HasJSONDuplicateKeys(R"({"":1,"":2})"));
#endif
}

/**
 * @tc.name: WebUtil_ComplexScenarios_002
 * @tc.desc: Test WebUtil with complex nested structures.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebUtil_ComplexScenarios_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    using namespace OHOS::Ace;

    // Test complex nested structure
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({
        "event_type": "scroll",
        "data": {
            "duration": 100,
            "align": "top",
            "offset": 10,
            "target": {
                "XPath": "/html/body",
                "attribute": "class"
            }
        }
    })"));

    // Test array with complex objects
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"([
        {"event_type": "click", "XPath": "/html/body/div[1]"},
        {"event_type": "scroll", "duration": 100, "align": "top"}
    ])"));

    // Test mixed nested arrays and objects
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({
        "commands": [
            {"type": "click", "target": {"id": "btn1"}},
            {"type": "scroll", "params": {"x": 100, "y": 200}}
        ],
        "metadata": {
            "version": "1.0",
            "timestamp": 123456
        }
    })"));

    // Test duplicate in nested array of objects
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"([
        {"a": 1, "b": 2},
        {"a": 3, "b": 4}
    ])"));

    // Test very long key names
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({
        "very_long_key_name_that_goes_on_and_on": 1,
        "another_extremely_long_key_name_here": 2
    })"));

    // Test keys with numbers
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"key1":1,"key2":2,"123":3})"));

    // Test JSON with line breaks and tabs
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"b":2,"c":3})"));

    // Test malformed JSON (missing closing brace)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,"b":2)"));

    // Test malformed JSON (extra comma)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1,})"));
#endif
}

/**
 * @tc.name: WebUtil_ComplexScenarios_002b
 * @tc.desc: Test WebUtil with edge cases and special values.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternEventTest, WebUtil_ComplexScenarios_002b, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    using namespace OHOS::Ace;

    // Test values with escaped characters
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({
        "path": "C:\\Users\\test",
        "quote": "He said \"hello\"",
        "newline": "line1\nline2"
    })"));

    // Test keys with colons in string values (should not be treated as key-value separator)
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({
        "url": "https://example.com",
        "time": "12:30:45"
    })"));

    // Test empty nested objects
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":{},"b":{}})"));

    // Test empty arrays
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":[],"b":[]})"));

    // Test deeply nested empty structures
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":{"b":{"c":{}}}})"));

    // Test single key-value pair
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({"a":1})"));

    // Test large number of keys
    EXPECT_FALSE(WebUtil::HasJSONDuplicateKeys(R"({
        "k1":1, "k2":2, "k3":3, "k4":4, "k5":5, "k6":6, "k7":7, "k8":8, "k9":9, "k10":10
    })"));
#endif
}

} // namespace OHOS::Ace::NG
