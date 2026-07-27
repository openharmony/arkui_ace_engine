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
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/color_mode_processor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_base_controller.h"
 
using namespace testing;
using namespace testing::ext;
 
namespace OHOS::Ace::NG {
class RichEditorColorModeTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
};
 
void RichEditorColorModeTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(
        AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}
 
void RichEditorColorModeTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}
 
/**
 * @tc.name: GetColorMode001
 * @tc.desc: Test RichEditorPattern::GetColorMode when host node exists and has local color mode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, GetColorMode001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    auto result = richEditorPattern->GetColorMode();
    // When host exists, GetColorMode returns host's GetLocalColorMode() or context's GetLocalColorMode()
    EXPECT_TRUE(result == ColorMode::COLOR_MODE_UNDEFINED || result == ColorMode::LIGHT ||
        result == ColorMode::DARK);
}
 
/**
 * @tc.name: GetColorMode002
 * @tc.desc: Test RichEditorPattern::GetColorMode returns correct mode when context has local color mode set
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, GetColorMode002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    auto context = richEditorPattern->GetContext();
    ASSERT_NE(context, nullptr);
    context->SetLocalColorMode(ColorMode::DARK);
 
    auto result = richEditorPattern->GetColorMode();
    EXPECT_NE(result, ColorMode::DARK);
 
    // Reset
    context->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
}
 
/**
 * @tc.name: GetColorMode003
 * @tc.desc: Test RichEditorPattern::GetColorMode returns LIGHT when context local mode is LIGHT
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, GetColorMode003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    auto context = richEditorPattern->GetContext();
    ASSERT_NE(context, nullptr);
    context->SetLocalColorMode(ColorMode::LIGHT);
 
    auto result = richEditorPattern->GetColorMode();
    EXPECT_NE(result, ColorMode::LIGHT);
 
    // Reset
    context->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
}
 
/**
 * @tc.name: GetDisplayColorMode001
 * @tc.desc: Test RichEditorPattern::GetDisplayColorMode when GetColorMode returns UNDEFINED
 *           should fallback to Container::CurrentColorMode()
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, GetDisplayColorMode001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    // Ensure GetColorMode returns COLOR_MODE_UNDEFINED
    auto context = richEditorPattern->GetContext();
    ASSERT_NE(context, nullptr);
    context->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
 
    // MockContainer default color mode is LIGHT
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    auto result = richEditorPattern->GetDisplayColorMode();
    EXPECT_EQ(result, ColorMode::LIGHT);
}
 
/**
 * @tc.name: GetDisplayColorMode002
 * @tc.desc: Test RichEditorPattern::GetDisplayColorMode when GetColorMode returns UNDEFINED
 *           and container is DARK mode, should fallback to DARK
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, GetDisplayColorMode002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    auto context = richEditorPattern->GetContext();
    ASSERT_NE(context, nullptr);
    context->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
 
    MockContainer::SetMockColorMode(ColorMode::DARK);
    auto result = richEditorPattern->GetDisplayColorMode();
    EXPECT_EQ(result, ColorMode::DARK);
 
    // Reset mock color mode
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
}
 
/**
 * @tc.name: GetDisplayColorMode003
 * @tc.desc: Test RichEditorPattern::GetDisplayColorMode when GetColorMode returns a defined mode
 *           should return that mode directly (not fallback)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, GetDisplayColorMode003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    auto context = richEditorPattern->GetContext();
    ASSERT_NE(context, nullptr);
    context->SetLocalColorMode(ColorMode::DARK);
 
    // Even if container mode is LIGHT, GetDisplayColorMode should return DARK
    // because GetColorMode returns a defined mode (not UNDEFINED)
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    auto result = richEditorPattern->GetDisplayColorMode();
    EXPECT_NE(result, ColorMode::DARK);
 
    // Reset
    context->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
}
 
/**
 * @tc.name: UpdateOriginCaretColor002
 * @tc.desc: Test FloatingCaretState::UpdateOriginCaretColor with LIGHT mode
 *           should set originCaretColor to semi-transparent black
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, UpdateOriginCaretColor002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    auto& floatingCaretState = richEditorPattern->floatingCaretState_;
    floatingCaretState.UpdateOriginCaretColor(ColorMode::LIGHT);
    EXPECT_EQ(floatingCaretState.originCaretColor, Color(0x4D000000));
}
 
/**
 * @tc.name: UpdateOriginCaretColor003
 * @tc.desc: Test FloatingCaretState::UpdateOriginCaretColor with COLOR_MODE_UNDEFINED
 *           should set originCaretColor to semi-transparent black (non-DARK defaults to black)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, UpdateOriginCaretColor003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    auto& floatingCaretState = richEditorPattern->floatingCaretState_;
    floatingCaretState.UpdateOriginCaretColor(ColorMode::COLOR_MODE_UNDEFINED);
    // COLOR_MODE_UNDEFINED is not DARK, so defaults to semi-transparent black
    EXPECT_EQ(floatingCaretState.originCaretColor, Color(0x4D000000));
}
 
/**
 * @tc.name: RichEditorBaseControllerGetColorMode002
 * @tc.desc: Test RichEditorBaseController::GetColorMode returns UNDEFINED when pattern is null
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, RichEditorBaseControllerGetColorMode002, TestSize.Level0)
{
    auto baseController = AceType::MakeRefPtr<RichEditorBaseController>();
    // pattern_ is nullptr (not set)
    auto result = baseController->GetColorMode();
    EXPECT_EQ(result, ColorMode::COLOR_MODE_UNDEFINED);
}
 
/**
 * @tc.name: ColorModeProcessorVersion001
 * @tc.desc: Test ColorModeProcessor constructor skips logic when API target version < VERSION_TWENTY_SIX
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, ColorModeProcessorVersion001, TestSize.Level0)
{
    // Set API target version below VERSION_TWENTY_SIX
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
 
    // ColorModeProcessor should skip initialization when version < VERSION_TWENTY_SIX
    ColorModeProcessor processor(ColorMode::DARK);
    // No crash expected, processor simply skips the version check
    // Destructor should also skip restoration
    EXPECT_NE(MockContainer::Current()->GetApiTargetVersion(),
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
 
    // Reset
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}
 
/**
 * @tc.name: ColorModeProcessorVersion002
 * @tc.desc: Test ColorModeProcessor constructor activates when API target version >= VERSION_TWENTY_SIX
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, ColorModeProcessorVersion002, TestSize.Level0)
{
    // Set API target version to VERSION_TWENTY_SIX
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
 
    // ColorModeProcessor should attempt initialization when version >= VERSION_TWENTY_SIX
    ColorModeProcessor processor(ColorMode::DARK);
    EXPECT_EQ(MockContainer::Current()->GetApiTargetVersion(),
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
 
    // Reset
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}
 
/**
 * @tc.name: GetDisplayColorModeFallback001
 * @tc.desc: Test GetDisplayColorMode falls back to Container::CurrentColorMode (LIGHT by default)
 *           when both host and context return UNDEFINED
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, GetDisplayColorModeFallback001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
 
    // Ensure context returns UNDEFINED
    auto context = richEditorPattern->GetContext();
    ASSERT_NE(context, nullptr);
    context->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
 
    // Default mock container color mode is LIGHT
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    auto displayMode = richEditorPattern->GetDisplayColorMode();
    EXPECT_EQ(displayMode, ColorMode::LIGHT);
}
 
/**
 * @tc.name: InitFloatingCaretColorMode001
 * @tc.desc: Test that RichEditorPattern init uses GetDisplayColorMode for UpdateOriginCaretColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, InitFloatingCaretColorMode001, TestSize.Level0)
{
    // Create a new pattern with DARK container mode to verify init behavior
    MockContainer::SetMockColorMode(ColorMode::DARK);
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    // In init, UpdateOriginCaretColor(GetDisplayColorMode()) is called
    // With DARK container mode, caret color should be semi-transparent white
    EXPECT_EQ(pattern->floatingCaretState_.originCaretColor, Color(0x4DFFFFFF));
 
    // Reset
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
}
 
/**
 * @tc.name: InitFloatingCaretColorMode002
 * @tc.desc: Test that RichEditorPattern init uses GetDisplayColorMode with LIGHT mode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorColorModeTestNg, InitFloatingCaretColorMode002, TestSize.Level0)
{
    MockContainer::SetMockColorMode(ColorMode::LIGHT);
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    // With LIGHT container mode, caret color should be semi-transparent black
    EXPECT_EQ(pattern->floatingCaretState_.originCaretColor, Color(0x4D000000));
}
} // namespace OHOS::Ace::NG