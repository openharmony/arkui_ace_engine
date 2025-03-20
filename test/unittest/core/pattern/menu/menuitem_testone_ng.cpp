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
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_row_pattern.h"
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
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_base.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_algorithm.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
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
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 100.0f;
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;

const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuItemTestOneNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<MenuItemLayoutAlgorithm> menuItemLayoutAlgorithm_;
};

void MenuItemTestOneNg::SetUpTestCase() {}

void MenuItemTestOneNg::TearDownTestCase() {}

void MenuItemTestOneNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    menuItemLayoutAlgorithm_ = AceType::MakeRefPtr<MenuItemLayoutAlgorithm>();
    MockContainer::SetUp();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuItemTestOneNg::TearDown()
{
    MockPipelineContext::TearDown();
    menuItemLayoutAlgorithm_ = nullptr;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    MockContainer::TearDown();
}

RefPtr<FrameNode> MenuItemTestOneNg::GetPreviewMenuWrapper(
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

void MenuItemTestOneNg::MockPipelineContextGetTheme()
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

/**
 * @tc.name: UpdateSelfSize001
 * @tc.desc: Test UpdateSelfSize func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, UpdateSelfSize001, TestSize.Level1)
{
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = 100;
    menuItemLayoutAlgorithm_->UpdateSelfSize(&layoutWrapper, 10.0f, 10.0f, 10.0f);
    layoutWrapper.currentChildCount_ = 100;
    menuItemLayoutAlgorithm_->UpdateSelfSize(&layoutWrapper, 10.0f, 10.0f, 10.0f);
    ASSERT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE));
}

/**
 * @tc.name: CheckNeedExpandContent001
 * @tc.desc: Test CheckNeedExpandContent func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CheckNeedExpandContent001, TestSize.Level1)
{
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    auto props = layoutWrapper.GetLayoutProperty();
    auto childConstraint = props->CreateChildConstraint();
    menuItemLayoutAlgorithm_->needExpandContent_ = false;
    menuItemLayoutAlgorithm_->CheckNeedExpandContent(&layoutWrapper, childConstraint);
    ASSERT_TRUE(menuItemLayoutAlgorithm_->needExpandContent_ == false);
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test Measure func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, Measure001, TestSize.Level1)
{
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));

    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutWrapper.GetLayoutProperty()->layoutConstraint_ = constraint;
    EXPECT_FALSE(layoutWrapper.GetLayoutProperty()->contentConstraint_);
    layoutWrapper.GetLayoutProperty()->contentConstraint_ = constraint;

    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> len = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = CalcSize(len, len);
    layoutWrapper.GetLayoutProperty()->calcLayoutConstraint_ = std::move(calcLayoutConstraint);
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    menuItemLayoutAlgorithm_->Measure(&layoutWrapper);
    ASSERT_TRUE(layoutWrapper.GetGeometryNode()->GetParentLayoutConstraint());
}

/**
 * @tc.name: Measure002
 * @tc.desc: Test Measure func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, Measure002, TestSize.Level1)
{
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));

    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutWrapper.GetLayoutProperty()->layoutConstraint_ = constraint;
    EXPECT_FALSE(layoutWrapper.GetLayoutProperty()->contentConstraint_);
    layoutWrapper.GetLayoutProperty()->contentConstraint_ = constraint;

    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> len = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = CalcSize(std::nullopt, len);
    layoutWrapper.GetLayoutProperty()->calcLayoutConstraint_ = std::move(calcLayoutConstraint);
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    menuItemLayoutAlgorithm_->Measure(&layoutWrapper);
    ASSERT_FALSE(layoutWrapper.GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize.value().Width().has_value());
}

/**
 * @tc.name: Measure003
 * @tc.desc: Test Measure func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, Measure003, TestSize.Level1)
{
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));

    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutWrapper.GetLayoutProperty()->layoutConstraint_ = constraint;
    EXPECT_FALSE(layoutWrapper.GetLayoutProperty()->contentConstraint_);
    layoutWrapper.GetLayoutProperty()->contentConstraint_ = constraint;

    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> len = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = std::nullopt;
    layoutWrapper.GetLayoutProperty()->calcLayoutConstraint_ = std::move(calcLayoutConstraint);
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    menuItemLayoutAlgorithm_->Measure(&layoutWrapper);
    ASSERT_FALSE(layoutWrapper.GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize.has_value());
}

/**
 * @tc.name: CheckNeedMatchParent001
 * @tc.desc: Test CheckNeedMatchParent func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CheckNeedMatchParent001, TestSize.Level1)
{
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);
    MockPipelineContextGetTheme();
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(18);

    /**
     * @tc.steps: step1. build frame node tree
     */
    RefPtr<FrameNode> outerMenuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() {
                return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
            });
    ASSERT_NE(outerMenuNode, nullptr);
    auto child = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());

    auto jsViewNode = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>()
    );
    ASSERT_NE(jsViewNode, nullptr);
    jsViewNode->MountToParent(outerMenuNode);

    auto jsViewNode1 = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>()
    );
    ASSERT_NE(jsViewNode1, nullptr);
    jsViewNode1->MountToParent(jsViewNode);

    RefPtr<FrameNode> innerMenuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() {return AceType::MakeRefPtr<InnerMenuPattern>(TARGET_ID, "", TYPE);});
    ASSERT_NE(innerMenuNode, nullptr);
    innerMenuNode->MountToParent(jsViewNode1);
    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    menuItemNode->MountToParent(innerMenuNode);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;

    auto innerMenuPattern = innerMenuNode->GetPattern<InnerMenuPattern>();
    ASSERT_NE(innerMenuPattern, nullptr);
    innerMenuPattern->isEmbedded_ = true;

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    auto layoutConstraint = props->GetLayoutConstraint();
    menuItemLayoutAlgorithm_->CheckNeedMatchParent(&layoutWrapper, layoutConstraint);

    EXPECT_EQ(menuItemPattern->GetExpandingMode(), SubMenuExpandingMode::EMBEDDED);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckUserHeight001
 * @tc.desc: Test CheckUserHeight func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CheckUserHeight001, TestSize.Level1)
{
    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    SizeF value(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT);
    props->UpdateMarginSelfIdealSize(value);
    props->UpdateContentConstraint();
    props->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(MENU_ITEM_SIZE_WIDTH), CalcLength(MENU_ITEM_SIZE_HEIGHT))
    );
    menuItemLayoutAlgorithm_->CheckUserHeight(&layoutWrapper);
}

/**
 * @tc.name: CalcItemHeight001
 * @tc.desc: Test CalcItemHeight func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CalcItemHeight001, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(20);
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    menuItemLayoutAlgorithm_->userSetPadding_ = true;
    menuItemLayoutAlgorithm_->userHeight_ = 48.0f;
    menuItemLayoutAlgorithm_->padding_ = props->CreatePaddingAndBorderWithDefault(12.0f, 4.0f, 0.0f, 0.0f);

    EXPECT_EQ(menuItemLayoutAlgorithm_->CalcItemHeight(30.0f, 30.0f), 40.0f);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CalcItemHeight002
 * @tc.desc: Test CalcItemHeight func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CalcItemHeight002, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(20);
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    menuItemLayoutAlgorithm_->userSetPadding_ = true;
    menuItemLayoutAlgorithm_->userHeight_ = 0.0f;
    menuItemLayoutAlgorithm_->padding_ = props->CreatePaddingAndBorderWithDefault(12.0f, 4.0f, 0.0f, 0.0f);

    EXPECT_EQ(menuItemLayoutAlgorithm_->CalcItemHeight(30.0f, 32.0f), 32.0f);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CalcItemHeight003
 * @tc.desc: Test CalcItemHeight func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CalcItemHeight003, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(20);
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    menuItemLayoutAlgorithm_->userSetPadding_ = false;
    menuItemLayoutAlgorithm_->userHeight_ = 48.0f;
    menuItemLayoutAlgorithm_->padding_ = props->CreatePaddingAndBorderWithDefault(12.0f, 4.0f, 0.0f, 0.0f);

    EXPECT_EQ(menuItemLayoutAlgorithm_->CalcItemHeight(30.0f, 32.0f), 48.0f);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CalcItemHeight004
 * @tc.desc: Test CalcItemHeight func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CalcItemHeight004, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(18);
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    menuItemLayoutAlgorithm_->userSetPadding_ = false;
    menuItemLayoutAlgorithm_->userHeight_ = 0.0f;
    menuItemLayoutAlgorithm_->padding_ = props->CreatePaddingAndBorderWithDefault(12.0f, 4.0f, 0.0f, 0.0f);

    EXPECT_EQ(menuItemLayoutAlgorithm_->CalcItemHeight(30.0f, 32.0f), 40.0f);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CalcContentExpandWidth001
 * @tc.desc: Test CalcContentExpandWidth func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, CalcContentExpandWidth001, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(20);
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    auto layoutConstraint = props->GetLayoutConstraint();

    menuItemLayoutAlgorithm_->minRowWidth_ = 50.0f;
    menuItemLayoutAlgorithm_->userSetPadding_ = true;
    menuItemLayoutAlgorithm_->padding_ = props->CreatePaddingAndBorderWithDefault(12.0f, 4.0f, 0.0f, 0.0f);
    menuItemLayoutAlgorithm_->CalcContentExpandWidth(layoutConstraint, 49.0f, 32.0f, 32.0f);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: GetDividerStroke001
 * @tc.desc: Test GetDividerStroke func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, GetDividerStroke001, TestSize.Level1)
{
    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto topDivider = FrameNode::GetOrCreateFrameNode(V2::MENU_DIVIDER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<MenuDividerPattern>(); });
    auto menuNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    topDivider->MountToParent(menuNode);
    menuItemPattern->topDivider_ = topDivider;
    ASSERT_EQ(menuItemLayoutAlgorithm_->GetDividerStroke(&layoutWrapper), 0.0f);
}

/**
 * @tc.name: GetDividerStroke002
 * @tc.desc: Test GetDividerStroke func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, GetDividerStroke002, TestSize.Level1)
{
    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto topDivider = FrameNode::GetOrCreateFrameNode(V2::MENU_DIVIDER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<MenuDividerPattern>(); });
    menuItemPattern->topDivider_ = topDivider;
    menuItemLayoutAlgorithm_->GetDividerStroke(&layoutWrapper);
    menuItemPattern->topDivider_ = nullptr;
    menuItemLayoutAlgorithm_->GetDividerStroke(&layoutWrapper);
}

/**
 * @tc.name: InitPadding001
 * @tc.desc: Test InitPadding func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, InitPadding001, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(18);
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>()
        );
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuItemNode, geometryNode, menuItemNode->GetLayoutProperty());
    auto props = layoutWrapper.GetLayoutProperty();
    PaddingProperty padding;
    props->UpdatePadding(padding);
    auto layoutConstraint = props->GetLayoutConstraint();
    menuItemLayoutAlgorithm_->horInterval_ = 12.0f;
    menuItemLayoutAlgorithm_->verInterval_ = 8.0f;
    menuItemLayoutAlgorithm_->InitPadding(props, layoutConstraint);

    padding.left = CalcLength(5.0f, DimensionUnit::PX);
    padding.right = CalcLength(5.0f, DimensionUnit::PX);
    padding.top = CalcLength(3.0f, DimensionUnit::PX);
    padding.bottom = CalcLength(3.0f, DimensionUnit::PX);
    menuItemLayoutAlgorithm_->InitPadding(props, layoutConstraint);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: MeasureClickableArea001
 * @tc.desc: Test MeasureClickableArea func .
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestOneNg, MeasureClickableArea001, TestSize.Level1)
{
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto clickableArea = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(clickableArea, nullptr);
    clickableArea->MountToParent(itemNode, CLICKABLE_AREA_VIEW_INDEX);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(18);
    ASSERT_NE(menuItemLayoutAlgorithm_, nullptr);
    menuItemLayoutAlgorithm_->userSetPadding_ = true;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(itemNode, geometryNode, itemNode->GetLayoutProperty());
    menuItemLayoutAlgorithm_->MeasureClickableArea(&layoutWrapper);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    menuItemLayoutAlgorithm_->MeasureClickableArea(&layoutWrapper);
}
} // namespace OHOS::Ace::NG