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

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/animation/mock_animation_manager.h"
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
const std::string TEXT_TAG = "text";
constexpr MenuType TYPE = MenuType::MENU;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float TWO_HUNDRED = 200.0f;
constexpr float ONE_HUNDRED = 100.0f;
constexpr float FOUR_HUNDRED = 400.0f;
constexpr float SPACE = 8.0f;
constexpr float ORIGIN_SCALE = 1.0f;
constexpr float SCALE_ANIMATION_FIRST = 0.8f;
constexpr float SCALE_ANIMATION_SECOND = 1.0f;
constexpr double VELOCITY = 0.0f;
constexpr double MASS = 1.0f;
constexpr double STIFFNESS = 228.0f;
constexpr double DAMPING = 22.0f;
constexpr double DIP_SCALE = 1.5;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float MENU_OFFSET_X = 10.0f;
constexpr float MENU_OFFSET_Y = 10.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
} // namespace
class MenuAnimationTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuAnimationTestNg();
    void InitMenuItemTestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> GetImagePreviewMenuWrapper(
        std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuAnimationTestNg::SetUpTestCase() {}

void MenuAnimationTestNg::TearDownTestCase() {}

void MenuAnimationTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuAnimationTestNg::TearDown()
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

void MenuAnimationTestNg::InitMenuAnimationTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuAnimationTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuAnimationTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuAnimationTestNg::GetPreviewMenuWrapper(
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

RefPtr<FrameNode> MenuAnimationTestNg::GetImagePreviewMenuWrapper(
    std::optional<MenuPreviewAnimationOptions> scaleOptions)
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
 * @tc.name: GetPreviewMenuAnimationOffset001
 * @tc.desc: Test GetPreviewMenuAnimationOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, GetPreviewMenuAnimationOffset001, TestSize.Level1)
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
 * @tc.name: InitPreviewMenuAnimationInfo001
 * @tc.desc: Test InitPreviewMenuAnimationInfo.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, InitPreviewMenuAnimationInfo001, TestSize.Level1)
{
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto pipeline = menuWrapperNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = AceType::MakeRefPtr<MenuTheme>();
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

/**
 * @tc.name: InitPreviewMenuAnimationInfo002
 * @tc.desc: Test InitPreviewMenuAnimationInfo.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, InitPreviewMenuAnimationInfo002, TestSize.Level1)
{
    auto menuWrapperNode = GetImagePreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    auto pipeline = menuWrapperNode->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto menuTheme = AceType::MakeRefPtr<MenuTheme>();
    ASSERT_NE(menuTheme, nullptr);

    auto menuNode = menuWrapperPattern->GetMenu();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);

    menuWrapperPattern->hasTransitionEffect_ = false;
    menuPattern->isShowHoverImage_ = true;
    menuPattern->previewMode_ = MenuPreviewMode::IMAGE;
    menuPattern->InitPreviewMenuAnimationInfo(menuTheme);
    EXPECT_EQ(menuPattern->disappearOffset_, menuPattern->endOffset_);
}

/**
 * @tc.name: CheckAndShowAnimation001
 * @tc.desc: test MenuWrapperPattern::CheckAndShowAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, CheckAndShowAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));

    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step2. execute CheckAndShowAnimation
     * @tc.expected: property is set as expected
     */
    wrapperPattern->isFirstShow_ = false;
    wrapperPattern->CheckAndShowAnimation();
    wrapperPattern->isFirstShow_ = true;
    EXPECT_TRUE(wrapperPattern->isFirstShow_);
    wrapperPattern->CheckAndShowAnimation();
    EXPECT_FALSE(wrapperPattern->isFirstShow_);
}

/**
 * @tc.name: CheckAndShowAnimation002
 * @tc.desc: test MenuWrapperPattern::CheckAndShowAnimation function with duration.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, CheckAndShowAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    auto geometryNode = mainMenu->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    mainMenu->MountToParent(wrapperNode);
    auto menuItem = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItem, nullptr);
    menuItem->MountToParent(mainMenu);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    /**
     * @tc.steps: step2. execute CheckAndShowAnimation with duration
     * @tc.expected: property is set as expected
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->menuAnimationDuration_ = 100;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    wrapperPattern->CheckAndShowAnimation();
    EXPECT_FALSE(wrapperPattern->isFirstShow_);
    auto context = wrapperNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    ASSERT_NE(context->GetTransformCenter(), std::nullopt);
    EXPECT_EQ(context->GetTransformCenter()->GetX().Value(), MENU_OFFSET_X);
    EXPECT_EQ(context->GetTransformCenter()->GetY().Value(), MENU_OFFSET_Y);
    EXPECT_EQ(wrapperPattern->GetMenuStatus(), MenuStatus::INIT);
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    menuItemPattern->OnClick();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(wrapperPattern->GetMenuStatus(), MenuStatus::ON_HIDE_ANIMATION);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::Enable(false);
    EXPECT_TRUE(menuItemPattern->IsSelected());
}

/**
 * @tc.name: GetAnimationOffset001
 * @tc.desc: test MenuWrapperPattern::GetAnimationOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, GetAnimationOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));

    auto prop = AceType::MakeRefPtr<MenuLayoutProperty>();
    mainMenu->SetLayoutProperty(prop);
    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step2. execute GetAnimationOffset
     * @tc.expected: property is set as expected
     */
    wrapperPattern->menuPlacement_ = Placement::LEFT;
    wrapperPattern->GetAnimationOffset();
    EXPECT_EQ(wrapperPattern->menuPlacement_, Placement::LEFT);
    wrapperPattern->menuPlacement_ = Placement::RIGHT;
    wrapperPattern->GetAnimationOffset();
    EXPECT_EQ(wrapperPattern->menuPlacement_, Placement::RIGHT);
    wrapperPattern->menuPlacement_ = Placement::TOP;
    wrapperPattern->GetAnimationOffset();
    EXPECT_EQ(wrapperPattern->menuPlacement_, Placement::TOP);
}

/**
 * @tc.name: ShowMenuDisappearAnimation001
 * @tc.desc: Test ShowMenuDisappearAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, ShowMenuDisappearAnimation001, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    std::cout << "before MockContainer::Current()->GetApiTargetVersion()" << std::endl;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    std::cout << "before MockContainer::Current()->SetApiTargetVersion()" << std::endl;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    MenuModelNG MenuModelInstance;
    MenuModelInstance.Create();
    std::cout << "before GetInstance()->Finish()" << std::endl;
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    std::cout << "before menuNode->GetPattern" << std::endl;
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->ShowMenuDisappearAnimation();
    auto renderContext = menuNode->GetRenderContext();
    std::cout << "before renderContext->GetOpacity()" << std::endl;
    EXPECT_EQ(renderContext->GetOpacity(), 0);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ShowStackMenuDisappearAnimation001
 * @tc.desc: Test ShowStackMenuDisappearAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, ShowStackMenuDisappearAnimation001, TestSize.Level1)
{
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto subMenuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    ASSERT_NE(subMenuNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    scroll->MountToParent(subMenuNode);
    auto innerMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(innerMenu, nullptr);
    innerMenu->MountToParent(scroll);
    auto menuItem = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItem, nullptr);
    menuItem->MountToParent(innerMenu);
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(rightRow, nullptr);
    rightRow->MountToParent(menuItem);
    auto image = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(image, nullptr);
    image->MountToParent(rightRow);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    AnimationOption animationOption;
    animationOption.SetDelay(10);
    auto children = subMenuNode->GetChildren();
    const RefPtr<InterpolatingSpring> MENU_ANIMATION_CURVE =
        AceType::MakeRefPtr<InterpolatingSpring>(VELOCITY, MASS, STIFFNESS, DAMPING);
    menuPattern->ShowStackMenuDisappearAnimation(menuNode, subMenuNode, animationOption);
    EXPECT_FALSE(animationOption.curve_->IsEqual(MENU_ANIMATION_CURVE));
}
/**
 * @tc.name: AnimationScale001
 * @tc.desc: Test Layout with preview content and start/stop animation scale options
 *           for MenuPreviewMode.IMAGE
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, AnimationScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    MenuPreviewAnimationOptions scaleOptions { 0.5f, 2.0f };

    auto menuWrapperNode = GetImagePreviewMenuWrapper(std::make_optional(scaleOptions));
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

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
    layoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);

    // @tc.expected: previewScale_ value set by user defined value after Measure and LayoutNormalPreviewMenu
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    EXPECT_EQ(menuPattern->GetPreviewBeforeAnimationScale(), scaleOptions.scaleFrom);
    EXPECT_EQ(menuPattern->GetPreviewAfterAnimationScale(), scaleOptions.scaleTo);
    layoutAlgorithm->LayoutPreviewMenu(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->previewScale_, scaleOptions.scaleTo - 1);
}

/**
 * @tc.name: AnimationScale002
 * @tc.desc: Test Layout with preview content and start/stop animation scale options
 *           for MenuPreviewMode.CUSTOM
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, AnimationScale002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    MenuPreviewAnimationOptions scaleOptions { 0.5f, 2.0f };

    auto menuWrapperNode =
        GetPreviewMenuWrapper(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT), std::make_optional(scaleOptions));
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

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
    layoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);

    // @tc.expected: previewScale_ value set by user defined value after Measure and LayoutNormalPreviewMenu
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    EXPECT_EQ(menuPattern->GetPreviewBeforeAnimationScale(), scaleOptions.scaleFrom);
    EXPECT_EQ(menuPattern->GetPreviewAfterAnimationScale(), scaleOptions.scaleTo);
    layoutAlgorithm->LayoutPreviewMenu(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->previewScale_, scaleOptions.scaleTo - 1);
}

/**
 * @tc.name: FixMenuOriginOffset001
 * @tc.desc: Test FixMenuOriginOffset
 * @tc.type: FUNC
 */
HWTEST_F(MenuAnimationTestNg, FixMenuOriginOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm is null
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(nodeId, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. set menuLayoutAlgorithm's placement an call FixMenuOriginOffset function
     * @tc.expected: test algorithm for each two double direction placement
     */
    SizeF previewSize = SizeF(10.0, 10.0);
    menuLayoutAlgorithm->previewSize_ = previewSize;
    auto beforeScalePreviewOffset = OffsetF((previewSize * ((1.0f - SCALE_ANIMATION_FIRST) / 2)).Width(),
        (previewSize * ((1.0f - SCALE_ANIMATION_FIRST) / 2)).Height());
    auto afterScalePreviewOffset = OffsetF((previewSize * ((SCALE_ANIMATION_SECOND - 1.0f) / 2)).Width(),
        (previewSize * ((SCALE_ANIMATION_SECOND - 1.0f) / 2)).Height());
    auto scaleOffset = afterScalePreviewOffset + beforeScalePreviewOffset;
    OffsetF fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(scaleOffset.GetX(), -scaleOffset.GetY()));
    menuLayoutAlgorithm->placement_ = Placement::LEFT_BOTTOM;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(scaleOffset.GetX(), -scaleOffset.GetY()));

    menuLayoutAlgorithm->placement_ = Placement::TOP_RIGHT;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(-scaleOffset.GetX(), scaleOffset.GetY()));
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_TOP;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(-scaleOffset.GetX(), scaleOffset.GetY()));

    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(scaleOffset.GetX(), scaleOffset.GetY()));
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(scaleOffset.GetX(), scaleOffset.GetY()));

    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_RIGHT;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(-scaleOffset.GetX(), -scaleOffset.GetY()));
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_BOTTOM;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(-scaleOffset.GetX(), -scaleOffset.GetY()));
    /**
     * @tc.steps: step3. set menuLayoutAlgorithm's placement an call FixMenuOriginOffset function
     * @tc.expected: test algorithm for each one single direction placement
     */
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(0.0f, -scaleOffset.GetY()));
    menuLayoutAlgorithm->placement_ = Placement::TOP;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(0.0f, scaleOffset.GetY()));
    menuLayoutAlgorithm->placement_ = Placement::LEFT;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(scaleOffset.GetX(), 0.0f));
    menuLayoutAlgorithm->placement_ = Placement::RIGHT;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(-scaleOffset.GetX(), 0.0f));
    /**
     * @tc.steps: step3. set menuLayoutAlgorithm's placement an call FixMenuOriginOffset function
     * @tc.expected: test algorithm for other placement
     */
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    fresult = menuLayoutAlgorithm->FixMenuOriginOffset(SCALE_ANIMATION_FIRST, SCALE_ANIMATION_SECOND);
    EXPECT_EQ(fresult, OffsetF(scaleOffset.GetX(), -scaleOffset.GetY()));
}
} // namespace OHOS::Ace::NG
