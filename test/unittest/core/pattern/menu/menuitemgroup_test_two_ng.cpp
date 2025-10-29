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

#include <type_traits>
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
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
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuItemGroupTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuItemGroupTwoTestNg();
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

void MenuItemGroupTwoTestNg::SetUpTestCase() {}

void MenuItemGroupTwoTestNg::TearDownTestCase() {}

void MenuItemGroupTwoTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme_ = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([menuTheme_](ThemeType type) -> RefPtr<Theme> {
        if (type == MenuTheme::TypeId()) {
            return menuTheme_;
        }
        return AceType::MakeRefPtr<SelectTheme>();
    });
    MockContainer::SetUp();
}

void MenuItemGroupTwoTestNg::TearDown()
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
    MockContainer::TearDown();
}

void MenuItemGroupTwoTestNg::InitMenuItemGroupTwoTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuItemGroupTwoTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuItemGroupTwoTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuItemGroupTwoTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: OnColorConfigurationUpdateTest001
 * @tc.desc: Test OnColorConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTwoTestNg, OnColorConfigurationUpdateTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create MenuItemGroupView and get frame node
     * @tc.expected: View and frame node created successfully
     */
    MenuItemGroupView menuItemGroupView;
    menuItemGroupView.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto menuItemGroupPattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(menuItemGroupPattern, nullptr);

    /**
     * @tc.steps2: Set up theme manager mock
     * @tc.expected: Theme manager returns select theme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        return selectTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps3: Create header and footer content
     * @tc.expected: Header and footer frame nodes created
     */
    menuItemGroupPattern->headerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(menuItemGroupPattern->headerContent_, nullptr);
    menuItemGroupPattern->footerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(menuItemGroupPattern->footerContent_, nullptr);

    /**
     * @tc.steps4: Get layout properties and themes
     * @tc.expected: Layout properties and themes obtained
     */
    auto headercontent = menuItemGroupPattern->headerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(headercontent, nullptr);
    auto headerpipeline = menuItemGroupPattern->headerContent_->GetContextWithCheck();
    ASSERT_NE(headerpipeline, nullptr);
    auto headermenuTheme = headerpipeline->GetTheme<SelectTheme>();
    ASSERT_NE(headermenuTheme, nullptr);

    auto footercontent = menuItemGroupPattern->footerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(footercontent, nullptr);
    auto footerpipeline = menuItemGroupPattern->footerContent_->GetContextWithCheck();
    ASSERT_NE(footerpipeline, nullptr);
    auto footermenuTheme = footerpipeline->GetTheme<SelectTheme>();
    ASSERT_NE(footermenuTheme, nullptr);

    /**
     * @tc.steps5: Set theme colors
     * @tc.expected: Theme colors set to red and blue
     */
    Color menuFontColor = Color::RED;
    Color secondaryFontColor = Color::BLUE;
    headermenuTheme->menuFontColor_ = menuFontColor;
    footermenuTheme->secondaryFontColor_ = secondaryFontColor;

    /**
     * @tc.steps6: Test with config change disabled
     * @tc.expected: Text colors not updated
     */
    g_isConfigChangePerform = false;
    EXPECT_EQ(SystemProperties::ConfigChangePerform(), false);
    menuItemGroupPattern->OnColorConfigurationUpdate();
    EXPECT_NE(headercontent->GetTextColor().value_or(Color::BLACK), headermenuTheme->GetMenuFontColor());
    EXPECT_NE(footercontent->GetTextColor().value_or(Color::BLACK), footermenuTheme->GetSecondaryFontColor());

    /**
     * @tc.steps7: Test with config change enabled
     * @tc.expected: Text colors updated to theme values
     */
    g_isConfigChangePerform = true;
    ASSERT_NE(SystemProperties::ConfigChangePerform(), false);
    menuItemGroupPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(headercontent->GetTextColor(), menuFontColor);
    EXPECT_EQ(footercontent->GetTextColor().value(), secondaryFontColor);
}

/**
 * @tc.name: MenuItemGroupViewCreateWithStringResourceObj001
 * @tc.desc: Test CreateWithStringResourceObj with HEADER types.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTwoTestNg, CreateWithStringResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create MenuItemGroupView and get frame node
     * @tc.expected: View and frame node created successfully
     */
    MenuItemGroupView view;
    view.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps2: Create header content
     * @tc.expected: Header frame node created
     */
    pattern->headerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(pattern->headerContent_, nullptr);
    auto textLayoutProperty = pattern->headerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps3: Call CreateWithStringResourceObj for header
     * @tc.expected: Resource object associated with header
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    view.CreateWithStringResourceObj(resObj, MenuItemGroupStringType::HEADER);

    /**
     * @tc.steps4: Test with empty resource cache
     * @tc.expected: Header content is empty
     */
    std::string str = "";
    std::string key = "MenuItemGroup" + MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::HEADER);
    pattern->AddResCache(key, str);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    resMgr->ReloadResources();
    EXPECT_EQ(textLayoutProperty->GetContentValue(u""), u"");

    /**
     * @tc.steps5: Test with valid resource cache
     * @tc.expected: Header content updated to "TEST"
     */
    str = "TEST";
    pattern->AddResCache(key, str);
    resMgr->ReloadResources();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), UtfUtils::Str8DebugToStr16(str));
}

/**
 * @tc.name: MenuItemGroupViewCreateWithStringResourceObj002
 * @tc.desc: Test CreateWithStringResourceObj with FOOTER types.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTwoTestNg, CreateWithStringResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps1: Create MenuItemGroupView and get frame node
     * @tc.expected: View and frame node created successfully
     */
    MenuItemGroupView view;
    view.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps2: Create footer content
     * @tc.expected: Footer frame node created
     */
    pattern->footerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(pattern->footerContent_, nullptr);
    auto textLayoutProperty = pattern->footerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps3: Call CreateWithStringResourceObj for footer
     * @tc.expected: Resource object associated with footer
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    view.CreateWithStringResourceObj(resObj, MenuItemGroupStringType::FOOTER);

    /**
     * @tc.steps4: Test with valid resource cache
     * @tc.expected: Footer content updated to "TEST"
     */
    std::string str = "TEST";
    std::string key = "MenuItemGroup" + MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::FOOTER);
    pattern->AddResCache(key, str);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    resMgr->ReloadResources();
    EXPECT_EQ(textLayoutProperty->GetContentValue(), UtfUtils::Str8DebugToStr16(str));
}

/**
 * @tc.name: StringTypeToString
 * @tc.desc: Test StringTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTwoTestNg, StringTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps1: Test HEADER string conversion
     * @tc.expected: Returns "Header"
     */
    std::string result1 = MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::HEADER);
    EXPECT_EQ(result1, "Header");

    /**
     * @tc.steps2: Test FOOTER string conversion
     * @tc.expected: Returns "Footer"
     */
    std::string result2 = MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::FOOTER);
    EXPECT_EQ(result2, "Footer");

    /**
     * @tc.steps3: Test unknown type conversion
     * @tc.expected: Returns "Unknown" for type 100
     */
    MenuItemGroupStringType unknownType = static_cast<MenuItemGroupStringType>(100);
    std::string result3 = MenuItemGroupView::StringTypeToString(unknownType);
    EXPECT_EQ(result3, "Unknown");
}
} // namespace OHOS::Ace::NG