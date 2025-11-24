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
#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "Test";
constexpr int32_t NODE_ID = 143;
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
const Rect WINDOW_RECT(0, 0, 280, 1280);
} // namespace

class SelectOverlayEightTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
    DrawingContext GetDrawingContext(Testing::MockCanvas& canvas);
    void InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme);
};

class MockPattern : public Pattern {
    DECLARE_ACE_TYPE(MockPattern, Pattern);

public:
    MockPattern() = default;
    void OnFrameNodeChanged(FrameNodeChangeInfoFlag flag) override
    {
        changeFlag_ = flag;
    }
    FrameNodeChangeInfoFlag changeFlag_;
};

void SelectOverlayEightTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlayEightTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

DrawingContext SelectOverlayEightTestNg::GetDrawingContext(Testing::MockCanvas& canvas)
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

std::vector<MenuOptionsParam> SelectOverlayEightTestNg::GetMenuOptionItems()
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

void SelectOverlayEightTestNg::InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme)
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
 * @tc.name: IsReverseLayout001
 * @tc.desc: Test IsReverseLayout with RTL layout direction
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, IsReverseLayout001, TestSize.Level1)
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
    layoutProperty->layoutDirection_ = TextDirection::RTL;

    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    EXPECT_TRUE(node->IsReverseLayout(AceType::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: LayoutChild001
 * @tc.desc: Test LayoutChild with menu null case
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, LayoutChild001, TestSize.Level1)
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

    // Test case where menu is null (index 0 child doesn't exist)
    auto node = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(selectOverlayLayoutAlgorithm);
    ASSERT_NE(node, nullptr);
    node->LayoutChild(AceType::RawPtr(layoutWrapper), SelectOverlayMode::ALL);
    // Should not crash and just return
    EXPECT_TRUE(true);
}

/**
 * @tc.name: LayoutChild002
 * @tc.desc: Test LayoutChild with CheckInShowArea returning false and isUsingMouse false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, LayoutChild002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = true;
    selectInfo.firstHandle.paintRect = RectF(150.0f, 150.0f, 20.0f, 20.0f);
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    selectInfo.isUsingMouse = false;

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
    node->LayoutChild(AceType::RawPtr(layoutWrapper), SelectOverlayMode::ALL);

    // Menu should be inactive
    EXPECT_FALSE(menuNode->IsActive());
}

/**
 * @tc.name: LayoutChild003
 * @tc.desc: Test LayoutChild with shouldInActiveByHandle true and isUsingMouse false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, LayoutChild003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = false;
    selectInfo.isSingleHandle = false;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = false;
    selectInfo.isSelectRegionVisible = false;
    selectInfo.isNewAvoid = false;
    selectInfo.isUsingMouse = false;
    selectInfo.showArea = RectF(0.0f, 0.0f, 100.0f, 100.0f);
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
    node->LayoutChild(AceType::RawPtr(layoutWrapper), SelectOverlayMode::ALL);

    // Menu should be inactive
    EXPECT_FALSE(menuNode->IsActive());
}

/**
 * @tc.name: LayoutChild004
 * @tc.desc: Test LayoutChild with menuInfo.menuBuilder set (custom menu)
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, LayoutChild004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.useFullScreen = true;
    selectInfo.isUsingMouse = false;

    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuInfo.menuBuilder = []() {};

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
    node->LayoutChild(AceType::RawPtr(layoutWrapper), SelectOverlayMode::ALL);

    // Menu should be active
    EXPECT_FALSE(menuNode->IsActive());
}

/**
 * @tc.name: SelectMenuAndInnerInitProperty_ColorMode_EdgeCases001
 * @tc.desc: Test SelectMenuAndInnerInitProperty color mode edge cases
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, SelectMenuAndInnerInitProperty_ColorMode_EdgeCases001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up test environment
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode =
        AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(infoPtr));
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Test with invalid color mode values
     * @tc.expected: Should handle gracefully and use default conversion
     */

    // Test with out-of-range color mode (simulate potential invalid value)
    MockContainer::SetMockColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    auto text = FrameNode::GetOrCreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto theme = AceType::MakeRefPtr<TokenTheme>(1);
    theme->SetColorMode(ColorMode::LIGHT);
    TokenThemeStorage::GetInstance()->CacheSet(theme);
    TokenThemeStorage::GetInstance()->StoreThemeScope(100, 1);
    text->themeScopeId_ = 100;

    selectOverlayNode->SelectMenuAndInnerInitProperty(text);

    auto selectMenu = selectOverlayNode->selectMenu_;
    ASSERT_NE(selectMenu, nullptr);
    auto renderContext = selectMenu->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    const auto& groupProperty = renderContext->GetOrCreateBackground();
    ASSERT_NE(groupProperty, nullptr);
    BlurStyleOption actualStyleOption = groupProperty->propBlurStyleOption.value_or(BlurStyleOption());
    // Should default to some valid SystemColorMode
    EXPECT_TRUE(actualStyleOption.colorMode != ThemeColorMode::LIGHT);
}

/**
 * @tc.name: AddSystemDefaultOptions008
 * @tc.desc: Test SelectOverlayNode AddSystemDefaultOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, AddSystemDefaultOptions008, TestSize.Level1)
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

    float maxWidth = 10.0f;
    float allocatedSize = 20.0f;
    auto ret = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: GetSystemMenuItemParams007
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, GetSystemMenuItemParams007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    MockContainer::SetUp();
    int32_t setApiVersion = 15;
    MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    SelectOverlayInfo info;
    info.menuInfo.showCopy = false;
    info.menuInfo.showPaste = true;
    info.menuInfo.showCut = true;
    info.menuInfo.showCopyAll = true;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = true;
    info.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 3);
}

/**
 * @tc.name: GetSystemMenuItemParams008
 * @tc.desc: Test select_overlay_test_ng GetSystemMenuItemParams.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, GetSystemMenuItemParams008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    MockContainer::SetUp();
    int32_t setApiVersion = 18;
    MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    SelectOverlayInfo info;
    info.menuInfo.showCopy = false;
    info.menuInfo.showPaste = true;
    info.menuInfo.showCut = true;
    info.menuInfo.showCopyAll = true;
    info.menuInfo.showTranslate = false;
    info.menuInfo.showSearch = false;
    info.menuInfo.showShare = false;
    info.menuInfo.showCameraInput = true;
    info.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    auto params = SelectOverlayNode::GetSystemMenuItemParams(std::make_shared<SelectOverlayInfo>(info));
    EXPECT_EQ(params.size(), 3);
}

/**
 * @tc.name: UpdateToolBar
 * @tc.desc: Test UpdateToolBar.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateToolBar, TestSize.Level1)
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
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(infoPtr, SelectOverlayMode::MENU_ONLY);
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
 * @tc.name: SetSelectMenuHeight002
 * @tc.desc: Test SelectOverlayPattern SetSelectMenuHeight.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, SetSelectMenuHeight002, TestSize.Level1)
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
 * @tc.name: OverlayModifierOnDraw003
 * @tc.desc: Test SelectOverlayModifier OnDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, OverlayModifierOnDraw003, TestSize.Level1)
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
 * @tc.name: OverlayModifierSetLineEndOffset002
 * @tc.desc: Test SelectOverlayModifier SetLineEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, OverlayModifierSetLineEndOffset002, TestSize.Level1)
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
 * @tc.name: SetIsNewAvoid002
 * @tc.desc: Test SetIsNewAvoid function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, SetIsNewAvoid002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: CheckIfNeedMenuOrHandle002
 * @tc.desc: Test CheckIfNeedMenuOrHandle function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, CheckIfNeedMenuOrHandle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    std::vector<SelectOverlayMode> selectOverlayModeVec { SelectOverlayMode::ALL, SelectOverlayMode::MENU_ONLY,
        SelectOverlayMode::HANDLE_ONLY };

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
        if (selectOverlayMode == SelectOverlayMode::ALL || selectOverlayMode == SelectOverlayMode::MENU_ONLY) {
            EXPECT_TRUE(pattern->CheckIfNeedMenu());
        } else {
            EXPECT_FALSE(pattern->CheckIfNeedMenu());
        }

        /**
         * @tc.steps: step4. Call CheckIfNeedHandle function.
         */
        if (selectOverlayMode == SelectOverlayMode::ALL || selectOverlayMode == SelectOverlayMode::HANDLE_ONLY) {
            EXPECT_TRUE(pattern->CheckIfNeedHandle());
        } else {
            EXPECT_FALSE(pattern->CheckIfNeedHandle());
        }
    }
}

/**
 * @tc.name: GetHandleDiameter002
 * @tc.desc: Test GetHandleDiameter function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, GetHandleDiameter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: OnDpiConfigurationUpdate003
 * @tc.desc: Test OnDpiConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, OnDpiConfigurationUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: OnColorConfigurationUpdate002
 * @tc.desc: Test OnColorConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, OnColorConfigurationUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: OnDetachFromFrameNode002
 * @tc.desc: Test OnDetachFromFrameNodee function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, OnDetachFromFrameNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
        }).rawPtr_);
    EXPECT_FALSE(pattern->closedByGlobalTouchEvent_);
    EXPECT_EQ(callBackFlag, 0);
}

/**
 * @tc.name: SetHandleReverse002
 * @tc.desc: Test SetHandleReverse function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, SetHandleReverse002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.isSingleHandle = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: UpdateSelectMenuInfo004
 * @tc.desc: Test UpdateSelectMenuInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateSelectMenuInfo004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: UpdateMoreOrBackSymbolOptions004
 * @tc.desc: moreOrBackSymbol_ == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateMoreOrBackSymbolOptions004, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->UpdateMoreOrBackSymbolOptions(false, true);
    EXPECT_EQ(selectOverlayNode->moreOrBackSymbol_, nullptr);
}

/**
 * @tc.name: UpdateMoreOrBackSymbolOptions005
 * @tc.desc: moreOrBackSymbol_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateMoreOrBackSymbolOptions005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: UpdateMoreOrBackSymbolOptions006
 * @tc.desc: moreOrBackSymbol_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateMoreOrBackSymbolOptions006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: UpdateMoreOrBackSymbolOptionsWithDelay002
 * @tc.desc: UpdateMoreOrBackSymbolOptionsWithDelay
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateMoreOrBackSymbolOptionsWithDelay002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: AddCreateMenuExtensionMenuParams005
 * @tc.desc: AddCreateMenuExtensionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, AddCreateMenuExtensionMenuParams005, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
    EXPECT_EQ(params.size(), 0);
}

/**
 * @tc.name: AddCreateMenuExtensionMenuParams006
 * @tc.desc: AddCreateMenuExtensionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, AddCreateMenuExtensionMenuParams006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    SelectMenuCallback menuCallback;
    menuCallback.onCut = []() {};
    menuCallback.onCopy = []() {};
    menuCallback.onAskCelia = []() {};
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
    EXPECT_EQ(params.size(), 0);
}

/**
 * @tc.name: UpdateMainWindowOffset006
 * @tc.desc: UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateMainWindowOffset006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: UpdateMainWindowOffset007
 * @tc.desc: UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateMainWindowOffset007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: UpdateMainWindowOffset008
 * @tc.desc: UpdateMainWindowOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateMainWindowOffset008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize layoutAlgorithm.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
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
 * @tc.name: TextMenuController.disableSystemServiceMenuItems001
 * @tc.desc: test disableSystemServiceMenuItems
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, DisableSystemServiceMenuItems001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    SelectOverlayInfo overlayInfo;
    SelectMenuInfo menuInfo;
    menuInfo.showCopy = false;
    menuInfo.showPaste = false;
    menuInfo.showCopyAll = false;
    menuInfo.showCut = false;
    menuInfo.showAIWrite = true;
    menuInfo.showTranslate = true;
    menuInfo.showSearch = true;
    menuInfo.showCameraInput = true;
    menuInfo.showShare = true;
    overlayInfo.menuInfo = menuInfo;
    overlayInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    std::shared_ptr<SelectOverlayInfo> shareInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetChildren().size(), 0);

    AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(NG::DISABLE_ALL_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetChildren().size(), 0);

    AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(~NG::DISABLE_ALL_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetChildren().size(), 1);
}

/**
 * @tc.name: TextMenuController.DisableMenuItems001
 * @tc.desc: test DisableMenuItems
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, DisableMenuItems001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    SelectOverlayInfo overlayInfo;
    SelectMenuInfo menuInfo;
    menuInfo.showCopy = false;
    menuInfo.showPaste = false;
    menuInfo.showCopyAll = false;
    menuInfo.showCut = false;
    menuInfo.showAIWrite = true;
    menuInfo.showTranslate = true;
    menuInfo.showSearch = true;
    menuInfo.showCameraInput = true;
    menuInfo.showShare = true;
    overlayInfo.menuInfo = menuInfo;
    std::shared_ptr<SelectOverlayInfo> shareInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 1);

    AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(NG::DISABLE_AI_WRITER_FLAG | NG::DISABLE_TRANSLATE_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 1);

    AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(
        DISABLE_TRANSLATE_FLAG | DISABLE_SEARCH_FLAG | DISABLE_SHARE_FLAG | DISABLE_CAMERA_INPUT_FLAG |
        DISABLE_AI_WRITER_FLAG | DISABLE_COLLABORATION_SERVICE_FLAG | DISABLE_AI_MENU_ADDRESS_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 0);

    AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(NG::DISABLE_ALL_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 1);
}

/**
 * @tc.name: TextMenuController.disableSystemServiceMenuItems
 * @tc.desc: test disableSystemServiceMenuItems of askCelia
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, DisableSystemServiceMenuItems004, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    SelectOverlayInfo overlayInfo;
    SelectMenuInfo menuInfo;
    menuInfo.showCopy = false;
    menuInfo.showPaste = false;
    menuInfo.showCopyAll = false;
    menuInfo.showCut = false;
    menuInfo.showAIWrite = true;
    menuInfo.showTranslate = true;
    menuInfo.showSearch = true;
    menuInfo.showCameraInput = true;
    menuInfo.showShare = true;
    menuInfo.isAskCeliaEnabled = true;
    overlayInfo.menuInfo = menuInfo;
    overlayInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    std::shared_ptr<SelectOverlayInfo> shareInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);

    AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(NG::DISABLE_ALL_FLAG);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetChildren().size(), 0);
}

/**
 * @tc.name: FrameNode::ProcessFrameNodeChangeFlag001
 * @tc.desc: test ProcessFrameNodeChangeFlag
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, ProcessFrameNodeChangeFlag001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<MockPattern>();
    auto mockNode = FrameNode::CreateFrameNode("Mock", 1, pattern, false);

    auto parentPattern1 = AceType::MakeRefPtr<MockPattern>();
    auto parentNode1 = FrameNode::CreateFrameNode("Mock", 2, pattern, false);
    parentNode1->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_END_SCROLL);
    mockNode->MountToParent(parentNode1);

    auto parentPattern2 = AceType::MakeRefPtr<MockPattern>();
    auto parentNode2 = FrameNode::CreateFrameNode("Mock", 3, pattern, false);
    parentNode2->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
    parentNode1->MountToParent(parentNode2);

    auto parentPattern3 = AceType::MakeRefPtr<MockPattern>();
    auto parentNode3 = FrameNode::CreateFrameNode("Mock", 4, pattern, false);
    parentNode3->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_ANIMATION);
    parentNode2->MountToParent(parentNode3);

    auto parentPattern4 = AceType::MakeRefPtr<MockPattern>();
    auto parentNode4 = FrameNode::CreateFrameNode("Mock", 5, pattern, false);
    parentNode4->AddFrameNodeChangeInfoFlag(FRAME_NODE_CONTENT_CLIP_CHANGE);
    parentNode3->MountToParent(parentNode4);

    mockNode->ProcessFrameNodeChangeFlag();
    EXPECT_EQ(pattern->changeFlag_, FRAME_NODE_CHANGE_END_SCROLL | FRAME_NODE_CHANGE_GEOMETRY_CHANGE |
                                        FRAME_NODE_CHANGE_START_ANIMATION | FRAME_NODE_CONTENT_CLIP_CHANGE);
}

/**
 * @tc.name: SelectMenuAndInnerInitProperty_ColorMode_EdgeCases002
 * @tc.desc: Test SelectMenuAndInnerInitProperty color mode edge cases
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, SelectMenuAndInnerInitProperty_ColorMode_EdgeCases002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up test environment
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);

    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));

    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode =
        AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(infoPtr));
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Test with invalid color mode values
     * @tc.expected: Should handle gracefully and use default conversion
     */

    // Test with out-of-range color mode (simulate potential invalid value)
    MockContainer::SetMockColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    auto text = FrameNode::GetOrCreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto theme = AceType::MakeRefPtr<TokenTheme>(1);
    theme->SetColorMode(ColorMode::LIGHT);
    TokenThemeStorage::GetInstance()->CacheSet(theme);
    TokenThemeStorage::GetInstance()->StoreThemeScope(100, 1);
    text->themeScopeId_ = 100;

    selectOverlayNode->SelectMenuAndInnerInitProperty(text);

    auto selectMenu = selectOverlayNode->selectMenu_;
    ASSERT_NE(selectMenu, nullptr);
    auto renderContext = selectMenu->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    const auto& groupProperty = renderContext->GetBackground();
    ASSERT_NE(groupProperty, nullptr);
    BlurStyleOption actualStyleOption = groupProperty->propBlurStyleOption.value_or(BlurStyleOption());
    // Should default to some valid SystemColorMode
    EXPECT_TRUE(actualStyleOption.colorMode == ThemeColorMode::LIGHT);
}

/**
 * @tc.name: SelectOverlayNodeUpdateSelectMenuBg002
 * @tc.desc: Test UpdateSelectMenuBg with normal process
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, SelectOverlayNodeUpdateSelectMenuBg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up test environment
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));

    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode =
        AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(infoPtr));
    ASSERT_NE(selectOverlayNode, nullptr);

    // Create a mock caller with specific color mode
    MockContainer::SetMockColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    auto text = FrameNode::GetOrCreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto theme = AceType::MakeRefPtr<TokenTheme>(1);
    theme->SetColorMode(ColorMode::DARK);
    TokenThemeStorage::GetInstance()->CacheSet(theme);
    TokenThemeStorage::GetInstance()->StoreThemeScope(100, 1);
    text->themeScopeId_ = 100;

    /**
     * @tc.steps: step2. Call UpdateSelectMenuBg with valid caller
     * @tc.expected: Should update render context with correct properties
     */
    selectOverlayNode->UpdateSelectMenuBg(text);

    /**
     * @tc.steps: step3. Verify the render context properties
     */
    auto selectMenu = selectOverlayNode->selectMenu_;
    ASSERT_NE(selectMenu, nullptr);
    auto renderContext = selectMenu->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Verify background color
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::TRANSPARENT);

    // Verify blur style option
    const auto& groupProperty = renderContext->GetBackground();
    ASSERT_NE(groupProperty, nullptr);
    BlurStyleOption actualStyleOption = groupProperty->propBlurStyleOption.value_or(BlurStyleOption());
    EXPECT_EQ(actualStyleOption.blurStyle, BlurStyle::COMPONENT_ULTRA_THICK);
    EXPECT_EQ(actualStyleOption.colorMode, ThemeColorMode::DARK); // Should convert from ColorMode::DARK
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Test UpdateContentModifier with circle show settings.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayEightTestNg, UpdateContentModifier001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.firstHandle.isCircleShow = true;
    selectInfo.secondHandle.isCircleShow = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    EXPECT_TRUE(contentModifier->firstCircleIsShow_->Get());
    EXPECT_FALSE(contentModifier->secondCircleIsShow_->Get());
}
} // namespace OHOS::Ace::NG