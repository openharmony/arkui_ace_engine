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
const std::string TEXT_TAG = "text";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
constexpr MenuType TYPE = MenuType::MENU;
constexpr int32_t TARGET_ID = 3;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(5.f), Dimension(10), Dimension(20), Color(0x000000) };
} // namespace
class MenuItemPatternTestOneNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuItemPatternTestOneNg();
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

void MenuItemPatternTestOneNg::SetUpTestCase() {}

void MenuItemPatternTestOneNg::TearDownTestCase() {}

void MenuItemPatternTestOneNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuItemPatternTestOneNg::MockPipelineContextGetTheme()
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

void MenuItemPatternTestOneNg::TearDown()
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

void MenuItemPatternTestOneNg::InitMenuItemPatternTestOneNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuItemPatternTestOneNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuItemPatternTestOneNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuItemPatternTestOneNg::GetPreviewMenuWrapper(
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
    customGeometryNode->SetFrameSize(SizeF(100.0f, 100.0f));
    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    return menuWrapperNode;
}

/**
 * @tc.name: OnAfterModifyDone001
 * @tc.desc: Verify OnAfterModifyDone().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnAfterModifyDone001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->OnAfterModifyDone();

    auto host = menuItemPattern->GetHost();
    host->UpdateInspectorId("test");
    menuItemPattern->OnAfterModifyDone();
    ASSERT_NE(host->GetInspectorId().value_or("").empty(), true);
}

/**
 * @tc.name: RecordChangeEvent001
 * @tc.desc: Verify RecordChangeEvent().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, RecordChangeEvent001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    menuItemPattern->RecordChangeEvent();

    ASSERT_EQ(!Recorder::EventRecorder::Get().IsComponentRecordEnable(), false);
}

/**
 * @tc.name: UpdateSubmenuExpandingMode001
 * @tc.desc: Verify UpdateSubmenuExpandingMode().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, UpdateSubmenuExpandingMode001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<UINode> node = menuItemPattern->GetHost();
    node->tag_ = V2::MENU_ITEM_ETS_TAG;
    menuItemPattern->UpdateSubmenuExpandingMode(node);

    ASSERT_NE(node->GetTag() == V2::MENU_ETS_TAG, true);
}

/**
 * @tc.name: OnExpandChanged001
 * @tc.desc: Verify OnExpandChanged
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnExpandChanged001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->isExpanded_ = true;
    menuItemPattern->OnExpandChanged(frameNode);

    ASSERT_EQ(menuItemPattern->embeddedMenu_, nullptr);
}

/**
 * @tc.name: OnExpandChanged002
 * @tc.desc: Verify OnExpandChanged
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnExpandChanged002, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content2";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto menu = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, V2::MENU_TAG, MenuType::MENU));
    frameNode->MountToParent(menu);
    menuItemPattern->isExpanded_ = true;
    menuItemPattern->OnExpandChanged(frameNode);

    EXPECT_EQ(menuItemPattern->embeddedMenu_, nullptr);
}

/**
 * @tc.name: HideEmbeddedExpandMenu001
 * @tc.desc: Verify OnExpandChanged
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, HideEmbeddedExpandMenu001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content2";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto menu = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, V2::MENU_TAG, MenuType::MENU));

    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, V2::MENU_TAG, MenuType::SUB_MENU));
    subMenu->MountToParent(frameNode);
    frameNode->MountToParent(menu);
    menu->MountToParent(wrapperNode);

    menuItemPattern->HideEmbeddedExpandMenu(subMenu);
    auto childIndex = frameNode->GetChildIndex(subMenu);
    auto notFound = -1;
    EXPECT_EQ(childIndex, notFound);
}

/**
 * @tc.name: RegisterOnClick001
 * @tc.desc: Verify RegisterOnClick
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, RegisterOnClick001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->RegisterOnClick();

    menuItemPattern->clickableArea_ = frameNode;
    menuItemPattern->RegisterOnClick();

    auto clickableAreaGestureHub = menuItemPattern->clickableArea_->GetOrCreateGestureEventHub();
    ASSERT_NE(clickableAreaGestureHub, nullptr);
}

/**
 * @tc.name: RegisterOnTouch001
 * @tc.desc: Verify RegisterOnTouch
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, RegisterOnTouch001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->RegisterOnTouch();

    menuItemPattern->clickableArea_ = frameNode;
    menuItemPattern->RegisterOnTouch();

    auto clickableAreaGestureHub = menuItemPattern->clickableArea_->GetOrCreateGestureEventHub();
    ASSERT_NE(clickableAreaGestureHub, nullptr);
}

/**
 * @tc.name: RegisterOnHover001
 * @tc.desc: Verify RegisterOnHover
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, RegisterOnHover001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->RegisterOnHover();

    menuItemPattern->clickableArea_ = frameNode;
    menuItemPattern->RegisterOnHover();

    auto clickableAreaGestureHub = menuItemPattern->clickableArea_->GetOrCreateGestureEventHub();
    ASSERT_NE(clickableAreaGestureHub, nullptr);
}

/**
 * @tc.name: RegisterOnKeyEvent001
 * @tc.desc: Verify RegisterOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, RegisterOnKeyEvent001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->RegisterOnKeyEvent();

    menuItemPattern->clickableArea_ = frameNode;
    menuItemPattern->RegisterOnKeyEvent();

    auto clickableAreaGestureHub = menuItemPattern->clickableArea_->GetOrCreateGestureEventHub();
    ASSERT_NE(clickableAreaGestureHub, nullptr);
}

/**
 * @tc.name: OnTouch001
 * @tc.desc: Verify OnTouch
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnTouch001, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);

    TouchEventInfo itemTouchDownEventInfo(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo downLocationInfo(3);
    Offset touchDownGlobalLocation(1, 1);
    downLocationInfo.SetTouchType(TouchType::DOWN);
    auto touchDownLocationInfo = downLocationInfo.SetGlobalLocation(touchDownGlobalLocation);
    itemTouchDownEventInfo.touches_.emplace_back(touchDownLocationInfo);
    menuItemPattern->OnTouch(itemTouchDownEventInfo);
    EXPECT_EQ(itemTouchDownEventInfo.touches_.size(), 1);

    TouchEventInfo itemTouchDownEventInfo2(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo downLocationInfo2(3);
    downLocationInfo2.SetTouchType(TouchType::UP);
    auto touchDownLocationInfo2 = downLocationInfo2.SetGlobalLocation(touchDownGlobalLocation);
    itemTouchDownEventInfo2.touches_.emplace_back(touchDownLocationInfo2);
    menuItemPattern->OnTouch(itemTouchDownEventInfo2);

    TouchEventInfo itemTouchDownEventInfo3(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo downLocationInfo3(3);
    downLocationInfo3.SetTouchType(TouchType::MOVE);
    auto touchDownLocationInfo3 = downLocationInfo2.SetGlobalLocation(touchDownGlobalLocation);
    itemTouchDownEventInfo3.touches_.emplace_back(touchDownLocationInfo3);
    menuItemPattern->OnTouch(itemTouchDownEventInfo3);

    ASSERT_EQ(itemTouchDownEventInfo.GetTouches().front().GetTouchType(), TouchType::DOWN);
}

/**
 * @tc.name: HandleOnChange001
 * @tc.desc: Verify HandleOnChange
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, HandleOnChange001, TestSize.Level1)
{
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);

    pattern->HandleOnChange();
    EXPECT_TRUE(pattern->isSelected_);

    auto host = pattern->GetHost();
    auto hub = host->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(hub, nullptr);

    bool isSelected = true;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    hub->SetSelectedChangeEvent(changeEvent);
    hub->SetOnChange(changeEvent);

    pattern->HandleOnChange();
    EXPECT_FALSE(pattern->isSelected_);
}

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: Verify OnVisibleChange().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnVisibleChange001, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    menuItemNode->MountToParent(mainMenu);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto parentNode = menuItemPattern->GetHost()->GetParent();

    ASSERT_NE(parentNode, nullptr);
    parentNode->tag_ = V2::MENU_ITEM_GROUP_ETS_TAG;
    menuItemPattern->OnVisibleChange(false);
    ASSERT_EQ(parentNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG, true);
}

/**
 * @tc.name: AddClickableArea001
 * @tc.desc: Verify AddClickableArea().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, AddClickableArea001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);

    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = true;
    menuItemPattern->AddClickableArea();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = false;
    menuItemPattern->AddClickableArea();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = menuItemNode;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = true;
    menuItemPattern->AddClickableArea();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->clickableArea_ = menuItemNode;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = false;
    menuItemPattern->AddClickableArea();
    ASSERT_EQ(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE), true);
}

/**
 * @tc.name: AddClickableArea002
 * @tc.desc: Verify AddClickableArea().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, AddClickableArea002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);

    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->clickableArea_ = menuItemNode;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = true;
    menuItemPattern->AddClickableArea();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->clickableArea_ = menuItemNode;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = false;
    menuItemPattern->AddClickableArea();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = false;
    menuItemPattern->AddClickableArea();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->clickableArea_ = nullptr;
    menuItemPattern->GetMenuPattern()->isEmbedded_ = true;
    menuItemPattern->AddClickableArea();
    ASSERT_EQ(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE), true);
}

/**
 * @tc.name: UpdateImageIcon001
 * @tc.desc: Verify UpdateImageIcon().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, UpdateImageIcon001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->IsSubMenu();

    RefPtr<FrameNode> menuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });

    ImageSourceInfo imageSourceInfo;
    std::function<void(WeakPtr<NG::FrameNode>)> symbol = [](const WeakPtr<NG::FrameNode>& node) {};
    menuItemPattern->UpdateImageIcon(menuNode, menuNode, imageSourceInfo, symbol, true);

    ASSERT_NE(menuItemPattern->GetLayoutProperty<MenuItemLayoutProperty>(), nullptr);
}

/**
 * @tc.name: UpdateSymbolIcon001
 * @tc.desc: Verify UpdateSymbolIcon().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, UpdateSymbolIcon001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateText
    itemPattern->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>([](GestureEvent&) {});
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto labelNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(labelNode, nullptr);
    EXPECT_EQ(labelNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), u"label");

    ImageSourceInfo imageSourceInfo;
    std::function<void(WeakPtr<NG::FrameNode>)> symbol = [](const WeakPtr<NG::FrameNode>& node) {};
    itemPattern->UpdateSymbolIcon(labelNode, labelNode, imageSourceInfo, symbol, true);

    std::function<void(WeakPtr<NG::FrameNode>)> symbol1 = nullptr;
    itemPattern->UpdateSymbolIcon(labelNode, labelNode, imageSourceInfo, symbol1, true);

    ASSERT_EQ(labelNode->GetLayoutProperty<TextLayoutProperty>(), nullptr);
}

/**
 * @tc.name: UpdateImageNode001
 * @tc.desc: Verify UpdateImageNode().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, UpdateImageNode001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));

    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);

    auto itemProperty = menuItemPattern->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    itemProperty->SetSelectSymbol([](WeakPtr<NG::FrameNode>) {});
    itemProperty->UpdateSelectIconSrc("");
    RefPtr<FrameNode> row = wrapperNode;
    RefPtr<FrameNode> selectIcon = menuItemNode;
    auto symbol = itemProperty->GetSelectSymbol();
    menuItemPattern->UpdateImageNode(row, selectIcon);
    ASSERT_NE(symbol, nullptr);
}

/**
 * @tc.name: CloseMenu001
 * @tc.desc: Verify CloseMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, CloseMenu001, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);

    auto topLevelMenuPattern = menuItemPattern->GetMenuPattern(true);
    ASSERT_NE(topLevelMenuPattern, nullptr);
    topLevelMenuPattern->type_ = MenuType::SELECT_OVERLAY_EXTENSION_MENU;
    menuItemPattern->IsSubMenu();
    menuItemPattern->CloseMenu();

    ASSERT_EQ(menuItemPattern->IsSelectOverlayMenu(), true);
}

/**
 * @tc.name: UpdateText001
 * @tc.desc: Verify UpdateText().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, UpdateText001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));

    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);

    auto itemProperty = menuItemPattern->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    itemProperty->SetSelectSymbol([](WeakPtr<NG::FrameNode>) {});
    itemProperty->UpdateSelectIconSrc("");
    itemProperty->UpdateLabel("abc");
    itemProperty->UpdateLayoutDirection(TextDirection::RTL);
    RefPtr<FrameNode> row = wrapperNode;
    auto theme =
        PipelineBase::GetCurrentContext() ? PipelineBase::GetCurrentContext()->GetTheme<SelectTheme>() : nullptr;

    theme->menuItemContentAlign_ = static_cast<uint32_t>(TextAlign::LEFT);
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    menuItemPattern->UpdateText(row, layoutProp, true);

    theme->menuItemContentAlign_ = static_cast<uint32_t>(TextAlign::RIGHT);
    menuItemPattern->UpdateText(row, layoutProp, true);

    theme->menuItemContentAlign_ = static_cast<uint32_t>(TextAlign::START);
    menuItemPattern->UpdateText(row, layoutProp, true);

    theme->menuItemContentAlign_ = static_cast<uint32_t>(TextAlign::END);
    menuItemPattern->UpdateText(row, layoutProp, true);

    theme->menuItemContentAlign_ = static_cast<uint32_t>(TextAlign::CENTER);
    menuItemPattern->UpdateText(row, layoutProp, true);

    EXPECT_FALSE(itemProperty->GetLabelFontSize().has_value());
}

/**
 * @tc.name: MarkIsSelected001
 * @tc.desc: Verify MarkIsSelected().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, MarkIsSelected001, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    bool isSelected = true;
    menuItemPattern->isSelected_ = true;
    auto eventHub = menuItemPattern->GetEventHub<MenuItemEventHub>();
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    eventHub->SetOnChange(changeEvent);
    eventHub->SetSelectedChangeEvent(changeEvent);

    menuItemPattern->MarkIsSelected(false);

    auto host = menuItemPattern->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: ParseMenuRadius001
 * @tc.desc: Verify ParseMenuRadius().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, ParseMenuRadius001, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto outterMenuNode = menuItemPattern->GetMenu(true);
    auto focusMenuRenderContext = outterMenuNode->GetRenderContext();
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    focusMenuRenderContext->UpdateBackBlurStyle(styleOption);

    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    auto menuWrapperNode = menuItemPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    menuWrapperPattern->hasCustomRadius_ = true;
    MenuParam param;
    menuItemPattern->ParseMenuRadius(param);

    menuItemPattern->ModifyDivider();
    ASSERT_NE(outterMenuNode, nullptr);

    auto menuLayoutProp = outterMenuNode->GetLayoutProperty<MenuLayoutProperty>();
    BorderRadiusProperty borderRadius;
    menuLayoutProp->UpdateBorderRadius(borderRadius);
    menuItemPattern->ParseMenuRadius(param);

    ASSERT_EQ(menuLayoutProp->GetBorderRadius().has_value(), true);
}

/**
 * @tc.name: FindTouchedEmbeddedMenuItem001
 * @tc.desc: Verify FindTouchedEmbeddedMenuItem().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, FindTouchedEmbeddedMenuItem001, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    PointF position;
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->isExpanded_ = true;
    menuItemPattern->embeddedMenu_ = wrapperNode;

    menuItemPattern->embeddedMenu_->tag_ = V2::MENU_ETS_TAG;
    menuItemPattern->FindTouchedEmbeddedMenuItem(position);

    menuItemPattern->clickableArea_ = wrapperNode;
    menuItemPattern->FindTouchedEmbeddedMenuItem(position);
}

/**
 * @tc.name: ShowSubMenuHelper001
 * @tc.desc: Verify ShowSubMenuHelper().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, ShowSubMenuHelper001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto outterMenuNode = menuItemPattern->GetMenu(true);
    auto focusMenuRenderContext = outterMenuNode->GetRenderContext();
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    focusMenuRenderContext->UpdateBackBlurStyle(styleOption);

    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);

    auto menuWrapperNode = menuItemPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);

    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->ShowSubMenuHelper(subMenu);

    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    auto topLevelMenuPattern = menuItemPattern->GetMenuPattern(true);
    ASSERT_NE(topLevelMenuPattern, nullptr);
    topLevelMenuPattern->type_ = MenuType::SELECT_OVERLAY_EXTENSION_MENU;
    menuItemPattern->IsSubMenu();
    menuItemPattern->CloseMenu();

    ASSERT_EQ(menuItemPattern->IsSelectOverlayMenu(), true);
    menuItemPattern->ShowSubMenuHelper(subMenu);

    ASSERT_EQ(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE), true);
}

/**
 * @tc.name: OnTouch002
 * @tc.desc: Verify OnTouch
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnTouch002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);

    Offset touchDownGlobalLocation(1, 1);
    TouchEventInfo itemTouchDownEventInfo2(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo downLocationInfo2(3);
    downLocationInfo2.SetTouchType(TouchType::UP);
    auto touchDownLocationInfo2 = downLocationInfo2.SetGlobalLocation(touchDownGlobalLocation);
    itemTouchDownEventInfo2.touches_.emplace_back(touchDownLocationInfo2);

    pattern->lastTouchOffset_ = std::make_unique<Offset>(Offset(1, 1));

    pattern->OnTouch(itemTouchDownEventInfo2);

    ASSERT_EQ(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE), true);
}

/**
 * @tc.name: AddExpandIcon001
 * @tc.desc: Verify AddExpandIcon().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, AddExpandIcon001, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->expandIcon_ = nullptr;
    menuItemPattern->AddExpandIcon(subMenuParent);

    menuItemPattern->expandIcon_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    menuItemPattern->AddExpandIcon(subMenuParent);

    menuItemPattern->GetMenuPattern()->isEmbedded_ = false;
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    auto menuPattern = menuItemPattern->GetMenu()->GetPattern<MenuPattern>();
    menuPattern->isStackSubmenu_ = false;
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->AddExpandIcon(subMenuParent);

    ASSERT_TRUE(menuItemPattern->expandingMode_ == SubMenuExpandingMode::EMBEDDED ||
                menuItemPattern->expandingMode_ == SubMenuExpandingMode::STACK);
}

/**
 * @tc.name: ModifyDivider001
 * @tc.desc: Verify ModifyDivider.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, ModifyDivider001, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto menu = menuItemPattern->GetMenu(true);

    CHECK_NULL_VOID(menu);
    auto menuProperty = menu->GetLayoutProperty<MenuLayoutProperty>();
    menuProperty->UpdateItemDivider(ITEM_DIVIDER);
    menuItemPattern->ModifyDivider();
    ASSERT_TRUE(menuProperty->GetItemDivider().has_value());
}

/**
 * @tc.name: InitFocusPadding001
 * @tc.desc: Verify InitFocusPadding
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, InitFocusPadding001, TestSize.Level1)
{
    // mock theme
    MockContainer::Current()->SetApiTargetVersion(99);
    MockPipelineContextGetTheme();
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();

    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->InitFocusPadding();
    auto padding = menuItemPattern->focusPadding_.ConvertToPx();
    EXPECT_EQ(padding, selectTheme->GetOptionFocusedBoxPadding().ConvertToPx());
}

/**
 * @tc.name: InitFocusEvent001
 * @tc.desc: Verify HandleFocusEvent().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, InitFocusEvent001, TestSize.Level1)
{
    // mock theme
    MockContainer::Current()->SetApiTargetVersion(99);
    MockPipelineContextGetTheme();
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();

    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    /**
     * @tc.steps: step1. MenuItemPattern OnModifyDone
     * @tc.expected: Check the param value
     */
    itemPattern->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>([](GestureEvent&) {});
    itemPattern->isOptionPattern_ = false;
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto labelNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(labelNode, nullptr);
    EXPECT_EQ(labelNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), u"label");
    
    /**
     * @tc.steps: step2. MenuItemPattern HandleFocusEvent
     * @tc.expected: Check the param value
     */
    itemPattern->isTextFadeOut_ = true;
    selectTheme->menuItemFocusedShadowStyle_ = 2.0;
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(itemNode->GetRenderContext());
    EXPECT_CALL(*mockRenderContext, SetClipToBounds(itemPattern->focusPadding_ == 0.0_vp));
    itemPattern->InitFocusEvent();
    itemPattern->HandleFocusEvent();
    EXPECT_EQ(itemPattern->isFocused_, true);
    EXPECT_EQ(itemPattern->isFocusBGColorSet_, true);
    EXPECT_EQ(itemPattern->isFocusShadowSet_, true);
}

/**
 * @tc.name: InitFocusEvent002
 * @tc.desc: Verify HandleBlurEvent().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, InitFocusEvent002, TestSize.Level1)
{
    // mock theme
    MockContainer::Current()->SetApiTargetVersion(99);
    MockPipelineContextGetTheme();
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();

    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    /**
     * @tc.steps: step1. MenuItemPattern OnModifyDone
     * @tc.expected: Check the param value
     */
    itemPattern->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>([](GestureEvent&) {});
    itemPattern->isOptionPattern_ = false;
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto labelNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(labelNode, nullptr);
    EXPECT_EQ(labelNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), u"label");
    
    /**
     * @tc.steps: step2. MenuItemPattern HandleBlurEvent
     * @tc.expected: Check the param value
     */
    itemPattern->isHovered_ = false;
    itemPattern->isTextFadeOut_ = true;
    itemPattern->isFocusBGColorSet_ = true;
    itemPattern->isFocusShadowSet_ = true;
    selectTheme->menuItemFocusedShadowStyle_ = 2.0;
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(itemNode->GetRenderContext());
    EXPECT_CALL(*mockRenderContext, SetClipToBounds(true));
    itemPattern->InitFocusEvent();
    itemPattern->HandleBlurEvent();
    EXPECT_EQ(itemPattern->isFocused_, false);
    EXPECT_EQ(itemPattern->isFocusBGColorSet_, false);
    EXPECT_EQ(itemPattern->isFocusShadowSet_, false);
}

/**
 * @tc.name: InitFocusEvent003
 * @tc.desc: Verify OptionHandleFocusEvent().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, InitFocusEvent003, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->optionApplyFocusedStyle_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return textTheme;
        } else {
            return selectTheme;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    itemPattern->SetTextNode(textNode);
    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    itemPattern->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>([](GestureEvent&) {});
    itemPattern->isOptionPattern_ = true;
    itemPattern->OnModifyDone();
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto labelNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(labelNode, nullptr);
    auto textLayoutProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), u"label");
    itemPattern->InitFocusEvent();
    itemPattern->OptionHandleFocusEvent();
    itemPattern->SetFocusStyle();
    ASSERT_NE(itemPattern->selectTheme_, nullptr);
    EXPECT_EQ(itemPattern->selectTheme_->GetoptionApplyFocusedStyle(), true);
    EXPECT_EQ(itemPattern->isFocusShadowSet_, true);

    itemPattern->showDefaultSelectedIcon_ = true;
    itemPattern->SetFocusStyle();
    EXPECT_EQ(itemPattern->fontColor_.has_value(), false);
}

/**
 * @tc.name: CreateCheckMarkNode001
 * @tc.desc: Verify CreateCheckMarkNode().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, CreateCheckMarkNode001, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    auto endRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuItemRowPattern>());
    ASSERT_NE(endRow, nullptr);
    endRow->MountToParent(itemNode);

    auto checkMarkNode = itemPattern->CreateCheckMarkNode(endRow, endRow->GetChildren().size());
    ASSERT_NE(checkMarkNode, nullptr);

    itemPattern->checkMarkNode_ = checkMarkNode;

    itemPattern->UpdateCheckMarkColor(Color::BLACK);
    auto checkLayoutProperty = itemPattern->checkMarkNode_->GetLayoutProperty<TextLayoutProperty>();
    auto symbolColorList = checkLayoutProperty->GetSymbolColorList();
    EXPECT_EQ(symbolColorList.has_value(), true);
    EXPECT_EQ(symbolColorList.value().front(), Color::BLACK);

    itemPattern->SetCheckMarkVisibleType(VisibleType::INVISIBLE);
    auto checkMarkLayoutProps = itemPattern->checkMarkNode_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(checkMarkLayoutProps, nullptr);
    auto type = checkMarkLayoutProps->GetVisibility().value_or(VisibleType::VISIBLE);
    EXPECT_EQ(type, VisibleType::INVISIBLE);
}

/**
 * @tc.name: SetShowDefaultSelectedIcon001
 * @tc.desc: Verify SetShowDefaultSelectedIcon().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, SetShowDefaultSelectedIcon001, TestSize.Level1)
{
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetShowDefaultSelectedIcon(false);
    EXPECT_EQ(itemPattern->endRowNode_, nullptr);
    EXPECT_EQ(itemPattern->showDefaultSelectedIcon_, false);
    itemPattern->SetShowDefaultSelectedIcon(true);
    EXPECT_EQ(itemPattern->endRowNode_, nullptr);
    EXPECT_EQ(itemPattern->showDefaultSelectedIcon_, true);
    itemPattern->isOptionPattern_ = true;
    itemPattern->SetShowDefaultSelectedIcon(true);
    EXPECT_NE(itemPattern->endRowNode_, nullptr);
    itemPattern->isOptionPattern_ = false;
    itemPattern->showDefaultSelectedIcon_ = true;
    itemPattern->SetShowDefaultSelectedIcon(true);
    EXPECT_NE(itemPattern->endRowNode_, nullptr);
    itemPattern->isOptionPattern_ = true;
    itemPattern->SetShowDefaultSelectedIcon(true);
    EXPECT_NE(itemPattern->endRowNode_, nullptr);
    itemPattern->SetShowDefaultSelectedIcon(true);
    EXPECT_NE(itemPattern->endRowNode_, nullptr);
}

/**
 * @tc.name: ApplySelectedThemeStyles001
 * @tc.desc: Verify ApplySelectedThemeStyles().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, ApplySelectedThemeStyles001, TestSize.Level1)
{
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->ApplySelectedThemeStyles();
    EXPECT_EQ(itemPattern->bgColor_.has_value(), false);
}

/**
 * @tc.name: InitFocusEvent004
 * @tc.desc: Verify OptionHandleBlurEvent().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, InitFocusEvent004, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->optionApplyFocusedStyle_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return textTheme;
        } else {
            return selectTheme;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    itemPattern->SetTextNode(textNode);
    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    itemPattern->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>([](GestureEvent&) {});
    itemPattern->isOptionPattern_ = true;
    itemPattern->OnModifyDone();
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto labelNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(labelNode, nullptr);
    auto textLayoutProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), u"label");
    itemPattern->InitFocusEvent();
    itemPattern->OptionHandleBlurEvent();
    itemPattern->ClearFocusStyle();
    ASSERT_NE(itemPattern->selectTheme_, nullptr);
    EXPECT_EQ(itemPattern->selectTheme_->GetoptionApplyFocusedStyle(), true);
    EXPECT_EQ(itemPattern->isFocusShadowSet_, false);
}

/**
 * @tc.name: GetSubMenu001
 * @tc.desc: Verify GetSubMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, GetSubMenu001, TestSize.Level1)
{
    auto jsViewNode = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode, nullptr);
    auto jsViewNode1 = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode1, nullptr);
    jsViewNode1->MountToParent(jsViewNode);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto node = AceType::DynamicCast<UINode>(jsViewNode);
    ASSERT_EQ(menuItemPattern->GetSubMenu(node), nullptr);
}

/**
 * @tc.name: GetSubMenu002
 * @tc.desc: Verify GetSubMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, GetSubMenu002, TestSize.Level1)
{
    auto jsViewNode = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode, nullptr);
    RefPtr<FrameNode> outerMenuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(outerMenuNode, nullptr);
    outerMenuNode->MountToParent(jsViewNode);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto node = AceType::DynamicCast<UINode>(jsViewNode);
    ASSERT_EQ(menuItemPattern->GetSubMenu(node), outerMenuNode);
}

/**
 * @tc.name: GetSubMenu003
 * @tc.desc: Verify GetSubMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, GetSubMenu003, TestSize.Level1)
{
    auto jsViewNode = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode, nullptr);
    auto jsViewNode1 = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode1, nullptr);
    jsViewNode1->MountToParent(jsViewNode);
    RefPtr<FrameNode> outerMenuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(outerMenuNode, nullptr);
    outerMenuNode->MountToParent(jsViewNode1);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto node = AceType::DynamicCast<UINode>(jsViewNode);
    ASSERT_EQ(menuItemPattern->GetSubMenu(node), outerMenuNode);
}

/**
 * @tc.name: GetSubMenu004
 * @tc.desc: Verify GetSubMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, GetSubMenu004, TestSize.Level1)
{
    auto jsViewNode = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode, nullptr);
    auto jsViewNode1 = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode1, nullptr);
    jsViewNode1->MountToParent(jsViewNode);
    auto jsViewNode2 = FrameNode::CreateFrameNode(
        V2::JS_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(jsViewNode2, nullptr);
    jsViewNode2->MountToParent(jsViewNode1);

    auto menuItemNode =
        FrameNode::CreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto node = AceType::DynamicCast<UINode>(jsViewNode);
    ASSERT_EQ(menuItemPattern->GetSubMenu(node), nullptr);
}

/**
 * @tc.name: ISNeedAddExpandIcon001
 * @tc.desc: Verify ISNeedAddExpandIcon().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, ISNeedAddExpandIcon001, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemPattern>());
    auto leftRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 4, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 5, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto expandIcon = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 6, AceType::MakeRefPtr<ImagePattern>());
    leftRow->MountToParent(menuItemNode);
    rightRow->MountToParent(menuItemNode);
    menuItemNode->MountToParent(menuNode);
    menuNode->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    menuItemPattern->isStackSubmenuHeader_ = true;
    EXPECT_TRUE(menuItemPattern->ISNeedAddExpandIcon(rightRow));

    menuItemPattern->isStackSubmenuHeader_ = false;
    EXPECT_FALSE(menuItemPattern->ISNeedAddExpandIcon(rightRow));

    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->isEmbedded_ = false;
    menuPattern->isStackSubmenu_ = false;
    EXPECT_TRUE(menuItemPattern->ISNeedAddExpandIcon(rightRow));
}

/**
 * @tc.name: AddExpandIcon002
 * @tc.desc: Verify AddExpandIcon().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, AddExpandIcon002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemPattern>());
    auto leftRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 4, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 5, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    leftRow->MountToParent(menuItemNode);
    rightRow->MountToParent(menuItemNode);
    menuItemNode->MountToParent(menuNode);
    menuNode->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->isEmbedded_ = false;
    menuPattern->isStackSubmenu_ = false;
    auto pipeline = menuItemNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto menuTheme = pipeline->GetTheme<MenuTheme>();
    ASSERT_NE(menuTheme, nullptr);

    menuItemPattern->AddExpandIcon(rightRow);
    EXPECT_NE(menuItemPattern->expandIcon_, nullptr);
    auto props = menuItemPattern->expandIcon_->GetLayoutProperty<TextLayoutProperty>();
    auto symbolSourceInfo = props->GetSymbolSourceInfo();
    EXPECT_TRUE(symbolSourceInfo.has_value());
    EXPECT_EQ(symbolSourceInfo.value().GetUnicode(), menuTheme->GetEmbeddedExpandIconId());
    EXPECT_EQ(menuItemPattern->expandIcon_->GetTag(), V2::SYMBOL_ETS_TAG);
    EXPECT_EQ(rightRow->GetChildren().size(), 1);

    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->AddExpandIcon(rightRow);
    EXPECT_NE(menuItemPattern->expandIcon_, nullptr);
    props = menuItemPattern->expandIcon_->GetLayoutProperty<TextLayoutProperty>();
    symbolSourceInfo = props->GetSymbolSourceInfo();
    EXPECT_TRUE(symbolSourceInfo.has_value());
    EXPECT_EQ(symbolSourceInfo.value().GetUnicode(), menuTheme->GetStackExpandIconId());
    EXPECT_EQ(menuItemPattern->expandIcon_->GetTag(), V2::SYMBOL_ETS_TAG);
}

/**
 * @tc.name: AddExpandIcon003
 * @tc.desc: Verify AddExpandIcon().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, AddExpandIcon003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemPattern>());
    auto leftRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 4, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 5, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    leftRow->MountToParent(menuItemNode);
    rightRow->MountToParent(menuItemNode);
    menuItemNode->MountToParent(menuNode);
    menuNode->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->isEmbedded_ = false;
    menuPattern->isStackSubmenu_ = false;
    auto pipeline = menuItemNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto menuTheme = pipeline->GetTheme<MenuTheme>();
    ASSERT_NE(menuTheme, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->SetExpandSymbol([](WeakPtr<NG::FrameNode> weakPtr) {});

    menuItemPattern->AddExpandIcon(rightRow);
    EXPECT_NE(menuItemPattern->expandIcon_, nullptr);
    auto props = menuItemPattern->expandIcon_->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(props, nullptr);
    auto symbolSourceInfo = props->GetSymbolSourceInfo();
    EXPECT_FALSE(symbolSourceInfo.has_value());
    EXPECT_EQ(menuItemPattern->expandIcon_->GetTag(), V2::SYMBOL_ETS_TAG);
}

/**
 * @tc.name: AddStackSubMenuHeader001
 * @tc.desc: Verify AddStackSubMenuHeader().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, AddStackSubMenuHeader001, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menuNode);
    menuNode->MountToParent(wrapperNode);
    auto menuStackNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->SetExpandSymbol([](WeakPtr<NG::FrameNode> weakPtr) {});

    menuItemPattern->AddStackSubMenuHeader(menuStackNode);
    auto menuStackProperty = menuStackNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuStackProperty);
    EXPECT_NE(menuStackProperty->GetExpandSymbol(), nullptr);
}

/**
 * @tc.name: ShowSubMenu001
 * @tc.desc: Verify ShowSubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, ShowSubMenu001, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->ShowSubMenu();

    auto parentMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(parentMenuPattern, nullptr);
    ASSERT_EQ(parentMenuPattern->GetSubMenuDepth(), 0);

    auto showedSubMenu = parentMenuPattern->GetShowedSubMenu();
    ASSERT_NE(showedSubMenu, nullptr);

    auto subMenuPattern = showedSubMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    ASSERT_EQ(subMenuPattern->GetSubMenuDepth(), 1);
}

/**
 * @tc.name: OnHover001
 * @tc.desc: Verify OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnHover001, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->OnHover(true);

    auto menuWrapper = menuItemPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    ASSERT_EQ(menuWrapper->GetChildren().size(), 1);
}

/**
 * @tc.name: OnHover002
 * @tc.desc: Verify OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnHover002, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto dummySubMenu = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, 3, AceType::MakeRefPtr<TextPattern>());
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    dummySubMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetSubMenuDepth(1);
    subMenuPattern->SetParentMenuItem(menuItemNode);
    
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->OnHover(true);

    auto menuWrapper = menuItemPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    ASSERT_EQ(menuWrapper->GetChildren().size(), 3);
}

/**
 * @tc.name: OnHover003
 * @tc.desc: Verify OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnHover003, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto dummySubMenu = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, 3, AceType::MakeRefPtr<TextPattern>());
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    dummySubMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetSubMenuDepth(1);
    auto tmpItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    subMenuPattern->SetParentMenuItem(tmpItemNode);
    
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->OnHover(true);

    auto menuWrapper = menuItemPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    ASSERT_EQ(menuWrapper->GetChildren().size(), 2);
}

/**
 * @tc.name: OnHover004
 * @tc.desc: Verify OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnHover004, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetSubMenuDepth(1);
    subMenuPattern->SetParentMenuItem(menuItemNode);
    
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->hideTask_.Reset([] {
    });
    menuItemPattern->OnHover(true);

    auto menuWrapper = menuItemPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    ASSERT_EQ(menuWrapper->GetChildren().size(), 2);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate() g_isConfigChangePerform = true.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps1: Set up theme manager mock
     * @tc.expected: Theme manager returns select theme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        return selectTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps2: Create frame nodes and patterns
     * @tc.expected: Nodes and patterns created and mounted
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto itemProperty = menuItemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps3: Create content and label nodes
     * @tc.expected: Nodes assigned to menu item pattern
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto labelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    menuItemPattern->content_ = contentNode;
    menuItemPattern->label_ = labelNode;

    /**
     * @tc.steps4: Get menu node and properties
     * @tc.expected: Menu node and properties obtained
     */
    auto menuNode = menuItemPattern->GetMenu();
    ASSERT_NE(menuNode, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    /**
     * @tc.steps5: Enable config change and set theme colors
     * @tc.expected: Config change is enabled
     */
    g_isConfigChangePerform = true;
    ASSERT_NE(SystemProperties::ConfigChangePerform(), false);
    Color menuFontColor = Color::RED;
    Color secondaryFontColor = Color::BLUE;
    selectTheme->menuFontColor_ = menuFontColor;
    selectTheme->secondaryFontColor_ = secondaryFontColor;

    /**
     * @tc.steps6: Call OnColorConfigurationUpdate and verify results
     * @tc.expected: Text colors updated to theme values
     */
    menuItemPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(itemProperty->GetLabelFontColor().value(), secondaryFontColor);
    EXPECT_EQ(itemProperty->GetFontColor().has_value(), false);
    EXPECT_EQ(menuProperty->GetFontColor().has_value(), false);
    auto textProperty = menuItemPattern->content_->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textProperty->GetTextColor().value(), menuFontColor);
}

/**
 * @tc.name: OnColorConfigurationUpdate002
 * @tc.desc: Test OnColorConfigurationUpdate() g_isConfigChangePerform = false.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnColorConfigurationUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps1: Set up theme manager mock
     * @tc.expected: Theme manager returns select theme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        return selectTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps2: Create frame nodes and patterns
     * @tc.expected: Nodes and patterns created and mounted
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto itemProperty = menuItemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps3: Create content and label nodes
     * @tc.expected: Nodes assigned to menu item pattern
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto labelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    menuItemPattern->content_ = contentNode;
    menuItemPattern->label_ = labelNode;

    /**
     * @tc.steps4: Get menu node and properties
     * @tc.expected: Menu node and properties obtained
     */
    auto menuNode = menuItemPattern->GetMenu();
    ASSERT_NE(menuNode, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    /**
     * @tc.steps5: Disable config change and set theme colors
     * @tc.expected: Config change is disabled
     */
    g_isConfigChangePerform = false;
    EXPECT_EQ(SystemProperties::ConfigChangePerform(), false);
    Color menuFontColor = Color::RED;
    Color secondaryFontColor = Color::BLUE;
    selectTheme->menuFontColor_ = menuFontColor;
    selectTheme->secondaryFontColor_ = secondaryFontColor;

    /**
     * @tc.steps6: Call OnColorConfigurationUpdate and verify results
     * @tc.expected: Text colors not updated
     */
    menuItemPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(itemProperty->GetLabelFontColor().has_value(), false);
    EXPECT_EQ(itemProperty->GetFontColor().has_value(), false);
    EXPECT_EQ(menuProperty->GetFontColor().has_value(), false);
    auto textProperty = menuItemPattern->content_->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textProperty->GetTextColor().has_value(), false);
}

/**
 * @tc.name: OnColorConfigurationUpdate003
 * @tc.desc: Test OnColorConfigurationUpdate() label_ = nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnColorConfigurationUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps1: Set up theme manager mock
     * @tc.expected: Theme manager returns select theme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        return selectTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps2: Create frame nodes and patterns
     * @tc.expected: Nodes and patterns created and mounted
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto itemProperty = menuItemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps3: Create content node (label is nullptr)
     * @tc.expected: Content node assigned, label remains nullptr
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    menuItemPattern->content_ = contentNode;

    /**
     * @tc.steps4: Get menu node and properties
     * @tc.expected: Menu node and properties obtained
     */
    auto menuNode = menuItemPattern->GetMenu();
    ASSERT_NE(menuNode, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    /**
     * @tc.steps5: Enable config change and set theme colors
     * @tc.expected: Config change is enabled
     */
    g_isConfigChangePerform = true;
    ASSERT_NE(SystemProperties::ConfigChangePerform(), false);
    Color menuFontColor = Color::RED;
    Color secondaryFontColor = Color::BLUE;
    selectTheme->menuFontColor_ = menuFontColor;
    selectTheme->secondaryFontColor_ = secondaryFontColor;

    /**
     * @tc.steps6: Call OnColorConfigurationUpdate and verify results
     * @tc.expected: Label color not updated, content color updated
     */
    menuItemPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(itemProperty->GetLabelFontColor().has_value(), false);
    EXPECT_EQ(itemProperty->GetFontColor().has_value(), false);
    EXPECT_EQ(menuProperty->GetFontColor().has_value(), false);
    auto textProperty = menuItemPattern->content_->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textProperty->GetTextColor().value(), menuFontColor);
}

/**
 * @tc.name: OnColorConfigurationUpdate004
 * @tc.desc: Test OnColorConfigurationUpdate() content_ = nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, OnColorConfigurationUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps1: Set up theme manager mock
     * @tc.expected: Theme manager returns select theme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        return selectTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps2: Create frame nodes and patterns
     * @tc.expected: Nodes and patterns created and mounted
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto itemProperty = menuItemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps3: Create label node (content is nullptr)
     * @tc.expected: Label node assigned, content remains nullptr
     */
    auto labelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    menuItemPattern->label_ = labelNode;

    /**
     * @tc.steps4: Get menu node and properties
     * @tc.expected: Menu node and properties obtained
     */
    auto menuNode = menuItemPattern->GetMenu();
    ASSERT_NE(menuNode, nullptr);
    auto menuProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    /**
     * @tc.steps5: Enable config change and set theme colors
     * @tc.expected: Config change is enabled
     */
    g_isConfigChangePerform = true;
    ASSERT_NE(SystemProperties::ConfigChangePerform(), false);
    Color menuFontColor = Color::RED;
    Color secondaryFontColor = Color::BLUE;
    selectTheme->menuFontColor_ = menuFontColor;
    selectTheme->secondaryFontColor_ = secondaryFontColor;

    /**
     * @tc.steps6: Call OnColorConfigurationUpdate and verify results
     * @tc.expected: Content color not updated, label color updated
     */
    menuItemPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(itemProperty->GetLabelFontColor().value(), secondaryFontColor);
    EXPECT_EQ(itemProperty->GetFontColor().has_value(), false);
    EXPECT_EQ(menuProperty->GetFontColor().has_value(), false);
    auto textProperty =
        menuItemPattern->content_ ? menuItemPattern->content_->GetLayoutProperty<TextLayoutProperty>() : nullptr;
    EXPECT_EQ(textProperty, nullptr);
}

/**
 * @tc.name: UpdateTextOverflow001
 * @tc.desc: Verify UpdateTextOverflow().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestOneNg, UpdateTextOverflow001, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);

    auto theme =
        PipelineBase::GetCurrentContext() ? PipelineBase::GetCurrentContext()->GetTheme<SelectTheme>() : nullptr;
    ASSERT_NE(theme, nullptr);
    theme = nullptr;
    MockContainer::Current()->SetApiTargetVersion(99);
    menuItemPattern->UpdateTextOverflow(textProperty, theme);
    EXPECT_EQ(textProperty->GetMaxLines(), 1);

    MockContainer::Current()->SetApiTargetVersion(10);
    menuItemPattern->UpdateTextOverflow(textProperty, theme);
    EXPECT_EQ(textProperty->GetMaxLines(), 1);

    theme =
        PipelineBase::GetCurrentContext() ? PipelineBase::GetCurrentContext()->GetTheme<SelectTheme>() : nullptr;
    ASSERT_NE(theme, nullptr);
    MockContainer::Current()->SetApiTargetVersion(99);
    theme->expandDisplay_ = true;
    menuItemPattern->UpdateTextOverflow(textProperty, theme);
    EXPECT_EQ(textProperty->GetMaxLines(), 1);
    EXPECT_EQ(textProperty->GetTextOverflow(), TextOverflow::ELLIPSIS);
}
} // namespace OHOS::Ace::NG
