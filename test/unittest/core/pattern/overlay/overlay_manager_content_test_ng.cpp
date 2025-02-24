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

#include "base/error/error_code.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/log/dump_log.h"
#include "base/window/foldable_window.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
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
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";

constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;

const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace
class OverlayManagerContentTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    DatePickerSettingData GenDatePickerSettingData();
};

void OverlayManagerContentTestNg::SetUpTestCase()
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
        } else if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void OverlayManagerContentTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayManagerContentTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayManagerContentTestNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayManagerContentTestNg::CreateSheetBuilder()
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}
DatePickerSettingData OverlayManagerContentTestNg::GenDatePickerSettingData()
{
    DatePickerSettingData datePickerSettingData;
    datePickerSettingData.isLunar = false;
    datePickerSettingData.showTime = false;
    datePickerSettingData.useMilitary = false;

    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(0);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.normalTextStyle_.textColor = Color::BLACK;
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    datePickerSettingData.properties = properties;
    datePickerSettingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    datePickerSettingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    datePickerSettingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    datePickerSettingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    return datePickerSettingData;
}

/**
 * @tc.name: OnBindContentCover006
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover006, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step4. set the onWillDismiss and transitionEffect.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, contentCoverParam, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}

/**
 * @tc.name: OnBindContentCover007
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover007, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    overlayManager->DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. call RemoveModal.
     * @tc.expected: modal node is nullptr
     */
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->ModalInteractiveDismiss();
    targetId = topModalPattern->GetTargetId();
    EXPECT_NE(overlayManager->GetModal(targetId), nullptr);
    overlayManager->RemoveModal(targetId);
    EXPECT_EQ(overlayManager->GetModal(targetId), nullptr);
}

/**
 * @tc.name: OnBindContentCover008
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover008, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step4. set the onWillDismiss and transitionEffect.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, contentCoverParam, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}

/**
 * @tc.name: OnBindContentCover009
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover009, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    overlayManager->DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. call RemoveModal.
     * @tc.expected: modal node is nullptr
     */
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->ModalInteractiveDismiss();
    targetId = topModalPattern->GetTargetId();
    EXPECT_NE(overlayManager->GetModal(targetId), nullptr);
    overlayManager->RemoveModal(targetId);
    EXPECT_EQ(overlayManager->GetModal(targetId), nullptr);
}

/**
 * @tc.name: OnBindContentCover010
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover010, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ATTRS_ALIGN_ITEMS,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step4. set the onWillDismiss and transitionEffect.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, contentCoverParam, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}

/**
 * @tc.name: OnBindContentCover011
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover011, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ATTRS_ALIGN_ITEMS,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    overlayManager->DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. call RemoveModal.
     * @tc.expected: modal node is nullptr
     */
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->ModalInteractiveDismiss();
    targetId = topModalPattern->GetTargetId();
    EXPECT_NE(overlayManager->GetModal(targetId), nullptr);
    overlayManager->RemoveModal(targetId);
    EXPECT_EQ(overlayManager->GetModal(targetId), nullptr);
}

/**
 * @tc.name: OnBindContentCover012
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover012, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step4. set the onWillDismiss and transitionEffect.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, contentCoverParam, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}

/**
 * @tc.name: OnBindContentCover013
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover013, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    overlayManager->DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. call RemoveModal.
     * @tc.expected: modal node is nullptr
     */
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->ModalInteractiveDismiss();
    targetId = topModalPattern->GetTargetId();
    EXPECT_NE(overlayManager->GetModal(targetId), nullptr);
    overlayManager->RemoveModal(targetId);
    EXPECT_EQ(overlayManager->GetModal(targetId), nullptr);
}

/**
 * @tc.name: OnBindContentCover014
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover014, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step4. set the onWillDismiss and transitionEffect.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, contentCoverParam, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}

/**
 * @tc.name: OnBindContentCover015
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover015, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    overlayManager->DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. call RemoveModal.
     * @tc.expected: modal node is nullptr
     */
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->ModalInteractiveDismiss();
    targetId = topModalPattern->GetTargetId();
    EXPECT_NE(overlayManager->GetModal(targetId), nullptr);
    overlayManager->RemoveModal(targetId);
    EXPECT_EQ(overlayManager->GetModal(targetId), nullptr);
}

/**
 * @tc.name: OnBindContentCover016
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover016, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ATTRS_ALIGN_ITEMS,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step4. set the onWillDismiss and transitionEffect.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, contentCoverParam, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}

/**
 * @tc.name: OnBindContentCover017
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover017, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ATTRS_ALIGN_ITEMS,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    overlayManager->DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. call RemoveModal.
     * @tc.expected: modal node is nullptr
     */
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->ModalInteractiveDismiss();
    targetId = topModalPattern->GetTargetId();
    EXPECT_NE(overlayManager->GetModal(targetId), nullptr);
    overlayManager->RemoveModal(targetId);
    EXPECT_EQ(overlayManager->GetModal(targetId), nullptr);
}

/**
 * @tc.name: OnBindContentCover018
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover018, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ATTRS_ALIGN_ITEMS,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step4. set the onWillDismiss and transitionEffect.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, contentCoverParam, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}

/**
 * @tc.name: OnBindContentCover019
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerContentTestNg, OnBindContentCover019, TestSize.Level1)
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
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ATTRS_ALIGN_ITEMS,
                ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    overlayManager->DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. call RemoveModal.
     * @tc.expected: modal node is nullptr
     */
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->ModalInteractiveDismiss();
    targetId = topModalPattern->GetTargetId();
    EXPECT_NE(overlayManager->GetModal(targetId), nullptr);
    overlayManager->RemoveModal(targetId);
    EXPECT_EQ(overlayManager->GetModal(targetId), nullptr);
}
} // namespace OHOS::Ace::NG
