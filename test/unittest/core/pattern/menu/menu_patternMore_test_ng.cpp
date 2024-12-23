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
constexpr int32_t HALF = 2;
constexpr float TARGET_FONT = 25.0f;
constexpr MenuType TYPE = MenuType::MENU;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float TWO_HUNDRED = 200.0f;
constexpr float ONE_HUNDRED = 100.0f;
constexpr float FOUR_HUNDRED = 400.0f;
constexpr float SPACE = 8.0f;
constexpr float ORIGIN_SCALE = 1.0f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(5.f), Dimension(10), Dimension(20), Color(0x000000) };
} // namespace
class MenuPattern2TestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuPattern2TestNg();
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

void MenuPattern2TestNg::SetUpTestCase() {}

void MenuPattern2TestNg::TearDownTestCase() {}

void MenuPattern2TestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuPattern2TestNg::TearDown()
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

void MenuPattern2TestNg::InitMenuPattern2TestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuPattern2TestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuPattern2TestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuPattern2TestNg::GetPreviewMenuWrapper(
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

void CheckTestResult(RefPtr<MenuItemPattern> itemPattern)
{
    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), u"content");
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    EXPECT_EQ(textProperty->GetFontSize().value(), Dimension(TARGET_FONT));
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());
    EXPECT_EQ(textProperty->GetTextColor().value(), Color::RED);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
    ASSERT_TRUE(labelProperty->GetContent().has_value());
    EXPECT_EQ(labelProperty->GetContent().value(), u"label");
    ASSERT_TRUE(labelProperty->GetFontSize().has_value());
    EXPECT_EQ(labelProperty->GetFontSize().value(), Dimension(TARGET_FONT));
    ASSERT_TRUE(labelProperty->GetFontWeight().has_value());
    EXPECT_EQ(labelProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(labelProperty->GetTextColor().has_value());
    EXPECT_EQ(labelProperty->GetTextColor().value(), Color::RED);
}

/**
 * @tc.name: ModifyDivider
 * @tc.desc: test ModifyDivider and SetItemGroupDivider.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TestNg, ModifyDivider, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(TARGET_FONT));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);
    MneuModelInstance.SetItemDivider(ITEM_DIVIDER);
    MneuModelInstance.SetItemGroupDivider(ITEM_DIVIDER);  // add divider

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemGroupView::Create();
    auto groupNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    MenuItemGroupView::Create();
    auto groupNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<MenuItemGroupPattern>();

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(groupNode);

    groupPattern->ModifyDivider();
    itemNode->OnMountToParentDone();
    groupPattern->OnModifyDone();
    groupNode->MountToParent(menuNode);
    groupNode->OnMountToParentDone();
    groupNode2->MountToParent(menuNode);
    groupNode2->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();
    groupPattern->UpdateMenuItemIconInfo();
    CheckTestResult(itemPattern);
}

/**
 * @tc.name: GetPreviewMenuAnimationOffset
 * @tc.desc: Test GetPreviewMenuAnimationOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TestNg, GetPreviewMenuAnimationOffset, TestSize.Level1)
{
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto w = ONE_HUNDRED;
    auto h = TWO_HUNDRED;
    menuGeometryNode->SetFrameSize(SizeF(w, h));

    auto scale = ORIGIN_SCALE;
    auto size = SizeF(ONE_HUNDRED, ONE_HUNDRED);
    auto center = OffsetF(FOUR_HUNDRED, FOUR_HUNDRED);

    auto cx = center.GetX();
    auto cy = center.GetY();
    auto top = cy - size.Height() * scale / HALF;
    auto bottom = cy + size.Height() * scale / HALF;
    auto left = cx - size.Width() * scale / HALF;
    auto right = cx + size.Width() * scale / HALF;

    menuPattern->UpdateLastPlacement(Placement::TOP);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(cx - w / HALF, top - SPACE - h));

    menuPattern->UpdateLastPlacement(Placement::TOP_LEFT);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(left, top - SPACE - h));

    menuPattern->UpdateLastPlacement(Placement::TOP_RIGHT);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(right - w, top - SPACE - h));

    menuPattern->UpdateLastPlacement(Placement::BOTTOM);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(cx - w / HALF, bottom + SPACE));

    menuPattern->UpdateLastPlacement(Placement::BOTTOM_LEFT);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(left, bottom + SPACE));

    menuPattern->UpdateLastPlacement(Placement::BOTTOM_RIGHT);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(right - w, bottom + SPACE));

    menuPattern->UpdateLastPlacement(Placement::LEFT);
    EXPECT_EQ(
        menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(left - SPACE - w, cy - h / HALF));

    menuPattern->UpdateLastPlacement(Placement::LEFT_TOP);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(left - SPACE - w, top));

    menuPattern->UpdateLastPlacement(Placement::LEFT_BOTTOM);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(left - SPACE - w, bottom - h));

    menuPattern->UpdateLastPlacement(Placement::RIGHT);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(right + SPACE, cy - h / HALF));

    menuPattern->UpdateLastPlacement(Placement::RIGHT_TOP);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(right + SPACE, top));

    menuPattern->UpdateLastPlacement(Placement::RIGHT_BOTTOM);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(right + SPACE, bottom - h));

    menuPattern->UpdateLastPlacement(Placement::NONE);
    EXPECT_EQ(menuPattern->GetPreviewMenuAnimationOffset(center, size, scale), OffsetF(left, bottom + SPACE));
}

/**
 * @tc.name: InitPreviewMenuAnimationInfo
 * @tc.desc: Test InitPreviewMenuAnimationInfo.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TestNg, InitPreviewMenuAnimationInfo, TestSize.Level1)
{
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto pipeline = menuWrapperNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);

    auto menuNode = menuWrapperPattern->GetMenu();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);

    menuWrapperPattern->hasTransitionEffect_ = true;
    menuPattern->InitPreviewMenuAnimationInfo(menuTheme);
    EXPECT_EQ(menuPattern->disappearOffset_, menuPattern->endOffset_);

    menuPattern->previewMode_ = MenuPreviewMode::CUSTOM;
    menuPattern->isShowHoverImage_ = true;

    auto previewNode = menuWrapperPattern->GetPreview();
    ASSERT_NE(previewNode, nullptr);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(previewPattern, nullptr);
    previewPattern->hoverImageScaleFrom_ = ORIGIN_SCALE;
    menuPattern->InitPreviewMenuAnimationInfo(menuTheme);
    EXPECT_TRUE(menuPattern->disappearOffset_.NonNegative());

    menuPattern->previewMode_ = MenuPreviewMode::IMAGE;
    menuPattern->InitPreviewMenuAnimationInfo(menuTheme);
    EXPECT_TRUE(menuPattern->disappearOffset_.NonNegative());
}
} // namespace OHOS::Ace::NG
