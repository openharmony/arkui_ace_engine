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

#include "base/memory/ace_type.h"
#include "test/mock/base/mock_pixel_map.h"
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
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
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

void MenuAccessibilityPropertyTestNg::SetUpTestCase() {}

void MenuAccessibilityPropertyTestNg::TearDownTestCase() {}

void MenuAccessibilityPropertyTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuAccessibilityPropertyTestNg::TearDown()
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

void MenuAccessibilityPropertyTestNg::MockPipelineContextGetTheme()
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

void MenuAccessibilityPropertyTestNg::InitMenuTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuAccessibilityPropertyTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuAccessibilityPropertyTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuAccessibilityPropertyTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: ActActionScroll001
 * @tc.desc: MenuAccessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAccessibilityPropertyTestNg, ActActionScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu, get menu frameNode and pattern, set callback function.
     * @tc.expected: FrameNode and pattern is not null, related function is called.
     */
    MenuModelNG model;
    model.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuAccessibilityProperty = frameNode->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty, nullptr);
    menuPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. When firstChild is null, call the callback function in menuAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step3. When firstChild is not null and firstChild tag is SCROLL_ETS_TAG, call the callback function in
     *                   menuAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->SetAxis(Axis::VERTICAL);
    scrollPattern->scrollableDistance_ = 1.0f;
    auto scroll =
        FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern);
    ASSERT_NE(scroll, nullptr);
    scroll->MountToParent(frameNode, 0);
    scroll->MarkModifyDone();
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step4. When firstChild is not null and firstChild tag is not SCROLL_ETS_TAG, call the callback
     *                   function in menuAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode, 0);
    textNode->MarkModifyDone();
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(menuAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: IsScrollable001
 * @tc.desc: Test menuAccessibilityProperty::IsScrollable
 * @tc.type: FUNC
 */
HWTEST_F(MenuAccessibilityPropertyTestNg, IsScrollable001, TestSize.Level1)
{
    InitMenuTestNg();
    EXPECT_FALSE(menuAccessibilityProperty_->IsScrollable());

    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->SetAxis(Axis::VERTICAL);
    scrollPattern->scrollableDistance_ = 1.0f;
    auto scroll =
        FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern);
    ASSERT_NE(scroll, nullptr);
    scroll->MountToParent(menuFrameNode_, 0);
    scroll->MarkModifyDone();
    EXPECT_TRUE(menuAccessibilityProperty_->IsScrollable());

    scrollPattern->SetAxis(Axis::NONE);
    EXPECT_FALSE(menuAccessibilityProperty_->IsScrollable());
    scrollPattern->scrollableDistance_ = 0.0f;
    EXPECT_FALSE(menuAccessibilityProperty_->IsScrollable());
    /**
     * @tc.steps: step1. Create Menu and test firstchild not SCROLL.
     */
    RefPtr<FrameNode> menuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuNode, nullptr);
    RefPtr<MenuAccessibilityProperty> menuAccessibility =
        menuNode->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibility, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(menuNode, 0);
    EXPECT_FALSE(menuAccessibility->IsScrollable());
}

/**
 * @tc.name: SetSpecificSupportAction001
 * @tc.desc: Test MenuAccessibilityProperty::SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(MenuAccessibilityPropertyTestNg, SetSpecificSupportAction001, TestSize.Level1)
{
    InitMenuTestNg();
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->SetAxis(Axis::VERTICAL);
    scrollPattern->scrollableDistance_ = 1.0f;
    scrollPattern->currentOffset_ = CURRENT_OFFSET;
    auto scroll =
        FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern);
    ASSERT_NE(scroll, nullptr);
    scroll->MountToParent(menuFrameNode_, 0);

    menuAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = menuAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
    /**
     * @tc.steps: step1. test IsAtTop and IsAtBottom.
     */
    scrollPattern->scrollableDistance_ = -1.0;
    scrollPattern->currentOffset_ = 0.0f;
    menuAccessibilityProperty_->SetSpecificSupportAction();
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(menuAccessibilityProperty_->supportActions_, expectActions);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    scrollPattern->SetAxis(Axis::NONE);
    scrollPattern->scrollableDistance_ = 0.0f;
    menuAccessibilityProperty_->SetSpecificSupportAction();
    EXPECT_EQ(menuAccessibilityProperty_->supportActions_, expectActions);
    /**
     * @tc.steps: step2. Create Menu and test firstchild not SCROLL.
     */
    RefPtr<FrameNode> menuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuNode, nullptr);
    RefPtr<MenuAccessibilityProperty> menuAccessibility =
        menuNode->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibility, nullptr);
    menuAccessibility->SetSpecificSupportAction();
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(menuNode, 0);
    menuAccessibility->SetSpecificSupportAction();
    EXPECT_EQ(menuAccessibility->supportActions_, (0));
}
} // namespace OHOS::Ace::NG
