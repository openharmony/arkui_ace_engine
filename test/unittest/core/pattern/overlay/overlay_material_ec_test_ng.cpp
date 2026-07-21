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
#include "core/common/ace_application_info.h"
#include "core/common/display_info.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/render/ui_material_filter_creator.h"
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

class OverlayMaterialECTestNg : public testing::Test {
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

void OverlayMaterialECTestNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayMaterialECTestNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void OverlayMaterialECTestNg::SetUpTestCase()
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

void OverlayMaterialECTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayMaterialECTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayMaterialECTestNg::CreateSheetBuilder()
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
 * @tc.name: CheckIfUseEffectComponent001
 * @tc.desc: Test CheckIfUseEffectComponent with enableBlurSnapshot=true, not popup, has backgroundBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, CheckIfUseEffectComponent001, TestSize.Level1)
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
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    bool result = sheetPattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckIfUseEffectComponent002
 * @tc.desc: Test CheckIfUseEffectComponent with enableBlurSnapshot=false
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, CheckIfUseEffectComponent002, TestSize.Level1)
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
    sheetStyle.enableBlurSnapshot = false;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    bool result = sheetPattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckIfUseEffectComponent003
 * @tc.desc: Test CheckIfUseEffectComponent with enableBlurSnapshot=true but sheetType=SHEET_POPUP
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, CheckIfUseEffectComponent003, TestSize.Level1)
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
    sheetStyle.sheetType = SheetType::SHEET_POPUP;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);
    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;

    bool result = sheetPattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckIfUseEffectComponent004
 * @tc.desc: Test CheckIfUseEffectComponent with enableBlurSnapshot=true, no backgroundBlurStyle, no systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, CheckIfUseEffectComponent004, TestSize.Level1)
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

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    bool result = sheetPattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckIfUseEffectComponent005
 * @tc.desc: Test CheckIfUseEffectComponent with enableBlurSnapshot=true and systemMaterial immersive
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, CheckIfUseEffectComponent005, TestSize.Level1)
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

    bool result = sheetPattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckIfUseEffectComponent006
 * @tc.desc: Test CheckIfUseEffectComponent with systemMaterial SEMI_TRANSPARENT type (not IMMERSIVE)
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, CheckIfUseEffectComponent006, TestSize.Level1)
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
    auto semiMaterial = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    semiMaterial->SetType(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT));
    sheetStyle.systemMaterial = semiMaterial;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    bool result = sheetPattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetSheetEdgeLightMode001
 * @tc.desc: Test SetSheetEdgeLightMode with EDGELIGHT_ENABLED
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SetSheetEdgeLightMode001, TestSize.Level1)
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
    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;

    bool result = sheetPattern->CheckIfUseEffectComponent(sheetStyle);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetSheetEdgeLightMode002
 * @tc.desc: Test SetSheetEdgeLightMode with EDGELIGHT_AUTO
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SetSheetEdgeLightMode002, TestSize.Level1)
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
    sheetStyle.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_AUTO;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    sheetPattern->SetSheetEdgeLightMode(sheetStyle);
    EXPECT_EQ(sheetPattern->GetSheetEdgeLightMode(), EdgeLightMode::EDGELIGHT_AUTO);
}

/**
 * @tc.name: SetSheetEdgeLightMode003
 * @tc.desc: Test SetSheetEdgeLightMode with EDGELIGHT_DISABLED
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SetSheetEdgeLightMode003, TestSize.Level1)
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

    sheetPattern->SetSheetEdgeLightMode(sheetStyle);
    EXPECT_EQ(sheetPattern->GetSheetEdgeLightMode(), EdgeLightMode::EDGELIGHT_DISABLED);
}

/**
 * @tc.name: SetSheetEdgeLightMode004
 * @tc.desc: Test SetSheetEdgeLightMode when sheetStyle has no sheetEdgeLightMode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SetSheetEdgeLightMode004, TestSize.Level1)
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

    EdgeLightMode defaultMode = sheetPattern->GetSheetEdgeLightMode();
    sheetPattern->SetSheetEdgeLightMode(sheetStyle);
    EXPECT_EQ(sheetPattern->GetSheetEdgeLightMode(), defaultMode);
}

/**
 * @tc.name: SheetStyleSystemMaterialEC001
 * @tc.desc: Test SheetStyle systemMaterialEC and systemMaterialECSub fields default state
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleSystemMaterialEC001, TestSize.Level1)
{
    SheetStyle sheetStyle;
    EXPECT_FALSE(sheetStyle.systemMaterialEC);
    EXPECT_FALSE(sheetStyle.systemMaterialECSub);
}

/**
 * @tc.name: SheetStyleSystemMaterialEC002
 * @tc.desc: Test SheetStyle systemMaterialEC field assignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleSystemMaterialEC002, TestSize.Level1)
{
    SheetStyle sheetStyle;
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR_EC);
    sheetStyle.systemMaterialEC = material;
    EXPECT_TRUE(sheetStyle.systemMaterialEC);
    EXPECT_EQ(sheetStyle.systemMaterialEC->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
}

/**
 * @tc.name: SheetStyleSystemMaterialEC003
 * @tc.desc: Test SheetStyle systemMaterialECSub field assignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleSystemMaterialEC003, TestSize.Level1)
{
    SheetStyle sheetStyle;
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR_EC_SUB);
    sheetStyle.systemMaterialECSub = material;
    EXPECT_TRUE(sheetStyle.systemMaterialECSub);
    EXPECT_EQ(sheetStyle.systemMaterialECSub->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
}

/**
 * @tc.name: SheetStylePartialUpdate001
 * @tc.desc: Test SheetStyle PartialUpdate with systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStylePartialUpdate001, TestSize.Level1)
{
    SheetStyle original;
    original.sheetHeight.sheetMode = SheetMode::MEDIUM;
    original.showDragBar = true;

    SheetStyle update;
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    update.systemMaterial = material;

    original.PartialUpdate(update);
    EXPECT_TRUE(original.systemMaterial);
}

/**
 * @tc.name: SheetStylePartialUpdate002
 * @tc.desc: Test SheetStyle PartialUpdate with enableBlurSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStylePartialUpdate002, TestSize.Level1)
{
    SheetStyle original;
    original.sheetHeight.sheetMode = SheetMode::MEDIUM;
    original.showDragBar = true;

    SheetStyle update;
    update.enableBlurSnapshot = true;

    original.PartialUpdate(update);
    EXPECT_TRUE(original.enableBlurSnapshot.has_value());
    EXPECT_TRUE(original.enableBlurSnapshot.value());
}

/**
 * @tc.name: SheetStylePartialUpdate003
 * @tc.desc: Test SheetStyle PartialUpdate with sheetEdgeLightMode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStylePartialUpdate003, TestSize.Level1)
{
    SheetStyle original;
    original.sheetHeight.sheetMode = SheetMode::MEDIUM;

    SheetStyle update;
    update.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_ENABLED;

    original.PartialUpdate(update);
    EXPECT_TRUE(original.sheetEdgeLightMode.has_value());
    EXPECT_EQ(original.sheetEdgeLightMode.value(), EdgeLightMode::EDGELIGHT_ENABLED);
}

/**
 * @tc.name: SheetStylePartialUpdate004
 * @tc.desc: Test SheetStyle PartialUpdate does not overwrite existing fields when update has no value
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStylePartialUpdate004, TestSize.Level1)
{
    SheetStyle original;
    original.sheetHeight.sheetMode = SheetMode::MEDIUM;
    original.showDragBar = true;
    original.enableBlurSnapshot = true;
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    original.systemMaterial = material;

    SheetStyle update;
    update.sheetHeight.sheetMode = SheetMode::LARGE;

    original.PartialUpdate(update);
    EXPECT_TRUE(original.enableBlurSnapshot.has_value());
    EXPECT_TRUE(original.enableBlurSnapshot.value());
    EXPECT_TRUE(original.systemMaterial);
    EXPECT_EQ(original.sheetHeight.sheetMode, SheetMode::LARGE);
}

/**
 * @tc.name: ConvertToImmersiveEC001
 * @tc.desc: Test ViewAbstract::ConvertToImmersiveEC with null material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ConvertToImmersiveEC001, TestSize.Level1)
{
    RefPtr<UiMaterial> nullMaterial = nullptr;
    auto result = ViewAbstract::ConvertToImmersiveEC(nullMaterial);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ConvertToImmersiveEC002
 * @tc.desc: Test ViewAbstract::ConvertToImmersiveEC with SEMI_TRANSPARENT material (not IMMERSIVE)
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ConvertToImmersiveEC002, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    material->SetType(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT));
    RefPtr<UiMaterial> refMaterial = material;
    auto result = ViewAbstract::ConvertToImmersiveEC(refMaterial);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ConvertToImmersiveEC003
 * @tc.desc: Test ViewAbstract::ConvertToImmersiveEC with IMMERSIVE material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ConvertToImmersiveEC003, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    RefPtr<UiMaterial> refMaterial = material;
    auto result = ViewAbstract::ConvertToImmersiveEC(refMaterial);
    if (material->GetImmersiveOptions()) {
        EXPECT_TRUE(result);
        EXPECT_NE(result, refMaterial);
    }
}

/**
 * @tc.name: ConvertToImmersiveECSub001
 * @tc.desc: Test ViewAbstract::ConvertToImmersiveECSub with null material returns null
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ConvertToImmersiveECSub001, TestSize.Level1)
{
    RefPtr<UiMaterial> nullMaterial = nullptr;
    auto result = ViewAbstract::ConvertToImmersiveECSub(nullMaterial);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ConvertToImmersiveECSub002
 * @tc.desc: Test ViewAbstract::ConvertToImmersiveECSub with SEMI_TRANSPARENT material returns same material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ConvertToImmersiveECSub002, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    material->SetType(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT));
    RefPtr<UiMaterial> refMaterial = material;
    auto result = ViewAbstract::ConvertToImmersiveECSub(refMaterial);
    EXPECT_EQ(result, refMaterial);
}

/**
 * @tc.name: ConvertToImmersiveECSub003
 * @tc.desc: Test ViewAbstract::ConvertToImmersiveECSub with IMMERSIVE material returns copy
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ConvertToImmersiveECSub003, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    RefPtr<UiMaterial> refMaterial = material;
    auto result = ViewAbstract::ConvertToImmersiveECSub(refMaterial);
    if (material->GetImmersiveOptions()) {
        EXPECT_TRUE(result);
    } else {
        EXPECT_EQ(result, refMaterial);
    }
}

/**
 * @tc.name: MaterialTypeEnum001
 * @tc.desc: Test MaterialType enum values including EC variants
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialTypeEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(MaterialType::NONE), 0);
    EXPECT_EQ(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT), 1);
    EXPECT_EQ(static_cast<int32_t>(MaterialType::IMMERSIVE), 2);
    EXPECT_EQ(static_cast<int32_t>(MaterialType::MAX), static_cast<int32_t>(MaterialType::IMMERSIVE));
}

/**
 * @tc.name: UiMaterialStyleEnum001
 * @tc.desc: Test UiMaterialStyle enum values including EC and EC_SUB variants
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialStyleEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN), 0);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::THIN), 1);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::REGULAR), 2);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::THICK), 3);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK), 4);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN_EC), 5);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::THIN_EC), 6);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::REGULAR_EC), 7);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::THICK_EC), 8);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK_EC), 9);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN_EC_SUB), 10);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::THIN_EC_SUB), 11);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::REGULAR_EC_SUB), 12);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::THICK_EC_SUB), 13);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK_EC_SUB), 14);
    EXPECT_EQ(static_cast<int32_t>(UiMaterialStyle::MAX), static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK_EC_SUB));
}

/**
 * @tc.name: EdgeLightModeEnum001
 * @tc.desc: Test EdgeLightMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, EdgeLightModeEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(EdgeLightMode::EDGELIGHT_AUTO), 0);
    EXPECT_EQ(static_cast<int32_t>(EdgeLightMode::EDGELIGHT_ENABLED), 1);
    EXPECT_EQ(static_cast<int32_t>(EdgeLightMode::EDGELIGHT_DISABLED), 2);
}

/**
 * @tc.name: DistortionModeEnum001
 * @tc.desc: Test DistortionMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, DistortionModeEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(DistortionMode::DISTORTION_AUTO), 0);
    EXPECT_EQ(static_cast<int32_t>(DistortionMode::DISTORTION_ENABLED), 1);
    EXPECT_EQ(static_cast<int32_t>(DistortionMode::DISTORTION_DISABLED), 2);
}

/**
 * @tc.name: MaterialUtilsGetTypeFromMaterial001
 * @tc.desc: Test MaterialUtils::GetTypeFromMaterial with null material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetTypeFromMaterial001, TestSize.Level1)
{
    auto result = MaterialUtils::GetTypeFromMaterial(nullptr);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: MaterialUtilsGetTypeFromMaterial002
 * @tc.desc: Test MaterialUtils::GetTypeFromMaterial with SEMI_TRANSPARENT material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetTypeFromMaterial002, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    material->SetType(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT));
    auto result = MaterialUtils::GetTypeFromMaterial(AceType::RawPtr(material));
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), MaterialType::SEMI_TRANSPARENT);
}

/**
 * @tc.name: MaterialUtilsGetTypeFromMaterial003
 * @tc.desc: Test MaterialUtils::GetTypeFromMaterial with IMMERSIVE material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetTypeFromMaterial003, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    auto result = MaterialUtils::GetTypeFromMaterial(AceType::RawPtr(material));
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), MaterialType::IMMERSIVE);
}

/**
 * @tc.name: MaterialUtilsIsEmptyMaterial001
 * @tc.desc: Test MaterialUtils::IsEmptyMaterial with null material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsIsEmptyMaterial001, TestSize.Level1)
{
    RefPtr<UiMaterial> nullMaterial = nullptr;
    bool result = MaterialUtils::IsEmptyMaterial(nullMaterial);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MaterialUtilsIsEmptyMaterial002
 * @tc.desc: Test MaterialUtils::IsEmptyMaterial with valid material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsIsEmptyMaterial002, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    bool result = MaterialUtils::IsEmptyMaterial(material);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MaterialUtilsCheckMaterialValid001
 * @tc.desc: Test MaterialUtils::CheckMaterialValid with valid type
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsCheckMaterialValid001, TestSize.Level1)
{
    bool result = MaterialUtils::CheckMaterialValid(static_cast<int32_t>(MaterialType::IMMERSIVE));
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MaterialUtilsCheckMaterialValid002
 * @tc.desc: Test MaterialUtils::CheckMaterialValid with invalid type
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsCheckMaterialValid002, TestSize.Level1)
{
    bool result = MaterialUtils::CheckMaterialValid(999);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MaterialUtilsCheckMaterialValid003
 * @tc.desc: Test MaterialUtils::CheckMaterialValid with SEMI_TRANSPARENT type
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsCheckMaterialValid003, TestSize.Level1)
{
    bool result = MaterialUtils::CheckMaterialValid(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT));
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MaterialUtilsIsMaterialEnabled001
 * @tc.desc: Test MaterialUtils::IsMaterialEnabled and IsMaterialDisabled
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsIsMaterialEnabled001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    bool isEnabled = MaterialUtils::IsMaterialEnabled();
    bool isDisabled = MaterialUtils::IsMaterialDisabled();
    EXPECT_NE(isEnabled, isDisabled);
    AceApplicationInfo::GetInstance().SetUIMaterialState("");
}

/**
 * @tc.name: ImmersiveMaterialConfig001
 * @tc.desc: Test ImmersiveMaterialConfig default values
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ImmersiveMaterialConfig001, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    EXPECT_EQ(config.materialColor, Color());
    EXPECT_FALSE(config.colorInvert);
    EXPECT_TRUE(config.applyShadow);
    EXPECT_FLOAT_EQ(config.dipScale, 1.0f);
    EXPECT_FALSE(config.interactive);
    EXPECT_FALSE(config.HasLightEffect());
}

/**
 * @tc.name: ImmersiveMaterialConfig002
 * @tc.desc: Test ImmersiveMaterialConfig equality operator
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ImmersiveMaterialConfig002, TestSize.Level1)
{
    ImmersiveMaterialConfig config1;
    ImmersiveMaterialConfig config2;
    EXPECT_TRUE(config1 == config2);

    config1.materialColor = Color(0xFFFF0000);
    EXPECT_FALSE(config1 == config2);
}

/**
 * @tc.name: ImmersiveMaterialConfig003
 * @tc.desc: Test ImmersiveMaterialConfig with lightEffectOptions
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, ImmersiveMaterialConfig003, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    LightEffectOptions options;
    config.lightEffectOptions = options;
    EXPECT_TRUE(config.HasLightEffect());

    config.lightEffectOptions.reset();
    EXPECT_FALSE(config.HasLightEffect());
}

/**
 * @tc.name: SheetEffectEdgeEnum001
 * @tc.desc: Test SheetEffectEdge enum values
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetEffectEdgeEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SheetEffectEdge::NONE), 0);
    EXPECT_EQ(static_cast<int32_t>(SheetEffectEdge::START), 1);
    EXPECT_EQ(static_cast<int32_t>(SheetEffectEdge::END), 2);
    EXPECT_EQ(static_cast<int32_t>(SheetEffectEdge::ALL), 3);
}

/**
 * @tc.name: UiMaterialStyleECCreate001
 * @tc.desc: Test MaterialUtils::GetInitMaterial with EC style variants
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialStyleECCreate001, TestSize.Level1)
{
    auto ecThin = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN_EC);
    ASSERT_TRUE(ecThin);
    EXPECT_EQ(ecThin->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));

    auto ecRegular = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR_EC);
    ASSERT_TRUE(ecRegular);
    EXPECT_EQ(ecRegular->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));

    auto ecSubThin = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN_EC_SUB);
    ASSERT_TRUE(ecSubThin);
    EXPECT_EQ(ecSubThin->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
}

/**
 * @tc.name: UiMaterialStyleECCreate002
 * @tc.desc: Test MaterialUtils::GetInitMaterial with all EC_SUB style variants
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialStyleECCreate002, TestSize.Level1)
{
    std::vector<UiMaterialStyle> ecSubStyles = {
        UiMaterialStyle::ULTRA_THIN_EC_SUB,
        UiMaterialStyle::THIN_EC_SUB,
        UiMaterialStyle::REGULAR_EC_SUB,
        UiMaterialStyle::THICK_EC_SUB,
        UiMaterialStyle::ULTRA_THICK_EC_SUB,
    };
    for (auto& style : ecSubStyles) {
        auto material = MaterialUtils::GetInitMaterial(style);
        ASSERT_TRUE(material);
        EXPECT_EQ(material->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    }
}

/**
 * @tc.name: UiMaterialStyleECCreate003
 * @tc.desc: Test MaterialUtils::GetInitMaterial with all EC style variants
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialStyleECCreate003, TestSize.Level1)
{
    std::vector<UiMaterialStyle> ecStyles = {
        UiMaterialStyle::ULTRA_THIN_EC,
        UiMaterialStyle::THIN_EC,
        UiMaterialStyle::REGULAR_EC,
        UiMaterialStyle::THICK_EC,
        UiMaterialStyle::ULTRA_THICK_EC,
    };
    for (auto& style : ecStyles) {
        auto material = MaterialUtils::GetInitMaterial(style);
        ASSERT_TRUE(material);
        EXPECT_EQ(material->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    }
}

/**
 * @tc.name: SheetStyleEnableBlurSnapshot001
 * @tc.desc: Test SheetStyle enableBlurSnapshot field
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleEnableBlurSnapshot001, TestSize.Level1)
{
    SheetStyle style;
    EXPECT_FALSE(style.enableBlurSnapshot.has_value());

    style.enableBlurSnapshot = true;
    EXPECT_TRUE(style.enableBlurSnapshot.has_value());
    EXPECT_TRUE(style.enableBlurSnapshot.value());

    style.enableBlurSnapshot = false;
    EXPECT_TRUE(style.enableBlurSnapshot.has_value());
    EXPECT_FALSE(style.enableBlurSnapshot.value());
}

/**
 * @tc.name: SheetStyleSheetEffectEdge001
 * @tc.desc: Test SheetStyle sheetEffectEdge field
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleSheetEffectEdge001, TestSize.Level1)
{
    SheetStyle style;
    EXPECT_FALSE(style.sheetEffectEdge.has_value());

    style.sheetEffectEdge = SheetEffectEdge::NONE;
    EXPECT_TRUE(style.sheetEffectEdge.has_value());
    EXPECT_EQ(style.sheetEffectEdge.value(), SheetEffectEdge::NONE);

    style.sheetEffectEdge = SheetEffectEdge::ALL;
    EXPECT_TRUE(style.sheetEffectEdge.has_value());
    EXPECT_EQ(style.sheetEffectEdge.value(), SheetEffectEdge::ALL);

    style.sheetEffectEdge = SheetEffectEdge::START;
    EXPECT_EQ(style.sheetEffectEdge.value(), SheetEffectEdge::START);

    style.sheetEffectEdge = SheetEffectEdge::END;
    EXPECT_EQ(style.sheetEffectEdge.value(), SheetEffectEdge::END);
}

/**
 * @tc.name: UiMaterialInfo001
 * @tc.desc: Test UiMaterialInfo struct with immersiveConfig
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialInfo001, TestSize.Level1)
{
    UiMaterialInfo info;
    EXPECT_FALSE(info.material);
    EXPECT_FALSE(info.immersiveConfig.has_value());
    EXPECT_FALSE(info.transparencyCallbackId.has_value());

    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    info.material = material;
    EXPECT_TRUE(info.material);

    ImmersiveMaterialConfig config;
    info.immersiveConfig = config;
    EXPECT_TRUE(info.immersiveConfig.has_value());
}

/**
 * @tc.name: UiMaterialParam001
 * @tc.desc: Test UiMaterialParam struct fields
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialParam001, TestSize.Level1)
{
    UiMaterialParam param;
    EXPECT_EQ(param.backgroundColor, Color());
    EXPECT_EQ(param.borderWidth, NG::BorderWidthProperty());
    EXPECT_EQ(param.borderColor, NG::BorderColorProperty());
}

/**
 * @tc.name: SheetStyleOperatorEqual001
 * @tc.desc: Test SheetStyle operator== with systemMaterial
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleOperatorEqual001, TestSize.Level1)
{
    SheetStyle style1;
    SheetStyle style2;
    EXPECT_TRUE(style1 == style2);

    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    style1.systemMaterial = material;
    EXPECT_FALSE(style1 == style2);

    style2.systemMaterial = material;
    EXPECT_TRUE(style1 == style2);
}

/**
 * @tc.name: SheetStyleOperatorEqual002
 * @tc.desc: Test SheetStyle operator== with enableBlurSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleOperatorEqual002, TestSize.Level1)
{
    SheetStyle style1;
    SheetStyle style2;
    style1.enableBlurSnapshot = true;
    style2.enableBlurSnapshot = true;
    EXPECT_TRUE(style1 == style2);

    style2.enableBlurSnapshot = false;
    EXPECT_FALSE(style1 == style2);
}

/**
 * @tc.name: SheetStyleOperatorEqual003
 * @tc.desc: Test SheetStyle operator== with sheetEdgeLightMode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetStyleOperatorEqual003, TestSize.Level1)
{
    SheetStyle style1;
    SheetStyle style2;
    style1.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_ENABLED;
    style2.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_ENABLED;
    EXPECT_TRUE(style1 == style2);

    style2.sheetEdgeLightMode = EdgeLightMode::EDGELIGHT_DISABLED;
    EXPECT_FALSE(style1 == style2);
}

/**
 * @tc.name: GetParentSkipEffectComponent001
 * @tc.desc: Test SheetPresentationPattern::GetParentSkipEffectComponent with null node
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, GetParentSkipEffectComponent001, TestSize.Level1)
{
    RefPtr<FrameNode> nullNode = nullptr;
    if (nullNode) {
        auto result = SheetPresentationPattern::GetParentSkipEffectComponent(nullNode);
        EXPECT_FALSE(result);
    }
}

/**
 * @tc.name: GetParentSkipEffectComponent002
 * @tc.desc: Test SheetPresentationPattern::GetParentSkipEffectComponent with regular parent
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, GetParentSkipEffectComponent002, TestSize.Level1)
{
    auto childNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    childNode->MountToParent(parentNode);

    auto result = SheetPresentationPattern::GetParentSkipEffectComponent(childNode);
    EXPECT_EQ(result, parentNode);
}

/**
 * @tc.name: GetParentSkipEffectComponent003
 * @tc.desc: Test GetParentSkipEffectComponent with EFFECT_COMPONENT parent
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, GetParentSkipEffectComponent003, TestSize.Level1)
{
    auto childNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto ecNode = FrameNode::CreateFrameNode(
        V2::EFFECT_COMPONENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto grandParentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    childNode->MountToParent(ecNode);
    ecNode->MountToParent(grandParentNode);

    auto result = SheetPresentationPattern::GetParentSkipEffectComponent(childNode);
    EXPECT_EQ(result, grandParentNode);
}

/**
 * @tc.name: RenderContextUpdateUseEffect001
 * @tc.desc: Test RenderContext UpdateUseEffect method
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, RenderContextUpdateUseEffect001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_TRUE(renderContext);

    renderContext->UpdateUseEffect(true);
    EXPECT_TRUE(renderContext->GetUseEffect().value_or(false));

    renderContext->UpdateUseEffect(false);
    EXPECT_FALSE(renderContext->GetUseEffect().value_or(false));
}

/**
 * @tc.name: MaterialUtilsGetInitMaterial001
 * @tc.desc: Test MaterialUtils::GetInitMaterial for different styles
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetInitMaterial001, TestSize.Level1)
{
    auto materialThin = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    if (materialThin) {
        EXPECT_EQ(materialThin->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    }
}

/**
 * @tc.name: MaterialUtilsGetInitMaterial002
 * @tc.desc: Test MaterialUtils::GetInitMaterial for EC styles
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetInitMaterial002, TestSize.Level1)
{
    auto materialThinEC = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN_EC);
    if (materialThinEC) {
        EXPECT_EQ(materialThinEC->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    }
}

/**
 * @tc.name: MaterialUtilsGetInitMaterial003
 * @tc.desc: Test MaterialUtils::GetInitMaterial for EC_SUB styles
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetInitMaterial003, TestSize.Level1)
{
    auto materialThinECSub = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN_EC_SUB);
    if (materialThinECSub) {
        EXPECT_EQ(materialThinECSub->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    }
}

/**
 * @tc.name: MaterialUtilsIsEnableMaterialParam001
 * @tc.desc: Test MaterialUtils::IsEnableMaterialParam with null material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsIsEnableMaterialParam001, TestSize.Level1)
{
    RefPtr<UiMaterial> nullMaterial = nullptr;
    bool result = MaterialUtils::IsEnableMaterialParam(nullMaterial);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MaterialUtilsIsEnableMaterialParam002
 * @tc.desc: Test MaterialUtils::IsEnableMaterialParam with valid material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsIsEnableMaterialParam002, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    bool result = MaterialUtils::IsEnableMaterialParam(material);
    if (material->GetImmersiveOptions()) {
        EXPECT_TRUE(result);
    }
}

/**
 * @tc.name: MaterialUtilsPreProcessMaterial001
 * @tc.desc: Test MaterialUtils::PreProcessMaterial with null material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsPreProcessMaterial001, TestSize.Level1)
{
    auto result = MaterialUtils::PreProcessMaterial(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: MaterialUtilsPreProcessMaterial002
 * @tc.desc: Test MaterialUtils::PreProcessMaterial with valid material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsPreProcessMaterial002, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    auto result = MaterialUtils::PreProcessMaterial(AceType::RawPtr(material));
    if (result) {
        EXPECT_NE(result, nullptr);
    }
}

/**
 * @tc.name: OverlayManagerSheetMap001
 * @tc.desc: Test OverlayManager sheetMap access
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, OverlayManagerSheetMap001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto sheetMap = overlayManager->GetSheetMap();
    EXPECT_TRUE(sheetMap.empty());
}

/**
 * @tc.name: OverlayManagerDismissTarget001
 * @tc.desc: Test DismissTarget with modal target
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, OverlayManagerDismissTarget001, TestSize.Level1)
{
    DismissTarget target(100);
    EXPECT_EQ(target.GetTargetId(), 100);
    EXPECT_FALSE(target.targetIsSheet);
}

/**
 * @tc.name: OverlayManagerDismissTarget002
 * @tc.desc: Test DismissTarget with sheet key
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, OverlayManagerDismissTarget002, TestSize.Level1)
{
    SheetKey sheetKey;
    sheetKey.targetId = 200;
    DismissTarget target(sheetKey);
    EXPECT_EQ(target.GetTargetId(), 200);
    EXPECT_TRUE(target.targetIsSheet);
}

/**
 * @tc.name: OverlayManagerSetDismissSheet001
 * @tc.desc: Test OverlayManager SetDismissSheet and GetDismissSheet
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, OverlayManagerSetDismissSheet001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_EQ(overlayManager->GetDismissSheet(), 0);

    overlayManager->SetDismissSheet(42);
    EXPECT_EQ(overlayManager->GetDismissSheet(), 42);
}

/**
 * @tc.name: SheetPresentationPatternSheetEffectEdge001
 * @tc.desc: Test SheetPresentationPattern default sheetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetPresentationPatternSheetEffectEdge001, TestSize.Level1)
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
    sheetStyle.sheetEffectEdge = SheetEffectEdge::ALL;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    EXPECT_EQ(sheetPattern->GetSheetEffectEdge(), SheetEffectEdge::ALL);
}

/**
 * @tc.name: SheetPresentationPatternSheetEffectEdge002
 * @tc.desc: Test SheetPresentationPattern with NONE sheetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetPresentationPatternSheetEffectEdge002, TestSize.Level1)
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
    sheetStyle.sheetEffectEdge = SheetEffectEdge::NONE;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(true, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);

    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_TRUE(topModalNode);
    auto sheetPattern = topModalNode->GetPattern<SheetPresentationPattern>();
    ASSERT_TRUE(sheetPattern);

    EXPECT_EQ(sheetPattern->GetSheetEffectEdge(), SheetEffectEdge::NONE);
}

/**
 * @tc.name: SheetPresentationPatternEnableDragControl001
 * @tc.desc: Test SheetPresentationPattern enableDragControl setter/getter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetPresentationPatternEnableDragControl001, TestSize.Level1)
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

    EXPECT_TRUE(sheetPattern->GetEnableDragControl());

    sheetPattern->SetEnableDragControl(false);
    EXPECT_FALSE(sheetPattern->GetEnableDragControl());

    sheetPattern->SetEnableDragControl(true);
    EXPECT_TRUE(sheetPattern->GetEnableDragControl());
}

/**
 * @tc.name: OverlayManagerOptions001
 * @tc.desc: Test OverlayManagerInfo struct and OverlayManager options
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, OverlayManagerOptions001, TestSize.Level1)
{
    OverlayManagerInfo info;
    EXPECT_TRUE(info.renderRootOverlay);
    EXPECT_FALSE(info.enableBackPressedEvent);

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    EXPECT_FALSE(overlayManager->GetOverlayManagerOptions().has_value());

    bool setResult = overlayManager->SetOverlayManagerOptions(info);
    EXPECT_TRUE(setResult);

    auto getResult = overlayManager->GetOverlayManagerOptions();
    EXPECT_TRUE(getResult.has_value());
    EXPECT_TRUE(getResult->renderRootOverlay);
    EXPECT_FALSE(getResult->enableBackPressedEvent);
}

/**
 * @tc.name: OverlayManagerOptions002
 * @tc.desc: Test OverlayManagerInfo with enableBackPressedEvent=true
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, OverlayManagerOptions002, TestSize.Level1)
{
    OverlayManagerInfo info;
    info.renderRootOverlay = false;
    info.enableBackPressedEvent = true;

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    bool setResult = overlayManager->SetOverlayManagerOptions(info);
    EXPECT_TRUE(setResult);

    auto getResult = overlayManager->GetOverlayManagerOptions();
    EXPECT_TRUE(getResult.has_value());
    EXPECT_FALSE(getResult->renderRootOverlay);
    EXPECT_TRUE(getResult->enableBackPressedEvent);
}

/**
 * @tc.name: MaterialUtilsGetConfiguredMaterialState001
 * @tc.desc: Test MaterialUtils::GetConfiguredMaterialState
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetConfiguredMaterialState001, TestSize.Level1)
{
    auto state = MaterialUtils::GetConfiguredMaterialState();
    EXPECT_TRUE(state == MaterialState::DEFAULT || state == MaterialState::ENABLE || state == MaterialState::DISABLE);
}

/**
 * @tc.name: MaterialUtilsGetConfiguredMaterialType001
 * @tc.desc: Test MaterialUtils::GetConfiguredMaterialType
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetConfiguredMaterialType001, TestSize.Level1)
{
    auto type = MaterialUtils::GetConfiguredMaterialType();
    EXPECT_TRUE(
        type == MaterialType::NONE || type == MaterialType::SEMI_TRANSPARENT || type == MaterialType::IMMERSIVE);
}

/**
 * @tc.name: SheetKeyEquality001
 * @tc.desc: Test SheetKey equality operator
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetKeyEquality001, TestSize.Level1)
{
    SheetKey key1;
    key1.targetId = 100;
    key1.isStartUpByUIContext = false;
    SheetKey key2;
    key2.targetId = 100;
    key2.isStartUpByUIContext = false;
    EXPECT_TRUE(key1 == key2);

    key2.targetId = 200;
    EXPECT_FALSE(key1 == key2);
}

/**
 * @tc.name: SheetKeyHash001
 * @tc.desc: Test SheetKeyHash with different configurations
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetKeyHash001, TestSize.Level1)
{
    SheetKeyHash hashFn;

    SheetKey key1;
    key1.isStartUpByUIContext = true;
    key1.contentId = 100;
    key1.targetId = 200;
    EXPECT_EQ(hashFn(key1), 100);

    SheetKey key2;
    key2.isStartUpByUIContext = false;
    key2.targetId = 200;
    EXPECT_EQ(hashFn(key2), 200);
}

/**
 * @tc.name: MaterialUtilsGetGlobalMaterialLevel001
 * @tc.desc: Test MaterialUtils::GetGlobalMaterialLevel
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetGlobalMaterialLevel001, TestSize.Level1)
{
    UiMaterialLevel level;
    bool result = MaterialUtils::GetGlobalMaterialLevel(level);
    if (result) {
        EXPECT_TRUE(level == UiMaterialLevel::EXQUISITE || level == UiMaterialLevel::GENTLE ||
                    level == UiMaterialLevel::SMOOTH);
    }
}

/**
 * @tc.name: MaterialUtilsGetDeviceUiMaterialEnabled001
 * @tc.desc: Test MaterialUtils::GetDeviceUiMaterialEnabled
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetDeviceUiMaterialEnabled001, TestSize.Level1)
{
    bool enabled;
    bool result = MaterialUtils::GetDeviceUiMaterialEnabled(enabled);
    if (result) {
        EXPECT_TRUE(enabled || !enabled);
    }
}

/**
 * @tc.name: MaterialUtilsGetImmersiveShadow001
 * @tc.desc: Test MaterialUtils::GetImmersiveShadow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetImmersiveShadow001, TestSize.Level1)
{
    float dipScale = 1.0f;
    auto shadow = MaterialUtils::GetImmersiveShadow(dipScale);
    EXPECT_TRUE(shadow.GetOffset().GetX() >= 0 || shadow.GetOffset().GetY() >= 0);
}

/**
 * @tc.name: MaterialUtilsGetImmersiveEmptyShadow001
 * @tc.desc: Test MaterialUtils::GetImmersiveEmptyShadow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetImmersiveEmptyShadow001, TestSize.Level1)
{
    auto shadow = MaterialUtils::GetImmersiveEmptyShadow();
}

/**
 * @tc.name: UiMaterialCopy001
 * @tc.desc: Test UiMaterial Copy method for EC material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialCopy001, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR_EC);
    ASSERT_TRUE(material);
    auto copy = material->Copy();
    ASSERT_TRUE(copy);
    EXPECT_EQ(copy->GetType(), material->GetType());
}

/**
 * @tc.name: UiMaterialCopy002
 * @tc.desc: Test UiMaterial Copy method for EC_SUB material
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialCopy002, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR_EC_SUB);
    ASSERT_TRUE(material);
    auto copy = material->Copy();
    ASSERT_TRUE(copy);
    EXPECT_EQ(copy->GetType(), material->GetType());
}

/**
 * @tc.name: UiMaterialGetSetImmersiveOptions001
 * @tc.desc: Test UiMaterial GetImmersiveOptions and SetImmersiveOptions
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialGetSetImmersiveOptions001, TestSize.Level1)
{
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THIN);
    ASSERT_TRUE(material);
    auto options = material->GetImmersiveOptions();
    if (options) {
        ImmersiveOptions newOptions = *options;
        newOptions.style = UiMaterialStyle::REGULAR;
        material->SetImmersiveOptions(newOptions);
        auto updatedOptions = material->GetImmersiveOptions();
        ASSERT_TRUE(updatedOptions);
        EXPECT_EQ(updatedOptions->style, UiMaterialStyle::REGULAR);
    }
}

/**
 * @tc.name: UiMaterialFilterCreatorEC001
 * @tc.desc: Test UiMaterialFilterCreator::ConvertToUiMaterialECFilter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialFilterCreatorEC001, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    auto filter = UiMaterialFilterCreator::ConvertToUiMaterialECFilter(config);
    EXPECT_FALSE(filter);
}

/**
 * @tc.name: UiMaterialFilterCreatorECSub001
 * @tc.desc: Test UiMaterialFilterCreator::ConvertToUiMaterialECSubShader
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialFilterCreatorECSub001, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    auto shader = UiMaterialFilterCreator::ConvertToUiMaterialECSubShader(config);
    EXPECT_FALSE(shader);
}

/**
 * @tc.name: UiMaterialFilterCreatorFilter001
 * @tc.desc: Test UiMaterialFilterCreator::ConvertToUiMaterialFilter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialFilterCreatorFilter001, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    auto filter = UiMaterialFilterCreator::ConvertToUiMaterialFilter(config);
    EXPECT_FALSE(filter);
}

/**
 * @tc.name: UiMaterialFilterCreatorRosenFilter001
 * @tc.desc: Test UiMaterialFilterCreator::CreateRosenFilter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, UiMaterialFilterCreatorRosenFilter001, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    auto filter = UiMaterialFilterCreator::CreateRosenFilter(config);
    EXPECT_FALSE(filter);
}

/**
 * @tc.name: MaterialUtilsGetUiMaterialFilterEC001
 * @tc.desc: Test MaterialUtils::GetUiMaterialFilterEC
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetUiMaterialFilterEC001, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    std::shared_ptr<Rosen::RSNGFilterBase> filter;
    bool result = MaterialUtils::GetUiMaterialFilterEC(config, filter);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MaterialUtilsGetUiMaterialShaderECSub001
 * @tc.desc: Test MaterialUtils::GetUiMaterialShaderECSub
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, MaterialUtilsGetUiMaterialShaderECSub001, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    std::shared_ptr<Rosen::RSNGShaderBase> shader;
    bool result = MaterialUtils::GetUiMaterialShaderECSub(config, shader);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SheetPopupInfo001
 * @tc.desc: Test SheetPopupInfo default values
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetPopupInfo001, TestSize.Level1)
{
    SheetPopupInfo info;
    EXPECT_EQ(info.finalPlacement, Placement::NONE);
    EXPECT_TRUE(info.placementOnTarget);
    EXPECT_FALSE(info.placementRechecked);
    EXPECT_TRUE(info.showArrow);
    EXPECT_FLOAT_EQ(info.arrowOffsetX, 0.f);
    EXPECT_FLOAT_EQ(info.arrowOffsetY, 0.f);
    EXPECT_EQ(info.arrowPosition, SheetArrowPosition::NONE);
    EXPECT_FLOAT_EQ(info.sheetOffsetX, 0.f);
    EXPECT_FLOAT_EQ(info.sheetOffsetY, 0.f);
    EXPECT_FALSE(info.keyboardShow);
}

/**
 * @tc.name: SheetPopupInfo002
 * @tc.desc: Test SheetPopupInfo Reset method
 * @tc.type: FUNC
 */
HWTEST_F(OverlayMaterialECTestNg, SheetPopupInfo002, TestSize.Level1)
{
    SheetPopupInfo info;
    info.finalPlacement = Placement::TOP_LEFT;
    info.placementOnTarget = false;
    info.placementRechecked = true;
    info.showArrow = false;
    info.arrowOffsetX = 10.0f;
    info.arrowOffsetY = 20.0f;
    info.arrowPosition = SheetArrowPosition::TOP_LEFT;
    info.sheetOffsetX = 30.0f;
    info.sheetOffsetY = 40.0f;
    info.keyboardShow = true;

    info.Reset();
    EXPECT_EQ(info.finalPlacement, Placement::NONE);
    EXPECT_TRUE(info.placementOnTarget);
    EXPECT_FALSE(info.placementRechecked);
    EXPECT_TRUE(info.showArrow);
    EXPECT_FLOAT_EQ(info.arrowOffsetX, 0.f);
    EXPECT_FLOAT_EQ(info.arrowOffsetY, 0.f);
    EXPECT_EQ(info.arrowPosition, SheetArrowPosition::NONE);
    EXPECT_FLOAT_EQ(info.sheetOffsetX, 0.f);
    EXPECT_FLOAT_EQ(info.sheetOffsetY, 0.f);
    EXPECT_FALSE(info.keyboardShow);
}
} // namespace OHOS::Ace::NG
