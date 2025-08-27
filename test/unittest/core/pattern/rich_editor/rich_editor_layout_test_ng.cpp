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
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const Dimension MIN_WIDTH = 100.0_px;
    const Dimension MIN_HEIGHT = 50.0_px;
    const Dimension MAX_WIDTH = 200.0_px;
    const Dimension MAX_HEIGHT = 150.0_px;
} // namespace
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
    CHECK_NULL_VOID(richEditorNode_);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
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

    AddSpan(EMPTY_STRING);
    AddSpan(INIT_VALUE_1);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    parentLayoutConstraint.selfIdealSize.SetHeight(std::nullopt);
    parentLayoutConstraint.selfIdealSize.SetWidth(1.0f);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    auto paragraphManager = AceType::MakeRefPtr<ParagraphManager>();
    layoutAlgorithm->paragraphManager_ = paragraphManager;

    ParagraphStyle testStyle = {};
    EXPECT_CALL(*paragraph, GetParagraphStyle()).WillRepeatedly(ReturnRef(testStyle));
    layoutAlgorithm->spans_.emplace_back(richEditorPattern->spans_);
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));

    ASSERT_NE(layoutAlgorithm->spans_.size(), 0);
    for (const auto& group : layoutAlgorithm->spans_) {
        for (const auto& child : group) {
            if (!child) {
                continue;
            }
            child->ResetReLayout();
            child->MarkReCreateParagraph();
        }
    }
    auto size = layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    EXPECT_NE(size.value().Width(), 1.0f);
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
 * @tc.name: UpdateFrameSizeWithLayoutPolicy001
 * @tc.desc: test LayoutPolicy MATCH_PARENT
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, UpdateFrameSizeWithLayoutPolicy001, TestSize.Level1)
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
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();

    auto frameSize = CONTAINER_SIZE;
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize, CONTAINER_SIZE);

    layoutProperty->calcLayoutConstraint_->minSize = CalcSize{ CalcLength(MIN_WIDTH), CalcLength(MIN_HEIGHT) };
    layoutProperty->calcLayoutConstraint_->maxSize = CalcSize{ CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize, CONTAINER_SIZE);
}

/**
 * @tc.name: UpdateFrameSizeWithLayoutPolicy002
 * @tc.desc: test LayoutPolicy WRAP_CONTENT and FIX_AT_IDEAL_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, UpdateFrameSizeWithLayoutPolicy002, TestSize.Level1)
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
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto contentSize = SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT);
    layoutWrapper->GetGeometryNode()->SetContentSize(contentSize);

    auto frameSize = CONTAINER_SIZE;
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize, contentSize);

    frameSize = CONTAINER_SIZE;
    layoutProperty->layoutPolicy_->widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_->heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize, contentSize);

    layoutProperty->calcLayoutConstraint_->minSize = CalcSize{ CalcLength(MIN_WIDTH), CalcLength(MIN_HEIGHT) };
    layoutProperty->calcLayoutConstraint_->maxSize = CalcSize{ CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize.Width(), static_cast<float>(MAX_WIDTH.ConvertToPx()));
    EXPECT_EQ(frameSize.Height(), static_cast<float>(MAX_HEIGHT.ConvertToPx()));

    frameSize = CONTAINER_SIZE;
    layoutProperty->layoutPolicy_->widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_->heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->calcLayoutConstraint_->minSize = CalcSize{ CalcLength(MIN_WIDTH), CalcLength(MIN_HEIGHT) };
    layoutProperty->calcLayoutConstraint_->maxSize = CalcSize{ CalcLength(MAX_WIDTH), CalcLength(MAX_HEIGHT) };
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize.Width(), static_cast<float>(MAX_WIDTH.ConvertToPx()));
    EXPECT_EQ(frameSize.Height(), static_cast<float>(MAX_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: UpdateFrameSizeWithLayoutPolicy003
 * @tc.desc: test LayoutPolicy WRAP_CONTENT and FIX_AT_IDEAL_SIZE with calcLayoutConstraint is nullPtr
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, UpdateFrameSizeWithLayoutPolicy003, TestSize.Level1)
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
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    layoutProperty->calcLayoutConstraint_ = nullptr;
    auto contentSize = SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT);
    layoutWrapper->GetGeometryNode()->SetContentSize(contentSize);

    auto frameSize = CONTAINER_SIZE;
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize, contentSize);

    frameSize = CONTAINER_SIZE;
    layoutProperty->layoutPolicy_->widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_->heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutAlgorithm->UpdateFrameSizeWithLayoutPolicy(AceType::RawPtr(layoutWrapper), frameSize);
    EXPECT_EQ(frameSize, contentSize);
}

/**
 * @tc.name: UpdateConstraintByLayoutPolicy
 * @tc.desc: test UpdateConstraintByLayoutPolicy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, UpdateConstraintByLayoutPolicy, TestSize.Level1)
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
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    LayoutPolicyProperty layoutPolicyProperty;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    auto contentSize = SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT);
    layoutAlgorithm->UpdateConstraintByLayoutPolicy(contentSize, parentLayoutConstraint,
        AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(parentLayoutConstraint.maxSize.Height(), CONTAINER_SIZE.Height());

    layoutProperty->layoutPolicy_->heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutAlgorithm->UpdateConstraintByLayoutPolicy(contentSize, parentLayoutConstraint,
        AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(parentLayoutConstraint.maxSize.Height(), CONTAINER_HEIGHT);

    CalcSize maxSize{ CalcLength(1.0), CalcLength(1.0) };
    MeasureProperty constraint;
    constraint.maxSize = maxSize;
    layoutProperty->UpdateCalcLayoutProperty(constraint);
    layoutAlgorithm->UpdateConstraintByLayoutPolicy(contentSize, parentLayoutConstraint,
        AceType::RawPtr(layoutWrapper));
    EXPECT_NE(parentLayoutConstraint.maxSize.Height(), CONTAINER_HEIGHT);
}

/**
 * @tc.name: UpdateMaxSizeByLayoutPolicy
 * @tc.desc: test UpdateMaxSizeByLayoutPolicy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, UpdateMaxSizeByLayoutPolicy, TestSize.Level1)
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
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT);
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    LayoutPolicyProperty layoutPolicyProperty;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;

    auto maxSize = parentLayoutConstraint.maxSize;
    layoutAlgorithm->UpdateMaxSizeByLayoutPolicy(parentLayoutConstraint, AceType::RawPtr(layoutWrapper), maxSize);
    EXPECT_EQ(maxSize.Width(), CONTAINER_WIDTH);

    layoutProperty->layoutPolicy_->widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutAlgorithm->UpdateMaxSizeByLayoutPolicy(parentLayoutConstraint, AceType::RawPtr(layoutWrapper), maxSize);
    EXPECT_EQ(maxSize.Width(), CONTAINER_WIDTH);

    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    maxSize = parentLayoutConstraint.maxSize;
    layoutAlgorithm->UpdateMaxSizeByLayoutPolicy(parentLayoutConstraint, AceType::RawPtr(layoutWrapper), maxSize);
    EXPECT_EQ(maxSize.Width(), std::numeric_limits<float>::max());
}

/**
 * @tc.name: HandleAISpanTest001
 * @tc.desc: test HandleAISpanTest
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, HandleAISpanTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    std::list<RefPtr<SpanItem>> spans;
    auto spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1->rangeStart = 0;
    spanItem1->position = 5;

    auto spanItem2 = AceType::MakeRefPtr<SpanItem>();
    spanItem2->rangeStart = 5;
    spanItem2->position = 10;

    auto spanItem3 = AceType::MakeRefPtr<SpanItem>();
    spanItem3->rangeStart = 10;
    spanItem3->position = 15;

    spans.push_back(spanItem1);
    spans.push_back(spanItem2);
    spans.push_back(spanItem3);

    std::map<int32_t, AISpan> aiSpanMap = { { 8, { 8, 12 } } };
    AISpanLayoutInfo aiSpanLayoutInfo{ aiSpanMap, true };
    // span:[0-5][5-10][10-15]
    layoutAlgorithm->HandleAISpan(spans, aiSpanLayoutInfo);
    EXPECT_EQ(spanItem1->aiSpanResultCount, 0);
    EXPECT_EQ(spanItem2->aiSpanResultCount, 1);
    EXPECT_EQ(spanItem3->aiSpanResultCount, 1);

    EXPECT_EQ(spanItem1->needReLayout, false);
    EXPECT_EQ(spanItem2->needReLayout, true);
    EXPECT_EQ(spanItem3->needReLayout, true);
}

/**
 * @tc.name: UpdateTextFieldManager001
 * @tc.desc: test RichEditorPattern UpdateTextFieldManager
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, UpdateTextFieldManager001, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdatePreviewTextStyle("underline");
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    /**
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    richEditorPattern->ShowHandles(true);
    richEditorPattern->ShowHandles(false);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    RichEditorTheme richEditorTheme;
    EXPECT_EQ(richEditorPattern->GetPreviewTextDecorationColor(), richEditorTheme.GetPreviewUnderLineColor());

    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    MockPipelineContext::GetCurrent()->SetRootSize(800, 2000);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);

    Offset Offset = { 1, 4 };
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);

    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), true);
}

/**
 * @tc.name: UpdateTextFieldManager002
 * @tc.desc: test UpdateTextFieldManager
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, UpdateTextFieldManager002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    context->SetTextFieldManager(textFieldManager);

    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    context->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_NE(textFieldManager->GetOnFocusTextField().Upgrade(), nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
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
 * @tc.name: RichEditorLayoutAlgorithmTest001
 * @tc.desc: test RichEditorLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, RichEditorLayoutAlgorithmTest001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    std::list<RefPtr<SpanItem>> spanList1;
    spanList1.push_back(AceType::MakeRefPtr<SpanItem>());
    spanList1.push_back(AceType::MakeRefPtr<SpanItem>());
    uint64_t hash1 = layoutAlgorithm->Hash(spanList1);

    std::list<RefPtr<SpanItem>> spanList2;
    spanList2.push_back(AceType::MakeRefPtr<SpanItem>());
    spanList2.push_back(AceType::MakeRefPtr<SpanItem>());
    uint64_t hash2 = layoutAlgorithm->Hash(spanList2);

    EXPECT_NE(hash1, hash2);
}

/**
 * @tc.name: RichEditorLayoutAlgorithmTest002
 * @tc.desc: test RichEditorLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorLayoutTestNg, RichEditorLayoutAlgorithmTest002, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    SizeF textSize;
    ASSERT_EQ(textSize.Width(), 0.0f);
    layoutAlgorithm->allSpans_.clear();
    layoutAlgorithm->HandleTextSizeWhenEmpty(AceType::RawPtr(layoutWrapper), textSize);
    EXPECT_NE(textSize.Width(), 0.0f);
}

} // namespace OHOS::Ace::NG
