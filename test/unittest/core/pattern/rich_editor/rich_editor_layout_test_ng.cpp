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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorLayoutTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorLayoutTestNg::SetUp()
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

void RichEditorLayoutTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorLayoutTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}


/**
 * @tc.name: OnDirtyLayoutWrapper001
 * @tc.desc: test on dirty layout wrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, OnDirtyLayoutWrapper001, TestSize.Level1)
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
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
    richEditorPattern->isRichEditorInit_ = true;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);

    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = -1;
    ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}


/**
 * @tc.name: OnDirtyLayoutWrapper002
 * @tc.desc: test on dirty layout wrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, OnDirtyLayoutWrapper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create richEditorPattern.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. create layoutWrapper and config.
     */
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    config.skipMeasure = true;

    /**
     * @tc.steps: step3. set currentFocus_ true and test OnDirtyLayoutWrapperSwap.
     */
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step4. change scene and test OnDirtyLayoutWrapperSwap.
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
    richEditorPattern->isShowMenu_ = true;
    ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);

    richEditorPattern->textSelector_ = TextSelector(-1, -1);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(true);

    richEditorNode_->GetGeometryNode()->SetContentSize(SizeF(BUILDER_WIDTH, BUILDER_HEIGHT));
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 70.0, 70.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}


/**
 * @tc.name: OnDirtyLayoutWrapper003
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, OnDirtyLayoutWrapper003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto rendenContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(rendenContext, nullptr);
    rendenContext->UpdateClipEdge(false);
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto globalOffset = OffsetF(15.0f, 3.0f);
    geometryNode->SetFrameSize(SizeF(20.0f, 5.0f));
    geometryNode->SetFrameOffset(globalOffset);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->parentGlobalOffset_ = globalOffset;
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    richEditorPattern->baselineOffset_ = 6.0f;
    richEditorPattern->CreateNodePaintMethod();
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}


/**
 * @tc.name: OnDirtyLayoutWrapper004
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, OnDirtyLayoutWrapper004, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto rendenContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(rendenContext, nullptr);
    rendenContext->ResetClipEdge();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    richEditorPattern->isModifyingContent_ = true;
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}


/**
 * @tc.name: RichEditorLayoutAlgorithm001
 * @tc.desc: test MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, RichEditorLayoutAlgorithm001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    parentLayoutConstraint.selfIdealSize.SetHeight(std::nullopt);
    parentLayoutConstraint.selfIdealSize.SetWidth(1.0f);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    auto paragraphManager = AceType::MakeRefPtr<ParagraphManager>();
    layoutAlgorithm->paragraphManager_ = paragraphManager;

    AddSpan(INIT_VALUE_1);
    layoutAlgorithm->spans_.emplace_back(richEditorPattern->spans_);
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));

    layoutAlgorithm->spans_.clear();
    auto size1 = layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(size1.value().Width(), 1.0f);

    richEditorPattern->presetParagraph_ = paragraph;
    auto size2 = layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(size2.value().Width(), 1.0f);
}

/**
 * @tc.name: RichEditorLayoutAlgorithm002
 * @tc.desc: test GetParagraphStyleSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, RichEditorLayoutAlgorithm002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    std::list<RefPtr<SpanItem>> spanGroup;
    spanGroup.clear();
    spanGroup.emplace_back(AceType::MakeRefPtr<PlaceholderSpanItem>());
    auto span = layoutAlgorithm->GetParagraphStyleSpanItem(spanGroup);
    EXPECT_EQ(*spanGroup.begin(), span);
}

/**
 * @tc.name: RichEditorLayoutAlgorithm003
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, RichEditorLayoutAlgorithm003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(10.0f, 1000.0f);
    layoutConstraint.minSize = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), 720.0f);
}

/**
 * @tc.name: RichEditorLayoutAlgorithm004
 * @tc.desc: test RichEditorLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, RichEditorLayoutAlgorithm004, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    auto paragraphManager = AceType::MakeRefPtr<ParagraphManager>();
    auto placeholderSpanItem = AceType::MakeRefPtr<PlaceholderSpanItem>();
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::u16string str = u"\n";
    spanItem->content = str;
    spans.emplace_back(spanItem);
    auto layoutAlgorithm = AceType::MakeRefPtr<RichEditorLayoutAlgorithm>(spans, AceType::RawPtr(paragraphManager),
        std::nullopt);
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_NE(*(layoutAlgorithm->allSpans_.begin()), nullptr);
}
} // namespace OHOS::Ace::NG
