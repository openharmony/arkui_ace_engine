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
#include <vector>

#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 143;
constexpr float AGING_MIN_SCALE = 1.75f;
} // namespace

class SelectOverlayPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
};

void SelectOverlayPaintMethodTestNg::SetUpTestCase()
{
    /**
     * @tc.desc: Set SelectTheme to themeManager before using themeManager to get SelectTheme
     */
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlayPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

std::vector<MenuOptionsParam> SelectOverlayPaintMethodTestNg::GetMenuOptionItems()
{
    /**
     * @tc.desc: Construct menu option information.
     */
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItemOne;
    menuOptionItemOne.content = "TestOne";
    menuOptionItemOne.action = [](const std::string&) {};
    MenuOptionsParam menuOptionItemTwo;
    menuOptionItemTwo.content = "TestTwo";
    menuOptionItemTwo.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItemOne);
    menuOptionItems.emplace_back(menuOptionItemTwo);
    return menuOptionItems;
}

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Test select_ovelay_paint_method UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. call UpdateContentModifier, paintWrapper is nullptr.
     * @tc.expected: the handle show value is false.
     */
    PaintWrapper* paintWrapper = nullptr;
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->firstHandleIsShow_->Set(false);
    overlayModifier->secondHandleIsShow_->Set(false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_TRUE(overlayModifier->firstHandleIsShow_->Get() == false);
    EXPECT_TRUE(overlayModifier->secondHandleIsShow_->Get() == false);
}

/**
 * @tc.name: UpdateOverlayModifier002
 * @tc.desc: Test select_ovelay_paint_method UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateOverlayModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. call UpdateContentModifier, mock TextOverlayTheme is nullptr.
     * @tc.expected: the handle show value is false.
     */
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->firstHandleIsShow_->Set(false);
    overlayModifier->secondHandleIsShow_->Set(false);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_TRUE(overlayModifier->firstHandleIsShow_->Get() == false);
    EXPECT_TRUE(overlayModifier->secondHandleIsShow_->Get() == false);
}

/**
 * @tc.name: UpdateOverlayModifier003
 * @tc.desc: Test select_ovelay_paint_method UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateOverlayModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the selectOverlayPaintMethod status value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->isCreated_ = true;
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, true);
    EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, true);

    /**
     * @tc.steps: step2. call UpdateContentModifier again.
     * @tc.expected: the selectOverlayPaintMethod status value is correct.
     */
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
    selectOverlayPaintMethod->hasExtensionMenu_ = false;
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, true);
    EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, false);
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    EXPECT_TRUE(overlayModifier->hasExtensionMenu_->Get() == false);
}

/**
 * @tc.name: UpdateOverlayModifier004
 * @tc.desc: Test select_ovelay_paint_method UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateOverlayModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the selectOverlayPaintMethod status value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    selectOverlayPaintMethod->hasShowAnimation_ = false;
    overlayModifier->circlesAndBackArrowOpacity_->Set(2.0);
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, true);
    EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, true);
    EXPECT_EQ(overlayModifier->circlesAndBackArrowOpacity_->Get(), 1.0);
}

/**
 * @tc.name: UpdateOverlayModifier005
 * @tc.desc: Test select_ovelay_paint_method UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateOverlayModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the status value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    overlayModifier->SetHasExtensionMenu(false);
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, true);
    EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, true);
    EXPECT_EQ(overlayModifier->hasExtensionMenu_->Get(), true);

    /**
     * @tc.steps: step2. call UpdateContentModifier again.
     * @tc.expected: the selectOverlayPaintMethod status value is correct.
     */
    selectOverlayPaintMethod->hasExtensionMenu_ = false;
    overlayModifier->SetHasExtensionMenu(true);
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, false);
    EXPECT_EQ(overlayModifier->hasExtensionMenu_->Get(), false);
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the isCreated_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
}

/**
 * @tc.name: UpdateContentModifier002
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto framenode = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the isCreated_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
}

/**
 * @tc.name: UpdateContentModifier003
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto framenode = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    framenode->viewPort_ = RectF(1, 1, 1, 1);
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier, paintWrapper is nullptr.
     * @tc.expected: the handleIsShown_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    PaintWrapper* paintWrapper = nullptr;
    selectOverlayPaintMethod->isCreated_ = true;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, true);
    selectOverlayPaintMethod->handleIsShown_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
}


/**
 * @tc.name: UpdateContentModifier004
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto framenode = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    /**
     * @tc.steps: step2. call UpdateContentModifier, mock TextOverlayTheme is nullptr.
     * @tc.expected: the handleIsShown_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    selectOverlayPaintMethod->isCreated_ = true;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, true);
    selectOverlayPaintMethod->handleIsShown_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
}

/**
 * @tc.name: UpdateContentModifier005
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto framenode = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    framenode->viewPort_ = RectF(1, 1, 1, 1);
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the handleIsShown_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->isCreated_ = true;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, true);
    selectOverlayPaintMethod->handleIsShown_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, true);
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, true);
}

/**
 * @tc.name: UpdateContentModifier006
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier by five situations.
     * @tc.expected: the handleIsShown_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->handleIsShown_ = true;
    contentModifier->SetHandleOpacity(2.0);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 2.0);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, true);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 2.0);
}

/**
 * @tc.name: UpdateContentModifier007
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier by five situations.
     * @tc.expected: the hasShowAnimation_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->isCreated_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    selectOverlayPaintMethod->handleIsShown_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
    selectOverlayPaintMethod->hasShowAnimation_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->hasShowAnimation_, false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, true);
    EXPECT_EQ(selectOverlayPaintMethod->hasShowAnimation_, false);
}

/**
 * @tc.name: UpdateContentModifier008
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier by five situations.
     * @tc.expected: the hasShowAnimation_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->handleIsShown_ = false;
    selectOverlayPaintMethod->hasShowAnimation_ = false;
    contentModifier->SetHandleOpacity(2.0);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 2.0);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, true);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 1.0);
}

/**
 * @tc.name: UpdateContentModifier009
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier by five situations.
     * @tc.expected: the hasShowAnimation_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->handleIsShown_ = false;
    selectOverlayPaintMethod->hasShowAnimation_ = true;
    contentModifier->SetHandleOpacity(2.0);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, true);
    EXPECT_EQ(selectOverlayPaintMethod->hasShowAnimation_, true);
    EXPECT_NE(contentModifier->handleOpacity_->Get(), 2.0);
}

/**
 * @tc.name: UpdateContentModifier010
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: handleColor equals theme handleColor.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    auto overlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(overlayTheme, nullptr);
    EXPECT_TRUE(contentModifier->handleColor_->Get() == overlayTheme->GetHandleColor());
    /**
     * @tc.steps: step3. set handlerColor and call UpdateContentModifier.
     * @tc.expected: the handleColor equals red.
     */
    selectOverlayPaintMethod->info_.handlerColor = Color::RED;
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_TRUE(contentModifier->handleColor_->Get() == Color::RED);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: UpdateContentModifier011
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.firstHandle.isShow = true;
    selectInfo.secondHandle.isShow = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: firstHandleIsShow_ and secondHandleIsShow_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->SetFirstHandleIsShow(false);
    contentModifier->SetSecondHandleIsShow(true);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), true);
    EXPECT_EQ(contentModifier->secondHandleIsShow_->Get(), false);
}

/**
 * @tc.name: UpdateContentModifier012
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.handleReverse = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: handleReverse_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->SetHandleReverse(false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(contentModifier->handleReverse_->Get(), false);

    selectOverlayPaintMethod->info_.handleReverse = true;
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(contentModifier->handleReverse_->Get(), true);
}

/**
 * @tc.name: UpdateContentModifier013
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.isSingleHandle = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: isSingleHandle_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->SetIsSingleHandle(false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(contentModifier->isSingleHandle_->Get(), true);
}

/**
 * @tc.name: UpdateContentModifier014
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: innerHandleColor_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    auto overlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(overlayTheme, nullptr);
    EXPECT_EQ(contentModifier->innerHandleColor_->Get(), overlayTheme->GetHandleColorInner());
}

/**
 * @tc.name: UpdateContentModifier015
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: handleRadius_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    auto overlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(overlayTheme, nullptr);
    EXPECT_EQ(contentModifier->handleRadius_->Get(), overlayTheme->GetHandleDiameter().ConvertToPx() / 2.0f);
}

/**
 * @tc.name: UpdateContentModifier016
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: innerHandleRadius_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    auto overlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(overlayTheme, nullptr);
    EXPECT_EQ(contentModifier->innerHandleRadius_->Get(), overlayTheme->GetHandleDiameterInner().ConvertToPx() / 2.0f);
}

/**
 * @tc.name: UpdateContentModifier017
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: isHiddenHandle_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->isHiddenHandle_ = true;
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    auto overlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(overlayTheme, nullptr);
    EXPECT_EQ(contentModifier->isHiddenHandle_->Get(), true);
}

/**
 * @tc.name: UpdateContentModifier018
 * @tc.desc: Test select_ovelay_paint_method UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateContentModifier018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.isHandleLineShow = true;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: isHandleLineShow_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->SetIsHandleLineShow(false);
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(contentModifier->isHandleLineShow_->Get(), true);
}

/**
 * @tc.name: SelectOverlayPaintMethod001
 * @tc.desc: Test select_ovelay_paint_method CheckCirclesAndBackArrowIsShown.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, SelectOverlayPaintMethod001, TestSize.Level1)
{
/**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    selectOverlayPaintMethod->isCreated_ = true;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    selectOverlayPaintMethod->hasShowAnimation_ = true;
    selectOverlayPaintMethod->CheckCirclesAndBackArrowIsShown();
    EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, true);

    selectOverlayPaintMethod->hasShowAnimation_ = false;
    selectOverlayPaintMethod->CheckCirclesAndBackArrowIsShown();
    EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, true);
}

/**
 * @tc.name: UpdateOverlayModifier006
 * @tc.desc: Test SelectOverlayPaintMethod UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateOverlayModifier006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetFontScale(AGING_MIN_SCALE);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    selectOverlayPaintMethod->hasShowAnimation_ = true;
    overlayModifier->SetHasExtensionMenu(false);
    /**
     * @tc.steps: step2. call CheckHasExtensionMenu.
     * @tc.expected: cover branch selectOverlayModifier_->GetHasExtensionMenu() != hasExtensionMenu_,
     * and hasExtensionMenu_ is true.
     */
    selectOverlayPaintMethod->CheckHasExtensionMenu();
    EXPECT_EQ(overlayModifier->GetHasExtensionMenu(), true);
    /**
     * @tc.steps: step3. call UpdateOverlayModifier.
     * @tc.expected: cover branch fontScale equal AGING_MIN_SCALE.
     */
    EXPECT_EQ(pipeline->GetFontScale(), AGING_MIN_SCALE);
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, true);
    EXPECT_EQ(overlayModifier->circlesAndBackArrowOpacity_->Get(), 1.0);
}

/**
 * @tc.name: UpdateOverlayModifier007
 * @tc.desc: Test select_ovelay_paint_method UpdateOverlayModifier when reverse layout.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPaintMethodTestNg, UpdateOverlayModifier007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto layoutProps = selectOverlayNode->GetLayoutProperty();
    ASSERT_NE(layoutProps, nullptr);
    layoutProps->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    const float offsetX = 120.5f;
    const float offsetY = 30.5f;
    pattern->defaultMenuStartOffset_ = OffsetF(offsetX, offsetY);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. call UpdateOverlayModifier.
     * @tc.expected: the status value is correct and reverse layout offset is not NULL.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto overlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(overlayTheme, nullptr);

    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    PaintWrapper paintWrapper(nullptr, AceType::MakeRefPtr<GeometryNode>(), paintProperty);
    selectOverlayPaintMethod->UpdateOverlayModifier(&paintWrapper);
    ASSERT_NE(overlayModifier->menuOptionOffset_, nullptr);
    EXPECT_TRUE(overlayModifier->isReverse_);
}
} // namespace OHOS::Ace::NG