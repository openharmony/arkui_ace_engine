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

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/animator.h"
#include "core/animation/spring_curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/custom/custom_node.h"
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
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_WIDTH = 480.f;
constexpr float SWIPER_HEIGHT = 800.f;
constexpr int32_t ITEM_NUMBER = 4;
constexpr int32_t DEFAULT_INTERVAL = 3000;
constexpr int32_t DEFAULT_DURATION = 400;
constexpr int32_t CALL_TIMES = 4;
constexpr float DRAG_SPEED = 500.0f;
constexpr float DRAG_OFFSET_X = 50.0f;
} // namespace

class SwiperTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void CreateWithItem(const std::function<void(SwiperModelNG)>& callback = nullptr);
    void CreateItem(int32_t itemNumber = ITEM_NUMBER);

    void CreateChildWrapperAppendToHostWrapper(
        int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapperNode>& hostWrapper);
    void InitLayoutWrapper(const RefPtr<FrameNode>& frameNode, RefPtr<LayoutAlgorithm>& algorithm,
        RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapperNode>& layoutWrapper);
    void InitChild(RefPtr<LayoutWrapperNode>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode);
    void InitArrowLayoutWrapper(const RefPtr<FrameNode>& frameNode_, const std::string& arrowType,
        RefPtr<FrameNode>& arrowNode, RefPtr<LayoutWrapperNode>& arrowLayoutWrapper);
    void AddArrowChild(const RefPtr<FrameNode>& arrowNode, const RefPtr<LayoutWrapperNode>& arrowLayoutWrapper);
    void CreateSwiperLayoutWrapper(const RefPtr<FrameNode>& frameNode_, RefPtr<LayoutWrapperNode>& swiperLayoutWrapper);

    RefPtr<FrameNode> frameNode_;
    RefPtr<SwiperPattern> pattern_;
    RefPtr<SwiperEventHub> eventHub_;
    RefPtr<SwiperLayoutProperty> layoutProperty_;
    RefPtr<SwiperPaintProperty> paintProperty_;
    RefPtr<SwiperAccessibilityProperty> accessibilityProperty_;
};

void SwiperTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));
}

void SwiperTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void SwiperTestNg::SetUp() {}

void SwiperTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void SwiperTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    eventHub_ = frameNode_->GetEventHub<SwiperEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
}

void SwiperTestNg::CreateWithItem(const std::function<void(SwiperModelNG)>& callback)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    if (callback) {
        callback(model);
    }
    CreateItem();
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void SwiperTestNg::CreateItem(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        TextModelNG model;
        model.Create("text");
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void SwiperTestNg::InitLayoutWrapper(const RefPtr<FrameNode>& frameNode, RefPtr<LayoutAlgorithm>& algorithm,
    RefPtr<FrameNode>& indicatorNode, RefPtr<LayoutWrapperNode>& layoutWrapper)
{
    indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();

    algorithm = indicatorPattern->CreateLayoutAlgorithm();

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
}

void SwiperTestNg::InitChild(RefPtr<LayoutWrapperNode>& indicatorNodeWrapper, const RefPtr<FrameNode>& indicatorNode)
{
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    indicatorNodeWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    float len = 20.f;
    firstGeometryNode->SetFrameSize(SizeF(len, len));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    len = 30.f;
    lastGeometryNode->SetFrameSize(SizeF(len, len));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorNodeWrapper->AppendChild(lastLayoutWrapper);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    indicatorNodeWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
}

void SwiperTestNg::CreateSwiperLayoutWrapper(
    const RefPtr<FrameNode>& frameNode_, RefPtr<LayoutWrapperNode>& swiperLayoutWrapper)
{
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());

    layoutProperty_->UpdateDisplayArrow(true);
    layoutProperty_->UpdateShowIndicator(true);
    layoutProperty_->UpdateIsSidebarMiddle(false);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto swiperNormalOffset = OffsetF(0.0f, 0.0f);
    auto swiperNormalSize = SizeF(648.0f, 240.0f);
    geometryNode->SetFrameOffset(swiperNormalOffset);
    geometryNode->SetFrameSize(swiperNormalSize);

    swiperLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
}

void SwiperTestNg::InitArrowLayoutWrapper(const RefPtr<FrameNode>& frameNode_, const std::string& arrowType,
    RefPtr<FrameNode>& arrowNode, RefPtr<LayoutWrapperNode>& arrowLayoutWrapper)
{
    int32_t buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    if (arrowType == V2::SWIPER_LEFT_ARROW_ETS_TAG) {
        buttonId = pattern_->GetLeftButtonId();
    } else if (arrowType == V2::SWIPER_RIGHT_ARROW_ETS_TAG) {
        buttonId = pattern_->GetRightButtonId();
    }

    arrowNode = FrameNode::GetOrCreateFrameNode(
        arrowType, buttonId, []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto arrowPattern = arrowNode->GetPattern<SwiperArrowPattern>();
    auto arrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(arrowPattern->GetSwiperArrowLayoutProperty());
    arrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    arrowLayoutProperty->UpdateBackgroundColor(Color::BLACK);
    arrowLayoutProperty->UpdateArrowSize(10.0_vp);
    arrowLayoutProperty->UpdateArrowColor(Color::BLACK);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    arrowLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    arrowLayoutProperty->UpdateContentConstraint();

    arrowNode->MarkModifyDone();
    frameNode_->AddChild(arrowNode);

    auto arrowGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    arrowGeometryNode->SetFrameSize(SizeF(36.0f, 36.0f));
    arrowLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(arrowNode, arrowGeometryNode, arrowLayoutProperty);
    auto arrowLayoutAlgorithm = arrowPattern->CreateLayoutAlgorithm();
    arrowLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arrowLayoutAlgorithm));
    AddArrowChild(arrowNode, arrowLayoutWrapper);
}

void SwiperTestNg::AddArrowChild(
    const RefPtr<FrameNode>& arrowNode, const RefPtr<LayoutWrapperNode>& arrowLayoutWrapper)
{
    auto arrowFirstChildNode = AceType::DynamicCast<FrameNode>(arrowNode->GetFirstChild());
    auto arrowFirstChildNodePattern = arrowFirstChildNode->GetPattern<ButtonPattern>();
    auto arrowFirstChildNodeLayoutProperty =
        AceType::DynamicCast<ButtonLayoutProperty>(arrowFirstChildNode->GetLayoutProperty());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> arrowFirstChildNodeWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(arrowFirstChildNode, geometryNode, arrowFirstChildNodeLayoutProperty);

    auto arrowFirstChildLayoutAlgorithm = arrowFirstChildNodePattern->CreateLayoutAlgorithm();
    arrowFirstChildNodeWrapper->SetLayoutAlgorithm(
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arrowFirstChildLayoutAlgorithm));
    arrowLayoutWrapper->AppendChild(arrowFirstChildNodeWrapper);
}

void SwiperTestNg::CreateChildWrapperAppendToHostWrapper(
    int32_t startIndex, int32_t endIndex, const RefPtr<LayoutWrapperNode>& hostWrapper)
{
    for (int32_t index = startIndex; index <= endIndex; index++) {
        auto childPattern = AceType::MakeRefPtr<Pattern>();
        auto childFrameNode = FrameNode::CreateFrameNode(BOX_NAME, index, childPattern);
        auto host = hostWrapper->GetHostNode();
            frameNode_->AddChild(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        childLayoutProperty->UpdateAspectRatio(1.0f);
        RefPtr<LayoutWrapperNode> childLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
        auto layoutAlgorithm = childPattern->CreateLayoutAlgorithm();
        childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
        hostWrapper->AppendChild(std::move(childLayoutWrapper));
    }
}

/**
 * @tc.name: AttrIndex001
 * @tc.desc: Test property about index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndex(1); });
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 0);

    /**
     * @tc.steps: step3. Set illegal value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndex(-1); });
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);

    /**
     * @tc.steps: step4. Set illegal value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndex(ITEM_NUMBER); });
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);
}

/**
 * @tc.name: AttrAutoPlay001
 * @tc.desc: Test property about autoPlay/interval/loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrAutoPlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_FALSE(pattern_->IsAutoPlay());
    EXPECT_EQ(pattern_->GetInterval(), DEFAULT_INTERVAL);
    EXPECT_TRUE(pattern_->IsLoop());

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetAutoPlay(true); });
    EXPECT_TRUE(pattern_->IsAutoPlay());

    /**
     * @tc.steps: step3. Set interval
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetAutoPlay(true);
        model.SetAutoPlayInterval(4000);
    });
    EXPECT_EQ(pattern_->GetInterval(), 4000);

    /**
     * @tc.steps: step4. Set loop
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetAutoPlay(true);
        model.SetLoop(false);
    });
    EXPECT_FALSE(pattern_->IsLoop());
}

/**
 * @tc.name: AttrIndicator001
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_TRUE(pattern_->IsShowIndicator());
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DOT);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndicatorType(SwiperIndicatorType::DIGIT); });
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
}

/**
 * @tc.name: AttrDuration001
 * @tc.desc: Test property about duration
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetDuration(), DEFAULT_DURATION);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDuration(500); });
    EXPECT_EQ(pattern_->GetDuration(), 500);
}

/**
 * @tc.name: AttrVertical001
 * @tc.desc: Test property about vertical
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrVertical001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetDirection(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDirection(Axis::VERTICAL); });
    EXPECT_EQ(pattern_->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: AttrItemSpace001
 * @tc.desc: Test property about itemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrItemSpace001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetItemSpace(), 0);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetItemSpace(Dimension(10)); });
    EXPECT_EQ(pattern_->GetItemSpace(), 10);
}

/**
 * @tc.name: AttrDisplayMode001
 * @tc.desc: Test property about displayMode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrDisplayMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_TRUE(SwiperUtils::IsStretch(layoutProperty_));

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR); });
    EXPECT_FALSE(SwiperUtils::IsStretch(layoutProperty_));
}

/**
 * @tc.name: AttrCachedCount001
 * @tc.desc: Test property about cachedCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrCachedCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(1), 1);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetCachedCount(2); });
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(1), 2);

    /**
     * @tc.steps: step3. Set illegal value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetCachedCount(-1); });
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(1), -1);
}

/**
 * @tc.name: AttrDisableSwipe001
 * @tc.desc: Test property about disableSwipe
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrDisableSwipe001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_FALSE(pattern_->IsDisableSwipe());

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisableSwipe(true); });
    EXPECT_TRUE(pattern_->IsDisableSwipe());
}

/**
 * @tc.name: AttrCurve001
 * @tc.desc: Test property about Curve
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrCurve001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetCurve(), nullptr);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetCurve(Curves::SMOOTH); });
    EXPECT_EQ(pattern_->GetCurve(), Curves::SMOOTH);
}

/**
 * @tc.name: AttrDisplayCount001
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrDisplayCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayCount(2); });
    EXPECT_EQ(pattern_->GetDisplayCount(), 2);

    /**
     * @tc.steps: step3. Set illegal value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayCount(0); });
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
}

/**
 * @tc.name: AttrEdgeEffect001
 * @tc.desc: Test property about EdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) { model.SetLoop(false); });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::SPRING);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::FADE);
    });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::FADE);

    /**
     * @tc.steps: step3. Set value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::NONE);
    });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::NONE);
}

/**
 * @tc.name: AttrMargin001
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AttrMargin001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetNextMargin(), 0);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0);

    /**
     * @tc.steps: step2. Set value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetNextMargin(Dimension(10));
        model.SetPreviousMargin(Dimension(5));
    });
    EXPECT_EQ(pattern_->GetNextMargin(), 10);
    EXPECT_EQ(pattern_->GetPrevMargin(), 5);

    /**
     * @tc.steps: step2. Set illegal value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetNextMargin(Dimension(SWIPER_WIDTH + 1));
        model.SetPreviousMargin(Dimension(5));
    });
    EXPECT_EQ(pattern_->GetNextMargin(), 0);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0);

    /**
     * @tc.steps: step2. Set illegal value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetNextMargin(Dimension(10));
        model.SetPreviousMargin(Dimension(SWIPER_WIDTH + 1));
    });
    EXPECT_EQ(pattern_->GetNextMargin(), 0);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0);
}

/**
 * @tc.name: SwiperEvent001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
    const char* name = "HandleTouchDown";
    pattern_->controller_ = CREATE_ANIMATOR(name);
    pattern_->controller_->status_ = Animator::Status::RUNNING;
    pattern_->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);

    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    pattern_->HandleTouchEvent(touchEventInfo);
    pattern_->controller_ = nullptr;
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::CANCEL);
    pattern_->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::MOVE);
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    pattern_->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperEvent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub_)));

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->restoreNodeInfo_.emplace(std::make_pair(1, "testFlushUITasks"));
    pattern_->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern_->direction_, Axis::HORIZONTAL);
    pattern_->touchEvent_ = nullptr;
    pattern_->InitTouchEvent(gestureEventHub);
    TouchEventFunc callback = [](TouchEventInfo& info) {};
    pattern_->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    pattern_->InitTouchEvent(gestureEventHub);
    EXPECT_TRUE(pattern_->touchEvent_);
    EXPECT_TRUE(pattern_->panEvent_);

    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.inputEventType_ = InputEventType::AXIS;
    pattern_->panEvent_->actionStart_(gestureEvent);
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    pattern_->panEvent_->actionEnd_(gestureEvent);
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    CommonFunc func = []() {};
    pattern_->swiperController_->SetTabBarFinishCallback(func);
    pattern_->panEvent_->actionStart_(gestureEvent);
    pattern_->panEvent_->actionEnd_(gestureEvent);
    pattern_->swiperController_->SetRemoveSwiperEventCallback(func);
    pattern_->panEvent_->actionStart_(gestureEvent);
    pattern_->panEvent_->actionEnd_(gestureEvent);
    pattern_->panEvent_->actionCancel_();
    EXPECT_TRUE(pattern_->swiperController_->tabBarFinishCallback_);
    EXPECT_TRUE(pattern_->swiperController_->removeSwiperEventCallback_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation001
 * @tc.desc: Swiper spring animation is playing
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation002
 * @tc.desc: StopAndResetSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    pattern_->StopAndResetSpringAnimation();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation003
 * @tc.desc: StopSpringAnimationAndFlushImmediately
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    pattern_->StopSpringAnimationAndFlushImmediately();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation004
 * @tc.desc: StopSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    pattern_->StopSpringAnimation();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation005
 * @tc.desc: Swiper spring animation is playing, handle touch down to break playing animation,
 *           and handle touch up to continue playing animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);

    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    pattern_->HandleTouchDown(touchLocationInfo);
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperUtilsTest001
 * @tc.desc: Test Swiper measure and layout function, set prevMargin and nextMargin property is 50_px.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, swiperGeometryNode, layoutProperty_);
    int32_t displaycount = 3;
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(displaycount);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    layoutProperty_->UpdateShowIndicator(false);
    layoutProperty_->UpdateLoop(false);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
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
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateDisplayCount(-1);
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest003
 * @tc.desc: Verify the CreateChildConstraint function when DisplayMode is AUTO_LINEAR.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest003, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR); });
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest004
 * @tc.desc: Verify the CreateChildConstraint function when NextMargin is normal and abnormal.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);

    layoutProperty_->UpdateNextMargin(Dimension(600));
    result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest005
 * @tc.desc: Verify the CreateChildConstraint function does not set a value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest005, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest006
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);

    layoutProperty_->UpdateNextMargin(Dimension(600));
    result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest007
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL and does not set value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest007, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest008
 * @tc.desc: Verify the CreateChildConstraint function when Direction is FREE.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest008, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::FREE);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperInit001
 * @tc.desc: InitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInit001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(frameNode_->children_.size(), 5);
}

/**
 * @tc.name: SwiperInit002
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInit002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_, FocusType::DISABLE, false);
    pattern_->InitOnKeyEvent(focusHub);
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
    CreateWithItem([](SwiperModelNG model) {});
    KeyEvent event = KeyEvent();
    event.action = KeyAction::CLICK;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
}

/**
 * @tc.name: SwiperFunc002
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    bool isVisible = false;
    pattern_->OnVisibleChange(isVisible);
    pattern_->isInit_ = false;
    pattern_->OnWindowHide();
    pattern_->OnVisibleChange(isVisible);
    EXPECT_FALSE(pattern_->isVisible_);
    isVisible = true;
    pattern_->OnWindowShow();
    pattern_->OnVisibleChange(isVisible);
    EXPECT_TRUE(pattern_->isVisible_);
    pattern_->isVisibleArea_ = true;
    pattern_->OnWindowShow();
}

/**
 * @tc.name: SwiperFunc003
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
}

/**
 * @tc.name: SwiperFunc004
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub_)));
    pattern_->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern_->direction_, Axis::HORIZONTAL);

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(
        "SwiperIndicator", 0, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    EXPECT_TRUE(frameNode_->geometryNode_);
    frameNode_->geometryNode_->frame_.SetOffset(OffsetF(0, 0));
    EXPECT_TRUE(pattern_->panEvent_);
    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.SetMainDelta(20.0);
    gestureEvent.SetLocalLocation(Offset(0, 0));
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    EXPECT_EQ(pattern_->currentOffset_, 0.0);

    layoutProperty_->propLoop_ = false;
    frameNode_->geometryNode_->frame_.SetSize(SizeF(10.f, 10.f));
    EXPECT_TRUE(pattern_->IsOutOfBoundary(20.0));
    // Swiper has reached boundary.
    frameNode_->geometryNode_->frame_.SetSize(SizeF(0, 0));
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    pattern_->currentOffset_ = 20.0;
    paintProperty_->propEdgeEffect_ = EdgeEffect::FADE;
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    pattern_->currentOffset_ = 20.0;
    paintProperty_->propEdgeEffect_ = EdgeEffect::NONE;
    pattern_->panEvent_->actionUpdate_(gestureEvent);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Swiper Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step4. When swiper is not scrollable, call the callback function in accessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    layoutProperty_->UpdateLoop(false);
    pattern_->SetAccessibilityAction();
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When swiper is scrollable, call the callback function in accessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    layoutProperty_->UpdateLoop(true);
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());
}

/**
 * @tc.name: SwiperModelNg001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg001, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetIndex(1);
    EXPECT_EQ(layoutProperty->GetIndex(), 1);

    /**
     * @tc.steps: step3.2. Test SetDisplayMode function.
     * @tc.expected: layoutProperty->GetDisplayMode() is equal to swiperDisplayMode.
     */
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    EXPECT_EQ(layoutProperty->GetDisplayMode(), SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step3.3. Test SetShowIndicator function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetShowIndicator(true);
    EXPECT_TRUE(layoutProperty->GetShowIndicator());

    /**
     * @tc.steps: step3.4. Test SetItemSpace function.
     * @tc.expected: layoutProperty->GetItemSpace() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    model.SetItemSpace(dimension);
    EXPECT_EQ(layoutProperty->GetItemSpace(), dimension);

    /**
     * @tc.steps: step3.5. Test SetCachedCount function.
     * @tc.expected:DisplayCount = -1 layoutProperty->SetCachedCount() is equal to 1.
     * @tc.expected:DisplayCount = 1 layoutProperty->SetCachedCount() is equal to 1.
     */
    model.SetCachedCount(-1);
    model.SetCachedCount(1);
    EXPECT_EQ(layoutProperty->GetCachedCount(), 1);

    /**
     * @tc.steps: step3.6. Test SetIsIndicatorCustomSize function.
     * @tc.expected: pattern->IsIndicatorCustomSize() is equal to true.
     */
    model.SetIsIndicatorCustomSize(true);
    EXPECT_TRUE(pattern->IsIndicatorCustomSize());

    /**
     * @tc.steps: step3.7. Test SetAutoPlay function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlay() is equal to true.
     */
    model.SetAutoPlay(true);
    EXPECT_TRUE(paintProperty->GetAutoPlay());

    /**
     * @tc.steps: step3.8. Test SetAutoPlayInterval function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlayInterval() is equal to 1.
     */
    model.SetAutoPlayInterval(1);
    EXPECT_EQ(paintProperty->GetAutoPlayInterval(), 1);

    /**
     * @tc.steps: step3.9. Test SetDuration function.
     * @tc.expected: SwiperPaintProperty->GetDuration() is equal to 1.
     */
    model.SetDuration(1);
    EXPECT_EQ(paintProperty->GetDuration(), 1);
}

/**
 * @tc.name: SwiperModelNg002
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg002, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();

    /**
     * @tc.steps: step3.1. Test SetLoop function.
     * @tc.expected: SwiperPaintProperty->GetLoop() is true.
     */
    model.SetLoop(true);
    EXPECT_TRUE(layoutProperty->GetLoop());

    /**
     * @tc.steps: step3.2. Test SetEnabled function.
     * @tc.expected: SwiperPaintProperty->GetEnabled() is true.
     */
    model.SetEnabled(true);
    EXPECT_TRUE(paintProperty->GetEnabled());

    /**
     * @tc.steps: step3.3. Test SetDisableSwipe function.
     * @tc.expected: SwiperPaintProperty->GetDisableSwipe() is true.
     */
    model.SetDisableSwipe(true);
    EXPECT_TRUE(paintProperty->GetDisableSwipe());

    /**
     * @tc.steps: step3.4. Test SetEdgeEffect function.
     * @tc.expected: SwiperPaintProperty->GetEdgeEffect() is true.
     */
    model.SetEdgeEffect(EdgeEffect::FADE);
    EXPECT_EQ(paintProperty->GetEdgeEffect(), EdgeEffect::FADE);

    /**
     * @tc.steps: step3.5. Test SetOnChange function.
     * @tc.expected:pattern->changeEvent_ not null.
     */
    auto onChange = [](const BaseEventInfo* info) {};
    model.SetOnChange(std::move(onChange));
    EXPECT_NE(pattern->changeEvent_, nullptr);

    /**
     * @tc.steps: step3.6. Test SetOnAnimationStart function.
     * @tc.expected:pattern->animationStartEvent_ not null.
     */
    auto onAnimationStart = [](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {};
    model.SetOnAnimationStart(std::move(onAnimationStart));
    EXPECT_NE(pattern->animationStartEvent_, nullptr);

    /**
     * @tc.steps: step3.7. Test SetOnAnimationEnd function.
     * @tc.expected:pattern->animationEndEvent_ not null.
     */
    auto onAnimationEnd = [](int32_t index, const AnimationCallbackInfo& info) {};
    model.SetOnAnimationEnd(std::move(onAnimationEnd));
    EXPECT_NE(pattern->animationEndEvent_, nullptr);
}

/**
 * @tc.name: SwiperModelNg003
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg003, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step3.1. Test SetIndicatorStyle function.
     * @tc.expected: SwiperPaintProperty->swiperParameters_->colorVal is swiperParameters.colorVal.
     */
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    model.SetIndicatorStyle(swiperParameters);
    EXPECT_EQ(pattern->swiperParameters_->colorVal, swiperParameters.colorVal);

    /**
     * @tc.steps: step3.2. Test SetPreviousMargin function.
     * @tc.expected: paintProperty->GetPrevMargin() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    model.SetPreviousMargin(dimension);
    EXPECT_EQ(layoutProperty->GetPrevMargin(), dimension);

    /**
     * @tc.steps: step3.3. Test SetNextMargin function.
     * @tc.expected: paintProperty->GetNextMargin() is equal to dimension.
     */
    model.SetNextMargin(dimension);
    EXPECT_EQ(layoutProperty->GetNextMargin(), dimension);

    /**
     * @tc.steps: step3.4. Test SetOnChangeEvent function.
     * @tc.expected: pattern->onIndexChangeEvent_ is not null.
     */
    auto onChangeEvent = [](const BaseEventInfo* info) {};
    model.SetOnChangeEvent(std::move(onChangeEvent));
    EXPECT_NE(pattern->onIndexChangeEvent_, nullptr);

    /**
     * @tc.steps: step3.5. Test SetIndicatorIsBoolean function.
     * @tc.expected: pattern->indicatorIsBoolean_ is true.
     */
    model.SetIndicatorIsBoolean(true);
    EXPECT_TRUE(pattern->indicatorIsBoolean_);

    /**
     * @tc.steps: step3.6. Test SetArrowStyle function.
     * @tc.expected: before set swiperArrowParameters, all result is null.
     */
    SwiperArrowParameters swiperArrowParameters;
    model.SetArrowStyle(swiperArrowParameters);

    /**
     * @tc.steps: step3.7. Test SetArrowStyle function.
     * @tc.expected: after set swiperArrowParameters, layoutProperty->IsShowBoard is true.
     */
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.backgroundSize = dimension;
    swiperArrowParameters.backgroundColor = Color(Color::BLUE);
    swiperArrowParameters.arrowSize = dimension;
    swiperArrowParameters.arrowColor = Color(Color::RED);
    swiperArrowParameters.isSidebarMiddle = true;
    model.SetArrowStyle(swiperArrowParameters);
    EXPECT_TRUE(layoutProperty->GetIsShowBackground());
    EXPECT_EQ(layoutProperty->GetBackgroundSize(), dimension);
    EXPECT_EQ(layoutProperty->GetBackgroundColor(), Color(Color::BLUE));
    EXPECT_EQ(layoutProperty->GetArrowSize(), dimension);
    EXPECT_EQ(layoutProperty->GetArrowColor(), Color(Color::RED));
    EXPECT_TRUE(layoutProperty->GetIsSidebarMiddle());

    /**
     * @tc.steps: step3.8. Test SetDisplayArrow function.
     * @tc.expected: layoutProperty->GetDisplayArrow() is true.
     */
    model.SetDisplayArrow(true);
    EXPECT_TRUE(layoutProperty->GetDisplayArrow());

    /**
     * @tc.steps: step3.9. Test SetHoverShow function.
     * @tc.expected: layoutProperty->GetHoverShow() is true.
     */
    model.SetHoverShow(true);
    EXPECT_TRUE(layoutProperty->GetHoverShow());
}

/**
 * @tc.name: SwiperFlushFocus001
 * @tc.desc: Swiper FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFlushFocus001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. Create curShowFrameNode, addChild to frameNode.
     */
    auto curShowFrame = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    curShowFrame->AddChild(child);
    frameNode_->AddChild(child2);

    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);

    /**
     * @tc.steps: step3. test FlushFocus with IsShowIndicator() is false.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->lastWeakFocusNode_ is not null.
     */
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->isLastIndicatorFocused_ = true;
    EXPECT_FALSE(pattern_->IsShowIndicator());
    pattern_->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->FlushFocus(curShowFrame);
    EXPECT_EQ(pattern_->lastWeakShowNode_, AceType::WeakClaim(AceType::RawPtr(curShowFrame)));

    /**
     * @tc.steps: step4. test FlushFocus with IsShowIndicator() is true and hasLeftButton and hasRightButton.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->currentFocus_ is false.
     */
    layoutProperty_->UpdateShowIndicator(true);
    pattern_->GetLeftButtonId();
    pattern_->GetRightButtonId();
    EXPECT_TRUE(layoutProperty_->GetShowIndicatorValue(true));
    EXPECT_TRUE(pattern_->IsShowIndicator());
    focusHub->currentFocus_ = true;
    pattern_->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->FlushFocus(curShowFrame);
}

/**
 * @tc.name: SwiperGetNextFocusNode001
 * @tc.desc: Swiper GetNextFocusNode.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperGetNextFocusNode001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. Create localShowNode and focusNode.
     */
    auto localShowNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHubLocal = AceType::MakeRefPtr<EventHub>();
    eventHubLocal->AttachHost(localShowNode);
    auto focusHubLocal = AceType::MakeRefPtr<FocusHub>(eventHubLocal);

    auto focusNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub_->AttachHost(focusNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);
    pattern_->lastWeakShowNode_ = AceType::WeakClaim(AceType::RawPtr(localShowNode));

    /**
     * @tc.steps: step3.1. Test different Axis::HORIZONTAL and FocusStep::UP.
     * @tc.expected: pattern_->GetNextFocusNode return nullptr.
     */
    pattern_->direction_ = Axis::HORIZONTAL;
    pattern_->GetNextFocusNode(FocusStep::UP, focusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.2. Test different Axis::VERTICAL and FocusStep::LEFT.
     * @tc.expected: pattern_->GetNextFocusNode return nullptr.
     */
    pattern_->direction_ = Axis::VERTICAL;
    pattern_->GetNextFocusNode(FocusStep::LEFT, focusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.3. Test different Axis::HORIZONTAL and FocusStep::DOWN.
     * @tc.expected: pattern_->GetNextFocusNode return nullptr.
     */
    pattern_->direction_ = Axis::HORIZONTAL;
    pattern_->GetNextFocusNode(FocusStep::LEFT, focusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.4. Test different Axis::VERTICAL and FocusStep::RIGHT.
     * @tc.expected: pattern_->GetNextFocusNode return nullptr.
     */
    pattern_->direction_ = Axis::VERTICAL;
    pattern_->GetNextFocusNode(FocusStep::RIGHT, focusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.5. Test different Axis::FREE.
     * @tc.expected: pattern_->GetNextFocusNode return nullptr.
     */
    pattern_->direction_ = Axis::FREE;
    pattern_->GetNextFocusNode(FocusStep::RIGHT, focusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.6. Test different Axis::HORIZONTAL and FocusStep::UP and has left right button.
     * @tc.expected: pattern_->GetNextFocusNode return nullptr.
     */
    pattern_->GetLeftButtonId();
    pattern_->GetRightButtonId();
    pattern_->direction_ = Axis::HORIZONTAL;
    pattern_->GetNextFocusNode(FocusStep::UP, focusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.steps: step3.7. Test different Axis::HORIZONTAL and FocusStep::UP and has left right button.
     * @tc.expected: pattern_->GetNextFocusNode return nullptr.
     */
    pattern_->direction_ = Axis::HORIZONTAL;
    pattern_->GetNextFocusNode(FocusStep::DOWN, focusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPreviousFocus001
 * @tc.desc: Swiper PreviousFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPreviousFocus001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLeftArrowNode =
        AceType::MakeRefPtr<FrameNode>(V2::SWIPER_LEFT_ARROW_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto swiperRightArrowNode =
        AceType::MakeRefPtr<FrameNode>(V2::SWIPER_INDICATOR_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    frameNode_->AddChild(swiperLeftArrowNode);
    frameNode_->AddChild(swiperRightArrowNode);
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);

    auto curEventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SWIPER_LEFT_ARROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    curEventHub->AttachHost(frameNode);
    auto curFocusHub = AceType::MakeRefPtr<FocusHub>(curEventHub);

    auto focusChildren = focusHub->GetChildren();
    pattern_->leftButtonId_ = std::nullopt;
    pattern_->PreviousFocus(curFocusHub);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);
    EXPECT_TRUE(curFocusHub->parentFocusable_);
    layoutProperty_->UpdateLoop(false);
    pattern_->PreviousFocus(curFocusHub);
    EXPECT_FALSE(curFocusHub->parentFocusable_);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);
    curFocusHub->GetFrameNode()->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
    pattern_->PreviousFocus(curFocusHub);
    EXPECT_TRUE(pattern_->isLastIndicatorFocused_);
    layoutProperty_->UpdateLoop(true);
    pattern_->GetLeftButtonId();
    EXPECT_FALSE(layoutProperty_->GetHoverShowValue(false));
    pattern_->PreviousFocus(curFocusHub);
    EXPECT_TRUE(pattern_->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), 0);
    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    pattern_->currentIndex_ = 10;
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    pattern_->startIndex_ = 10;
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 10);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 0);
    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    pattern_->endIndex_ = 10;
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 10);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_TRUE(accessibilityProperty_->HasRange());
    AccessibilityValue result = accessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 3);
    EXPECT_EQ(result.current, 0);

    for (int index = 0; index <= 10; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
            frameNode_->AddChild(indicatorNode);
    }
    pattern_->currentIndex_ = 10;

    result = accessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 14);
    EXPECT_EQ(result.current, 10);
}

/**
 * @tc.name: SwiperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateLoop(false);
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());

    for (int index = 0; index <= 10; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
            frameNode_->AddChild(indicatorNode);
    }
    pattern_->OnModifyDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 4);
    for (int index = 0; index <= 10; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
            frameNode_->AddChild(indicatorNode);
    }
    pattern_->OnModifyDone();
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 15);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateLoop(false);
    for (int index = 0; index <= 10; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
            frameNode_->AddChild(indicatorNode);
    }
    pattern_->currentIndex_ = 1;
    pattern_->OnModifyDone();
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    layoutProperty_->UpdateLoop(true);
    accessibilityProperty_->ResetSupportAction();
    supportAceActions = accessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: SwiperAccessibilityPropertySetSpecificSupportAction001
 * @tc.desc: Test GetSupportAction of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertySetSpecificSupportAction001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateLoop(false);
    accessibilityProperty_->SetSpecificSupportAction();

    /**
     * @tc.steps: step2. call SetSpecificSupportAction.
     * @tc.expected: GetCurrentIndex() < 0.
     */
    pattern_->GetLeftButtonId();
    pattern_->GetRightButtonId();
    accessibilityProperty_->SetSpecificSupportAction();
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step2. call SetSpecificSupportAction.
     * @tc.expected: GetCurrentIndex() > GetCollectionItemCounts().
     */
    for (int index = 0; index <= 10; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
            frameNode_->AddChild(indicatorNode);
    }
    accessibilityProperty_->SetSpecificSupportAction();
    pattern_->currentIndex_ = pattern_->TotalCount();
    EXPECT_LE(accessibilityProperty_->GetCurrentIndex(), accessibilityProperty_->GetCollectionItemCounts());
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateLeft(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateRight(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty right is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateRight(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateTop(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty top is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateBottom(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty bottom is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<DotIndicatorLayoutAlgorithm> algorithm =
        AceType::DynamicCast<DotIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnAttachToFrameNode();
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
}

/**
 * @tc.name: SwiperIndicatorOnModifyDone001
 * @tc.desc: Test SwiperIndicator OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);


    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    DirtySwapConfig config;
    config.frameSizeChange = false;
    EXPECT_FALSE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
    config.frameSizeChange = true;
    EXPECT_TRUE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
}

/**
 * @tc.name: SwiperIndicatorHandleClick001
 * @tc.desc: Test SwiperIndicator HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. SelectedFontSize is 14.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step4. SelectedFontSize is 60.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step4. SelectedFontSize is -1.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. FontSize is 14.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step3. FontSize is 30.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    Dimension fontSize = 30.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. FontSize is -10.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    Dimension fontSize = -10.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. FontColor is 0xff000000.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);

    /**
     * @tc.steps: step3. FontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. FontColor is 0xff00ff00.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. SelectedFontColor001 is 0xff000000.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);

    /**
     * @tc.steps: step4. SelectedFontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. FontWeight is NORMAL.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(backTextLayoutProperty->GetFontWeight(), FontWeight::NORMAL);
    /**
     * @tc.steps: step3. FontWeight is BOLDER.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. SelectedFontWeight is NORMAL.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(frontTextLayoutProperty->GetFontWeight(), FontWeight::NORMAL);
    /**
     * @tc.steps: step3. SelectedFontWeight is MEDIUM.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemHeight(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemWidth(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemHeight(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = pattern_->CreateLayoutAlgorithm();
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, layoutProperty_);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 327.0, 1121.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
    EXPECT_EQ(indicatorNodeWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(327.0, 1106.0));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout002
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = pattern_->CreateLayoutAlgorithm();
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, layoutProperty_);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    auto swiperPatternAlgorithm = pattern_->CreateLayoutAlgorithm();
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    Dimension dimension = 20.0_vp;
    layoutProperty_->UpdateLeft(dimension);
    layoutProperty_->UpdateTop(dimension);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, layoutProperty_);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 20.0, 20.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout004
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    auto swiperPatternAlgorithm = pattern_->CreateLayoutAlgorithm();
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    Dimension dimension = 20.0_vp;
    layoutProperty_->UpdateRight(dimension);
    layoutProperty_->UpdateBottom(dimension);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> indicatorNodeWrapper;
    InitChild(indicatorNodeWrapper, indicatorNode);
    LayoutWrapperNode swiperLayoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, layoutProperty_);
    swiperLayoutWrapper.AppendChild(indicatorNodeWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 634.0, 1086.0 .
     */
    swiperPatternAlgorithm->Layout(&swiperLayoutWrapper);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout005
 * @tc.desc: Test SwiperLayoutAlgorithm Layout with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper;
    CreateSwiperLayoutWrapper(frameNode_, swiperLayoutWrapper);
    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    auto indicatorGeometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_LEFT_ARROW_ETS_TAG, leftArrowNode, leftArrowNodeWrapper);
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_RIGHT_ARROW_ETS_TAG, rightArrowNode, rightArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(leftArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(rightArrowNodeWrapper);

    /**
     * @tc.cases: case1. Axis is HORIZONTAL, arrow is in the switch.
     */
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));
    auto leftArrowGeometryNode = leftArrowNodeWrapper->GetGeometryNode();
    auto leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    auto rightArrowGeometryNode = rightArrowNodeWrapper->GetGeometryNode();
    auto rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(leftArrowOffset, OffsetF(286.0f, 196.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(322.0f, 196.0f));

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
    layoutProperty_->UpdateShowIndicator(false);
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));
    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(leftArrowOffset, OffsetF(0.0f, 102.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(612.0f, 102.0f));

    /**
     * @tc.cases: case4. Axis is VERTICAL, arrow is in the switch.
     */
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateShowIndicator(true);
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 50.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 100.0f));
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));
    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(leftArrowOffset, OffsetF(12.0f, 64.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(12.0f, 100.0f));

    /**
     * @tc.cases: case5. Axis is VERTICAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 15.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 220.0f));
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));
    leftArrowOffset = leftArrowGeometryNode->GetMarginFrameOffset();
    rightArrowOffset = rightArrowGeometryNode->GetMarginFrameOffset();
    EXPECT_EQ(leftArrowOffset, OffsetF(12.0f, 89.0f));
    EXPECT_EQ(rightArrowOffset, OffsetF(12.0f, 125.0f));

    /**
     * @tc.cases: case6. Axis is VERTICAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper;
    CreateSwiperLayoutWrapper(frameNode_, swiperLayoutWrapper);

    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    /**
     * @tc.steps: step3. Create arrow node and layoutWrapper.
     */
    RefPtr<FrameNode> leftArrowNode;
    RefPtr<FrameNode> rightArrowNode;
    RefPtr<LayoutWrapperNode> leftArrowNodeWrapper;
    RefPtr<LayoutWrapperNode> rightArrowNodeWrapper;
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_LEFT_ARROW_ETS_TAG, leftArrowNode, leftArrowNodeWrapper);
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_RIGHT_ARROW_ETS_TAG, rightArrowNode, rightArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(leftArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(rightArrowNodeWrapper);

    /**
     * @tc.steps: step4. call Measure.
     * @tc.expected: Return button measure, SizeF(3.0f, 3.0f).
     */
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));
    auto leftArrowChild = swiperLayoutWrapper->GetOrCreateChildByIndex(0);
    auto leftArrowChildGeometryNode = leftArrowChild->GetGeometryNode();
    auto leftArrowChildSize = leftArrowChildGeometryNode->GetFrameSize();
    EXPECT_EQ(leftArrowChildSize, SizeF(3.0f, 3.0f));

    auto rightArrowChild = swiperLayoutWrapper->GetOrCreateChildByIndex(1);
    auto rightArrowChildGeometryNode = rightArrowChild->GetGeometryNode();
    auto rightArrowChildSize = rightArrowChildGeometryNode->GetFrameSize();
    EXPECT_EQ(rightArrowChildSize, SizeF(3.0f, 3.0f));
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateContentModifier001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
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
 * @tc.name: SwiperIndicatorUpdateContentModifier003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateContentModifier003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;
    paintMethod->touchBottomType_ = TouchBottomType::START;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorCalculateNormalMargin001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorCalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorCalculateNormalMargin001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: run success
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);

    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 347.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorCalculatePointCenterX001
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorCalculatePointCenterX001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->turnPageRate_ = 1.0;
    /**
     * @tc.steps: step3. call CalculatePointCenterX.
     * @tc.expected: run success
     */
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    paintMethod->turnPageRate_ = 1.0;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);
}

/**
 * @tc.name: SwiperIndicatorUpdateBackgroundX001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateBackgroundX001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->turnPageRate_ = 1.0;
    paintMethod->touchBottomType_ = TouchBottomType::START;
    /**
     * @tc.steps: step3. call UpdateBackground.
     * @tc.expected: run success
     */
    paintMethod->UpdateBackground(&paintWrapper);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintNormalIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 342.0
     *               paintMethod->normalMargin_.Y is 548.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 342.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintNormalIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = 10;

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 202.0
     *               paintMethod->normalMargin_.Y is 548.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 202.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintPressIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: paintMethod->dotIndicatorModifier_ is true.
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
    paintMethod->IsCustomSizeValue_ = true;
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = 10;

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: itemHalfSizes_->Get()[1] is 6.65 .
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(
        paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[1], 10.f * 0.5 * 1.33f));
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->PaintPressIndicator(&paintWrapper);
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintHoverIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = 10;
    paintMethod->currentIndex_ = 10;
    paintMethod->mouseClickIndex_ = 5;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(5);
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: itemHalfSizes_->Get()[0] is 13.30 .
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(
        paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[0], 20.f * 0.5 * 1.33f));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(10, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10, DimensionUnit::PX));
    indicatorPattern->mouseClickIndex_ = 5;
    pattern_->indicatorDoingAnimation_ = false;
    pattern_->currentIndex_ = 10;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: pattern_->indicatorDoingAnimation_ is true.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperIndicatorHandleClick003
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));
    pattern_->indicatorDoingAnimation_ = true;

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: pattern_->indicatorDoingAnimation_ is false.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperInitIndicator001
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator002
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto layoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_->GetLastChild is 1.
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild(), 1);
}

/**
 * @tc.name: SwiperInitIndicator003
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(textNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator004
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(textNode);
    auto layoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is TEXT_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator005
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SetDotIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDotIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetDotIndicatorStyle001, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    CreateWithItem([swiperParameters](SwiperModelNG model) { model.SetDotIndicatorStyle(swiperParameters); });
    ASSERT_EQ(pattern_->swiperParameters_->colorVal, swiperParameters.colorVal);
}

/**
 * @tc.name: SetDigitIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDigitIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetDigitIndicatorStyle001, TestSize.Level1)
{
    SwiperDigitalParameters digitalParameters;
    digitalParameters.fontColor = Color(Color::GREEN);
    CreateWithItem([digitalParameters](SwiperModelNG model) { model.SetDigitIndicatorStyle(digitalParameters); });
    ASSERT_EQ(pattern_->swiperDigitalParameters_->fontColor, digitalParameters.fontColor);
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test DigitIndicatorLayoutAlgorithm SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNode children is empty.
     */
    algorithm->Layout(&layoutWrapper);
    auto hostNode = layoutWrapper.GetHostNode();
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
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    LinearVector<float> normalItemHalfSizes;
    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT == SELECTED_ITEM_HALF_HEIGHT.
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);

    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 20.f.
     *               itemHalfSizes_->Get()[2] is 20.f.
     *               itemHalfSizes_->Get()[3] is 20.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 20.f);

    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT < SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    LinearVector<float> normalItemHalfSizesSecond;
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(25.f);
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(15.f);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizesSecond, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 25.f.
     *               itemHalfSizes_->Get()[2] is 20.f.
     *               itemHalfSizes_->Get()[3] is 15.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 25.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 15.f);
}

/**
 * @tc.name: DotIndicatorModifier002
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier002, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);

    // ITEM_HALF_WIDTH != SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT > SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> normalItemHalfSizesThird;
    normalItemHalfSizesThird.emplace_back(20.f);
    normalItemHalfSizesThird.emplace_back(10.f);
    normalItemHalfSizesThird.emplace_back(30.f);
    normalItemHalfSizesThird.emplace_back(35.f);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizesThird, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
}

/**
 * @tc.name: DotIndicatorModifier003
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier003, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
    // call the UpdateHoverPaintProperty to set property.
    dotIndicatorModifier.UpdateHoverPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
}

/**
 * @tc.name: DotIndicatorModifier004
 * @tc.desc: Test PaintMask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier004, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.PaintMask(context);
}

/**
 * @tc.name: DotIndicatorModifier005
 * @tc.desc: Test PaintMask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier005, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::END;
    dotIndicatorModifier.onDraw(context);
}

/**
 * @tc.name: SwiperDistributedTest001
 * @tc.desc: Test the distributed capability of Swiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern_.
     */
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. Set Index.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    layoutProperty_->UpdateIndex(1);
    std::string ret = pattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":1})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":1})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 1);
    restoreInfo_ = R"({"Index":0})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 0);
    restoreInfo_ = "invalid_json_string";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 0);
}

/**
 * @tc.name: ArrowOnModifyDone001
 * @tc.desc: Test ArrowOnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ArrowOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrowNode);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    /**
     * @tc.steps: step3. call OnModifyDone.
     * @tc.expected: leftArrowPattern->isFirstCreate_ is false.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrowNode);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
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
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(AtLeast(1));

    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrowNode);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(5);

    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto rightArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG,
        pattern_->GetRightButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    EXPECT_NE(rightArrowNode, nullptr);
    frameNode_->AddChild(rightArrowNode);
    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(rightArrowPattern, nullptr);
    auto rightSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(rightArrowPattern->GetSwiperArrowLayoutProperty());

    EXPECT_NE(rightSwiperArrowLayoutProperty, nullptr);
    rightSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    rightSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    rightSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    rightSwiperArrowLayoutProperty->UpdateDirection(Axis::VERTICAL);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(5);

    rightArrowPattern->OnModifyDone();
    EXPECT_FALSE(rightArrowPattern->isFirstCreate_);

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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrowNode);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(5);

    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });

    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();

    /**
     * @tc.steps: step3. Add child node.
     */
    auto childCount = 5;
    for (int index = 0; index < childCount; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
            frameNode_->AddChild(indicatorNode);
    }
    frameNode_->AddChild(leftArrowNode);

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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrowNode);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(1);

    leftArrowPattern->OnModifyDone();
    ASSERT_NE(leftArrowPattern->isFirstCreate_, true);

    /**
     * @tc.cases: case3.1 isHover is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.2 isHover is true, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = false;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.3 isHover is false, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, false);

    /**
     * @tc.cases: case3.4 isHover is false, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrowNode);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    buttonNode->renderContext_ = mockRenderContext;
    Mock::AllowLeak(mockRenderContext.rawPtr_);
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(1);

    leftArrowPattern->OnModifyDone();
    ASSERT_NE(leftArrowPattern->isFirstCreate_, true);

    /**
     * @tc.cases: case3.1 isHover is true, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isHover_ = true;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::DOWN);

    /**
     * @tc.cases: case3.2 isHover is true, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isHover_ = false;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::DOWN);

    /**
     * @tc.cases: case3.3 isHover is false, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isHover_ = true;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::UP);

    /**
     * @tc.cases: case3.4 isHover is false, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);

    /**
     * @tc.steps: step3.1 call GetNextFocusNode.
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_INDICATOR_ETS_TAG.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    pattern_->GetNextFocusNode(FocusStep::NONE, rightArrow->GetFocusHub());
    auto curFocusNode = pattern_->GetNextFocusNode(FocusStep::LEFT, rightArrow->GetFocusHub()).Upgrade();
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_INDICATOR_ETS_TAG);
    EXPECT_TRUE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.cases: case3.2
     * @tc.expected: isLastIndicatorFocused_ is false.
     */
    pattern_->GetNextFocusNode(FocusStep::LEFT, curFocusNode);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.cases: case3.3
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_INDICATOR_ETS_TAG.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    curFocusNode = pattern_->GetNextFocusNode(FocusStep::RIGHT, leftArrow->GetFocusHub()).Upgrade();
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_INDICATOR_ETS_TAG);
    EXPECT_TRUE(pattern_->isLastIndicatorFocused_);

    /**
     * @tc.cases: case3.4
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_RIGHT_ARROW_ETS_TAG.
     */
    curFocusNode = pattern_->GetNextFocusNode(FocusStep::RIGHT, curFocusNode).Upgrade();
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_RIGHT_ARROW_ETS_TAG);

    /**
     * @tc.cases: case3.5
     * @tc.expected: isLastIndicatorFocused_ is false.
     */
    pattern_->GetNextFocusNode(FocusStep::RIGHT, curFocusNode);
    EXPECT_FALSE(pattern_->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPatternPreviousFocus001
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);

    /**
     * @tc.steps: step3. call PreviousFocus.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->currentIndex_ = 0;
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateHoverShow(true);
    pattern_->PreviousFocus(indicatorNode->GetFocusHub());
    EXPECT_TRUE(pattern_->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPatternPreviousFocus002
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);

    /**
     * @tc.steps: step3.1 call PreviousFocus.
     * @tc.expected: rightArrow->GetFocusHub()->parentFocusable is true.
     */
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->currentIndex_ = 0;
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateHoverShow(true);
    pattern_->PreviousFocus(rightArrow->GetFocusHub());
    EXPECT_TRUE(rightArrow->GetFocusHub()->parentFocusable_);
    /**
     * @tc.cases: case3.2
     * @tc.expected: curFocusNode FrameName is V2::SWIPER_LEFT_ARROW_ETS_TAG.
     */
    pattern_->currentIndex_ = 1;
    auto curFocusNode = pattern_->PreviousFocus(rightArrow->GetFocusHub()).Upgrade();
    EXPECT_EQ(curFocusNode->GetFrameName(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperPatternPreviousFocus003
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus003, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });

    /**
     * @tc.steps: step3. call PreviousFocus.
     * @tc.expected: frameNode_->GetFocusHub()->parentFocusable is true.
     */
    pattern_->PreviousFocus(frameNode_->GetFocusHub());
    EXPECT_TRUE(frameNode_->GetFocusHub()->parentFocusable_);
}

/**
 * @tc.name: SwiperPatternNextFocus001
 * @tc.desc: Test SwiperPattern SwiperPatternNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);

    /**
     * @tc.steps: step3. call NextFocus.
     * @tc.expected: isLastIndicatorFocused_ is true.
     */
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateHoverShow(true);
    pattern_->NextFocus(indicatorNode->GetFocusHub());
    EXPECT_TRUE(pattern_->isLastIndicatorFocused_);
}

/**
 * @tc.name: SwiperPatternNextFocus002
 * @tc.desc: Test SwiperPattern SwiperPatternNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);

    /**
     * @tc.steps: step3.1 call PreviousFocus.
     * @tc.expected: leftArrow->GetFocusHub()->parentFocusable is true.
     */
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateHoverShow(true);
    pattern_->NextFocus(leftArrow->GetFocusHub());
    EXPECT_TRUE(leftArrow->GetFocusHub()->parentFocusable_);
}

/**
 * @tc.name: SwiperPatternNextFocus003
 * @tc.desc: Test SwiperPattern SwiperPatternNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus003, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });

    /**
     * @tc.steps: step3. call NextFocus.
     * @tc.expected: frameNode_->GetFocusHub()->parentFocusable is true.
     */
    pattern_->NextFocus(frameNode_->GetFocusHub());
    EXPECT_TRUE(frameNode_->GetFocusHub()->parentFocusable_);
}

/**
 * @tc.name: SwiperArrowPatternButtonClickEvent001
 * @tc.desc: Test SwiperArrowPattern ButtonClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperArrowPatternButtonClickEvent001, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);

    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);

    auto leftArrowPattern = leftArrow->GetPattern<SwiperArrowPattern>();
    auto rightArrowPattern = rightArrow->GetPattern<SwiperArrowPattern>();
    ASSERT_NE(rightArrowPattern, nullptr);

    /**
     * @tc.steps: step3. call ButtonClickEvent.
     * @tc.expected: isOnButtonClick is true.
     */
    auto swiperController = pattern_->GetSwiperController();
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
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->jumpIndex_ = 0;
    pattern_->targetIndex_ = 1;
    layoutProperty_->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = 1.0f;

    /**
     * @tc.steps: step3. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->CreateLayoutAlgorithm();
            layoutProperty_->UpdateLoop(false);
        }
        pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    }
}

/**
 * @tc.name: SwiperPatternOnIndexChange001
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnIndexChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    ASSERT_EQ(pattern_->TotalCount(), 6);
    pattern_->oldIndex_ = 1;
    layoutProperty_->UpdateIndex(2);

    /**
     * @tc.steps: step3. call OnIndexChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->OnIndexChange();
}

/**
 * @tc.name: SwiperPatternGetLoopIndex001
 * @tc.desc: GetLoopIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetLoopIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    /**
     * @tc.steps: step3. call GetLoopIndex.
     * @tc.expected: Related function runs ok.
     */
    int32_t originalIndex = -1;
    pattern_->GetLoopIndex(originalIndex);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
            pattern_->isInit_ = false;
            if (i == 1) {
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

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
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
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    pattern_->indicatorDoingAnimation_ = false;
    pattern_->jumpIndex_ = 1;

    for (int i = 0; i <= 1; i++) {
        pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
        pattern_->indicatorDoingAnimation_ = true;
        pattern_->targetIndex_ = 1;
        AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
            ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    }

    AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
            if (i == 1) {
                AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)
                    ->UpdateEdgeEffect(EdgeEffect::FADE);
                continue;
            }
            AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
        }
        AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->layoutProperty_)->padding_ =
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
    CreateWithItem([](SwiperModelNG model) {});
    int32_t index = -1;
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call SwipeTo.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-2, SwiperItemInfo { 1, 2 }));
            frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(400);
        }
        pattern_->isVisible_ = true;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                frameNode_->Clean(false, false);
                pattern_->rightButtonId_ = 1;
                continue;
            }
            pattern_->SwipeTo(index);
            index = 2;
        }
        index = -1;
    }

    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                break;
            }
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
            pattern_->currentIndex_ = 0;
        }
        pattern_->currentIndex_ = 1;
    }

    pattern_->usePropertyAnimation_ = true;
    pattern_->SwipeTo(index);
}

/**
 * @tc.name: SwiperPatternShowNext001
 * @tc.desc: ShowNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowNext001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    ASSERT_EQ(pattern_->TotalCount(), 4);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-1);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->currentIndex_ = 1;
    pattern_->preTargetIndex_ = -1;

    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();

    /**
     * @tc.steps: step2. call ShowNext.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                pattern_->preTargetIndex_ = 0;
                ASSERT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-3, SwiperItemInfo { 1, 2 }));
            pattern_->preTargetIndex_ = -1;
            EXPECT_EQ(pattern_->TotalCount(), 7);
            EXPECT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 6);
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                pattern_->currentIndex_ = 5;
                continue;
            }
            pattern_->currentIndex_ = 1;
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }
    layoutProperty_->UpdateLoop(true);
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(1);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        frameNode_->Clean(false, false);
    }
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    for (int i = 0; i <= 1; i++) {
        pattern_->ShowNext();
        pattern_->isVisible_ = false;
    }
}

/**
 * @tc.name: SwiperPatternShowPrevious001
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowPrevious001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = -1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-3);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    EXPECT_EQ(pattern_->TotalDisPlayCount(), 0);
    EXPECT_FALSE(pattern_->IsLoop());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                pattern_->preTargetIndex_ = 0;
                ASSERT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-3, SwiperItemInfo { 1, 2 }));
            pattern_->preTargetIndex_ = 1;
            EXPECT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 1);
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                pattern_->currentIndex_ = 1;
                continue;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_ = 1;
    layoutProperty_->UpdateLoop(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            pattern_->preTargetIndex_.reset();
        }
        pattern_->isVisible_ = false;
    }

    layoutProperty_->UpdateLoop(true);
    pattern_->rightButtonId_.reset();
    pattern_->leftButtonId_.reset();
    layoutProperty_->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(1);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        frameNode_->Clean(false, false);
    }
}

/**
 * @tc.name: SwiperPatternFinishAnimation001
 * @tc.desc: FinishAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternFinishAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call FinishAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->FinishAnimation();
            pattern_->usePropertyAnimation_ = true;
            pattern_->isUserFinish_ = true;
                }
        pattern_->swiperController_->SetFinishCallback([]() {});
    }
}

/**
 * @tc.name: SwiperPatternInitSwiperController001
 * @tc.desc: InitSwiperController
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitSwiperController001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->swiperController_->showPrevImpl_ = nullptr;

    /**
     * @tc.steps: step2. call InitSwiperController.
     * @tc.expected: Related function runs ok.
     */
    pattern_->InitSwiperController();
    pattern_->swiperController_->swipeToImpl_(0, true);
    pattern_->swiperController_->swipeToWithoutAnimationImpl_(0);
    pattern_->swiperController_->showNextImpl_();
    pattern_->swiperController_->showPrevImpl_();
    pattern_->swiperController_->finishImpl_();
}

/**
 * @tc.name: SwiperPatternAutoPlay001
 * @tc.desc: StopAutoPlay and StartAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAutoPlay001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    layoutProperty_->UpdateLoop(true);
    pattern_->isVisible_ = true;

    /**
     * @tc.steps: step2. call InitTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    pattern_->StopAutoPlay();
    pattern_->StartAutoPlay();
}

/**
 * @tc.name: SwiperPatternHandleTouchUp001
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchUp001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->controller_ = AceType::MakeRefPtr<Animator>();
    ASSERT_NE(pattern_->controller_, nullptr);
    pattern_->controller_->status_ = Animator::Status::PAUSED;

    /**
     * @tc.steps: step2. call HandleTouchUp.
     * @tc.expected: Related function runs ok.
     */
    pattern_->HandleTouchUp();
}

/**
 * @tc.name: SwiperPatternOnVisibleChange001
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnVisibleChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->isInit_ = false;
    pattern_->isWindowShow_ = false;

    /**
     * @tc.steps: step2. call OnVisibleChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->OnVisibleChange(true);
}

/**
 * @tc.name: SwiperPatternPlayFadeAnimation001
 * @tc.desc: PlayFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayFadeAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->fadeOffset_ = 0.0f;
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->PlayFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternPlayFadeAnimation002
 * @tc.desc: PlayFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayFadeAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->fadeOffset_ = 100.0f;
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->PlayFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
    pattern_->fadeOffset_ = -100.0f;
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->PlayFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternStopFadeAnimation001
 * @tc.desc: StopFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternStopFadeAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->StopFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternPlayPropertyTranslateAnimation001
 * @tc.desc: PlayPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayPropertyTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
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
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));

    /**
     * @tc.steps: step2. call PlayPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);
        layoutProperty_->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternUpdateOffsetAfterPropertyAnimation001
 * @tc.desc: UpdateOffsetAfterPropertyAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateOffsetAfterPropertyAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float offset = 0.1f;

    /**
     * @tc.steps: step2. call UpdateOffsetAfterPropertyAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->UpdateOffsetAfterPropertyAnimation(offset);
}

/**
 * @tc.name: SwiperPatternOnPropertyTranslateAnimationFinish001
 * @tc.desc: OnPropertyTranslateAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnPropertyTranslateAnimationFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto offset = OffsetF(0.1f, 0.2f);
    pattern_->usePropertyAnimation_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(pattern_->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call OnPropertyTranslateAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnPropertyTranslateAnimationFinish(offset);
        pattern_->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternStopPropertyTranslateAnimation001
 * @tc.desc: StopPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternStopPropertyTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->usePropertyAnimation_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(pattern_->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call StopPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->StopPropertyTranslateAnimation();
        pattern_->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternGetCurveIncludeMotion001
 * @tc.desc: GetCurveIncludeMotion
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCurveIncludeMotion001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(nullptr);
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
                pattern_->GetCurveIncludeMotion();
                if (i == 1) {
                    curve2->UpdateVelocity(-0.1f);
                    continue;
                }
                frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
                curve1->UpdateVelocity(-0.1f);
            }
            curve1->UpdateVelocity(0.1f);
        }
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve2);
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
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->indicatorId_.reset();
    float translate = 0.1f;

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PlayIndicatorTranslateAnimation(translate);
            if (i == 1) {
                break;
            }
            pattern_->indicatorId_ = 1;
        }
    }
}

/**
 * @tc.name: SwiperPatternPlayTranslateAnimation001
 * @tc.desc: PlayTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float startPos = 0.1f;
    float endPos = 0.2f;
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    float velocity = 0.1f;
    float mass = 0.1f;
    float stiffness = 0.2f;
    float damping = 0.3f;
    pattern_->controller_ = nullptr;
    auto curve1 = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);

    /**
     * @tc.steps: step2. call PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->PlayTranslateAnimation(startPos, endPos, nextIndex, restartAutoPlay, velocity);
        pattern_->controller_ = AceType::MakeRefPtr<Animator>();
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
    }

    double value = 1.0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->PlayTranslateAnimation(startPos, endPos, nextIndex, restartAutoPlay, velocity);
                Animation<double>::ValueCallback valueCallback = static_cast<CurveAnimation<double>*>(
                    AceType::RawPtr(pattern_->controller_->interpolators_.front()))
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
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));

    /**
     * @tc.steps: step2. call GetRemainingOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetDistanceToEdge();
            if (i == 1) {
                pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
                continue;
            }
            pattern_->itemPosition_.clear();
        }
        layoutProperty_->UpdateLoop(false);
    }
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->GetDistanceToEdge();
}

/**
 * @tc.name: SwiperPatternCalculateDisplayCount001
 * @tc.desc: CalculateDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCalculateDisplayCount001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);

    /**
     * @tc.steps: step2. call CalculateDisplayCount.
     * @tc.expected: Related function runs ok.
     */
    pattern_->CalculateDisplayCount();
}

/**
 * @tc.name: SwiperPatternOnTouchTestHit001
 * @tc.desc: OnTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTouchTestHit001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call OnTouchTestHit.
     * @tc.expected: Related function runs ok.
     */
    CommonFunc callback = [] {};
    pattern_->isTouchDown_ = false;
    pattern_->swiperController_->SetRemoveTabBarEventCallback(callback);
    pattern_->OnTouchTestHit(SourceType::TOUCH);
    EXPECT_NE(pattern_->swiperController_->GetRemoveTabBarEventCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation002
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    pattern_->PlayIndicatorTranslateAnimation(0.1f);
    EXPECT_NE(pattern_->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = false;
    config.skipLayout = false;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->isDragging_ = true;
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_NE(pattern_->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternGetDisplayCount002
 * @tc.desc: GetDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetDisplayCount002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();

    /**
     * @tc.steps: step2. Set the FrameSize of the model.
     */
    frameNode_->GetGeometryNode()->SetFrameSize(SizeF(720.f, 1136.f));
    Dimension SWIPER_MINSIZE = 50.0_vp;

    for (int i = 0; i < 4; i++) {
        /**
         * @tc.steps: step3. Update the MinSize of one swiper item.
         * @tc.expected: Related function runs ok.
         */
        layoutProperty_->UpdateMinSize(SWIPER_MINSIZE);
        EXPECT_EQ(layoutProperty_->GetMinSize().value_or(Dimension(0.0, DimensionUnit::VP)), SWIPER_MINSIZE);

        /**
         * @tc.steps: step4. Call GetDisplayCount.
         * @tc.expected: The return value is correct.
         */
        float displaycount = static_cast<int32_t>(
            floor((SizeF(720.f, 1136.f).Width() - 2 * 16.f + 16.f) / (SWIPER_MINSIZE.ConvertToPx() + 16.f)));
        displaycount = displaycount > 0 ? displaycount : 1;
        displaycount = displaycount > pattern_->TotalCount() ? pattern_->TotalCount() : displaycount;
        EXPECT_EQ(pattern_->GetDisplayCount(), displaycount);

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
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t currentIndex = 1;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
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

/**
 * @tc.name: SwiperPatternUpdateAnimationProperty001
 * @tc.desc: UpdateAnimationProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateAnimationProperty001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    };
    pattern_->isDragging_ = true;
    float velocity = 0.1f;

    /**
     * @tc.steps: step2. call UpdateAnimationProperty.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j >= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->UpdateAnimationProperty(velocity);
                pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
                if (i == 1) {
                    velocity = -1300;
                    continue;
                }
                if (i == 1 && j == 1) {
                    break;
                }
                velocity = 0.0f;
            }
            if (i == 1) {
                pattern_->isDragging_ = false;
                continue;
            }
            velocity = 0.1f;
        }
        velocity = 1300;
    }
}

/**
 * @tc.name: SwiperPatternGetFirstItemInfoInVisibleArea001
 * @tc.desc: GetFirstItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetFirstItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetFirstItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetFirstItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            layoutProperty_->UpdatePrevMargin(dimension);
            layoutProperty_->layoutConstraint_->scaleProperty =
                ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        layoutProperty_->ResetPrevMargin();
        layoutProperty_->layoutConstraint_->scaleProperty =
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
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetTranslateLength.
     * @tc.expected: Related function runs ok.
     */
    pattern_->GetTranslateLength();
}

/**
 * @tc.name: SwiperPatternGetSecondItemInfoInVisibleArea001
 * @tc.desc: GetSecondItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetSecondItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetSecondItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetSecondItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            layoutProperty_->UpdatePrevMargin(dimension);
            layoutProperty_->layoutConstraint_->scaleProperty =
                ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        layoutProperty_->ResetPrevMargin();
        layoutProperty_->layoutConstraint_->scaleProperty =
            ScaleProperty { 0.0f, 0.0f, 0.0f };
    }
    pattern_->itemPosition_.erase(2);
    pattern_->GetSecondItemInfoInVisibleArea();
}

/**
 * @tc.name: SwiperPatternPostTranslateTask001
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPostTranslateTask001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    uint32_t delayTime = 10;
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    };
    pattern_->itemPosition_.clear();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    /**
     * @tc.steps: step2. call PostTranslateTask.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->PostTranslateTask(delayTime);
                pattern_->translateTask_();
                if (j == 1) {
                    frameNode_->AddChild(leftArrow);
                    continue;
                }
                frameNode_->Clean(false, false);
                layoutProperty_->ResetMinSize();
                layoutProperty_->UpdateDisplayCount(1);
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        pattern_->translateTask_ = CancelableCallback<void()>([]() {});
        pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PostTranslateTask(delayTime);
            pattern_->translateTask_();
            if (i == 1) {
                layoutProperty_->UpdateLoop(true);
                continue;
            }
            layoutProperty_->UpdateLoop(false);
        }
        pattern_->itemPosition_.erase(1);
        pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    }
}

/**
 * @tc.name: SwiperPatternRegisterVisibleAreaChange001
 * @tc.desc: RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternRegisterVisibleAreaChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call RegisterVisibleAreaChange.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->RegisterVisibleAreaChange();
            if (i == 1) {
                pattern_->hasVisibleChangeRegistered_ = false;
            }
            pattern_->hasVisibleChangeRegistered_ = true;
        }
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    }

    pattern_->isWindowShow_ = false;
    for (int i = 0; i <= 1; i++) {
        pattern_->RegisterVisibleAreaChange();
        pattern_->isWindowShow_ = true;
        pattern_->isVisibleArea_ = true;
        pattern_->isVisible_ = true;
    }
}

/**
 * @tc.name: SwiperPatternTriggerEventOnFinish001
 * @tc.desc: TriggerEventOnFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerEventOnFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    int32_t nextIndex = 1;
    pattern_->preTargetIndex_ = 1;
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call TriggerEventOnFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->TriggerEventOnFinish(nextIndex);
            if (i == 1) {
                break;
            }
            nextIndex = 2;
            pattern_->isFinishAnimation_ = true;
        }
        pattern_->isFinishAnimation_ = false;
    }
}

/**
 * @tc.name: SwiperPatternArrowHover001
 * @tc.desc: ArrowHover
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternArrowHover001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    bool hoverFlag = true;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();

    /**
     * @tc.steps: step2. call ArrowHover.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ArrowHover(hoverFlag);
            if (i == 1) {
                pattern_->leftButtonId_.reset();
            }
            pattern_->leftButtonId_ = 1;
        }
        pattern_->rightButtonId_ = 1;
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToLeft001
 * @tc.desc: TriggerAnimationEndOnSwipeToLeft
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnSwipeToLeft001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToLeft.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->TriggerAnimationEndOnSwipeToLeft();
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToRight001
 * @tc.desc: TriggerAnimationEndOnSwipeToRight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnSwipeToRight001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToRight.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->TriggerAnimationEndOnSwipeToRight();
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternOnTranslateFinish001
 * @tc.desc: OnTranslateFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTranslateFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    bool forceStop = true;
    frameNode_->Clean(false, false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto indicatorNode1 = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNode2 = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnTranslateFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnTranslateFinish(nextIndex, restartAutoPlay, forceStop);
            if (i == 1) {
                pattern_->isFinishAnimation_ = false;
                continue;
            }
            pattern_->isFinishAnimation_ = true;
            frameNode_->AddChild(indicatorNode1);
            pattern_->isVisible_ = false;
        }
        frameNode_->Clean(false, false);
        frameNode_->AddChild(leftArrow);
        frameNode_->AddChild(indicatorNode2);
        forceStop = false;
        pattern_->isVisible_ = true;
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
        layoutProperty_->UpdateLoop(true);
    }
}

/**
 * @tc.name: SwiperPatternCheckAndSetArrowHoverState001
 * @tc.desc: CheckAndSetArrowHoverState
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCheckAndSetArrowHoverState001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->indicatorId_ = 1;
    layoutProperty_->UpdateShowIndicator(false);
    auto mousePoint = PointF(0.0f, 0.0f);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNode1 = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });

    /**
     * @tc.steps: step2. call CheckAndSetArrowHoverState.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->CheckAndSetArrowHoverState(mousePoint);
                if (j == 1) {
                    pattern_->leftButtonId_ = 1;
                    continue;
                }
                pattern_->leftButtonId_.reset();
            }
            pattern_->rightButtonId_.reset();
        }
        pattern_->indicatorId_.reset();
    }

    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->indicatorId_ = 1;
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(indicatorNode);
    frameNode_->AddChild(rightArrow);
    frameNode_->AddChild(indicatorNode1);
    layoutProperty_->UpdateIsSidebarMiddle(true);
    pattern_->CheckAndSetArrowHoverState(mousePoint);
    layoutProperty_->UpdateIsSidebarMiddle(false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->CheckAndSetArrowHoverState(mousePoint);
            if (i == 1) {
                pattern_->currentIndex_ = 1;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
    }
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    for (int i = 0; i <= 1; i++) {
        pattern_->CheckAndSetArrowHoverState(mousePoint);
        layoutProperty_->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternHandleMouseEvent001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleMouseEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto info = MouseInfo();
    layoutProperty_->UpdateShowIndicator(true);

    /**
     * @tc.steps: step2. call HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->HandleMouseEvent(info);
        layoutProperty_->UpdateShowIndicator(false);
    }
}

/**
 * @tc.name: SwiperPatternGetCustomPropertyOffset001
 * @tc.desc: GetCustomPropertyOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCustomPropertyOffset001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->ResetPrevMargin();

    /**
     * @tc.steps: step2. call GetCustomPropertyOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetCustomPropertyOffset();
            if (i == 1) {
                break;
            }
            layoutProperty_->UpdateDirection(Axis::VERTICAL);
            layoutProperty_->UpdatePrevMargin(Dimension(0));
        }
        layoutProperty_->UpdatePrevMargin(Dimension(1));
    }
}

/**
 * @tc.name: SwiperPatternGetCurrentFirstIndexStartPos001
 * @tc.desc: GetCurrentFirstIndexStartPos
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCurrentFirstIndexStartPos001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetCurrentFirstIndexStartPos.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        ASSERT_EQ(pattern_->GetCurrentFirstIndexStartPos(), i == 0 ? 0.0 : 1);
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAnimationStart001
 * @tc.desc: OnSpringAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnSpringAnimationStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    float velocity = 200.0f;
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnSpringAnimationStart(velocity);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAndFadeAnimationFinish001
 * @tc.desc: OnSpringAndFadeAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnSpringAndFadeAnimationFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAndFadeAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->fadeAnimationIsRunning_ = true;
        pattern_->OnSpringAndFadeAnimationFinish();
        EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnFadeAnimationStart001
 * @tc.desc: OnFadeAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnFadeAnimationStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnFadeAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->fadeAnimationIsRunning_ = false;
        pattern_->OnFadeAnimationStart();
        EXPECT_TRUE(pattern_->fadeAnimationIsRunning_);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternComputeNextIndexByVelocity001
 * @tc.desc: ComputeNextIndexByVelocity
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternComputeNextIndexByVelocity001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float velocity = 0.1f;
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 2, 1 }));

    /**
     * @tc.steps: step2. call ComputeNextIndexByVelocity.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ComputeNextIndexByVelocity(velocity);
            if (i == 1) {
                continue;
            }
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 2, 1 }));
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
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
        swiperLayoutAlgorithm->targetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward001
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackward001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
        swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
        swiperLayoutAlgorithm->targetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmSetInactive001
 * @tc.desc: SetInactive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmSetInactive001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    CreateWithItem([](SwiperModelNG model) {});
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty_);
    float startMainPos = 0.1f;
    float endMainPos = 0.0f;
    int32_t targetIndex = 1;
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
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
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
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t endIndex = -1;
    float endPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetIsLoop(false);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    swiperLayoutAlgorithm->itemPosition_.clear();
    layoutWrapper.currentChildCount_ = 2;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            if (i == 1) {
                endIndex = 1;
                auto indicatorNode_test =
                    FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
                            layoutWrapper.childrenMap_.emplace(
                    std::make_pair(1, AceType::MakeRefPtr<LayoutWrapperNode>(
                                          indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
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
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto indicatorWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(lastLayoutWrapper);
    layoutProperty->UpdateLeft(Dimension(1));
    layoutProperty->UpdateTop(Dimension(1));
    indicatorWrapper->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.parentIdealSize = OptionalSizeF(0.1f, 0.2f);
    indicatorWrapper->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    indicatorWrapper->currentChildCount_ = 1;

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
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
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
            if (i == 1 && j == 1) {
                AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_.reset();
                AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_ = 1;
            }
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->GetNodeLayoutWrapperByTag(&layoutWrapper, tagName);
                if (i == 0 && j == 1) {
                    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_.reset();
                    continue;
                } else if (i == 1 && j == 0) {
                    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_ = 1;
                    continue;
                } else if (i == 1 && j == 1) {
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

/**
 * @tc.name: SwiperLayoutAlgorithmGetChildMaxSize001
 * @tc.desc: GetChildMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmGetChildMaxSize001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        0, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty())));
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        1, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, nullptr, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    bool isMainAxis = true;
    swiperLayoutAlgorithm->totalItemCount_ = 3;

    /**
     * @tc.steps: step2. call GetChildMaxSize.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->GetChildMaxSize(&layoutWrapper, axis, isMainAxis);
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        isMainAxis = false;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper001
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasureSwiper001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    swiperLayoutAlgorithm->totalItemCount_ = 2;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
            if (i == 1) {
                int32_t targetIndex_test = 1;
                swiperLayoutAlgorithm->SetTargetIndex(targetIndex_test);
                continue;
            }
            swiperLayoutAlgorithm->prevMargin_ = 1.0f;
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 1 }));
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, -1 }));
        }
        swiperLayoutAlgorithm->isLoop_ = false;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (j == 1) {
                    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
                    continue;
                }
                if (i == 1) {
                    break;
                }
                swiperLayoutAlgorithm->jumpIndex_ = 1;
                swiperLayoutAlgorithm->startMainPos_ = 1.0f;
            }
            if (i == 1) {
                break;
            }
            swiperLayoutAlgorithm->jumpIndex_ = 0;
        }
        swiperLayoutAlgorithm->jumpIndex_ = 1;
        swiperLayoutAlgorithm->startMainPos_ = -1.0f;
    }

    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (j == 1) {
                    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
                    swiperLayoutAlgorithm->spaceWidth_ = 0.0f;
                    continue;
                }
                if (i == 1 && j == 1) {
                    break;
                }
                swiperLayoutAlgorithm->startMainPos_ = 2.0f;
                swiperLayoutAlgorithm->spaceWidth_ = -2.0f;
            }
            if (i == 1) {
                swiperLayoutAlgorithm->isLoop_ = true;
                continue;
            }
            if (i == 1 && j == 1) {
                break;
            }
            swiperLayoutAlgorithm->isLoop_ = false;
        }
        swiperLayoutAlgorithm->prevMargin_ = -1.0f;
    }

    swiperLayoutAlgorithm->jumpIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (i == 1 && j == 0) {
                    swiperLayoutAlgorithm->endMainPos_ = -2.0f;
                    continue;
                }
                if (i == 1 && j == 1) {
                    swiperLayoutAlgorithm->prevMargin_ = 1.0f;
                    continue;
                }
                if (i == 1 && j == 1 && k == 1) {
                    break;
                }
                swiperLayoutAlgorithm->targetIndex_ = 1;
                swiperLayoutAlgorithm->itemPosition_.clear();
            }
            if (i == 1) {
                swiperLayoutAlgorithm->targetIndex_ = 0;
                continue;
            }
            swiperLayoutAlgorithm->startMainPos_ = 2.0f;
        }
        swiperLayoutAlgorithm->targetIndex_ = -1.0f;
    }

    swiperLayoutAlgorithm->targetIndex_.reset();
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 1 }));
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (j == 1) {
                    swiperLayoutAlgorithm->itemPosition_.clear();
                    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
                    continue;
                }
                swiperLayoutAlgorithm->itemPosition_.clear();
                swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 3, 1 }));
                swiperLayoutAlgorithm->currentOffset_ = -1.0f;
            }
            swiperLayoutAlgorithm->itemPosition_.clear();
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 3, 1 }));
        }
        swiperLayoutAlgorithm->overScrollFeature_ = true;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
            if (i == 1) {
                swiperLayoutAlgorithm->endMainPos_ = 1.0f;
                continue;
            }
            swiperLayoutAlgorithm->endMainPos_ = 2.0f;
        }
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 3, 1 }));
    }
    swiperLayoutAlgorithm->overScrollFeature_ = false;
    swiperLayoutAlgorithm->currentOffset_ = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
            if (i == 1) {
                swiperLayoutAlgorithm->startMainPos_ = 0;
                continue;
            }
            swiperLayoutAlgorithm->startMainPos_ = 4;
        }
        swiperLayoutAlgorithm->itemPosition_.clear();
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 1, 1 }));
    }
}

/**
 * @tc.name: SwiperPatternHandleDragEnd001
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    double dragVelocity = 0.1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call HandleDragEnd.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->HandleDragEnd(dragVelocity);
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        }
        pattern_->swiperController_->removeSwiperEventCallback_ = []() {};
        ASSERT_NE(&(pattern_->swiperController_->removeSwiperEventCallback_), nullptr);
    }
}

/**
 * @tc.name: SwiperPatternUpdateCurrentOffset001
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateCurrentOffset001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    dimension.unit_ = DimensionUnit::NONE;
    layoutProperty_->UpdateMinSize(dimension);
    float offset = 0.1f;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));

    /**
     * @tc.steps: step2. call UpdateCurrentOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->UpdateCurrentOffset(offset);
            if (i == 1) {
                layoutProperty_->UpdateMinSize(dimension);
                continue;
            }
            layoutProperty_->ResetMinSize();
        }
        pattern_->itemPosition_.clear();
    }
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper001
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    frameNode_->Clean(false, false);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->BeforeCreateLayoutWrapper();
            if (i == 1) {
                frameNode_->AddChild(leftArrow);
                continue;
            }
            pattern_->rightButtonId_.reset();
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
        }
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(0);
    }

    frameNode_->AddChild(rightArrow);
    pattern_->currentIndex_ = 0;
    pattern_->oldIndex_ = 0;
    for (int i = 0; i <= 1; i++) {
        pattern_->BeforeCreateLayoutWrapper();
        pattern_->currentIndex_ = 1;
    }
    pattern_->jumpIndex_.reset();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    frameNode_->Clean(false, false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->BeforeCreateLayoutWrapper();
                if (i == 1 && j == 0) {
                    pattern_->jumpIndex_ = 0;
                    continue;
                }
                if (i == 1 && j == 1) {
                    pattern_->jumpIndex_ = 10;
                    continue;
                }
                pattern_->jumpIndex_ = -1;
                pattern_->usePropertyAnimation_ = true;
            }
            pattern_->jumpIndex_ = 10;
            pattern_->rightButtonId_.reset();
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
            frameNode_->AddChild(leftArrow);
            frameNode_->AddChild(rightArrow);
        }
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
        pattern_->jumpIndex_ = -1;
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnForceStop001
 * @tc.desc: TriggerAnimationEndOnForceStop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnForceStop001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = CustomNode::CreateCustomNode(1, "CustomNode");
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    pattern_->currentIndex_ = 0;
    pattern_->pauseTargetIndex_ = 2;
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnForceStop.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->TriggerAnimationEndOnForceStop();
            pattern_->currentIndex_ = 1;
        }
        frameNode_->Clean(false, false);
        frameNode_->AddChild(rightArrow);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternIsVisibleChildrenSizeLessThanSwiper001
 * @tc.desc: IsVisibleChildrenSizeLessThanSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternIsVisibleChildrenSizeLessThanSwiper001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    ASSERT_TRUE(static_cast<int32_t>(pattern_->itemPosition_.size()) == pattern_->TotalCount());

    /**
     * @tc.steps: step2. call IsVisibleChildrenSizeLessThanSwiper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->IsVisibleChildrenSizeLessThanSwiper();
            if (i == 1) {
                pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->IsVisibleChildrenSizeLessThanSwiper();
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        }
    }
}

/**
 * @tc.name: SwiperPatternSwipeToWithoutAnimation001
 * @tc.desc: SwipeToWithoutAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSwipeToWithoutAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    int32_t index = 1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));

    /**
     * @tc.steps: step2. call SwipeToWithoutAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->SwipeToWithoutAnimation(index);
        pattern_->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternGetLastItemInfoInVisibleArea001
 * @tc.desc: GetLastItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetLastItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetLastItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    pattern_->GetLastItemInfoInVisibleArea();
}

/**
 * @tc.name: SwiperPatternHandleDragStart001
 * @tc.desc: HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->swiperController_->SetRemoveTabBarEventCallback([]() {});

    /**
     * @tc.steps: step2. call HandleDragStart.
     * @tc.expected: Related function runs ok.
     */
    auto info = GestureEvent();
    pattern_->HandleDragStart(info);
}

/**
 * @tc.name: SwiperPatternHandleDragUpdate001
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragUpdate001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto info = GestureEvent();
    auto localLocation = Offset(-1.0, 1.0);
    info.SetLocalLocation(localLocation);
    frameNode_->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    frameNode_->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    indicatorNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    indicatorNode->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));

    /**
     * @tc.steps: step2. call HandleDragUpdate.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->HandleDragUpdate(info);
        info.SetLocalLocation(Offset(1.0, 2.0));
        frameNode_->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
        pattern_->indicatorId_ = 1;
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndicatorType(SwiperIndicatorType::DOT);
        indicatorNode->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
    }
}

/**
 * @tc.name: SwiperPatternHandleDragUpdate002
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragUpdate002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto info = GestureEvent();
    auto localLocation = Offset(-1.0, 1.0);
    info.SetLocalLocation(localLocation);
    frameNode_->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    frameNode_->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    indicatorNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    indicatorNode->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));

    /**
     * @tc.steps: step2. call HandleDragUpdate.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->HandleDragUpdate(info);
        info.SetLocalLocation(Offset(1.0, 2.0));
        frameNode_->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
        pattern_->indicatorId_ = 1;
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndicatorType(SwiperIndicatorType::DOT);
        indicatorNode->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
    }
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper002
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->BeforeCreateLayoutWrapper();
            if (i == 1) {
                pattern_->mainSizeIsMeasured_ = false;
                continue;
            }
            pattern_->mainSizeIsMeasured_ = true;
        }
        pattern_->isNeedResetPrevMarginAndNextMargin_ = true;
    }
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper003
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();
    pattern_->isVoluntarilyClear_ = false;

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->BeforeCreateLayoutWrapper();
        pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    }
}

/**
 * @tc.name: SwiperPatternIsVisibleChildrenSizeLessThanSwiper002
 * @tc.desc: IsVisibleChildrenSizeLessThanSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternIsVisibleChildrenSizeLessThanSwiper002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.clear();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 3 }));

    /**
     * @tc.steps: step2. call IsVisibleChildrenSizeLessThanSwiper.
     * @tc.expected: Related function runs ok.
     */
    pattern_->IsVisibleChildrenSizeLessThanSwiper();
}

/**
 * @tc.name: SwiperPatternHandleDragEnd002
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragEnd002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    double dragVelocity = 0.1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.clear();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateDisplayCount(0);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->fadeOffset_ = 1.0f;

    /**
     * @tc.steps: step2. call HandleDragEnd.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->HandleDragEnd(dragVelocity);
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 1, 2 }));
            pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::FADE);
    }
}

/**
 * @tc.name: SwiperPatternShowPrevious002
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowPrevious002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateShowIndicator(false);
    ASSERT_EQ(pattern_->TotalCount(), 0);
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = -1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-3);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    EXPECT_EQ(pattern_->TotalDisPlayCount(), 0);
    EXPECT_FALSE(pattern_->IsLoop());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(-3);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        frameNode_->Clean(false, false);
    }

    for (int i = 0; i <= 1; i++) {
        pattern_->ShowPrevious();
        pattern_->isVisible_ = false;
        pattern_->preTargetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper002
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasureSwiper002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    swiperLayoutAlgorithm->isLoop_ = false;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
}

/**
 * @tc.name: SwiperPatternPreviousFocus004
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus004, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    pattern_->leftButtonId_.reset();
    pattern_->indicatorId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->currentIndex_ = 1;
    layoutProperty_->UpdateShowIndicator(false);
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);

    /**
     * @tc.steps: step2. call PreviousFocus.
     * @tc.expected: frameNode_->GetFocusHub()->parentFocusable is true.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PreviousFocus(frameNode_->GetFocusHub());
            if (i == 1) {
                layoutProperty_->UpdateLoop(true);
                continue;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
    }
}

/**
 * @tc.name: SwiperPatternPreviousFocus005
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus005, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    pattern_->leftButtonId_.reset();
    pattern_->indicatorId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->currentIndex_ = 1;
    layoutProperty_->UpdateShowIndicator(false);
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);

    /**
     * @tc.steps: step2. call PreviousFocus.
     * @tc.expected: frameNode_->GetFocusHub()->parentFocusable is true.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PreviousFocus(frameNode_->GetFocusHub());
            if (i == 1) {
                layoutProperty_->UpdateLoop(true);
                continue;
            }
            pattern_->leftButtonId_ = 1;
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
    }
}

/**
 * @tc.name: SwiperPatternNextFocus004
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus004, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    pattern_->leftButtonId_.reset();
    pattern_->indicatorId_ = 1;
    pattern_->rightButtonId_.reset();
    pattern_->currentIndex_ = 1;
    layoutProperty_->UpdateShowIndicator(false);
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);

    /**
     * @tc.steps: step2. call NextFocus.
     * @tc.expected: the related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->NextFocus(frameNode_->GetFocusHub());
            if (i == 1) {
                layoutProperty_->UpdateLoop(true);
                continue;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
    }
}

/**
 * @tc.name: SwiperInitIndicator006
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->indicatorId_ = 1;
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateShowIndicator(true);
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DOT;

    /**
     * @tc.steps: step2. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperPatternAutoPlay002
 * @tc.desc: StartAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAutoPlay002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->isVisible_ = true;
    pattern_->isIndicatorLongPress_ = false;
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);

    /**
     * @tc.steps: step2. call StartAutoPlay.
     * @tc.expected: Related functions run ok.
     */
    pattern_->StartAutoPlay();
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm002
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCreateLayoutAlgorithm002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->jumpIndex_.reset();
    pattern_->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    pattern_->CreateLayoutAlgorithm();
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm003
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCreateLayoutAlgorithm003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float velocity = 0.1f;

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->UpdateAnimationProperty(velocity);
        pattern_->isDragging_ = true;
    }
}

/**
 * @tc.name: SwiperPatternOnTouchTestHit002
 * @tc.desc: OnTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTouchTestHit002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto hitTestType = SourceType::MOUSE;

    /**
     * @tc.steps: step2. call OnTouchTestHit.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnTouchTestHit(hitTestType);
        pattern_->isTouchDown_ = true;
    }
}

/**
 * @tc.name: SwiperPatternHandleTouchDown001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchDown001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->usePropertyAnimation_ = true;

    /**
     * @tc.steps: step2. call HandleTouchDown.
     * @tc.expected: Related function runs ok.
     */
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    pattern_->HandleTouchDown(touchLocationInfo);
}

/**
 * @tc.name: SwiperPatternPlayPropertyTranslateAnimation002
 * @tc.desc: PlayPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayPropertyTranslateAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->usePropertyAnimation_ = true;
    float translate = 0.1f;
    int32_t nextIndex = 1;
    float velocity = 0.1f;
    pattern_->usePropertyAnimation_ = true;
    pattern_->itemPositionInAnimation_.clear();
    pattern_->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call HandleTouchDown.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg002
 * @tc.desc: HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::CANCEL);
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::MOVE);
    indicatorPattern->isPressed_ = true;
    indicatorPattern->HandleTouchEvent(touchEventInfo);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg003
 * @tc.desc: HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = GestureEvent();
    indicatorPattern->HandleLongPress(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg004
 * @tc.desc: HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->HandleHoverEvent(true);
    indicatorPattern->HandleHoverEvent(false);
}

/**
 * @tc.name: SwiperPatternPreviousFocus006
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus006, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->indicatorId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->currentIndex_ = 1;
    EXPECT_TRUE(pattern_->IsLoop());
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);

    /**
     * @tc.steps: step2. call PreviousFocus.
     * @tc.expected: frameNode_->GetFocusHub()->parentFocusable is true.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PreviousFocus(frameNode_->GetFocusHub());
            if (i == 1) {
                layoutProperty_->UpdateLoop(true);
                continue;
            }
            pattern_->indicatorId_ = 1;
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
    }
}

/**
 * @tc.name: SwiperInitArrow001
 * @tc.desc: Test SwiperPattern SwiperInitArrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitArrow001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();

    layoutProperty_->UpdateDisplayArrow(true);
    layoutProperty_->UpdateHoverShow(true);
    layoutProperty_->UpdateIsShowBackground(true);
    layoutProperty_->UpdateBackgroundSize(Dimension(1));
    layoutProperty_->UpdateBackgroundColor(Color(1));
    layoutProperty_->UpdateArrowSize(Dimension(1));
    layoutProperty_->UpdateArrowColor(Color(1));
    layoutProperty_->UpdateIsSidebarMiddle(true);

    /**
     * @tc.steps: step3. call InitArrow.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->InitArrow();
            if (i == 1) {
                break;
            }
            pattern_->leftButtonId_ = 1;
        }
        layoutProperty_->UpdateDisplayArrow(false);
    }

    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->InitArrow();
    EXPECT_FALSE(pattern_->HasLeftButtonNode());
    EXPECT_FALSE(pattern_->HasRightButtonNode());
}

/**
 * @tc.name: SwiperModelNGSetDisplayCount001
 * @tc.desc: Test SetDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNGSetDisplayCount001, TestSize.Level1)
{
    SwiperModelNG mode;
    auto controller = mode.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    ASSERT_NE(controller, nullptr);
    int32_t displayCount = 0;

    /**
     * @tc.steps: step3. call SetDisplayCount.
     * @tc.expected: the related function runs ok.
     */
    mode.SetDisplayCount(displayCount);
}

/**
 * @tc.name: SwiperPatternUpdateCurrentOffset002
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateCurrentOffset002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    dimension.unit_ = DimensionUnit::NONE;
    layoutProperty_->UpdateMinSize(dimension);
    float offset = 0.1f;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    pattern_->contentMainSize_ = 1;
    pattern_->currentOffset_ = 1;
    pattern_->isDragging_ = true;
    pattern_->currentDelta_ = 1.0f;
    pattern_->currentIndexOffset_ = 1.0f;

    /**
     * @tc.steps: step2. call UpdateCurrentOffset.
     * @tc.expected: Related function runs ok.
     */
    pattern_->UpdateCurrentOffset(offset);
    EXPECT_LT(pattern_->currentDelta_, 1.0f);
    EXPECT_GT(pattern_->currentIndexOffset_, 1.0f);
    pattern_->currentOffset_ = 0;
    pattern_->isDragging_ = true;
    pattern_->UpdateCurrentOffset(offset);
    EXPECT_GT(pattern_->currentDelta_, 0.712f);
    EXPECT_LT(pattern_->currentIndexOffset_, 1.288f);
    pattern_->isDragging_ = false;
    pattern_->UpdateCurrentOffset(offset);
    EXPECT_LT(pattern_->currentIndexOffset_, 1.388f);
}

/**
 * @tc.name: SwiperPatternUpdateCurrentOffset003
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateCurrentOffset003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    dimension.unit_ = DimensionUnit::NONE;
    layoutProperty_->UpdateMinSize(dimension);
    float offset = 0.1f;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::FADE);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    pattern_->contentMainSize_ = 1;
    pattern_->currentOffset_ = 1;
    pattern_->currentDelta_ = 1.0f;

    /**
     * @tc.steps: step2. call UpdateCurrentOffset.
     * @tc.expected: Related function runs ok.
     */
    pattern_->UpdateCurrentOffset(offset);
    EXPECT_FLOAT_EQ(pattern_->currentDelta_, 0.9f);
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->UpdateCurrentOffset(offset);
    EXPECT_FLOAT_EQ(pattern_->currentDelta_, 0.8f);
}

/**
 * @tc.name: SwiperPatternUpdateCurrentOffset004
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateCurrentOffset004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    dimension.unit_ = DimensionUnit::NONE;
    layoutProperty_->UpdateMinSize(dimension);
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    float offset = 0.1f;
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::FADE);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    pattern_->contentMainSize_ = 1;
    pattern_->currentOffset_ = 1;
    pattern_->isDragging_ = true;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->currentDelta_ = 1.0f;
    pattern_->currentIndexOffset_ = 1.0f;

    /**
     * @tc.steps: step2. call UpdateCurrentOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->UpdateCurrentOffset(offset);
            if (i == 1) {
                pattern_->itemPosition_.clear();
                pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
                pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1.0f, 2.0f }));
                continue;
            }
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1.0f, 2.0f }));
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1.0f, 2.0f }));
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    }
    EXPECT_FLOAT_EQ(pattern_->currentDelta_, 0.6f);
    layoutProperty_->UpdateLoop(true);
    EXPECT_FLOAT_EQ(pattern_->currentIndexOffset_, 1.1f);
    pattern_->UpdateCurrentOffset(offset);
    EXPECT_FLOAT_EQ(pattern_->currentIndexOffset_, 1.2f);
    EXPECT_FLOAT_EQ(pattern_->currentDelta_, 0.5f);
    pattern_->isDragging_ = false;
    pattern_->UpdateCurrentOffset(offset);
    EXPECT_FLOAT_EQ(pattern_->currentDelta_, 0.4f);
    EXPECT_FLOAT_EQ(pattern_->currentIndexOffset_, 1.3f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper003
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasureSwiper003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 0.0f }));
    swiperLayoutAlgorithm->prevMargin_ = -1.0f;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForwardItem001
 * @tc.desc: LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForwardItem001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t currentIndex = 0;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 1;
    layoutWrapper.AppendChild(firstLayoutWrapper);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    indicatorNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())->ResetDisplayCount();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call LayoutForwardItem.
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
}

/**
 * @tc.name: SwiperPatternOnModifyDone001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    frameNode_->AddChild(indicatorNode);


    RefPtr<SwiperPattern> indicatorPattern = indicatorNode->GetPattern<SwiperPattern>();
    indicatorPattern->panEvent_ =
        AceType::MakeRefPtr<PanEvent>([](GestureEvent&) {}, [](GestureEvent&) {}, [](GestureEvent&) {}, [] {});
    indicatorPattern->OnModifyDone();
}

/**
 * @tc.name: SwiperFlushFocus002
 * @tc.desc: Swiper FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFlushFocus002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);
    focusHub->currentFocus_ = true;
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps: step2. Create curShowFrameNode, addChild to frameNode.
     */
    auto curShowFrame = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto child1 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    child->GetOrCreateFocusHub();
    child1->GetOrCreateFocusHub();
    curShowFrame->AddChild(child);
    frameNode_->AddChild(child1);
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(child);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub1);
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    eventHub2->AttachHost(child1);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(eventHub2);

    /**
     * @tc.steps: step3. test FlushFocus with IsShowIndicator() is true.
     * @tc.expected: the related function runs ok.
     */
    layoutProperty_->UpdateShowIndicator(true);
    pattern_->isLastIndicatorFocused_ = true;
    pattern_->FlushFocus(curShowFrame);
}

/**
 * @tc.name: SwiperPatternShowPrevious003
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowPrevious003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = 1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    frameNode_->AddChild(indicatorNode);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());
    EXPECT_TRUE(pattern_->preTargetIndex_.has_value());
    EXPECT_TRUE(pattern_->IsLoop());
    EXPECT_EQ(pattern_->TotalCount(), 3);
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
    pattern_->targetIndex_ = 2;
    EXPECT_FALSE(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()) <= 0 && !pattern_->IsLoop());
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());
    EXPECT_FALSE(pattern_->TotalCount() <= 0 || pattern_->GetDisplayCount() == 0);

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->preTargetIndex_.value(), -1);
    pattern_->isVisible_ = false;
    pattern_->preTargetIndex_ = 0;
    pattern_->isUserFinish_ = true;
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->preTargetIndex_.value(), 0);
}

/**
 * @tc.name: SwiperPatternNextFocus005
 * @tc.desc: Test SwiperPattern SwiperPatternNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternNextFocus005, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    pattern_->leftButtonId_.reset();
    pattern_->indicatorId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->currentIndex_ = 1;
    layoutProperty_->UpdateShowIndicator(false);
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(rightArrow);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub1);
    focusHub->parentFocusable_ = false;

    /**
     * @tc.steps: step2. call NextFocus.
     * @tc.expected: the related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->NextFocus(frameNode_->GetFocusHub());
            if (i == 1) {
                pattern_->currentIndex_ = 1;
                continue;
            }
            pattern_->currentIndex_ = 0;
            EXPECT_FALSE(pattern_->isLastIndicatorFocused_);
        }
        layoutProperty_->UpdateLoop(false);
    }
}

/**
 * @tc.name: SwiperPatternPreviousFocus007
 * @tc.desc: Test SwiperPattern SwiperPatternPreviousFocus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPreviousFocus007, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->Clean(false, false);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->indicatorId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->leftButtonId_ = 1;
    pattern_->currentIndex_ = 0;
    EXPECT_TRUE(pattern_->IsLoop());
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);
    pattern_->isLastIndicatorFocused_ = false;
    focusHub->parentFocusable_ = false;
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(leftArrow);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub1);

    /**
     * @tc.steps: step2. call PreviousFocus.
     * @tc.expected: frameNode_->GetFocusHub()->parentFocusable is true.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PreviousFocus(frameNode_->GetFocusHub());
            if (i == 1) {
                pattern_->currentIndex_ = 0;
                continue;
            }
            pattern_->currentIndex_ = 1;
            EXPECT_FALSE(pattern_->isLastIndicatorFocused_);
        }
        layoutProperty_->UpdateLoop(false);
    }
}

/**
 * @tc.name: SwiperPatternPostTranslateTask002
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPostTranslateTask002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    uint32_t delayTime = 10;
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    };
    pattern_->itemPosition_.clear();
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateDisplayCount(2);
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call PostTranslateTask.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PostTranslateTask(delayTime);
            pattern_->translateTask_();
            if (i == 1) {
                layoutProperty_->UpdateLoop(true);
                continue;
            }
            layoutProperty_->UpdateLoop(false);
        }
        pattern_->currentIndex_ = 0;
    }
    EXPECT_EQ(pattern_->targetIndex_.value(), 1);
}

/**
 * @tc.name: SwiperOnLoopChange001
 * @tc.desc: Swiper OnLoopChange.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperOnLoopChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->preLoop_ = true;
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->ResetPrevMargin();
    layoutProperty_->ResetNextMargin();

    /**
     * @tc.steps: step2. call OnLoopChange.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnLoopChange();
            if (i == 1) {
                layoutProperty_->ResetPrevMargin();
                continue;
            }
            layoutProperty_->UpdatePrevMargin(Dimension(1));
        }
        layoutProperty_->UpdateNextMargin(Dimension(1));
    }
}

/**
 * @tc.name: SwiperPatternInitPanEvent001
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitPanEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    frameNode_->AddChild(indicatorNode);


    /**
     * @tc.steps: step2. test InitPanEvent.
     * @tc.expected: Related function runs ok.
     */
    RefPtr<SwiperPattern> indicatorPattern = indicatorNode->GetPattern<SwiperPattern>();
    indicatorPattern->panEvent_ =
        AceType::MakeRefPtr<PanEvent>([](GestureEvent&) {}, [](GestureEvent&) {}, [](GestureEvent&) {}, [] {});
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub_);
    indicatorPattern->direction_ = Axis::HORIZONTAL;
    indicatorPattern->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);
    indicatorPattern->InitPanEvent(gestureHub);
    auto info = GestureEvent();
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    indicatorPattern->panEvent_->actionStart_(info);
    indicatorPattern->panEvent_->actionEnd_(info);
    info.SetMainDelta(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            indicatorPattern->InitPanEvent(gestureHub);
            indicatorPattern->panEvent_->actionUpdate_(info);
            if (i == 1) {
                info.SetInputEventType(InputEventType::AXIS);
                continue;
            }
            info.SetInputEventType(InputEventType::MOUSE_BUTTON);
        }
        info.SetSourceTool(SourceTool::TOUCHPAD);
    }
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(-1);
    indicatorPattern->InitPanEvent(gestureHub);
    indicatorPattern->panEvent_->actionUpdate_(info);
}

/**
 * @tc.name: SwiperPatternCheckMarkDirtyNodeForRenderIndicator001
 * @tc.desc: Test CheckMarkDirtyNodeForRenderIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCheckMarkDirtyNodeForRenderIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto indicatorNode_test =
        FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    indicatorNode->AddChild(indicatorNode_test);


    RefPtr<SwiperPattern> indicatorPattern = indicatorNode->GetPattern<SwiperPattern>();

    /**
     * @tc.steps: step2. test CheckMarkDirtyNodeForRenderIndicator.
     * @tc.expected: Related function runs ok.
     */
    indicatorPattern->indicatorId_.reset();
    float additionalOffset = 0.1f;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
    indicatorPattern->indicatorId_ = 1;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
}

/**
 * @tc.name: SwiperIndicatorPatternHandleLongDragUpdate001
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternHandleLongDragUpdate001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternCheckIsTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternCheckIsTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->currentIndex_ = -5;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
}

/**
 * @tc.name: SwiperPatternHandleTouchUp002
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchUp002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->isDragging_ = false;
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->velocity_ = 1.0f;

    /**
     * @tc.steps: step2. call HandleTouchUp.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->HandleTouchUp();
            if (i == 1) {
                pattern_->isDragging_ = false;
                continue;
            }
            pattern_->isDragging_ = true;
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
    }
    EXPECT_FLOAT_EQ(pattern_->velocity_.value(), 1.f);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation003
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    pattern_->stopIndicatorAnimation_ = false;
    pattern_->itemPosition_.clear();
    float translate = 0.1f;

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlayIndicatorTranslateAnimation(translate);
    pattern_->stopIndicatorAnimation_ = true;
    pattern_->indicatorId_ = 1;
    pattern_->PlayIndicatorTranslateAnimation(translate);
}

/**
 * @tc.name: SwiperPatternPlaySpringAnimation001
 * @tc.desc: PlaySpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlaySpringAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->contentMainSize_ = 1.0f;
    pattern_->itemPosition_.clear();
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    double dragVelocity = 0.1f;

    /**
     * @tc.steps: step2. call PlaySpringAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlaySpringAnimation(dragVelocity);
}

/**
 * @tc.name: SwiperPatternHandleDragEnd003
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragEnd003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_NE(frameNode_->GetLayoutProperty<SwiperLayoutProperty>(), nullptr);
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(rightArrow);
    frameNode_->AddChild(indicatorNode);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    double dragVelocity = 0.1;
    pattern_->fadeOffset_ = 1.0f;
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->currentIndex_ = 2;

    /**
     * @tc.steps: step2. call HandleDragEnd.
     * @tc.expected: Related function runs ok.
     */
    pattern_->swiperController_->SetAddTabBarEventCallback([] { return; });
    pattern_->HandleDragEnd(dragVelocity);
}

/**
 * @tc.name: SwiperIndicatorPatternHandleLongDrag001
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternHandleLongDrag001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    layoutProperty_->UpdateDisplayCount(10);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    GestureEvent info;
    info.mainDelta_ = 1.0f;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchLocationInfo));

    pattern_->currentIndex_ = 0;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchLocationInfo));
}

/**
 * @tc.name: SwiperIndicatorPatternHandleDragEnd001
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternHandleDragEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    indicatorPattern->HandleDragEnd(1.0f);
    paintProperty_->UpdateAutoPlay(true);
    indicatorPattern->HandleDragEnd(1.0f);
    ASSERT_TRUE(paintProperty_->GetAutoPlay().value_or(false));
}

/**
 * @tc.name: SwiperIndicatorGetMouseClickIndex001
 * @tc.desc: Test GetMouseClickIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorGetMouseClickIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    indicatorPattern->GetMouseClickIndex();
    paintProperty->UpdateIsCustomSize(true);
    indicatorPattern->GetMouseClickIndex();
    ASSERT_TRUE(paintProperty->GetIsCustomSizeValue(false));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0010
 * @tc.desc: HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0010, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    paintProperty_->UpdateAutoPlay(true);
    auto info = GestureEvent();
    indicatorPattern->HandleLongPress(info);
    ASSERT_TRUE(paintProperty_->GetAutoPlay().value_or(false));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0011
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0011, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    touchEventInfo.touches_.front().localLocation_.SetX(50.0f);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    pattern_->currentIndex_ = 0;
    layoutProperty_->UpdateLoop(false);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0012
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0012, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    info.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::PRESS;
    indicatorPattern->isClicked_ = true;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);
    info.localLocation_.SetX(5.0);
    info.localLocation_.SetY(15.0);
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0013
 * @tc.desc: InitHoverMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0013, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    auto info = HoverInfo();
    auto info1 = MouseInfo();
    indicatorPattern->hoverEvent_ = nullptr;
    info.SetSourceDevice(SourceType::NONE);
    indicatorPattern->InitHoverMouseEvent();
    indicatorPattern->hoverEvent_->onHoverEventCallback_(true, info);
    indicatorPattern->mouseEvent_->onMouseCallback_(info1);
    indicatorPattern->hoverEvent_ = nullptr;
    info.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern->InitHoverMouseEvent();
    indicatorPattern->hoverEvent_->onHoverEventCallback_(true, info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0014
 * @tc.desc: HandleMouseClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0014, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    indicatorPattern->isRepeatClicked_ = true;
    auto info = GestureEvent();
    indicatorPattern->HandleMouseClick(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0015
 * @tc.desc: HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0015, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->isHover_ = true;
    layoutProperty_->UpdateHoverShow(true);
    pattern_->isAtHotRegion_ = false;
    indicatorPattern->HandleHoverEvent(true);
    indicatorPattern->HandleHoverEvent(false);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0016
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0016, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    touchEventInfo.touches_.front().localLocation_.SetX(50.0f);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    touchEventInfo.touches_.front().localLocation_.SetX(1.0f);
    indicatorPattern->dragStartPoint_.SetX(20.0f);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    touchEventInfo.touches_.front().localLocation_.SetX(1.0f);
    indicatorPattern->dragStartPoint_.SetX(10.0f);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0017
 * @tc.desc: InitTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0017, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    TouchEventInfo touchEventInfo("down");
    indicatorPattern->touchEvent_ = nullptr;
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    indicatorPattern->InitTouchEvent(gestureHub);
    indicatorPattern->touchEvent_->callback_(touchEventInfo);
}

/**
 * @tc.name: SwiperPatternCheckMarkDirtyNodeForRenderIndicator002
 * @tc.desc: Test CheckMarkDirtyNodeForRenderIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCheckMarkDirtyNodeForRenderIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    indicatorNode->AddChild(indicatorNode_test);


    RefPtr<SwiperPattern> indicatorPattern = indicatorNode->GetPattern<SwiperPattern>();
    float additionalOffset = -1.0f;
    indicatorPattern->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 0.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(3, SwiperItemInfo { 1.0f, 0.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 2.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1.0f, 2.0f }));

    /**
     * @tc.steps: step2. test CheckMarkDirtyNodeForRenderIndicator.
     * @tc.expected: Related function runs ok.
     */
    indicatorPattern->indicatorId_ = 1;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation004
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    pattern_->stopIndicatorAnimation_ = false;
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 0.0f }));
    float translate = 0.1f;
    pattern_->swiperController_->SetTurnPageRateCallback(nullptr);

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->stopIndicatorAnimation_ = true;
    pattern_->indicatorId_ = 1;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PlayIndicatorTranslateAnimation(translate);
            if (i == 1) {
                pattern_->swiperController_->SetTurnPageRateCallback(nullptr);
                continue;
            }
            pattern_->swiperController_->SetTurnPageRateCallback([](int32_t, float) {});
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    }
}

/**
 * @tc.name: SwiperPatternInitHoverMouseEvent001
 * @tc.desc: InitHoverMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitHoverMouseEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    eventHub_->AttachHost(frameNode_);
    pattern_->hoverEvent_ = nullptr;
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->InitHoverMouseEvent();
    pattern_->hoverEvent_->onHoverCallback_(true);
    pattern_->mouseEvent_->onMouseCallback_(info);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->InitHoverMouseEvent();
    pattern_->hoverEvent_->onHoverCallback_(true);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward004
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackward004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    indicatorNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t endIndex = -1;
    float endPos = 2.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->isLoop_ = false;
    swiperLayoutAlgorithm->startMainPos_ = 0.0f;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
    swiperLayoutAlgorithm->totalItemCount_ = 1;
    swiperLayoutAlgorithm->nextMargin_ = 0.0f;
    swiperLayoutAlgorithm->endMainPos_ = 1.0f;
    swiperLayoutAlgorithm->spaceWidth_ = 0.0f;
    swiperLayoutAlgorithm->overScrollFeature_ = false;
    int32_t currentIndex = 0;
    EXPECT_FALSE(
        swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, axis, currentIndex, 0.0f, endPos));
    EXPECT_FLOAT_EQ(endPos, 2.0f);
    swiperLayoutAlgorithm->contentMainSize_ = 1.0f;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            swiperLayoutAlgorithm->startMainPos_ = 0.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->canOverScroll_ = false;
                continue;
            }
            swiperLayoutAlgorithm->canOverScroll_ = true;
        }
        swiperLayoutAlgorithm->jumpIndex_ = 1;
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->startMainPos_, 0.0f);
    EXPECT_TRUE(GreatNotEqual(endPos, swiperLayoutAlgorithm->startMainPos_));
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            swiperLayoutAlgorithm->startMainPos_ = 0.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 2.0f, 2.0f }));
                swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
                continue;
            }
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
            swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
        }
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 2.0f, 2.0f }));
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->contentMainSize_, 1.0f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward003
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
        layoutProperty_->UpdateMinSize(Dimension(0));
        layoutProperty_->UpdateDisplayCount(0);
        layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward004
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(0));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 1.0f }));

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
                continue;
            }
            swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
        }
        layoutProperty_->UpdateMinSize(Dimension(1));
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->endMainPos_, 480.0f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward005
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    auto currentIndex = startIndex - 1;
    auto result = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper, layoutConstraint, axis, currentIndex, currentStartPos, currentEndPos);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
        startIndex = 2;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward006
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    swiperLayoutAlgorithm->jumpIndex_ = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 1.0f }));
    swiperLayoutAlgorithm->endMainPos_ = 1.0f;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            swiperLayoutAlgorithm->endMainPos_ = 1.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->canOverScroll_ = false;
                continue;
            }
            swiperLayoutAlgorithm->canOverScroll_ = true;
        }
        swiperLayoutAlgorithm->jumpIndex_.reset();
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward007
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward007, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    swiperLayoutAlgorithm->jumpIndex_ = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 0.0f }));
    swiperLayoutAlgorithm->prevMargin_ = 0.0f;
    swiperLayoutAlgorithm->contentMainSize_ = 0.0f;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
    EXPECT_FALSE(swiperLayoutAlgorithm->itemPosition_.empty());
}

/**
 * @tc.name: SwiperPatternOnTranslateFinish002
 * @tc.desc: OnTranslateFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTranslateFinish002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    bool forceStop = true;
    frameNode_->Clean(false, false);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto indicatorNode1 = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG, pattern_->GetIndicatorId(),
        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->currentIndex_ = 1;
    frameNode_->AddChild(leftArrow);
    frameNode_->AddChild(indicatorNode1);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->isVisible_ = true;
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    pattern_->isIndicatorLongPress_ = false;
    EXPECT_EQ(frameNode_->GetChildren().size(), 2);
    auto indicatorNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(
        frameNode_->GetChildIndexById(indicatorNode1->GetId())));
    EXPECT_NE(indicatorNode, nullptr);

    /**
     * @tc.steps: step2. call OnTranslateFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnTranslateFinish(nextIndex, restartAutoPlay, forceStop);
            if (i == 1) {
                pattern_->isUserFinish_ = true;
                continue;
            }
            pattern_->isUserFinish_ = false;
        }
        pattern_->isVisible_ = false;
    }
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0018
 * @tc.desc: HandleTouchClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0018, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    auto info = GestureEvent();
    layoutProperty_->UpdateDirection(Axis::NONE);
    info.localLocation_.SetX(5.0f);
    indicatorPattern->HandleTouchClick(info);
    layoutProperty_->UpdateDirection(Axis::NONE);
    info.localLocation_.SetX(500.0f);
    indicatorPattern->HandleTouchClick(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0019
 * @tc.desc: UpdateTextContentSub
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0019, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);

    auto firstTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto lastTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    pattern_->currentFirstIndex_ = -2;
    layoutProperty_->UpdateIndex(1);
    indicatorPattern->UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0020
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0020, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->Clean(false, false);
    frameNode_->AddChild(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.mainDelta_ = 1.0f;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->currentIndex_ = 0;
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
    layoutProperty_->UpdateLoop(false);
    ASSERT_FALSE(layoutProperty_->GetLoop().value_or(true));
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    touchEventInfo.touches_.front().localLocation_.SetX(2.0f);
    indicatorPattern->dragStartPoint_.SetX(1.0f);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0021
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0021, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    info.SetSourceDevice(SourceType::MOUSE);
    info.action_ = MouseAction::PRESS;
    indicatorPattern->isClicked_ = true;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);
    info.localLocation_.SetX(5.0);
    info.localLocation_.SetY(15.0);
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperPatternOnModifyDone002
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnModifyDone002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    frameNode_->AddChild(indicatorNode);


    RefPtr<SwiperPattern> indicatorPattern = indicatorNode->GetPattern<SwiperPattern>();
    indicatorPattern->panEvent_ =
        AceType::MakeRefPtr<PanEvent>([](GestureEvent&) {}, [](GestureEvent&) {}, [](GestureEvent&) {}, [] {});
    indicatorPattern->OnModifyDone();
    indicatorPattern->swiperController_->removeSwiperEventCallback_();
    indicatorPattern->swiperController_->addSwiperEventCallback_();
    EXPECT_NE(indicatorPattern, nullptr);
}

/**
 * @tc.name: SwiperPaintMethodClipPadding001
 * @tc.desc: ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodClipPadding001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    RSCanvas canvas;

    /**
     * @tc.steps: step2. call ClipPadding.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needClipPadding_ = true;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_TRUE(swiperPaintMethod1.needClipPadding_);
    swiperPaintMethod1.needClipPadding_ = false;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_FALSE(swiperPaintMethod1.needClipPadding_);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade001
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    RSCanvas canvas;

    /**
     * @tc.steps: step2. call PaintFade whith setting needPaintFade_ and renderContext.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_TRUE(swiperPaintMethod1.needPaintFade_);
    swiperPaintMethod1.needPaintFade_ = false;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_FALSE(swiperPaintMethod1.needPaintFade_);
    paintWrapper.renderContext_ = renderContext;
    swiperPaintMethod1.needClipPadding_ = true;
    renderContext->UpdateClipEdge(false);
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    paintWrapper.renderContext_ = nullptr;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_TRUE(swiperPaintMethod1.needClipPadding_);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade002
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    RSCanvas canvas;
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = 1.0f;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 1.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
    swiperPaintMethod1.mainDelta_ = 0.002f;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 0.002f);
}

/**
 * @tc.name: SwiperPatternAlgorithmMeasure001
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });

    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper;
    CreateSwiperLayoutWrapper(frameNode_, swiperLayoutWrapper);

    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    /**
     * @tc.steps: step3. Create arrow node and layoutWrapper.
     */
    RefPtr<FrameNode> leftArrowNode;
    RefPtr<FrameNode> rightArrowNode;
    RefPtr<LayoutWrapperNode> leftArrowNodeWrapper;
    RefPtr<LayoutWrapperNode> rightArrowNodeWrapper;
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_LEFT_ARROW_ETS_TAG, leftArrowNode, leftArrowNodeWrapper);
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_RIGHT_ARROW_ETS_TAG, rightArrowNode, rightArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(leftArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(rightArrowNodeWrapper);

    /**
     * @tc.steps: step4. call Measure.
     * @tc.expected: Return button measure, SizeF(3.0f, 3.0f).
     */
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_FALSE(swiperPatternAlgorithm->mainSizeIsMeasured_);
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    swiperLayoutWrapper->isConstraintNotChanged_ = true;
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_TRUE(swiperLayoutWrapper->isConstraintNotChanged_);
}

/**
 * @tc.name: SwiperPaintMethodGetForegroundDrawFunction001
 * @tc.desc: GetForegroundDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodGetForegroundDrawFunction001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    RSCanvas canvas;

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    auto canvasDrawFunction = swiperPaintMethod1.GetForegroundDrawFunction(&paintWrapper);
    canvasDrawFunction(canvas);
    EXPECT_TRUE(canvasDrawFunction);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade003
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    RSCanvas canvas;
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = -1.0f;
    EXPECT_FALSE(NearZero(swiperPaintMethod1.mainDelta_));
    EXPECT_FALSE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -1.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade004
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    RSCanvas canvas;
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(paintWrapper.paintProperty_, nullptr);
    auto frameSize = paintWrapper.GetGeometryNode()->GetFrameSize();
    /**
     * @tc.steps: step2. call PaintFade whith setting mainDelta_ and width.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = 3000.0f;
    float testnumber = 2000.0f;
    frameSize.SetWidth(testnumber);
    EXPECT_EQ(frameSize.width_, testnumber);
    EXPECT_FALSE(NearZero(swiperPaintMethod1.mainDelta_));
    EXPECT_TRUE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::VERTICAL);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 3000.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    frameSize.SetHeight(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 3000.0f);

    /**
     * @tc.steps: step3. call PaintFade whith setting mainDelta_ and width in different confidions.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.mainDelta_ = -3000.0f;
    EXPECT_FALSE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    swiperPaintMethod1.axis_ = Axis::VERTICAL;
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::VERTICAL);
    frameSize.SetWidth(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -3000.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
    frameSize.SetHeight(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -3000.0f);
}

/**
 * @tc.name: SwiperPatternRegisterVisibleAreaChange002
 * @tc.desc: RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternRegisterVisibleAreaChange002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto pipeline = frameNode_->GetContext();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call RegisterVisibleAreaChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->hasVisibleChangeRegistered_ = false;
    paintProperty_->UpdateAutoPlay(true);
    pattern_->RegisterVisibleAreaChange();
    EXPECT_TRUE(pattern_->hasVisibleChangeRegistered_);
    pattern_->isWindowShow_ = false;
    pattern_->hasVisibleChangeRegistered_ = false;
    paintProperty_->UpdateAutoPlay(true);
    pattern_->RegisterVisibleAreaChange();
    EXPECT_TRUE(pattern_->hasVisibleChangeRegistered_);
}

/**
 * @tc.name: SwiperPatternInitSurfaceChangedCallback001
 * @tc.desc: InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitSurfaceChangedCallback001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    frameNode_->Clean(false, false);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });

    /**
     * @tc.steps: step2. call InitSurfaceChangedCallback and then callback.
     * @tc.expected: Related function is called.
     */
    auto pipeline = frameNode_->GetContext();
    pattern_->surfaceChangedCallbackId_.emplace(1);
    pattern_->InitSurfaceChangedCallback();
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber, 1);
    auto testFunction = pipeline->surfaceChangedCallbackMap_[1];
    testFunction(1, 1, 1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);
    auto callbacknumber = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber, 1);

    /**
     * @tc.steps: step3. call InitSurfaceChangedCallback and then callback in different conditions.
     * @tc.expected: Related function is called.
     */
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber2 = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber2, 1);
    auto testFunction2 = pipeline->surfaceChangedCallbackMap_[1];
    testFunction2(1, 1, 1, 1, WindowSizeChangeReason::UNDEFINED);
    auto callbacknumber2 = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber2, 1);

    auto childswiperNode1 = FrameNode::CreateFrameNode("childswiper", 1, AceType::MakeRefPtr<SwiperPattern>(), false);
    childswiperNode1->MountToParent(frameNode_);
    auto childswiperNode2 =
        FrameNode::CreateFrameNode(V2::JS_LAZY_FOR_EACH_ETS_TAG, 2, AceType::MakeRefPtr<SwiperPattern>(), false);
    childswiperNode2->MountToParent(frameNode_);
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber3 = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber3, 1);
    auto testFunction3 = pipeline->surfaceChangedCallbackMap_[1];
    testFunction3(1, 1, 1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);
    auto callbacknumber3 = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber3, 1);
}

/**
 * @tc.name: SwiperPatternMarkDirtyNodeSelf001
 * @tc.desc: MarkDirtyNodeSelf
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternMarkDirtyNodeSelf001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    frameNode_->Clean(false, false);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call MarkDirtyNodeSelf.
     * @tc.expected: Related function is called.
     */
    pattern_->crossMatchChild_ = true;
    pattern_->MarkDirtyNodeSelf();
    EXPECT_TRUE(pattern_->crossMatchChild_);
    pattern_->crossMatchChild_ = false;
    pattern_->MarkDirtyNodeSelf();
    EXPECT_FALSE(pattern_->crossMatchChild_);
}

/**
 * @tc.name: SwiperPatternOnWindowHide001
 * @tc.desc: MarkDirtyNodeSelf
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnWindowHide001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    frameNode_->Clean(false, false);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call MarkDirtyNodeSelf.
     * @tc.expected: Related function is called.
     */
    pattern_->isDragging_ = true;
    pattern_->OnWindowHide();
    EXPECT_FALSE(pattern_->isDragging_);
    pattern_->isDragging_ = false;
    pattern_->OnWindowHide();
    EXPECT_FALSE(pattern_->isDragging_);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout006
 * @tc.desc: Test SwiperLayoutAlgorithm Layout with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper;
    CreateSwiperLayoutWrapper(frameNode_, swiperLayoutWrapper);
    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    auto indicatorGeometryNode = AceType::MakeRefPtr<GeometryNode>();
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
    InitArrowLayoutWrapper(frameNode_, "test01", leftArrowNode, leftArrowNodeWrapper);
    InitArrowLayoutWrapper(frameNode_, "test02", rightArrowNode, rightArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(leftArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(rightArrowNodeWrapper);

    /**
     * @tc.cases: case3. Axis is HORIZONTAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_NE(swiperPatternAlgorithm, nullptr);
    pattern_->leftButtonId_.emplace(1);
    pattern_->rightButtonId_.emplace(1);
    swiperPatternAlgorithm->Layout(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_NE(swiperPatternAlgorithm, nullptr);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap003
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    paintProperty_->GetAutoPlay().emplace(false);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    config.skipMeasure = false;
    paintProperty_->GetAutoPlay().emplace(false);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    paintProperty_->GetAutoPlay().emplace(true);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    paintProperty_->GetAutoPlay().emplace(true);
    config.skipMeasure = false;
    config.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForwardItem002
 * @tc.desc: LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForwardItem002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode =
        FrameNode::GetOrCreateFrameNode("test", 1, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t currentIndex = 0;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 1;
    layoutWrapper.AppendChild(firstLayoutWrapper);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    indicatorNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())->ResetDisplayCount();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call LayoutForwardItem in different layoutWrapper and make the return value false.
     * @tc.expected: Related function runs ok.
     */
    currentIndex = 0;
    auto swiperNode2 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_RIGHT_ARROW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper2 = LayoutWrapperNode(swiperNode2, geometryNode, swiperNode2->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result2 = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_FALSE(result2);
    currentIndex = 0;
    auto swiperNode3 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_LEFT_ARROW_ETS_TAG, 3, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper3 = LayoutWrapperNode(swiperNode3, geometryNode, swiperNode3->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper3, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result3 = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper3, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_FALSE(result3);
    currentIndex = 0;
    auto swiperNode4 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, 4, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper4 = LayoutWrapperNode(swiperNode4, geometryNode, swiperNode2->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper4, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result4 = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_FALSE(result4);

    /**
     * @tc.steps: step3. call LayoutForwardItem in different layoutWrapper and make the return value ture.
     * @tc.expected: Related function runs ok.
     */
    currentIndex = 0;
    auto wrapper = layoutWrapper.GetOrCreateChildByIndex(1);
    auto layoutProperty = wrapper->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_NE(result, true);
}

/**
 * @tc.name: SwiperPatternHandleScroll001
 * @tc.desc: test HandleScroll SELF_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll002
 * @tc.desc: test HandleScroll SELF_FIRST but scrolling within boundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll).Times(0);
    pattern_->parent_ = mockScroll;
    pattern_->enableNestedScroll_ = true;

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll003
 * @tc.desc: test HandleScroll SELF_FIRST while scrolling out of boundary and EdgeEffect doesn't consume extra offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo{ .startPos = -0.5 } });

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    pattern_->parent_ = mockScroll;
    pattern_->enableNestedScroll_ = true;

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 5.0f);
    EXPECT_TRUE(res.reachEdge);
}

/**
 * @tc.name: SwiperPatternHandleScroll004
 * @tc.desc: test HandleScroll SELF_FIRST and scrolling out of boundary and EdgeEffect consumes extra offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo{ .startPos = -0.5 } });

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    pattern_->parent_ = mockScroll;
    pattern_->enableNestedScroll_ = true;

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll005
 * @tc.desc: test HandleScroll called by CHILD_SCROLL when edge is reached. Should pass offset back to child.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto swiperNode = FrameNode::CreateFrameNode("Swiper", 0, AceType::MakeRefPtr<SwiperPattern>());
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    swiperPattern->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    swiperPattern->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });

    auto res = swiperPattern->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 5.0f);

    // three level nesting
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    swiperPattern->parent_ = mockScroll;
    swiperPattern->enableNestedScroll_ = true;
    res = swiperPattern->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 5.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll006
 * @tc.desc: test HandleScroll from child animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    // during animation
    pattern_->targetIndex_ = 1;

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_ANIMATION, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 5.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll007
 * @tc.desc: test HandleScroll from child mouse scroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll007, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);

    // showPrevious
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 0.0f);

    // showNext
    res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity001
 * @tc.desc: test HandleScrollVelocity self handle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScrollVelocity001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity002
 * @tc.desc: test HandleScrollVelocity pass to parent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScrollVelocity002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo{ .startPos = 0.0f } });
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    pattern_->parent_ = mockScroll;
    pattern_->enableNestedScroll_ = true;

    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity003
 * @tc.desc: test HandleScrollVelocity pass to parent and parent doesn't consume
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScrollVelocity003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo{ .startPos = 0.0f } });
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));
    pattern_->parent_ = mockScroll;
    pattern_->enableNestedScroll_ = true;

    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(res);

    // change EdgeEffect to Spring and redo
    // should consume velocity
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    mockScroll.Reset();
    mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));

    pattern_->parent_ = mockScroll;
    res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SwiperPatternOnScrollStart001
 * @tc.desc: test OnScrollStartRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnScrollStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    auto mockScrollNode = FrameNode::CreateFrameNode("MockScroll", -1, mockScroll);
    frameNode_->MountToParent(mockScrollNode);

    EXPECT_CALL(*mockScroll, OnScrollStartRecursive).Times(1);
    EXPECT_CALL(*mockScroll, GetAxis).Times(1).WillOnce(Return(Axis::HORIZONTAL));
    pattern_->enableNestedScroll_ = true;
    pattern_->isDragging_ = false;
    pattern_->OnScrollStartRecursive(5.0f);
    EXPECT_TRUE(pattern_->childScrolling_);
}

/**
 * @tc.name: SwiperPatternOnScrollEnd001
 * @tc.desc: test OnScrollEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnScrollEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, OnScrollEndRecursive).Times(1);
    pattern_->enableNestedScroll_ = true;
    pattern_->parent_ = mockScroll;
    pattern_->OnScrollEndRecursive();
    EXPECT_FALSE(pattern_->childScrolling_);

    pattern_->NotifyParentScrollEnd();
}

/**
 * @tc.name: SwiperDragScene001
 * @tc.desc: test Swiper drag LTPO
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDragScene001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto renderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    EXPECT_TRUE(!!renderContext);
    EXPECT_CALL(*renderContext, CalcExpectedFrameRate(_, _)).Times(CALL_TIMES);
    auto info = GestureEvent();
    auto localLocation = Offset(DRAG_OFFSET_X, 0.0f);
    info.SetLocalLocation(localLocation);
    info.SetMainVelocity(DRAG_SPEED);
    pattern_->HandleDragStart(info);
    pattern_->HandleDragUpdate(info);
    pattern_->HandleDragUpdate(info);
    pattern_->HandleDragEnd(info.GetMainVelocity());
}

/**
 * @tc.name: HandleTouchBottomLoop001
 * @tc.desc: test Swiper indicator no touch bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = 1;
    pattern_->currentIndex_ = 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: HandleTouchBottomLoop002
 * @tc.desc: test Swiper indicator touch left bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: HandleTouchBottomLoop003
 * @tc.desc: test Swiper indicator touch right bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
}

/**
 * @tc.name: CalculateGestureState001
 * @tc.desc: test Swiper indicator gesture state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureState001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->CalculateGestureState(1.0f, 0.0f);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);

    pattern_->CalculateGestureState(-1.0f, 0.0f);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->CalculateGestureState(0.0f, -1.1f);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->CalculateGestureState(0.0f, -1.1f);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->CalculateGestureState(0.0f, -0.9f);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);
}

/**
 * @tc.name: GetStartAndEndIndex001
 * @tc.desc: get long point start and end index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetStartAndEndIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->itemCount_ = pattern_->TotalCount();
    paintMethod->turnPageRate_ = -0.9f;

    // expand to long point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto index = pattern_->TotalCount() - 1;
    auto expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    expectVal = std::pair<int32_t, int32_t>(0, 0);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);
}

/**
 * @tc.name: GetStartAndEndIndex002
 * @tc.desc: get long point start and end index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetStartAndEndIndex002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->itemCount_ = pattern_->TotalCount();
    paintMethod->turnPageRate_ = -0.8f;

    // shrink to black point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto expectVal = std::pair<int32_t, int32_t>(0, 0);
    auto index = pattern_->TotalCount() - 1;
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(1), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);
}

/**
 * @tc.name: AdjustPointCenterXForTouchBottom
 * @tc.desc: adjust long point centerX for touch bottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AdjustPointCenterXForTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    DotIndicatorPaintMethod::StarAndEndPointCenter pointCenter;
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }

    int32_t startCurrentIndex = 0;
    int32_t endCurrentIndex = totalCount - 1;

    // shrink to black point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex);
    EXPECT_EQ(pointCenter.endLongPointRightCenterX, endVectorBlackPointCenterX[0]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[0]);

    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex);
    EXPECT_EQ(pointCenter.endLongPointRightCenterX, endVectorBlackPointCenterX[startCurrentIndex]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[startCurrentIndex]);

    // expand to long point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex);
    EXPECT_EQ(pointCenter.startLongPointRightCenterX, endVectorBlackPointCenterX[endCurrentIndex]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[endCurrentIndex]);

    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex);
    EXPECT_EQ(pointCenter.startLongPointRightCenterX, endVectorBlackPointCenterX[0]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[0]);
}

/**
 * @tc.name: GetLongPointAnimationStateSecondCenter
 * @tc.desc: get long point animation state second center
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetLongPointAnimationStateSecondCenter001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    std::vector<std::pair<float, float>> pointCenterX;
    paintMethod->turnPageRate_ = -1.0f;

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 0);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 0);
}

/**
 * @tc.name: PlayLongPointAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PlayLongPointAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };

    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE, endVectorBlackPointCenterX);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);

    longPointCenterX.emplace_back(1.0f, 1.0f);
    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetChildMaxSize004
 * @tc.desc: GetChildMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmGetChildMaxSize004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(swiperGeometryNode, nullptr);

    Axis axis = Axis::VERTICAL;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();

    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, swiperGeometryNode, layoutProperty_);
    ASSERT_NE(layoutWrapper, nullptr);

    int32_t displaycount = 3;
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateDisplayCount(displaycount);

    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    layoutProperty_->UpdateShowIndicator(false);
    layoutProperty_->UpdateLoop(false);

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(swiperLayoutAlgorithm, nullptr);

    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    int32_t startIndex = 0;
    int32_t endIndex = 4;
    swiperLayoutAlgorithm->currentIndex_ = 1;
    CreateChildWrapperAppendToHostWrapper(startIndex, endIndex, layoutWrapper);
    /**
     * @tc.steps: step1.Set Axis to Axis:: VERTICAL
     * @tc.expected: Axis equals Axis: HORIZONTAL condition is false
     */
    bool isForward = true;
    swiperLayoutAlgorithm->ResetOffscreenItemPosition((AceType::RawPtr(layoutWrapper)), 1, isForward, axis);
    EXPECT_FALSE(axis == Axis::HORIZONTAL);
}

/**
 * @tc.name: ResetDisplayCount001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ResetDisplayCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetIndex(1);
    EXPECT_EQ(layoutProperty->GetIndex(), 1);

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetDisplayCount(10);
    model.ResetDisplayCount();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode = AceType::DynamicCast<FrameNode>(element);
    pattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_NE(pattern->GetDisplayCount(), 10);
}

/**
 * @tc.name: SetMinSize001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetMinSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. Calling the SetMinSize interface to set Dimension
     * @tc.expected: LayoutProperty ->GetMinSize(), equal to Dimension()
     */
    model.SetMinSize(Dimension(10));
    layoutProperty->GetMinSize();
    EXPECT_EQ(layoutProperty->GetMinSize(), Dimension(10));
}

/**
 * @tc.name: GetContentDrawFunction001
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetContentDrawFunction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });

    EXPECT_NE(indicatorNode, nullptr);
    frameNode_->AddChild(indicatorNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Calling the switchPaintMethod1. GetContentDrawFunction (&paintWrapper) interface
     * @tc.expected: paintFunc not empty
     */
    auto paintFunc = swiperPaintMethod1.GetContentDrawFunction(&paintWrapper);
    EXPECT_NE(paintFunc, nullptr);
}

/**
 * @tc.name: SwiperAccessibilityPropertyGetEndIndex002
 * @tc.desc: Test GetEndIndex of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilityPropertyGetEndIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);

    RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    frameNode_->AddChild(indicatorNode);
    /**
     * @tc.steps: step1. Set endIndex_ Call GetEndIndex when the value is 10
     * @tc.expected: AccessibilityProperty_ -> GetEndIndex() result is 10
     */
    pattern_->endIndex_ = 10;
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 10);
    /**
     * @tc.steps: step2.  Set endIndex_ Call GetEndIndex when the value is 0
     * @tc.expected: AccessibilityProperty_ -> GetEndIndex() result is 0
     */
    pattern_->endIndex_ = 0;
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 0);
}

/**
 * @tc.name: SwiperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of model.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilitySetSpecificSupportAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);
    layoutProperty_->UpdateLoop(false);
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());

    for (int index = 0; index <= 10; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        frameNode_->AddChild(indicatorNode);
    }
    /**
     * @tc.steps: step1.Call AccessibilityProperty_ -> SetSpecificSupportAction()
     * @tc.expected: accessibilityProperty_->IsScrollable() is true
     */
    pattern_->OnModifyDone();
    accessibilityProperty_->SetSpecificSupportAction();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: SwiperAccessibilitySetSpecificSupportAction008
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAccessibilitySetSpecificSupportAction008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);
    /**
     * @tc.steps: step1. Calling the SetOnGestureSwipe interface to pass in GestureSwipeEvent_
     * @tc.expected: Indicator GestureSwipeEvent_ Not empty
     */
    SwiperModelNG model;
    model.Create();
    GestureSwipeEvent gestureSwipeEvent_;
    model.SetOnGestureSwipe(std::move(gestureSwipeEvent_));
    EXPECT_TRUE(gestureSwipeEvent_ == nullptr);
}

/**
 * @tc.name: SwiperPatternSetNestedScroll002
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSetNestedScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(GetChildRect(frameNode_, 0).GetX(), 0);

    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    NestedScrollOptions nestedOpt;

    pattern->SetNestedScroll(std::move(nestedOpt));
    EXPECT_TRUE(pattern->enableNestedScroll_ == false);

    pattern->enableNestedScroll_ = true;
    pattern->SetNestedScroll(std::move(nestedOpt));
    EXPECT_TRUE(pattern->enableNestedScroll_ == false);
}

HWTEST_F(SwiperTestNg, SwiperPatternOnModifyDone00081, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub_)));

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->restoreNodeInfo_.emplace(std::make_pair(1, "testFlushUITasks"));
    pattern_->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern_->direction_, Axis::HORIZONTAL);

    pattern_->touchEvent_ = nullptr;
    pattern_->InitTouchEvent(gestureEventHub);
    TouchEventFunc callback = [](TouchEventInfo& info) {};

    pattern_->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    pattern_->InitTouchEvent(gestureEventHub);
    // EXPECT_TRUE(pattern_->touchEvent_);
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->panEvent_);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto leftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(leftArrow);
    auto rightArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    frameNode_->AddChild(rightArrow);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorNodeLeftArrow = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG,
        pattern_->GetLeftButtonId(), []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    indicatorNode->AddChild(indicatorNodeLeftArrow);
    frameNode_->AddChild(indicatorNode);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = false;
    config.skipLayout = false;

    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->isDragging_ = true;
    pattern_->windowSizeChangeReason_ = WindowSizeChangeReason::ROTATION;
    /**
     * @tc.steps: step2. Calling the OnDirtyLayoutWrapperSwap interface
     * @tc.expected: Pattern_ -> WindowSizeChangeReason_ Not equal to WindowSizeChangeReason::ROTATION
     */
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_NE(pattern_->windowSizeChangeReason_, WindowSizeChangeReason::ROTATION);
}

/**
 * @tc.name: SwiperAutoLinearAnimationNeedReset002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAutoLinearAnimationNeedReset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(frameNode_->children_.size(), 5);
    pattern_->itemPosition_.clear();
    /**
     * @tc.steps: step2. Calling the AutoLinearAnimationNeedReset interface
     * @tc.expected: ItemPosition_ Empty() condition is true
     */
    pattern_->AutoLinearAnimationNeedReset(0);
    EXPECT_TRUE(pattern_->itemPosition_.empty());
}

/**
 * @tc.name: SwiperPatternAlgorithmMeasure003
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAlgorithmMeasure003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::HORIZONTAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });

    RefPtr<FrameNode> indicatorNode;
    RefPtr<LayoutWrapperNode> layoutWrapper;
    RefPtr<LayoutAlgorithm> algorithm;
    InitLayoutWrapper(frameNode_, algorithm, indicatorNode, layoutWrapper);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper;
    CreateSwiperLayoutWrapper(frameNode_, swiperLayoutWrapper);

    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    /**
     * @tc.steps: step3. Create arrow node and layoutWrapper.
     */
    RefPtr<FrameNode> leftArrowNode;
    RefPtr<FrameNode> rightArrowNode;
    RefPtr<LayoutWrapperNode> leftArrowNodeWrapper;
    RefPtr<LayoutWrapperNode> rightArrowNodeWrapper;
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_LEFT_ARROW_ETS_TAG, leftArrowNode, leftArrowNodeWrapper);
    InitArrowLayoutWrapper(frameNode_, V2::SWIPER_RIGHT_ARROW_ETS_TAG, rightArrowNode, rightArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(leftArrowNodeWrapper);
    swiperLayoutWrapper->AppendChild(rightArrowNodeWrapper);

    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_FALSE(swiperPatternAlgorithm->mainSizeIsMeasured_);

    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    swiperLayoutWrapper->isConstraintNotChanged_ = true;
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_TRUE(swiperLayoutWrapper->isConstraintNotChanged_);

    /**
     * @tc.steps: step1. Set totalItemCount_ Equal to 0
     * @tc.expected: SwitchPatternAlgorithm ->totalitemCount_== 0 condition is true
     */
    swiperPatternAlgorithm->totalItemCount_ = 0;
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_TRUE(swiperPatternAlgorithm->totalItemCount_ == 0);

    /**
     * @tc.steps: step1. Set totalItem Count_ Greater than 0
     * @tc.expected: SwitchPatternAlgorithm ->totalitemCount_ Condition greater than 0 is true
     */
    swiperPatternAlgorithm->totalItemCount_ = 10;
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    swiperLayoutWrapper->isConstraintNotChanged_ = true;
    swiperPatternAlgorithm->Measure(AceType::RawPtr(swiperLayoutWrapper));
    EXPECT_TRUE(swiperPatternAlgorithm->totalItemCount_ > 0);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout004
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);

    layoutProperty_->UpdateContentConstraint();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, swiperGeometryNode, layoutProperty_);
    int32_t displaycount = 3;
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);

    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(displaycount);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    layoutProperty_->UpdateShowIndicator(false);
    layoutProperty_->UpdateLoop(false);

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    int32_t startIndex = 0;
    int32_t endIndex = 4;
    swiperLayoutAlgorithm->currentIndex_ = 1;

    CreateChildWrapperAppendToHostWrapper(startIndex, endIndex, layoutWrapper);
    swiperLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    swiperLayoutAlgorithm->prevMargin_ = 1.0f;
    /**
     * @tc.steps: step1. Set switchLayoutAlgorithm ->prevMargin_ Condition is 1.0
     * @tc.expected: SwitchLayoutAlgorithm ->prevMargin_ Not equal to 0.0f
     */
    swiperLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(swiperLayoutAlgorithm->prevMargin_ != 0.0f);
}
} // namespace OHOS::Ace::NG
