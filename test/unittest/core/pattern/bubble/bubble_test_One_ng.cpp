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
} // namespace OHOS::Ace::NG
