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
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
int32_t testNumber0 = 0;
int32_t testNumber5 = 5;
}
class RichEditorDeleteTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<RichEditorPattern> GetRichEditorPattern();
    static void TearDownTestSuite();
    static int32_t GetEmojiStringLength(std::string emojiString);
};

void RichEditorDeleteTestNg::SetUp()
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

void RichEditorDeleteTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorDeleteTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * get emoji string length in UTF-16 format
 */
int32_t RichEditorDeleteTestNg::GetEmojiStringLength(std::string emojiString)
{
    std::u16string u16EmojiString = StringUtils::Str8ToStr16(emojiString);
    return static_cast<int32_t>(u16EmojiString.length());
}

RefPtr<RichEditorPattern> RichEditorDeleteTestNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: DeleteValueSetTextSpan
 * @tc.desc: test add delete text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteValueSetTextSpan, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. test add span
     */
    AddSpan(INIT_VALUE_1);
    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);
    auto info = richEditorController->GetSpansInfo(0, 6);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);

    auto it = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    auto spanItem = it->GetSpanItem();
    spanItem->position = 0;
    spanItem->textStyle_ = TextStyle();
    spanItem->textStyle_.value().propFontFamilies_.push_back("test1");
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(0);
    richEditorPattern->DeleteValueSetTextSpan(spanItem, 0, 1, spanResult);

    EXPECT_EQ(spanResult.GetTextStyle().textAlign, int(TextAlign::END));
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[0], "5.00px");
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[1], "10.00px");

    ClearSpan();
}

/**
 * @tc.name: DeleteValueSetImageSpan001
 * @tc.desc: test delete imagespan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteValueSetImageSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize span properties
     */
    ImageSpanOptions options;
    options.image = IMAGE_VALUE;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    ImageSpanAttribute imageStyle;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;

    /**
     * @tc.steps: step3. test delete image span
     */
    richEditorController->AddImageSpan(options);
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(0);
    auto spanItem = richEditorPattern->spans_.front();
    richEditorPattern->DeleteValueSetImageSpan(spanItem, spanResult);
    EXPECT_EQ(spanResult.GetMargin(), marginProp->ToString());
    EXPECT_EQ(spanResult.GetBorderRadius(),
        "{\"topLeft\":\"10.00px\",\"topRight\":\"10.00px\",\"bottomLeft\":\"10.00px\",\"bottomRight\":\"10.00px\"}");

    ClearSpan();
}

/**
 * @tc.name: DeleteValueSetImageSpan002
 * @tc.desc: test DeleteValueSetImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteValueSetImageSpan002, TestSize.Level1)
{
    AddImageSpan();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(richEditorNode_->GetLastChild());
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    imageLayoutProperty->UpdateVerticalAlign(VerticalAlign::CENTER);
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(richEditorNode_->GetChildIndexById(imageNode->GetId()));

    auto spans = richEditorPattern->GetSpanItemChildren();
    ASSERT_FALSE(spans.empty());
    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(spans.back());
    ASSERT_NE(imageSpanItem, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);

    ImageSourceInfo info;
    info.pixmap_ = pixelMap;
    imageLayoutProperty->UpdateImageSourceInfo(info);
    richEditorPattern->DeleteValueSetImageSpan(imageSpanItem, spanResult);
    EXPECT_EQ(spanResult.GetValuePixelMap(), pixelMap);
}

/**
 * @tc.name: DeleteValueSetImageSpan003
 * @tc.desc: test DeleteValueSetImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteValueSetImageSpan003, TestSize.Level1)
{
    AddImageSpan();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto imageNode = AceType::DynamicCast<FrameNode>(richEditorNode_->GetLastChild());
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    imageLayoutProperty->UpdateVerticalAlign(VerticalAlign::CENTER);

    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(richEditorNode_->GetChildIndexById(imageNode->GetId()));

    auto spans = richEditorPattern->GetSpanItemChildren();
    ASSERT_FALSE(spans.empty());
    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(spans.back());
    ASSERT_NE(imageSpanItem, nullptr);
    richEditorPattern->DeleteValueSetImageSpan(imageSpanItem, spanResult);
    EXPECT_EQ(spanResult.GetObjectFit(), ImageFit::FILL);
    EXPECT_EQ(spanResult.GetVerticalAlign(), VerticalAlign::CENTER);
}

/**
 * @tc.name: HandleOnDelete001
 * @tc.desc: test RichEditorPattern HandleOnDelete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, HandleOnDelete001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleOnDelete(true);
    richEditorPattern->HandleOnDelete(false);
}

/**
 * @tc.name: DeleteSelectOperation001
 * @tc.desc: test DeleteSelectOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteSelectOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorPattern::OperationRecord record;
    richEditorPattern->DeleteSelectOperation(&record);

    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);

    EXPECT_TRUE(richEditorPattern->selectOverlay_->SelectOverlayIsOn());
    richEditorPattern->DeleteSelectOperation(nullptr);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->SelectOverlayIsOn());
}

/**
 * @tc.name: DeleteBackward001
 * @tc.desc: test DeleteBackward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteBackward001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->DeleteBackward(0);

    ASSERT_EQ(richEditorPattern->IsPreviewTextInputting(), true);
}

/**
 * @tc.name: DeleteBackward002
 * @tc.desc: test DeleteBackward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteBackward002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. delete image&text
     */
    AddImageSpan();
    std::u16string emoji = u"👨‍👩‍👧‍👦";
    AddSpan(emoji);
    auto contentLength = richEditorPattern->GetTextContentLength();
    richEditorPattern->caretPosition_ = contentLength;
    richEditorPattern->DeleteBackward(contentLength);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);

    /**
     * @tc.steps: step2. delete length is greater than content length
     */
    AddSpan(INIT_VALUE_1);
    AddSpan(emoji);
    contentLength = richEditorPattern->GetTextContentLength();
    richEditorPattern->caretPosition_ = contentLength;
    richEditorPattern->DeleteBackward(contentLength + 1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);

    /**
     * @tc.steps: step3. delete emojis
     */
    std::u16string emojis = u"12345📡👨‍👩‍👧‍👦👁️\n🇨🇳3️⃣👁️‍🗨️";
    AddSpan(emojis);
    contentLength = richEditorPattern->GetTextContentLength();
    richEditorPattern->caretPosition_ = contentLength;
    richEditorPattern->DeleteBackward(contentLength);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: DeleteBackward003
 * @tc.desc: test DeleteBackward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteBackward003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step1. create and add emoji
     */
    std::string caseEmoji = "3️⃣";
    int32_t bytesOfOneEmoji = GetEmojiStringLength(caseEmoji);
    AddSpan(caseEmoji);

    /**
     * @tc.step: step2. DeleteBackward in end of emoji
     */
    richEditorPattern->caretPosition_ = bytesOfOneEmoji;
    richEditorPattern->DeleteBackward(bytesOfOneEmoji);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);

    /**
     * @tc.step: step3. DeleteForward in start of emoji
     */
    AddSpan(caseEmoji);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteForward(bytesOfOneEmoji);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: DeleteForward001
 * @tc.desc: test DeleteForward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteForward001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->DeleteForward(0);
    ASSERT_EQ(richEditorPattern->IsPreviewTextInputting(), true);
}

/**
 * @tc.name: DeleteBackwardOperation001
 * @tc.desc: test DeleteBackwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteBackwardOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->caretPosition_ = 100;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->DeleteBackwardOperation(0);

    ASSERT_EQ(richEditorPattern->spans_.empty(), true);
}

/**
 * @tc.name: DeleteBackwardOperation002
 * @tc.desc: test DeleteBackwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteBackwardOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    richEditorPattern->caretPosition_ = 100;
    richEditorPattern->previewLongPress_ = true;
    richEditorNode_.Reset();
    auto ret = richEditorPattern->DeleteBackwardOperation(0);
    EXPECT_EQ(ret, u"");
}

/**
 * @tc.name: DeleteSpansByRange001
 * @tc.desc: test DeleteSpansByRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteSpansByRange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    SpanPositionInfo startInfo;
    SpanPositionInfo endInfo;
    startInfo.spanIndex_ = -1;

    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);

    richEditorPattern->spans_.clear();
    host->children_.clear();
    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    host->AddChild(textframeNode);
    textframeNode->SetParent(host);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);

    richEditorPattern->DeleteSpansByRange(0, 0, startInfo, endInfo);

    ASSERT_EQ(startInfo.spanIndex_ >= static_cast<int32_t>(host->GetChildren().size()), false);
}

/**
 * @tc.name: DeleteSpansByRange001
 * @tc.desc: test DeleteSpansByRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteSpansByRange002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanPositionInfo startInfo;
    SpanPositionInfo endInfo;
    startInfo.spanIndex_ = -1;
    richEditorPattern->DeleteSpansByRange(0, 0, startInfo, endInfo);
    EXPECT_EQ(richEditorPattern->GetHost()->GetChildren().size(), 0);
}

/**
 * @tc.name: GetDeletedSpan001
 * @tc.desc: test GetDeletedSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, GetDeletedSpan001, TestSize.Level1)
{
    /**
     * @tc.step: step1. get richeditor pattern and add text span.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    int32_t innerPosition = 0;
    RichEditorChangeValue changeValue;

    richEditorPattern->usingMouseRightButton_ = false;
    richEditorPattern->isLongPress_ = false;
    richEditorPattern->dataDetectorAdapter_->hasClickedMenuOption_ = false;
    richEditorPattern->HandleFocusEvent();

    richEditorPattern->GetDeletedSpan(changeValue, innerPosition, -99, RichEditorDeleteDirection::BACKWARD);

    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    richEditorPattern->GetDeletedSpan(changeValue, innerPosition, -99, RichEditorDeleteDirection::BACKWARD);

    EXPECT_EQ(richEditorPattern->textSelector_.SelectNothing(), true);
}

/**
 * @tc.name: DoDeleteActions001
 * @tc.desc: test DoDeleteActions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DoDeleteActions001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto aboutToDeleteFunc = [](const RichEditorDeleteValue&) { return false; };
    eventHub->SetAboutToDelete(std::move(aboutToDeleteFunc));
    RichEditorDeleteValue info;
    richEditorPattern->DoDeleteActions(0, 0, info);

    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->DeleteForward(0);
    richEditorPattern->DoDeleteActions(0, 0, info);
    ASSERT_EQ(richEditorPattern->IsPreviewTextInputting(), true);
}

/**
 * @tc.name: DeleteValueInStyledString001
 * @tc.desc: test RichEditorPattern DeleteValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    richEditorPattern->caretVisible_ = false;
    richEditorPattern->previewLongPress_ = true;

    ASSERT_EQ(!richEditorPattern->BeforeStyledStringChange(0, 10, u""), false);

    richEditorPattern->DeleteValueInStyledString(0, 0, true, false);

    richEditorPattern->DeleteValueInStyledString(0, 0, false, false);

    ASSERT_EQ(!richEditorPattern->textSelector_.SelectNothing(), false);
}

/**
 * @tc.name: ProcessDeleteNodes001
 * @tc.desc: test ProcessDeleteNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, ProcessDeleteNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorAbstractSpanResult a;
    a.SetSpanType(SpanResultType::SYMBOL);
    std::list<RichEditorAbstractSpanResult> list;
    list.emplace_back(a);
    int32_t res = richEditorPattern->ProcessDeleteNodes(list);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: ProcessDeleteNodes002
 * @tc.desc: test ProcessDeleteNodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, ProcessDeleteNodes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = SpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, nodeId);
    auto newAddFrameNode = SpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, nodeId);
    newAddFrameNode->GetSpanItem()->content = INIT_VALUE_3;
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorNode_->children_.push_back(newAddFrameNode);

    auto span = RichEditorAbstractSpanResult();
    span.spanType_ = SpanResultType::TEXT;
    span.offsetInSpan_ = 1;
    auto ui_node = richEditorNode_->GetChildAtIndex(span.GetSpanIndex());
    auto spanNode = AceType::DynamicCast<SpanNode>(ui_node);
    auto spanItem = spanNode->GetSpanItem();
    auto textTemp = spanItem->content;
    std::list<RichEditorAbstractSpanResult> list;
    list.emplace_back(span);
    richEditorPattern->ProcessDeleteNodes(list);
    EXPECT_EQ(spanItem->content, textTemp);
}

/**
 * @tc.name: DeleteContentRichEditor001
 * @tc.desc: test DeleteContentRichEditor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteContentRichEditor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    std::string insertValue = "hello";
    RichEditorPattern::OperationRecord record;
    richEditorPattern->InsertValueOperation(StringUtils::Str8ToStr16(insertValue), &record, OperationType::DEFAULT);
    richEditorPattern->DeleteContent(3);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 2);
}

/**
 * @tc.name: DeleteSpansOperation001
 * @tc.desc: test DeleteSpansOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteSpansOperation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    AddSpan("test");
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->DeleteSpansOperation(0, 0);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: DeleteSpansOperation002
 * @tc.desc: test DeleteSpansOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteSpansOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto newFrameNode = ImageSpanNode::GetOrCreateSpanNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    richEditorNode_->children_.push_back(newFrameNode);
    richEditorPattern->DeleteSpansOperation(0, 5);
    EXPECT_EQ(richEditorPattern->textForDisplay_.size(), 0);
}

/**
 * @tc.name: AIDeleteComb001
 * @tc.desc: test AIDeleteComb
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, AIDeleteComb001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(u"");
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id1]"] = AceType::MakeRefPtr<SpanItem>();
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id1]");
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();
}

/**
 * @tc.name: HandleOnDeleteComb001
 * @tc.desc: test HandleOnDeleteComb
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, HandleOnDeleteComb001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->rangeStart = 2;
    spanItem->position = 10;
    spanItem->unicode = 1;
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->caretPosition_ = 6;
    auto ret = richEditorPattern->HandleOnDeleteComb(true);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: DeleteSpans001
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteSpans001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RangeOptions options;
    options.start = 0;
    options.end = 1;
    richEditorPattern->isSpanStringMode_ = true;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.push_back(spanItem);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_3);
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    eventHub->SetOnWillChange([](const RichEditorChangeValue& value) -> bool { return false; });
    richEditorPattern->redoOperationRecords_.emplace_back();
    richEditorPattern->DeleteSpans(options);
    EXPECT_FALSE(richEditorPattern->redoOperationRecords_.empty());
}

/**
 * @tc.name: DeleteForwardOperation001
 * @tc.desc: test DeleteForwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteForwardOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t length = 1;
    AddSpan(EXCEPT_VALUE);
    richEditorNode_.Reset();
    auto ret = richEditorPattern->DeleteForwardOperation(length);
    EXPECT_EQ(ret, u"");
}

/**
 * @tc.name: DeleteForwardOperation002
 * @tc.desc: test DeleteForwardOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteForwardOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t length = 1;
    ClearSpan();
    richEditorPattern->caretPosition_ = 100;
    richEditorPattern->DeleteForwardOperation(length);
    EXPECT_TRUE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: DeleteRange001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteRange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 8;
    int32_t end = 7;
    richEditorPattern->DeleteRange(start, end);
    EXPECT_NE(start, richEditorPattern->caretPosition_);
}

/**
 * @tc.name: DeleteRange002
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteRange002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = -2;
    int32_t end = -1;
    richEditorPattern->DeleteRange(start, end);
    EXPECT_NE(start, richEditorPattern->caretPosition_);
}

/**
 * @tc.name: DeleteRange003
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteRange003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 1;
    int32_t end = 1;
    richEditorPattern->DeleteRange(start, end);
    EXPECT_NE(start, richEditorPattern->caretPosition_);
}

/**
 * @tc.name: DeleteRange004
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteRange004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 0;
    int32_t end = 2;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_->text_ = u"test";
    auto styleString = richEditorPattern->styledString_;
    richEditorPattern->previewLongPress_ = true;

    auto focusHub = richEditorPattern->GetFocusHub();
    focusHub->currentFocus_ = true;

    richEditorPattern->DeleteRange(start, end);
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: DeleteRange005
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteRange005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    int32_t start = 0;
    int32_t end = 2;
    richEditorPattern->DeleteRange(start, end);
    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: CalcDeleteValueObj001
 * @tc.desc: test CalcDeleteValueObj delete builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, CalcDeleteValueObj001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto spans = richEditorPattern->GetSpanItemChildren();
    ASSERT_FALSE(spans.empty());
    auto spanItem = spans.back();
    ASSERT_NE(spanItem, nullptr);
    int32_t currentPosition = INIT_VALUE_1.size() - 2;
    spanItem->placeholderIndex = currentPosition;

    RichEditorDeleteValue info;
    int32_t length = 2;
    richEditorPattern->CalcDeleteValueObj(currentPosition, length, info);
    EXPECT_EQ(info.GetRichEditorDeleteSpans().size(), 1);
}

/**
 * @tc.name: InsertOrDeleteSpace001
 * @tc.desc: test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, InsertOrDeleteSpace001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    size_t index = -1;
    bool tag = richEditorPattern->InsertOrDeleteSpace(index);
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: InsertOrDeleteSpace002
 * @tc.desc: test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, InsertOrDeleteSpace002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    size_t index = 0;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"test";
    spanItem->rangeStart = 0;
    spanItem->position = 4;
    richEditorPattern->spans_.push_back(spanItem);
    bool tag = richEditorPattern->InsertOrDeleteSpace(index);
    EXPECT_TRUE(tag);
}

/**
 * @tc.name: InsertOrDeleteSpace003
 * @tc.desc: test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, InsertOrDeleteSpace003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    size_t index = 0;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u" test";
    spanItem->rangeStart = 0;
    spanItem->position = 5;
    richEditorPattern->spans_.push_back(spanItem);
    bool tag = richEditorPattern->InsertOrDeleteSpace(index);
    EXPECT_TRUE(tag);
}

/**
 * @tc.name: DeleteValueSetSymbolSpan001
 * @tc.desc: test DeleteValueSetSymbolSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDeleteTestNg, DeleteValueSetSymbolSpan001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    EXPECT_NE(spanItem, nullptr);
    RichEditorAbstractSpanResult spanResult;
    auto result = richEditorPattern->DeleteValueSetSymbolSpan(spanItem, spanResult);
    EXPECT_TRUE(result == SYMBOL_SPAN_LENGTH);
}

}