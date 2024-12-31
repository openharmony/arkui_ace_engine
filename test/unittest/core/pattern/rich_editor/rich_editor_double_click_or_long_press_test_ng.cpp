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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorDoubleClickOrLongPressTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    RefPtr<RichEditorPattern> GetRichEditorPattern();
};

RefPtr<RichEditorPattern> RichEditorDoubleClickOrLongPressTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

void RichEditorDoubleClickOrLongPressTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorDoubleClickOrLongPressTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorDoubleClickOrLongPressTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/*
 * @tc.name: HandleDoubleClickOrLongPress001
 * @tc.desc: test Mouse Double Click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleDoubleClickOrLongPress001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    AddSpan(TEST_INSERT_U16VALUE);

    TestParagraphRect paragraphRect = { .start = 0, .end = 1, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 1,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    richEditorPattern->isMousePressed_ = true;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);

    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/**
 * @tc.name: HandleDoubleClickOrLongPress002
 * @tc.desc: test HandleDoubleClickOrLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleDoubleClickOrLongPress002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    GestureEvent info;
    RefPtr<FrameNode> imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 0, AceType::MakeRefPtr<ImagePattern>());
    richEditorPattern->caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    richEditorPattern->isLongPress_ = true;
    richEditorPattern->HandleDoubleClickOrLongPress(info, imageNode);
    /**
     * @tc.steps: step2. add span and select text
     */
    AddSpan("test");
    RectF rect(0, 0, 5, 5);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);
    richEditorPattern->HandleDoubleClickOrLongPress(info, imageNode);

    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: HandleDoubleClickOrLongPress003
 * @tc.desc: test HandleDoubleClickOrLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleDoubleClickOrLongPress003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    GestureEvent info;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->selectOverlay_->hasTransform_ = true;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    PositionWithAffinity defaultPositionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*mockParagraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(defaultPositionWithAffinity));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
}

/**
 * @tc.name: HandleDoubleClickOrLongPress004
 * @tc.desc: test HandleDoubleClickOrLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleDoubleClickOrLongPress004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    richEditorNode_->eventHub_->GetOrCreateFocusHub();
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    GestureEvent info;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->selectOverlay_->hasTransform_ = true;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    PositionWithAffinity defaultPositionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*mockParagraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(defaultPositionWithAffinity));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->isMousePressed_ = true;
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_FALSE(richEditorPattern->isLongPress_);
}

/**
 * @tc.name: HandleDoubleClickOrLongPress005
 * @tc.desc: test HandleDoubleClickOrLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleDoubleClickOrLongPress005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);
    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;

    richEditorPattern->previewTextRecord_.previewContent = "123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->HandleDoubleClickOrLongPress(info);

    richEditorPattern->previewTextRecord_.previewContent = "123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = false;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->HandleDoubleClickOrLongPress(info);

    richEditorPattern->status_ = Status::NONE;
    richEditorPattern->HandleDoubleClickOrLongPress(info);

    AddSpan("test");
    richEditorPattern->textSelector_.Update(3, 4);
    EXPECT_EQ(richEditorPattern->IsSelected(), true);
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_EQ(richEditorPattern->IsSelected(), false);
}

/**
 * @tc.name: HandleDoubleClickOrLongPress002
 * @tc.desc: test HandleDoubleClickOrLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleDoubleClickOrLongPress006, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceTool(SourceTool::FINGER);
    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->selectOverlay_->hasTransform_ = true;
    auto localOffset = info.GetLocalLocation();
    richEditorPattern->HandleDoubleClickOrLongPress(info, richEditorNode_);
    EXPECT_TRUE(localOffset == richEditorPattern->ConvertGlobalToLocalOffset(info.GetGlobalLocation()));
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->HandleDoubleClickOrLongPress(info, richEditorNode_);
    EXPECT_TRUE(richEditorPattern->isEditing_);
}

/**
 * @tc.name: HandleDoubleClickOrLongPress007
 * @tc.desc: test Long press edit status is keep false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleDoubleClickOrLongPress007, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    GestureEvent info;
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_FALSE(richEditorController->IsEditing());

    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Long press to trigger the callback function and keep preview state
     */

    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_FALSE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test RichEditorPattern HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleLongPress001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    richEditorPattern->HandleLongPress(info);
    focusHub->focusType_ = FocusType::DISABLE;
    richEditorPattern->HandleLongPress(info);
    ASSERT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleLongPress002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    FingerInfo fingerInfo1;
    FingerInfo fingerInfo2;
    std::list<FingerInfo> fingerList;
    fingerList.push_back(fingerInfo1);
    fingerList.push_back(fingerInfo2);
    info.SetFingerList(fingerList);
    richEditorPattern->HandleLongPress(info);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetX(), info.GetOffsetX());
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetY(), info.GetOffsetY());
}

/**
 * @tc.name: HandleLongPress003
 * @tc.desc: test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleLongPress003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetOffsetX(0.0);
    info.SetOffsetY(0.0);
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->HandleLongPress(info);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetX(), info.GetOffsetX());
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetY(), info.GetOffsetY());
}

/**
 * @tc.name: HandleLongPress004
 * @tc.desc: test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDoubleClickOrLongPressTestNg, HandleLongPress004, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetOffsetX(0.0);
    info.SetOffsetY(0.0);
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    richEditorPattern->HandleLongPress(info);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetX(), info.GetOffsetX());
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetY(), info.GetOffsetY());
}

} // namespace OHOS::Ace::NG