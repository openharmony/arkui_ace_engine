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
int32_t testNumber0 = 0;
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