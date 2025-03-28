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
#include <vector>

#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"

#define protected public
#define private public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "Test";
const RectF FIRST_HANDLE_REGION(0, 0, 10, 10);
const RectF SECOND_HANDLE_REGION(10, 10, 10, 10);
const RectF SECOND_HANDLE_REGION2(20, 20, 10, 10);
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const Color COLOR_ALPHA_MASK = Color::FromRGB(255, 100, 100);
const OffsetF offset(10, 10);
constexpr float RK356_HEIGHT = 1136.0f;
const OffsetF OFFSET_ITEM1 = OffsetF(5, 5);
double spaceBetweenText = 2.0f;
const RectF MENU_RECT(100, 300, 100, 1000);
} // namespace

class SelectOverlayTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
    DrawingContext GetDrawingContext(Testing::MockCanvas& canvas);
};

void SelectOverlayTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlayTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

std::vector<MenuOptionsParam> SelectOverlayTestTwoNg::GetMenuOptionItems()
{
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    menuOptionItem1.id = "OH_DEFAULT_CUT";
    MenuOptionsParam menuOptionItem2;
    menuOptionItem2.content = "test2";
    menuOptionItem2.action = [](const std::string&) {};
    menuOptionItem2.id = "OH_DEFAULT_COPY";
    menuOptionItems.emplace_back(menuOptionItem1);
    menuOptionItems.emplace_back(menuOptionItem2);
    return menuOptionItems;
}

DrawingContext SelectOverlayTestTwoNg::GetDrawingContext(Testing::MockCanvas& canvas)
{
    DrawingContext context { canvas, 100, 100 };
    EXPECT_CALL(canvas, Save()).Times(AnyNumber());
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, Translate(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, Restore()).Times(AnyNumber());
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    return context;
}

/**
 * @tc.name: Measure003
 * @tc.desc: Test pattern->GetMode() != SelectOverlayMode::HANDLE_ONLY = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, Measure003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    pattern->overlayMode_ = SelectOverlayMode::ALL;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    selectOverlayLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_NE(safeAreaManager, nullptr);
}

/**
 * @tc.name: AdjustMenuOffsetAtSingleHandleBottom001
 * @tc.desc: shouldAvoidKeyboard = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AdjustMenuOffsetAtSingleHandleBottom001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = RK356_HEIGHT - 1;
    insetBottom.end = RK356_HEIGHT;
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    CHECK_NULL_VOID(pipeline);
    pipeline->safeAreaManager_ = safeAreamanager;
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->isSingleHandle = true;
    OffsetF menuOffset(400, 500);
    node->AdjustMenuOffsetAtSingleHandleBottom(FIRST_HANDLE_REGION, MENU_RECT, menuOffset, spaceBetweenText);
    auto expectRes = FIRST_HANDLE_REGION.Bottom() - spaceBetweenText - MENU_RECT.Height();
    EXPECT_EQ(menuOffset.GetY(), expectRes);
}

/**
 * @tc.name: AdjustMenuOffsetAtSingleHandleBottom002
 * @tc.desc: keyboardInsert.start) = false,
 *           GreatNotEqual(keyboardInsert.Length(), 0.0f) = false GreatNotEqual(menuOffset.GetY() + menuRect.Height()
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AdjustMenuOffsetAtSingleHandleBottom002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    SafeAreaInsets::Inset insetBottom;
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    CHECK_NULL_VOID(pipeline);
    pipeline->safeAreaManager_ = safeAreamanager;
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->isSingleHandle = true;
    OffsetF menuOffset(400, 500);
    node->AdjustMenuOffsetAtSingleHandleBottom(FIRST_HANDLE_REGION, MENU_RECT, menuOffset, spaceBetweenText);
    auto expectRes = FIRST_HANDLE_REGION.Bottom() - spaceBetweenText - MENU_RECT.Height();
    EXPECT_NE(menuOffset.GetY(), expectRes);
}

/**
 * @tc.name: AdjustSelectMenuOffsetWhenHandlesUnshown001
 * @tc.desc: topArea > menuOffset.GetY() = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AdjustSelectMenuOffsetWhenHandlesUnshown001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    SafeAreaInsets::Inset left { 0, 1 };
    SafeAreaInsets::Inset top { 0, 400 };
    SafeAreaInsets::Inset right { 0, 3 };
    SafeAreaInsets::Inset bottom { 0, 4 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);
    pipeline->UpdateSystemSafeArea(safeAreaInsets);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->isSingleHandle = true;
    node->info_->selectArea = { 100, 500, 200, 50 };

    auto result = node->AdjustSelectMenuOffsetWhenHandlesUnshown(MENU_RECT, spaceBetweenText);
    auto expect =
        ((pattern->info_->selectArea.Top() + pattern->info_->selectArea.Bottom() - MENU_RECT.Height()) / 2.0f);
    EXPECT_EQ(result.GetY(), expect);
}

/**
 * @tc.name: AdjustSelectMenuOffsetWhenHandlesUnshown002
 * @tc.desc: !isBottomTouchKeyboard = false shouldAvoidKeyboard = false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AdjustSelectMenuOffsetWhenHandlesUnshown002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = 1335;
    insetBottom.end = 1336;
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    pipeline->safeAreaManager_ = safeAreamanager;
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->isSingleHandle = true;
    node->info_->selectArea = { 100, 500, 200, 800 };
    auto res = node->AdjustSelectMenuOffsetWhenHandlesUnshown(MENU_RECT, spaceBetweenText);
    EXPECT_EQ(res.GetY(), MENU_RECT.GetOffset().GetY());
}

/**
 * @tc.name: AdjustSelectMenuOffsetWhenHandlesUnshown003
 * @tc.desc: shouldAvoidKeyboard = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AdjustSelectMenuOffsetWhenHandlesUnshown003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = RK356_HEIGHT - 1;
    insetBottom.end = RK356_HEIGHT;
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    pipeline->safeAreaManager_ = safeAreamanager;
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->isSingleHandle = true;
    node->info_->selectArea = { 100, 500, 200, 700 };

    auto res = node->AdjustSelectMenuOffsetWhenHandlesUnshown(MENU_RECT, spaceBetweenText);
    auto expect =
        ((pattern->info_->selectArea.Top() + pattern->info_->selectArea.Bottom() - MENU_RECT.Height()) / 2.0f);
    EXPECT_EQ(res.GetY(), expect);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort001
 * @tc.desc: !info_->clipHandleDrawRect = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CheckHandleIsInClipViewPort001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->clipHandleDrawRect = false;
    node->info_->secondHandle.isPaintHandleWithPoints = true;
    node->info_->handleLevelMode = HandleLevelMode::OVERLAY;
    node->info_->isSingleHandle = false;
    node->info_->ancestorViewPort.emplace(RectF(1, 1, 1, 1));
    node->info_->firstHandle.paintRect = RectF(2, 2, 2, 2);
    node->info_->firstHandle.isShow = false;
    node->info_->handleReverse = false;
    EXPECT_FALSE(node->info_->firstHandle.isShow);
    node->CheckHandleIsInClipViewPort();
    EXPECT_FALSE(node->info_->firstHandle.isShow);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort002
 * @tc.desc: info_->secondHandle.isPaintHandleWithPoints = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CheckHandleIsInClipViewPort002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->clipHandleDrawRect = true;
    node->info_->secondHandle.isPaintHandleWithPoints = true;
    node->info_->handleLevelMode = HandleLevelMode::OVERLAY;
    node->info_->isSingleHandle = false;
    node->info_->ancestorViewPort.emplace(RectF(1, 1, 1, 1));
    node->info_->firstHandle.paintRect = RectF(2, 2, 2, 2);
    node->info_->firstHandle.isShow = false;
    node->info_->handleReverse = false;
    EXPECT_FALSE(node->info_->firstHandle.isShow);
    node->CheckHandleIsInClipViewPort();
    EXPECT_FALSE(node->info_->firstHandle.isShow);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort003
 * @tc.desc: info_->secondHandle.isPaintHandleWithPoints = false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CheckHandleIsInClipViewPort003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->clipHandleDrawRect = true;
    node->info_->secondHandle.isPaintHandleWithPoints = false;
    node->info_->handleLevelMode = HandleLevelMode::OVERLAY;
    node->info_->isSingleHandle = true;
    node->info_->ancestorViewPort.emplace(RectF(1, 1, 1, 1));
    node->info_->firstHandle.paintRect = RectF(2, 2, 2, 2);
    node->info_->firstHandle.isShow = false;
    node->info_->handleReverse = false;
    EXPECT_FALSE(node->info_->firstHandle.isShow);
    node->CheckHandleIsInClipViewPort();
    EXPECT_FALSE(node->info_->firstHandle.isShow);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort004
 * @tc.desc: info_->handleLevelMode == HandleLevelMode::EMBED
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CheckHandleIsInClipViewPort004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->clipHandleDrawRect = true;
    node->info_->secondHandle.isPaintHandleWithPoints = false;
    node->info_->handleLevelMode = HandleLevelMode::EMBED;
    node->info_->isSingleHandle = false;
    node->info_->ancestorViewPort.emplace(RectF(1, 1, 1, 1));
    node->info_->firstHandle.paintRect = RectF(2, 2, 2, 2);
    node->info_->firstHandle.isShow = false;
    node->info_->handleReverse = false;
    EXPECT_FALSE(node->info_->firstHandle.isShow);
    node->CheckHandleIsInClipViewPort();
    EXPECT_FALSE(node->info_->firstHandle.isShow);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort005
 * @tc.desc: info_->handleLevelMode != HandleLevelMode::EMBED
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CheckHandleIsInClipViewPort005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->clipHandleDrawRect = true;
    node->info_->secondHandle.isPaintHandleWithPoints = false;
    node->info_->handleLevelMode = HandleLevelMode::OVERLAY;
    node->info_->isSingleHandle = true;
    node->info_->ancestorViewPort.emplace(RectF(1, 1, 1, 1));
    node->info_->firstHandle.paintRect = RectF(2, 2, 2, 2);
    node->info_->firstHandle.isShow = false;
    node->info_->handleReverse = false;
    EXPECT_FALSE(node->info_->firstHandle.isShow);
    node->CheckHandleIsInClipViewPort();
    EXPECT_FALSE(node->info_->firstHandle.isShow);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort006
 * @tc.desc: !info_->isSingleHandle = false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CheckHandleIsInClipViewPort006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->clipHandleDrawRect = true;
    node->info_->secondHandle.isPaintHandleWithPoints = false;
    node->info_->handleLevelMode = HandleLevelMode::OVERLAY;
    node->info_->isSingleHandle = true;
    node->info_->ancestorViewPort.emplace(RectF(1, 1, 1, 1));
    node->info_->firstHandle.paintRect = RectF(2, 2, 2, 2);
    node->info_->firstHandle.isShow = false;
    node->info_->handleReverse = false;
    EXPECT_FALSE(node->info_->firstHandle.isShow);
    node->CheckHandleIsInClipViewPort();
    EXPECT_FALSE(node->info_->firstHandle.isShow);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort007
 * @tc.desc: !info_->isSingleHandle = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CheckHandleIsInClipViewPort007, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->info_->clipHandleDrawRect = true;
    node->info_->secondHandle.isPaintHandleWithPoints = false;
    node->info_->handleLevelMode = HandleLevelMode::OVERLAY;
    node->info_->isSingleHandle = false;
    node->info_->ancestorViewPort.emplace(RectF(1, 1, 1, 1));
    node->info_->firstHandle.paintRect = RectF(2, 2, 2, 2);
    node->info_->firstHandle.isShow = false;
    node->info_->handleReverse = false;
    EXPECT_FALSE(node->info_->firstHandle.isShow);
    node->CheckHandleIsInClipViewPort();
    EXPECT_TRUE(node->info_->firstHandle.isShow);
}

/**
 * @tc.name: UpdateMoreOrBackSymbolOptions001
 * @tc.desc: moreOrBackSymbol_ == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMoreOrBackSymbolOptions001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->UpdateMoreOrBackSymbolOptions(false, true);
    EXPECT_EQ(selectOverlayNode->moreOrBackSymbol_, nullptr);
}

/**
 * @tc.name: UpdateMoreOrBackSymbolOptions002
 * @tc.desc: moreOrBackSymbol_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMoreOrBackSymbolOptions002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->isMoreOrBackSymbolIcon_ = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->moreButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->UpdateMoreOrBackSymbolOptions(true, true);
    EXPECT_NE(selectOverlayNode->moreOrBackSymbol_, nullptr);
    auto parent = selectOverlayNode->moreOrBackSymbol_->GetParent();
    EXPECT_NE(parent, nullptr);
}

/**
 * @tc.name: UpdateMoreOrBackSymbolOptions003
 * @tc.desc: moreOrBackSymbol_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMoreOrBackSymbolOptions003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->isMoreOrBackSymbolIcon_ = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->moreButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->UpdateMoreOrBackSymbolOptions(true, false);
    EXPECT_NE(selectOverlayNode->moreOrBackSymbol_, nullptr);
    auto parent = selectOverlayNode->moreOrBackSymbol_->GetParent();
    EXPECT_NE(parent, nullptr);
}

/**
 * @tc.name: UpdateMoreOrBackSymbolOptionsWithDelay001
 * @tc.desc: UpdateMoreOrBackSymbolOptionsWithDelay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMoreOrBackSymbolOptionsWithDelay001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->isMoreOrBackSymbolIcon_ = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->UpdateMoreOrBackSymbolOptionsWithDelay();
    EXPECT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams001
 * @tc.desc: AddCreateMenuExtensionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AddCreateMenuExtensionMenuParams001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    SelectMenuCallback menuCallback;
    menuCallback.onCut = []() {};
    infoPtr->menuCallback = menuCallback;
    auto menuOptionItems = GetMenuOptionItems();
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->isMoreOrBackSymbolIcon_ = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    EXPECT_NE(selectOverlayNode, nullptr);
    std::vector<OptionParam> params;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(menuOptionItems, infoPtr, 1, params);
    EXPECT_EQ(params.size(), 1);
}

/**
 * @tc.name: UpdateMainWindowOffset001
 * @tc.desc: UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMainWindowOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    pattern->SetIsMenuShowInSubWindow(false);

    /**
     * @tc.steps: step3. Call SelectOverlayLayoutAlgorithm UpdateMainWindowOffset
     */
    auto selectOverlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    selectOverlayLayoutAlgorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->mainWindowOffset_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->containerModalOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: UpdateMainWindowOffset002
 * @tc.desc: UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMainWindowOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    pattern->SetIsMenuShowInSubWindow(true);
    auto containerId = -1;
    pattern->SetContainerId(containerId);

    /**
     * @tc.steps: step3. Call SelectOverlayLayoutAlgorithm UpdateMainWindowOffset
     */
    auto selectOverlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    selectOverlayLayoutAlgorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->mainWindowOffset_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->containerModalOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: UpdateMainWindowOffset003
 * @tc.desc: UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMainWindowOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    pattern->SetIsMenuShowInSubWindow(true);
    auto containerId = 100000;
    pattern->SetContainerId(containerId);

    /**
     * @tc.steps: step3. Call SelectOverlayLayoutAlgorithm UpdateMainWindowOffset
     */
    auto selectOverlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    selectOverlayLayoutAlgorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->mainWindowOffset_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->containerModalOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: UpdateMainWindowOffset004
 * @tc.desc: UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateMainWindowOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    pattern->SetIsMenuShowInSubWindow(true);
    auto containerId = 100000;
    pattern->SetContainerId(containerId);

    /**
     * @tc.steps: step3. Mock theme
     */
    auto selectOverlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    /**
     * @tc.steps: step4. Call SelectOverlayLayoutAlgorithm UpdateMainWindowOffset
     */
    selectOverlayLayoutAlgorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->mainWindowOffset_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(selectOverlayLayoutAlgorithm->containerModalOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: GetIsMenuShowInSubWindow001
 * @tc.desc: GetIsMenuShowInSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, GetIsMenuShowInSubWindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    pattern->SetIsMenuShowInSubWindow(true);

    /**
     * @tc.steps: step3. Call SelectOverlayLayoutAlgorithm GetIsMenuShowInSubWindow
     */
    auto selectOverlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    EXPECT_EQ(selectOverlayLayoutAlgorithm->GetIsMenuShowInSubWindow(AceType::RawPtr(layoutWrapper)), true);
}

/**
 * @tc.name: GetIsMenuShowInSubWindow002
 * @tc.desc: GetIsMenuShowInSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, GetIsMenuShowInSubWindow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    pattern->SetIsMenuShowInSubWindow(false);

    /**
     * @tc.steps: step3. Call SelectOverlayLayoutAlgorithm GetIsMenuShowInSubWindow
     */
    auto selectOverlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    EXPECT_EQ(selectOverlayLayoutAlgorithm->GetIsMenuShowInSubWindow(AceType::RawPtr(layoutWrapper)), false);
}

/**
 * @tc.name: BuildButtonPasteButton
 * @tc.desc: Test BuildButtonPasteButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, BuildButtonPasteButton, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    float maxWidth = 3.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() {
        pasteCount++;
    };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    /**
     * @tc.steps: step2. call ShowPaste.
     */
    selectOverlayNode->isDefaultBtnOverMaxWidth_ = false;
    std::string pasteLabel = "粘贴";
    selectOverlayNode->ShowPaste(maxWidth, allocatedSize, infoPtr, pasteLabel);
    
    auto button = AceType::DynamicCast<FrameNode>(selectOverlayNode->selectMenuInner_->GetLastChild());
    EXPECT_NE(button, nullptr);
    auto gestureEventHubPtr = button->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHubPtr, nullptr);
    if (gestureEventHubPtr->clickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->clickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }

    if (gestureEventHubPtr->userParallelClickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->userParallelClickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }
    EXPECT_EQ(pasteCount, 0);
}

/**
 * @tc.name: AddCreateMenuItems
 * @tc.desc: Test AddCreateMenuItems different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AddCreateMenuItems, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) {
        return true;
    };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {
    };
    float maxWidth = 3.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    /**
     * @tc.steps: step2. call AddCreateMenuItems.
     */
    selectOverlayNode->isDefaultBtnOverMaxWidth_ = false;
    std::vector<NG::MenuOptionsParam> menuItems = { { .id = "OH_DEFAULT_PASTE" } };
    selectOverlayNode->AddCreateMenuItems(menuItems, infoPtr, maxWidth);

    auto button = AceType::DynamicCast<FrameNode>(selectOverlayNode->selectMenuInner_->GetLastChild());
    EXPECT_NE(button, nullptr);
    auto gestureEventHubPtr = button->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHubPtr, nullptr);
    if (gestureEventHubPtr->clickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->clickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }

    if (gestureEventHubPtr->userParallelClickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->userParallelClickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }
    EXPECT_EQ(pasteCount, 0);
}

/**
 * @tc.name: OnCustomSelectMenuAppear
 * @tc.desc: Test OnCustomSelectMenuAppear.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, OnCustomSelectMenuAppear, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto overlayEventHub = selectOverlayNode->GetEventHub<SelectOverlayEventHub>();
    EXPECT_NE(overlayEventHub, nullptr);
    bool isAppear = false;
    bool isMenuShow = false;
    bool isMenuHide = false;
    overlayEventHub->SetMenuAppearCallback([&]() { isAppear = true; });
    overlayEventHub->SetMenuShowCallback([&]() { isMenuShow = true; });
    overlayEventHub->SetMenuHideCallback([&]() { isMenuHide = true; });
    /**
     * @tc.steps: step2. call OnCustomSelectMenuAppear.
     */
    selectOverlayNode->isDefaultBtnOverMaxWidth_ = false;
    selectOverlayNode->OnCustomSelectMenuAppear();
    EXPECT_TRUE(selectOverlayNode->isCustomMenuAppear_);
    EXPECT_TRUE(isAppear);
    EXPECT_TRUE(isMenuShow);
    infoPtr->menuInfo.menuIsShow = false;
    overlayEventHub->lastMenuIsShow_.reset();
    selectOverlayNode->OnCustomSelectMenuAppear();
    EXPECT_TRUE(isMenuHide);
}

/**
 * @tc.name: FireCustomMenuChangeEvent
 * @tc.desc: Test FireCustomMenuChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, FireCustomMenuChangeEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto overlayEventHub = selectOverlayNode->GetEventHub<SelectOverlayEventHub>();
    EXPECT_NE(overlayEventHub, nullptr);
    bool isMenuShow = false;
    bool isMenuHide = false;
    overlayEventHub->SetMenuShowCallback([&]() { isMenuShow = true; });
    overlayEventHub->SetMenuHideCallback([&]() { isMenuHide = true; });
    /**
     * @tc.steps: step2. call FireCustomMenuChangeEvent.
     */
    selectOverlayNode->OnCustomSelectMenuAppear();
    EXPECT_TRUE(selectOverlayNode->isCustomMenuAppear_);
    selectOverlayNode->FireCustomMenuChangeEvent(true);
    EXPECT_TRUE(isMenuShow);
    selectOverlayNode->FireCustomMenuChangeEvent(false);
    EXPECT_TRUE(isMenuHide);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuOptions
 * @tc.desc: Test AddCreateMenuExtensionMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AddCreateMenuExtensionMenuOptions, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return AceType::MakeRefPtr<TextOverlayTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        }
        return AceType::MakeRefPtr<TextOverlayTheme>();
    });
    /**
     * @tc.steps: step2. call AddCreateMenuExtensionMenuOptions.
     */
    std::vector<MenuOptionsParam> params = {
        { .id = "OH_DEFAULT_CUT" },
        { .id = "OH_DEFAULT_COPY" },
        { .id = "OH_DEFAULT_PASTE" },
        { .id = "OH_DEFAULT_SELECT_ALL" },
        { .id = "OH_DEFAULT_TRANSLATE" },
        { .id = "OH_DEFAULT_SEARCH" },
        { .id = "OH_DEFAULT_SHARE" },
        { .id = "OH_DEFAULT_CAMERA_INPUT" },
        { .id = "OH_DEFAULT_AI_WRITE" },
        { .id = "DEFAULT" },
    };
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->AddCreateMenuExtensionMenuOptions(params, infoPtr, 0);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
}

/**
 * @tc.name: CreateMenuNode
 * @tc.desc: Test CreateMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CreateMenuNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        std::transform(params.begin(), params.end(), std::back_inserter(paramlist),
            [](NG::MenuItemParam item) { return item.menuOptionsParam; });
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return AceType::MakeRefPtr<TextOverlayTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        }
        return AceType::MakeRefPtr<TextOverlayTheme>();
    });
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    /**
     * @tc.steps: step2. call CreateMenuNode.
     */
    infoPtr->menuInfo.showCopy = true;
    infoPtr->menuInfo.showPaste = true;
    infoPtr->menuInfo.showCut = true;
    infoPtr->menuInfo.showCopyAll = true;
    infoPtr->menuInfo.showTranslate = true;
    infoPtr->menuInfo.showSearch = true;
    infoPtr->menuInfo.showCameraInput = true;
    infoPtr->menuInfo.showAIWrite = true;
    infoPtr->isUsingMouse = false;
    auto menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
    infoPtr->menuInfo.showCopy = false;
    infoPtr->menuInfo.showPaste = false;
    infoPtr->menuInfo.showCut = false;
    infoPtr->menuInfo.showCopyAll = false;
    infoPtr->menuInfo.showTranslate = false;
    infoPtr->menuInfo.showSearch = false;
    infoPtr->menuInfo.showCameraInput = false;
    infoPtr->menuInfo.showAIWrite = false;
    infoPtr->isUsingMouse = true;
    menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
    infoPtr->isUsingMouse = false;
    menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
}

/**
 * @tc.name: UpdateToolBar
 * @tc.desc: Test UpdateToolBar.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateToolBar, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuBuilder = nullptr;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showAIWrite = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        std::transform(params.begin(), params.end(), std::back_inserter(paramlist),
            [](NG::MenuItemParam item) { return item.menuOptionsParam; });
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return AceType::MakeRefPtr<TextOverlayTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        }
        return AceType::MakeRefPtr<TextOverlayTheme>();
    });

    /**
     * @tc.steps: step2. call UpdateToolBar.
     */
    selectOverlayNode->isExtensionMenu_ = true;
    selectOverlayNode->extensionMenu_ = FrameNode::GetOrCreateFrameNode("ExtensionMenu",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    infoPtr->menuInfo.menuDisable = true;
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("BackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->UpdateToolBar(true, true);
    selectOverlayNode->extensionMenu_ = nullptr;
    selectOverlayNode->UpdateToolBar(true, true);
    selectOverlayNode->isExtensionMenu_ = false;
    selectOverlayNode->UpdateToolBar(true, true);

    infoPtr->onCreateCallback.onCreateMenuCallback = nullptr;
    selectOverlayNode->isDefaultBtnOverMaxWidth_ = false;
    selectOverlayNode->UpdateToolBar(true, true);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE);
}

/**
 * @tc.name: MeasureChild
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::MeasureChild
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, MeasureChild, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    frameNode->GetAllChildrenWithBuild();
    auto customMenuLayoutWrapper = frameNode->GetChildByIndex(0);
    ASSERT_NE(customMenuLayoutWrapper, nullptr);
    auto customNode = AceType::DynamicCast<FrameNode>(customMenuLayoutWrapper);
    ASSERT_NE(customNode, nullptr);
    customNode->isLayoutComplete_ = true;
    /**
     * @tc.steps: step2. call MeasureChild.
     */
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    overlayLayoutAlgorithm->MeasureChild(AceType::RawPtr(frameNode));
    EXPECT_FALSE(customNode->isLayoutComplete_);
}

/**
 * @tc.name: CalculateCustomMenuByMouseOffset
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::CalculateCustomMenuByMouseOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CalculateCustomMenuByMouseOffset, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    frameNode->GetAllChildrenWithBuild();
    auto customMenuLayoutWrapper = frameNode->GetChildByIndex(0);
    ASSERT_NE(customMenuLayoutWrapper, nullptr);
    auto customNode = AceType::DynamicCast<FrameNode>(customMenuLayoutWrapper);
    ASSERT_NE(customNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF constraint = {
        .selfIdealSize = OptionalSizeF(100.0f, 100.0f)
    };
    layoutProperty->layoutConstraint_ = constraint;
    auto menu = frameNode->GetChildByIndex(0);
    ASSERT_NE(menu, nullptr);
    menu->GetGeometryNode()->SetFrameWidth(101.0f);
    menu->GetGeometryNode()->SetFrameHeight(101.0f);
    infoPtr->rightClickOffset = OffsetF(102.0f, 100);
    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    auto offset = overlayLayoutAlgorithm->CalculateCustomMenuByMouseOffset(AceType::RawPtr(frameNode));
    EXPECT_EQ(offset.GetX(), 1.0f);
    EXPECT_EQ(offset.GetY(), 49.5f);
    infoPtr->rightClickOffset = OffsetF(50.0f, 50.f);
    menu->GetGeometryNode()->SetFrameHeight(60.0f);
    menu->GetGeometryNode()->SetFrameWidth(80.0f);
    offset = overlayLayoutAlgorithm->CalculateCustomMenuByMouseOffset(AceType::RawPtr(frameNode));
    EXPECT_EQ(offset.GetX(), 20.0f);
    EXPECT_EQ(offset.GetY(), 39.0f);
    infoPtr->rightClickOffset = OffsetF(80.0f, 50.f);
    menu->GetGeometryNode()->SetFrameHeight(-60.0f);
    menu->GetGeometryNode()->SetFrameWidth(140.0f);
    EXPECT_EQ(offset.GetX(), 20.0f);
    EXPECT_EQ(offset.GetY(), 39.0f);
}

/**
 * @tc.name: AdjustMenuTooFarAway
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::AdjustMenuTooFarAway
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AdjustMenuTooFarAway, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    frameNode->GetAllChildrenWithBuild();
    auto customMenuLayoutWrapper = frameNode->GetChildByIndex(0);
    ASSERT_NE(customMenuLayoutWrapper, nullptr);
    auto customNode = AceType::DynamicCast<FrameNode>(customMenuLayoutWrapper);
    ASSERT_NE(customNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF constraint = { .selfIdealSize = OptionalSizeF(100.0f, 100.0f) };
    layoutProperty->layoutConstraint_ = constraint;
    auto menu = frameNode->GetChildByIndex(0);
    ASSERT_NE(menu, nullptr);
    menu->GetGeometryNode()->SetFrameWidth(101.0f);
    menu->GetGeometryNode()->SetFrameHeight(101.0f);
    infoPtr->rightClickOffset = OffsetF(102.0f, 100);
    auto callerNode = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    callerNode->GetGeometryNode()->SetFrameWidth(5);
    callerNode->GetGeometryNode()->SetFrameHeight(100);
    infoPtr->callerFrameNode = AceType::WeakClaim(AceType::RawPtr(callerNode));
    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    OffsetF menuOffset;
    RectF menuRect = RectF(OffsetF(10.0f, 10.0f), SizeF(20.0f, 20.0));
    overlayLayoutAlgorithm->AdjustMenuTooFarAway(AceType::RawPtr(frameNode), menuOffset, menuRect);
    EXPECT_EQ(menuOffset.GetX(), -5.0f);
    callerNode->GetGeometryNode()->SetFrameWidth(30);
    menuRect.SetLeft(-15);
    overlayLayoutAlgorithm->AdjustMenuTooFarAway(AceType::RawPtr(frameNode), menuOffset, menuRect);
    EXPECT_EQ(menuOffset.GetX(), -10.0f);
}

/**
 * @tc.name: ComputeExtensionMenuPosition
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::ComputeExtensionMenuPosition
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, ComputeExtensionMenuPosition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto childNode = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto childNode1 = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto childNode2 = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    childNode->MountToParent(frameNode);
    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);
    frameNode->GetAllChildrenWithBuild();
    auto customMenuLayoutWrapper = frameNode->GetChildByIndex(0);
    ASSERT_NE(customMenuLayoutWrapper, nullptr);
    auto customNode = AceType::DynamicCast<FrameNode>(customMenuLayoutWrapper);
    ASSERT_NE(customNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF constraint = { .selfIdealSize = OptionalSizeF(100.0f, 100.0f) };
    layoutProperty->layoutConstraint_ = constraint;
    auto menu = frameNode->GetChildByIndex(0);
    ASSERT_NE(menu, nullptr);
    /**
     * @tc.steps: step2. Update selectOverlayPattern properties.
     */
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    OffsetF menuOffset;
    auto offset = overlayLayoutAlgorithm->ComputeExtensionMenuPosition(AceType::RawPtr(frameNode), menuOffset);
    EXPECT_EQ(offset.GetY(), -8.0f);
    overlayLayoutAlgorithm->defaultMenuEndOffset_ = OffsetF(0.0f, 10.0f);
    offset = overlayLayoutAlgorithm->ComputeExtensionMenuPosition(AceType::RawPtr(frameNode), menuOffset);
    EXPECT_EQ(offset.GetY(), 2.0f);
}

/**
 * @tc.name: CreateExtensionMenuOptionCallback
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::CreateExtensionMenuOptionCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, CreateExtensionMenuOptionCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto childNode = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto childNode1 = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto childNode2 = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    childNode->MountToParent(frameNode);
    childNode1->MountToParent(frameNode);
    childNode2->MountToParent(frameNode);
    frameNode->GetAllChildrenWithBuild();
    auto customMenuLayoutWrapper = frameNode->GetChildByIndex(0);
    ASSERT_NE(customMenuLayoutWrapper, nullptr);
    auto customNode = AceType::DynamicCast<FrameNode>(customMenuLayoutWrapper);
    ASSERT_NE(customNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF constraint = { .selfIdealSize = OptionalSizeF(100.0f, 100.0f) };
    layoutProperty->layoutConstraint_ = constraint;
    auto menu = frameNode->GetChildByIndex(0);
    ASSERT_NE(menu, nullptr);
    /**
     * @tc.steps: step2. call CreateExtensionMenuOptionCallback.
     */
    OnMenuItemCallback onCreateCallback = { .onMenuItemClick = [](const NG::MenuItemParam& param) {
        return false;
    } };
    std::function<void()> systemEvent = nullptr;
    MenuOptionsParam item;
    auto callback = selectOverlayNode->CreateExtensionMenuOptionCallback(0, onCreateCallback, systemEvent, item);
    callback();

    onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    int32_t retStart = 0;
    int32_t retEnd = 0;
    onCreateCallback.textRangeCallback = [&](int32_t start, int32_t end) {
        retStart = start;
        retEnd = end;
    };
    callback = selectOverlayNode->CreateExtensionMenuOptionCallback(0, onCreateCallback, systemEvent, item);
    callback();
    EXPECT_EQ(retStart, -1);
    EXPECT_EQ(retEnd, -1);

    bool isSystemEventCalled = false;
    systemEvent = [&]() { isSystemEventCalled = true; };
    callback = selectOverlayNode->CreateExtensionMenuOptionCallback(0, onCreateCallback, systemEvent, item);
    callback();
    EXPECT_FALSE(isSystemEventCalled);

    onCreateCallback.onMenuItemClick = nullptr;
    callback = selectOverlayNode->CreateExtensionMenuOptionCallback(0, onCreateCallback, systemEvent, item);
    callback();
    EXPECT_TRUE(isSystemEventCalled);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::AddCreateMenuExtensionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, AddCreateMenuExtensionMenuParams, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onSearch = []() {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto childNode = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    /**
     * @tc.steps: step2. call AddCreateMenuExtensionMenuParams.
     */
    std::vector<MenuOptionsParam> params = {
        { .id = "OH_DEFAULT_SEARCH", .content = "Search" },
        { .id = "OH_DEFAULT_PASTE", .content = "Paste" },
        { .id = "NONE", .content = "NONE" },
    };
    std::vector<OptionParam> optParams;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(params, infoPtr, -1, optParams);
    ASSERT_EQ(static_cast<int32_t>(optParams.size()), 3);
    auto it = optParams.begin();
    EXPECT_NE((*(it)).action, nullptr);
    it++;
    EXPECT_TRUE((*(it)).isPasteOption);
    it++;
    EXPECT_EQ((*(it)).value, "NONE");
}

/**
 * @tc.name: UpdateToolBarExtensionMenu
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::UpdateToolBar
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestTwoNg, UpdateToolBarExtensionMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onSearch = []() {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto childNode = FrameNode::GetOrCreateFrameNode(
        "Text", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    /**
     * @tc.steps: step2. call AddCreateMenuExtensionMenuParams.
     */
    selectOverlayNode->isExtensionMenu_ = true;
    selectOverlayNode->extensionMenu_ = childNode;
    selectOverlayNode->backButton_ = childNode;
    selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONE;
    infoPtr->menuInfo.menuIsShow = true;
    infoPtr->menuInfo.menuDisable = false;
    selectOverlayNode->UpdateToolBar(false, false);
    EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::VISIBLE);

    infoPtr->menuInfo.menuIsShow = false;
    selectOverlayNode->UpdateToolBar(false, false);
    EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::GONE);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::GONE);

    infoPtr->menuInfo.menuDisable = true;
    selectOverlayNode->backButton_ = nullptr;
    selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->UpdateToolBar(false, false);
    EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::GONE);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::GONE);
}  
} // namespace OHOS::Ace::NG
