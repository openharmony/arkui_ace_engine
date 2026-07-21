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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "ui/properties/blur_style_option.h"
#include "ui/properties/ui_material.h"
#include "ui/properties/ui_material_structs.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/display_info.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {

RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == DragBarTheme::TypeId()) {
        return AceType::MakeRefPtr<DragBarTheme>();
    } else if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == SheetTheme::TypeId()) {
        auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
        sheetTheme->closeIconButtonWidth_ = SHEET_CLOSE_ICON_WIDTH;
        sheetTheme->centerDefaultWidth_ = SHEET_LANDSCAPE_WIDTH;
        return sheetTheme;
    } else {
        return nullptr;
    }
}
} // namespace

class SheetECTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
    RefPtr<FrameNode> CreateTargetNode();
    void CreateSheetBuilder();
    int32_t minPlatformVersion_ = 0;
    std::function<RefPtr<UINode>(int32_t id)> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
};

void SheetECTestNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void SheetECTestNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void SheetECTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_ELEVEN);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetECTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> SheetECTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void SheetECTestNg::CreateSheetBuilder()
{
    builderFunc_ = [](int32_t id) -> RefPtr<UINode> {
        auto column =
            FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, id, AceType::MakeRefPtr<LinearLayoutPattern>(true));
        auto button = FrameNode::CreateFrameNode(
            V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
        column->AddChild(button);
        return column;
    };
    titleBuilderFunc_ = []() -> RefPtr<UINode> {
        auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        auto text = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        column->AddChild(text);
        return column;
    };
}

/**
 * @tc.name: SheetECBindSheet001
 * @tc.desc: Test OnBindSheet with systemMaterial and enableBlurSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheet001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    EXPECT_FALSE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: SheetECBindSheet002
 * @tc.desc: Test OnBindSheet with systemMaterial EC style
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheet002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR_EC);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    EXPECT_FALSE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: SheetECBindSheet003
 * @tc.desc: Test OnBindSheet with backgroundBlurStyle and enableBlurSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheet003, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.backgroundBlurStyle = BlurStyleOption { .blurStyle = BlurStyle::COMPONENT_THICK };

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    EXPECT_FALSE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: SheetECBindSheet004
 * @tc.desc: Test OnBindSheet with sheetEdgeLightMode ENABLED
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheet004, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_ENABLED;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);
    EXPECT_EQ(sheetPattern->GetSheetEdgeLightMode(), EdgeLightMode::EDGELIGHT_ENABLED);
}

/**
 * @tc.name: SheetECBindSheet005
 * @tc.desc: Test OnBindSheet with sheetEffectEdge START
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheet005, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.sheetEffectEdge = SheetEffectEdge::START;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);
    EXPECT_EQ(sheetPattern->GetSheetEffectEdge(), SheetEffectEdge::START);
}

/**
 * @tc.name: SheetECBindSheet006
 * @tc.desc: Test OnBindSheet with combined EC options (systemMaterial + enableBlurSnapshot + sheetEdgeLightMode)
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheet006, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR);
    sheetStyle.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_AUTO;
    sheetStyle.sheetEffectEdge = SheetEffectEdge::ALL;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);
    EXPECT_EQ(sheetPattern->GetSheetEffectEdge(), SheetEffectEdge::ALL);
    EXPECT_EQ(sheetPattern->GetSheetEdgeLightMode(), EdgeLightMode::EDGELIGHT_AUTO);
}

/**
 * @tc.name: SheetECSetSheetRenderMaterial001
 * @tc.desc: Test SetSheetRenderMaterial with systemMaterial IMMERSIVE
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetSheetRenderMaterial001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->SetSheetRenderMaterial();
}

/**
 * @tc.name: SheetECSetSheetRenderMaterial002
 * @tc.desc: Test SetSheetRenderMaterial with systemMaterial and enableBlurSnapshot (ECSub path)
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetSheetRenderMaterial002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->SetSheetRenderMaterial();
}

/**
 * @tc.name: SheetECSetSheetRenderMaterial003
 * @tc.desc: Test SetSheetRenderMaterial without systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetSheetRenderMaterial003, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->SetSheetRenderMaterial();
}

/**
 * @tc.name: SheetECClearSheetRenderMaterial001
 * @tc.desc: Test ClearSheetRenderMaterial with systemMaterial present
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECClearSheetRenderMaterial001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->ClearSheetRenderMaterial();
}

/**
 * @tc.name: SheetECClearSheetRenderMaterial002
 * @tc.desc: Test ClearSheetRenderMaterial without systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECClearSheetRenderMaterial002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->ClearSheetRenderMaterial();
}

/**
 * @tc.name: SheetECSetBlurUnderEffectComponent001
 * @tc.desc: Test SetBlurUnderEffectComponent when parent is not effectComponent
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetBlurUnderEffectComponent001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    BlurStyleOption bgBlurStyle { .blurStyle = BlurStyle::COMPONENT_THICK };
    bool result = sheetPattern->SetBlurUnderEffectComponent(bgBlurStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SheetECSetBlurUnderEffectComponent002
 * @tc.desc: Test SetBlurUnderEffectComponent when parent is effectComponent
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetBlurUnderEffectComponent002, TestSize.Level1)
{
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(-1, "", nullptr));
    auto ecNode = FrameNode::CreateFrameNode(
        V2::EFFECT_COMPONENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    sheetNode->MountToParent(ecNode);

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    BlurStyleOption bgBlurStyle { .blurStyle = BlurStyle::COMPONENT_THICK };
    bool result = sheetPattern->SetBlurUnderEffectComponent(bgBlurStyle);
    EXPECT_TRUE(result);

    auto sheetRenderContext = sheetNode->GetRenderContext();
    ASSERT_TRUE(sheetRenderContext);
    EXPECT_TRUE(sheetRenderContext->GetUseEffect().value_or(false));
}

/**
 * @tc.name: SheetECSetBlurUnderEffectComponent003
 * @tc.desc: Test SetBlurUnderEffectComponent with null host
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetBlurUnderEffectComponent003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SheetPresentationPattern>(-1, "", nullptr);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    pattern->DetachFromFrameNode(frameNode.GetRawPtr());

    BlurStyleOption bgBlurStyle { .blurStyle = BlurStyle::COMPONENT_THICK };
    bool result = pattern->SetBlurUnderEffectComponent(bgBlurStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SheetECMountSheetEffectComponent001
 * @tc.desc: Test MountSheetEffectComponent returns null when CheckIfUseEffectComponent is false
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECMountSheetEffectComponent001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    auto sheetWrapperNode =
        FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<SheetWrapperPattern>(targetNode->GetId(), targetNode->GetTag()));

    auto sheetPageNode = topModalNode;
    auto sheetNodePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetNodePattern);

    bool useEC = sheetNodePattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_FALSE(useEC);

    auto ecNode = overlayManager->MountSheetEffectComponent(sheetWrapperNode, sheetStyle, sheetPageNode);
    EXPECT_FALSE(ecNode);
}

/**
 * @tc.name: SheetECMountSheetEffectComponent002
 * @tc.desc: Test MountSheetEffectComponent with enableBlurSnapshot and backgroundBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECMountSheetEffectComponent002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.backgroundBlurStyle = BlurStyleOption { .blurStyle = BlurStyle::COMPONENT_THICK };

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    auto sheetWrapperNode =
        FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<SheetWrapperPattern>(targetNode->GetId(), targetNode->GetTag()));
    sheetWrapperNode->MountToParent(rootNode);

    auto sheetPageNode = topModalNode;
    auto sheetNodePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetNodePattern);

    bool useEC = sheetNodePattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_TRUE(useEC);

    auto ecNode = overlayManager->MountSheetEffectComponent(sheetWrapperNode, sheetStyle, sheetPageNode);
    if (ecNode) {
        EXPECT_EQ(ecNode->GetTag(), V2::EFFECT_COMPONENT_ETS_TAG);
    }
}

/**
 * @tc.name: SheetECMountSheetEffectComponent003
 * @tc.desc: Test MountSheetEffectComponent with systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECMountSheetEffectComponent003, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    auto sheetWrapperNode =
        FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<SheetWrapperPattern>(targetNode->GetId(), targetNode->GetTag()));
    sheetWrapperNode->MountToParent(rootNode);

    auto ecNode = overlayManager->MountSheetEffectComponent(sheetWrapperNode, sheetStyle, topModalNode);
    if (ecNode) {
        EXPECT_EQ(ecNode->GetTag(), V2::EFFECT_COMPONENT_ETS_TAG);
        if (sheetStyle.systemMaterialEC) {
            EXPECT_TRUE(sheetStyle.systemMaterialEC);
        }
    }
}

/**
 * @tc.name: SheetECMountSheetEffectComponent004
 * @tc.desc: Test MountSheetEffectComponent with null sheetWrapperNode
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECMountSheetEffectComponent004, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    RefPtr<FrameNode> nullWrapper = nullptr;
    SheetStyle sheetStyle;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.backgroundBlurStyle = BlurStyleOption { .blurStyle = BlurStyle::COMPONENT_THICK };
    auto sheetPageNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(-1, "", nullptr));

    auto ecNode = overlayManager->MountSheetEffectComponent(nullWrapper, sheetStyle, sheetPageNode);
    EXPECT_FALSE(ecNode);
}

/**
 * @tc.name: SheetECMountSheetEffectComponent005
 * @tc.desc: Test MountSheetEffectComponent with null sheetPageNode
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECMountSheetEffectComponent005, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>(-1, ""));
    SheetStyle sheetStyle;
    sheetStyle.enableBlurSnapshot = true;
    RefPtr<FrameNode> nullSheetPage = nullptr;

    auto ecNode = overlayManager->MountSheetEffectComponent(sheetWrapperNode, sheetStyle, nullSheetPage);
    EXPECT_FALSE(ecNode);
}

/**
 * @tc.name: SheetECWrapperPattern001
 * @tc.desc: Test SheetWrapperPattern SetSheetECNode
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECWrapperPattern001, TestSize.Level1)
{
    auto wrapperPattern = AceType::MakeRefPtr<SheetWrapperPattern>(100, "Button");
    ASSERT_TRUE(wrapperPattern);

    auto ecNode = FrameNode::CreateFrameNode(
        V2::EFFECT_COMPONENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());

    wrapperPattern->SetSheetECNode(ecNode);
    auto storedECNode = wrapperPattern->sheetECNode_;
    EXPECT_EQ(storedECNode, ecNode);
}

/**
 * @tc.name: SheetECWrapperPattern002
 * @tc.desc: Test SheetWrapperPattern GetSheetECNode when no EC node set
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECWrapperPattern002, TestSize.Level1)
{
    auto wrapperPattern = AceType::MakeRefPtr<SheetWrapperPattern>(100, "Button");
    ASSERT_TRUE(wrapperPattern);

    auto storedECNode = wrapperPattern->sheetECNode_;
    EXPECT_FALSE(storedECNode);
}

/**
 * @tc.name: SheetECUpdateSheetRender001
 * @tc.desc: Test OverlayManager UpdateSheetRender with systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetRender001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    SheetStyle updateStyle;
    updateStyle.sheetHeight.sheetMode = SheetMode::LARGE;
    updateStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR);
    updateStyle.enableBlurSnapshot = true;

    overlayManager->UpdateSheetRender(topModalNode, updateStyle, false);
}

/**
 * @tc.name: SheetECUpdateSheetRender002
 * @tc.desc: Test OverlayManager UpdateSheetRender with backgroundBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetRender002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.backgroundBlurStyle = BlurStyleOption { .blurStyle = BlurStyle::COMPONENT_THICK };

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    SheetStyle updateStyle;
    updateStyle.backgroundBlurStyle = BlurStyleOption { .blurStyle = BlurStyle::COMPONENT_REGULAR };

    overlayManager->UpdateSheetRender(topModalNode, updateStyle, false);
}

/**
 * @tc.name: SheetECUpdateSheetRenderProperty001
 * @tc.desc: Test OverlayManager UpdateSheetRenderProperty with systemMaterial update
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetRenderProperty001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    SheetStyle currentStyle;
    SheetStyle newStyle;
    newStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    newStyle.enableBlurSnapshot = true;

    overlayManager->UpdateSheetRenderProperty(topModalNode, newStyle, false);
}

/**
 * @tc.name: SheetECUpdateSheetRenderProperty002
 * @tc.desc: Test OverlayManager UpdateSheetRenderProperty with sheetEdgeLightMode
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetRenderProperty002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_DISABLED;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    EXPECT_EQ(sheetPattern->GetSheetEdgeLightMode(), EdgeLightMode::EDGELIGHT_DISABLED);
}

/**
 * @tc.name: SheetECUpdateSheetRenderProperty003
 * @tc.desc: Test OverlayManager UpdateSheetRenderProperty with sheetEffectEdge update
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetRenderProperty003, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.sheetEffectEdge = SheetEffectEdge::END;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    EXPECT_EQ(sheetPattern->GetSheetEffectEdge(), SheetEffectEdge::END);
}

/**
 * @tc.name: SheetECUpdateSheetStyle001
 * @tc.desc: Test OverlayManager UpdateSheetStyle preserves systemMaterialEC
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetStyle001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    SheetStyle updateStyle;
    updateStyle.sheetHeight.sheetMode = SheetMode::LARGE;
    auto updatedStyle = overlayManager->UpdateSheetStyle(topModalNode, updateStyle, false);
    EXPECT_EQ(updatedStyle.sheetHeight.sheetMode, SheetMode::LARGE);
}

/**
 * @tc.name: SheetECDismissSheet001
 * @tc.desc: Test DismissSheet with sheet that has systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECDismissSheet001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    EXPECT_FALSE(overlayManager->modalStack_.empty());

    overlayManager->DismissSheet();
}

/**
 * @tc.name: SheetECDismissSheet002
 * @tc.desc: Test DismissSheet with sheet that has enableBlurSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECDismissSheet002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.enableBlurSnapshot = true;
    sheetStyle.backgroundBlurStyle = BlurStyleOption { .blurStyle = BlurStyle::COMPONENT_THICK };

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    EXPECT_FALSE(overlayManager->modalStack_.empty());

    overlayManager->DismissSheet();
}

/**
 * @tc.name: SheetECCloseSheet001
 * @tc.desc: Test CloseSheet with SheetKey
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECCloseSheet001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    SheetKey sheetKey;
    sheetKey.targetId = targetNode->GetId();
    overlayManager->CloseSheet(sheetKey);
}

/**
 * @tc.name: SheetECSetSheetBorderWidth001
 * @tc.desc: Test SetSheetBorderWidth with partial update
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetSheetBorderWidth001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.borderWidth = NG::BorderWidthProperty({ 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp });
    sheetStyle.borderColor = NG::BorderColorProperty({ Color::RED, Color::RED, Color::RED, Color::RED });

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->SetSheetBorderWidth(true);
}

/**
 * @tc.name: SheetECSetSheetBorderWidth002
 * @tc.desc: Test SetSheetBorderWidth without partial update
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetSheetBorderWidth002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.borderWidth = NG::BorderWidthProperty({ 2.0_vp, 2.0_vp, 2.0_vp, 2.0_vp });

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->SetSheetBorderWidth(false);
}

/**
 * @tc.name: SheetECIsSheetBottom001
 * @tc.desc: Test IsSheetBottom with different sheet types
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECIsSheetBottom001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SheetPresentationPattern>(100, "Button", nullptr);

    pattern->sheetType_ = SheetType::SHEET_BOTTOM;
    EXPECT_TRUE(pattern->IsSheetBottom());

    pattern->sheetType_ = SheetType::SHEET_CENTER;
    EXPECT_FALSE(pattern->IsSheetBottom());

    pattern->sheetType_ = SheetType::SHEET_POPUP;
    EXPECT_FALSE(pattern->IsSheetBottom());

    pattern->sheetType_ = SheetType::SHEET_BOTTOM_OFFSET;
    EXPECT_FALSE(pattern->IsSheetBottom());
}

/**
 * @tc.name: SheetECIsSheetBottom002
 * @tc.desc: Test IsSheetBottomStyle with different API versions and sheet types
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECIsSheetBottom002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SheetPresentationPattern>(100, "Button", nullptr);

    pattern->sheetType_ = SheetType::SHEET_BOTTOM;
    EXPECT_TRUE(pattern->IsSheetBottomStyle());

    pattern->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    auto backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    EXPECT_TRUE(pattern->IsSheetBottomStyle());

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    EXPECT_FALSE(pattern->IsSheetBottomStyle());

    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SheetECSheetPresentationProperty001
 * @tc.desc: Test SheetPresentationProperty with systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetPresentationProperty001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    auto layoutProperty = topModalNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_TRUE(layoutProperty);
    auto storedStyle = layoutProperty->GetSheetStyleValue();
    EXPECT_TRUE(storedStyle.systemMaterial);
}

/**
 * @tc.name: SheetECIsNotBottomStyleInSubwindow001
 * @tc.desc: Test IsNotBottomStyleInSubwindow with SHEET_CENTER type in subwindow
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECIsNotBottomStyleInSubwindow001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetStyle.showInSubWindow = true;
    auto layoutProperty = topModalNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_TRUE(layoutProperty);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;

    EXPECT_TRUE(sheetPattern->IsNotBottomStyleInSubwindow());
}

/**
 * @tc.name: SheetECIsNotBottomStyleInSubwindow002
 * @tc.desc: Test IsNotBottomStyleInSubwindow with SHEET_BOTTOM type not in subwindow
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECIsNotBottomStyleInSubwindow002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    EXPECT_FALSE(sheetPattern->IsNotBottomStyleInSubwindow());
}

/**
 * @tc.name: SheetECSheetMaskInit001
 * @tc.desc: Test InitSheetMask with systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetMaskInit001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.maskColor = Color(0x80000000);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);
}

/**
 * @tc.name: SheetECSheetPresentationPropertyUpdate001
 * @tc.desc: Test SheetPresentationProperty with updated systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetPresentationPropertyUpdate001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);

    SheetStyle updateStyle;
    updateStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR);

    overlayManager->UpdateSheetPage(topModalNode, updateStyle);
}

/**
 * @tc.name: SheetECBindSheetCreateParam001
 * @tc.desc: Test BindSheetCreateParam struct
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheetCreateParam001, TestSize.Level1)
{
    BindSheetCreateParam param;
    EXPECT_FALSE(param.isStartByUIContext);
    EXPECT_FALSE(param.targetNode);
    EXPECT_FALSE(param.sheetContentNode);
    EXPECT_FALSE(param.callback);
}

/**
 * @tc.name: SheetECBindSheetCreateParam002
 * @tc.desc: Test BindSheetCreateParam with sheetStyle containing EC material
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECBindSheetCreateParam002, TestSize.Level1)
{
    SheetStyle style;
    style.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR_EC);
    style.enableBlurSnapshot = true;

    BindSheetCreateParam param;
    param.style = style;
    EXPECT_TRUE(param.style.systemMaterial);
    EXPECT_TRUE(param.style.enableBlurSnapshot.has_value());
}

/**
 * @tc.name: SheetECSheetHeightOperator001
 * @tc.desc: Test SheetHeight equality operator
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetHeightOperator001, TestSize.Level1)
{
    SheetHeight h1;
    h1.sheetMode = SheetMode::MEDIUM;
    SheetHeight h2;
    h2.sheetMode = SheetMode::MEDIUM;
    EXPECT_TRUE(h1 == h2);
    EXPECT_FALSE(h1 != h2);

    h2.sheetMode = SheetMode::LARGE;
    EXPECT_FALSE(h1 == h2);
    EXPECT_TRUE(h1 != h2);
}

/**
 * @tc.name: SheetECSheetHeightOperator002
 * @tc.desc: Test SheetHeight with height dimension
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetHeightOperator002, TestSize.Level1)
{
    SheetHeight h1;
    h1.height = Dimension(500);
    SheetHeight h2;
    h2.height = Dimension(500);
    EXPECT_TRUE(h1 == h2);

    h2.height = Dimension(600);
    EXPECT_FALSE(h1 == h2);
}

/**
 * @tc.name: SheetECUpdateSheetBackgroundColor001
 * @tc.desc: Test UpdateSheetBackgroundColor with EC material
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetBackgroundColor001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.backgroundColor = Color::WHITE;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->UpdateSheetBackgroundColor();
}

/**
 * @tc.name: SheetECUpdateSheetBackgroundBlurStyle001
 * @tc.desc: Test UpdateSheetBackgroundBlurStyle with EC material
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetBackgroundBlurStyle001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.backgroundBlurStyle = BlurStyleOption { .blurStyle = BlurStyle::COMPONENT_THICK };

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->UpdateSheetBackgroundBlurStyle();
}

/**
 * @tc.name: SheetECSheetThemeType001
 * @tc.desc: Test SheetPresentationPattern sheetThemeType_ field
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetThemeType001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SheetPresentationPattern>(100, "Button", nullptr);
    EXPECT_EQ(pattern->sheetThemeType_, "auto");
}

/**
 * @tc.name: SheetECSetSheetHeightForTranslate001
 * @tc.desc: Test SetSheetHeightForTranslate and GetSheetHeightForTranslate
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSetSheetHeightForTranslate001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SheetPresentationPattern>(100, "Button", nullptr);
    EXPECT_FLOAT_EQ(pattern->GetSheetHeightForTranslate(), 0.0);

    pattern->SetSheetHeightForTranslate(500.0f);
    EXPECT_FLOAT_EQ(pattern->GetSheetHeightForTranslate(), 500.0f);
}

/**
 * @tc.name: SheetECNeedDoubleAvoidAfterLayout001
 * @tc.desc: Test SetNeedDoubleAvoidAfterLayout and GetNeedDoubleAvoidAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECNeedDoubleAvoidAfterLayout001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<SheetPresentationPattern>(100, "Button", nullptr);
    EXPECT_FALSE(pattern->GetNeedDoubleAvoidAfterLayout());

    pattern->SetNeedDoubleAvoidAfterLayout(true);
    EXPECT_TRUE(pattern->GetNeedDoubleAvoidAfterLayout());

    pattern->SetNeedDoubleAvoidAfterLayout(false);
    EXPECT_FALSE(pattern->GetNeedDoubleAvoidAfterLayout());
}

/**
 * @tc.name: SheetECRenderContextBackBlurStyle001
 * @tc.desc: Test RenderContext UpdateBackBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECRenderContextBackBlurStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_TRUE(renderContext);

    BlurStyleOption option { .blurStyle = BlurStyle::COMPONENT_THICK };
    renderContext->UpdateBackBlurStyle(option);
}

/**
 * @tc.name: SheetECRenderContextBackBlurStyle002
 * @tc.desc: Test RenderContext UpdateBackBlurStyle with different styles
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECRenderContextBackBlurStyle002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::EFFECT_COMPONENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_TRUE(renderContext);

    BlurStyleOption option { .blurStyle = BlurStyle::COMPONENT_REGULAR };
    renderContext->UpdateBackBlurStyle(option);
}

/**
 * @tc.name: SheetECSheetKeyboardAvoidMode001
 * @tc.desc: Test SheetKeyboardAvoidMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetKeyboardAvoidMode001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SheetKeyboardAvoidMode::NONE), 0);
    EXPECT_EQ(static_cast<int32_t>(SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE), 1);
    EXPECT_EQ(static_cast<int32_t>(SheetKeyboardAvoidMode::RESIZE_ONLY), 2);
    EXPECT_EQ(static_cast<int32_t>(SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL), 3);
    EXPECT_EQ(static_cast<int32_t>(SheetKeyboardAvoidMode::POPUP_SHEET), 4);
}

/**
 * @tc.name: SheetECScrollSizeMode001
 * @tc.desc: Test ScrollSizeMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECScrollSizeMode001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(ScrollSizeMode::FOLLOW_DETENT), 0);
    EXPECT_EQ(static_cast<int32_t>(ScrollSizeMode::CONTINUOUS), 1);
}

/**
 * @tc.name: SheetECUpdateSheetParamResource001
 * @tc.desc: Test UpdateSheetParamResource with sheetNode and sheetStyle containing EC material
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECUpdateSheetParamResource001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->UpdateSheetParamResource(topModalNode, sheetStyle);
}

/**
 * @tc.name: SheetECRemoveSheetResourceByMaterial001
 * @tc.desc: Test RemoveSheetResourceByMaterial
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECRemoveSheetResourceByMaterial001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.showDragBar = true;
    sheetStyle.systemMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->RemoveSheetResourceByMaterial(topModalNode, sheetStyle);
}

/**
 * @tc.name: SheetECIsModalEmpty001
 * @tc.desc: Test OverlayManager IsModalEmpty
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECIsModalEmpty001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_TRUE(overlayManager->IsModalEmpty());
}

/**
 * @tc.name: SheetECHasModalPage001
 * @tc.desc: Test OverlayManager HasModalPage
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECHasModalPage001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_FALSE(overlayManager->HasModalPage());
}

/**
 * @tc.name: SheetECSheetTypeEnum001
 * @tc.desc: Test SheetType enum values
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetTypeEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_BOTTOM), 0);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_CENTER), 1);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_POPUP), 2);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_SIDE), 3);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_CONTENT_COVER), 4);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_BOTTOMLANDSPACE), 5);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_BOTTOM_FREE_WINDOW), 6);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_BOTTOM_OFFSET), 7);
    EXPECT_EQ(static_cast<int32_t>(SheetType::SHEET_MINIMIZE), 8);
}

/**
 * @tc.name: SheetECSheetModeEnum001
 * @tc.desc: Test SheetMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetModeEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SheetMode::MEDIUM), 0);
    EXPECT_EQ(static_cast<int32_t>(SheetMode::LARGE), 1);
    EXPECT_EQ(static_cast<int32_t>(SheetMode::AUTO), 2);
}

/**
 * @tc.name: SheetECSheetAccessibilityDetents001
 * @tc.desc: Test SheetAccessibilityDetents enum values
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetAccessibilityDetents001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SheetAccessibilityDetents::HIGH), 0);
    EXPECT_EQ(static_cast<int32_t>(SheetAccessibilityDetents::MEDIUM), 1);
    EXPECT_EQ(static_cast<int32_t>(SheetAccessibilityDetents::LOW), 2);
}

/**
 * @tc.name: SheetECSheetArrowPosition001
 * @tc.desc: Test SheetArrowPosition enum values
 * @tc.type: FUNC
 */
HWTEST_F(SheetECTestNg, SheetECSheetArrowPosition001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::TOP_LEFT), 0);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::TOP_RIGHT), 1);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::BOTTOM_LEFT), 2);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::BOTTOM_RIGHT), 3);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::LEFT_TOP), 4);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::LEFT_BOTTOM), 5);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::RIGHT_TOP), 6);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::RIGHT_BOTTOM), 7);
    EXPECT_EQ(static_cast<int32_t>(SheetArrowPosition::NONE), 8);
}
} // namespace OHOS::Ace::NG
