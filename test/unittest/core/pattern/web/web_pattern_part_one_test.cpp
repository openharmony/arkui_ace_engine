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

#include <gmock/gmock.h>

#include "gtest/gtest.h"
#define private public
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class MockWebContextMenuParam : public WebContextMenuParam {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (const, override));
    MOCK_METHOD(int32_t, GetYCoord, (), (const, override));
    MOCK_METHOD(std::string, GetLinkUrl, (), (const, override));
    MOCK_METHOD(std::string, GetUnfilteredLinkUrl, (), (const, override));
    MOCK_METHOD(std::string, GetSourceUrl, (), (const, override));
    MOCK_METHOD(bool, HasImageContents, (), (const, override));
    MOCK_METHOD(bool, IsEditable, (), (const, override));
    MOCK_METHOD(int, GetEditStateFlags, (), (const, override));
    MOCK_METHOD(int, GetSourceType, (), (const, override));
    MOCK_METHOD(int, GetMediaType, (), (const, override));
    MOCK_METHOD(int, GetInputFieldType, (), (const, override));
    MOCK_METHOD(std::string, GetSelectionText, (), (const, override));
    MOCK_METHOD(bool, IsAILink, (), (const, override));
};

class MockWebContextSelectOverlay : public WebContextSelectOverlay {
public:
    MockWebContextSelectOverlay(WeakPtr<TextBase> textBase) : WebContextSelectOverlay(textBase) {}
    ~MockWebContextSelectOverlay() override = default;
    bool IsCurrentMenuVisibile()
    {
        return true;
    }
};

class MockWebContextSelectOverlayfalse : public WebContextSelectOverlay {
public:
    MockWebContextSelectOverlayfalse(WeakPtr<TextBase> textBase) : WebContextSelectOverlay(textBase) {}
    ~MockWebContextSelectOverlayfalse() override = default;
    bool IsCurrentMenuVisibile()
    {
        return false;
    }
};

class MockContextMenuResult : public ContextMenuResult {
public:
    MOCK_METHOD(void, Cancel, (), (const, override));
    MOCK_METHOD(void, CopyImage, (), (const, override));
    MOCK_METHOD(void, Copy, (), (const, override));
    MOCK_METHOD(void, Paste, (), (const, override));
    MOCK_METHOD(void, Cut, (), (const, override));
    MOCK_METHOD(void, SelectAll, (), (const, override));
    MOCK_METHOD(void, Undo, (), (const, override));
    MOCK_METHOD(void, Redo, (), (const, override));
    MOCK_METHOD(void, PasteAndMatchStyle, (), (const, override));
};

class WebPatternPartOneTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternPartOneTest::SetUpTestCase() {}
void WebPatternPartOneTest::TearDownTestCase() {}
void WebPatternPartOneTest::SetUp() {}
void WebPatternPartOneTest::TearDown() {}

/**
 * @tc.name: ShowContextSelectOverlay_001
 * @tc.desc: ShowContextSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, ShowContextSelectOverlay_001, TestSize.Level1)
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
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<WebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    auto responseType = TextResponseType::RIGHT_CLICK;

    webPattern->ShowContextSelectOverlay(RectF(), RectF(), responseType, true);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: ShowContextSelectOverlay_002
 * @tc.desc: ShowContextSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, ShowContextSelectOverlay_002, TestSize.Level1)
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
    auto responseType = TextResponseType::RIGHT_CLICK;

    webPattern->ShowContextSelectOverlay(RectF(), RectF(), responseType, true);

    EXPECT_EQ(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: CloseContextSelectionMenu_001
 * @tc.desc: CloseContextSelectionMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CloseContextSelectionMenu_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;

    webPattern->CloseContextSelectionMenu();
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: CloseContextSelectionMenu_002
 * @tc.desc: CloseContextSelectionMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CloseContextSelectionMenu_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlayfalse>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;

    webPattern->CloseContextSelectionMenu();
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: CloseContextSelectionMenu_003
 * @tc.desc: CloseContextSelectionMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CloseContextSelectionMenu_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->contextSelectOverlay_ = nullptr;

    webPattern->CloseContextSelectionMenu();
    EXPECT_EQ(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_001
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnContextMenuShow_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<BaseEventInfo> emptyInfo = nullptr;
    webPattern->contextSelectOverlay_ = nullptr;

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_EQ(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_002
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnContextMenuShow_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    webPattern->contextMenuParam_ = nullptr;
    RefPtr<WebContextMenuParam> param_ = nullptr;
    RefPtr<ContextMenuResult> result_;
    auto emptyInfo = std::make_shared<ContextMenuEvent>(param_, result_);

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
    EXPECT_EQ(webPattern->contextMenuParam_, nullptr);
    EXPECT_EQ(webPattern->contextMenuResult_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_003
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnContextMenuShow_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    webPattern->contextMenuParam_ = nullptr;
    auto param_ = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> result_ = nullptr;
    auto emptyInfo = std::make_shared<ContextMenuEvent>(param_, result_);

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
    EXPECT_NE(webPattern->contextMenuParam_, nullptr);
    EXPECT_EQ(webPattern->contextMenuResult_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_004
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnContextMenuShow_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    webPattern->contextMenuParam_ = nullptr;
    auto param_ = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto result_ = AceType::MakeRefPtr<MockContextMenuResult>();
    auto emptyInfo = std::make_shared<ContextMenuEvent>(param_, result_);

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
    EXPECT_NE(webPattern->contextMenuParam_, nullptr);
    EXPECT_NE(webPattern->contextMenuResult_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_005
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnContextMenuShow_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    webPattern->contextMenuParam_ = nullptr;
    auto param_ = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto result_ = AceType::MakeRefPtr<MockContextMenuResult>();
    auto emptyInfo = std::make_shared<ContextMenuEvent>(param_, result_);

    auto adapter = webPattern->GetDataDetectorAdapter();
    adapter->config_.enable = true;
    adapter->config_.enablePreview = true;
    EXPECT_CALL(*param_, IsAILink()).WillRepeatedly(Return(true));
    EXPECT_CALL(*param_, GetLinkUrl()).WillRepeatedly(Return("www.example.com"));

    webPattern->isNewDragStyle_ = true;
    webPattern->OnContextMenuShow(emptyInfo, false, true);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
    EXPECT_NE(webPattern->contextMenuParam_, nullptr);
    EXPECT_NE(webPattern->contextMenuResult_, nullptr);
    // cannot cover all because of the fake mock delegate
#endif
}

/**
 * @tc.name: ShowPreviewMenu_001
 * @tc.desc: ShowPreviewMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, ShowPreviewMenu_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->contextMenuParam_ = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto adapter = webPattern->GetDataDetectorAdapter();
    adapter->InitAIMenu();
    adapter->config_.enable = true;
    adapter->config_.enablePreview = true;

    auto param_ = AceType::MakeRefPtr<MockWebContextMenuParam>();
    webPattern->contextMenuParam_ = param_;
    EXPECT_CALL(*param_, GetSourceType())
        .WillOnce(Return(OHOS::NWeb::NWebContextMenuParams::ContextMenuSourceType::CM_ST_MOUSE))
        .WillOnce(Return(OHOS::NWeb::NWebContextMenuParams::ContextMenuSourceType::CM_ST_LONG_PRESS))
        .WillRepeatedly(Return(OHOS::NWeb::NWebContextMenuParams::ContextMenuSourceType::CM_ST_NONE));

    webPattern->ShowPreviewMenu(WebElementType::AILINK);
    webPattern->ShowPreviewMenu(WebElementType::AILINK);
    webPattern->ShowPreviewMenu(WebElementType::AILINK);
#endif
}

/**
 * @tc.name: OnContextMenuHide_001
 * @tc.desc: OnContextMenuHide.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnContextMenuHide_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->OnContextMenuHide();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: NeedSoftKeyboard_001
 * @tc.desc: NeedSoftKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, NeedSoftKeyboard_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    auto ret = webPattern->NeedSoftKeyboard();
    EXPECT_NE(ret, false);
#endif
}

/**
 * @tc.name: NeedSoftKeyboard_002
 * @tc.desc: NeedSoftKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, NeedSoftKeyboard_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;

    auto ret = webPattern->NeedSoftKeyboard();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: OnAttachToMainTree_001
 * @tc.desc: OnAttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnAttachToMainTree_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->OnAttachToMainTree();
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnDetachFromMainTree_001
 * @tc.desc: OnDetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnDetachFromMainTree_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    webPattern->OnDetachFromMainTree();
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnAttachToFrameNode_001
 * @tc.desc: OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnAttachToFrameNode_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto renderContextForSurface_ = RenderContext::Create();
    auto renderContextForPopupSurface_ = RenderContext::Create();
    webPattern->renderContextForSurface_ = renderContextForSurface_;
    webPattern->renderContextForPopupSurface_ = renderContextForPopupSurface_;

    webPattern->OnAttachToFrameNode();
    EXPECT_NE(webPattern->renderContextForSurface_, nullptr);
    EXPECT_NE(webPattern->renderContextForPopupSurface_, nullptr);
#endif
}

/**
 * @tc.name: OnDetachFromFrameNode_001
 * @tc.desc: OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnDetachFromFrameNode_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;

    auto pattern = AceType::MakeRefPtr<Pattern>();
    FrameNode node("exampleTag", 1, pattern, true, false);
    webPattern->OnDetachFromFrameNode(&node);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnDetachFromFrameNode_002
 * @tc.desc: OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnDetachFromFrameNode_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    auto pattern = AceType::MakeRefPtr<Pattern>();
    FrameNode node("exampleTag", 1, pattern, true, false);
    webPattern->OnDetachFromFrameNode(&node);
    EXPECT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_001
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, SetRotation_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = rotation;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_002
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, SetRotation_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = 0;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_003
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, SetRotation_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = rotation;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_004
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, SetRotation_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = 0;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_005
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, SetRotation_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = 0;
    webPattern->renderSurface_ = nullptr;

    webPattern->SetRotation(rotation);
    EXPECT_EQ(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: InitEvent_001
 * @tc.desc: InitEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, InitEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->InitEvent();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitFeatureParam_001
 * @tc.desc: InitFeatureParam.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, InitFeatureParam_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->InitFeatureParam();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_001
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, HandleFlingMove_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::TOUCH_SCREEN);
    event.SetSourceTool(SourceTool::FINGER);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_002
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, HandleFlingMove_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::AXIS);
    event.SetSourceTool(SourceTool::FINGER);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_003
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, HandleFlingMove_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::TOUCH_SCREEN);
    event.SetSourceTool(SourceTool::TOUCHPAD);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_004
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, HandleFlingMove_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    GestureEvent event;
    event.SetInputEventType(InputEventType::AXIS);
    event.SetSourceTool(SourceTool::TOUCHPAD);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_005
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, HandleFlingMove_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::AXIS);
    event.SetSourceTool(SourceTool::TOUCHPAD);
    std::vector<KeyCode> keyCodes;
    keyCodes.push_back(KeyCode::KEY_FN);
    event.SetPressedKeyCodes(keyCodes);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitPinchEvent_001
 * @tc.desc: InitPinchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, InitPinchEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    RefPtr<PinchGesture> pinchGesture_ = AceType::MakeRefPtr<PinchGesture>(1, 1.1);
    webPattern->pinchGesture_ = pinchGesture_;
    EXPECT_NE(webPattern->pinchGesture_, nullptr);

    webPattern->InitPinchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitPinchEvent_002
 * @tc.desc: InitPinchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, InitPinchEvent_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    webPattern->pinchGesture_ = nullptr;
    EXPECT_EQ(webPattern->pinchGesture_, nullptr);

    webPattern->InitPinchEvent(gestureHub);
    EXPECT_NE(webPattern->pinchGesture_, nullptr);
#endif
}

/**
 * @tc.name: CheckZoomStatus_001
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 3;
    double scale = 1.0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_002
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, false);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_003
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_004
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_005
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, false);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_006
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_007
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_008
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_009
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, CheckZoomStatus_009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
    webPattern->zoomErrorCount_ = 0;
#endif
}

/**
 * @tc.name: SetUpdateInstanceIdCallback_001
 * @tc.desc: Test SetUpdateInstanceIdCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, SetUpdateInstanceIdCallback_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    int32_t instanceId = -1;
    auto callback = [&instanceId](int32_t id) { instanceId = id; };
    webPattern->SetUpdateInstanceIdCallback(std::move(callback));
    MockPipelineContext::TearDown();
    ASSERT_NE(webPattern->updateInstanceIdCallback_, nullptr);
    webPattern->updateInstanceIdCallback_(123);
    EXPECT_EQ(instanceId, 123);
#endif
}

/**
 * @tc.name: OnScrollBarColorUpdate_001
 * @tc.desc: Test OnScrollBarColorUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnScrollBarColorUpdate_001, TestSize.Level1)
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
    webPattern->needOnFocus_ = true;
    webPattern->OnScrollBarColorUpdate("red");
#endif
}

/**
 * @tc.name: OnScrollBarColorUpdate_002
 * @tc.desc: Test OnScrollBarColorUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnScrollBarColorUpdate_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    ASSERT_EQ(webPattern->delegate_, nullptr);
    webPattern->needOnFocus_ = true;
    webPattern->OnScrollBarColorUpdate("red");
#endif
}

/**
 * @tc.name: OnDefaultTextEncodingFormatUpdate_001
 * @tc.desc: Test OnDefaultTextEncodingFormatUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnDefaultTextEncodingFormatUpdate_001, TestSize.Level1)
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
    webPattern->UpdateDefaultTextEncodingFormat("UTF-8");
#endif
}

/**
 * @tc.name: OnNativeVideoPlayerConfigUpdate_001
 * @tc.desc: Test OnNativeVideoPlayerConfigUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnNativeVideoPlayerConfigUpdate_001, TestSize.Level1)
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
    // const std::tuple<bool, bool>& config
    std::tuple<bool, bool> config = std::make_tuple(true, false);
    webPattern->OnNativeVideoPlayerConfigUpdate(config);
#endif
}

/**
 * @tc.name: RegistVirtualKeyBoardListener_001
 * @tc.desc: Test RegistVirtualKeyBoardListener function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, RegistVirtualKeyBoardListener_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->RegistVirtualKeyBoardListener(pipelineContext);
    MockPipelineContext::TearDown();
    ASSERT_EQ(webPattern->needUpdateWeb_, false);
#endif
}

/**
 * @tc.name: InitEnhanceSurfaceFlag_001
 * @tc.desc: Test InitEnhanceSurfaceFlag function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, InitEnhanceSurfaceFlag_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    SystemProperties::SetExtSurfaceEnabled(true);
    webpattern.InitEnhanceSurfaceFlag();
    ASSERT_EQ(webpattern.isEnhanceSurface_, true);
#endif
}

/**
 * @tc.name: InitEnhanceSurfaceFlag_002
 * @tc.desc: Test InitEnhanceSurfaceFlag function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, InitEnhanceSurfaceFlag_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    SystemProperties::SetExtSurfaceEnabled(false);
    webpattern.InitEnhanceSurfaceFlag();
    ASSERT_EQ(webpattern.isEnhanceSurface_, false);
#endif
}

/**
 * @tc.name: OnModifyDone_001
 * @tc.desc: Test OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnModifyDone_001, TestSize.Level1)
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
    webPattern->OnModifyDone();
#endif
}

/**
 * @tc.name: OnModifyDone_002
 * @tc.desc: Test OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, OnModifyDone_002, TestSize.Level1)
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
#endif
}

/**
 * @tc.name: InitInOfflineMode_001
 * @tc.desc: Test InitInOfflineMode function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, InitInOfflineMode_001, TestSize.Level1)
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
    webPattern->InitInOfflineMode();
    ASSERT_EQ(webPattern->offlineWebInited_, true);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_001
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, IsNeedResizeVisibleViewport_001, TestSize.Level1)
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
    webPattern->IsNeedResizeVisibleViewport();
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_002
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, IsNeedResizeVisibleViewport_002, TestSize.Level1)
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
    webPattern->visibleViewportSize_.SetHeight(-1.0);
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_003
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, IsNeedResizeVisibleViewport_003, TestSize.Level1)
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
    webPattern->visibleViewportSize_.SetWidth(-1.0);
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_004
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, IsNeedResizeVisibleViewport_004, TestSize.Level1)
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
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_NONE;
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_005
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, IsNeedResizeVisibleViewport_005, TestSize.Level1)
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
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_NONE;
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoardHide_001
 * @tc.desc: Test ProcessVirtualKeyBoardHide function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, ProcessVirtualKeyBoardHide_001, TestSize.Level1)
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
    webPattern->ProcessVirtualKeyBoardHide(1000, 2000, true);
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoardShow_001
 * @tc.desc: Test ProcessVirtualKeyBoardShow function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, ProcessVirtualKeyBoardShow_001, TestSize.Level1)
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
    webPattern->ProcessVirtualKeyBoardShow(1000, 2000, 500.0, false);
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoard_001
 * @tc.desc: Test ProcessVirtualKeyBoard function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, ProcessVirtualKeyBoard_001, TestSize.Level1)
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
    webPattern->ProcessVirtualKeyBoard(1000, 2000, 500.0);
#endif
}

/**
 * @tc.name: UpdateWebLayoutSize_001
 * @tc.desc: Test UpdateWebLayoutSize function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternPartOneTest, UpdateWebLayoutSize_001, TestSize.Level1)
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
    webPattern->UpdateWebLayoutSize(1000, 2000, true, true);
#endif
}
} // namespace OHOS::Ace::NG
