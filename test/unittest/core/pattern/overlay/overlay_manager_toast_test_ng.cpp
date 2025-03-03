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
#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t DURATION = 2;
} // namespace
class OverlayManagerToastTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
};

void OverlayManagerToastTestNg::SetUpTestCase()
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
void OverlayManagerToastTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayManagerToastTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

/**
 * @tc.name: ToastShowModeTest001
 * @tc.desc: Test OverlayManager::ShowToast with showMode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastShowModeTest001, TestSize.Level1)
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
    toastContext->UpdateOffset(OffsetT<Dimension> { 0.0_vp, 0.0_vp });
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest001, TestSize.Level1)
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest002, TestSize.Level1)
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest004, TestSize.Level1)
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest005, TestSize.Level1)
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest006, TestSize.Level1)
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast and get toastNode.
     */
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast and get toastNode.
     */
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toast and toastNode.
     */
    auto toastId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, AceType::MakeRefPtr<ToastPattern>());
    ASSERT_NE(toastNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    MockPipelineContext::GetCurrent()->rootNode_ = rootNode;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    toastNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
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
HWTEST_F(OverlayManagerToastTestNg, ToastTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo and update hoverModeArea enableHoverMode.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
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
 * @tc.name: ToastTest011
 * @tc.desc: Test ShowToast UpdateToastAlign
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo and update hoverModeArea enableHoverMode.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto layoutAlgorithm = toastPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    toastPattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(toastPattern->IsDefaultToast());
}

/**
 * @tc.name: ToastDumpInfoTest001
 * @tc.desc: Test Toast DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastDumpInfoTest001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
