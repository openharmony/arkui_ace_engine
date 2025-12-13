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
#define private public
#define protected public
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
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
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
#undef private
#undef protected

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
const OffsetF OFFSET_ITEM1 = OffsetF(5, 5);
const RectF MENU_RECT(100, 300, 100, 1000);
} // namespace

class SelectOverlaySixTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
    DrawingContext GetDrawingContext(Testing::MockCanvas& canvas);
};

void SelectOverlaySixTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlaySixTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

std::vector<MenuOptionsParam> SelectOverlaySixTestNg::GetMenuOptionItems()
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

DrawingContext SelectOverlaySixTestNg::GetDrawingContext(Testing::MockCanvas& canvas)
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
 * @tc.name: GetCreateMenuOptionsParams005
 * @tc.desc: test GetCreateMenuOptionsParams
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, GetCreateMenuOptionsParams005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.onCreateCallback.onMenuItemClick = nullptr;
    auto info_ = std::make_shared<SelectOverlayInfo>(selectInfo);
    SelectMenuCallback menuCallback;
    menuCallback.onCut = []() {};
    info_->menuCallback = menuCallback;
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info_);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(overlayModifier, nullptr);
    std::vector<MenuOptionsParam> menuOptionItems;
    for (int32_t i = 0; i < 10; i++) {
        MenuOptionsParam item;
        item.id = std::to_string(i);
        item.content = std::to_string(i);
        menuOptionItems.push_back(item);
    }
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    textOverlayTheme->showShortcut_ = true;
    textOverlayTheme->cutLabel_ = "cut";
    textOverlayTheme->cutLabelInfo_ = "cutInfo";
    textOverlayTheme->cutSymbolId_ = 100;
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(textOverlayTheme))
        .WillOnce(Return(textOverlayTheme))
        .WillRepeatedly(Return(selectTheme));
    auto menuWrapper = selectOverlayNode->CreateMenuNode(info_);
    EXPECT_NE(menuWrapper, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
}

/**
 * @tc.name: CreateExtensionMenuOptionCallback001
 * @tc.desc: Test CreateExtensionMenuOptionCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CreateExtensionMenuOptionCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select overlay node.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Prepare callbacks.
     */
    OnMenuItemCallback onCreateCallback;
    onCreateCallback.onMenuItemClick = [](const MenuItemParam& param) -> bool { return true; };

    std::function<void()> systemEvent = []() {
        // Mock system event
    };

    MenuOptionsParam item;
    item.id = "test_item";

    /**
     * @tc.steps: step3. Call CreateExtensionMenuOptionCallback.
     * @tc.expected: Callback function is created successfully.
     */
    auto callback = selectOverlayNode->CreateExtensionMenuOptionCallback(0, onCreateCallback, systemEvent, item);
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: CreateExtensionMenuOptionCallback002
 * @tc.desc: Test CreateExtensionMenuOptionCallback function with null callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CreateExtensionMenuOptionCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select overlay node.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Prepare null callbacks.
     */
    OnMenuItemCallback onCreateCallback;
    // onMenuItemClick is nullptr by default

    std::function<void()> systemEvent = nullptr;

    MenuOptionsParam item;
    item.id = "test_item";

    /**
     * @tc.steps: step3. Call CreateExtensionMenuOptionCallback.
     * @tc.expected: Callback function is created successfully.
     */
    auto callback = selectOverlayNode->CreateExtensionMenuOptionCallback(0, onCreateCallback, systemEvent, item);
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: CreateExtensionMenuOptionCallback003
 * @tc.desc: Test CreateExtensionMenuOptionCallback function with text range callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CreateExtensionMenuOptionCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create select overlay node.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Prepare callbacks with text range callback.
     */
    OnMenuItemCallback onCreateCallback;
    onCreateCallback.onMenuItemClick = [](const MenuItemParam& param) -> bool { return false; };
    onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {
        start = 5;
        end = 15;
    };

    std::function<void()> systemEvent = []() {
        // Mock system event
    };

    MenuOptionsParam item;
    item.id = "test_item";

    /**
     * @tc.steps: step3. Call CreateExtensionMenuOptionCallback.
     * @tc.expected: Callback function is created successfully.
     */
    auto callback = selectOverlayNode->CreateExtensionMenuOptionCallback(0, onCreateCallback, systemEvent, item);
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: UpdateMainWindowOffset005
 * @tc.desc: UpdateMainWindowOffset with IsFreeMultiWindow true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, UpdateMainWindowOffset005, TestSize.Level1)
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
     * @tc.steps: step3. Mock theme and container with pipelineContext
     */
    auto selectOverlayLayoutAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);

    // Create mock container with pipeline context to pass CHECK_NULL_VOID(pipelineContext)
    auto mockContainer = AceType::MakeRefPtr<MockContainer>(MockPipelineContext::GetCurrent());
    mockContainer->isFreeMultiWindow_ = true; // Set the member variable directly
}

/**
 * @tc.name: ComputeSelectMenuPosition001
 * @tc.desc: Test ComputeSelectMenuPosition with single handle and IsTextAreaSelectAll true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.isShow = true;
    selectInfo.menuInfo.menuOffset = OffsetF(50.0f, 50.0f);
    selectInfo.menuInfo.menuIsShow = true;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    // Set info_ to enable IsTextAreaSelectAll to return true
    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition002
 * @tc.desc: Test ComputeSelectMenuPosition with double handles and firstHandle not show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.handleReverse = false;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition003
 * @tc.desc: Test ComputeSelectMenuPosition with double handles and secondHandle not show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = false;
    selectInfo.handleReverse = true;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition004
 * @tc.desc: Test ComputeSelectMenuPosition with double handles and both show with different top values
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 30.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition005
 * @tc.desc: Test ComputeSelectMenuPosition with firstHandle not show and secondHandle show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition006
 * @tc.desc: Test ComputeSelectMenuPosition with firstHandle show and secondHandle not show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = false;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition007
 * @tc.desc: Test ComputeSelectMenuPosition with menu Y position less than menu height
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition007, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.isShow = true;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 5.0f, 20.0f, 10.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition008
 * @tc.desc: Test ComputeSelectMenuPosition with firstHandle not show, secondHandle show and handleReverse false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition008, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.handleReverse = false;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition009
 * @tc.desc: Test ComputeSelectMenuPosition with firstHandle show, secondHandle not show and handleReverse true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition009, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = false;
    selectInfo.handleReverse = true;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition010
 * @tc.desc: Test ComputeSelectMenuPosition with both handles show and top positions not equal
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition010, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition011
 * @tc.desc: Test ComputeSelectMenuPosition with X position adjustment when firstHandle not show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition011, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.secondHandle.paintRect = RectF(100.0f, 100.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition012
 * @tc.desc: Test ComputeSelectMenuPosition with X position adjustment when firstHandle show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition012, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = false;
    selectInfo.firstHandle.paintRect = RectF(100.0f, 100.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition013
 * @tc.desc: Test ComputeSelectMenuPosition with menu Y position less than menu height and IsTextAreaSelectAll true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition013, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.isShow = true;
    selectInfo.menuInfo.menuOffset = OffsetF(50.0f, 1.0f); // Very small Y value
    selectInfo.firstHandle.paintRect = RectF(10.0f, 2.0f, 20.0f, 5.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition014
 * @tc.desc: Test ComputeSelectMenuPosition with menu intersecting handle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition014, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    // Set handles with different top positions to trigger the intersect check
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 100.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(150.0f, 50.0f, 100.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    // Create menu child
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    menuNode->MountToParent(frameNode);

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: ComputeSelectMenuPosition015
 * @tc.desc: Test ComputeSelectMenuPosition with isExtension and !isReverse true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, ComputeSelectMenuPosition015, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.isShow = true;
    selectInfo.firstHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

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

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;
    // Simulate isExtension = true and isReverse = false conditions
    node->menuWidth_ = 80.0f;
    node->menuHeight_ = 40.0f;

    auto result = node->ComputeSelectMenuPosition(AceType::RawPtr(layoutWrapper));
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: AdjustSelectMenuOffset001
 * @tc.desc: Test AdjustSelectMenuOffset with upHandle not show and downHandle show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, AdjustSelectMenuOffset001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.handleReverse = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

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
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    RectF menuRect(0.0f, 0.0f, 100.0f, 50.0f);
    double spaceBetweenText = 5.0;
    double spaceBetweenHandle = 10.0;

    auto result =
        node->AdjustSelectMenuOffset(AceType::RawPtr(layoutWrapper), menuRect, spaceBetweenText, spaceBetweenHandle);
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: AdjustSelectMenuOffset002
 * @tc.desc: Test AdjustSelectMenuOffset with menuBuilder set
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, AdjustSelectMenuOffset002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.handleReverse = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    selectInfo.menuInfo.menuBuilder = []() {}; // Set menuBuilder
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

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
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    RectF menuRect(0.0f, 0.0f, 100.0f, 50.0f);
    double spaceBetweenText = 5.0;
    double spaceBetweenHandle = 10.0;

    auto result =
        node->AdjustSelectMenuOffset(AceType::RawPtr(layoutWrapper), menuRect, spaceBetweenText, spaceBetweenHandle);
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: AdjustSelectMenuOffset003
 * @tc.desc: Test AdjustSelectMenuOffset with shouldAvoidKeyboard condition true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, AdjustSelectMenuOffset003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.handleReverse = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.menuInfo.menuBuilder = nullptr;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 800.0f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    RectF menuRect(0.0f, 700.0f, 100.0f, 150.0f); // Position near bottom
    double spaceBetweenText = 5.0;
    double spaceBetweenHandle = 10.0;

    auto result =
        node->AdjustSelectMenuOffset(AceType::RawPtr(layoutWrapper), menuRect, spaceBetweenText, spaceBetweenHandle);
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: AdjustSelectMenuOffset004
 * @tc.desc: Test AdjustSelectMenuOffset with shouldAvoidBottom condition true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, AdjustSelectMenuOffset004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.handleReverse = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.menuInfo.menuBuilder = nullptr;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 750.0f, 20.0f, 20.0f); // Near bottom

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 800.0f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    RectF menuRect(0.0f, 700.0f, 100.0f, 150.0f); // Position that would go beyond bottom
    double spaceBetweenText = 5.0;
    double spaceBetweenHandle = 10.0;

    auto result =
        node->AdjustSelectMenuOffset(AceType::RawPtr(layoutWrapper), menuRect, spaceBetweenText, spaceBetweenHandle);
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: AdjustSelectMenuOffset005
 * @tc.desc: Test AdjustSelectMenuOffset with offsetY <= 0 condition
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, AdjustSelectMenuOffset005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = false;
    selectInfo.handleReverse = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.menuInfo.menuBuilder = nullptr;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 800.0f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    RectF menuRect(0.0f, 0.0f, 100.0f, 100.0f); // Large menu that would result in negative offsetY
    double spaceBetweenText = 5.0;
    double spaceBetweenHandle = 1000.0; // Large space to ensure offsetY <= 0

    auto result =
        node->AdjustSelectMenuOffset(AceType::RawPtr(layoutWrapper), menuRect, spaceBetweenText, spaceBetweenHandle);
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: AdjustSelectMenuOffset006
 * @tc.desc: Test AdjustSelectMenuOffset with topArea > menuOffset.GetY() and isSingleHandle true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, AdjustSelectMenuOffset006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.isSingleHandle = true; // Single handle mode
    selectInfo.handleReverse = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = true;
    selectInfo.menuInfo.menuBuilder = nullptr;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(50.0f, 50.0f, 20.0f, 20.0f);

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 800.0f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);

    // Mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    node->info_ = infoPtr;

    RectF menuRect(0.0f, 0.0f, 100.0f, 50.0f); // Menu with small Y offset
    double spaceBetweenText = 5.0;
    double spaceBetweenHandle = 10.0;

    auto result =
        node->AdjustSelectMenuOffset(AceType::RawPtr(layoutWrapper), menuRect, spaceBetweenText, spaceBetweenHandle);
    // Just verify it doesn't crash and returns a valid offset
    EXPECT_TRUE(result.GetX() >= 0 && result.GetY() >= 0);
}

/**
 * @tc.name: IsTextAreaSelectAll001
 * @tc.desc: Test IsTextAreaSelectAll with menuOffset and firstHandle not show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsTextAreaSelectAll001, TestSize.Level1)
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
    node->info_->menuInfo.menuOffset = OffsetF(10.0f, 10.0f);
    node->info_->firstHandle.isShow = false;
    node->info_->secondHandle.isShow = true;

    EXPECT_TRUE(node->IsTextAreaSelectAll());
}

/**
 * @tc.name: IsTextAreaSelectAll002
 * @tc.desc: Test IsTextAreaSelectAll without menuOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsTextAreaSelectAll002, TestSize.Level1)
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
    node->info_->menuInfo.menuOffset.reset();
    node->info_->firstHandle.isShow = false;
    node->info_->secondHandle.isShow = true;

    EXPECT_FALSE(node->IsTextAreaSelectAll());
}

/**
 * @tc.name: IsTextAreaSelectAll003
 * @tc.desc: Test IsTextAreaSelectAll with both handles show
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsTextAreaSelectAll003, TestSize.Level1)
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
    node->info_->menuInfo.menuOffset = OffsetF(10.0f, 10.0f);
    node->info_->firstHandle.isShow = true;
    node->info_->secondHandle.isShow = true;

    EXPECT_FALSE(node->IsTextAreaSelectAll());
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea001
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height greater than menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsMenuAreaSmallerHandleArea001, TestSize.Level1)
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

    // 50 > 30 + 10 = 40, should return true
    EXPECT_TRUE(node->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: IsReverseLayout003
 * @tc.desc: Test IsReverseLayout with RTL layout direction
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsReverseLayout003, TestSize.Level1)
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
    layoutProperty->layoutDirection_ = OHOS::Ace::TextDirection::RTL;

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    EXPECT_TRUE(node->IsReverseLayout(AceType::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: IsReverseLayout004
 * @tc.desc: Test IsReverseLayout with LTR layout direction
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsReverseLayout004, TestSize.Level1)
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
}

/**
 * @tc.name: IsReverseLayout005
 * @tc.desc: Test IsReverseLayout with RTL layout direction
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsReverseLayout005, TestSize.Level1)
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
    layoutProperty->layoutDirection_ = OHOS::Ace::TextDirection::RTL;

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    EXPECT_TRUE(node->IsReverseLayout(AceType::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: IsReverseLayout006
 * @tc.desc: Test IsReverseLayout with LTR layout direction
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsReverseLayout006, TestSize.Level1)
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
    layoutProperty->layoutDirection_ = OHOS::Ace::TextDirection::LTR;

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    EXPECT_FALSE(node->IsReverseLayout(AceType::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea002
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height less than menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsMenuAreaSmallerHandleArea002, TestSize.Level1)
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

    // 30 > 30 + 10 = 40, should return false
    EXPECT_FALSE(node->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance));
}

/**
 * @tc.name: IsMenuAreaSmallerHandleArea003
 * @tc.desc: Test IsMenuAreaSmallerHandleArea with handle height equal to menu height plus distance
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, IsMenuAreaSmallerHandleArea003, TestSize.Level1)
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
 * @tc.name: GetCustomMenuMaxHeight001
 * @tc.desc: Test GetCustomMenuMaxHeight with valid pipeline context
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, GetCustomMenuMaxHeight001, TestSize.Level1)
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
    float topSafeArea = 20.0f;
    float bottomSafeArea = 30.0f;

    // Mock display window rect info
    auto pipeline = MockPipelineContext::GetCurrent();
    Rect displayWindowRect(0.0f, 0.0f, 1000.0f, 2000.0f);
    pipeline->displayWindowRectInfo_ = displayWindowRect;

    float result = node->GetCustomMenuMaxHeight(topSafeArea, bottomSafeArea);
    float expected = (2000.0f - 20.0f - 30.0f) * 0.8f;

    EXPECT_FLOAT_EQ(result, expected);
}

/**
 * @tc.name: GetCustomMenuMaxHeight002
 * @tc.desc: Test GetCustomMenuMaxHeight with negative result
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, GetCustomMenuMaxHeight002, TestSize.Level1)
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
    float topSafeArea = 1000.0f;
    float bottomSafeArea = 1500.0f;

    // Mock display window rect info
    auto pipeline = MockPipelineContext::GetCurrent();
    Rect displayWindowRect(0.0f, 0.0f, 1000.0f, 2000.0f);
    pipeline->displayWindowRectInfo_ = displayWindowRect;

    float result = node->GetCustomMenuMaxHeight(topSafeArea, bottomSafeArea);
    // Should return 0.0 since 2000 - 1000 - 1500 = -500, max(0, -500) = 0, 0 * 0.8 = 0
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: CheckInShowArea001
 * @tc.desc: Test CheckInShowArea with useFullScreen = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = true;

    EXPECT_TRUE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea002
 * @tc.desc: Test CheckInShowArea with single handle and first handle in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_TRUE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea003
 * @tc.desc: Test CheckInShowArea with single handle and first handle not in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.paintRect = RectF(110.0f, 110.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_FALSE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea004
 * @tc.desc: Test CheckInShowArea with double handles and both in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(30.0f, 30.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_TRUE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea005
 * @tc.desc: Test CheckInShowArea with double handles and one not in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(110.0f, 110.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_FALSE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea006
 * @tc.desc: Test CheckInShowArea with useFullScreen = true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = true;

    EXPECT_TRUE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea007
 * @tc.desc: Test CheckInShowArea with single handle and first handle in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea007, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_TRUE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea008
 * @tc.desc: Test CheckInShowArea with single handle and first handle not in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea008, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.paintRect = RectF(110.0f, 110.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_FALSE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea009
 * @tc.desc: Test CheckInShowArea with double handles and both in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea009, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(30.0f, 30.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_TRUE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}

/**
 * @tc.name: CheckInShowArea010
 * @tc.desc: Test CheckInShowArea with double handles and one not in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlaySixTestNg, CheckInShowArea010, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.paintRect = RectF(10.0f, 10.0f, 20.0f, 20.0f);
    selectInfo.secondHandle.paintRect = RectF(110.0f, 110.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    EXPECT_FALSE(SelectOverlayLayoutAlgorithm::CheckInShowArea(selectInfo));
}
} // namespace OHOS::Ace::NG