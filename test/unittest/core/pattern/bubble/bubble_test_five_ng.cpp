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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float MARGIN_START = 10.0f;
constexpr float MARGIN_END = 10.0f;
constexpr float MARGIN_BOTTOM = 10.0f;
constexpr float MARGIN_TOP = 10.0f;
constexpr float SIZE_TWENTY = 20.0f;
constexpr float SIZE_THIRTY = 30.0f;
constexpr float SIZE_FORTY = 40.0f;
constexpr float POSITION_FIFTY = 50.0f;
constexpr float RESULT_FIFTY = 50.0f;
constexpr float SIZE_ONE_HUNDRED = 100.0f;
constexpr float RESULT_ONE_HUNDRED = 100.0f;
constexpr float POSITION_ONE_HUNDRED_FIFTY = 150.0f;
constexpr float RESULT_ONE_HUNDRED_FIFTY = 150.0f;
constexpr float SIZE_TWO_HUNDRED = 200.0f;
constexpr float OFFSET_TWO_HUNDRED = 200.0f;
constexpr float SIZE_FIVE_HUNDRED = 500.0f;
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

class BubbleFiveTestNg : public testing::Test {
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

void BubbleFiveTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void BubbleFiveTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void BubbleFiveTestNg::InitSetting(BubbleLayoutAlgorithm& algorithm)
{
    algorithm.marginStart_ = MARGIN_START;
    algorithm.marginEnd_ = MARGIN_END;
    algorithm.marginTop_ = MARGIN_TOP;
    algorithm.marginBottom_ = MARGIN_BOTTOM;
    algorithm.targetSpace_ = Dimension(0.0f);
    algorithm.userSetTargetSpace_ = Dimension(0.0f);
}

void BubbleFiveTestNg::InitGetRectSetting(BubbleLayoutAlgorithm& algorithm)
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

void BubbleFiveTestNg::InitCheckPositionSetting(BubbleLayoutAlgorithm& algorithm)
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

void BubbleFiveTestNg::InitFuncMap(BubbleLayoutAlgorithm& algorithm)
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

void BubbleFiveTestNg::InitCanPlacement(BubbleLayoutAlgorithm& algorithm)
{
    algorithm.canPlacement_.bottom = true;
    algorithm.canPlacement_.top = true;
    algorithm.canPlacement_.right = true;
    algorithm.canPlacement_.left = true;
}

RefPtr<FrameNode> BubbleFiveTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleFiveTestNg::CreateBubbleNode(const TestProperty& testProperty)
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
 * @tc.name: AvoidToTargetPlacement001
 * @tc.desc: Test AvoidToTargetPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, AvoidToTargetPlacement001, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleFiveTestNg::InitSetting(algorithm);
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
HWTEST_F(BubbleFiveTestNg, AvoidToTargetPlacement002, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleFiveTestNg::InitSetting(algorithm);
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
HWTEST_F(BubbleFiveTestNg, AvoidToTargetPlacement003, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleFiveTestNg::InitSetting(algorithm);
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
    BubbleFiveTestNg::InitFuncMap(algorithm);
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
HWTEST_F(BubbleFiveTestNg, AvoidToTargetPlacement004, TestSize.Level1)
{
    BubbleLayoutAlgorithm algorithm;
    algorithm.wrapperSize_ = SizeF(SIZE_TWO_HUNDRED, SIZE_TWO_HUNDRED);
    BubbleFiveTestNg::InitSetting(algorithm);
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
    BubbleFiveTestNg::InitFuncMap(algorithm);
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
HWTEST_F(BubbleFiveTestNg, AvoidOrCoverParent001, TestSize.Level1)
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
    BubbleFiveTestNg::InitSetting(algorithm);
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
HWTEST_F(BubbleFiveTestNg, AvoidOrCoverParent002, TestSize.Level1)
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
    BubbleFiveTestNg::InitSetting(algorithm);
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
HWTEST_F(BubbleFiveTestNg, BubblePatternUpdateBubbleBackGroundColorTest001, TestSize.Level1)
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
HWTEST_F(BubbleFiveTestNg, BubblePatternUpdateMaskColorTest001, TestSize.Level1)
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

/**
 * @tc.name: InitTargetSizeAndPosition002
 * @tc.desc: Test InitTargetSizeAndPosition.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, InitTargetSizeAndPosition002, TestSize.Level1)
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
    bool showInSubwindow = true;
    layoutAlgorithm->expandDisplay_ = true;
    layoutAlgorithm->InitTargetSizeAndPosition(showInSubwindow, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutAlgorithm->targetOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: UpdateContentPositionRange001
 * @tc.desc: Test adjust bubble position.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, UpdateContentPositionRange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. test GetBubblePosition.
     */
    float xMin = 200.0f;
    float xMax = 1000.0f;
    float yMin = 200.0f;
    float yMax = 1000.0f;
    Dimension BUBBLE_ARROW_HEIGHT = 8.0_vp;
    layoutAlgorithm->placement_ = Placement::BOTTOM;
    layoutAlgorithm->UpdateContentPositionRange(xMin, xMax, yMin, yMax);
    EXPECT_EQ(yMin, 200.0 + BUBBLE_ARROW_HEIGHT.ConvertToPx());

    layoutAlgorithm->placement_ = Placement::RIGHT;
    layoutAlgorithm->UpdateContentPositionRange(xMin, xMax, yMin, yMax);
    EXPECT_EQ(xMin, 200.0 + BUBBLE_ARROW_HEIGHT.ConvertToPx());
}

/**
 * @tc.name: BubblePatternUpdateArrowWidthTest001
 * @tc.desc: Test BubblePattern::UpdateArrowWidth
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, BubblePatternUpdateArrowWidthTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create bubble frame node.
     * @tc.expected: step1. Frame node is created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get BubblePattern from frame node.
     * @tc.expected: step2. BubblePattern is not null.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);

    /**
     * @tc.steps: step3. Update arrow width to 1.0f.
     * @tc.expected: step3. Arrow width is updated correctly.
     */
    CalcDimension dimension = { 1.0f };
    bubblePattern->UpdateArrowWidth(dimension);

    /**
     * @tc.steps: step4. Verify arrow width value in layout property.
     * @tc.expected: step4. Arrow width value is 1.0f.
     */
    auto bubbleLayout = frameNode->GetLayoutPropertyPtr<BubbleLayoutProperty>();
    ASSERT_NE(bubbleLayout, nullptr);

    CalcDimension defaultValue = { 0.0f };
    auto arrowWidthValue = bubbleLayout->GetArrowWidthValue(Dimension(defaultValue));
    EXPECT_EQ(arrowWidthValue, Dimension(1.0f));
}

/**
 * @tc.name: BubblePatternUpdateArrowHeightTest001
 * @tc.desc: Test BubblePattern::UpdateArrowHeight
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, BubblePatternUpdateArrowHeightTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create bubble frame node.
     * @tc.expected: step1. Frame node is created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get BubblePattern from frame node.
     * @tc.expected: step2. BubblePattern is not null.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);

    /**
     * @tc.steps: step3. Update arrow height to 1.0f.
     * @tc.expected: step3. Arrow height is updated correctly.
     */
    CalcDimension dimension = { 1.0f };
    bubblePattern->UpdateArrowHeight(dimension);

    /**
     * @tc.steps: step4. Verify arrow height value in layout property.
     * @tc.expected: step4. Arrow height value is 1.0f.
     */
    auto bubbleLayout = frameNode->GetLayoutPropertyPtr<BubbleLayoutProperty>();
    ASSERT_NE(bubbleLayout, nullptr);

    CalcDimension defaultValue = { 0.0f };
    auto arrowHeightValue = bubbleLayout->GetArrowHeightValue(Dimension(defaultValue));
    EXPECT_EQ(arrowHeightValue, Dimension(1.0f));
}

/**
 * @tc.name: BubblePatternUpdateWidthTest001
 * @tc.desc: Test BubblePattern::UpdateWidth
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, BubblePatternUpdateWidthTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create bubble frame node.
     * @tc.expected: step1. Frame node is created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get BubblePattern from frame node.
     * @tc.expected: step2. BubblePattern is not null.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);

    /**
     * @tc.steps: step3. Add a child node to bubble.
     * @tc.expected: step3. Child node is created and added successfully.
     */
    auto child = FrameNode::CreateFrameNode("child", 11, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(child, nullptr);
    frameNode->AddChild(child);

    /**
     * @tc.steps: step4. Update bubble width to 1.0f.
     * @tc.expected: step4. Bubble width is updated correctly.
     */
    CalcDimension dimension = { 1.0f };
    bubblePattern->UpdateWidth(dimension);

    /**
     * @tc.steps: step5. Verify width value in measure property.
     * @tc.expected: step5. Width value is 1.0f (due to measure property setup).
     */
    auto layoutProperty = child->GetLayoutProperty();
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    auto width = layoutConstraint->selfIdealSize->Width();
    EXPECT_DOUBLE_EQ(width->GetDimension().ConvertToPx(), 1.0f);
}

/**
 * @tc.name: BubblePatternUpdateRadiusTest001
 * @tc.desc: Test BubblePattern::UpdateRadius
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, BubblePatternUpdateRadiusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create bubble frame node.
     * @tc.expected: step1. Frame node is created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get BubblePattern from frame node.
     * @tc.expected: step2. BubblePattern is not null.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);

    /**
     * @tc.steps: step3. Update bubble radius to 1.0f.
     * @tc.expected: step3. Bubble radius is updated correctly.
     */
    CalcDimension dimension = { 1.0f };
    bubblePattern->UpdateRadius(dimension);

    /**
     * @tc.steps: step4. Verify radius value in layout property.
     * @tc.expected: step4. Radius value is 1.0f.
     */
    auto bubbleLayout = frameNode->GetLayoutPropertyPtr<BubbleLayoutProperty>();
    ASSERT_NE(bubbleLayout, nullptr);

    CalcDimension defaultValue = { 0.0f };
    auto radiusValue = bubbleLayout->GetRadiusValue(Dimension(defaultValue));
    EXPECT_EQ(radiusValue, Dimension(1.0f));
}

/**
 * @tc.name: BubblePatternUpdateBubbleTextTest001
 * @tc.desc: Test BubblePattern::UpdateBubbleText
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, BubblePatternUpdateBubbleTextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create bubble frame node.
     * @tc.expected: step1. Frame node is created successfully.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get BubblePattern from frame node.
     * @tc.expected: step2. BubblePattern is not null.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);

    /**
     * @tc.steps: step3. Create and set message node.
     * @tc.expected: step3. Message node is created and set successfully.
     */
    auto messageNode = FrameNode::CreateFrameNode("messageNode", 11, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(messageNode, nullptr);

    bubblePattern->SetMessageNode(messageNode);

    /**
     * @tc.steps: step4. Update bubble text color to BLACK.
     * @tc.expected: step4. Text color is updated correctly.
     */
    bubblePattern->UpdateBubbleText(Color::BLACK);

    /**
     * @tc.steps: step5. Verify text color in message node layout property.
     * @tc.expected: step5. Text color is BLACK.
     */
    auto textProperLayout = messageNode->GetLayoutPropertyPtr<TextLayoutProperty>();
    ASSERT_NE(textProperLayout, nullptr);

    auto textColorValue = textProperLayout->GetTextColorValue(Color::RED);
    EXPECT_EQ(textColorValue, Color::BLACK);
}


/**
 * @tc.name: OnWindowSizeChangedTest001
 * @tc.desc: Test OnWindowSizeChanged func.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleFiveTestNg, OnWindowSizeChangedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get bubblePattern.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    ASSERT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. call OnWindowSizeChanged.
     * @tc.expected: step2. Check the property is correct.
     */

    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    PopupInfo popupInfo;
    popupInfo.popupNode = frameNode;
    popupInfo.target = AceType::WeakClaim(AceType::RawPtr(targetNode));
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::MAXIMIZE);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, false);
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::RECOVER);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, false);
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, false);
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::HIDE);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, false);
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::TRANSFORM);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, false);
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::CUSTOM_ANIMATION);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, false);
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::FULL_TO_SPLIT);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, false);
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::AVOID_AREA_CHANGE);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).isCurrentOnShow, true);
}
} // namespace OHOS::Ace::NG