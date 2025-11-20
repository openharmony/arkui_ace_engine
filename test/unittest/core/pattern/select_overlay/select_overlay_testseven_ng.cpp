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
#include <vector>
#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "ui/base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
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
int32_t callBackFlag = 0;
const OffsetF OFFSET_ITEM1 = OffsetF(5, 5);
const RectF MENU_RECT(100, 300, 100, 1000);
constexpr float CUSTOM_MENU_HEIGHT_CONSTRAINT_FACTOR = 0.8;
} // namespace

class SelectOverlaySevenTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
    DrawingContext GetDrawingContext(Testing::MockCanvas& canvas);
    void InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme);
};

void SelectOverlaySevenTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlaySevenTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

std::vector<MenuOptionsParam> SelectOverlaySevenTestNg::GetMenuOptionItems()
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

DrawingContext SelectOverlaySevenTestNg::GetDrawingContext(Testing::MockCanvas& canvas)
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

void SelectOverlaySevenTestNg::InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme)
{
    CHECK_NULL_VOID(textOverlayTheme);
    textOverlayTheme->cutLabel_ = "剪切";
    textOverlayTheme->copyLabel_ = "复制";
    textOverlayTheme->pasteLabel_ = "粘贴";
    textOverlayTheme->selectAllLabel_ = "全选";
    textOverlayTheme->translateLabel_ = "翻译";
    textOverlayTheme->shareLabel_ = "分享";
    textOverlayTheme->searchLabel_ = "搜索";
    textOverlayTheme->cameraInput_ = "拍摄输入";
    textOverlayTheme->aiWrite_ = "小艺帮写";
}

/**
 * @tc.name: LayoutChild005
 * @tc.desc: Test LayoutChild with menuInfo.menuIsShow false and mode not MENU_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, LayoutChild005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = true;
    selectInfo.isUsingMouse = false;
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.menuInfo.menuDisable = false;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu and button children
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);
    node->LayoutChild(AceType::RawPtr(layoutWrapper), SelectOverlayMode::ALL);

    // Extension menu should be false
    EXPECT_FALSE(node->hasExtensionMenu_);
}

/**
 * @tc.name: LayoutChild006
 * @tc.desc: Test LayoutChild with menuInfo.menuIsShow true and menu width > height
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, LayoutChild006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = true;
    selectInfo.isUsingMouse = false;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.menuDisable = false;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu and button children
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->MountToParent(frameNode);

    // Set geometry sizes
    auto menuGeometry = menuNode->GetGeometryNode();
    menuGeometry->SetPreFrameSize(SizeF(100.0f, 50.0f)); // Width > Height

    auto buttonGeometry = buttonNode->GetGeometryNode();
    buttonGeometry->SetPreFrameSize(SizeF(30.0f, 30.0f));

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);
    node->LayoutChild(AceType::RawPtr(layoutWrapper), SelectOverlayMode::MENU_ONLY);

    // Extension menu should be true
    EXPECT_FALSE(node->hasExtensionMenu_);
}

/**
 * @tc.name: IsReverseLayout002
 * @tc.desc: Test IsReverseLayout with LTR layout direction
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsReverseLayout002, TestSize.Level1)
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

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->layoutDirection_ = TextDirection::LTR;

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    EXPECT_FALSE(node->IsReverseLayout(AceType::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea005
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height greater than menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsMenuAreaSmallerHandleArea005, TestSize.Level1)
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

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    RectF handleRect(0.0f, 0.0f, 10.0f, 50.0f); // Height = 50
    float menuHeight = 30.0f;
    float menuDistance = 10.0f;

    // 50 > 30 + 10 = 40, should return true (greater)
    EXPECT_TRUE(node->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea006
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height equal to menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsMenuAreaSmallerHandleArea006, TestSize.Level1)
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

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    RectF handleRect(0.0f, 0.0f, 10.0f, 40.0f); // Height = 40
    float menuHeight = 30.0f;
    float menuDistance = 10.0f;

    // 40 > 30 + 10 = 40, should return false (not greater)
    EXPECT_FALSE(node->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea007
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height less than menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsMenuAreaSmallerHandleArea007, TestSize.Level1)
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

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    RectF handleRect(0.0f, 0.0f, 10.0f, 30.0f); // Height = 30
    float menuHeight = 30.0f;
    float menuDistance = 10.0f;

    // 30 > 30 + 10 = 40, should return false (not greater)
    EXPECT_FALSE(node->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea004
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height equal to menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsMenuAreaSmallerHandleArea004, TestSize.Level1)
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

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    RectF handleRect(0.0f, 0.0f, 10.0f, 40.0f); // Height = 40
    float menuHeight = 30.0f;
    float menuDistance = 10.0f;

    // 40 > 30 + 10 = 40, should return false (not greater)
    EXPECT_FALSE(node->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea008
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height equal to menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsMenuAreaSmallerHandleArea008, TestSize.Level1)
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

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    RectF handleRect(0.0f, 0.0f, 10.0f, 40.0f); // Height = 40
    float menuHeight = 30.0f;
    float menuDistance = 10.0f;

    // 40 > 30 + 10 = 40, should return false (not greater)
    EXPECT_FALSE(node->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: CheckHideBackOrMoreButton001
 * @tc.desc: Test CheckHideBackOrMoreButton with intersecting rectangles
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, CheckHideBackOrMoreButton001, TestSize.Level1)
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

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);

    // Create mock layout wrappers
    auto extensionMenuWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto buttonWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // Set geometry nodes with intersecting rectangles
    extensionMenuWrapper->GetGeometryNode()->SetFrameOffset(OffsetF(0.0f, 0.0f));
    extensionMenuWrapper->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 100.0f));
    buttonWrapper->GetGeometryNode()->SetFrameOffset(OffsetF(50.0f, 50.0f));
    buttonWrapper->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 100.0f));

    node->CheckHideBackOrMoreButton(extensionMenuWrapper, buttonWrapper);
    EXPECT_TRUE(node->GetHideMoreOrBack());
}

/**
 * @tc.name: CheckHideBackOrMoreButton002
 * @tc.desc: Test CheckHideBackOrMoreButton with non-intersecting rectangles
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, CheckHideBackOrMoreButton002, TestSize.Level1)
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

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    node->hideMoreOrBack_ = false; // Reset to false

    // Create mock layout wrappers
    auto extensionMenuWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto buttonWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // Set geometry nodes with non-intersecting rectangles
    extensionMenuWrapper->GetGeometryNode()->SetFrameOffset(OffsetF(0.0f, 0.0f));
    extensionMenuWrapper->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 100.0f));
    buttonWrapper->GetGeometryNode()->SetFrameOffset(OffsetF(150.0f, 150.0f));
    buttonWrapper->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 100.0f));
    node->CheckHideBackOrMoreButton(extensionMenuWrapper, buttonWrapper);
    EXPECT_TRUE(node->GetHideMoreOrBack());
}

/**
 * @tc.name: SelectOverlayNodeTest001
 * @tc.desc: Test SelectOverlayNode DispatchVisibleState with different triggers.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Test FrameNodeTrigger::HIDE
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLE;
    selectOverlayNode->DispatchVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDE);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE);

    // Test other triggers (FrameNodeTrigger::SHOW, FrameNodeTrigger::SHOWN, FrameNodeTrigger::HIDDEN)
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLE;
    selectOverlayNode->DispatchVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);

    selectOverlayNode->DispatchVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOWN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);

    selectOverlayNode->DispatchVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDDEN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);
}

/**
 * @tc.name: SelectOverlayNodeTest002
 * @tc.desc: Test SelectOverlayNode DispatchVisibleToGoneState with different triggers.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Test FrameNodeTrigger::SHOW
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE; // 正确设置初始状态
    selectOverlayNode->DispatchVisibleToGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);

    // Test FrameNodeTrigger::HIDDEN
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE; // 正确设置初始状态
    selectOverlayNode->DispatchVisibleToGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDDEN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE);

    // Test other triggers (FrameNodeTrigger::SHOWN, FrameNodeTrigger::HIDE)
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE; // 正确设置初始状态
    selectOverlayNode->DispatchVisibleToGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOWN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLETOGONE); // Should remain unchanged

    selectOverlayNode->DispatchVisibleToGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDE);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLETOGONE); // Should remain unchanged
}

/**
 * @tc.name: SelectOverlayNodeTest003
 * @tc.desc: Test SelectOverlayNode DispatchGoneState with different triggers.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Test FrameNodeTrigger::SHOW
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->DispatchGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);

    // Test FrameNodeTrigger::HIDDEN
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->DispatchGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDDEN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE);

    // Test other triggers (FrameNodeTrigger::SHOWN, FrameNodeTrigger::HIDE)
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->DispatchGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOWN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE); // Should remain unchanged

    selectOverlayNode->DispatchGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDE);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE); // Should remain unchanged
}

/**
 * @tc.name: SelectOverlayNodeTest004
 * @tc.desc: Test SelectOverlayNode DispatchGoneToVisibleState with different triggers.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Test FrameNodeTrigger::SHOWN
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONETOVISIBLE; // 确保初始状态正确
    selectOverlayNode->DispatchGoneToVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOWN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);

    // Test FrameNodeTrigger::HIDE
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONETOVISIBLE; // 确保初始状态正确
    selectOverlayNode->DispatchGoneToVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDE);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE);

    // Test other triggers (FrameNodeTrigger::SHOW, FrameNodeTrigger::HIDDEN)
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONETOVISIBLE; // 确保初始状态正确
    selectOverlayNode->DispatchGoneToVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONETOVISIBLE); // Should remain unchanged

    selectOverlayNode->DispatchGoneToVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDDEN);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONETOVISIBLE); // Should remain unchanged
}

/**
 * @tc.name: SelectOverlayNodeTest005
 * @tc.desc: Test SelectOverlayNode SetFrameNodeStatus with different node types.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Test FrameNodeType::SELECTMENU
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::SELECTMENU, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);

    // Test FrameNodeType::EXTENSIONMENU
    selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::EXTENSIONMENU, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::VISIBLE);

    // Test FrameNodeType::BACKBUTTON
    selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::BACKBUTTON, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::VISIBLE);

    // Test FrameNodeType::MENUONLY
    selectOverlayNode->menuOnlyStatus_ = FrameNodeStatus::GONE;
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::MENUONLY, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->menuOnlyStatus_, FrameNodeStatus::VISIBLE);

    // Test invalid node type
    selectOverlayNode->SetFrameNodeStatus(static_cast<FrameNodeType>(100), FrameNodeStatus::VISIBLE);
    // Should not crash and all statuses should remain unchanged
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->menuOnlyStatus_, FrameNodeStatus::VISIBLE);
}

/**
 * @tc.name: SelectOverlayNodeTest006
 * @tc.desc: Test SelectOverlayNode SetFrameNodeVisibility with different node types.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Ensure all nodes exist - 创建工具栏确保节点存在
    selectOverlayNode->CreateToolBar();
    ASSERT_NE(selectOverlayNode->selectMenu_, nullptr);
    // 创建backButton_节点以确保其存在
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(selectOverlayNode->backButton_, nullptr);

    // Test FrameNodeType::SELECTMENU
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::SELECTMENU, VisibleType::INVISIBLE);
    EXPECT_EQ(selectOverlayNode->selectMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::INVISIBLE);

    // Test FrameNodeType::EXTENSIONMENU
    // 注意：extensionMenu_可能为nullptr，只有在特定条件下才会创建
    if (selectOverlayNode->extensionMenu_ != nullptr) {
        selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::EXTENSIONMENU, VisibleType::INVISIBLE);
        EXPECT_EQ(selectOverlayNode->extensionMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::INVISIBLE);
    }

    // Test FrameNodeType::BACKBUTTON
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::BACKBUTTON, VisibleType::INVISIBLE);
    EXPECT_EQ(selectOverlayNode->backButton_->GetLayoutProperty()->GetVisibility(), VisibleType::INVISIBLE);

    // Test FrameNodeType::MENUONLY
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::MENUONLY, VisibleType::INVISIBLE);
    EXPECT_EQ(selectOverlayNode->GetLayoutProperty()->GetVisibility(), VisibleType::INVISIBLE);

    // Test invalid node type
    selectOverlayNode->SetFrameNodeVisibility(static_cast<FrameNodeType>(100), VisibleType::GONE);
    // Should not crash
}

/**
 * @tc.name: SelectOverlayNodeTest007
 * @tc.desc: Test SelectOverlayNode SetFrameNodeOpacity with different node types.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest007, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Ensure all nodes exist - 创建工具栏确保节点存在
    selectOverlayNode->CreateToolBar();
    ASSERT_NE(selectOverlayNode->selectMenu_, nullptr);
    // 创建backButton_节点以确保其存在
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(selectOverlayNode->backButton_, nullptr);

    // Test FrameNodeType::SELECTMENU
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::SELECTMENU, 0.5);
    EXPECT_EQ(selectOverlayNode->selectMenu_->GetRenderContext()->GetOpacity().value_or(1.0), 0.5);

    // Test FrameNodeType::EXTENSIONMENU
    // 注意：extensionMenu_可能为nullptr，只有在特定条件下才会创建
    if (selectOverlayNode->extensionMenu_ != nullptr) {
        selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::EXTENSIONMENU, 0.6);
        EXPECT_EQ(selectOverlayNode->extensionMenu_->GetRenderContext()->GetOpacity().value_or(1.0), 0.6);
    }

    // Test FrameNodeType::BACKBUTTON
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::BACKBUTTON, 0.7);
    EXPECT_NEAR(selectOverlayNode->backButton_->GetRenderContext()->GetOpacity().value_or(1.0), 0.7, 0.001);

    // Test FrameNodeType::MENUONLY
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::MENUONLY, 0.9);
    EXPECT_NEAR(selectOverlayNode->GetRenderContext()->GetOpacity().value_or(1.0), 0.9, 0.001);

    // Test invalid node type
    selectOverlayNode->SetFrameNodeOpacity(static_cast<FrameNodeType>(100), 0.1);
    // Should not crash
}

/**
 * @tc.name: SelectOverlayNodeTest008
 * @tc.desc: Test SelectOverlayNode HideFrameNodeImmediately with different node types.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest008, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // Ensure all nodes exist - 创建工具栏确保节点存在
    selectOverlayNode->CreateToolBar();
    ASSERT_NE(selectOverlayNode->selectMenu_, nullptr);
    // 创建backButton_节点以确保其存在
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(selectOverlayNode->backButton_, nullptr);

    // Test FrameNodeType::SELECTMENU
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLE;
    selectOverlayNode->HideFrameNodeImmediately(FrameNodeType::SELECTMENU);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE);
    EXPECT_EQ(selectOverlayNode->selectMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);

    // Test FrameNodeType::EXTENSIONMENU
    // 注意：extensionMenu_可能为nullptr，只有在特定条件下才会创建
    if (selectOverlayNode->extensionMenu_ != nullptr) {
        selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::VISIBLE;
        selectOverlayNode->HideFrameNodeImmediately(FrameNodeType::EXTENSIONMENU);
        EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::GONE);
        EXPECT_EQ(selectOverlayNode->extensionMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);
    }

    // Test FrameNodeType::BACKBUTTON
    selectOverlayNode->backButtonStatus_ = FrameNodeStatus::VISIBLE;
    selectOverlayNode->HideFrameNodeImmediately(FrameNodeType::BACKBUTTON);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::GONE);
    EXPECT_EQ(selectOverlayNode->backButton_->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);

    // Test FrameNodeType::MENUONLY
    selectOverlayNode->menuOnlyStatus_ = FrameNodeStatus::VISIBLE;
    selectOverlayNode->HideFrameNodeImmediately(FrameNodeType::MENUONLY);
    EXPECT_EQ(selectOverlayNode->menuOnlyStatus_, FrameNodeStatus::GONE);
    EXPECT_EQ(selectOverlayNode->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);

    // Test invalid node type
    selectOverlayNode->HideFrameNodeImmediately(static_cast<FrameNodeType>(100));
    // Should not crash
}

/**
 * @tc.name: SelectOverlayNodeTest009
 * @tc.desc: Test SelectOverlayNode ExecuteOverlayStatus with different triggers.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest009, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto eventHub = selectOverlayNode->GetEventHub<SelectOverlayEventHub>();
    ASSERT_NE(eventHub, nullptr);

    // Test FrameNodeTrigger::SHOWN
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::GONETOVISIBLE;
    bool menuShowCalled = false;
    eventHub->SetMenuShowCallback([&menuShowCalled]() { menuShowCalled = true; });
    selectOverlayNode->ExecuteOverlayStatus(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOWN);
    EXPECT_FALSE(menuShowCalled);

    // Test FrameNodeTrigger::HIDDEN
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE;
    bool menuHideCalled = false;
    eventHub->SetMenuHideCallback([&menuHideCalled]() { menuHideCalled = true; });
    selectOverlayNode->ExecuteOverlayStatus(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDDEN);
    EXPECT_FALSE(menuHideCalled);

    // Test other triggers (FrameNodeTrigger::SHOW, FrameNodeTrigger::HIDE)
    selectOverlayNode->ExecuteOverlayStatus(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
    selectOverlayNode->ExecuteOverlayStatus(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDE);
    // Should not crash
}

/**
 * @tc.name: SelectOverlayNodeTest010
 * @tc.desc: Test SelectOverlayNode IsInSelectedOrSelectOverlayArea with menu options.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, SelectOverlayNodeTest010, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    // 创建工具栏确保节点存在
    selectOverlayNode->CreateToolBar();

    // Test point inside select area
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetSelectOverlayInfo()->selectArea = RectF(0, 0, 100, 100);

    // 设置菜单节点的几何信息
    if (selectOverlayNode->selectMenu_ && selectOverlayNode->selectMenu_->GetGeometryNode()) {
        auto geometryNode = selectOverlayNode->selectMenu_->GetGeometryNode();
        geometryNode->SetFrameOffset(OffsetF(100, 100));
        geometryNode->SetFrameSize(SizeF(100, 100));
    }

    NG::PointF pointInArea(50, 50);
    EXPECT_FALSE(selectOverlayNode->IsInSelectedOrSelectOverlayArea(pointInArea));

    // Test point outside select area but inside menu
    NG::PointF pointInMenu(150, 150);
    EXPECT_TRUE(selectOverlayNode->IsInSelectedOrSelectOverlayArea(pointInMenu));

    // Test with null pattern
    SelectOverlayInfo selectOverlayInfo;
    auto selectOverlayPattern = AceType::MakeRefPtr<SelectOverlayPattern>(
        std::make_shared<SelectOverlayInfo>(selectOverlayInfo), SelectOverlayMode::ALL);
    auto nullPatternNode = AceType::MakeRefPtr<SelectOverlayNode>(selectOverlayPattern);
    NG::PointF testPoint(0, 0);
    EXPECT_FALSE(nullPatternNode->IsInSelectedOrSelectOverlayArea(testPoint));
}

/**
 * @tc.name: BuildButton007
 * @tc.desc: Test BuildButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, BuildButton007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;

    std::vector<MenuOptionsParam> menuVec;
    MenuOptionsParam menu1;
    menu1.id = "1";
    menu1.content = "1";
    menu1.action = [](const std::string& menuId) {};

    MenuOptionsParam menu2;
    menu2.id = "1";
    menu2.content = "1";
    menu2.action = [](const std::string& menuId) {};

    menuVec.push_back(menu1);
    menuVec.push_back(menu2);
    selectInfo.menuOptionItems = menuVec;
    float maxWidth = 40.0f;
    float allocatedSize = 50.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return;
    };
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::SetUp();
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, mockContainer);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(frameNode);
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto selectOverlayItem = FrameNode::CreateFrameNode("xyz", 3, pattern, false);
    selectOverlayItem.Reset();
    selectOverlayManager.selectOverlayItem_ = selectOverlayItem;
    selectOverlayManager.CreateAndShowSelectOverlay(selectInfo, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    /**
     * @tc.steps: step2. call BuildButton.
     */
    int32_t extensionOptionStartIndex = 0;
    selectOverlayNode->LandscapeMenuAddMenuOptions(true, maxWidth, allocatedSize, extensionOptionStartIndex, infoPtr);
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_FALSE(selectOverlayNode->isShowInDefaultMenu_[0]);
}

/**
 * @tc.name: GetCustomMenuMaxHeight
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::GetCustomMenuMaxHeight
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, GetCustomMenuMaxHeight, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    auto rect = pipelineContext->GetDisplayWindowRectInfo();
    float topSafeArea = 10.0f;
    float bottomSafeArea = 20.0f;
    float expected = std::max(0.0f, static_cast<float>(rect.Height() - topSafeArea - bottomSafeArea)) *
                     CUSTOM_MENU_HEIGHT_CONSTRAINT_FACTOR;
    /**
     * @tc.steps: step2. call GetCustomMenuMaxHeight.
     */

    EXPECT_EQ(overlayLayoutAlgorithm->GetCustomMenuMaxHeight(topSafeArea, bottomSafeArea), expected);
}

/**
 * @tc.name: CalculateCustomMenuLayoutConstraint
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::CalculateCustomMenuLayoutConstraint
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, CalculateCustomMenuLayoutConstraint, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);

    LayoutConstraintF constraint = { .selfIdealSize = OptionalSizeF(100.0f, 100.0f) };
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->layoutConstraint_ = constraint;

    auto theme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(theme, nullptr);
    // Calculate the spacing with text and handle, menu is fixed up the handle and text.
    double menuSpacingBetweenText = theme->GetMenuSpacingWithText().ConvertToPx();
    double menuSpacingBetweenHandle = theme->GetHandleDiameter().ConvertToPx();

    // paint rect is in global position, need to convert to local position
    auto offset = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    const auto firstHandleRect = overlayLayoutAlgorithm->info_->firstHandle.GetPaintRect() - offset;
    const auto secondHandleRect = overlayLayoutAlgorithm->info_->secondHandle.GetPaintRect() - offset;

    auto top = overlayLayoutAlgorithm->info_->isNewAvoid ? overlayLayoutAlgorithm->info_->selectArea.Top()
                                                         : firstHandleRect.Top();
    auto bottom = overlayLayoutAlgorithm->info_->isNewAvoid ? overlayLayoutAlgorithm->info_->selectArea.Bottom()
                                                            : secondHandleRect.Bottom();
    auto topSpace = top - menuSpacingBetweenText - menuSpacingBetweenHandle;
    auto bottomSpace = constraint.maxSize.Height() - (bottom + menuSpacingBetweenText + menuSpacingBetweenHandle);

    /**
     * @tc.steps: step2. call CalculateCustomMenuLayoutConstraint.
     */
    overlayLayoutAlgorithm->info_->isUsingMouse = true;
    auto result1 = OptionalSizeF(std::nullopt, constraint.maxSize.Height());
    overlayLayoutAlgorithm->CalculateCustomMenuLayoutConstraint(AceType::RawPtr(layoutWrapper), constraint);
    EXPECT_NE(constraint.selfIdealSize, result1);

    overlayLayoutAlgorithm->info_->isUsingMouse = false;
    auto result2 = OptionalSizeF(std::nullopt, std::max(topSpace, bottomSpace));
    overlayLayoutAlgorithm->CalculateCustomMenuLayoutConstraint(AceType::RawPtr(layoutWrapper), constraint);

    EXPECT_NE(constraint.selfIdealSize, result2);
}

/**
 * @tc.name: AdjustMenuInRootRect
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::AdjustMenuInRootRect
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, AdjustMenuInRootRect, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(textOverlayTheme));

    OffsetF menuOffset(100.0f, 100.0f);
    auto menuSize = SizeF(4.0f, 6.0f);
    auto rootSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto defaultPositionX = textOverlayTheme->GetDefaultMenuPositionX();
    auto menuX = LessOrEqual(menuOffset.GetX(), defaultPositionX) ? defaultPositionX : menuOffset.GetX();
    menuX = GreatOrEqual(menuX + menuSize.Width(), rootSize.Width() - defaultPositionX)
                ? rootSize.Width() - defaultPositionX - menuSize.Width()
                : menuX;

    // adjust y
    auto menuY = LessNotEqual(menuOffset.GetY(), 0.0f) ? 0.0f : menuOffset.GetY();
    menuY = GreatNotEqual(menuY + menuSize.Height(), rootSize.Height()) ? rootSize.Height() - menuSize.Height() : menuY;

    /**
     * @tc.steps: step2. call AdjustMenuInRootRect.
     */
    overlayLayoutAlgorithm->AdjustMenuInRootRect(menuOffset, menuSize, rootSize);
    EXPECT_EQ(menuOffset.GetX(), menuX);
    EXPECT_EQ(menuOffset.GetY(), menuY);
}

/**
 * @tc.name: AdjustSelectMenuOffset
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::AdjustSelectMenuOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, AdjustSelectMenuOffset, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    overlayLayoutAlgorithm->mainWindowOffset_ = OffsetF(0.0f, 0.0f);
    overlayLayoutAlgorithm->containerModalOffset_ = OffsetF(0.0f, 0.0f);
    /**
     * @tc.steps: step2. call AdjustSelectMenuOffset.
     */
    double spaceBetweenText = 10.0;
    double spaceBetweenHandle = 5.0;
    overlayLayoutAlgorithm->info_->firstHandle.isShow = true;
    overlayLayoutAlgorithm->info_->secondHandle.isShow = false;
    overlayLayoutAlgorithm->info_->isSingleHandle = false;
    overlayLayoutAlgorithm->info_->handleReverse = false;

    RectF firstPaintRect(100.f, 100.0f, 50.0f, 30.0f);
    overlayLayoutAlgorithm->info_->firstHandle.paintRect = firstPaintRect;
    RectF menuRect1(90.0f, 90.0f, 200.0f, 50.0f);

    auto result1 = overlayLayoutAlgorithm->AdjustSelectMenuOffset(
        AceType::RawPtr(layoutWrapper), menuRect1, spaceBetweenText, spaceBetweenHandle);
    EXPECT_EQ(result1.GetY(), firstPaintRect.Bottom() + spaceBetweenText + spaceBetweenHandle);

    // avoid soft keyboard and root bottom
    spaceBetweenText = 10.0;
    spaceBetweenHandle = 5.0;
    overlayLayoutAlgorithm->info_->firstHandle.isShow = false;
    overlayLayoutAlgorithm->info_->secondHandle.isShow = true;
    overlayLayoutAlgorithm->info_->handleReverse = true;

    RectF secondPaintRect(100.f, 500.0f, 50.0f, 30.0f);
    overlayLayoutAlgorithm->info_->secondHandle.paintRect = secondPaintRect;
    RectF menuRect2(100.0f, 1800.0f, 200.0f, 100.0f);

    auto result2 = overlayLayoutAlgorithm->AdjustSelectMenuOffset(
        AceType::RawPtr(layoutWrapper), menuRect2, spaceBetweenText, spaceBetweenHandle);
    EXPECT_EQ(result2.GetY(), menuRect2.GetY());

    spaceBetweenText = 10.0;
    spaceBetweenHandle = 5.0;
    overlayLayoutAlgorithm->info_->isSingleHandle = false;
    overlayLayoutAlgorithm->info_->firstHandle.isShow = true;
    overlayLayoutAlgorithm->info_->secondHandle.isShow = false;
    overlayLayoutAlgorithm->info_->handleReverse = false;

    RectF firstPaintRect2(300.f, 300.0f, 50.0f, 30.0f);
    overlayLayoutAlgorithm->info_->firstHandle.paintRect = firstPaintRect2;
    RectF menuRect3(100.0f, 100.0f, 200.0f, 50.0f);
    auto expectedY = menuRect3.GetY();
    auto result3 = overlayLayoutAlgorithm->AdjustSelectMenuOffset(
        AceType::RawPtr(layoutWrapper), menuRect3, spaceBetweenText, spaceBetweenHandle);
    EXPECT_EQ(result3.GetY(), expectedY);
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::IsMenuAreaSmallerHandleArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsMenuAreaSmallerHandleArea, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);

    RectF handleRect(10.0f, 10.0f, 10.0f, 10.0f);
    float menuHeight = 2.0f;
    float menuDistance = 2.0f;
    /**
     * @tc.steps: step2. call IsMenuAreaSmallerHandleArea.
     */

    EXPECT_TRUE(overlayLayoutAlgorithm->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: NewMenuAvoidStrategyGetY001
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::NewMenuAvoidStrategyGetY
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, NewMenuAvoidStrategyGetY001, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);

    AvoidStrategyMember avoidStrategyMember;
    avoidStrategyMember.selectAreaTop = 200.0;
    avoidStrategyMember.menuHeight = 50.0;
    avoidStrategyMember.menuSpacing = 10.0;
    avoidStrategyMember.menuSpacingBetweenText = 5.0;
    avoidStrategyMember.selectAndRootRectAreaBottom = 500.0;
    avoidStrategyMember.selectAndRootRectAreaTop = 150.0;
    avoidStrategyMember.bottomLimitOffsetY = 450.0;

    avoidStrategyMember.hasKeyboard = true;
    overlayLayoutAlgorithm->info_->handleReverse = false;
    overlayLayoutAlgorithm->info_->firstHandle.isShow = true;

    float offsetY = 0.0f;

    overlayLayoutAlgorithm->NewMenuAvoidStrategyGetY(avoidStrategyMember, offsetY);
    /**
     * @tc.steps: step2. call NewMenuAvoidStrategyGetY.
     */

    EXPECT_EQ(offsetY, 140);

    overlayLayoutAlgorithm->info_->handleReverse = false;
    overlayLayoutAlgorithm->info_->firstHandle.isShow = false;
    overlayLayoutAlgorithm->info_->isSingleLine = false;
    avoidStrategyMember.downHandleIsReallyShow = true;
    offsetY = 0.0f;
    overlayLayoutAlgorithm->NewMenuAvoidStrategyGetY(avoidStrategyMember, offsetY);
    EXPECT_NE(offsetY, 0.0f);

    overlayLayoutAlgorithm->info_->handleReverse = false;
    overlayLayoutAlgorithm->info_->firstHandle.isShow = false;
    overlayLayoutAlgorithm->info_->isSingleLine = true;
    avoidStrategyMember.downHandleIsReallyShow = false;
    offsetY = 0.0f;
    overlayLayoutAlgorithm->NewMenuAvoidStrategyGetY(avoidStrategyMember, offsetY);
    EXPECT_NE(offsetY, 0.0f);

    overlayLayoutAlgorithm->info_->handleReverse = false;
    overlayLayoutAlgorithm->info_->firstHandle.isShow = false;
    overlayLayoutAlgorithm->info_->isSingleLine = false;
    avoidStrategyMember.downHandleIsReallyShow = false;
    offsetY = 0.0f;
    overlayLayoutAlgorithm->NewMenuAvoidStrategyGetY(avoidStrategyMember, offsetY);
    EXPECT_NE(offsetY, 0.0f);
}

/**
 * @tc.name: NewMenuAvoidStrategyGetY002
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::NewMenuAvoidStrategyGetY
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, NewMenuAvoidStrategyGetY002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    SelectHandleInfo selectHandleInfo;
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    overlayLayoutAlgorithm->info_->handleReverse = false;
    overlayLayoutAlgorithm->info_->firstHandle = selectHandleInfo;
    overlayLayoutAlgorithm->info_->secondHandle = selectHandleInfo;

    AvoidStrategyMember avoidStrategyMember;
    avoidStrategyMember.selectAreaTop = 100.0;
    avoidStrategyMember.menuHeight = 50.0;
    avoidStrategyMember.menuSpacing = 10.0;
    avoidStrategyMember.menuSpacingBetweenText = 5.0;
    avoidStrategyMember.selectAndRootRectAreaBottom = 500.0;
    avoidStrategyMember.selectAndRootRectAreaTop = 50.0;
    avoidStrategyMember.bottomLimitOffsetY = 450.0;
    avoidStrategyMember.hasKeyboard = false;
    avoidStrategyMember.keyboardInsertStart = 0.0;
    avoidStrategyMember.downHandleIsReallyShow = true;

    SafeAreaInsets systemSafeArea;
    systemSafeArea.top_.start = 0;
    systemSafeArea.top_.end = 150;
    safeAreaManager->UpdateSystemSafeArea(systemSafeArea);
    float offsetY = 0.0f;

    overlayLayoutAlgorithm->NewMenuAvoidStrategyGetY(avoidStrategyMember, offsetY);
    /**
     * @tc.steps: step2. call NewMenuAvoidStrategyGetY.
     */
    EXPECT_EQ(offsetY, 250);

    avoidStrategyMember.selectAreaTop = 100.0;
    avoidStrategyMember.menuHeight = 50.0;
    avoidStrategyMember.menuSpacing = 10.0;
    avoidStrategyMember.menuSpacingBetweenText = 5.0;
    avoidStrategyMember.selectAndRootRectAreaBottom = 600.0;
    avoidStrategyMember.selectAndRootRectAreaTop = 50.0;
    avoidStrategyMember.bottomLimitOffsetY = 450.0;
    avoidStrategyMember.hasKeyboard = false;
    avoidStrategyMember.keyboardInsertStart = 0.0;
    avoidStrategyMember.downHandleIsReallyShow = true;

    systemSafeArea.top_.start = 0;
    systemSafeArea.top_.end = 50;
    safeAreaManager->UpdateSystemSafeArea(systemSafeArea);
    offsetY = 0.0f;

    overlayLayoutAlgorithm->NewMenuAvoidStrategyGetY(avoidStrategyMember, offsetY);
    /**
     * @tc.steps: step2. call NewMenuAvoidStrategyGetY.
     */
    double selectBottom = avoidStrategyMember.selectAndRootRectAreaBottom;
    double offsetBetweenSelectArea =
        (avoidStrategyMember.selectAndRootRectAreaTop + selectBottom - avoidStrategyMember.menuHeight) / 2.0;
    offsetBetweenSelectArea = std::clamp(offsetBetweenSelectArea, 50.0, avoidStrategyMember.bottomLimitOffsetY);
    EXPECT_EQ(offsetY, offsetBetweenSelectArea);
}

/**
 * @tc.name: IsReverseLayout
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::IsReverseLayout
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, IsReverseLayout, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto result = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;

    /**
     * @tc.steps: step2. call IsReverseLayout.
     */

    EXPECT_EQ(overlayLayoutAlgorithm->IsReverseLayout(AceType::RawPtr(layoutWrapper)), result);
}

/**
 * @tc.name: CheckHandleIsInClipViewPort
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::CheckHandleIsInClipViewPort
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, CheckHandleIsInClipViewPort, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    overlayLayoutAlgorithm->info_->clipHandleDrawRect = false;
    bool expected = overlayLayoutAlgorithm->info_->firstHandle.isShow;
    overlayLayoutAlgorithm->CheckHandleIsInClipViewPort();
    EXPECT_EQ(overlayLayoutAlgorithm->info_->firstHandle.isShow, expected);

    overlayLayoutAlgorithm->info_->clipHandleDrawRect = true;
    overlayLayoutAlgorithm->info_->secondHandle.isPaintHandleWithPoints = false;
    overlayLayoutAlgorithm->info_->handleLevelMode = HandleLevelMode::OVERLAY;
    overlayLayoutAlgorithm->info_->isSingleHandle = false;
    overlayLayoutAlgorithm->info_->handleReverse = false;

    /**
     * @tc.steps: step2. call CheckHandleIsInClipViewPort.
     */
    overlayLayoutAlgorithm->info_->firstHandle.paintRect = RectF(50.0f, 100.0f, 30.0f, 20.0f);
    overlayLayoutAlgorithm->info_->secondHandle.paintRect = RectF(50.0f, 200.0f, 30.0f, 20.0f);

    overlayLayoutAlgorithm->CheckHandleIsInClipViewPort();
    EXPECT_FALSE(overlayLayoutAlgorithm->info_->firstHandle.isShow);
    EXPECT_FALSE(overlayLayoutAlgorithm->info_->secondHandle.isShow);
}

/**
 * @tc.name: UpdateMainWindowOffset
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, UpdateMainWindowOffset, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    pattern->SetIsMenuShowInSubWindow(false);
    OffsetF expected = OffsetF(0.0, 0.0);
    overlayLayoutAlgorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(overlayLayoutAlgorithm->mainWindowOffset_, expected);
    EXPECT_EQ(overlayLayoutAlgorithm->containerModalOffset_, expected);

    pattern->SetIsMenuShowInSubWindow(true);
    pattern->SetContainerId(-1);
    expected = OffsetF(0.0, 0.0);
    overlayLayoutAlgorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(overlayLayoutAlgorithm->mainWindowOffset_, expected);
    EXPECT_EQ(overlayLayoutAlgorithm->containerModalOffset_, expected);

    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->expandDisplay_ = true;
    auto displayWindowRect = pipelineContext->GetDisplayWindowRectInfo();
    auto result = OffsetF(displayWindowRect.Left(), displayWindowRect.Top());
    overlayLayoutAlgorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(overlayLayoutAlgorithm->mainWindowOffset_, result);
    EXPECT_EQ(overlayLayoutAlgorithm->containerModalOffset_, overlayLayoutAlgorithm->info_->containerModalOffset);
}

/**
 * @tc.name: GetIsMenuShowInSubWindow
 * @tc.desc: Test SelectOverlayLayoutAlgorithm::GetIsMenuShowInSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySevenTestNg, GetIsMenuShowInSubWindow, TestSize.Level1)
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
    auto overlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(overlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    auto result = overlayLayoutAlgorithm->GetIsMenuShowInSubWindow(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(result, pattern->GetIsMenuShowInSubWindow());
}
} // namespace OHOS::Ace::NG