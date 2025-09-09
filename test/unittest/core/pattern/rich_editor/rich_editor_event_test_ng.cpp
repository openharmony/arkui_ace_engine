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
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
 
using namespace testing;
using namespace testing::ext;
 
namespace OHOS::Ace::NG {
namespace {
bool g_isOnEditChangeCalled = false;
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
 * @tc.name: RichEditorEventTestNg
 * @tc.desc: test HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, HandleBlurEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. add span and select
     */
    AddSpan(u"test");
    richEditorPattern->textSelector_.Update(1, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 3);

    /**
     * @tc.step: step3. Request focus and set blurReason_
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    focusHub->blurReason_ = BlurReason::FRAME_DESTROY;

    /**
     * @tc.step: step4. call the callback function
     */
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->HandleBlurEvent();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
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
 * @tc.name: SetGestureOptions001
 * @tc.desc: test SetGestureOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, SetGestureOptions001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    OHOS::Ace::UserGestureOptions userGestureOptions;
    userGestureOptions.onLongPress = [](GestureEvent& info) {};
    auto spanItem = AceType::MakeRefPtr<SpanItem>();

    richEditorPattern->SetGestureOptions(userGestureOptions, spanItem);

    EXPECT_NE(userGestureOptions.onLongPress, nullptr);
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

/**
 * @tc.name: ExpandDefaultResponseRegion001
 * @tc.desc: test ExpandDefaultResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, ExpandDefaultResponseRegion001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RectF rect(0, 0, 5, 5);
    RectF retRect;
    retRect = richEditorPattern->ExpandDefaultResponseRegion(rect);
    EXPECT_EQ(rect.Width(), retRect.Width());
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus001
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, IsResponseRegionExpandingNeededForStylus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::UNKNOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus002
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, IsResponseRegionExpandingNeededForStylus002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.type = TouchType::UNKNOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus003
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, IsResponseRegionExpandingNeededForStylus003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::DOWN;
    bool ret = false;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus004
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, IsResponseRegionExpandingNeededForStylus004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::UNKNOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus005
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, IsResponseRegionExpandingNeededForStylus005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::DOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus006
 * @tc.desc: test testInput text IsResponseRegionExpandingNeededForStylus001
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, IsResponseRegionExpandingNeededForStylus006, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.sourceTool = SourceTool::PEN;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_TRUE(ret);
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.type = TouchType::MOVE;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::MOVE;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.type = TouchType::DOWN;
    touchEvent.sourceTool = SourceTool::PEN;
    EXPECT_TRUE(richEditorNode_->IsVisible());
    richEditorNode_->layoutProperty_->OnVisibilityUpdate(VisibleType::INVISIBLE);
    EXPECT_FALSE(richEditorNode_->IsVisible());
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: RichEditorEventHub001
 * @tc.desc: test get insert
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, RichEditorEventHub001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set insert value
     */
    RichEditorInsertValue insertValueInfo;
    insertValueInfo.SetInsertOffset(1);
    insertValueInfo.SetInsertValue(INIT_VALUE_1);
    /**
     * @tc.steps: step2. get insert value
     */
    EXPECT_EQ(insertValueInfo.GetInsertOffset(), 1);
    EXPECT_EQ(insertValueInfo.GetInsertValue(), INIT_VALUE_1);
}

/**
 * @tc.name: RichEditorEventHub002
 * @tc.desc: test span result
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, RichEditorEventHub002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set span result
     */
    RichEditorAbstractSpanResult result;
    FONT_FEATURES_LIST fontFeature;
    RefPtr<ResourceObject> valueResource;
    SymbolSpanStyle symbolSpanStyle;

    result.SetSpanRangeEnd(1);
    result.SetFontFeature(fontFeature);
    result.SetLineHeight(20.0);
    result.SetLetterspacing(20.0);
    result.SetValueResource(valueResource);
    result.SetValueString(TEST_STR);
    result.SetSymbolSpanStyle(symbolSpanStyle);
    result.SetTextDecoration(TextDecoration::UNDERLINE);
    result.SetColor("");

    /**
     * @tc.steps: step2. get span result
     */
    EXPECT_EQ(result.GetSpanRangeEnd(), 1);
    EXPECT_EQ(result.GetFontFeatures(), fontFeature);
    EXPECT_EQ(result.GetLineHeight(), 20.0);
    EXPECT_EQ(result.GetLetterspacing(), 20.0);
    EXPECT_EQ(result.GetFontColor(), "");
    EXPECT_EQ(result.GetFontSize(), 0);
    EXPECT_EQ(result.GetValueResource(), valueResource);
    EXPECT_EQ(result.GetValueString(), TEST_STR);
    EXPECT_EQ(result.GetSymbolSpanStyle().lineHeight, 0.0);
    EXPECT_EQ(result.GetFontWeight(), 0);
    EXPECT_EQ(result.GetFontFamily(), "");
    EXPECT_EQ(result.GetTextDecoration(), TextDecoration::UNDERLINE);
    EXPECT_EQ(result.GetColor(), "");
}

/**
 * @tc.name: RichEditorEventHub003
 * @tc.desc: test edit change event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, RichEditorEventHub003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set OnEditingChange func
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](bool value) {
        g_isOnEditChangeCalled = value;
    };
    richEditorModel.SetOnEditingChange(std::move(func));

    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. fire OnEditingChange func
     * @tc.expected: expect g_isOnEditChangeCalled is true
     */
    eventHub->FireOnEditingChange(true);
    EXPECT_EQ(g_isOnEditChangeCalled, true);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorEventHub004
 * @tc.desc: test GetDragExtraParams
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, RichEditorEventHub004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch !extraInfo.empty()
     * @tc.expected: expect return jsonStr is {"extraInfo":"info"}
     */
    auto jsonStr = eventHub->GetDragExtraParams("info", Point(0, 250.f), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"extraInfo\":\"info\"}");

    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch type == DragEventType::DROP
     * @tc.expected: expect return jsonStr is {"extraInfo":"info"}
     */
    jsonStr = eventHub->GetDragExtraParams("info", Point(0, 250.f), DragEventType::DROP);
    EXPECT_EQ(jsonStr, "{\"extraInfo\":\"info\"}");

    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch timestamp_ != 0
     * @tc.expected: expect return jsonStr is {}
     */
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    eventHub->timestamp_ = timestamp;
    jsonStr = eventHub->GetDragExtraParams("", Point(0, 250.f), DragEventType::DROP);
    EXPECT_EQ(jsonStr, "{}");

    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch pattern->GetTimestamp() == timestamp_
     * @tc.expected: expect return jsonStr is {"isInComponent":true}
     */
    richEditorPattern->timestamp_ = timestamp;
    jsonStr = eventHub->GetDragExtraParams("", Point(0, 250.f), DragEventType::DROP);
    EXPECT_EQ(jsonStr, "{\"isInComponent\":true}");
    EXPECT_EQ(eventHub->timestamp_, 0);
}

/**
 * @tc.name: RichEditorEventHub005
 * @tc.desc: test fire event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, RichEditorEventHub005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init eventHub
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. fire event when there is null func
     */
    RichEditorChangeValue value;
    StyledStringChangeValue info;
    TextCommonEvent event;
    eventHub->FireOnDidChange(value);
    eventHub->FireOnCut(event);
    eventHub->FireOnCopy(event);
    EXPECT_TRUE(eventHub->FireOnWillChange(value));
    EXPECT_TRUE(eventHub->FireOnStyledStringWillChange(info));

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: PreventDefault001
 * @tc.desc: test PreventDefault001 in ImageSpan and TextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEventTestNg, PreventDefault001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    // add imageSpan
    ClearSpan();
    ImageSpanOptions imageSpanOptions;
    GestureEventFunc callback2 = [](GestureEvent& info) {
        info.SetPreventDefault(true);
    };
    imageSpanOptions.userGestureOption.onClick = callback2;
    richEditorController->AddImageSpan(imageSpanOptions);

    /**
     * @tc.steps: step1. Click on imagespan
     */
    GestureEvent info2;
    info2.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info2);
    EXPECT_FALSE(richEditorPattern->HasFocus());
}

}