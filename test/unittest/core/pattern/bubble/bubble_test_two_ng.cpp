/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include <string>

#include "gtest/gtest.h"

#include "base/geometry/ng/rect_t.h"

#define private public
#define protected public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/rosen/testing_path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float POSITION_FIVE = 5.0f;
constexpr float RESULT_FIVE = 5.0f;
constexpr float RESULT_TEN = 10.0f;
constexpr float BORDER_RADIUS_TEN = 10.0f;
constexpr float MARGIN_START = 10.0f;
constexpr float MARGIN_END = 10.0f;
constexpr float MARGIN_BOTTOM = 10.0f;
constexpr float MARGIN_TOP = 10.0f;
constexpr float POSITION_TWENTY = 20.0f;
constexpr float SIZE_TWENTY = 20.0f;
constexpr float RESULT_TWENTY = 20.0f;
constexpr float RESULT_TWENTY_FIVE = 25.0f;
constexpr float SIZE_THIRTY = 30.0f;
constexpr float RESULT_THIRTY = 30.0f;
constexpr float SIZE_FORTY = 40.0f;
constexpr float RESULT_FORTY = 40.0f;
constexpr float POSITION_FIFTY = 50.0f;
constexpr float RESULT_FIFTY = 50.0f;
constexpr float RESULT_SIXTY = 60.0f;
constexpr float RESULT_SEVENTY = 70.0f;
constexpr float POSITION_EIGHTY = 80.0f;
constexpr float SIZE_EIGHTY = 80.0f;
constexpr float RESULT_EIGHTY = 80.0f;
constexpr float RESULT_NINETY = 90.0f;
constexpr float POSITION_ONE_HUNDRED = 100.0f;
constexpr float SIZE_ONE_HUNDRED = 100.0f;
constexpr float RESULT_ONE_HUNDRED = 100.0f;
constexpr float RESULT_ONE_HUNDRED_TWENTY = 120.0f;
constexpr float POSITION_ONE_HUNDRED_FIFTY = 150.0f;
constexpr float RESULT_ONE_HUNDRED_FIFTY = 150.0f;
constexpr float CHILDSIZE_ONE_HUNDRED_EIGHTY = 180.0f;
constexpr float SIZE_TWO_HUNDRED = 200.0f;
constexpr float OFFSET_TWO_HUNDRED = 200.0f;
constexpr float SIZE_FIVE_HUNDRED = 500.0f;
constexpr float MAX_AREA_SPACE = 900.0f;
} // namespace
struct TestProperty {
    // layout property
    std::optional<bool> enableArrow = std::nullopt;
    std::optional<bool> useCustom = std::nullopt;
    std::optional<Placement> placement = std::nullopt;
    std::optional<bool> showInSubWindow = std::nullopt;
    std::optional<OffsetF> displayWindowOffset = std::nullopt;

    // render property
    std::optional<bool> autoCancel = std::nullopt;
    std::optional<Color> maskColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
    std::optional<Dimension> arrowOffset = std::nullopt;
};

class MockBubbleTheme : public PopupTheme, public ButtonTheme {
    DECLARE_ACE_TYPE(MockBubbleTheme, PopupTheme, ButtonTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MockBubbleTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MockBubbleTheme> theme = AceType::MakeRefPtr<MockBubbleTheme>();
            return theme;
        }
    };

    ~MockBubbleTheme() override = default;

protected:
    MockBubbleTheme() = default;
};

class BubbleTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void InitSetting(BubbleLayoutAlgorithm& algorithm);
    void InitFuncMap(BubbleLayoutAlgorithm& algorithm);
    void InitCanPlacement(BubbleLayoutAlgorithm& algorithm);
    void InitGetRectSetting(BubbleLayoutAlgorithm& algorithm);
    void InitCheckPositionSetting(BubbleLayoutAlgorithm& algorithm);

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
};

void BubbleTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void BubbleTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void BubbleTestTwoNg::InitSetting(BubbleLayoutAlgorithm& algorithm)
{
    algorithm.marginStart_ = MARGIN_START;
    algorithm.marginEnd_ = MARGIN_END;
    algorithm.marginTop_ = MARGIN_TOP;
    algorithm.marginBottom_ = MARGIN_BOTTOM;
    algorithm.targetSpace_ = Dimension(0.0f);
    algorithm.userSetTargetSpace_ = Dimension(0.0f);
}

void BubbleTestTwoNg::InitGetRectSetting(BubbleLayoutAlgorithm& algorithm)
{
    algorithm.marginStart_ = MARGIN_START;
    algorithm.marginEnd_ = MARGIN_END;
    algorithm.marginTop_ = MARGIN_TOP;
    algorithm.marginBottom_ = MARGIN_BOTTOM;
    algorithm.targetSpace_ = Dimension(0.0f);
    algorithm.userSetTargetSpace_ = Dimension(0.0f);
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
}

void BubbleTestTwoNg::InitCheckPositionSetting(BubbleLayoutAlgorithm& algorithm)
{
    algorithm.marginStart_ = MARGIN_START;
    algorithm.marginEnd_ = MARGIN_END;
    algorithm.marginTop_ = MARGIN_TOP;
    algorithm.marginBottom_ = MARGIN_BOTTOM;
    algorithm.targetSpace_ = Dimension(0.0f);
    algorithm.userSetTargetSpace_ = Dimension(0.0f);
    algorithm.wrapperSize_ = SizeF(SIZE_FIVE_HUNDRED, SIZE_FIVE_HUNDRED);
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_FIVE_HUNDRED, SIZE_FIVE_HUNDRED);
    algorithm.targetOffset_ = OffsetF(OFFSET_TWO_HUNDRED, OFFSET_TWO_HUNDRED);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    algorithm.isHalfFoldHover_ = false;
}

void BubbleTestTwoNg::InitFuncMap(BubbleLayoutAlgorithm& algorithm)
{
    algorithm.placementFuncMap_[Placement::TOP] = &BubbleLayoutAlgorithm::GetPositionWithPlacementTop;
    algorithm.placementFuncMap_[Placement::TOP_LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementTopLeft;
    algorithm.placementFuncMap_[Placement::TOP_RIGHT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementTopRight;
    algorithm.placementFuncMap_[Placement::BOTTOM] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottom;
    algorithm.placementFuncMap_[Placement::BOTTOM_LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottomLeft;
    algorithm.placementFuncMap_[Placement::BOTTOM_RIGHT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottomRight;
    algorithm.placementFuncMap_[Placement::LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementLeft;
    algorithm.placementFuncMap_[Placement::LEFT_TOP] = &BubbleLayoutAlgorithm::GetPositionWithPlacementLeftTop;
    algorithm.placementFuncMap_[Placement::LEFT_BOTTOM] = &BubbleLayoutAlgorithm::GetPositionWithPlacementLeftBottom;
    algorithm.placementFuncMap_[Placement::RIGHT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementRight;
    algorithm.placementFuncMap_[Placement::RIGHT_TOP] = &BubbleLayoutAlgorithm::GetPositionWithPlacementRightTop;
    algorithm.placementFuncMap_[Placement::RIGHT_BOTTOM] = &BubbleLayoutAlgorithm::GetPositionWithPlacementRightBottom;
}

void BubbleTestTwoNg::InitCanPlacement(BubbleLayoutAlgorithm& algorithm)
{
    algorithm.canPlacement_.bottom = true;
    algorithm.canPlacement_.top = true;
    algorithm.canPlacement_.right = true;
    algorithm.canPlacement_.left = true;
}

RefPtr<FrameNode> BubbleTestTwoNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleTestTwoNg::CreateBubbleNode(const TestProperty& testProperty)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();

    // update layout property
    if (testProperty.enableArrow.has_value()) {
        layoutProperty->UpdateEnableArrow(testProperty.enableArrow.value());
    }
    if (testProperty.useCustom.has_value()) {
        layoutProperty->UpdateUseCustom(testProperty.useCustom.value());
    }
    if (testProperty.placement.has_value()) {
        layoutProperty->UpdatePlacement(testProperty.placement.value());
    }
    if (testProperty.showInSubWindow.has_value()) {
        layoutProperty->UpdateShowInSubWindow(testProperty.showInSubWindow.value());
    }
    if (testProperty.displayWindowOffset.has_value()) {
        layoutProperty->UpdateDisplayWindowOffset(testProperty.displayWindowOffset.value());
    }

    // update render property
    if (testProperty.autoCancel.has_value()) {
        renderProperty->UpdateAutoCancel(testProperty.autoCancel.value());
    }
    if (testProperty.maskColor.has_value()) {
        renderProperty->UpdateMaskColor(testProperty.maskColor.value());
    }
    if (testProperty.backgroundColor.has_value()) {
        renderProperty->UpdateBackgroundColor(testProperty.backgroundColor.value());
    }
    if (testProperty.placement.has_value()) {
        renderProperty->UpdatePlacement(testProperty.placement.value());
    }
    if (testProperty.enableArrow.has_value()) {
        renderProperty->UpdateEnableArrow(testProperty.enableArrow.value());
    }
    if (testProperty.useCustom.has_value()) {
        renderProperty->UpdateUseCustom(testProperty.useCustom.value());
    }
    if (testProperty.arrowOffset.has_value()) {
        renderProperty->UpdateArrowOffset(testProperty.arrowOffset.value());
    }
    return popupNode;
}

/**
 * @tc.name: InitWrapperRect001
 * @tc.desc: Test InitWrapperRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, InitWrapperRect001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    WeakPtr<AceType> bubble = Referenced::WeakClaim(Referenced::RawPtr(frameNode));
    ElementRegister::GetInstance()->itemMap_.insert({ 1, bubble });
    BubbleLayoutAlgorithm bubbleLayoutAlgorithm;
    bubbleLayoutAlgorithm.targetTag_ = "test1";
    bubbleLayoutAlgorithm.targetNodeId_ = 1;
    RefPtr<BubbleLayoutProperty> layoutProp = AceType::MakeRefPtr<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    bubbleLayoutAlgorithm.isHalfFoldHover_ = true;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    RefPtr<MockContainer> containerOne = AceType::MakeRefPtr<MockContainer>();
    RefPtr<MockContainer> containerTwo = AceType::MakeRefPtr<MockContainer>();
    MockContainer::Current()->GetMockDisplayInfo()->SetFoldStatus(FoldStatus::HALF_FOLD);
    layoutProp->UpdateEnableHoverMode(true);
    AceEngine::Get().AddContainer(0, containerOne);
    AceEngine::Get().AddContainer(1, containerTwo);
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    EXPECT_FALSE(bubbleLayoutAlgorithm.isHalfFoldHover_);
    bubbleLayoutAlgorithm.foldCreaseBottom_ = -1;
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    EXPECT_EQ(bubbleLayoutAlgorithm.wrapperRect_.y_, -1);
    bubbleLayoutAlgorithm.foldCreaseTop_ = 1;
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    EXPECT_EQ(bubbleLayoutAlgorithm.wrapperRect_.y_, 0);
}

/**
 * @tc.name: UpdateBubbleMaxSize001
 * @tc.desc: Test UpdateBubbleMaxSize.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, UpdateBubbleMaxSize001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto childNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    frameNode->AddChild(childNode);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(bubbleLayoutProperty, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    bool showInSubwindow = false;
    layoutAlgorithm->useCustom_ = false;
    layoutAlgorithm->UpdateBubbleMaxSize(AceType::RawPtr(layoutWrapper), showInSubwindow);
    layoutAlgorithm->useCustom_ = true;
    layoutAlgorithm->UpdateBubbleMaxSize(AceType::RawPtr(layoutWrapper), showInSubwindow);
    auto childProp = childNode->GetLayoutProperty();
    ASSERT_NE(childProp, nullptr);
    auto layoutConstraint = childProp->GetLayoutConstraint();
    CHECK_EQUAL_VOID(layoutConstraint.has_value(), false);
    EXPECT_EQ(layoutConstraint->maxSize.Width(), 0);
}

/**
 * @tc.name: CreateBubbleNode001
 * @tc.desc: Test CreateBubbleNode
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, CreateBubbleNode001, TestSize.Level1)
{
    auto param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);
    param->enableHoverMode_ = true;
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManagerOne, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    BubbleView::CreateBubbleNode("test1", 1, param);
    EXPECT_TRUE(param->HasEnableHoverMode());
}

/**
 * @tc.name: InitTargetSizeAndPosition
 * @tc.desc: Test InitTargetSizeAndPosition.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, InitTargetSizeAndPosition, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(bubbleLayoutProperty, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    bool showInSubwindow = false;
    layoutAlgorithm->InitTargetSizeAndPosition(showInSubwindow, AceType::RawPtr(layoutWrapper));
    showInSubwindow = true;
    layoutAlgorithm->InitTargetSizeAndPosition(showInSubwindow, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutAlgorithm->targetOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: AdjustAvoidPosition001
 * @tc.desc: Test AdjustAvoidPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AdjustAvoidPosition001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    OffsetF position(POSITION_TWENTY, POSITION_TWENTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    float width = SIZE_THIRTY;
    float height = SIZE_THIRTY;

    OffsetF result = algorithm.AdjustAvoidPosition(position, width, height, arrowPosition);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_TWENTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_TWENTY);
    EXPECT_FLOAT_EQ(arrowPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(arrowPosition.GetY(), 0.0f);

    position.SetX(POSITION_EIGHTY);
    position.SetY(POSITION_TWENTY);
    arrowPosition.SetX(0.0f);
    arrowPosition.SetY(0.0f);

    result = algorithm.AdjustAvoidPosition(position, width, height, arrowPosition);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_SIXTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_TWENTY);
    EXPECT_FLOAT_EQ(arrowPosition.GetX(), -RESULT_TWENTY);
    EXPECT_FLOAT_EQ(arrowPosition.GetY(), 0.0f);
}

/**
 * @tc.name: AdjustAvoidPosition002
 * @tc.desc: Test AdjustAvoidPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AdjustAvoidPosition002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    OffsetF position(POSITION_TWENTY, POSITION_EIGHTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    float width = SIZE_THIRTY;
    float height = SIZE_THIRTY;

    OffsetF result = algorithm.AdjustAvoidPosition(position, width, height, arrowPosition);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_TWENTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_SIXTY);
    EXPECT_FLOAT_EQ(arrowPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(arrowPosition.GetY(), -RESULT_TWENTY);

    position.SetX(POSITION_FIVE);
    position.SetY(POSITION_TWENTY);
    arrowPosition.SetX(0.0f);
    arrowPosition.SetY(0.0f);

    result = algorithm.AdjustAvoidPosition(position, width, height, arrowPosition);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_TWENTY);
    EXPECT_FLOAT_EQ(arrowPosition.GetX(), RESULT_FIVE);
    EXPECT_FLOAT_EQ(arrowPosition.GetY(), 0.0f);
}

/**
 * @tc.name: AdjustAvoidPosition003
 * @tc.desc: Test AdjustAvoidPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AdjustAvoidPosition003, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    OffsetF position(POSITION_TWENTY, POSITION_FIVE);
    OffsetF arrowPosition(0.0f, 0.0f);
    float width = SIZE_THIRTY;
    float height = SIZE_THIRTY;

    OffsetF result = algorithm.AdjustAvoidPosition(position, width, height, arrowPosition);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_TWENTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_TEN);
    EXPECT_FLOAT_EQ(arrowPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(arrowPosition.GetY(), RESULT_FIVE);

    position.SetX(POSITION_EIGHTY + POSITION_FIVE);
    position.SetY(POSITION_EIGHTY + POSITION_FIVE);
    arrowPosition.SetX(0.0f);
    arrowPosition.SetY(0.0f);

    result = algorithm.AdjustAvoidPosition(position, width, height, arrowPosition);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_SIXTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_SIXTY);
    EXPECT_FLOAT_EQ(arrowPosition.GetX(), -RESULT_TWENTY_FIVE);
    EXPECT_FLOAT_EQ(arrowPosition.GetY(), -RESULT_TWENTY_FIVE);
}

/**
 * @tc.name: CoverParent001
 * @tc.desc: Test CoverParent
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, CoverParent001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    algorithm.arrowHeight_ = 0.0f;

    algorithm.isHalfFoldHover_ = false;
    algorithm.avoidKeyboard_ = true;
    SizeF childSize(SIZE_TWENTY, SIZE_TWENTY);

    OffsetF position = algorithm.CoverParent(childSize, Placement::BOTTOM);
    EXPECT_FLOAT_EQ(position.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(position.GetY(), RESULT_TEN);

    algorithm.wrapperSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    algorithm.avoidKeyboard_ = false;
    position = algorithm.CoverParent(childSize, Placement::BOTTOM);
    EXPECT_FLOAT_EQ(position.GetX(), RESULT_SIXTY);
    EXPECT_FLOAT_EQ(position.GetY(), RESULT_TEN);

    algorithm.targetOffset_ = OffsetF(-POSITION_FIFTY, -POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_TWENTY, SIZE_TWENTY);
    position = algorithm.CoverParent(childSize, Placement::BOTTOM);
    EXPECT_FLOAT_EQ(position.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(position.GetY(), RESULT_TEN);

    algorithm.isHalfFoldHover_ = true;
    algorithm.avoidKeyboard_ = false;
    position = algorithm.CoverParent(childSize, Placement::BOTTOM);
    EXPECT_FLOAT_EQ(position.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(position.GetY(), RESULT_TEN);

    algorithm.avoidKeyboard_ = true;
    position = algorithm.CoverParent(childSize, Placement::BOTTOM);
    EXPECT_FLOAT_EQ(position.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(position.GetY(), RESULT_TEN);
}

/**
 * @tc.name: AvoidToTopOrBottomByWidth001
 * @tc.desc: Test AvoidToTopOrBottomByWidth
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTopOrBottomByWidth001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    algorithm.arrowHeight_ = 0.0f;
    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    SizeF resultSize(0.0f, 0.0f);
    algorithm.isHalfFoldHover_ = false;

    OffsetF position = algorithm.AvoidToTopOrBottomByWidth(childSize, arrowPosition, resultSize);
    EXPECT_EQ(algorithm.placement_, Placement::BOTTOM);
    EXPECT_FLOAT_EQ(resultSize.Width(), SIZE_THIRTY);
    EXPECT_FLOAT_EQ(resultSize.Height(), SIZE_THIRTY);
    EXPECT_FLOAT_EQ(position.GetX(), RESULT_FIFTY + RESULT_FIVE);
    EXPECT_FLOAT_EQ(position.GetY(), RESULT_NINETY);

    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    position = algorithm.AvoidToTopOrBottomByWidth(childSize, arrowPosition, resultSize);
    EXPECT_EQ(algorithm.placement_, Placement::BOTTOM);
    EXPECT_FLOAT_EQ(resultSize.Width(), SIZE_THIRTY);
    EXPECT_FLOAT_EQ(resultSize.Height(), SIZE_THIRTY);

    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_ONE_HUNDRED_FIFTY);
    algorithm.isHalfFoldHover_ = false;
    position = algorithm.AvoidToTopOrBottomByWidth(childSize, arrowPosition, resultSize);
    EXPECT_EQ(algorithm.placement_, Placement::TOP);
    EXPECT_FLOAT_EQ(resultSize.Width(), SIZE_THIRTY);
    EXPECT_FLOAT_EQ(resultSize.Height(), SIZE_THIRTY);

    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    position = algorithm.AvoidToTopOrBottomByWidth(childSize, arrowPosition, resultSize);
    EXPECT_EQ(algorithm.placement_, Placement::TOP);
    EXPECT_FLOAT_EQ(resultSize.Width(), SIZE_THIRTY);
    EXPECT_FLOAT_EQ(resultSize.Height(), SIZE_THIRTY);
}

/**
 * @tc.name: AvoidToTargetBottom001
 * @tc.desc: Test AvoidToTargetBottom
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetBottom001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(CHILDSIZE_ONE_HUNDRED_EIGHTY, SIZE_THIRTY);

    algorithm.placement_ = Placement::BOTTOM_LEFT;
    bool result = algorithm.AvoidToTargetBottom(childSize, arrowPosition, resultPosition, resultSize, false);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);

    algorithm.placement_ = Placement::BOTTOM_RIGHT;
    result = algorithm.AvoidToTargetBottom(childSize, arrowPosition, resultPosition, resultSize, false);
    EXPECT_FALSE(result);
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);

    algorithm.placement_ = Placement::BOTTOM;
    algorithm.targetOffset_ = OffsetF(0.0f, POSITION_FIFTY);
    SizeF childMid(SIZE_EIGHTY, SIZE_THIRTY);
    result = algorithm.AvoidToTargetBottom(childMid, arrowPosition, resultPosition, resultSize, false);
    EXPECT_FALSE(result);
    EXPECT_FLOAT_EQ(resultSize.Width() - RESULT_ONE_HUNDRED, childMid.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childMid.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);
}

/**
 * @tc.name: AvoidToTargetBottom002
 * @tc.desc: Test AvoidToTargetBottom
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetBottom002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);

    algorithm.placement_ = Placement::BOTTOM_LEFT;
    bool result = algorithm.AvoidToTargetBottom(childSize, arrowPosition, resultPosition, resultSize, true);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);

    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.placement_ = Placement::BOTTOM_RIGHT;
    result = algorithm.AvoidToTargetBottom(childSize, arrowPosition, resultPosition, resultSize, true);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);

    algorithm.isHalfFoldHover_ = false;
    algorithm.placement_ = Placement::BOTTOM;
    algorithm.targetOffset_ = OffsetF(0.0f, POSITION_FIFTY);
    result = algorithm.AvoidToTargetBottom(childSize, arrowPosition, resultPosition, resultSize, true);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_TEN);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);
}

/**
 * @tc.name: AvoidToTargetTop001
 * @tc.desc: Test AvoidToTargetTop
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetTop001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = false;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_ONE_HUNDRED);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    SizeF childSize(CHILDSIZE_ONE_HUNDRED_EIGHTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF resultSize(0.0f, 0.0f);
    algorithm.placement_ = Placement::TOP_LEFT;

    EXPECT_FALSE(algorithm.AvoidToTargetTop(childSize, arrowPosition, resultPosition, resultSize, false));
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width() - CHILDSIZE_ONE_HUNDRED_EIGHTY);
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height() - SIZE_THIRTY);
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_SEVENTY);

    childSize.SetWidth(SIZE_THIRTY);
    childSize.SetHeight(SIZE_THIRTY);
    EXPECT_TRUE(algorithm.AvoidToTargetTop(childSize, arrowPosition, resultPosition, resultSize, true));
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_SEVENTY);

    algorithm.placement_ = Placement::TOP_RIGHT;
    childSize.SetWidth(CHILDSIZE_ONE_HUNDRED_EIGHTY);
    childSize.SetHeight(SIZE_THIRTY);
    EXPECT_FALSE(algorithm.AvoidToTargetTop(childSize, arrowPosition, resultPosition, resultSize, false));
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width() - RESULT_ONE_HUNDRED_FIFTY);
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_SEVENTY);

    childSize.SetWidth(SIZE_THIRTY);
    childSize.SetHeight(SIZE_THIRTY);
    EXPECT_TRUE(algorithm.AvoidToTargetTop(childSize, arrowPosition, resultPosition, resultSize, true));
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_SIXTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_SEVENTY);
}

/**
 * @tc.name: AvoidToTargetTop002
 * @tc.desc: Test AvoidToTargetTop
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetTop002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetOffset_ = OffsetF(POSITION_ONE_HUNDRED, POSITION_ONE_HUNDRED_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    SizeF childMid(SIZE_EIGHTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF resultSize(0.0f, 0.0f);
    algorithm.placement_ = Placement::TOP;

    EXPECT_TRUE(algorithm.AvoidToTargetTop(childMid, arrowPosition, resultPosition, resultSize, true));
    EXPECT_FLOAT_EQ(resultSize.Width(), childMid.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childMid.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_EIGHTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_ONE_HUNDRED_TWENTY);
}

/**
 * @tc.name: AvoidToTargetTopMid001
 * @tc.desc: Test AvoidToTargetTopMid
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetTopMid001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = false;
    algorithm.targetOffset_ = OffsetF(0.0f, POSITION_ONE_HUNDRED);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childSize(SIZE_EIGHTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF size(SIZE_THIRTY, SIZE_THIRTY);

    EXPECT_FALSE(algorithm.AvoidToTargetTopMid(childSize, arrowPosition, resultPosition, size, false));
    EXPECT_FLOAT_EQ(size.Width(), RESULT_THIRTY);
    EXPECT_FLOAT_EQ(size.Height(), RESULT_THIRTY);
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);
}

/**
 * @tc.name: AvoidToTargetTopMid002
 * @tc.desc: Test AvoidToTargetTopMid
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetTopMid002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = false;
    algorithm.bCaretMode_ = false;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_ONE_HUNDRED);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF size;

    EXPECT_TRUE(algorithm.AvoidToTargetTopMid(childSize, arrowPosition, resultPosition, size, true));
    EXPECT_FLOAT_EQ(size.Width(), RESULT_THIRTY);
    EXPECT_FLOAT_EQ(size.Height(), RESULT_THIRTY);
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_FIFTY + RESULT_FIVE);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_SEVENTY);
}

/**
 * @tc.name: AvoidToTargetTopMid003
 * @tc.desc: Test AvoidToTargetTopMid
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetTopMid003, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.bCaretMode_ = true;
    algorithm.targetOffset_ = OffsetF(POSITION_ONE_HUNDRED, POSITION_ONE_HUNDRED_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childMid(SIZE_EIGHTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF size;

    EXPECT_TRUE(algorithm.AvoidToTargetTopMid(childMid, arrowPosition, resultPosition, size, true));
    EXPECT_FLOAT_EQ(size.Width(), RESULT_EIGHTY);
    EXPECT_FLOAT_EQ(size.Height(), SIZE_THIRTY);
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_EIGHTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_ONE_HUNDRED_TWENTY);
}

/**
 * @tc.name: AvoidToTargetRight001
 * @tc.desc: Test AvoidToTargetRight
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetRight001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    SizeF childSize(CHILDSIZE_ONE_HUNDRED_EIGHTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF size;

    algorithm.placement_ = Placement::RIGHT_TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, false));

    algorithm.placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_FALSE(algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, false));

    algorithm.placement_ = Placement::RIGHT;
    EXPECT_FALSE(algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, false));
}

/**
 * @tc.name: AvoidToTargetRight002
 * @tc.desc: Test AvoidToTargetRight
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetRight002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);
    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF size;

    algorithm.isHalfFoldHover_ = false;
    algorithm.placement_ = Placement::RIGHT_TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, true));
    EXPECT_FLOAT_EQ(size.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(size.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);

    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, true));
    EXPECT_FLOAT_EQ(size.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(size.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);

    algorithm.isHalfFoldHover_ = false;
    algorithm.placement_ = Placement::RIGHT;
    algorithm.targetOffset_ = OffsetF(0.0f, POSITION_FIFTY);
    EXPECT_TRUE(algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, true));
    EXPECT_FLOAT_EQ(size.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(size.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_TEN);
}

/**
 * @tc.name: AvoidToTargetRight003
 * @tc.desc: Test AvoidToTargetRight
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetRight003, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.isHalfFoldHover_ = false;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF size;

    algorithm.placement_ = Placement::RIGHT_TOP;
    bool ret = algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, false);
    EXPECT_TRUE(ret);
    EXPECT_FLOAT_EQ(size.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(size.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);

    algorithm.placement_ = Placement::RIGHT_BOTTOM;
    ret = algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, false);
    EXPECT_TRUE(ret);
    EXPECT_FLOAT_EQ(size.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(size.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_TEN);

    algorithm.placement_ = Placement::RIGHT;
    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    ret = algorithm.AvoidToTargetRight(childSize, arrowPosition, resultPosition, size, false);
    EXPECT_TRUE(ret);
    EXPECT_FLOAT_EQ(size.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(size.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), 0.0f);
}

/**
 * @tc.name: AvoidToTargetLeft001
 * @tc.desc: Test AvoidToTargetLeft
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetLeft001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = false;
    algorithm.targetOffset_ = OffsetF(POSITION_ONE_HUNDRED, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childSize(CHILDSIZE_ONE_HUNDRED_EIGHTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF resultSize(0.0f, 0.0f);

    algorithm.placement_ = Placement::LEFT_TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetLeft(childSize, arrowPosition, resultPosition, resultSize, false));
}

/**
 * @tc.name: AvoidToTargetLeft002
 * @tc.desc: Test AvoidToTargetLeft
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetLeft002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(BORDER_RADIUS_TEN);
    algorithm.isHalfFoldHover_ = false;
    algorithm.targetOffset_ = OffsetF(POSITION_ONE_HUNDRED, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF resultSize(0.0f, 0.0f);

    algorithm.placement_ = Placement::LEFT_TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetLeft(childSize, arrowPosition, resultPosition, resultSize, false));
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_SEVENTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_FIFTY);
}

/**
 * @tc.name: AvoidToTargetLeft003
 * @tc.desc: Test AvoidToTargetLeft
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetLeft003, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = false;
    algorithm.targetOffset_ = OffsetF(POSITION_ONE_HUNDRED, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF resultSize(0.0f, 0.0f);

    algorithm.placement_ = Placement::LEFT_BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetLeft(childSize, arrowPosition, resultPosition, resultSize, true));
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_SEVENTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_SIXTY);
}

/**
 * @tc.name: AvoidToTargetLeft004
 * @tc.desc: Test AvoidToTargetLeft
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetLeft004, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.scaledBubbleSpacing_ = 0.0f;
    algorithm.borderRadius_ = Dimension(0.0f);
    algorithm.isHalfFoldHover_ = true;
    algorithm.wrapperRect_.SetRect(0.0f, 0.0f, SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetOffset_ = OffsetF(POSITION_ONE_HUNDRED, POSITION_ONE_HUNDRED_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_FORTY, SIZE_FORTY);

    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF resultSize(0.0f, 0.0f);

    algorithm.placement_ = Placement::LEFT;
    EXPECT_TRUE(algorithm.AvoidToTargetLeft(childSize, arrowPosition, resultPosition, resultSize, true));
    EXPECT_FLOAT_EQ(resultSize.Width(), childSize.Width());
    EXPECT_FLOAT_EQ(resultSize.Height(), childSize.Height());
    EXPECT_FLOAT_EQ(resultPosition.GetX(), RESULT_SEVENTY);
    EXPECT_FLOAT_EQ(resultPosition.GetY(), RESULT_ONE_HUNDRED_FIFTY + RESULT_FIVE);
}

/**
 * @tc.name: CheckPositionBottom001
 * @tc.desc: Test CheckPositionBottom
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, CheckPositionBottom001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitCheckPositionSetting(algorithm);

    algorithm.maxAreaSpace_ = 0.0f;
    size_t i = 0;
    size_t step = 1;
    OffsetF arrowPosition = OffsetF(0.0f, 0.0f);
    OffsetF position = OffsetF(0.0f, 0.0f);
    SizeF childSize = SizeF(SIZE_THIRTY, SIZE_THIRTY);
    algorithm.canPlacement_.bottom = false;
    EXPECT_TRUE(algorithm.CheckPositionBottom(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, MAX_AREA_SPACE);
    EXPECT_TRUE(algorithm.canPlacement_.bottom);

    algorithm.maxAreaSpace_ = 0.0f;
    i = 0;
    step = 1;
    arrowPosition = OffsetF(0.0f, 0.0f);
    position = OffsetF(0.0f, 0.0f);
    childSize = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetOffset_ = OffsetF(0.0f, 0.0f);
    algorithm.targetSize_ = SizeF(SIZE_FIVE_HUNDRED, SIZE_FIVE_HUNDRED);
    algorithm.canPlacement_.bottom = false;
    EXPECT_FALSE(algorithm.CheckPositionBottom(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, 0.0f);
    EXPECT_FALSE(algorithm.canPlacement_.bottom);
}

/**
 * @tc.name: CheckPositionTop001
 * @tc.desc: Test CheckPositionTop
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, CheckPositionTop001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitCheckPositionSetting(algorithm);

    algorithm.maxAreaSpace_ = 0.0f;
    size_t i = 0;
    size_t step = 1;
    OffsetF arrowPosition = OffsetF(0.0f, 0.0f);
    OffsetF position = OffsetF(0.0f, 0.0f);
    SizeF childSize = SizeF(SIZE_THIRTY, SIZE_THIRTY);
    algorithm.canPlacement_.top = false;
    EXPECT_TRUE(algorithm.CheckPositionTop(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, MAX_AREA_SPACE);
    EXPECT_TRUE(algorithm.canPlacement_.top);

    algorithm.maxAreaSpace_ = 0.0f;
    i = 0;
    step = 1;
    arrowPosition = OffsetF(0.0f, 0.0f);
    position = OffsetF(0.0f, 0.0f);
    childSize = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetOffset_ = OffsetF(0.0f, 0.0f);
    algorithm.targetSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.canPlacement_.top = false;
    EXPECT_FALSE(algorithm.CheckPositionTop(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, 0.0f);
    EXPECT_FALSE(algorithm.canPlacement_.top);
}

/**
 * @tc.name: CheckPositionRight001
 * @tc.desc: Test CheckPositionRight
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, CheckPositionRight001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitCheckPositionSetting(algorithm);

    algorithm.maxAreaSpace_ = 0.0f;
    size_t i = 0;
    size_t step = 1;
    OffsetF arrowPosition = OffsetF(0.0f, 0.0f);
    OffsetF position = OffsetF(0.0f, 0.0f);
    SizeF childSize = SizeF(SIZE_THIRTY, SIZE_THIRTY);
    algorithm.canPlacement_.right = false;
    EXPECT_TRUE(algorithm.CheckPositionRight(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, MAX_AREA_SPACE);
    EXPECT_TRUE(algorithm.canPlacement_.right);

    algorithm.maxAreaSpace_ = 0.0f;
    i = 0;
    step = 1;
    arrowPosition = OffsetF(0.0f, 0.0f);
    position = OffsetF(0.0f, 0.0f);
    childSize = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetSize_ = SizeF(SIZE_FIVE_HUNDRED, SIZE_FIVE_HUNDRED);
    algorithm.targetOffset_ = OffsetF(0.0f, 0.0f);
    algorithm.canPlacement_.right = false;
    EXPECT_FALSE(algorithm.CheckPositionRight(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, 0.0f);
    EXPECT_FALSE(algorithm.canPlacement_.right);
}

/**
 * @tc.name: CheckPositionLeft001
 * @tc.desc: Test CheckPositionLeft
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, CheckPositionLeft001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitCheckPositionSetting(algorithm);

    algorithm.maxAreaSpace_ = 0.0f;
    size_t i = 0;
    size_t step = 1;
    OffsetF arrowPosition = OffsetF(0.0f, 0.0f);
    OffsetF position = OffsetF(0.0f, 0.0f);
    SizeF childSize = SizeF(SIZE_THIRTY, SIZE_THIRTY);
    algorithm.canPlacement_.left = false;
    EXPECT_TRUE(algorithm.CheckPositionLeft(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, MAX_AREA_SPACE);
    EXPECT_TRUE(algorithm.canPlacement_.left);

    algorithm.maxAreaSpace_ = 0.0f;
    i = 0;
    step = 1;
    arrowPosition = OffsetF(0.0f, 0.0f);
    position = OffsetF(0.0f, 0.0f);
    childSize = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    algorithm.targetOffset_ = OffsetF(0.0f, 0.0f);
    algorithm.canPlacement_.left = false;
    EXPECT_FALSE(algorithm.CheckPositionLeft(position, childSize, step, i, arrowPosition));
    EXPECT_FLOAT_EQ(algorithm.maxAreaSpace_, 0.0f);
    EXPECT_FALSE(algorithm.canPlacement_.left);
}

/**
 * @tc.name: GetBottomRect001
 * @tc.desc: Test GetBottomRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, GetBottomRect001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitGetRectSetting(algorithm);

    algorithm.isHalfFoldHover_ = false;
    Rect rect = algorithm.GetBottomRect();
    EXPECT_FLOAT_EQ(rect.Width(), CHILDSIZE_ONE_HUNDRED_EIGHTY);
    EXPECT_FLOAT_EQ(rect.Height(), RESULT_FORTY);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_TEN);
    EXPECT_FLOAT_EQ(rect.Top(), RESULT_ONE_HUNDRED_FIFTY);

    algorithm.isHalfFoldHover_ = true;
    rect = algorithm.GetBottomRect();
    EXPECT_FLOAT_EQ(rect.Width(), CHILDSIZE_ONE_HUNDRED_EIGHTY);
    EXPECT_FLOAT_EQ(rect.Height(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_TEN);
    EXPECT_FLOAT_EQ(rect.Top(), RESULT_ONE_HUNDRED_FIFTY);
}

/**
 * @tc.name: GetTopRect001
 * @tc.desc: Test GetTopRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, GetTopRect001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitGetRectSetting(algorithm);

    algorithm.isHalfFoldHover_ = false;
    Rect rect = algorithm.GetTopRect();
    EXPECT_FLOAT_EQ(rect.Width(), CHILDSIZE_ONE_HUNDRED_EIGHTY);
    EXPECT_FLOAT_EQ(rect.Height(), RESULT_FORTY);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_TEN);
    EXPECT_FLOAT_EQ(rect.Top(), RESULT_TEN);

    algorithm.isHalfFoldHover_ = true;
    rect = algorithm.GetTopRect();
    EXPECT_FLOAT_EQ(rect.Width(), CHILDSIZE_ONE_HUNDRED_EIGHTY);
    EXPECT_FLOAT_EQ(rect.Height(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_TEN);
    EXPECT_FLOAT_EQ(rect.Top(), 0.0f);
}

/**
 * @tc.name: GetRightRect001
 * @tc.desc: Test GetRightRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, GetRightRect001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitGetRectSetting(algorithm);

    algorithm.isHalfFoldHover_ = false;
    Rect rect = algorithm.GetRightRect();
    EXPECT_FLOAT_EQ(rect.Width(), RESULT_FORTY);
    EXPECT_FLOAT_EQ(rect.Height(), CHILDSIZE_ONE_HUNDRED_EIGHTY);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_ONE_HUNDRED_FIFTY);
    EXPECT_FLOAT_EQ(rect.Top(), RESULT_TEN);

    algorithm.isHalfFoldHover_ = true;
    rect = algorithm.GetRightRect();
    EXPECT_FLOAT_EQ(rect.Width(), RESULT_FORTY);
    EXPECT_FLOAT_EQ(rect.Height(), SIZE_TWO_HUNDRED);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_ONE_HUNDRED_FIFTY);
    EXPECT_FLOAT_EQ(rect.Top(), 0.0f);
}

/**
 * @tc.name: GetLeftRect001
 * @tc.desc: Test GetLeftRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, GetLeftRect001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    BubbleTestTwoNg::InitGetRectSetting(algorithm);

    algorithm.isHalfFoldHover_ = false;
    Rect rect = algorithm.GetLeftRect();
    EXPECT_FLOAT_EQ(rect.Width(), RESULT_FORTY);
    EXPECT_FLOAT_EQ(rect.Height(), CHILDSIZE_ONE_HUNDRED_EIGHTY);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_TEN);
    EXPECT_FLOAT_EQ(rect.Top(), RESULT_TEN);

    algorithm.isHalfFoldHover_ = true;
    rect = algorithm.GetLeftRect();
    EXPECT_FLOAT_EQ(rect.Width(), RESULT_FORTY);
    EXPECT_FLOAT_EQ(rect.Height(), SIZE_TWO_HUNDRED);
    EXPECT_FLOAT_EQ(rect.Left(), RESULT_TEN);
    EXPECT_FLOAT_EQ(rect.Top(), 0.0f);
}

/**
 * @tc.name: AvoidToTargetPlacement001
 * @tc.desc: Test AvoidToTargetPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetPlacement001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);

    algorithm.canPlacement_.bottom = false;
    algorithm.canPlacement_.top = false;
    algorithm.canPlacement_.right = false;
    algorithm.canPlacement_.left = false;
    bool canCompress = false;
    algorithm.placement_ = Placement::BOTTOM_LEFT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM_RIGHT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_LEFT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_RIGHT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_BOTTOM;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::NONE;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
}

/**
 * @tc.name: AvoidToTargetPlacement002
 * @tc.desc: Test AvoidToTargetPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetPlacement002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);

    algorithm.canPlacement_.bottom = false;
    algorithm.canPlacement_.top = false;
    algorithm.canPlacement_.right = false;
    algorithm.canPlacement_.left = false;
    bool canCompress = true;
    algorithm.placement_ = Placement::BOTTOM_LEFT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM_RIGHT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_LEFT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_RIGHT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_TOP;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_BOTTOM;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::NONE;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
}

/**
 * @tc.name: AvoidToTargetPlacement003
 * @tc.desc: Test AvoidToTargetPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetPlacement003, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(SIZE_THIRTY, SIZE_THIRTY);

    algorithm.canPlacement_.bottom = true;
    algorithm.canPlacement_.top = true;
    algorithm.canPlacement_.right = true;
    algorithm.canPlacement_.left = true;
    bool canCompress = true;
    BubbleTestTwoNg::InitFuncMap(algorithm);
    algorithm.placement_ = Placement::BOTTOM_LEFT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM_RIGHT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_LEFT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_RIGHT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::NONE;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
}

/**
 * @tc.name: AvoidToTargetPlacement004
 * @tc.desc: Test AvoidToTargetPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidToTargetPlacement004, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, POSITION_FIFTY);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(SIZE_TWENTY, SIZE_TWENTY);

    algorithm.isHalfFoldHover_ = false;
    algorithm.canPlacement_.bottom = true;
    algorithm.canPlacement_.top = true;
    algorithm.canPlacement_.right = true;
    algorithm.canPlacement_.left = true;
    bool canCompress = false;
    BubbleTestTwoNg::InitFuncMap(algorithm);
    algorithm.placement_ = Placement::BOTTOM_LEFT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM_RIGHT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_LEFT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP_RIGHT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::RIGHT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_TOP;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT_BOTTOM;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::LEFT;
    EXPECT_TRUE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
    algorithm.placement_ = Placement::NONE;
    EXPECT_FALSE(algorithm.AvoidToTargetPlacement(childSize, arrowPosition, resultPosition, resultSize, canCompress));
}

/**
 * @tc.name: AvoidOrCoverParent001
 * @tc.desc: Test AvoidOrCoverParent
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidOrCoverParent001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, 0.0f);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(SIZE_TWENTY, SIZE_TWENTY);
    Placement originPlacement = Placement::BOTTOM_LEFT;
    algorithm.placementFuncMap_[Placement::BOTTOM_LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottomLeft;
    OffsetF ArrowOffset(0.0f, 0.0f);
    algorithm.avoidTarget_ = AvoidanceMode::AVOID_AROUND_TARGET;
    algorithm.hasPlacement_ = true;
    algorithm.hasWidth_ = true;
    InitCanPlacement(algorithm);
    OffsetF result =
        algorithm.AvoidOrCoverParent(childSize, bubbleLayoutProperty, layoutWrapper, originPlacement, ArrowOffset);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_ONE_HUNDRED);

    algorithm.hasWidth_ = false;
    result = algorithm.AvoidOrCoverParent(childSize, bubbleLayoutProperty, layoutWrapper, originPlacement, ArrowOffset);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_ONE_HUNDRED);

    childSize = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    result = algorithm.AvoidOrCoverParent(childSize, bubbleLayoutProperty, layoutWrapper, originPlacement, ArrowOffset);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_ONE_HUNDRED);
}

/**
 * @tc.name: AvoidOrCoverParent002
 * @tc.desc: Test AvoidOrCoverParent
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, AvoidOrCoverParent002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleTestTwoNg::InitSetting(algorithm);
    algorithm.arrowHeight_ = 0.0f;
    algorithm.targetOffset_ = OffsetF(POSITION_FIFTY, 0.0f);
    algorithm.targetSize_ = SizeF(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);
    SizeF resultSize(0.0f, 0.0f);
    OffsetF arrowPosition(0.0f, 0.0f);
    OffsetF resultPosition(0.0f, 0.0f);
    SizeF childSize(SIZE_ONE_HUNDRED, SIZE_ONE_HUNDRED);

    Placement originPlacement = Placement::BOTTOM_LEFT;
    algorithm.placementFuncMap_[Placement::BOTTOM_LEFT] = &BubbleLayoutAlgorithm::GetPositionWithPlacementBottomLeft;
    OffsetF ArrowOffset(0.0f, 0.0f);

    algorithm.avoidTarget_ = AvoidanceMode::AVOID_AROUND_TARGET;
    algorithm.hasPlacement_ = false;
    algorithm.hasWidth_ = true;
    InitCanPlacement(algorithm);

    OffsetF result =
        algorithm.AvoidOrCoverParent(childSize, bubbleLayoutProperty, layoutWrapper, originPlacement, ArrowOffset);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_ONE_HUNDRED);

    algorithm.hasWidth_ = false;
    algorithm.maxAreaInfo_ =
        PopupMaxAreaInfo { Placement::BOTTOM_LEFT, OffsetF { POSITION_FIFTY, POSITION_ONE_HUNDRED_FIFTY },
            SizeF { SIZE_FORTY, SIZE_FORTY }, OffsetF { 0.0f, 0.0f } };
    result = algorithm.AvoidOrCoverParent(childSize, bubbleLayoutProperty, layoutWrapper, originPlacement, ArrowOffset);
    EXPECT_FLOAT_EQ(result.GetX(), RESULT_FIFTY);
    EXPECT_FLOAT_EQ(result.GetY(), RESULT_ONE_HUNDRED_FIFTY);
}

/**
 * @tc.name: BubblePatternUpdateBubbleBackGroundColorTest001
 * @tc.desc: Test BubblePattern::UpdateBubbleBackGroundColor
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, BubblePatternUpdateBubbleBackGroundColorTest001, TestSize.Level1)
{
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto host = bubblePattern->GetHost();
    ASSERT_NE(host, nullptr);

    Color testColor = Color::RED;

    bubblePattern->UpdateBubbleBackGroundColor(testColor);

    auto popupPaintProp = host->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(popupPaintProp, nullptr);

    EXPECT_EQ(popupPaintProp->GetBackgroundColor().value(), testColor);
}

/**
 * @tc.name: BubblePatternUpdateMaskColorTest001
 * @tc.desc: Test BubblePattern::UpdateMaskColor
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, BubblePatternUpdateMaskColorTest001, TestSize.Level1)
{
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto host = bubblePattern->GetHost();
    ASSERT_EQ(host, frameNode);

    Color testColor = Color::GREEN;

    bubblePattern->UpdateMaskColor(testColor);

    auto popupPaintProp = host->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(popupPaintProp, nullptr);

    EXPECT_EQ(popupPaintProp->GetMaskColor().value(), testColor);
}
} // namespace OHOS::Ace::NG