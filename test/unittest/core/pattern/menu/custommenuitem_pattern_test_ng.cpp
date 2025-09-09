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
#include "test/mock/core/common/mock_container.h"
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
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/custom_menu_item_layout_algorithm.h"
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
const std::string MENU_TAG = "menu";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
} // namespace
class CustomMenuItemPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitCustomMenuItemPatternTestNg();
    void InitMenuItemTestNg();
    void MockPipelineContextGetTheme();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void CustomMenuItemPatternTestNg::SetUpTestCase() {}

void CustomMenuItemPatternTestNg::TearDownTestCase() {}

void CustomMenuItemPatternTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void CustomMenuItemPatternTestNg::MockPipelineContextGetTheme()
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

void CustomMenuItemPatternTestNg::TearDown()
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

void CustomMenuItemPatternTestNg::InitCustomMenuItemPatternTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void CustomMenuItemPatternTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* CustomMenuItemPatternTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> CustomMenuItemPatternTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: Create001
 * @tc.desc: Test CustomMenuItem creation
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, Create001, TestSize.Level1)
{
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(itemNode->GetEventHub<EventHub>());
    auto touch = itemNode->GetOrCreateGestureEventHub()->touchEventActuator_;
    ASSERT_TRUE(touch);
    ASSERT_FALSE(touch->touchEvents_.empty());
}

/**
 * @tc.name: OnTouch001
 * @tc.desc: Test CustomMenuItem OnTouch
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, OnTouch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);

    pattern->lastTouchOffset_ = nullptr;
    /**
     * @tc.steps: step2. execute OnTouch
     * @tc.expected: result as expected
     */
    // execute touch down event
    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset location(1, 1);
    locationInfo.SetTouchType(TouchType::DOWN);
    locationInfo.SetLocalLocation(location);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);

    info.touches_.pop_front();
    locationInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);

    pattern->lastTouchOffset_ = std::make_unique<Offset>(Offset(1, 0));
    info.touches_.pop_front();
    locationInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);

    info.touches_.pop_front();
    locationInfo.SetTouchType(TouchType::CANCEL);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: Test CustomMenuItem OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, OnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. execute OnKeyEvent
     * @tc.expected: result as expected
     */
    KeyEvent keyEvent(KeyCode::KEY_ESCAPE, KeyAction::DOWN);
    auto ret = pattern->OnKeyEvent(keyEvent);
    EXPECT_FALSE(ret);

    keyEvent.code = KeyCode::KEY_ENTER;
    ret = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(ret);

    keyEvent.action = KeyAction::UP;
    ret = pattern->OnKeyEvent(keyEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: MenuItemPatternTestBasicNg028
 * @tc.desc: Verify MenuItemModelNG::Create when version is 12.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, MenuItemPatternTestBasicNg028, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(itemNode->GetEventHub<EventHub>());
    auto touch = itemNode->GetOrCreateGestureEventHub()->touchEventActuator_;
    ASSERT_TRUE(touch);
    ASSERT_FALSE(touch->touchEvents_.empty());
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: RegisterAccessibilityChildActionNotify001
 * @tc.desc: Test callback function.
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, RegisterAccessibilityChildActionNotify001, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    /**
     * @tc.steps: step1. create outter menu and set show in subwindow true
     */
    auto outterMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, MENU_TAG, MenuType::MENU));
    ASSERT_NE(outterMenuNode, nullptr);
    auto outterMenuLayoutProps = outterMenuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(outterMenuLayoutProps, nullptr);
    outterMenuLayoutProps->UpdateShowInSubWindow(true);
    /**
     * @tc.steps: step2. create inner menu and set show in subwindow false
     */
    auto innerMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, MENU_TAG, MenuType::MENU));
    ASSERT_NE(innerMenuNode, nullptr);
    auto innerMenuLayoutProps = innerMenuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(innerMenuLayoutProps, nullptr);
    innerMenuLayoutProps->UpdateShowInSubWindow(false);
    innerMenuLayoutProps->UpdateExpandingMode(SubMenuExpandingMode::STACK);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4,
        AceType::MakeRefPtr<CustomMenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    menuItemNode->MountToParent(innerMenuNode);
    innerMenuNode->MountToParent(outterMenuNode);
    outterMenuNode->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->expandingMode_ = innerMenuLayoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    /**
     * @tc.steps: step3. call ShowSubMenu to create submenu
     * @tc.expected: expect subMenu's showInSubwindow param is true
     */
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->ShowSubMenu(ShowSubMenuType::LONG_PRESS);
    auto menuitemAccessibilityProperty = menuItemNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(menuitemAccessibilityProperty, nullptr);
    auto callback = menuitemAccessibilityProperty->GetNotifyChildActionFunc();
    ASSERT_NE(callback, nullptr);
    auto reuslt = callback(menuItemNode, NotifyChildActionType::ACTION_CLICK);
    EXPECT_EQ(reuslt, AccessibilityActionResult::ACTION_RISE);
}

/**
 * @tc.name: CustomMenuItemLayoutAlgorithmMeasure001
 * @tc.desc: Test CustomMenuItemLayoutAlgorithm Measure with different child layout policies
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, CustomMenuItemLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem and set the LayoutPolicyProperty to FIX_AT_IDEAL_SIZE.
     */
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, -1, menuItemPattern);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    layoutProp->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    layoutProp->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    LayoutConstraintF layoutConstraintF;
    layoutProp->UpdateLayoutConstraint(layoutConstraintF);
    layoutProp->UpdateContentConstraint();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItemNode, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Create a subcomponent of the Text type and Set FrameSize to (200, 100).
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SizeF(200.0f, 100.0f));
    auto childLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(childLayoutProperty, nullptr);

    LayoutConstraintF childLayoutConstraintF = {
        .selfIdealSize = { 200.f, 100.f },
    };

    /**
     * @tc.steps: step3. Add the Text component as a child of the menuitem component.
     */
    childLayoutProperty->UpdateLayoutConstraint(childLayoutConstraintF);
    childLayoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, childGeometryNode, childLayoutProperty);
    menuItemNode->AddChild(frameNode);
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Calling the algorithm calculates the size of the menuIten component.
     * @tc.expected: result as expected
     */
    auto algorithm = AceType::MakeRefPtr<CustomMenuItemLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    EXPECT_FLOAT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), 200.f);
    EXPECT_FLOAT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Height(), 100.f);
}

/**
 * @tc.name: CustomMenuItemLayoutAlgorithmMeasure002
 * @tc.desc: Test CustomMenuItemLayoutAlgorithm Measure
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, CustomMenuItemLayoutAlgorithmMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem and Set FrameSize to (200, 100).
     */
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, -1, menuItemPattern);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 100.0f));
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 0.f, 0.f },
        .maxSize = { 200.f, 100.f },
        .percentReference = { 200.f, 100.f },
        .parentIdealSize = { 200.f, 100.f },
        .selfIdealSize = { 200.f, 100.f }
    };
    layoutProp->UpdateLayoutConstraint(layoutConstraintF);
    layoutProp->UpdateContentConstraint();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItemNode, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Create a subcomponent of the Button type and set the LayoutPolicyProperty to MATCH_PARENT.
     */
    auto pattern = AceType::MakeRefPtr<ButtonPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(childGeometryNode, nullptr);
    LayoutConstraintF layoutConstraintF1 = {
        .minSize = { 0.f, 0.f },
        .maxSize = { 200.f, 100.f },
        .percentReference = { 200.f, 100.f },
        .parentIdealSize = { 200.f, 100.f },
    };
    auto childLayoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateLayoutConstraint(layoutConstraintF1);
    childLayoutProperty->UpdateContentConstraint();
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    /**
     * @tc.steps: step3. Add the Button component as a child of the menuitem component.
     */
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, childGeometryNode, childLayoutProperty);
    menuItemNode->AddChild(frameNode);
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Calling the algorithm calculates the size of the Button component.
     * @tc.expected: result as expected
     */
    auto algorithm = AceType::MakeRefPtr<CustomMenuItemLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.Measure(Referenced::RawPtr(childLayoutWrapper));
    EXPECT_FLOAT_EQ(childLayoutWrapper->GetGeometryNode()->GetFrameSize().Width(), 200.f);
    EXPECT_FLOAT_EQ(childLayoutWrapper->GetGeometryNode()->GetFrameSize().Height(), 100.f);
}

/**
 * @tc.name: CustomMenuItemLayoutAlgorithmMeasure003
 * @tc.desc: Test CustomMenuItemLayoutAlgorithm Measure with different child layout policies
 * @tc.type: FUNC
 */
HWTEST_F(CustomMenuItemPatternTestNg, CustomMenuItemLayoutAlgorithmMeasure003, TestSize.Level1)
{
    // create host FrameNode and Pattern; 100 means hostNode's id is 100
    auto hostNode = FrameNode::CreateFrameNode("custom_menu_item", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(hostNode, nullptr);
    // create LayoutProperty and LayoutWrapper
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    LayoutConstraintF layoutConstraintF;
    layoutProperty->UpdateLayoutConstraint(layoutConstraintF);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(hostNode, geometryNode, layoutProperty);

    // Mock Pattern : IsEnableChildrenMatchParent
    class MockPattern : public Pattern {
    public:
        bool enableMatchParent = false;
        bool IsEnableChildrenMatchParent() override { return enableMatchParent; }
    };
    auto mockPattern = AceType::MakeRefPtr<MockPattern>();
    hostNode->pattern_ = mockPattern;

    // create childNode1: layoutPolicy = NO_MATCH; 101 means childNode1's id is 101
    auto childNode1 = FrameNode::CreateFrameNode("child1", 101, AceType::MakeRefPtr<Pattern>());
    auto childLayoutProperty1 = AceType::MakeRefPtr<LayoutProperty>();
    childNode1->layoutProperty_ = childLayoutProperty1;
    auto childWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(childNode1,
        AceType::MakeRefPtr<GeometryNode>(), childLayoutProperty1);
    layoutWrapper.AppendChild(childWrapper1);

    // create childNode2: layoutPolicy = MATCH_PARENT; 102 means childNode2's id is 102
    auto childNode2 = FrameNode::CreateFrameNode("child2", 102, AceType::MakeRefPtr<Pattern>());
    auto childLayoutProperty2 = AceType::MakeRefPtr<LayoutProperty>();
    LayoutPolicyProperty policy2;
    policy2.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    policy2.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    childLayoutProperty2->layoutPolicy_ = policy2;
    childNode2->layoutProperty_ = childLayoutProperty2;
    auto childWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(childNode2,
        AceType::MakeRefPtr<GeometryNode>(), childLayoutProperty2);
    layoutWrapper.AppendChild(childWrapper2);

    // create CustomMenuItemLayoutAlgorithm
    auto layoutAlgorithm = AceType::MakeRefPtr<CustomMenuItemLayoutAlgorithm>();
    // 1. test enableMatchParent = false
    mockPattern->enableMatchParent = false;
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(std::isinf(layoutConstraintF.maxSize.Width()));
    EXPECT_FALSE(std::isinf(layoutConstraintF.maxSize.Height()));
    EXPECT_EQ(layoutAlgorithm->layoutPolicyChildren_.size(), 0);
}
} // namespace OHOS::Ace::NG
