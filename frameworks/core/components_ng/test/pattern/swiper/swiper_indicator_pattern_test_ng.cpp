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
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"
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
constexpr double SWIPER_INDEX_ONE = 1.0;
constexpr double SWIPER_INDEX_ZERO = 0.0;
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
const OffsetF MARGIN_OFFSET = OffsetF(50.0, 60.0);
constexpr float CONTEXT_WIDTH = 100.0f;
constexpr float CONTEXT_HEIGHT = 100.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ITEM_WIDTH = 20.0f;
constexpr float ITEM_HEIGHT = 10.0f;
constexpr float ITEM_HEIGHT_LARGE = 25.0f;
constexpr float SELECTED_ITEM_WIDTH = 30.0f;
constexpr float SELECTED_ITEM_HEIGHT = 15.0f;
constexpr float SELECTED_ITEM_HEIGHT_LARGE = 35.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::pair<float, float>& LONG_POINT_CENTER_X = { 0, 0 };
static Axis indicatorDirection_;
static SwiperIndicatorType indicatorType_;
constexpr int32_t SWIPER_ITEMCOUNT = 10;
constexpr int32_t SWIPER_HOVERINDEX = 10;
constexpr int32_t SWIPER_CURRENTINDEX = 10;
constexpr int32_t SWIPER_MOUSECLICKINDEX = 5;
const SizeF SWIPER_CHILD_SIZEF_SMALL = SizeF(20.0, 20.0);
const SizeF SWIPER_CHILD_SIZEF_BIG = SizeF(30.0, 30.0);
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;
} // namespace
class SwiperIndicatorPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void CommomAttrInfo();
    void SetUp() override;
    void TearDown() override;
    void InitLayoutWrapper(const RefPtr<FrameNode>& frameNode, RefPtr<LayoutAlgorithm>& algorithm,
        RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapper>& layoutWrapper);
    void InitChild(RefPtr<LayoutWrapper>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode);

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

void SwiperIndicatorPatternTestNg::CommomAttrInfo()
{
    /**
    * @tc.steps: step1. Init Swiper node
     */
    SwiperModelNG mode;
    auto controller = mode.Create();
    mode.SetDirection(indicatorDirection_);
    ASSERT_NE(controller, nullptr);
    mode.SetIndicatorType(indicatorType_);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));
}

void SwiperIndicatorPatternTestNg::InitLayoutWrapper(const RefPtr<FrameNode>& frameNode,
    RefPtr<LayoutAlgorithm>& algorithm, RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapper>& layoutWrapper)
{
    indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
}

void SwiperIndicatorPatternTestNg::InitChild(
    RefPtr<LayoutWrapper>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode)
{
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    indicatorNodeWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapper> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(lastLayoutWrapper);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    indicatorNodeWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
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
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLeft(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(100.00, 568.00));
    layoutProperty->Reset();
    ASSERT_NE(layoutProperty->Clone(), nullptr);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateRight(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty right is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateRight(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTop(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty top is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateBottom(Dimension(SWIPER_INDICATOR_SIZE, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty bottom is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    RefPtr<DotIndicatorLayoutAlgorithm> algorithm =
        AceType::DynamicCast<DotIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create theme manager and set theme
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

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
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    GestureEvent info;
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    indicatorPattern->HandleClick(info);
}

/**
 * @tc.name: SwiperIndicatorGetContentModifier001
 * @tc.desc: Test SwiperIndicator GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorGetContentModifier001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper and GetContentModifier.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod =
        AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    /**
     * @tc.steps: step3. call GetContentModifier.
     */
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper);
    RefPtr<Modifier> ptrModifier = paintMethod->GetContentModifier(&paintWrapper);
    ASSERT_NE(ptrModifier, nullptr);
}

/**
 * @tc.name: SelectedFontSize001
 * @tc.desc: Test SwiperIndicator SelectedFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedFontSize001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. SelectedFontSize is 14.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step4. SelectedFontSize is 60.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = 60.0_px;
    layoutProperty->UpdateSelectedFontSize(fontSize);
    indicatorPattern->OnModifyDone();
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 60);
}

/**
 * @tc.name: SelectedFontSize002
 * @tc.desc: Test SwiperIndicator SelectedFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedFontSize002, TestSize.Level2)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);

    /**
     * @tc.steps: step4. SelectedFontSize is -1.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = -1.0_px;
    layoutProperty->UpdateSelectedFontSize(fontSize);
    indicatorPattern->OnModifyDone();
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);
}

/**
 * @tc.name: FontSize001
 * @tc.desc: Test SwiperIndicator FontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, FontSize001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. FontSize is 14.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);
    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step3. FontSize is 30.
     */

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = 30.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 30);
}

/**
 * @tc.name: FontSize002
 * @tc.desc: Test SwiperIndicator FontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, FontSize002, TestSize.Level2)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. FontSize is -10.
     */

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    Dimension fontSize = -10.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);
}

/**
 * @tc.name: FontColor001
 * @tc.desc: Test SwiperIndicator FontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, FontColor001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. FontColor is 0xff000000.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);

    /**
     * @tc.steps: step3. FontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontColor(Color::WHITE);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xffffffff);
}

/**
 * @tc.name: FontColor002
 * @tc.desc: Test SwiperIndicator FontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, FontColor002, TestSize.Level2)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. FontColor is 0xff00ff00.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontColor(Color());
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);
}

/**
 * @tc.name: SelectedFontColor001
 * @tc.desc: Test SwiperIndicator SelectedFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedFontColor001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. SelectedFontColor001 is 0xff000000.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);

    /**
     * @tc.steps: step4. SelectedFontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSelectedFontColor(Color::WHITE);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xffffffff);
}

/**
 * @tc.name: SelectedFontColor002
 * @tc.desc: Test SwiperIndicator SelectedFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedFontColor002, TestSize.Level2)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    /**
     * @tc.steps: step3. SelectedFontColor is Color().
     */
    layoutProperty->UpdateSelectedFontColor(Color());
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);
}

/**
 * @tc.name: FontWeight001
 * @tc.desc: Test SwiperIndicator FontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, FontWeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. FontWeight is NORMAL.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(backTextFrameNode, nullptr);
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    ASSERT_NE(backTextLayoutProperty, nullptr);
    EXPECT_EQ(backTextLayoutProperty->GetFontWeight(), FontWeight::NORMAL);
    /**
     * @tc.steps: step3. FontWeight is BOLDER.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontWeight(FontWeight::BOLDER);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetFontWeight(), FontWeight::BOLDER);
}

/**
 * @tc.name: SelectedFontWeight001
 * @tc.desc: Test SwiperIndicator SelectedFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedFontWeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    /**
     * @tc.steps: step3. SelectedFontWeight is NORMAL.
     */
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    swiperEventHub->FireIndicatorChangeEvent(0);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(frontTextFrameNode, nullptr);
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    ASSERT_NE(frontTextLayoutProperty, nullptr);
    EXPECT_EQ(frontTextLayoutProperty->GetFontWeight(), FontWeight::NORMAL);
    /**
     * @tc.steps: step3. SelectedFontWeight is MEDIUM.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSelectedFontWeight(FontWeight::MEDIUM);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetFontWeight(), FontWeight::MEDIUM);
}

/**
 * @tc.name: ItemWidth001
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, ItemWidth001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemWidth002
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, ItemWidth002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemWidth(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight001
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, ItemHeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight002
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, ItemHeight002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemHeight(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth001
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedItemWidth001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth002
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedItemWidth002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemWidth(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight001
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedItemHeight001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight002
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SelectedItemHeight002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);
    frameNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedItemHeight(Dimension(SWIPER_INDICATOR_SIZE_MINUS, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout001
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperLayoutAlgorithmLayout001, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    ASSERT_NE(indicatorNodeWrapper, nullptr);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 327.0, 1106.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(327.0, 1106.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout002
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperLayoutAlgorithmLayout002, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 654.0, 553.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(654.0, 553.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout003
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperLayoutAlgorithmLayout003, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    Dimension dimension = 20.0_vp;
    swiperLayoutProperty->UpdateLeft(dimension);
    swiperLayoutProperty->UpdateTop(dimension);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 20.0, 20.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(20.0, 20.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout004
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperLayoutAlgorithmLayout004, TestSize.Level1)
{
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapper> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    auto swiperPatternAlgorithm = swiperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    swiperLayoutProperty->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    Dimension dimension = 20.0_vp;
    swiperLayoutProperty->UpdateRight(dimension);
    swiperLayoutProperty->UpdateBottom(dimension);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapper swiperLayoutWrapper = LayoutWrapper(swiperNode, geometryNode, swiperLayoutProperty);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 634.0, 1086.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(634.0, 1086.0));
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorUpdateContentModifier001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper and GetContentModifier.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isPressed_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isPressed_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorUpdateContentModifier002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper and GetContentModifier.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorPaintNormalIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(ITEM_HEIGHT, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(SELECTED_ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(SELECTED_ITEM_HEIGHT, DimensionUnit::PX));

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 336.0
     *               paintMethod->normalMargin_.Y is 547.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 336.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 547.5);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorPaintNormalIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(ITEM_HEIGHT, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(SELECTED_ITEM_WIDTH, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(SELECTED_ITEM_HEIGHT, DimensionUnit::PX));

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = SWIPER_ITEMCOUNT;

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 196.0
     *               paintMethod->normalMargin_.Y is 547.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 196.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 547.5);
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorPaintPressIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: paintMethod->dotIndicatorModifier_ is true.
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorPaintPressIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemHeight(Dimension(ITEM_HEIGHT, DimensionUnit::PX));
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = SWIPER_ITEMCOUNT;

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: itemHalfSizes_->Get()[1] is 6.65 .
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(
        paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[1], ITEM_HEIGHT * 0.5 * INDICATOR_ZOOM_IN_SCALE));
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorPaintHoverIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = SWIPER_HOVERINDEX;
    paintMethod->currentIndex_ = SWIPER_CURRENTINDEX;
    paintMethod->mouseClickIndex_ = SWIPER_MOUSECLICKINDEX;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(SWIPER_MOUSECLICKINDEX);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: dotIndicatorModifier_->GetIsPressed is false.
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorPaintHoverIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create PaintWrapper.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemWidth(Dimension(ITEM_WIDTH, DimensionUnit::PX));
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: itemHalfSizes_->Get()[0] is 13.30 .
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(
        paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[0], ITEM_WIDTH * 0.5 * INDICATOR_ZOOM_IN_SCALE));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapper> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 30.00));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    indicatorPattern->OnModifyDone();

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapper> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00));
    EXPECT_EQ(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00));
}

/**
 * @tc.name: SwiperIndicatorHandleClick002
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorHandleClick002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    frameNode->AddChild(swiperNode);

    auto swiperNodeTwo = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNodeTwo, nullptr);
    frameNode->AddChild(swiperNodeTwo);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateItemWidth(Dimension(10, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10, DimensionUnit::PX));
    indicatorPattern->mouseClickIndex_ = SWIPER_MOUSECLICKINDEX;
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->indicatorDoingAnimation_ = false;
    swiperPattern->currentIndex_ = 10;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: swiperPattern->indicatorDoingAnimation_ is true.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_TRUE(swiperPattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperIndicatorHandleClick003
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperIndicatorHandleClick003, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    swiperPattern->indicatorDoingAnimation_ = true;

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: swiperPattern->indicatorDoingAnimation_ is false.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(swiperPattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperInitIndicator001
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperInitIndicator001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator002
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperInitIndicator002, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);
    auto layoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode->GetLastChild is nullptr.
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild(), nullptr);
}

/**
 * @tc.name: SwiperInitIndicator003
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperInitIndicator003, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    swiperNode->AddChild(textNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator004
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperInitIndicator004, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    swiperNode->AddChild(textNode);
    auto layoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is TEXT_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator005
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperInitIndicator005, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperNode = swiperPattern->GetHost();
    ASSERT_NE(swiperNode, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: swiperNode lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SetDotIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDotIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SetDotIndicatorStyle001, TestSize.Level1)
{
    SwiperModelNG mode;
    auto controller = mode.Create();
    ASSERT_NE(controller, nullptr);
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperNode, nullptr);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call SetDotIndicatorStyle.
     * @tc.expected: swiperParameters_ colorVal is swiperParameters colorVal
     */
    mode.SetDotIndicatorStyle(swiperParameters);
    ASSERT_EQ(pattern->swiperParameters_->colorVal, swiperParameters.colorVal);
}

/**
 * @tc.name: SetDigitIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDigitIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SetDigitIndicatorStyle001, TestSize.Level1)
{
    SwiperModelNG mode;
    auto controller = mode.Create();
    ASSERT_NE(controller, nullptr);
    SwiperDigitalParameters digitalParameters;
    digitalParameters.fontColor = Color(Color::GREEN);

    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperNode, nullptr);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call SetDigitIndicatorStyle.
     * @tc.expected: swiperDigitalParameters_ fontColor is digitalParameters fontColor
     */
    mode.SetDigitIndicatorStyle(digitalParameters);
    ASSERT_EQ(pattern->swiperDigitalParameters_->fontColor, digitalParameters.fontColor);
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test DigitIndicatorLayoutAlgorithm SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create LayoutWrapper and set SwiperLayoutAlgorithm.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);

    frameNode->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);

    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNode children is empty.
     */
    algorithm->Layout(&layoutWrapper);
    auto hostNode = layoutWrapper.GetHostNode();
    ASSERT_NE(hostNode, nullptr);
    auto children = hostNode->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: DotIndicatorModifier001
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, DotIndicatorModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DotIndicatorModifier. Update PaintProperty.Call the function onDraw.
     * @tc.expected: step1. Check the PaintProperty update success.
     */
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(ITEM_WIDTH);
    LinearVector<float> normalItemHalfSizes;
    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT == SELECTED_ITEM_HALF_HEIGHT.
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);
    normalItemHalfSizes.emplace_back(ITEM_WIDTH);

    dotIndicatorModifier.UpdateShrinkPaintProperty(
        MARGIN_OFFSET, normalItemHalfSizes, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[2] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is ITEM_WIDTH.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], ITEM_WIDTH);

    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT < SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    LinearVector<float> normalItemHalfSizesSecond;
    normalItemHalfSizesSecond.emplace_back(ITEM_WIDTH);
    normalItemHalfSizesSecond.emplace_back(ITEM_HEIGHT_LARGE);
    normalItemHalfSizesSecond.emplace_back(ITEM_WIDTH);
    normalItemHalfSizesSecond.emplace_back(SELECTED_ITEM_HEIGHT);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        MARGIN_OFFSET, normalItemHalfSizesSecond, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT_LARGE.
     *               itemHalfSizes_->Get()[2] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT_LARGE);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT);
}

/**
 * @tc.name: DotIndicatorModifier002
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, DotIndicatorModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DotIndicatorModifier. Update PaintProperty.Call the function onDraw.
     * @tc.expected: step1. Check the PaintProperty update success.
     */
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(ITEM_WIDTH);

    // ITEM_HALF_WIDTH != SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT > SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ONE;
    LinearVector<float> normalItemHalfSizesThird;
    normalItemHalfSizesThird.emplace_back(ITEM_WIDTH);
    normalItemHalfSizesThird.emplace_back(ITEM_HEIGHT);
    normalItemHalfSizesThird.emplace_back(SELECTED_ITEM_WIDTH);
    normalItemHalfSizesThird.emplace_back(SELECTED_ITEM_HEIGHT_LARGE);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        MARGIN_OFFSET, normalItemHalfSizesThird, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT.
     *               itemHalfSizes_->Get()[2] is SELECTED_ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT_LARGE.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], SELECTED_ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT_LARGE);
}

/**
 * @tc.name: DotIndicatorModifier003
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorPatternTestNg, DotIndicatorModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DotIndicatorModifier. Update PaintProperty.Call the function onDraw.
     * @tc.expected: step1. Check the PaintProperty update success.
     */
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, CONTEXT_WIDTH, CONTEXT_HEIGHT };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ZERO;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(ITEM_WIDTH);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = SWIPER_INDEX_ONE;
    dotIndicatorModifier.hoverToNormalIndex_ = SWIPER_INDEX_ONE;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(ITEM_WIDTH);
    itemHalfSizes.emplace_back(ITEM_HEIGHT);
    itemHalfSizes.emplace_back(SELECTED_ITEM_WIDTH);
    itemHalfSizes.emplace_back(SELECTED_ITEM_HEIGHT_LARGE);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT.
     *               itemHalfSizes_->Get()[2] is SELECTED_ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT_LARGE.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], SELECTED_ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT_LARGE);
    // call the UpdateHoverPaintProperty to set property.
    dotIndicatorModifier.UpdateHoverPaintProperty(itemHalfSizes, vectorBlackPointCenterX, LONG_POINT_CENTER_X);
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is ITEM_WIDTH.
     *               itemHalfSizes_->Get()[1] is ITEM_HEIGHT.
     *               itemHalfSizes_->Get()[2] is SELECTED_ITEM_WIDTH.
     *               itemHalfSizes_->Get()[3] is SELECTED_ITEM_HEIGHT_LARGE.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], ITEM_HEIGHT);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], SELECTED_ITEM_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], SELECTED_ITEM_HEIGHT_LARGE);
}
} // namespace OHOS::Ace::NG