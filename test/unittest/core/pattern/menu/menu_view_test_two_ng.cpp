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

#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
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
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
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
const std::string TEXT_TAG = "text";
constexpr int32_t TARGET_ID = 100;
const int32_t NODE_ID = 1;
constexpr float TWO_HUNDRED = 200.0f;

} // namespace
class MenuViewTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    void InitMenuWrapperNode();
    RefPtr<FrameNode> GetMenuWrapperForHoverScale(bool isInterrupt);
    void MockPipelineContextGetTheme();
    int32_t GetNodeId();
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<FrameNode> wrapperNode_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<FrameNode> subMenuParent_;
    RefPtr<FrameNode> subMenu_;
    RefPtr<FrameNode> menuWrapperNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    int32_t nodeId_ = 1;
    bool isSubMenuBuilded_ = false;
};

void MenuViewTwoTestNg::SetUpTestCase() {}

void MenuViewTwoTestNg::TearDownTestCase() {}

void MenuViewTwoTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    InitMenuTestNg();
    isSubMenuBuilded_ = false;
    MockContainer::SetUp();
}

void MenuViewTwoTestNg::MockPipelineContextGetTheme()
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

void MenuViewTwoTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    menuFrameNode_ = nullptr;
    menuItemFrameNode_ = nullptr;
    subMenuParent_ = nullptr;
    menuItemPattern_ = nullptr;
    wrapperNode_ = nullptr;
    subMenu_ = nullptr;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    MockContainer::TearDown();
}

int32_t MenuViewTwoTestNg::GetNodeId()
{
    nodeId_++;
    return nodeId_;
}

void MenuViewTwoTestNg::InitMenuTestNg()
{
    std::function<void()> buildFun = [this]() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
        isSubMenuBuilded_ = true;
    };
    wrapperNode_ =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuFrameNode_ = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    subMenu_ = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    menuItemFrameNode_ =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    subMenuParent_ =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    auto itemComponent = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent3 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    itemComponent->MountToParent(subMenuParent_);
    itemComponent2->MountToParent(subMenuParent_);
    itemComponent3->MountToParent(subMenuParent_);
    menuItemFrameNode_->MountToParent(menuFrameNode_);
    subMenuParent_->MountToParent(menuFrameNode_);
    menuFrameNode_->MountToParent(wrapperNode_);
    subMenu_->MountToParent(wrapperNode_);
    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);
    menuItemPattern_->SetSubBuilder(buildFun);
    menuItemPattern_->SetIsSubMenuShowed(false);
    auto pattern2 = subMenuParent_->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->SetSubBuilder(buildFun);
    pattern2->SetIsSubMenuShowed(false);
    auto menuPattern = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetShowedSubMenu(subMenu_);
    auto subMenuPattern = subMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent_);
}

void MenuViewTwoTestNg::InitMenuWrapperNode()
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    menuWrapperNode_ = MenuView::Create(std::move(selectParams), NODE_ID, "");
}

RefPtr<FrameNode> MenuViewTwoTestNg::GetMenuWrapperForHoverScale(bool isInterrupt)
{
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(targetNode, nullptr);

    MenuParam menuParam;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    menuParam.isShowHoverImage = true;
    menuParam.hoverScaleInterruption = isInterrupt;

    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(TARGET_ID));
    CHECK_NULL_RETURN(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetMenuParam(menuParam);
    menuWrapperPattern->SetIsShowHoverImage(true);
    menuWrapperPattern->SetHoverScaleInterruption(menuParam.hoverScaleInterruption);

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(targetNode->GetId(), targetNode->GetTag(), MenuType::MENU));
    CHECK_NULL_RETURN(menuNode, nullptr);
    menuNode->MountToParent(menuWrapperNode);

    auto flexNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<FlexLayoutPattern>(false));
    CHECK_NULL_RETURN(flexNode, nullptr);
    flexNode->MountToParent(menuWrapperNode);

    auto stackNode = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_RETURN(stackNode, nullptr);
    stackNode->MountToParent(flexNode);

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->MountToParent(stackNode);

    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    CHECK_NULL_RETURN(previewNode, nullptr);
    auto menuPreviewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_RETURN(menuPreviewPattern, nullptr);
    menuPreviewPattern->SetIsShowHoverImage(true);
    previewNode->MountToParent(stackNode);

    return menuWrapperNode;
}

/**
 * @tc.name: UpdateHoverImagePreivewPosition
 * @tc.desc: Verify flex position for hoverImage.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTwoTestNg, UpdateHoverImagePreivewPosition001, TestSize.Level1)
{
    auto menuWrapperNode = GetMenuWrapperForHoverScale(false);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto flexNode = menuWrapperPattern->GetHoverImageFlexNode();
    ASSERT_NE(flexNode, nullptr);

    auto geometryNode = flexNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset(OffsetF(TWO_HUNDRED, TWO_HUNDRED));

    auto menuPreview = menuWrapperPattern->GetHoverImageCustomPreview();
    ASSERT_NE(menuPreview, nullptr);
    auto menuPreviewPattern = menuPreview->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(menuPreviewPattern, nullptr);

    MenuView::UpdateHoverImagePreivewPosition(menuPreviewPattern);

    auto flexRenderContext = flexNode->GetRenderContext();
    ASSERT_NE(flexRenderContext, nullptr);
    auto offset = OffsetT<Dimension>(Dimension(TWO_HUNDRED), Dimension(TWO_HUNDRED));
    EXPECT_EQ(offset, flexRenderContext->GetPositionValue({}));
}

/**
 * @tc.name: ShowHoverImageForInterruption
 * @tc.desc: Verify stackNode opacity and clipEdge
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTwoTestNg, ShowHoverImageForInterruption001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto menuWrapperNode = GetMenuWrapperForHoverScale(true);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto stackNode = menuWrapperPattern->GetHoverImageStackNode();
    ASSERT_NE(stackNode, nullptr);

    auto menuPreview = menuWrapperPattern->GetHoverImageCustomPreview();
    ASSERT_NE(menuPreview, nullptr);

    auto imageNode = menuWrapperPattern->GetHoverImagePreview();
    ASSERT_NE(imageNode, nullptr);
    auto imageContext = imageNode->GetRenderContext();
    ASSERT_NE(imageContext, nullptr);

    auto menu = menuWrapperPattern->GetMenu();
    ASSERT_NE(menu, nullptr);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto targetNode = FrameNode::GetOrCreateFrameNode(
        menuPattern->GetTargetTag(), menuPattern->GetTargetId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(targetNode, nullptr);

    MenuView::ShowHoverImageForInterruption(stackNode, menuPreview, imageContext, menuWrapperPattern);

    auto stackContext = stackNode->GetRenderContext();
    ASSERT_NE(stackContext, nullptr);
    EXPECT_TRUE(stackContext->GetClipEdge().value_or(false));
    EXPECT_TRUE(NearZero(stackContext->GetOpacity().value_or(1.0f)));
}

/**
 * @tc.name: UpdateMenuProperties002
 * @tc.desc: Verify UpdateMenuProperties function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTwoTestNg, UpdateMenuProperties002, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    OptionParam param1;
    optionParams.emplace_back(param1);

    MenuParam menuParam;
    menuParam.placement = Placement::NONE;
    menuParam.anchorPosition = OffsetF(10.0f, 10.0f);
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    menuParam.placement = OHOS::Ace::Placement::TOP;
    ASSERT_NE(wrapperNode_, nullptr);
    ASSERT_NE(menuFrameNode_, nullptr);

    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);

    MenuView::UpdateMenuProperties(wrapperNode_, menuFrameNode_, menuParam, MenuType::MENU);
    auto menuProperty = menuFrameNode_->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    EXPECT_TRUE(menuProperty->HasAnchorPosition());
}

/**
 * @tc.name: CheckHoverImageFinishForInterruption
 * @tc.desc: Verify stackNode opacity
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTwoTestNg, CheckHoverImageFinishForInterruption001, TestSize.Level1)
{
    auto menuWrapperNode = GetMenuWrapperForHoverScale(true);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto stackNode = menuWrapperPattern->GetHoverImageStackNode();
    ASSERT_NE(stackNode, nullptr);

    auto menuPreview = menuWrapperPattern->GetHoverImageCustomPreview();
    ASSERT_NE(menuPreview, nullptr);
    auto menuPreviewPattern = menuPreview->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(menuPreviewPattern, nullptr);

    MenuView::SetMenuHoverScaleStatus(TARGET_ID, MenuHoverScaleStatus::MENU_SHOW);
    MenuView::CheckHoverImageFinishForInterruption(menuWrapperPattern, menuPreviewPattern, stackNode);

    auto stackContext = stackNode->GetRenderContext();
    ASSERT_NE(stackContext, nullptr);
    auto opacity = stackContext->GetOpacity().value_or(0.0f);
    EXPECT_TRUE(NearEqual(opacity, 1.0));
}

/**
@tc.name: ReloadMenuParam001
@tc.desc: Test ReloadMenuParam function.
@tc.type: FUNC
*/
HWTEST_F(MenuViewTwoTestNg, ReloadMenuParam001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize MenuParam with default values
     * @tc.expected: MenuParam initialized with 0.0_vp borderRadius
     */
    InitMenuTestNg();
    ASSERT_NE(menuFrameNode_, nullptr);
    MenuParam menuParam;
    menuParam.borderRadius = NG::BorderRadiusProperty(0.0_vp);
    menuParam.previewBorderRadius = NG::BorderRadiusProperty(0.0_vp);
    menuParam.outlineColor = NG::BorderColorProperty();
    menuParam.outlineWidth = NG::BorderWidthProperty();
    menuParam.isDarkMode = true;
    menuParam.isWithTheme = false;

    /**
     * @tc.steps2: Temporarily set config change flag and call ReloadMenuParam
     * @tc.expected: MenuParam values remain unchanged after reload
     */
    auto data = g_isConfigChangePerform;
    if (!data) {
        g_isConfigChangePerform = true;
    }
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);

    /**
     * @tc.steps3: Verify MenuParam values
     * @tc.expected: All properties match initial settings
     */
    MenuParam& menuParamValue = const_cast<MenuParam&>(menuParam);
    EXPECT_EQ(menuParamValue.borderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParam.previewBorderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParamValue.outlineColor, NG::BorderColorProperty());
    EXPECT_EQ(menuParamValue.outlineWidth, NG::BorderWidthProperty());

    ResourceParseUtils::SetNeedReload(true);
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);
    g_isConfigChangePerform = data;

    menuParamValue = const_cast<MenuParam&>(menuParam);
    EXPECT_EQ(menuParamValue.borderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParam.previewBorderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParamValue.outlineColor, NG::BorderColorProperty());
    EXPECT_EQ(menuParamValue.outlineWidth, NG::BorderWidthProperty());
}

/**
 * @tc.name: ReloadMenuParam002
 * @tc.desc: Test ReloadMenuParam function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTwoTestNg, ReloadMenuParam002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuParam with default values.
     * @tc.expected: step1. borderRadius is 0.0_vp.
     */
    InitMenuTestNg();
    ASSERT_NE(menuFrameNode_, nullptr);
    MenuParam menuParam;
    menuParam.isDarkMode = true;
    menuParam.isWithTheme = false;

    /**
     * @tc.steps: step2. Set config change flag and reload.
     * @tc.expected: step2. All param values stay unchanged.
     */
    g_isConfigChangePerform = true;
    MenuParam& menuParamValue = const_cast<MenuParam&>(menuParam);
    menuParam.borderRadius = NG::BorderRadiusProperty(0.0_vp);
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);
    EXPECT_EQ(menuParamValue.borderRadius, NG::BorderRadiusProperty(0.0_vp));

    menuParam.previewBorderRadius = NG::BorderRadiusProperty(0.0_vp);
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);
    EXPECT_EQ(menuParam.previewBorderRadius, NG::BorderRadiusProperty(0.0_vp));

    menuParam.outlineColor = NG::BorderColorProperty();
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);
    EXPECT_EQ(menuParamValue.outlineColor, NG::BorderColorProperty());

    menuParam.outlineWidth = NG::BorderWidthProperty();
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);
    EXPECT_EQ(menuParamValue.outlineWidth, NG::BorderWidthProperty());

    g_isConfigChangePerform = false;
}

/**
@tc.name: ReloadMenuParam003
@tc.desc: Test ReloadMenuParam function.
@tc.type: FUNC
*/
HWTEST_F(MenuViewTwoTestNg, ReloadMenuParam003, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize MenuParam with specific values, including isWithTheme = true.
     * @tc.expected: MenuParam initialized with 0.0_vp and flags set.
     */
    InitMenuTestNg();
    ASSERT_NE(menuFrameNode_, nullptr);
    MenuParam menuParam;
    menuParam.borderRadius = NG::BorderRadiusProperty(0.0_vp);
    menuParam.previewBorderRadius = NG::BorderRadiusProperty(0.0_vp);
    menuParam.outlineColor = NG::BorderColorProperty();
    menuParam.outlineWidth = NG::BorderWidthProperty();
    menuParam.isDarkMode = true;
    menuParam.isWithTheme = true;

    auto pipeline = menuFrameNode_->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->colorMode_ = ColorMode::LIGHT;

    /**
     * @tc.steps2: Set config change flag and call ReloadMenuParam.
     * @tc.expected: Reload block should be skipped due to isWithTheme = true.
     */
    auto data = g_isConfigChangePerform;
    if (!data) {
        g_isConfigChangePerform = true;
    }
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);

    /**
     * @tc.steps3: Assert all fields remain unchanged (no reloading happened).
     */
    MenuParam& menuParamValue = const_cast<MenuParam&>(menuParam);
    EXPECT_EQ(menuParamValue.borderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParam.previewBorderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParamValue.outlineColor, NG::BorderColorProperty());
    EXPECT_EQ(menuParamValue.outlineWidth, NG::BorderWidthProperty());
    EXPECT_TRUE(menuParamValue.isDarkMode);

    ResourceParseUtils::SetNeedReload(true);
    MenuView::ReloadMenuParam(menuFrameNode_, menuParam);
    g_isConfigChangePerform = data;
    ResourceParseUtils::SetNeedReload(false);

    menuParamValue = const_cast<MenuParam&>(menuParam);
    EXPECT_EQ(menuParamValue.borderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParam.previewBorderRadius, NG::BorderRadiusProperty(0.0_vp));
    EXPECT_EQ(menuParamValue.outlineColor, NG::BorderColorProperty());
    EXPECT_EQ(menuParamValue.outlineWidth, NG::BorderWidthProperty());
    EXPECT_TRUE(menuParamValue.isDarkMode);
    g_isConfigChangePerform = false;
}
} // namespace OHOS::Ace::NG