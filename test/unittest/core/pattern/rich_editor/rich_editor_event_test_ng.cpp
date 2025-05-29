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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_clipboard.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
 
using namespace testing;
using namespace testing::ext;
 
namespace OHOS::Ace::NG {
namespace {
const std::u16string TEST_INSERT_LINE_SPACE = u" ";
} // namespace
 
class RichEditorEventTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<RichEditorPattern> GetRichEditorPattern();
};
 
void RichEditorEventTestNg::SetUp()
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
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}
 
void RichEditorEventTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}
 
void RichEditorEventTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}
 
RefPtr<RichEditorPattern> RichEditorEventTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

 /**
 * @tc.name: AddSpanHoverEvent001
 * @tc.desc: test AddSpanHoverEven
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, AddSpanHoverEvent001, TestSize.Level1)
{
    // 0: Get richEditor Node and richEditor Pattern
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.clear();

    // 1: addImageSpan
    ImageSpanOptions options;
    UserMouseOptions mouseOption;
    UserGestureOptions gestureOption;
    auto gestureFunc = [](GestureEvent& info) -> void {};
    auto hoverFunc = [](bool, HoverInfo& info) -> void {};
    gestureOption.onDoubleClick = gestureFunc;
    mouseOption.onHover = hoverFunc;
    options.userMouseOption = mouseOption;
    options.userGestureOption = gestureOption;
    richEditorPattern->AddImageSpan(options);

    // 2: check doubleClick and hover func.
    EXPECT_EQ(richEditorPattern->spans_.size(), 1);
    auto it = richEditorPattern->spans_.begin();
    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(*it);
    ASSERT_NE(imageSpanItem, nullptr);
    EXPECT_NE(imageSpanItem->options.userMouseOption.onHover, nullptr);
    EXPECT_NE(imageSpanItem->options.userGestureOption.onDoubleClick, nullptr);
}

/**
 * @tc.name: HandleBlurEvent001
 * @tc.desc: test HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleBlurEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto func = []() {};

    richEditorPattern->customKeyboardBuilder_ = func;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::FRAME_DESTROY;
    richEditorPattern->HandleBlurEvent();

    richEditorPattern->customKeyboardBuilder_ = nullptr;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::FRAME_DESTROY;
    richEditorPattern->HandleBlurEvent();

    richEditorPattern->customKeyboardBuilder_ = func;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::WINDOW_BLUR;
    richEditorPattern->HandleBlurEvent();

    richEditorPattern->customKeyboardBuilder_ = nullptr;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->blurReason_ = BlurReason::WINDOW_BLUR;
    richEditorPattern->HandleBlurEvent();
    EXPECT_EQ(richEditorPattern->isEditing_, false);
}

/**
 * @tc.name: HandleBlurEvent002
 * @tc.desc: test HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleBlurEvent002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<Pattern> pattern;
    richEditorPattern->magnifierController_ = nullptr;
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->HandleBlurEvent();
    EXPECT_FALSE(richEditorPattern->isEditing_);
}

/**
 * @tc.name: HandleFocusEvent001
 * @tc.desc: test HandleFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleFocusEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->previewLongPress_ = false;

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = true;
    richEditorPattern->isLongPress_ = true;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = false;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = true;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = false;
    richEditorPattern->HandleFocusEvent();

    EXPECT_EQ(richEditorPattern->textSelector_.SelectNothing(), true);
}

/**
 * @tc.name: HandleUserLongPressEvent001
 * @tc.desc: test HandleUserLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleUserLongPressEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto gestureEventFunc = [](GestureEvent& info) { return true; };
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->onLongPress = std::move(gestureEventFunc);
    richEditorPattern->spans_.push_back(spanItem);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserLongPressEvent(info);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleUserLongPressEvent002
 * @tc.desc: test HandleUserLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleUserLongPressEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserLongPressEvent(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleUserLongPressEvent003
 * @tc.desc: test HandleUserLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleUserLongPressEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info = GestureEvent();
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc));

    bool ret = richEditorPattern->HandleUserLongPressEvent(info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleUserGestureEvent001
 * @tc.desc: test HandleUserGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleUserGestureEvent001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });

    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info;
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    EXPECT_TRUE(richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc)));
}

/**
 * @tc.name: HandleFocusEvent002
 * @tc.desc: test HandleFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleFocusEvent002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isOnlyRequestFocus_ = true;
    richEditorPattern->HandleFocusEvent();
    EXPECT_FALSE(richEditorPattern->isOnlyRequestFocus_);
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, GetThumbnailCallback001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto host = richEditorPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    gestureHub->InitDragDropEvent();
    gestureHub->SetThumbnailCallback(richEditorPattern->GetThumbnailCallback());
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}


/**
 * @tc.name: GetThumbnailCallback002
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, GetThumbnailCallback002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    richEditorPattern->InitDragDropEvent();
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: GetThumbnailCallback003
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, GetThumbnailCallback003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    richEditorPattern->InitDragDropEvent();
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: GetThumbnailCallback004
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, GetThumbnailCallback004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetThumbnailCallback()(Offset(1.0f, 10.0f));
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: GetThumbnailCallback005
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, GetThumbnailCallback005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    auto thumbnailCallback = richEditorPattern->GetThumbnailCallback();
    Offset point(10, 10);
    thumbnailCallback(point);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
}

}