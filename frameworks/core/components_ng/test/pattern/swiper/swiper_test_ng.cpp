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

#include <cstddef>

#include "gtest/gtest.h"

#include "core/components/common/layout/constants.h"
#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected
#include "test/mock/core/common/mock_container.h"

#include "core/animation/animator.h"
#include "core/animation/spring_curve.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_IDEAL_WIDTH = 720.0f;
constexpr float SWIPER_IDEAL_HEIGHT = 1200.0f;
constexpr int32_t CURRENT_INDEX = 1;
constexpr int32_t CACHED_COUNT = 1;
constexpr int32_t DISPLAY_COUNT = 3;
constexpr Dimension ITEM_SPACE = Dimension(20, DimensionUnit::PX);
constexpr Dimension SWIPER_MARGIN = 16.0_vp;
constexpr Dimension SWIPER_GUTTER = 16.0_vp;
constexpr Dimension PREVIOUS_MARGIN = Dimension(50, DimensionUnit::PX);
constexpr Dimension NEXT_MARGIN = Dimension(50, DimensionUnit::PX);
constexpr Dimension NEXT_MARGIN_EXTRA_LARGE = Dimension(600, DimensionUnit::PX);
constexpr int32_t MAX_NODE_NUMBER = 3;
constexpr double MAIN_DELTA = 20.0;
constexpr float GEOMETRY_WIDTH = 10.0f;
constexpr float GEOMETRY_HEIGHT = 10.0f;
constexpr int32_t SWIPER_DEFAULT_INDEX = 1;
constexpr int32_t SWIPER_ERROR = -1;
constexpr int32_t INDEX_NUM = 10;
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

// swiper_property
constexpr int32_t INDEX_DEFAULT = 1;
constexpr int32_t SWIPER_LAYOUT_PROPERTY_INDEX_1 = -1;
constexpr int32_t SWIPER_LAYOUT_PROPERTY_INDEX_2 = 0;
constexpr int32_t SWIPER_LAYOUT_PROPERTY_INDEX_3 = 1;
const std::vector<int32_t> SWIPER_LAYOUT_PROPERTY_INDEX = { SWIPER_LAYOUT_PROPERTY_INDEX_1,
    SWIPER_LAYOUT_PROPERTY_INDEX_2, SWIPER_LAYOUT_PROPERTY_INDEX_3 };

const bool SWIPER_PAINT_PROPERTY_AUTOPLAY = false;
constexpr int32_t SWIPER_PAINT_PROPERTY_INTERVAL_DEFAULT = 3000;
constexpr int32_t SWIPER_PAINT_PROPERTY_INTERVAL_1 = 5000;
constexpr int32_t SWIPER_PAINT_PROPERTY_INTERVAL_2 = -100;
const std::vector<int32_t> SWIPER_PAINT_PROPERTY_INTERVAL = { SWIPER_PAINT_PROPERTY_INTERVAL_1,
    SWIPER_PAINT_PROPERTY_INTERVAL_2 };
const bool SWIPER_LAYOUT_PROPERTY_SHOW_INDICATOR = false;
const bool SWIPER_PAINT_PROPERTY_LOOP = false;
const SwiperDisplayMode SWIPER_LAYOUT_PROPERTY_DISPLAY_MODE = SwiperDisplayMode::AUTO_LINEAR;
const std::vector<EdgeEffect> SWIPER_PAINT_PROPERTY_EDGE_EFFECT = { EdgeEffect::FADE, EdgeEffect::NONE,
    EdgeEffect::SPRING };

const RefPtr<Curve> LINEAR = AceType::MakeRefPtr<LinearCurve>();
const RefPtr<Curve> SINE = AceType::MakeRefPtr<SineCurve>();
const RefPtr<Curve> EASE = AceType::MakeRefPtr<CubicCurve>(0.25f, 0.1f, 0.25f, 1.0f);
const RefPtr<Curve> SMOOTH = AceType::MakeRefPtr<CubicCurve>(0.4f, 0.0f, 0.4f, 1.0f);
const RefPtr<Curve> ELASTICS = AceType::MakeRefPtr<ElasticsCurve>(2.0f);
const std::vector<RefPtr<Curve>> SWIPER_PAINT_PROPERTY_CURVE = { LINEAR, SINE, EASE, SMOOTH, ELASTICS };

const std::vector<int32_t> SWIPER_PAINT_PROPERTY_DURATION = { 100, 2000, 400 };
constexpr Dimension SWIPER_PAINT_PROPERTY_ITEM_SPACE_1 = Dimension(0);
constexpr Dimension SWIPER_PAINT_PROPERTY_ITEM_SPACE_2 = Dimension(1);
constexpr Dimension SWIPER_PAINT_PROPERTY_ITEM_SPACE_3 = Dimension(10);
const std::vector<Dimension> SWIPER_PAINT_PROPERTY_ITEM_SPACE = { SWIPER_PAINT_PROPERTY_ITEM_SPACE_1,
    SWIPER_PAINT_PROPERTY_ITEM_SPACE_2, SWIPER_PAINT_PROPERTY_ITEM_SPACE_3 };

const std::vector<int32_t> SWIPER_PAINT_PROPERTY_CACHED_COUNT = { 2, 1, 5, 10 };
const std::vector<int32_t> SWIPER_PAINT_PROPERTY_DISPLAY_COUNT = { 2, 5, 3, 10 };
const bool SWIPER_LAYOUT_PROPERTY_SHOW_DISABLE_SWIPE = true;

const std::vector<Axis> SWIPER_PAINT_PROPERTY_DIRECTION = { Axis::HORIZONTAL, Axis::FREE, Axis::NONE, Axis::VERTICAL };
constexpr Dimension ARROW_BACKGROUND_SIZE = 3.0_vp;
constexpr Dimension ARROW_SIZE = 10.0_vp;
const SizeF ARROW_FRAME_SIZE = SizeF(3.0f, 3.0f);
} // namespace

class SwiperTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void CommomAttrInfo();
    void SetUp() override;
    void TearDown() override;
    void InitSwiperTestNg();
    void CreateChildWrapperAppendToHostWrapper(
        int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapperNode>& hostWrapper);
    void InitLayoutWrapper(const RefPtr<FrameNode>& frameNode, RefPtr<LayoutAlgorithm>& algorithm,
        RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapperNode>& layoutWrapper);
    void InitChild(RefPtr<LayoutWrapperNode>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode);
    void InitArrowLayoutWrapper(const RefPtr<FrameNode>& swiperFrameNode, const std::string& arrowType,
        RefPtr<FrameNode>& arrowNode, RefPtr<LayoutWrapperNode>& arrowLayoutWrapper);
    void AddArrowChild(const RefPtr<FrameNode>& arrowNode, const RefPtr<LayoutWrapperNode>& arrowLayoutWrapper);
    void CreateSwiperLayoutWrapper(const RefPtr<FrameNode>& swiperNode, RefPtr<LayoutWrapperNode>& swiperLayoutWrapper);

    RefPtr<FrameNode> CreateSwiperFrameNode();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SwiperPattern> swiperPattern_;
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty_;
    RefPtr<SwiperAccessibilityProperty> swiperAccessibilityProperty_;
};

RefPtr<FrameNode> SwiperTestNg::CreateSwiperFrameNode()
{
    SwiperModelNG swiper;
    swiper.Create();
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

void SwiperTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SwiperTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void SwiperTestNg::CommomAttrInfo()
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

void SwiperTestNg::InitLayoutWrapper(const RefPtr<FrameNode>& frameNode, RefPtr<LayoutAlgorithm>& algorithm,
    RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapperNode>& layoutWrapper)
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
    layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
}

void SwiperTestNg::InitChild(RefPtr<LayoutWrapperNode>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode)
{
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    indicatorNodeWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(lastLayoutWrapper);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    indicatorNodeWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
}

void SwiperTestNg::CreateSwiperLayoutWrapper(
    const RefPtr<FrameNode>& swiperNode, RefPtr<LayoutWrapperNode>& swiperLayoutWrapper)
{
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    ASSERT_NE(swiperLayoutProperty, nullptr);

    swiperLayoutProperty->UpdateDisplayArrow(true);
    swiperLayoutProperty->UpdateShowIndicator(true);
    swiperLayoutProperty->UpdateIsSidebarMiddle(false);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    swiperLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutProperty->UpdateContentConstraint();

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto swiperNormalOffset = OffsetF(0.0f, 0.0f);
    auto swiperNormalSize = SizeF(648.0f, 240.0f);
    geometryNode->SetFrameOffset(swiperNormalOffset);
    geometryNode->SetFrameSize(swiperNormalSize);

    swiperLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode, swiperLayoutProperty);
}

void SwiperTestNg::InitArrowLayoutWrapper(const RefPtr<FrameNode>& swiperFrameNode, const std::string& arrowType,
    RefPtr<FrameNode>& arrowNode, RefPtr<LayoutWrapperNode>& arrowLayoutWrapper)
{
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    if (arrowType == V2::SWIPER_LEFT_ARROW_ETS_TAG) {
        buttonId = swiperPattern->GetLeftButtonId();
    } else if (arrowType == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        buttonId = swiperPattern->GetRightButtonId();
    }

    arrowNode = FrameNode::GetOrCreateFrameNode(
        arrowType, buttonId, []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(arrowNode, nullptr);

    auto arrowPattern = arrowNode->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(arrowPattern, nullptr);

    auto arrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(arrowPattern->GetSwiperArrowLayoutProperty());
    ASSERT_NE(arrowLayoutProperty, nullptr);

    arrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    arrowLayoutProperty->UpdateBackgroundColor(Color::BLACK);
    arrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);
    arrowLayoutProperty->UpdateArrowColor(Color::BLACK);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    arrowLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    arrowLayoutProperty->UpdateContentConstraint();

    arrowNode->MarkModifyDone();
    swiperFrameNode->AddChild(arrowNode);

    auto arrowGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(arrowGeometryNode, nullptr);
    arrowGeometryNode->SetFrameSize(SizeF(36.0f, 36.0f));
    arrowLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(arrowNode, arrowGeometryNode, arrowLayoutProperty);
    ASSERT_NE(arrowLayoutWrapper, nullptr);
    auto arrowLayoutAlgorithm = arrowPattern->CreateLayoutAlgorithm();
    ASSERT_NE(arrowLayoutAlgorithm, nullptr);
    arrowLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arrowLayoutAlgorithm));

    AddArrowChild(arrowNode, arrowLayoutWrapper);
}

void SwiperTestNg::AddArrowChild(
    const RefPtr<FrameNode>& arrowNode, const RefPtr<LayoutWrapperNode>& arrowLayoutWrapper)
{
    auto arrowFirstChildNode = AceType::DynamicCast<FrameNode>(arrowNode->GetFirstChild());
    ASSERT_NE(arrowFirstChildNode, nullptr);
    auto arrowFirstChildNodePattern = arrowFirstChildNode->GetPattern<ButtonPattern>();
    ASSERT_NE(arrowFirstChildNodePattern, nullptr);
    auto arrowFirstChildNodeLayoutProperty =
        AceType::DynamicCast<ButtonLayoutProperty>(arrowFirstChildNode->GetLayoutProperty());
    ASSERT_NE(arrowFirstChildNodeLayoutProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> arrowFirstChildNodeWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(arrowFirstChildNode, geometryNode, arrowFirstChildNodeLayoutProperty);
    ASSERT_NE(arrowFirstChildNodeWrapper, nullptr);

    auto arrowFirstChildLayoutAlgorithm = arrowFirstChildNodePattern->CreateLayoutAlgorithm();
    ASSERT_NE(arrowFirstChildLayoutAlgorithm, nullptr);
    arrowFirstChildNodeWrapper->SetLayoutAlgorithm(
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arrowFirstChildLayoutAlgorithm));
    ASSERT_NE(arrowLayoutWrapper, nullptr);
    arrowLayoutWrapper->AppendChild(arrowFirstChildNodeWrapper);
}

void SwiperTestNg::CreateChildWrapperAppendToHostWrapper(
    int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapperNode>& hostWrapper)
{
    ASSERT_NE(hostWrapper, nullptr);
    for (int32_t index = startIndex; index <= endIndex; index++) {
        auto childPattern = AceType::MakeRefPtr<Pattern>();
        auto childFrameNode = FrameNode::CreateFrameNode(BOX_NAME, index, childPattern);
        ASSERT_NE(childFrameNode, nullptr);
        auto host = hostWrapper->GetHostNode();
        ASSERT_NE(host, nullptr);
        host->AddChild(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        ASSERT_NE(childGeometryNode, nullptr);
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        ASSERT_NE(childLayoutProperty, nullptr);
        childLayoutProperty->UpdateAspectRatio(1.0f);
        RefPtr<LayoutWrapperNode> childLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
        auto layoutAlgorithm = childPattern->CreateLayoutAlgorithm();
        ASSERT_NE(layoutAlgorithm, nullptr);
        childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
        hostWrapper->AppendChild(std::move(childLayoutWrapper));
    }
}

void SwiperTestNg::SetUp() {}

void SwiperTestNg::TearDown()
{
    frameNode_ = nullptr;
    swiperPattern_ = nullptr;
    swiperLayoutProperty_ = nullptr;
    swiperAccessibilityProperty_ = nullptr;
}

void SwiperTestNg::InitSwiperTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    swiperPattern_ = frameNode_->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern_, nullptr);

    swiperLayoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty_, nullptr);

    swiperAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    ASSERT_NE(swiperAccessibilityProperty_, nullptr);

    swiperLayoutProperty_->UpdateShowIndicator(false);
}

/**
 * @tc.name: SwiperLayoutPropertyTest001
 * @tc.desc: Set one index value into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutPropertyTest001, TestSize.Level1)
{
    SwiperModelNG swiper;
    swiper.Create();
    swiper.SetIndex(INDEX_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetIndex().value_or(0), INDEX_DEFAULT);
}

/**
 * @tc.name: SwiperLayoutPropertyTest002
 * @tc.desc: set a lot of index values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutPropertyTest002, TestSize.Level1)
{
    for (unsigned int i = 0; i < SWIPER_LAYOUT_PROPERTY_INDEX.size(); ++i) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetIndex(SWIPER_LAYOUT_PROPERTY_INDEX[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetIndex().value_or(0), SWIPER_LAYOUT_PROPERTY_INDEX[i]);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest003
 * @tc.desc: set autoPlay value into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest003, TestSize.Level1)
{
    SwiperModelNG swiper;
    swiper.Create();
    swiper.SetAutoPlay(SWIPER_PAINT_PROPERTY_AUTOPLAY);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetAutoPlay().value_or(false), SWIPER_PAINT_PROPERTY_AUTOPLAY);
}

/**
 * @tc.name: SwiperPaintPropertyTest004
 * @tc.desc: set a lot of intertval values into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest004, TestSize.Level1)
{
    for (const auto& interval : SWIPER_PAINT_PROPERTY_INTERVAL) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetAutoPlayInterval(interval);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(
            swiperPaintProperty->GetAutoPlayInterval().value_or(SWIPER_PAINT_PROPERTY_INTERVAL_DEFAULT), interval);
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest005
 * @tc.desc: set showIndicator value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutPropertyTest005, TestSize.Level1)
{
    SwiperModelNG swiper;
    swiper.Create();
    swiper.SetShowIndicator(SWIPER_LAYOUT_PROPERTY_SHOW_INDICATOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetShowIndicator().value_or(false), SWIPER_LAYOUT_PROPERTY_SHOW_INDICATOR);
}

/**
 * @tc.name: SwiperPaintPropertyTest006
 * @tc.desc: set loop value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest006, TestSize.Level1)
{
    SwiperModelNG swiper;
    swiper.Create();
    swiper.SetLoop(SWIPER_PAINT_PROPERTY_LOOP);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetLoop().value_or(false), SWIPER_PAINT_PROPERTY_LOOP);
}

/**
 * @tc.name: SwiperLayoutPropertyTest007
 * @tc.desc: set one displayMode value into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutPropertyTest007, TestSize.Level1)
{
    SwiperModelNG swiper;
    swiper.Create();
    swiper.SetDisplayMode(SWIPER_LAYOUT_PROPERTY_DISPLAY_MODE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH),
        SWIPER_LAYOUT_PROPERTY_DISPLAY_MODE);
}

/**
 * @tc.name: SwiperPaintPropertyTest008
 * @tc.desc: set one effectMode value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest008, TestSize.Level1)
{
    for (const auto& effectMode : SWIPER_PAINT_PROPERTY_EDGE_EFFECT) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetEdgeEffect(effectMode);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_FALSE(frameNode == nullptr);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::FADE), effectMode);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest009
 * @tc.desc: set curve value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest009, TestSize.Level1)
{
    for (int32_t i = 0; i < static_cast<int32_t>(SWIPER_PAINT_PROPERTY_CURVE.size()); ++i) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetCurve(SWIPER_PAINT_PROPERTY_CURVE[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(swiperPaintProperty->GetCurve().value_or(Curves::EASE), SWIPER_PAINT_PROPERTY_CURVE[i]);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest0010
 * @tc.desc: set duration value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest0010, TestSize.Level1)
{
    for (const auto& duration : SWIPER_PAINT_PROPERTY_DURATION) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetDuration(duration);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
        EXPECT_FALSE(swiperPaintProperty == nullptr);
        EXPECT_EQ(swiperPaintProperty->GetDuration().value_or(Curves::EASE), duration);
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest0011
 * @tc.desc: set a lot of itemSpace values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutPropertyTest0011, TestSize.Level1)
{
    for (const auto& itemSpace : SWIPER_PAINT_PROPERTY_ITEM_SPACE) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetItemSpace(itemSpace);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetItemSpace().value_or(Dimension(0)).Value(),
            static_cast<int32_t>(itemSpace.Value()));
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest0012
 * @tc.desc: set a lot of cachedCount values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutPropertyTest0012, TestSize.Level1)
{
    for (unsigned int i = 0; i < SWIPER_PAINT_PROPERTY_CACHED_COUNT.size(); ++i) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetCachedCount(SWIPER_PAINT_PROPERTY_CACHED_COUNT[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetCachedCount().value_or(1), SWIPER_PAINT_PROPERTY_CACHED_COUNT[i]);
    }
}

/**
 * @tc.name: SwiperLayoutPropertyTest0013
 * @tc.desc: set a lot of displayCount values into SwiperLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutPropertyTest0013, TestSize.Level1)
{
    for (unsigned int i = 0; i < SWIPER_PAINT_PROPERTY_DISPLAY_COUNT.size(); ++i) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetDisplayCount(SWIPER_PAINT_PROPERTY_DISPLAY_COUNT[i]);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetDisplayCount().value_or(1), SWIPER_PAINT_PROPERTY_DISPLAY_COUNT[i]);
    }
}

/**
 * @tc.name: SwiperPaintPropertyTest0014
 * @tc.desc: set disableSwipe value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest0014, TestSize.Level1)
{
    SwiperModelNG swiper;
    swiper.Create();
    swiper.SetDisableSwipe(SWIPER_LAYOUT_PROPERTY_SHOW_DISABLE_SWIPE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_FALSE(swiperPaintProperty == nullptr);
    EXPECT_EQ(swiperPaintProperty->GetDisableSwipe().value_or(false), SWIPER_LAYOUT_PROPERTY_SHOW_DISABLE_SWIPE);
}

/**
 * @tc.name: SwiperLayoutPropertyTest0015
 * @tc.desc: set one direction value into SwiperPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintPropertyTest0015, TestSize.Level1)
{
    for (const auto& direction : SWIPER_PAINT_PROPERTY_DIRECTION) {
        SwiperModelNG swiper;
        swiper.Create();
        swiper.SetDirection(direction);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_FALSE(frameNode == nullptr);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
        EXPECT_FALSE(swiperNode == nullptr);
        auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
        EXPECT_FALSE(swiperLayoutProperty == nullptr);
        EXPECT_EQ(swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL), direction);
    }
}

/**
 * @tc.name: SwiperPropertyTest0016
 * @tc.desc: set id into Swiper and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPropertyTest0016, TestSize.Level1)
{
    SwiperModelNG swiper;
    swiper.Create();
    ViewAbstract::SetInspectorId(V2::SWIPER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    EXPECT_EQ(swiperNode->GetInspectorId().value_or(""), V2::SWIPER_ETS_TAG);
}

/**
 * @tc.name: SwiperPropertyTest0017
 * @tc.desc: set minSize into Swiper and get it.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPropertyTest0017, TestSize.Level1)
{
    constexpr Dimension SWIPER_MINSIZE = 300.0_vp;
    SwiperModelNG swiper;
    swiper.Create();
    swiper.SetMinSize(SWIPER_MINSIZE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(frameNode);
    EXPECT_FALSE(swiperNode == nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_FALSE(swiperLayoutProperty == nullptr);
    EXPECT_EQ(swiperLayoutProperty->GetMinSize().value_or(Dimension(0.0, DimensionUnit::VP)), SWIPER_MINSIZE);
}

/**
 * @tc.name: SwiperEvent001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperEvent001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoList;
    infoList.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoList;
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
    const char* name = "HandleTouchDown";
    pattern->controller_ = CREATE_ANIMATOR(name);
    pattern->controller_->status_ = Animator::Status::RUNNING;
    pattern->springController_ = CREATE_ANIMATOR(name);
    pattern->springController_->status_ = Animator::Status::RUNNING;
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);

    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    pattern->HandleTouchEvent(touchEventInfo);
    pattern->controller_ = nullptr;
    pattern->springController_ = nullptr;
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::CANCEL);
    pattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::MOVE);
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperEvent002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    auto pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->restoreNodeInfo_.emplace(std::make_pair(1, "testFlushUITasks"));
    EXPECT_CALL(*pipeline, FlushUITasks()).WillRepeatedly(Return());

    pattern->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern->direction_, Axis::HORIZONTAL);
    pattern->touchEvent_ = nullptr;
    pattern->InitTouchEvent(gestureEventHub);
    TouchEventFunc callback = [](TouchEventInfo& info) {};
    pattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    pattern->InitTouchEvent(gestureEventHub);
    EXPECT_TRUE(pattern->touchEvent_);

    EXPECT_TRUE(pattern->panEvent_);
    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.inputEventType_ = InputEventType::AXIS;
    pattern->panEvent_->actionStart_(gestureEvent);
    pattern->panEvent_->actionUpdate_(gestureEvent);
    pattern->panEvent_->actionEnd_(gestureEvent);
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    CommonFunc func = []() {};
    pattern->swiperController_->SetTabBarFinishCallback(func);
    pattern->panEvent_->actionStart_(gestureEvent);
    pattern->panEvent_->actionEnd_(gestureEvent);
    pattern->swiperController_->SetRemoveSwiperEventCallback(func);
    pattern->panEvent_->actionStart_(gestureEvent);
    pattern->panEvent_->actionEnd_(gestureEvent);
    pattern->panEvent_->actionCancel_();
    EXPECT_TRUE(pattern->swiperController_->tabBarFinishCallback_);
    EXPECT_TRUE(pattern->swiperController_->removeSwiperEventCallback_);
}

/**
 * @tc.name: SwiperUtilsTest001
 * @tc.desc: Test Swiper measure and layout function, set prevMargin and nextMargin property is 50_px.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest001, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(swiperGeometryNode, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    swiperLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutProperty->UpdateContentConstraint();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperFrameNode, swiperGeometryNode, swiperLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    int32_t displaycount = 3;
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(displaycount);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperPaintProperty->UpdateLoop(false);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    int32_t startIndex = 0;
    int32_t endIndex = 4;
    swiperLayoutAlgorithm->currentIndex_ = 1;
    CreateChildWrapperAppendToHostWrapper(startIndex, endIndex, layoutWrapper);
    swiperLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    swiperLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    for (int32_t index = startIndex; index <= endIndex; index++) {
        auto childLayout = layoutWrapper->GetOrCreateChildByIndex(index);
        ASSERT_NE(childLayout, nullptr);
    }
}

/**
 * @tc.name: SwiperUtilsTest002
 * @tc.desc: Verify the CreateChildConstraint function when DisplayCount is -1.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest002, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisplayCount(-1);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest003
 * @tc.desc: Verify the CreateChildConstraint function when DisplayMode is AUTO_LINEAR.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest003, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest004
 * @tc.desc: Verify the CreateChildConstraint function when NextMargin is normal and abnormal.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest004, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);

    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN_EXTRA_LARGE);
    result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest005
 * @tc.desc: Verify the CreateChildConstraint function does not set a value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest005, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest006
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest006, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);

    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN_EXTRA_LARGE);
    result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest007
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL and does not set value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest007, TestSize.Level2)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest008
 * @tc.desc: Verify the CreateChildConstraint function when Direction is FREE.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest008, TestSize.Level1)
{
    auto swiperFrameNode = CreateSwiperFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(CURRENT_INDEX);
    swiperLayoutProperty->UpdateItemSpace(ITEM_SPACE);
    swiperLayoutProperty->UpdateCachedCount(CACHED_COUNT);
    swiperLayoutProperty->UpdateDirection(Axis::FREE);
    swiperLayoutProperty->UpdateDisplayCount(DISPLAY_COUNT);
    swiperLayoutProperty->UpdatePrevMargin(PREVIOUS_MARGIN);
    swiperLayoutProperty->UpdateNextMargin(NEXT_MARGIN);

    OptionalSizeF setSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto result = SwiperUtils::CreateChildConstraint(swiperLayoutProperty, setSize);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperInit001
 * @tc.desc: InitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInit001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto indicatorNode =
        FrameNode::GetOrCreateFrameNode("Indicator", 0, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    swiperNode->children_.clear();
    swiperNode->AddChild(indicatorNode);
    pattern->InitIndicator();
    EXPECT_EQ(swiperNode->children_.size(), 2);
    swiperNode->children_.clear();
    indicatorNode = FrameNode::GetOrCreateFrameNode(
        "SwiperIndicator", 0, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);
    pattern->InitIndicator();
    EXPECT_EQ(swiperNode->children_.size(), 1);
}

/**
 * @tc.name: SwiperInit002
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInit002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(eventHub, FocusType::DISABLE, false);
    pattern->InitOnKeyEvent(focusHub);
    KeyEvent event = KeyEvent();
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(event));
}

/**
 * @tc.name: SwiperFunc001
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    KeyEvent event = KeyEvent();
    event.action = KeyAction::CLICK;
    EXPECT_FALSE(pattern->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(pattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(pattern->OnKeyEvent(event));
}

/**
 * @tc.name: SwiperFunc002
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    bool isVisible = false;
    pattern->OnVisibleChange(isVisible);
    pattern->isInit_ = false;
    pattern->OnWindowHide();
    pattern->OnVisibleChange(isVisible);
    EXPECT_FALSE(pattern->isVisible_);
    isVisible = true;
    pattern->OnWindowShow();
    pattern->OnVisibleChange(isVisible);
    EXPECT_TRUE(pattern->isVisible_);
}

/**
 * @tc.name: SwiperFunc003
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    pattern->OnIndexChange();
    int32_t nodeId = 0;
    while (nodeId < MAX_NODE_NUMBER) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(
            "SwiperIndicator", nodeId, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        swiperNode->AddChild(indicatorNode);
        nodeId++;
    }
    pattern->OnIndexChange();
    EXPECT_EQ(pattern->TotalCount(), MAX_NODE_NUMBER - 1);
}

/**
 * @tc.name: SwiperFunc004
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    pattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    pattern->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern->direction_, Axis::HORIZONTAL);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(
        "SwiperIndicator", 0, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    swiperNode->AddChild(indicatorNode);
    EXPECT_TRUE(swiperNode->geometryNode_);
    swiperNode->geometryNode_->frame_.SetOffset(OffsetF(0, 0));
    EXPECT_TRUE(pattern->panEvent_);
    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.SetMainDelta(MAIN_DELTA);
    gestureEvent.SetLocalLocation(Offset(0, 0));
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    pattern->panEvent_->actionUpdate_(gestureEvent);
    EXPECT_EQ(pattern->currentOffset_, 0.0);

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->propLoop_ = false;
    swiperNode->geometryNode_->frame_.SetSize(SizeF(GEOMETRY_WIDTH, GEOMETRY_HEIGHT));
    EXPECT_FALSE(pattern->IsOutOfBoundary(MAIN_DELTA));
    // Swiper has reached boundary.
    swiperNode->geometryNode_->frame_.SetSize(SizeF(0, 0));
    pattern->panEvent_->actionUpdate_(gestureEvent);
    pattern->currentOffset_ = MAIN_DELTA;
    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::FADE;
    pattern->panEvent_->actionUpdate_(gestureEvent);
    pattern->currentOffset_ = MAIN_DELTA;
    swiperPaintProperty->propEdgeEffect_ = EdgeEffect::NONE;
    pattern->panEvent_->actionUpdate_(gestureEvent);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Swiper Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper and initialize related properties.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Get swiper frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    swiperPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get swiper accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto swiperAccessibilityProperty = frameNode->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    ASSERT_NE(swiperAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When swiper is not scrollable, call the callback function in swiperAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When swiper is scrollable, call the callback function in swiperAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    swiperPaintProperty->UpdateLoop(true);
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(swiperAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: SwiperModelNg001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SwiperModelNG.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: swiperLayoutProperty->GetIndex() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetIndex(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.2. Test SetDisplayMode function.
     * @tc.expected: swiperLayoutProperty->GetDisplayMode() is equal to swiperDisplayMode.
     */
    swiperModelNG.SetDisplayMode(SwiperDisplayMode::STRETCH);
    EXPECT_EQ(swiperLayoutProperty->GetDisplayMode(), SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step3.3. Test SetShowIndicator function.
     * @tc.expected: swiperLayoutProperty->GetIndex() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetShowIndicator(true);
    EXPECT_TRUE(swiperLayoutProperty->GetShowIndicator());

    /**
     * @tc.steps: step3.4. Test SetItemSpace function.
     * @tc.expected: swiperLayoutProperty->GetItemSpace() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    swiperModelNG.SetItemSpace(dimension);
    EXPECT_EQ(swiperLayoutProperty->GetItemSpace(), dimension);

    /**
     * @tc.steps: step3.5. Test SetCachedCount function.
     * @tc.expected:DisplayCount = -1 swiperLayoutProperty->SetCachedCount() is equal to SWIPER_DEFAULT_INDEX.
     * @tc.expected:DisplayCount = 1 swiperLayoutProperty->SetCachedCount() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetCachedCount(-SWIPER_DEFAULT_INDEX);
    swiperModelNG.SetCachedCount(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperLayoutProperty->GetCachedCount(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.6. Test SetIsIndicatorCustomSize function.
     * @tc.expected: swiperPattern->IsIndicatorCustomSize() is equal to true.
     */
    swiperModelNG.SetIsIndicatorCustomSize(true);
    EXPECT_TRUE(swiperPattern->IsIndicatorCustomSize());

    /**
     * @tc.steps: step3.7. Test SetAutoPlay function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlay() is equal to true.
     */
    swiperModelNG.SetAutoPlay(true);
    EXPECT_TRUE(swiperPaintProperty->GetAutoPlay());

    /**
     * @tc.steps: step3.8. Test SetAutoPlayInterval function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlayInterval() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetAutoPlayInterval(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperPaintProperty->GetAutoPlayInterval(), SWIPER_DEFAULT_INDEX);

    /**
     * @tc.steps: step3.9. Test SetDuration function.
     * @tc.expected: SwiperPaintProperty->GetDuration() is equal to SWIPER_DEFAULT_INDEX.
     */
    swiperModelNG.SetDuration(SWIPER_DEFAULT_INDEX);
    EXPECT_EQ(swiperPaintProperty->GetDuration(), SWIPER_DEFAULT_INDEX);
}

/**
 * @tc.name: SwiperModelNg002
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SwiperModelNG.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    auto eventHub = swiperFrameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3.1. Test SetLoop function.
     * @tc.expected: SwiperPaintProperty->GetLoop() is true.
     */
    swiperModelNG.SetLoop(true);
    EXPECT_TRUE(swiperPaintProperty->GetLoop());

    /**
     * @tc.steps: step3.2. Test SetEnabled function.
     * @tc.expected: SwiperPaintProperty->GetEnabled() is true.
     */
    swiperModelNG.SetEnabled(true);
    EXPECT_TRUE(swiperPaintProperty->GetEnabled());

    /**
     * @tc.steps: step3.3. Test SetDisableSwipe function.
     * @tc.expected: SwiperPaintProperty->GetDisableSwipe() is true.
     */
    swiperModelNG.SetDisableSwipe(true);
    EXPECT_TRUE(swiperPaintProperty->GetDisableSwipe());

    /**
     * @tc.steps: step3.4. Test SetEdgeEffect function.
     * @tc.expected: SwiperPaintProperty->GetEdgeEffect() is true.
     */
    swiperModelNG.SetEdgeEffect(EdgeEffect::FADE);
    EXPECT_EQ(swiperPaintProperty->GetEdgeEffect(), EdgeEffect::FADE);

    /**
     * @tc.steps: step3.5. Test SetOnChange function.
     * @tc.expected:swiperPattern->changeEvent_ not null.
     */
    auto onChange = [](const BaseEventInfo* info) {};
    swiperModelNG.SetOnChange(std::move(onChange));
    EXPECT_NE(swiperPattern->changeEvent_, nullptr);

    /**
     * @tc.steps: step3.6. Test SetOnAnimationStart function.
     * @tc.expected:swiperPattern->animationStartEvent_ not null.
     */
    auto onAnimationStart = [](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {};
    swiperModelNG.SetOnAnimationStart(std::move(onAnimationStart));
    EXPECT_NE(eventHub->animationStartEvent_, nullptr);

    /**
     * @tc.steps: step3.7. Test SetOnAnimationEnd function.
     * @tc.expected:swiperPattern->animationEndEvent_ not null.
     */
    auto onAnimationEnd = [](int32_t index, const AnimationCallbackInfo& info) {};
    swiperModelNG.SetOnAnimationEnd(std::move(onAnimationEnd));
    EXPECT_NE(eventHub->animationEndEvent_, nullptr);
}

/**
 * @tc.name: SwiperModelNg003
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SwiperModelNG.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    /**
     * @tc.steps: step2. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    auto eventHub = swiperFrameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3.1. Test SetIndicatorStyle function.
     * @tc.expected: SwiperPaintProperty->swiperParameters_->colorVal is swiperParameters.colorVal.
     */
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    swiperModelNG.SetIndicatorStyle(swiperParameters);
    EXPECT_EQ(swiperPattern->swiperParameters_->colorVal, swiperParameters.colorVal);

    /**
     * @tc.steps: step3.2. Test SetPreviousMargin function.
     * @tc.expected: swiperPaintProperty->GetPrevMargin() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    swiperModelNG.SetPreviousMargin(dimension);
    EXPECT_EQ(swiperLayoutProperty->GetPrevMargin(), dimension);

    /**
     * @tc.steps: step3.3. Test SetNextMargin function.
     * @tc.expected: swiperPaintProperty->GetNextMargin() is equal to dimension.
     */
    swiperModelNG.SetNextMargin(dimension);
    EXPECT_EQ(swiperLayoutProperty->GetNextMargin(), dimension);

    /**
     * @tc.steps: step3.4. Test SetOnChangeEvent function.
     * @tc.expected: swiperPaintProperty->GetLoop() is not null.
     */
    auto onAnimationEnd = [](const BaseEventInfo* info) {};
    swiperModelNG.SetOnChangeEvent(std::move(onAnimationEnd));
    EXPECT_NE(swiperPattern->onIndexChangeEvent_, nullptr);

    /**
     * @tc.steps: step3.5. Test SetIndicatorIsBoolean function.
     * @tc.expected: swiperPattern->indicatorIsBoolean_ is true.
     */
    swiperModelNG.SetIndicatorIsBoolean(true);
    EXPECT_TRUE(swiperPattern->indicatorIsBoolean_);

    /**
     * @tc.steps: step3.6. Test SetArrowStyle function.
     * @tc.expected: before set swiperArrowParameters, all result is null.
     */
    SwiperArrowParameters swiperArrowParameters;
    swiperModelNG.SetArrowStyle(swiperArrowParameters);

    /**
     * @tc.steps: step3.7. Test SetArrowStyle function.
     * @tc.expected: after set swiperArrowParameters, swiperLayoutProperty->IsShowBoard is true.
     */
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.backgroundSize = dimension;
    swiperArrowParameters.backgroundColor = Color(Color::BLUE);
    swiperArrowParameters.arrowSize = dimension;
    swiperArrowParameters.arrowColor = Color(Color::RED);
    swiperArrowParameters.isSidebarMiddle = true;
    swiperModelNG.SetArrowStyle(swiperArrowParameters);
    EXPECT_TRUE(swiperLayoutProperty->GetIsShowBackground());
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundSize(), dimension);
    EXPECT_EQ(swiperLayoutProperty->GetBackgroundColor(), Color(Color::BLUE));
    EXPECT_EQ(swiperLayoutProperty->GetArrowSize(), dimension);
    EXPECT_EQ(swiperLayoutProperty->GetArrowColor(), Color(Color::RED));
    EXPECT_TRUE(swiperLayoutProperty->GetIsSidebarMiddle());

    /**
     * @tc.steps: step3.8. Test SetDisplayArrow function.
     * @tc.expected: swiperLayoutProperty->GetDisplayArrow() is true.
     */
    swiperModelNG.SetDisplayArrow(true);
    EXPECT_TRUE(swiperLayoutProperty->GetDisplayArrow());

    /**
     * @tc.steps: step3.9. Test SetHoverShow function.
     * @tc.expected: swiperLayoutProperty->GetHoverShow() is true.
     */
    swiperModelNG.SetHoverShow(true);
    EXPECT_TRUE(swiperLayoutProperty->GetHoverShow());
}

/**
 * @tc.name: SwiperFlushFocus001
 * @tc.desc: Swiper FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFlushFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Create curShowFrameNode, addChild to frameNode.
     */
    auto curShowFrame = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    curShowFrame->AddChild(child);
    swiperFrameNode->AddChild(child2);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(swiperFrameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    /**
     * @tc.steps: step3. test FlushFocus with IsShowIndicator() is false.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->lastWeakFocusNode_ is not null.
     */
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperPattern->isLastIndicatorFocused_ = true;
    EXPECT_FALSE(swiperPattern->IsShowIndicator());
    swiperPattern->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->FlushFocus(curShowFrame);
    EXPECT_EQ(swiperPattern->lastWeakShowNode_, AceType::WeakClaim(AceType::RawPtr(curShowFrame)));

    /**
     * @tc.steps: step4. test FlushFocus with IsShowIndicator() is true and hasLeftButton and hasRightButton.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->currentFocus_ is false.
     */
    swiperLayoutProperty->UpdateShowIndicator(true);
    swiperPattern->GetLeftButtonId();
    swiperPattern->GetRightButtonId();
    EXPECT_TRUE(swiperLayoutProperty->GetShowIndicatorValue(true));
    EXPECT_TRUE(swiperPattern->IsShowIndicator());
    focusHub->currentFocus_ = true;
    swiperPattern->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->FlushFocus(curShowFrame);
}

/**
 * @tc.name: SwiperGetNextFocusNode001
 * @tc.desc: Swiper GetNextFocusNode.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperGetNextFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
     */
    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Create localShowNode and focusNode.
     */
    auto localShowNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHubLocal = AceType::MakeRefPtr<EventHub>();
    eventHubLocal->AttachHost(localShowNode);
    auto focusHubLocal = AceType::MakeRefPtr<FocusHub>(eventHubLocal);

    auto focusNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(focusNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    swiperPattern->lastWeakShowNode_ = AceType::WeakClaim(AceType::RawPtr(localShowNode));

    /**
     * @tc.steps: step3. Test different Axis and FocusStep.
     */
    /**
     * @tc.steps: step3.1. Test different Axis::HORIZONTAL and FocusStep::UP.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::UP, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.2. Test different Axis::VERTICAL and FocusStep::LEFT.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::VERTICAL;
    swiperPattern->GetNextFocusNode(FocusStep::LEFT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.3. Test different Axis::HORIZONTAL and FocusStep::DOWN.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::LEFT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.4. Test different Axis::VERTICAL and FocusStep::RIGHT.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::VERTICAL;
    swiperPattern->GetNextFocusNode(FocusStep::RIGHT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.5. Test different Axis::FREE.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::FREE;
    swiperPattern->GetNextFocusNode(FocusStep::RIGHT, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.6. Test different Axis::HORIZONTAL and FocusStep::UP and has left right button.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->GetLeftButtonId();
    swiperPattern->GetRightButtonId();
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::UP, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.7. Test different Axis::HORIZONTAL and FocusStep::UP and has left right button.
     * @tc.expected: swiperPattern->GetNextFocusNode return nullptr.
     */
    swiperPattern->direction_ = Axis::HORIZONTAL;
    swiperPattern->GetNextFocusNode(FocusStep::DOWN, focusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPreviousFocus001
 * @tc.desc: Swiper PreviousFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPreviousFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
     */
    SwiperModelNG swiperModelNG;
    swiperModelNG.Create();

    auto swiperFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    auto swiperLeftArrowNode =
        AceType::MakeRefPtr<FrameNode>(V2::SWIPER_LEFT_ARROW_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto swiperRightArrowNode =
        AceType::MakeRefPtr<FrameNode>(V2::SWIPER_INDICATOR_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    swiperFrameNode->AddChild(swiperLeftArrowNode);
    swiperFrameNode->AddChild(swiperRightArrowNode);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(swiperFrameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    auto curEventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SWIPER_LEFT_ARROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    curEventHub->AttachHost(frameNode);
    auto curFocusHub = AceType::MakeRefPtr<FocusHub>(curEventHub);

    auto focusChildren = focusHub->GetChildren();
    swiperPattern->leftButtonId_ = std::nullopt;
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);
    EXPECT_FALSE(curFocusHub->parentFocusable_);
    swiperModelNG.SetLoop(false);
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_FALSE(curFocusHub->parentFocusable_);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);
    curFocusHub->GetFrameNode()->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);
    swiperModelNG.SetLoop(true);
    swiperPattern->GetLeftButtonId();
    EXPECT_FALSE(swiperLayoutProperty->GetHoverShowValue(false));
    swiperPattern->PreviousFocus(curFocusHub);
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetCurrentIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
    swiperPattern_->currentIndex_ = INDEX_NUM;
    EXPECT_EQ(swiperAccessibilityProperty_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetBeginIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
    swiperPattern_->startIndex_ = INDEX_NUM;
    EXPECT_EQ(swiperAccessibilityProperty_->GetBeginIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetEndIndex(), SWIPER_ERROR);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
    swiperPattern_->endIndex_ = INDEX_NUM;
    EXPECT_EQ(swiperAccessibilityProperty_->GetEndIndex(), INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_TRUE(swiperAccessibilityProperty_->HasRange());
    AccessibilityValue result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 0);
    EXPECT_EQ(result.current, 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->currentIndex_ = INDEX_NUM;

    result = swiperAccessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, INDEX_NUM);
    EXPECT_EQ(result.current, INDEX_NUM);
}

/**
 * @tc.name: SwiperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitSwiperTestNg();

    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    EXPECT_FALSE(swiperAccessibilityProperty_->IsScrollable());

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->OnModifyDone();
    EXPECT_TRUE(swiperAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitSwiperTestNg();

    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), 0);

    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->OnModifyDone();
    EXPECT_EQ(swiperAccessibilityProperty_->GetCollectionItemCounts(), INDEX_NUM + 1);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitSwiperTestNg();

    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperPattern_->currentIndex_ = 1;
    swiperPattern_->OnModifyDone();
    swiperAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = swiperAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    swiperPaintProperty->UpdateLoop(true);
    swiperAccessibilityProperty_->ResetSupportAction();
    supportAceActions = swiperAccessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: SwiperAccessibilityPropertySetSpecificSupportAction001
 * @tc.desc: Test GetSupportAction of swiper.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertySetSpecificSupportAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. InitSwiperTestNg.
     */
    InitSwiperTestNg();

    /**
     * @tc.steps: step2. call SetSpecificSupportAction with swiperAccessibilityProperty_->IsScrollable() is false.
     * @tc.expected: swiperAccessibilityProperty_->IsScrollable() is false.
     */
    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    swiperAccessibilityProperty_->SetSpecificSupportAction();

    /**
     * @tc.steps: step2. call SetSpecificSupportAction.
     * @tc.expected: GetCurrentIndex() < 0.
     */
    swiperPattern_->GetLeftButtonId();
    swiperPattern_->GetRightButtonId();
    swiperAccessibilityProperty_->SetSpecificSupportAction();
    EXPECT_LT(swiperAccessibilityProperty_->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step2. call SetSpecificSupportAction.
     * @tc.expected: GetCurrentIndex() > GetCollectionItemCounts().
     */
    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode_->AddChild(indicatorNode);
    }
    swiperAccessibilityProperty_->SetSpecificSupportAction();
    swiperPattern_->currentIndex_ = swiperPattern_->TotalCount();
    EXPECT_LE(swiperAccessibilityProperty_->GetCurrentIndex(), swiperAccessibilityProperty_->GetCollectionItemCounts());
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure002
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmMeasure002, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

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
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

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
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout003, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

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
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout004, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

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
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout005, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

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
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout006, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

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
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

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
HWTEST_F(SwiperTestNg, SwiperIndicatorOnAttachToFrameNodeTest001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorOnModifyDone001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorInitClickEvent001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorGetContentModifier001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SelectedFontSize001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, SelectedFontSize002, TestSize.Level2)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, FontSize001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, FontSize002, TestSize.Level2)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, FontColor001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, FontColor002, TestSize.Level2)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, SelectedFontColor001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, SelectedFontColor002, TestSize.Level2)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, FontWeight001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, SelectedFontWeight001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, ItemWidth001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemWidth002
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ItemWidth002, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight001
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ItemHeight001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight002
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ItemHeight002, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth001
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemWidth001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth002
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemWidth002, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight001
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemHeight001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight002
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemHeight002, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout001
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout001, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> layoutWrapper;
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
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(swiperNode, geometryNode, swiperLayoutProperty);
    ASSERT_NE(indicatorNodeWrapper, nullptr);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 327.0, 1121.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(327.0, 1121.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout002
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout002, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> layoutWrapper;
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
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(swiperNode, geometryNode, swiperLayoutProperty);
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
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout003, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> layoutWrapper;
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
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(swiperNode, geometryNode, swiperLayoutProperty);
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
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout004, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> layoutWrapper;
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
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(swiperNode, geometryNode, swiperLayoutProperty);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 634.0, 1086.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(634.0, 1086.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout005
 * @tc.desc: Test SwiperLayoutAlgorithm Layout with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create layoutWrapper and set swiperLayoutAlgorithm.
     */
    auto swiperNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(swiperNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper;
    CreateSwiperLayoutWrapper(swiperNode, swiperLayoutWrapper);
    ASSERT_NE(swiperLayoutWrapper, nullptr);
    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto indicatorGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(indicatorGeometryNode, nullptr);
    auto indicatorNormalOffset = OffsetF(250.0f, 190.0f);
    auto indicatorNormalSize = SizeF(144.0f, 48.0f);
    indicatorGeometryNode->SetFrameOffset(indicatorNormalOffset);
    indicatorGeometryNode->SetFrameSize(indicatorNormalSize);

    RefPtr<LayoutWrapperNode> indicatorNodeWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        indicatorNode, indicatorGeometryNode, indicatorNode->GetLayoutProperty());
    swiperLayoutWrapper->AppendChild(indicatorNodeWrapper);
    /**
     * @tc.steps: step3. Create arrow node and layoutWrapper.
     */
    RefPtr<FrameNode> leftArrowNode;
    RefPtr<FrameNode> rightArrowNode;
    RefPtr<LayoutWrapperNode> leftArrowNodeWrapper;
    RefPtr<LayoutWrapperNode> rightArrowNodeWrapper;
    InitArrowLayoutWrapper(swiperNode, V2::SWIPER_LEFT_ARROW_ETS_TAG, leftArrowNode, leftArrowNodeWrapper);
    InitArrowLayoutWrapper(swiperNode, V2::SWIPER_RIGHT_ARROW_ETS_TAG, rightArrowNode, rightArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(leftArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(rightArrowNodeWrapper);

    /**
     * @tc.cases: case1. Axis is HORIZONTAL, arrow is in the switch.
     */
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));

    auto leftArrowGeometryNode = leftArrowNodeWrapper->GetGeometryNode();
    ASSERT_NE(leftArrowGeometryNode, nullptr);
    auto leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    auto rightArrowGeometryNode = rightArrowNodeWrapper->GetGeometryNode();
    ASSERT_NE(rightArrowGeometryNode, nullptr);
    auto rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();

    EXPECT_EQ(leftArrowOffset, OffsetF(214.0f, 196.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(394.0f, 196.0f));

    /**
     * @tc.cases: case2. Axis is HORIZONTAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(15.0f, 240.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(625.0f, 48.0f));
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));

    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();

    /**
     * @tc.cases: case3. Axis is HORIZONTAL, arrow is in the switch, not show indicator.
     */
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));

    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();

    EXPECT_EQ(leftArrowOffset, OffsetF(0.0f, 102.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(612.0f, 102.0f));

    /**
     * @tc.cases: case4. Axis is VERTICAL, arrow is in the switch.
     */
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    swiperLayoutProperty->UpdateShowIndicator(true);
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 50.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 100.0f));
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));

    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(leftArrowOffset, OffsetF(12.0f, 14.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(12.0f, 150.0f));

    /**
     * @tc.cases: case5. Axis is VERTICAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 15.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 220.0f));
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));

    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();

    EXPECT_EQ(leftArrowOffset, OffsetF(12.0f, 0.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(12.0f, 204.0f));

    /**
     * @tc.cases: case6. Axis is VERTICAL, arrow is in the switch, not show indicator.
     */
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));

    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();

    EXPECT_EQ(leftArrowOffset, OffsetF(306.0f, 0.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(306.0f, 204.0f));
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasure001
 * @tc.desc: Test SwiperLayoutAlgorithm Measure with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create layoutWrapper and set swiperLayoutAlgorithm.
     */
    auto swiperNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(swiperNode, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper;
    CreateSwiperLayoutWrapper(swiperNode, swiperLayoutWrapper);
    ASSERT_NE(swiperLayoutWrapper, nullptr);

    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperPatternAlgorithm, nullptr);
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->GetLayoutProperty());
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    /**
     * @tc.steps: step3. Create arrow node and layoutWrapper.
     */
    RefPtr<FrameNode> leftArrowNode;
    RefPtr<FrameNode> rightArrowNode;
    RefPtr<LayoutWrapperNode> leftArrowNodeWrapper;
    RefPtr<LayoutWrapperNode> rightArrowNodeWrapper;
    InitArrowLayoutWrapper(swiperNode, V2::SWIPER_LEFT_ARROW_ETS_TAG, leftArrowNode, leftArrowNodeWrapper);
    InitArrowLayoutWrapper(swiperNode, V2::SWIPER_RIGHT_ARROW_ETS_TAG, rightArrowNode, rightArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(leftArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(rightArrowNodeWrapper);

    /**
     * @tc.steps: step4. call Measure.
     * @tc.expected: Return button measure, SizeF(3.0f, 3.0f).
     */
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));

    auto leftArrowChild = swiperLayoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(leftArrowChild, nullptr);
    auto leftArrowChildGeometryNode = leftArrowChild->GetGeometryNode();
    ASSERT_NE(leftArrowChildGeometryNode, nullptr);
    auto leftArrowChildSize = leftArrowChildGeometryNode->GetFrameSize();
    EXPECT_EQ(leftArrowChildSize, ARROW_FRAME_SIZE);

    auto rightArrowChild = swiperLayoutWrapper->GetOrCreateChildByIndex(1);
    ASSERT_NE(rightArrowChild, nullptr);
    auto rightArrowChildGeometryNode = rightArrowChild->GetGeometryNode();
    ASSERT_NE(rightArrowChildGeometryNode, nullptr);
    auto rightArrowChildSize = rightArrowChildGeometryNode->GetFrameSize();

    EXPECT_EQ(rightArrowChildSize, ARROW_FRAME_SIZE);
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateContentModifier001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateContentModifier002, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintNormalIndicator001, TestSize.Level1)
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
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 346.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 547.5);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintNormalIndicator002, TestSize.Level1)
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
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 206.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 547.5);
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintPressIndicator001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintPressIndicator002, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintHoverIndicator001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintHoverIndicator002, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
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
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick002, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick003, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperInitIndicator001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperInitIndicator002, TestSize.Level1)
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
     * @tc.expected: swiperNode->GetLastChild is 1.
     */
    swiperPattern->InitIndicator();
    ASSERT_EQ(swiperNode->GetLastChild(), 1);
}

/**
 * @tc.name: SwiperInitIndicator003
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator003, TestSize.Level1)
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
    ASSERT_EQ(swiperNode->GetLastChild()->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator004
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator004, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperInitIndicator005, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SetDotIndicatorStyle001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SetDigitIndicatorStyle001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

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
HWTEST_F(SwiperTestNg, DotIndicatorModifier001, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, DotIndicatorModifier002, TestSize.Level1)
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
HWTEST_F(SwiperTestNg, DotIndicatorModifier003, TestSize.Level1)
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

/**
 * @tc.name: SwiperDistributedTest001
 * @tc.desc: Test the distributed capability of Swiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    auto swiperLayoutProperty = pattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set Index.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    swiperLayoutProperty->UpdateIndex(1);
    std::string ret = pattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":1})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":1})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(swiperLayoutProperty->GetIndexValue(0), 1);
    restoreInfo_ = R"({"Index":0})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(swiperLayoutProperty->GetIndexValue(0), 0);
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(swiperLayoutProperty->GetIndexValue(0), 0);
}

/**
 * @tc.name: ArrowOnModifyDone001
 * @tc.desc: Test ArrowOnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ArrowOnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_NE(swiperPattern, nullptr);

    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    EXPECT_NE(leftArrowNode, nullptr);

    frameNode->AddChild(leftArrowNode);

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(leftArrowPattern, nullptr);

    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());

    EXPECT_NE(leftSwiperArrowLayoutProperty, nullptr);
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);
    /**
     * @tc.steps: step3. call OnModifyDone.
     * @tc.expected: leftArrowPattern->isFirstCreate_ is false.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(1);

    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);
}

/**
 * @tc.name: ArrowOnModifyDone002
 * @tc.desc: Test ArrowOnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ArrowOnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_NE(swiperPattern, nullptr);

    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    EXPECT_NE(leftArrowNode, nullptr);

    frameNode->AddChild(leftArrowNode);

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(leftArrowPattern, nullptr);

    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());

    EXPECT_NE(leftSwiperArrowLayoutProperty, nullptr);
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);
    leftSwiperArrowLayoutProperty->UpdateIsShowBackground(true);
    leftSwiperArrowLayoutProperty->UpdateEnabled(false);
    leftSwiperArrowLayoutProperty->UpdateDirection(Axis::VERTICAL);
    /**
     * @tc.steps: step3. call OnModifyDone.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(AtLeast(1));

    leftArrowPattern->OnModifyDone();
    EXPECT_EQ(leftArrowPattern->isFirstCreate_, false);

    leftArrowPattern->OnModifyDone();
    auto firstChild = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG, imageSourceInfo->GetResourceId());
}

/**
 * @tc.name: UpdateArrowContent001
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateArrowContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_NE(swiperPattern, nullptr);

    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    EXPECT_NE(leftArrowNode, nullptr);

    frameNode->AddChild(leftArrowNode);

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(leftArrowPattern, nullptr);

    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());

    EXPECT_NE(leftSwiperArrowLayoutProperty, nullptr);
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(5);

    leftArrowPattern->OnModifyDone();
    EXPECT_EQ(leftArrowPattern->isFirstCreate_, false);

    /**
     * @tc.steps: step3. call UpdateArrowContent.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG.
     */
    leftArrowPattern->UpdateArrowContent();
    auto firstChild = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG, imageSourceInfo->GetResourceId());
}

/**
 * @tc.name: UpdateArrowContent002
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateArrowContent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();
    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_NE(swiperPattern, nullptr);

    auto rightArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG,
        swiperPattern->GetRightButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    EXPECT_NE(rightArrowNode, nullptr);

    frameNode->AddChild(rightArrowNode);

    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(rightArrowPattern, nullptr);

    auto rightSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(rightArrowPattern->GetSwiperArrowLayoutProperty());

    EXPECT_NE(rightSwiperArrowLayoutProperty, nullptr);
    rightSwiperArrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    rightSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    rightSwiperArrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);
    rightSwiperArrowLayoutProperty->UpdateDirection(Axis::VERTICAL);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(5);

    rightArrowPattern->OnModifyDone();
    EXPECT_EQ(rightArrowPattern->isFirstCreate_, false);

    /**
     * @tc.steps: step3. call UpdateArrowContent.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG.
     */
    rightArrowPattern->UpdateArrowContent();
    auto firstChild = AceType::DynamicCast<FrameNode>(rightArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG, imageSourceInfo->GetResourceId());
}

/**
 * @tc.name: SetButtonVisible001
 * @tc.desc: Test SetButtonVisible
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetButtonVisible001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrowNode, nullptr);
    frameNode->AddChild(leftArrowNode);

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(leftArrowPattern, nullptr);

    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    ASSERT_NE(leftSwiperArrowLayoutProperty, nullptr);
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(5);

    leftArrowPattern->OnModifyDone();
    EXPECT_EQ(leftArrowPattern->isFirstCreate_, false);

    /**
     * @tc.cases: case3.1 Selected point is not at both ends and RenderContext.SetVisible() will be called.
     */
    leftArrowPattern->index_ = 1;
    leftSwiperArrowLayoutProperty->UpdateHoverShow(true);
    leftArrowPattern->SetButtonVisible(false);

    /**
     * @tc.cases: case3.2 Selected point is not at both ends and RenderContext.SetVisible() will be called.
     */
    leftSwiperArrowLayoutProperty->UpdateHoverShow(false);
    leftArrowPattern->SetButtonVisible(false);

    /**
     * @tc.cases: case3.3 Selected point is first point and loop value is false RenderContext.SetVisible() will be
     * called..
     */
    leftArrowPattern->index_ = 0;
    leftSwiperArrowLayoutProperty->UpdateLoop(false);
    leftArrowPattern->SetButtonVisible(true);

    /**
     * @tc.cases: case3.4 Selected point is first point and loop value is true RenderContext.SetVisible() will be
     * called.
     */
    leftSwiperArrowLayoutProperty->UpdateLoop(true);
    leftArrowPattern->SetButtonVisible(false);
}

/**
 * @tc.name: TotalCount001
 * @tc.desc: Test TotalCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, TotalCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrowNode, nullptr);

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(leftArrowPattern, nullptr);

    /**
     * @tc.steps: step3. Add child node.
     */
    auto childCount = 5;
    for (int index = 0; index < childCount; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        frameNode->AddChild(indicatorNode);
    }
    frameNode->AddChild(leftArrowNode);

    /**
     * @tc.steps: step4. call TotalCount.
     * @tc.expected: The totlaCount is childCount - 1.
     */
    auto totalCount = leftArrowPattern->TotalCount();
    EXPECT_NE(totalCount, childCount);
}

/**
 * @tc.name: ButtonOnHover001
 * @tc.desc: Test ButtonOnHover
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ButtonOnHover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrowNode, nullptr);
    frameNode->AddChild(leftArrowNode);

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(leftArrowPattern, nullptr);

    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    ASSERT_NE(leftSwiperArrowLayoutProperty, nullptr);
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(1);

    leftArrowPattern->OnModifyDone();
    ASSERT_NE(leftArrowPattern->isFirstCreate_, true);

    /**
     * @tc.cases: case3.1 isHover is true, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.2 isHover is true, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isTouch_ = false;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.3 isHover is false, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, false);

    /**
     * @tc.cases: case3.4 isHover is false, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isTouch_ = false;
    leftArrowPattern->ButtonOnHover(buttonNode, false);
}

/**
 * @tc.name: ButtonTouchEvent001
 * @tc.desc: Test ButtonTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ButtonTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::HORIZONTAL;
    indicatorType_ = SwiperIndicatorType::DOT;
    CommomAttrInfo();

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step2. Create leftArrowPattern.
     */
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrowNode, nullptr);
    frameNode->AddChild(leftArrowNode);

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(leftArrowPattern, nullptr);

    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    ASSERT_NE(leftSwiperArrowLayoutProperty, nullptr);
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(ARROW_BACKGROUND_SIZE);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(ARROW_SIZE);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(1);

    leftArrowPattern->OnModifyDone();
    ASSERT_NE(leftArrowPattern->isFirstCreate_, true);

    /**
     * @tc.cases: case3.1 isHover is true, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isHover_ = true;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::DOWN);

    /**
     * @tc.cases: case3.2 isHover is true, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isHover_ = false;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::DOWN);

    /**
     * @tc.cases: case3.3 isHover is false, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isHover_ = true;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::UP);

    /**
     * @tc.cases: case3.4 isHover is false, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    EXPECT_CALL(*mockRenderContext, BlendBgColor(_)).Times(1);
    leftArrowPattern->isHover_ = false;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::CANCEL);
}

/**
 * @tc.name: SwiperPatternGetNextFocusNode001
 * @tc.desc: Test SwiperPattern SwiperPatternGetNextFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetNextFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, swiperPattern->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    frameNode->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    frameNode->AddChild(rightArrow);

    /**
     * @tc.steps: step3.1 call GetNextFocusNode.
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_INDICATOR_ETS_TAG.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    swiperPattern->GetNextFocusNode(FocusStep::NONE, rightArrow->GetFocusHub());
    auto curFocusNode = swiperPattern->GetNextFocusNode(FocusStep::LEFT, rightArrow->GetFocusHub()).Upgrade();
    ASSERT_NE(curFocusNode, nullptr);
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_INDICATOR_ETS_TAG);
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.cases: case3.2
     * @tc.expected: isLastIndicatorFocused_ is false.
     */
    swiperPattern->GetNextFocusNode(FocusStep::LEFT, curFocusNode);
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.cases: case3.3
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_INDICATOR_ETS_TAG.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    curFocusNode = swiperPattern->GetNextFocusNode(FocusStep::RIGHT, leftArrow->GetFocusHub()).Upgrade();
    ASSERT_NE(curFocusNode, nullptr);
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_INDICATOR_ETS_TAG);
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);

    /**
     * @tc.cases: case3.4
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_RIGHT_ARROW_ETS_TAG.
     */
    curFocusNode = swiperPattern->GetNextFocusNode(FocusStep::RIGHT, curFocusNode).Upgrade();
    ASSERT_NE(curFocusNode, nullptr);
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_RIGHT_ARROW_ETS_TAG);

    /**
     * @tc.cases: case3.5
     * @tc.expected: isLastIndicatorFocused_ is false.
     */
    swiperPattern->GetNextFocusNode(FocusStep::RIGHT, curFocusNode);
    EXPECT_FALSE(swiperPattern->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPatternPreviousFocus001
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, swiperPattern->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    frameNode->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    frameNode->AddChild(rightArrow);

    /**
     * @tc.steps: step3. call PreviousFocus.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->currentIndex_ = 0;
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateHoverShow(true);
    swiperPattern->PreviousFocus(indicatorNode->GetFocusHub());
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPatternPreviousFocus002
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    frameNode->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    frameNode->AddChild(rightArrow);

    /**
     * @tc.steps: step3.1 call PreviousFocus.
     * @tc.expected: rightArrow->GetFocusHub()->parentFocusable is true.
     */
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->currentIndex_ = 0;
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateHoverShow(true);
    swiperPattern->PreviousFocus(rightArrow->GetFocusHub());
    EXPECT_TRUE(rightArrow->GetFocusHub()->parentFocusable_);
    /**
     * @tc.cases: case3.2
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_LEFT_ARROW_ETS_TAG.
     */
    swiperPattern->currentIndex_ = 1;
    auto curFocusNode = swiperPattern->PreviousFocus(rightArrow->GetFocusHub()).Upgrade();
    ASSERT_NE(curFocusNode, nullptr);
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperPatternPreviousFocus003
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus003, TestSize.Level2)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step3. call PreviousFocus.
     * @tc.expected: frameNode->GetFocusHub()->parentFocusable is true.
     */
    swiperPattern->PreviousFocus(frameNode->GetFocusHub());
    EXPECT_TRUE(frameNode->GetFocusHub()->parentFocusable_);
}

/**
 * @tc.name: SwiperPatternNextFocus001
 * @tc.desc: Test SwiperPattern SwiperPatternNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, swiperPattern->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    frameNode->AddChild(indicatorNode);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    frameNode->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    frameNode->AddChild(rightArrow);

    /**
     * @tc.steps: step3. call NextFocus.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->currentIndex_ = swiperPattern->TotalCount() - 1;
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateHoverShow(true);
    swiperPattern->NextFocus(indicatorNode->GetFocusHub());
    EXPECT_TRUE(swiperPattern->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPatternNextFocus002
 * @tc.desc: Test SwiperPattern SwiperPatternNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    frameNode->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    frameNode->AddChild(rightArrow);

    /**
     * @tc.steps: step3.1 call PreviousFocus.
     * @tc.expected: leftArrow->GetFocusHub()->parentFocusable is true.
     */
    swiperPattern->isLastIndicatorFocused_ = false;
    swiperPattern->currentIndex_ = swiperPattern->TotalCount() - 1;
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateLoop(false);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateHoverShow(true);
    swiperPattern->NextFocus(leftArrow->GetFocusHub());
    EXPECT_TRUE(leftArrow->GetFocusHub()->parentFocusable_);
}

/**
 * @tc.name: SwiperPatternNextFocus003
 * @tc.desc: Test SwiperPattern SwiperPatternNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus003, TestSize.Level2)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step3. call NextFocus.
     * @tc.expected: frameNode->GetFocusHub()->parentFocusable is true.
     */
    swiperPattern->NextFocus(frameNode->GetFocusHub());
    EXPECT_TRUE(frameNode->GetFocusHub()->parentFocusable_);
}

/**
 * @tc.name: SwiperArrowPatternButtonClickEvent001
 * @tc.desc: Test SwiperArrowPattern ButtonClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperArrowPatternButtonClickEvent001, TestSize.Level2)
{
    /**
     * @tc.steps: step1. Create swiper node.
     */
    indicatorDirection_ = Axis::VERTICAL;
    indicatorType_ = SwiperIndicatorType::DIGIT;
    CommomAttrInfo();

    /**
     * @tc.steps: step2. Create SwiperPattern.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    frameNode->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    frameNode->AddChild(rightArrow);

    auto leftArrowPattern = leftArrow->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(leftArrowPattern, nullptr);
    auto rightArrowPattern = rightArrow->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(rightArrowPattern, nullptr);

    /**
     * @tc.steps: step3. call ButtonClickEvent.
     * @tc.expected: isOnButtonClick is true.
     */
    auto swiperController = swiperPattern->GetSwiperController();
    auto isOnButtonClick = false;
    swiperController->SetShowPrevImpl([&isOnButtonClick]() { isOnButtonClick = true; });
    leftArrowPattern->ButtonClickEvent();
    EXPECT_TRUE(isOnButtonClick);

    isOnButtonClick = false;
    swiperController->SetShowNextImpl([&isOnButtonClick]() { isOnButtonClick = true; });
    rightArrowPattern->ButtonClickEvent();
    EXPECT_TRUE(isOnButtonClick);
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm001
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCreateLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->jumpIndex_ = 0;
    swiperPattern->targetIndex_ = 1;
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = 1.0f;

    /**
     * @tc.steps: step3. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->CreateLayoutAlgorithm();
            swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
        }
        swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    }
}

/**
 * @tc.name: SwiperPatternOnIndexChange001
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnIndexChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    swiperNode->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, swiperPattern->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    swiperNode->AddChild(indicatorNode);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    swiperPattern->leftButtonId_.reset();
    ASSERT_EQ(swiperPattern->TotalCount(), 2);
    swiperPattern->oldIndex_ = 1;
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(2);

    /**
     * @tc.steps: step3. call OnIndexChange.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->OnIndexChange();
}

/**
 * @tc.name: SwiperPatternGetLoopIndex001
 * @tc.desc: GetLoopIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetLoopIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    swiperNode->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, swiperPattern->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    swiperNode->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call GetLoopIndex.
     * @tc.expected: Related function runs ok.
     */
    int32_t originalIndex = -1;
    swiperPattern->GetLoopIndex(originalIndex);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    swiperNode->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(indicatorNodeLeftArrow, nullptr);
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    swiperNode->AddChild(indicatorNode);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    swiperPattern->isInit_ = true;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
            swiperPattern->isInit_ = false;
            if (i == 0) {
                config.skipLayout = false;
                continue;
            }
            config.skipLayout = true;
        }
        config.skipMeasure = false;
    }
    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    struct SwiperItemInfo swiperItemInfo3;
    struct SwiperItemInfo swiperItemInfo4;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo2.startPos = 1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo3.startPos = -1.0f;
    swiperItemInfo3.endPos = 0.0f;
    swiperItemInfo4.startPos = 1.0f;
    swiperItemInfo4.endPos = 1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
    swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    swiperPattern->indicatorDoingAnimation_ = false;
    swiperPattern->jumpIndex_ = 1;

    for (int i = 0; i <= 1; i++) {
        swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
        swiperPattern->indicatorDoingAnimation_ = true;
        swiperPattern->targetIndex_ = 1;
        AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
            ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    }

    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    AceType::DynamicCast<SwiperPaintProperty>(swiperNode->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
            if (i == 0) {
                AceType::DynamicCast<SwiperPaintProperty>(swiperNode->paintProperty_)
                    ->UpdateEdgeEffect(EdgeEffect::FADE);
                continue;
            }
            AceType::DynamicCast<SwiperPaintProperty>(swiperNode->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
        }
        AceType::DynamicCast<SwiperLayoutProperty>(swiperNode->layoutProperty_)->padding_ =
            std::make_unique<PaddingProperty>();
    }
}

/**
 * @tc.name: SwiperPatternSwipeTo001
 * @tc.desc: SwipeTo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSwipeTo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    int32_t index = -1;
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    swiperPattern->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call SwipeTo.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->SwipeTo(index);
            if (i == 0) {
                swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(0);
                continue;
            }
            swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(400);
        }
        swiperPattern->isVisible_ = true;
    }
}

/**
 * @tc.name: SwiperPatternShowNext001
 * @tc.desc: ShowNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowNext001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    ASSERT_EQ(swiperPattern->TotalCount(), 2);
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    ASSERT_TRUE(swiperPattern->IsLoop());
    swiperPattern->currentIndex_ = 1;
    swiperPattern->preTargetIndex_ = -1;

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    swiperNode->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(indicatorNodeLeftArrow, nullptr);
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    swiperNode->AddChild(indicatorNode);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    swiperPattern->leftButtonId_.reset();
    ASSERT_EQ(swiperPattern->TotalCount() - swiperPattern->GetDisplayCount(), 4);

    /**
     * @tc.steps: step2. call ShowNext.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->ShowNext();
            if (i == 0) {
                swiperPattern->preTargetIndex_ = 0;
                ASSERT_EQ(swiperPattern->GetLoopIndex(swiperPattern->preTargetIndex_.value()), 0);
                continue;
            }
            swiperPattern->preTargetIndex_ = -1;
            ASSERT_EQ(swiperPattern->GetLoopIndex(swiperPattern->preTargetIndex_.value()), 4);
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
        ASSERT_FALSE(swiperPattern->IsLoop());
    }

    swiperPattern->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->ShowNext();
            if (i == 0) {
                swiperPattern->currentIndex_ = 5;
                continue;
            }
            swiperPattern->currentIndex_ = 1;
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
        ASSERT_FALSE(swiperPattern->IsLoop());
    }
}

/**
 * @tc.name: SwiperPatternShowPrevious001
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowPrevious001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    ASSERT_EQ(swiperPattern->TotalCount(), 5);
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    ASSERT_TRUE(swiperPattern->IsLoop());
    swiperPattern->currentIndex_ = 0;
    swiperPattern->preTargetIndex_ = -1;

    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    swiperPattern->leftButtonId_.reset();
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(indicatorNodeLeftArrow, nullptr);
    indicatorNode->AddChild(indicatorNodeLeftArrow);

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->ShowPrevious();
            if (i == 0) {
                swiperPattern->preTargetIndex_ = 0;
                ASSERT_EQ(swiperPattern->GetLoopIndex(swiperPattern->preTargetIndex_.value()), 0);
                continue;
            }
            swiperPattern->preTargetIndex_ = -1;
            ASSERT_EQ(swiperPattern->GetLoopIndex(swiperPattern->preTargetIndex_.value()), 3);
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
        ASSERT_FALSE(swiperPattern->IsLoop());
    }

    swiperPattern->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->ShowPrevious();
            if (i == 0) {
                swiperPattern->currentIndex_ = 1;
                continue;
            }
            swiperPattern->currentIndex_ = 0;
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
        ASSERT_FALSE(swiperPattern->IsLoop());
    }

    swiperPattern->preTargetIndex_ = 1;
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    swiperPattern->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->ShowPrevious();
            swiperPattern->preTargetIndex_.reset();
        }
        swiperPattern->isVisible_ = false;
    }
}

/**
 * @tc.name: SwiperPatternFinishAnimation001
 * @tc.desc: FinishAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternFinishAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->swiperController_ = AceType::MakeRefPtr<SwiperController>();
    ASSERT_NE(swiperPattern->swiperController_, nullptr);

    /**
     * @tc.steps: step2. call FinishAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->FinishAnimation();
        swiperPattern->swiperController_->SetFinishCallback([]() {});
        ASSERT_NE(swiperPattern->swiperController_->finishCallback_, nullptr);
    }
}

/**
 * @tc.name: SwiperPatternStopSpringAnimation001
 * @tc.desc: StopSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternStopSpringAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->springController_ = AceType::MakeRefPtr<Animator>();
    ASSERT_NE(swiperPattern->springController_, nullptr);
    swiperPattern->springController_->status_ = Animator::Status::RUNNING;

    /**
     * @tc.steps: step2. call StopSpringAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->StopSpringAnimation();
        swiperPattern->springController_->status_ = Animator::Status::STOPPED;
    }
}

/**
 * @tc.name: SwiperPatternInitSwiperController001
 * @tc.desc: InitSwiperController
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitSwiperController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->swiperController_ = AceType::MakeRefPtr<SwiperController>();
    ASSERT_NE(swiperPattern->swiperController_, nullptr);
    swiperPattern->swiperController_->showPrevImpl_ = nullptr;

    /**
     * @tc.steps: step2. call InitSwiperController.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->InitSwiperController();
    swiperPattern->swiperController_->swipeToImpl_(0, true);
    swiperPattern->swiperController_->swipeToWithoutAnimationImpl_(0);
    swiperPattern->swiperController_->showNextImpl_();
    swiperPattern->swiperController_->showPrevImpl_();
    swiperPattern->swiperController_->finishImpl_();
}

/**
 * @tc.name: SwiperPatternInitTouchEvent001
 * @tc.desc: InitTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->touchEvent_ = nullptr;
    auto gestureHub = swiperNode->GetOrCreateGestureEventHub();
    auto info = new TouchEventInfo("swiper_test");

    /**
     * @tc.steps: step2. call InitTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->InitTouchEvent(gestureHub);
    swiperPattern->touchEvent_->callback_(*info);
}

/**
 * @tc.name: SwiperPatternAutoPlay001
 * @tc.desc: StopAutoPlay and StartAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAutoPlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    swiperPattern->isVisible_ = true;

    /**
     * @tc.steps: step2. call InitTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->StopAutoPlay();
    swiperPattern->StartAutoPlay();
}

/**
 * @tc.name: SwiperPatternHandleTouchUp001
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchUp001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->controller_ = AceType::MakeRefPtr<Animator>();
    ASSERT_NE(swiperPattern->controller_, nullptr);
    swiperPattern->controller_->status_ = Animator::Status::PAUSED;
    swiperPattern->springController_ = AceType::MakeRefPtr<Animator>();
    swiperPattern->springController_->status_ = Animator::Status::PAUSED;

    /**
     * @tc.steps: step2. call HandleTouchUp.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->HandleTouchUp();
}

/**
 * @tc.name: SwiperPatternOnVisibleChange001
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnVisibleChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->isInit_ = false;
    swiperPattern->isWindowShow_ = false;

    /**
     * @tc.steps: step2. call OnVisibleChange.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->OnVisibleChange(true);
}

/**
 * @tc.name: SwiperPatternPlaySpringAnimation001
 * @tc.desc: PlaySpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlaySpringAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    double dragVelocity = 1.0;
    swiperPattern->springController_ = nullptr;
    swiperPattern->currentOffset_ = 1;
    swiperPattern->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));

    /**
     * @tc.steps: step2. call PlaySpringAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->PlaySpringAnimation(dragVelocity);
            if (i == 1) {
                break;
            }
            swiperPattern->springController_ = AceType::MakeRefPtr<Animator>();
            ASSERT_NE(swiperPattern->springController_, nullptr);
            swiperPattern->currentOffset_ = 0;
        }
        swiperPattern->contentMainSize_ = -1.0f;
    }
    double position = 1.0;
    swiperPattern->contentMainSize_ = 1.0f;
    swiperPattern->PlaySpringAnimation(dragVelocity);
    ScrollMotion::ValueCallback valueCallback = swiperPattern->springController_->motion_->callbacks_.begin()->second;
    valueCallback.callback_(position);
    Animator::StatusCallback statusCallback1 = swiperPattern->springController_->startCallbacks_.begin()->second;
    statusCallback1.callback_();
    Animator::StatusCallback statusCallback2 = swiperPattern->springController_->stopCallbacks_.begin()->second;
    statusCallback2.callback_();
}

/**
 * @tc.name: SwiperPatternPlayFadeAnimation001
 * @tc.desc: PlayFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayFadeAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->fadeOffset_ = 0.0f;
    swiperPattern->fadeController_ = nullptr;

    /**
     * @tc.steps: step2. call PlayFadeAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->PlayFadeAnimation();
            if (i == 1) {
                break;
            }
            swiperPattern->fadeOffset_ = 1.0f;
            swiperPattern->fadeController_ = nullptr;
        }
        swiperPattern->fadeController_ = AceType::MakeRefPtr<Animator>();
    }
    double position = 1.0;
    swiperPattern->PlayFadeAnimation();
    Animation<double>::ValueCallback valueCallback =
        static_cast<CurveAnimation<double>*>(AceType::RawPtr(swiperPattern->fadeController_->interpolators_.front()))
            ->callbacks_.begin()
            ->second;
    valueCallback.callback_(position);
    Animator::StatusCallback statusCallback1 = swiperPattern->fadeController_->startCallbacks_.begin()->second;
    statusCallback1.callback_();
    Animator::StatusCallback statusCallback2 = swiperPattern->fadeController_->stopCallbacks_.begin()->second;
    statusCallback2.callback_();
}

/**
 * @tc.name: SwiperPatternPlayPropertyTranslateAnimation001
 * @tc.desc: PlayPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayPropertyTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::HORIZONTAL);
    float translate = 0.1f;
    int32_t nextIndex = 1;
    float velocity = 0.2f;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    swiperPattern->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));

    /**
     * @tc.steps: step2. call PlayPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternUpdateOffsetAfterPropertyAnimation001
 * @tc.desc: UpdateOffsetAfterPropertyAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateOffsetAfterPropertyAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    float offset = 0.1f;

    /**
     * @tc.steps: step2. call UpdateOffsetAfterPropertyAnimation.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->UpdateOffsetAfterPropertyAnimation(offset);
}

/**
 * @tc.name: SwiperPatternOnPropertyTranslateAnimationFinish001
 * @tc.desc: OnPropertyTranslateAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnPropertyTranslateAnimationFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto offset = OffsetF(0.1f, 0.2f);
    swiperPattern->usePropertyAnimation_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    swiperPattern->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(swiperPattern->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call OnPropertyTranslateAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->OnPropertyTranslateAnimationFinish(offset);
        swiperPattern->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternStopPropertyTranslateAnimation001
 * @tc.desc: StopPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternStopPropertyTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->usePropertyAnimation_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    swiperPattern->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(swiperPattern->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call StopPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->StopPropertyTranslateAnimation();
        swiperPattern->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternGetCurveIncludeMotion001
 * @tc.desc: GetCurveIncludeMotion
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCurveIncludeMotion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(nullptr);
    float velocity = 0.1f;
    float mass = 0.1f;
    float stiffness = 0.2f;
    float damping = 0.3f;
    auto curve1 = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);
    auto curve2 = AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);

    /**
     * @tc.steps: step2. call GetCurveIncludeMotion.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperPattern->GetCurveIncludeMotion(velocity);
                if (i == 1) {
                    curve2->UpdateVelocity(-0.1f);
                    continue;
                }
                swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
                curve1->UpdateVelocity(-0.1f);
            }
            curve1->UpdateVelocity(0.1f);
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve2);
        curve2->UpdateVelocity(0.1f);
    }
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation001
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->indicatorId_.reset();
    float translate = 0.1f;

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->PlayIndicatorTranslateAnimation(translate);
            if (i == 1) {
                break;
            }
            swiperPattern->indicatorId_ = 1;
            swiperPattern->indicatorController_ = nullptr;
        }
        swiperPattern->indicatorController_ = AceType::MakeRefPtr<Animator>();
    }
}

/**
 * @tc.name: SwiperPatternPlayTranslateAnimation001
 * @tc.desc: PlayTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    float startPos = 0.1f;
    float endPos = 0.2f;
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    float velocity = 0.1f;
    float mass = 0.1f;
    float stiffness = 0.2f;
    float damping = 0.3f;
    swiperPattern->controller_ = nullptr;
    auto curve1 = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);

    /**
     * @tc.steps: step2. call PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->PlayTranslateAnimation(startPos, endPos, nextIndex, restartAutoPlay, velocity);
        swiperPattern->controller_ = AceType::MakeRefPtr<Animator>();
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
    }

    double value = 1.0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperPattern->PlayTranslateAnimation(startPos, endPos, nextIndex, restartAutoPlay, velocity);
                Animation<double>::ValueCallback valueCallback = static_cast<CurveAnimation<double>*>(
                    AceType::RawPtr(swiperPattern->controller_->interpolators_.front()))
                                                                     ->callbacks_.begin()
                                                                     ->second;
                valueCallback.callback_(value);
                value = 0;
                startPos = 0.0f;
                endPos = 0.0f;
            }
            endPos = 0.1f;
        }
        endPos = 0.0f;
        startPos = 0.1f;
    }
}

/**
 * @tc.name: SwiperPatternGetRemainingOffset001
 * @tc.desc: GetRemainingOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetRemainingOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));

    /**
     * @tc.steps: step2. call GetRemainingOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->GetRemainingOffset();
            if (i == 1) {
                swiperPattern->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
                continue;
            }
            swiperPattern->itemPosition_.clear();
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
    }
    swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    swiperPattern->GetRemainingOffset();
}

/**
 * @tc.name: SwiperPatternCalculateDisplayCount001
 * @tc.desc: CalculateDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCalculateDisplayCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto dimension = Dimension(1);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateMinSize(dimension);

    /**
     * @tc.steps: step2. call CalculateDisplayCount.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->CalculateDisplayCount();
}

/**
 * @tc.name: SwiperPatternOnTouchTestHit001
 * @tc.desc: OnTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTouchTestHit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step2. call OnTouchTestHit.
     * @tc.expected: Related function runs ok.
     */
    CommonFunc callback = [] {};
    swiperPattern->isTouchDown_ = false;
    swiperPattern->swiperController_->SetRemoveTabBarEventCallback(callback);
    swiperPattern->OnTouchTestHit(SourceType::TOUCH);
    EXPECT_NE(swiperPattern->swiperController_->GetRemoveTabBarEventCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation002
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, swiperPattern->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    swiperNode->AddChild(indicatorNode);

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    swiperPattern->swiperController_->SetTurnPageRateCallback(callback);
    swiperPattern->PlayIndicatorTranslateAnimation(0.1f);
    EXPECT_NE(swiperPattern->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    swiperNode->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(indicatorNodeLeftArrow, nullptr);
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    swiperNode->AddChild(indicatorNode);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    swiperPattern->isInit_ = true;
    config.skipMeasure = false;
    config.skipLayout = false;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    swiperPattern->swiperController_->SetTurnPageRateCallback(callback);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    swiperPattern->isDragging_ = true;
    swiperPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_NE(swiperPattern->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternGetDisplayCount002
 * @tc.desc: GetDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetDisplayCount002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */

    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperController = swiperPattern->GetSwiperController();

    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    swiperPattern->leftButtonId_.reset();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(SWIPER_IDEAL_WIDTH, SWIPER_IDEAL_HEIGHT));
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    swiperLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step2. Set the FrameSize of the swiper.
     */
    swiperNode->GetGeometryNode()->SetFrameSize(CONTAINER_SIZE);
    Dimension SWIPER_MINSIZE = 50.0_vp;

    for (int i = 0; i < 4; i++) {
        /**
         * @tc.steps: step3. Update the MinSize of one swiper item.
         * @tc.expected: Related function runs ok.
         */
        swiperLayoutProperty->UpdateMinSize(SWIPER_MINSIZE);
        EXPECT_EQ(swiperLayoutProperty->GetMinSize().value_or(Dimension(0.0, DimensionUnit::VP)), SWIPER_MINSIZE);

        /**
         * @tc.steps: step4. Call GetDisplayCount.
         * @tc.expected: The return value is correct.
         */
        float displaycount = static_cast<int32_t>(
            floor((CONTAINER_SIZE.Width() - 2 * SWIPER_MARGIN.ConvertToPx() + SWIPER_GUTTER.ConvertToPx()) /
                  (SWIPER_MINSIZE.ConvertToPx() + SWIPER_GUTTER.ConvertToPx())));
        displaycount = displaycount > 0 ? displaycount : 1;
        displaycount = displaycount > swiperPattern->TotalCount() ? swiperPattern->TotalCount() : displaycount;
        EXPECT_EQ(swiperPattern->GetDisplayCount(), displaycount);

        constexpr Dimension delta = 200.0_vp;
        SWIPER_MINSIZE += delta;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackwardItem001
 * @tc.desc: LayoutBackwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackwardItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t currentIndex = 1;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    /**
     * @tc.steps: step2. call LayoutBackwardItem.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackwardItem(
                &layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->isLoop_ = true;
                continue;
            }
            swiperLayoutAlgorithm->isLoop_ = false;
        }
        currentIndex = 0;
    }

    currentIndex = 1;
    indicatorNode->tag_ = V2::SWIPER_LEFT_ARROW_ETS_TAG;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackwardItem(
                &layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
            if (i == 1) {
                indicatorNode->tag_ = V2::SWIPER_RIGHT_ARROW_ETS_TAG;
                continue;
            }
            indicatorNode->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
        }
        indicatorNode->tag_ = V2::SWIPER_ETS_TAG;
    }
}

// /**
//  * @tc.name: SwiperLayoutAlgorithmOffScreenLayoutDirection001
//  * @tc.desc: OffScreenLayoutDirection
//  * @tc.type: FUNC
//  */
// HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmOffScreenLayoutDirection001, TestSize.Level1)
// {
//     /**
//      * @tc.steps: step1. Create swipernode.
//      */
//     auto* stack = ViewStackProcessor::GetInstance();
//     auto swiperNode =
//         FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
//     stack->Push(swiperNode);
//     auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
//     ASSERT_NE(swiperPattern, nullptr);
//     auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
//     swiperLayoutAlgorithm->targetIndex_ = 1;
//     struct SwiperItemInfo swiperItemInfo1;
//     swiperItemInfo1.startPos = -1.0f;
//     swiperItemInfo1.endPos = -1.0f;
//     swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));

//     /**
//      * @tc.steps: step2. call OffScreenLayoutDirection.
//      * @tc.expected: Related function runs ok.
//      */
//     for (int i = 0; i <= 1; i++) {
//         for (int j = 0; j <= 1; j++) {
//             swiperLayoutAlgorithm->OffScreenLayoutDirection();
//             if (i == 1) {
//                 swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
//                 continue;
//             }
//             swiperLayoutAlgorithm->itemPosition_.clear();
//         }
//         swiperLayoutAlgorithm->targetIndex_.reset();
//     }

//     swiperLayoutAlgorithm->targetIndex_ = 1;
//     swiperLayoutAlgorithm->itemPosition_.clear();
//     swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
//     for (int i = 0; i <= 1; i++) {
//         swiperLayoutAlgorithm->OffScreenLayoutDirection();
//         swiperLayoutAlgorithm->targetIndex_ = -1;
//     }
// }

/**
 * @tc.name: SwiperPatternUpdateAnimationProperty001
 * @tc.desc: UpdateAnimationProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateAnimationProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    };
    swiperPattern->isDragging_ = true;
    float velocity = 0.1f;

    /**
     * @tc.steps: step2. call UpdateAnimationProperty.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j >= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperPattern->UpdateAnimationProperty(velocity);
                swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
                if (i == 1) {
                    velocity = -200.1f;
                    continue;
                }
                if (i == 1 && j == 1) {
                    break;
                }
                velocity = 0.0f;
            }
            if (i == 1) {
                swiperPattern->isDragging_ = false;
                continue;
            }
            velocity = 0.1f;
        }
        velocity = 200.1f;
    }
}

/**
 * @tc.name: SwiperPatternGetFirstItemInfoInVisibleArea001
 * @tc.desc: GetFirstItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetFirstItemInfoInVisibleArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    swiperPattern->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetFirstItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->GetFirstItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            swiperPattern->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            swiperPattern->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            swiperPattern->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateNextMargin(dimension);
            swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->layoutConstraint_->scaleProperty =
                ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->ResetNextMargin();
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->layoutConstraint_->scaleProperty =
            ScaleProperty { 0.0f, 0.0f, 0.0f };
    }
}

/**
 * @tc.name: SwiperPatternGetTranslateLength001
 * @tc.desc: GetTranslateLength
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetTranslateLength001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetTranslateLength.
     * @tc.expected: Related function runs ok.
     */
    swiperPattern->GetTranslateLength();
}

/**
 * @tc.name: SwiperPatternGetSecondItemInfoInVisibleArea001
 * @tc.desc: GetSecondItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetSecondItemInfoInVisibleArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    swiperPattern->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetSecondItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->GetSecondItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            swiperPattern->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            swiperPattern->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            swiperPattern->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdatePrevMargin(dimension);
            swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->layoutConstraint_->scaleProperty =
                ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->ResetPrevMargin();
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->layoutConstraint_->scaleProperty =
            ScaleProperty { 0.0f, 0.0f, 0.0f };
    }
    swiperPattern->itemPosition_.erase(2);
    swiperPattern->GetSecondItemInfoInVisibleArea();
}

/**
 * @tc.name: SwiperPatternPostTranslateTask001
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPostTranslateTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    uint32_t delayTime = 10;
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    };
    swiperPattern->itemPosition_.clear();
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(swiperNode->layoutProperty_, nullptr);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    swiperPattern->leftButtonId_.reset();
    swiperPattern->rightButtonId_.reset();
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);

    /**
     * @tc.steps: step2. call PostTranslateTask.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperPattern->PostTranslateTask(delayTime);
                if (j == 1) {
                    swiperNode->AddChild(leftArrow);
                    continue;
                }
                swiperNode->Clean(false, false);
                swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->ResetMinSize();
                swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
            }
            swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(0);
        }
        swiperPattern->translateTask_ = CancelableCallback<void()>([]() {});
        swiperPattern->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->PostTranslateTask(delayTime);
            if (i == 1) {
                swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
                continue;
            }
            swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
        }
        swiperPattern->itemPosition_.erase(1);
        swiperPattern->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    }
}

/**
 * @tc.name: SwiperPatternRegisterVisibleAreaChange001
 * @tc.desc: RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternRegisterVisibleAreaChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    /**
     * @tc.steps: step2. call RegisterVisibleAreaChange.
     * @tc.expected: Related function runs ok.
     */
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->RegisterVisibleAreaChange();
            if (i == 1) {
                swiperPattern->hasVisibleChangeRegistered_ = false;
            }
            swiperPattern->hasVisibleChangeRegistered_ = true;
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    }

    swiperPattern->isWindowShow_ = false;
    for (int i = 0; i <= 1; i++) {
        swiperPattern->RegisterVisibleAreaChange();
        swiperPattern->isWindowShow_ = true;
        swiperPattern->isVisibleArea_ = true;
        swiperPattern->isVisible_ = true;
    }
}

/**
 * @tc.name: SwiperPatternTriggerEventOnFinish001
 * @tc.desc: TriggerEventOnFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerEventOnFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    int32_t nextIndex = 1;
    swiperPattern->preTargetIndex_ = 1;
    swiperPattern->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call TriggerEventOnFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->TriggerEventOnFinish(nextIndex);
            if (i == 1) {
                break;
            }
            nextIndex = 2;
            swiperPattern->isFinishAnimation_ = true;
        }
        swiperPattern->isFinishAnimation_ = false;
    }
}

/**
 * @tc.name: SwiperPatternArrowHover001
 * @tc.desc: ArrowHover
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternArrowHover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    bool hoverFlag = true;
    swiperPattern->leftButtonId_.reset();
    swiperPattern->rightButtonId_.reset();

    /**
     * @tc.steps: step2. call ArrowHover.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->ArrowHover(hoverFlag);
            if (i == 1) {
                swiperPattern->leftButtonId_.reset();
            }
            swiperPattern->leftButtonId_ = 1;
        }
        swiperPattern->rightButtonId_ = 1;
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToLeft001
 * @tc.desc: TriggerAnimationEndOnSwipeToLeft
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnSwipeToLeft001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToLeft.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->TriggerAnimationEndOnSwipeToLeft();
        swiperPattern->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToRight001
 * @tc.desc: TriggerAnimationEndOnSwipeToRight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnSwipeToRight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToRight.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->TriggerAnimationEndOnSwipeToRight();
        swiperPattern->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternOnTranslateFinish001
 * @tc.desc: OnTranslateFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTranslateFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    bool forceStop = true;
    swiperNode->Clean(false, false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    auto indicatorNode1 = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode1, nullptr);
    auto indicatorNode2 = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode2, nullptr);
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperPattern->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnTranslateFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->OnTranslateFinish(nextIndex, restartAutoPlay, forceStop);
            if (i == 1) {
                swiperPattern->isFinishAnimation_ = false;
                continue;
            }
            swiperPattern->isFinishAnimation_ = true;
            swiperNode->AddChild(indicatorNode1);
            swiperPattern->isVisible_ = false;
        }
        swiperNode->Clean(false, false);
        swiperNode->AddChild(leftArrow);
        swiperNode->AddChild(indicatorNode2);
        forceStop = false;
        swiperPattern->isVisible_ = true;
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(true);
    }
}

/**
 * @tc.name: SwiperPatternCheckAndSetArrowHoverState001
 * @tc.desc: CheckAndSetArrowHoverState
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCheckAndSetArrowHoverState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(swiperNode->paintProperty_, nullptr);
    swiperPattern->currentIndex_ = 1;
    swiperPattern->leftButtonId_ = 1;
    swiperPattern->rightButtonId_ = 1;
    swiperPattern->indicatorId_ = 1;
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto mousePoint = PointF(0.0f, 0.0f);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto indicatorNode1 = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode1, nullptr);

    /**
     * @tc.steps: step2. call CheckAndSetArrowHoverState.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperPattern->CheckAndSetArrowHoverState(mousePoint);
                if (j == 1) {
                    swiperPattern->leftButtonId_ = 1;
                    continue;
                }
                swiperPattern->leftButtonId_.reset();
            }
            swiperPattern->rightButtonId_.reset();
        }
        swiperPattern->indicatorId_.reset();
    }

    swiperPattern->leftButtonId_ = 1;
    swiperPattern->rightButtonId_ = 1;
    swiperPattern->indicatorId_ = 1;
    swiperNode->Clean(false, false);
    swiperNode->AddChild(leftArrow);
    swiperNode->AddChild(indicatorNode);
    swiperNode->AddChild(rightArrow);
    swiperNode->AddChild(indicatorNode1);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(swiperNode->layoutProperty_, nullptr);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIsSidebarMiddle(true);
    swiperPattern->CheckAndSetArrowHoverState(mousePoint);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIsSidebarMiddle(false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->CheckAndSetArrowHoverState(mousePoint);
            if (i == 1) {
                swiperPattern->currentIndex_ = 1;
            }
            swiperPattern->currentIndex_ = 0;
        }
        swiperNode->GetPaintProperty<SwiperPaintProperty>()->UpdateLoop(false);
    }
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::HORIZONTAL);
    for (int i = 0; i <= 1; i++) {
        swiperPattern->CheckAndSetArrowHoverState(mousePoint);
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternHandleMouseEvent001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto info = MouseInfo();
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(swiperNode->layoutProperty_, nullptr);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);

    /**
     * @tc.steps: step2. call HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->HandleMouseEvent(info);
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    }
}

/**
 * @tc.name: SwiperPatternGetCustomPropertyOffset001
 * @tc.desc: GetCustomPropertyOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCustomPropertyOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(swiperNode->layoutProperty_, nullptr);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. call GetCustomPropertyOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->GetCustomPropertyOffset();
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternGetCurrentFirstIndexStartPos001
 * @tc.desc: GetCurrentFirstIndexStartPos
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCurrentFirstIndexStartPos001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetCurrentFirstIndexStartPos.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        ASSERT_EQ(swiperPattern->GetCurrentFirstIndexStartPos(), i == 0 ? 0.0 : 1);
        swiperPattern->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAnimationStart001
 * @tc.desc: OnSpringAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnSpringAnimationStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    swiperPattern->leftButtonId_.reset();
    swiperPattern->rightButtonId_.reset();
    float velocity = 200.0f;
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->Clean(false, false);
    swiperNode->AddChild(leftArrow);
    swiperNode->AddChild(rightArrow);
    swiperPattern->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { -1, 1 }));
    swiperPattern->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->OnSpringAnimationStart(velocity);
        swiperPattern->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAndFadeAnimationFinish001
 * @tc.desc: OnSpringAndFadeAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnSpringAndFadeAnimationFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->Clean(false, false);
    swiperNode->AddChild(leftArrow);
    swiperNode->AddChild(rightArrow);
    swiperPattern->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    swiperPattern->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAndFadeAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->OnSpringAndFadeAnimationFinish();
        swiperPattern->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnFadeAnimationStart001
 * @tc.desc: OnFadeAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnFadeAnimationStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, swiperPattern->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(leftArrow, nullptr);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, swiperPattern->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(rightArrow, nullptr);
    swiperNode->Clean(false, false);
    swiperNode->AddChild(leftArrow);
    swiperNode->AddChild(rightArrow);
    swiperPattern->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    swiperPattern->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnFadeAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperPattern->OnFadeAnimationStart();
        swiperPattern->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternComputeNextIndexByVelocity001
 * @tc.desc: ComputeNextIndexByVelocity
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternComputeNextIndexByVelocity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    float velocity = 0.1f;
    swiperPattern->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 2, 1 }));

    /**
     * @tc.steps: step2. call ComputeNextIndexByVelocity.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperPattern->ComputeNextIndexByVelocity(velocity);
            if (i == 1) {
                continue;
            }
            swiperPattern->itemPosition_.clear();
            swiperPattern->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 2, 1 }));
            velocity = 0;
        }
        velocity = 200;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward001
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->targetIndex_ = 1;
                continue;
            }
            swiperLayoutAlgorithm->targetIndex_ = 0;
        }
        swiperLayoutAlgorithm->forwardFeature_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward001
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t endIndex = 1;
    float endPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            if (i == 1) {
                swiperLayoutAlgorithm->targetIndex_ = 1;
                continue;
            }
            swiperLayoutAlgorithm->targetIndex_ = 0;
        }
        swiperLayoutAlgorithm->backwardFeature_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmSetInactive001
 * @tc.desc: SetInactive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmSetInactive001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    float startMainPos = 0.1f;
    float endMainPos = 0.0f;
    std::optional<int32_t> targetIndex = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
    swiperLayoutAlgorithm->prevMargin_ = 0.0;
    swiperLayoutAlgorithm->nextMargin_ = 0.0;

    /**
     * @tc.steps: step2. call SetInactive.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, targetIndex);
            startMainPos = 3;
        }
        swiperLayoutAlgorithm->prevMargin_ = 1.0;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, targetIndex);
            endMainPos = 3;
        }
        swiperLayoutAlgorithm->nextMargin_ = 1.0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward002
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(false);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (i == 1) {
                break;
            }
            swiperLayoutAlgorithm->SetIsLoop(true);
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateMinSize(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdatePrevMargin(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateNextMargin(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateDisplayCount(1);
        }
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateMinSize(Dimension(-1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdatePrevMargin(Dimension(-1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateNextMargin(Dimension(1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateDisplayCount(0);
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->overScrollFeature_ = false;
            }
            swiperLayoutAlgorithm->overScrollFeature_ = true;
        }
        swiperLayoutAlgorithm->canOverScroll_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward002
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t endIndex = -1;
    float endPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetIsLoop(false);
    swiperLayoutAlgorithm->totalItemCount_ = 1;
    swiperLayoutAlgorithm->itemPosition_.clear();

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            if (i == 1) {
                endIndex = 0;
                continue;
            }
            swiperLayoutAlgorithm->SetIsLoop(true);
        }
        swiperLayoutAlgorithm->SetIsLoop(false);
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->overScrollFeature_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmPlaceDigitChild001
 * @tc.desc: PlaceDigitChild
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmPlaceDigitChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto indicatorWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(indicatorNodeLeftArrow, nullptr);
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(lastLayoutWrapper);
    layoutProperty->UpdateLeft(Dimension(1));
    layoutProperty->UpdateTop(Dimension(1));

    /**
     * @tc.steps: step2. call PlaceDigitChild.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->PlaceDigitChild(indicatorWrapper, layoutProperty);
            if (i == 1) {
                layoutProperty->UpdateDirection(Axis::VERTICAL);
                continue;
            }
            indicatorWrapper->currentChildCount_ = 2;
            layoutProperty->padding_ = std::make_unique<PaddingProperty>();
            layoutProperty->UpdateLeft(Dimension(0));
            layoutProperty->UpdateRight(Dimension(1));
            layoutProperty->UpdateTop(Dimension(0));
            layoutProperty->UpdateBottom(Dimension(1));
        }
        layoutProperty->UpdateRight(Dimension(0));
        layoutProperty->UpdateBottom(Dimension(0));
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetNodeLayoutWrapperByTag001
 * @tc.desc: GetNodeLayoutWrapperByTag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmGetNodeLayoutWrapperByTag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    stack->Push(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(swiperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    ASSERT_NE(indicatorNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        swiperPattern->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    ASSERT_NE(indicatorNodeLeftArrow, nullptr);
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_SMALL);
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    ASSERT_NE(lastChild, nullptr);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SWIPER_CHILD_SIZEF_BIG);
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);
    string tagName = V2::SWIPER_INDICATOR_ETS_TAG;
    layoutWrapper.currentChildCount_ = 0;
    indicatorNode->pattern_ = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(indicatorNode->pattern_, nullptr);
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_ = 1;
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_ = 1;
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->rightButtonId_ = 1;

    /**
     * @tc.steps: step2. call GetNodeLayoutWrapperByTag.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if(i==1 && j==1){
                AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_.reset();
                AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_ = 1;
            }
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->GetNodeLayoutWrapperByTag(&layoutWrapper, tagName);
                if (i==0 && j == 1) {
                    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_.reset();
                    continue;
                }
                else if(i==1 && j==0){
                    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_ = 1;
                    continue;
                }
                else if(i==1 && j==1){
                    break;
                }
                layoutWrapper.currentChildCount_ = 1;
            }
            AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_.reset();
        }
        AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->rightButtonId_.reset();
    }
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_.reset();
    swiperLayoutAlgorithm->GetNodeLayoutWrapperByTag(&layoutWrapper, tagName);
}
} // namespace OHOS::Ace::NG
