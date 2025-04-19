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
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
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
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const std::string TEXT_TAG = "text";
} // namespace

class OverlayManagerTestOneNG : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static RefPtr<FrameNode> CreateRootNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    int32_t minPlatformVersion_ = 0;
};

void OverlayManagerTestOneNG::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayManagerTestOneNG::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void OverlayManagerTestOneNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>(V2::STAGE_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
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
void OverlayManagerTestOneNG::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayManagerTestOneNG::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> OverlayManagerTestOneNG::CreateRootNode()
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    return frameNode;
}

void OverlayManagerTestOneNG::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayManagerTestOneNG::CreateSheetBuilder()
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
 * @tc.name: GetModalNodeInStack001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, GetModalNodeInStack001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. stack is empty.
     */
    std::stack<WeakPtr<FrameNode>> stack;
    auto ret = overlayManager->GetModalNodeInStack(stack);
    EXPECT_EQ(ret, nullptr);
    /**
     * @tc.steps: step2. stack is not empty.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    overlayManager->PlayTransitionEffectIn(frameNode);
    auto textNode = Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(frameNode));
    stack.emplace(textNode);
    ret = overlayManager->GetModalNodeInStack(stack);
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: BindContentCover001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, BindContentCover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    targetNode->MountToParent(stageNode);
    stageNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    /**
     * @tc.steps: step2. scall OnBindContentCover.
     */
    ModalStyle modalStyle;
    CreateSheetBuilder();
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    overlayManager->OnBindContentCover(false, nullptr, std::move(builderFunc_), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    auto pageNode1 = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(pageNode1, nullptr);
    overlayManager->modalStack_.emplace(pageNode1);
    CreateSheetBuilder();
    overlayManager->isAllowedBeCovered_ = false;
    modalStyle.backgroundColor = std::make_optional(Color(100));
    overlayManager->OnBindContentCover(true, nullptr, std::move(builderFunc_), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: SheetSpringBack001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, SheetSpringBack001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call SheetSpringBack function.
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    overlayManager->dismissTarget_ = DismissTarget(SheetKey(1));
    overlayManager->sheetMap_.emplace(SheetKey(1), Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(stageNode)));
    overlayManager->SheetSpringBack();
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, -1, AceType::MakeRefPtr<SheetPresentationPattern>(-1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->dismissTarget_ = DismissTarget(SheetKey(-1));
    overlayManager->sheetMap_.emplace(SheetKey(-1), Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(sheetNode)));
    overlayManager->SheetSpringBack();
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->isDismissProcess_);
}

/**
 * @tc.name: DismissContentCover001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, DismissContentCover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call DismissContentCover function.
     */
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    overlayManager->DismissContentCover();
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->modalList_.clear();
    overlayManager->DismissContentCover();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> node = nullptr;
    overlayManager->modalList_.emplace_back(node);
    overlayManager->modalList_.emplace_back(sheetNode);
    overlayManager->dismissTarget_ = DismissTarget(1);
    overlayManager->DismissContentCover();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(frameNode, nullptr);
    overlayManager->modalList_.clear();
    overlayManager->modalList_.emplace_back(frameNode);
    overlayManager->DismissContentCover();
    auto modelNode1 = FrameNode::CreateFrameNode(V2::MODAL_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ModalPresentationPattern>(2, ModalTransition::NONE, nullptr));
    ASSERT_NE(modelNode1, nullptr);
    overlayManager->modalList_.clear();
    overlayManager->dismissTarget_ = DismissTarget(2);
    overlayManager->modalList_.emplace_back(frameNode);
    overlayManager->modalList_.emplace_back(modelNode1);
    overlayManager->DismissContentCover();
    auto modelNode2 = FrameNode::CreateFrameNode(V2::MODAL_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ModalPresentationPattern>(1, ModalTransition::NONE, nullptr));
    ASSERT_NE(modelNode2, nullptr);
    auto childrens = sheetNode->ModifyChildren();
    childrens.emplace_back(modelNode2);
    overlayManager->dismissTarget_ = DismissTarget(1);
    overlayManager->DismissContentCover();
    EXPECT_NE(overlayManager->lastModalNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RemoveOfOverlayManager001
 * @tc.desc: Test remove function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, RemoveOfOverlayManager001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call remove function.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(frameNode, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto modelNode = FrameNode::CreateFrameNode(
        V2::MODAL_PAGE_TAG, 2, AceType::MakeRefPtr<ModalPresentationPattern>(2, ModalTransition::NONE, nullptr));
    ASSERT_NE(modelNode, nullptr);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> node = nullptr;
    overlayManager->modalList_.emplace_back(node);
    overlayManager->modalList_.emplace_back(frameNode);
    overlayManager->modalList_.emplace_back(sheetNode);
    overlayManager->modalList_.emplace_back(modelNode);
    overlayManager->RemoveModal(2);
    overlayManager->RemoveSheetNode(modelNode);
    EXPECT_EQ(overlayManager->modalStack_.size(), 3);
}

/**
 * @tc.name: UpdateSheetPage001
 * @tc.desc: Test remove function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, UpdateSheetPage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(frameNode, nullptr);
    SheetStyle sheetStyle;
    overlayManager->UpdateSheetPage(frameNode, sheetStyle, 0, false, false, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->UpdateSheetPage(sheetNode, sheetStyle, 2, false, false, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr);
    auto sheetNodePattern = sheetNode->GetPattern<SheetPresentationPattern>();
    overlayManager->UpdateSheetPage(sheetNode, sheetStyle, 1, false, false, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(sheetNodePattern->GetSheetType(), SheetType::SHEET_BOTTOM);
}

/**
 * @tc.name: DismissSheet001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, DismissSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    overlayManager->DismissSheet();
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->sheetMap_.clear();
    overlayManager->DismissSheet();
    overlayManager->sheetMap_.clear();
    overlayManager->dismissTarget_ = DismissTarget(SheetKey(1));
    overlayManager->sheetMap_.emplace(SheetKey(-1), Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(sheetNode)));
    overlayManager->DismissSheet();
    EXPECT_FALSE(sheetNode->GetPattern<SheetPresentationPattern>()->isDismissProcess_);
}

/**
 * @tc.name: DismissSheet002
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, DismissSheet002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */

    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->sheetMap_.clear();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    overlayManager->dismissTarget_ = DismissTarget(SheetKey(2));
    overlayManager->sheetMap_.emplace(SheetKey(2), Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(stageNode)));
    overlayManager->DismissSheet();
    EXPECT_FALSE(sheetNode->GetPattern<SheetPresentationPattern>()->isDismissProcess_);
}

/**
 * @tc.name: CloseSheet001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, CloseSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    SheetKey sheetKey(1);
    overlayManager->CloseSheet(sheetKey);
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->sheetMap_.clear();
    overlayManager->CloseSheet(sheetKey);
    overlayManager->sheetMap_.emplace(SheetKey(-1), Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(sheetNode)));
    overlayManager->CloseSheet(sheetKey);
    overlayManager->sheetMap_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> node = nullptr;
    overlayManager->sheetMap_.emplace(SheetKey(1), Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(node)));
    overlayManager->CloseSheet(sheetKey);
    overlayManager->sheetMap_.clear();
    overlayManager->sheetMap_.emplace(SheetKey(1), Ace::Referenced::WeakClaim(Ace::Referenced::RawPtr(sheetNode)));
    overlayManager->CloseSheet(sheetKey);
    EXPECT_NE(overlayManager->sheetMap_.find(sheetKey), overlayManager->sheetMap_.end());
}

/**
 * @tc.name: CleanInvalidModalNode001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, CleanInvalidModalNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    Ace::WeakPtr<FrameNode> invalidNode = nullptr;
    overlayManager->CleanInvalidModalNode(invalidNode);
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->CleanInvalidModalNode(invalidNode);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 2, AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->modalStack_.emplace(stageNode);
    invalidNode = AceType::WeakClaim(AceType::RawPtr(stageNode));
    overlayManager->CleanInvalidModalNode(invalidNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: FireNavigationStateChange001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, FireNavigationStateChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto modelNode = FrameNode::CreateFrameNode(V2::MODAL_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ModalPresentationPattern>(1, ModalTransition::NONE, nullptr));
    ASSERT_NE(modelNode, nullptr);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(13);
    overlayManager->PlayAlphaModalTransition(modelNode, true);
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto stageManager = pipelineContext->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(pageNode, nullptr);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    pagePattern->isOnShow_ = false;
    stageManager->stageNode_->children_.emplace_back(pageNode);
    overlayManager->FireNavigationStateChange(true, nullptr);
    EXPECT_FALSE(stageManager->stageNode_->children_.empty());
}

/**
 * @tc.name: UpdatePopupMap001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, UpdatePopupMap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. create PopupInfo and call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = false;
    popupInfo.isCurrentOnShow = true;
    auto ret = overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: MountPopup001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, MountPopup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = false;
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);

    popupNode->MountToParent(rootNode);
    popupInfo.isCurrentOnShow = true;
    popupInfo.markNeedUpdate = true;
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);

    popupNode->MountToParent(rootNode);
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateShowInSubWindow(false);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdatePrimaryButtonShow(true);
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);
    EXPECT_TRUE(overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow);
}

/**
 * @tc.name: MountPopup002
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, MountPopup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    popupPattern->transitionStatus_ = TransitionStatus::ENTERING;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateShowInSubWindow(true);
    layoutProp->UpdateBlockEvent(true);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdatePrimaryButtonShow(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    paintProperty->UpdateUseCustom(true);
    popupInfo.focusable = true;
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);

    overlayManager->popupMap_.clear();
    popupNode->MountToParent(rootNode);
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    popupInfo.focusable = false;
    popupPattern->transitionStatus_ = TransitionStatus::ENTERING;
    layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    layoutProp->UpdateShowInSubWindow(true);
    layoutProp->UpdateBlockEvent(false);
    paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    paintProperty->UpdatePrimaryButtonShow(true);
    paintProperty->UpdateUseCustom(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);
    EXPECT_TRUE(overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow);
}

/**
 * @tc.name: MountPopup003
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, MountPopup003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    popupInfo.focusable = false;
    popupPattern->transitionStatus_ = TransitionStatus::ENTERING;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateShowInSubWindow(true);
    layoutProp->UpdateBlockEvent(false);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdatePrimaryButtonShow(true);
    paintProperty->UpdateUseCustom(false);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);
    EXPECT_TRUE(overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow);

    overlayManager->popupMap_.clear();
    popupNode->MountToParent(rootNode);
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    popupInfo.focusable = false;
    layoutProp->UpdateShowInSubWindow(true);
    paintProperty->UpdatePrimaryButtonShow(true);
    paintProperty->UpdateUseCustom(false);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_FIVE);
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);
    EXPECT_TRUE(overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow);
}

/**
 * @tc.name: MountPopup004
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, MountPopup004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    EXPECT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    popupInfo.focusable = false;
    popupPattern->transitionStatus_ = TransitionStatus::ENTERING;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    MockContainer::Current()->SetIsScenceBoardWindow(true);
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);
    EXPECT_TRUE(overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow);

    popupNode->MountToParent(rootNode);
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    popupInfo.focusable = false;
    paintProperty->UpdatePrimaryButtonShow(false);
    layoutProp->UpdateShowInSubWindow(true);
    MockContainer::Current()->SetIsScenceBoardWindow(false);
    overlayManager->MountPopup(targetNode->GetId(), popupInfo);
    EXPECT_TRUE(overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow);
}

/**
 * @tc.name: HidePopup001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, HidePopup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();

    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    EXPECT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = false;
    popupInfo.isCurrentOnShow = true;
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);

    overlayManager->popupMap_.clear();
    popupInfo.markNeedUpdate = true;
    popupPattern->SetTransitionStatus(TransitionStatus::EXITING);
    MockContainer::Current()->SetIsScenceBoardWindow(false);
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);

    overlayManager->popupMap_.clear();
    popupPattern->SetTransitionStatus(TransitionStatus::ENTERING);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdatePrimaryButtonShow(true);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateShowInSubWindow(false);
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);

    popupNode->MountToParent(rootNode);
    layoutProp->UpdateShowInSubWindow(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    paintProperty->UpdateUseCustom(true);
    popupPattern->SetHasTransition(true);
    popupInfo.focusable = true;
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);
    EXPECT_FALSE(overlayManager->popupMap_[targetNode->GetId()].markNeedUpdate);
}

/**
 * @tc.name: HidePopup002
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, HidePopup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    MockContainer::Current()->SetIsScenceBoardWindow(false);
    popupPattern->SetTransitionStatus(TransitionStatus::ENTERING);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    paintProperty->UpdatePrimaryButtonShow(true);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();

    popupNode->MountToParent(rootNode);
    layoutProp->UpdateShowInSubWindow(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    paintProperty->UpdateUseCustom(true);
    popupInfo.focusable = false;
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);

    popupNode->MountToParent(rootNode);
    layoutProp->UpdateShowInSubWindow(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    paintProperty->UpdateUseCustom(false);
    popupInfo.focusable = false;
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);

    popupNode->MountToParent(rootNode);
    layoutProp->UpdateShowInSubWindow(true);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_FIVE);
    paintProperty->UpdateUseCustom(false);
    popupInfo.focusable = false;
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);

    popupNode->MountToParent(rootNode);
    overlayManager->popupMap_.clear();
    paintProperty->UpdatePrimaryButtonShow(false);
    paintProperty->UpdateUseCustom(false);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_THIRTEEN);
    overlayManager->HidePopup(targetNode->GetId(), popupInfo);
    EXPECT_FALSE(overlayManager->popupMap_[targetNode->GetId()].markNeedUpdate);
}

/**
 * @tc.name: HidePopupWithoutAnimation001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, HidePopupWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    EXPECT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateAutoCancel(false);
    auto ret = overlayManager->HidePopupWithoutAnimation(targetNode->GetId(), popupInfo);
    EXPECT_EQ(ret, nullptr);
    paintProperty->UpdateAutoCancel(true);
    overlayManager->rootNodeWeak_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    overlayManager->HidePopupWithoutAnimation(targetNode->GetId(), popupInfo);
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: HideAllPopups001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, HideAllPopups001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    EXPECT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = false;
    popupInfo.isCurrentOnShow = true;
    overlayManager->popupMap_[targetNode->GetId()] = popupInfo;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateShowInSubWindow(true);
    popupNode->MountToParent(rootNode);
    overlayManager->HideAllPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetNode->GetId()].markNeedUpdate);
}

/**
 * @tc.name: HideCustomPopups001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, HideCustomPopups001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    overlayManager->popupMap_.clear();
    overlayManager->HideCustomPopups();

    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.markNeedUpdate = false;
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->HideCustomPopups();

    overlayManager->popupMap_.clear();
    popupInfo.target = targetNode;
    popupInfo.isCurrentOnShow = false;
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->HideCustomPopups();

    overlayManager->popupMap_.clear();
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    popupInfo.isCurrentOnShow = true;
    layoutProp->UpdateShowInSubWindow(true);
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->HideCustomPopups();

    overlayManager->popupMap_.clear();
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdatePrimaryButtonShow(true);
    popupInfo.isCurrentOnShow = true;
    overlayManager->HideCustomPopups();

    overlayManager->popupMap_.clear();
    popupNode->MountToParent(rootNode);
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    paintProperty->UpdatePrimaryButtonShow(false);
    layoutProp->UpdateShowInSubWindow(false);
    MockContainer::Current()->SetIsScenceBoardWindow(true);
    overlayManager->HideCustomPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetNode->GetId()].markNeedUpdate);
}

/**
 * @tc.name: CheckTargetIdIsValid001
 * @tc.desc: Test OverlayManager::CheckTargetIdIsValid.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, CheckTargetIdIsValid001, TestSize.Level1)
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
    menuPattern->SetHasTransitionEffect(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    menuNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. call showMenu when menuNode already appended.
     * @tc.expected: function exits rightly
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    EXPECT_FALSE(overlayManager->CheckTargetIdIsValid(-1));
}

/**
 * @tc.name: PlayKeyboardTransition001
 * @tc.desc: Test OverlayManager::PlayKeyboardTransition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, PlayKeyboardTransition001, TestSize.Level1)
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
    menuPattern->SetHasTransitionEffect(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    menuNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    AnimationOption option;
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    overlayManager->PlayKeyboardTransition(stageNode, false);
    EXPECT_NE(stageNode, nullptr);
}

/**
 * @tc.name: CheckTopModalNode001
 * @tc.desc: Test OverlayManager::CheckTopModalNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, MenuNewTest021, TestSize.Level1)
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
    menuPattern->SetHasTransitionEffect(true);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    menuNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> sheetNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    BlurStyleOption bgBlurStyle;
    auto renderContext = sheetNode->GetRenderContext();
    overlayManager->SetSheetBackgroundBlurStyle(sheetNode, bgBlurStyle);
    EXPECT_FALSE(renderContext->GetBackgroundEffect().has_value());
    sheetNode->tag_ = "test";
    EXPECT_FALSE(overlayManager->CheckTopModalNode(sheetNode, 10));
    sheetNode->tag_ = "SheetPage";
    EXPECT_FALSE(overlayManager->CheckTopModalNode(sheetNode, 10));
}

/**
 * @tc.name: RemoveAllModalInOverlay001
 * @tc.desc: Test OverlayManager::RemoveAllModalInOverlay
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, RemoveAllModalInOverlay001, TestSize.Level1)
{
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    Ace::WeakPtr<FrameNode> invalidNode = nullptr;
    overlayManager->CleanInvalidModalNode(invalidNode);
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->CleanInvalidModalNode(invalidNode);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 2, AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    overlayManager->modalStack_.emplace(sheetNode);
    overlayManager->modalStack_.emplace(stageNode);
    invalidNode = AceType::WeakClaim(AceType::RawPtr(stageNode));
    overlayManager->CleanInvalidModalNode(invalidNode);
    overlayManager->RemoveAllModalInOverlay();
    EXPECT_FALSE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: CreateSheetKey001
 * @tc.desc: Test OverlayManager::CreateSheetKey
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, CreateSheetKey001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    SheetKey testKey;
    EXPECT_TRUE(overlayManager->CreateSheetKey(stageNode, -1, testKey));
}

/**
 * @tc.name: GetMenuPreviewCenter001
 * @tc.desc: Test OverlayManager::GetMenuPreviewCenter
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, GetMenuPreviewCenter001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    NG::OffsetF test(10.0, 10.0);
    EXPECT_FALSE(overlayManager->GetMenuPreviewCenter(test));
    stageNode->tag_ = "MenuWrapper";
    EXPECT_FALSE(overlayManager->GetMenuPreviewCenter(test));
}

/**
 * @tc.name: RemoveFilterAnimation001
 * @tc.desc: Test OverlayManager::RemoveFilterAnimation
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, RemoveFilterAnimation001, TestSize.Level1)
{
    SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->SetHasFilter(true);
    overlayManager->SetFilterColumnNode(rootNode);
    overlayManager->RemoveFilterAnimation();
    EXPECT_FALSE(!overlayManager->hasFilter_);
}

/**
 * @tc.name: RemovePixelMap001
 * @tc.desc: Test OverlayManager::RemovePixelMap
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, RemovePixelMap001, TestSize.Level1)
{
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    overlayManager->hasPixelMap_ = false;
    overlayManager->hasPixelMap_ = true;
    overlayManager->RemovePixelMap();
    EXPECT_FALSE(overlayManager->hasPixelMap_);
}

/**
 * @tc.name: CheckTargetIdIsValid001
 * @tc.desc: Test OverlayManager::CheckTargetIdIsValid
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, CheckTargetIdIsValid002, TestSize.Level1)
{
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    overlayNode = nullptr;
    overlayManager->CloseBindSheetByUIContext(overlayNode, -1);
    EXPECT_FALSE(overlayManager->CheckTargetIdIsValid(-1));
}

/**
 * @tc.name: PlayBubbleStyleSheetTransition001
 * @tc.desc: Test OverlayManager::PlayBubbleStyleSheetTransition
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, PlayBubbleStyleSheetTransition001, TestSize.Level1)
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
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto topSheetPattern = topSheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(topSheetPattern, nullptr);

    /**
     * @tc.steps: step3. test PlayBubbleStyleSheetTransition().
     */
    overlayManager->PlayBubbleStyleSheetTransition(topSheetNode, false);
    EXPECT_EQ(topSheetPattern->height_, overlayManager->sheetHeight_);
}

/**
 * @tc.name: AvoidCustomKeyboard001
 * @tc.desc: Test OverlayManager::AvoidCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, AvoidCustomKeyboard001, TestSize.Level1)
{
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto keyboardThd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    overlayManager->BindKeyboardWithNode(keyboardThd, 0);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    overlayManager->customKeyboardMap_.emplace(1, AceType::RawPtr(keyboardFst));
    overlayManager->customKeyboardMap_.emplace(2, AceType::RawPtr(keyboardScd));
    overlayManager->BindKeyboardWithNode(keyboardThd, 1);
    overlayManager->BindKeyboardWithNode(keyboardThd, 2);
    overlayManager->UpdateCustomKeyboardPosition();
    overlayManager->AvoidCustomKeyboard(1, 1.0);
    auto customKeyboardNode = overlayManager->customKeyboardMap_[1];
    EXPECT_TRUE(customKeyboardNode->GetRenderContext());
    overlayManager->CloseKeyboard(1);
    auto it = overlayManager->customKeyboardMap_.find(1);
    EXPECT_TRUE(it != overlayManager->customKeyboardMap_.end());
    overlayManager->AvoidCustomKeyboard(5, 1.0);
    auto it1 = overlayManager->customKeyboardMap_.find(5);
    EXPECT_FALSE(it1 != overlayManager->customKeyboardMap_.end());
}

/**
 * @tc.name: RemovePixelMapAnimation001
 * @tc.desc: Test OverlayManager::RemovePixelMapAnimation
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, RemovePixelMapAnimation001, TestSize.Level1)
{
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));
    auto hub = columnNode->GetOrCreateGestureEventHub();
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    hub->SetPixelMap(pixelMap);
    overlayManager->hasPixelMap_ = false;
    overlayManager->RemovePixelMap();
    overlayManager->isOnAnimation_ = false;
    overlayManager->hasPixelMap_ = true;
    overlayManager->RemovePixelMapAnimation(false, 1.0, 1.0, true);
    EXPECT_TRUE(overlayManager->pixmapColumnNodeWeak_.Upgrade());
}

/**
 * @tc.name: RemoveAllModalInOverlay001
 * @tc.desc: Test OverlayManager::RemoveAllModalInOverlay
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, RemoveAllModalInOverlay003, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    CreateSheetBuilder();
    ModalStyle modalStyle;
    modalStyle.modalTransition = ModalTransition::NONE;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc_), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    SheetKey key;
    overlayManager->CleanSheet(rootNode, key);
    overlayManager->RemoveAllModalInOverlay();
    EXPECT_TRUE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: RemovePopupInSubwindow001
 * @tc.desc: Test OverlayManager::RemovePopupInSubwindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, RemovePopupInSubwindow001, TestSize.Level1)
{
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    /**
     * @tc.steps: step2. set PopupInteractiveDismiss and PopupCallBackOnWillDismiss.
     */
    overlayManager->popupMap_.insert({ 0, NG::PopupInfo() });
    overlayManager->popupMap_.insert({ 1, NG::PopupInfo() });
    overlayManager->popupMap_.insert({ 2, NG::PopupInfo() });
    bool testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_FALSE(testResult);
}

/**
 * @tc.name: GetMenuNode001
 * @tc.desc: Test OverlayManager::GetMenuNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, GetMenuNode001, TestSize.Level1)
{
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    overlayManager->HideMenu(overlayNode, 10, true);
    overlayManager->menuMap_.insert({ 1, overlayNode });
    overlayManager->menuMap_.insert({ 2, overlayNode });
    EXPECT_TRUE(overlayManager->GetMenuNode(2));
    EXPECT_FALSE(overlayManager->GetMenuNode(3));
}

/**
 * @tc.name: CleanHoverImagePreviewInSubWindow001
 * @tc.desc: Test OverlayManager::CleanHoverImagePreviewInSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, CleanHoverImagePreviewInSubWindow001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    rootNode->tag_ = "Flex";
    overlayManager->CleanHoverImagePreviewInSubWindow(rootNode);
    EXPECT_TRUE(rootNode->GetTag() == V2::FLEX_ETS_TAG);
}

/**
 * @tc.name: CustomDialogRecordEvent001
 * @tc.desc: Test OverlayManager::CustomDialogRecordEvent
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, CustomDialogRecordEvent001, TestSize.Level1)
{
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto index = static_cast<int32_t>(Recorder::EventCategory::CATEGORY_COMPONENT);
    Recorder::EventRecorder::Get().eventSwitch_[index] = true;
    Recorder::EventRecorder::Get().globalSwitch_[index] = true;
    DialogProperties dialogProps;
    overlayManager->CustomDialogRecordEvent(dialogProps);
    Recorder::EventParamsBuilder builder;
    EXPECT_NE(builder.params_, nullptr);
}

/**
 * @tc.name: HideCustomPopups002
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, HideCustomPopups002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    EXPECT_NE(popupPattern, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    popupInfo.markNeedUpdate = true;
    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateShowInSubWindow(false);
    auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdatePrimaryButtonShow(false);
    popupPattern->SetTransitionStatus(TransitionStatus::EXITING);
    overlayManager->HideCustomPopups();
    EXPECT_FALSE(overlayManager->popupMap_[targetNode->GetId()].markNeedUpdate);
}

/**
 * @tc.name: ErasePopup001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, ErasePopup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto targetNode = CreateTargetNode();
    ASSERT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    ASSERT_NE(popupNode, nullptr);
    popupNode->MountToParent(rootNode);
    auto popupPattern = popupNode->GetPattern<BubblePattern>();
    EXPECT_NE(popupPattern, nullptr);
    auto accessibilityProperty = popupNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
    EXPECT_NE(accessibilityProperty, nullptr);
    PopupInfo popupInfo;
    popupInfo.popupId = popupId;
    popupInfo.popupNode = popupNode;
    popupInfo.target = targetNode;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateShowInSubWindow(true);
    overlayManager->popupMap_.clear();
    overlayManager->UpdatePopupMap(targetNode->GetId(), popupInfo);
    overlayManager->ErasePopup(0);
    overlayManager->ErasePopup(1);
    EXPECT_EQ(accessibilityProperty->GetShowedState(), 0);
}

/**
 * @tc.name: ShowMenu001
 * @tc.desc: Test function of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, ShowMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    int32_t targetId = 1;
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, targetId, AceType::MakeRefPtr<MenuWrapperPattern>(-1));
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, targetId, AceType::MakeRefPtr<MenuPattern>(targetId, TEXT_TAG, MenuType::MENU));
    menuNode->MountToParent(wrapperNode);
    overlayManager->ShowMenu(targetId, OffsetF(), menuNode);
    EXPECT_TRUE(overlayManager->menuMap_.find(menuNode) != overlayManager->menuMap_.end());

    overlayManager->menuMap_.clear();
    targetId = 2;
    auto wrapperNode1 =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, targetId, AceType::MakeRefPtr<MenuWrapperPattern>(-1));
    ASSERT_NE(wrapperNode1, nullptr);
    auto menuNode1 = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, targetId, AceType::MakeRefPtr<MenuPattern>(targetId, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode1, nullptr);
    auto menuNode2 = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    menuNode1->MountToParent(wrapperNode1);
    menuNode2->MountToParent(menuNode1);
    overlayManager->ShowMenu(targetId, OffsetF(), menuNode1);
    EXPECT_FALSE(overlayManager->menuMap_.find(menuNode1) != overlayManager->menuMap_.end());
}

/**
 * @tc.name: GetBoolFromTipsEnterAndLeaveInfo001
 * @tc.desc: Test GetBoolFromTipsEnterAndLeaveInfo of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, GetBoolFromTipsEnterAndLeaveInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    bool result = overlayManager->GetBoolFromTipsEnterAndLeaveInfo(1, 1);
    EXPECT_FALSE(result);
    overlayManager->tipsEnterAndLeaveInfoMap_[1] = { { 2, true } };
    result = overlayManager->GetBoolFromTipsEnterAndLeaveInfo(1, 1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetTipsEnterAndLeaveInfo001
 * @tc.desc: Test GetTipsEnterAndLeaveInfo of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, GetTipsEnterAndLeaveInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    auto result = overlayManager->GetTipsEnterAndLeaveInfo(1);
    EXPECT_EQ(result, -1);
    overlayManager->tipsEnterAndLeaveInfoMap_[1] = {};
    result = overlayManager->GetTipsEnterAndLeaveInfo(1);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: UpdateTipsEnterAndLeaveInfo001
 * @tc.desc: Test UpdateTipsEnterAndLeaveInfo of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, UpdateTipsEnterAndLeaveInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    overlayManager->tipsEnterAndLeaveInfoMap_[1] = {};
    overlayManager->UpdateTipsEnterAndLeaveInfo(1);
    overlayManager->UpdateTipsEnterAndLeaveInfo(1);
    EXPECT_TRUE(overlayManager->GetBoolFromTipsEnterAndLeaveInfo(1, 1));
}

/**
 * @tc.name: UpdateTipsEnterAndLeaveInfoBool001
 * @tc.desc: Test UpdateTipsEnterAndLeaveInfoBool of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, UpdateTipsEnterAndLeaveInfoBool001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    overlayManager->tipsEnterAndLeaveInfoMap_[1] = {};
    overlayManager->UpdateTipsEnterAndLeaveInfoBool(1);
    EXPECT_FALSE(overlayManager->GetBoolFromTipsEnterAndLeaveInfo(1, 1));
    overlayManager->tipsEnterAndLeaveInfoMap_[1] = { { 1, true } };
    overlayManager->UpdateTipsEnterAndLeaveInfoBool(1);
    EXPECT_FALSE(overlayManager->GetBoolFromTipsEnterAndLeaveInfo(1, 1));
    overlayManager->UpdateTipsEnterAndLeaveInfoBool(1);
    EXPECT_FALSE(overlayManager->GetBoolFromTipsEnterAndLeaveInfo(1, 1));
}

/**
 * @tc.name: EraseTipsEnterAndLeaveInfo001
 * @tc.desc: Test EraseTipsEnterAndLeaveInfo of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, EraseTipsEnterAndLeaveInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    overlayManager->tipsEnterAndLeaveInfoMap_[1] = { { 2, true } };
    overlayManager->EraseTipsEnterAndLeaveInfo(1, 1);
    EXPECT_EQ(overlayManager->tipsEnterAndLeaveInfoMap_.size(), 1);
    overlayManager->EraseTipsEnterAndLeaveInfo(1, 2);
    EXPECT_EQ(overlayManager->tipsEnterAndLeaveInfoMap_.size(), 0);
}

/**
 * @tc.name: UpdatePreviousDisappearingTime001
 * @tc.desc: Test UpdatePreviousDisappearingTime && EraseTipsInfo of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, UpdatePreviousDisappearingTime001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    PopupInfo popupInfo;
    overlayManager->tipsInfoList_.emplace_back(1, popupInfo);
    overlayManager->tipsInfoList_.emplace_back(3, popupInfo);
    overlayManager->UpdatePreviousDisappearingTime(2);
    EXPECT_FALSE(overlayManager->GetBoolFromTipsEnterAndLeaveInfo(1, 1));
    overlayManager->EraseTipsInfo(3);
    EXPECT_EQ(overlayManager->tipsInfoList_.size(), 1);
}

/**
 * @tc.name: UpdateTipsInfo001
 * @tc.desc: Test UpdateTipsInfo of OverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestOneNG, UpdateTipsInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and OverlayManager.
     */
    auto rootNode = CreateRootNode();
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    /**
     * @tc.steps: step2. call function.
     */
    PopupInfo popupInfo;
    popupInfo.popupId = 1;
    PopupInfo popupInfo2;
    popupInfo2.popupId = 2;
    overlayManager->tipsInfoList_.emplace_back(1, popupInfo);
    overlayManager->tipsInfoList_.emplace_back(3, popupInfo);
    overlayManager->UpdateTipsInfo(1, popupInfo2);
    auto popupInfoGet = overlayManager->GetTipsInfo(1);
    EXPECT_EQ(popupInfoGet.popupId, popupInfo2.popupId);
}
} // namespace OHOS::Ace::NG