/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_canvas.h"

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
#include "core/components/theme/icon_theme.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_TAG = "text";
} // namespace

class MenuItemPatternTransformTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
};

void MenuItemPatternTransformTestNg::SetUpTestCase() {}

void MenuItemPatternTransformTestNg::TearDownTestCase() {}

void MenuItemPatternTransformTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuItemPatternTransformTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    MockContainer::TearDown();
}

void MenuItemPatternTransformTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly([](ThemeType type, int32_t) -> RefPtr<Theme> {
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
 * @tc.name: UpdatePreviewPosition001
 * @tc.desc: Verify UpdatePreviewPosition with Placement::TOP to cover GetTransformCenter TOP branch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTransformTestNg, UpdatePreviewPosition001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    MockPipelineContextGetTheme();

    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto previewNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 6, AceType::MakeRefPtr<Pattern>());

    mainMenu->MountToParent(wrapperNode);
    previewNode->MountToParent(wrapperNode);
    menuItemNode->MountToParent(mainMenu);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->previewMode_ = MenuPreviewMode::IMAGE;
    menuPattern->lastPlacement_ = Placement::TOP;

    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->hasTransitionEffect_ = true;

    SizeF oldMenuSize(100.0f, 100.0f);
    SizeF menuSize(100.0f, 200.0f);
    menuItemPattern->UpdatePreviewPosition(oldMenuSize, menuSize);

    auto menuRenderContext = mainMenu->GetRenderContext();
    ASSERT_NE(menuRenderContext, nullptr);
    ASSERT_EQ(menuPattern->GetLastPlacement().value_or(Placement::NONE), Placement::TOP);
}

/**
 * @tc.name: UpdatePreviewPosition002
 * @tc.desc: Verify UpdatePreviewPosition with Placement::TOP_LEFT to cover GetTransformCenter TOP_LEFT branch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTransformTestNg, UpdatePreviewPosition002, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    MockPipelineContextGetTheme();

    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto previewNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 6, AceType::MakeRefPtr<Pattern>());

    mainMenu->MountToParent(wrapperNode);
    previewNode->MountToParent(wrapperNode);
    menuItemNode->MountToParent(mainMenu);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->previewMode_ = MenuPreviewMode::IMAGE;
    menuPattern->lastPlacement_ = Placement::TOP_LEFT;

    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->hasTransitionEffect_ = true;

    SizeF oldMenuSize(100.0f, 100.0f);
    SizeF menuSize(100.0f, 200.0f);
    menuItemPattern->UpdatePreviewPosition(oldMenuSize, menuSize);

    auto menuRenderContext = mainMenu->GetRenderContext();
    ASSERT_NE(menuRenderContext, nullptr);
    ASSERT_EQ(menuPattern->GetLastPlacement().value_or(Placement::NONE), Placement::TOP_LEFT);
}

/**
 * @tc.name: UpdatePreviewPosition003
 * @tc.desc: Verify UpdatePreviewPosition with Placement::TOP_RIGHT to cover GetTransformCenter TOP_RIGHT branch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTransformTestNg, UpdatePreviewPosition003, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    MockPipelineContextGetTheme();

    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto previewNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 6, AceType::MakeRefPtr<Pattern>());

    mainMenu->MountToParent(wrapperNode);
    previewNode->MountToParent(wrapperNode);
    menuItemNode->MountToParent(mainMenu);

    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->previewMode_ = MenuPreviewMode::IMAGE;
    menuPattern->lastPlacement_ = Placement::TOP_RIGHT;

    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->hasTransitionEffect_ = true;

    SizeF oldMenuSize(100.0f, 100.0f);
    SizeF menuSize(100.0f, 200.0f);
    menuItemPattern->UpdatePreviewPosition(oldMenuSize, menuSize);

    auto menuRenderContext = mainMenu->GetRenderContext();
    ASSERT_NE(menuRenderContext, nullptr);
    ASSERT_EQ(menuPattern->GetLastPlacement().value_or(Placement::NONE), Placement::TOP_RIGHT);
}
} // namespace OHOS::Ace::NG
