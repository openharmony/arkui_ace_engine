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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/web_event.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/base_text_select_overlay.h"
#include "core/components_ng/pattern/web/web_context_menu_overlay.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

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
        return editStateFlags_;
    }

    void SetEditStateFlags(int flags) { editStateFlags_ = flags; }

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

private:
    int editStateFlags_ = 0;
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
    MOCK_METHOD(void, Undo, (), (const, override));
    MOCK_METHOD(void, Redo, (), (const, override));
    MOCK_METHOD(void, PasteAndMatchStyle, (), (const, override));
    MOCK_METHOD(void, RequestPasswordAutoFill, (), (const, override));
};

class WebContextMenuOverlayTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebContextMenuOverlayTest::SetUpTestCase() {}
void WebContextMenuOverlayTest::TearDownTestCase() {}
void WebContextMenuOverlayTest::SetUp() {}
void WebContextMenuOverlayTest::TearDown() {}

/**
 * @tc.name: PreProcessOverlay_001
 * @tc.desc: Test PreProcessOverlay with null textBase.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, PreProcessOverlay_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

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
 * @tc.name: CheckHandleVisible_001
 * @tc.desc: Test CheckHandleVisible always returns false.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, CheckHandleVisible_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    RectF paintRect(0, 0, 100.0f, 100.0f);
    bool result = overlay.CheckHandleVisible(paintRect);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetFirstHandleInfo_001
 * @tc.desc: Test GetFirstHandleInfo with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetFirstHandleInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetFirstHandleInfo();
    EXPECT_EQ(result, std::nullopt);
}

/**
 * @tc.name: GetFirstHandleInfo_002
 * @tc.desc: Test GetFirstHandleInfo with valid pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetFirstHandleInfo_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetFirstHandleInfo();
    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(result.value().isShow);
}

/**
 * @tc.name: GetSecondHandleInfo_001
 * @tc.desc: Test GetSecondHandleInfo with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetSecondHandleInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetSecondHandleInfo();
    EXPECT_EQ(result, std::nullopt);
}

/**
 * @tc.name: GetSecondHandleInfo_002
 * @tc.desc: Test GetSecondHandleInfo with valid pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetSecondHandleInfo_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    std::optional<SelectHandleInfo> result = overlay.GetSecondHandleInfo();
    ASSERT_TRUE(result.has_value());
    EXPECT_FALSE(result.value().isShow);
}

/**
 * @tc.name: OnUpdateMenuInfo_001
 * @tc.desc: Test OnUpdateMenuInfo with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateMenuInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_TRUE(selectMenuInfo.showCopyAll);
}

/**
 * @tc.name: OnUpdateMenuInfo_002
 * @tc.desc: Test OnUpdateMenuInfo with null contextMenuParam.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateMenuInfo_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_TRUE(selectMenuInfo.showCopyAll);
}

/**
 * @tc.name: OnUpdateMenuInfo_003
 * @tc.desc: Test OnUpdateMenuInfo with all edit state flags enabled.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateMenuInfo_003, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    int allFlags = OHOS::NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_CUT |
                   OHOS::NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_COPY |
                   OHOS::NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_PASTE |
                   OHOS::NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_SELECT_ALL;
    mockMenuParam->SetEditStateFlags(allFlags);

    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return("text"));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(false));

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_TRUE(selectMenuInfo.showCut);
    EXPECT_TRUE(selectMenuInfo.showCopy);
    EXPECT_TRUE(selectMenuInfo.showPaste);
    EXPECT_TRUE(selectMenuInfo.showCopyAll);
    EXPECT_EQ(selectMenuInfo.menuType, OptionMenuType::MOUSE_MENU);
    EXPECT_FALSE(selectMenuInfo.showCameraInput);
}

/**
 * @tc.name: OnUpdateMenuInfo_004
 * @tc.desc: Test OnUpdateMenuInfo with no edit state flags.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateMenuInfo_004, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    mockMenuParam->SetEditStateFlags(0); // No flags

    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(false));

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    EXPECT_FALSE(selectMenuInfo.showCut);
    EXPECT_FALSE(selectMenuInfo.showCopy);
    EXPECT_FALSE(selectMenuInfo.showPaste);
    EXPECT_FALSE(selectMenuInfo.showCopyAll);
}

/**
 * @tc.name: OnUpdateMenuInfo_005
 * @tc.desc: Test OnUpdateMenuInfo with hasText and hasImage.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateMenuInfo_005, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    mockMenuParam->SetEditStateFlags(
        OHOS::NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_COPY);

    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return("Hello"));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(true));

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);
    // hasText_ should be true, hasImage_ should be true
}

/**
 * @tc.name: GetSelectArea_001
 * @tc.desc: Test GetSelectArea with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetSelectArea_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    RectF result = overlay.GetSelectArea();
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.Width(), 0);
    EXPECT_EQ(result.Height(), 0);
}

/**
 * @tc.name: GetSelectArea_002
 * @tc.desc: Test GetSelectArea with valid pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetSelectArea_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    RectF result = overlay.GetSelectArea();
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
    EXPECT_EQ(result.Width(), 0);
    EXPECT_EQ(result.Height(), 0);
}

/**
 * @tc.name: GetSelectedText_001
 * @tc.desc: Test GetSelectedText with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetSelectedText_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    std::string result = overlay.GetSelectedText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetSelectedText_002
 * @tc.desc: Test GetSelectedText with valid pattern but null contextMenuParam.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetSelectedText_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    std::string result = overlay.GetSelectedText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetSelectedText_003
 * @tc.desc: Test GetSelectedText with valid contextMenuParam.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, GetSelectedText_003, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return("HelloWorld"));
    std::string result = overlay.GetSelectedText();
    EXPECT_EQ(result, "HelloWorld");
}

/**
 * @tc.name: OnMenuItemAction_002
 * @tc.desc: Test OnMenuItemAction with COPY action and hasText.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnMenuItemAction_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto mockMenuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, mockMenuResult);
    webPattern->OnContextMenuShow(eventInfo);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return("text"));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(false));
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);

    OptionMenuActionId actionId = OptionMenuActionId::COPY;
    OptionMenuType type = OptionMenuType::MOUSE_MENU;
    EXPECT_CALL(*mockMenuResult, Copy).Times(1);
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnMenuItemAction_003
 * @tc.desc: Test OnMenuItemAction with COPY action and hasImage.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnMenuItemAction_003, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto mockMenuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, mockMenuResult);
    webPattern->OnContextMenuShow(eventInfo);

    SelectMenuInfo selectMenuInfo;
    SelectOverlayDirtyFlag dirtyFlag = DIRTY_COPY_ALL_ITEM;
    EXPECT_CALL(*mockMenuParam, GetSelectionText).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*mockMenuParam, HasImageContents).Times(1).WillOnce(Return(true));
    overlay.OnUpdateMenuInfo(selectMenuInfo, dirtyFlag);

    OptionMenuActionId actionId = OptionMenuActionId::COPY;
    OptionMenuType type = OptionMenuType::MOUSE_MENU;
    EXPECT_CALL(*mockMenuResult, CopyImage).Times(1);
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnMenuItemAction_004
 * @tc.desc: Test OnMenuItemAction with CUT action.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnMenuItemAction_004, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto mockMenuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, mockMenuResult);
    webPattern->OnContextMenuShow(eventInfo);

    OptionMenuActionId actionId = OptionMenuActionId::CUT;
    OptionMenuType type = OptionMenuType::MOUSE_MENU;
    EXPECT_CALL(*mockMenuResult, Cut).Times(1);
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnMenuItemAction_005
 * @tc.desc: Test OnMenuItemAction with PASTE action.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnMenuItemAction_005, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto mockMenuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, mockMenuResult);
    webPattern->OnContextMenuShow(eventInfo);

    OptionMenuActionId actionId = OptionMenuActionId::PASTE;
    OptionMenuType type = OptionMenuType::MOUSE_MENU;
    EXPECT_CALL(*mockMenuResult, Paste).Times(1);
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnMenuItemAction_006
 * @tc.desc: Test OnMenuItemAction with SELECT_ALL action.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnMenuItemAction_006, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto mockMenuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, mockMenuResult);
    webPattern->OnContextMenuShow(eventInfo);

    OptionMenuActionId actionId = OptionMenuActionId::SELECT_ALL;
    OptionMenuType type = OptionMenuType::MOUSE_MENU;
    EXPECT_CALL(*mockMenuResult, SelectAll).Times(1);
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnMenuItemAction_007
 * @tc.desc: Test OnMenuItemAction with DISAPPEAR action.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnMenuItemAction_007, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto mockMenuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, mockMenuResult);
    webPattern->OnContextMenuShow(eventInfo);

    OptionMenuActionId actionId = OptionMenuActionId::DISAPPEAR;
    OptionMenuType type = OptionMenuType::MOUSE_MENU;
    EXPECT_CALL(*mockMenuResult, Cancel).Times(1);
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnMenuItemAction_008
 * @tc.desc: Test OnMenuItemAction with unsupported action.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnMenuItemAction_008, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto mockMenuResult = AceType::MakeRefPtr<MockContextMenuResult>();
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, mockMenuResult);
    webPattern->OnContextMenuShow(eventInfo);

    OptionMenuActionId actionId = OptionMenuActionId::AI_WRITE;
    OptionMenuType type = OptionMenuType::MOUSE_MENU;
    // Should enter default case, no action expected
    overlay.OnMenuItemAction(actionId, type);
}

/**
 * @tc.name: OnHandleMoveDone_002
 * @tc.desc: Test OnHandleMoveDone with valid pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnHandleMoveDone_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    RectF rect;
    bool isFirst = false;
    overlay.OnHandleMoveDone(rect, isFirst);
}

/**
 * @tc.name: OnHandleGlobalTouchEvent_001
 * @tc.desc: Test OnHandleGlobalTouchEvent with mouse click down.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnHandleGlobalTouchEvent_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    SourceType sourceType = SourceType::MOUSE;
    TouchType touchType = TouchType::DOWN;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_FALSE(overlay.IsCurrentMenuVisibile());
}

/**
 * @tc.name: OnHandleGlobalTouchEvent_002
 * @tc.desc: Test OnHandleGlobalTouchEvent with touch up.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnHandleGlobalTouchEvent_002, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    SourceType sourceType = SourceType::TOUCH;
    TouchType touchType = TouchType::UP;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_FALSE(overlay.IsCurrentMenuVisibile());
}

/**
 * @tc.name: OnHandleGlobalTouchEvent_003
 * @tc.desc: Test OnHandleGlobalTouchEvent with non-matching source/touch type.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnHandleGlobalTouchEvent_003, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    SourceType sourceType = SourceType::TOUCH_PAD;
    TouchType touchType = TouchType::MOVE;
    overlay.OnHandleGlobalTouchEvent(sourceType, touchType);
    EXPECT_FALSE(overlay.IsCurrentMenuVisibile());
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_001
 * @tc.desc: Test OnUpdateSelectOverlayInfo with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateSelectOverlayInfo_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_FALSE(selectInfo.isNewAvoid);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_002
 * @tc.desc: Test OnUpdateSelectOverlayInfo with null contextMenuParam.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateSelectOverlayInfo_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_003
 * @tc.desc: Test OnUpdateSelectOverlayInfo with valid contextMenuParam and requestCode != REQUEST_RECREATE.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateSelectOverlayInfo_003, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    EXPECT_CALL(*mockMenuParam, GetXCoord).Times(1).WillOnce(Return(100));
    EXPECT_CALL(*mockMenuParam, GetYCoord).Times(1).WillOnce(Return(100));

    SelectOverlayInfo selectInfo;
    int32_t requestCode = 0;
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_TRUE(selectInfo.handlerColor.has_value());
    EXPECT_TRUE(selectInfo.isUsingMouse);
    EXPECT_EQ(selectInfo.rightClickOffset, OffsetF(100.0f, 100.0f));
    EXPECT_EQ(selectInfo.menuInfo.responseType, static_cast<int32_t>(TextResponseType::RIGHT_CLICK));
    EXPECT_EQ(selectInfo.menuInfo.editorType, static_cast<int32_t>(TextSpanType::MIXED));
    EXPECT_TRUE(selectInfo.isNewAvoid);
    EXPECT_FALSE(selectInfo.recreateOverlay);
}

/**
 * @tc.name: OnUpdateSelectOverlayInfo_004
 * @tc.desc: Test OnUpdateSelectOverlayInfo with requestCode == REQUEST_RECREATE.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnUpdateSelectOverlayInfo_004, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    auto mockMenuParam = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> menuResult = nullptr;
    std::shared_ptr<BaseEventInfo> eventInfo = std::make_shared<ContextMenuEvent>(mockMenuParam, menuResult);
    webPattern->OnContextMenuShow(eventInfo);

    EXPECT_CALL(*mockMenuParam, GetXCoord).Times(1).WillOnce(Return(50));
    EXPECT_CALL(*mockMenuParam, GetYCoord).Times(1).WillOnce(Return(50));

    SelectOverlayInfo selectInfo;
    int32_t requestCode = REQUEST_RECREATE;
    overlay.OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    EXPECT_TRUE(selectInfo.recreateOverlay);
}

/**
 * @tc.name: FilterSupportedMenuItems_001
 * @tc.desc: Test FilterSupportedMenuItems with supported items.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, FilterSupportedMenuItems_001, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    std::vector<NG::MenuItemParam> menuItemList;
    NG::MenuItemParam item1;
    item1.menuOptionsParam.id = OH_DEFAULT_CUT;
    menuItemList.push_back(item1);

    NG::MenuItemParam item2;
    item2.menuOptionsParam.id = OH_DEFAULT_COPY;
    menuItemList.push_back(item2);

    NG::MenuItemParam item3;
    item3.menuOptionsParam.id = "unsupported_item";
    menuItemList.push_back(item3);

    auto result = overlay.FilterSupportedMenuItems(menuItemList);
    EXPECT_EQ(result.size(), 2);  // Only supported items
}

/**
 * @tc.name: FilterSupportedMenuItems_002
 * @tc.desc: Test FilterSupportedMenuItems with empty list.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, FilterSupportedMenuItems_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    std::vector<NG::MenuItemParam> menuItemList;
    auto result = overlay.FilterSupportedMenuItems(menuItemList);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: FilterSupportedMenuItems_003
 * @tc.desc: Test FilterSupportedMenuItems with all supported items.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, FilterSupportedMenuItems_003, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    std::vector<NG::MenuItemParam> menuItemList;
    NG::MenuItemParam item1;
    item1.menuOptionsParam.id = OH_DEFAULT_CUT;
    menuItemList.push_back(item1);

    NG::MenuItemParam item2;
    item2.menuOptionsParam.id = OH_DEFAULT_COPY;
    menuItemList.push_back(item2);

    NG::MenuItemParam item3;
    item3.menuOptionsParam.id = OH_DEFAULT_PASTE;
    menuItemList.push_back(item3);

    NG::MenuItemParam item4;
    item4.menuOptionsParam.id = OH_DEFAULT_SELECT_ALL;
    menuItemList.push_back(item4);

    auto result = overlay.FilterSupportedMenuItems(menuItemList);
    EXPECT_EQ(result.size(), 4);
}

/**
 * @tc.name: BuildMenuOptions_001
 * @tc.desc: Test BuildMenuOptions with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, BuildMenuOptions_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    std::vector<NG::MenuItemParam> menuItemList;
    auto result = overlay.BuildMenuOptions(menuItemList);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: BuildMenuOptions_002
 * @tc.desc: Test BuildMenuOptions without onCreateMenuCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, BuildMenuOptions_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    std::vector<NG::MenuItemParam> menuItemList;
    NG::MenuItemParam item;
    item.menuOptionsParam.id = OH_DEFAULT_CUT;
    menuItemList.push_back(item);

    auto result = overlay.BuildMenuOptions(menuItemList);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: BuildMenuOptions_003
 * @tc.desc: Test BuildMenuOptions with onCreateMenuCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, BuildMenuOptions_003, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    // Set onCreateMenuCallback using public method
    webPattern->UpdateEditMenuOptions(
        [](const std::vector<NG::MenuItemParam>& items) {
            std::vector<MenuOptionsParam> options;
            for (const auto& item : items) {
                MenuOptionsParam option;
                option.id = item.menuOptionsParam.id;
                options.push_back(option);
            }
            return options;
        },
        [](const NG::MenuItemParam&) { return true; },
        [](const std::vector<NG::MenuItemParam>&) { return std::vector<MenuOptionsParam>(); }
    );

    std::vector<NG::MenuItemParam> menuItemList;
    NG::MenuItemParam item;
    item.menuOptionsParam.id = OH_DEFAULT_CUT;
    item.menuOptionsParam.content = "Cut";
    menuItemList.push_back(item);

    auto result = overlay.BuildMenuOptions(menuItemList);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: SetEditMenuOption_001
 * @tc.desc: Test SetEditMenuOption with null pattern.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, SetEditMenuOption_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    SelectOverlayInfo selectInfo;
    overlay.SetEditMenuOption(selectInfo);
    EXPECT_FALSE(selectInfo.menuInfo.hasOnPrepareMenuCallback);
}

/**
 * @tc.name: SetEditMenuOption_002
 * @tc.desc: Test SetEditMenuOption with onPrepareMenuCallback and onMenuItemClick.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, SetEditMenuOption_002, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    // Set callbacks using public method
    webPattern->UpdateEditMenuOptions(
        [](const std::vector<NG::MenuItemParam>&) { return std::vector<MenuOptionsParam>(); },
        [](const NG::MenuItemParam&) { return true; },
        [](const std::vector<NG::MenuItemParam>&) { return std::vector<MenuOptionsParam>(); }
    );

    SelectOverlayInfo selectInfo;
    overlay.SetEditMenuOption(selectInfo);
    EXPECT_TRUE(selectInfo.onCreateCallback.onPrepareMenuCallback != nullptr);
    EXPECT_TRUE(selectInfo.onCreateCallback.onMenuItemClick != nullptr);
    EXPECT_TRUE(selectInfo.menuInfo.hasOnPrepareMenuCallback);
}

/**
 * @tc.name: SetEditMenuOption_003
 * @tc.desc: Test SetEditMenuOption without callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, SetEditMenuOption_003, TestSize.Level1)
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
    WeakPtr<TextBase> textBase = Referenced::WeakClaim(Referenced::RawPtr(webPattern));
    WebContextMenuOverlay overlay(textBase);

    SelectOverlayInfo selectInfo;
    overlay.SetEditMenuOption(selectInfo);
    EXPECT_TRUE(selectInfo.onCreateCallback.onCreateMenuCallback != nullptr);
    EXPECT_FALSE(selectInfo.menuInfo.hasOnPrepareMenuCallback);
}

/**
 * @tc.name: OnHandleGlobalEvent_001
 * @tc.desc: Test OnHandleGlobalEvent with TOUCH source and DOWN type.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnHandleGlobalEvent_001, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    TouchEvent event;
    event.sourceType = SourceType::TOUCH;
    event.type = TouchType::DOWN;

    PointF touchPoint(10.0f, 10.0f);
    PointF localPoint(5.0f, 5.0f);
    overlay.OnHandleGlobalEvent(touchPoint, localPoint, event);
    EXPECT_FALSE(overlay.IsCurrentMenuVisibile());
}

/**
 * @tc.name: OnHandleGlobalEvent_002
 * @tc.desc: Test OnHandleGlobalEvent with TOUCH_PAD source and DOWN type.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnHandleGlobalEvent_002, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    TouchEvent event;
    event.sourceType = SourceType::TOUCH_PAD;
    event.type = TouchType::DOWN;

    PointF touchPoint(10.0f, 10.0f);
    PointF localPoint(5.0f, 5.0f);
    overlay.OnHandleGlobalEvent(touchPoint, localPoint, event);
    EXPECT_FALSE(overlay.IsCurrentMenuVisibile());
}

/**
 * @tc.name: OnHandleGlobalEvent_003
 * @tc.desc: Test OnHandleGlobalEvent with non-matching source and type.
 * @tc.type: FUNC
 */
HWTEST_F(WebContextMenuOverlayTest, OnHandleGlobalEvent_003, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    WebContextMenuOverlay overlay(textBase);

    TouchEvent event;
    event.sourceType = SourceType::MOUSE;
    event.type = TouchType::MOVE;

    PointF touchPoint(10.0f, 10.0f);
    PointF localPoint(5.0f, 5.0f);
    overlay.OnHandleGlobalEvent(touchPoint, localPoint, event);
    EXPECT_FALSE(overlay.IsCurrentMenuVisibile());
}

} // namespace OHOS::Ace::NG
