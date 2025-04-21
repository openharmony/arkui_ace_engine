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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "base/geometry/ng/rect_t.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/rosen/testing_path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float ZERO = 0.0f;

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float CONTAINER_WIDTH = 600.0f;
constexpr float CONTAINER_HEIGHT = 1000.0f;
constexpr float TARGET_WIDTH = 100.0f;
constexpr float TARGET_HEIGHT = 200.0f;
constexpr float TARGET_X = 100.0f;
constexpr float TARGET_Y = 150.0f;
constexpr int CHILD_SIZE_X = 1;
constexpr int CHILD_SIZE_Y = 2;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float POSITION_OFFSET = 100.0f;
constexpr bool BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE = true;
constexpr bool BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_FALSE = false;
constexpr bool BUBBLE_PROPERTY_SHOW = true;
const OffsetF BUBBLE_POSITION_OFFSET = OffsetF(100.0f, 100.0f);
constexpr Dimension BUBBLE_CHILD_OFFSET = 8.0_vp;
const SafeAreaInsets::Inset KEYBOARD_INSET = { .start = 500.f, .end = 1000.f };

const std::string CLIP_PATH = "M100 0 L0 100 L50 200 L150 200 L200 100 Z";
const std::string BUBBLE_MESSAGE = "Hello World";
const std::string BUBBLE_NEW_MESSAGE = "Good";
const std::string STATE = "true";
const OffsetF DISPLAY_WINDOW_OFFSET = OffsetF(ZERO, ZERO);
const OffsetF TARGET_OFFSET(TARGET_X, TARGET_Y);
const OffsetF MESSAGE_OFFSET = OffsetF(6, 16);
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF TARGET_SIZE(TARGET_WIDTH, TARGET_HEIGHT);
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const std::string ARROW_PATH_EMPTY = "";
const std::vector<Placement> BUBBLE_LAYOUT_PROPERTY_PLACEMENTS = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
    Placement::BOTTOM, Placement::TOP_LEFT, Placement::TOP_RIGHT, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT,
    Placement::LEFT_BOTTOM, Placement::LEFT_TOP, Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP, Placement::NONE };
const Offset POPUP_PARAM_POSITION_OFFSET = Offset(100.0f, 100.0f);
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
            RefPtr<MockBubbleTheme> theme = AceType::Claim(new MockBubbleTheme());
            return theme;
        }
    };

    ~MockBubbleTheme() override = default;

protected:
    MockBubbleTheme() = default;
};

class BubbleTestOneNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
};

void BubbleTestOneNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void BubbleTestOneNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

PaddingProperty BubbleTestOneNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<FrameNode> BubbleTestOneNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleTestOneNg::CreateBubbleNode(const TestProperty& testProperty)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
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
 * @tc.name: AdjustPosition001
 * @tc.desc: Test AdjustPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, AdjustPosition001, TestSize.Level1)
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
    layoutAlgorithm->placement_ = Placement::RIGHT;
    layoutAlgorithm->showArrow_ = true;
    OffsetF tesPos(10.0f, 10.0f);
    layoutAlgorithm->AdjustPosition(tesPos, 1.0f, 1.0f, 1.0f);
    EXPECT_EQ(layoutAlgorithm->placement_, Placement::RIGHT);
    int testCase = 100;
    layoutAlgorithm->placement_ = static_cast<Placement>(testCase);
    layoutAlgorithm->AdjustPosition(tesPos, 1.0f, 1.0f, 1.0f);
    EXPECT_EQ(layoutAlgorithm->showArrow_, true);
    layoutAlgorithm->AdjustPosition(tesPos, 1.0f, 1.0f, 100.0f);
    EXPECT_EQ(layoutAlgorithm->showArrow_, true);
}

/**
 * @tc.name: GetPositionWithPlacementNew001
 * @tc.desc: Test GetPositionWithPlacementNew
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetPositionWithPlacementNew001, TestSize.Level1)
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
    SizeF testSize;
    OffsetF topPosition;
    OffsetF botPosition;
    OffsetF arrPosition;
    int testCase = layoutAlgorithm->placementFuncMap_.size() + 1;
    layoutAlgorithm->placement_ = static_cast<Placement>(testCase);
    auto func = layoutAlgorithm->placementFuncMap_.find(static_cast<Placement>(testCase));
    layoutAlgorithm->GetPositionWithPlacementNew(testSize, topPosition, botPosition, arrPosition);
    EXPECT_TRUE(func == layoutAlgorithm->placementFuncMap_.end());
    layoutAlgorithm->placementFuncMap_[Placement::TOP] = nullptr;
    layoutAlgorithm->placement_ = Placement::TOP;
    func = layoutAlgorithm->placementFuncMap_.find(static_cast<Placement>(Placement::TOP));
    layoutAlgorithm->GetPositionWithPlacementNew(testSize, topPosition, botPosition, arrPosition);
    EXPECT_TRUE(func != layoutAlgorithm->placementFuncMap_.end());
}

/**
 * @tc.name: UpdateChildPosition001
 * @tc.desc: Test UpdateChildPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, UpdateChildPosition001, TestSize.Level1)
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
    OffsetF offset(0.0f, 0.0f);
    layoutAlgorithm->placement_ = Placement::TOP_RIGHT;
    layoutAlgorithm->enableArrow_ = false;
    layoutAlgorithm->childSize_.SetWidth(16.0f);
    layoutAlgorithm->childSize_.SetHeight(16.0f);
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), 8.0f);
    offset.Reset();
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), 0);
    offset.Reset();
    layoutAlgorithm->placement_ = Placement::BOTTOM_RIGHT;
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), 0);
    offset.Reset();
    layoutAlgorithm->placement_ = Placement::LEFT_BOTTOM;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), 0.0f);
    offset.Reset();
    layoutAlgorithm->enableArrow_ = false;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetX(), 8.0f);
    offset.Reset();
    layoutAlgorithm->placement_ = Placement::RIGHT_BOTTOM;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetX(), -8.0f);
    offset.Reset();
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetX(), 0);
}

/**
 * @tc.name: GetArrowBuildPlacement001
 * @tc.desc: Test GetArrowBuildPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetArrowBuildPlacement001, TestSize.Level1)
{
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
    Placement arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetX(1000.0f);
    layoutAlgorithm->childSize_.SetWidth(1000.0f);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::TOP_LEFT);
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowOffset_.SetValue(20.0f);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::TOP);
    layoutAlgorithm->bCaretMode_ = true;
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::TOP);
}

/**
 * @tc.name: GetArrowBuildPlacement002
 * @tc.desc: Test GetArrowBuildPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetArrowBuildPlacement002, TestSize.Level1)
{
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
    Placement arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowPlacement_ = Placement::LEFT;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetY(1000.0f);
    layoutAlgorithm->childSize_.SetHeight(1000.0f);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::RIGHT_TOP);
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::PERCENT);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::RIGHT);
    layoutAlgorithm->bCaretMode_ = true;
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::RIGHT);
}

/**
 * @tc.name: GetArrowBuildPlacement003
 * @tc.desc: Test GetArrowBuildPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetArrowBuildPlacement003, TestSize.Level1)
{
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
    Placement arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetX(1000.0f);
    layoutAlgorithm->childSize_.SetWidth(1000.0f);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::BOTTOM_LEFT);
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::PERCENT);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::BOTTOM);
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->bCaretMode_ = true;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::BOTTOM);
}

/**
 * @tc.name: GetArrowBuildPlacement004
 * @tc.desc: Test GetArrowBuildPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetArrowBuildPlacement004, TestSize.Level1)
{
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
    Placement arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetY(1000.0f);
    layoutAlgorithm->childSize_.SetHeight(1000.0f);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::LEFT_TOP);
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::PERCENT);
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::LEFT);
    arrowBuildPlacement = Placement::NONE;
    layoutAlgorithm->bCaretMode_ = true;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::LEFT);
    layoutAlgorithm->arrowPlacement_ = Placement::NONE;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
}

/**
 * @tc.name: BuildCornerPath001
 * @tc.desc: Test BuildCornerPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BuildCornerPath001, TestSize.Level1)
{
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
    Placement arrowBuildPlacement = Placement::NONE;
    std::string path = layoutAlgorithm->BuildCornerPath(arrowBuildPlacement, 0.0f);
    EXPECT_EQ(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath001
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath001, TestSize.Level1)
{
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
    layoutAlgorithm->bCaretMode_ = false;
    auto path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
    layoutAlgorithm->bCaretMode_ = true;
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = false;
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetX(1000.0f);
    layoutAlgorithm->childSize_.SetWidth(1000.0f);
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath002
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath002, TestSize.Level1)
{
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
    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetY(1000.0f);
    layoutAlgorithm->childSize_.SetHeight(1000.0f);
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath003
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath003, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath004
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath004, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowPlacement_ = Placement::LEFT;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetY(1000.0f);
    layoutAlgorithm->childSize_.SetHeight(1000.0f);
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath005
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath005, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath006
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath006, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetX(1000.0f);
    layoutAlgorithm->childSize_.SetWidth(1000.0f);
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath007
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath007, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath008
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath008, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetY(1000.0f);
    layoutAlgorithm->childSize_.SetHeight(1000.0f);
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath009
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath009, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    layoutAlgorithm->childOffset_.SetX(1000.0f);
    layoutAlgorithm->childSize_.SetWidth(1000.0f);
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: ClipBubbleWithPath010
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, ClipBubbleWithPath010, TestSize.Level1)
{
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
    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->arrowOffset_.SetUnit(DimensionUnit::LPX);
    layoutAlgorithm->borderRadius_.SetValue(16.0f);
    layoutAlgorithm->arrowOffset_.SetValue(1.0f);
    std::string path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: FitToScreenNew001
 * @tc.desc: Test ClipBubbleWithPath
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, FitToScreenNew001, TestSize.Level1)
{
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
    size_t index = 0;
    SizeF childSize;
    OffsetF testF = layoutAlgorithm->FitToScreenNew(OffsetF(10.0f, 10.0f), 0, index, childSize);
    EXPECT_EQ(testF, OffsetF(0.0f, 0.0f));
    testF = layoutAlgorithm->FitToScreenNew(OffsetF(0.0f, 0.0f), 0, index, childSize, true);
    EXPECT_EQ(testF, OffsetF(0.0f, 0.0f));
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    testF = layoutAlgorithm->FitToScreenNew(OffsetF(0.0f, 0.0f), 0, index, childSize, true);
    EXPECT_EQ(testF, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: GetIfNeedArrow001
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetIfNeedArrow001, TestSize.Level1)
{
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
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(frameNode->GetLayoutProperty());
    EXPECT_NE(layoutProperty, nullptr);
    SizeF childSize;
    //placement_
    layoutAlgorithm->placement_ = Placement::LEFT;
    bool test = layoutAlgorithm->GetIfNeedArrow(layoutProperty, childSize);
    EXPECT_EQ(test, false);
    childSize.SetHeight(100.0f);
    test = layoutAlgorithm->GetIfNeedArrow(layoutProperty, childSize);
    EXPECT_EQ(test, true);
    layoutAlgorithm->placement_ = Placement::TOP;
    childSize.SetWidth(100.0f);
    test = layoutAlgorithm->GetIfNeedArrow(layoutProperty, childSize);
    EXPECT_EQ(test, true);
}

/**
 * @tc.name: GetAdjustPosition001
 * @tc.desc: Test GetAdjustPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetAdjustPosition001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP, Placement::NONE };
    SizeF childSize(1, 2);
    auto targetSize = layoutAlgorithm->targetSize_ = SizeF(100.0f, 100.0f);
    auto targetOffset = layoutAlgorithm->targetOffset_ = OffsetF(100.0f, 100.0f);
    OffsetF bottomPosition = OffsetF(targetOffset.GetX() + (targetSize.Width() - childSize.Width()) / 2.0,
        targetOffset.GetY() + targetSize.Height());
    OffsetF topPosition = OffsetF(targetOffset.GetX() + (targetSize.Width() - childSize.Width()) / 2.0,
        targetOffset.GetY() - childSize.Height());
    auto offsetPos = OffsetF(0.0f, 0.0f);
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->bVertical_ = true;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->placement_ = Placement::LEFT;
    auto pos = layoutAlgorithm->GetAdjustPosition(
        curPlaceStates, 1, childSize, topPosition, bottomPosition, offsetPos);
    EXPECT_EQ(pos.GetX(), 0.0f);
    layoutAlgorithm->bVertical_ = false;
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->bHorizontal_ = true;
    layoutAlgorithm->placement_ = Placement::TOP;
    pos = layoutAlgorithm->GetAdjustPosition(
        curPlaceStates, 1, childSize, topPosition, bottomPosition, offsetPos);
    EXPECT_EQ(pos.GetX(), 0.0f);
}

/**
 * @tc.name: CheckPositionInPlacementRect001
 * @tc.desc: Test CheckPositionInPlacementRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CheckPositionInPlacementRect001, TestSize.Level1)
{
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
    Rect tstRect;
    OffsetF tstPosition(100.0f, 100.0f);
    SizeF childSize;
    bool tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    ASSERT_NE(tstRuslt, true);
    tstRect.SetLeft(1000.0f);
    tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    ASSERT_NE(tstRuslt, true);
}

/**
 * @tc.name: CheckPositionInPlacementRect002
 * @tc.desc: Test CheckPositionInPlacementRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CheckPositionInPlacementRect002, TestSize.Level1)
{
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
    Rect tstRect;
    OffsetF tstPosition(100.0f, 100.0f);
    SizeF childSize;
    tstRect.SetWidth(1000.0f);
    tstRect.SetTop(1000.0f);
    bool tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    ASSERT_NE(tstRuslt, true);
}

/**
 * @tc.name: CheckPositionInPlacementRect003
 * @tc.desc: Test CheckPositionInPlacementRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CheckPositionInPlacementRect003, TestSize.Level1)
{
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
    Rect tstRect;
    OffsetF tstPosition(100.0f, 100.0f);
    SizeF childSize;
    tstRect.SetWidth(1000.0f);
    tstRect.SetHeight(1000.0f);
    bool tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    ASSERT_NE(tstRuslt, false);
    tstRect.SetHeight(0.0f);
    tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    ASSERT_NE(tstRuslt, true);
    tstPosition.SetY(0.01f);
    childSize = {100.0f, 100.0f};
    tstRect.SetRect(0.0f, 0.0f, 1000.0f, 1000.0f);
    tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    EXPECT_TRUE(tstRuslt);
}

/**
 * @tc.name: CheckPositionInPlacementRect004
 * @tc.desc: Test CheckPositionInPlacementRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CheckPositionInPlacementRect004, TestSize.Level1)
{
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
    Rect tstRect;
    OffsetF tstPosition(10.0f, 10.0f);
    SizeF childSize = {900.0f, 900.0f};
    tstRect.SetWidth(1000.0f);
    tstRect.SetHeight(1000.0f);
    bool tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    EXPECT_EQ(tstRuslt, true);
    tstRect = {0.0f, 0.0f, 500.0f, 500.0f};
    tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    EXPECT_EQ(tstRuslt, false);
    tstRect = {0.0f, 0.0f, 1000.0f, 1000.0f};
    tstPosition = {501.0f, 0.0f};
    childSize = {500.0f, 500.0f};
    tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    EXPECT_EQ(tstRuslt, false);
    tstPosition = {0.0f, 501.0f};
    tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    EXPECT_EQ(tstRuslt, false);
    tstPosition = {499.0f, 499.0f};
    tstRuslt = layoutAlgorithm->CheckPositionInPlacementRect(tstRect, tstPosition, childSize);
    EXPECT_EQ(tstRuslt, true);
}

/**
 * @tc.name: UpdateClipOffset001
 * @tc.desc: Test CheckPositionInPlacementRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, UpdateClipOffset001, TestSize.Level1)
{
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
    layoutAlgorithm->bCaretMode_ = false;
    layoutAlgorithm->UpdateClipOffset(frameNode);
    ASSERT_NE(layoutAlgorithm->bCaretMode_, true);
}

/**
 * @tc.name: GetErrorPositionType001
 * @tc.desc: Test GetErrorPositionType
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetErrorPositionType001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
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
    SizeF tstSize(100.0f, 100.0f);
    OffsetF tstOffset(9.0f, 2.0f);
    PointF tstPoint(tstOffset.GetX(), tstOffset.GetY());
    layoutAlgorithm->top_ = 1.0f;
    layoutAlgorithm->bottom_ = 1.0f;
    layoutAlgorithm->selfSize_.SetHeight(10.0f);
    layoutAlgorithm->selfSize_.SetWidth(20.0f);
    auto tstRet = layoutAlgorithm->GetErrorPositionType(tstOffset, tstSize);
    EXPECT_TRUE(tstRet == BubbleLayoutAlgorithm::ErrorPositionType::BOTTOM_RIGHT_ERROR);
}

/**
 * @tc.name: FitToScreen001
 * @tc.desc: Test FitToScreen
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, FitToScreen001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create node
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
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
     * @tc.steps: step2.RectF::IsInRegion(109, 102)==false.
     * @tc.expected: childPosition.x = selfSize_.width_ - tstSize.width_ - HORIZON_SPACING_WITH_SCREEN.ConvertToPx()
     */
    SizeF tstSize(100.0f, 100.0f);
    OffsetF tstOffset(9.0f, 2.0f);
    layoutAlgorithm->top_ = 1.0f;
    layoutAlgorithm->bottom_ = 1.0f;
    layoutAlgorithm->selfSize_.SetHeight(10.0f);
    layoutAlgorithm->selfSize_.SetWidth(20.0f);
    auto tstChildPosition = layoutAlgorithm->FitToScreen(tstOffset, tstSize);
    EXPECT_LT(tstChildPosition.GetX(), 0.0f);
    /**
     * @tc.steps: step2.RectF::IsInRegion(9.0f, 2.0f)==true.
     * @tc.expected: childPosition.x = tstOffset.GetX()
     */
    tstSize.Reset();
    tstChildPosition = layoutAlgorithm->FitToScreen(tstOffset, tstSize);
    EXPECT_GT(tstChildPosition.GetX(), 0.0f);
}

/**
 * @tc.name: GetChildPosition001
 * @tc.desc: Test GetChildPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetChildPosition001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
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
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(bubblePattern->CreateLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    SizeF tstChildSize(0.0f, 0.0f);
    layoutAlgorithm->placement_ = Placement::TOP;
    layoutAlgorithm->GetChildPosition(tstChildSize, layoutProperty, false);
    EXPECT_TRUE(layoutAlgorithm->arrowPlacement_ == Placement::TOP);
    layoutAlgorithm->placement_ = Placement::TOP_LEFT;
    layoutAlgorithm->GetChildPosition(tstChildSize, layoutProperty, false);
    EXPECT_TRUE(layoutAlgorithm->arrowPlacement_ == Placement::TOP);
    layoutAlgorithm->placement_ = Placement::TOP_RIGHT;
    layoutAlgorithm->GetChildPosition(tstChildSize, layoutProperty, true);
    EXPECT_TRUE(layoutAlgorithm->arrowPlacement_ == Placement::TOP);
}

/**
 * @tc.name: UpdateHostWindowRect001
 * @tc.desc: Test UpdateHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, UpdateHostWindowRect001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
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
    layoutAlgorithm->UpdateHostWindowRect();
    EXPECT_EQ(layoutAlgorithm->hostWindowRect_, Rect());
}

/**
 * @tc.name: SetBubbleRadius001
 * @tc.desc: Test SetBubbleRadius
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, SetBubbleRadius001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
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
    layoutAlgorithm->childSize_ = {100.0f, 50.0f};
    layoutAlgorithm->borderRadius_ = 0.5_pct;
    layoutAlgorithm->SetBubbleRadius();
    EXPECT_EQ(layoutAlgorithm->borderRadius_.ConvertToPx(), 12.5f);
    layoutAlgorithm->borderRadius_ = 10.0_px;
    layoutAlgorithm->border_.SetBorderRadius(Radius(layoutAlgorithm->borderRadius_));
    layoutAlgorithm->SetBubbleRadius();
    EXPECT_EQ(layoutAlgorithm->borderRadius_.ConvertToPx(), 10.0f);
    layoutAlgorithm->borderRadius_ = 75.0_px;
    layoutAlgorithm->border_.SetBorderRadius(Radius(layoutAlgorithm->borderRadius_));
    layoutAlgorithm->SetBubbleRadius();
    EXPECT_EQ(layoutAlgorithm->borderRadius_.ConvertToPx(), 25.0f);
    layoutAlgorithm->childSize_ = {50.0f, 100.0f};
    layoutAlgorithm->borderRadius_ = 0.5_pct;
    layoutAlgorithm->border_.SetBorderRadius(Radius(layoutAlgorithm->borderRadius_));
    layoutAlgorithm->SetBubbleRadius();
    EXPECT_EQ(layoutAlgorithm->borderRadius_.ConvertToPx(), 12.5f);
    layoutAlgorithm->borderRadius_ = 10.0_px;
    layoutAlgorithm->border_.SetBorderRadius(Radius(layoutAlgorithm->borderRadius_));
    layoutAlgorithm->SetBubbleRadius();
    EXPECT_EQ(layoutAlgorithm->borderRadius_.ConvertToPx(), 10.0f);
    layoutAlgorithm->borderRadius_ = 75.0_px;
    layoutAlgorithm->border_.SetBorderRadius(Radius(layoutAlgorithm->borderRadius_));
    layoutAlgorithm->SetBubbleRadius();
    EXPECT_EQ(layoutAlgorithm->borderRadius_.ConvertToPx(), 25.0f);
}

/**
 * @tc.name: UpdateBubbleText001
 * @tc.desc: Test UpdateBubbleText
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, UpdateBubbleText001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    ASSERT_NE(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    bubblePattern->showArrow_ = false;
    bubblePattern->UpdateBubbleText();
    EXPECT_EQ(bubblePattern->showArrow_, false);
}

/**
 * @tc.name: BubbleAlgorithmTest001
 * @tc.desc: Test GetAdjustPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. excute GetAdjustPosition
     * @tc.expected: step2. check whether the result is correct.
     */
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP, Placement::NONE };
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    auto targetSize = layoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    auto targetOffset = layoutAlgorithm->targetOffset_ = OffsetF(POSITION_OFFSET, POSITION_OFFSET);
    layoutAlgorithm->bCaretMode_ = layoutAlgorithm->bVertical_ = layoutAlgorithm->bHorizontal_ = true;
    OffsetF bottomPosition = OffsetF(targetOffset.GetX() + (targetSize.Width() - childSize.Width()) / 2.0,
        targetOffset.GetY() + targetSize.Height());
    OffsetF topPosition = OffsetF(targetOffset.GetX() + (targetSize.Width() - childSize.Width()) / 2.0,
        targetOffset.GetY() - childSize.Height());
    auto offsetPos = OffsetF(ZERO, ZERO);
    layoutAlgorithm->showArrow_ = true;
    auto pos = layoutAlgorithm->GetAdjustPosition(
        curPlaceStates, 1, childSize, topPosition, bottomPosition, offsetPos);
    EXPECT_EQ(pos.GetX(), ZERO);
    EXPECT_EQ(pos.GetY(), ZERO);
}

/**
 * @tc.name: BubbleAlgorithmTest002
 * @tc.desc: Test AddTargetSpace
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    bubbleLayoutAlgorithm->targetSecurity_ = 0;
    OffsetF position(TARGET_X, TARGET_Y);
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
        Placement::BOTTOM, Placement::NONE };
    /**
     * @tc.steps: step2. excute AddTargetSpace
     * @tc.expected: step2. check whether the result is correct.
     */
    for (auto &placement : curPlaceStates) {
        bubbleLayoutAlgorithm->placement_ = placement;
        auto pos = bubbleLayoutAlgorithm->AddTargetSpace(position);
        EXPECT_EQ(pos.GetY(), TARGET_Y);
        EXPECT_EQ(pos.GetX(), TARGET_X);
    }
}

/**
 * @tc.name: BubbleAlgorithmTest003
 * @tc.desc: Test CheckPosition
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    bubbleLayoutAlgorithm->targetSecurity_ = 0;
    OffsetF position(ZERO, ZERO);
    size_t i = 1;
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
        Placement::BOTTOM, Placement::NONE };
    /**
     * @tc.steps: step2. excute CheckPosition
     * @tc.expected: step2. check whether the result is correct.
     */
    for (auto &placement : curPlaceStates) {
        bubbleLayoutAlgorithm->placement_ = placement;
        auto ret = bubbleLayoutAlgorithm->CheckPosition(position, childSize, 1, i);
        if (placement == Placement::NONE)
            EXPECT_FALSE(ret);
    }
}

/**
 * @tc.name: BubbleAlgorithmTest004
 * @tc.desc: Test GetArrowOffset
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
        Placement::BOTTOM, Placement::NONE };
    std::vector<ArrowOfTargetOffset> curOffsets = { ArrowOfTargetOffset::START, ArrowOfTargetOffset::CENTER,
        ArrowOfTargetOffset::END };
    /**
     * @tc.steps: step2. excute GetArrowOffset
     * @tc.expected: step2. check whether the result is correct.
     */
    for (auto &placement : curPlaceStates) {
        for (auto &offset : curOffsets) {
            bubbleLayoutAlgorithm->arrowOfTargetOffset_ = offset;
            auto arrowOffset = bubbleLayoutAlgorithm->GetArrowOffset(placement);
            if (placement == Placement::NONE && offset == ArrowOfTargetOffset::END) {
                EXPECT_EQ(arrowOffset, -8);
            }
        }
    }
}

/**
 * @tc.name: BubbleAlgorithmTest005
 * @tc.desc: Test UpdateArrowOffset
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::TOP_LEFT, Placement::TOP_RIGHT,
        Placement::BOTTOM, Placement::NONE };
    std::optional<Dimension> offset = std::nullopt;
    /**
     * @tc.steps: step2. excute UpdateArrowOffset
     * @tc.expected: step2. check whether the properties is correct.
     */
    for (int i = 0; i < curPlaceStates.size(); i++) {

        bubbleLayoutAlgorithm->UpdateArrowOffset(offset, curPlaceStates[i]);
    }
    offset = 20.0_px;
    bubbleLayoutAlgorithm->UpdateArrowOffset(offset, curPlaceStates[0]);
    offset = 20.0_pct;
    bubbleLayoutAlgorithm->UpdateArrowOffset(offset, curPlaceStates[0]);
    EXPECT_EQ(bubbleLayoutAlgorithm->arrowOfTargetOffset_, ArrowOfTargetOffset::END);
    offset = 0.0_pct;
    bubbleLayoutAlgorithm->UpdateArrowOffset(offset, curPlaceStates[0]);
    EXPECT_EQ(bubbleLayoutAlgorithm->arrowOfTargetOffset_, ArrowOfTargetOffset::START);
    offset = 0.5_pct;
    bubbleLayoutAlgorithm->UpdateArrowOffset(offset, curPlaceStates[0]);
    EXPECT_EQ(bubbleLayoutAlgorithm->arrowOfTargetOffset_, ArrowOfTargetOffset::CENTER);
}

/**
 * @tc.name: BubbleAlgorithmTest006
 * @tc.desc: Test GetPositionWithPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    bubbleLayoutAlgorithm->targetSecurity_ = 0;
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    /**
     * @tc.steps: step2. excute GetPositionWithPlacement
     * @tc.expected: step2. check whether the properties is correct.
     */
    for (auto placement : BUBBLE_LAYOUT_PROPERTY_PLACEMENTS) {
        OffsetF childPosition(ZERO, ZERO), arrowPosition(ZERO, ZERO);
        bubbleLayoutAlgorithm->GetPositionWithPlacement(childPosition, arrowPosition, childSize, placement);
        if (placement == Placement::NONE) {
            EXPECT_EQ(childPosition.GetY(), ZERO);
            EXPECT_EQ(childPosition.GetX(), ZERO);
        }
    }
}

/*
 * @tc.name: BubblePaintMethod004
 * @tc.desc: Test BubblePaintMethod PaintOuterBorder.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePaintMethod004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    Testing::MockCanvas canvas;

    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateBubbleNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    auto bubblePaintProperty = frameNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(bubblePaintProperty, nullptr);

    WeakPtr<RenderContext> renderContext;
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, bubblePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    /**
     * @tc.steps: step2. Call the function PaintOuterBorder and PaintInnerBorder.
     */
    
    bubblePaintMethod.GetInnerBorderOffset();
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    bubblePaintMethod.PaintOuterBorder(canvas, paintWrapper);
    bubblePaintMethod.PaintInnerBorder(canvas, paintWrapper);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    bubblePaintMethod.PaintOuterBorder(canvas, paintWrapper);
    bubblePaintMethod.PaintInnerBorder(canvas, paintWrapper);
    /**
     * @tc.steps: step3. call SetArrowWidth.
     * @tc.expected: step3. Check the property.
     */
    float arrowWidth = 2.0;
    bubblePaintMethod.SetArrowWidth(arrowWidth);
    EXPECT_EQ(bubblePaintMethod.arrowWidth_, 2.0);
}

/*
 * @tc.name: BubblePaintMethod005
 * @tc.desc: Test BubblePaintMethod BuildDoubleBorderPath.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePaintMethod005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the BubblePaintMethod.
     */
    BubblePaintMethod bubblePaintMethod;
    Testing::TestingPath Path;
    /**
     * @tc.steps: step2. Call the function BuildDoubleBorderPath.
     */
    bubblePaintMethod.needPaintOuterBorder_ = false;
    bubblePaintMethod.arrowPlacement_ = Placement::NONE;
    bubblePaintMethod.BuildDoubleBorderPath(Path);
    bubblePaintMethod.needPaintOuterBorder_ = true;
    bubblePaintMethod.arrowPlacement_ = Placement::BOTTOM;
    bubblePaintMethod.BuildDoubleBorderPath(Path);
    bubblePaintMethod.arrowPlacement_ = Placement::LEFT;
    bubblePaintMethod.BuildDoubleBorderPath(Path);
    bubblePaintMethod.arrowPlacement_ = Placement::RIGHT;
    bubblePaintMethod.BuildDoubleBorderPath(Path);
    bubblePaintMethod.arrowPlacement_ = Placement::TOP;
    bubblePaintMethod.BuildDoubleBorderPath(Path);
    /**
     * @tc.steps: step3. call SetShowArrow.
     * @tc.expected: step3. Check the property.
     */
    bubblePaintMethod.SetShowArrow(true);
    EXPECT_TRUE(bubblePaintMethod.showArrow_);
}

/**
 * @tc.name: BubblePatternTest017
 * @tc.desc: Test CreateCustomBubbleNode with with Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
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
    /**
     * @tc.steps: step2. call OnColorConfigurationUpdate.
     * @tc.expected: step2. Check the property is correct.
     */
    bubblePattern->isCustomPopup_ = true;
    bubblePattern->OnColorConfigurationUpdate();
    bubblePattern->isCustomPopup_ = false;
    bubblePattern->OnColorConfigurationUpdate();
    EXPECT_EQ(bubblePattern->colorMode_, ColorMode::LIGHT);
}

/**
 * @tc.name: BubblePatternTest018
 * @tc.desc: Test CreateCustomBubbleNode with with Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePatternTest018, TestSize.Level1)
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
    bubblePattern->OnWindowSizeChanged(20, 10, WindowSizeChangeReason::RESIZE);
    layoutProp->UpdateShowInSubWindow(false);
    bubblePattern->OnWindowSizeChanged(20, 10, WindowSizeChangeReason::TRANSFORM);
    bubblePattern->OnWindowHide();
    EXPECT_FALSE(layoutProp->GetShowInSubWindow().value_or(false));
    layoutProp->UpdateShowInSubWindow(true);
    bubblePattern->OnWindowSizeChanged(20, 10, WindowSizeChangeReason::TRANSFORM);
    bubblePattern->OnWindowHide();
    EXPECT_TRUE(layoutProp->GetShowInSubWindow().value_or(false));
}

/**
 * @tc.name: BubblePatternTest019
 * @tc.desc: Test bubble pattern InitTouchEvent HandleTouchEvent HandleTouchDOWN.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePatternTest019, TestSize.Level1)
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
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create pattern and update paintProperty gestureHub and test InitTouchEvent.
     * @tc.expected: step2. check whether the gestureEvent info is correct.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_NE(bubblePattern, nullptr);
    auto paintProperty = bubblePattern->CreatePaintProperty();
    EXPECT_NE(paintProperty, nullptr);
    auto bubblePaintProperty = AceType::DynamicCast<BubbleRenderProperty>(paintProperty);
    EXPECT_NE(bubblePaintProperty, nullptr);
    bubblePaintProperty->UpdateAutoCancel(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_FALSE);

    /**
     * @tc.steps: step3. create gestureHub and test InitTouchEvent HandleTouchEvent.
     * @tc.expected: step3. check whether the function is executed.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<GestureEventHub> gestureHub =
        AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    bubblePattern->InitTouchEvent();

    bubblePattern->SetInteractiveDismiss(false);
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    bubblePattern->HandleTouchEvent(touchEventInfo);

    bubblePattern->touchRegion_ = RectF(0, 0, 200, 200);
    TouchEventInfo touchEventInfo1 = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo1 = TouchLocationInfo(1);
    touchLocationInfo1.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo1.SetTouchType(TouchType::DOWN);
    touchEventInfo1.AddTouchLocationInfo(std::move(touchLocationInfo1));
    bubblePattern->HandleTouchEvent(touchEventInfo1);

    bubblePaintProperty->UpdateAutoCancel(BUBBLE_PAINT_PROPERTY_AUTO_CANCEL_TRUE);
}

/**
 * @tc.name: BubblePatternTest020
 * @tc.desc: Test bubble GetButtonRowNode.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProps = pattern->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProps, nullptr);
    /**
     * @tc.steps: step3. set properties and call MarkModifyDone function.
     */
    paintProps->UpdateUseCustom(false);
    paintProps->UpdatePrimaryButtonShow(true);
    paintProps->UpdateSecondaryButtonShow(true);
    popupNode->MarkModifyDone();
    /**
     * @tc.steps: step4. call hover, touch callback.
     * @tc.expected: after hover callback, isHover_ equal to true.
     */
    auto buttonRowNode = pattern->GetButtonRowNode();
}

 /**
  * @tc.name: BubblePatternTest022
  * @tc.desc: Test UpdateCommonParam with with Offset, Radius, ArrowHeight, ArrowWidth, Shadow and EnableHoverMode.
  * @tc.type: FUNC
  */
HWTEST_F(BubbleTestOneNg, BubblePatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set popup value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetTargetOffset(POPUP_PARAM_POSITION_OFFSET);
    popupParam->setErrorArrowHeight_ = true;
    popupParam->setErrorArrowWidth_ = true;
    popupParam->setErrorRadius_ = true;
    popupParam->childwidth_ = 100.0_px;
    popupParam->SetEnableHoverMode(true);
    /**
     * @tc.steps: step2. create CustomBubbleNode with positon offset
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(rowFrameNode, nullptr);
    auto blankFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(blankFrameNode, nullptr);
    rowFrameNode->AddChild(blankFrameNode);
    auto popupNode =
        BubbleView::CreateCustomBubbleNode(targetNode->GetTag(), targetNode->GetId(), rowFrameNode, popupParam);
    ASSERT_NE(popupNode, nullptr);
    /**
     * @tc.steps: step3. use BubbleLayoutProperty to check PositionOffset.
     * @tc.expected: check whether GetPositionOffset value is correct.
     */
    int32_t settingApiVersion = 13;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    BubbleView::UpdateCommonParam(popupNode->GetId(), popupParam);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_EQ(property->GetPositionOffset().value(), BUBBLE_POSITION_OFFSET);
}

/**
 * @tc.name: BubblePatternTest023
 * @tc.desc: Test bubble callback function
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Register bubble state callback function，and call this function.
     * @tc.expected: Check callNum value
     */
    int32_t callNum = 0;
    std::function<void(const std::string&)> callback = [&](const std::string& param) { callNum++; };
    pattern->RegisterDoubleBindCallback(callback);
    pattern->CallDoubleBindCallback("false");
    EXPECT_EQ(callNum, 1);
}

/**
 * @tc.name: BubblePatternTest024
 * @tc.desc: Test bubble callback function
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubblePatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Update bubble param.
     * @tc.expected: Check callNum value
     */
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    ButtonProperties buttonProperties0 { true, "Button0" };
    ButtonProperties buttonProperties1 { true, "Button1" };
    popupParam->SetPrimaryButtonProperties(buttonProperties0);
    popupParam->SetSecondaryButtonProperties(buttonProperties1);
    auto popupId = popupNode->GetId();
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
    auto columnNode = popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);
    auto combinedChild = columnNode->GetFirstChild();
    ASSERT_NE(combinedChild, nullptr);
    auto scrollNode = combinedChild->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(scrollNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetContent().value(), u"Good");
}

/**
 * @tc.name: BubbleAlgorithmTest007
 * @tc.desc: Test bubble ClipBubbleWithPath.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest007, TestSize.Level1)
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

    /**
     * @tc.steps: step2. get pattern and create layoutAlgorithm.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. test GetArrowBuildPlacement ClipBubbleWithPath
     */
    Placement arrowBuildPlacement = Placement::NONE;

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::TOP_RIGHT);
    auto path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");

    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::BOTTOM);
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");

    layoutAlgorithm->arrowPlacement_ = Placement::LEFT;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::RIGHT);
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->GetArrowBuildPlacement(arrowBuildPlacement);
    EXPECT_EQ(arrowBuildPlacement, Placement::LEFT);
    path = layoutAlgorithm->ClipBubbleWithPath();
    EXPECT_NE(path, "");
}

/**
 * @tc.name: BubbleAlgorithmTest008
 * @tc.desc: Test bubble UpdateChildPosition.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAlgorithmTest008, TestSize.Level1)
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
     * @tc.steps: step2. test UpdateChildPosition.
     */
    layoutAlgorithm->enableArrow_ = false;
    OffsetF offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::TOP;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), BUBBLE_CHILD_OFFSET.ConvertToPx());

    offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::BOTTOM;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetY(), -BUBBLE_CHILD_OFFSET.ConvertToPx());

    offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::LEFT;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetX(), BUBBLE_CHILD_OFFSET.ConvertToPx());

    offset = OffsetF(0, 0);
    layoutAlgorithm->placement_ = Placement::RIGHT;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(offset.GetX(), -BUBBLE_CHILD_OFFSET.ConvertToPx());

    layoutAlgorithm->enableArrow_ = true;
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
    layoutAlgorithm->enableArrow_ = false;
    layoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: BubbleAccessibilityTest001
 * @tc.desc: Test BubblePattern::CreateAccessibilityProperty function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAccessibilityTest001, TestSize.Level1)
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
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get BubbleAccessibilityProperty.
     * @tc.expected: step2. BubbleAccessibilityProperty is not nullptr.
     */
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
}

/**
 * @tc.name: BubbleAccessibilityTest002
 * @tc.desc: Test BubbleAccessibilityProperty::SetShowedState function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, BubbleAccessibilityTest002, TestSize.Level1)
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
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. BubbleAccessibilityProperty is not nullptr.
     */
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. set showedState 0.
     * @tc.expected: step3 get showedState 0.
     */
    accessibilityProperty->SetShowedState(0);
    auto showedState = accessibilityProperty->GetShowedState();
    EXPECT_EQ(showedState, 0);

    /**
     * @tc.steps: step4. set showedState 1.
     * @tc.expected: step4 get showedState 1.
     */
    accessibilityProperty->SetShowedState(1);
    showedState = accessibilityProperty->GetShowedState();
    EXPECT_EQ(showedState, 1);
}

/**
 * @tc.name: HandleKeyboardTest
 * @tc.desc: Test HandleKeyboard function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, HandleKeyboardTest, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test HandleKeyboard.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    manager->keyboardInset_ = KEYBOARD_INSET;
    layoutAlgorithm->wrapperSize_ = {1000.0f, 1000.0f};
    bool isShowInSubwindow = false;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->HandleKeyboard(AceType::RawPtr(layoutWrapper), isShowInSubwindow);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.Height(), 1000.0f);
    layoutAlgorithm->wrapperSize_ = {1000.0f, 1000.0f};
    isShowInSubwindow = true;
    layoutAlgorithm->HandleKeyboard(AceType::RawPtr(layoutWrapper), isShowInSubwindow);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.Height(), 1000.0f);
}

/**
 * @tc.name: AdjustPositionNewTest
 * @tc.desc: Test AdjustPositionNew function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, AdjustPositionNewTest, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test AdjustPositionNew.
     */
    layoutAlgorithm->wrapperSize_ = {1000.0f, 1000.0f};
    OffsetF position = {10.0f, 10.0f};
    float height = 200.0f;
    float width = 200.0f;
    auto result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, position);
    position = {1000.0f, 1000.0f};
    result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, OffsetF(800.0f, 800.0f));
    position = {200.0f, 1000.0f};
    result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, OffsetF(200.0f, 800.0f));
    position = {1000.0f, 200.0f};
    result = layoutAlgorithm->AdjustPositionNew(position, height, width);
    EXPECT_EQ(result, OffsetF(800.0f, 200.0f));
}

/**
 * @tc.name: GetBubblePositionTest
 * @tc.desc: Test GetBubblePosition function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, GetBubblePositionTest, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test GetBubblePosition.
     */
    layoutAlgorithm->placement_ = Placement::LEFT;
    float xMin = 200.0f;
    float xMax = 1000.0f;
    float yMin = 200.0f;
    float yMax = 1000.0f;
    OffsetF position = {10.0f, 10.0f};
    layoutAlgorithm->showArrow_ = true;
    auto result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, true);
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: CheckArrowPositionTest
 * @tc.desc: Test CheckArrowPosition function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CheckArrowPositionTest, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test CheckArrowPosition.
     */
    layoutAlgorithm->placement_ = Placement::LEFT;
    float xMin = 200.0f;
    float xMax = 1000.0f;
    float yMin = 200.0f;
    float yMax = 1000.0f;
    OffsetF position = {10.0f, 10.0f};
    layoutAlgorithm->showArrow_ = true;
    auto result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, true);
    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    result = layoutAlgorithm->GetBubblePosition(position, xMin, xMax, yMin, yMax);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: UpdateBubbleText
 * @tc.desc: Test UpdateBubbleText function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, UpdateBubbleText, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set value to popupParam.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto pattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. test UpdateBubbleText.
     */
    pattern->UpdateBubbleText();
    auto columnNode = popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);
    auto combinedChild = columnNode->GetFirstChild();
    ASSERT_NE(combinedChild, nullptr);
    auto scrollNode = combinedChild->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(scrollNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto popupTheme = pattern->GetPopupTheme();
    auto color = popupTheme->GetFontPrimaryColor();
    EXPECT_EQ(layoutProperty->GetTextColor().value(), color);
}

/**
 * @tc.name: HandleUIExtensionKeyboard
 * @tc.desc: Test HandleUIExtensionKeyboard function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, HandleUIExtensionKeyboard, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test HandleUIExtensionKeyboard.
     */
    layoutAlgorithm->showArrow_ = false;
    bool showInSubwindow = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = true;
    layoutAlgorithm->avoidKeyboard_ = false;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = false;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = false;
    layoutAlgorithm->avoidKeyboard_ = false;
    layoutAlgorithm->HandleUIExtensionKeyboard(AceType::RawPtr(layoutWrapper), showInSubwindow);
    EXPECT_EQ(layoutAlgorithm->showArrow_, false);
}

/**
 * @tc.name: CheckIfNeedRemoveArrow
 * @tc.desc: Test CheckIfNeedRemoveArrow function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CheckIfNeedRemoveArrow, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test CheckIfNeedRemoveArrow.
     */
    float xMin = 0.0;
    float xMax = 100.0;
    float yMin = 0.0;
    float yMax = 100.0;
    Dimension BUBBLE_ARROW_HEIGHT = 8.0_vp;
    layoutAlgorithm->arrowHeight_ = BUBBLE_ARROW_HEIGHT.ConvertToPx();

    layoutAlgorithm->showArrow_ = true;
    layoutAlgorithm->avoidKeyboard_ = true;
    layoutAlgorithm->placement_ = Placement::TOP;
    yMin = yMax + layoutAlgorithm->arrowHeight_ - 1.0;
    auto result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, true);

    layoutAlgorithm->showArrow_ = true;
    yMin = yMax + layoutAlgorithm->arrowHeight_ + 1.0;
    result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, false);

    layoutAlgorithm->placement_ = Placement::LEFT;
    yMin = 0;
    layoutAlgorithm->showArrow_ = true;
    xMin = xMax + layoutAlgorithm->arrowHeight_ - 1.0;
    result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, true);

    layoutAlgorithm->showArrow_ = true;
    xMin = xMax + layoutAlgorithm->arrowHeight_ + 1.0;
    result = layoutAlgorithm->CheckIfNeedRemoveArrow(xMin, xMax, yMin, yMax);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateScrollHeight
 * @tc.desc: Test UpdateScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, UpdateScrollHeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);

    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(popupNode, geometryNode, popupNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test UpdateScrollHeight.
     */
    bubblePattern->enableHoverMode_ = true;
    bool showInSubwindow = true;
    layoutAlgorithm->UpdateScrollHeight(AceType::RawPtr(layoutWrapper), showInSubwindow);
    showInSubwindow = false;
    layoutAlgorithm->UpdateScrollHeight(AceType::RawPtr(layoutWrapper), showInSubwindow);
    EXPECT_EQ(bubblePattern->enableHoverMode_, true);
}

/**
 * @tc.name: CheckArrowPosition1
 * @tc.desc: Test CheckArrowPosition1 function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CheckArrowPosition1, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test CheckArrowPosition1.
     */
    
    std::vector<Placement> curPlaceStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
        Placement::BOTTOM, Placement::NONE };

    for (auto &placement : curPlaceStates) {
        OffsetF position = {0.0f, 0.0f};
        layoutAlgorithm->showArrow_ = true;
        layoutAlgorithm->avoidKeyboard_ = true;
        layoutAlgorithm->placement_ = placement;
        layoutAlgorithm->CheckArrowPosition(position, 10.0f, 10.0f);
    }
    EXPECT_EQ(layoutAlgorithm->avoidKeyboard_, true);
}

/**
 * @tc.name: IsUIExtensionWindow
 * @tc.desc: Test IsUIExtensionWindow function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, IsUIExtensionWindow, TestSize.Level1)
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test IsUIExtensionWindow.
     */

    EXPECT_EQ(layoutAlgorithm->IsUIExtensionWindow(), false);
}

/**
 * @tc.name: InitWrapperRect
 * @tc.desc: Test InitWrapperRect function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, InitWrapperRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    ButtonProperties buttonProperties { true, "Button" };
    buttonProperties.action = AceType::MakeRefPtr<ClickEvent>(nullptr);
    popupParam->SetPrimaryButtonProperties(buttonProperties);
    popupParam->SetSecondaryButtonProperties(buttonProperties);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    /**
     * @tc.steps: step2. create bubble and get popupNode.
     * @tc.expected: Check the popupNode were created successfully.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MockBubbleTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);

    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(popupNode, geometryNode, popupNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test InitWrapperRect.
     */
    bubblePattern->enableHoverMode_ = true;
    layoutAlgorithm->isHalfFoldHover_ = true;
    layoutAlgorithm->InitWrapperRect(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(bubblePattern->enableHoverMode_, true);
}

/**
 * @tc.name: CreateBubbleNode001
 * @tc.desc: Test CreateBubbleNode with istips Offset, Radius, ArrowHeight, ArrowWidth and Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestOneNg, CreateBubbleNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set popup value to popupParam.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetTargetOffset(POPUP_PARAM_POSITION_OFFSET);

    Dimension radius = 20.0_px;
    Dimension arrowHeight = 20.0_px;
    Dimension arrowWidth = 20.0_px;
    Shadow shadow = ShadowConfig::DefaultShadowL;
    popupParam->SetRadius(radius);
    popupParam->SetTipsFlag(true);
    popupParam->SetArrowHeight(arrowHeight);
    popupParam->SetArrowWidth(arrowWidth);
    popupParam->SetShadow(shadow);

    /**
     * @tc.steps: step2. create BubbleNode with position offset
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    auto popupNode = BubbleView::CreateBubbleNode(targetNode->GetTag(), targetNode->GetId(), popupParam);
    ASSERT_NE(popupNode, nullptr);
    auto firstTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    ASSERT_NE(firstTextNode, nullptr);

    /**
     * @tc.steps: step3. use BubbleLayoutProperty to check PositionOffset.
     * @tc.expected: check whether GetPositionOffset value is correct.
     */
    auto property = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_EQ(property->GetPositionOffset().value(), BUBBLE_POSITION_OFFSET);
    EXPECT_EQ(property->GetRadius().value(), radius);
    EXPECT_EQ(property->GetArrowHeight().value(), arrowHeight);
    EXPECT_EQ(property->GetArrowWidth().value(), arrowWidth);
}
} // namespace OHOS::Ace::NG
