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
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t DURATION = 2;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
const std::string MENU_CONTENT = "复制";
constexpr int32_t OVERLAY_EXISTS = 0;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
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
    if (!sheetStyle.sheetMode.has_value()) {
        sheetStyle.sheetMode = SheetMode::MEDIUM;
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
 * @tc.name: MenuTest001
 * @tc.desc: Test OverlayManager::ShowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, MenuTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node and root node.
     */
    auto menuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, menuId, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenuFirst = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto subMenuSecond = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    mainMenu->MountToParent(menuNode);
    subMenuFirst->MountToParent(menuNode);
    subMenuSecond->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuWrapperPattern>();
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    menuNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. call showMenu when menuNode already appended.
     * @tc.expected: function exits rightly
     */
    auto targetId = rootNode->GetId();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowMenu(targetId, MENU_OFFSET, menuNode);
    overlayManager->HideMenu(menuNode, targetId);
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    overlayManager->ShowMenuInSubWindow(rootNode->GetId(), MENU_OFFSET, menuNode);
    overlayManager->HideMenuInSubWindow(menuNode, rootNode->GetId());
    overlayManager->HideMenuInSubWindow();
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    overlayManager->ShowMenuAnimation(menuNode);
    EXPECT_FALSE(menuPattern == nullptr);
    EXPECT_FALSE(menuPattern->animationOption_.GetOnFinishEvent() == nullptr);
    menuPattern->StartShowAnimation();
    auto menuHelper = overlayManager->ShowMenuHelper(menuNode, rootNode->GetId(), MENU_OFFSET);
    EXPECT_TRUE(menuHelper);

    /**
     * @tc.steps: step3. call HideMenu related functions after menuNode already erased.
     * @tc.expected: return normally
     */
    overlayManager->HideAllMenus();
    overlayManager->DeleteMenu(targetId);
    overlayManager->HideMenu(menuNode, targetId);
    overlayManager->HideMenuInSubWindow(menuNode, targetId);
    overlayManager->HideMenuInSubWindow();
    EXPECT_TRUE(overlayManager->menuMap_.empty());

    /**
     * @tc.steps: step4. call DeleteMenu again after menuNode already erased.
     * @tc.expected: return normally
     */
    overlayManager->RemoveMenu(menuNode);
    overlayManager->RemoveOverlayInSubwindow();
    overlayManager->DeleteMenu(targetId);
    EXPECT_TRUE(overlayManager->menuMap_.empty());
}

/**
 * @tc.name: MenuTest002
 * @tc.desc: Test OverlayManager::ShowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, MenuTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto targetId = rootNode->GetId();
    auto menuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, menuId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId));
    auto subMenuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto subMenuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, subMenuId, AceType::MakeRefPtr<MenuPattern>(1, "Test", MenuType::MENU));
    subMenuNode->MountToParent(menuNode);
    /**
     * @tc.steps: step2. call showMenu when menuNode is nullptr and menuMap is empty.
     * @tc.expected: function exits normally
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowMenu(targetId, MENU_OFFSET, nullptr);
    overlayManager->ShowMenuInSubWindow(targetId, MENU_OFFSET, nullptr);
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    /**
     * @tc.steps: step3. call showMenu when menuNode is not appended.
     * @tc.expected: menuNode mounted successfully
     */
    overlayManager->ShowMenu(targetId, MENU_OFFSET, menuNode);
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    /**
     * @tc.steps: step4. call showMenu when menuNode is nullptr and menuMap is not empty.
     * @tc.expected: function exits normally
     */
    overlayManager->ShowMenu(targetId, MENU_OFFSET, nullptr);
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    /**
     * @tc.steps: step5. call HideAllMenus.
     * @tc.expected: function exits normally
     */
    overlayManager->CleanMenuInSubWindow(targetId);
    overlayManager->FocusOverlayNode(menuNode, false);
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    EXPECT_FALSE(overlayManager->RemoveOverlayInSubwindow());
    EXPECT_TRUE(overlayManager->RemoveAllModalInOverlay());
    EXPECT_FALSE(overlayManager->RemoveOverlay(false));
    overlayManager->RemoveMenu(rootNode);
}

/**
 * @tc.name: MenuTest003
 * @tc.desc: Test OverlayManager::PopMenuAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, MenuTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node , preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto previewContext = previewNode->GetRenderContext();
    ASSERT_NE(previewContext, nullptr);
    auto menuContext = previewNode->GetRenderContext();
    ASSERT_NE(menuContext, nullptr);
    previewContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
    menuContext->UpdateTransformScale(VectorF(1.0f, 1.0f));

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    /**
     * @tc.steps: step2. call PopMenuAnimation when showPreviewAnimation is true
     * @tc.expected: the render context of menu and preview will update, and menu wrapper node will remove
     */
    EXPECT_EQ(rootNode->GetChildren().size(), 1);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
    overlayManager->PopMenuAnimation(menuWrapperNode, true);
    pipeline->taskExecutor_ = nullptr;
    EXPECT_EQ(menuContext->GetTransformScale(), VectorF(1.0f, 1.0f));
    EXPECT_EQ(previewContext->GetTransformScale(), VectorF(1.0f, 1.0f));
    EXPECT_EQ(rootNode->GetChildren().size(), 0);

    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    /**
     * @tc.steps: step2. call PopMenuAnimation when showPreviewAnimation is false
     * @tc.expected: the none of node will remove.
     */
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
    overlayManager->PopMenuAnimation(menuWrapperNode, false);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuTest004
 * @tc.desc: Test OverlayManager::CleanMenuInSubWindowWithAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, MenuTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto menuWrapperContext = menuWrapperNode->GetRenderContext();
    ASSERT_NE(menuWrapperContext, nullptr);
    menuWrapperContext->UpdateOpacity(1.0);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto previewContext = previewNode->GetRenderContext();
    ASSERT_NE(previewContext, nullptr);
    auto menuContext = previewNode->GetRenderContext();
    ASSERT_NE(menuContext, nullptr);
    previewContext->UpdateTransformScale(VectorF(0.0f, 0.0f));
    menuContext->UpdateTransformScale(VectorF(0.0f, 0.0f));
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    /**
     * @tc.steps: step2. call PopMenuAnimation when showPreviewAnimation is false
     * @tc.expected: the render context of menu and preview will update
     */
    overlayManager->CleanMenuInSubWindowWithAnimation();
    pipeline->taskExecutor_ = nullptr;
    EXPECT_EQ(menuContext->GetTransformScale(), VectorF(1.0f, 1.0f));
    EXPECT_EQ(previewContext->GetTransformScale(), VectorF(1.0f, 1.0f));
}

/**
 * @tc.name: MenuTest005
 * @tc.desc: Test OverlayManager::ShowMenuAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, MenuTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node , preview node and root node.
     */
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    menuWrapperNode->MountToParent(rootNode);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto focusHub = menuWrapperNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    /**
     * @tc.steps: step2. call ShowMenuAnimation and call StartShowAnimation of menu pattern
     * @tc.expected: the isFirstShow_ of preview pattern true and parentFocusable_ of menuWrapper's focus hub is true
     */
    overlayManager->ShowMenuAnimation(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->StartShowAnimation();
    pipeline->taskExecutor_ = nullptr;

    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(previewPattern, nullptr);
    EXPECT_TRUE(previewPattern->isFirstShow_);
}

/**
 * @tc.name: MenuTest006
 * @tc.desc: Test OverlayManager::UpdateContextMenuDisappearPosition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, MenuTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance , set two different menu_offset.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlay = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlay, nullptr);
    overlay->ResetContextMenuDragHideFinished();
    const OffsetF menu_zero_offset(0.0, 0.0);
    const OffsetF menu_five_offset(5.0, 0.0);
    overlay->UpdateContextMenuDisappearPosition(menu_zero_offset);
    overlay->UpdateDragMoveVector(menu_five_offset);
    overlay->UpdateContextMenuDisappearPosition(MENU_OFFSET);
    /**
     * @tc.steps: step2. create menu and call UpdateContextMenuDisappearPosition.
     * @tc.expected: submenu is called
     */
    auto menuId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, menuId, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenuFirst = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto subMenuSecond = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    mainMenu->MountToParent(menuNode);
    subMenuFirst->MountToParent(menuNode);
    subMenuSecond->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuWrapperPattern>();
    auto rootNode = overlay->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    menuNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto targetId = rootNode->GetId();
    overlay->ShowMenu(targetId, MENU_OFFSET, menuNode);
    overlay->UpdateContextMenuDisappearPosition(menu_five_offset);
    EXPECT_EQ(rootNode->GetChildren().size(), 2);
    auto node = AceType::DynamicCast<FrameNode>(rootNode->GetChildren().back());
    EXPECT_EQ(node->GetTag(), V2::MENU_WRAPPER_ETS_TAG);
    overlay->HideMenu(menuNode, targetId);
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
 * @tc.desc:  Test OverlayManager::RemoveOverlay related functions.
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
 * @tc.name: ToastShowModeTest001
 * @tc.desc: Test OverlayManager::ShowToast with showMode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastShowModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast node with showMode, and show it.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    MockPipelineContext::GetCurrent()->rootNode_ = rootNode;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto toastInfo = NG::ToastInfo { .message = MESSAGE,
        .duration = DURATION,
        .bottom = BOTTOMSTRING,
        .showMode = NG::ToastShowMode::TOP_MOST,
        .isRightToLeft = true };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    overlayManager->ShowToast(toastInfo, nullptr);
    EXPECT_FALSE(overlayManager->toastMap_.empty());
    /**
     * @tc.steps: step2. Test Toast showMode and offset.
     */
    auto toastNode = overlayManager->toastMap_.begin()->second.Upgrade();
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    toastContext->UpdateOffset(OffsetT<Dimension>{0.0_vp, 0.0_vp});
    EXPECT_FALSE(pattern->IsDefaultToast());
    EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(toastNode->CreateLayoutWrapper(), DirtySwapConfig()));
    EXPECT_EQ(toastContext->GetOffset()->GetX().ConvertToPx(), 0.0);
    EXPECT_EQ(toastContext->GetOffset()->GetY().ConvertToPx(), 0.0);
    /**
     * @tc.steps: step3. PopToast.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_FALSE(overlayManager->toastMap_.empty());
}

/**
 * @tc.name: ToastTest001
 * @tc.desc: Test OverlayManager::ShowToast->PopToast.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and toast node.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode =
        FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));

    /**
     * @tc.steps: step2. create overlayManager and call ShowToast when rootElement is nullptr.
     * @tc.expected: toastMap_ is empty
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    overlayManager->ShowToast(toastInfo, nullptr);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    /**
     * @tc.steps: step2. call PopToast.
     * @tc.expected: toastMap_ is empty
     */
    overlayManager->PopToast(toastId);
    overlayManager->DeleteModal(DURATION);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
}
/**
 * @tc.name: ToastTest002
 * @tc.desc: Test OverlayManager::ShowToast->PopToast.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and toast node.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode =
        FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));

    /**
     * @tc.steps: step2. create overlayManager and call ShowToast when rootElement is not nullptr.
     * @tc.expected: toastMap_ is empty
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::GetCurrent()->rootNode_ = rootNode;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    overlayManager->ShowToast(toastInfo, nullptr);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    /**
     * @tc.steps: step2. call PopToast.
     * @tc.expected: toastMap_ is empty
     */
    overlayManager->PopToast(toastId);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
}

/**
 * @tc.name: ToastTest004
 * @tc.desc: Test OverlayManager::ShowToast->PopToast.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast node with alignment.
     * @tc.expected: toast property has alignment.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(toastProperty->GetToastAlignmentValue(), Alignment::TOP_LEFT);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. update different alignment to property.
     * @tc.expected: call the OnDirtyLayoutWrapperSwap function always return true.
     */
    std::vector<Alignment> alignments = { Alignment::TOP_LEFT, Alignment::TOP_CENTER, Alignment::TOP_RIGHT,
        Alignment::CENTER_LEFT, Alignment::CENTER, Alignment::CENTER_RIGHT, Alignment::BOTTOM_LEFT,
        Alignment::BOTTOM_CENTER, Alignment::BOTTOM_RIGHT };
    for (auto alignment : alignments) {
        toastProperty->UpdateToastAlignment(alignment);
        EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(toastNode, DirtySwapConfig()));
    }
}

/**
 * @tc.name: ToastTest005
 * @tc.desc: Test Toast.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest005, TestSize.Level1)
{
    // create mock theme manager
    auto backupThemeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto toastTheme = AceType::MakeRefPtr<ToastTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(toastTheme));

    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto toastContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(toastContext);
    auto theme = toastContext->GetTheme<ToastTheme>();
    ASSERT_NE(theme, nullptr);

    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);

    auto fontSize = Dimension(10.0);
    theme->textStyle_.fontSize_ = fontSize;
    /**
     * @tc.steps: step1. update TextProperty in Toast alignment to property.
     * @tc.expected: call the UpdateTextSizeConstraint function expected true and don't set MaxLine.
     */
    toastPattern->UpdateTextSizeConstraint(textNode);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(textLayoutProperty->GetMaxLines(), std::nullopt);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);

    // restore mock theme manager
    MockPipelineContext::GetCurrent()->SetThemeManager(backupThemeManager);
}

/**
 * @tc.name: ToastTest006
 * @tc.desc: Test OverlayManager::ToastView.UpdateTextLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest006, TestSize.Level1)
{
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    const std::optional<Color> textColor = Color::RED;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step1. update TextProperty in Toast alignment to property.
     * @tc.expected: call the UpdateTextLayoutProperty function expected true and Set TextColor RED.
     */
    ToastView::UpdateTextLayoutProperty(textNode, MESSAGE, false, textColor);
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    EXPECT_TRUE(toastProperty->HasToastAlignment());
    EXPECT_EQ(textLayoutProperty->GetTextColor(), Color::RED);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest007
 * @tc.desc: Test ToastPattern::CreateAccessibilityProperty function.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast and get toastNode.
     */
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode =
        FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
    ASSERT_NE(toastNode, nullptr);
    toastNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get ToastAccessibilityProperty.
     * @tc.expected: step2. ToastAccessibilityProperty is not nullptr.
     */
    auto accessibilityProperty = toastNode->GetAccessibilityProperty<ToastAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
}

/**
 * @tc.name: ToastTest008
 * @tc.desc: Test ToastAccessibilityProperty::SetSelectStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast and get toastNode.
     */
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode =
        FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
    ASSERT_NE(toastNode, nullptr);
    toastNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. ToastAccessibilityProperty is not nullptr.
     */
    auto accessibilityProperty = toastNode->GetAccessibilityProperty<ToastAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. set showedSelectStatus OFF.
     * @tc.expected: step3 get showedSelectStatus OFF.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    toastProperty->SetSelectStatus(ToastLayoutProperty::SelectStatus::OFF);
    auto showedSelectStatus = toastProperty->GetSelectStatus();
    EXPECT_EQ(showedSelectStatus, ToastLayoutProperty::SelectStatus::OFF);

    /**
     * @tc.steps: step4. set showedSelectStatus ON.
     * @tc.expected: step4 get showedSelectStatus ON.
     */
    toastProperty->SetSelectStatus(ToastLayoutProperty::SelectStatus::ON);
    showedSelectStatus = toastProperty->GetSelectStatus();
    EXPECT_EQ(showedSelectStatus, ToastLayoutProperty::SelectStatus::ON);
}

/**
 * @tc.name: ToastTest009
 * @tc.desc: Test ShowToast hoverModeArea default and enableHoverMode default
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast and toastNode.
     */
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode =
        FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
    ASSERT_NE(toastNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    MockPipelineContext::GetCurrent()->rootNode_ = rootNode;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    toastNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto toastInfo = NG::ToastInfo { .message = MESSAGE,
        .duration = DURATION,
        .bottom = BOTTOMSTRING,
        .isRightToLeft = true };
    /**
     * @tc.steps: step2. create overlayManager and call ShowToast when rootElement is nullptr.
     * @tc.expected: toastMap_ is empty
     */
    overlayManager->ShowToast(toastInfo, nullptr);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    /**
     * @tc.steps: step3. Test Toast showMode and hoverModeArea.
     */
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    EXPECT_TRUE(toastPattern->IsDefaultToast());
    EXPECT_FALSE(toastPattern->toastInfo_.enableHoverMode);
    EXPECT_EQ(toastPattern->toastInfo_.hoverModeArea, HoverModeAreaType::BOTTOM_SCREEN);
}

/**
 * @tc.name: ToastTest010
 * @tc.desc: Test ShowToast hoverModeArea TOP_SCREEN and enableHoverMode true
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo and update hoverModeArea enableHoverMode.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE,
        .duration = DURATION,
        .bottom = BOTTOMSTRING,
        .isRightToLeft = true };
    toastInfo.enableHoverMode = true;
    toastInfo.hoverModeArea = HoverModeAreaType::TOP_SCREEN;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    /**
     * @tc.steps: step3. Test Toast showMode and hoverModeArea.
     */
    EXPECT_TRUE(toastPattern->IsDefaultToast());
    EXPECT_TRUE(toastPattern->toastInfo_.enableHoverMode);
    EXPECT_EQ(toastPattern->toastInfo_.hoverModeArea, HoverModeAreaType::TOP_SCREEN);
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
 * @tc.name: ToastDumpInfoTest001
 * @tc.desc: Test Toast DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestNg, ToastDumpInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. clear dump info and create toast pattern.
     */
    DumpLog::GetInstance().description_.clear();
    auto pattern = AceType::MakeRefPtr<ToastPattern>();
    ToastInfo info;
    info.shadow = ShadowConfig::DefaultShadowL;
    /**
     * @tc.steps: step3. set info and dump info.
     * @tc.expected: dump success, the description not empty
     */
    pattern->SetToastInfo(info);
    pattern->DumpInfo();
    EXPECT_NE(DumpLog::GetInstance().description_.size(), 0);
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
        .isScenceBoardDialog = true,
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
} // namespace OHOS::Ace::NG
