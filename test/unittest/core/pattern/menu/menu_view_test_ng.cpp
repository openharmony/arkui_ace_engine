/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/common/ace_engine.h"
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
constexpr int32_t NODE_ID = 1;
constexpr float ZERO = 0.0f;
constexpr float ONE = 1.0f;
constexpr float TWO = 2.0f;
constexpr float FIVE = 5.0f;
constexpr float TEN = 10.0f;
constexpr float TWENTY = 20.0f;
constexpr float ONE_HUNDRED = 100.0f;
constexpr float TWO_HUNDRED = 200.0f;

} // namespace
class MenuViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    void InitMenuWrapperNode();
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

void MenuViewTestNg::SetUpTestCase() {}

void MenuViewTestNg::TearDownTestCase() {}

void MenuViewTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    InitMenuTestNg();
    isSubMenuBuilded_ = false;
    MockContainer::SetUp();
}

void MenuViewTestNg::MockPipelineContextGetTheme()
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

void MenuViewTestNg::TearDown()
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

int32_t MenuViewTestNg::GetNodeId()
{
    nodeId_++;
    return nodeId_;
}

void MenuViewTestNg::InitMenuTestNg()
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

void MenuViewTestNg::InitMenuWrapperNode()
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    menuWrapperNode_ = MenuView::Create(std::move(selectParams), NODE_ID, "");
}

/**
 * @tc.name: GetHasIcon001
 * @tc.desc: MenuView GetHasIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, GetHasIcon001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    OptionParam param1;
    param1.isPasteOption = true;
    param1.icon = "";
    OptionParam param2;
    param2.isPasteOption = true;
    param2.icon = "abc";
    OptionParam param3;
    param3.isPasteOption = false;
    param3.icon = "";
    OptionParam param4;
    param4.isPasteOption = false;
    param4.icon = "abc";

    optionParams.emplace_back(param1);
    optionParams.emplace_back(param2);
    optionParams.emplace_back(param3);
    optionParams.emplace_back(param4);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 3, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
}
/**
 * @tc.name: GetMenuPixelMap001
 * @tc.desc: MenuView GetMenuPixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, GetMenuPixelMap001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    MenuParam menuParam;
    MenuView::GetMenuPixelMap(targetNode, menuParam, wrapperNode_);

    ASSERT_NE(targetNode, nullptr);
}

/**
 * @tc.name: SkipMenuTest001
 * @tc.desc: Verify bindMenu gesture event.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, SkipMenuTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a targetNode
     */
    TextModelNG textModel;
    textModel.Create("Text");
    /**
     * @tc.steps: step2. bindMenuGesture with optionParams.
     * @tc.expected: check the menu event is not nullptr.
     */
    std::vector<OptionParam> optionParams;
    MenuParam param;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    ViewAbstractModelNG viewAbstractModel;
    viewAbstractModel.BindMenuGesture(std::move(optionParams), nullptr, param);
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub->showMenu_, nullptr);
    EXPECT_NE(gestureHub->bindMenuTouch_, nullptr);
    NG::ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: SkipMenuTest002
 * @tc.desc: Verify skip function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, SkipMenuTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a overlayManger
     */
    auto overlayManger = AceType::MakeRefPtr<OverlayManager>(nullptr);
    /**
     * @tc.steps: step2. skip menu show with target id
     * @tc.expected: check the skip ids not empty.
     */
    overlayManger->SkipMenuShow(TARGET_ID);
    ASSERT_FALSE(overlayManger->skipTargetIds_.empty());
    /**
     * @tc.steps: step3. skip menu show with target id again
     * @tc.expected: The skip id is not added repeatedly.
     */
    overlayManger->SkipMenuShow(TARGET_ID);
    EXPECT_EQ(overlayManger->skipTargetIds_.size(), 1);
    /**
     * @tc.steps: step4. search targetId will skip
     * @tc.expected: Return true skip the menu show.
     */
    EXPECT_TRUE(overlayManger->CheckSkipMenuShow(TARGET_ID));
    /**
     * @tc.steps: step5. resume the target menu show
     * @tc.expected: Remove success and CheckSkipMenuShow return false.
     */
    overlayManger->ResumeMenuShow(TARGET_ID);
    ASSERT_TRUE(overlayManger->skipTargetIds_.empty());
    EXPECT_FALSE(overlayManger->CheckSkipMenuShow(TARGET_ID));
}

/**
 * @tc.name: UpdateEmbeddedPercentReference001
 * @tc.desc: Verify UpdateEmbeddedPercentReference.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateEmbeddedPercentReference001, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    ASSERT_EQ(frameNode->GetParent(), wrapperNode);
    auto wrapperLayoutProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF wrapperLayoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    wrapperLayoutProperty->UpdateLayoutConstraint(wrapperLayoutConstraint);
    wrapperNode->SetLayoutProperty(wrapperLayoutProperty);
    auto menuItemProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    menuItemProperty->UpdateLayoutConstraint(layoutConstraintF);
    frameNode->SetLayoutProperty(menuItemProperty);
    menuItemProperty->UpdateContent("test1");
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateEmbeddedPercentReference(layoutWrapper, childConstraint, layoutConstraint);
    EXPECT_EQ(childConstraint.percentReference.height_, FIVE);
}

/**
 * @tc.name: UpdateEmbeddedPercentReference002
 * @tc.desc: Verify UpdateEmbeddedPercentReference.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateEmbeddedPercentReference002, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    ASSERT_EQ(frameNode->GetParent(), wrapperNode);
    auto wrapperLayoutProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF wrapperLayoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    wrapperLayoutProperty->UpdateLayoutConstraint(wrapperLayoutConstraint);
    wrapperNode->SetLayoutProperty(wrapperLayoutProperty);
    auto menuItemProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    menuItemProperty->UpdateLayoutConstraint(layoutConstraintF);
    frameNode->SetLayoutProperty(menuItemProperty);
    menuItemProperty->UpdateContent("test1");
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        std::make_optional<CalcSize>(CalcLength(TEN), CalcLength(TWENTY));
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateEmbeddedPercentReference(layoutWrapper, childConstraint, layoutConstraint);
    EXPECT_EQ(childConstraint.percentReference.height_, TWENTY);
}

/**
 * @tc.name: UpdateEmbeddedPercentReference003
 * @tc.desc: Verify UpdateEmbeddedPercentReference.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateEmbeddedPercentReference003, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    ASSERT_EQ(frameNode->GetParent(), wrapperNode);
    auto wrapperLayoutProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF wrapperLayoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    wrapperLayoutProperty->UpdateLayoutConstraint(wrapperLayoutConstraint);
    wrapperNode->SetLayoutProperty(wrapperLayoutProperty);
    auto menuItemProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    menuItemProperty->UpdateLayoutConstraint(layoutConstraintF);
    frameNode->SetLayoutProperty(menuItemProperty);
    menuItemProperty->UpdateContent("test1");
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateEmbeddedPercentReference(layoutWrapper, childConstraint, layoutConstraint);
    EXPECT_EQ(childConstraint.percentReference.height_, FIVE);
}

/**
 * @tc.name: UpdateEmbeddedPercentReference004
 * @tc.desc: Verify UpdateEmbeddedPercentReference.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateEmbeddedPercentReference004, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    auto wrapperLayoutProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF wrapperLayoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    wrapperLayoutProperty->UpdateLayoutConstraint(wrapperLayoutConstraint);
    wrapperNode->SetLayoutProperty(wrapperLayoutProperty);
    auto menuItemProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    menuItemProperty->UpdateLayoutConstraint(layoutConstraintF);
    frameNode->SetLayoutProperty(menuItemProperty);
    menuItemProperty->UpdateContent("test1");
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        std::make_optional<CalcSize>(CalcLength(TEN), CalcLength(TWENTY));
    layoutWrapper->GetGeometryNode()->parentLayoutConstraint_ = std::make_optional<LayoutConstraintF>();
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateEmbeddedPercentReference(layoutWrapper, childConstraint, layoutConstraint);
    EXPECT_EQ(childConstraint.percentReference.height_, TWENTY);
}

/**
 * @tc.name: UpdateEmbeddedPercentReference005
 * @tc.desc: Verify UpdateEmbeddedPercentReference.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateEmbeddedPercentReference005, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    ASSERT_EQ(frameNode->GetParent(), wrapperNode);
    auto wrapperLayoutProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF wrapperLayoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    wrapperLayoutProperty->UpdateLayoutConstraint(wrapperLayoutConstraint);
    wrapperNode->SetLayoutProperty(wrapperLayoutProperty);
    auto menuItemProperty = AceType::MakeRefPtr<MenuItemLayoutProperty>();
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    menuItemProperty->UpdateLayoutConstraint(layoutConstraintF);
    frameNode->SetLayoutProperty(menuItemProperty);
    menuItemProperty->UpdateContent("test1");
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        std::make_optional<CalcSize>(CalcLength(TEN), std::nullopt);
    layoutWrapper->GetGeometryNode()->parentLayoutConstraint_ = std::make_optional<LayoutConstraintF>();
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateEmbeddedPercentReference(layoutWrapper, childConstraint, layoutConstraint);
    EXPECT_EQ(childConstraint.percentReference.height_, FIVE);
}

/**
 * @tc.name: UpdateSelfSize001
 * @tc.desc: Verify UpdateSelfSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateSelfSize001, TestSize.Level1)
{
    auto menuNodeTwo =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuNodeNew =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    menuNodeNew->MountToParent(menuNodeTwo);
    ASSERT_NE(menuNodeNew, nullptr);
    menuNode->MountToParent(menuNodeNew);
    ASSERT_NE(menuNode, nullptr);
    frameNode->MountToParent(menuNode);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    auto childWrapper = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper->GetOrCreateChildByIndex(0));
    ASSERT_NE(childWrapper, nullptr);
    auto iter = layoutWrapper->childrenMap_.find(0);
    if (iter == layoutWrapper->childrenMap_.end()) {
        layoutWrapper->AppendChild(childWrapper);
    }
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateSelfSize(AccessibilityManager::RawPtr(layoutWrapper), childConstraint, layoutConstraint);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.width_, TEN);
}

/**
 * @tc.name: UpdateSelfSize002
 * @tc.desc: Verify UpdateSelfSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateSelfSize002, TestSize.Level1)
{
    auto menuNodeTwo =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuNodeNew =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNodeNew, nullptr);
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    menuNodeNew->MountToParent(menuNodeTwo);
    menuNode->MountToParent(menuNodeNew);
    frameNode->MountToParent(menuNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto firstFrameNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    layoutWrapper->AppendChild(childLayoutWrapper);
    auto pattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    pattern->isStackSubmenu_ = true;
    pattern->isEmbedded_ = true;
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    auto childWrapper = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper->GetOrCreateChildByIndex(0));
    ASSERT_NE(childWrapper, nullptr);
    auto iter = layoutWrapper->childrenMap_.find(0);
    if (iter == layoutWrapper->childrenMap_.end()) {
        layoutWrapper->AppendChild(childWrapper);
    }
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateSelfSize(AccessibilityManager::RawPtr(layoutWrapper), childConstraint, layoutConstraint);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->frame_.rect_.width_, ONE_HUNDRED);
}

/**
 * @tc.name: ResetLayoutConstraintMinWidth001
 * @tc.desc: Verify ResetLayoutConstraintMinWidth.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, ResetLayoutConstraintMinWidth001, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    LayoutConstraintF layoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    EXPECT_EQ(algorithm->ResetLayoutConstraintMinWidth(layoutWrapper, layoutConstraint).selfIdealSize.width_, ONE);
}

/**
 * @tc.name: ResetLayoutConstraintMinWidth002
 * @tc.desc: Verify ResetLayoutConstraintMinWidth.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, ResetLayoutConstraintMinWidth002, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        std::make_optional<CalcSize>(CalcLength(TEN), CalcLength(TWENTY));
    LayoutConstraintF layoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    EXPECT_EQ(algorithm->ResetLayoutConstraintMinWidth(layoutWrapper, layoutConstraint).selfIdealSize.width_, ONE);
}

/**
 * @tc.name: ResetLayoutConstraintMinWidth003
 * @tc.desc: Verify ResetLayoutConstraintMinWidth.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, ResetLayoutConstraintMinWidth003, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
        std::make_optional<CalcSize>(std::nullopt, CalcLength(TWENTY));
    LayoutConstraintF layoutConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    EXPECT_EQ(algorithm->ResetLayoutConstraintMinWidth(layoutWrapper, layoutConstraint).selfIdealSize.width_, ONE);
}

/**
 * @tc.name: UpdateSelectOverlayMenuMinWidth001
 * @tc.desc: Verify UpdateSelectOverlayMenuMinWidth.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateSelectOverlayMenuMinWidth001, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, "");
    ASSERT_NE(menuWrapperNode, nullptr);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    auto multiPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(multiPattern, nullptr);
    multiPattern->GetMainMenuPattern()->type_ = MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU;
    multiPattern->GetMenuWrapper()->GetPattern<MenuWrapperPattern>()->isSelectOverlaySubWindowWrapper_ = true;
    multiPattern->GetMenuWrapper()->GetPattern<MenuWrapperPattern>()->containerId_ = 1;
    MockContainer::SetUp();
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;
    pipelineContext->SetContainerModalButtonsRect(false);
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, MockContainer::Current());
    auto columnInfo = AceType::MakeRefPtr<GridColumnInfo>();
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    EXPECT_FALSE(algorithm->UpdateSelectOverlayMenuMinWidth(multiPattern, columnInfo));
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateSelectOverlayMenuMinWidth002
 * @tc.desc: Verify UpdateSelectOverlayMenuMinWidth.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateSelectOverlayMenuMinWidth002, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, "");
    ASSERT_NE(menuWrapperNode, nullptr);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    auto multiPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(multiPattern, nullptr);
    multiPattern->GetMainMenuPattern()->type_ = MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU;
    multiPattern->GetMenuWrapper()->GetPattern<MenuWrapperPattern>()->isSelectOverlaySubWindowWrapper_ = true;
    multiPattern->GetMenuWrapper()->GetPattern<MenuWrapperPattern>()->containerId_ = 1;
    MockContainer::SetUp();
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    pipelineContext->displayWindowRectInfo_.width_ = TWENTY;
    mockContainer->pipelineContext_ = pipelineContext;
    pipelineContext->SetContainerModalButtonsRect(false);
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, MockContainer::Current());
    auto columnInfo = AceType::MakeRefPtr<GridColumnInfo>();
    columnInfo->parent_ = AceType::MakeRefPtr<GridContainerInfo>();
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    EXPECT_TRUE(algorithm->UpdateSelectOverlayMenuMinWidth(multiPattern, columnInfo));
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateMenuDefaultConstraintByDevice001
 * @tc.desc: Verify UpdateMenuDefaultConstraintByDevice.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateMenuDefaultConstraintByDevice001, TestSize.Level1)
{
    InitMenuWrapperNode();
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode_->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(NODE_ID, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    float paddingWidth = FIVE;
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    bool idealSizeHasVal = true;
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateMenuDefaultConstraintByDevice(
        menuPattern, childConstraint, paddingWidth, layoutConstraint, idealSizeHasVal);
    EXPECT_EQ(layoutConstraint->selfIdealSize.width_, ZERO);
}

/**
 * @tc.name: UpdateMenuDefaultConstraintByDevice002
 * @tc.desc: Verify UpdateMenuDefaultConstraintByDevice.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateMenuDefaultConstraintByDevice002, TestSize.Level1)
{
    InitMenuWrapperNode();
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode_->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(NODE_ID, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    float paddingWidth = FIVE;
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    bool idealSizeHasVal = false;
    menuPattern->GetMainMenuPattern()->type_ = MenuType::CONTEXT_MENU;
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateMenuDefaultConstraintByDevice(
        menuPattern, childConstraint, paddingWidth, layoutConstraint, idealSizeHasVal);
    EXPECT_EQ(layoutConstraint->selfIdealSize.width_, TEN);
}

/**
 * @tc.name: UpdateMenuDefaultConstraintByDevice003
 * @tc.desc: Verify UpdateMenuDefaultConstraintByDevice.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateMenuDefaultConstraintByDevice003, TestSize.Level1)
{
    InitMenuWrapperNode();
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode_->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(NODE_ID, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    float paddingWidth = FIVE;
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    bool idealSizeHasVal = true;
    menuPattern->GetMainMenuPattern()->type_ = MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU;
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateMenuDefaultConstraintByDevice(
        menuPattern, childConstraint, paddingWidth, layoutConstraint, idealSizeHasVal);
    EXPECT_EQ(layoutConstraint->selfIdealSize.width_, ZERO);
}

/**
 * @tc.name: UpdateMenuDefaultConstraintByDevice004
 * @tc.desc: Verify UpdateMenuDefaultConstraintByDevice.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateMenuDefaultConstraintByDevice004, TestSize.Level1)
{
    InitMenuWrapperNode();
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode_->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(NODE_ID, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    LayoutConstraintF childConstraint = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
        .selfIdealSize = { ONE, FIVE },
    };
    float paddingWidth = FIVE;
    std::optional<LayoutConstraintF> layoutConstraint = std::make_optional<LayoutConstraintF>();
    layoutConstraint->minSize = SizeF { ONE, TWO };
    layoutConstraint->maxSize = SizeF { ONE_HUNDRED, TWO_HUNDRED };
    layoutConstraint->percentReference = SizeF { TEN, TWENTY };
    layoutConstraint->parentIdealSize = OptionalSize<float> { TEN, TWENTY };
    layoutConstraint->selfIdealSize = OptionalSize<float> { TEN, TWENTY };
    bool idealSizeHasVal = true;
    menuPattern->GetMainMenuPattern()->type_ = MenuType::SUB_MENU;
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    algorithm->UpdateMenuDefaultConstraintByDevice(
        menuPattern, childConstraint, paddingWidth, layoutConstraint, idealSizeHasVal);
    EXPECT_EQ(layoutConstraint->selfIdealSize.width_, TEN);
}

/**
 * @tc.name: SetHasCustomOutline001
 * @tc.desc: Verify SetHasCustomOutline.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, SetHasCustomOutline001, TestSize.Level1)
{
    InitMenuWrapperNode();
    MenuView menuView;
    MenuParam menuParam;
    BorderWidthProperty borderWidthPropertyOne = { 0.0_px, 0.0_px, 0.0_px, 0.0_px };
    BorderWidthProperty borderWidthPropertyTwo = { -1.0_px, 0.0_px, 0.0_px, 0.0_px };
    BorderWidthProperty borderWidthPropertyThree = { 0.0_px, -1.0_px, 0.0_px, 0.0_px };
    BorderWidthProperty borderWidthPropertyFour = { 0.0_px, 0.0_px, -1.0_px, 0.0_px };
    BorderWidthProperty borderWidthPropertyFive = { 0.0_px, 0.0_px, 0.0_px, -1.0_px };
    menuView.SetHasCustomOutline(menuWrapperNode_, menuFrameNode_, menuParam);
    auto menuWrapperPattern = menuWrapperNode_->GetPattern<MenuWrapperPattern>();
    EXPECT_FALSE(menuWrapperPattern->hasCustomOutlineWidth_);
    menuParam.outlineWidth = borderWidthPropertyOne;
    menuView.SetHasCustomOutline(menuWrapperNode_, menuFrameNode_, menuParam);
    EXPECT_TRUE(menuWrapperPattern->hasCustomOutlineWidth_);
    menuParam.outlineWidth = borderWidthPropertyTwo;
    menuView.SetHasCustomOutline(menuWrapperNode_, menuFrameNode_, menuParam);
    EXPECT_FALSE(menuWrapperPattern->hasCustomOutlineWidth_);
    menuParam.outlineWidth = borderWidthPropertyThree;
    menuView.SetHasCustomOutline(menuWrapperNode_, menuFrameNode_, menuParam);
    EXPECT_FALSE(menuWrapperPattern->hasCustomOutlineWidth_);
    menuParam.outlineWidth = borderWidthPropertyFour;
    menuView.SetHasCustomOutline(menuWrapperNode_, menuFrameNode_, menuParam);
    EXPECT_FALSE(menuWrapperPattern->hasCustomOutlineWidth_);
    menuParam.outlineWidth = borderWidthPropertyFive;
    menuView.SetHasCustomOutline(menuWrapperNode_, menuFrameNode_, menuParam);
    EXPECT_FALSE(menuWrapperPattern->hasCustomOutlineWidth_);
}

/**
 * @tc.name: UpdateMenuNodeByAnimation001
 * @tc.desc: Verify UpdateMenuNodeByAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateMenuNodeByAnimation001, TestSize.Level1)
{
    InitMenuWrapperNode();
    MenuView menuView;
    PreparedInfoForDrag data;
    menuView.UpdateMenuNodeByAnimation(menuFrameNode_, data);
    EXPECT_EQ(menuFrameNode_->GetRenderContext()->GetTransformScale()->x, 0.4f);
    EXPECT_EQ(menuFrameNode_->GetRenderContext()->GetTransformScale()->y, 0.4f);
}

/**
 * @tc.name: SetWordBreak001
 * @tc.desc: Test MenuView GetSetWordBreak is BREAK_WORD.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, SetWordBreak001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->menuWordBreak_ = WordBreak::BREAK_WORD;
    auto textProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textProperty->UpdateWordBreak(theme->GetWordBreak());
    EXPECT_EQ(textProperty->GetWordBreak(), WordBreak::BREAK_WORD);
}

/**
 * @tc.name: SetWordBreak002
 * @tc.desc: Test MenuView GetSetWordBreak is BREAK_ALL.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, SetWordBreak002, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->menuWordBreak_ = WordBreak::BREAK_ALL;
    auto textProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textProperty->UpdateWordBreak(theme->GetWordBreak());
    EXPECT_EQ(textProperty->GetWordBreak(), WordBreak::BREAK_ALL);
}

/**
 * @tc.name: UpdateMenuProperties001
 * @tc.desc: Verify UpdateMenuProperties function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateMenuProperties001, TestSize.Level1)
{
    MenuParam menuParam;
    menuParam.outlineWidth->SetBorderWidth(Dimension(10));
    menuParam.enableArrow = true;
    ASSERT_NE(wrapperNode_, nullptr);
    auto menuWrapperPattern = wrapperNode_->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetHasCustomOutlineWidth(true);
    MenuView::UpdateMenuProperties(wrapperNode_, menuFrameNode_, menuParam, MenuType::MENU);
    EXPECT_EQ(menuWrapperPattern->GetMenuParam().outlineWidth->leftDimen->ToString(), "10.00px");
}

/**
 * @tc.name: UpdateMenuMaskType001
 * @tc.desc: Verify UpdateMenuMaskType with UpdateMenuParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, UpdateMenuMaskType001, TestSize.Level1)
{
    MenuParam menuParam;
    menuParam.enableHoverMode = true;
    menuParam.maskEnable = true;
    menuParam.maskType = NG::MenuMaskType();
    menuParam.maskType->maskColor = Color::RED;
    menuParam.maskType->maskBackGroundBlueStyle = BlurStyle::REGULAR;
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapperNode, nullptr);

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(menuWrapperNode);

    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    auto filterRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(filterRenderContext, nullptr);
    columnNode->renderContext_ = filterRenderContext;

    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetMenuParam(menuParam);

    auto pipeline = MockPipelineContext::GetCurrent();
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->pipelineContext_ = pipeline;
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->SetFilterColumnNode(columnNode);
    menuWrapperPattern->SetFilterColumnNode(columnNode);

    MenuView::UpdateMenuParam(menuWrapperNode, menuNode, menuParam);

    EXPECT_EQ(filterRenderContext->GetBackgroundColorValue(), Color::RED);
    EXPECT_EQ(filterRenderContext->GetBackBlurStyle()->blurStyle, BlurStyle::REGULAR);
}
} // namespace OHOS::Ace::NG
