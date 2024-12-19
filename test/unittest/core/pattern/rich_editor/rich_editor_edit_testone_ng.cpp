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

class RichEditorEditTestOneNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorEditTestOneNg::SetUp()
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

void RichEditorEditTestOneNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorEditTestOneNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetRightTextOfCursor001
 * @tc.desc: test GetRightTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetRightTextOfCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"tesol";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(2));
    EXPECT_EQ(ret, "ol");

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(2));
    EXPECT_EQ(ret, "es");
}

/**
 * @tc.name: GetRightTextOfCursor002
 * @tc.desc: test get right text of cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetRightTextOfCursor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(3));
    EXPECT_EQ(ret, "hel");
}

/**
 * @tc.name: GetTextIndexAtCursor001
 * @tc.desc: test get text index at cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetTextIndexAtCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 3;
    EXPECT_EQ(richEditorPattern->GetTextIndexAtCursor(), 3);
}

/**
 * @tc.name: GetSelectedSpanText002
 * @tc.desc: test get select span text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetSelectedSpanText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto ret = richEditorPattern->GetSelectedSpanText(INIT_U16VALUE_1, -1, 1);
    ret = richEditorPattern->GetSelectedSpanText(INIT_U16VALUE_1, -1, 10);
    ret = richEditorPattern->GetSelectedSpanText(INIT_U16VALUE_1, 0, 1);
    EXPECT_EQ(StringUtils::Str16ToStr8(ret), "h");
}

/**
 * @tc.name: GetChildByIndex002
 * @tc.desc: test get child by index
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetChildByIndex002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetChildByIndex(-1);
    AddSpan(INIT_VALUE_1);
    auto ret = richEditorPattern->GetChildByIndex(0);
    EXPECT_EQ(*(richEditorNode_->GetChildren().begin()), ret);
}

/**
 * @tc.name: GetChildByIndex001
 * @tc.desc: test GetChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetChildByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    AddSpan(INIT_VALUE_1);
    auto ret1 = richEditorPattern->GetChildByIndex(1);
    EXPECT_EQ(ret1, nullptr);
    auto ret2 = richEditorPattern->GetChildByIndex(-1);
    EXPECT_EQ(ret2, nullptr);
    auto ret3 = richEditorPattern->GetChildByIndex(0);
    EXPECT_NE(ret3, nullptr);
}

/**
 * @tc.name: GetSelectedSpanText001
 * @tc.desc: test GetSelectedSpanText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetSelectedSpanText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string ori = u"12345";

    std::vector<int> start = { -1, 0, 15 };
    std::vector<int> end = { 10, -3 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto ret = richEditorPattern->GetSelectedSpanText(ori, start[i], end[j]);
            EXPECT_EQ(StringUtils::Str16ToStr8(ret), "");
        }
    }

    auto ret = richEditorPattern->GetSelectedSpanText(ori, 0, 1);
    EXPECT_EQ(StringUtils::Str16ToStr8(ret), "1");
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, CreateNodePaintMethod001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, CreateNodePaintMethod002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->contentMod_ = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, richEditorPattern);
    richEditorPattern->isCustomFont_ = true;
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: GetSpanItemByIndex001
 * @tc.desc: test GetSpanItemByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetSpanItemByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto ret = richEditorPattern->GetSpanItemByIndex(-1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(0);
    EXPECT_EQ(ret, richEditorPattern->spans_.front());
}

/**
 * @tc.name: DeleteValueSetTextSpan
 * @tc.desc: test add delete text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, DeleteValueSetTextSpan, TestSize.Level1)
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
    spanItem->textStyle_.value().fontFamilies_.push_back("test1");
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(0);
    richEditorPattern->DeleteValueSetTextSpan(spanItem, 0, 1, spanResult);

    EXPECT_EQ(spanResult.GetTextStyle().textAlign, int(TextAlign::END));
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[0], "5.00px");
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[1], "10.00px");

    ClearSpan();
}

/**
 * @tc.name: DeleteValueSetImageSpan
 * @tc.desc: test delete imagespan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, DeleteValueSetImageSpan, TestSize.Level1)
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
 * @tc.name: InsertValueByPaste001
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, InsertValueByPaste001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. construct spanItem_.
     */
    textPattern->isSpanStringMode_ = true;

    auto pasteStr = richEditorPattern->GetPasteStr();
    richEditorPattern->InsertValueByPaste(pasteStr);

    richEditorPattern->OnAreaChangedInner();
    OffsetF Offset = {1, 2};
    EXPECT_NE(richEditorPattern->GetPaintRectGlobalOffset(), Offset);
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetThumbnailCallback001, TestSize.Level1)
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
 * @tc.name: SetSelection001
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, SetSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->DumpInfo();

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);

    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), false);

    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    richEditorPattern->ScrollToSafeArea();
    EXPECT_EQ(LessNotEqual(manager->GetHeight(), 800.0f), true);

    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    Offset Offset = {1, 4};
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    int32_t index = 1;
    richEditorPattern->MouseDoubleClickParagraphEnd(index);
    EXPECT_NE(richEditorPattern->GetParagraphEndPosition(index), index);

    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    int32_t start = 1;
    int32_t end = 3;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetStart(), start);

    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetEnd(), end);

    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetEnd(), end);
}

/**
 * @tc.name: CreateHandles001
 * @tc.desc: test CreateHandles
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, CreateHandles001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 3;

    richEditorPattern->CreateHandles();
    auto offsetF = OffsetF(0.0f, 0.0f);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset, offsetF);

    richEditorPattern->ShowHandles(false);
    EXPECT_NE(richEditorPattern->showSelect_, false);

    richEditorPattern->ShowHandles(true);
    EXPECT_EQ(richEditorPattern->showSelect_, true);

    Offset textOffset = {1, 3};
    EXPECT_NE(richEditorPattern->BetweenSelection(textOffset), true);

    richEditorPattern->CloseHandleAndSelect();
    EXPECT_EQ(richEditorPattern->showSelect_, false);
}

/**
 * @tc.name: RefreshSelectOverlay001
 * @tc.desc: test RefreshSelectOverlay and more.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, RefreshSelectOverlay001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    int32_t posx = 1;
    int32_t posy = 3;
    richEditorPattern->HandleSurfacePositionChanged(posx, posy);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->themeManager_ = theme;

    richEditorPattern->customKeyboardBuilder_ = []() {};
    richEditorPattern->DumpInfo();
    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), true);

    richEditorPattern->selectOverlay_->SetUsingMouse(false);
    richEditorPattern->UpdateSelectionInfo(posx, posy);
    EXPECT_EQ(richEditorPattern->sourceType_, SourceType::TOUCH);

    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    Offset Offset = {1, 4};
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: ShowHandles001
 * @tc.desc: test ShowHandles
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ShowHandles001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    auto offsetF = OffsetF(0.0f, 0.0f);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset, offsetF);

    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);

    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->ShowHandles(false);
    EXPECT_EQ(richEditorPattern->showSelect_, true);

    richEditorPattern->isSpanStringMode_ = true;
    auto pasteStr = richEditorPattern->GetPasteStr();
    richEditorPattern->InsertValueByPaste(pasteStr);
    EXPECT_EQ(richEditorPattern->caretVisible_, true);

    richEditorPattern->GetThumbnailCallback();
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: HandleOnPaste001
 * @tc.desc: test HandleOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleOnPaste001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    AddSpan("testHandleOnPaste1");
    richEditorPattern->HandleOnPaste();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 8;
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);

    ClearSpan();
    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->OnCopyOperation(true);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
}

/**
 * @tc.name: HandleAIWrite001
 * @tc.desc: test GetAIWriteInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleAIWrite001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);

    richEditorPattern->textSelector_.Update(0, 5);
    AIWriteInfo info;
    richEditorPattern->GetAIWriteInfo(info);
    EXPECT_EQ(info.selectStart, 0);
    EXPECT_EQ(info.selectEnd, 5);
    EXPECT_EQ(info.selectLength, 5);
    EXPECT_EQ(info.firstHandle, richEditorPattern->textSelector_.firstHandle.ToString());
    EXPECT_EQ(info.secondHandle, richEditorPattern->textSelector_.secondHandle.ToString());
    RefPtr<SpanString> spanString = SpanString::DecodeTlv(info.selectBuffer);
    ASSERT_NE(spanString, nullptr);
    auto textContent = spanString->GetString();
    EXPECT_EQ(textContent.empty(), false);
}

/**
 * @tc.name: HandleAIWrite001
 * @tc.desc: test HandleOnAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleAIWrite002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->HandleOnAIWrite();
    auto start = richEditorPattern->operationRecords_.size();

    std::vector<uint8_t> buff;
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"dddd结果回填123456");
    spanStr->EncodeTlv(buff);
    richEditorPattern->HandleAIWriteResult(0, 5, buff);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 3);
}

/**
 * @tc.name: HandleAIWrite001
 * @tc.desc: test AddSpansAndReplacePlaceholder&SetSubSpansWithAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleAIWrite003, TestSize.Level1)
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
     * @tc.steps: step2. add span
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;
    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 0);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddSymbolSpan(options1);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddImageSpan(options3);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 5);

    /**
     * @tc.steps: step3. replace and recover placeholder for non-text.
     */
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"");
    ASSERT_NE(spanString, nullptr);
    richEditorPattern->SetSubSpansWithAIWrite(spanString, 0, 12);
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"test![id1]占位符![id2]");
    richEditorPattern->textSelector_.Update(0, 10);
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanStr);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 4);
}

/**
 * @tc.name: GetTextBoxes001
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetTextBoxes001, TestSize.Level1)
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
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update)) << "Reach Top Boundary";

    EXPECT_EQ(richEditorPattern->MoveTextRect(0.0f), 0.0f);

    auto offsetF = OffsetF(0.0f, 0.5f);
    richEditorPattern->MoveCaretToContentRect(offsetF, 8.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    richEditorPattern->MoveCaretToContentRect(1.0f, 10);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    richEditorPattern->contentChange_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
}

/**
 * @tc.name: UpdateTextStyle
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, UpdateTextStyle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE);
    textStyle.SetLineHeight(LINE_HEIGHT_VALUE);
    textStyle.SetLetterSpacing(LETTER_SPACING);

    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateLineHeight = LINE_HEIGHT_VALUE;
    updateSpanStyle.updateLetterSpacing = LETTER_SPACING;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;

    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetLetterSpacing(), LETTER_SPACING);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: UpdateTextStyle
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, UpdateTextStyle2, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;
    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: SetTypingStyle
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, SetTypingStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    AddSpan(INIT_VALUE_1);
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle2.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle2.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: HasSameTypingStyle001
 * @tc.desc: test HasSameTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HasSameTypingStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    auto spanItem = it->GetSpanItem();

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    auto ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = std::nullopt;
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_.value().fontFamilies_.push_back("test1");
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTypingStyle
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, SetTypingStyle2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: MoveCaretToContentRect001
 * @tc.desc: test MoveCaretToContentRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, MoveCaretToContentRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->selectOverlayNode_ = overlayNode;

    richEditorPattern->OnAreaChangedInner();
    OffsetF Offset = { 1, 2 };
    EXPECT_NE(richEditorPattern->GetPaintRectGlobalOffset(), Offset);

    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootHeight_ = 80.0;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);

    int32_t scroll_from_update = 1;
    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 5, 100, 160);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update));

    /**
     * @tc.steps: step1. set isShowPlaceholder_
     */
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 120);
    richEditorPattern->contentRect_ = RectF(0, 5, 100, 60);
    auto offsetF = OffsetF(0.0f, 0.5f);
    richEditorPattern->isShowPlaceholder_ = false;
    richEditorPattern->MoveCaretToContentRect(offsetF, 80.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    /**
     * @tc.steps: step2. set MoveCaretToContentRect second parameter
     */
    richEditorPattern->MoveCaretToContentRect(offsetF, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    /**
     * @tc.steps: step3. set MoveCaretToContentRect first parameter
     */
    auto offsetFtemp = OffsetF(0.0f, 10.0f);
    richEditorPattern->MoveCaretToContentRect(offsetFtemp, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);
}

/**
 * @tc.name: InitScrollablePattern001
 * @tc.desc: test InitScrollablePattern
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, InitScrollablePattern001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->SetThemeManager(theme);

    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), false);

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), false);

    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: GetThumbnailCallback002
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetThumbnailCallback002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    richEditorPattern->InitDragDropEvent();
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: VirtualKeyboardAreaChanged002
 * @tc.desc: test OnVirtualKeyboardAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, VirtualKeyboardAreaChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    richEditorPattern->OnVirtualKeyboardAreaChanged();
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: GetSelectedBackgroundColor001
 * @tc.desc: test GetSelectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    richEditorPattern->selectedBackgroundColor_.reset();
    auto ret = richEditorPattern->GetSelectedBackgroundColor();
    EXPECT_NE(ret.GetValue(), 0);
}

/**
 * @tc.name: HandleOnDragDrop001
 * @tc.desc: test HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleOnDragDrop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->HandleOnDragDrop(event);
    EXPECT_NE(event->GetData(), nullptr);
}

/**
 * @tc.name: ResetKeyboardIfNeed001
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ResetKeyboardIfNeed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    richEditorPattern->imeShown_ = true;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->currentFocus_ = true;
    richEditorPattern->action_ = TextInputAction::SEARCH;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::SEARCH);
}

/**
 * @tc.name: GetChangeSpanStyle001
 * @tc.desc: test GetChangeSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetChangeSpanStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;

    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);

    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(StringUtils::ToWstring(firstInfo.GetValue()).length());
    firstInfo.SetEraseLength(firstLength);
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    int32_t lastLength = static_cast<int32_t>(StringUtils::ToWstring(lastInfo.GetValue()).length());
    lastInfo.SetEraseLength(lastLength);

    std::optional<TextStyle> spanTextStyle;
    RefPtr<SpanNode> spanNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    int32_t spanIndex = 0;
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
    /**
     * @tc.steps: step2. change parameter and call function.
    */
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    lastInfo.SetSpanIndex(richEditorPattern->spans_.size() - 1);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
    /**
     * @tc.steps: step4. change parameter and call function.
    */
    lastInfo.SetEraseLength(lastLength - 1);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
}

/**
 * @tc.name: RichEditorPatternTestUpdatePreviewText003
 * @tc.desc: test UpdatePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, RichEditorPatternTestUpdatePreviewText003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string previewTextValue;
    PreviewRange previewRange;

    previewRange.start = 0;
    previewRange.end = 0;
    ASSERT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), false);
}

/**
 * @tc.name: RichEditorPatternTestSetPreviewText001
 * @tc.desc: test SetPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, RichEditorPatternTestSetPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdatePreviewTextStyle("underline");
    std::vector<std::tuple<int, int, std::string, int>> testPreviewList;
    testPreviewList.emplace_back(-1, -1, PREVIEW_TEXT_VALUE1, 0);
    testPreviewList.emplace_back(0, -1, PREVIEW_TEXT_VALUE1, -1);
    testPreviewList.emplace_back(-1, 0, PREVIEW_TEXT_VALUE1, -1);
    testPreviewList.emplace_back(0, 0, PREVIEW_TEXT_VALUE1, 0);
    PreviewRange previewRange;
    for (const auto& testCase : testPreviewList) {
        previewRange.start = std::get<0>(testCase);
        previewRange.end = std::get<1>(testCase);
        ASSERT_EQ(richEditorPattern->SetPreviewText(std::get<2>(testCase), previewRange), std::get<3>(testCase));
    }
}

/**
 * @tc.name: RichEditorPatternTestGetPreviewTextStyle001
 * @tc.desc: test GetPreviewTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, RichEditorPatternTestGetPreviewTextStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);

    auto layoutProperty = host->layoutProperty_;
    host->layoutProperty_ = nullptr;
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);
    host->layoutProperty_ = layoutProperty;

    ASSERT_NE(host->layoutProperty_, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);

    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);

    property->UpdatePreviewTextStyle("normal");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);

    property->UpdatePreviewTextStyle("underline");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::UNDERLINE);

    property->UpdatePreviewTextStyle("unknown");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);
}

/**
 * @tc.name: HandleOnCut001
 * @tc.desc: test RichEditorPattern HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleOnCut001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->copyOption_ = CopyOptions::None;
    richEditorPattern->HandleOnCut();
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleOnCut();
    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
    richEditorPattern->textSelector_.baseOffset = -2;
    richEditorPattern->textSelector_.destinationOffset = -2;
    richEditorPattern->HandleOnCut();
    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
}

/**
 * @tc.name: HandleOnCut004
 * @tc.desc: test HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleOnCut004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

} // namespace OHOS::Ace::NG