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
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlayTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
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
} // namespace OHOS::Ace::NG
