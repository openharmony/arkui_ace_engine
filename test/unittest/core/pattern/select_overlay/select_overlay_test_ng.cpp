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
#include <iostream>
#include <vector>
#include "core/accessibility/accessibility_manager.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"
#define private public
#define protected public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/security_component/security_component_layout_property.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline/base/constants.h"
#include "core/components/theme/icon_theme.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "Test";
constexpr int32_t NODE_ID = 143;
constexpr int32_t NODE_ID2 = 153;
constexpr int32_t NODE_ID3 = 10;
constexpr int32_t OPTION_INDEX_COPY = 1;
const RectF FIRST_HANDLE_REGION(0, 0, 10, 10);
const RectF SECOND_HANDLE_REGION(10, 10, 10, 10);
const RectF SECOND_HANDLE_REGION2(20, 20, 10, 10);
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const Color COLOR_ALPHA_MASK = Color::FromRGB(255, 100, 100);
constexpr MenuType TYPE = MenuType::MENU;
const OffsetF offset(10, 10);
int32_t callBackFlag = 0;
constexpr float RK356_HEIGHT = 1136.0f;
const OffsetF OFFSET_ITEM1 = OffsetF(5, 5);
const Rect WINDOW_RECT(0, 0, 280, 1280);
constexpr int32_t TEST_THEME_SCOPE_ID = 0;
const std::string NODE_TEST_SELECT_TEXT = "Test selected text";

SelectOverlayInfo CreateDefaultNodeTestInfo()
{
    SelectOverlayInfo info;
    info.firstHandle.paintRect = FIRST_HANDLE_REGION;
    info.firstHandle.isShow = true;
    info.firstHandle.isTouchable = true;
    info.secondHandle.paintRect = SECOND_HANDLE_REGION;
    info.secondHandle.isShow = true;
    info.secondHandle.isTouchable = true;
    info.isSingleHandle = false;
    info.menuInfo.menuIsShow = true;
    info.selectText = NODE_TEST_SELECT_TEXT;
    return info;
}

RefPtr<SelectOverlayNode> CreateSelectOverlayNodeForNodeTest(SelectOverlayMode mode = SelectOverlayMode::ALL)
{
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    return AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info, mode));
}

RefPtr<MockThemeManager> PrepareThemeManagerForNodeTest(const RefPtr<TextOverlayTheme>& textOverlayTheme,
    const RefPtr<SelectTheme>& selectTheme = AceType::MakeRefPtr<SelectTheme>(),
    const RefPtr<IconTheme>& iconTheme = AceType::MakeRefPtr<IconTheme>())
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto getTheme = [textOverlayTheme, selectTheme, iconTheme](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return textOverlayTheme;
        }
        if (type == SelectTheme::TypeId()) {
            return selectTheme;
        }
        if (type == IconTheme::TypeId()) {
            return iconTheme;
        }
        return textOverlayTheme;
    };
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([getTheme](ThemeType type) -> RefPtr<Theme> { return getTheme(type); });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([getTheme](ThemeType type, int32_t) -> RefPtr<Theme> { return getTheme(type); });
    return themeManager;
}

RefPtr<FrameNode> CreateCallerFrameNodeForNodeTest(
    int32_t apiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX), int32_t themeScopeId = 100)
{
    auto caller = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), []() {
            return AceType::MakeRefPtr<TextPattern>();
        });
    CHECK_NULL_RETURN(caller, nullptr);
    caller->apiVersion_ = apiVersion;
    caller->themeScopeId_ = themeScopeId;
    return caller;
}

void InvokeUserClick(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto gestureEventHub = node->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    GestureEvent gestureEvent;
    if (gestureEventHub->clickEventActuator_ && gestureEventHub->clickEventActuator_->userCallback_) {
        auto clickCallback = gestureEventHub->clickEventActuator_->userCallback_->callback_;
        clickCallback(gestureEvent);
        return;
    }
    if (gestureEventHub->userParallelClickEventActuator_ &&
        gestureEventHub->userParallelClickEventActuator_->userCallback_) {
        auto clickCallback = gestureEventHub->userParallelClickEventActuator_->userCallback_->callback_;
        clickCallback(gestureEvent);
    }
}

RefPtr<FrameNode> FindFirstFrameNodeByTag(const RefPtr<UINode>& node, const std::string& tag)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode && frameNode->GetTag() == tag) {
        return frameNode;
    }
    CHECK_NULL_RETURN(node, nullptr);
    for (const auto& child : node->GetChildren()) {
        auto result = FindFirstFrameNodeByTag(child, tag);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

RefPtr<FrameNode> FindFirstMenuItemWithPasteButton(const RefPtr<UINode>& node)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode && frameNode->GetTag() == V2::MENU_ITEM_ETS_TAG) {
        auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
        if (menuItemPattern && menuItemPattern->GetPasteButton()) {
            return frameNode;
        }
    }
    CHECK_NULL_RETURN(node, nullptr);
    for (const auto& child : node->GetChildren()) {
        auto result = FindFirstMenuItemWithPasteButton(child);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

RefPtr<FrameNode> CreateExtensionMenuForAnimationTest(const SizeF& extensionMenuSize,
    const RectF& selectMenuPaintRect, size_t menuItemCount)
{
    auto extensionMenu = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(0, "SelectOverlayExtensionMenu", MenuType::SELECT_OVERLAY_EXTENSION_MENU));
    CHECK_NULL_RETURN(extensionMenu, nullptr);
    auto extensionMenuPattern = extensionMenu->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(extensionMenuPattern, nullptr);
    extensionMenuPattern->SetSelectMenuPaintRect(selectMenuPaintRect);

    auto scrollNode = FrameNode::CreateFrameNode("ScrollNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>());
    CHECK_NULL_RETURN(scrollNode, nullptr);
    auto innerMenuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(0, "SelectOverlayInnerMenu", MenuType::MENU));
    CHECK_NULL_RETURN(innerMenuNode, nullptr);
    auto innerMenuPattern = innerMenuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(innerMenuPattern, nullptr);
    for (size_t index = 0; index < menuItemCount; ++index) {
        auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        CHECK_NULL_RETURN(menuItemNode, nullptr);
        innerMenuPattern->AddMenuItemNode(menuItemNode);
        menuItemNode->MountToParent(innerMenuNode);
    }
    innerMenuNode->MountToParent(scrollNode);
    scrollNode->MountToParent(extensionMenu);

    auto extensionRenderContext = extensionMenu->GetRenderContext();
    auto scrollRenderContext = scrollNode->GetRenderContext();
    auto innerMenuRenderContext = innerMenuNode->GetRenderContext();
    CHECK_NULL_RETURN(extensionRenderContext && scrollRenderContext && innerMenuRenderContext, nullptr);
    extensionRenderContext->UpdatePaintRect(RectF(OffsetF(), extensionMenuSize));
    scrollRenderContext->UpdatePaintRect(RectF(OffsetF(), extensionMenuSize));
    innerMenuRenderContext->UpdatePaintRect(RectF(OffsetF(), extensionMenuSize));
    return extensionMenu;
}
} // namespace

class SelectOverlayTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
    DrawingContext GetDrawingContext(Testing::MockCanvas& canvas);
    void InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme);
    static RefPtr<Theme> GetMockThemeForTest(ThemeType type);
};

void SelectOverlayTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    auto rootNode = MockPipelineContext::GetCurrent()->rootNode_;
    if (rootNode) {
        auto rootRenderContext = rootNode->GetRenderContext();
        if (rootRenderContext) {
            rootRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 1280.0f, 2480.0f));
        }
    }
}

void SelectOverlayTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

std::vector<MenuOptionsParam> SelectOverlayTestNg::GetMenuOptionItems()
{
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    MenuOptionsParam menuOptionItem2;
    menuOptionItem2.content = "test2";
    menuOptionItem2.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItem1);
    menuOptionItems.emplace_back(menuOptionItem2);
    return menuOptionItems;
}

DrawingContext SelectOverlayTestNg::GetDrawingContext(Testing::MockCanvas& canvas)
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

void SelectOverlayTestNg::InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme)
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

RefPtr<Theme> SelectOverlayTestNg::GetMockThemeForTest(ThemeType type)
{
    if (type == SelectTheme::TypeId()) {
        return AceType::MakeRefPtr<SelectTheme>();
    }
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    textOverlayTheme->showShortcut_ = true;
    textOverlayTheme->pasteLabel_ = "pasteLabel";
    return textOverlayTheme;
}

/**
 * @tc.name: SelectFrameNodeCreator002
 * @tc.desc: Test CreateSelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode with camera input.
     * @tc.expected: the selectOverlayNode including selectMenu with camera input is created successfully.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
}

/**
 * @tc.name: SelectFrameNodeAnimationTest001
 * @tc.desc: Test MoreAnimation and BackAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create default menu and extension menu .
     * @tc.expected: The default menu and extended menu are created successfully.
     */
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    /**
     * @tc.steps: step3. Execute MoreAnimation.
     * @tc.expected: The node state switches correctly.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->MoreOrBackAnimation(true);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
    /**
     * @tc.steps: step4. Execute BackAnimation.
     * @tc.expected: The node state switches correctly.
     */
    selectOverlayNode->isDoingAnimation_ = false;
    selectOverlayNode->MoreOrBackAnimation(false);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}
/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test SelectOverlayPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.isSingleHandle = true;
    bool isShow[2] = { false, true };
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.firstHandle.isShow = isShow[turn];
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call OnAttachToFrameNode function.
         * @tc.expected: the function exits normally.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        ASSERT_NE(pattern->info_, nullptr);
        pattern->info_->isHandleLineShow = isShow[turn];
        pattern->OnAttachToFrameNode();
        EXPECT_NE(pattern->GetSelectOverlayInfo(), nullptr);
    }
}
/**
 * @tc.name: UpdateSelectHandleInfo001
 * @tc.desc: Test SelectOverlayPattern UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectHandleInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. call UpdateHandleInfo functions without changing HandleInfo.
     * @tc.expected: The branch of function runs correctly
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    pattern->UpdateFirstSelectHandleInfo(selectInfo.firstHandle);
    pattern->UpdateSecondSelectHandleInfo(selectInfo.secondHandle);
    pattern->UpdateFirstAndSecondHandleInfo(selectInfo.firstHandle, selectInfo.secondHandle);
    EXPECT_EQ(pattern->info_->firstHandle, selectInfo.firstHandle);
    EXPECT_EQ(pattern->info_->secondHandle, selectInfo.secondHandle);
}
/**
 * @tc.name: UpdateSelectHandleInfo002
 * @tc.desc: Test SelectOverlayPattern UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectHandleInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    bool handleReverse[2] = { false, true };
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.handleReverse = handleReverse[turn];
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call UpdateHandleInfo functions with changing HandleInfo.
         * @tc.expected: The branch of function runs correctly
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        SelectOverlayInfo selectInfo2;
        selectInfo2.singleLineHeight = NODE_ID2;
        selectInfo2.firstHandle.isShow = false;
        selectInfo2.secondHandle.isShow = false;
        SelectOverlayInfo selectInfo3;
        selectInfo3.singleLineHeight = NODE_ID3;
        pattern->UpdateFirstSelectHandleInfo(selectInfo2.firstHandle);
        pattern->UpdateSecondSelectHandleInfo(selectInfo2.secondHandle);
        pattern->UpdateFirstAndSecondHandleInfo(selectInfo3.firstHandle, selectInfo3.secondHandle);
    }
}
/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test SelectOverlayPattern OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and geometryNode.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    /**
     * @tc.steps: step2. Call OnDirtyLayoutWrapperSwap function.
     * @tc.expected: return false
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    DirtySwapConfig config;
    config.skipMeasure = true;
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    layoutWrapper->skipMeasureContent_ = false;
    config.skipMeasure = false;
    EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}
/**
 * @tc.name: UpdateShowArea001
 * @tc.desc: Test SelectOverlayPattern UpdateShowArea.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateShowArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Call UpdateShowArea
     * @tc.expected: the function exits normally
     */
    RectF area;
    pattern->UpdateShowArea(area);
    EXPECT_NE(pattern->GetSelectOverlayInfo(), nullptr);

    area = RectF(1, 1, 1, 1);
    pattern->UpdateShowArea(area);
    EXPECT_NE(pattern->GetSelectOverlayInfo(), nullptr);
}

/**
 * @tc.name: HandleOperator001
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Construct GestureEvent and Call UpdateShowArea
     * @tc.expected: the function exits normally
     */
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    pattern->HandleOnClick(info);
    EXPECT_FALSE(pattern->GetSelectOverlayInfo()->isSingleHandle);
    pattern->HandlePanEnd(info);
    EXPECT_FALSE(pattern->GetSelectOverlayInfo()->isSingleHandle);
    infoPtr->menuInfo.menuIsShow = true;
    pattern->firstHandleDrag_ = true;
    callBackFlag = 0;
    infoPtr->onHandleMoveDone = [&](const RectF& tmp, bool isFirst) {
        callBackFlag = 1;
    };
    pattern->HandlePanEnd(info);
    EXPECT_EQ(callBackFlag, 1);
    pattern->firstHandleDrag_ = false;
    pattern->secondHandleDrag_ = true;

    callBackFlag = 0;
    pattern->HandlePanEnd(info);
    EXPECT_EQ(callBackFlag, 1);

    /**
     * @tc.steps: step4. Menu is not show, call HandleOnClick
     * @tc.expected: menuIsShow is true.
     */
    ASSERT_NE(pattern->info_, nullptr);
    pattern->info_->isSingleHandle = true;
    pattern->info_->isHandleLineShow = false;
    pattern->info_->menuInfo.menuIsShow = false;
    pattern->HandleOnClick(info);
    EXPECT_TRUE(pattern->info_->menuInfo.menuIsShow);
}

/**
 * @tc.name: HandleOperator002
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.isSingleHandle = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Construct GestureEvent and Call HandleOperator functions in firstHandleRegion.
     * @tc.expected: the function runs rightly
     */
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    pattern->HandleOnClick(info);
    EXPECT_TRUE(pattern->GetSelectOverlayInfo()->menuInfo.menuIsShow);
    pattern->isFirstHandleTouchDown_ = true;
    pattern->HandlePanStart(info);
    EXPECT_TRUE(pattern->firstHandleDrag_);
    const auto& offset = OffsetF(info.GetDelta().GetX(), info.GetDelta().GetY());
    auto firstHandlePaintRect = pattern->GetSelectOverlayInfo()->firstHandle.paintRect + offset;
    pattern->HandlePanMove(info);
    auto firstHandlePaintRect2 = pattern->GetSelectOverlayInfo()->secondHandle.paintRect;
    EXPECT_EQ(firstHandlePaintRect.GetX(), firstHandlePaintRect2.GetX());
    pattern->HandlePanEnd(info);
    EXPECT_FALSE(pattern->firstHandleDrag_);
    /**
     * @tc.steps: step4. Construct GestureEvent and Call HandleOperator functions in secondHandleRegion.
     * @tc.expected: the function runs rightly
     */
    GestureEvent info2;
    info2.localLocation_ = Offset(11, 11);
    ASSERT_NE(pattern->info_, nullptr);
    pattern->info_->isHandleLineShow = false;
    pattern->isSecondHandleTouchDown_ = true;
    pattern->HandlePanStart(info2);
    EXPECT_TRUE(pattern->secondHandleDrag_);
    const auto& offset2 = OffsetF(info2.GetDelta().GetX(), info2.GetDelta().GetY());
    auto secondHandlePaintRect = pattern->GetSelectOverlayInfo()->secondHandle.paintRect + offset2;
    pattern->HandlePanMove(info2);
    auto secondHandlePaintRect2 = pattern->GetSelectOverlayInfo()->secondHandle.paintRect;
    EXPECT_EQ(secondHandlePaintRect.GetX(), secondHandlePaintRect2.GetX());
    pattern->HandlePanEnd(info2);
    EXPECT_FALSE(pattern->secondHandleDrag_);
    /**
     * @tc.steps: step5. Construct GestureEvent and Call HandleOperator functions which is not in handleRegion.
     * @tc.expected: the function runs rightly
     */
    GestureEvent info3;
    info3.localLocation_ = Offset(21, 21);
    pattern->info_->isSingleHandle = false;
    pattern->HandlePanStart(info3);
    pattern->HandlePanMove(info3);
    EXPECT_FALSE(pattern->firstHandleDrag_);
    EXPECT_FALSE(pattern->secondHandleDrag_);

    // in first region
    GestureEvent info4;
    info4.localLocation_ = Offset(1, 1);
    pattern->info_->isSingleHandle = false;
    callBackFlag = 0;
    pattern->info_->onHandleMoveStart = [&](const GestureEvent& event, bool isFirst) {
        callBackFlag = 1;
    };
    pattern->isFirstHandleTouchDown_ = true;
    pattern->HandlePanStart(info4);
    EXPECT_EQ(callBackFlag, 1);

    // not in first region and in second region
    info4.localLocation_ = Offset(11, 11);
    callBackFlag = 0;
    pattern->isSecondHandleTouchDown_ = true;
    pattern->HandlePanStart(info4);
    EXPECT_EQ(callBackFlag, 1);

    // not in neither region
    info4.localLocation_ = Offset(21, 21);
    callBackFlag = 0;
    pattern->info_->menuInfo.menuIsShow = false;

    for (int i = 0; i < 4; ++i) {
        pattern->info_->isSingleHandle = i & 1;
        pattern->info_->isHandleLineShow = i >> 1 & 1;
        callBackFlag = 0;
        pattern->HandlePanStart(info4);
        EXPECT_EQ(callBackFlag, 0);
    }
}

/**
 * @tc.name: HandleOperator003
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Construct TouchEventInfo and Call HandleTouchEvent function.
     * @tc.expected: check whether the function is executed.
     */
    TouchEventInfo touchInfo("touchDown");
    infoPtr->onTouchDown = [](const TouchEventInfo& info) {
        callBackFlag = 1;
        return ;
    };
    infoPtr->onTouchUp = [](const TouchEventInfo& info) {
        callBackFlag = 2;
        return ;
    };
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchInfo);
    EXPECT_EQ(callBackFlag, 1);
}

/**
 * @tc.name: HandleOperator003
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Construct TouchEventInfo and Call HandleTouchEvent function.
     * @tc.expected: check whether the function is executed.
     */
    TouchEventInfo touchInfo("touchDown");
    infoPtr->onTouchDown = [](const TouchEventInfo& info) {
        callBackFlag = 1;
        return;
    };
    infoPtr->onTouchUp = [](const TouchEventInfo& info) {
        callBackFlag = 2;
        return;
    };
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchInfo);
    EXPECT_EQ(callBackFlag, 2);
}

/**
 * @tc.name: HandleOperator003
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Construct TouchEventInfo and Call HandleTouchEvent function.
     * @tc.expected: check whether the function is executed.
     */
    TouchEventInfo touchInfo("touchDown");
    infoPtr->onTouchDown = [](const TouchEventInfo& info) {
        callBackFlag = 1;
        return;
    };
    infoPtr->onTouchMove = [](const TouchEventInfo& info) {
        callBackFlag = 3;
        return;
    };
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchInfo);
    EXPECT_EQ(callBackFlag, 3);
}

/**
 * @tc.name: CheckHandleReverse001
 * @tc.desc: Test SelectOverlayPattern CheckHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CheckHandleReverse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectHandleInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID3;
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = FIRST_HANDLE_REGION;
    SelectHandleInfo secondHandle;
    secondHandle.paintRect = SECOND_HANDLE_REGION2;
    selectInfo.firstHandle = firstHandle;
    selectInfo.secondHandle = secondHandle;
    bool handleReverse[2] = { false, true };
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.handleReverse = handleReverse[turn];
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call CheckHandleReverse function.
         * @tc.expected: check whether the value of handleReverse is correct.
         */
        pattern->CheckHandleReverse();
        auto res = pattern->GetSelectOverlayInfo()->handleReverse;
        EXPECT_FALSE(res);
    }
}
/**
 * @tc.name: CheckHandleReverse002
 * @tc.desc: Test SelectOverlayPattern CheckHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CheckHandleReverse002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectHandleInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID3;
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = SECOND_HANDLE_REGION2;
    SelectHandleInfo secondHandle;
    secondHandle.paintRect = FIRST_HANDLE_REGION;
    selectInfo.firstHandle = firstHandle;
    selectInfo.secondHandle = secondHandle;
    bool handleReverse[2] = { false, true };
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.handleReverse = handleReverse[turn];
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call CheckHandleReverse function.
         * @tc.expected: check whether the value of handleReverse is correct.
         */
        pattern->CheckHandleReverse();
        auto res = pattern->GetSelectOverlayInfo()->handleReverse;
        EXPECT_TRUE(res);
    }
}
/**
 * @tc.name: SelectOverlayLayout001
 * @tc.desc: Test selectOverlay layout.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    bool menuIsShow[2] = { false, true };
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.menuInfo.menuIsShow = menuIsShow[turn];
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern and geometryNode.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        /**
         * @tc.steps: step3. Get layoutWrapper and layoutAlgorithm.
         * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
         */
        auto layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
        auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
        ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
        layoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

        auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
        // create menu and extensionMenu
        for (int i = 0; i < 3; i++) {
            auto item = FrameNode::GetOrCreateFrameNode(
                V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
            // add item to selectOverlayNode
            selectOverlayNode->AddChild(item);
            RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
            firstGeometryNode->Reset();
            RefPtr<LayoutWrapperNode> firstLayoutWrapper =
                AceType::MakeRefPtr<LayoutWrapperNode>(item, firstGeometryNode, item->GetLayoutProperty());
            ASSERT_NE(firstLayoutWrapper, nullptr);
            auto itemPattern = item->GetPattern<MenuPattern>();
            ASSERT_NE(itemPattern, nullptr);
            firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
            auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
            ASSERT_NE(itemLayoutAlgorithm, nullptr);
            firstLayoutWrapper->SetLayoutAlgorithm(
                AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
            firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
            layoutWrapper->AppendChild(firstLayoutWrapper);
        }

        /**
         * @tc.steps: step4. use layoutAlgorithm to measure and layout.
         * @tc.expected: the function runs rightly.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    }
}
/**
 * @tc.name: SelectOverlayNodeTest001
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea with menuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return false
     */
    const NG::PointF point { 9.0f, 12.0f };
    auto result = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step4. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return true
     */
    const NG::PointF point2 { 12.0f, 12.0f };
    auto result2 = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point2);
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: SelectOverlayNodeTest002
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea without menuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return false
     */
    const NG::PointF point { 9.0f, 12.0f };
    auto result = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step4. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return true
     */
    const NG::PointF point2 { 12.0f, 12.0f };
    auto result2 = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point2);
    EXPECT_TRUE(result2);
}
/**
 * @tc.name: SelectFrameNodeAnimationTest002
 * @tc.desc: Test MoreAnimation and BackAnimation when isShowInDefaultMenu is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeAnimationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create default menu and extension menu .
     * @tc.expected: The default menu and extended menu are created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    for (int i = 0; i < 7; i++) {
        selectOverlayNode->isShowInDefaultMenu_[i] = false;
    }
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
}

/**
 * @tc.name: SetHasShowAnimation001
 * @tc.desc: Test SetHasShowAnimation when argument is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetHasShowAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call SetHasShowAnimation and argument is true .
     * @tc.expected: The hasShowAnimation_ be changed success.
     */
    pattern->SetHasShowAnimation(true);
    EXPECT_TRUE(pattern->hasShowAnimation_);
}

/**
 * @tc.name: SetFrameNodeStatus001
 * @tc.desc: Test SetFrameNodeStatus different argument.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call SetFrameNodeStatus and pass different parameters .
     * @tc.expected: the corresponding value was successfully changed.
     */
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::SELECTMENU, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::EXTENSIONMENU, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::VISIBLE);
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::BACKBUTTON, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::VISIBLE);
}

/**
 * @tc.name: SetFrameNodeVisibility001
 * @tc.desc: Test SetFrameNodeVisibility different argument.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeVisibility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [](ThemeType type) -> RefPtr<Theme> { return SelectOverlayTestNg::GetMockThemeForTest(type); });
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create default menu and extension menu .
     */
    selectOverlayNode->CreateToolBar();
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    /**
     * @tc.steps: step3. call SetFrameNodeVisibility and pass different parameters .
     * @tc.expected: the corresponding value was successfully changed.
     */
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::SELECTMENU, VisibleType::VISIBLE);
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::EXTENSIONMENU, VisibleType::VISIBLE);
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::BACKBUTTON, VisibleType::VISIBLE);
    EXPECT_EQ(selectOverlayNode->selectMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_EQ(selectOverlayNode->extensionMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_EQ(selectOverlayNode->backButton_->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: SetFrameNodeOpacity001
 * @tc.desc: Test SetFrameNodeOpacity different argument.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeOpacity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [](ThemeType type) -> RefPtr<Theme> { return SelectOverlayTestNg::GetMockThemeForTest(type); });
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create default menu and extension menu .
     */
    selectOverlayNode->CreateToolBar();
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    /**
     * @tc.steps: step3. call SetFrameNodeOpacity and pass different parameters .
     * @tc.expected: the corresponding value was successfully changed.
     */
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::SELECTMENU, 0.0);
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::EXTENSIONMENU, 0.0);
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::BACKBUTTON, 0.0);

    EXPECT_EQ(selectOverlayNode->selectMenu_->GetRenderContext()->GetOpacity(), 0.0);
    EXPECT_EQ(selectOverlayNode->extensionMenu_->GetRenderContext()->GetOpacity(), 0.0);
    EXPECT_EQ(selectOverlayNode->backButton_->GetRenderContext()->GetOpacity(), 0.0);
}

/**
 * @tc.name: ShowSelectOverlay001
 * @tc.desc: Test hasShowAnimation_ value change situation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    bool animate[2] = { true, false };
    /**
     * @tc.steps: step2. call ShowSelectOverlay  .
     * @tc.expected: the hasShowAnimation_ value was successfully changed.
     */
    for (int i = 0; i < 2; i++) {
        selectOverlayNode->ShowSelectOverlay(animate[i]);
        EXPECT_EQ(pattern->hasShowAnimation_, animate[i]);
    }
}

/**
 * @tc.name: HideSelectOverlay001
 * @tc.desc: Test select_overlay_node HideSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HideSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ShowSelectOverlay  .
     * @tc.expected: the circlesAndBackArrowOpacity_ value was successfully changed.
     */
    pattern->CreateNodePaintMethod();
    ASSERT_NE(pattern->selectOverlayModifier_, nullptr);
    selectOverlayNode->HideSelectOverlay([]() {});
    EXPECT_EQ(pattern->selectOverlayModifier_->circlesAndBackArrowOpacity_->Get(), 0.0);
}

/**
 * @tc.name: UpdateToolBar001
 * @tc.desc: Test select_overlay_node UpdateToolBar.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateToolBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern six situation.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
            case 3:
                selectInfo.menuInfo.menuDisable = true;
                break;
            case 1:
            case 4:
                selectInfo.menuInfo.menuDisable = false;
                selectInfo.menuInfo.menuIsShow = true;
                break;
            case 2:
            case 6:
                selectInfo.menuInfo.menuDisable = false;
                selectInfo.menuInfo.menuIsShow = false;
                break;
            default:
                break;
        }

        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        selectOverlayNode->isExtensionMenu_ = true;
        selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
        selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        if (i < 3) {
            selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE;
            selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::GONETOVISIBLE;
            selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONETOVISIBLE;
        }
        EXPECT_NE(selectOverlayNode->backButton_, nullptr);
        EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayNode->CreateToolBar();
        /**
         * @tc.steps: step3. call UpdateToolBar for call the other function .
         * @tc.expected: the isExtensionMenu_ value was successfully changed.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        selectOverlayNode->UpdateToolBar(false);

        EXPECT_TRUE(selectOverlayNode->isExtensionMenu_);

        selectOverlayNode->UpdateToolBar(true);

        EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
    }
}

/**
 * @tc.name: ContentModifierOnDraw001
 * @tc.desc: Test select_ovelay_content_modifier onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ContentModifierOnDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern,canvs
     * and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [selectTheme, textOverlayTheme, iconTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == SelectTheme::TypeId()) {
                return selectTheme;
            }
            if (type == TextOverlayTheme::TypeId()) {
                return textOverlayTheme;
            }
            if (type == IconTheme::TypeId()) {
                return iconTheme;
            }
            return textOverlayTheme;
        });
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(textOverlayTheme));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(contentModifier, nullptr);
    EXPECT_NE(overlayModifier, nullptr);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(AtLeast(1));
    DrawingContext context { canvas, 100, 100 };
    /**
     * @tc.steps: step2. get the contentModifier and initialize properies and call onDraw function.
     * @tc.expected: the innerHandleRadius_ value is correct.
     */
    contentModifier->SetIsSingleHandle(true);
    contentModifier->SetFirstHandleIsShow(true);
    contentModifier->SetInShowArea(true);
    EXPECT_EQ(contentModifier->inShowArea_->Get(), true);
    contentModifier->SetHandleReverse(false);
    EXPECT_EQ(contentModifier->handleReverse_->Get(), false);
    contentModifier->SetViewPort(SECOND_HANDLE_REGION);
    EXPECT_EQ(contentModifier->viewPort_->Get(), SECOND_HANDLE_REGION);
    contentModifier->SetFirstHandle(SECOND_HANDLE_REGION);
    EXPECT_EQ(contentModifier->firstHandle_->Get(), SECOND_HANDLE_REGION);
    contentModifier->SetSecondHandle(SECOND_HANDLE_REGION);
    EXPECT_EQ(contentModifier->secondHandle_->Get(), SECOND_HANDLE_REGION);
    contentModifier->SetHandleColor(Color::RED);
    EXPECT_EQ(contentModifier->handleColor_->Get(), Color::RED);
    contentModifier->SetInnerHandleColor(Color::RED);
    EXPECT_EQ(contentModifier->innerHandleColor_->Get(), Color::RED);
    contentModifier->SetHandleRadius(2.0f);
    EXPECT_EQ(contentModifier->handleRadius_->Get(), 2.0f);
    contentModifier->SetInnerHandleRadius(2.0f);
    EXPECT_EQ(contentModifier->innerHandleRadius_->Get(), 2.0f);
    contentModifier->SetHandleOpacity(2.0f);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 2.0f);
    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                contentModifier->SetFirstHandleIsShow(true);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), true);
                break;
            case 1:
                contentModifier->SetIsSingleHandle(true);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), true);
                contentModifier->SetFirstHandleIsShow(false);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), false);
                contentModifier->SetSecondHandleIsShow(true);
                EXPECT_EQ(contentModifier->secondHandleIsShow_->Get(), true);
                break;
            case 2:
                contentModifier->SetIsSingleHandle(false);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), false);
                contentModifier->SetFirstHandleIsShow(true);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), true);
                break;
            case 3:
                contentModifier->SetIsSingleHandle(true);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), true);
                contentModifier->SetFirstHandleIsShow(false);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), false);
                contentModifier->SetSecondHandleIsShow(false);
                EXPECT_EQ(contentModifier->secondHandleIsShow_->Get(), false);
                break;
            case 4:
                contentModifier->SetIsSingleHandle(false);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), false);
                break;
            case 5:
                contentModifier->SetInShowArea(false);
                EXPECT_EQ(contentModifier->inShowArea_->Get(), false);
                break;
            default:
                break;
        }

        contentModifier->onDraw(context);
    }
    EXPECT_EQ(contentModifier->innerHandleRadius_->Get(), 2.0f);
}

/**
 * @tc.name: ContentModifierOnDraw002
 * @tc.desc: Test select_ovelay_content_modifier onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ContentModifierOnDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern, canvas, context
     * and initialize properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    auto contentModifier = pattern->selectOverlayContentModifier_;
    EXPECT_NE(contentModifier, nullptr);

    /**
     * @tc.steps: step2. set param and call onDraw function.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
    contentModifier->isUsingMouse_ = false;
    contentModifier->SetIsHiddenHandle(true);
    contentModifier->onDraw(context);
    EXPECT_EQ(contentModifier->isHiddenHandle_->Get(), true);
}

/**
 * @tc.name: ContentModifierOnDraw003
 * @tc.desc: Test select_ovelay_content_modifier onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ContentModifierOnDraw003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern,canvs
     * and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    EXPECT_NE(contentModifier, nullptr);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, 100, 100 };
    /**
     * @tc.steps: step3. set param and call onDraw function.
     */
    contentModifier->isUsingMouse_ = false;
    contentModifier->SetIsHiddenHandle(false);
    contentModifier->SetInShowArea(true);
    contentModifier->SetIsSingleHandle(false);
    contentModifier->SetHandleReverse(true);
    contentModifier->onDraw(context);
    EXPECT_EQ(contentModifier->isHiddenHandle_->Get(), false);
}

/**
 * @tc.name: ContentModifierOnDraw004
 * @tc.desc: Test select_ovelay_content_modifier onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ContentModifierOnDraw004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern,canvs
     * and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    auto contentModifier = pattern->selectOverlayContentModifier_;
    EXPECT_NE(contentModifier, nullptr);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(AtLeast(1));
    contentModifier->isUsingMouse_ = false;
    contentModifier->SetIsHiddenHandle(false);
    contentModifier->SetInShowArea(true);

    /**
     * @tc.steps: step2. set param and call PaintSingleHandle function
    */
    contentModifier->isPaintHandleUsePoints_ = true;
    contentModifier->SetIsSingleHandle(true);
    contentModifier->firstHandlePaintInfo_.width = 6.0f;
    contentModifier->firstHandleIsShow_->Set(true);
    contentModifier->secondHandlePaintInfo_.width = 6.0f;
    contentModifier->secondHandleIsShow_->Set(true);
    contentModifier->PaintSingleHandle(canvas);
    EXPECT_EQ(contentModifier->isPaintHandleUsePoints_, true);

    /**
     * @tc.steps: step3. set param and call PaintSingleHandle function
    */
    contentModifier->isPaintHandleUsePoints_ = true;
    contentModifier->SetIsSingleHandle(false);
    contentModifier->SetFirstHandleIsShow(true);
    contentModifier->SetSecondHandleIsShow(true);
    contentModifier->PaintDoubleHandle(canvas);
    EXPECT_EQ(contentModifier->isPaintHandleUsePoints_, true);
}

/**
 * @tc.name: OverlayModifierOnDraw001
 * @tc.desc: Test select_ovelay_modifier onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OverlayModifierOnDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern,canvs
     * and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(overlayModifier, nullptr);
    Testing::MockCanvas canvas;
    DrawingContext context = GetDrawingContext(canvas);
    for (int32_t i = 0; i < 4; i++) {
        overlayModifier->circleOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
        EXPECT_NE(overlayModifier->circleOffset_[i], nullptr);
        if (i < 4 - 1) {
            overlayModifier->lineEndOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
            EXPECT_NE(overlayModifier->lineEndOffset_[i], nullptr);
        }
    }
    overlayModifier->rotationAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetMenuOptionOffset(offset);
    overlayModifier->pointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetHeadPointRadius(Dimension(1.0));
    /**
     * @tc.steps: step2. call onDraw.
     * @tc.expected: the menuOptionOffset_ value is correct.
     */
    overlayModifier->onDraw(context);
    EXPECT_EQ(overlayModifier->hasExtensionMenu_->Get(), false);
}

/**
 * @tc.name: SelectOverlayLayout002
 * @tc.desc: Test selectOverlay layout when checkIsInShowArea is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.useFullScreen = false;
    bool isSingleHandle[2] = { false, true };
    for (int i = 0; i < 2; i++) {
        selectInfo.isSingleHandle = isSingleHandle[i];
        selectInfo.firstHandle.paintRect = FIRST_HANDLE_REGION;
        selectInfo.secondHandle.paintRect = SECOND_HANDLE_REGION;
        selectInfo.showArea = FIRST_HANDLE_REGION;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern and geometryNode.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        /**
         * @tc.steps: step3. Get layoutWrapper and layoutAlgorithm.
         * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
         */
        LayoutWrapperNode* layoutWrapper =
            new LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
        auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
        ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
        layoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

        auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
        // create menu
        auto item = FrameNode::GetOrCreateFrameNode(
            V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
        // add item to selectOverlayNode
        selectOverlayNode->AddChild(item);
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(item, itemGeometryNode, item->GetLayoutProperty());
        EXPECT_FALSE(itemLayoutWrapper == nullptr);
        auto itemPattern = item->GetPattern<MenuPattern>();
        EXPECT_FALSE(itemPattern == nullptr);
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
        EXPECT_FALSE(itemLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper->AppendChild(itemLayoutWrapper);
        /**
         * @tc.steps: step4. use layoutAlgorithm to measure and layout.
         * @tc.expected: RemoveChildInRenderTree is executed successfully when checkIsInShowArea is false.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayLayoutAlgorithm->Layout(layoutWrapper);
        EXPECT_FALSE(layoutWrapper->isActive_);
    }
}

/**
 * @tc.name: IsMenuShow001
 * @tc.desc: Test IsMenuShow function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsMenuShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and call IsMenuShow function.
     * @tc.expected: The isMenuShow returns false
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsMenuShow());
}

/**
 * @tc.name: IsHandleShow001
 * @tc.desc: Test IsHandleShow function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsHandleShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and call IsHandleShow function.
     * @tc.expected: The IsHandleShow returns true.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsHandleShow());
}

/**
 * @tc.name: StartHiddenHandleTask001
 * @tc.desc: Test StartHiddenHandleTask function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, StartHiddenHandleTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    ASSERT_NE(taskExecutor, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = taskExecutor;
    /**
     * @tc.steps: step2. Create pattern and call StartHiddenHandleTask function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StartHiddenHandleTask();
}

/**
 * @tc.name: HiddenHandle001
 * @tc.desc: Test HiddenHandle function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HiddenHandle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and call HiddenHandle function.
     * @tc.expected: The selectInfo->isHiddenHandle_ value is true
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isHiddenHandle_ = false;
    pattern->HiddenHandle();
    EXPECT_TRUE(pattern->isHiddenHandle_);
}

/**
 * @tc.name: StopHiddenHandleTask001
 * @tc.desc: Test StopHiddenHandleTask function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, StopHiddenHandleTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and call StopHiddenHandleTask function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StopHiddenHandleTask();
}

/**
 * @tc.name: UpdateSelectArea001
 * @tc.desc: Test UpdateSelectArea function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call UpdateSelectArea function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetSelectOverlayInfo()->selectArea, RectF());
    RectF area;
    area = RectF(1, 1, 1, 1);
    pattern->UpdateSelectArea(area);
    EXPECT_EQ(pattern->GetSelectOverlayInfo()->selectArea, area);
}

/**
 * @tc.name: SetIsNewAvoid001
 * @tc.desc: Test SetIsNewAvoid function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetIsNewAvoid001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call SetIsNewAvoid function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->GetSelectOverlayInfo()->isNewAvoid);
    pattern->SetIsNewAvoid(true);
    EXPECT_TRUE(pattern->GetSelectOverlayInfo()->isNewAvoid);
}

/**
 * @tc.name: CheckIfNeedMenuOrHandle001
 * @tc.desc: Test CheckIfNeedMenuOrHandle function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CheckIfNeedMenuOrHandle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    std::vector<SelectOverlayMode> selectOverlayModeVec {
        SelectOverlayMode::ALL, SelectOverlayMode::MENU_ONLY, SelectOverlayMode::HANDLE_ONLY };

    /**
     * @tc.steps: step2. Create selectOverlay node in each SelectOverlayMode.
     */
    for (const auto& selectOverlayMode : selectOverlayModeVec) {
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr, selectOverlayMode);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);

        /**
         * @tc.steps: step3. Create pattern and call CheckIfNeedMenu function.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        EXPECT_EQ(pattern->GetMode(), selectOverlayMode);
        if (selectOverlayMode == SelectOverlayMode::ALL ||
            selectOverlayMode == SelectOverlayMode::MENU_ONLY) {
            EXPECT_TRUE(pattern->CheckIfNeedMenu());
        } else {
            EXPECT_FALSE(pattern->CheckIfNeedMenu());
        }

        /**
         * @tc.steps: step4. Call CheckIfNeedHandle function.
         */
        if (selectOverlayMode == SelectOverlayMode::ALL ||
            selectOverlayMode == SelectOverlayMode::HANDLE_ONLY) {
            EXPECT_TRUE(pattern->CheckIfNeedHandle());
        } else {
            EXPECT_FALSE(pattern->CheckIfNeedHandle());
        }
    }
}

/**
 * @tc.name: GetHandleDiameter001
 * @tc.desc: Test GetHandleDiameter function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetHandleDiameter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call GetHandleDiameter function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetHandleDiameter(), 0.0f);
}

/**
 * @tc.name: OnDpiConfigurationUpdate001
 * @tc.desc: Test OnDpiConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnDpiConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call OnDpiConfigurationUpdate function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDpiConfigurationUpdate();
    EXPECT_FALSE(selectOverlayNode->GetIsExtensionMenu());
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call OnColorConfigurationUpdate function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(selectOverlayNode->GetIsExtensionMenu());
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Test OnThemeScopeUpdate function when api target version is less than VERSION_TWENTY_SIX.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call OnThemeScopeUpdate function.
     * @tc.expected: The function returns true.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(TEST_THEME_SCOPE_ID));
}

/**
 * @tc.name: OnThemeScopeUpdate002
 * @tc.desc: Test OnThemeScopeUpdate function when api target version is greater than or equal to VERSION_TWENTY_SIX.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnThemeScopeUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call OnThemeScopeUpdate function.
     * @tc.expected: The function returns true.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->OnThemeScopeUpdate(TEST_THEME_SCOPE_ID));
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: Test OnDetachFromFrameNodee function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto testCallback = [](bool closedByGlobalTouchEvent_) {
        callBackFlag = static_cast<int32_t>(closedByGlobalTouchEvent_);
        return;
    };
    selectInfo.onClose = testCallback;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call OnDetachFromFrameNode function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNode(
        FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton", ElementRegister::GetInstance()->MakeUniqueId(), []() {
            return AceType::MakeRefPtr<ButtonPattern>();
        }).GetRawPtr());
    EXPECT_FALSE(pattern->closedByGlobalTouchEvent_);
    EXPECT_EQ(callBackFlag, 0);
}

/**
 * @tc.name: SetHandleReverse001
 * @tc.desc: Test SetHandleReverse function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetHandleReverse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.steps: step2. Create pattern and call SetHandleReverse function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    pattern->info_->handleReverse = true;
    pattern->SetHandleReverse(true);
    EXPECT_TRUE(pattern->info_->handleReverse);
    pattern->SetHandleReverse(false);
    EXPECT_FALSE(pattern->info_->handleReverse);
}

/**
 * @tc.name: UpdateSelectMenuInfo001
 * @tc.desc: Test UpdateSelectMenuInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectMenuInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call UpdateSelectMenuInfo function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectMenuInfo infoMenu;
    OffsetF testCase(4, 5);
    infoMenu.menuOffset = testCase;
    pattern->UpdateSelectMenuInfo(infoMenu);
    EXPECT_EQ(pattern->info_->menuInfo.menuOffset, testCase);
}

/**
 * @tc.name: ShowOrHiddenMenu001
 * @tc.desc: Test ShowOrHiddenMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowOrHiddenMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call ShowOrHiddenMenu function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    for (int i = 0; i < 2; ++i) {
        bool isHidden = i;
        for (int j = 0; j < 2; ++j) {
            infoPtr->menuInfo.menuIsShow = j;
            for (int k = 0; k < 4; ++k) {
                infoPtr->firstHandle.isShow = k & 1;
                infoPtr->secondHandle.isShow = k >> 1 & 1;
                pattern->ShowOrHiddenMenu(isHidden);
                if (infoPtr->menuInfo.menuIsShow && isHidden) {
                    EXPECT_FALSE(pattern->info_->menuInfo.menuIsShow);
                } else if (!infoPtr->menuInfo.menuIsShow && !isHidden &&
                           (infoPtr->firstHandle.isShow || infoPtr->secondHandle.isShow)) {
                    EXPECT_TRUE(pattern->info_->menuInfo.menuIsShow);
                }
            }
        }
    }
}

/**
 * @tc.name: DisableMenu001
 * @tc.desc: Test DisableMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, DisableMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call DisableMenu function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    std::vector<bool> testCases = { true, false };
    for (uint32_t turn = 0; turn < testCases.size(); ++turn) {
        pattern->DisableMenu(testCases[turn]);
        EXPECT_EQ(pattern->info_->menuInfo.menuDisable, testCases[turn]);
    }
}

/**
 * @tc.name: SetClosedByGlobalEvent001
 * @tc.desc: Test SetClosedByGlobalEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetClosedByGlobalEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call SetClosedByGlobalEvent function.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->SetClosedByGlobalEvent(true);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->closedByGlobalTouchEvent_);
}

/**
 * @tc.name: UpdateToolBar002
 * @tc.desc: Test select_overlay_node UpdateToolBar.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateToolBar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern six situation.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->isExtensionMenu_ = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE;
    selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::GONETOVISIBLE;
    selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONETOVISIBLE;
    ASSERT_NE(selectOverlayNode->backButton_, nullptr);
    ASSERT_NE(selectOverlayNode->selectMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return;
    };
    infoPtr->menuCallback.onPaste = []() {
        callBackFlag = 2;
        return;
    };

    /**
    * @tc.steps: step3. call UpdateToolBar for call the other function.
    * @tc.expected: the isExtensionMenu_ value was successfully changed.
    */
    selectOverlayNode->UpdateToolBar(false);
    EXPECT_TRUE(selectOverlayNode->isExtensionMenu_);
    selectOverlayNode->UpdateToolBar(true);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
    EXPECT_TRUE(selectOverlayNode->isShowInDefaultMenu_[OPTION_INDEX_COPY]);
}

/**
 * @tc.name: ExecuteOverlayStatus001
 * @tc.desc: Test ExecuteOverlayStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ExecuteOverlayStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call ExecuteOverlayStatus function.
     */

    FrameNodeType type = (FrameNodeType) 4;
    selectOverlayNode->ExecuteOverlayStatus(type, FrameNodeTrigger::HIDDEN);
    ASSERT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: SetFrameNodeOpacity002
 * @tc.desc: Test SetFrameNodeOpacity function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeOpacity002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call SetFrameNodeOpacity function.
     */

    FrameNodeType type = (FrameNodeType) 4;
    selectOverlayNode->SetFrameNodeOpacity(type, 0.0);
    ASSERT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: SetFrameNodeVisibility002
 * @tc.desc: Test SetFrameNodeVisibility function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeVisibility002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call SetFrameNodeVisibility function.
     */

    FrameNodeType type = (FrameNodeType) 4;
    selectOverlayNode->SetFrameNodeVisibility(type, VisibleType::INVISIBLE);
    ASSERT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: SetFrameNodeStatus002
 * @tc.desc: Test SetFrameNodeStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeStatus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call SetFrameNodeStatus function.
     */

    FrameNodeType type = (FrameNodeType) 4;
    selectOverlayNode->SetFrameNodeStatus(type, FrameNodeStatus::VISIBLE);
    ASSERT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: SelectOverlayNodeTest003
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea with menuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNodeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;

    /**
     * @tc.steps: step3. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return false
     */
    pattern->info_->menuInfo.menuBuilder = []() {
        return ;
    };
    frameNode->geometryNode_ = nullptr;
    selectOverlayNode->selectMenu_ = nullptr;
    selectOverlayNode->extensionMenu_ = nullptr;
    const NG::PointF point { 9.0f, 12.0f };
    auto result = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return true
     */
    const NG::PointF point2 { 12.0f, 12.0f };
    auto result2 = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point2);
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: DispatchGoneToVisibleState01
 * @tc.desc: Test DispatchGoneToVisibleState function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, DispatchGoneToVisibleState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call DispatchGoneToVisibleState function.
     */
    FrameNodeType type = FrameNodeType::BACKBUTTON;
    FrameNodeTrigger trigger = (FrameNodeTrigger) 4;
    selectOverlayNode->DispatchGoneToVisibleState(type, trigger);
    ASSERT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: DispatchGoneState001
 * @tc.desc: Test DispatchGoneState function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, DispatchGoneState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call DispatchGoneState function.
     */
    FrameNodeType type = FrameNodeType::BACKBUTTON;
    FrameNodeTrigger trigger = (FrameNodeTrigger) 4;
    selectOverlayNode->DispatchGoneState(type, trigger);
    ASSERT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: IsTextAreaSelectAll001
 * @tc.desc: Test IsTextAreaSelectAll in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsTextAreaSelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectInfo
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;

    /**
    * @tc.steps: step2. Get layoutWrapper and layoutAlgorithm.
    */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);

    /**
    * @tc.steps: step3. Test cases.
    */
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    for (int i = 0; i < 2; ++i) {
        infoPtr->firstHandle.isShow = i;
        for (int j = 0; j < 2; ++j) {
            infoPtr->secondHandle.isShow = j;
            EXPECT_FALSE(newNode->IsTextAreaSelectAll());
        }
    }

    infoPtr->menuInfo.menuOffset = {0, 0};
    for (int i = 0; i < 2; ++i) {
        infoPtr->firstHandle.isShow = i;
        for (int j = 0; j < 2; ++j) {
            infoPtr->secondHandle.isShow = j;
            EXPECT_EQ(newNode->IsTextAreaSelectAll(), i == 0 || j == 0);
        }
    }
}

/**
 * @tc.name: ComputeExtensionMenuPosition001
 * @tc.desc: Test ComputeExtensionMenuPosition in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ComputeExtensionMenuPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectInfo
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;

    /**
    * @tc.steps: step2. Get layoutWrapper and layoutAlgorithm.
    */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);

    /**
    * @tc.steps: step3. Test Case.
    */
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    newNode->ComputeSelectMenuPosition(AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: CheckInShowArea001
 * @tc.desc: Test CheckInShowArea in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CheckInShowArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectInfo
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;

    /**
    * @tc.steps: step2. Get layoutWrapper and layoutAlgorithm.
    */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);

    /**
    * @tc.steps: step3. Test cases.
    */
    std::vector<RectF> handlePaintRect = {
        {1, 1, 1, 1}, {3, 3, 1, 1}
    };
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    SelectOverlayInfo selectInfo1;
    selectInfo1.useFullScreen = false;
    selectInfo1.isSingleHandle = false;
    selectInfo1.showArea = {1, 1, 1, 1};

    for (uint32_t first = 0; first < handlePaintRect.size(); ++first) {
        selectInfo1.firstHandle.paintRect = handlePaintRect[first];
        for (uint32_t second = 0; second < handlePaintRect.size(); ++second) {
            selectInfo1.secondHandle.paintRect = handlePaintRect[second];
            bool expectRes = (first == 0) && (second == 0);
            EXPECT_EQ(newNode->CheckInShowArea(selectInfo1), expectRes);
        }
    }
}

/**
 * @tc.name: ComputeSelectMenuPosition001
 * @tc.desc: Test ComputeSelectMenuPosition in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ComputeSelectMenuPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.menuInfo.menuIsShow = false;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
    * @tc.steps: step2. Create pattern and geometryNode.
    */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize({ 300, 150 });

    /**
    * @tc.steps: step3. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    // create menu and extensionMenu
    auto item = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
    // add item to selectOverlayNode
    selectOverlayNode->AddChild(item);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();

    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize({ 2, 1 });

    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(item, firstGeometryNode, item->GetLayoutProperty());
    ASSERT_NE(firstLayoutWrapper, nullptr);
    auto itemPattern = item->GetPattern<MenuPattern>();
    ASSERT_NE(itemPattern, nullptr);
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
    ASSERT_NE(itemLayoutAlgorithm, nullptr);

    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper->AppendChild(firstLayoutWrapper);

    /**
    * @tc.steps: step4. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    infoPtr->firstHandle.paintRect = {
        1, 1, 1, 1
    };
    infoPtr->secondHandle.paintRect = {
        3, 3, 1, 1
    };

    auto ret1 = newNode->ComputeSelectMenuPosition(AccessibilityManager::RawPtr(layoutWrapper));
    OffsetF expectRet1(16.0, 2.0);
    bool equal1 = (ret1 == expectRet1);
    EXPECT_TRUE(equal1);

    infoPtr->firstHandle.isShow = false;
    infoPtr->menuInfo.menuOffset = {1, 1};
    infoPtr->secondHandle.isShow = false;
    infoPtr->isSingleHandle = true;
    auto ret2 = newNode->ComputeSelectMenuPosition(AccessibilityManager::RawPtr(layoutWrapper));
    OffsetF expectRet2(16.0, 1.0);
    bool equal2 = (ret2 == expectRet2);
    EXPECT_TRUE(equal2);
}

/**
 * @tc.name: NewMenuAvoidStrategy001
 * @tc.desc: Test NewMenuAvoidStrategy001 in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, NewMenuAvoidStrategy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.selectArea = { 100, 500, 200, 50 };

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
    * @tc.steps: step2. Create pattern and geometryNode.
    */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    /**
    * @tc.steps: step3. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);

    /**
    * @tc.steps: step4. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    auto menuWidth = 200;
    auto menuHeight = 100;
    auto ret1 = newNode->NewMenuAvoidStrategy(AccessibilityManager::RawPtr(layoutWrapper), menuWidth, menuHeight);
    std::cout << ret1.ToString();
    OffsetF expectRet1(100, 398);
    bool equal1 = (ret1 == expectRet1);
    EXPECT_TRUE(equal1);

    infoPtr->firstHandle.isShow = false;
    infoPtr->secondHandle.isShow = false;
    auto ret2 = newNode->NewMenuAvoidStrategy(AccessibilityManager::RawPtr(layoutWrapper), menuWidth, menuHeight);
    OffsetF expectRet2(100, -100);
    bool equal2 = (ret2 == expectRet2);
    EXPECT_TRUE(equal2);

    infoPtr->firstHandle.isShow = false;
    infoPtr->secondHandle.isShow = true;
    auto ret3 = newNode->NewMenuAvoidStrategy(AccessibilityManager::RawPtr(layoutWrapper), menuWidth, menuHeight);
    OffsetF expectRet3(100, 0);
    bool equal3 = (ret3 == expectRet3);
    EXPECT_TRUE(equal3);
}

/**
 * @tc.name: NewMenuAvoidStrategy002
 * @tc.desc: Test NewMenuAvoidStrategy002 in Select Overlay algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, NewMenuAvoidStrategy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.selectArea = { 100, 500, 200, 50 };

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
    * @tc.steps: step2. Create pattern and geometryNode.
    */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    /**
    * @tc.steps: step3. Get layoutWrapper and layoutAlgorithm.
    * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
    */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);

    /**
    * @tc.steps: step4. set keyboardInset_ to button.
    */
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = RK356_HEIGHT - 1;
    insetBottom.end = RK356_HEIGHT;
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->safeAreaManager_ = safeAreamanager;

    /**
    * @tc.steps: step5. Test cases.
    */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    auto menuWidth = 200;
    auto menuHeight = 100;
    infoPtr->firstHandle.isShow = false;
    infoPtr->secondHandle.isShow = false;
    auto ret = newNode->NewMenuAvoidStrategy(AccessibilityManager::RawPtr(layoutWrapper), menuWidth, menuHeight);
    OffsetF expectRet(100, 200);
    bool equal = (ret == expectRet);
    EXPECT_TRUE(equal);
}

/**
 * @tc.name: UpdateFirstAndSecondHandleInfo001
 * @tc.desc: Test SelectOverlayPattern UpdateFirstAndSecondHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateFirstAndSecondHandleInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    /**
     * @tc.steps: step3. Test cases.
     */
    SelectHandleInfo comInfoFirst;
    comInfoFirst.isShow = true;
    SelectHandleInfo comInfoSecond;
    comInfoSecond.isShow = false;

    pattern->info_->firstHandle.isShow = true;
    pattern->info_->secondHandle.isShow = true;
    pattern->UpdateFirstAndSecondHandleInfo(comInfoFirst, comInfoSecond);
    EXPECT_EQ(pattern->info_->firstHandle, comInfoFirst);
    EXPECT_EQ(pattern->info_->secondHandle, comInfoSecond);

    pattern->info_->firstHandle.isShow = true;
    pattern->info_->secondHandle.isShow = true;
    pattern->UpdateFirstAndSecondHandleInfo(comInfoSecond, comInfoFirst);
    EXPECT_EQ(pattern->info_->firstHandle, comInfoSecond);
    EXPECT_EQ(pattern->info_->secondHandle, comInfoFirst);

    pattern->info_->firstHandle.isShow = true;
    pattern->info_->secondHandle.isShow = true;
    pattern->UpdateFirstAndSecondHandleInfo(comInfoSecond, comInfoSecond);
    EXPECT_EQ(pattern->info_->firstHandle, comInfoSecond);
    EXPECT_EQ(pattern->info_->secondHandle, comInfoSecond);

    pattern->info_->firstHandle.isShow = true;
    pattern->info_->secondHandle.isShow = true;
    pattern->UpdateFirstAndSecondHandleInfo(comInfoFirst, comInfoFirst);
    EXPECT_EQ(pattern->info_->firstHandle, comInfoFirst);
    EXPECT_EQ(pattern->info_->firstHandle, comInfoFirst);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: Test SelectOverlayPattern BeforeCreateLayoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, BeforeCreateLayoutWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(pattern, nullptr);
    callBackFlag = 1;
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(callBackFlag, 1);
    pattern->info_->menuInfo.menuBuilder = []() {
        callBackFlag = 2;
        return;
    };
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(callBackFlag, 1);

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    // create menu and extensionMenu
    auto item = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
    // add item to selectOverlayNode
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    selectOverlayNode->AddChild(item);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(callBackFlag, 1);
}

/**
 * @tc.name: AddMenuResponseRegion001
 * @tc.desc: Test SelectOverlayPattern AddMenuResponseRegion.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuResponseRegion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    // create menu and extensionMenu
    auto item = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
    // add item to selectOverlayNode
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    selectOverlayNode->AddChild(item);

    std::vector<DimensionRect> tmp;
    auto layoutProperty = pattern->CreateLayoutProperty();
    frameNode->SetLayoutProperty(layoutProperty);
    pattern->AddMenuResponseRegion(tmp);
    EXPECT_EQ(tmp.size(), 2);

    tmp.clear();
    auto layoutProps = pattern->GetLayoutProperty<LayoutProperty>();
    layoutProps->UpdateSafeAreaInsets(SafeAreaInsets());
    pattern->AddMenuResponseRegion(tmp);
    EXPECT_EQ(tmp.size(), 2);
    // if TextOverlayTheme is NULL, SelectOverlayNode::CreateToolBar() still continue, result in 2 children.
}

/**
 * @tc.name: GetDefaultLineWidth001
 * @tc.desc: Test SelectOverlayPattern GetDefaultLineWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetDefaultLineWidth001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    Dimension dimension = SelectHandleInfo::GetDefaultLineWidth();
    EXPECT_EQ(dimension.Value(), 2);
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test SelectOverlayLayoutAlgorithm Measure.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, Measure001, TestSize.Level1)
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
    pattern->info_->menuInfo.menuBuilder = []() { return; };
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    auto item = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    selectOverlayNode->AddChild(item);
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize({ 2, 1 });
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(item, firstGeometryNode, item->GetLayoutProperty());
    auto itemPattern = item->GetPattern<MenuPattern>();
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper->AppendChild(firstLayoutWrapper);
    selectOverlayLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetChildByIndex(1), nullptr);
}

/**
 * @tc.name: Measure002
 * @tc.desc: Test SelectOverlayLayoutAlgorithm Measure.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, Measure002, TestSize.Level1)
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
    pattern->info_->menuInfo.menuBuilder = nullptr;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    auto item = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    selectOverlayNode->AddChild(item);
    auto layoutProperty = pattern->CreateLayoutProperty();
    selectOverlayLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetChildByIndex(1), nullptr);
}

/**
 * @tc.name: Measure003
 * @tc.desc: Test SelectOverlayLayoutAlgorithm Measure.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, Measure003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Construct the root node and set its size
    */

    SelectOverlayInfo selectInfo;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline->rootNode_, nullptr);
    ASSERT_NE(pipeline->rootNode_->GetGeometryNode(), nullptr);
    pipeline->rootNode_->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 50.0f));

    /**
    * @tc.steps: step2. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */

    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr, SelectOverlayMode::HANDLE_ONLY);
    frameNode->MountToParent(pipeline->rootNode_);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    pattern->info_->menuInfo.menuBuilder = nullptr;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
    * @tc.steps: step3. Get the layout algorithm.
    * Call the measure function of the layout algorithm.
    */

    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto layoutProperty = pattern->CreateLayoutProperty();
    selectOverlayLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));

    /**
    * @tc.steps: step4. Contrast.
    * expected: geometryNode size is SizeF(100.0f, 50.0f).
    */

    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(100.0f, 50.0f));
}

/**
* @tc.name: Measure004
* @tc.desc: Test SelectOverlayLayoutAlgorithm Measure.
* @tc.type: FUNC
*/
HWTEST_F(SelectOverlayTestNg, Measure004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Construct the selectInfo.
    */
    SelectOverlayInfo selectInfo;
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = FIRST_HANDLE_REGION;
    SelectHandleInfo secondHandle;
    secondHandle.paintRect = SECOND_HANDLE_REGION2;
    selectInfo.firstHandle = firstHandle;
    selectInfo.secondHandle = secondHandle;
    selectInfo.selectArea = { 100, 500, 200, 50 };

    /**
    * @tc.steps: step2. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    /**
    * @tc.steps: step3. Set up custom menu.
    */

    pattern->info_->menuInfo.menuBuilder = []() { return; };
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);

    /**
    * @tc.steps: step4. SelectOverlayNode append child.
    */

    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    auto item = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    selectOverlayNode->AddChild(item);

    auto pattern1 = item->GetPattern();
    ASSERT_NE(pattern1, nullptr);
    item->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    /**
    * @tc.steps: step5. Set DisplayWindowRectInfo.
    */

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 800, 800 }); // 800: window width and height

    /**
    * @tc.steps: step6. Get the layout algorithm.
    * Call the measure function of the layout algorithm.
    */

    selectOverlayLayoutAlgorithm->Measure(AceType::RawPtr(selectOverlayNode));

    EXPECT_EQ(item->GetGeometryNode()->GetFrameSize(), SizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT));
    EXPECT_NE(selectOverlayNode->GetChildByIndex(0), nullptr);
}

/**
* @tc.name: Measure005
* @tc.desc: Test SelectOverlayLayoutAlgorithm Measure.
* @tc.type: FUNC
*/
HWTEST_F(SelectOverlayTestNg, Measure005, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Construct the selectInfo.
    */
    SelectOverlayInfo selectInfo;
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = FIRST_HANDLE_REGION;
    SelectHandleInfo secondHandle;
    secondHandle.paintRect = SECOND_HANDLE_REGION2;
    selectInfo.firstHandle = firstHandle;
    selectInfo.secondHandle = secondHandle;
    selectInfo.selectArea = { 100, 500, 200, 50 };

    /**
    * @tc.steps: step2. Create selectOverlayNode and initialize selectOverlayInfo properties.
    */

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    /**
    * @tc.steps: step3. Set up custom menu.
    */

    pattern->info_->menuInfo.menuBuilder = []() { return; };
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);

    /**
    * @tc.steps: step4. SelectOverlayNode append children.
    */

    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    auto item = FrameNode::GetOrCreateFrameNode("TestSelectMenu", 3,
        []() { return AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::SELECT_OVERLAY_CUSTOM_MENU); });
    selectOverlayNode->AddChild(item);

    auto pattern1 = item->GetPattern();
    ASSERT_NE(pattern1, nullptr);
    item->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    auto item2 = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    item2->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    selectOverlayNode->AddChild(item2);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize({ 2, 1 });
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(item, firstGeometryNode, item->GetLayoutProperty());
    ASSERT_NE(firstLayoutWrapper, nullptr);
    auto itemPattern = item->GetPattern<MenuPattern>();
    ASSERT_NE(itemPattern, nullptr);
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
    ASSERT_NE(itemLayoutAlgorithm, nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper->AppendChild(firstLayoutWrapper);

    /**
    * @tc.steps: step5. Set DisplayWindowRectInfo.
    */

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 800, 800 }); // 800: window width and height

    /**
    * @tc.steps: step6. Get the layout algorithm.
    * Call the measure function of the layout algorithm.
    */

    selectOverlayLayoutAlgorithm->Measure(AceType::RawPtr(selectOverlayNode));

    EXPECT_EQ(item2->GetGeometryNode()->GetFrameSize(), SizeF(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT));
    EXPECT_NE(selectOverlayNode->GetChildByIndex(0), nullptr);
    EXPECT_NE(selectOverlayNode->GetChildByIndex(1), nullptr);
}
/**
 * @tc.name: CalculateCustomMenuByMouseOffset
 * @tc.desc: Test SelectOverlayLayoutAlgorithm CalculateCustomMenuByMouseOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CalculateCustomMenuByMouseOffset, TestSize.Level1)
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
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    SelectMenuInfo infoMenu;
    OffsetF testCase(4, 5);
    infoMenu.menuOffset = testCase;
    pattern->UpdateSelectMenuInfo(infoMenu);
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    newNode->CalculateCustomMenuByMouseOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(pattern->info_->menuInfo.menuOffset, testCase);
}

/**
 * @tc.name: CalculateCustomMenuLayoutConstraint
 * @tc.desc: Test SelectOverlayLayoutAlgorithm CalculateCustomMenuLayoutConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CalculateCustomMenuLayoutConstraint, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = FIRST_HANDLE_REGION;
    SelectHandleInfo secondHandle;
    secondHandle.paintRect = SECOND_HANDLE_REGION2;
    selectInfo.firstHandle = firstHandle;
    selectInfo.secondHandle = secondHandle;
    selectInfo.selectArea = { 100, 500, 200, 50 };

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    pattern->info_->menuInfo.menuBuilder = []() { return; };
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);

    auto menu = layoutWrapper->GetOrCreateChildByIndex(0);
    auto item = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "test", TYPE); });
    selectOverlayNode->AddChild(item);

    layoutWrapper->GetGeometryNode()->GetFrameOffset() = OFFSET_ITEM1;
    infoPtr->isNewAvoid = false;
    infoPtr->isUsingMouse = false;
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    newNode->CalculateCustomMenuLayoutConstraint(AceType::RawPtr(layoutWrapper), childLayoutConstraint);
    EXPECT_EQ(childLayoutConstraint.selfIdealSize.Height(), 45);
}

/**
 * @tc.name: CalculateCustomMenuByMouseOffset002
 * @tc.desc: Test SelectOverlayLayoutAlgorithm CalculateCustomMenuByMouseOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CalculateCustomMenuByMouseOffset002, TestSize.Level1)
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
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto item = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
    selectOverlayNode->AddChild(item);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize({ 2, 1 });
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(item, firstGeometryNode, item->GetLayoutProperty());
    ASSERT_NE(firstLayoutWrapper, nullptr);
    auto itemPattern = item->GetPattern<MenuPattern>();
    ASSERT_NE(itemPattern, nullptr);
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
    ASSERT_NE(itemLayoutAlgorithm, nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper->AppendChild(firstLayoutWrapper);

    SelectMenuInfo infoMenu;
    OffsetF testCase(4, 5);
    infoMenu.menuOffset = testCase;
    pattern->UpdateSelectMenuInfo(infoMenu);
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    newNode->CalculateCustomMenuByMouseOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(pattern->info_->menuInfo.menuOffset->GetX(), 4.0f);
}

/**
 * @tc.name: StartHiddenHandleTask002
 * @tc.desc: Test SelectOverlayPattern StartHiddenHandleTask.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, StartHiddenHandleTask002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    bool isDelay = false;
    RectF area;
    area = RectF(1, 1, 1, 1);
    pattern->UpdateShowArea(area);
    pattern->StartHiddenHandleTask(isDelay);
    EXPECT_NE(pattern->GetSelectOverlayInfo(), nullptr);
}

/**
 * @tc.name: SetSelectRegionVisible001
 * @tc.desc: Test SelectOverlayPattern SetSelectRegionVisible.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetSelectRegionVisible001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    bool isSelectRegionVisible = true;
    pattern->SetSelectRegionVisible(isSelectRegionVisible);
    EXPECT_EQ(pattern->info_->isSelectRegionVisible, true);
}

/**
 * @tc.name: SetSelectRegionVisible002
 * @tc.desc: Test SelectOverlayPattern SetSelectRegionVisible.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetSelectRegionVisible002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    bool isSelectRegionVisible = false;
    pattern->SetSelectRegionVisible(isSelectRegionVisible);
    EXPECT_EQ(pattern->info_->isSelectRegionVisible, false);
}

/**
 * @tc.name: UpdateSelectMenuInfo002
 * @tc.desc: Test SelectOverlayPattern UpdateSelectMenuInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectMenuInfo002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectMenuInfo infoMenu;
    OffsetF testCase(0, 0);
    infoMenu.menuOffset = testCase;
    pattern->UpdateSelectMenuInfo(infoMenu);
    EXPECT_EQ(pattern->info_->menuInfo.menuOffset, testCase);
}

/**
 * @tc.name: CreateToolBar001
 * @tc.desc: Test SelectOverlayNode CreateToolBar001.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateToolBar001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.menuBuilder = []() { return; };
    selectInfo.menuCallback.onAppear = []() { return; };
    selectInfo.menuCallback.onDisappear = []() { return; };
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->CreateToolBar();
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
}

/**
 * @tc.name: CreateToolBar002
 * @tc.desc: Test SelectOverlayNode CreateToolBar002.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateToolBar002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.menuInfo.menuBuilder = []() { return; };
    selectInfo.menuCallback.onAppear = []() { return; };
    selectInfo.menuCallback.onDisappear = []() { return; };
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->CreateToolBar();
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
}

/**
 * @tc.name: AddSystemDefaultOptions001
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.showCameraInput = true;
    float maxWidth = 2.0f;
    float allocatedSize = 3.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddSystemDefaultOptions002
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    selectInfo.menuInfo.showCameraInput = true;
    float maxWidth = 2.0f;
    float allocatedSize = 3.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddSystemDefaultOptions003
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    selectInfo.menuInfo.showCameraInput = true;
    float maxWidth = 2.0f;
    float allocatedSize = 3.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddSystemDefaultOptions004
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    selectInfo.menuInfo.showCameraInput = true;
    float maxWidth = 2.0f;
    float allocatedSize = 3.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddSystemDefaultOptions005
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    selectInfo.menuInfo.showCameraInput = false;
    float maxWidth = 2.0f;
    float allocatedSize = 3.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddSystemDefaultOptions006
 * @tc.desc: Test AddSystemDefaultOptions different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    selectInfo.menuInfo.showCameraInput = false;
    float maxWidth = 60.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    /**
     * @tc.steps: step2. call AddSystemDefaultOptions.
     * @tc.expected: the value was successfully changed.
     */
    pipeline->SetFontScale(1.85f);
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BuildButton001
 * @tc.desc: Test BuildButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, BuildButton001, TestSize.Level1)
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
    float maxWidth = 50.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return ;
    };
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    /**
     * @tc.steps: step2. call BuildButton.
     */
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_FALSE(result);
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
    EXPECT_NE(selectOverlayNode->isShowInDefaultMenu_[0], false);
}

/**
 * @tc.name: CreateSelectOverlayNode001
 * @tc.desc: Test CreateSelectOverlayNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateSelectOverlayNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern, canvas, context
     * and initialize properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    /**
     * @tc.steps: step2. set param and call function.
     */
    selectOverlayNode->DispatchVisibleToGoneState(FrameNodeType::SELECTMENU, FrameNodeTrigger::SHOW);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    /**
     * @tc.steps: step2. set param and call function.
     */
    selectOverlayNode->DispatchGoneToVisibleState(FrameNodeType::SELECTMENU, FrameNodeTrigger::HIDE);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
}

/**
 * @tc.name: DispatchVisibleToGoneState001
 * @tc.desc: Test DispatchVisibleToGoneState.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, DispatchVisibleToGoneState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern, canvas, context
     * and initialize properties.
    */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->isUsingMouse = false;
    infoPtr->isUseOverlayNG = true;
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: UpdateToolBar003
 * @tc.desc: Test SelectOverlayNode UpdateToolBar.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateToolBar003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.menuDisable = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 1);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE;
    selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::GONETOVISIBLE;
    selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONETOVISIBLE;
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->menuCallback.onCut = []() { return; };
    infoPtr->menuCallback.onPaste = []() { return; };
    infoPtr->menuInfo.menuBuilder = []() { return; };
    selectOverlayNode->backButton_ = nullptr;
    selectOverlayNode->UpdateToolBar(false);
    selectOverlayNode->UpdateToolBar(true);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: AddExtensionMenuOptions
 * @tc.desc: Test SelectOverlayNode AddExtensionMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddExtensionMenuOptions, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    for (int i = 0; i < 7; i++) {
        selectOverlayNode->isShowInDefaultMenu_[i] = false;
    }
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, -1);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
}

/**
 * @tc.name: UpdateSelectMenuInfo003
 * @tc.desc: Test SelectOverlayPattern UpdateSelectMenuInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectMenuInfo003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    auto updateAction = [](SelectMenuInfo& infoMenu) {
        return;
    };
    pattern->UpdateSelectMenuInfo(updateAction);
    std::function<void(SelectMenuInfo& infoMenu)> updateAction1 = nullptr;
    pattern->UpdateSelectMenuInfo(updateAction1);
    EXPECT_FALSE(selectInfo.menuInfo.menuDisable);
}

/**
 * @tc.name: CreateCustomSelectOverlay
 * @tc.desc: Test SelectOverlayNode CreateCustomSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateCustomSelectOverlay, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {
        return ;
    };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    selectOverlayNode->CreateCustomSelectOverlay(infoPtr);
    selectInfo.menuInfo.menuIsShow = false;
    selectOverlayNode->CreateCustomSelectOverlay(infoPtr);
    EXPECT_NE(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::GONE);

    ASSERT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto menuPattern = selectOverlayNode->selectMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    EXPECT_NE(menuPattern->GetTargetId(), -1);
}

/**
 * @tc.name: SelectOverlayModifier001
 * @tc.desc: Test selectOverlay modifier function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    EXPECT_NE(contentModifier, nullptr);
    auto selectOverlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(selectOverlayModifier, nullptr);

    /**
     * @tc.steps: step2. Test selectOverlay modifier SelectOverlayModifier function.
     */
    selectOverlayModifier->SetDefaultCircleAndLineEndOffset();
    Dimension radius = 2.0_vp;
    selectOverlayModifier->pointRadius_ =
        AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    selectOverlayModifier->SetOtherPointRadius(radius);
    EXPECT_EQ(radius, 2.0_vp);
}

/**
 * @tc.name: IsInSelectedOrSelectOverlayArea003
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea without menuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsInSelectedOrSelectOverlayArea003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return false
     */
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    const NG::PointF point { 9.0f, 12.0f };
    auto result = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsInSelectedOrSelectOverlayArea004
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea without patternChildren is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsInSelectedOrSelectOverlayArea004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;

    /**
     * @tc.steps: step3. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return false
     */
    const NG::PointF point { 9.0f, 12.0f };
    auto result = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UpdateMenuInner002
 * @tc.desc: Test UpdateMenuInner paddingWidth
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateMenuInner002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Call UpdateMenuInner.
     * @tc.expected: return false
     */

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    selectOverlayNode->UpdateMenuInner(infoPtr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: UpdateMenuInner003
 * @tc.desc: Test UpdateMenuInner
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateMenuInner003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Call UpdateMenuInner.
     * @tc.expected: return false
     */
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);

    selectOverlayNode->UpdateMenuInner(infoPtr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: UpdateMenuInner004
 * @tc.desc: Test UpdateMenuInner
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateMenuInner004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Call UpdateMenuInner.
     * @tc.expected: return false
     */

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    selectOverlayNode->UpdateMenuInner(infoPtr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: ExecuteOverlayStatus003
 * @tc.desc: Test ExecuteOverlayStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ExecuteOverlayStatus003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call ExecuteOverlayStatus function.
     */

    selectOverlayNode->ExecuteOverlayStatus(FrameNodeType::BACKBUTTON, FrameNodeTrigger::HIDDEN);
    ASSERT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: ExecuteOverlayStatus002
 * @tc.desc: Test ExecuteOverlayStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ExecuteOverlayStatus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create invalid type and call ExecuteOverlayStatus function.
     */

    selectOverlayNode->ExecuteOverlayStatus(FrameNodeType::EXTENSIONMENU, FrameNodeTrigger::HIDDEN);
    ASSERT_NE(selectOverlayNode, nullptr);
}


/**
 * @tc.name: AddSystemDefaultOptions007
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions007, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCopy = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    float maxWidth = 8.0f;
    float allocatedSize = 11.0f;
    auto ret = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AddSystemDefaultOptions008
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptions008, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCameraInput = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);

    float maxWidth = 8.0f;
    float allocatedSize = 11.0f;
    auto ret = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ShowShare002
 * @tc.desc: Test SelectOverlayNode ShowShare.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowShare002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.menuDisable = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    float maxWidth = 8.0f;
    float allocatedSize = 14.0f;
    std::string shareLabel = "分享";
    selectOverlayNode->ShowShare(maxWidth, allocatedSize, infoPtr, shareLabel);
    EXPECT_TRUE(selectOverlayNode->isDefaultBtnOverMaxWidth_);
}

/**
 * @tc.name: ShowShare003
 * @tc.desc: Test SelectOverlayNode ShowShare.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowShare003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.menuDisable = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    float maxWidth = 8.0f;
    float allocatedSize = 13.0f;
    std::string shareLabel = "分享";
    selectOverlayNode->ShowShare(maxWidth, allocatedSize, infoPtr, shareLabel);
    EXPECT_TRUE(selectOverlayNode->isDefaultBtnOverMaxWidth_);
}

/**
 * @tc.name: ShowCamera001
 * @tc.desc: Test SelectOverlayNode ShowCamera.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowCamera001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCameraInput = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);

    float maxWidth = 8.0f;
    float allocatedSize = 14.0f;
    std::string cameraInputLabel = "拍摄输入";
    selectOverlayNode->ShowCamera(maxWidth, allocatedSize, infoPtr, cameraInputLabel);
    EXPECT_TRUE(selectOverlayNode->isDefaultBtnOverMaxWidth_);
}

/**
 * @tc.name: ShowCamera002
 * @tc.desc: Test SelectOverlayNode ShowCamera.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowCamera002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCameraInput = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);

    float maxWidth = 8.0f;
    float allocatedSize = 11.0f;
    std::string cameraInputLabel = "拍摄输入";
    selectOverlayNode->ShowCamera(maxWidth, allocatedSize, infoPtr, cameraInputLabel);
    EXPECT_TRUE(selectOverlayNode->isDefaultBtnOverMaxWidth_);
}

/**
 * @tc.name: ShowCamera003
 * @tc.desc: Test SelectOverlayNode ShowCamera.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowCamera003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCameraInput = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);

    float maxWidth = 8.0f;
    float allocatedSize = 80.0f;
    std::string cameraInputLabel = "拍摄输入";
    selectOverlayNode->ShowCamera(maxWidth, allocatedSize, infoPtr, cameraInputLabel);
    EXPECT_TRUE(selectOverlayNode->isDefaultBtnOverMaxWidth_);
}

/**
 * @tc.name: SetSelectMenuHeight001
 * @tc.desc: Test SelectOverlayPattern SetSelectMenuHeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetSelectMenuHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call SetSelectMenuHeight function.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetSelectMenuHeight();
}

/**
 * @tc.name: OverlayModifierOnDraw002
 * @tc.desc: Test SelectOverlayModifier OnDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OverlayModifierOnDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern, canvas
     * and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(overlayModifier, nullptr);
    Testing::MockCanvas canvas;
    DrawingContext context = GetDrawingContext(canvas);
    for (int32_t i = 0; i < 4; i++) {
        overlayModifier->circleOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
        EXPECT_NE(overlayModifier->circleOffset_[i], nullptr);
        if (i < 4 - 1) {
            overlayModifier->lineEndOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
            EXPECT_NE(overlayModifier->lineEndOffset_[i], nullptr);
        }
    }
    overlayModifier->rotationAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetMenuOptionOffset(offset);
    overlayModifier->pointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetHeadPointRadius(Dimension(1.0));
    overlayModifier->isNewAvoid_ = true;
    overlayModifier->SetFirstHandleIsShow(true);
    overlayModifier->SetSecondHandleIsShow(true);
    EXPECT_EQ(overlayModifier->firstHandleIsShow_->Get(), true);
    EXPECT_EQ(overlayModifier->secondHandleIsShow_->Get(), true);
    /**
     * @tc.steps: step2. call onDraw.
     * @tc.expected: cover branch isNewAvoid_, firstHandleIsShow_ and secondHandleIsShow_ are true.
     */
    overlayModifier->onDraw(context);
    EXPECT_EQ(overlayModifier->hasExtensionMenu_->Get(), false);
}

/**
 * @tc.name: OverlayModifierSetLineEndOffset001
 * @tc.desc: Test SelectOverlayModifier SetLineEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OverlayModifierSetLineEndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode, pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(overlayModifier, nullptr);
    for (int32_t i = 0; i < 4; i++) {
        overlayModifier->circleOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
        EXPECT_NE(overlayModifier->circleOffset_[i], nullptr);
        if (i < 4 - 1) {
            overlayModifier->lineEndOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
            EXPECT_NE(overlayModifier->lineEndOffset_[i], nullptr);
        }
    }
    overlayModifier->rotationAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetMenuOptionOffset(offset);
    overlayModifier->pointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetOtherPointRadius(Dimension(1.0));
    overlayModifier->SetHeadPointRadius(Dimension(1.0));
    /**
     * @tc.steps: step2. call SetLineEndOffset, when isMore is true.
     * @tc.expected: rotationAngle_ is 0.
     */
    overlayModifier->SetLineEndOffset(true);
    EXPECT_EQ(overlayModifier->rotationAngle_->Get(), 0);
    /**
     * @tc.steps: step3. call SetLineEndOffset, when isMore is false.
     * @tc.expected: rotationAngle_ isn't 0.
     */
    overlayModifier->SetLineEndOffset(false);
    EXPECT_NE(overlayModifier->rotationAngle_->Get(), 0);
}

/**
 * @tc.name: OverlayModifierSetHeadPointRadius001
 * @tc.desc: Test SelectOverlayModifier SetHeadPointRadius.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OverlayModifierSetHeadPointRadius001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode, pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(overlayModifier, nullptr);
    /**
     * @tc.steps: step2. call SetOtherPointRadius and SetHeadPointRadius.
     * @tc.expected: pointRadius_ and headPointRadius_ have value.
     */
    overlayModifier->SetOtherPointRadius(Dimension(1.0));
    overlayModifier->SetHeadPointRadius(Dimension(1.0));
    EXPECT_EQ(overlayModifier->pointRadius_->Get(), 1.0);
    EXPECT_EQ(overlayModifier->headPointRadius_->Get(), 1.0);
    /**
     * @tc.steps: step3. call SetOtherPointRadius and SetHeadPointRadius.
     * @tc.expected: pointRadius_ and headPointRadius_ are nullptr.
     */
    overlayModifier->pointRadius_ = nullptr;
    overlayModifier->headPointRadius_ = nullptr;
    overlayModifier->SetOtherPointRadius(Dimension(1.0));
    overlayModifier->SetHeadPointRadius(Dimension(1.0));
    EXPECT_EQ(overlayModifier->headPointRadius_, nullptr);
    EXPECT_EQ(overlayModifier->pointRadius_, nullptr);
}

/**
 * @tc.name: GetCreateMenuOptionsParams001
 * @tc.desc: Test select_overlay_test_ng GetCreateMenuOptionsParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetCreateMenuOptionsParams001, TestSize.Level1)
{
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool {
        return false;
    };
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    selectInfo.onCreateCallback.onCreateMenuCallback = nullptr;
    auto info_ = std::make_shared<SelectOverlayInfo>(selectInfo);

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
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(textOverlayTheme))
        .WillOnce(Return(textOverlayTheme))
        .WillRepeatedly(SelectOverlayTestNg::GetMockThemeForTest);
    auto menuWrapper = selectOverlayNode->CreateMenuNode(info_);
    EXPECT_NE(menuWrapper, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
}

/**
 * @tc.name: LandscapeMenuAddMenuOptions001
 * @tc.desc: Test select_overlay_test_ng LandscapeMenuAddMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, LandscapeMenuAddMenuOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    int32_t extensionOptionStartIndex = -1;
    selectOverlayNode->LandscapeMenuAddMenuOptions(false, 300.0, 200.0, extensionOptionStartIndex, infoPtr);
    EXPECT_EQ(extensionOptionStartIndex, -1);
}

/**
 * @tc.name: LandscapeMenuAddMenuOptions002
 * @tc.desc: Test select_overlay_test_ng LandscapeMenuAddMenuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, LandscapeMenuAddMenuOptions002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    int32_t extensionOptionStartIndex = -1;
    selectOverlayNode->LandscapeMenuAddMenuOptions(false, 300.0, 320.0, extensionOptionStartIndex, infoPtr);
    EXPECT_NE(extensionOptionStartIndex, 0);
}

/**
 * @tc.name: GetSystemMenuItemParams001
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetSystemMenuItemParams001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo info;
    info.menuInfo.showCopy = true;
    info.menuInfo.showPaste = true;
    info.menuInfo.showCut = true;
    info.menuInfo.showCopyAll = true;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = true;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 5);
}

/**
 * @tc.name: GetSystemMenuItemParams002
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetSystemMenuItemParams002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo info;
    info.menuInfo.showCopy = false;
    info.menuInfo.showPaste = false;
    info.menuInfo.showCut = false;
    info.menuInfo.showCopyAll = false;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = false;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 0);
}

/**
 * @tc.name: GetSystemMenuItemParams003
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetSystemMenuItemParams003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo info;
    info.menuInfo.showCopy = true;
    info.menuInfo.showPaste = false;
    info.menuInfo.showCut = true;
    info.menuInfo.showCopyAll = false;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = true;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 3);
}

/**
 * @tc.name: GetSystemMenuItemParams004
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetSystemMenuItemParams004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo info;
    info.menuInfo.showCopy = false;
    info.menuInfo.showPaste = true;
    info.menuInfo.showCut = false;
    info.menuInfo.showCopyAll = true;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = false;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 2);
}

/**
 * @tc.name: GetSystemMenuItemParams005
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetSystemMenuItemParams005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo info;
    info.menuInfo.showCopy = false;
    info.menuInfo.showPaste = true;
    info.menuInfo.showCut = false;
    info.menuInfo.showCopyAll = false;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = false;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 1);
}

/**
 * @tc.name: GetSystemMenuItemParams006
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetSystemMenuItemParams006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo info;
    info.menuInfo.showCopy = false;
    info.menuInfo.showPaste = true;
    info.menuInfo.showCut = true;
    info.menuInfo.showCopyAll = true;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = true;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 4);
}

/**
 * @tc.name: AddCreateMenuItems001
 * @tc.desc: Test select_overlay_test_ng AddCreateMenuItems.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    MenuOptionsParam menuItem3;
    menuItem3.content = "item3";
    menuItem3.id = "item3";
    menuOptionItems.emplace_back(menuItem3);

    MenuOptionsParam menuItem4;
    menuItem4.content = "OH_DEFAULT_PASTE";
    menuItem4.id = "OH_DEFAULT_PASTE";
    menuOptionItems.emplace_back(menuItem4);

    auto info = pattern->GetSelectOverlayInfo();

    float maxWidth = 100.0f;
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, info, maxWidth);
    EXPECT_NE(index, 3);
}

/**
 * @tc.name: CreatExtensionMenu001
 * @tc.desc: Test select_overlay_test_ng CreatExtensionMenu.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreatExtensionMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    std::vector<OptionParam> params;
    selectOverlayNode->CreatExtensionMenu(std::move(params), nullptr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
}

/**
 * @tc.name: IsFirstHandleMoveStart
 * @tc.desc: Test IsFirstHandleMoveStart.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsFirstHandleMoveStart, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    pattern->isFirstHandleTouchDown_ = true;
    pattern->isSecondHandleTouchDown_ = true;
    EXPECT_FALSE(pattern->IsSingleHandleMenuShow());
    EXPECT_FALSE(pattern->IsSingleHandle());
    EXPECT_FALSE(pattern->IsFirstHandleMoveStart(info.GetLocalLocation()));
}

/**
 * @tc.name: CreateMenuNode001
 * @tc.desc: Test select_overlay_test_ng CreateMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateMenuNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode, pattern.
     */
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    selectInfo.onCreateCallback.onCreateMenuCallback = nullptr;
    auto info_ = std::make_shared<SelectOverlayInfo>(selectInfo);

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
    /**
     * @tc.steps: step2. call CreateMenuNode and check menuWrapperNoShortCut.
    */
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    textOverlayTheme->showShortcut_ = false;
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(textOverlayTheme))
        .WillOnce(Return(textOverlayTheme))
        .WillRepeatedly(SelectOverlayTestNg::GetMockThemeForTest);
    auto menuWrapperNoShortCut = selectOverlayNode->CreateMenuNode(info_);
    EXPECT_NE(menuWrapperNoShortCut, nullptr);
    textOverlayTheme->showShortcut_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(textOverlayTheme))
        .WillOnce(Return(textOverlayTheme))
        .WillRepeatedly(SelectOverlayTestNg::GetMockThemeForTest);
    auto menuWrapperShortCut = selectOverlayNode->CreateMenuNode(info_);
    EXPECT_NE(menuWrapperShortCut, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
}

/**
 * @tc.name: CreateMenuNode002
 * @tc.desc: Test select_overlay_test_ng CreateMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateMenuNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode, pattern.
     */
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    selectInfo.onCreateCallback.onCreateMenuCallback = nullptr;
    auto info_ = std::make_shared<SelectOverlayInfo>(selectInfo);

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
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(textOverlayTheme))
        .WillOnce(Return(textOverlayTheme))
        .WillRepeatedly(SelectOverlayTestNg::GetMockThemeForTest);
    auto menuWrapperNoShortCut = selectOverlayNode->CreateMenuNode(info_);
    EXPECT_NE(menuWrapperNoShortCut, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
}

/**
 * @tc.name: GetDefaultButtonAndMenuWidth001
 * @tc.desc: Test GetDefaultButtonAndMenuWidth with UIExtension Window.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetDefaultButtonAndMenuWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set TextOverlayTheme to themeManager and Create selectOverlayNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Set container UIExtension State and Window Rect.
     */
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    container->SetIsUIExtensionWindow(true);
    MockPipelineContext::SetCurrentWindowRect(WINDOW_RECT);

    /**
     * @tc.steps: step3. test GetDefaultButtonAndMenuWidth return value.
     * @tc.expected: maxWidth changed is right.
     */
    float maxWidth = 1040.0f;
    const auto& menuPadding = textOverlayTheme->GetMenuPadding();

    auto backButtonWidth = textOverlayTheme->GetMenuToolbarHeight().ConvertToPx() - menuPadding.Top().ConvertToPx() -
                           menuPadding.Bottom().ConvertToPx();
    auto gap = textOverlayTheme->GetOverlayMenuHorizontalGap().ConvertToPx() * 2;
    selectOverlayNode->GetDefaultButtonAndMenuWidth(maxWidth);
    EXPECT_EQ(maxWidth, WINDOW_RECT.Width() - gap - menuPadding.Left().ConvertToPx() -
                            menuPadding.Right().ConvertToPx() - backButtonWidth);
}

/**
 * @tc.name: GetDefaultButtonAndMenuWidth002
 * @tc.desc: Test GetDefaultButtonAndMenuWidth without UIExtension Window.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, GetDefaultButtonAndMenuWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set TextOverlayTheme to themeManager and Create selectOverlayNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Set container UIExtension State and Window Rect.
     */
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    container->SetIsUIExtensionWindow(false);
    MockPipelineContext::SetCurrentWindowRect(WINDOW_RECT);

    /**
     * @tc.steps: step3. test GetDefaultButtonAndMenuWidth return value.
     * @tc.expected: maxWidth changed is right.
     */
    float maxWidth = 1040.0f;
    const auto& menuPadding = textOverlayTheme->GetMenuPadding();

    auto backButtonWidth = textOverlayTheme->GetMenuToolbarHeight().ConvertToPx() - menuPadding.Top().ConvertToPx() -
                           menuPadding.Bottom().ConvertToPx();
    selectOverlayNode->GetDefaultButtonAndMenuWidth(maxWidth);
    EXPECT_EQ(maxWidth, textOverlayTheme->GetMaxOverlayMenuWidth().ConvertToPx() - menuPadding.Left().ConvertToPx() -
                            menuPadding.Right().ConvertToPx() - backButtonWidth);
}

/**
 * @tc.name: AddSystemDefaultOptionsBorderParam
 * @tc.desc: Test AddSystemDefaultOptionsBorderParam different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddSystemDefaultOptionsBorderParam, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectInfo and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showCameraInput = true;
    float maxWidth = 50.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);

    /**
     * @tc.steps: step2. call AddSystemDefaultOptions.
     */
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    auto result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_FALSE(result);

    maxWidth = 0.0f;
    result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_TRUE(result);

    maxWidth = -1.0f;
    result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CreateMenuNode003
 * @tc.desc: Test select_overlay_test_ng CreateMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateMenuNode003, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode, pattern.
     */
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    selectInfo.onCreateCallback.onCreateMenuCallback = nullptr;
    auto info_ = std::make_shared<SelectOverlayInfo>(selectInfo);

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
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(textOverlayTheme))
        .WillOnce(Return(textOverlayTheme))
        .WillRepeatedly(SelectOverlayTestNg::GetMockThemeForTest);
    auto menuWrapperNoShortCut = selectOverlayNode->CreateMenuNode(info_);
    EXPECT_NE(menuWrapperNoShortCut, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback001
 * @tc.desc: Test AddMenuItemByCreateMenuCallback with backButton.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ApiTargetVersion.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /**
     * @tc.steps: step2. Set TextOverlayTheme to themeManager and Create selectOverlayNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.showAIWrite = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    auto onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return {};
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step3. test AddMenuItemByCreateMenuCallback.
     * @tc.expected: The default menu is created successfully and backButton is reset.
     */
    float maxWidth = 2.0f;
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddMenuItemByCreateMenuCallback(infoPtr, maxWidth);
    EXPECT_FALSE(selectOverlayNode->backButton_);
    EXPECT_TRUE(selectOverlayNode->selectMenu_);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback002
 * @tc.desc: Test AddMenuItemByCreateMenuCallback without backButton.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ApiTargetVersion.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /**
     * @tc.steps: step2. Set TextOverlayTheme to themeManager and Create selectOverlayNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuInfo.showAIWrite = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    auto onCreateMenuCallback = [menuOptionItems](
                                    const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return menuOptionItems;
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step3. test AddMenuItemByCreateMenuCallback.
     * @tc.expected: The backButton and moreButton are created successfully.
     */
    float maxWidth = 1040.0f;
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddMenuItemByCreateMenuCallback(infoPtr, maxWidth);
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_NE(selectOverlayNode->moreButton_, nullptr);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback003
 * @tc.desc: Test AddMenuItemByCreateMenuCallback with Lower version.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ApiTargetVersion.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    /**
     * @tc.steps: step2. Set TextOverlayTheme to themeManager and Create selectOverlayNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = false;
    selectInfo.menuInfo.showSearch = false;
    selectInfo.menuInfo.showShare = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.showAIWrite = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    auto onCreateMenuCallback = [menuOptionItems](
                                    const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return menuOptionItems;
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step3. test AddMenuItemByCreateMenuCallback.
     * @tc.expected: The backButton and moreButton are created successfully.
     */
    float maxWidth = 1040.0f;
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddMenuItemByCreateMenuCallback(infoPtr, maxWidth);
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_NE(selectOverlayNode->moreButton_, nullptr);
    EXPECT_EQ(selectOverlayNode->moreOrBackSymbol_, nullptr);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback004
 * @tc.desc: Test AddMenuItemByCreateMenuCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ApiTargetVersion.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /**
     * @tc.steps: step2. Set TextOverlayTheme to themeManager and Create selectOverlayNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuInfo.showAIWrite = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    auto onCreateMenuCallback = [menuOptionItems](
                                    const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return menuOptionItems;
    };
    auto onPrepareMenuCallback = [menuOptionItems](
                                     const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return menuOptionItems;
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback;
    selectInfo.onCreateCallback.onPrepareMenuCallback = onPrepareMenuCallback;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step3. test AddMenuItemByCreateMenuCallback.
     * @tc.expected: The backButton and moreButton are created successfully.
     */
    float maxWidth = 1040.0f;
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddMenuItemByCreateMenuCallback(infoPtr, maxWidth);
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_NE(selectOverlayNode->moreButton_, nullptr);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback005
 * @tc.desc: Test AddMenuItemByCreateMenuCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ApiTargetVersion.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /**
     * @tc.steps: step2. Set TextOverlayTheme to themeManager and Create selectOverlayNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.showCameraInput = true;
    selectInfo.menuInfo.showAIWrite = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    auto onCreateMenuCallback = nullptr;
    auto onPrepareMenuCallback = [menuOptionItems](
                                     const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return menuOptionItems;
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback;
    selectInfo.onCreateCallback.onPrepareMenuCallback = onPrepareMenuCallback;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step3. test AddMenuItemByCreateMenuCallback.
     * @tc.expected: The backButton and moreButton are created successfully.
     */
    float maxWidth = 1040.0f;
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddMenuItemByCreateMenuCallback(infoPtr, maxWidth);
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_NE(selectOverlayNode->moreButton_, nullptr);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}

/**
 * @tc.name: AddCreateMenuItems002
 * @tc.desc: Test AddCreateMenuItems with multiple menu items.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);

    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));

    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    MenuOptionsParam menuItem3;
    menuItem3.content = "item3";
    menuItem3.id = "item3";
    menuOptionItems.emplace_back(menuItem3);

    auto info = pattern->GetSelectOverlayInfo();
    float maxWidth = 1040.0f;

    /**
     * @tc.steps: step2. Call AddCreateMenuItems with the prepared data.
     * @tc.expected: The function returns the correct index.
     */
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, info, maxWidth);
    EXPECT_EQ(index, -1);

    /**
     * @tc.expected: The menu items are correctly added to selectMenuInner_.
     */
    auto selectMenuInner = selectOverlayNode->selectMenuInner_;
    ASSERT_NE(selectMenuInner, nullptr);
    EXPECT_EQ(selectMenuInner->GetChildren().size(), 4);
}

/**
 * @tc.name: AddCreateMenuItems003
 * @tc.desc: Test AddCreateMenuItems when menu items exceed maxWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Prepare MenuItems1.
     */

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    /**
     * @tc.steps: step3. Prepare MenuItems2.
     */

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    /**
     * @tc.steps: step4. Prepare MenuItems3.
     */

    MenuOptionsParam menuItem3;
    menuItem3.content = "item3";
    menuItem3.id = "item3";
    menuOptionItems.emplace_back(menuItem3);

    float maxWidth = 100.0f; // 设置较小的 maxWidth

    /**
     * @tc.steps: step5. Call AddCreateMenuItems and verify the return value.
     * @tc.expected: The function returns an index less than the total number of menu items.
     */
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, infoPtr, maxWidth);
    EXPECT_LT(index, static_cast<int32_t>(menuOptionItems.size()));

    /**
     * @tc.expected: The number of menu items actually added is correct.
     */
    auto selectMenuInner = selectOverlayNode->selectMenuInner_;
    ASSERT_NE(selectMenuInner, nullptr);
    EXPECT_EQ(selectMenuInner->GetChildren().size(), 4);
}

/**
 * @tc.name: AddCreateMenuItems004
 * @tc.desc: Test AddCreateMenuItems with empty menu items.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare empty menu items.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    std::vector<MenuOptionsParam> menuOptionItems = {};
    float maxWidth = 1040.0f;

    /**
     * @tc.steps: step2. Call AddCreateMenuItems and verify the return value.
     * @tc.expected: The function returns -1.
     */
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, infoPtr, maxWidth);
    EXPECT_EQ(index, -1);

    /**
     * @tc.expected: selectMenuInner_ is not empty.
     */
    auto selectMenuInner = selectOverlayNode->selectMenuInner_;
    ASSERT_NE(selectMenuInner, nullptr);
    EXPECT_EQ(selectMenuInner->GetChildren().size(), 4);
}

/**
 * @tc.name: AddCreateMenuItems005
 * @tc.desc: Test AddCreateMenuItems with OH_DEFAULT_PASTE menu item.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return AceType::MakeRefPtr<TextOverlayTheme>();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else {
            return AceType::MakeRefPtr<SelectTheme>();
        }
    });
    auto textOverlayTheme = MockPipelineContext::GetCurrent()->GetTheme<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "OH_DEFAULT_PASTE";
    menuItem1.id = "OH_DEFAULT_PASTE";
    menuOptionItems.emplace_back(menuItem1);

    float maxWidth = 1040.0f;

    /**
     * @tc.steps: step2. Call AddCreateMenuItems and verify the return value.
     * @tc.expected: The function returns 0, index != -1 indicates successful creation of menu.
     */
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, infoPtr, maxWidth);
    EXPECT_EQ(index, 0);

    /**
     * @tc.expected: OH_DEFAULT_PASTE menu item is handled correctly.
     */
    auto selectMenuInner = selectOverlayNode->selectMenuInner_;
    ASSERT_NE(selectMenuInner, nullptr);
    auto child = selectMenuInner->GetChildAtIndex(0);
    ASSERT_NE(child, nullptr);
    auto button = AceType::DynamicCast<FrameNode>(child);
    ASSERT_NE(button, nullptr);
    EXPECT_EQ(button->GetTag(), "SelectMenuButton");
}

/**
 * @tc.name: AddCreateMenuItems006
 * @tc.desc: Test AddCreateMenuItems with nullptr info.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    float maxWidth = 1040.0f;

    /**
     * @tc.steps: step2. Call AddCreateMenuItems and verify the return value.
     * @tc.expected: The function returns -1.
     */
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, infoPtr, maxWidth);
    EXPECT_EQ(index, -1);

    /**
     * @tc.expected: selectMenuInner_ is not empty.
     */
    auto selectMenuInner = selectOverlayNode->selectMenuInner_;
    ASSERT_NE(selectMenuInner, nullptr);
    EXPECT_EQ(selectMenuInner->GetChildren().size(), 4);
}

/**
 * @tc.name: AddCreateMenuItems007
 * @tc.desc: Test AddCreateMenuItems with isFirstOption flag.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    float maxWidth = 1040.0f;

    /**
     * @tc.steps: step2. Call AddCreateMenuItems and verify the return value.
     * @tc.expected: The function returns -1.
     */
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, infoPtr, maxWidth);
    EXPECT_EQ(index, -1);

    /**
     * @tc.expected: isFirstOption flag is set correctly for the first menu item.
     */
    EXPECT_FALSE(menuOptionItems[0].isFirstOption);
}

/**
 * @tc.name: UpdateMenuColors001
 * @tc.desc: Test UpdateMenuColors returns early when caller frame node is missing.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateMenuColors001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->selectMenu_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    selectOverlayNode->selectMenuInner_ =
        FrameNode::GetOrCreateFrameNode("SelectMenuInner", ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    selectOverlayNode->moreButton_ = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->moreOrBackSymbol_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(selectOverlayNode->selectMenu_, nullptr);
    ASSERT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    ASSERT_NE(selectOverlayNode->moreButton_, nullptr);
    ASSERT_NE(selectOverlayNode->moreOrBackSymbol_, nullptr);

    selectOverlayNode->UpdateMenuColors();

    auto moreButtonPattern = selectOverlayNode->moreButton_->GetPattern<ButtonPattern>();
    auto moreOrBackLayoutProperty = selectOverlayNode->moreOrBackSymbol_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(moreButtonPattern, nullptr);
    ASSERT_NE(moreOrBackLayoutProperty, nullptr);
    EXPECT_FALSE(moreButtonPattern->clickedColor_.has_value());
    EXPECT_FALSE(moreButtonPattern->blendClickColor_.has_value());
    EXPECT_FALSE(moreButtonPattern->blendHoverColor_.has_value());
    EXPECT_FALSE(moreOrBackLayoutProperty->GetSymbolColorList().has_value());
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams001
 * @tc.desc: Test AddCreateMenuExtensionMenuParams with multiple menu items.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onCut = []() {};
    selectInfo.menuCallback.onCopy = []() {};
    selectInfo.menuCallback.onSelectAll = []() {};
    selectInfo.menuCallback.onPaste = []() {};
    selectInfo.menuCallback.onTranslate = []() {};
    selectInfo.menuCallback.onSearch = []() {};
    selectInfo.menuCallback.onShare = []() {};
    selectInfo.menuCallback.onCameraInput = []() {};
    selectInfo.menuCallback.onAIWrite = []() {};

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    std::vector<MenuOptionsParam> menuOptionItems;
    std::vector<std::pair<std::string, std::string>> menuItems = { { "Cut", "OH_DEFAULT_CUT" },
        { "Copy", "OH_DEFAULT_COPY" }, { "Select All", "OH_DEFAULT_SELECT_ALL" },
        { "Translate", "OH_DEFAULT_TRANSLATE" }, { "Search", "OH_DEFAULT_SEARCH" }, { "Share", "OH_DEFAULT_SHARE" },
        { "Camera Input", "OH_DEFAULT_CAMERA_INPUT" }, { "Ai Write", "OH_DEFAULT_AI_WRITE" } };

    for (const auto& item : menuItems) {
        MenuOptionsParam menuItem;
        menuItem.content = item.first;
        menuItem.id = item.second;
        menuOptionItems.emplace_back(menuItem);
    }

    std::vector<OptionParam> params;
    int32_t startIndex = 0;

    /**
     * @tc.steps: step2. Mock ThemeManager and IconTheme.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(iconTheme, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(textOverlayTheme)) // 第一次调用返回 TextOverlayTheme
        .WillRepeatedly(Return(iconTheme)); // 后续调用返回 IconTheme

    /**
     * @tc.steps: step3. Call AddCreateMenuExtensionMenuParams.
     * @tc.expected: The function correctly adds menu items and triggers GetSystemIconPath.
     */
    std::vector<std::string> paramIds;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(menuOptionItems, infoPtr, startIndex, params, paramIds);

    /**
     * @tc.expected: The params vector contains the correct number of items.
     */
    EXPECT_EQ(params.size(), menuOptionItems.size());

    /**
     * @tc.expected: The icon path for each menu item is correctly set.
     */
    EXPECT_EQ(params[0].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_CUT_SVG));
    EXPECT_EQ(params[1].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_COPY_SVG));
    EXPECT_EQ(params[2].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_SELECT_ALL_SVG));
    EXPECT_EQ(params[3].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_TRANSLATE_SVG));
    EXPECT_EQ(params[4].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_SEARCH_SVG));
    EXPECT_EQ(params[5].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_SHARE_SVG));
    EXPECT_EQ(params[6].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_TAKEPHOTO_SVG));
    EXPECT_EQ(params[7].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_AI_WRITE_SVG));
    EXPECT_TRUE(params[7].isAIWriteOption);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams002
 * @tc.desc: Test AddCreateMenuExtensionMenuParams with startIndex greater than menu items size.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onCut = []() {};
    selectInfo.menuCallback.onCopy = []() {};
    selectInfo.menuCallback.onPaste = []() {};

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "Cut";
    menuItem1.id = "OH_DEFAULT_CUT";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "Copy";
    menuItem2.id = "OH_DEFAULT_COPY";
    menuOptionItems.emplace_back(menuItem2);

    std::vector<OptionParam> params;
    int32_t startIndex = 3; // startIndex 大于菜单项数量

    /**
     * @tc.steps: step2. Mock ThemeManager and IconTheme.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(iconTheme, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [selectTheme, textOverlayTheme, iconTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == SelectTheme::TypeId()) {
                return selectTheme;
            }
            if (type == TextOverlayTheme::TypeId()) {
                return textOverlayTheme;
            }
            if (type == IconTheme::TypeId()) {
                return iconTheme;
            }
            return textOverlayTheme;
        });

    /**
     * @tc.steps: step3. Call AddCreateMenuExtensionMenuParams.
     * @tc.expected: The function does not add any items to params.
     */
    std::vector<std::string> paramIds;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(menuOptionItems, infoPtr, startIndex, params, paramIds);

    /**
     * @tc.expected: The params vector is empty.
     */
    EXPECT_TRUE(params.empty());
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams003
 * @tc.desc: Test AddCreateMenuExtensionMenuParams with OH_DEFAULT_PASTE menu item.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onPaste = []() {};

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "Paste";
    menuItem1.id = "OH_DEFAULT_PASTE";
    menuOptionItems.emplace_back(menuItem1);

    std::vector<OptionParam> params;
    int32_t startIndex = 0;

    /**
     * @tc.steps: step2. Mock ThemeManager and IconTheme.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(iconTheme, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [selectTheme, textOverlayTheme, iconTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == SelectTheme::TypeId()) {
                return selectTheme;
            }
            if (type == TextOverlayTheme::TypeId()) {
                return textOverlayTheme;
            }
            if (type == IconTheme::TypeId()) {
                return iconTheme;
            }
            return textOverlayTheme;
        });

    /**
     * @tc.steps: step3. Call AddCreateMenuExtensionMenuParams.
     * @tc.expected: The function correctly adds the OH_DEFAULT_PASTE menu item.
     */
    std::vector<std::string> paramIds;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(menuOptionItems, infoPtr, startIndex, params, paramIds);

    /**
     * @tc.expected: The params vector contains one item.
     */
    EXPECT_EQ(params.size(), 1);

    /**
     * @tc.expected: The OH_DEFAULT_PASTE menu item has the correct properties.
     */
    EXPECT_EQ(params[0].value, "");
    EXPECT_EQ(params[0].icon, " "); // OH_DEFAULT_PASTE 的 icon 应为空
    EXPECT_TRUE(params[0].isPasteOption);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams004
 * @tc.desc: Test AddCreateMenuExtensionMenuParams with symbol callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onCut = []() {};

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "Cut";
    menuItem1.id = "OH_DEFAULT_CUT";
    menuOptionItems.emplace_back(menuItem1);

    std::vector<OptionParam> params;
    int32_t startIndex = 0;

    /**
     * @tc.steps: step2. Mock ThemeManager and IconTheme.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(iconTheme, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(textOverlayTheme)).WillRepeatedly(Return(iconTheme));

    /**
     * @tc.steps: step3. Call AddCreateMenuExtensionMenuParams.
     * @tc.expected: The function correctly adds the menu item with symbol callback.
     */
    std::vector<std::string> paramIds;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(menuOptionItems, infoPtr, startIndex, params, paramIds);

    /**
     * @tc.expected: The params vector contains one item.
     */
    EXPECT_EQ(params.size(), 1);

    /**
     * @tc.expected: The symbol callback is correctly set.
     */
    EXPECT_NE(params[0].symbol, nullptr);
}

/*
 * @tc.name: AddCreateMenuExtensionMenuParams006
 * @tc.desc: Test AddCreateMenuExtensionMenuParams with symbol callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onCut = []() {};

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "Custom Menu Item";
    menuItem1.id = "other";
    menuItem1.symbolId = 10;
    menuOptionItems.emplace_back(menuItem1);

    std::vector<OptionParam> params;
    int32_t startIndex = 0;

    /**
     * @tc.steps: step2. Mock ThemeManager and IconTheme.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(iconTheme, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(textOverlayTheme)).WillRepeatedly(Return(iconTheme));

    /**
     * @tc.steps: step3. Call AddCreateMenuExtensionMenuParams.
     * @tc.expected: The function correctly adds the menu item with symbol callback.
     */
    std::vector<std::string> paramIds;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(menuOptionItems, infoPtr, startIndex, params, paramIds);

    /**
     * @tc.expected: The params vector contains one item.
     */
    EXPECT_EQ(params.size(), 1);

    /**
     * @tc.expected: The symbol callback is correctly set.
     */
    EXPECT_NE(params[0].symbol, nullptr);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams007
 * @tc.desc: Test AddCreateMenuExtensionMenuParams with symbol callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuCallback.onCut = []() {};

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "Custom Menu Item";
    menuItem1.id = "other";
    menuItem1.symbolId = 0;
    menuOptionItems.emplace_back(menuItem1);

    std::vector<OptionParam> params;
    int32_t startIndex = 0;

    /**
     * @tc.steps: step2. Mock ThemeManager and IconTheme.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(iconTheme, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(textOverlayTheme)).WillRepeatedly(Return(iconTheme));

    /**
     * @tc.steps: step3. Call AddCreateMenuExtensionMenuParams.
     * @tc.expected: The function correctly adds the menu item with symbol callback.
     */
    std::vector<std::string> paramIds;
    selectOverlayNode->AddCreateMenuExtensionMenuParams(menuOptionItems, infoPtr, startIndex, params, paramIds);

    /**
     * @tc.expected: The params vector contains one item.
     */
    EXPECT_EQ(params.size(), 1);

    /**
     * @tc.expected: The symbol callback is correctly set.
     */
    EXPECT_EQ(params[0].symbol, nullptr);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams008
 * @tc.desc: Test AddCreateMenuExtensionMenuParams keeps toolbar system items in extension menu when font scale is large.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams008, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupFontScale = pipeline->GetFontScale();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    pipeline->SetFontScale(1.85f);

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCopy = true;
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;

    std::vector<MenuOptionsParam> menuOptionItems;
    menuOptionItems.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_COPY, .content = "copy" });
    menuOptionItems.emplace_back(MenuOptionsParam { .id = "custom_item", .content = "custom item" });

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);

    std::vector<OptionParam> params;
    std::vector<std::string> paramIds;
    node->AddCreateMenuExtensionMenuParams(menuOptionItems, info, 1, params, paramIds);

    ASSERT_EQ(params.size(), 2);
    ASSERT_EQ(paramIds.size(), 2);
    EXPECT_EQ(paramIds[0], OH_DEFAULT_COPY);
    EXPECT_EQ(paramIds[1], "custom_item");
    EXPECT_NE(params[0].symbol, nullptr);
    EXPECT_FALSE(params[0].isTextMenuGridMenuItem);

    pipeline->SetFontScale(backupFontScale);
    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams009
 * @tc.desc: Test AddCreateMenuExtensionMenuParams skips toolbar system items in smooth material scene.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams009, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCopy = true;
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;

    std::vector<MenuOptionsParam> menuOptionItems;
    menuOptionItems.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_COPY, .content = "copy" });
    menuOptionItems.emplace_back(MenuOptionsParam { .id = "custom_item", .content = "custom item" });

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);

    std::vector<OptionParam> params;
    std::vector<std::string> paramIds;
    node->AddCreateMenuExtensionMenuParams(menuOptionItems, info, 1, params, paramIds);

    ASSERT_EQ(params.size(), 1);
    ASSERT_EQ(paramIds.size(), 1);
    EXPECT_EQ(paramIds[0], "custom_item");

    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams010
 * @tc.desc: Test AddCreateMenuExtensionMenuParams keeps auto fill system callback directly.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuExtensionMenuParams010, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    int32_t onMenuItemClickCount = 0;
    int32_t onAutoFillCount = 0;
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuCallback.onAutoFill = [&onAutoFillCount]() { onAutoFillCount++; };
    info->onCreateCallback.onMenuItemClick = [&onMenuItemClickCount](const NG::MenuItemParam&) {
        onMenuItemClickCount++;
        return false;
    };

    std::vector<MenuOptionsParam> menuOptionItems;
    menuOptionItems.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_AUTO_FILL, .content = "auto_fill" });

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);

    std::vector<OptionParam> params;
    std::vector<std::string> paramIds;
    node->AddCreateMenuExtensionMenuParams(menuOptionItems, info, 0, params, paramIds);

    ASSERT_EQ(params.size(), 1);
    ASSERT_EQ(paramIds.size(), 1);
    ASSERT_TRUE(static_cast<bool>(params[0].action));
    params[0].action();
    EXPECT_EQ(onAutoFillCount, 1);
    EXPECT_EQ(onMenuItemClickCount, 0);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm.AdjustToInfo
 * @tc.desc: test AdjustToInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AdjustToInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.computeMenuOffset = [](LayoutWrapper*, OffsetF&, const RectF, OffsetF&,
        std::shared_ptr<SelectOverlayInfo>&) { return true; };
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and geometryNode.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    /**
     * @tc.steps: step2. Call OnDirtyLayoutWrapperSwap function.
     * @tc.expected: return false
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutWrapperPtr = AccessibilityManager::RawPtr(layoutWrapper);
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    auto newNode = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(newNode, nullptr);
    auto menuOffset = OffsetF();
    auto menuRect = RectF();
    auto windowOffset = OffsetF();
    auto ret = newNode->AdjustToInfo(layoutWrapperPtr, menuOffset, menuRect, windowOffset, infoPtr);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: InitSurfaceChangedCallback
 * @tc.desc: Test InitSurfaceChangedCallback with RTL layout direction
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, InitSurfaceChangedCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create selectoverlay node.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. modify overlay mode and test InitSurfaceChangedCallback.
     */
    pattern->overlayMode_ = SelectOverlayMode::HANDLE_ONLY;
    pattern->surfaceChangeCallbackId_.reset();
    pattern->InitSurfaceChangedCallback();
    EXPECT_FALSE(pattern->surfaceChangeCallbackId_.has_value());

    pattern->overlayMode_ = SelectOverlayMode::MENU_ONLY;
    infoPtr->menuInfo.menuBuilder = []() {};
    pattern->InitSurfaceChangedCallback();
    EXPECT_FALSE(pattern->surfaceChangeCallbackId_.has_value());

    infoPtr->menuInfo.menuBuilder = nullptr;
    pattern->pipeline_ = MockPipelineContext::GetCurrent();
    pattern->InitSurfaceChangedCallback();
    pattern->HandleSurfaceChanged();
    EXPECT_TRUE(pattern->surfaceChangeCallbackId_.has_value());
}


/**
 * @tc.name: PasteButtonTest
 * @tc.desc: Test add paste item.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, PasteButtonTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SelectOverlayNode and prepare menu items.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);

    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));

    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);

    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "OH_DEFAULT_PASTE";
    menuOptionItems.emplace_back(menuItem1);

    auto info = pattern->GetSelectOverlayInfo();
    float maxWidth = 1040.0f;

    /**
     * @tc.steps: step2. Call AddCreateMenuItems with the prepared data.
     * @tc.expected: The function returns the correct index.
     */
    int32_t index = selectOverlayNode->AddCreateMenuItems(menuOptionItems, info, maxWidth);
    EXPECT_LT(index, static_cast<int32_t>(menuOptionItems.size()));

    /**
     * @tc.expected: The menu items are correctly added to selectMenuInner_.
     */
    auto selectMenuInner = selectOverlayNode->selectMenuInner_;
    ASSERT_NE(selectMenuInner, nullptr);
    EXPECT_EQ(selectMenuInner->GetChildren().size(), 1);
}

/**
 * @tc.name: SelectOverlayNode_ConvertToIntMenuId002
 * @tc.desc: Test ConvertToIntMenuId with built-in menu ids.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_ConvertToIntMenuId002, TestSize.Level1)
{
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_CUT), static_cast<int32_t>(NativeMenuId::ID_CUT));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_COPY), static_cast<int32_t>(NativeMenuId::ID_COPY));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_PASTE), static_cast<int32_t>(NativeMenuId::ID_PASTE));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_SELECT_ALL),
        static_cast<int32_t>(NativeMenuId::ID_SELECT_ALL));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_TRANSLATE),
        static_cast<int32_t>(NativeMenuId::ID_TRANSLATE));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_SEARCH),
        static_cast<int32_t>(NativeMenuId::ID_SEARCH));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_SHARE), static_cast<int32_t>(NativeMenuId::ID_SHARE));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_CAMERA_INPUT),
        static_cast<int32_t>(NativeMenuId::ID_CAMERA_INPUT));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_AI_WRITE),
        static_cast<int32_t>(NativeMenuId::ID_AI_WRITE));
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId(OH_DEFAULT_ASK_CELIA),
        static_cast<int32_t>(NativeMenuId::ID_ASK_CELIA));
}

/**
 * @tc.name: SelectOverlayNode_ConvertToIntMenuId003
 * @tc.desc: Test ConvertToIntMenuId with numeric and invalid strings.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_ConvertToIntMenuId003, TestSize.Level1)
{
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId("2048"), 2048);
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId("-12"), -12);
    EXPECT_EQ(SelectOverlayNode::ConvertToIntMenuId("invalid_menu_id"), -1);
}

/**
 * @tc.name: SelectOverlayNode_ConvertToStrMenuId002
 * @tc.desc: Test ConvertToStrMenuId with built-in menu ids.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_ConvertToStrMenuId002, TestSize.Level1)
{
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_CUT)), OH_DEFAULT_CUT);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_COPY)), OH_DEFAULT_COPY);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_PASTE)), OH_DEFAULT_PASTE);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_SELECT_ALL)),
        OH_DEFAULT_SELECT_ALL);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_TRANSLATE)),
        OH_DEFAULT_TRANSLATE);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_SEARCH)),
        OH_DEFAULT_SEARCH);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_SHARE)), OH_DEFAULT_SHARE);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_CAMERA_INPUT)),
        OH_DEFAULT_CAMERA_INPUT);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_AI_WRITE)),
        OH_DEFAULT_AI_WRITE);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(static_cast<int32_t>(NativeMenuId::ID_ASK_CELIA)),
        OH_DEFAULT_ASK_CELIA);
}

/**
 * @tc.name: SelectOverlayNode_ConvertToStrMenuId003
 * @tc.desc: Test ConvertToStrMenuId with out-of-range values.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_ConvertToStrMenuId003, TestSize.Level1)
{
    auto minMenuId = static_cast<int32_t>(NativeMenuId::ID_CUT);
    auto maxMenuId = static_cast<int32_t>(NativeMenuId::ID_PASSWORD_VAULT);
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(minMenuId - 1), std::to_string(minMenuId - 1));
    EXPECT_EQ(SelectOverlayNode::ConvertToStrMenuId(maxMenuId + 1), std::to_string(maxMenuId + 1));
}

/**
 * @tc.name: SelectOverlayNode_IsShowOnTargetAPIVersion001
 * @tc.desc: Test IsShowOnTargetAPIVersion across API boundaries.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_IsShowOnTargetAPIVersion001, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    EXPECT_TRUE(node->IsShowOnTargetAPIVersion());

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    EXPECT_FALSE(node->IsShowOnTargetAPIVersion());

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SEVENTEEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SEVENTEEN));
    EXPECT_FALSE(node->IsShowOnTargetAPIVersion());

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    EXPECT_FALSE(node->IsShowOnTargetAPIVersion());

    container->SetApiTargetVersion(backupContainerApiVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
}

/**
 * @tc.name: SelectOverlayNode_IsShowTranslateOnTargetAPIVersion001
 * @tc.desc: Test IsShowTranslateOnTargetAPIVersion across API boundaries.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_IsShowTranslateOnTargetAPIVersion001, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    EXPECT_TRUE(node->IsShowTranslateOnTargetAPIVersion());

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    EXPECT_FALSE(node->IsShowTranslateOnTargetAPIVersion());

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    EXPECT_FALSE(node->IsShowTranslateOnTargetAPIVersion());

    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FIFTEEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FIFTEEN));
    EXPECT_FALSE(node->IsShowTranslateOnTargetAPIVersion());

    container->SetApiTargetVersion(backupContainerApiVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
}

/**
 * @tc.name: SelectOverlayNode_GetMenuUiMaterial001
 * @tc.desc: Test GetMenuUiMaterial creates immersive material and updates color mode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetMenuUiMaterial001, TestSize.Level1)
{
    auto& darkMaterial = SelectOverlayNode::GetMenuUiMaterial(ColorMode::DARK);
    ASSERT_NE(darkMaterial, nullptr);
    EXPECT_EQ(darkMaterial->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    ASSERT_NE(darkMaterial->GetImmersiveOptions(), nullptr);
    EXPECT_EQ(darkMaterial->GetImmersiveOptions()->colorMode, ColorMode::DARK);

    auto& lightMaterial = SelectOverlayNode::GetMenuUiMaterial(ColorMode::LIGHT);
    ASSERT_NE(lightMaterial, nullptr);
    ASSERT_NE(lightMaterial->GetImmersiveOptions(), nullptr);
    EXPECT_EQ(lightMaterial->GetImmersiveOptions()->colorMode, ColorMode::LIGHT);
}

/**
 * @tc.name: SelectOverlayNode_UpdateNewMaterialProperties001
 * @tc.desc: Test UpdateNewMaterialProperties applies immersive system material in exquisite mode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_UpdateNewMaterialProperties001, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupLevel = g_uiMaterialLevel;
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);
    auto target = FrameNode::GetOrCreateFrameNode(
        TEST_TAG, ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(target, nullptr);
    target->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);

    node->UpdateNewMaterialProperties(target, ColorMode::DARK);
    auto renderContext = target->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto systemMaterial = renderContext->GetSystemMaterial();
    ASSERT_NE(systemMaterial, nullptr);
    ASSERT_NE(systemMaterial->GetImmersiveOptions(), nullptr);
    EXPECT_EQ(systemMaterial->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    EXPECT_EQ(systemMaterial->GetImmersiveOptions()->colorMode, ColorMode::DARK);

    g_uiMaterialLevel = backupLevel;
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: SelectOverlayNode_UpdateNewMaterialProperties002
 * @tc.desc: Test UpdateNewMaterialProperties falls back to low-end background in smooth mode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_UpdateNewMaterialProperties002, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupLevel = g_uiMaterialLevel;
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    textOverlayTheme->menuBackgroundColorLowEnd_ = Color::FromRGB(12, 34, 56);
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);
    auto target = FrameNode::GetOrCreateFrameNode(
        TEST_TAG, ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(target, nullptr);
    target->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);

    node->UpdateNewMaterialProperties(target, ColorMode::LIGHT);
    auto renderContext = target->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSystemMaterial(), nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT),
        textOverlayTheme->GetMenuBackgroundColorLowEnd());
    EXPECT_TRUE(renderContext->GetBackShadow().has_value());

    g_uiMaterialLevel = backupLevel;
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: SelectOverlayNode_UpdateNewMaterialProperties003
 * @tc.desc: Test UpdateNewMaterialProperties is a no-op when new material is disabled by version.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_UpdateNewMaterialProperties003, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);
    auto target = FrameNode::GetOrCreateFrameNode(
        TEST_TAG, ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(target, nullptr);
    target->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    auto renderContext = target->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::RED);

    node->UpdateNewMaterialProperties(target, ColorMode::DARK);
    EXPECT_EQ(renderContext->GetSystemMaterial(), nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT), Color::RED);
}

/**
 * @tc.name: SelectOverlayNode_GetDefaultOptionsParams001
 * @tc.desc: Test GetDefaultOptionsParams returns selected primary default items.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetDefaultOptionsParams001, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuCallback.onCut = []() {};
    info->menuCallback.onPaste = []() {};
    info->menuCallback.onAutoFill = []() {};
    info->menuCallback.autoFillSubMenuCallback.onPasswordVault = []() {};

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    for (auto& isShow : node->isShowInDefaultMenu_) {
        isShow = true;
    }
    node->isShowInDefaultMenu_[0] = false;
    node->isShowInDefaultMenu_[2] = false;
    node->isShowInDefaultMenu_[11] = false;

    std::vector<std::string> paramIds;
    auto params = node->GetDefaultOptionsParams(info, paramIds);

    ASSERT_EQ(params.size(), 3);
    ASSERT_EQ(paramIds.size(), 3);
    EXPECT_EQ(paramIds[0], OH_DEFAULT_CUT);
    EXPECT_EQ(paramIds[1], OH_DEFAULT_PASTE);
    EXPECT_EQ(paramIds[2], OH_DEFAULT_AUTO_FILL);
    EXPECT_EQ(params[0].icon, iconTheme->GetIconPath(InternalResource::ResourceId::IC_CUT_SVG));
    EXPECT_TRUE(params[1].isPasteOption);
    ASSERT_EQ(params[2].subMenuItems.size(), 1);
    EXPECT_EQ(params[2].subMenuItems[0].value, textOverlayTheme->GetPasswordVaultLabel());
}

/**
 * @tc.name: SelectOverlayNode_GetDefaultOptionsParams002
 * @tc.desc: Test GetDefaultOptionsParams returns flexible items and updates flags.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetDefaultOptionsParams002, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    info->menuCallback.onCameraInput = []() {};
    info->menuCallback.onAIWrite = []() {};
    info->menuCallback.onAIMenuOption = [](const std::string&) {};
    info->menuCallback.onAskCelia = []() {};

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    for (auto& isShow : node->isShowInDefaultMenu_) {
        isShow = true;
    }
    node->isShowInDefaultMenu_[7] = false;
    node->isShowInDefaultMenu_[8] = false;
    node->isShowInDefaultMenu_[9] = false;
    node->isShowInDefaultMenu_[10] = false;

    std::vector<std::string> paramIds;
    auto params = node->GetDefaultOptionsParams(info, paramIds);

    ASSERT_EQ(params.size(), 4);
    ASSERT_EQ(paramIds.size(), 4);
    EXPECT_EQ(paramIds[0], OH_DEFAULT_CAMERA_INPUT);
    EXPECT_EQ(paramIds[1], OH_DEFAULT_AI_WRITE);
    EXPECT_EQ(paramIds[2], OH_DEFAULT_AI_MENU_PHONE);
    EXPECT_EQ(paramIds[3], OH_DEFAULT_ASK_CELIA);
    EXPECT_TRUE(params[1].isAIWriteOption);
    EXPECT_TRUE(params[2].isAIMenuOption);
    EXPECT_TRUE(params[3].isAskCeliaOption);
}

/**
 * @tc.name: SelectOverlayNode_GetDefaultOptionsParams003
 * @tc.desc: Test GetDefaultOptionsParams returns empty when all default items are already shown.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetDefaultOptionsParams003, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    for (auto& isShow : node->isShowInDefaultMenu_) {
        isShow = true;
    }

    std::vector<std::string> paramIds;
    auto params = node->GetDefaultOptionsParams(info, paramIds);
    EXPECT_TRUE(params.empty());
    EXPECT_TRUE(paramIds.empty());
}

/**
 * @tc.name: SelectOverlayNode_GetDefaultOptionsParams004
 * @tc.desc: Test GetDefaultOptionsParams uses empty icon path when IconTheme is unavailable.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetDefaultOptionsParams004, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), nullptr);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuCallback.onCopy = []() {};
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    for (auto& isShow : node->isShowInDefaultMenu_) {
        isShow = true;
    }
    node->isShowInDefaultMenu_[1] = false;

    std::vector<std::string> paramIds;
    auto params = node->GetDefaultOptionsParams(info, paramIds);
    ASSERT_EQ(params.size(), 1);
    EXPECT_EQ(paramIds[0], OH_DEFAULT_COPY);
    EXPECT_EQ(params[0].icon, "");
}

/**
 * @tc.name: SelectOverlayNode_GetSymbolFunc001
 * @tc.desc: Test GetSymbolFunc applies AI gradient symbol and normal symbol correctly.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetSymbolFunc001, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    textOverlayTheme->aiMenuSymbolId_ = 1001;
    textOverlayTheme->copySymbolId_ = 1002;
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);

    auto aiSymbolFunc = node->GetSymbolFunc(OH_DEFAULT_AI_MENU_PHONE);
    ASSERT_NE(aiSymbolFunc, nullptr);
    auto aiSymbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(aiSymbolNode, nullptr);
    aiSymbolFunc(WeakPtr<FrameNode>(aiSymbolNode));
    auto aiLayoutProperty = aiSymbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(aiLayoutProperty, nullptr);
    EXPECT_EQ(aiLayoutProperty->GetSymbolSourceInfoValue(SymbolSourceInfo()), SymbolSourceInfo(1001));
    EXPECT_TRUE(aiLayoutProperty->HasFontForegroudGradiantColor());

    auto copySymbolFunc = node->GetSymbolFunc(OH_DEFAULT_COPY);
    ASSERT_NE(copySymbolFunc, nullptr);
    auto copySymbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(copySymbolNode, nullptr);
    copySymbolFunc(WeakPtr<FrameNode>(copySymbolNode));
    auto copyLayoutProperty = copySymbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(copyLayoutProperty, nullptr);
    EXPECT_EQ(copyLayoutProperty->GetSymbolSourceInfoValue(SymbolSourceInfo()), SymbolSourceInfo(1002));
    EXPECT_FALSE(copyLayoutProperty->HasFontForegroudGradiantColor());
}

/**
 * @tc.name: SelectOverlayNode_GetSymbolFunc002
 * @tc.desc: Test GetSymbolFunc returns nullptr for unknown symbol id.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetSymbolFunc002, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetSymbolFunc("unknown_symbol"), nullptr);
}

/**
 * @tc.name: SelectOverlayNode_GetSymbolFunc003
 * @tc.desc: Test GetSymbolFunc keeps AIWrite symbol without gradient color.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetSymbolFunc003, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    textOverlayTheme->aiWriteSymbolId_ = 1003;
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);

    auto aiWriteSymbolFunc = node->GetSymbolFunc(OH_DEFAULT_AI_WRITE);
    ASSERT_NE(aiWriteSymbolFunc, nullptr);
    auto aiWriteSymbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(aiWriteSymbolNode, nullptr);
    aiWriteSymbolFunc(WeakPtr<FrameNode>(aiWriteSymbolNode));
    auto aiWriteLayoutProperty = aiWriteSymbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(aiWriteLayoutProperty, nullptr);
    EXPECT_EQ(aiWriteLayoutProperty->GetSymbolSourceInfoValue(SymbolSourceInfo()), SymbolSourceInfo(1003));
    EXPECT_FALSE(aiWriteLayoutProperty->HasFontForegroudGradiantColor());
}

/**
 * @tc.name: SelectOverlayNode_GetSymbolFunc004
 * @tc.desc: Test GetSymbolFunc applies gradient color for AskCelia symbol.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_GetSymbolFunc004, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    textOverlayTheme->askCeliaSymbolId_ = 1004;
    PrepareThemeManagerForNodeTest(textOverlayTheme);

    auto node = CreateSelectOverlayNodeForNodeTest();
    ASSERT_NE(node, nullptr);

    auto askCeliaSymbolFunc = node->GetSymbolFunc(OH_DEFAULT_ASK_CELIA);
    ASSERT_NE(askCeliaSymbolFunc, nullptr);
    auto askCeliaSymbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(askCeliaSymbolNode, nullptr);
    askCeliaSymbolFunc(WeakPtr<FrameNode>(askCeliaSymbolNode));
    auto askCeliaLayoutProperty = askCeliaSymbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(askCeliaLayoutProperty, nullptr);
    EXPECT_EQ(askCeliaLayoutProperty->GetSymbolSourceInfoValue(SymbolSourceInfo()), SymbolSourceInfo(1004));
    EXPECT_TRUE(askCeliaLayoutProperty->HasFontForegroudGradiantColor());
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback006
 * @tc.desc: Test AddMenuItemByCreateMenuCallback enables extension grid menu in new animation scene.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback006, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCopy = true;
    info->menuInfo.showPaste = true;
    info->menuInfo.showCut = true;
    info->menuInfo.showCopyAll = true;
    info->menuCallback.onCopy = []() {};
    info->menuCallback.onPaste = []() {};
    info->menuCallback.onCut = []() {};
    info->menuCallback.onSelectAll = []() {};
    info->onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam&) { return false; };
    info->onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>&) {
        std::vector<MenuOptionsParam> items;
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_COPY, .content = "copy" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_PASTE, .content = "paste" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_CUT, .content = "cut" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_SELECT_ALL, .content = "select all" });
        items.emplace_back(MenuOptionsParam { .id = "custom_item", .content = "custom item" });
        return items;
    };
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenuInner_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenuInner_, nullptr);

    node->AddMenuItemByCreateMenuCallback(info, 1.0f);
    ASSERT_NE(node->extensionMenu_, nullptr);
    auto outerMenuPattern = node->extensionMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(outerMenuPattern, nullptr);
    EXPECT_TRUE(outerMenuPattern->GetIsGridMenu());
    EXPECT_TRUE(outerMenuPattern->GetIsExtensionMenuEnableNewAnimation());

    auto scrollNode = AceType::DynamicCast<FrameNode>(node->extensionMenu_->GetChildAtIndex(0));
    ASSERT_NE(scrollNode, nullptr);
    auto innerMenuNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    ASSERT_NE(innerMenuNode, nullptr);
    auto innerMenuPattern = innerMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(innerMenuPattern, nullptr);
    auto menuItems = innerMenuPattern->GetMenuItems();
    ASSERT_GE(menuItems.size(), 3);
    EXPECT_TRUE(menuItems[0]->GetPattern<MenuItemPattern>()->IsTextMenuGridMenuItem());
    EXPECT_TRUE(menuItems[1]->GetPattern<MenuItemPattern>()->IsTextMenuGridMenuItem());
    EXPECT_TRUE(menuItems[2]->GetPattern<MenuItemPattern>()->IsTextMenuGridMenuItem());

    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback007
 * @tc.desc: Test AddMenuItemByCreateMenuCallback disables extension grid menu in smooth material scene.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback007, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCopy = true;
    info->menuInfo.showPaste = true;
    info->menuInfo.showCut = true;
    info->menuInfo.showCopyAll = true;
    info->menuCallback.onCopy = []() {};
    info->menuCallback.onPaste = []() {};
    info->menuCallback.onCut = []() {};
    info->menuCallback.onSelectAll = []() {};
    info->onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam&) { return false; };
    info->onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>&) {
        std::vector<MenuOptionsParam> items;
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_COPY, .content = "copy" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_PASTE, .content = "paste" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_CUT, .content = "cut" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_SELECT_ALL, .content = "select all" });
        items.emplace_back(MenuOptionsParam { .id = "custom_item", .content = "custom item" });
        return items;
    };
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenuInner_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenuInner_, nullptr);

    node->AddMenuItemByCreateMenuCallback(info, 1.0f);
    ASSERT_NE(node->extensionMenu_, nullptr);
    auto outerMenuPattern = node->extensionMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(outerMenuPattern, nullptr);
    EXPECT_FALSE(outerMenuPattern->GetIsGridMenu());
    EXPECT_FALSE(outerMenuPattern->GetIsExtensionMenuEnableNewAnimation());

    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: SelectOverlayNode_AddExtensionMenuOptionsLargeFont001
 * @tc.desc: Test AddExtensionMenuOptions keeps toolbar system items but disables grid style when font scale is large.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNode_AddExtensionMenuOptionsLargeFont001, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupFontScale = pipeline->GetFontScale();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    pipeline->SetFontScale(1.85f);

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme, iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCopy = true;
    info->menuInfo.showPaste = true;
    info->menuInfo.showCut = true;
    info->menuInfo.showCopyAll = true;
    info->menuCallback.onCopy = []() {};
    info->menuCallback.onPaste = []() {};
    info->menuCallback.onCut = []() {};
    info->menuCallback.onSelectAll = []() {};
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    node->CreateToolBar();
    node->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(node->backButton_, nullptr);
    for (auto& isShow : node->isShowInDefaultMenu_) {
        isShow = true;
    }

    node->AddExtensionMenuOptions(info, 0);

    ASSERT_NE(node->extensionMenu_, nullptr);
    auto outerMenuPattern = node->extensionMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(outerMenuPattern, nullptr);
    EXPECT_FALSE(outerMenuPattern->GetIsGridMenu());
    EXPECT_TRUE(outerMenuPattern->GetIsExtensionMenuEnableNewAnimation());

    auto scrollNode = AceType::DynamicCast<FrameNode>(node->extensionMenu_->GetChildAtIndex(0));
    ASSERT_NE(scrollNode, nullptr);
    auto innerMenuNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    ASSERT_NE(innerMenuNode, nullptr);
    auto innerMenuPattern = innerMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(innerMenuPattern, nullptr);
    auto menuItems = innerMenuPattern->GetMenuItems();
    ASSERT_EQ(menuItems.size(), 4);
    for (const auto& menuItem : menuItems) {
        auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
        ASSERT_NE(menuItemPattern, nullptr);
        EXPECT_FALSE(menuItemPattern->IsTextMenuGridMenuItem());
    }

    pipeline->SetFontScale(backupFontScale);
    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: AddMenuItemByCreateMenuCallback008
 * @tc.desc: Test AddMenuItemByCreateMenuCallback disables grid style but keeps new animation enabled when font scale is large.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddMenuItemByCreateMenuCallback008, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupFontScale = pipeline->GetFontScale();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    pipeline->SetFontScale(1.85f);

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    PrepareThemeManagerForNodeTest(textOverlayTheme, AceType::MakeRefPtr<SelectTheme>(), iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCopy = true;
    info->menuInfo.showPaste = true;
    info->menuInfo.showCut = true;
    info->menuInfo.showCopyAll = true;
    info->menuCallback.onCopy = []() {};
    info->menuCallback.onPaste = []() {};
    info->menuCallback.onCut = []() {};
    info->menuCallback.onSelectAll = []() {};
    info->onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam&) { return false; };
    info->onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>&) {
        std::vector<MenuOptionsParam> items;
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_COPY, .content = "copy" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_PASTE, .content = "paste" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_CUT, .content = "cut" });
        items.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_SELECT_ALL, .content = "select all" });
        items.emplace_back(MenuOptionsParam { .id = "custom_item", .content = "custom item" });
        return items;
    };
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenuInner_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenuInner_, nullptr);

    node->AddMenuItemByCreateMenuCallback(info, 1.0f);
    ASSERT_NE(node->extensionMenu_, nullptr);
    auto outerMenuPattern = node->extensionMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(outerMenuPattern, nullptr);
    EXPECT_FALSE(outerMenuPattern->GetIsGridMenu());
    EXPECT_TRUE(outerMenuPattern->GetIsExtensionMenuEnableNewAnimation());

    auto scrollNode = AceType::DynamicCast<FrameNode>(node->extensionMenu_->GetChildAtIndex(0));
    ASSERT_NE(scrollNode, nullptr);
    auto innerMenuNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    ASSERT_NE(innerMenuNode, nullptr);
    auto innerMenuPattern = innerMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(innerMenuPattern, nullptr);
    auto menuItems = innerMenuPattern->GetMenuItems();
    ASSERT_GE(menuItems.size(), 5);
    for (size_t index = 0; index < 4; ++index) {
        auto menuItemPattern = menuItems[index]->GetPattern<MenuItemPattern>();
        ASSERT_NE(menuItemPattern, nullptr);
        EXPECT_FALSE(menuItemPattern->IsTextMenuGridMenuItem());
    }

    pipeline->SetFontScale(backupFontScale);
    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: CreatExtensionMenu002
 * @tc.desc: Test CreatExtensionMenu keeps grid style disabled when font scale is large.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreatExtensionMenu002, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupFontScale = pipeline->GetFontScale();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    pipeline->SetFontScale(1.85f);

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    textOverlayTheme->copySymbolId_ = 1001;
    textOverlayTheme->pasteSymbolId_ = 1002;
    textOverlayTheme->cutSymbolId_ = 1003;
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenu_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenu_, nullptr);
    node->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(node->backButton_, nullptr);

    std::vector<OptionParam> params;
    params.emplace_back("copy", "", []() {});
    params.emplace_back("paste", "", []() {});
    params.emplace_back("cut", "", []() {});
    params[0].symbol = node->GetSymbolFunc(OH_DEFAULT_COPY);
    params[1].symbol = node->GetSymbolFunc(OH_DEFAULT_PASTE);
    params[2].symbol = node->GetSymbolFunc(OH_DEFAULT_CUT);
    params[0].isTextMenuGridMenuItem = true;
    params[1].isTextMenuGridMenuItem = true;
    params[2].isTextMenuGridMenuItem = true;
    params[1].isPasteOption = true;

    node->CreatExtensionMenu(std::move(params), caller, 3);

    ASSERT_NE(node->extensionMenu_, nullptr);
    auto outerMenuPattern = node->extensionMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(outerMenuPattern, nullptr);
    EXPECT_FALSE(outerMenuPattern->GetIsGridMenu());
    EXPECT_TRUE(outerMenuPattern->GetIsExtensionMenuEnableNewAnimation());

    auto scrollNode = AceType::DynamicCast<FrameNode>(node->extensionMenu_->GetChildAtIndex(0));
    ASSERT_NE(scrollNode, nullptr);
    auto innerMenuNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    ASSERT_NE(innerMenuNode, nullptr);
    auto innerMenuPattern = innerMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(innerMenuPattern, nullptr);
    EXPECT_FALSE(innerMenuPattern->gridMenuPasteItemBuilder_.has_value());

    pipeline->SetFontScale(backupFontScale);
    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: SelectOverlayNodeBuildGridMenuPasteItem001
 * @tc.desc: Test text menu grid paste builder updates theme scope id and placeholder state.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNodeBuildGridMenuPasteItem001, TestSize.Level1)
{
#ifndef OHOS_PLATFORM
    GTEST_SKIP() << "OHOS platform only";
#endif
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    APIVersionGuard apiVersionGuard(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto backupContainerApiVersion = container->GetApiTargetVersion();
    auto backupApplicationApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    auto backupMinPlatformVersion = MockPipelineContext::GetCurrent()->GetMinPlatformVersion();
    auto backupLevel = g_uiMaterialLevel;
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;

    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    textOverlayTheme->copySymbolId_ = 1001;
    textOverlayTheme->pasteSymbolId_ = 1002;
    textOverlayTheme->cutSymbolId_ = 1003;
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme, iconTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto caller = CreateCallerFrameNodeForNodeTest(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX), 321);
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenu_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenu_, nullptr);
    node->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(node->backButton_, nullptr);

    std::vector<OptionParam> params;
    params.emplace_back(textOverlayTheme->GetCopyLabel(), "", []() {});
    params.emplace_back(textOverlayTheme->GetPasteLabel(), "", []() {});
    params.emplace_back(textOverlayTheme->GetCutLabel(), "", []() {});
    params[0].symbol = node->GetSymbolFunc(OH_DEFAULT_COPY);
    params[1].symbol = node->GetSymbolFunc(OH_DEFAULT_PASTE);
    params[2].symbol = node->GetSymbolFunc(OH_DEFAULT_CUT);
    params[0].isTextMenuGridMenuItem = true;
    params[1].isTextMenuGridMenuItem = true;
    params[2].isTextMenuGridMenuItem = true;
    params[1].isPasteOption = true;
    params[1].enabled = false;

    node->CreatExtensionMenu(std::move(params), caller, 3);
    ASSERT_NE(node->extensionMenu_, nullptr);
    auto scrollNode = AceType::DynamicCast<FrameNode>(node->extensionMenu_->GetChildAtIndex(0));
    ASSERT_NE(scrollNode, nullptr);
    auto innerMenuNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    ASSERT_NE(innerMenuNode, nullptr);
    auto innerMenuPattern = innerMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(innerMenuPattern, nullptr);
    ASSERT_EQ(innerMenuPattern->GetMenuItems().size(), 3);
    auto pasteMenuItemPattern = innerMenuPattern->GetMenuItems()[1]->GetPattern<MenuItemPattern>();
    ASSERT_NE(pasteMenuItemPattern, nullptr);
#ifdef OHOS_PLATFORM
    EXPECT_NE(pasteMenuItemPattern->GetPasteButton(), nullptr);
#endif

    OptionParam gridPasteParam;
    gridPasteParam.value = textOverlayTheme->GetPasteLabel();
    gridPasteParam.isPasteOption = true;
    gridPasteParam.isTextMenuGridMenuItem = true;
    gridPasteParam.enabled = false;
    auto defaultGridItem = MenuView::CreateGridItem(gridPasteParam, 0);
    ASSERT_NE(defaultGridItem, nullptr);
    defaultGridItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    auto builtPasteItem = innerMenuPattern->BuildGridMenuPasteItem(
        gridPasteParam, defaultGridItem, caller->GetThemeScopeId());
    ASSERT_NE(builtPasteItem, nullptr);
    EXPECT_EQ(builtPasteItem->GetTag(), V2::RELATIVE_CONTAINER_ETS_TAG);
    EXPECT_EQ(builtPasteItem->GetThemeScopeId(), caller->GetThemeScopeId());
    EXPECT_EQ(defaultGridItem->GetInspectorId().value_or(""), "__gridPasteDisplayColumn__");
    ASSERT_NE(defaultGridItem->GetRenderContext(), nullptr);
    EXPECT_EQ(static_cast<float>(defaultGridItem->GetRenderContext()->GetOpacityValue(1.0)), 0.0f);

    auto overlayColumn = AceType::DynamicCast<FrameNode>(builtPasteItem->GetChildAtIndex(1));
    ASSERT_NE(overlayColumn, nullptr);
    EXPECT_EQ(overlayColumn->GetThemeScopeId(), caller->GetThemeScopeId());
    auto pasteNode = AceType::DynamicCast<FrameNode>(overlayColumn->GetChildAtIndex(0));
    ASSERT_NE(pasteNode, nullptr);
    EXPECT_EQ(pasteNode->GetThemeScopeId(), caller->GetThemeScopeId());
    auto pasteEventHub = pasteNode->GetEventHub<EventHub>();
    ASSERT_NE(pasteEventHub, nullptr);
    EXPECT_FALSE(pasteEventHub->IsEnabled());

    g_uiMaterialLevel = backupLevel;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(backupMinPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApplicationApiVersion);
    container->SetApiTargetVersion(backupContainerApiVersion);
}

/**
 * @tc.name: ContinuePlayExtensionMenuDistortAnimation001
 * @tc.desc: Test ContinuePlayExtensionMenuDistortAnimation updates transform center for different placements.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ContinuePlayExtensionMenuDistortAnimation001, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);

    auto selectMenuPaintRect = RectF(OffsetF(20.0f, 100.0f), SizeF(140.0f, 60.0f));
    auto extensionMenu = CreateExtensionMenuForAnimationTest(SizeF(120.0f, 80.0f), selectMenuPaintRect, 2);
    ASSERT_NE(extensionMenu, nullptr);
    auto renderContext = extensionMenu->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    RectF selectMenuTargetRect(OffsetF(10.0f, 40.0f), SizeF(160.0f, 50.0f));

    node->ContinuePlayExtensionMenuDistortAnimation(
        extensionMenu, OffsetF(10.0f, 20.0f), Placement::TOP, selectMenuTargetRect);
    ASSERT_TRUE(renderContext->GetTransformCenter().has_value());
    EXPECT_EQ(renderContext->GetTransformCenter()->GetX().Value(), 60.0f);
    EXPECT_EQ(renderContext->GetTransformCenter()->GetY().Value(), 80.0f);

    node->ContinuePlayExtensionMenuDistortAnimation(
        extensionMenu, OffsetF(10.0f, 140.0f), Placement::BOTTOM, selectMenuTargetRect);
    ASSERT_TRUE(renderContext->GetTransformCenter().has_value());
    EXPECT_EQ(renderContext->GetTransformCenter()->GetX().Value(), 60.0f);
    EXPECT_EQ(renderContext->GetTransformCenter()->GetY().Value(), 0.0f);

    node->ContinuePlayExtensionMenuDistortAnimation(
        extensionMenu, OffsetF(10.0f, 80.0f), Placement::NONE, selectMenuTargetRect);
    ASSERT_TRUE(renderContext->GetTransformCenter().has_value());
    EXPECT_EQ(renderContext->GetTransformCenter()->GetX().Value(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformCenter()->GetY().Value(), 0.0f);
}

/**
 * @tc.name: PlayExtensionMenuDistortAnimation001
 * @tc.desc: Test PlayExtensionMenuDistortAnimation handles bottom and overlap placements.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, PlayExtensionMenuDistortAnimation001, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenu_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenu_, nullptr);
    ASSERT_NE(node->selectMenuInner_, nullptr);

    auto selectMenuPaintRect = RectF(OffsetF(30.0f, 100.0f), SizeF(140.0f, 60.0f));
    node->selectMenu_->GetRenderContext()->UpdatePaintRect(selectMenuPaintRect);
    node->selectMenuInner_->GetRenderContext()->UpdatePaintRect(selectMenuPaintRect);

    auto extensionMenuBottom = CreateExtensionMenuForAnimationTest(SizeF(120.0f, 40.0f), selectMenuPaintRect, 2);
    ASSERT_NE(extensionMenuBottom, nullptr);
    node->extensionMenu_ = extensionMenuBottom;
    node->PlayExtensionMenuDistortAnimation(extensionMenuBottom, OffsetF(30.0f, 130.0f));
    EXPECT_NE(extensionMenuBottom->GetRenderContext(), nullptr);

    auto extensionMenuOverlap = CreateExtensionMenuForAnimationTest(SizeF(120.0f, 100.0f), selectMenuPaintRect, 3);
    ASSERT_NE(extensionMenuOverlap, nullptr);
    node->extensionMenu_ = extensionMenuOverlap;
    node->PlayExtensionMenuDistortAnimation(extensionMenuOverlap, OffsetF(30.0f, 80.0f));
    EXPECT_NE(extensionMenuOverlap->GetRenderContext(), nullptr);
}

/**
 * @tc.name: AddCreateMenuItems008
 * @tc.desc: Test create menu paste button click triggers create menu callback and fallback paste callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, AddCreateMenuItems008, TestSize.Level1)
{
#ifndef OHOS_PLATFORM
    GTEST_SKIP() << "OHOS platform only";
#endif
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto getTheme = [textOverlayTheme, selectTheme](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return textOverlayTheme;
        }
        if (type == SelectTheme::TypeId()) {
            return selectTheme;
        }
        if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        }
        return selectTheme;
    };
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([getTheme](ThemeType type) -> RefPtr<Theme> { return getTheme(type); });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([getTheme](ThemeType type, int32_t) -> RefPtr<Theme> { return getTheme(type); });

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupFontScale = pipeline->GetFontScale();
    pipeline->SetFontScale(1.0f);

    int32_t onCreateMenuClickCount = 0;
    int32_t onPasteCount = 0;
    int32_t clickStart = -1;
    int32_t clickEnd = -1;
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuCallback.onPaste = [&onPasteCount]() { onPasteCount++; };
    info->onCreateCallback.onMenuItemClick = [&onCreateMenuClickCount, &clickStart, &clickEnd](const MenuItemParam& param) {
        onCreateMenuClickCount++;
        clickStart = param.start;
        clickEnd = param.end;
        return false;
    };
    info->onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {
        start = 3;
        end = 9;
    };

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    ASSERT_NE(node->selectMenuInner_, nullptr);

    std::vector<MenuOptionsParam> menuOptionItems;
    menuOptionItems.emplace_back(MenuOptionsParam { .id = OH_DEFAULT_PASTE, .content = "paste" });
    auto index = node->AddCreateMenuItems(menuOptionItems, info, 1000.0f);
    EXPECT_EQ(index, 0);

    auto pasteButton = AceType::DynamicCast<FrameNode>(node->selectMenuInner_->GetChildAtIndex(0));
    ASSERT_NE(pasteButton, nullptr);
    const auto& layoutConstraint = pasteButton->GetLayoutProperty()->GetCalcLayoutConstraint();
    ASSERT_NE(layoutConstraint, nullptr);
    ASSERT_TRUE(layoutConstraint->selfIdealSize.has_value());
    EXPECT_TRUE(layoutConstraint->selfIdealSize->Height().has_value());
    InvokeUserClick(pasteButton);
    EXPECT_EQ(onCreateMenuClickCount, 0);
    EXPECT_EQ(onPasteCount, 0);
    EXPECT_EQ(clickStart, -1);
    EXPECT_EQ(clickEnd, -1);

    pipeline->SetFontScale(backupFontScale);
}

/**
 * @tc.name: CreateToolBarPasteButton001
 * @tc.desc: Test toolbar paste button uses adaptive height and disabled style when callback is empty.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateToolBarPasteButton001, TestSize.Level1)
{
#ifndef OHOS_PLATFORM
    GTEST_SKIP() << "OHOS platform only";
#endif
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto getTheme = [textOverlayTheme, selectTheme](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return textOverlayTheme;
        }
        if (type == SelectTheme::TypeId()) {
            return selectTheme;
        }
        if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        }
        return selectTheme;
    };
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([getTheme](ThemeType type) -> RefPtr<Theme> { return getTheme(type); });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([getTheme](ThemeType type, int32_t) -> RefPtr<Theme> { return getTheme(type); });

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupFontScale = pipeline->GetFontScale();
    pipeline->SetFontScale(1.85f);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCut = false;
    info->menuInfo.showCopy = false;
    info->menuInfo.showPaste = true;
    info->menuInfo.showCopyAll = false;
    info->menuInfo.showTranslate = false;
    info->menuInfo.showSearch = false;
    info->menuInfo.showShare = false;
    info->menuInfo.showCameraInput = false;
    info->menuInfo.showAIWrite = false;
    info->menuInfo.showAutoFill = false;
    info->menuInfo.isAskCeliaEnabled = false;

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenu_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenuInner_, nullptr);
    auto pasteButton = AceType::DynamicCast<FrameNode>(node->selectMenuInner_->GetChildAtIndex(0));
    ASSERT_NE(pasteButton, nullptr);
    const auto& layoutConstraint = pasteButton->GetLayoutProperty()->GetCalcLayoutConstraint();
    ASSERT_NE(layoutConstraint, nullptr);
    ASSERT_TRUE(layoutConstraint->selfIdealSize.has_value());
    EXPECT_FALSE(layoutConstraint->selfIdealSize->Height().has_value());

    pipeline->SetFontScale(backupFontScale);
}

/**
 * @tc.name: CreatExtensionMenuPasteItem001
 * @tc.desc: Test extension menu paste list item creates relative container and paste callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreatExtensionMenuPasteItem001, TestSize.Level1)
{
#ifndef OHOS_PLATFORM
    GTEST_SKIP() << "OHOS platform only";
#endif
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme, iconTheme);

    int32_t onPasteActionCount = 0;
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto caller = CreateCallerFrameNodeForNodeTest();
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    if (!node->selectMenu_) {
        node->CreateToolBar();
    }
    ASSERT_NE(node->selectMenu_, nullptr);
    node->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(node->backButton_, nullptr);

    std::vector<OptionParam> params;
    params.emplace_back("copy", "", []() {});
    params.emplace_back(textOverlayTheme->GetPasteLabel(), "", [&onPasteActionCount]() { onPasteActionCount++; });
    params[1].isPasteOption = true;
    params[1].disableSystemClick = true;
    node->CreatExtensionMenu(std::move(params), caller, 0);

    ASSERT_NE(node->extensionMenu_, nullptr);
    auto relativeContainer = FindFirstFrameNodeByTag(node->extensionMenu_, V2::RELATIVE_CONTAINER_ETS_TAG);
    ASSERT_NE(relativeContainer, nullptr);
    auto pasteMenuItem = FindFirstMenuItemWithPasteButton(node->extensionMenu_);
    ASSERT_NE(pasteMenuItem, nullptr);
    auto pastePattern = pasteMenuItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(pastePattern, nullptr);
    auto pasteNode = pastePattern->GetPasteButton();
    ASSERT_NE(pasteNode, nullptr);
    InvokeUserClick(pasteNode);
    EXPECT_EQ(onPasteActionCount, 1);
}

/**
 * @tc.name: CreateMenuNodePasteItem001
 * @tc.desc: Test right click paste item uses mouse-mode paste button path.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CreateMenuNodePasteItem001, TestSize.Level1)
{
#ifndef OHOS_PLATFORM
    GTEST_SKIP() << "OHOS platform only";
#endif
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    ASSERT_NE(iconTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme, iconTheme);

    int32_t onPasteCount = 0;
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    info->menuInfo.showCut = false;
    info->menuInfo.showCopy = false;
    info->menuInfo.showPaste = true;
    info->menuInfo.showCopyAll = false;
    info->menuInfo.showTranslate = false;
    info->menuInfo.showSearch = false;
    info->menuInfo.showShare = false;
    info->menuInfo.showCameraInput = false;
    info->menuInfo.showAIWrite = false;
    info->menuInfo.showAutoFill = false;
    info->menuInfo.isAskCeliaEnabled = false;
    info->menuCallback.onPaste = [&onPasteCount]() { onPasteCount++; };

    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    auto menuWrapper = node->CreateMenuNode(info);
    ASSERT_NE(menuWrapper, nullptr);
    auto relativeContainer = FindFirstFrameNodeByTag(menuWrapper, V2::RELATIVE_CONTAINER_ETS_TAG);
    ASSERT_NE(relativeContainer, nullptr);
    auto pasteMenuItem = FindFirstMenuItemWithPasteButton(menuWrapper);
    ASSERT_NE(pasteMenuItem, nullptr);
    auto pastePattern = pasteMenuItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(pastePattern, nullptr);
    auto pasteNode = pastePattern->GetPasteButton();
    ASSERT_NE(pasteNode, nullptr);
    InvokeUserClick(pasteNode);
    EXPECT_EQ(onPasteCount, 1);
}

/**
 * @tc.name: UpdateMenuColors003
 * @tc.desc: Test UpdateMenuColors updates more/back symbol color and handles rowless extension item.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateMenuColors003, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto caller = CreateCallerFrameNodeForNodeTest(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX), 200);
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    node->selectMenuInner_ = FrameNode::GetOrCreateFrameNode("SelectMenuInner",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    node->moreOrBackSymbol_ = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(node->moreOrBackSymbol_, nullptr);

    auto extensionMenu = FrameNode::GetOrCreateFrameNode("ExtensionMenu",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto scrollNode = FrameNode::GetOrCreateFrameNode("ScrollNode",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto innerMenuNode = FrameNode::GetOrCreateFrameNode("InnerMenuNode",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto menuItem = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    menuItem->MountToParent(innerMenuNode);
    innerMenuNode->MountToParent(scrollNode);
    scrollNode->MountToParent(extensionMenu);
    node->extensionMenu_ = extensionMenu;

    node->UpdateMenuColors();
    auto layoutProperty = node->moreOrBackSymbol_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_TRUE(layoutProperty->GetSymbolColorList().has_value());
    EXPECT_EQ(layoutProperty->GetSymbolColorList()->front(), textOverlayTheme->GetSymbolColor());
}

/**
 * @tc.name: UpdateMenuColors004
 * @tc.desc: Test UpdateMenuColors updates text and symbol colors for extension menu item row.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateMenuColors004, TestSize.Level1)
{
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    ASSERT_NE(selectTheme, nullptr);
    PrepareThemeManagerForNodeTest(textOverlayTheme, selectTheme);

    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultNodeTestInfo());
    auto caller = CreateCallerFrameNodeForNodeTest(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX), 201);
    ASSERT_NE(caller, nullptr);
    info->callerFrameNode = caller;
    auto node = AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(info));
    ASSERT_NE(node, nullptr);
    node->selectMenuInner_ = FrameNode::GetOrCreateFrameNode("SelectMenuInner",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });

    auto extensionMenu = FrameNode::GetOrCreateFrameNode("ExtensionMenu",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto scrollNode = FrameNode::GetOrCreateFrameNode("ScrollNode",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto innerMenuNode = FrameNode::GetOrCreateFrameNode("InnerMenuNode",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto menuItem = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto row = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    symbolNode->MountToParent(row);
    textNode->MountToParent(row);
    row->MountToParent(menuItem);
    menuItem->MountToParent(innerMenuNode);
    innerMenuNode->MountToParent(scrollNode);
    scrollNode->MountToParent(extensionMenu);
    node->extensionMenu_ = extensionMenu;

    node->UpdateMenuColors();

    auto textRenderContext = textNode->GetRenderContext();
    ASSERT_NE(textRenderContext, nullptr);
    EXPECT_EQ(textRenderContext->GetForegroundColor().value_or(Color::TRANSPARENT), selectTheme->GetMenuFontColor());
    auto symbolLayoutProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(symbolLayoutProperty, nullptr);
    ASSERT_TRUE(symbolLayoutProperty->GetSymbolColorList().has_value());
    EXPECT_EQ(symbolLayoutProperty->GetSymbolColorList()->front(), selectTheme->GetMenuIconColor());
}
} // namespace OHOS::Ace::NG
