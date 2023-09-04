/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/render/adapter/txt_paragraph.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "frameworks/base/window/drag_window.h"
#include "frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "frameworks/core/components_ng/pattern/root/root_pattern.h"
#include "frameworks/core/components_ng/pattern/text/span_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
const std::string INIT_VALUE_1 = "hello1";
const std::string INIT_VALUE_2 = "hello2";
const std::string TEST_INSERT_VALUE = "s";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const std::string IMAGE_VALUE = "image1";
const std::string BUNDLE_NAME = "bundleName";
const std::string MODULE_NAME = "moduleName";
} // namespace

class RichEditorTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void AddSpan(const std::string& content);
    void AddImageSpan();
    void ClearSpan();

protected:
    static void MockKeyboardBuilder() {}
    RefPtr<FrameNode> richEditorNode_;
};

void RichEditorTestNg::SetUp()
{
    MockPipelineBase::SetUp();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
}

void RichEditorTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockPipelineBase::TearDown();
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
}

void RichEditorTestNg::AddSpan(const std::string& content)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanModelNG spanModelNG;
    spanModelNG.Create(content);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetTextColor(TEXT_COLOR_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    spanModelNG.SetFontWeight(FONT_WEIGHT_VALUE);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetTextDecoration(TEXT_DECORATION_VALUE);
    spanModelNG.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    spanModelNG.SetTextCase(TEXT_CASE_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    spanNode->MountToParent(richEditorNode_, richEditorNode_->children_.size());
    richEditorPattern->spans_.emplace_back(spanNode->spanItem_);
    int32_t spanTextLength = 0;
    for (auto child = richEditorPattern->spans_.begin(); child != richEditorPattern->spans_.end();
         child++) {
        spanTextLength += StringUtils::ToWstring((*child)->content).length();
        (*child)->position = spanTextLength;
    }
}

void RichEditorTestNg::AddImageSpan()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    ImageSourceInfo imageInfo(IMAGE_VALUE, BUNDLE_NAME, MODULE_NAME);
    imageLayoutProperty->UpdateImageSourceInfo(imageInfo);
    imageNode->MountToParent(richEditorNode_, richEditorNode_->children_.size());
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->content = " ";
    spanItem->placeHolderIndex = 0;
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.emplace_back(spanItem);
    int32_t spanTextLength = 0;
    for (auto child = richEditorPattern->spans_.begin(); child != richEditorPattern->spans_.end();
         child++) {
        spanTextLength += StringUtils::ToWstring((*child)->content).length();
        (*child)->position = spanTextLength;
    }
}

void RichEditorTestNg::ClearSpan()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_->children_.clear();
    richEditorPattern->spans_.clear();
    richEditorPattern->caretPosition_ = 0;
}

/**
 * @tc.name: RichEditorModel001
 * @tc.desc: test create
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    EXPECT_EQ(ViewStackProcessor::GetInstance()->elementsStack_.size(), 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel002
 * @tc.desc: test create
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel002, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetDraggable(true);
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode()->draggable_);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel003
 * @tc.desc: test set on ready
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel003, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = []() { testOnReadyEvent = 1; };
    richEditorModel.SetOnReady(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnReady();
    EXPECT_EQ(testOnReadyEvent, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel004
 * @tc.desc: test set about to IME input
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel004, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorInsertValue&) {
        testAboutToIMEInput = 1;
        return true;
    };
    richEditorModel.SetAboutToIMEInput(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorInsertValue info;
    eventHub->FireAboutToIMEInput(info);
    EXPECT_EQ(testAboutToIMEInput, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel005
 * @tc.desc: test set on IME input complete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel005, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorAbstractSpanResult&) { testOnIMEInputComplete = 1; };
    richEditorModel.SetOnIMEInputComplete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorAbstractSpanResult info;
    eventHub->FireOnIMEInputComplete(info);
    EXPECT_EQ(testOnIMEInputComplete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel006
 * @tc.desc: test set about to delete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel006, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorDeleteValue&) {
        testAboutToDelete = 1;
        return true;
    };
    richEditorModel.SetAboutToDelete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorDeleteValue info;
    eventHub->FireAboutToDelete(info);
    EXPECT_EQ(testAboutToDelete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel007
 * @tc.desc: test set on delete complete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel007, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = []() { testOnDeleteComplete = 1; };
    richEditorModel.SetOnDeleteComplete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnDeleteComplete();
    EXPECT_EQ(testOnDeleteComplete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorInsertValue001
 * @tc.desc: test calc insert value object
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextInsertValueInfo info;
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.GetSpanIndex(), 0);
    EXPECT_EQ(info.GetOffsetInSpan(), 0);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.GetSpanIndex(), 1);
    EXPECT_EQ(info.GetOffsetInSpan(), 0);
}

/**
 * @tc.name: RichEditorInsertValue002
 * @tc.desc: test insert value last
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it3 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result3 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result3, it3->spanItem_->content);
    ClearSpan();
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it4 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result4 = TEST_INSERT_VALUE;
    EXPECT_EQ(result4, it4->spanItem_->content);
    ClearSpan();
}

/**
 * @tc.name: RichEditorInsertValue003
 * @tc.desc: test insert value between text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    AddSpan(INIT_VALUE_2);
    richEditorPattern->caretPosition_ = INIT_VALUE_1.size();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result1 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddImageSpan();
    AddImageSpan();
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(2));
    const std::string result2 = TEST_INSERT_VALUE;
    EXPECT_EQ(result2, it2->spanItem_->content);
}

/**
 * @tc.name: RichEditorInsertValue004
 * @tc.desc: test insert value first
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
}

/**
 * @tc.name: RichEditorCursorMove001
 * @tc.desc: test move cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorCursorMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->CursorMoveLeft();
    EXPECT_EQ(richEditorPattern->caretPosition_, 1);
    richEditorPattern->CursorMoveRight();
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->CursorMoveUp();
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->CursorMoveDown();
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
}

/**
 * @tc.name: RichEditorDelete001
 * @tc.desc: test delete forward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDelete001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteForward(7);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDelete002
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDelete002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(7);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorController001
 * @tc.desc: test add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController001, TestSize.Level1)
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
    options.offset = 1;
    auto index1 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index1, 0);
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 2;
    auto index2 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index2, 1);
}

/**
 * @tc.name: RichEditorController002
 * @tc.desc: test add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextSpanOptions options;
    options.offset = 1;
    options.value = INIT_VALUE_1;
    options.style->SetTextColor(TEXT_COLOR_VALUE);
    options.style->SetFontSize(FONT_SIZE_VALUE);
    options.style->SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    options.style->SetFontWeight(FONT_WEIGHT_VALUE);
    options.style->SetFontFamilies(FONT_FAMILY_VALUE);
    options.style->SetTextDecoration(TEXT_DECORATION_VALUE);
    options.style->SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    auto index1 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index2, 1);
}

/**
 * @tc.name: RichEditorController003
 * @tc.desc: test get caret offset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    auto offset1 = richEditorController->GetCaretOffset();
    EXPECT_EQ(offset1, 1);
    richEditorPattern->caretPosition_ = 2;
    auto offset2 = richEditorController->GetCaretOffset();
    EXPECT_EQ(offset2, 2);
}

/**
 * @tc.name: RichEditorController004
 * @tc.desc: test set caret offset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorController->SetCaretOffset(2);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorController->SetCaretOffset(-1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
}

/**
 * @tc.name: RichEditorController005
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE;
    updateSpanStyle.updateItalicFontStyle = ITALIC_FONT_STYLE_VALUE;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT_VALUE;
    updateSpanStyle.updateFontFamily = FONT_FAMILY_VALUE;
    updateSpanStyle.updateTextDecoration = TEXT_DECORATION_VALUE;
    updateSpanStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(5, 10, textStyle, imageStyle);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 5);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(1));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan1->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan1->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan1->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    auto newSpan2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(3));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan2->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan2->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan2->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan2->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
}

/**
 * @tc.name: RichEditorController006
 * @tc.desc: test get span info
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    auto info1 = richEditorController->GetSpansInfo(1, 10);
    EXPECT_EQ(info1.selection_.selection[0], 1);
    EXPECT_EQ(info1.selection_.selection[1], 10);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 3);
    auto info2 = richEditorController->GetSpansInfo(10, 1);
    EXPECT_EQ(info2.selection_.selection[0], 1);
    EXPECT_EQ(info2.selection_.selection[1], 10);
    auto info3 = richEditorController->GetSpansInfo(-1, 10);
    EXPECT_EQ(info3.selection_.selection[0], 0);
    EXPECT_EQ(info3.selection_.selection[1], 10);
    auto info4 = richEditorController->GetSpansInfo(1, -10);
    EXPECT_EQ(info4.selection_.selection[0], 0);
    EXPECT_EQ(info4.selection_.selection[1], 1);
}

/**
 * @tc.name: RichEditorController007
 * @tc.desc: test delete span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option1;
    option1.start = 5;
    option1.end = 10;
    richEditorController->DeleteSpans(option1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option2;
    option2.start = 10;
    option2.end = 5;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option3;
    option3.start = -5;
    option3.end = 10;
    richEditorController->DeleteSpans(option3);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option4;
    option4.start = 5;
    option4.end = -10;
    richEditorController->DeleteSpans(option4);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);
}

/**
 * @tc.name: OnDirtyLayoutWrapper001
 * @tc.desc: test on dirty layout wrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnDirtyLayoutWrapper001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
    EXPECT_EQ(richEditorPattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: test handle click event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    auto layoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto richEditorLayoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(layoutAlgorithm);
    richEditorPattern->paragraph_ = richEditorLayoutAlgorithm->GetParagraph();
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: HandleFocusEvent001
 * @tc.desc: test handle focus event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleFocusEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto func = std::bind(&RichEditorTestNg::MockKeyboardBuilder);
    richEditorPattern->customKeyboardBuilder_ = std::move(func);
    richEditorPattern->HandleFocusEvent();
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
    EXPECT_TRUE(richEditorPattern->isCustomKeyboardAttached_);
}

/**
 * @tc.name: RequestKeyboard001
 * @tc.desc: test request keyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RequestKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto func = std::bind(&RichEditorTestNg::MockKeyboardBuilder);
    richEditorPattern->customKeyboardBuilder_ = std::move(func);
    auto ret1 = richEditorPattern->RequestKeyboard(true, false, true);
    EXPECT_TRUE(ret1);
}

/**
 * @tc.name: CloseKeyboard001
 * @tc.desc: test close keyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CloseKeyboard001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto func = std::bind(&RichEditorTestNg::MockKeyboardBuilder);
    richEditorPattern->customKeyboardBuilder_ = std::move(func);
    richEditorPattern->HandleFocusEvent();
    richEditorPattern->CloseKeyboard(true);
    EXPECT_FALSE(richEditorPattern->isCustomKeyboardAttached_);
}

/**
 * @tc.name: MoveCaretAfterTextChange001
 * @tc.desc: test move caret after text change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, MoveCaretAfterTextChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->moveDirection_ = MoveDirection::BACKWARD;
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 4);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection::FORWARD;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
}
} // namespace OHOS::Ace::NG
