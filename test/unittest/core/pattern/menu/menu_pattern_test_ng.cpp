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

#include <type_traits>
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_layout_algorithm.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/event/touch_event.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
const std::string MENU_ITEM_TEXT = "menuItem";
const std::string MENU_ITEM_GROUP_TEXT = "menuItemGroup";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float NEW_FULL_SCREEN_WIDTH = 360.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr double DIP_SCALE = 1.5;
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};

} // namespace
class MenuPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    void InitMenuItemTestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuPatternTestNg::SetUpTestCase() {}

void MenuPatternTestNg::TearDownTestCase() {}

void MenuPatternTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuPatternTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    menuFrameNode_ = nullptr;
    menuAccessibilityProperty_ = nullptr;
    menuItemFrameNode_ = nullptr;
    menuItemPattern_ = nullptr;
    menuItemAccessibilityProperty_ = nullptr;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
}

void MenuPatternTestNg::InitMenuTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuPatternTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuPatternTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuPatternTestNg::GetPreviewMenuWrapper(
    SizeF itemSize, std::optional<MenuPreviewAnimationOptions> scaleOptions)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    if (!(LessOrEqual(itemSize.Width(), 0.0) || LessOrEqual(itemSize.Height(), 0.0))) {
        auto itemGeometryNode = textNode->GetGeometryNode();
        CHECK_NULL_RETURN(itemGeometryNode, nullptr);
        itemGeometryNode->SetFrameSize(itemSize);
    }
    targetNode->MountToParent(rootNode);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    if (scaleOptions != std::nullopt) {
        menuParam.previewAnimationOptions = scaleOptions.value();
    }
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(customNode, nullptr);
    auto customGeometryNode = customNode->GetGeometryNode();
    CHECK_NULL_RETURN(customGeometryNode, nullptr);
    customGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    return menuWrapperNode;
}

/**
 * @tc.name: MenuPatternTest038
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg038, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest039
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg039, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest040
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg040, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest041
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg041, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest042
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg042, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest043
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg043, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest044
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg044, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = NEW_FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest045
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg045, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = NEW_FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest046
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg046, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = NEW_FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest047
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg047, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest048
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg048, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest049
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg049, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::CONTEXT_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest050
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg050, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest051
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg051, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::DESKTOP_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest052
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg052, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::NAVIGATION_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest053
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg053, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_EXTENSION_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest054
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg054, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_CUSTOM_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest055
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg055, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_SUB_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest056
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg056, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU);

    menuPattern->FireBuilder();
    auto val = menuPattern->IsSelectMenu();

    EXPECT_EQ(val, false);
}

/**
 * @tc.name: MenuPatternTest057
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg057, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest058
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg058, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest059
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg059, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest060
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg060, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest061
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg061, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest062
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg062, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest063
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg063, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = NEW_FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest064
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg064, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = NEW_FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest065
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg065, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().screenWidth_ = NEW_FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest066
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg066, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest067
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg067, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest068
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg068, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::CONTEXT_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest069
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg069, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest070
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg070, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::DESKTOP_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest071
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg071, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::NAVIGATION_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest072
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg072, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_EXTENSION_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest073
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg073, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_CUSTOM_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest074
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg074, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_SUB_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest075
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg075, TestSize.Level1)
{
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(GetPreviewMenuWrapper()->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}

/**
 * @tc.name: MenuPatternTest0410
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPatternTestNg0410, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->FireBuilder();
    auto val = menuNode->isRestoreInfoUsed_;

    EXPECT_NE(val, false);
}
} // namespace OHOS::Ace::NG
