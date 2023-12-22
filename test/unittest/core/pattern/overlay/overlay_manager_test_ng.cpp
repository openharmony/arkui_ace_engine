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
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t DURATION = 2;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
constexpr float MINUS_HEIGHT = -5.0f;
} // namespace
class OverlayManagerTestNg : public testing::Test {
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
};

void OverlayManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
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
void OverlayManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> OverlayManagerTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayManagerTestNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetMode.has_value()) {
        sheetStyle.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayManagerTestNg::CreateSheetBuilder()
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
 * @tc.name: PopupTest001
 * @tc.desc: Test OverlayManager::ShowPopup.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, PopupTest001, TestSize.Level1)
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
 * @tc.name: BindContentCover001
 * @tc.desc: Test OverlayManager::BindContentCover create modal node.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindContentCover001, TestSize.Level1)
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
    overlayManager->BindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, targetNode);
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
 * @tc.name: BindContentCover002
 * @tc.desc: Test OverlayManager::BindContentCover change ModalTransition dynamically.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindContentCover002, TestSize.Level1)
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
    bool isShow = true;
    auto onAppear = []() {};
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->BindContentCover(
        isShow, nullptr, std::move(builderFunc), modalStyle, onAppear, nullptr, targetNode);
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
    overlayManager->BindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, targetNode);
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
    overlayManager->BindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, targetNode);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_NE(topModalNode, nullptr);
    EXPECT_EQ(topModalNode->GetRenderContext()->GetBackgroundColorValue(), Color::GREEN);
    overlayManager->BindContentCover(!isShow, nullptr, nullptr, modalStyle, nullptr, nullptr, targetNode);
}

/**
 * @tc.name: BindContentCover003
 * @tc.desc: Test OverlayManager::BindContentCover destroy modal node.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindContentCover003, TestSize.Level1)
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
    overlayManager->BindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step4. destroy modal page.
     * @tc.expected: destroy successfully
     */
    auto onDisappear = []() {};
    overlayManager->BindContentCover(!isShow, nullptr, nullptr, modalStyle, nullptr, onDisappear, targetNode);
    EXPECT_TRUE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: BindSheet001
 * @tc.desc: Test OverlayManager::BindSheet create sheet page.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create builder func.
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

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create sheet node and get sheet node, get pattern.
     * @tc.expected: related function is called.
     */
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_FALSE(topSheetNode == nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    EXPECT_FALSE(topSheetPattern == nullptr);
    auto sheetLayoutProperty = topSheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);
    auto sheetChildren = topSheetNode->GetChildren();
    auto oprationNode = sheetChildren.front();
    EXPECT_FALSE(oprationNode == nullptr);
    auto scrollNode = *(std::next(sheetChildren.begin(), 1));
    EXPECT_FALSE(scrollNode == nullptr);
    auto closeIconNode = topSheetNode->GetLastChild();
    EXPECT_FALSE(closeIconNode == nullptr);
    auto sheetDragBarNode = AceType::DynamicCast<FrameNode>(oprationNode->GetFirstChild());
    EXPECT_FALSE(sheetDragBarNode == nullptr);
    auto sheetDragBarPattern = sheetDragBarNode->GetPattern<SheetDragBarPattern>();
    EXPECT_FALSE(sheetDragBarPattern == nullptr);
    auto sheetDragBarPaintProperty = sheetDragBarNode->GetPaintProperty<SheetDragBarPaintProperty>();
    EXPECT_FALSE(sheetDragBarPaintProperty == nullptr);
    SheetStyle sheetStyle1;
    topSheetPattern->pageHeight_ = 10;

    // sheetStyle1.sheetMode is null.
    sheetStyle1.sheetMode = std::nullopt;
    overlayManager->sheetHeight_ = 0;
    sheetStyle1.height->unit_ = DimensionUnit::PERCENT;
    sheetStyle1.height->value_ = 2.0;
    overlayManager->ComputeSheetOffset(sheetStyle1, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 2));

    overlayManager->sheetHeight_ = 0;
    sheetStyle1.height->unit_ = DimensionUnit::PERCENT;
    sheetStyle1.height->value_ = -2.0;
    overlayManager->ComputeSheetOffset(sheetStyle1, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 2));

    overlayManager->sheetHeight_ = 0;
    sheetStyle1.height->unit_ = DimensionUnit::PERCENT;
    sheetStyle1.height->value_ = 0.1;
    overlayManager->ComputeSheetOffset(sheetStyle1, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 1.0));

    overlayManager->sheetHeight_ = 0;
    sheetStyle1.height->unit_ = DimensionUnit::VP;
    sheetStyle1.height->value_ = 2;
    overlayManager->ComputeSheetOffset(sheetStyle1, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 2));

    // sheetStyle1.sheetMode is not null.
    sheetStyle1.sheetMode = SheetMode(5);
    overlayManager->sheetHeight_ = 0;
    sheetStyle1.height->unit_ = DimensionUnit::PERCENT;
    sheetStyle1.height->value_ = 2.0;
    overlayManager->ComputeSheetOffset(sheetStyle1, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 0));

    std::string title = "11";
    std::string subtitle = "22";
    sheetStyle1.sheetTitle = title;
    EXPECT_EQ(sheetStyle1.sheetTitle, title);
    sheetStyle1.sheetSubtitle = subtitle;
    EXPECT_EQ(sheetStyle1.sheetSubtitle, subtitle);
    std::stack<WeakPtr<FrameNode>> modalStack;
    overlayManager->modalStack_ = modalStack;
    EXPECT_FALSE(sheetDragBarPaintProperty == nullptr);
}

/**
 * @tc.name: RemoveAllModalInOverlay001
 * @tc.desc: Test OverlayManager::RemoveAllModalInOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, RemoveAllModalInOverlay001, TestSize.Level1)
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
     * @tc.steps: step2. create builder.
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

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. Run BindSheet to add something to modalStack and modalList.
     */
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_EQ(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);

    /**
     * @tc.steps: step4. run RemoveAllModalInOverlay func.
     */
    overlayManager->modalStack_.emplace(nullptr);
    overlayManager->modalList_.pop_back();
    EXPECT_TRUE(overlayManager->RemoveAllModalInOverlay());
    overlayManager->BindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_TRUE(overlayManager->RemoveAllModalInOverlay());

    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetNode->tag_ = V2::ROOT_ETS_TAG;
    EXPECT_TRUE(overlayManager->RemoveAllModalInOverlay());
}

/**
 * @tc.name: BindSheet002
 * @tc.desc: Test OverlayManager::BindSheet change sheetStyle dynamically.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindSheet002, TestSize.Level1)
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
     * @tc.steps: step2. create builder.
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

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create sheet node and get sheet node, get pattern.
     * @tc.expected: related function is called.
     */
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    auto onAppear = []() {};
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        onAppear, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_FALSE(topSheetNode == nullptr);
    auto sheetNodeLayoutProperty = topSheetNode->GetLayoutProperty<SheetPresentationProperty>();
    auto style = sheetNodeLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->sheetMode.value(), SheetMode::MEDIUM);
    EXPECT_EQ(style->showDragBar.value(), true);

    /**
     * @tc.steps: step4. Change the sheetStyle.
     * @tc.expected: the sheetStyle is updated successfully
     */
    sheetStyle.sheetMode = SheetMode::AUTO;
    sheetStyle.showDragBar = false;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_FALSE(topSheetNode == nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->InitialLayoutProps();
    sheetStyle.sheetMode = SheetMode::MEDIUM;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->InitialLayoutProps();
    EXPECT_EQ(sheetPattern->GetTargetId(), topSheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId());
    sheetNodeLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetNodeLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->sheetMode.value(), SheetMode::MEDIUM);
    EXPECT_EQ(style->showDragBar.value(), false);

    /**
     * @tc.steps: step4. Change the backgroundColor.
     * @tc.expected: the backgroundColor is updated successfully
     */
    sheetStyle.backgroundColor = Color::GREEN;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_FALSE(topSheetNode == nullptr);
    EXPECT_EQ(sheetNode->GetRenderContext()->GetBackgroundColorValue(), Color::GREEN);
    overlayManager->OnBindSheet(!isShow, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, targetNode);
}

/**
 * @tc.name: DestroySheet003
 * @tc.desc: Test OverlayManager::DestroySheet func
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, DestroySheet003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create builder.
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

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create sheet node.
     * @tc.expected: Make sure the modalStack holds the sheetNode.
     */
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_EQ(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);

    /**
     * @tc.steps: step4. run destroySheet func
     */
    sheetNode->tag_ = V2::SHEET_MASK_TAG;
    EXPECT_NE(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);
    overlayManager->DestroySheet(sheetNode, targetId);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    sheetNode->tag_ = V2::SHEET_PAGE_TAG;
    sheetNode->GetPattern<SheetPresentationPattern>()->targetId_ = targetId - 1;
    EXPECT_NE(sheetNode->GetPattern<SheetPresentationPattern>()->targetId_, targetId);
    overlayManager->DestroySheet(sheetNode, targetId);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    sheetNode->tag_ = V2::SHEET_PAGE_TAG;
    sheetNode->GetPattern<SheetPresentationPattern>()->targetId_ = targetId;
    overlayManager->DestroySheet(sheetNode, targetId);
    EXPECT_TRUE(overlayManager->modalStack_.empty());

    auto targetNodeSecond = CreateTargetNode();
    targetNodeSecond->MountToParent(stageNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNodeSecond);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    overlayManager->DestroySheet(sheetNode, targetId);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: BindSheet003
 * @tc.desc: Test OverlayManager::BindSheet destroy sheet node.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindSheet003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create builder.
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

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create sheet node.
     * @tc.expected: Make sure the modalStack holds the sheetNode.
     */
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_EQ(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);

    /**
     * @tc.steps: step4. destroy modal page.
     * @tc.expected: destroy modal successfully.
     */
    auto onDisappear = []() {};
    overlayManager->OnBindSheet(
        !isShow, nullptr, nullptr, nullptr, sheetStyle, nullptr, onDisappear, nullptr, targetNode);
    overlayManager->modalList_.emplace_back(AceType::WeakClaim(AceType::RawPtr(stageNode)));
    overlayManager->DestroySheet(sheetNode, targetId);
    overlayManager->FindWindowScene(targetNode);
    overlayManager->DeleteModal(targetId);
    EXPECT_TRUE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: GetSheetMask001
 * @tc.desc: Test OverlayManager::GetSheetMask.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, GetSheetMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create builder.
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

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step3. create sheet node.
     * @tc.expected: Make sure the modalStack holds the sheetNode.
     */
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_EQ(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);

    /**
     * @tc.steps: step4. Run GetSheetMask Func.
     * @tc.expected: if the color is set, Make sure the maskNode is exist and it's color is right.
     */
    auto maskNode = overlayManager->GetSheetMask(sheetNode);
    EXPECT_FALSE(maskNode == nullptr);
    auto onDisappear = []() {};
    overlayManager->OnBindSheet(
        !isShow, nullptr, nullptr, nullptr, sheetStyle, nullptr, onDisappear, nullptr, targetNode);
    sheetStyle.maskColor = Color::BLUE;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_FALSE(sheetNode == nullptr);
    EXPECT_EQ(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);
    maskNode = overlayManager->GetSheetMask(sheetNode);
    EXPECT_FALSE(maskNode == nullptr);
    EXPECT_EQ(maskNode->GetTag(), V2::SHEET_MASK_TAG);
    EXPECT_EQ(maskNode->GetRenderContext()->GetBackgroundColorValue(), Color::BLUE);

    /**
     * @tc.steps: step5. destroy sheetNode.
     * @tc.expected: Make sure the maskNode is destroyed.
     */
    overlayManager->OnBindSheet(
        !isShow, nullptr, nullptr, nullptr, sheetStyle, nullptr, onDisappear, nullptr, targetNode);
    overlayManager->modalList_.emplace_back(AceType::WeakClaim(AceType::RawPtr(stageNode)));
    overlayManager->DestroySheet(sheetNode, targetId);
    overlayManager->FindWindowScene(targetNode);
    overlayManager->DeleteModal(targetId);
    EXPECT_TRUE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: PopupTest002
 * @tc.desc: Test OverlayManager::PopupEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, PopupTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and popupInfo.
     */
    std::vector<RefPtr<FrameNode>> targetNodes;
    std::vector<PopupInfo> popups;
    for (int i = 0; i < 2; i++) {
        auto targetNode = CreateTargetNode();
        ASSERT_NE(targetNode, nullptr);
        targetNodes.emplace_back(targetNode);
        auto targetId = targetNodes[i]->GetId();
        auto targetTag = targetNodes[i]->GetTag();

        auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
        auto popupNode = FrameNode::CreateFrameNode(
            V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
        PopupInfo popupInfo;
        popupInfo.popupId = popupId;
        popupInfo.popupNode = popupNode;
        popupInfo.target = targetNode;
        popupInfo.markNeedUpdate = true;
        popupInfo.isBlockEvent = false;
        popups.emplace_back(popupInfo);
    }
    /**
     * @tc.steps: step2. create overlayManager and call ShowPopup.
     * @tc.expected: Push popup successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto targetId1 = targetNodes[0]->GetId();
    auto targetId2 = targetNodes[1]->GetId();
    overlayManager->ShowPopup(targetId1, popups[0]);
    EXPECT_TRUE(overlayManager->popupMap_[targetId1].isCurrentOnShow);
    overlayManager->ShowPopup(targetId2, popups[1]);
    EXPECT_TRUE(overlayManager->popupMap_[targetId2].isCurrentOnShow);
    /**
     * @tc.steps: step3. call HideCustomPopups when childCount is 2
     * @tc.expected: popupMap's data is updated successfully
     */
    overlayManager->HideCustomPopups();
    EXPECT_FALSE(overlayManager->popupMap_.empty());
    EXPECT_FALSE(rootNode->GetChildren().empty());
    /**
     * @tc.steps: step4. call RemoveOverlay when childCount is 2
     * @tc.expected: remove one popupNode at a time
     */
    overlayManager->HidePopup(targetId1, popups[0]);
    overlayManager->HidePopup(targetId2, popups[1]);
    EXPECT_TRUE(overlayManager->RemoveOverlay(false));
    EXPECT_FALSE(overlayManager->popupMap_.empty());
    overlayManager->ErasePopup(targetId1);
    overlayManager->ErasePopup(targetId2);
    EXPECT_TRUE(overlayManager->popupMap_.empty());
    /**
     * @tc.steps: step5. call HideCustomPopups when popupMap_ is empty
     * @tc.expected: function exits normally
     */
    overlayManager->HideCustomPopups();
    EXPECT_TRUE(overlayManager->popupMap_.empty());
}
/**
 * @tc.name: PopupTest003
 * @tc.desc: Test OverlayManager::HidePopup.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, PopupTest003, TestSize.Level1)
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
    EXPECT_TRUE(iter == rootChildren.begin());
}
/**
 * @tc.name: MenuTest001
 * @tc.desc: Test OverlayManager::ShowMenu.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, MenuTest001, TestSize.Level1)
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
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    overlayManager->ShowMenuInSubWindow(rootNode->GetId(), MENU_OFFSET, menuNode);
    overlayManager->HideMenuInSubWindow(menuNode, rootNode->GetId());
    overlayManager->HideMenuInSubWindow();
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    overlayManager->SetShowMenuAnimation(menuNode, true);
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
HWTEST_F(OverlayManagerTestNg, MenuTest002, TestSize.Level1)
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
    overlayManager->HideAllMenus();
    overlayManager->CleanMenuInSubWindow();
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
HWTEST_F(OverlayManagerTestNg, MenuTest003, TestSize.Level1)
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
    previewContext->UpdateTransformScale(VectorF(0.0f, 0.0f));
    menuContext->UpdateTransformScale(VectorF(0.0f, 0.0f));

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
     * @tc.expected: the preview node will remove
     */
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 2);
    overlayManager->PopMenuAnimation(menuWrapperNode, false);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MenuTest004
 * @tc.desc: Test OverlayManager::CleanMenuInSubWindowWithAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, MenuTest004, TestSize.Level1)
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
 * @tc.desc: Test OverlayManager::SetShowMenuAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, MenuTest005, TestSize.Level1)
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
    focusHub->parentFocusable_ = false;
    menuPattern->SetPreviewMode(MenuPreviewMode::CUSTOM);
    /**
     * @tc.steps: step2. call SetShowMenuAnimation and call StartShowAnimation of menu pattern
     * @tc.expected: the isFirstShow_ of preview pattern true and parentFocusable_ of menuWrapper's focus hub is true
     */
    overlayManager->SetShowMenuAnimation(menuWrapperNode, false);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    menuWrapperPattern->StartShowAnimation();
    pipeline->taskExecutor_ = nullptr;

    EXPECT_TRUE(focusHub->parentFocusable_);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(previewPattern, nullptr);
    EXPECT_TRUE(previewPattern->isFirstShow_);
}

/**
 * @tc.name: DeleteModal001
 * @tc.desc: Test OverlayManager::DeleteModal
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, DeleteModal001, TestSize.Level1)
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
    overlayManager->ShowToast(MESSAGE, DURATION, BOTTOMSTRING, true);
    EXPECT_FALSE(overlayManager->toastMap_.empty());

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

    /**
     * @tc.steps: step3. create sheet node and run DeleteModal.
     */
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    overlayManager->modalList_.emplace_back(nullptr);
    overlayManager->DeleteModal(targetId);
    EXPECT_EQ(overlayManager->modalList_.size(), 1);

    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    overlayManager->modalList_.emplace_back(nullptr);
    overlayManager->DeleteModal(targetId + 1);
    EXPECT_EQ(overlayManager->modalList_.size(), 3);
}

/**
 * @tc.name: PopupTest004
 * @tc.desc: Test OverlayManager::HideAllPopups when useCustom is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, PopupTest004, TestSize.Level1)
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
    EXPECT_FALSE(rootNode->GetChildren().empty());
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
 * @tc.name: RemoveOverlayTest001
 * @tc.desc: Test OverlayManager::RemoveOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, RemoveOverlayTest001, TestSize.Level1)
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
HWTEST_F(OverlayManagerTestNg, RemoveOverlayTest002, TestSize.Level1)
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
    overlayManager->BindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    EXPECT_TRUE(overlayManager->RemoveOverlay(false));

    /**
     * @tc.steps: step4. Change the ModalTransition and Call RemoveModalInOverlay.
     * @tc.expected: remove successfully.
     */
    modalStyle.modalTransition = ModalTransition::ALPHA;
    overlayManager->BindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, targetNode);
    EXPECT_TRUE(overlayManager->RemoveModalInOverlay());
}

/**
 * @tc.name: ToastShowModeTest001
 * @tc.desc: Test OverlayManager::ShowToast with showMode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, ToastShowModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast node with showMode, and show it.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    MockPipelineContext::GetCurrent()->rootNode_ = rootNode;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowToast(MESSAGE, DURATION, BOTTOMSTRING, true, ToastShowMode::TOP_MOST);
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
    EXPECT_FALSE(pattern->IsDefaultToast());
    EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(toastNode->CreateLayoutWrapper(), DirtySwapConfig()));
    EXPECT_EQ(toastContext->GetOffset()->GetX().ConvertToPx(), 360.0);
    EXPECT_EQ(toastContext->GetOffset()->GetY().ConvertToPx(), 1280.0);
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
HWTEST_F(OverlayManagerTestNg, ToastTest001, TestSize.Level1)
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
    overlayManager->ShowToast(MESSAGE, DURATION, BOTTOMSTRING, true);
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
HWTEST_F(OverlayManagerTestNg, ToastTest002, TestSize.Level1)
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
    overlayManager->ShowToast(MESSAGE, DURATION, BOTTOMSTRING, true);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    /**
     * @tc.steps: step2. call PopToast.
     * @tc.expected: toastMap_ is empty
     */
    overlayManager->PopToast(toastId);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
}
/**
 * @tc.name: DialogTest001
 * @tc.desc: Test OverlayManager::ShowCustomDialog->CloseDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, DialogTest001, TestSize.Level1)
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
HWTEST_F(OverlayManagerTestNg, DialogTest002, TestSize.Level1)
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
HWTEST_F(OverlayManagerTestNg, DialogTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;

    DatePickerSettingData datePickerSettingData;
    datePickerSettingData.isLunar = false;
    datePickerSettingData.showTime = true;
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

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowDateDialog(dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step3. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(
        dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent, dialogCancelEvent);
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
    overlayManager->ShowTimeDialog(
        dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    EXPECT_TRUE(overlayManager->RemoveOverlay(true));
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    overlayManager->ShowTimeDialog(
        dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_TRUE(overlayManager->RemoveOverlay(true));
}

/**
 * @tc.name: SheetPresentationPattern1
 * @tc.desc: Test SheetPresentationPattern create sheet page.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, SheetPresentationPattern1, TestSize.Level1)
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
     * @tc.steps: step2. create builder.
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

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    bool isShow = true;
    auto onAppear = []() {};
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        onAppear, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_FALSE(topSheetNode == nullptr);
    auto sheetNodeLayoutProperty = topSheetNode->GetLayoutProperty<SheetPresentationProperty>();
    auto style = sheetNodeLayoutProperty->GetSheetStyle();
    EXPECT_EQ(style->sheetMode.value(), SheetMode::MEDIUM);
    EXPECT_EQ(style->showDragBar.value(), true);

    sheetStyle.sheetMode = SheetMode::LARGE;
    sheetStyle.showDragBar = false;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, targetNode);
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_FALSE(topSheetNode == nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    EXPECT_EQ(sheetPattern->GetTargetId(), topSheetNode->GetPattern<SheetPresentationPattern>()->GetTargetId());
    sheetPattern->InitPanEvent();
    GestureEvent info;
    sheetPattern->HandleDragUpdate(info);
    sheetPattern->HandleDragEnd({});
    sheetNodeLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    style = sheetNodeLayoutProperty->GetSheetStyle();
    auto sheetLayoutAlgorithm = sheetPattern->CreateLayoutAlgorithm();
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(sheetNode)), geometryNode->Clone(), sheetNodeLayoutProperty->Clone());
    EXPECT_FALSE(layoutWrapper == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(sheetLayoutAlgorithm));
    DirtySwapConfig dirtySwapConfig;
    EXPECT_TRUE(sheetPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
    sheetPattern->InitPanEvent();
    EXPECT_EQ(style->sheetMode.value(), SheetMode::LARGE);
    EXPECT_EQ(style->showDragBar.value(), false);
}

/**
 * @tc.name: OnDialogCloseEvent
 * @tc.desc: Test OverlayManager::OnDialogCloseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, OnDialogCloseEvent, TestSize.Level1)
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
 * @tc.name: BindSheet004
 * @tc.desc: Test OverlayManager::BindSheet create center sheet page.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindSheet004, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    // assert
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test sheetThemeType_ = popup, sheetStyle.sheetType = center.
     * @tc.expected: height = (setHeight + screenHeight) / 2.
     */
    topSheetPattern->sheetThemeType_ = "popup";
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    topSheetPattern->pageHeight_ = 1000;
    auto setSheetSize = SizeF({ 500, 500 });
    topSheetNode->GetGeometryNode()->SetFrameSize(setSheetSize);
    overlayManager->sheetHeight_ = 0;
    overlayManager->ComputeSheetOffset(sheetStyle, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 750));
}

/**
 * @tc.name: BindSheet005
 * @tc.desc: Test OverlayManager::BindSheet create detent sheet page.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindSheet005, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test sheetThemeType_ = auto, sheetStyle.sheetType = bottom, set pageHeight = 1000.
     */
    topSheetPattern->sheetThemeType_ = "auto";
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    topSheetPattern->pageHeight_ = 1000;

    /**
     * @tc.steps: step4. test sheetStyle.detents.sheetMode has value, sheetMode = MEDIUM.
     * @tc.expected: height = pageHeight_*0.6 = 1000*0.6 = 600.
     */
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    overlayManager->sheetHeight_ = 0;
    overlayManager->ComputeSheetOffset(sheetStyle, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 600));
    sheetStyle.detents.clear();

    /**
     * @tc.steps: step5. test sheetStyle.detents.sheetMode has value, sheetMode = MEDIUM.
     * @tc.expected: height = pageHeight_-8 = 1000-8 = 992.
     */
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    overlayManager->sheetHeight_ = 0;
    overlayManager->ComputeSheetOffset(sheetStyle, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 992));

    /**
     * @tc.steps: step6. test sheetStyle.detents.height has value, height unit is %.
     * @tc.expected: height = pageHeight*0.5 = 1000*0.5 = 500.
     */
    sheetStyle.detents.clear();
    detent.sheetMode = std::nullopt;
    Dimension detentHeight { 0.5, DimensionUnit::PERCENT };
    detent.height = detentHeight;
    sheetStyle.detents.emplace_back(detent);
    overlayManager->sheetHeight_ = 0;
    overlayManager->ComputeSheetOffset(sheetStyle, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 500));

    /**
     * @tc.steps: step7. test sheetStyle.detents.height has value, height unit is vp.
     * @tc.expected: height = setHeight = 600.
     */
    sheetStyle.detents.clear();
    detent.height->unit_ = DimensionUnit::VP;
    detent.height->value_ = 600;
    sheetStyle.detents.emplace_back(detent);
    overlayManager->sheetHeight_ = 0;
    overlayManager->ComputeSheetOffset(sheetStyle, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 600));

    /**
     * @tc.steps: step8. test sheetStyle.detents.height has value, height unit is vp, setHeight > maxHeight.
     * @tc.expected: height = setHeight = maxHeight = pageHeight-8 = 992.
     */
    sheetStyle.detents.clear();
    detent.height->unit_ = DimensionUnit::VP;
    detent.height->value_ = 1500;
    sheetStyle.detents.emplace_back(detent);
    overlayManager->sheetHeight_ = 0;
    overlayManager->ComputeSheetOffset(sheetStyle, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 992));

    /**
     * @tc.steps: step9. test sheetStyle.detents.height has value, height unit is vp, setHeight < 0.
     * @tc.expected: height = setHeight = maxHeight = pageHeight-8 = 992.
     */
    sheetStyle.detents.clear();
    detent.height->unit_ = DimensionUnit::VP;
    detent.height->value_ = -100;
    sheetStyle.detents.emplace_back(detent);
    overlayManager->sheetHeight_ = 0;
    overlayManager->ComputeSheetOffset(sheetStyle, topSheetNode);
    EXPECT_TRUE(NearEqual(overlayManager->sheetHeight_, 992));
}

/**
 * @tc.name: BindSheet006
 * @tc.desc: Test OverlayManager::PlayBubbleStyleSheetTransition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, BindSheet006, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test PlayBubbleStyleSheetTransition().
     */
    overlayManager->PlayBubbleStyleSheetTransition(topSheetNode, true);
    EXPECT_EQ(topSheetPattern->height_, overlayManager->sheetHeight_);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test SheetPresentationPattern::HandleDragUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, HandleDragUpdate001, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);
    topSheetPattern->OnDirtyLayoutWrapperSwap(topSheetNode->CreateLayoutWrapper(), DirtySwapConfig());

    /**
     * @tc.steps: step3. Init height , sheetDetentHeight and currentOffset, set minDelta < 0.
     * @tc.expected: currentOffset is -5.
     */
    topSheetPattern->sheetDetentHeight_.emplace_back(20);
    topSheetPattern->sheetDetentHeight_.emplace_back(30);
    topSheetPattern->height_ = 20;
    topSheetPattern->pageHeight_ = 50;
    topSheetPattern->sheetMaxHeight_ = 30;
    topSheetPattern->OnCoordScrollStart();
    GestureEvent info;
    info.SetMainDelta(MINUS_HEIGHT);
    topSheetPattern->HandleDragUpdate(info);
    EXPECT_TRUE(NearEqual(topSheetPattern->currentOffset_, -5));

    /**
     * @tc.steps: step4. Init height , sheetDetentHeight and set currentOffset < 0,
     * @tc.expected: currentOffset = height_ - sheetMaxHeight_.
     */
    topSheetPattern->currentOffset_ = -5;
    topSheetPattern->HandleDragUpdate(info);
    EXPECT_TRUE(NearEqual(topSheetPattern->currentOffset_, -10));

    /**
     * @tc.steps: step5. Do OnCoordScrollUpdate when scrollOffset < 0 .
     * @tc.expected: return true
     */
    topSheetPattern->OnCoordScrollEnd(*topSheetPattern->sheetDetentHeight_.end());
    auto ret = topSheetPattern->OnCoordScrollUpdate(*topSheetPattern->sheetDetentHeight_.end());
    EXPECT_TRUE(ret);
}
/**
 * @tc.name: TestBindSheet
 * @tc.desc: Test SheetPresentationPattern::AvoidSafeArea().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, TestSheetAvoidSafeArea1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet node and initialize sheet pattern.
     */
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(-1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto dragBarNode = FrameNode::CreateFrameNode(
        "SheetDragBar", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    dragBarNode->MountToParent(sheetNode);
    scroll->MountToParent(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800, 2000));
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    MockPipelineContext::GetCurrent()->SetRootSize(800, 2000);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    SafeAreaInsets::Inset upKeyboard { 0, 200 };
    sheetPattern->pageHeight_ = 2000;
    sheetPattern->sheetHeight_ = 2000;
    /**
     * @tc.steps: step2. keyboard up, and sheet will goes to correct position.
     * @tc.cases: case1. keyboard up, but sheet needs not up beacure hsafe is enough.
     */
    safeAreaManager->keyboardInset_ = upKeyboard;
    textFieldManager->SetClickPosition(Offset(0, 1000));
    sheetPattern->height_ = 1000;
    sheetPattern->AvoidSafeArea();
    EXPECT_EQ(static_cast<int>(renderContext->GetTransformTranslate()->y.ConvertToPx()), sheetPattern->height_);
    EXPECT_EQ(sheetPattern->keyboardHeight_, 200);
    /**
     * @tc.cases: case2. keyboard up, sheet needs not up and does not reach LARGE.
     */
    sheetPattern->keyboardHeight_ = 0;
    sheetPattern->height_ = 100;
    textFieldManager->SetClickPosition(Offset(0, 1900));
    sheetPattern->AvoidSafeArea();
    EXPECT_EQ(static_cast<int>(renderContext->GetTransformTranslate()->y.ConvertToPx()),
        2000 - sheetPattern->height_ -
            (200 - (MockPipelineContext::GetCurrent()->GetRootHeight() - textFieldManager->GetClickPosition().GetY() -
                       textFieldManager->GetHeight())));
    /**
     * @tc.cases: case3. sheet height = 1900 - 8vp, sheet goes up to LARGE and need to scroll.
     */
    sheetPattern->keyboardHeight_ = 0;
    sheetPattern->height_ = 1950;
    textFieldManager->SetClickPosition(Offset(0, 1900));
    sheetPattern->AvoidSafeArea();
    // LARGE : translate offset is 8vp, need to scroll with 20 + hsafe,
    EXPECT_EQ(static_cast<int>(renderContext->GetTransformTranslate()->y.ConvertToPx()), 8);
    EXPECT_TRUE(sheetPattern->isScrolling_);
    /**
     * @tc.cases: case4. softkeyboard is down.
     */
    SafeAreaInsets::Inset downKeyboard { 0, 0 };
    safeAreaManager->keyboardInset_ = downKeyboard;
    sheetPattern->AvoidSafeArea();
    EXPECT_EQ(static_cast<int>(renderContext->GetTransformTranslate()->y.ConvertToPx()), 2000 - 1950);
    EXPECT_EQ(sheetPattern->keyboardHeight_, 0);
    EXPECT_FALSE(sheetPattern->isScrolling_);
}

/**
 * @tc.name: TestBindSheet
 * @tc.desc: Test SheetPresentationPattern::OnDirtyLayoutWrapperSwap() and root Rotates.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, TestSheetAvoidSafeArea2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet node and initialize sheet pattern.
     */
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(-1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto dragBarNode = FrameNode::CreateFrameNode(
        "SheetDragBar", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto contentNode = FrameNode::CreateFrameNode(
        "SheetDragBar", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scroll);
    scroll->MountToParent(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SheetStyle sheetStyle;
    CreateSheetStyle(sheetStyle);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    geometryNode->SetFrameSize(SizeF(800, 2000));
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    MockPipelineContext::GetCurrent()->SetRootSize(800, 2000);
    sheetPattern->pageHeight_ = 2000;
    sheetPattern->sheetHeight_ = 2000;
    sheetPattern->height_ = 500;
    auto sheetLayoutAlgorithm = sheetPattern->CreateLayoutAlgorithm();
    AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetLayoutAlgorithm)->sheetMaxHeight_ = 500;
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(sheetLayoutAlgorithm));
    /**
     * @tc.cases: case1. window rotates after layout.
     */
    sheetPattern->OnWindowSizeChanged(2000, 800, WindowSizeChangeReason::ROTATION);
    sheetPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, DirtySwapConfig());
    EXPECT_EQ(static_cast<int>(renderContext->GetTransformTranslate()->y.ConvertToPx()),
        sheetPattern->pageHeight_ - sheetPattern->height_);
    /**
     * @tc.cases: case2. window rotates to vertical screen.
     */
    sheetPattern->OnWindowSizeChanged(800, 2000, WindowSizeChangeReason::RESIZE);
    sheetPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, DirtySwapConfig());
    EXPECT_FALSE(sheetPattern->windowRotate_);
}

/**
 * @tc.name: TestBindSheet
 * @tc.desc: Test Sheet avoids aiBar.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, TestSheetAvoidaiBar, TestSize.Level1)
{
    auto operationColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    NG::SheetStyle style;
    auto sheetNode = SheetView::CreateSheetPage(0, "", operationColumn, operationColumn, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto scrollNode = AceType::DynamicCast<FrameNode>(sheetNode->GetChildAtIndex(1));
    ASSERT_NE(scrollNode, nullptr);
    auto scrollLayoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(scrollLayoutProperty, nullptr);
    EXPECT_EQ(scrollLayoutProperty->GetScrollContentEndOffsetValue(.0f),
        PipelineContext::GetCurrentContext()->GetSafeArea().bottom_.Length());
}

/**
 * @tc.name: DialogTest004
 * @tc.desc: Test OverlayManager::GetDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, DialogTest004, TestSize.Level1)
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
HWTEST_F(OverlayManagerTestNg, DialogTest005, TestSize.Level1)
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
 * @tc.name: SheetPresentationPattern2
 * @tc.desc: Test SheetPresentationPattern::CheckSheetHeightChange().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, SheetPresentationPattern2, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test CheckSheetHeightChange().
     */
    topSheetPattern->pageHeight_ = 1000;
    topSheetPattern->sheetMaxHeight_ = 1000;
    topSheetPattern->isFirstInit_ = true;
    topSheetPattern->InitialLayoutProps();
    EXPECT_FALSE(topSheetPattern->isFirstInit_);
    topSheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    topSheetPattern->CheckSheetHeightChange();
    EXPECT_EQ(topSheetPattern->sheetType_, SheetType::SHEET_BOTTOM);
}

/**
 * @tc.name: SheetPresentationPattern3
 * @tc.desc: Test SheetPresentationPattern::InitSheetDetents().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, SheetPresentationPattern3, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test InitSheetDetents(), sheetType = BOTTOM.
     */
    topSheetPattern->pageHeight_ = 1000;
    topSheetPattern->sheetMaxHeight_ = 1000;
    topSheetPattern->sheetThemeType_ = "auto";
    auto sheetLayoutProperty = topSheetNode->GetLayoutProperty<SheetPresentationProperty>();
    EXPECT_FALSE(sheetLayoutProperty == nullptr);

    /**
     * @tc.steps: step4. test sheetMode has value.
     * @tc.expected: sheetStyle.detents = {600,992}.
     */
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    topSheetPattern->InitSheetDetents();
    EXPECT_TRUE(NearEqual(topSheetPattern->sheetDetentHeight_.front(), 600));
    EXPECT_TRUE(NearEqual(topSheetPattern->sheetDetentHeight_.back(), 992));

    /**
     * @tc.steps: step5. test sheetStyle.height has value.
     */
    sheetStyle.detents.clear();
    SheetHeight detent1;
    Dimension detentHeight { 0.5, DimensionUnit::PERCENT };
    detent1.height = detentHeight;
    sheetStyle.detents.emplace_back(detent1);

    /**
     * @tc.steps: step6. set height > maxHeight.
     * @tc.expected: height = pageHeight_-8 = 992.
     */
    detent1.height->unit_ = DimensionUnit::VP;
    detent1.height->value_ = 1200;
    sheetStyle.detents.emplace_back(detent1);

    /**
     * @tc.steps: step6. set height < 0.
     * @tc.expected: height = pageHeight_-8 = 992.
     */
    detent1.height->unit_ = DimensionUnit::VP;
    detent1.height->value_ = -10;
    sheetStyle.detents.emplace_back(detent1);

    /**
     * @tc.steps: step7. InitSheetDetents(), sheetStyle.detents push{500,992,992}.
     * @tc.expected: sheetStyle.detents = {500,992}.
     */
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    topSheetPattern->InitSheetDetents();
    EXPECT_TRUE(NearEqual(topSheetPattern->sheetDetentHeight_.size(), 2));
    EXPECT_TRUE(NearEqual(topSheetPattern->sheetDetentHeight_.front(), 500));
    EXPECT_TRUE(NearEqual(topSheetPattern->sheetDetentHeight_.back(), 992));

    /**
     * @tc.steps: step8. test InitSheetDetents(), sheetType = CENTER.
     * @tc.expected: height = (centerHeight_+pageHeight_)/2 = 750.
     */
    sheetStyle.detents.clear();
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    topSheetPattern->sheetThemeType_ = "popup";
    topSheetPattern->centerHeight_ = 500;
    topSheetPattern->InitSheetDetents();
    EXPECT_TRUE(NearEqual(topSheetPattern->sheetDetentHeight_.front(), 750));
}

/**
 * @tc.name: SheetPresentationPattern4
 * @tc.desc: Test SheetPresentationPattern::InitialSingleGearHeight().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, SheetPresentationPattern4, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test InitialSingleGearHeight().
     */
    topSheetPattern->pageHeight_ = 1000;
    topSheetPattern->sheetMaxHeight_ = 1000;
    topSheetPattern->isFirstInit_ = true;

    /**
     * @tc.steps: step4. set sheetStyle.height = 0.5, unit is %.
     * @tc.expected: height = 1000*0.5 = 500.
     */
    Dimension singleHeight { 0.5, DimensionUnit::PERCENT };
    sheetStyle.height = singleHeight;
    EXPECT_TRUE(NearEqual(topSheetPattern->InitialSingleGearHeight(sheetStyle), 500));

    /**
     * @tc.steps: step5. set sheetStyle.height > maxHeight.
     * @tc.expected: height = 1000-8 = 992.
     */
    sheetStyle.height->unit_ = DimensionUnit::VP;
    sheetStyle.height->value_ = 1200;
    EXPECT_TRUE(NearEqual(topSheetPattern->InitialSingleGearHeight(sheetStyle), 992));

    /**
     * @tc.steps: step6. set sheetStyle.height < 0.
     * @tc.expected: height = 1000-8 = 992.
     */
    sheetStyle.height->unit_ = DimensionUnit::VP;
    sheetStyle.height->value_ = -10;
    EXPECT_TRUE(NearEqual(topSheetPattern->InitialSingleGearHeight(sheetStyle), 992));
}

/**
 * @tc.name: Bindsheet007
 * @tc.desc: Test OverlayManager::DismissSheet().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, Bindsheet007, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test DismissSheet().
     * @tc.expected: callback is false.
     */
    overlayManager->DismissSheet();
    EXPECT_FALSE(topSheetPattern->callback_);
}

/**
 * @tc.name: SheetPresentationPattern5
 * @tc.desc: Test SheetPresentationPattern::BubbleStyleSheetTransition().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, SheetPresentationPattern5, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test SheetPresentationPattern::BubbleStyleSheetTransition().
     * @tc.expected: callback is false.
     */
    topSheetPattern->BubbleStyleSheetTransition(false);
    EXPECT_FALSE(topSheetPattern->callback_);
}

/**
 * @tc.name: SheetPresentationPattern6
 * @tc.desc: Test SheetPresentationPattern::ClipSheetNode().
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestNg, SheetPresentationPattern6, TestSize.Level1)
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
        nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test clip sheet node, set sheetSize.
     * @tc.expected: clipPath is as same as set.
     */
    auto sheetSize = SizeF(1000, 720);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    auto sheetRadius = sheetTheme->GetSheetRadius();
    std::string substring = "720.000000 Z";

    /**
     * @tc.steps: step4. test clipPath.
     */
    auto popupPath = topSheetPattern->GetPopupStyleSheetClipPath(sheetSize, sheetRadius);
    EXPECT_EQ(popupPath.length(), 412);
    EXPECT_EQ(popupPath.substr(400, 12), substring);
    auto centerPath = topSheetPattern->GetCenterStyleSheetClipPath(sheetSize, sheetRadius);
    EXPECT_EQ(centerPath.length(), 297);
    EXPECT_EQ(centerPath.substr(285, 12), substring);
    auto bottomPath = topSheetPattern->GetBottomStyleSheetClipPath(sheetSize, sheetRadius);
    EXPECT_EQ(bottomPath.length(), 190);
    EXPECT_EQ(bottomPath.substr(178, 12), substring);
}

} // namespace OHOS::Ace::NG
