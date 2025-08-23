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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
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
const std::u16string PLACEHOLDER_TEXT = u"Placeholder text";
} // namespace

class RichEditorEditTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorEditTestNg::SetUp()
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

void RichEditorEditTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorEditTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}


/**
 * @tc.name: RichEditorInsertValue001
 * @tc.desc: test calc insert value object
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue001, TestSize.Level1)
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
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(contentNode->GetLastChild());
    ASSERT_NE(it1, nullptr);
    const std::u16string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it2 = AceType::DynamicCast<SpanNode>(contentNode->GetLastChild());
    ASSERT_NE(it2, nullptr);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it3 = AceType::DynamicCast<SpanNode>(contentNode->GetLastChild());
    ASSERT_NE(it3, nullptr);
    const std::u16string result3 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result3, it3->spanItem_->content);
    ClearSpan();
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it4 = AceType::DynamicCast<SpanNode>(contentNode->GetLastChild());
    ASSERT_NE(it4, nullptr);
    const std::u16string result4 = TEST_INSERT_VALUE;
    EXPECT_EQ(result4, it4->spanItem_->content);
    ClearSpan();
    richEditorPattern->InsertValue(u" ");
    auto it5 = AceType::DynamicCast<SpanNode>(contentNode->GetLastChild());
    EXPECT_TRUE(it5);
}

/**
 * @tc.name: RichEditorInsertValue003
 * @tc.desc: test insert value between text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    AddSpan(INIT_VALUE_2);
    richEditorPattern->caretPosition_ = INIT_VALUE_1.size();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(contentNode->GetFirstChild());
    const std::u16string result1 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
}

/**
 * @tc.name: RichEditorInsertValue004
 * @tc.desc: test insert value first
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(contentNode->GetFirstChild());
    const std::u16string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
}

/**
 * @tc.name: RichEditorInsertValue005
 * @tc.desc: test insert value if the insert char is line separator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->moveLength_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_LINE_SEP);
    auto it1 = AceType::DynamicCast<SpanNode>(contentNode->GetLastChild());
    const std::u16string result1 = INIT_VALUE_1;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->moveLength_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_LINE_SEP);
    auto it2 = AceType::DynamicCast<SpanNode>(contentNode->GetFirstChild());
    const std::u16string result2 = EXCEPT_VALUE;
    EXPECT_EQ(result2, it2->spanItem_->content);
}

/**
 * @tc.name: TestRichEditorGetAllChildren001
 * @tc.desc: test GetAllChildren
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorGetAllChildren001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetAllChildren();
    EXPECT_EQ(richEditorPattern->childNodes_.size(), 0);
}

/**
 * @tc.name: TestRichEditorCursorMoveLineBegin001
 * @tc.desc: test CursorMoveLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorCursorMoveLineBegin001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->caretPosition_ = 0;
    auto ret = richEditorPattern->CursorMoveLineBegin();
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step3. change parameter and call function.
     */
    richEditorPattern->caretPosition_ = 10;
    richEditorPattern->lastClickOffset_.x_ = 10.0f;
    richEditorPattern->lastClickOffset_.y_ = 20.0f;
    ret = richEditorPattern->CursorMoveLineBegin();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: TestRichEditorCalcLineEndPosition001
 * @tc.desc: test CalcLineEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorCalcLineEndPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
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
    EXPECT_EQ(richEditorPattern->CalcLineEndPosition(), 0);
}

/**
 * @tc.name: TestRichEditorCalcMoveUpPos001
 * @tc.desc: test CalcMoveUpPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorCalcMoveUpPos001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    float lmSizeOffset = 0.0f;
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->CalcMoveUpPos(lmSizeOffset);
    EXPECT_EQ(lmSizeOffset, 0.0f);
}

/**
 * @tc.name: TestRichEditorCalcLineInfoByPosition001
 * @tc.desc: test CalcLineInfoByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorCalcLineInfoByPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto ret = richEditorPattern->CalcLineInfoByPosition();
    EXPECT_EQ(ret.Height(), 0.0f);
}

/**
 * @tc.name: TestRichEditorGetTextPaintOffset001
 * @tc.desc: test GetTextPaintOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorGetTextPaintOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto ret = richEditorPattern->GetTextPaintOffset();
    EXPECT_EQ(ret.IsNegative(), false);
}

/**
 * @tc.name: TestRichEditorBeforeChangeText001
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorBeforeChangeText001, TestSize.Level1)
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
    RichEditorPattern::OperationRecord operationRecord;
    OHOS::Ace::NG::RecordType recodrType = OHOS::Ace::NG::RecordType::DEL_BACKWARD;
    auto ret = richEditorPattern->BeforeChangeText(changeValue, operationRecord, recodrType, 100);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: CalcInsertValueObj001
 * @tc.desc: test CalcInsertValueObj
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CalcInsertValueObj001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("test1");
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    it->content = u"test";
    TextInsertValueInfo info;
    richEditorPattern->UpdateSpanPosition();

    std::vector<std::pair<int, int>> testPairs;
    testPairs.push_back(std::make_pair(0, 0));
    testPairs.push_back(std::make_pair(3, 0));
    testPairs.push_back(std::make_pair(5, 1));
    for (const auto& testCase : testPairs) {
        richEditorPattern->caretPosition_ = testCase.first;
        richEditorPattern->CalcInsertValueObj(info);
        EXPECT_EQ(info.spanIndex_, testCase.second);
    }
}

/**
 * @tc.name: CalcInsertValueObj002
 * @tc.desc: test CalcInsertValueObj
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CalcInsertValueObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("test1");
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    TextInsertValueInfo info;
    it->content = u"test123\n";
    it->position = 4;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->moveLength_ = 2;
    richEditorPattern->CalcInsertValueObj(info, richEditorPattern->caretPosition_, true);
    EXPECT_EQ(info.spanIndex_, 0);
}

/**
 * @tc.name: CalcInsertValueObj003
 * @tc.desc: test CalcInsertValueObj
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CalcInsertValueObj003, TestSize.Level1)
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
 * @tc.name: UpdateChildrenOffset002
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, UpdateChildrenOffset002, TestSize.Level1)
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
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = nullptr;
    richEditorPattern->spans_.emplace_back(spanItem3);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0,
        .end = 1,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->isSpanStringMode_ = true;
    auto childNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<RichEditorPattern>(), true);
    host->AddChild(childNode1);
    childNode1->SetParent(host);
    auto childNode2 = FrameNode::CreateFrameNode("childNode", 2, AceType::MakeRefPtr<ImagePattern>());
    host->AddChild(childNode2);
    childNode2->SetParent(host);
    auto childNode3 = FrameNode::CreateFrameNode("childNode", 3, AceType::MakeRefPtr<PlaceholderSpanPattern>());
    host->AddChild(childNode3);
    childNode3->SetParent(host);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    auto imageItem = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->MountImageNode(imageItem);
    richEditorPattern->HandleOnCameraInput();
    richEditorPattern->UpdateChildrenOffset();
    EXPECT_NE(richEditorPattern->spans_.size(), 0);
}

/**
 * @tc.name: GetSelectArea001
 * @tc.desc: test GetSelectArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetSelectArea001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };
    richEditorPattern->isShowPlaceholder_ = true;
    auto res = richEditorPattern->GetSelectArea(SelectRectsType::ALL_LINES);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::LEFT_TOP_POINT);
    EXPECT_TRUE(res.IsValid());
    res = richEditorPattern->GetSelectArea(SelectRectsType::RIGHT_BOTTOM_POINT);
    EXPECT_TRUE(res.IsValid());
}

/**
 * @tc.name: RichEditorGetCrossOverHeight001
 * @tc.desc: test RichEditorGetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorGetCrossOverHeight001, TestSize.Level1)
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

    richEditorPattern->keyboardAvoidance_ = true;
    richEditorPattern->contentChange_ = true;
    auto ret = richEditorPattern->GetCrossOverHeight();
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: RichEditorDelete001
 * @tc.desc: test delete forward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 0);
}

/**
 * @tc.name: RichEditorDelete002
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(contentNode->GetChildren().size(), 0);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(6);
    EXPECT_EQ(contentNode->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDelete003
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteBackward(1);
    EXPECT_NE(static_cast<int32_t>(contentNode->GetChildren().size()), 0);
    richEditorPattern->textSelector_ = TextSelector(0, 1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(contentNode->GetChildren().size(), 0);
    while (!richEditorPattern->spans_.empty()) {
        richEditorPattern->spans_.pop_back();
    }
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(contentNode->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDelete004
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1
    ASSERT_EQ(richEditorPattern->caretPosition_, 6);

    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
    richEditorPattern->DeleteBackward(2);
    EXPECT_EQ(richEditorPattern->caretPosition_, 3);
    richEditorPattern->DeleteBackward(3);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    EXPECT_EQ(contentNode->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDelete005
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1
    ASSERT_EQ(richEditorPattern->caretPosition_, 6);
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 7);
    ASSERT_EQ(contentNode->GetChildren().size(), 2);

    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
}

/**
 * @tc.name: RichEditorDelete006
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1
    ASSERT_EQ(richEditorPattern->caretPosition_, 6);
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 8);
    ASSERT_EQ(contentNode->GetChildren().size(), 2);

    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    EXPECT_EQ(contentNode->GetChildren().size(), 1);
}

/**
 * @tc.name: RichEditorDeleteForwardEmoji
 * @tc.desc: test DeleteForward Emoji And Emoji Selected
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDeleteForwardEmoji, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("😄3😄😄");
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->textSelector_ = TextSelector(2, 5);
    richEditorPattern->DeleteForward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->DeleteForward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
}

/**
 * @tc.name: RichEditorDeleteBackwardEmoji
 * @tc.desc: test DeleteBackward Emoji And Emoji Selected
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDeleteBackwardEmoji, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("😄3😄😄");
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->textSelector_ = TextSelector(2, 5);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: GetTextSpansInfo
 * @tc.desc: test get paragraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetTextSpansInfo, TestSize.Level1)
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
    TextSpanOptions options;
    options.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options);

    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    style1.paragraphSpacing = Dimension(20.0f, DimensionUnit::PX);
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);

    auto info = richEditorController->GetSpansInfo(0, 6);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto valueString = info.selection_.resultObjects.begin()->valueString;
    auto textStyle = info.selection_.resultObjects.begin()->textStyle;

    EXPECT_EQ(textStyle.textAlign, int(TextAlign::END));
    EXPECT_EQ(textStyle.leadingMarginSize[0], "5.00px");
    EXPECT_EQ(textStyle.leadingMarginSize[1], "10.00px");
    EXPECT_TRUE(textStyle.paragraphSpacing.has_value());

    struct UpdateParagraphStyle style2;
    style2.textAlign = TextAlign::END;
    richEditorPattern->UpdateParagraphStyle(0, 6, style2);

    info = richEditorController->GetSpansInfo(0, 6);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    textStyle = info.selection_.resultObjects.begin()->textStyle;
    EXPECT_FALSE(textStyle.paragraphSpacing.has_value());
    ClearSpan();
}

/**
 * @tc.name: GetImageSpansInfo
 * @tc.desc: test image span layoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetImageSpansInfo, TestSize.Level1)
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
     * @tc.steps: step3. test add span
     */
    richEditorController->AddImageSpan(options);
    auto info = richEditorController->GetSpansInfo(0, 1);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto imageStyleout = info.selection_.resultObjects.begin()->imageStyle;
    EXPECT_EQ(imageStyleout.borderRadius,
        "{\"topLeft\":\"10.00px\",\"topRight\":\"10.00px\",\"bottomLeft\":\"10.00px\",\"bottomRight\":\"10.00px\"}");
    EXPECT_EQ(imageStyleout.margin, marginProp->ToString());
    ClearSpan();
}

/**
 * @tc.name: GetParagraphNodes001
 * @tc.desc: test get paragraph nodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto nodes = richEditorPattern->GetParagraphNodes(1, 5);
    EXPECT_EQ(nodes.size(), 0);
    nodes = richEditorPattern->GetParagraphNodes(0, INT_MAX);
    EXPECT_EQ(nodes.size(), 0);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    // add multiple paragraphs
    AddSpan(INIT_VALUE_1 + u"\n"); // length 7
    AddImageSpan();               // length 1
    AddSpan(INIT_VALUE_2 + u"\n"); // length 7
    AddSpan(INIT_VALUE_1);        // length 6
    AddSpan(INIT_VALUE_2 + u"\n");
    AddSpan(INIT_VALUE_2);
    AddSpan(INIT_VALUE_2 + u"\n");
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(contentNode->children_.size(), 8);

    nodes = richEditorPattern->GetParagraphNodes(3, 5);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), contentNode->GetChildAtIndex(0)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(0, INT_MAX);
    EXPECT_EQ(nodes.size(), 7);

    nodes = richEditorPattern->GetParagraphNodes(10, 15);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), contentNode->GetChildAtIndex(2)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(6, 7);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), contentNode->GetChildAtIndex(0)->GetId());

    // selecting only the placeholder region
    nodes = richEditorPattern->GetParagraphNodes(7, 8);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), contentNode->GetChildAtIndex(1)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(2, 20);
    EXPECT_EQ(nodes.size(), 4);
    EXPECT_EQ(nodes[3]->GetId(), contentNode->GetChildAtIndex(4)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(400, 404);
    EXPECT_EQ(nodes.size(), 0);
}

/**
 * @tc.name: GetParagraphNodes002
 * @tc.desc: test get paragraph nodes with multiple placeholders
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphNodes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    // add multiple paragraphs
    AddImageSpan(); // length 1
    AddImageSpan(); // length 1
    AddImageSpan(); // length 1

    EXPECT_EQ(contentNode->children_.size(), 3);

    auto nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_TRUE(nodes.empty());

    AddSpan(INIT_VALUE_2);

    // selecting only placeholder, should return span in the same paragraph
    nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_EQ(nodes.size(), 1);

    nodes = richEditorPattern->GetParagraphNodes(4, 6);
    EXPECT_EQ(nodes.size(), 1);
}

/**
 * @tc.name: GetParagraphNodes003
 * @tc.desc: test get paragraph nodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphNodes003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    AddSpan("0123");
    AddImageSpan();
    AddSpan("45789\n");
    AddSpan("aaaaaaaaaa");

    EXPECT_EQ(contentNode->children_.size(), 4);

    auto nodes = richEditorPattern->GetParagraphNodes(50, 52);
    EXPECT_EQ(nodes.size(), 0);

    nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_EQ(nodes.size(), 2);
}

/**
 * @tc.name: CalcSpansRange001
 * @tc.desc: test calculate spans range after get paragraph nodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CalcSpansRange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(INIT_VALUE_9);
    auto nodes = richEditorPattern->GetParagraphNodes(50, 52);
    EXPECT_EQ(nodes.size(), 0);
    auto range = richEditorPattern->CalcSpansRange(nodes);
    EXPECT_EQ(range.first, -1);
    EXPECT_EQ(range.second, -1);

    nodes = richEditorPattern->GetParagraphNodes(15, 20);
    EXPECT_EQ(nodes.size(), 1);
    range = richEditorPattern->CalcSpansRange(nodes);
    EXPECT_EQ(range.first, 11);
    EXPECT_EQ(range.second, 22);

    nodes = richEditorPattern->GetParagraphNodes(5, 25);
    EXPECT_EQ(nodes.size(), 3);
    range = richEditorPattern->CalcSpansRange(nodes);
    EXPECT_EQ(range.first, 0);
    EXPECT_EQ(range.second, 32);
}

/**
 * @tc.name: CalcSpansRange002
 * @tc.desc: test calculate spans range
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CalcSpansRange002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // all spanNodes empty
    std::vector<RefPtr<SpanNode>> spanNodes;
    spanNodes.push_back(nullptr);
    spanNodes.push_back(nullptr);
    auto range = richEditorPattern->CalcSpansRange(spanNodes);
    EXPECT_EQ(range.first, -1);
    EXPECT_EQ(range.second, -1);

    // mutiple spanNodes fisrt without spanItem
    spanNodes.clear();
    RefPtr<SpanNode> firstNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    RefPtr<SpanNode> lastNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(2);
    firstNode->spanItem_ = nullptr;
    lastNode->spanItem_->position = 10;
    spanNodes.push_back(firstNode);
    spanNodes.push_back(lastNode);
    range = richEditorPattern->CalcSpansRange(spanNodes);
    EXPECT_EQ(range.first, -1);
    EXPECT_EQ(range.second, -1);

    // mutiple spanNodes last without spanItem
    spanNodes.clear();
    firstNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(3);
    lastNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(4);
    firstNode->spanItem_->rangeStart = 5;
    lastNode->spanItem_ = nullptr;
    spanNodes.push_back(firstNode);
    spanNodes.push_back(lastNode);
    range = richEditorPattern->CalcSpansRange(spanNodes);
    EXPECT_EQ(range.first, -1);
    EXPECT_EQ(range.second, -1);
}

/**
 * @tc.name: GetParagraphLength001
 * @tc.desc: test get paragraph length
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    // Add multiple paragraphs
    auto host = richEditorPattern->GetContentHost();
    AddImageSpan(); // length 1
    auto length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 1);
    AddImageSpan();
    AddImageSpan();
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 3);
    AddSpan(INIT_VALUE_1 + u"\n"); // length 7
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 10);
    AddImageSpan();
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 11);
}

/**
 * @tc.name: GetLeftTextOfCursor001
 * @tc.desc: test GetLeftTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetLeftTextOfCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"tesol";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    auto ret = richEditorPattern->GetLeftTextOfCursor(1);
    EXPECT_EQ(ret, u"e");

    ret = richEditorPattern->GetLeftTextOfCursor(2);
    EXPECT_EQ(ret, u"e");

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = richEditorPattern->GetLeftTextOfCursor(1);
    EXPECT_EQ(ret, u"t");

    richEditorPattern->textSelector_.baseOffset = 3;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = richEditorPattern->GetLeftTextOfCursor(1);
    EXPECT_EQ(ret, u"e");
}

/**
 * @tc.name: GetLeftTextOfCursor002
 * @tc.desc: test get left text of cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetLeftTextOfCursor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto ret = richEditorPattern->GetLeftTextOfCursor(3);
    EXPECT_EQ(ret, u"");
}

/**
 * @tc.name: SetPlaceholder001
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RichEditorPattern>());
    ASSERT_NE(textframeNode, nullptr);
    host->AddChild(textframeNode);
    textframeNode->SetParent(host);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    std::vector<std::list<RefPtr<SpanItem>>> spanItemList;
    richEditorPattern->spans_.clear();
    richEditorPattern->SetPlaceholder(spanItemList);
    EXPECT_FALSE(richEditorPattern->isShowPlaceholder_);
}

/**
 * @tc.name: SetPlaceholder002
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    std::u16string value = PLACEHOLDER_TEXT;
    options.value = value;
    options.fontSize = Dimension(12.0);
    options.fontStyle = OHOS::Ace::FontStyle::ITALIC;
    options.fontWeight = FontWeight::BOLD;
    options.fontColor = Color::BLACK;
    options.fontFamilies = { "Arial", "Helvetica" };
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetPlaceholder(), value);
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder003
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder003, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    options.value = PLACEHOLDER_TEXT;
    options.fontSize = Dimension(12.0);
    options.fontStyle = OHOS::Ace::FontStyle::ITALIC;
    options.fontWeight = FontWeight::BOLD;
    options.fontColor = Color::BLACK;
    options.fontFamilies = { "Arial", "Helvetica" };
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetPlaceholderFontSize(), Dimension(12.0));
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder004
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder004, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    options.value = PLACEHOLDER_TEXT;
    options.fontSize = Dimension(12.0);
    options.fontStyle = OHOS::Ace::FontStyle::ITALIC;
    options.fontWeight = FontWeight::BOLD;
    options.fontColor = Color::BLACK;
    options.fontFamilies = { "Arial", "Helvetica" };
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetPlaceholderItalicFontStyle(), OHOS::Ace::FontStyle::ITALIC);
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder005
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder005, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    options.value = PLACEHOLDER_TEXT;
    options.fontSize = Dimension(12.0);
    options.fontStyle = OHOS::Ace::FontStyle::ITALIC;
    options.fontWeight = FontWeight::BOLD;
    options.fontColor = Color::BLACK;
    options.fontFamilies = { "Arial", "Helvetica" };
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetPlaceholderFontWeight(), FontWeight::BOLD);
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder006
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder006, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    options.value = PLACEHOLDER_TEXT;
    options.fontSize = Dimension(12.0);
    options.fontStyle = OHOS::Ace::FontStyle::ITALIC;
    options.fontWeight = FontWeight::BOLD;
    options.fontColor = Color::BLACK;
    options.fontFamilies = { "Arial", "Helvetica" };
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetPlaceholderTextColor(), Color::BLACK);
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder007
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder007, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(options.fontColor.has_value());
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder008
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder008, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(options.value.has_value());
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder009
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder009, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(options.fontSize.has_value());
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder010
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder010, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(options.fontStyle.has_value());
    frameNode.Reset();
}

/**
 * @tc.name: SetPlaceholder011
 * @tc.desc: test SetPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetPlaceholder011, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions options;
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), options);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(options.fontWeight.has_value());
    frameNode.Reset();
}

/**
 * @tc.name: IsHint001
 * @tc.desc: Test IsHint.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, IsHint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto accProp = richEditorNode_->GetAccessibilityProperty<RichEditorAccessibilityProperty>();
    ASSERT_NE(accProp, nullptr);

    EXPECT_FALSE(accProp->IsHint());

    /**
     * @tc.steps: step2. set placeholder
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 1, AceType::MakeRefPtr<RichEditorPattern>());
    PlaceholderOptions placeholder;
    placeholder.value = PLACEHOLDER_TEXT;
    RichEditorModelNG::SetPlaceholder(Referenced::RawPtr(frameNode), placeholder);
    auto textLayoutProperty = frameNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetPlaceholder(), PLACEHOLDER_TEXT);

    /**
     * @tc.steps: step3. set text span
     */
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
    EXPECT_FALSE(accProp->IsHint());
}

/**
 * @tc.name: ProvidePlaceHolderText001
 * @tc.desc: test provide placeholder information to inputmethod function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, ProvidePlaceHolderText, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = richEditorPattern->GetMiscTextConfig();
    auto textconfig = miscTextConfig.value();
    auto placeholder = UtfUtils::Str16ToStr8(textconfig.inputAttribute.placeholder).c_str();
    size_t count = 0;
    size_t i = 0;
    while (i < placeholder.size()) {
        count++;
        i += (placeholder[i] >= 0xD800 && placeholder[i] <= 0xDBFF) ? 2 : 1;
    }
    EXPECT_NE(count, 0);
#endif
}

/**
 * @tc.name: InsertValueOperation001
 * @tc.desc: test InsertValueOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, InsertValueOperation001, TestSize.Level1)
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

    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    std::u16string insertValue = u"test123";
    RichEditorPattern::OperationRecord record;

    richEditorPattern->InsertValueOperation(insertValue, &record, OperationType::DEFAULT);

    EXPECT_TRUE(richEditorPattern->typingStyle_.has_value());
}

/**
 * @tc.name: InsertValueOperation002
 * @tc.desc: test InsertValueOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, InsertValueOperation002, TestSize.Level1)
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

    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
    richEditorPattern->textSelector_.Update(0, 6);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->InsertValueOperation(INIT_VALUE_1, nullptr, OperationType::DEFAULT, false);
}

/**
 * @tc.name: ProcessInsertValue001
 * @tc.desc: test ProcessInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, ProcessInsertValue001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string insertValue = u"abc";
    richEditorPattern->isEditing_ = true;
    richEditorPattern->isSpanStringMode_ = false;
    auto size = richEditorPattern->operationRecords_.size();
    richEditorPattern->ProcessInsertValue(insertValue, OperationType::IME, true);
    EXPECT_TRUE(richEditorPattern->IsEditing());
    EXPECT_NE(size, richEditorPattern->operationRecords_.size());
}

/**
 * @tc.name: ProcessInsertValue002
 * @tc.desc: test ProcessInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, ProcessInsertValue002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::u16string insertValue = u"abc";
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->previewTextRecord_.needReplacePreviewText = true;
    richEditorPattern->ProcessInsertValue(insertValue, OperationType::DEFAULT, false);

    ASSERT_EQ(richEditorPattern->previewTextRecord_.IsValid(), false);
}

/**
 * @tc.name: TestRichEditorBeforeChangeText002
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, TestRichEditorBeforeChangeText002, TestSize.Level1)
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
 * @tc.name: BeforeChangeText001
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, BeforeChangeText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    RichEditorPattern::OperationRecord operationRecord;
    OHOS::Ace::NG::RecordType recodrType = OHOS::Ace::NG::RecordType::DEL_BACKWARD;
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    eventHub->SetOnDidChange([](const RichEditorChangeValue& value) -> bool { return false; });
    auto ret = richEditorPattern->BeforeChangeText(changeValue, operationRecord, recodrType, 100);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: BeforeChangeText002
 * @tc.desc: test BeforeChangeText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, BeforeChangeText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    TextSpanOptions options;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem);
    options.offset = -1;
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    eventHub->SetOnDidChange([](const RichEditorChangeValue& value) -> bool { return false; });
    auto ret = richEditorPattern->BeforeChangeText(changeValue, options);
    EXPECT_FALSE(richEditorPattern->spans_.empty());
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateChildrenOffset001
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, UpdateChildrenOffset001, TestSize.Level1)
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
 * @tc.name: UpdateChildrenOffset003
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, UpdateChildrenOffset003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.emplace_back();
    richEditorPattern->UpdateChildrenOffset();
    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: UpdateChildrenOffset004
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, UpdateChildrenOffset004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);

    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    richEditorPattern->isSpanStringMode_ = true;

    std::list<RefPtr<UINode>>& childrens = host->ModifyChildren();
    auto childNode2 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childrens.emplace_back(childNode2);

    richEditorPattern->UpdateChildrenOffset();
    EXPECT_TRUE(childNode2->GetSpanItem());
}

/**
 * @tc.name: UpdateChildrenOffset005
 * @tc.desc: test UpdateChildrenOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, UpdateChildrenOffset005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);

    AddSpan(INIT_VALUE_1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->isSpanStringMode_ = true;

    std::list<RefPtr<UINode>>& childrens = host->ModifyChildren();
    auto childNode2 = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childNode2->imageSpanItem_ = nullptr;
    childrens.emplace_back(childNode2);

    richEditorPattern->UpdateChildrenOffset();
    EXPECT_FALSE(childNode2->GetSpanItem());
}

} // namespace OHOS::Ace::NG