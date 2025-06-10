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
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorPatternTestFourNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestFourNg::SetUp()
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

void RichEditorPatternTestFourNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestFourNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: AddImageSpan001
 * @tc.desc: test AddImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, AddImageSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ImageSpanOptions options;
    int32_t res = richEditorPattern->AddImageSpan(options, TextChangeReason::UNKNOWN, true, 0, false);
    ASSERT_EQ(res, 0);
}

/**
 * @tc.name: SetMenuParam001
 * @tc.desc: test SetMenuParam
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMenuParam001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddImageSpan();
    std::function<void()> tempFunc = []() { };
    std::function<void()>& func = tempFunc;
    SelectMenuParam menuParam;
    richEditorPattern->SetPreviewMenuParam(TextSpanType::IMAGE, func, menuParam);
    EXPECT_TRUE(static_cast<bool>(richEditorPattern->oneStepDragController_));
}

/**
 * @tc.name: AddImageSpan002
 * @tc.desc: test AddImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, AddImageSpan002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    ImageSpanOptions options;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    ImageSpanAttribute imageStyle;
    imageStyle.verticalAlign = VerticalAlign::FOLLOW_PARAGRAPH;
    options.imageAttribute = imageStyle;
    auto index = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index, 0);
    auto spanItem = richEditorPattern->spans_.front();
    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(spanItem);
    ASSERT_NE(imageSpanItem, nullptr);
    auto imageAttribute = imageSpanItem->options.imageAttribute;
    bool hasImageAttribute = imageAttribute.has_value();
    EXPECT_TRUE(hasImageAttribute);
    auto verticalAlign = imageAttribute.value().verticalAlign;
    auto hasVerticalAlign = verticalAlign.has_value();
    EXPECT_TRUE(hasVerticalAlign);
    EXPECT_EQ(verticalAlign.value(), VerticalAlign::FOLLOW_PARAGRAPH);
}

/**
 * @tc.name: CalcCursorOffsetByPosition001
 * @tc.desc: test CalcCursorOffsetByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, CalcCursorOffsetByPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    float selectLineHeight = 0;
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    AddSpan("test");
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    richEditorPattern->spans_.clear();
    richEditorPattern->CalcCursorOffsetByPosition(0, selectLineHeight, true, true);

    ASSERT_EQ(richEditorPattern->GetTextContentLength() == 0, true);
}

/**
 * @tc.name: CheckEditorTypeChange001
 * @tc.desc: test CheckEditorTypeChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, CheckEditorTypeChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CheckEditorTypeChange();

    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = 143;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    richEditorPattern->selectOverlayProxy_ = proxy;
    richEditorPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType =
        static_cast<int32_t>(TextSpanType::TEXT);
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType =
        static_cast<int32_t>(TextSpanType::NONE);
    richEditorPattern->selectedType_ = TextSpanType::TEXT;
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType =
        static_cast<int32_t>(TextSpanType::TEXT);
    richEditorPattern->selectedType_ = TextSpanType::TEXT;
    richEditorPattern->CheckEditorTypeChange();

    richEditorPattern->selectOverlayProxy_->selectOverlayId_ = 1;
    richEditorPattern->CheckEditorTypeChange();

    EXPECT_TRUE(richEditorPattern->selectOverlayProxy_);
}

/**
 * @tc.name: GetLeftWordPosition001
 * @tc.desc: test GetLeftWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetLeftWordPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan("hello1");
    int32_t res = richEditorPattern->GetLeftWordPosition(-9999);

    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, HandleSurfaceChanged001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    richEditorPattern->HandleSurfaceChanged(0, 0, 0, 0, WindowSizeChangeReason::DRAG);

    EXPECT_EQ(richEditorPattern->magnifierController_->GetShowMagnifier(), false);
}

/**
 * @tc.name: SetMaxLength001
 * @tc.desc: test SetMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    int32_t maxLength = 1;
    richEditorPattern->SetMaxLength(maxLength);
    EXPECT_EQ(richEditorPattern->GetMaxLength(), 1);
}

/**
 * @tc.name: SetMaxLength002
 * @tc.desc: test SetMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLength002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    EXPECT_EQ(richEditorPattern->GetMaxLength(), INT_MAX);
}

/**
 * @tc.name: SetMaxLines001
 * @tc.desc: test SetMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLines001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    int32_t maxLines = 1;
    richEditorPattern->SetMaxLines(maxLines);
    EXPECT_EQ(richEditorPattern->GetMaxLines(), 1);
}

/**
 * @tc.name: SetMaxLines002
 * @tc.desc: test SetMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLines002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    int32_t maxLines = 0;
    richEditorPattern->SetMaxLines(maxLines);
    EXPECT_EQ(richEditorPattern->GetMaxLines(), 0);
}

/**
 * @tc.name: SetMaxLines003
 * @tc.desc: test SetMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLines003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    EXPECT_EQ(richEditorPattern->GetMaxLines(), INT_MAX);
}

/**
 * @tc.name: SetMaxLinesHeight001
 * @tc.desc: test SetMaxLinesHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLinesHeight001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    float height = 0.0f;
    richEditorPattern->SetMaxLinesHeight(height);
    EXPECT_EQ(richEditorPattern->GetMaxLinesHeight(), 0.0f);
}

/**
 * @tc.name: SetMaxLinesHeight002
 * @tc.desc: test SetMaxLinesHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLinesHeight002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    float height = 10.0f;
    richEditorPattern->SetMaxLinesHeight(height);
    EXPECT_EQ(richEditorPattern->GetMaxLinesHeight(), 10.0f);
}

/**
 * @tc.name: SetMaxLinesHeight003
 * @tc.desc: test SetMaxLinesHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetMaxLinesHeight003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    EXPECT_EQ(richEditorPattern->GetMaxLinesHeight(), FLT_MAX);
}

/**
 * @tc.name: ResetFirstNodeStyle001
 * @tc.desc: test ResetFirstNodeStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ResetFirstNodeStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    auto index3 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index3, 2);
    auto index4 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index4, 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: ProcessStyledString001
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    ASSERT_EQ(richEditorPattern->spans_.empty(), true);
}

/**
 * @tc.name: ProcessStyledString002
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->textForDisplay_ = INIT_VALUE_1;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: ProcessStyledString003
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, ProcessStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: SetSelection007
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetSelection007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    ASSERT_EQ(richEditorPattern->contentMod_, nullptr);
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->previewTextRecord_.previewContent = u"test";
    richEditorPattern->previewTextRecord_.startOffset = 1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = -1;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: SetSelection008
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, SetSelection008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    ASSERT_EQ(richEditorPattern->contentMod_, nullptr);
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);
    richEditorPattern->previewTextRecord_.previewContent = u"test";
    richEditorPattern->previewTextRecord_.startOffset = -1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_TRUE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: GetTextBoxes002
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetTextBoxes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 3;

    std::vector<RectF> res;
    auto ret = richEditorPattern->GetTextBoxes();
    EXPECT_EQ(ret, res);

    TextLineMetrics lineMetrics;
    richEditorPattern->GetLineCount();
    EXPECT_EQ(richEditorPattern->GetLineHeight(), 0.0f);
    EXPECT_EQ(richEditorPattern->GetLetterSpacing(), 0.0f);
    auto retLineMetrics = richEditorPattern->GetLineMetrics(-1);
    EXPECT_EQ(retLineMetrics.x, 0);

    auto retLineMetricsS = richEditorPattern->GetLineMetrics(2);
    EXPECT_EQ(retLineMetricsS.x, 0);

    int32_t scroll_from_update = 1;
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 1, 100, 160);
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update)) << "Reach Top Boundary";
}

/**
 * @tc.name: GetCrossOverHeight004
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetCrossOverHeight004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: GetCrossOverHeight005
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, GetCrossOverHeight005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = false;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = false;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CalculateTruncationLength001
 * @tc.desc: test CalculateTruncationLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, CalculateTruncationLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    std::string insertValue = "hello";
    int32_t start = 2;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 4;
    int32_t length = richEditorPattern->CalculateTruncationLength(StringUtils::Str8ToStr16(insertValue), start);
    EXPECT_EQ(length, 4);
}

/**
 * @tc.name: CalculateTruncationLength002
 * @tc.desc: test CalculateTruncationLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestFourNg, CalculateTruncationLength002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    std::string insertValue = "hello";
    int32_t start = 2;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    int32_t length = richEditorPattern->CalculateTruncationLength(StringUtils::Str8ToStr16(insertValue), start);
    EXPECT_EQ(length, 2);
}

} // namespace OHOS::Ace::NG