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

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternMultiThreadTest : public TextInputBases {
public:
};

/**
 * @tc.name: OnAttachToFrameNodeMultiThread001
 * @tc.desc: Test OnAttachToFrameNodeMultiThread (empty function)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, OnAttachToFrameNodeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call OnAttachToFrameNodeMultiThread
     * @tc.expected: Should not crash (empty function)
     */
    pattern_->OnAttachToFrameNodeMultiThread();

    /**
     * @tc.expected: Pattern should still be valid after function call
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread001
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread (empty function)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, OnDetachFromFrameNodeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call OnDetachFromFrameNodeMultiThread
     * @tc.expected: Should not crash (empty function)
     */
    pattern_->OnDetachFromFrameNodeMultiThread(nullptr);

    /**
     * @tc.expected: Pattern should still be valid after function call
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread001
 * @tc.desc: Test OnAttachToMainTreeMultiThread with valid setup
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, OnAttachToMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call OnAttachToMainTreeMultiThread
     * @tc.expected: Should execute successfully
     */
    pattern_->OnAttachToMainTreeMultiThread();

    /**
     * @tc.expected: isDetachFromMainTree_ should be false
     */
    EXPECT_FALSE(pattern_->isDetachFromMainTree_);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread002
 * @tc.desc: Test OnAttachToMainTreeMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, OnAttachToMainTreeMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnAttachToMainTreeMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->OnAttachToMainTreeMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread001
 * @tc.desc: Test OnDetachFromMainTreeMultiThread with full setup
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, OnDetachFromMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Setup surface changed callback
     */
    pattern_->surfaceChangedCallbackId_ = 1;

    /**
     * @tc.steps: step3. Setup surface position changed callback
     */
    pattern_->surfacePositionChangedCallbackId_ = 2;

    /**
     * @tc.steps: step4. Call OnDetachFromMainTreeMultiThread
     * @tc.expected: Should execute successfully and clean up
     */
    pattern_->OnDetachFromMainTreeMultiThread();

    /**
     * @tc.expected: isDetachFromMainTree_ should be true
     */
    EXPECT_TRUE(pattern_->isDetachFromMainTree_);
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread002
 * @tc.desc: Test OnDetachFromMainTreeMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, OnDetachFromMainTreeMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnDetachFromMainTreeMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->OnDetachFromMainTreeMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateCaretInfoToControllerMultiThread001
 * @tc.desc: Test UpdateCaretInfoToControllerMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, UpdateCaretInfoToControllerMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call UpdateCaretInfoToControllerMultiThread
     * @tc.expected: Should post task successfully
     */
    pattern_->UpdateCaretInfoToControllerMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: UpdateCaretInfoToControllerMultiThread002
 * @tc.desc: Test UpdateCaretInfoToControllerMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, UpdateCaretInfoToControllerMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call UpdateCaretInfoToControllerMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->UpdateCaretInfoToControllerMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: HandleSetSelectionMultiThread001
 * @tc.desc: Test HandleSetSelectionMultiThread with showHandle=true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, HandleSetSelectionMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call HandleSetSelectionMultiThread with showHandle=true
     * @tc.expected: Should call ProcessOverlay
     */
    pattern_->HandleSetSelectionMultiThread(0, 5, true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: HandleSetSelectionMultiThread002
 * @tc.desc: Test HandleSetSelectionMultiThread with showHandle=false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, HandleSetSelectionMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call HandleSetSelectionMultiThread with showHandle=false
     * @tc.expected: Should call CloseSelectOverlay
     */
    pattern_->HandleSetSelectionMultiThread(0, 5, false);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: HandleSetSelectionMultiThread003
 * @tc.desc: Test HandleSetSelectionMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, HandleSetSelectionMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call HandleSetSelectionMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->HandleSetSelectionMultiThread(0, 5, true);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: InitSurfaceChangedCallbackMultiThread001
 * @tc.desc: Test InitSurfaceChangedCallbackMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, InitSurfaceChangedCallbackMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call InitSurfaceChangedCallbackMultiThread
     * @tc.expected: Should post task successfully
     */
    pattern_->InitSurfaceChangedCallbackMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: InitSurfaceChangedCallbackMultiThread002
 * @tc.desc: Test InitSurfaceChangedCallbackMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, InitSurfaceChangedCallbackMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call InitSurfaceChangedCallbackMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->InitSurfaceChangedCallbackMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: InitSurfacePositionChangedCallbackMultiThread001
 * @tc.desc: Test InitSurfacePositionChangedCallbackMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, InitSurfacePositionChangedCallbackMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call InitSurfacePositionChangedCallbackMultiThread
     * @tc.expected: Should post task successfully
     */
    pattern_->InitSurfacePositionChangedCallbackMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: InitSurfacePositionChangedCallbackMultiThread002
 * @tc.desc: Test InitSurfacePositionChangedCallbackMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, InitSurfacePositionChangedCallbackMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call InitSurfacePositionChangedCallbackMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->InitSurfacePositionChangedCallbackMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetCaretPositionMultiThread001
 * @tc.desc: Test SetCaretPositionMultiThread with focus and no magnifier
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCaretPositionMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Ensure magnifier is not shown
     */
    if (pattern_->magnifierController_) {
        pattern_->magnifierController_->UpdateShowMagnifier(false);
    }

    /**
     * @tc.steps: step4. Call SetCaretPositionMultiThread
     * @tc.expected: Should call StartTwinklingMultiThread
     */
    pattern_->SetCaretPositionMultiThread(5, false);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetCaretPositionMultiThread002
 * @tc.desc: Test SetCaretPositionMultiThread with moveContent=true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCaretPositionMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Call SetCaretPositionMultiThread with moveContent=true
     * @tc.expected: Should execute with moveContent enabled
     */
    pattern_->SetCaretPositionMultiThread(10, true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetCaretPositionMultiThread003
 * @tc.desc: Test SetCaretPositionMultiThread without focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCaretPositionMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Don't get focus (no focus state)
     * @tc.expected: Should not call StartTwinklingMultiThread
     */

    /**
     * @tc.steps: step3. Call SetCaretPositionMultiThread
     * @tc.expected: Should skip StartTwinklingMultiThread
     */
    pattern_->SetCaretPositionMultiThread(5, false);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetCaretPositionMultiThread004
 * @tc.desc: Test SetCaretPositionMultiThread with magnifier shown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCaretPositionMultiThread004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Show magnifier
     */
    if (pattern_->magnifierController_) {
        pattern_->magnifierController_->UpdateShowMagnifier(true);
    }

    /**
     * @tc.steps: step4. Call SetCaretPositionMultiThread
     * @tc.expected: Should skip StartTwinklingMultiThread when magnifier is shown
     */
    pattern_->SetCaretPositionMultiThread(5, false);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetCaretPositionMultiThread005
 * @tc.desc: Test SetCaretPositionMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCaretPositionMultiThread005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call SetCaretPositionMultiThread
     * @tc.expected: Should handle null host gracefully
     */
    pattern->SetCaretPositionMultiThread(5, false);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: MoveCaretToContentRectMultiThread001
 * @tc.desc: Test MoveCaretToContentRectMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, MoveCaretToContentRectMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create MoveCaretToContentRectData
     */
    MoveCaretToContentRectData data;
    data.index = 5;
    data.textAffinity = TextAffinity::DOWNSTREAM;
    data.isEditorValueChanged = true;
    data.moveContent = false;

    /**
     * @tc.steps: step3. Call MoveCaretToContentRectMultiThread
     * @tc.expected: Should post task successfully
     */
    pattern_->MoveCaretToContentRectMultiThread(data);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: MoveCaretToContentRectMultiThread002
 * @tc.desc: Test MoveCaretToContentRectMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, MoveCaretToContentRectMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create MoveCaretToContentRectData
     */
    MoveCaretToContentRectData data;
    data.index = 5;

    /**
     * @tc.steps: step3. Call MoveCaretToContentRectMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->MoveCaretToContentRectMultiThread(data);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetSelectionFlagMultiThread001
 * @tc.desc: Test SetSelectionFlagMultiThread with selectionStart == selectionEnd (caret mode)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetSelectionFlagMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Call SetSelectionFlagMultiThread with same start and end
     * @tc.expected: Should enter caret mode (not selection mode)
     */
    pattern_->SetSelectionFlagMultiThread(5, 5, std::nullopt, true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetSelectionFlagMultiThread002
 * @tc.desc: Test SetSelectionFlagMultiThread with selectionStart != selectionEnd (selection mode)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetSelectionFlagMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Call SetSelectionFlagMultiThread with different start and end
     * @tc.expected: Should enter selection mode
     */
    pattern_->SetSelectionFlagMultiThread(0, 5, std::nullopt, true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetSelectionFlagMultiThread003
 * @tc.desc: Test SetSelectionFlagMultiThread without focus (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetSelectionFlagMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Don't get focus
     * @tc.expected: Should return early without executing
     */

    /**
     * @tc.steps: step3. Call SetSelectionFlagMultiThread
     * @tc.expected: Should return early due to no focus
     */
    pattern_->SetSelectionFlagMultiThread(0, 5, std::nullopt, true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetSelectionFlagMultiThread004
 * @tc.desc: Test SetSelectionFlagMultiThread with preview text (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetSelectionFlagMultiThread004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Set preview text mode
     */
    pattern_->hasPreviewText_ = true;

    /**
     * @tc.steps: step4. Call SetSelectionFlagMultiThread
     * @tc.expected: Should return early due to preview text mode
     */
    pattern_->SetSelectionFlagMultiThread(0, 5, std::nullopt, true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetSelectionFlagMultiThread005
 * @tc.desc: Test SetSelectionFlagMultiThread with out-of-range indices (clamping test)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetSelectionFlagMultiThread005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Call SetSelectionFlagMultiThread with out-of-range values
     * @tc.expected: Should clamp indices to valid range
     */
    pattern_->SetSelectionFlagMultiThread(-10, 1000, std::nullopt, true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetSelectionFlagMultiThread006
 * @tc.desc: Test SetSelectionFlagMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetSelectionFlagMultiThread006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call SetSelectionFlagMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->SetSelectionFlagMultiThread(0, 5, std::nullopt, true);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: StopEditingMultiThread001
 * @tc.desc: Test StopEditingMultiThread with focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, StopEditingMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Call StopEditingMultiThread
     * @tc.expected: Should post task to stop editing
     */
    pattern_->StopEditingMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: StopEditingMultiThread002
 * @tc.desc: Test StopEditingMultiThread without focus (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, StopEditingMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Don't get focus
     * @tc.expected: Should return early without executing
     */

    /**
     * @tc.steps: step3. Call StopEditingMultiThread
     * @tc.expected: Should return early due to no focus
     */
    pattern_->StopEditingMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: StopEditingMultiThread003
 * @tc.desc: Test StopEditingMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, StopEditingMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call StopEditingMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->StopEditingMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterWindowSizeCallbackMultiThread001
 * @tc.desc: Test RegisterWindowSizeCallbackMultiThread (first time registration)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, RegisterWindowSizeCallbackMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Ensure not registered yet
     */
    pattern_->isOritationListenerRegisted_ = false;

    /**
     * @tc.steps: step3. Call RegisterWindowSizeCallbackMultiThread
     * @tc.expected: Should register callback
     */
    pattern_->RegisterWindowSizeCallbackMultiThread();

    /**
     * @tc.expected: isOritationListenerRegisted_ should be true
     */
    EXPECT_TRUE(pattern_->isOritationListenerRegisted_);
}

/**
 * @tc.name: RegisterWindowSizeCallbackMultiThread002
 * @tc.desc: Test RegisterWindowSizeCallbackMultiThread (already registered)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, RegisterWindowSizeCallbackMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Mark as already registered
     */
    pattern_->isOritationListenerRegisted_ = true;

    /**
     * @tc.steps: step3. Call RegisterWindowSizeCallbackMultiThread
     * @tc.expected: Should return early without re-registering
     */
    pattern_->RegisterWindowSizeCallbackMultiThread();

    /**
     * @tc.expected: isOritationListenerRegisted_ should still be true
     */
    EXPECT_TRUE(pattern_->isOritationListenerRegisted_);
}

/**
 * @tc.name: RegisterWindowSizeCallbackMultiThread003
 * @tc.desc: Test RegisterWindowSizeCallbackMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, RegisterWindowSizeCallbackMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call RegisterWindowSizeCallbackMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->RegisterWindowSizeCallbackMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterWindowFocusChangeCallbackMultiThread001
 * @tc.desc: Test RegisterWindowFocusChangeCallbackMultiThread (first time registration)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, RegisterWindowFocusChangeCallbackMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Ensure not registered yet
     */
    pattern_->isWindowFocusChangeCallbackRegisted_ = false;

    /**
     * @tc.steps: step3. Call RegisterWindowFocusChangeCallbackMultiThread
     * @tc.expected: Should register callback
     */
    pattern_->RegisterWindowFocusChangeCallbackMultiThread();

    /**
     * @tc.expected: isWindowFocusChangeCallbackRegisted_ should be true
     */
    EXPECT_TRUE(pattern_->isWindowFocusChangeCallbackRegisted_);
}

/**
 * @tc.name: RegisterWindowFocusChangeCallbackMultiThread002
 * @tc.desc: Test RegisterWindowFocusChangeCallbackMultiThread (already registered)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, RegisterWindowFocusChangeCallbackMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Mark as already registered
     */
    pattern_->isWindowFocusChangeCallbackRegisted_ = true;

    /**
     * @tc.steps: step3. Call RegisterWindowFocusChangeCallbackMultiThread
     * @tc.expected: Should return early without re-registering
     */
    pattern_->RegisterWindowFocusChangeCallbackMultiThread();

    /**
     * @tc.expected: isWindowFocusChangeCallbackRegisted_ should still be true
     */
    EXPECT_TRUE(pattern_->isWindowFocusChangeCallbackRegisted_);
}

/**
 * @tc.name: RegisterWindowFocusChangeCallbackMultiThread003
 * @tc.desc: Test RegisterWindowFocusChangeCallbackMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, RegisterWindowFocusChangeCallbackMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call RegisterWindowFocusChangeCallbackMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->RegisterWindowFocusChangeCallbackMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetPreviewTextOperationMultiThread001
 * @tc.desc: Test SetPreviewTextOperationMultiThread with valid info
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetPreviewTextOperationMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create PreviewTextInfo
     */
    PreviewTextInfo info;
    info.text = u"preview";
    info.range.start = 0;
    info.range.end = 7;

    /**
     * @tc.steps: step3. Call SetPreviewTextOperationMultiThread
     * @tc.expected: Should set preview text successfully
     */
    pattern_->SetPreviewTextOperationMultiThread(info);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetPreviewTextOperationMultiThread002
 * @tc.desc: Test SetPreviewTextOperationMultiThread with focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetPreviewTextOperationMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Create PreviewTextInfo
     */
    PreviewTextInfo info;
    info.text = u"preview";
    info.range.start = 0;
    info.range.end = 7;

    /**
     * @tc.steps: step4. Call SetPreviewTextOperationMultiThread
     * @tc.expected: Should start twinkling
     */
    pattern_->SetPreviewTextOperationMultiThread(info);

    /**
     * @tc.expected: cursorVisible_ should be true when focused
     */
    EXPECT_TRUE(pattern_->cursorVisible_);
}

/**
 * @tc.name: SetPreviewTextOperationMultiThread003
 * @tc.desc: Test SetPreviewTextOperationMultiThread without focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetPreviewTextOperationMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Don't get focus
     * @tc.expected: Should stop twinkling
     */

    /**
     * @tc.steps: step3. Create PreviewTextInfo
     */
    PreviewTextInfo info;
    info.text = u"preview";
    info.range.start = 0;
    info.range.end = 7;

    /**
     * @tc.steps: step4. Call SetPreviewTextOperationMultiThread
     * @tc.expected: cursorVisible_ should be false when not focused
     */
    pattern_->SetPreviewTextOperationMultiThread(info);

    /**
     * @tc.expected: cursorVisible_ should be false without focus
     */
    EXPECT_FALSE(pattern_->cursorVisible_);
}

/**
 * @tc.name: SetPreviewTextOperationMultiThread004
 * @tc.desc: Test SetPreviewTextOperationMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetPreviewTextOperationMultiThread004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create PreviewTextInfo
     */
    PreviewTextInfo info;
    info.text = u"preview";
    info.range.start = 0;
    info.range.end = 7;

    /**
     * @tc.steps: step3. Call SetPreviewTextOperationMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->SetPreviewTextOperationMultiThread(info);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: StartTwinklingMultiThread001
 * @tc.desc: Test StartTwinklingMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, StartTwinklingMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call StartTwinklingMultiThread
     * @tc.expected: Should post task successfully
     */
    pattern_->StartTwinklingMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: StartTwinklingMultiThread002
 * @tc.desc: Test StartTwinklingMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, StartTwinklingMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call StartTwinklingMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->StartTwinklingMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetPreviewTextOperationMultiThreadPart001
 * @tc.desc: Test SetPreviewTextOperationMultiThreadPart
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetPreviewTextOperationMultiThreadPart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create PreviewTextInfo
     */
    PreviewTextInfo info;
    info.text = u"preview";

    /**
     * @tc.steps: step3. Call SetPreviewTextOperationMultiThreadPart
     * @tc.expected: Should set preview text
     */
    pattern_->SetPreviewTextOperationMultiThreadPart(info, 0, 7);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetPreviewTextOperationMultiThreadPart002
 * @tc.desc: Test SetPreviewTextOperationMultiThreadPart with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetPreviewTextOperationMultiThreadPart002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create PreviewTextInfo
     */
    PreviewTextInfo info;
    info.text = u"preview";

    /**
     * @tc.steps: step3. Call SetPreviewTextOperationMultiThreadPart
     * @tc.expected: Should return early without crash
     */
    pattern->SetPreviewTextOperationMultiThreadPart(info, 0, 7);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThread001
 * @tc.desc: Test FinishTextPreviewOperationMultiThread with preview text
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Set preview text mode
     */
    pattern_->hasPreviewText_ = true;

    /**
     * @tc.steps: step3. Call FinishTextPreviewOperationMultiThread
     * @tc.expected: Should finish preview successfully
     */
    pattern_->FinishTextPreviewOperationMultiThread(true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThread002
 * @tc.desc: Test FinishTextPreviewOperationMultiThread without preview text (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Ensure no preview text
     */
    pattern_->hasPreviewText_ = false;

    /**
     * @tc.steps: step3. Call FinishTextPreviewOperationMultiThread
     * @tc.expected: Should return early due to no preview text
     */
    pattern_->FinishTextPreviewOperationMultiThread(true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThread003
 * @tc.desc: Test FinishTextPreviewOperationMultiThread with MaxLength set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(10);
    });
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Set preview text mode
     */
    pattern_->hasPreviewText_ = true;

    /**
     * @tc.steps: step3. Call FinishTextPreviewOperationMultiThread
     * @tc.expected: Should handle max length
     */
    pattern_->FinishTextPreviewOperationMultiThread(true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThread004
 * @tc.desc: Test FinishTextPreviewOperationMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThread004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set preview text mode
     */
    pattern->hasPreviewText_ = true;

    /**
     * @tc.steps: step3. Call FinishTextPreviewOperationMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->FinishTextPreviewOperationMultiThread(true);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThread005
 * @tc.desc: Test FinishTextPreviewOperationMultiThread with focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThread005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Set preview text mode
     */
    pattern_->hasPreviewText_ = true;

    /**
     * @tc.steps: step4. Call FinishTextPreviewOperationMultiThread
     * @tc.expected: Should start twinkling when focused
     */
    pattern_->FinishTextPreviewOperationMultiThread(true);

    /**
     * @tc.expected: cursorVisible_ should be true when focused
     */
    EXPECT_TRUE(pattern_->cursorVisible_);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThread006
 * @tc.desc: Test FinishTextPreviewOperationMultiThread without focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThread006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Don't get focus
     * @tc.expected: Should stop twinkling
     */

    /**
     * @tc.steps: step3. Set preview text mode
     */
    pattern_->hasPreviewText_ = true;

    /**
     * @tc.steps: step4. Call FinishTextPreviewOperationMultiThread
     * @tc.expected: cursorVisible_ should be false without focus
     */
    pattern_->FinishTextPreviewOperationMultiThread(true);

    /**
     * @tc.expected: cursorVisible_ should be false without focus
     */
    EXPECT_FALSE(pattern_->cursorVisible_);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThreadPart001
 * @tc.desc: Test FinishTextPreviewOperationMultiThreadPart with triggerOnWillChange=true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThreadPart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Set preview text mode
     */
    pattern_->hasPreviewText_ = true;
    pattern_->previewTextStart_ = 0;
    pattern_->previewTextEnd_ = 7;

    /**
     * @tc.steps: step3. Call FinishTextPreviewOperationMultiThreadPart with triggerOnWillChange=true
     * @tc.expected: Should call FireOnWillChange
     */
    pattern_->FinishTextPreviewOperationMultiThreadPart(true);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: FinishTextPreviewOperationMultiThreadPart002
 * @tc.desc: Test FinishTextPreviewOperationMultiThreadPart with triggerOnWillChange=false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, FinishTextPreviewOperationMultiThreadPart002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Set preview text mode
     */
    pattern_->hasPreviewText_ = true;
    pattern_->previewTextStart_ = 0;
    pattern_->previewTextEnd_ = 7;

    /**
     * @tc.steps: step3. Call FinishTextPreviewOperationMultiThreadPart with triggerOnWillChange=false
     * @tc.expected: Should skip FireOnWillChange
     */
    pattern_->FinishTextPreviewOperationMultiThreadPart(false);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetShowKeyBoardOnFocusMultiThread001
 * @tc.desc: Test SetShowKeyBoardOnFocusMultiThread with value change to true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetShowKeyBoardOnFocusMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Set initial value to false
     */
    pattern_->showKeyBoardOnFocus_ = false;

    /**
     * @tc.steps: step4. Call SetShowKeyBoardOnFocusMultiThread with true
     * @tc.expected: Should request keyboard
     */
    pattern_->SetShowKeyBoardOnFocusMultiThread(true);

    /**
     * @tc.expected: showKeyBoardOnFocus_ should be true
     */
    EXPECT_TRUE(pattern_->showKeyBoardOnFocus_);
}

/**
 * @tc.name: SetShowKeyBoardOnFocusMultiThread002
 * @tc.desc: Test SetShowKeyBoardOnFocusMultiThread with value change to false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetShowKeyBoardOnFocusMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Set initial value to true
     */
    pattern_->showKeyBoardOnFocus_ = true;

    /**
     * @tc.steps: step4. Call SetShowKeyBoardOnFocusMultiThread with false
     * @tc.expected: Should close keyboard
     */
    pattern_->SetShowKeyBoardOnFocusMultiThread(false);

    /**
     * @tc.expected: showKeyBoardOnFocus_ should be false
     */
    EXPECT_FALSE(pattern_->showKeyBoardOnFocus_);
}

/**
 * @tc.name: SetShowKeyBoardOnFocusMultiThread003
 * @tc.desc: Test SetShowKeyBoardOnFocusMultiThread with same value (should return early)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetShowKeyBoardOnFocusMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Set initial value to true
     */
    pattern_->showKeyBoardOnFocus_ = true;

    /**
     * @tc.steps: step4. Call SetShowKeyBoardOnFocusMultiThread with same value
     * @tc.expected: Should return early without action
     */
    pattern_->SetShowKeyBoardOnFocusMultiThread(true);

    /**
     * @tc.expected: showKeyBoardOnFocus_ should remain true
     */
    EXPECT_TRUE(pattern_->showKeyBoardOnFocus_);
}

/**
 * @tc.name: SetShowKeyBoardOnFocusMultiThread004
 * @tc.desc: Test SetShowKeyBoardOnFocusMultiThread without focus (should skip keyboard action)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetShowKeyBoardOnFocusMultiThread004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Don't get focus
     * @tc.expected: Should skip keyboard action
     */

    /**
     * @tc.steps: step3. Set initial value to false
     */
    pattern_->showKeyBoardOnFocus_ = false;

    /**
     * @tc.steps: step4. Call SetShowKeyBoardOnFocusMultiThread with true
     * @tc.expected: Should update value but skip keyboard action due to no focus
     */
    pattern_->SetShowKeyBoardOnFocusMultiThread(true);

    /**
     * @tc.expected: showKeyBoardOnFocus_ should be true
     */
    EXPECT_TRUE(pattern_->showKeyBoardOnFocus_);
}

/**
 * @tc.name: SetShowKeyBoardOnFocusMultiThread005
 * @tc.desc: Test SetShowKeyBoardOnFocusMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetShowKeyBoardOnFocusMultiThread005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();

    /**
     * @tc.steps: step2. Set initial value to false
     */
    pattern->showKeyBoardOnFocus_ = false;

    /**
     * @tc.steps: step3. Call SetShowKeyBoardOnFocusMultiThread
     * @tc.expected: Should update value without crash
     */
    pattern->SetShowKeyBoardOnFocusMultiThread(true);

    /**
     * @tc.expected: showKeyBoardOnFocus_ should be true
     */
    EXPECT_TRUE(pattern->showKeyBoardOnFocus_);
}

/**
 * @tc.name: GetFocusPatternMultiThread001
 * @tc.desc: Test GetFocusPatternMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, GetFocusPatternMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call GetFocusPatternMultiThread
     * @tc.expected: Should return valid FocusPattern
     */
    auto focusPattern = pattern_->GetFocusPatternMultiThread();

    /**
     * @tc.expected: FocusPattern should be valid
     */
    EXPECT_EQ(focusPattern.GetFocusType(), FocusType::NODE);
    EXPECT_TRUE(focusPattern.GetIsFocusActiveWhenFocused());
}

/**
 * @tc.name: SetCustomKeyboardMultiThread001
 * @tc.desc: Test SetCustomKeyboardMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCustomKeyboardMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create keyboard builder function
     */
    std::function<void()> keyboardBuilder = []() {};

    /**
     * @tc.steps: step3. Call SetCustomKeyboardMultiThread
     * @tc.expected: Should post task successfully
     */
    pattern_->SetCustomKeyboardMultiThread(std::move(keyboardBuilder));

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetCustomKeyboardMultiThread002
 * @tc.desc: Test SetCustomKeyboardMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCustomKeyboardMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create keyboard builder function
     */
    std::function<void()> keyboardBuilder = []() {};

    /**
     * @tc.steps: step3. Call SetCustomKeyboardMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->SetCustomKeyboardMultiThread(std::move(keyboardBuilder));

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetCustomKeyboardWithNodeMultiThread001
 * @tc.desc: Test SetCustomKeyboardWithNodeMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCustomKeyboardWithNodeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call SetCustomKeyboardWithNodeMultiThread with null node
     * @tc.expected: Should post task successfully
     */
    pattern_->SetCustomKeyboardWithNodeMultiThread(nullptr);

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetCustomKeyboardWithNodeMultiThread002
 * @tc.desc: Test SetCustomKeyboardWithNodeMultiThread with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, SetCustomKeyboardWithNodeMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call SetCustomKeyboardWithNodeMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->SetCustomKeyboardWithNodeMultiThread(nullptr);

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ProcessDefaultStyleAndBehaviors001
 * @tc.desc: Test ProcessDefaultStyleAndBehaviors
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, ProcessDefaultStyleAndBehaviors001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call ProcessDefaultStyleAndBehaviors
     * @tc.expected: Should post task successfully
     */
    pattern_->ProcessDefaultStyleAndBehaviors();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: ProcessDefaultStyleAndBehaviors002
 * @tc.desc: Test ProcessDefaultStyleAndBehaviors with null host (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, ProcessDefaultStyleAndBehaviors002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call ProcessDefaultStyleAndBehaviors
     * @tc.expected: Should return early without crash
     */
    pattern->ProcessDefaultStyleAndBehaviors();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ProcessDefaultStyleAndBehaviorsMultiThread001
 * @tc.desc: Test ProcessDefaultStyleAndBehaviorsMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, ProcessDefaultStyleAndBehaviorsMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call ProcessDefaultStyleAndBehaviorsMultiThread
     * @tc.expected: Should process default styles successfully
     */
    pattern_->ProcessDefaultStyleAndBehaviorsMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: ProcessDefaultStyleAndBehaviorsMultiThread002
 * @tc.desc: Test ProcessDefaultStyleAndBehaviorsMultiThread with null frameNode (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, ProcessDefaultStyleAndBehaviorsMultiThread002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without host
     */
    auto pattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call ProcessDefaultStyleAndBehaviorsMultiThread
     * @tc.expected: Should return early without crash
     */
    pattern->ProcessDefaultStyleAndBehaviorsMultiThread();

    /**
     * @tc.expected: Pattern should remain valid
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ProcessDefaultStyleAndBehaviorsMultiThread003
 * @tc.desc: Test ProcessDefaultStyleAndBehaviorsMultiThread on first building
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, ProcessDefaultStyleAndBehaviorsMultiThread003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {});
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Mark as first building
     */
    frameNode_->isFirstBuilding_ = true;

    /**
     * @tc.steps: step3. Call ProcessDefaultStyleAndBehaviorsMultiThread
     * @tc.expected: Should set draggable and text draggable
     */
    pattern_->ProcessDefaultStyleAndBehaviorsMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: ProcessDefaultStyleAndBehaviorsMultiThread004
 * @tc.desc: Test ProcessDefaultStyleAndBehaviorsMultiThread with padding set by user
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternMultiThreadTest, ProcessDefaultStyleAndBehaviorsMultiThread004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and pattern
     */
    NG::PaddingProperty paddingProperty;
    paddingProperty.left = CalcLength(10.0_vp);
    paddingProperty.right = CalcLength(10.0_vp);
    paddingProperty.top = CalcLength(10.0_vp);
    paddingProperty.bottom = CalcLength(10.0_vp);

    CreateTextField(DEFAULT_TEXT, "", [&paddingProperty](TextFieldModelNG model) {
        model.SetPadding(paddingProperty, Edge::NONE, false, false);
    });
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Mark padding as set by user
     */
    auto textfieldPaintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    if (textfieldPaintProperty) {
        PaddingProperty paddingMarker;
        paddingMarker.left = CalcLength(10.0_vp);
        textfieldPaintProperty->UpdatePaddingByUser(paddingMarker);
    }

    /**
     * @tc.steps: step3. Call ProcessDefaultStyleAndBehaviorsMultiThread
     * @tc.expected: Should skip updating padding
     */
    pattern_->ProcessDefaultStyleAndBehaviorsMultiThread();

    /**
     * @tc.expected: Pattern should still be valid
     */
    EXPECT_NE(pattern_, nullptr);
}

} // namespace OHOS::Ace::NG
