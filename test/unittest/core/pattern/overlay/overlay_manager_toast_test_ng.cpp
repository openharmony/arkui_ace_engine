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
#include "ui/base/ace_type.h"
#include "ui/base/geometry/dimension.h"

#define private public
#define protected public
#include "test/mock/base/mock_subwindow.h"
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
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/alignment.h"
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
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_pattern.h"
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
constexpr double DOUBLEONE = 1.0f;
constexpr int32_t CALLBACK_COUNT = 3;
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
    EXPECT_CALL(*AceType::DynamicCast<MockPipelineContext>(MockPipelineContext::GetCurrentContext()),
        GetSafeAreaWithoutProcess())
        .WillRepeatedly(Return(SafeAreaInsets {}));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(nullptr));
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
    theme->textStyle_.fontSize_.value = fontSize;
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

/**
 * @tc.name: ToastThemeGetTopTest001
 * @tc.desc: Test ToastTheme::GetTop function.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastThemeGetTopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ToastTheme and set top value.
     */
    auto toastTheme = AceType::MakeRefPtr<ToastTheme>();
    Dimension topValue = 10.0_vp;
    toastTheme->top_ = topValue;
    /**
     * @tc.steps: step2. call GetTop function and check the returned value.
     * @tc.expected: the returned value should be equal to the set top value.
     */
    const Dimension& result = toastTheme->GetTop();
    EXPECT_EQ(result, topValue);
}

/**
 * @tc.name: FoldStatusChangedAnimation
 * @tc.desc: Test FoldStatusChangedAnimation
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, FoldStatusChangedAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    toastPattern->FoldStatusChangedAnimation();
    EXPECT_FALSE(toastPattern->IsDefaultToast());
}

/**
 * @tc.name: AdjustOffsetForKeyboard
 * @tc.desc: Test AdjustOffsetForKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, AdjustOffsetForKeyboard, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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

    Dimension offsetY = 100.0_vp;
    double toastBottom = 100;
    float textHeight = 100;
    bool needResizeBottom = false;
    toastPattern->AdjustOffsetForKeyboard(offsetY, toastBottom, textHeight, needResizeBottom);
    EXPECT_FALSE(toastPattern->IsDefaultToast());
}

/**
 * @tc.name: GetTextLayoutConstraint
 * @tc.desc: Test GetTextLayoutConstraint
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, GetTextLayoutConstraint, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto layoutAlgorithm = AceType::DynamicCast<ToastLayoutAlgorithm>(toastPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(toastNode, geometryNode, toastNode->GetLayoutProperty());

    
    layoutAlgorithm->GetTextLayoutConstraint(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(toastPattern->IsDefaultToast());
}

/**
 * @tc.name: DumpInfo
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, DumpInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    toastPattern->DumpInfo(json);
    EXPECT_FALSE(toastPattern->IsDefaultToast());
}

/**
 * @tc.name: ToastLayoutAlgorithmLayout001
 * @tc.desc: Test Layout
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastLayoutAlgorithmLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready ToastLayoutAlgorithm.
     */
    ToastLayoutAlgorithm toastLayoutAlgorithm;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    toastInfo.offset = DimensionOffset(Dimension(DOUBLEONE), Dimension(DOUBLEONE));
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto layoutWrapperNode = toastNode->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    auto frameNode = layoutWrapper->GetHostNode();
    ASSERT_NE(frameNode, nullptr);
    auto toastPattern = frameNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto toastProperty = frameNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    EXPECT_TRUE(AceApplicationInfo::GetInstance().IsRightToLeft());
    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::TOP_END);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::CENTER_START);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::CENTER_END);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_START);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_END);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::DEFAULT);
    toastLayoutAlgorithm.Layout(layoutWrapper);
}

/**
 * @tc.name: ToastLayoutAlgorithmLayout002
 * @tc.desc: Test Layout
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastLayoutAlgorithmLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready ToastLayoutAlgorithm.
     */
    ToastLayoutAlgorithm toastLayoutAlgorithm;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    toastInfo.offset = DimensionOffset(Dimension(DOUBLEONE), Dimension(DOUBLEONE));
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto layoutWrapperNode = toastNode->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    auto frameNode = layoutWrapper->GetHostNode();
    ASSERT_NE(frameNode, nullptr);
    auto toastPattern = frameNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto toastProperty = frameNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    EXPECT_FALSE(AceApplicationInfo::GetInstance().IsRightToLeft());
    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::TOP_END);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::CENTER_START);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::CENTER_END);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_START);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_END);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    toastPattern->GetToastInfo().alignment = static_cast<int32_t>(ToastAlignment::DEFAULT);
    toastLayoutAlgorithm.Layout(layoutWrapper);

    auto context = toastNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto toastTheme = context->GetTheme<ToastTheme>();
    ASSERT_NE(toastTheme, nullptr);
    toastTheme->toastDoubleBorderEnable_ = true;
    toastLayoutAlgorithm.Layout(layoutWrapper);
}

/**
 * @tc.name: ToastLayoutAlgorithmGetTextLayoutConstraint001
 * @tc.desc: Test GetTextLayoutConstraint
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastLayoutAlgorithmGetTextLayoutConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready ToastLayoutAlgorithm.
     */
    ToastLayoutAlgorithm toastLayoutAlgorithm;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    toastInfo.offset = DimensionOffset(Dimension(DOUBLEONE), Dimension(DOUBLEONE));
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto layoutWrapperNode = toastNode->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    ASSERT_NE(frameNode, nullptr);
    auto toastPattern = frameNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto toastProperty = frameNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto context = toastPattern->GetToastContext();
    ASSERT_NE(context, nullptr);

    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    EXPECT_FALSE(container->IsSubContainer());
    container->isUIExtensionWindow_ = true;
    EXPECT_TRUE(toastPattern->IsAlignedWithHostWindow());

    context->safeAreaManager_ = nullptr;
    auto safeAreaManager = context->GetSafeAreaManager();
    ASSERT_EQ(safeAreaManager, nullptr);
    container->SetApiTargetVersion(19);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
    toastLayoutAlgorithm.GetTextLayoutConstraint(layoutWrapper);
    container->ResetContainer();
}

/**
 * @tc.name: ToastLayoutAlgorithmGetTextLayoutConstraint002
 * @tc.desc: Test GetTextLayoutConstraint
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastLayoutAlgorithmGetTextLayoutConstraint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready ToastLayoutAlgorithm.
     */
    ToastLayoutAlgorithm toastLayoutAlgorithm;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    toastInfo.offset = DimensionOffset(Dimension(DOUBLEONE), Dimension(DOUBLEONE));
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto layoutWrapperNode = toastNode->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);
    auto frameNode = layoutWrapper->GetHostNode();
    ASSERT_NE(frameNode, nullptr);
    auto toastPattern = frameNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto toastProperty = frameNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto context = toastPattern->GetToastContext();
    ASSERT_NE(context, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    EXPECT_TRUE(toastPattern->IsAlignedWithHostWindow());
    context->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    auto safeAreaManager = context->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    safeAreaManager->keyboardInset_ = { .end = 10.0f, .start = 0.0f };
    auto inset = safeAreaManager->GetKeyboardInset().Length();
    auto keyboardInset = NearEqual(inset, 0.0f) ? safeAreaManager->GetRawKeyboardHeight() : inset;
    EXPECT_TRUE(GreatNotEqual(keyboardInset, 0));
    container->SetApiTargetVersion(19);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());
    AceEngine::Get().AddContainer(Container::CurrentId(), AceType::MakeRefPtr<MockContainer>());
    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId());
    auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    auto parentContainer = AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(currentId));
    ASSERT_NE(parentContainer, nullptr);
    parentContainer->isUIExtensionWindow_ = true;
    toastLayoutAlgorithm.GetTextLayoutConstraint(layoutWrapper);
    container->ResetContainer();
}

/**
 * @tc.name: ToastLayoutAlgorithmGetTextLayoutConstraint003
 * @tc.desc: Test GetTextLayoutConstraint
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastLayoutAlgorithmGetTextLayoutConstraint003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready ToastLayoutAlgorithm.
     */
    ToastLayoutAlgorithm toastLayoutAlgorithm;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::SYSTEM_TOP_MOST;
    toastInfo.offset = DimensionOffset(Dimension(DOUBLEONE), Dimension(DOUBLEONE));
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto layoutWrapperNode = toastNode->CreateLayoutWrapper(true, true);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    ASSERT_NE(layoutWrapper, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    ASSERT_NE(frameNode, nullptr);
    auto toastPattern = frameNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto toastProperty = frameNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto context = toastPattern->GetToastContext();
    ASSERT_NE(context, nullptr);

    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    EXPECT_FALSE(container->IsSubContainer());
    container->isUIExtensionWindow_ = true;
    EXPECT_FALSE(toastPattern->IsAlignedWithHostWindow());

    context->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    auto safeAreaManager = context->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    safeAreaManager->keyboardInset_ = { .end = 10.0f, .start = 0.0f };
    auto inset = safeAreaManager->GetKeyboardInset().Length();
    auto keyboardInset = NearEqual(inset, 0.0f) ? safeAreaManager->GetRawKeyboardHeight() : inset;
    EXPECT_TRUE(GreatNotEqual(keyboardInset, 0));
    container->SetApiTargetVersion(19);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
    toastLayoutAlgorithm.GetTextLayoutConstraint(layoutWrapper);
    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternDumpInfo001
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternDumpInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto host = toastPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(toastProp);

    toastProp->propToastAlignment_ = std::nullopt;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    toastPattern->DumpInfo(json);
    EXPECT_FALSE((toastProp->HasToastAlignment()));

    toastProp->propToastAlignment_ = Alignment();
    json.reset();
    json = std::make_unique<JsonValue>();
    toastPattern->DumpInfo(json);
    EXPECT_TRUE((toastProp->HasToastAlignment()));
}

/**
 * @tc.name: ToastPatternDumpInfo002
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternDumpInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto host = toastPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(toastProp);

    toastProp->propToastAlignment_ = std::nullopt;
    toastPattern->DumpInfo();
    EXPECT_FALSE((toastProp->HasToastAlignment()));

    toastProp->propToastAlignment_ = Alignment();
    toastPattern->DumpInfo();
    EXPECT_TRUE((toastProp->HasToastAlignment()));
}

/**
 * @tc.name: ToastPatternUpdateToastSize
 * @tc.desc: Test UpdateToastSize
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternUpdateToastSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto host = toastPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(toastProp);

    auto container = Container::Current();
    container->SetApiTargetVersion(11);
    EXPECT_FALSE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE));
    toastPattern->UpdateToastSize(host);
}

/**
 * @tc.name: ToastPatternGetBottomValue
 * @tc.desc: Test GetBottomValue
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetBottomValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::DEFAULT;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    toastPattern->wrapperRect_ = Rect(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE);
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipeline = host->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto toastTheme = pipeline->GetTheme<ToastTheme>();
    ASSERT_NE(toastTheme, nullptr);
    toastTheme->bottom_ = Dimension(DOUBLEONE, DimensionUnit::PERCENT);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    toastProp->propBottom_ = Dimension(DOUBLEONE, DimensionUnit::PERCENT);
    auto toastBottom = toastProp->GetBottomValue(toastTheme->GetBottom());
    EXPECT_TRUE(toastBottom.Unit() == DimensionUnit::PERCENT);

    EXPECT_EQ(toastPattern->GetBottomValue(layoutWrapper), 1.0);
}

/**
 * @tc.name: ToastPatternInitWrapperRect001
 * @tc.desc: Test InitWrapperRect
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternInitWrapperRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::SYSTEM_TOP_MOST;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    toastPattern->wrapperRect_ = Rect(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE);
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    auto layoutWrapperPtr = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapper));
    ASSERT_NE(layoutWrapperPtr, nullptr);

    auto containerId = MockContainer::CurrentId();
    EXPECT_FALSE(containerId >= MIN_SUBCONTAINER_ID);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(context, nullptr);
    toastPattern->InitWrapperRect(layoutWrapperPtr, toastProp);

    MockContainer::UpdateCurrent(MIN_SUBCONTAINER_ID);
    containerId = MockContainer::CurrentId();
    EXPECT_TRUE(containerId >= MIN_SUBCONTAINER_ID);
    toastPattern->InitWrapperRect(layoutWrapperPtr, toastProp);
    MockContainer::UpdateCurrent(0);
}

/**
 * @tc.name: ToastPatternInitWrapperRect002
 * @tc.desc: Test InitWrapperRect
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternInitWrapperRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    toastPattern->wrapperRect_ = Rect(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE);
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProps = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProps, nullptr);
    auto layoutWrapperPtr = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapper));
    ASSERT_NE(layoutWrapperPtr, nullptr);

    auto containerId = MockContainer::CurrentId();
    EXPECT_FALSE(containerId >= MIN_SUBCONTAINER_ID);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(context, nullptr);
    toastProps->propToastAlignment_ = Alignment::TOP_CENTER;
    Alignment alignment = toastProps->GetToastAlignmentValue(Alignment::BOTTOM_CENTER);
    EXPECT_TRUE(alignment == Alignment::TOP_CENTER);
    toastPattern->InitWrapperRect(layoutWrapperPtr, toastProps);

    toastProps->propToastAlignment_ = Alignment::TOP_RIGHT;
    alignment = toastProps->GetToastAlignmentValue(Alignment::BOTTOM_CENTER);
    EXPECT_TRUE(alignment == Alignment::TOP_RIGHT);
    toastPattern->InitWrapperRect(layoutWrapperPtr, toastProps);

    toastProps->propToastAlignment_ = Alignment::BOTTOM_LEFT;
    alignment = toastProps->GetToastAlignmentValue(Alignment::BOTTOM_CENTER);
    EXPECT_TRUE(alignment == Alignment::BOTTOM_LEFT);
    toastPattern->InitWrapperRect(layoutWrapperPtr, toastProps);
}

/**
 * @tc.name: ToastPatternInitUIExtensionHostWindowRect001
 * @tc.desc: Test InitUIExtensionHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternInitUIExtensionHostWindowRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    toastPattern->wrapperRect_ = Rect(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE);

    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    EXPECT_FALSE(container->IsSubContainer());
    container->isUIExtensionWindow_ = true;
    EXPECT_TRUE(toastPattern->IsAlignedWithHostWindow());

    toastPattern->InitUIExtensionHostWindowRect();
    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternInitUIExtensionHostWindowRect002
 * @tc.desc: Test InitUIExtensionHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternInitUIExtensionHostWindowRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    toastPattern->wrapperRect_ = Rect(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE);

    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());

    AceEngine::Get().AddContainer(Container::CurrentId() + 1, AceType::MakeRefPtr<MockContainer>());
    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId() + 1);
    auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    auto containerParent = AceEngine::Get().GetContainer(currentId);
    ASSERT_NE(container, nullptr);

    toastPattern->InitUIExtensionHostWindowRect();
    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternGetSystemTopMostSubwindowSize
 * @tc.desc: Test GetSystemTopMostSubwindowSize
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetSystemTopMostSubwindowSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->UpdateCurrent(-1);
    auto subwindow = SubwindowManager::GetInstance()->GetSystemToastWindow(Container::CurrentId());
    ASSERT_EQ(subwindow, nullptr);
    toastPattern->GetSystemTopMostSubwindowSize();

    container->UpdateCurrent(10);
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    EXPECT_CALL(*mockSubwindow, GetChildContainerId()).Times(1).WillOnce(Return(0));
    SubwindowManager::GetInstance()->AddSystemToastWindow(Container::CurrentId(), mockSubwindow);
    ASSERT_NE(SubwindowManager::GetInstance()->GetSystemToastWindow(Container::CurrentId()), nullptr);
    EXPECT_CALL(*mockSubwindow, GetWindowRect())
        .Times(1)
        .WillOnce(Return(RectF(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE)));
    toastPattern->GetSystemTopMostSubwindowSize();
    EXPECT_CALL(*mockSubwindow, GetWindowRect()).Times(1).WillOnce(Return(RectF()));
    toastPattern->GetSystemTopMostSubwindowSize();
    EXPECT_CALL(*mockSubwindow, GetWindowRect())
        .Times(1)
        .WillOnce(Return(RectF(DOUBLEONE, DOUBLEONE, DOUBLEONE, 0.0f)));
    toastPattern->GetSystemTopMostSubwindowSize();

    container->ResetContainer();
    mockSubwindow = nullptr;
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: ToastPatternOnDetachFromFrameNode
 * @tc.desc: Test OnDetachFromFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternOnDetachFromFrameNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto containerId = Container::CurrentId();
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    auto current_context = PipelineContext::GetCurrentContextSafelyWithCheck();
    auto pipeline = parentContainerId < 0 ? current_context : PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    toastPattern->foldDisplayModeChangedCallbackId_ = std::nullopt;
    toastPattern->halfFoldHoverChangedCallbackId_ = std::nullopt;
    toastPattern->OnDetachFromFrameNode(AceType::RawPtr(toastNode));
}

/**
 * @tc.name: ToastPatternIsUIExtensionSubWindow
 * @tc.desc: Test IsUIExtensionSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternIsUIExtensionSubWindow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    container->UpdateCurrent(-1);

    EXPECT_FALSE(toastPattern->IsUIExtensionSubWindow());
    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternIsShowInFreeMultiWindow
 * @tc.desc: Test IsShowInFreeMultiWindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternIsShowInFreeMultiWindow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isFreeMultiWindow_ = true;
    EXPECT_TRUE(toastPattern->IsShowInFreeMultiWindow());
    container->isSubContainer_ = true;
    EXPECT_FALSE(toastPattern->IsShowInFreeMultiWindow());
    container->UpdateCurrent(11);
    AceEngine::Get().AddContainer(Container::CurrentId(), container);
    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId());
    auto containerparent =
        AceEngine::Get().GetContainer(SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId()));
    ASSERT_NE(containerparent, nullptr);
    EXPECT_TRUE(toastPattern->IsShowInFreeMultiWindow());
    MockContainer::TearDown();
    EXPECT_FALSE(toastPattern->IsShowInFreeMultiWindow());

    containerparent = nullptr;
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

/**
 * @tc.name: ToastPatternGetTextMaxHeight001
 * @tc.desc: Test GetTextMaxHeight
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetTextMaxHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::SYSTEM_TOP_MOST;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);

    EXPECT_NE(toastPattern->GetTextMaxHeight(), 0.0f);
}

/**
 * @tc.name: ToastPatternGetTextMaxHeight002
 * @tc.desc: Test GetTextMaxHeight
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetTextMaxHeight002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    EXPECT_TRUE(toastPattern->IsAlignedWithHostWindow());
    toastPattern->uiExtensionHostWindowRect_ = Rect(0, 0, 0, 0);
    auto deviceHeight = toastPattern->uiExtensionHostWindowRect_.Height();
    EXPECT_TRUE(LessOrEqual(deviceHeight, 0.0));

    EXPECT_NE(toastPattern->GetTextMaxHeight(), 0.0f);
    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternGetTextMaxWidth001
 * @tc.desc: Test GetTextMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetTextMaxWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::SYSTEM_TOP_MOST;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);

    EXPECT_EQ(toastPattern->GetTextMaxWidth(), 0.0f);
}

/**
 * @tc.name: ToastPatternGetTextMaxWidth002
 * @tc.desc: Test GetTextMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetTextMaxWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipelineContext, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    EXPECT_TRUE(toastPattern->IsAlignedWithHostWindow());
    toastPattern->uiExtensionHostWindowRect_ = Rect(0, 0, 0, 0);
    auto deviceWidth = toastPattern->uiExtensionHostWindowRect_.Width();
    EXPECT_TRUE(LessOrEqual(deviceWidth, 0.0));

    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    ASSERT_NE(toastTheme, nullptr);
    auto marging = toastTheme->GetMarging();
    auto maxWidth = deviceWidth - marging.Left().ConvertToPx() - marging.Right().ConvertToPx();
    auto maxLimitWidth = toastTheme->GetMaxWidth();
    EXPECT_FALSE(GreatNotEqual(maxWidth, maxLimitWidth.ConvertToPx()));
    EXPECT_EQ(toastPattern->GetTextMaxWidth(), 0.0f);
    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternUpdateTextSizeConstraint
 * @tc.desc: Test UpdateTextSizeConstraint
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternUpdateTextSizeConstraint, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    CHECK_NULL_VOID(textNode);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto gridColumnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::TOAST);
    gridColumnInfo->parent_ = nullptr;
    EXPECT_EQ(gridColumnInfo->GetParent(), nullptr);

    toastPattern->UpdateTextSizeConstraint(textNode);
}

/**
 * @tc.name: ToastPatternBeforeCreateLayoutWrapper
 * @tc.desc: Test BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternBeforeCreateLayoutWrapper, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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

    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->UpdateCurrent(MIN_SUBCONTAINER_ID);
    container->apiTargetVersion_ = 19;
    EXPECT_FALSE(Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
    auto containerId = Container::CurrentId();
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
    EXPECT_EQ(parentContainer, nullptr);
    toastPattern->BeforeCreateLayoutWrapper();

    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternAdjustOffsetForKeyboard001
 * @tc.desc: Test AdjustOffsetForKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternAdjustOffsetForKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    Dimension offsetY = Dimension(0.0);
    double toastBottom = 0.0;
    float textHeight = 0.0f;
    bool needResizeBottom = false;

    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(context, nullptr);
    context->safeAreaManager_ = nullptr;
    EXPECT_EQ(context->GetSafeAreaManager(), nullptr);
    toastPattern->AdjustOffsetForKeyboard(offsetY, toastBottom, textHeight, needResizeBottom);

    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    context->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    EXPECT_NE(context->GetSafeAreaManager(), nullptr);
    context->safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    context->safeAreaManager_->keyboardInset_ = { .start = 0, .end = 1 };
    EXPECT_TRUE(toastPattern->IsAlignedWithHostWindow());
    toastPattern->AdjustOffsetForKeyboard(offsetY, toastBottom, textHeight, needResizeBottom);
    EXPECT_FALSE(needResizeBottom);

    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternAdjustOffsetForKeyboard002
 * @tc.desc: Test AdjustOffsetForKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternAdjustOffsetForKeyboard002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    Dimension offsetY = Dimension(0.0);
    double toastBottom = 0.0;
    float textHeight = 10.0f;
    bool needResizeBottom = false;

    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(context, nullptr);
    auto deviceHeight = context->GetRootHeight();
    textHeight = deviceHeight;
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    context->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    EXPECT_NE(context->GetSafeAreaManager(), nullptr);
    context->safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    context->safeAreaManager_->keyboardInset_ = { .start = 0, .end = 1 };
    auto toastSubwindow = SubwindowManager::GetInstance()->GetToastSubwindow(Container::CurrentId());
    EXPECT_EQ(toastSubwindow, nullptr);
    toastPattern->AdjustOffsetForKeyboard(offsetY, toastBottom, textHeight, needResizeBottom);
    EXPECT_TRUE(needResizeBottom);

    needResizeBottom = false;
    container->UpdateCurrent(12);
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).Times(1).WillOnce(Return(Rect()));
    EXPECT_CALL(*mockSubwindow, GetChildContainerId()).Times(1).WillOnce(Return(0));
    SubwindowManager::GetInstance()->AddToastSubwindow(Container::CurrentId(), mockSubwindow);
    ASSERT_NE(SubwindowManager::GetInstance()->GetToastSubwindow(Container::CurrentId()), nullptr);
    toastPattern->AdjustOffsetForKeyboard(offsetY, toastBottom, textHeight, needResizeBottom);
    EXPECT_TRUE(needResizeBottom);

    container->ResetContainer();
    mockSubwindow = nullptr;
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: ToastPatternAdjustOffsetForKeyboard003
 * @tc.desc: Test AdjustOffsetForKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternAdjustOffsetForKeyboard003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    Dimension offsetY = Dimension(0.0);
    double toastBottom = 0.0;
    float textHeight = 10.0f;
    bool needResizeBottom = false;

    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(context, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    context->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    EXPECT_NE(context->GetSafeAreaManager(), nullptr);
    context->safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    context->safeAreaManager_->keyboardInset_ = { .start = 0, .end = 1 };
    container->UpdateCurrent(13);
    AceEngine::Get().AddContainer(Container::CurrentId(), AceType::MakeRefPtr<MockContainer>());
    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId());
    auto containerparent = AceType::DynamicCast<MockContainer>(
        AceEngine::Get().GetContainer(SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId())));
    ASSERT_NE(containerparent, nullptr);
    EXPECT_FALSE(containerparent->IsUIExtensionWindow());
    auto deviceHeight = context->GetRootHeight();
    textHeight = deviceHeight;

    toastPattern->AdjustOffsetForKeyboard(offsetY, toastBottom, textHeight, needResizeBottom);
    EXPECT_TRUE(needResizeBottom);

    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternGetOffsetY001
 * @tc.desc: Test GetOffsetY
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetOffsetY001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto context = toastPattern->GetToastContext();
    ASSERT_NE(context, nullptr);
    context->minPlatformVersion_ = 8;
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(text, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    toastProp->propToastAlignment_ = std::nullopt;
    EXPECT_FALSE(toastProp->HasToastAlignment());
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(19);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
    toastProp->propToastOffset_ = DimensionOffset(Dimension(10.0), Dimension(10.0));

    EXPECT_NE(toastPattern->GetOffsetY(layoutWrapper), Dimension(0.0));

    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternGetOffsetY002
 * @tc.desc: Test GetOffsetY
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetOffsetY002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto context = toastPattern->GetToastContext();
    ASSERT_NE(context, nullptr);
    context->minPlatformVersion_ = 8;
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(text, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    toastProp->propToastAlignment_ = std::nullopt;
    EXPECT_FALSE(toastProp->HasToastAlignment());
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(19);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));

    context->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    EXPECT_NE(context->GetSafeAreaManager(), nullptr);
    context->safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    context->safeAreaManager_->keyboardInset_ = { .start = 0, .end = 1 };
    toastPattern->wrapperRect_.y_ = context->GetRootHeight();
    toastProp->propToastOffset_ = DimensionOffset(Dimension(10.0), Dimension(10.0));

    EXPECT_NE(toastPattern->GetOffsetY(layoutWrapper), Dimension(0.0));

    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternGetOffsetY003
 * @tc.desc: Test GetOffsetY
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternGetOffsetY003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto context = toastPattern->GetToastContext();
    ASSERT_NE(context, nullptr);
    context->minPlatformVersion_ = 8;
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(text, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    toastProp->propToastAlignment_ = std::nullopt;
    EXPECT_FALSE(toastProp->HasToastAlignment());
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(19);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));

    context->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    EXPECT_NE(context->GetSafeAreaManager(), nullptr);
    context->safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    context->safeAreaManager_->keyboardInset_ = { .start = 0, .end = context->GetRootHeight() + 1 };
    toastProp->propToastOffset_ = DimensionOffset(Dimension(10.0), Dimension(10.0));

    EXPECT_NE(toastPattern->GetOffsetY(layoutWrapper), Dimension(0.0));

    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternOnDirtyLayoutWrapperSwap
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternOnDirtyLayoutWrapperSwap, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto dirty = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(dirty, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(context, nullptr);
    auto toastNodeDirty = dirty->GetHostNode();
    ASSERT_NE(toastNodeDirty, nullptr);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    auto dialogTheme = context->GetTheme<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    toastPattern->OnDirtyLayoutWrapperSwap(dirty, {});
    EXPECT_FALSE(toastPattern->expandDisplay_);
    container->isFreeMultiWindow_ = true;
    dialogTheme->expandDisplay_ = true;
    toastPattern->OnDirtyLayoutWrapperSwap(dirty, {});
    EXPECT_TRUE(toastPattern->expandDisplay_);
    container->ResetContainer();
}

/**
 * @tc.name: ToastPatternUpdateHoverModeRect001
 * @tc.desc: Test UpdateHoverModeRect
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternUpdateHoverModeRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    toastPattern->wrapperRect_ = Rect(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE);
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProps = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProps, nullptr);
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    auto container = Container::CurrentSafelyWithCheck();
    auto displayInfo = container->GetDisplayInfo();
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
    EXPECT_TRUE(foldCreaseRects.empty());
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    safeAreaManager->keyboardInset_ = { .start = 0, .end = 1 };
    EXPECT_TRUE(safeAreaManager->GetKeyboardInset().IsValid());
    toastProps->propHoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    toastPattern->UpdateHoverModeRect(toastProps, safeAreaManager, 0.0f, 0.0f);
}

/**
 * @tc.name: ToastPatternUpdateHoverModeRect002
 * @tc.desc: Test UpdateHoverModeRect with empty displayInfo
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, ToastPatternUpdateHoverModeRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    toastPattern->wrapperRect_ = Rect(DOUBLEONE, DOUBLEONE, DOUBLEONE, DOUBLEONE);
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProps = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProps, nullptr);
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreaManager, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetDisplayInfo(nullptr);
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    safeAreaManager->keyboardInset_ = { .start = 0, .end = 1 };
    EXPECT_TRUE(safeAreaManager->GetKeyboardInset().IsValid());
    toastProps->propHoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    toastPattern->UpdateHoverModeRect(toastProps, safeAreaManager, 0.0f, 0.0f);
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode with empty displayInfo
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
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
    auto containerId = Container::CurrentId();
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    auto current_context = PipelineContext::GetCurrentContextSafelyWithCheck();
    auto pipeline = parentContainerId < 0 ? current_context : PipelineContext::GetMainPipelineContext();
    ASSERT_NE(pipeline, nullptr);
    auto currentCallBackId = pipeline->callbackId_;
    toastPattern->OnAttachToFrameNode();
    toastPattern->OnDetachFromFrameNode(AceType::RawPtr(toastNode));
    EXPECT_EQ(toastPattern->rowKeyboardCallbackId_, currentCallBackId + CALLBACK_COUNT);
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Increase the coverage of ToastPattern::OnWindowSizeChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestNg, OnWindowSizeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready toastInfo.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION};
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    /**
     * @tc.steps: step2. create ToastNode toastPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();

    auto pipeline = toastNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->isSubContainer_ = true;
    AceEngine::Get().AddContainer(pipeline->GetInstanceId(), container);

    auto overlayManager = pipeline->GetOverlayManager();

    toastPattern->OnWindowSizeChanged(0, 0,  WindowSizeChangeReason::ROTATION);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    toastPattern->OnWindowSizeChanged(0, 0,  WindowSizeChangeReason::DRAG_MOVE);
    EXPECT_TRUE(overlayManager->toastMap_.empty());
}
} // namespace OHOS::Ace::NG
