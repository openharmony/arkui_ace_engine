/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
const OffsetF MENU_OFFSET(10.0, 10.0);
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
const std::string MENU_CONTENT = "复制";
constexpr int32_t OVERLAY_EXISTS = 0;
} // namespace
class OverlayTestNg : public testing::Test {
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

void OverlayTestNg::SetUpTestCase()
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
void OverlayTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayTestNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayTestNg::CreateSheetBuilder()
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
DatePickerSettingData OverlayTestNg::GenDatePickerSettingData()
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
    properties.normalTextStyle_.fontSize = Dimension(10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(15);
    properties.selectedTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    datePickerSettingData.properties = properties;
    datePickerSettingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    datePickerSettingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    datePickerSettingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    datePickerSettingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    return datePickerSettingData;
}
/**
 * @tc.name: PopupTest001
 * @tc.desc: Test OverlayManager::ShowPopup.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, PopupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;

    /**
     * @tc.steps: step2. create overlayManager and call HidePopup.
     * @tc.expected: popupMap's data is updated successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    popupNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->HidePopup(targetId, popupInfo);
    EXPECT_FALSE(overlayManager->popupMap_[targetId].isCurrentOnShow);

    /**
     * @tc.steps: step3. call HidePopup, ErasePopup, HideAllPopups
     * @tc.expected: popupMap's data is updated successfully
     */
    overlayManager->HidePopup(targetId, popupInfo);
    EXPECT_FALSE(overlayManager->popupMap_[targetId].markNeedUpdate);
    overlayManager->ErasePopup(targetId);
    overlayManager->HideAllPopups();
    EXPECT_TRUE(overlayManager->popupMap_.empty());
}

/**
 * @tc.name: OnBindContentCover001
 * @tc.desc: Test OverlayManager::OnBindContentCover create modal node.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OnBindContentCover001, TestSize.Level1)
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
     * @tc.steps: step2. create target node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related function is called.
     */
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::NONE;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    overlayManager->PlayDefaultModalTransition(rootNode, false);
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(topModalPattern, nullptr);
    overlayManager->ModalExitProcess(topModalNode);
    overlayManager->PlayDefaultModalTransition(topModalNode, false);
    auto type = topModalPattern->GetType();
    EXPECT_EQ(type, ModalTransition::NONE);
}

/**
 * @tc.name: OnBindContentCover002
 * @tc.desc: Test OverlayManager::OnBindContentCover change ModalTransition dynamically.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OnBindContentCover002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(1.0, 1.0));
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->stageManager_->stageNode_ = stageNode;

    /**
     * @tc.steps: step2. create target node.
     */
    CreateSheetBuilder();
    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related function is called.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    auto onWillAppear = []() {};
    auto onAppear = []() {};
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc_), modalStyle, onAppear, nullptr,
        onWillAppear, nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(topModalPattern, nullptr);
    auto type = topModalPattern->GetType();
    EXPECT_EQ(type, ModalTransition::DEFAULT);

    /**
     * @tc.steps: step4. Change the ModalTransition.
     * @tc.expected: the ModalTransition is updated successfully
     */
    modalStyle.modalTransition = ModalTransition::NONE;
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc_), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_NE(topModalNode, nullptr);
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(topModalPattern, nullptr);
    type = topModalPattern->GetType();
    EXPECT_EQ(type, ModalTransition::NONE);

    /**
     * @tc.steps: step5. Change the backgroundColor.
     * @tc.expected: the backgroundColor is updated successfully
     */
    modalStyle.backgroundColor = Color::GREEN;
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc_), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_NE(topModalNode, nullptr);
    EXPECT_EQ(topModalNode->GetRenderContext()->GetBackgroundColorValue(), Color::GREEN);
    overlayManager->OnBindContentCover(
        !isShow, nullptr, nullptr, modalStyle, nullptr, nullptr, nullptr, nullptr, ContentCoverParam(), targetNode);
}

/**
 * @tc.name: OnBindContentCover003
 * @tc.desc: Test OverlayManager::OnBindContentCover destroy modal node.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OnBindContentCover003, TestSize.Level1)
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
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node.
     */
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::NONE;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. destroy modal page.
     * @tc.expected: destroy successfully
     */
    auto onWillDisappear = []() {};
    auto onDisappear = []() {};
    overlayManager->OnBindContentCover(!isShow, nullptr, nullptr, modalStyle, nullptr, onDisappear, nullptr,
        onWillDisappear, ContentCoverParam(), targetNode);
    EXPECT_TRUE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: OnBindContentCover004
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OnBindContentCover004, TestSize.Level1)
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
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
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
 * @tc.name: OnBindContentCover005
 * @tc.desc: Test OverlayManager::OnBindContentCover improvement supplement.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OnBindContentCover005, TestSize.Level1)
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
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
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
 * @tc.name: PopupTest003
 * @tc.desc: Test OverlayManager::HidePopup.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, PopupTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;

    /**
     * @tc.steps: step2. create overlayManager and call HidePopup.
     * @tc.expected: popupMap's data is updated successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    popupNode->MountToParent(rootNode);
    targetNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->HidePopup(targetId, popupInfo);
    overlayManager->BlurOverlayNode(rootNode);
    overlayManager->MarkDirty(rootNode->layoutProperty_->GetPropertyChangeFlag());
    EXPECT_FALSE(overlayManager->popupMap_[targetId].markNeedUpdate);
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find(rootChildren.begin(), rootChildren.end(), popupInfo.popupNode);
    EXPECT_TRUE(iter == rootChildren.end());
}

/**
 * @tc.name: PopupTest004
 * @tc.desc: Test OverlayManager::HideAllPopups when useCustom is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, PopupTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);

    /**
     * @tc.steps: step2. create overlayManager and call HideAllPopups when ShowInSubwindow is false.
     * @tc.expected: popupMap's data is updated successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowPopup(targetId, popupInfo);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId].markNeedUpdate);
    EXPECT_TRUE(rootNode->GetChildren().empty());
    /**
     * @tc.steps: step3. update ShowInSubwindow and call HideAllPopups again.
     * @tc.expected: popupMap's data is updated successfully
     */
    layoutProp->UpdateShowInSubWindow(true);
    overlayManager->ShowPopup(targetId, popupInfo);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetId].markNeedUpdate);

    /**
     * @tc.steps: step4. call ShowIndexerPopup and RemoveIndexerPopup.
     * @tc.expected: mount and remove successfully,Repeatedly calling the function exits normally
     */
    EXPECT_TRUE(overlayManager->customPopupMap_.empty());
    overlayManager->ShowIndexerPopup(targetId, popupNode);
    EXPECT_FALSE(overlayManager->customPopupMap_.empty());
    overlayManager->ShowIndexerPopup(targetId, popupNode);
    EXPECT_EQ(overlayManager->customPopupMap_[targetId], popupNode);
    overlayManager->RemoveIndexerPopup();
    EXPECT_TRUE(overlayManager->customPopupMap_.empty());
    overlayManager->RemoveIndexerPopup();
    EXPECT_TRUE(overlayManager->customPopupMap_.empty());

    /**
     * @tc.steps: step5. call ShowIndexerPopup and RemoveIndexerPopupById.
     * @tc.expected: mount and remove successfully,Repeatedly calling the function exits normally
     */
    EXPECT_TRUE(overlayManager->customPopupMap_.empty());
    overlayManager->ShowIndexerPopup(targetId, popupNode);
    EXPECT_FALSE(overlayManager->customPopupMap_.empty());
    overlayManager->ShowIndexerPopup(targetId, popupNode);
    EXPECT_EQ(overlayManager->customPopupMap_[targetId], popupNode);
    overlayManager->RemoveIndexerPopupById(targetId);
    EXPECT_TRUE(overlayManager->customPopupMap_.empty());
    overlayManager->RemoveIndexerPopupById(targetId);
    EXPECT_TRUE(overlayManager->customPopupMap_.empty());
}

/**
 * @tc.name: PopupTest005
 * @tc.desc: Test OverlayManager::CleanPopupInSubWindow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, PopupTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance , set two different menu_offset.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlay = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlay, nullptr);
    auto rootNode = AceType::DynamicCast<FrameNode>(overlay->GetRootNode().Upgrade());
    ASSERT_NE(rootNode, nullptr);
    rootNode->isLayoutComplete_ = true;

    /**
     * @tc.steps: step2. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    overlay->ShowPopup(targetId, popupInfo);
    overlay->CleanPopupInSubWindow();
    overlay->HideAllPopups();
    EXPECT_EQ(rootNode->GetChildren().size(), 1);
}

/**
 * @tc.name: PopupTest006
 * @tc.desc: Test OverlayManager::ShowPopup and HidePopup when hastransition is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, PopupTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isBlockEvent = false;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: visibility of layoutProperty is updated successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    rootNode->isLayoutComplete_ = true;
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    popupPattern->SetHasTransition(true);
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(popupParam, nullptr);
    popupPattern->SetPopupParam(popupParam);
    overlayManager->ShowPopup(targetId, popupInfo);
    EXPECT_TRUE(popupPattern->GetHasTransition());
    auto layoutProp1 = popupInfo.popupNode->GetLayoutProperty();
    EXPECT_EQ(layoutProp1->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: RemoveOverlayTest001
 * @tc.desc: Test OverlayManager::RemoveOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, RemoveOverlayTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;

    /**
     * @tc.steps: step2. create overlayManager and call removeOverlay when has one child.
     * @tc.expected: removing overlay failed
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->HidePopup(targetId, popupInfo);
    EXPECT_FALSE(overlayManager->popupMap_[targetId].markNeedUpdate);
    auto res = overlayManager->RemoveOverlay(false);
    EXPECT_FALSE(res);
    EXPECT_FALSE(overlayManager->RemoveOverlayInSubwindow());
}
/**
 * @tc.name: RemoveOverlayTest002
 * @tc.desc: Test OverlayManager::RemoveOverlay related functions.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, RemoveOverlayTest002, TestSize.Level1)
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
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;

    /**
     * @tc.steps: step2. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and call removeOverlay when modalStack is not empty.
     * @tc.expected: remove successfully.
     */
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::NONE;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    EXPECT_TRUE(overlayManager->RemoveOverlay(false));

    /**
     * @tc.steps: step4. Change the ModalTransition and Call RemoveModalInOverlay.
     * @tc.expected: remove successfully.
     */
    modalStyle.modalTransition = ModalTransition::ALPHA;
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_TRUE(overlayManager->RemoveModalInOverlay());
}

/**
 * @tc.name: RemoveModalInOverlay001
 * @tc.desc: Branch: if (modalStack_.empty())
 *           Condition: CHECK_NULL_RETURN(topModalNode, false)
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, RemoveModalInOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and rootNode.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;

    /**
     * @tc.steps: step2. create overlayManager, test RemoveModalInOverlay function.
     * @tc.expected: modalstack_ is empty.
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->modalStack_ = std::stack<WeakPtr<FrameNode>>();
    EXPECT_FALSE(overlayManager->RemoveModalInOverlay());
}

/**
 * @tc.name: GetModalStackTop001
 * @tc.desc: Branch: if (modalStack_.empty())
 *           Condition: modalStack_ = empty()
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, GetModalStackTop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and rootNode.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;

    /**
     * @tc.steps: step2. create overlayManager, test GetModalStackTop function.
     * @tc.expected: GetModalStackTop return nullptr.
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->modalStack_ = std::stack<WeakPtr<FrameNode>>();
    EXPECT_EQ(overlayManager->GetModalStackTop(), nullptr);
}

/**
 * @tc.name: RemoveOverlayTest003
 * @tc.desc:  Test OverlayManager::RemoveOverlay from atomicService.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, RemoveOverlayTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create atomicservice node.
     */
    auto atom = FrameNode::CreateFrameNode(V2::ATOMIC_SERVICE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto menuBarRow = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto stageNode = FrameNode::CreateFrameNode(
    V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    atom->AddChild(stageNode);
    atom->AddChild(menuBarRow);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetInstallationFree(1);
    /**
     * @tc.steps: step2. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    atom->MountToParent(rootNode);
    /**
     * @tc.steps: step3. showpopup node.
     */
    overlayManager->ShowPopup(targetId, popupInfo);
    /**
     * @tc.steps: step4. remove popupNode from atomicService.
     */
    auto res = overlayManager->RemoveOverlay(false);
    EXPECT_FALSE(res);
    EXPECT_EQ(overlayManager->RemoveOverlayInSubwindow(), OVERLAY_EXISTS);
}

/**
 * @tc.name: RemoveOverlayTest004
 * @tc.desc: Test OverlayManager::RemoveOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, RemoveOverlayTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);

    /**
     * @tc.steps: step2. create overlayManager and call HideAllPopups when ShowInSubwindow is false.
     * @tc.expected: popupMap's data is updated successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowPopup(targetId, popupInfo);

    /**
     * @tc.steps: step3. create overlayManager and call removeOverlay when has one child.
     * @tc.expected: removing overlay failed
     */
    EXPECT_FALSE(overlayManager->RemoveOverlay(false));
    EXPECT_FALSE(overlayManager->RemoveOverlayInSubwindow());
    EXPECT_TRUE(overlayManager->RemoveNonKeyboardOverlay(popupNode));
}

/**
 * @tc.name: GetOverlayFrameNode001
 * @tc.desc: Test OverlayManager::GetOverlayFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, GetOverlayFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateUseCustom(true);

    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: popupMap's data is updated successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowPopup(targetId, popupInfo);

    /**
     * @tc.steps: step3. call GetOverlayFrameNode when has one child.
     * @tc.expected: removing overlay failed
     */
    auto newNode = overlayManager->GetOverlayFrameNode();
    EXPECT_EQ(newNode, nullptr);
}

/**
 * @tc.name: GetOverlayFrameNode002
 * @tc.desc: Test OverlayManager::GetOverlayFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, GetOverlayFrameNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create atomicservice node.
     */
    auto atom = FrameNode::CreateFrameNode(V2::ATOMIC_SERVICE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto menuBarRow = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto stageNode = FrameNode::CreateFrameNode(
    V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    atom->AddChild(stageNode);
    atom->AddChild(menuBarRow);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetInstallationFree(1);

    /**
     * @tc.steps: step2. create target node and popupInfo.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    atom->MountToParent(rootNode);

    /**
     * @tc.steps: step3. showpopup node.
     */
    overlayManager->ShowPopup(targetId, popupInfo);

    /**
     * @tc.steps: step4. call GetOverlayFrameNode when has one child.
     * @tc.expected: removing overlay failed
     */
    auto newNode = overlayManager->GetOverlayFrameNode();
    EXPECT_EQ(newNode, nullptr);
}

/**
 * @tc.name: DialogTest001
 * @tc.desc: Test OverlayManager::ShowCustomDialog->CloseDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    /**
     * @tc.steps: step2. create overlayManager and call ShowCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step3. call DialogInMapHoldingFocus when dialogMap_ is not empty and focusHub is nullptr.
     * @tc.expected: return false
     */
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step4. call CloseDialog when dialogMap_ is not empty.
     * @tc.expected: remove successfully
     */
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step4. call CloseDialog again when dialogMap_ is empty.
     * @tc.expected: function exits normally
     */
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}
/**
 * @tc.name: DialogTest002
 * @tc.desc: Test OverlayManager::ShowDialog->RemoveOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogParam;
    dialogParam.isShowInSubWindow = true;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: dialogNode is created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialogNode = overlayManager->ShowDialog(dialogParam, nullptr, true);
    EXPECT_NE(dialogNode, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step3. create focusHub and call DialogInMapHoldingFocus when dialogMap_ is not empty.
     * @tc.expected: return true
     */
    auto eventHub = dialogNode->GetEventHub<DialogEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    dialogNode->eventHub_ = eventHub;
    EXPECT_TRUE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step3. call RemoveOverlayInSubwindow.
     * @tc.expected: remove successfully.
     */
    EXPECT_TRUE(overlayManager->RemoveOverlayInSubwindow());
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
}

/**
 * @tc.name: DialogTest003
 * @tc.desc: Test OverlayManager::ShowDateDialog->ShowTimeDialog->RemoveOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;

    auto datePickerSettingData = GenDatePickerSettingData();

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowDateDialog(
        dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step3. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);

    /**
     * @tc.steps: step4. call RemoveOverlay when dialogChildCount is 2
     * @tc.expected: remove lastChild successfully
     */
    EXPECT_TRUE(overlayManager->RemoveOverlay(false));
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step5. ShowTimeDialog again and call RemoveOverlay with isBackPressed
     * @tc.expected: remove  successfully
     */
    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    EXPECT_TRUE(overlayManager->RemoveOverlay(true));
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_TRUE(overlayManager->RemoveOverlay(true));
}

/**
 * @tc.name: OnDialogCloseEvent
 * @tc.desc: Test OverlayManager::OnDialogCloseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OnDialogCloseEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and toast node.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. create overlayManager and call ShowToast when rootElement is nullptr.
     * @tc.expected: toastMap_ is empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnDialogCloseEvent(dialogNode);
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());

    auto dialogPattern = dialogNode->GetPattern();
    EXPECT_FALSE(dialogPattern == nullptr);
    overlayManager->OnDialogCloseEvent(dialogNode);

    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    overlayManager->OnDialogCloseEvent(dialogNode);
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DialogTransitionTest001
 * @tc.desc: Test OverlayManager::ShowDialog->Set no transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTransitionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect is nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    EXPECT_EQ(transitionEffect, nullptr);
}

/**
 * @tc.name: DialogTransitionTest002
 * @tc.desc: Test OverlayManager::ShowDialog->Set symmetry transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTransitionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto opacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto scaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    opacityTransition->SetNext(scaleTransition);
    dialogProperties.transitionEffect = opacityTransition;

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    ASSERT_NE(transitionEffect, nullptr);
    auto dialogScaleTransition = transitionEffect->GetNext();
    ASSERT_NE(dialogScaleTransition, nullptr);
}

/**
 * @tc.name: DialogTransitionTest003
 * @tc.desc: Test OverlayManager::ShowDialog->Set asymmetric transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTransitionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);
}

/**
 * @tc.name: DialogTest004
 * @tc.desc: Test OverlayManager::GetDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. test OverlayManager.GetDialog function.
     * @tc.expected: overlayManager.dialog.id equal to GetDialog(dialogId).id.
     */
    int32_t dialogId = dialog->GetId();
    auto dialogNode = overlayManager->GetDialog(dialogId);
    CHECK_NULL_VOID(dialogNode);
    EXPECT_EQ(dialogId, dialogNode->GetId());
}

/**
 * @tc.name: DialogTest005
 * @tc.desc: Test OverlayManager::OpenCustomDialog->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogParam.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogParam;
    dialogParam.isShowInSubWindow = false;

    /**
     * @tc.steps: step2. create overlayManager and call OpenCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto callbackFunc = [overlayManager](int32_t dialogId) {
        /**
         * @tc.steps: step4. call CloseCustomDialog when dialogMap_ is not empty.
         * @tc.expected: remove successfully
         */
        overlayManager->CloseCustomDialog(dialogId);
        EXPECT_TRUE(overlayManager->dialogMap_.empty());

        /**
         * @tc.steps: step4. call CloseDialog again when dialogMap_ is empty.
         * @tc.expected: function exits normally
         */
        overlayManager->CloseCustomDialog(dialogId);
        EXPECT_TRUE(overlayManager->dialogMap_.empty());
    };

    overlayManager->OpenCustomDialog(dialogParam, callbackFunc);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DialogTest006
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create root node and dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogProperties;
    /**
     * @tc.steps: step2. Create overlayManager and call ShowDialog.
     */
    auto overlay = AceType::DynamicCast<FrameNode>(rootNode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    auto dialogMapSize = overlayManager->dialogMap_.size();
    /**
     * @tc.steps4: Call DismissDialog function.
     * @tc.expected: DismissDialog function is called.
     */
    ViewAbstract::DismissDialog();
    EXPECT_EQ(overlayManager->dialogMap_.size(), dialogMapSize - 1);
}

/**
 * @tc.name: DialogTest007
 * @tc.desc: Test OverlayManager::OpenCustomDialog->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    /**
     * @tc.steps: step2. create dialog content node.
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParam;
    dialogParam.contentNode = contentNode;
    auto contentNodeNew = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParamNew;
    dialogParamNew.contentNode = contentNodeNew;

    /**
     * @tc.steps: step3. call OpenCustomDialog for contentNode.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    auto openCallbackFst = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackFst);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    auto dialogNode = overlayManager->GetDialogNodeWithExistContent(contentNode);
    EXPECT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step4. call OpenCustomDialog for contentNode again.
     * @tc.expected: cannot open again and dialogMap_ is still 1.
     */
    auto openCallbackSnd = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackSnd);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step5. call CloseCustomDialog for contentNodeNew.
     * @tc.expected: contentNodeNew has not been open before, so CloseCustomDialog failed.
     */
    auto closeCallbackFst = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
    };
    overlayManager->CloseCustomDialog(contentNodeNew, closeCallbackFst);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step6. call CloseCustomDialog for contentNode.
     * @tc.expected: CloseCustomDialog succeed.
     */
    auto closeCallbackSnd = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->CloseCustomDialog(contentNode, closeCallbackSnd);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DialogTest008
 * @tc.desc: Test OverlayManager::OpenCustomDialog->UpdateCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    /**
     * @tc.steps: step2. create dialog content node.
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParam;
    dialogParam.contentNode = contentNode;
    dialogParam.alignment = DialogAlignment::TOP_START;
    dialogParam.offset = DimensionOffset(Dimension(0.0), Dimension(0.0));
    dialogParam.autoCancel = false;
    auto contentNodeNew = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParamNew;
    dialogParamNew.contentNode = contentNodeNew;
    dialogParamNew.alignment = DialogAlignment::BOTTOM_END;
    dialogParamNew.offset = DimensionOffset(Dimension(10.0), Dimension(10.0));
    dialogParamNew.autoCancel = true;

    /**
     * @tc.steps: step3. call OpenCustomDialog and then check dialogLayoutProp.
     * @tc.expected: OpenCustomDialog succeed and dialogLayoutProp is correct.
     */
    auto openCallback = [](int32_t errorCode) {};
    overlayManager->OpenCustomDialog(dialogParam, openCallback);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    auto dialogNode = overlayManager->GetDialogNodeWithExistContent(contentNode);
    EXPECT_NE(dialogNode, nullptr);
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    EXPECT_NE(dialogLayoutProp, nullptr);
    EXPECT_EQ(dialogLayoutProp->propDialogAlignment_, DialogAlignment::TOP_START);
    EXPECT_EQ(dialogLayoutProp->propDialogOffset_, DimensionOffset(Dimension(0.0), Dimension(0.0)));
    EXPECT_EQ(dialogLayoutProp->propAutoCancel_, false);

    /**
     * @tc.steps: step4. call UpdateCustomDialog for contentNodeNew.
     * @tc.expected: UpdateCustomDialog failed because contentNodeNew has not been opened.
     */
    auto updateCallbackFst = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
    };
    overlayManager->UpdateCustomDialog(contentNodeNew, dialogParamNew, updateCallbackFst);
    EXPECT_EQ(dialogLayoutProp->propDialogAlignment_, DialogAlignment::TOP_START);
    EXPECT_EQ(dialogLayoutProp->propDialogOffset_, DimensionOffset(Dimension(0.0), Dimension(0.0)));
    EXPECT_EQ(dialogLayoutProp->propAutoCancel_, false);

    /**
     * @tc.steps: step5. call UpdateCustomDialog for contentNode.
     * @tc.expected: UpdateCustomDialog succeed and dialogLayoutProp is updated.
     */
    auto updateCallbackSnd = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->UpdateCustomDialog(contentNode, dialogParamNew, updateCallbackSnd);
    EXPECT_EQ(dialogLayoutProp->propDialogAlignment_, DialogAlignment::BOTTOM_END);
    EXPECT_EQ(dialogLayoutProp->propDialogOffset_, DimensionOffset(Dimension(10.0), Dimension(10.0)));
    EXPECT_EQ(dialogLayoutProp->propAutoCancel_, true);
}

/**
 * @tc.name: DialogTest009
 * @tc.desc: Test OverlayManager::OpenCustomDialog->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogParam.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogParam;
    dialogParam.focusable = false;

    /**
     * @tc.steps: step2. create overlayManager and call OpenCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto callbackFunc = [overlayManager](int32_t dialogId) {
        /**
         * @tc.steps: step4. call CloseCustomDialog when dialogMap_ is not empty.
         * @tc.expected: remove successfully
         */
        overlayManager->CloseCustomDialog(dialogId);
        EXPECT_TRUE(overlayManager->dialogMap_.empty());

        /**
         * @tc.steps: step4. call CloseDialog again when dialogMap_ is empty.
         * @tc.expected: function exits normally
         */
        overlayManager->CloseCustomDialog(dialogId);
        EXPECT_TRUE(overlayManager->dialogMap_.empty());
    };

    overlayManager->OpenCustomDialog(dialogParam, callbackFunc);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DialogTest010
 * @tc.desc: Test SetDialogMask->DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->SetDialogMask(dialogProperties);
    auto dialogMapSize = overlayManager->dialogMap_.size();
    EXPECT_EQ(dialogMapSize, 1);

    /**
     * @tc.steps: step3. test OverlayManager.GetDialog function.
     * @tc.expected: overlayManager.dialog.id equal to GetDialog(dialogId).id.
     */
    int32_t dialogId = dialog->GetId();
    auto dialogNode = overlayManager->GetDialog(dialogId);
    CHECK_NULL_VOID(dialogNode);
    EXPECT_EQ(dialogId, dialogNode->GetId());

    /**
     * @tc.steps4: Call DismissDialog function.
     * @tc.expected: DismissDialog function is called.
     */
    ViewAbstract::DismissDialog();
    EXPECT_EQ(overlayManager->dialogMap_.size(), dialogMapSize);
}

/**
 * @tc.name: DialogTest011
 * @tc.desc: Test OverlayManager::OpenCustomDialog->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogParam.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    /**
     * @tc.steps: step2. create dialog content node.
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParam;
    dialogParam.contentNode = contentNode;

    /**
     * @tc.steps: step3. call OpenCustomDialog for contentNode.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    overlayManager->OpenCustomDialog(dialogParam, nullptr);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());

    /**
     * @tc.steps: step4. call CloseCustomDialog for contentNode.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    overlayManager->CloseCustomDialog(contentNode, nullptr);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DialogTest012
 * @tc.desc: Test OverlayManager::OpenCustomDialog(customBuilderWithId)->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    /**
     * @tc.steps: step2. create dialog content node.
     */
    int32_t newDialogId;
    DialogProperties dialogParam;
    dialogParam.customBuilderWithId = [&newDialogId](const int32_t dialogId) {
        EXPECT_TRUE(dialogId > 0);
        newDialogId = dialogId;
    };

    /**
     * @tc.steps: step3. call OpenCustomDialog for contentNode.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    auto openCallbackFst = [](int32_t errorCode) {
        EXPECT_NE(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackFst);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());

    EXPECT_TRUE(newDialogId > 0);
    overlayManager->CloseCustomDialog(newDialogId);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DialogTest013
 * @tc.desc: Test OverlayManager::OpenCustomDialog(customBuilder)->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    /**
     * @tc.steps: step2. create dialog customBuilder.
     */
    DialogProperties dialogParam;
    dialogParam.customBuilder = []() {};

    /**
     * @tc.steps: step3. call OpenCustomDialog for customBuilder.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    auto openCallbackFst = [](int32_t errorCode) {
        EXPECT_NE(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackFst);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());

    /**
     * @tc.steps: step4. call OpenCustomDialog for contentNode again.
     * @tc.expected: cannot open again and dialogMap_ is still 1.
     */
    auto openCallbackSnd = [](int32_t errorCode) {
        EXPECT_NE(errorCode, ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackSnd);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DialogTest014
 * @tc.desc: Test OverlayManager::OpenCustomDialog(customCNode)->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    /**
     * @tc.steps: step2. create dialog content node.
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParam;
    dialogParam.customCNode = AceType::WeakClaim(AceType::RawPtr(contentNode));

    /**
     * @tc.steps: step3. call OpenCustomDialog for contentNode.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    auto openCallbackFst = [](int32_t errorCode) {
        EXPECT_NE(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackFst);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    auto dialogNode = overlayManager->GetDialogNodeWithExistContent(contentNode);
    EXPECT_NE(dialogNode, nullptr);

    /**
     * @tc.steps: step4. call OpenCustomDialog for contentNode again.
     * @tc.expected: cannot open again and dialogMap_ is still 1.
     */
    auto openCallbackSnd = [](int32_t errorCode) {
        EXPECT_NE(errorCode, ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackSnd);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);

    /**
     * @tc.steps: step5. call CloseCustomDialog for contentNode.
     * @tc.expected: CloseCustomDialog succeed.
     */
    auto closeCallbackSnd = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->CloseCustomDialog(contentNode, closeCallbackSnd);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
}

/**
 * @tc.name: BuildAIEntityMenu
 * @tc.desc: Test OverlayManager::BuildAIEntityMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, BuildAIEntityMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. create menuOptions and call BuildAIEntityMenu.
     * @tc.expected: build AI entity menu successful.
     */
    std::vector<std::pair<std::string, std::function<void()>>> menuOptions;
    menuOptions.push_back(std::make_pair(MENU_CONTENT, []() {}));
    EXPECT_NE(overlayManager->BuildAIEntityMenu(menuOptions), nullptr);
}

/**
 * @tc.name: CreateAIEntityMenu
 * @tc.desc: Test OverlayManager::CreateAIEntityMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, CreateAIEntityMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node, target node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. create menuOptions and call CreateAIEntityMenu.
     * @tc.expected: create AI entity menu successful.
     */
    std::vector<std::pair<std::string, std::function<void()>>> menuOptions;
    menuOptions.push_back(std::make_pair(MENU_CONTENT, []() {}));
    EXPECT_NE(overlayManager->CreateAIEntityMenu(menuOptions, targetNode), nullptr);
}

/**
 * @tc.name: ShowAIEntityMenu
 * @tc.desc: Test OverlayManager::ShowAIEntityMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ShowAIEntityMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node, target node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. create menuOptions, handleRect and call CreateAIEntityMenu.
     * @tc.expected: ShowAIEntityMenu return true.
     */
    std::vector<std::pair<std::string, std::function<void()>>> menuOptions;
    menuOptions.push_back(std::make_pair(MENU_CONTENT, []() {}));
    RectF handleRect(3.0, 3.0, 100.0f, 75.0f);
    EXPECT_TRUE(overlayManager->ShowAIEntityMenu(menuOptions, handleRect, targetNode));
    auto rootChildren = rootNode->GetChildren();
    auto iter = std::find_if(rootChildren.begin(), rootChildren.end(), [](const RefPtr<UINode>& uiNode) {
        CHECK_NULL_RETURN(uiNode, false);
        return uiNode->GetTag() == V2::MENU_WRAPPER_ETS_TAG;
    });
    EXPECT_TRUE(iter != rootChildren.end());
}

/**
 * @tc.name: OnBindKeyboard001
 * @tc.desc: Test OverlayManager::BindKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OnBindKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlay = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlay, nullptr);
    auto rootNode = AceType::DynamicCast<FrameNode>(overlay->GetRootNode().Upgrade());
    ASSERT_NE(rootNode, nullptr);

    /**
     * @tc.steps: step2. BindKeyboard.
     * @tc.expected: customKeyboardMap_ size equals 0.
     */
    overlay->BindKeyboard([](){}, textFieldNode->GetId());
    EXPECT_EQ(overlay->customKeyboardMap_.size(), 0);
    /**
     * @tc.steps: step3. CloseKeyboard.
     * @tc.expected: customKeyboardMap_ size equals 0.
     */
    overlay->CloseKeyboard(textFieldNode->GetId());
    EXPECT_EQ(overlay->customKeyboardMap_.size(), 0);
}

/**
 * @tc.name: CreateOverlayNode001
 * @tc.desc: Test OverlayManager::CreateOverlayNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, CreateOverlayNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rootNode, overlayManager and stageNode.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = nullptr;

    /**
     * @tc.steps: step2. create overlayManager and call AddFrameNodeToOverlay.
     * @tc.expected: overlayNode_ is nullptr
     */
    overlayManager->CreateOverlayNode();
    EXPECT_TRUE(overlayManager->overlayNode_ == nullptr);

    /**
     * @tc.steps: step3. set stageManager and call CreateOverlayNode.
     * @tc.expected: overlayManager->overlayNode_ is not nullptr and the size of root's children equals childSize + 1.
     */
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);
    int32_t childrenSize = rootNode->GetChildren().size();
    overlayManager->CreateOverlayNode();
    EXPECT_FALSE(overlayManager->overlayNode_ == nullptr);
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 1);

    /**
     * @tc.steps: step4.call CreateOverlayNode again.
     * @tc.expected: the size of root's children also equals childSize + 1.
     */
    overlayManager->CreateOverlayNode();
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 1);
    
    /**
     * @tc.steps: step5.call CreateOverlayNode again.
     * @tc.expected: the overlay node is layoutNode.
     */
    overlayManager->overlayNode_ = nullptr;
    overlayManager->overlayInfo_ = NG::OverlayManagerInfo { .renderRootOverlay = false };
    overlayManager->CreateOverlayNode();
    EXPECT_EQ(overlayManager->overlayNode_->GetIsLayoutNode(), true);
}

/**
 * @tc.name: AddFrameNodeToOverlay001
 * @tc.desc: Test OverlayManager::AddFrameNodeToOverlay when index is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, AddFrameNodeToOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, rootNode, overlayManager and stageNode.
     */
    auto frameNode = CreateTargetNode();
    ASSERT_NE(frameNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. call AddFrameNodeToOverlay to add the frameNode to the overlayNode_.
     * @tc.expected: overlayNode_ is not nullptr, both the size of overlayNode_'s children and
     * the size of frameNodeMapOnOverlay_ equal 1.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode);
    EXPECT_FALSE(overlayManager->overlayNode_ == nullptr);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildren().size(), 1);
    EXPECT_EQ(overlayManager->frameNodeMapOnOverlay_.size(), 1);

    /**
     * @tc.steps: step3. call AddFrameNodeToOverlay to add the frameNode to the overlayNode_ again.
     * @tc.expected: both the size of overlayNode_'s children and the size of frameNodeMapOnOverlay_ equal 2.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildren().size(), 1);
    EXPECT_EQ(overlayManager->frameNodeMapOnOverlay_.size(), 1);

    /**
     * @tc.steps: step4. create frameNode2 and call AddFrameNodeToOverlay to add frameNode2.
     * @tc.expected: both the size of overlayNode_'s children and the size of frameNodeMapOnOverlay_ also equal 2.
     */
    auto frameNode2 = CreateTargetNode();
    ASSERT_NE(frameNode2, nullptr);
    overlayManager->AddFrameNodeToOverlay(frameNode2);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildren().size(), 2);
    EXPECT_EQ(overlayManager->frameNodeMapOnOverlay_.size(), 2);
}

/**
 * @tc.name: AddFrameNodeToOverlay002
 * @tc.desc: Test OverlayManager::AddFrameNodeToOverlay when index is not null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, AddFrameNodeToOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, rootNode, overlayManager, stageNode and index.
     */
    auto frameNode = CreateTargetNode();
    ASSERT_NE(frameNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);
    int32_t index = 0;

    /**
     * @tc.steps: step2. call AddFrameNodeToOverlay to add the frameNode to the overlayNode_.
     * @tc.expected: overlayNode_ is not nullptr.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode, index);
    EXPECT_FALSE(overlayManager->overlayNode_ == nullptr);

    /**
     * @tc.steps: step3. set the index to -1, create frameNode2 and call AddFrameNodeToOverlay again.
     * @tc.expected: the frameNode2 is added to the end of the overlayNode_.
     */
    index = -1;
    auto frameNode2 = CreateTargetNode();
    ASSERT_NE(frameNode2, nullptr);
    overlayManager->AddFrameNodeToOverlay(frameNode2, index);
    EXPECT_EQ(overlayManager->overlayNode_->GetLastChild()->GetId(), frameNode2->GetId());

    /**
     * @tc.steps: step4. create frameNode3 and call AddFrameNodeToOverlay without index.
     * @tc.expected: the frameNode is added to the end of the overlayNode_.
     */
    auto frameNode3 = CreateTargetNode();
    ASSERT_NE(frameNode3, nullptr);
    overlayManager->AddFrameNodeToOverlay(frameNode3);
    EXPECT_EQ(overlayManager->overlayNode_->GetLastChild()->GetId(), frameNode3->GetId());

    /**
     * @tc.steps: step5. set index = 2, create frameNode4 and call AddFrameNodeToOverlay to add frameNode4.
     * @tc.expected: the index of frameNode4 of overlayNode_'s children equals 1.
     */
    index = 2;
    auto frameNode4 = CreateTargetNode();
    ASSERT_NE(frameNode4, nullptr);
    overlayManager->AddFrameNodeToOverlay(frameNode4, index);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildIndexById(frameNode4->GetId()), 1);

    /**
     * @tc.steps: step6. set index = 2, create frameNode4 and call AddFrameNodeToOverlay to add frameNode4.
     * @tc.expected: the index of frameNode4 of overlayNode_'s children equals 1.
     */
    index = 1;
    auto frameNode5 = CreateTargetNode();
    ASSERT_NE(frameNode5, nullptr);
    overlayManager->AddFrameNodeToOverlay(frameNode5, index);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildIndexById(frameNode5->GetId()), 1);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildIndexById(frameNode4->GetId()), 2);

    /**
     * @tc.steps: step7. call AddFrameNodeToOverlay to add frameNode again when index = 1.
     * @tc.expected: the index of frameNode5 of overlayNode_'s children equals 0,
     * and the index of frameNode5 of overlayNode_'s children equals 1.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode, index);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildIndexById(frameNode5->GetId()), 0);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildIndexById(frameNode->GetId()), 1);
}

/**
 * @tc.name: CreateOverlayNodeWithOrder001
 * @tc.desc: Test OverlayManager::CreateOverlayNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, CreateOverlayNodeWithOrder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rootNode, overlayManager and stageNode.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = nullptr;

    /**
     * @tc.steps: step2. create overlayManager and call CreateOverlayNodeWithOrder.
     * @tc.expected: the size of root's children does not change.
     */
    int32_t childrenSize = rootNode->GetChildren().size();
    overlayManager->CreateOverlayNodeWithOrder(std::nullopt);
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 1);
    overlayManager->CreateOverlayNodeWithOrder(std::make_optional(0.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 2);

    /**
     * @tc.steps: step3. set stageManager and call CreateOverlayNodeWithOrder.
     * @tc.expected: the size of root's children equals childrenSize + 1.
     */
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);
    overlayManager->CreateOverlayNodeWithOrder(std::make_optional(0.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 4);

    /**
     * @tc.steps: step4.call CreateOverlayNodeWithOrder again.
     * @tc.expected: the size of root's children equals childrenSize + 2.
     */
    overlayManager->CreateOverlayNodeWithOrder(std::make_optional(0.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 5);
}

/**
 * @tc.name: CreateOverlayNodeWithOrder002
 * @tc.desc: Test OverlayManager::CreateOverlayNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, CreateOverlayNodeWithOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rootNode, overlayManager and stageNode.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);

    /**
     * @tc.steps: step2.call CreateOverlayNodeWithOrder again.
     * @tc.expected: the overlay node is layoutNode.
     */
    int32_t childrenSize = rootNode->GetChildren().size();
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);
    overlayManager->overlayInfo_ = NG::OverlayManagerInfo { .renderRootOverlay = false };
    overlayManager->CreateOverlayNodeWithOrder(std::make_optional(0.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 2);
}

/**
 * @tc.name: AddFrameNodeWithOrder001
 * @tc.desc: Test OverlayManager::AddFrameNodeWithOrder when levelOrder is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, AddFrameNodeWithOrder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, rootNode, overlayManager and stageNode.
     */
    auto frameNode = CreateTargetNode();
    ASSERT_NE(frameNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. call AddFrameNodeWithOrder to add the frameNode with levelOrder.
     * @tc.expected: both the size of rootNode's children equal childrenSize + 1
     * and the size of nodeIdOrderMap and orderNodesMap equal 0.
     */
    int32_t childrenSize = rootNode->GetChildren().size();
    overlayManager->AddFrameNodeWithOrder(frameNode, std::nullopt);
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 1);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);
}

/**
 * @tc.name: AddFrameNodeWithOrder002
 * @tc.desc: Test OverlayManager::AddFrameNodeWithOrder when levelOrder is not null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, AddFrameNodeWithOrder002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, rootNode, overlayManager, stageNode and index.
     */
    auto frameNode = CreateTargetNode();
    ASSERT_NE(frameNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. call AddFrameNodeWithOrder to add the frameNode with levelOrder.
     * @tc.expected: both the size of rootNode's children equal childrenSize + 1
     * and the size of nodeIdOrderMap and orderNodesMap equal 1.
     */
    int32_t childrenSize = rootNode->GetChildren().size();
    overlayManager->AddFrameNodeWithOrder(frameNode, std::make_optional(0.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 1);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);

    /**
     * @tc.steps: step3. set LevelOrder = 0.0f, create frameNode2 and call AddFrameNodeToOverlay again.
     * @tc.expected: the frameNode2 is added to the new OrderLevelNode that end of the rootNode.
     */
    auto frameNode2 = CreateTargetNode();
    ASSERT_NE(frameNode2, nullptr);
    overlayManager->AddFrameNodeWithOrder(frameNode2, std::make_optional(0.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 2);
    EXPECT_EQ(rootNode->GetLastChild()->GetId(), frameNode2->GetParent()->GetId());
    EXPECT_EQ(rootNode->GetLastChild()->GetLastChild()->GetId(), frameNode2->GetId());

    /**
     * @tc.steps: step4. set LevelOrder = -1.0f, create frameNode3 and call AddFrameNodeToOverlay again.
     * @tc.expected: the index of frameNode4's parentNode(the new OrderLevelNode) of rootNode's children equals 1.
     */
    auto frameNode3 = CreateTargetNode();
    ASSERT_NE(frameNode3, nullptr);
    overlayManager->AddFrameNodeWithOrder(frameNode3, std::make_optional(-1.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 3);
    EXPECT_EQ(rootNode->GetChildIndexById(frameNode3->GetParent()->GetId()), 1);
    EXPECT_EQ(rootNode->GetChildIndexById(frameNode2->GetParent()->GetId()), 3);

    /**
     * @tc.steps: step5. set LevelOrder = 1.0f, create frameNode4 and call AddFrameNodeWithOrder again.
     * @tc.expected: the index of frameNode4's parentNode(the new OrderLevelNode) of rootNode's children equals 3.
     */
    auto frameNode4 = CreateTargetNode();
    ASSERT_NE(frameNode4, nullptr);
    overlayManager->AddFrameNodeWithOrder(frameNode4, std::make_optional(1.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 4);
    EXPECT_EQ(rootNode->GetChildIndexById(frameNode3->GetParent()->GetId()), 1);
    EXPECT_EQ(rootNode->GetChildIndexById(frameNode2->GetParent()->GetId()), 3);
    EXPECT_EQ(rootNode->GetChildIndexById(frameNode4->GetParent()->GetId()), 4);
}

/**
 * @tc.name: AddFrameNodeWithOrder003
 * @tc.desc: Test OverlayManager::AddFrameNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, AddFrameNodeWithOrder003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rootNode, overlayManager and stageNode.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);

    auto nextNode1 = overlayManager->GetNextNodeWithOrder(std::nullopt);
    EXPECT_EQ(nextNode1, nullptr);
}

/**
 * @tc.name: AddFrameNodeWithOrder004
 * @tc.desc: Test OverlayManager::AddFrameNodeWithOrder.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, AddFrameNodeWithOrder004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, rootNode, overlayManager, stageNode and index.
     */
    auto frameNode = CreateTargetNode();
    ASSERT_NE(frameNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. call AddFrameNodeWithOrder to add the frameNode with levelOrder.
     * @tc.expected: both the size of rootNode's children equal childrenSize + 1
     * and the size of nodeIdOrderMap and orderNodesMap equal 1.
     */
    int32_t childrenSize = rootNode->GetChildren().size();
    overlayManager->AddFrameNodeWithOrder(frameNode, std::make_optional(0.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), childrenSize + 1);
    EXPECT_EQ(overlayManager->nodeIdOrderMap_.size(), 1);
    EXPECT_EQ(overlayManager->orderNodesMap_.size(), 1);

    auto overlayNode = frameNode->GetParent();
    auto nextNode = overlayManager->GetNextNodeWithOrder(std::make_optional(-1.0f));
    EXPECT_EQ(nextNode->GetId(), overlayNode->GetId());
}

/**
 * @tc.name: RemoveFrameNodeOnOverlay001
 * @tc.desc: Test OverlayManager::RemoveFrameNodeOnOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, RemoveFrameNodeOnOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNodes, rootNode, overlayManager and stageNode.
     */
    auto frameNode1 = CreateTargetNode();
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = CreateTargetNode();
    ASSERT_NE(frameNode2, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. add frameNode1 and frameNode2 to the overlayNode_,
     * then call RemoveFrameNodeOnOverlay to remove frameNode1.
     * @tc.expected: both the size of overlayNode_'s children and frameNodeMapOnOverlay_ equal 1.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode1);
    overlayManager->AddFrameNodeToOverlay(frameNode2);
    overlayManager->RemoveFrameNodeOnOverlay(frameNode1);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildren().size(), 1);
    EXPECT_EQ(overlayManager->frameNodeMapOnOverlay_.size(), 1);

    /**
     * @tc.steps: step3. call RemoveFrameNodeOnOverlay to remove frameNode1 again.
     * @tc.expected: both the size of overlayNode_'s children and frameNodeMapOnOverlay_ equal 1.
     */
    overlayManager->RemoveFrameNodeOnOverlay(frameNode1);
    EXPECT_EQ(overlayManager->overlayNode_->GetChildren().size(), 1);
    EXPECT_EQ(overlayManager->frameNodeMapOnOverlay_.size(), 1);

    /**
     * @tc.steps: step4. call RemoveFrameNodeOnOverlay to remove frameNode2.
     * @tc.expected: overlayNode_ is nullptr and the size of frameNodeMapOnOverlay_ equal 0.
     */
    overlayManager->RemoveFrameNodeOnOverlay(frameNode2);
    EXPECT_TRUE(overlayManager->overlayNode_ == nullptr);
    EXPECT_EQ(overlayManager->frameNodeMapOnOverlay_.size(), 0);
    ;
}

/**
 * @tc.name: HideNodeOnOverlay001
 * @tc.desc: Test OverlayManager::HideNodeOnOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, HideNodeOnOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, rootNode, overlayManager and stageNode.
     */
    auto frameNode = CreateTargetNode();
    ASSERT_NE(frameNode, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. add frameNode to the overlayNode_, then call HideNodeOnOverlay.
     * @tc.expected: the frameNode is set to VisibleType::GONE.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode);
    overlayManager->HideNodeOnOverlay(frameNode);
    EXPECT_EQ(frameNode->layoutProperty_->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: ShowNodeOnOverlay001
 * @tc.desc: Test OverlayManager::ShowNodeOnOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ShowNodeOnOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode, rootNode, overlayManager and stageNode.
     */
    auto frameNode = CreateTargetNode();
    ASSERT_NE(frameNode, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. add frameNode to the overlayNode_ and hide it, then call ShowNodeOnOverlay.
     * @tc.expected: the frameNode is set to VisibleType::VISIBLE.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode);
    overlayManager->HideNodeOnOverlay(frameNode);
    overlayManager->ShowNodeOnOverlay(frameNode);
    EXPECT_EQ(frameNode->layoutProperty_->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: HideAllNodesOnOverlay001
 * @tc.desc: Test OverlayManager::HideAllNodesOnOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, HideAllNodesOnOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNodes, rootNode, overlayManager and stageNode.
     */
    auto frameNode1 = CreateTargetNode();
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = CreateTargetNode();
    ASSERT_NE(frameNode2, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. add frameNode1 and frameNode2 to the overlayNode_, then call HideAllNodesOnOverlay.
     * @tc.expected: both frameNode1 and frameNode2 are set to VisibleType::GONE.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode1);
    overlayManager->AddFrameNodeToOverlay(frameNode2);
    overlayManager->HideAllNodesOnOverlay();
    EXPECT_EQ(frameNode1->layoutProperty_->GetVisibility(), VisibleType::GONE);
    EXPECT_EQ(frameNode2->layoutProperty_->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: ShowAllNodesOnOverlay001
 * @tc.desc: Test OverlayManager::ShowAllNodesOnOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ShowAllNodesOnOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNodes, rootNode, overlayManager and stageNode.
     */
    auto frameNode1 = CreateTargetNode();
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = CreateTargetNode();
    ASSERT_NE(frameNode2, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    pipelineContext->stageManager_->stageNode_ = stageNode;
    stageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step2. add frameNode1 and frameNode2 to the overlayNode_, and call hide them,
     * then call ShowAllNodesOnOverlay.
     * @tc.expected: both frameNode1 and frameNode2 are set to VisibleType::VISIBLE.
     */
    overlayManager->AddFrameNodeToOverlay(frameNode1);
    overlayManager->AddFrameNodeToOverlay(frameNode2);
    overlayManager->HideAllNodesOnOverlay();
    overlayManager->ShowAllNodesOnOverlay();
    EXPECT_EQ(frameNode1->layoutProperty_->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_EQ(frameNode2->layoutProperty_->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: DialogDumpInfoTest001
 * @tc.desc: Test Dialog DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogDumpInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. clear dump info and create dialog pattern.
     */
    DumpLog::GetInstance().description_.clear();
    auto pattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
    /**
     * @tc.steps: step2. build empty prop.
     */
    DialogProperties props;
    pattern->dialogProperties_ = props;
    /**
     * @tc.steps: step3. dump info.
     * @tc.expected: dump success, the description not empty
     */
    pattern->DumpInfo();
    EXPECT_NE(DumpLog::GetInstance().description_.size(), 0);
    /**
     * @tc.steps: step4. make a full property, and retry
     * @tc.expected: dump success, the description not empty
     */
    DumpLog::GetInstance().description_.clear();
    DialogProperties propsFill {
        .type = DialogType::ACTION_SHEET,
        .title = "title",
        .content = "content",
        .checkboxContent = "checkboxContent",
        .alignment = DialogAlignment::CENTER,
        .autoCancel = false,
        .customStyle = true,
        .isMenu = true,
        .isSelect = true,
        .offset = DimensionOffset(),
        .maskColor = std::make_optional(Color::RED),
        .backgroundColor = std::make_optional(Color::RED),
        .isShowInSubWindow = true,
        .buttonDirection = DialogButtonDirection::HORIZONTAL,
        .isMask = true,
        .isModal = false,
        .isSceneBoardDialog = true,
        .isSysBlurStyle = false,
        .backgroundBlurStyle = 1,
        .shadow = std::make_optional<Shadow>(),
        .borderWidth = std::make_optional<NG::BorderWidthProperty>(),
        .borderColor = std::make_optional<NG::BorderColorProperty>(),
        .borderStyle = std::make_optional<NG::BorderStyleProperty>(),
        .maskRect = std::make_optional<DimensionRect>(),
    };
    ButtonInfo info;
    propsFill.buttons.push_back(info);
    pattern->dialogProperties_ = props;
    pattern->DumpInfo();
    EXPECT_NE(DumpLog::GetInstance().description_.size(), 0);
}

/**
 * @tc.name: BeforeCreateLayoutWrapperTest001
 * @tc.desc: Test OverlayManager::BeforeCreateLayoutWrapper destroy modal node.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, BeforeCreateLayoutWrapperTest001, TestSize.Level1)
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
     * @tc.steps: step2. create target node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related function is called.
     */
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::NONE;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->SetEnableSafeArea(true);
    topModalPattern->BeforeCreateLayoutWrapper();
    auto modalNodeLayoutProperty = topModalNode->GetLayoutProperty();
    EXPECT_NE(modalNodeLayoutProperty->safeAreaPadding_, nullptr);
    EXPECT_TRUE(topModalPattern->enableSafeArea_);
    topModalPattern->SetEnableSafeArea(false);
    topModalPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(modalNodeLayoutProperty->safeAreaPadding_, nullptr);
    EXPECT_FALSE(topModalPattern->enableSafeArea_);
}

/**
 * @tc.name: BeforeCreateLayoutWrapperTest002
 * @tc.desc: Test OverlayManager::BeforeCreateLayoutWrapper safeAreaPadding.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, BeforeCreateLayoutWrapperTest002, TestSize.Level1)
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
     * @tc.steps: step2. create target node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        IgnoreLayoutSafeAreaOpts opts;
        opts.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM | NG::LAYOUT_SAFE_AREA_TYPE_KEYBOARD;
        frameNode->layoutProperty_->UpdateIgnoreLayoutSafeAreaOpts(opts);
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create modal node and get modal node, get pattern.
     * @tc.expected: related function is called.
     */
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::NONE;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    topModalPattern->SetEnableSafeArea(true);
    EXPECT_TRUE(topModalPattern->enableSafeArea_);
    auto host = topModalPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto context = host->GetContext();
    EXPECT_NE(context, nullptr);
    auto inset = context->GetSafeAreaWithoutProcess();
    NG::CalcLength safeAreaPaddingLeft(inset.left_.Length());
    NG::CalcLength safeAreaPaddingRight(inset.right_.Length());
    topModalPattern->BeforeCreateLayoutWrapper();
    auto modalNodeLayoutProperty = topModalNode->layoutProperty_;
    ASSERT_NE(modalNodeLayoutProperty, nullptr);
    const std::unique_ptr<PaddingProperty>& modalSafeAreaPaddingProp =
        modalNodeLayoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(modalSafeAreaPaddingProp, nullptr);
    EXPECT_EQ(modalSafeAreaPaddingProp->left, safeAreaPaddingLeft);
    EXPECT_EQ(modalSafeAreaPaddingProp->right, safeAreaPaddingRight);
}

/**
 * @tc.name: DialogWithNodeTest001
 * @tc.desc: Test OverlayManager::OpenCustomDialog->UpdateCustomDialogWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogWithNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    /**
     * @tc.steps: step2. create dialog content node.
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParam;
    dialogParam.contentNode = contentNode;
    dialogParam.alignment = DialogAlignment::TOP_START;
    dialogParam.offset = DimensionOffset(Dimension(0.0), Dimension(0.0));
    dialogParam.autoCancel = false;
    auto contentNodeNew = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParamNew;
    dialogParamNew.contentNode = contentNodeNew;
    dialogParamNew.alignment = DialogAlignment::BOTTOM_END;
    dialogParamNew.offset = DimensionOffset(Dimension(10.0), Dimension(10.0));
    dialogParamNew.autoCancel = true;

    /**
     * @tc.steps: step3. call OpenCustomDialog and then check dialogLayoutProp.
     * @tc.expected: OpenCustomDialog succeed and dialogLayoutProp is correct.
     */
    auto openCallback = [](int32_t dialogId) {};
    overlayManager->OpenCustomDialog(dialogParam, openCallback);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    auto dialogNode = overlayManager->GetDialogNodeWithExistContent(contentNode);
    EXPECT_NE(dialogNode, nullptr);
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    EXPECT_NE(dialogLayoutProp, nullptr);
    EXPECT_EQ(dialogLayoutProp->propDialogAlignment_, DialogAlignment::TOP_START);
    EXPECT_EQ(dialogLayoutProp->propDialogOffset_, DimensionOffset(Dimension(0.0), Dimension(0.0)));
    EXPECT_EQ(dialogLayoutProp->propAutoCancel_, false);

    /**
     * @tc.steps: step4. call UpdateCustomDialog for contentNodeNew.
     * @tc.expected: UpdateCustomDialog failed because contentNodeNew has not been opened.
     */
    auto updateCallbackFst = [](int32_t dialogId) {};
    overlayManager->UpdateCustomDialogWithNode(contentNodeNew, dialogParamNew, updateCallbackFst);
    EXPECT_EQ(dialogLayoutProp->propDialogAlignment_, DialogAlignment::TOP_START);
    EXPECT_EQ(dialogLayoutProp->propDialogOffset_, DimensionOffset(Dimension(0.0), Dimension(0.0)));
    EXPECT_EQ(dialogLayoutProp->propAutoCancel_, false);

    /**
     * @tc.steps: step5. call UpdateCustomDialog for contentNode.
     * @tc.expected: UpdateCustomDialog succeed and dialogLayoutProp is updated.
     */
    auto updateCallbackSnd = [](int32_t dialogId) {};
    overlayManager->UpdateCustomDialog(contentNode, dialogParamNew, updateCallbackSnd);
    EXPECT_EQ(dialogLayoutProp->propDialogAlignment_, DialogAlignment::BOTTOM_END);
    EXPECT_EQ(dialogLayoutProp->propDialogOffset_, DimensionOffset(Dimension(10.0), Dimension(10.0)));
    EXPECT_EQ(dialogLayoutProp->propAutoCancel_, true);
}

/**
 * @tc.name: OverlayManagerContetx001
 * @tc.desc: Test OverlayManager GetPipelineContext
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, OverlayManagerContetx001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto geometryNode = stageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(1.0, 1.0));
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->stageManager_->stageNode_ = stageNode;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_NE(overlayManager->context_.Upgrade(), nullptr);
    auto context = overlayManager->GetPipelineContext();
    ASSERT_NE(context, nullptr);

    overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_EQ(overlayManager->context_.Upgrade(), nullptr);
    context = overlayManager->GetPipelineContext();
    ASSERT_NE(context, nullptr);
}

/**
 * @tc.name: DialogTransitionTest006
 * @tc.desc: Test OverlayManager::ShowDialog->Set no transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, DialogTransitionTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect is nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    EXPECT_EQ(transitionEffect, nullptr);
}
} // namespace OHOS::Ace::NG
