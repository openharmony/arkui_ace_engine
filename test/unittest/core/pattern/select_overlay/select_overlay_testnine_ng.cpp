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
#include <vector>

#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/pipeline/base/constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 143;
} // namespace

class SelectOverlayNineTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
    DrawingContext GetDrawingContext(Testing::MockCanvas& canvas);
    void InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme);
};

class MockPattern : public Pattern {
    DECLARE_ACE_TYPE(MockPattern, Pattern);

public:
    MockPattern() = default;
    void OnFrameNodeChanged(FrameNodeChangeInfoFlag flag) override
    {
        changeFlag_ = flag;
    }
    FrameNodeChangeInfoFlag changeFlag_;
};

void SelectOverlayNineTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlayNineTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

DrawingContext SelectOverlayNineTestNg::GetDrawingContext(Testing::MockCanvas& canvas)
{
    DrawingContext context { canvas, 100, 100 };
    EXPECT_CALL(canvas, Save()).Times(AnyNumber());
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, Translate(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, Restore()).Times(AnyNumber());
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    return context;
}

std::vector<MenuOptionsParam> SelectOverlayNineTestNg::GetMenuOptionItems()
{
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    MenuOptionsParam menuOptionItem2;
    menuOptionItem2.content = "test2";
    menuOptionItem2.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItem1);
    menuOptionItems.emplace_back(menuOptionItem2);
    return menuOptionItems;
}

void SelectOverlayNineTestNg::InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme)
{
    CHECK_NULL_VOID(textOverlayTheme);
    textOverlayTheme->cutLabel_ = "剪切";
    textOverlayTheme->copyLabel_ = "复制";
    textOverlayTheme->pasteLabel_ = "粘贴";
    textOverlayTheme->selectAllLabel_ = "全选";
    textOverlayTheme->translateLabel_ = "翻译";
    textOverlayTheme->shareLabel_ = "分享";
    textOverlayTheme->searchLabel_ = "搜索";
    textOverlayTheme->cameraInput_ = "拍摄输入";
    textOverlayTheme->aiWrite_ = "小艺帮写";
}

/**
 * @tc.name: HideSelectOverlay001
 * @tc.desc: Test select_overlay_node HideSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, HideSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ShowSelectOverlay.
     * @tc.expected: the circlesAndBackArrowOpacity_ value was successfully changed.
     */
    pattern->overlayMode_ = SelectOverlayMode::MENU_ONLY;
    pattern->CreateNodePaintMethod();
    ASSERT_NE(pattern->selectOverlayModifier_, nullptr);
    selectOverlayNode->HideSelectOverlay([]() {});
    EXPECT_EQ(pattern->selectOverlayModifier_->circlesAndBackArrowOpacity_->Get(), 1.0);
}

/**
 * @tc.name: SelectOverlayNodeUpdateSelectMenuBg001
 * @tc.desc: Test UpdateSelectMenuBg with normal process
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, SelectOverlayNodeUpdateSelectMenuBg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up test environment
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    auto shadowTheme = AceType::MakeRefPtr<ShadowTheme>();
    ASSERT_NE(shadowTheme, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(shadowTheme));

    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode =
        AceType::DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(infoPtr));
    ASSERT_NE(selectOverlayNode, nullptr);

    MockContainer::SetMockColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    auto text = FrameNode::GetOrCreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto theme = AceType::MakeRefPtr<TokenTheme>(1);
    theme->SetColorMode(ColorMode::DARK);
    TokenThemeStorage::GetInstance()->CacheSet(theme);
    TokenThemeStorage::GetInstance()->StoreThemeScope(100, 1);
    text->themeScopeId_ = 100;

    /**
     * @tc.steps: step2. Call UpdateSelectMenuBg with valid caller
     * @tc.expected: Should update render context with correct properties
     */
    selectOverlayNode->UpdateSelectMenuBg(text);

    /**
     * @tc.steps: step3. Verify the render context properties
     */
    auto selectMenu = selectOverlayNode->selectMenu_;
    ASSERT_NE(selectMenu, nullptr);
    auto renderContext = selectMenu->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    EXPECT_EQ(renderContext->GetBackgroundColor(), std::nullopt);
    renderContext->GetOrCreateBackground();
    const auto& groupProperty = renderContext->GetBackground();
    ASSERT_NE(groupProperty, nullptr);
    BlurStyleOption actualStyleOption = groupProperty->propBlurStyleOption.value_or(BlurStyleOption());
    EXPECT_EQ(actualStyleOption.blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(actualStyleOption.colorMode, ThemeColorMode::SYSTEM);
}

/**
 * @tc.name: GetOverlayModifier001
 * @tc.desc: Test GetOverlayModifier when selectOverlayModifier_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, GetOverlayModifier001, TestSize.Level1)
{
    SelectOverlayPaintMethod paintMethod(
        nullptr, nullptr, SelectOverlayInfo(), OffsetF(), 0.0f, false, false, false, false, OffsetF(), false, nullptr);
    PaintWrapper* paintWrapper = nullptr;
    auto result = paintMethod.GetOverlayModifier(paintWrapper);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetOverlayModifier002
 * @tc.desc: Test GetOverlayModifier when menuBuilder is set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, GetOverlayModifier002, TestSize.Level1)
{
    auto selectOverlayModifier = AceType::MakeRefPtr<SelectOverlayModifier>(OffsetF(), false, nullptr);
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuBuilder = []() {};

    SelectOverlayPaintMethod paintMethod(selectOverlayModifier, nullptr, selectInfo, OffsetF(), 0.0f, false, false,
        false, false, OffsetF(), false, nullptr);
    PaintWrapper* paintWrapper = nullptr;
    auto result = paintMethod.GetOverlayModifier(paintWrapper);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetOverlayModifier003
 * @tc.desc: Test GetOverlayModifier when selectOverlayModifier_ is valid and menuBuilder is not set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, GetOverlayModifier003, TestSize.Level1)
{
    auto selectOverlayModifier = AceType::MakeRefPtr<SelectOverlayModifier>(OffsetF(), false, nullptr);
    SelectOverlayInfo selectInfo;

    SelectOverlayPaintMethod paintMethod(selectOverlayModifier, nullptr, selectInfo, OffsetF(), 0.0f, false, false,
        false, false, OffsetF(), false, nullptr);
    PaintWrapper* paintWrapper = nullptr;
    auto result = paintMethod.GetOverlayModifier(paintWrapper);
    EXPECT_EQ(result, selectOverlayModifier);
}

/**
 * @tc.name: GetContentModifier
 * @tc.desc: Test GetContentModifier when selectOverlayContentModifier_ is valid.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, GetContentModifier, TestSize.Level1)
{
    auto selectOverlayPattern =
        AceType::MakeRefPtr<SelectOverlayPattern>(std::make_shared<SelectOverlayInfo>(), SelectOverlayMode::ALL);
    auto selectOverlayContentModifier = AceType::MakeRefPtr<SelectOverlayContentModifier>(selectOverlayPattern);
    SelectOverlayPaintMethod paintMethod(nullptr, selectOverlayContentModifier, SelectOverlayInfo(), OffsetF(), 0.0f,
        false, false, false, false, OffsetF(), false, nullptr);
    PaintWrapper* paintWrapper = nullptr;
    auto result = paintMethod.GetContentModifier(paintWrapper);
    EXPECT_EQ(result, selectOverlayContentModifier);
}

/**
 * @tc.name: CheckHandleIsShown001
 * @tc.desc: Test CheckHandleIsShown when handleIsShown_ is false and hasShowAnimation_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, CheckHandleIsShown001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions: handleIsShown_ is false and hasShowAnimation_ is true.
     */
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->handleIsShown_ = false;
    selectOverlayPaintMethod->hasShowAnimation_ = true;

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->SetHandleOpacity(0.0);

    selectOverlayPaintMethod->CheckHandleIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->handleIsShown_);
}

/**
 * @tc.name: CheckHandleIsShown002
 * @tc.desc: Test CheckHandleIsShown when handleIsShown_ is false and hasShowAnimation_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, CheckHandleIsShown002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions: handleIsShown_ is false and hasShowAnimation_ is false.
     */
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->handleIsShown_ = false;
    selectOverlayPaintMethod->hasShowAnimation_ = false;

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->SetHandleOpacity(0.0);

    selectOverlayPaintMethod->CheckHandleIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->handleIsShown_);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 1.0);
}

/**
 * @tc.name: CheckHandleIsShown003
 * @tc.desc: Test CheckHandleIsShown when handleIsShown_ is already true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, CheckHandleIsShown003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions: handleIsShown_ is already true.
     */
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->handleIsShown_ = true;
    selectOverlayPaintMethod->hasShowAnimation_ = true;

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->SetHandleOpacity(0.5);

    selectOverlayPaintMethod->CheckHandleIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->handleIsShown_);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 0.5);
}

/**
 * @tc.name: CheckCirclesAndBackArrowIsShown
 * @tc.desc: Test CheckCirclesAndBackArrowIsShown when hasExtensionMenu_ is true and hasShowAnimation_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, CheckCirclesAndBackArrowIsShown, TestSize.Level1)
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
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions: hasExtensionMenu_ is true and hasShowAnimation_ is true.
     */
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    selectOverlayPaintMethod->hasShowAnimation_ = true;

    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetCirclesAndBackArrowOpacity(0.0);

    selectOverlayPaintMethod->CheckCirclesAndBackArrowIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->circlesAndBackArrowIsShown_);
    EXPECT_TRUE(overlayModifier->GetHasExtensionMenu());
}

/**
 * @tc.name: CheckCirclesAndBackArrowIsShown001
 * @tc.desc: Test CheckCirclesAndBackArrowIsShown when circlesAndBackArrowIsShown_ is already true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, CheckCirclesAndBackArrowIsShown001, TestSize.Level1)
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
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions: circlesAndBackArrowIsShown_ is already true.
     */
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = true;
    selectOverlayPaintMethod->hasExtensionMenu_ = true;

    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetCirclesAndBackArrowOpacity(0.5);

    selectOverlayPaintMethod->CheckCirclesAndBackArrowIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->circlesAndBackArrowIsShown_);
    EXPECT_EQ(overlayModifier->circlesAndBackArrowOpacity_->Get(), 0.5);
    EXPECT_TRUE(overlayModifier->GetHasExtensionMenu());
}

/**
 * @tc.name: IsModeSwitchComplete001
 * @tc.desc: Test IsModeSwitchComplete when all conditions are met for EMBED mode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, IsModeSwitchComplete001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.handleLevelMode = HandleLevelMode::EMBED;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    auto selectOverlayContentModifier = AceType::MakeRefPtr<SelectOverlayContentModifier>(pattern);
    ASSERT_NE(selectOverlayContentModifier, nullptr);

    auto callerFrameNode = FrameNode::GetOrCreateFrameNode(
        "CallerNode", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });

    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(callerFrameNode));

    SelectOverlayPaintMethod paintMethod(nullptr, selectOverlayContentModifier, selectInfo, OffsetF(), 0.0f, false,
        false, false, false, OffsetF(), false, nullptr);

    auto result = paintMethod.IsModeSwitchComplete();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsModeSwitchComplete002
 * @tc.desc: Test IsModeSwitchComplete when all conditions are met for EMBED mode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, IsModeSwitchComplete002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.handleLevelMode = HandleLevelMode::EMBED;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    auto selectOverlayContentModifier = AceType::MakeRefPtr<SelectOverlayContentModifier>(pattern);
    ASSERT_NE(selectOverlayContentModifier, nullptr);

    auto callerFrameNode = FrameNode::GetOrCreateFrameNode(
        "CallerNode", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });

    auto parentNode = FrameNode::GetOrCreateFrameNode(
        "ParentNode", ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });

    parentNode->AddChild(callerFrameNode);

    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(callerFrameNode));

    auto contentModifier = AceType::MakeRefPtr<SelectOverlayContentModifier>(pattern);
    SelectOverlayPaintMethod paintMethod(AceType::MakeRefPtr<SelectOverlayModifier>(OffsetF(), false, nullptr),
        contentModifier, selectInfo, OffsetF(), 0.0f, false, false, false, false, OffsetF(), false, nullptr);
    PaintWrapper* paintWrapper = nullptr;
    auto result = paintMethod.GetContentModifier(paintWrapper);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: IsModeSwitchComplete006
 * @tc.desc: Test IsModeSwitchComplete when selectOverlayContentModifier_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, IsModeSwitchComplete006, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.handleLevelMode = HandleLevelMode::EMBED;

    SelectOverlayPaintMethod paintMethod(AceType::MakeRefPtr<SelectOverlayModifier>(OffsetF(), false, nullptr), nullptr,
        selectInfo, OffsetF(), 0.0f, false, false, false, false, OffsetF(), false, nullptr);

    auto result = paintMethod.IsModeSwitchComplete();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckHasExtensionMenu001
 * @tc.desc: Test CheckHasExtensionMenu when hasExtensionMenu_ is true but modifier hasExtensionMenu is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, CheckHasExtensionMenu001, TestSize.Level1)
{
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
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    pattern->selectOverlayModifier_->SetHasExtensionMenu(false);
    selectOverlayPaintMethod->hasShowAnimation_ = false;

    EXPECT_TRUE(pattern->selectOverlayModifier_->GetHasExtensionMenu());

    selectOverlayPaintMethod->CheckHasExtensionMenu();
}

/**
 * @tc.name: CheckHasExtensionMenu002
 * @tc.desc: Test CheckHasExtensionMenu when hasExtensionMenu_ equals modifier value.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, CheckHasExtensionMenu002, TestSize.Level1)
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
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions: hasExtensionMenu_ equals modifier value.
     */
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetHasExtensionMenu(true);

    selectOverlayPaintMethod->CheckHasExtensionMenu();

    EXPECT_TRUE(overlayModifier->GetHasExtensionMenu());
}

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Test UpdateOverlayModifier with font scale less than AGING_MIN_SCALE.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, UpdateOverlayModifier001, TestSize.Level1)
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
     * @tc.steps: step2. call UpdateOverlayModifier with font scale less than AGING_MIN_SCALE.
     * @tc.expected: tempY calculated with buttonRadius + top.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    float fontScaleBackup = pipeline->GetFontScale();
    pipeline->SetFontScale(1.0f);
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    pipeline->SetFontScale(fontScaleBackup);
}

/**
 * @tc.name: UpdateOverlayModifier003
 * @tc.desc: Test UpdateOverlayModifier with isReversePaint_ true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, UpdateOverlayModifier003, TestSize.Level1)
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
     * @tc.steps: step2. call UpdateOverlayModifier with isReversePaint_ true.
     * @tc.expected: offset calculated with defaultMenuStartOffset_.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->isReversePaint_ = true;
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    EXPECT_TRUE(overlayModifier->isReverse_);
}

/**
 * @tc.name: UpdateOverlayModifier010
 * @tc.desc: Test UpdateOverlayModifier with isNewAvoid true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, UpdateOverlayModifier010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.isNewAvoid = true;
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
     * @tc.steps: step2. call UpdateOverlayModifier with isNewAvoid true.
     * @tc.expected: isNewAvoid value is correctly set in modifier.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    EXPECT_TRUE(overlayModifier->isNewAvoid_);
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Test UpdateContentModifier with forceDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, UpdateContentModifier001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.firstHandle.forceDraw = true;
    selectInfo.secondHandle.forceDraw = true;
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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    EXPECT_TRUE(contentModifier->firstHandleIsShow_->Get());
    EXPECT_TRUE(contentModifier->secondHandleIsShow_->Get());
}

/**
 * @tc.name: UpdateContentModifier002
 * @tc.desc: Test UpdateContentModifier with handlerColor value.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNineTestNg, UpdateContentModifier022, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.handlerColor = Color::BLUE;
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

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(12);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    EXPECT_TRUE(contentModifier->handleColor_->Get() == Color::BLUE);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

} // namespace OHOS::Ace::NG