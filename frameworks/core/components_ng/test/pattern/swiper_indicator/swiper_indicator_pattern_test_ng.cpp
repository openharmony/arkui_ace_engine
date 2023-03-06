/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#define protected public
#define private public
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_pattern.h"
#undef private
#undef protected
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double SWIPER_INDICATOR_SIZE = 100.0;
constexpr double SWIPER_INDICATOR_SIZE_MINUS = -1000.0;
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
} // namespace
class SwiperIndicatorPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

    void SetUp() override;
    void TearDown() override;

protected:
};

void SwiperIndicatorPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SwiperIndicatorPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void SwiperIndicatorPatternTestNg::SetUp() {}

void SwiperIndicatorPatternTestNg::TearDown() {}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::HORIZONTAL);
    EXPECT_FALSE(controller == nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<SwiperIndicatorPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure002
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    mode.SetDirection(Axis::VERTICAL);
    auto controller = mode.Create();
    EXPECT_FALSE(controller == nullptr);

    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    auto swiperIndicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_FALSE(swiperPattern == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<SwiperIndicatorPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    paintProperty->UpdateSize(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    auto swiperIndicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateLeft(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(100.00, 568.00));
    layoutProperty->Reset();
    EXPECT_FALSE(layoutProperty->Clone() == nullptr);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::HORIZONTAL);
    EXPECT_FALSE(controller == nullptr);

    auto pipeline = MockPipelineBase::GetCurrent();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    CHECK_NULL_VOID(pipeline);
    auto swiperIndicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateRight(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty right is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout003
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::HORIZONTAL);
    EXPECT_FALSE(controller == nullptr);

    auto pipeline = MockPipelineBase::GetCurrent();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    CHECK_NULL_VOID(pipeline);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateRight(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout004
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateTop(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty top is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 100.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout005
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateBottom(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty bottom is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 1036.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout006
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(algorithm == nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 568.00));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    RefPtr<SwiperIndicatorLayoutAlgorithm> algorithm =
        AceType::DynamicCast<SwiperIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(algorithm == nullptr);

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.7, DimensionUnit::PERCENT)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.5, DimensionUnit::PERCENT)), 50.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 20.0, Dimension(0.0, DimensionUnit::PERCENT)), 0.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(70.0, DimensionUnit::PX)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(-10.0, 40.0, Dimension(-20.0, DimensionUnit::PX)), 0.0);
}

/**
 * @tc.name: SwiperIndicatorOnAttachToFrameNodeTest001
 * @tc.desc: Test SwiperIndicator OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorOnAttachToFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    /**
     * @tc.steps: step2. Create theme manager and set theme
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);
    indicatorPattern->OnAttachToFrameNode();

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
}

/**
 * @tc.name: SwiperIndicatorOnModifyDone001
 * @tc.desc: Test SwiperIndicator OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorOnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);
    indicatorPattern->OnModifyDone();

    DirtySwapConfig config;
    config.frameSizeChange = false;
    EXPECT_FALSE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
    config.frameSizeChange = true;
    EXPECT_TRUE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
}

/**
 * @tc.name: SwiperIndicatorInitClickEvent001
 * @tc.desc: Test SwiperIndicator InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorInitClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    indicatorPattern->clickEvent_ = nullptr;
    RefPtr<GestureEventHub> gestureHub = frameNode->GetOrCreateGestureEventHub();
    indicatorPattern->InitClickEvent(gestureHub);
    indicatorPattern->InitClickEvent(gestureHub);
    gestureHub->ActClick();
}

/**
 * @tc.name: SwiperIndicatorHandleClick001
 * @tc.desc: Test SwiperIndicator HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorHandleClick001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(Axis::VERTICAL);
    EXPECT_FALSE(controller == nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    EXPECT_FALSE(indicatorNode == nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    EXPECT_FALSE(indicatorPattern == nullptr);

    GestureEvent info;
    auto paintProperty = indicatorNode->GetPaintProperty<SwiperIndicatorPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    indicatorPattern->HandleClick(info);
}
} // namespace OHOS::Ace::NG