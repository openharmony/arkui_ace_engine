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

#include "core/components/web/web_event.h"
#define protected public
#include "core/components_ng/pattern/text/base_text_select_overlay.h"
#undef protected
#include "core/components_ng/pattern/web/web_context_select_overlay.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/base/mock_task_executor.h"
#define private public
#include "test/mock/core/common/mock_container.h"
#undef private
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {

class MockWebContextMenuParam : public WebContextMenuParam {
    DECLARE_ACE_TYPE(MockWebContextMenuParam, WebContextMenuParam);
public:
    MockWebContextMenuParam() = default;
    ~MockWebContextMenuParam() override = default;

    std::string GetLinkUrl() const override
    {
        return "";
    }

    std::string GetUnfilteredLinkUrl() const override
    {
        return "";
    }

    std::string GetSourceUrl() const override
    {
        return "";
    }

    bool IsEditable() const override
    {
        return false;
    }

    int GetEditStateFlags() const override
    {
        return 0;
    }

    int GetSourceType() const override
    {
        return 0;
    }

    int GetMediaType() const override
    {
        return 0;
    }

    int GetInputFieldType() const override
    {
        return 0;
    }

    MOCK_METHOD(int32_t, GetXCoord, (), (const, override));
    MOCK_METHOD(int32_t, GetYCoord, (), (const, override));
    MOCK_METHOD(bool, HasImageContents, (), (const, override));
    MOCK_METHOD(std::string, GetSelectionText, (), (const, override));
};

class MockContextMenuResult : public ContextMenuResult {
    DECLARE_ACE_TYPE(MockContextMenuResult, ContextMenuResult);
public:
    MockContextMenuResult() = default;
    ~MockContextMenuResult() override = default;

    MOCK_METHOD(void, Cancel, (), (const, override));
    MOCK_METHOD(void, CopyImage, (), (const, override));
    MOCK_METHOD(void, Copy, (), (const, override));
    MOCK_METHOD(void, Paste, (), (const, override));
    MOCK_METHOD(void, Cut, (), (const, override));
    MOCK_METHOD(void, SelectAll, (), (const, override));
};

class WebContextSelectOverlayTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebContextSelectOverlayTest::SetUpTestCase() {}
void WebContextSelectOverlayTest::TearDownTestCase() {}
void WebContextSelectOverlayTest::SetUp() {}
void WebContextSelectOverlayTest::TearDown() {}

/**
 * @tc.name: PreProcessOverlay_001
 * @tc.desc: Test function PreProcessOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, PreProcessOverlay_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    OverlayRequest request;
    request.menuIsShow = false;
    request.hideHandle = false;
    request.animation = false;
    request.hideHandleLine = false;
    request.requestCode = 0;
    bool result = overlay.PreProcessOverlay(request);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PreProcessOverlay_002
 * @tc.desc: Test function PreProcessOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, PreProcessOverlay_002, TestSize.Level1)
{
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::SetUp();

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    OverlayRequest request;
    request.menuIsShow = false;
    request.hideHandle = false;
    request.animation = false;
    request.hideHandleLine = false;
    request.requestCode = 0;
    bool result = overlay.PreProcessOverlay(request);
    EXPECT_TRUE(result);

    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: CheckHandleVisible_001
 * @tc.desc: Test function CheckHandleVisible.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, CheckHandleVisible_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    RectF paintRect(0, 0, 100.0f, 100.0f);
    bool result = overlay.CheckHandleVisible(paintRect);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetFirstHandleInfo_001
 * @tc.desc: Test function GetFirstHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetFirstHandleInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetFirstHandleInfo();
    EXPECT_EQ(result, std::nullopt);
}

/**
 * @tc.name: GetFirstHandleInfo_002
 * @tc.desc: Test function GetFirstHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetFirstHandleInfo_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetFirstHandleInfo();
    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(result.value().isShow);
}

/**
 * @tc.name: GetSecondHandleInfo_001
 * @tc.desc: Test function GetSecondHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetSecondHandleInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetSecondHandleInfo();
    EXPECT_EQ(result, std::nullopt);
}

/**
 * @tc.name: GetSecondHandleInfo_002
 * @tc.desc: Test function GetSecondHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetSecondHandleInfo_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetSecondHandleInfo();
    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(result.value().isShow);
}

/**
 * @tc.name: OnUpdateMenuInfo_001
 * @tc.desc: Test function OnUpdateMenuInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateMenuInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_TRUE(selectMenuInfo.showCopyAll);
    EXPECT_TRUE(selectMenuInfo.showCopy);
    EXPECT_TRUE(selectMenuInfo.showCut);
    EXPECT_TRUE(selectMenuInfo.showPaste);
    EXPECT_FALSE(selectMenuInfo.menuIsShow);
    EXPECT_FALSE(selectMenuInfo.showCameraInput);
}

/**
 * @tc.name: OnUpdateMenuInfo_002
 * @tc.desc: Test function OnUpdateMenuInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateMenuInfo_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_TRUE(selectMenuInfo.showCopyAll);
    EXPECT_TRUE(selectMenuInfo.showCopy);
    EXPECT_TRUE(selectMenuInfo.showCut);
    EXPECT_TRUE(selectMenuInfo.showPaste);
    EXPECT_FALSE(selectMenuInfo.menuIsShow);
    EXPECT_FALSE(selectMenuInfo.showCameraInput);
}

/**
 * @tc.name: OnUpdateMenuInfo_003
 * @tc.desc: Test function OnUpdateMenuInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateMenuInfo_003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    auto mockMenuParam = AceType::DynamicCast<MockWebContextMenuParam>(menuParam);
    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(false));
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_TRUE(selectMenuInfo.showCopyAll);
    EXPECT_TRUE(selectMenuInfo.showCopy);
    EXPECT_TRUE(selectMenuInfo.showCut);
    EXPECT_TRUE(selectMenuInfo.showPaste);
    EXPECT_FALSE(selectMenuInfo.menuIsShow);
    EXPECT_FALSE(selectMenuInfo.showCameraInput);
}

/**
 * @tc.name: OnUpdateMenuInfo_004
 * @tc.desc: Test function OnUpdateMenuInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateMenuInfo_004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_VIEWPORT;
    auto mockMenuParam = AceType::DynamicCast<MockWebContextMenuParam>(menuParam);
    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(false));
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_TRUE(selectMenuInfo.showCopyAll);
    EXPECT_FALSE(selectMenuInfo.showCopy);
    EXPECT_FALSE(selectMenuInfo.showCut);
    EXPECT_FALSE(selectMenuInfo.showPaste);
    EXPECT_TRUE(selectMenuInfo.menuIsShow);
    EXPECT_FALSE(selectMenuInfo.showCameraInput);
}

/**
 * @tc.name: GetSelectArea_001
 * @tc.desc: Test function GetSelectArea.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetSelectArea_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    RectF result = overlay.GetSelectArea();
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.Width(), 0);
    EXPECT_EQ(result.Height(), 0);
}

/**
 * @tc.name: GetSelectArea_002
 * @tc.desc: Test function GetSelectArea.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetSelectArea_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RectF result = overlay.GetSelectArea();
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.Width(), 0);
    EXPECT_EQ(result.Height(), 0);
}

/**
 * @tc.name: GetSelectedText_001
 * @tc.desc: Test function GetSelectedText.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetSelectedText_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    std::string result = overlay.GetSelectedText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetSelectedText_002
 * @tc.desc: Test function GetSelectedText.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetSelectedText_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    std::string result = overlay.GetSelectedText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetSelectedText_003
 * @tc.desc: Test function GetSelectedText.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, GetSelectedText_003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    auto mockMenuParam = AceType::DynamicCast<MockWebContextMenuParam>(menuParam);
    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return("HelloWorld"));
    std::string result = overlay.GetSelectedText();
    EXPECT_EQ(result, "HelloWorld");
}

/**
 * @tc.name: OnMenuItemAction_001
 * @tc.desc: Test function OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnMenuItemAction_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    OptionMenuActionId actionId = OptionMenuActionId::AI_WRITE;
    OptionMenuType type = OptionMenuType::NO_MENU;
    overlay.OnMenuItemAction(actionId, type);
    EXPECT_EQ(overlay.GetPattern<WebPattern>(), nullptr);
}

/**
 * @tc.name: OnMenuItemAction_002
 * @tc.desc: Test function OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnMenuItemAction_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    OptionMenuActionId actionId = OptionMenuActionId::AI_WRITE;
    OptionMenuType type = OptionMenuType::NO_MENU;
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnMenuItemAction_003
 * @tc.desc: Test function OnMenuItemAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnMenuItemAction_003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    auto mockMenuParam = AceType::DynamicCast<MockWebContextMenuParam>(menuParam);
    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return("HelloWorld"));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(false));
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);

    OptionMenuActionId actionId = OptionMenuActionId::COPY;
    OptionMenuType type = OptionMenuType::NO_MENU;
    auto mockMenuResult = AceType::DynamicCast<MockContextMenuResult>(menuResult);
    EXPECT_CALL(*mockMenuResult, Copy);
    overlay.OnMenuItemAction(actionId, type);

    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(true));
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_CALL(*mockMenuResult, CopyImage);
    overlay.OnMenuItemAction(actionId, type);

    actionId = OptionMenuActionId::CUT;
    EXPECT_CALL(*mockMenuResult, Cut);
    overlay.OnMenuItemAction(actionId, type);

    actionId = OptionMenuActionId::PASTE;
    EXPECT_CALL(*mockMenuResult, Paste);
    overlay.OnMenuItemAction(actionId, type);

    actionId = OptionMenuActionId::SELECT_ALL;
    EXPECT_CALL(*mockMenuResult, SelectAll);
    overlay.OnMenuItemAction(actionId, type);

    actionId = OptionMenuActionId::DISAPPEAR;
    EXPECT_CALL(*mockMenuResult, Cancel);
    overlay.OnMenuItemAction(actionId, type);

    actionId = OptionMenuActionId::AI_WRITE;
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnHandleMoveDone_001
 * @tc.desc: Test function OnHandleMoveDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnHandleMoveDone_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    RectF rect;
    bool isFirst = false;
    overlay.OnHandleMoveDone(rect, isFirst);
    EXPECT_EQ(overlay.GetPattern<WebPattern>(), nullptr);
}

/**
 * @tc.name: OnHandleMoveDone_002
 * @tc.desc: Test function OnHandleMoveDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnHandleMoveDone_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RectF rect;
    bool isFirst = false;
    overlay.OnHandleMoveDone(rect, isFirst);
}

/**
 * @tc.name: OnCloseOverlay_001
 * @tc.desc: Test function OnCloseOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnCloseOverlay_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    OptionMenuType menuType = OptionMenuType::NO_MENU;
    CloseReason reason = CloseReason::CLOSE_REASON_NORMAL;
    RefPtr<OverlayInfo> info;
    overlay.OnCloseOverlay(menuType, reason, info);
    EXPECT_EQ(overlay.GetPattern<WebPattern>(), nullptr);
}

/**
 * @tc.name: OnCloseOverlay_002
 * @tc.desc: Test function OnCloseOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnCloseOverlay_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    OptionMenuType menuType = OptionMenuType::NO_MENU;
    CloseReason reason = CloseReason::CLOSE_REASON_NORMAL;
    RefPtr<OverlayInfo> info;
    overlay.OnCloseOverlay(menuType, reason, info);
}

/**
 * @tc.name: OnCloseOverlay_003
 * @tc.desc: Test function OnCloseOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnCloseOverlay_003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    OptionMenuType menuType = OptionMenuType::NO_MENU;
    CloseReason reason = CloseReason::CLOSE_REASON_NORMAL;
    RefPtr<OverlayInfo> info;
    auto mockMenuResult = AceType::DynamicCast<MockContextMenuResult>(menuResult);
    EXPECT_CALL(*mockMenuResult, Cancel);
    overlay.OnCloseOverlay(menuType, reason, info);
}

/**
 * @tc.name: OnHandleGlobalTouchEvent_001
 * @tc.desc: Test function OnHandleGlobalTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnHandleGlobalTouchEvent_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    SourceType sourceType = SourceType::MOUSE;
    TouchType touchType = TouchType::DOWN;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_TRUE(overlay.IsMouseClickDown(sourceType, touchType));

    sourceType = SourceType::TOUCH;
    touchType = TouchType::UP;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_TRUE(overlay.IsTouchUp(sourceType, touchType));

    sourceType = SourceType::NONE;
    touchType = TouchType::UNKNOWN;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_001
 * @tc.desc: Test function OnUpdateSelectOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateSelectOverlayInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextSelectOverlay overlay(textBase);

    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_FALSE(selectInfo.handlerColor.has_value());
    EXPECT_FALSE(selectInfo.handleReverse);
    EXPECT_FALSE(selectInfo.isUsingMouse);
    EXPECT_EQ(selectInfo.rightClickOffset, OffsetF());
    EXPECT_FALSE(selectInfo.isNewAvoid);
    EXPECT_TRUE(selectInfo.isHandleLineShow);
    EXPECT_FALSE(selectInfo.isSingleHandle);
    EXPECT_FALSE(selectInfo.recreateOverlay);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_002
 * @tc.desc: Test function OnUpdateSelectOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateSelectOverlayInfo_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_FALSE(selectInfo.handlerColor.has_value());
    EXPECT_FALSE(selectInfo.handleReverse);
    EXPECT_FALSE(selectInfo.isUsingMouse);
    EXPECT_EQ(selectInfo.rightClickOffset, OffsetF());
    EXPECT_FALSE(selectInfo.isNewAvoid);
    EXPECT_TRUE(selectInfo.isHandleLineShow);
    EXPECT_FALSE(selectInfo.isSingleHandle);
    EXPECT_FALSE(selectInfo.recreateOverlay);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_003
 * @tc.desc: Test function OnUpdateSelectOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateSelectOverlayInfo_003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    auto mockMenuParam = AceType::DynamicCast<MockWebContextMenuParam>(menuParam);
    EXPECT_CALL(*mockMenuParam, GetXCoord).Times(1).WillOnce(Return(100));
    EXPECT_CALL(*mockMenuParam, GetYCoord).Times(1).WillOnce(Return(100));

    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    overlay.SetIsSingleHandle(false);
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_TRUE(selectInfo.handlerColor.has_value());
    EXPECT_FALSE(selectInfo.handleReverse);
    EXPECT_TRUE(selectInfo.isUsingMouse);
    EXPECT_EQ(selectInfo.rightClickOffset, OffsetF(100.0f, 100.0f));
    EXPECT_TRUE(selectInfo.isNewAvoid);
    EXPECT_TRUE(selectInfo.isHandleLineShow);
    EXPECT_FALSE(selectInfo.isSingleHandle);
    EXPECT_FALSE(selectInfo.recreateOverlay);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_004
 * @tc.desc: Test function OnUpdateSelectOverlayInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextSelectOverlayTest, OnUpdateSelectOverlayInfo_004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));;
    WebContextSelectOverlay overlay(textBase);

    RefPtr<WebContextMenuParam> menuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(menuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    auto mockMenuParam = AceType::DynamicCast<MockWebContextMenuParam>(menuParam);
    EXPECT_CALL(*mockMenuParam, GetXCoord).Times(1).WillOnce(Return(10));
    EXPECT_CALL(*mockMenuParam, GetYCoord).Times(1).WillOnce(Return(10));

    SelectOverlayInfo selectInfo;
    int32_t requestCode = REQUEST_RECREATE;
    overlay.SetIsSingleHandle(true);
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_TRUE(selectInfo.handlerColor.has_value());
    EXPECT_FALSE(selectInfo.handleReverse);
    EXPECT_TRUE(selectInfo.isUsingMouse);
    EXPECT_EQ(selectInfo.rightClickOffset, OffsetF(10.0f, 10.0f));
    EXPECT_TRUE(selectInfo.isNewAvoid);
    EXPECT_FALSE(selectInfo.isHandleLineShow);
    EXPECT_TRUE(selectInfo.isSingleHandle);
    EXPECT_TRUE(selectInfo.recreateOverlay);
}

} // namespace OHOS::Ace::NG
