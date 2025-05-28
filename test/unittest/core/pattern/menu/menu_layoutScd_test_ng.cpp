/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/pipeline/pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
constexpr float CURRENT_OFFSET = -0.5f;
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
const std::string MENU_ITEM_TEXT = "menuItem";
const std::string MENU_ITEM_GROUP_TEXT = "menuItemGroup";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float POSITION_OFFSET = 100.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr double MENU_OFFSET_X = 10.0;
constexpr double MENU_OFFSET_Y = 10.0;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;

constexpr float OFFSET_THIRD = 200.0f;
constexpr float OFFSET_FORTH = 300.0f;
constexpr float OFFSET_FIFTH = 50.0f;
constexpr int OFFSET_Y_THIRD = 20;
constexpr int TOP_LEFT_Y = 18;
constexpr int PLACEMENT_RIGHT_Y = 29;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr float PREVIEW_HEIGHT = 125.0f;
constexpr float GREATER_WINDOW_MENU_HEIGHT = 1190.0f;
constexpr float GREATER_WINDOW_PREVIEW_WIDTH = 800.0f;
constexpr float GREATER_WINDOW_PREVIEW_WIDTH_SECOND = 900.0f;
constexpr float GREATER_WINDOW_PREVIEW_HEIGHT = 1165.0f;
constexpr float GREATER_WINDOW_PREVIEW_HEIGHT_SECOND = 1376.0f;
constexpr float GREATER_HALF_PREVIEW_MENUITEM_HEIGHT = 700.0f;
constexpr float SCALE_PREVIEW_WIDTH_FORTH = 576.0f;
constexpr float SCALE_PREVIEW_WIDTH_FORTH_SECOND = 720.0f;
constexpr float SCALE_PREVIEW_HEIGHT = 270.0f;
constexpr float SCALE_PREVIEW_HEIGHT_FORTH = 100.0f;
constexpr float SCALE_MENU_HEIGHT = 952.0f;
constexpr float MENU_SIZE_WIDTH_SECOND = 199.0f;
constexpr double DIP_SCALE = 1.5;
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
constexpr double CONST_DOUBLE_ZREO = 0.0;
constexpr float SCALE_ANIMATION_FIRST = 0.8f;
constexpr float PLACEMENT_MENU_SPACE = 12.0f;
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuLayout2TestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuLayout2TestNg::SetUpTestCase() {}

void MenuLayout2TestNg::TearDownTestCase() {}

void MenuLayout2TestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayout2TestNg::TearDown()
{
    MockContainer::TearDown();
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

RefPtr<FrameNode> MenuLayout2TestNg::GetPreviewMenuWrapper(
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

void MenuLayout2TestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else {
            return AceType::MakeRefPtr<MenuTheme>();
        }
    });
}

RefPtr<FrameNode> GetImagePreviewMenuWrapper(std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    CHECK_NULL_RETURN(menuWrapperNode, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto previewNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(previewNode, nullptr);
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    menuPattern->SetPreviewMode(MenuPreviewMode::IMAGE);
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    if (scaleOptions != std::nullopt) {
        menuPattern->SetPreviewBeforeAnimationScale(scaleOptions.value().scaleFrom);
        menuPattern->SetPreviewAfterAnimationScale(scaleOptions.value().scaleTo);
    }

    return menuWrapperNode;
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4200
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4200, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, OFFSET_THIRD);
    menuAlgorithm->previewScale_ = 1.0f;

    /**
     * @tc.steps: step2. the window can accommodate preview, placement is default, layout preview and menu
     * @tc.expected: preview size is fixed [PREVIEW_WIDTH, TARGET_SIZE_HEIGHT], menu and preview bottom border
     * distance TARGET_SECURITY, align the menu with the left border of the preview
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM_LEFT);
    menuAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(OFFSET_FORTH, OFFSET_THIRD);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), OffsetF(OFFSET_FORTH, OFFSET_THIRD));
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto expectMenuOffset = OffsetF(OFFSET_FORTH, OFFSET_THIRD + TARGET_SIZE_HEIGHT + PLACEMENT_MENU_SPACE);
    auto oldexpectMenuOffset = OffsetF(OFFSET_FORTH, OFFSET_THIRD / 2 + TARGET_SECURITY.ConvertToPx());
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));

    /**
     * @tc.steps: step3. the window can accommodate preview, placement is BOTTOM, layout preview and menu
     * @tc.expected: menu and preview bottom border distance TARGET_SECURITY, align the menu with the preview in the
     * center
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM);
    menuAlgorithm->placement_ = Placement::BOTTOM;
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    expectMenuOffset = OffsetF(OFFSET_FORTH, OFFSET_THIRD + TARGET_SIZE_HEIGHT + TARGET_SECURITY.ConvertToPx());
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    EXPECT_EQ(menuPattern->endOffset_, expectMenuOffset);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4300
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4300, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    /**
     * @tc.steps: step2. the height of window can't accommodate preview and menu, placement is default,
     * layout preview and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH, SCALE_OFFSET], scale the height of the menu
     * to SCALE_MENU_HEIGHT
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM_LEFT);
    menuAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    OffsetF center(menuAlgorithm->targetOffset_.GetX() + menuAlgorithm->targetSize_.Width() / 2,
        menuAlgorithm->targetOffset_.GetY() + menuAlgorithm->targetSize_.Height() / 2);
    auto previewSize = previewGeometryNode->GetMarginFrameSize() * menuAlgorithm->previewScale_;
    OffsetF offset(center.GetX() - previewSize.Width() / 2, 0.0f);
    auto x =
        std::clamp(offset.GetX(), static_cast<float>(menuAlgorithm->wrapperRect_.Left()) + menuAlgorithm->paddingStart_,
            static_cast<float>(menuAlgorithm->wrapperRect_.Right()) - menuAlgorithm->paddingEnd_ - previewSize.Width());
    auto expectPreviewOffset = OffsetF(x, 0.0f);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(88.062, 88.062));
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), OffsetF(406.031, (OFFSET_Y_THIRD - TOP_LEFT_Y) / 2));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4400
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4400, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, OFFSET_FORTH);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    auto pipelineContext = menuAlgorithm->GetCurrentPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. the window can accommodate preview, placement is TOP_LEFT, layout preview and menu
     * @tc.expected: preview size is fixed [PREVIEW_WIDTH, TARGET_SIZE_HEIGHT], menu and preview top border
     * distance TARGET_SECURITY, align the menu with the left border of the preview
     */
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    menuAlgorithm->placement_ = Placement::TOP_LEFT;
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(OFFSET_FORTH - OFFSET_THIRD - TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(CONST_DOUBLE_ZREO, CONST_DOUBLE_ZREO));
    auto expectMenuOffset = OffsetF(-TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO));

    /**
     * @tc.steps: step3. the window can accommodate preview, placement is TOP, layout preview and menu
     * @tc.expected: menu and preview bottom border distance TARGET_SECURITY, align the menu with the preview in the
     * center
     */
    layoutProperty->UpdateMenuPlacement(Placement::TOP);
    menuAlgorithm->placement_ = Placement::TOP;
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4500
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4500, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    auto pipelineContext = menuAlgorithm->GetCurrentPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. the height of window can't accommodate preview and menu, placement is TOP_LEFT,
     * layout preview and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH, SCALE_OFFSET], scale the height of the menu
     * to SCALE_MENU_HEIGHT
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->placement_ = Placement::TOP_LEFT;
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset =
        OffsetF(OFFSET_FORTH - GREATER_HALF_PREVIEW_MENUITEM_HEIGHT / 2 - OFFSET_FIFTH, CONST_DOUBLE_ZREO);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), OffsetF(CONST_DOUBLE_ZREO, CONST_DOUBLE_ZREO));
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(CONST_DOUBLE_ZREO, CONST_DOUBLE_ZREO));
    auto expectMenuOffset = OffsetF(-TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4600
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4600, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is TABLET, create menu node, preview node and menuLayoutAlgorithm, then set the
     * initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_HEIGHT;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, OFFSET_THIRD));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_HEIGHT, FULL_SCREEN_WIDTH);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_THIRD, OFFSET_THIRD);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    auto pipelineContext = menuAlgorithm->GetCurrentPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. the window can accommodate preview, placement is RIGHT_TOP, layout preview and menu
     * @tc.expected: menu and preview right border distance TARGET_SECURITY, align the menu with the top border of the
     * preview
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::RIGHT_TOP);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.0f, 0.0f, FULL_SCREEN_HEIGHT, FULL_SCREEN_WIDTH));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(OFFSET_THIRD, OFFSET_THIRD + (TARGET_SIZE_HEIGHT - OFFSET_THIRD) / 2);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), OffsetF(0, 0));
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(0, 0));
    auto expectMenuOffset = OffsetF(-TARGET_SIZE_WIDTH, -CONST_DOUBLE_ZREO);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO));
    /**
     * @tc.steps: step3. the window can accommodate preview, placement is LEFT_TOP, layout preview and menu
     * @tc.expected: menu and preview left border distance TARGET_SECURITY, align the menu with the top border of the
     * preview
     */
    layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::LEFT_TOP);
    menuAlgorithm->placement_ = Placement::LEFT_TOP;
    menuAlgorithm->targetOffset_ = OffsetF(FULL_SCREEN_HEIGHT - OFFSET_THIRD, OFFSET_THIRD);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4700
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4700, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is TABLET, create menu node, preview node and menuLayoutAlgorithm, then set the
     * initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH_SECOND, TARGET_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, OFFSET_THIRD));
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_THIRD, OFFSET_THIRD);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;

    /**
     * @tc.steps: step2. the window can not accommodate preview, placement is default, layout preview and menu
     * @tc.expected: preview size is fixed [SCALE_PREVIEW_WIDTH_SECOND, SCALE_MENU_HEIGHT_SECOND], menu and preview
     * right border distance TARGET_SECURITY, align the menu with the top border of the preview
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::RIGHT_TOP);
    menuAlgorithm->placement_ = Placement::RIGHT_TOP;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(CONST_DOUBLE_ZREO, CONST_DOUBLE_ZREO);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(-MENU_SIZE_WIDTH_SECOND, -MENU_SIZE_WIDTH_SECOND * 2));
    auto expectMenuOffset = OffsetF(-MENU_SIZE_WIDTH_SECOND, CONST_DOUBLE_ZREO);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(MENU_SIZE_WIDTH_SECOND, CONST_DOUBLE_ZREO));
    /**
     * @tc.steps: step3. the window can not accommodate preview, placement is RIGHT, layout preview and menu
     * @tc.expected: menu and preview bottom right distance TARGET_SECURITY, align the menu with the preview in the
     * center
     */
    layoutProperty->UpdateMenuPlacement(Placement::RIGHT);
    menuAlgorithm->placement_ = Placement::RIGHT;
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    menuGeometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH_SECOND, TARGET_SIZE_HEIGHT));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4800
 * @tc.desc: Test Measure with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4800, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is PHONE, create menu node, preview node and menuLayoutAlgorithm, then set the
     * initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
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

    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));

    /**
     * @tc.steps: step2. call Measure function
     * @tc.expected: the placement of the menu defaults to BOTTOM_LEFT
     */
    menuAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(menuAlgorithm->placement_, OHOS::Ace::Placement::BOTTOM_LEFT);
    ASSERT_TRUE(menuLayoutProperty->GetMenuPlacement().has_value());
    EXPECT_EQ(menuLayoutProperty->GetMenuPlacement().value(), OHOS::Ace::Placement::BOTTOM_LEFT);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg4900
 * @tc.desc: Test Measure with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg4900, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is TABLET, create menu node, preview node and menuLayoutAlgorithm, then set the
     * initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    SystemProperties::SetDeviceType(DeviceType::TABLET);
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
    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step2. call Measure function
     * @tc.expected: the placement of the menu defaults to RIGHT_TOP
     */
    menuAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(menuAlgorithm->placement_, OHOS::Ace::Placement::BOTTOM_LEFT);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5000
 * @tc.desc: Test Measure with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5000, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is PHONE and orientation is LANDSCAPE, create menu node, preview node and
     * menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
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
    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step2. call Measure function
     * @tc.expected: the placement of the menu defaults to RIGHT_TOP
     */
    menuAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(menuAlgorithm->placement_, OHOS::Ace::Placement::BOTTOM_LEFT);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5100
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetImagePreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;

    /**
     * @tc.steps: step2. the width of window can't accommodate preview and menu, placement is BOTTOM_LEFT,
     * layout preview and menu
     * @tc.expected: scale the preview to [FULL_SCREEN_WIDTH, SCALE_PREVIEW_HEIGHT]
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM_LEFT);
    menuAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    previewGeometryNode->SetFrameSize(SizeF(GREATER_WINDOW_PREVIEW_WIDTH, OFFSET_FORTH));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(CONST_DOUBLE_ZREO, CONST_DOUBLE_ZREO);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(FULL_SCREEN_WIDTH, SCALE_PREVIEW_HEIGHT));
    auto expectMenuOffset = OffsetF(CONST_DOUBLE_ZREO, 282);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5200
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5200, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetImagePreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;

    /**
     * @tc.steps: step2. the width of window can't accommodate preview and menu, placement is TOP_LEFT,
     * layout preview and menu
     * @tc.expected: scale the preview to [FULL_SCREEN_WIDTH, SCALE_PREVIEW_HEIGHT]
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->placement_ = Placement::TOP_LEFT;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    previewGeometryNode->SetFrameSize(SizeF(GREATER_WINDOW_PREVIEW_WIDTH, OFFSET_FORTH));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectMenuOffset = OffsetF(0.0f, 382.0f);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    EXPECT_TRUE(previewGeometryNode->GetFrameOffset().NonNegative());
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(SCALE_PREVIEW_WIDTH_FORTH_SECOND, SCALE_PREVIEW_HEIGHT));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5300
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5300, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    /**
     * @tc.steps: step2. the height of window can't accommodate preview and menu, and the menu height is less than half
     * the height of the preview content , placement is BOTTOM_LEFT, layout preview and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH, SCALE_PREVIEW_HEIGHT_THIRD]
     */
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_PREVIEW_HEIGHT));
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM_LEFT);
    menuAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(305.536, CONST_DOUBLE_ZREO);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(88.927, FULL_SCREEN_HEIGHT - POSITION_OFFSET));
    auto expectMenuOffset = OffsetF(406.464, OFFSET_Y_THIRD * DIP_SCALE - PLACEMENT_RIGHT_Y);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    /**
     * @tc.steps: step3. the height of window can't accommodate preview and menu, and the menu height is less than half
     * the height of the preview content , placement is TOP_LEFT, layout preview and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH, SCALE_PREVIEW_HEIGHT_THIRD], menu is on top
     */
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->placement_ = Placement::TOP_LEFT;
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    EXPECT_TRUE(previewGeometryNode->GetFrameOffset().NonNegative());
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(88.927, FULL_SCREEN_HEIGHT - POSITION_OFFSET));
    EXPECT_TRUE(menuGeometryNode->GetFrameOffset().NonNegative());
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5400
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5400, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper(SizeF(TARGET_SIZE_WIDTH, GREATER_HALF_PREVIEW_MENUITEM_HEIGHT));
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;

    /**
     * @tc.steps: step2. the height of window can't accommodate preview and menu, and the menu height is less than half
     * height of the preview content, but the item total size is great than it , placement is BOTTOM_LEFT,
     * layout preview and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH_THIRD, SCALE_PREVIEW_HEIGHT_SECOND]
     */
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM_LEFT);
    menuAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_PREVIEW_HEIGHT_SECOND));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(322.481, CONST_DOUBLE_ZREO);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(55.0388, 757.333));
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), OffsetF(389.519, OFFSET_Y_THIRD * DIP_SCALE - PLACEMENT_RIGHT_Y));
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(OFFSET_THIRD / 2, 378.667f));

    /**
     * @tc.steps: step3. the height of window can't accommodate preview and menu, and the menu height is less than half
     * height of the preview content, but the item total size is great than it , placement is TOP_LEFT, layout preview
     * and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH_THIRD, SCALE_PREVIEW_HEIGHT_SECOND]
     */
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->placement_ = Placement::TOP_LEFT;

    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_PREVIEW_HEIGHT_SECOND));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    EXPECT_TRUE(previewGeometryNode->GetFrameOffset().NonNegative());
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(55.0388, 757.333));
    EXPECT_TRUE(menuGeometryNode->GetFrameOffset().NonNegative());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5500
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5500, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, OFFSET_FORTH));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, OFFSET_THIRD);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    auto pipelineContext = menuAlgorithm->GetCurrentPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. the window can accommodate preview, placement is TOP_LEFT, but menu is in top security
     * layout preview and menu
     * @tc.expected: preview offset is fixed [OFFSET_FORTH + (TARGET_SIZE_WIDTH - PREVIEW_WIDTH) / 2,
     * PORTRAIT_TOP_SECURITY.ConvertToPx() + OFFSET_FORTH + TARGET_SECURITY.ConvertToPx()],
     * menu offset is [OFFSET_FORTH + (TARGET_SIZE_WIDTH - PREVIEW_WIDTH) / 2, PORTRAIT_TOP_SECURITY.ConvertToPx()]
     */
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    menuAlgorithm->placement_ = Placement::TOP_LEFT;
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(CONST_DOUBLE_ZREO, CONST_DOUBLE_ZREO);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(CONST_DOUBLE_ZREO, CONST_DOUBLE_ZREO));
    auto expectMenuOffset = OffsetF(-TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, CONST_DOUBLE_ZREO));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5600
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5600, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, OFFSET_FORTH));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, FULL_SCREEN_HEIGHT - OFFSET_THIRD);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->param_.previewMenuGap = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;

    /**
     * @tc.steps: step2. the window can accommodate preview, placement is BOTTOM_LEFT, but menu is in top security
     * layout preview and menu
     * @tc.expected: preview offset is fixed [OFFSET_FORTH, FULL_SCREEN_HEIGHT - OFFSET_FORTH -
     * TARGET_SECURITY.ConvertToPx() - TARGET_SIZE_HEIGHT], menu offset is [OFFSET_FORTH, FULL_SCREEN_HEIGHT -
     * OFFSET_FORTH]
     */
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    menuAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM_LEFT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset =
        OffsetF(OFFSET_FORTH, FULL_SCREEN_HEIGHT - OFFSET_FORTH - TARGET_SECURITY.ConvertToPx() - TARGET_SIZE_HEIGHT);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), expectPreviewOffset);
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto expectMenuOffset = OffsetF(OFFSET_FORTH, FULL_SCREEN_HEIGHT - OFFSET_FORTH);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, OFFSET_FORTH));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5700
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5700, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetImagePreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;

    /**
     * @tc.steps: step2. the width and height of window can't accommodate preview and menu, placement is BOTTOM_LEFT,
     * layout preview and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH_FORTH, SCALE_PREVIEW_HEIGHT_FORTH]
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::BOTTOM_LEFT);
    menuAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    previewGeometryNode->SetFrameSize(SizeF(GREATER_WINDOW_PREVIEW_WIDTH_SECOND, PREVIEW_HEIGHT));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), OffsetF(0.0, 0.0));
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(SCALE_PREVIEW_WIDTH_FORTH_SECOND, SCALE_PREVIEW_HEIGHT_FORTH));
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), OffsetF(0.0, SCALE_PREVIEW_HEIGHT_FORTH + PLACEMENT_MENU_SPACE));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5800
 * @tc.desc: Test Layout with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5800, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetImagePreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FORTH, 0.0f);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    auto pipelineContext = menuAlgorithm->GetCurrentPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. the width and height of window can't accommodate preview and menu, placement is TOP_LEFT,
     * layout preview and menu
     * @tc.expected: scale the preview to [SCALE_PREVIEW_WIDTH_FORTH, SCALE_PREVIEW_HEIGHT_FORTH], the size of menu is
     * [TARGET_SIZE_WIDTH, SCALE_MENU_HEIGHT]
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->placement_ = Placement::TOP_LEFT;
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    previewGeometryNode->SetFrameSize(SizeF(GREATER_WINDOW_PREVIEW_WIDTH_SECOND, PREVIEW_HEIGHT));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    auto expectPreviewOffset = OffsetF(OFFSET_FORTH + (TARGET_SIZE_WIDTH - SCALE_PREVIEW_WIDTH_FORTH) / 2,
        PORTRAIT_TOP_SECURITY.ConvertToPx() + TARGET_SECURITY.ConvertToPx() + SCALE_MENU_HEIGHT);
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(previewGeometryNode->GetFrameSize(), SizeF(0.0f, 0.0f));
    auto expectMenuOffset = OffsetF(-TARGET_SIZE_WIDTH, 0);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), expectMenuOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameSize(), SizeF(TARGET_SIZE_WIDTH, 0.0f));
}

/**
 * @tc.name: SubMenuLayoutAlgorithmTestNg001
 * @tc.desc: Test SubMenuLayoutAlgorithm VerticalLayoutSubMenuHalfScreen and ModifySubMenuWrapper function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, SubMenuLayoutAlgorithmTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu item and submenu, set the layering parameter to false and call the
     * VerticalLayoutSubMenuHalfScreen method
     * @tc.expected: submenu node not null
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();

    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto subMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);

    // create subMenuLayoutAlgorithm
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);

    // link menuItem and submenu
    ASSERT_TRUE(menuPattern);
    menuPattern->SetParentMenuItem(item);
    item->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.type = TYPE;
    auto menuWrapperNode = MenuView::Create(textNode, TARGET_ID, "", menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto result = algorithm->VerticalLayoutSubMenuHalfScreen(menuNode->GetGeometryNode()->GetFrameSize(),
        algorithm->position_.GetY(), item->GetGeometryNode()->GetFrameSize(), item, false, nullptr);
    ASSERT_EQ(result, 0.0f);
    SizeF size_f(100, 200);
    algorithm->wrapperSize_ = size_f;

    /**
     * @tc.steps: step2. call the ModifySubMenuWrapper method.
     * @tc.expected: wrapperSize_ is not Data anomalies
     */
    algorithm->ModifySubMenuWrapper(wrapper);
    ASSERT_EQ(algorithm->wrapperSize_, SizeF(0, 0));
}

/**
 * @tc.name: SubMenuLayoutAlgorithmTestNg002
 * @tc.desc: Test SubMenuLayoutAlgorithm InitializePaddingAPI12 function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, SubMenuLayoutAlgorithmTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu item and submenu, set the layering parameter to false and call the
     * VerticalLayoutSubMenuHalfScreen method
     * @tc.expected: submenu node, subMenuLayoutAlgorithm are not null
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();

    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto subMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);

    // create subMenuLayoutAlgorithm
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);

    // link menuItem and submenu
    ASSERT_TRUE(menuPattern);
    menuPattern->SetParentMenuItem(item);
    item->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.type = TYPE;
    auto menuWrapperNode = MenuView::Create(textNode, TARGET_ID, "", menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto result = algorithm->VerticalLayoutSubMenuHalfScreen(menuNode->GetGeometryNode()->GetFrameSize(),
        algorithm->position_.GetY(), item->GetGeometryNode()->GetFrameSize(), item, false, nullptr);
    ASSERT_EQ(result, 0.0f);
    SizeF size_f(100, 200);
    algorithm->wrapperSize_ = size_f;
    algorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());

    /**
     * @tc.steps: step2. call the ModifySubMenuWrapper method.
     * @tc.expected: wrapperSize_ is not Data anomalies
     */
    algorithm->ModifySubMenuWrapper(wrapper);
    ASSERT_EQ(algorithm->wrapperSize_, SizeF(0, 0));

    /**
     * @tc.steps: step3. call the InitializePaddingAPI12 method.
     * @tc.expected: padding is not zero
     */
    algorithm->canExpandCurrentWindow_ = true;
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    selectTheme->menuMediumMargin_ = 10.0_vp;
    algorithm->InitializePaddingAPI12(wrapper);
    ASSERT_EQ(algorithm->paddingStart_, 10.0f);
    ASSERT_EQ(algorithm->paddingEnd_, 10.0f);
    ASSERT_EQ(algorithm->paddingTop_, 0.0f);
    ASSERT_EQ(algorithm->paddingBottom_, 0.0f);
}

/**
 * @tc.name: SubMenuLayoutAlgorithmTestNg003
 * @tc.desc: Test SubMenuLayoutAlgorithm InitializePaddingAPI12 function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, SubMenuLayoutAlgorithmTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu item and submenu, set the layering parameter to false and call the
     * VerticalLayoutSubMenuHalfScreen method
     * @tc.expected: submenu node, subMenuLayoutAlgorithm are not null
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();

    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto subMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);

    // create subMenuLayoutAlgorithm
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);
    ASSERT_TRUE(menuPattern);

    // associated menuItem and submenu
    menuPattern->SetParentMenuItem(item);
    item->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.type = TYPE;
    auto menuWrapperNode = MenuView::Create(textNode, TARGET_ID, "", menuParam);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto result = algorithm->VerticalLayoutSubMenuHalfScreen(menuNode->GetGeometryNode()->GetFrameSize(),
        algorithm->position_.GetY(), item->GetGeometryNode()->GetFrameSize(), item, false, nullptr);
    ASSERT_EQ(result, 0.0f);
    SizeF size_f(100, 200);
    algorithm->wrapperSize_ = size_f;
    algorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());

    /**
     * @tc.steps: step2. call the ModifySubMenuWrapper method.
     * @tc.expected: wrapperSize_ is not Data anomalies
     */
    algorithm->ModifySubMenuWrapper(wrapper);
    ASSERT_EQ(algorithm->wrapperSize_, SizeF(0, 0));

    /**
     * @tc.cases: case2. layering parameter is false.
     * @tc.expected: padding is not zero
     */
    algorithm->canExpandCurrentWindow_ = false;
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    selectTheme->menuLargeMargin_ = 10.0_vp;
    algorithm->InitializePaddingAPI12(wrapper);
    ASSERT_EQ(algorithm->paddingStart_, 10.0f);
    ASSERT_EQ(algorithm->paddingEnd_, 10.0f);
    ASSERT_EQ(algorithm->paddingTop_, 0.0f);
    ASSERT_EQ(algorithm->paddingBottom_, 0.0f);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5900
 * @tc.desc: Verify Initialize and Measure when hierarchicalParameter is true.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg5900, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menuWrapperNode and menuNode.
     * @tc.expected: menuWrapperNode and menuNode are not null.
     */
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;

    // create menuWrapperNode to get main menu
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());

    /**
     * @tc.steps: step2. build menu layoutwrapper and set the hierarchical parameter to true.
     * @tc.expected: no exception in the method return value.
     */
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    int32_t backApiversion = container->GetApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    container->SetApiTargetVersion(backApiversion);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg6000
 * @tc.desc: Verify Initialize and Measure when hierarchicalParameter is false.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg6000, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menuWrapperNode and menuNode.
     * @tc.expected: menuWrapperNode and menuNode are not null.
     */
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;

    // create menuWrapperNode to get main menu
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());

    /**
     * @tc.steps: step2. build menu layoutwrapper and set the hierarchical parameter to false.
     * @tc.expected: no exception in the method return value.
     */
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->canExpandCurrentWindow_ = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    int32_t backApiversion = container->GetApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    container->SetApiTargetVersion(backApiversion);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg038
 * @tc.desc: Test InitTargetSizeAndPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmInitTarget, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm and target is null
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(nodeId, TEXT_TAG, MenuType::CONTEXT_MENU);
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(nodeId, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    menuLayoutAlgorithm->targetNodeId_ = nodeId;
    menuLayoutAlgorithm->targetTag_ = "text";
    auto target = FrameNode::GetOrCreateFrameNode("text", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(target, nullptr);

    /**
     * @tc.steps: step3. layoutWrapper, target node and the geometry node of target is not null, isContextMenu is false
     * @tc.expected: targetOffset_ is OffsetF(0.0f, 0.0f)
     */
    std::vector<SelectParam> params;
    params.push_back({ "MenuItem", "Icon" });
    auto frameNode = MenuView::Create(params, 1, EMPTY_TEXT);
    ASSERT_NE(frameNode, nullptr);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode* layoutWrapper =
        new LayoutWrapperNode(frameNode, menuGeometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    geometryNode->frame_ = geometryProperty;
    target->geometryNode_ = geometryNode;
    menuLayoutAlgorithm->InitTargetSizeAndPosition(layoutWrapper, false, menuPattern);
    EXPECT_EQ(menuLayoutAlgorithm->targetOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg043
 * @tc.desc: Test Measure with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TestNg, MenuLayoutAlgorithmTestNg043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is PHONE and orientation is LANDSCAPE, create menu node, preview node and
     * menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
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
    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    menuAlgorithm->Measure(&layoutWrapper);
    menuPattern->SetIsHeightModifiedBySelect(true);
    menuLayoutProperty->UpdateSelectModifiedHeight(CURRENT_OFFSET);
    /**
     * @tc.steps: step2. call Measure function
     * @tc.expected: the placement of the menu defaults to RIGHT_TOP
     */
    menuAlgorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(menuPattern->IsHeightModifiedBySelect());
    EXPECT_TRUE(LessOrEqual(CURRENT_OFFSET, menuAlgorithm->wrapperRect_.Height() * SCALE_ANIMATION_FIRST));

    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuAlgorithm->wrapperSize_ = size_f;
    menuAlgorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());
    auto result = menuAlgorithm->VerticalLayout(size, clickPosition, true);
    EXPECT_EQ(result, clickPosition);
}
} // namespace OHOS::Ace::NG
