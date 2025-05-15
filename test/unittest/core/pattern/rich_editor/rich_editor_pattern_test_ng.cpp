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
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
int32_t testSpanNodeId = 1;
int32_t testFrameNodeId = 1;
int32_t testNumber0 = 0;
int32_t testNumber2 = 2;
int32_t testNumber4 = 4;
int32_t testNumber5 = 5;
} // namespace

class RichEditorPatternTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestNg::SetUp()
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

void RichEditorPatternTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorPatternTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorPatternTestRequestKeyboard001
 * @tc.desc: test RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestRequestKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto func = [] {};

    auto customKeyboardBuilder = richEditorPattern->customKeyboardBuilder_;
    richEditorPattern->customKeyboardBuilder_ = func;
    ASSERT_EQ(richEditorPattern->RequestKeyboard(true, true, true), true);
    richEditorPattern->customKeyboardBuilder_ = customKeyboardBuilder;
}

/**
 * @tc.name: RichEditorPatternTestCloseCustomKeyboard001
 * @tc.desc: test CloseCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestCloseCustomKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CloseCustomKeyboard();

    auto func = []() {};
    auto oldFunc = richEditorPattern->customKeyboardBuilder_;

    richEditorPattern->customKeyboardBuilder_ = func;

    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, false);
    EXPECT_EQ(richEditorPattern->RequestCustomKeyboard(), true);
    EXPECT_EQ(richEditorPattern->RequestCustomKeyboard(), true);
    EXPECT_EQ(richEditorPattern->isCustomKeyboardAttached_, true);
    EXPECT_NE(richEditorPattern->keyboardOverlay_, nullptr);
    ASSERT_EQ(richEditorPattern->CloseCustomKeyboard(), true);

    richEditorPattern->customKeyboardBuilder_ = oldFunc;
}

/**
 * @tc.name: RichEditorPatternTestInsertDiffStyleValueInSpan001
 * @tc.desc: test InsertDiffStyleValueInSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestInsertDiffStyleValueInSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanNode = AceType::MakeRefPtr<SpanNode>(testSpanNodeId);
    ASSERT_NE(spanNode, nullptr);

    TextInsertValueInfo info;
    std::u16string insertValue;
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);

    richEditorPattern->InsertDiffStyleValueInSpan(spanNode, info, insertValue, false);
    ASSERT_EQ(richEditorPattern->moveLength_, 0);
}

/**
 * @tc.name: RichEditorPatternTestCreateTextSpanNode001
 * @tc.desc: test CreateTextSpanNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestCreateTextSpanNode001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanNode> spanNode;

    TextInsertValueInfo info;
    std::u16string insertValue;
    UpdateSpanStyle updateSpanStyle;
    TextStyle textStyle;

    updateSpanStyle.useThemeFontColor = false;

    auto typingStyle = richEditorPattern->typingStyle_;
    auto typingTextStyle = richEditorPattern->typingTextStyle_;

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = textStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->CreateTextSpanNode(spanNode, info, insertValue, false);
    EXPECT_EQ(spanNode->GetSpanItem()->useThemeDecorationColor, true);

    richEditorPattern->typingStyle_ = typingStyle;
    richEditorPattern->typingTextStyle_ = typingTextStyle;
}

/**
 * @tc.name: RichEditorPatternTestInitPreviewText001
 * @tc.desc: test InitPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorPatternTestInitPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::u16string previewTextValue;
    PreviewRange range;

    range.start = -1;
    range.end = 0;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), false);

    range.start = 0;
    range.end = -1;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), false);

    range.start = -1;
    range.end = -1;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), true);

    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    ASSERT_EQ(richEditorPattern->InitPreviewText(previewTextValue, range), true);
}

/**
 * @tc.name: VirtualKeyboardAreaChanged001
 * @tc.desc: test OnVirtualKeyboardAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, VirtualKeyboardAreaChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    float height = 0.0f;
    auto x = richEditorPattern->CalcCursorOffsetByPosition(richEditorPattern->textSelector_.GetStart(), height).GetX();
    richEditorPattern->OnVirtualKeyboardAreaChanged();
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetX(), x);
}

/**
 * @tc.name: RichEditorToJsonValue001
 * @tc.desc: test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, RichEditorToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    auto jsonObject = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    EXPECT_FALSE(filter.IsFastFilter());
    richEditorPattern->SetRequestKeyboardOnFocus(true);
    richEditorPattern->ToJsonValue(jsonObject, filter);
    EXPECT_EQ(jsonObject->GetString("enableKeyboardOnFocus"), "true");

    filter.filterFixed = 10;
    EXPECT_TRUE(filter.IsFastFilter());
    richEditorPattern->ToJsonValue(jsonObject, filter);
    EXPECT_FALSE(jsonObject->IsNull());
}

/**
 * @tc.name: IsClickBoundary001
 * @tc.desc: test IsClickBoundary
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, IsClickBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    auto length = richEditorPattern->GetTextContentLength();
    auto caretPosition = length + 1;
    auto ret = richEditorPattern->IsClickBoundary(caretPosition);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: UpdateChildrenOffset001
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, UpdateChildrenOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    richEditorPattern->isSpanStringMode_ = true;
    std::list<RefPtr<UINode>>& childrens = host->ModifyChildren();
    auto childNode2 = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<ImagePattern>());
    auto childNode3 = FrameNode::CreateFrameNode("childNode", 3, AceType::MakeRefPtr<PlaceholderSpanPattern>());
    auto childNode4 = FrameNode::CreateFrameNode("childNode", 4, AceType::MakeRefPtr<ImagePattern>());
    auto childNode5 = FrameNode::CreateFrameNode("childNode", 5, AceType::MakeRefPtr<PlaceholderSpanPattern>());
    auto childNode6 = FrameNode::CreateFrameNode("childNode", 5, AceType::MakeRefPtr<Pattern>());
    childrens.emplace_back(childNode2);
    childrens.emplace_back(childNode3);
    childrens.emplace_back(childNode4);
    childrens.emplace_back(childNode5);
    richEditorPattern->UpdateChildrenOffset();
    EXPECT_NE(richEditorPattern->spans_.size(), 0);
}

/**
 * @tc.name: NeedAiAnalysis001
 * @tc.desc: test NeedAiAnalysis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, NeedAiAnalysis001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    std::string content = "";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    CaretUpdateType targeType1 = CaretUpdateType::PRESSED;
    int32_t pos = 0;
    int32_t spanStart = 10;
    auto ret = richEditorPattern->NeedAiAnalysis(targeType1, pos, spanStart, content);
    EXPECT_FALSE(ret);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    CaretUpdateType targeType2 = CaretUpdateType::DOUBLE_CLICK;
    ret = richEditorPattern->NeedAiAnalysis(targeType2, pos, spanStart, content);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustCursorPosition001
 * @tc.desc: test AdjustCursorPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, AdjustCursorPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);
    int32_t pos = 0;
    richEditorPattern->AdjustCursorPosition(pos);
    EXPECT_EQ(pos, 0);
}

/**
 * @tc.name: GetReplacedSpan001
 * @tc.desc: test GetReplacedSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetReplacedSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
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

    RichEditorChangeValue changeValue;
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;
    int32_t innerPosition = 0;
    std::u16string insertValue = u"test123\n123";
    int32_t textIndex = 1;
    std::optional<TextStyle> textStyle = std::optional<TextStyle>(TextStyle());
    richEditorPattern->GetReplacedSpan(
        changeValue, innerPosition, insertValue, textIndex, textStyle, spanParaStyle, std::nullopt, false, false);
    auto uiNode = host->GetChildAtIndex(0);
    EXPECT_NE(uiNode, nullptr);
    EXPECT_EQ(uiNode->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: GetReplacedSpanFission001
 * @tc.desc: test GetReplacedSpanFission
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetReplacedSpanFission001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    std::u16string content = u"test123\n";
    int32_t startSpanIndex = 0;
    int32_t offsetInSpan = 0;
    std::optional<TextStyle> textStyle = std::optional<TextStyle>(TextStyle());
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;
    std::optional<std::u16string> urlAddress = std::nullopt;
    richEditorPattern->GetReplacedSpanFission(
        changeValue, innerPosition, content, startSpanIndex, offsetInSpan, textStyle, spanParaStyle, urlAddress);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: CalcInsertValueObj003
 * @tc.desc: test CalcInsertValueObj
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, CalcInsertValueObj003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->spans_.clear();
    AddSpan(u"");
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    TextInsertValueInfo info;
    it->content = u"";
    it->position = 0;
    int textIndex = 1;
    richEditorPattern->CalcInsertValueObj(info, textIndex, false);
    EXPECT_NE(info.GetSpanIndex(), richEditorPattern->spans_.size());

    /**
     * @tc.steps: step2. change parameter and call function.
     */
    it->content = u"test123\n";
    it->position = 18;
    textIndex = 18;
    richEditorPattern->CalcInsertValueObj(info, textIndex, false);
    EXPECT_NE(info.GetSpanIndex(), richEditorPattern->spans_.size());
}

/**
 * @tc.name: GetDelPartiallySpanItem001
 * @tc.desc: test GetDelPartiallySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetDelPartiallySpanItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);
    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    firstInfo.SetValue(u"");
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    lastInfo.SetValue(u"test123\n");
    int32_t lastLength = static_cast<int32_t>(lastInfo.GetValue().length());
    lastInfo.SetEraseLength(lastLength - 1);
    std::u16string originalStr;
    int32_t originalPos = 0;
    auto ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    auto it = richEditorPattern->spans_.front();
    EXPECT_NE(ret, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
    firstInfo.SetEraseLength(firstLength);
    lastLength = static_cast<int32_t>(lastInfo.GetValue().length());
    lastInfo.SetEraseLength(lastLength);
    ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: TestRichEditorBeforeChangeText002
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, TestRichEditorBeforeChangeText002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    TextSpanOptions options;
    options.style = std::optional<TextStyle>(TextStyle(5));
    richEditorPattern->spans_.clear();
    auto ret = richEditorPattern->BeforeChangeText(changeValue, options);
    EXPECT_EQ(ret, true);
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    options.offset = 200;
    ret = richEditorPattern->BeforeChangeText(changeValue, options);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: FixMoveDownChange001
 * @tc.desc: test FixMoveDownChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, FixMoveDownChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    span1.SetValue(u"test123");
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    span2.SetValue(u"test");
    changeValue.replacedSpans_.emplace_back(span2);
    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
    firstInfo.SetEraseLength(firstLength);
    auto spanIndex = firstInfo.GetSpanIndex();
    richEditorPattern->FixMoveDownChange(changeValue, 0);
    EXPECT_EQ(spanIndex, firstInfo.GetSpanIndex());
}

/**
 * @tc.name: BeforeUndo001
 * @tc.desc: test BeforeUndo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, BeforeUndo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
    record.afterCaretPosition = 1;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    record.deleteCaretPostion = 0;
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPostion = -1;
    record.deleteText = u"test\n";
    richEditorPattern->BeforeUndo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: BeforeRedo001
 * @tc.desc: test BeforeRedo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, BeforeRedo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    RichEditorPattern::OperationRecord record;
    record.addText = u"test123\n";
    record.beforeCaretPosition = 20;
    /**
     * @tc.steps: step2. change parameters and call function.
     */
    record.deleteCaretPostion = 0;
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
    /**
     * @tc.steps: step3. change parameters and call function.
     */
    record.deleteCaretPostion = -1;
    record.deleteText = u"test\n";
    richEditorPattern->BeforeRedo(changeValue, innerPosition, record);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: GetThumbnailCallback003
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetThumbnailCallback003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetThumbnailCallback()(Offset(1.0f, 10.0f));
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: GetPreviewTextDecorationColor001
 * @tc.desc: test GetPreviewTextDecorationColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetPreviewTextDecorationColor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutproperty = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutproperty, nullptr);
    layoutproperty->UpdatePreviewTextStyle("underline");

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    RichEditorTheme richEditorTheme;
    EXPECT_EQ(richEditorPattern->GetPreviewTextDecorationColor(), richEditorTheme.GetPreviewUnderLineColor());

    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->UpdatePreviewTextStyle("normal");
    EXPECT_EQ(richEditorPattern->GetPreviewTextDecorationColor(), Color::TRANSPARENT);

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: GetPreviewTextUnderlineWidth001
 * @tc.desc: test GetPreviewTextUnderlineWidth
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetPreviewTextUnderlineWidth001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    RichEditorTheme richEditorTheme;
    EXPECT_EQ(
        richEditorPattern->GetPreviewTextUnderlineWidth(), richEditorTheme.GetPreviewUnderlineWidth().ConvertToPx()
    );

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: ToGestureSpan001
 * @tc.desc: test ToGestureSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ToGestureSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();

    spanItem->onClick = [](GestureEvent& info) {};
    spanItem->onLongPress = [](GestureEvent& info) {};

    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToGestureSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: FinishTextPreview001
 * @tc.desc: test FinishTextPreview
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, FinishTextPreview001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;

    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE2, previewRange);
    richEditorPattern->FinishTextPreview();

    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, testFrameNodeId, richEditorPattern);
    ASSERT_NE(childFrameNode, nullptr);
    auto childSpanNode = AceType::MakeRefPtr<SpanNode>(testSpanNodeId);
    ASSERT_NE(childSpanNode, nullptr);

    do {
        auto newHost1 = richEditorPattern->GetContentHost();
        auto newHost2 = richEditorPattern->GetContentHost();
        ASSERT_EQ(newHost1, newHost2);

        newHost1->children_.emplace_back(childFrameNode);
        newHost1->children_.emplace_back(childSpanNode);
        ASSERT_EQ(newHost1, newHost2);
    } while (0);

    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE2, previewRange);
    richEditorPattern->FinishTextPreview();
    EXPECT_EQ(richEditorPattern->previewTextRecord_.previewContent, u"");
}

/**
 * @tc.name: OnBackPressed001
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, OnBackPressed001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);

    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);

    auto func = []() {};
    richEditorPattern->SetCustomKeyboard(func);
    richEditorPattern->RequestCustomKeyboard();
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);

    richEditorPattern->imeShown_ = true;
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);
}

/**
 * @tc.name: AddUdmfData001
 * @tc.desc: test AddUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, AddUdmfData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    ResultObject resultObject;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPESYMBOLSPAN;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valueString = INIT_VALUE_1;
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valueString.clear();
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    resultObject.type = SelectSpanType::TYPEIMAGE;
    resultObject.valuePixelMap = PixelMap::CreatePixelMap(nullptr);
    ASSERT_NE(resultObject.valuePixelMap, nullptr);
    richEditorPattern->dragResultObjects_.emplace_back(resultObject);

    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);

    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    richEditorPattern->AddUdmfData(event);
    if (UdmfClient::GetInstance()->CreateUnifiedData()) {
        EXPECT_NE(event->GetData(), 0);
    } else {
        EXPECT_EQ(event->GetData(), 0);
    }
}

/**
 * @tc.name: ToBaselineOffsetSpan001
 * @tc.desc: test ToBaselineOffsetSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ToBaselineOffsetSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->textLineStyle->UpdateBaselineOffset(Dimension(testNumber5, DimensionUnit::PX));
    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToBaselineOffsetSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: ToTextShadowSpan001
 * @tc.desc: test ToTextShadowSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, ToTextShadowSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    Shadow textShadow1 = Shadow();
    Shadow textShadow2 = Shadow();
    textShadow1.SetColor(Color::RED);
    textShadow2.SetColor(Color::WHITE);
    std::vector<Shadow> shadows { textShadow1, textShadow2 };
    spanItem->fontStyle->UpdateTextShadow(shadows);
    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToTextShadowSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: GetPreviewTextRects001
 * @tc.desc: test GetPreviewTextRects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetPreviewTextRects001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->InitPreviewText(PREVIEW_TEXT_VALUE1, previewRange);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> firstRects { RectF(testNumber0, testNumber0, testNumber5, testNumber5) };
    EXPECT_CALL(*paragraph, GetTightRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(firstRects));
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testNumber0, .end = testNumber2 });
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testNumber2, .end = testNumber4 });

    EXPECT_NE(richEditorPattern->GetPreviewTextRects().size(), 0);
}

/**
 * @tc.name: IsLineSeparatorInLast001
 * @tc.desc: test IsLineSeparatorInLast
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, IsLineSeparatorInLast001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanNode = AceType::MakeRefPtr<SpanNode>(testSpanNodeId);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanNode, nullptr);

    spanItem->content = u"ni\nhao";
    EXPECT_FALSE(richEditorPattern->IsLineSeparatorInLast(spanNode));

    spanItem->content = u"nihao\n";
    EXPECT_TRUE(richEditorPattern->IsLineSeparatorInLast(spanNode));
}

/**
 * @tc.name: GetRichEditorController001
 * @tc.desc: test GetRichEditorController
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, GetRichEditorController001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto controller = richEditorModel.GetRichEditorController();
    ASSERT_NE(controller, nullptr);
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: test OnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, OnHandleMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnHandleMove(rect, true);
}

/**
 * @tc.name: UpdateSelectorOnHandleMove001
 * @tc.desc: test UpdateSelectorOnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestNg, UpdateSelectorOnHandleMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->UpdateSelectorOnHandleMove(offsetF, true);
}
} // namespace