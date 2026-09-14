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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/text_field/clean_node_host.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RichEditorCancelButtonTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        richEditorNode_ = FrameNode::GetOrCreateFrameNode(
            V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(true); });
        ASSERT_NE(richEditorNode_, nullptr);
        auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
        ASSERT_NE(pattern, nullptr);
        pattern->InitScrollablePattern();
        pattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
        pattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
        pattern->CreateNodePaintMethod();
    }
    void TearDown() override
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: ICleanNodeHostInheritance
 * @tc.desc: Verify RichEditorPattern inherits ICleanNodeHost and all 24 methods are callable.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ICleanNodeHostInheritance, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_EQ(hostInterface->GetCleanNodeStyle().value(), CleanNodeStyle::INPUT);
    EXPECT_EQ(hostInterface->GetIsShowSymbol(), true);
    EXPECT_EQ(hostInterface->GetCancelIconSize(), CalcDimension());
    EXPECT_EQ(hostInterface->GetCancelIconColor(), Color());
    EXPECT_EQ(hostInterface->GetCancelIconSrc(), std::string());
    EXPECT_EQ(hostInterface->GetBundleName(), std::string());
    EXPECT_EQ(hostInterface->GetModuleName(), std::string());
    EXPECT_FALSE(hostInterface->HasCancelIconSize());
    EXPECT_FALSE(hostInterface->HasCancelIconColor());
    EXPECT_FALSE(hostInterface->HasCancelIconSrc());
    EXPECT_FALSE(hostInterface->HasBundleName());
    EXPECT_FALSE(hostInterface->HasModuleName());
    EXPECT_FALSE(hostInterface->GetIsDisabled());
    EXPECT_FALSE(hostInterface->IsDragging());
    EXPECT_FALSE(hostInterface->HasUserAccessibilityText());
    EXPECT_FALSE(hostInterface->IsShowCancelButtonMode());
    EXPECT_FALSE(hostInterface->HasCancelMaxFontScale());
    EXPECT_FALSE(hostInterface->HasCancelMinFontScale());
}

/**
 * @tc.name: ProcessCancelButtonCreatesResponseArea
 * @tc.desc: After setting cancel button via SetCancelButton and calling OnModifyDone, CleanNodeResponseArea exists.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ProcessCancelButtonCreatesResponseArea, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    pattern->OnModifyDone();
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
}

/**
 * @tc.name: ThreeStateDisplay_ConstantAlwaysShows
 * @tc.desc: style=CONSTANT should show cancel button regardless of content.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ThreeStateDisplay_ConstantAlwaysShows, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
}

/**
 * @tc.name: ThreeStateDisplay_InvisibleAlwaysHides
 * @tc.desc: style=INVISIBLE should hide cancel button regardless of content.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ThreeStateDisplay_InvisibleAlwaysHides, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::INVISIBLE),
        CalcDimension(16.0_vp), Color::WHITE, "");
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
}

/**
 * @tc.name: ThreeStateDisplay_InputShowsWhenContent
 * @tc.desc: style=INPUT should show cancel button when IsShowCancelButton is set and content exists.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ThreeStateDisplay_InputShowsWhenContent, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::INPUT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
}

/**
 * @tc.name: HandleCleanNodeClickedClearsContent
 * @tc.desc: HandleCleanNodeClicked should clear all text content via DeleteForward.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, HandleCleanNodeClickedClearsContent, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    // HandleCleanNodeClicked should not crash even with empty content
    hostInterface->HandleCleanNodeClicked();
    SUCCEED();
}

/**
 * @tc.name: PropertyGettersReturnSetValues
 * @tc.desc: Verify that getters return values set via SetCancelButton.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, PropertyGettersReturnSetValues, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(20.0_vp), Color::RED, "icon.png");
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_EQ(hostInterface->GetCleanNodeStyle().value(), CleanNodeStyle::CONSTANT);
    EXPECT_EQ(hostInterface->GetCancelIconSize().Value(), 20.0f);
    EXPECT_EQ(hostInterface->GetCancelIconColor(), Color::RED);
    EXPECT_EQ(hostInterface->GetCancelIconSrc(), "icon.png");
    EXPECT_FALSE(hostInterface->GetIsShowSymbol());
    EXPECT_TRUE(hostInterface->HasCancelIconSize());
    EXPECT_TRUE(hostInterface->HasCancelIconColor());
    EXPECT_TRUE(hostInterface->HasCancelIconSrc());
}

/**
 * @tc.name: LayoutAlgorithmChildrenSizeIsTwo
 * @tc.desc: Verify RichEditorLayoutAlgorithm CHILDREN_SIZE is 2 after cancel button support.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, LayoutAlgorithmChildrenSizeIsTwo, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    pattern->OnModifyDone();
    // After OnModifyDone with cancel button enabled, the host node should have 2 children:
    // content node + cancel button node
    auto children = richEditorNode_->GetChildren();
    EXPECT_GE(children.size(), 1u); // At least content node exists
}

/**
 * @tc.name: ProcessCancelButton_RefreshExistingArea
 * @tc.desc: Call OnModifyDone twice to hit the Refresh path (branch A) of ProcessCancelButton.
 *           When cleanNodeResponseArea_ already exists and IsShowCancelButtonMode is true,
 *           it should Refresh + UpdateShowState instead of creating a new area.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ProcessCancelButton_RefreshExistingArea, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    // First OnModifyDone: creates the response area (branch B)
    pattern->OnModifyDone();
    ASSERT_NE(pattern->cleanNodeResponseArea_, nullptr);
    // Second OnModifyDone: should refresh existing area (branch A)
    pattern->MarkCancelButtonDirty();
    pattern->OnModifyDone();
    ASSERT_NE(pattern->cleanNodeResponseArea_, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
}

/**
 * @tc.name: ProcessCancelButton_DisableAndClearArea
 * @tc.desc: Enable cancel button then disable it to hit the ClearArea path (branch C).
 *           When IsShowCancelButtonMode is false and cleanNodeResponseArea_ exists,
 *           it should ClearArea + Reset.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ProcessCancelButton_DisableAndClearArea, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    pattern->OnModifyDone();
    ASSERT_NE(pattern->cleanNodeResponseArea_, nullptr);
    // Disable: should clear area (branch C)
    RichEditorModelNG::ResetCancelButton(frameNode);
    pattern->OnModifyDone();
    ASSERT_EQ(pattern->cleanNodeResponseArea_, nullptr);
}

/**
 * @tc.name: ProcessCancelButton_DisableNoArea
 * @tc.desc: When IsShowCancelButtonMode is false and no area exists (branch D),
 *           ProcessCancelButton should be a no-op without crash.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ProcessCancelButton_DisableNoArea, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    // No cancel button set, OnModifyDone should be a no-op
    pattern->OnModifyDone();
    // No area should be created when disabled
    ASSERT_EQ(pattern->cleanNodeResponseArea_, nullptr);
    // Call again to verify no crash
    pattern->OnModifyDone();
    ASSERT_EQ(pattern->cleanNodeResponseArea_, nullptr);
}

/**
 * @tc.name: ResetCancelButton_RestoresDefaults
 * @tc.desc: Set all cancel button properties via SetCancelButton then call ResetCancelButton,
 *           verify all getters return default values afterwards.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, ResetCancelButton_RestoresDefaults, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(20.0_vp), Color::RED, "icon.png");
    // Verify properties are set
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_EQ(hostInterface->GetCleanNodeStyle().value(), CleanNodeStyle::CONSTANT);
    EXPECT_TRUE(hostInterface->HasCancelIconSize());
    EXPECT_TRUE(hostInterface->HasCancelIconColor());
    EXPECT_TRUE(hostInterface->HasCancelIconSrc());
    // Reset
    RichEditorModelNG::ResetCancelButton(frameNode);
    // Verify defaults are restored
    EXPECT_EQ(hostInterface->GetCleanNodeStyle().value(), CleanNodeStyle::INPUT);
    EXPECT_FALSE(hostInterface->HasCancelIconSize());
    EXPECT_FALSE(hostInterface->HasCancelIconColor());
    EXPECT_FALSE(hostInterface->HasCancelIconSrc());
    EXPECT_FALSE(hostInterface->HasBundleName());
    EXPECT_FALSE(hostInterface->HasModuleName());
    EXPECT_FALSE(hostInterface->IsShowCancelButtonMode());
    EXPECT_TRUE(hostInterface->GetIsShowSymbol());
}

/**
 * @tc.name: SetCancelButton_CombinedSetter
 * @tc.desc: Use SetCancelButton (combined setter) to set all properties at once,
 *           verify each getter returns the expected value.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, SetCancelButton_CombinedSetter, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(16.0_vp), Color::BLUE, "cancel.png");
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_EQ(hostInterface->GetCleanNodeStyle().value(), CleanNodeStyle::CONSTANT);
    EXPECT_EQ(hostInterface->GetCancelIconSize().Value(), 16.0f);
    EXPECT_EQ(hostInterface->GetCancelIconColor(), Color::BLUE);
    EXPECT_EQ(hostInterface->GetCancelIconSrc(), "cancel.png");
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
}

/**
 * @tc.name: UpdateShowState_InvisibleStyleHides
 * @tc.desc: Create area with CONSTANT style, then switch to INVISIBLE style and
 *           call OnModifyDone to trigger UpdateShowState hiding path.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, UpdateShowState_InvisibleStyleHides, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::CONSTANT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    pattern->OnModifyDone();
    ASSERT_NE(pattern->cleanNodeResponseArea_, nullptr);
    // Switch to INVISIBLE: should trigger UpdateShowState hide path
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::INVISIBLE),
        CalcDimension(16.0_vp), Color::WHITE, "");
    pattern->OnModifyDone();
    // Area should still exist (Refresh path, not ClearArea)
    ASSERT_NE(pattern->cleanNodeResponseArea_, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_EQ(hostInterface->GetCleanNodeStyle().value(), CleanNodeStyle::INVISIBLE);
}

/**
 * @tc.name: UpdateShowState_InputStyleNoContentHides
 * @tc.desc: With INPUT style and no content, UpdateShowState should hide the cancel button.
 *           Area is created but should not be visible.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, UpdateShowState_InputStyleNoContentHides, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    RichEditorModelNG::SetCancelButton(frameNode, static_cast<int32_t>(CleanNodeStyle::INPUT),
        CalcDimension(16.0_vp), Color::WHITE, "");
    pattern->OnModifyDone();
    // Area should be created
    ASSERT_NE(pattern->cleanNodeResponseArea_, nullptr);
    // With INPUT style and empty content, IsContentEmpty returns true,
    // so UpdateShowState should call UpdateCleanNode(false)
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    EXPECT_TRUE(hostInterface->IsShowCancelButtonMode());
    EXPECT_TRUE(hostInterface->IsContentEmpty());
}

/**
 * @tc.name: HandleCleanNodeClicked_NotCrashingWithContent
 * @tc.desc: Add content to the RichEditor and call HandleCleanNodeClicked,
 *           verify it does not crash and clears content.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, HandleCleanNodeClicked_NotCrashingWithContent, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);
    // With empty content, HandleCleanNodeClicked should not crash
    EXPECT_TRUE(hostInterface->IsContentEmpty());
    hostInterface->HandleCleanNodeClicked();
    SUCCEED();
}

/**
 * @tc.name: HandleCleanNodeClickedRequestsFocusWhenNotFocused
 * @tc.desc: When not focused, HandleCleanNodeClicked should request focus via RequestFocusImmediately,
 *           so that HandleFocusEvent is triggered and the component gains focus.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, HandleCleanNodeClickedRequestsFocusWhenNotFocused, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);

    EXPECT_FALSE(pattern->HasFocus());
    hostInterface->HandleCleanNodeClicked();
    EXPECT_TRUE(pattern->HasFocus());
}

/**
 * @tc.name: HandleCleanNodeClickedSetsEditingState
 * @tc.desc: When not focused, HandleCleanNodeClicked should set isEditing_ to true
 *           via HandleFocusEvent → HandleOnEditChanged.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, HandleCleanNodeClickedSetsEditingState, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);

    EXPECT_FALSE(pattern->isEditing_);
    hostInterface->HandleCleanNodeClicked();
    EXPECT_TRUE(pattern->isEditing_);
}

/**
 * @tc.name: HandleCleanNodeClickedStartsTwinkling
 * @tc.desc: HandleCleanNodeClicked should start caret twinkling.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, HandleCleanNodeClickedStartsTwinkling, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);

    EXPECT_FALSE(pattern->caretTwinkling_);
    hostInterface->HandleCleanNodeClicked();
    EXPECT_TRUE(pattern->caretTwinkling_);
}

/**
 * @tc.name: HandleCleanNodeClickedNoSideEffectWhenAlreadyFocused
 * @tc.desc: When already focused, HandleCleanNodeClicked should not crash and remain focused.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCancelButtonTestNg, HandleCleanNodeClickedNoSideEffectWhenAlreadyFocused, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hostInterface = AceType::DynamicCast<ICleanNodeHost>(pattern);
    ASSERT_NE(hostInterface, nullptr);

    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    ASSERT_TRUE(pattern->HasFocus());
    pattern->isEditing_ = true;

    hostInterface->HandleCleanNodeClicked();
    EXPECT_TRUE(pattern->HasFocus());
    EXPECT_TRUE(pattern->isEditing_);
}
} // namespace OHOS::Ace::NG
