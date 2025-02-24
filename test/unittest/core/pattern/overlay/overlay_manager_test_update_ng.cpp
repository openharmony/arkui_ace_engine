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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_method.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::BorderWidthProperty BORDER_WIDTH_TEST = { 1.0_vp, 1.0_vp, 1.0_vp, 0.0_vp };
const NG::BorderStyleProperty BORDER_STYLE_TEST = {BorderStyle::SOLID,
    BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID};
const NG::BorderColorProperty BORDER_COLOR_TEST = { Color::BLUE,
    Color::BLUE, Color::BLUE, Color::BLUE };
const NG::BorderWidthProperty NEW_BORDER_WIDTH_TEST = { 10.0_vp, 15.0_vp, 5.0_vp, 0.0_vp };
const NG::BorderStyleProperty NEW_BORDER_STYLE_TEST = {BorderStyle::SOLID,
    BorderStyle::DASHED, BorderStyle::DOTTED, BorderStyle::NONE};
const NG::BorderColorProperty NEW_BORDER_COLOR_TEST = { Color::RED,
    Color::GREEN, Color::GRAY, Color::BLACK };
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace

class OverlayManagerTestUpdateNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    int32_t minPlatformVersion_ = 0;
};

void OverlayManagerTestUpdateNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayManagerTestUpdateNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void OverlayManagerTestUpdateNg::SetUpTestCase()
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
        if (type == DragBarTheme::TypeId()) {
            return AceType::MakeRefPtr<DragBarTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return AceType::MakeRefPtr<PickerTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == MenuTheme::TypeId()) {
            return AceType::MakeRefPtr<MenuTheme>();
        } else if (type == ToastTheme::TypeId()) {
            return AceType::MakeRefPtr<ToastTheme>();
        } else if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void OverlayManagerTestUpdateNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void OverlayManagerTestUpdateNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme.Upgrade();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

RefPtr<FrameNode> OverlayManagerTestUpdateNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayManagerTestUpdateNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayManagerTestUpdateNg::CreateSheetBuilder()
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}

/**
 * @tc.name: OnBindSheet001
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    Dimension width{ 300, DimensionUnit::VP };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::VP };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet002
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    Dimension width{ 300, DimensionUnit::VP };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::VP };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet003
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    Dimension width{ 300, DimensionUnit::VP };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::VP };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet004
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    Dimension width{ 300, DimensionUnit::FP };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::FP };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet005
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    Dimension width{ 300, DimensionUnit::FP };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::FP };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet006
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    Dimension width{ 300, DimensionUnit::FP };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::FP };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet007
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    Dimension width{ 300, DimensionUnit::PX };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::PX };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet008
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    Dimension width{ 300, DimensionUnit::PX };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::PX };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet009
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle width.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle width.
     * @tc.expected: the sheetStyle width is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    Dimension width{ 300, DimensionUnit::PX };
    sheetStyle.width = width;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), width);

    Dimension widthNew{ 400, DimensionUnit::PX };
    sheetStyle.width = widthNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->width.value(), widthNew);
}

/**
 * @tc.name: OnBindSheet010
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle shadow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackShadow().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle shadow.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    Shadow shadow = ShadowConfig::DefaultShadowL;
    sheetStyle.shadow = shadow;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadow);

    Shadow shadowNew = ShadowConfig::NoneShadow;
    sheetStyle.shadow = shadowNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadowNew);
}

/**
 * @tc.name: OnBindSheet011
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle shadow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackShadow().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle shadow.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    Shadow shadow = ShadowConfig::DefaultShadowL;
    sheetStyle.shadow = shadow;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadow);

    Shadow shadowNew = ShadowConfig::NoneShadow;
    sheetStyle.shadow = shadowNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadowNew);
}

/**
 * @tc.name: OnBindSheet012
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle shadow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackShadow().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle shadow.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    Shadow shadow = ShadowConfig::DefaultShadowL;
    sheetStyle.shadow = shadow;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadow);

    Shadow shadowNew = ShadowConfig::NoneShadow;
    sheetStyle.shadow = shadowNew;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadowNew);
}

/**
 * @tc.name: OnBindSheet013
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOM. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.borderWidth = BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), BORDER_WIDTH_TEST);

    sheetStyle.borderWidth = NEW_BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), NEW_BORDER_WIDTH_TEST);
}

/**
 * @tc.name: OnBindSheet014
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderColor().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOM. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.borderColor = BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), BORDER_COLOR_TEST);

    sheetStyle.borderColor = NEW_BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), NEW_BORDER_COLOR_TEST);
}

/**
 * @tc.name: OnBindSheet015
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderStyle().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOM. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.borderStyle = BORDER_STYLE_TEST;
    sheetStyle.backgroundColor = Color::BLUE;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), BORDER_STYLE_TEST);

    sheetStyle.borderStyle = NEW_BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), NEW_BORDER_STYLE_TEST);
}

/**
 * @tc.name: OnBindSheet016
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOM. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.backgroundColor = Color::BLUE;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);

    sheetStyle.backgroundColor = Color::GRAY;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::GRAY);
}

/**
 * @tc.name: OnBindSheet017
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.borderWidth = BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), BORDER_WIDTH_TEST);

    sheetStyle.borderWidth = NEW_BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), NEW_BORDER_WIDTH_TEST);
}

/**
 * @tc.name: OnBindSheet018
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderColor().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.borderColor = BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), BORDER_COLOR_TEST);

    sheetStyle.borderColor = NEW_BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), NEW_BORDER_COLOR_TEST);
}

/**
 * @tc.name: OnBindSheet019
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderStyle().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.borderStyle = BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), BORDER_STYLE_TEST);

    sheetStyle.borderStyle = NEW_BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), NEW_BORDER_STYLE_TEST);
}

/**
 * @tc.name: OnBindSheet020
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_CENTER. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.backgroundColor = Color::BLUE;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);

    sheetStyle.backgroundColor = Color::GRAY;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::GRAY);
}

/**
 * @tc.name: OnBindSheet021
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    sheetStyle.borderWidth = BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), BORDER_WIDTH_TEST);

    sheetStyle.borderWidth = NEW_BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), NEW_BORDER_WIDTH_TEST);
}

/**
 * @tc.name: OnBindSheet022
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderColor().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    sheetStyle.borderColor = BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), BORDER_COLOR_TEST);

    sheetStyle.borderColor = NEW_BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), NEW_BORDER_COLOR_TEST);
}

/**
 * @tc.name: OnBindSheet023
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderStyle().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    sheetStyle.borderStyle = BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), BORDER_STYLE_TEST);

    sheetStyle.borderStyle = NEW_BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), NEW_BORDER_STYLE_TEST);
}

/**
 * @tc.name: OnBindSheet024
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_POPUP. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    sheetStyle.backgroundColor = Color::BLUE;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);

    sheetStyle.backgroundColor = Color::GRAY;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::GRAY);
}

/**
 * @tc.name: OnBindSheet025
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetStyle.borderWidth = BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), BORDER_WIDTH_TEST);

    sheetStyle.borderWidth = NEW_BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), NEW_BORDER_WIDTH_TEST);
}

/**
 * @tc.name: OnBindSheet026
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderColor().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetStyle.borderColor = BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), BORDER_COLOR_TEST);

    sheetStyle.borderColor = NEW_BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), NEW_BORDER_COLOR_TEST);
}

/**
 * @tc.name: OnBindSheet027
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderStyle().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetStyle.borderStyle = BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), BORDER_STYLE_TEST);

    sheetStyle.borderStyle = NEW_BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), NEW_BORDER_STYLE_TEST);
}

/**
 * @tc.name: OnBindSheet028
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    
    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOMLANDSPACE. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetStyle.backgroundColor = Color::BLUE;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);

    sheetStyle.backgroundColor = Color::GRAY;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::GRAY);
}

/**
 * @tc.name: OnBindSheet029
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOM_FREE_WINDOW. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    sheetStyle.borderWidth = BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), BORDER_WIDTH_TEST);

    sheetStyle.borderWidth = NEW_BORDER_WIDTH_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderWidth().value(), NEW_BORDER_WIDTH_TEST);
}

/**
 * @tc.name: OnBindSheet030
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderColor().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOM_FREE_WINDOW. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    sheetStyle.borderColor = BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), BORDER_COLOR_TEST);

    sheetStyle.borderColor = NEW_BORDER_COLOR_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderColor().value(), NEW_BORDER_COLOR_TEST);
}

/**
 * @tc.name: OnBindSheet031
 * @tc.desc: Test OverlayManager::OnBindSheet change sheetStyle border.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderStyle().has_value(), false);

    /**
     * @tc.steps: step3. Set sheetType = SHEET_BOTTOM_FREE_WINDOW. Change the sheetStyle border.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    sheetStyle.borderStyle = BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), BORDER_STYLE_TEST);

    sheetStyle.borderStyle = NEW_BORDER_STYLE_TEST;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBorderStyle().value(), NEW_BORDER_STYLE_TEST);
}

/**
 * @tc.name: OnBindSheet032
 * @tc.desc: Test OverlayManager::OnBindSheet closeIcon test.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, OnBindSheet032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    /**
     * @tc.steps: step2. create sheetNode.
     * @tc.expected: closeIcon is Image.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto buttonNode = sheetNode->GetChildAtIndex(2);
    ASSERT_NE(buttonNode, nullptr);
    auto iconNode = buttonNode->GetChildAtIndex(0);
    ASSERT_NE(iconNode, nullptr);
    ASSERT_EQ(iconNode->GetTag(), V2::IMAGE_ETS_TAG);
    /**
     * @tc.steps: step3. Change SDK Version.
     * @tc.expected: closeIcon is Symbol.
     */
    auto newTargetNode = CreateTargetNode();
    newTargetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        newTargetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    buttonNode = sheetNode->GetChildAtIndex(2);
    ASSERT_NE(buttonNode, nullptr);
    iconNode = buttonNode->GetChildAtIndex(0);
    ASSERT_NE(iconNode, nullptr);
    ASSERT_EQ(iconNode->GetTag(), V2::SYMBOL_ETS_TAG);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));
}

/**
 * @tc.name: UpdateSheetRender001
 * @tc.desc: Test OverlayManager::UpdateSheetRender shadow update.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestUpdateNg, UpdateSheetRender001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    sheetStyle.shadow.reset();
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackShadow().has_value(), false);
    /**
     * @tc.steps: step3. Change the SheetTheme shadow.
     * @tc.expected: the shadow is updated successfully from shadow theme
     */
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    sheetTheme->sheetShadowConfig_ = static_cast<int>(ShadowStyle::OuterFloatingMD);
    OverlayManagerTestUpdateNg::SetSheetTheme(sheetTheme);
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    auto shadowTheme = AceType::MakeRefPtr<ShadowTheme>();
    EXPECT_CALL(*themeManager, GetTheme(ShadowTheme::TypeId())).WillRepeatedly(Return(shadowTheme));
    overlayManager->UpdateSheetRender(sheetNode, sheetStyle, false);
    EXPECT_EQ(renderContext->GetBackShadow().has_value(), true);
    Shadow shadow = shadowTheme->GetShadow(ShadowStyle::OuterFloatingMD, SystemProperties::GetColorMode());
    EXPECT_EQ(renderContext->GetBackShadow().value(), shadow);
}

} // namespace OHOS::Ace::NG