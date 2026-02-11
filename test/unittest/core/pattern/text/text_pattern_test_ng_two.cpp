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

#include "text_base.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/render/mock_paragraph.h"

namespace OHOS::Ace::NG {

// Test constants
constexpr int32_t TEST_PLACEHOLDER_COUNT = 5;
constexpr const char16_t* TEST_TEXT_CONTENT = u"TestContent";

/**
 * @tc.name: CombinedStateTest001
 * @tc.desc: Test combination of multiple state flags
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CombinedStateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set multiple flags
     */
    textPattern->status_ = Status::DRAGGING;
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(true);
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Verify all flags are set correctly
     * @tc.expected: step3. All flags are true
     */
    EXPECT_TRUE(textPattern->IsDragging());
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step4. Reset all flags
     */
    textPattern->status_ = Status::NONE;
    textPattern->SetIsMeasureBoundary(false);
    textPattern->SetIsCustomFont(false);
    textPattern->ResetContChange();

    /**
     * @tc.steps: step5. Verify all flags are reset
     * @tc.expected: step5. All flags are false
     */
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
    EXPECT_FALSE(textPattern->GetIsCustomFont());
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: CombinedStateTest002
 * @tc.desc: Test combination of dragging state with other flags
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CombinedStateTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set dragging state with all other flags true
     */
    textPattern->status_ = Status::DRAGGING;
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(true);
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Verify dragging is true, all others true
     * @tc.expected: step3. All flags are true
     */
    EXPECT_TRUE(textPattern->IsDragging());
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step4. Change to non-dragging state
     */
    textPattern->status_ = Status::FLOATING;

    /**
     * @tc.steps: step5. Verify dragging is false, but other flags remain true
     * @tc.expected: step5. Dragging is false, other flags are true
     */
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_TRUE(textPattern->GetContChange());
}

/**
 * @tc.name: CombinedStateTest003
 * @tc.desc: Test all flags in false state
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CombinedStateTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Ensure all flags are in default false state
     */
    textPattern->status_ = Status::NONE;
    textPattern->SetIsMeasureBoundary(false);
    textPattern->SetIsCustomFont(false);
    textPattern->ResetContChange();

    /**
     * @tc.steps: step3. Verify all flags are false
     * @tc.expected: step3. All flags are false
     */
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
    EXPECT_FALSE(textPattern->GetIsCustomFont());
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: CombinedStateTest004
 * @tc.desc: Test combination of status and flags in different configurations
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CombinedStateTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Test configuration 1: DRAGGING + all flags true
     * @tc.expected: step2. All flags are true
     */
    textPattern->status_ = Status::DRAGGING;
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(true);
    textPattern->MarkContentChange();
    EXPECT_TRUE(textPattern->IsDragging());
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step3. Test configuration 2: FLOATING + mixed flags
     * @tc.expected: step3. Dragging is false, measure boundary is false, custom font is true, contChange is false
     */
    textPattern->status_ = Status::FLOATING;
    textPattern->SetIsMeasureBoundary(false);
    textPattern->SetIsCustomFont(true);
    textPattern->ResetContChange();
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_FALSE(textPattern->GetContChange());

    /**
     * @tc.steps: step4. Test configuration 3: ON_DROP + all flags false
     * @tc.expected: step4. All flags are false
     */
    textPattern->status_ = Status::ON_DROP;
    textPattern->SetIsMeasureBoundary(false);
    textPattern->SetIsCustomFont(false);
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
    EXPECT_FALSE(textPattern->GetIsCustomFont());
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: CombinedStateTest005
 * @tc.desc: Test state consistency after multiple operations
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CombinedStateTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set initial state
     */
    textPattern->status_ = Status::DRAGGING;
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(true);
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Perform state transitions
     */
    for (int i = 0; i < 50; i++) {
        /**
         * @tc.steps: step3.1 Toggle flags
         */
        textPattern->SetIsMeasureBoundary(i % 2 == 0);
        textPattern->SetIsCustomFont(i % 3 == 0);

        /**
         * @tc.steps: step3.2 Toggle content change
         */
        if (i % 2 == 0) {
            textPattern->MarkContentChange();
        } else {
            textPattern->ResetContChange();
        }

        /**
         * @tc.steps: step3.3 Verify state consistency
         * @tc.expected: step3.3 State is consistent with toggle pattern
         */
        if (i % 2 == 0) {
            EXPECT_TRUE(textPattern->IsMeasureBoundary());
            EXPECT_TRUE(textPattern->GetContChange());
        } else {
            EXPECT_FALSE(textPattern->IsMeasureBoundary());
            EXPECT_FALSE(textPattern->GetContChange());
        }
    }

    /**
     * @tc.steps: step4. Verify dragging state remains
     * @tc.expected: step4. Dragging is true
     */
    EXPECT_TRUE(textPattern->IsDragging());
}

/**
 * @tc.name: CombinedStateTest006
 * @tc.desc: Test all state flags in extreme configurations
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CombinedStateTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Configuration 1: All true
     * @tc.expected: step2. All flags are true
     */
    textPattern->status_ = Status::DRAGGING;
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(true);
    textPattern->MarkContentChange();
    EXPECT_TRUE(textPattern->IsDragging());
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step3. Configuration 2: All false
     * @tc.expected: step3. All flags are false
     */
    textPattern->status_ = Status::NONE;
    textPattern->SetIsMeasureBoundary(false);
    textPattern->SetIsCustomFont(false);
    textPattern->ResetContChange();
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
    EXPECT_FALSE(textPattern->GetIsCustomFont());
    EXPECT_FALSE(textPattern->GetContChange());

    /**
     * @tc.steps: step4. Configuration 3: Alternating pattern
     * @tc.expected: step4. Dragging is false, measure boundary is true, custom font is false, contChange is true
     */
    textPattern->status_ = Status::FLOATING;
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(false);
    textPattern->MarkContentChange();
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
    EXPECT_FALSE(textPattern->GetIsCustomFont());
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step5. Configuration 4: Reverse alternating pattern
     * @tc.expected: step5. Dragging is false, measure boundary is false, custom font is true, contChange is false
     */
    textPattern->status_ = Status::ON_DROP;
    textPattern->SetIsMeasureBoundary(false);
    textPattern->SetIsCustomFont(true);
    textPattern->ResetContChange();
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: ContentChangeFlag001
 * @tc.desc: Test content change flag state machine
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentChangeFlag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initial state: flag is false
     * @tc.expected: step2. contChange is false
     */
    EXPECT_FALSE(textPattern->GetContChange());

    /**
     * @tc.steps: step3. Mark as changed
     * @tc.expected: step3. contChange is true
     */
    textPattern->MarkContentChange();
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step4. Reset flag
     * @tc.expected: step4. contChange is false
     */
    textPattern->ResetContChange();
    EXPECT_FALSE(textPattern->GetContChange());

    /**
     * @tc.steps: step5. Mark as changed again
     * @tc.expected: step5. contChange is true
     */
    textPattern->MarkContentChange();
    EXPECT_TRUE(textPattern->GetContChange());
}

/**
 * @tc.name: ContentChangeFlag002
 * @tc.desc: Test multiple MarkContentChange calls
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentChangeFlag002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Mark as changed multiple times
     */
    textPattern->MarkContentChange();
    textPattern->MarkContentChange();
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Verify flag is still true
     * @tc.expected: step3. contChange is true
     */
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step4. Reset should set to false
     * @tc.expected: step4. contChange is false
     */
    textPattern->ResetContChange();
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: ContentChangeFlag003
 * @tc.desc: Test ResetContChange multiple times
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentChangeFlag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Mark as changed
     * @tc.expected: step2. contChange is true
     */
    textPattern->MarkContentChange();
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step3. Reset multiple times
     */
    textPattern->ResetContChange();
    textPattern->ResetContChange();
    textPattern->ResetContChange();

    /**
     * @tc.steps: step4. Verify flag remains false
     * @tc.expected: step4. contChange is false
     */
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: ContentChangeFlag004
 * @tc.desc: Test content change flag with rapid mark and reset
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentChangeFlag004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Rapid mark and reset cycles
     * @tc.expected: step2. Flag toggles correctly each cycle
     */
    for (int i = 0; i < 100; i++) {
        textPattern->MarkContentChange();
        EXPECT_TRUE(textPattern->GetContChange());
        textPattern->ResetContChange();
        EXPECT_FALSE(textPattern->GetContChange());
    }
}

/**
 * @tc.name: ContentModifierLifecycle001
 * @tc.desc: Test content modifier creation and lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentModifierLifecycle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Setup frame node
     * @tc.expected: step2. frameNode is created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;

    /**
     * @tc.steps: step3. Content modifier is null initially
     * @tc.expected: step3. Content modifier is nullptr
     */
    EXPECT_EQ(textPattern->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step4. Create modifier
     * @tc.expected: step4. Content modifier is not nullptr
     */
    textPattern->CreateModifier();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step5. Create modifier again - should reuse existing
     * @tc.expected: step5. Same modifier instance is returned
     */
    auto firstMod = textPattern->GetContentModifier();
    textPattern->CreateModifier();
    auto secondMod = textPattern->GetContentModifier();
    EXPECT_EQ(firstMod, secondMod);
}

/**
 * @tc.name: ContentModifierLifecycle002
 * @tc.desc: Test content modifier with frame node lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentModifierLifecycle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create frame node
     * @tc.expected: step2. frameNode is created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;

    /**
     * @tc.steps: step3. Create modifier
     * @tc.expected: step3. Content modifier is not nullptr
     */
    textPattern->CreateModifier();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step4. Clear frame node reference
     */
    textPattern->frameNode_.Reset();

    /**
     * @tc.steps: step5. Content modifier should still exist
     * @tc.expected: step5. Content modifier is not nullptr
     */
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: ContentModifierLifecycle003
 * @tc.desc: Test OnWindowHide and OnWindowShow sequence
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentModifierLifecycle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Setup frame node and content modifier
     * @tc.expected: step2. frameNode and content modifier are created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    textPattern->CreateModifier();

    /**
     * @tc.steps: step3. Call OnWindowHide
     * @tc.expected: step3. Content modifier exists after OnWindowHide
     */
    textPattern->OnWindowHide();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step4. Call OnWindowShow
     * @tc.expected: step4. Content modifier exists after OnWindowShow
     */
    textPattern->OnWindowShow();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step5. Call OnWindowHide again
     * @tc.expected: step5. Content modifier exists after OnWindowHide
     */
    textPattern->OnWindowHide();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: ContentModifierLifecycle004
 * @tc.desc: Test content modifier persistence across operations
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ContentModifierLifecycle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Setup frame node
     * @tc.expected: step2. frameNode is created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;

    /**
     * @tc.steps: step3. Create modifier
     * @tc.expected: step3. Modifier is created successfully
     */
    textPattern->CreateModifier();
    auto firstMod = textPattern->GetContentModifier();
    ASSERT_NE(firstMod, nullptr);

    /**
     * @tc.steps: step4. Perform various operations
     */
    textPattern->OnWindowHide();
    textPattern->OnWindowShow();
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(true);
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step5. Verify modifier still exists and is same instance
     * @tc.expected: step5. Same modifier instance is returned
     */
    auto secondMod = textPattern->GetContentModifier();
    EXPECT_EQ(firstMod, secondMod);
}

/**
 * @tc.name: CustomFontFlag001
 * @tc.desc: Test custom font flag state transitions
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CustomFontFlag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initial state: flag is false
     * @tc.expected: step2. isCustomFont is false
     */
    EXPECT_FALSE(textPattern->GetIsCustomFont());

    /**
     * @tc.steps: step3. Set to true
     * @tc.expected: step3. isCustomFont is true
     */
    textPattern->SetIsCustomFont(true);
    EXPECT_TRUE(textPattern->GetIsCustomFont());

    /**
     * @tc.steps: step4. Set back to false
     * @tc.expected: step4. isCustomFont is false
     */
    textPattern->SetIsCustomFont(false);
    EXPECT_FALSE(textPattern->GetIsCustomFont());
}

/**
 * @tc.name: CustomFontFlag002
 * @tc.desc: Test SetIsCustomFont with same value multiple times
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CustomFontFlag002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set to true multiple times
     * @tc.expected: step2. isCustomFont is true
     */
    textPattern->SetIsCustomFont(true);
    EXPECT_TRUE(textPattern->GetIsCustomFont());

    textPattern->SetIsCustomFont(true);
    EXPECT_TRUE(textPattern->GetIsCustomFont());

    /**
     * @tc.steps: step3. Set to false multiple times
     * @tc.expected: step3. isCustomFont is false
     */
    textPattern->SetIsCustomFont(false);
    EXPECT_FALSE(textPattern->GetIsCustomFont());

    textPattern->SetIsCustomFont(false);
    EXPECT_FALSE(textPattern->GetIsCustomFont());
}

/**
 * @tc.name: CustomFontFlag003
 * @tc.desc: Test GetIsCustomFont returns correct value after multiple sets
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CustomFontFlag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Toggle custom font flag multiple times
     * @tc.expected: step2. isCustomFont toggles correctly
     */
    for (int i = 0; i < 10; i++) {
        textPattern->SetIsCustomFont(i % 2 == 0);
        EXPECT_EQ(textPattern->GetIsCustomFont(), i % 2 == 0);
    }
}

/**
 * @tc.name: EmptyTextForDisplay001
 * @tc.desc: Test GetTextForDisplay with various empty states
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, EmptyTextForDisplay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Test with default constructed string
     * @tc.expected: step2. textForDisplay is empty
     */
    EXPECT_TRUE(textPattern->GetTextForDisplay().empty());

    /**
     * @tc.steps: step3. Set to empty string explicitly
     * @tc.expected: step3. textForDisplay is empty
     */
    textPattern->textForDisplay_ = u"";
    EXPECT_TRUE(textPattern->GetTextForDisplay().empty());

    /**
     * @tc.steps: step4. Set to non-empty string
     * @tc.expected: step4. textForDisplay is "NonEmpty"
     */
    textPattern->textForDisplay_ = u"NonEmpty";
    EXPECT_FALSE(textPattern->GetTextForDisplay().empty());
    EXPECT_EQ(textPattern->GetTextForDisplay(), u"NonEmpty");
}

/**
 * @tc.name: EmptyTextForDisplay002
 * @tc.desc: Test GetTextForDisplay with whitespace
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, EmptyTextForDisplay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Test with whitespace only
     * @tc.expected: step2. textForDisplay is not empty
     */
    textPattern->textForDisplay_ = u"   ";
    EXPECT_FALSE(textPattern->GetTextForDisplay().empty());

    /**
     * @tc.steps: step3. Test with tabs
     * @tc.expected: step3. textForDisplay is not empty
     */
    textPattern->textForDisplay_ = u"\t\t";
    EXPECT_FALSE(textPattern->GetTextForDisplay().empty());

    /**
     * @tc.steps: step4. Test with newlines
     * @tc.expected: step4. textForDisplay is not empty
     */
    textPattern->textForDisplay_ = u"\n\n";
    EXPECT_FALSE(textPattern->GetTextForDisplay().empty());
}

/**
 * @tc.name: GetContChange001
 * @tc.desc: Test GetContChange returns true after MarkContentChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetContChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Mark content as changed
     */
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Verify GetContChange returns true
     * @tc.expected: step3. contChange is true
     */
    EXPECT_TRUE(textPattern->GetContChange());
}

/**
 * @tc.name: GetContChange002
 * @tc.desc: Test GetContChange returns false after ResetContChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetContChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Mark content as changed
     */
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Reset content change flag
     */
    textPattern->ResetContChange();

    /**
     * @tc.steps: step4. Verify GetContChange returns false
     * @tc.expected: step4. contChange is false
     */
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: GetContChange003
 * @tc.desc: Test GetContChange initial default value
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetContChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Verify initial default value is false
     * @tc.expected: step2. contChange is false
     */
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: GetContChange004
 * @tc.desc: Test GetContChange consistency across multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetContChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Mark as changed
     */
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Call GetContChange multiple times without reset
     * @tc.expected: step3. contChange is always true
     */
    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(textPattern->GetContChange());
    }

    /**
     * @tc.steps: step4. Reset once
     */
    textPattern->ResetContChange();

    /**
     * @tc.steps: step5. Call GetContChange multiple times after reset
     * @tc.expected: step5. contChange is always false
     */
    for (int i = 0; i < 100; i++) {
        EXPECT_FALSE(textPattern->GetContChange());
    }
}

/**
 * @tc.name: GetContentModifier001
 * @tc.desc: Test GetContentModifier after CreateModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Setup frame node
     * @tc.expected: step2. frameNode is created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;

    /**
     * @tc.steps: step3. Create modifier
     */
    textPattern->CreateModifier();

    /**
     * @tc.steps: step4. Verify content modifier is created
     * @tc.expected: step4. Content modifier is not nullptr
     */
    auto contentMod = textPattern->GetContentModifier();
    EXPECT_NE(contentMod, nullptr);
}

/**
 * @tc.name: GetContentModifier002
 * @tc.desc: Test GetContentModifier before CreateModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetContentModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Get content modifier before creating - should be null
     * @tc.expected: step2. Content modifier is nullptr
     */
    auto contentMod = textPattern->GetContentModifier();
    EXPECT_EQ(contentMod, nullptr);
}

/**
 * @tc.name: GetIsCustomFont001
 * @tc.desc: Test GetIsCustomFont returns initial default value
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetIsCustomFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Verify initial default value is false
     * @tc.expected: step2. isCustomFont is false
     */
    EXPECT_FALSE(textPattern->GetIsCustomFont());
}

/**
 * @tc.name: GetOrCreateMagnifier001
 * @tc.desc: Test GetOrCreateMagnifier creates new magnifier
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOrCreateMagnifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create magnifier for the first time
     */
    auto magnifier = textPattern->GetOrCreateMagnifier();

    /**
     * @tc.steps: step3. Verify magnifier is created
     * @tc.expected: step3. Magnifier is not nullptr
     */
    EXPECT_NE(magnifier, nullptr);
}

/**
 * @tc.name: GetOrCreateMagnifier002
 * @tc.desc: Test GetOrCreateMagnifier reuses existing magnifier
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOrCreateMagnifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create magnifier first time
     * @tc.expected: step2. First magnifier is created successfully
     */
    auto firstMagnifier = textPattern->GetOrCreateMagnifier();
    ASSERT_NE(firstMagnifier, nullptr);

    /**
     * @tc.steps: step3. Create magnifier second time - should return same instance
     * @tc.expected: step3. Same magnifier instance is returned
     */
    auto secondMagnifier = textPattern->GetOrCreateMagnifier();
    EXPECT_EQ(firstMagnifier, secondMagnifier);
}

/**
 * @tc.name: GetOrCreateMagnifier003
 * @tc.desc: Test GetOrCreateMagnifier with multiple TextPattern instances
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOrCreateMagnifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create multiple TextPattern instances
     * @tc.expected: step1. Both TextPattern instances are created successfully
     */
    auto textPattern1 = AceType::MakeRefPtr<TextPattern>();
    auto textPattern2 = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern1, nullptr);
    ASSERT_NE(textPattern2, nullptr);

    /**
     * @tc.steps: step2. Create magnifiers for both
     */
    auto magnifier1 = textPattern1->GetOrCreateMagnifier();
    auto magnifier2 = textPattern2->GetOrCreateMagnifier();

    /**
     * @tc.steps: step3. Verify both magnifiers are created and different
     * @tc.expected: step3. Both magnifiers are not nullptr and are different instances
     */
    EXPECT_NE(magnifier1, nullptr);
    EXPECT_NE(magnifier2, nullptr);
    EXPECT_NE(magnifier1, magnifier2);
}

/**
 * @tc.name: GetOrCreateMagnifier004
 * @tc.desc: Test GetOrCreateMagnifier after frame node creation
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOrCreateMagnifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create frame node
     * @tc.expected: step2. frameNode is created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;

    /**
     * @tc.steps: step3. Create magnifier after frame node
     * @tc.expected: step3. Magnifier is not nullptr
     */
    auto magnifier = textPattern->GetOrCreateMagnifier();
    EXPECT_NE(magnifier, nullptr);

    /**
     * @tc.steps: step4. Create modifier after magnifier
     * @tc.expected: step4. Content modifier is not nullptr
     */
    textPattern->CreateModifier();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step5. Both should coexist
     * @tc.expected: step5. Both magnifier and content modifier are not nullptr
     */
    EXPECT_NE(magnifier, nullptr);
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: GetTextContentLength003
 * @tc.desc: Test GetTextContentLength with empty spans
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextContentLength003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set text content but keep spans empty
     */
    textPattern->textForDisplay_ = std::u16string(TEST_TEXT_CONTENT);
    textPattern->placeholderCount_ = TEST_PLACEHOLDER_COUNT;

    /**
     * @tc.steps: step3. Verify returns 0 when spans_ is empty
     * @tc.expected: step3. Text content length is 0
     */
    auto result = textPattern->GetTextContentLength();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: GetTextContentLength006
 * @tc.desc: Test GetTextContentLength with large placeholder count
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextContentLength006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Add span
     * @tc.expected: step2. Span is created successfully
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    textPattern->spans_.emplace_back(spanItem);

    /**
     * @tc.steps: step3. Test with large placeholder count
     * @tc.expected: step3. Text content length is 1005
     */
    textPattern->textForDisplay_ = u"Large";
    textPattern->placeholderCount_ = 1000;
    EXPECT_EQ(textPattern->GetTextContentLength(), 1005);
}

/**
 * @tc.name: GetTextContentLength007
 * @tc.desc: Test GetTextContentLength with Unicode text
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextContentLength007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Add span
     * @tc.expected: step2. Span is created successfully
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    textPattern->spans_.emplace_back(spanItem);

    /**
     * @tc.steps: step3. Test with Unicode emoji
     * @tc.expected: step3. Text content length is 12
     */
    textPattern->textForDisplay_ = u"Hello🌍World";
    textPattern->placeholderCount_ = 0;
    EXPECT_EQ(textPattern->GetTextContentLength(), 12);
}

/**
 * @tc.name: GetTextContentLength008
 * @tc.desc: Test GetTextContentLength with mixed language text
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextContentLength008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Add span
     * @tc.expected: step2. Span is created successfully
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    textPattern->spans_.emplace_back(spanItem);

    /**
     * @tc.steps: step3. Test with mixed CJK and Latin
     * @tc.expected: step3. Text content length is 14 (Each CJK character counts as 1, Latin characters count as 1)
     */
    textPattern->textForDisplay_ = u"Hello你好World世界";
    textPattern->placeholderCount_ = 0;
    EXPECT_EQ(textPattern->GetTextContentLength(), 14);
}

/**
 * @tc.name: GetTextForDisplay001
 * @tc.desc: Test GetTextForDisplay returns correct text
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextForDisplay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set display text
     */
    std::u16string testText = u"DisplayText";
    textPattern->textForDisplay_ = testText;

    /**
     * @tc.steps: step3. Verify returned text matches
     * @tc.expected: step3. Returned text matches testText
     */
    auto result = textPattern->GetTextForDisplay();
    EXPECT_EQ(result, testText);
}

/**
 * @tc.name: GetTextForDisplay002
 * @tc.desc: Test GetTextForDisplay with empty text
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextForDisplay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Keep text empty
     */
    textPattern->textForDisplay_.clear();

    /**
     * @tc.steps: step3. Verify returns empty string
     * @tc.expected: step3. Returned text is empty
     */
    auto result = textPattern->GetTextForDisplay();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetTextForDisplay003
 * @tc.desc: Test GetTextForDisplay with special characters
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextForDisplay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set text with special characters
     */
    std::u16string testText = u"Special@#$%^&*()Characters";
    textPattern->textForDisplay_ = testText;

    /**
     * @tc.steps: step3. Verify returned text matches
     * @tc.expected: step3. Returned text matches testText
     */
    auto result = textPattern->GetTextForDisplay();
    EXPECT_EQ(result, testText);
}

/**
 * @tc.name: GetTextForDisplay004
 * @tc.desc: Test GetTextForDisplay with very long text
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextForDisplay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set very long text
     */
    std::u16string longText(10000, u'A');
    textPattern->textForDisplay_ = longText;

    /**
     * @tc.steps: step3. Verify returned text matches
     * @tc.expected: step3. Returned text length is 10000 and matches longText
     */
    auto result = textPattern->GetTextForDisplay();
    EXPECT_EQ(result.length(), 10000);
    EXPECT_EQ(result, longText);
}

/**
 * @tc.name: GetTextForDisplay005
 * @tc.desc: Test GetTextForDisplay returns reference to internal string
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextForDisplay005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set text content
     */
    std::u16string testText = u"ReferenceTest";
    textPattern->textForDisplay_ = testText;

    /**
     * @tc.steps: step3. Get reference multiple times
     */
    auto& ref1 = textPattern->GetTextForDisplay();
    auto& ref2 = textPattern->GetTextForDisplay();

    /**
     * @tc.steps: step4. Verify both references point to same string
     * @tc.expected: step4. Both references point to same address and equal to testText
     */
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1, testText);
}

/**
 * @tc.name: GetTextForDisplay006
 * @tc.desc: Test GetTextForDisplay with multilingual text
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextForDisplay006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Test with Chinese characters
     * @tc.expected: step2. Returned text is "你好世界"
     */
    textPattern->textForDisplay_ = u"你好世界";
    EXPECT_EQ(textPattern->GetTextForDisplay(), u"你好世界");

    /**
     * @tc.steps: step3. Test with Japanese characters
     * @tc.expected: step3. Returned text is "こんにちは"
     */
    textPattern->textForDisplay_ = u"こんにちは";
    EXPECT_EQ(textPattern->GetTextForDisplay(), u"こんにちは");

    /**
     * @tc.steps: step4. Test with Korean characters
     * @tc.expected: step4. Returned text is "안녕하세요"
     */
    textPattern->textForDisplay_ = u"안녕하세요";
    EXPECT_EQ(textPattern->GetTextForDisplay(), u"안녕하세요");

    /**
     * @tc.steps: step5. Test with mixed scripts
     * @tc.expected: step5. Returned text is "Hello你好世界"
     */
    textPattern->textForDisplay_ = u"Hello你好世界";
    EXPECT_EQ(textPattern->GetTextForDisplay(), u"Hello你好世界");
}

/**
 * @tc.name: IsDragging001
 * @tc.desc: Test IsDragging returns true when status_ is DRAGGING
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsDragging001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and set status to DRAGGING
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->status_ = Status::DRAGGING;

    /**
     * @tc.steps: step2. Call IsDragging
     * @tc.expected: step2. IsDragging returns true when status is DRAGGING
     */
    EXPECT_TRUE(textPattern->IsDragging());
}

/**
 * @tc.name: IsDragging002
 * @tc.desc: Test IsDragging returns false when status_ is NONE
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsDragging002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and set status to NONE
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->status_ = Status::NONE;

    /**
     * @tc.steps: step2. Call IsDragging
     * @tc.expected: step2. IsDragging returns false when status is NONE
     */
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: IsDragging003
 * @tc.desc: Test IsDragging returns false when status_ is FLOATING
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsDragging003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and set status to FLOATING
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->status_ = Status::FLOATING;

    /**
     * @tc.steps: step2. Call IsDragging
     * @tc.expected: step2. IsDragging returns false when status is FLOATING
     */
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: IsDragging004
 * @tc.desc: Test IsDragging returns false when status_ is ON_DROP
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsDragging004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and set status to ON_DROP
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->status_ = Status::ON_DROP;

    /**
     * @tc.steps: step2. Call IsDragging
     * @tc.expected: step2. IsDragging returns false when status is ON_DROP
     */
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: IsDragging005
 * @tc.desc: Test IsDragging with all status values
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsDragging005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Test all status values
     * @tc.expected: step2. IsDragging returns correct value for each status
     */
    textPattern->status_ = Status::NONE;
    EXPECT_FALSE(textPattern->IsDragging());

    textPattern->status_ = Status::DRAGGING;
    EXPECT_TRUE(textPattern->IsDragging());

    textPattern->status_ = Status::FLOATING;
    EXPECT_FALSE(textPattern->IsDragging());

    textPattern->status_ = Status::ON_DROP;
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: IsDragging006
 * @tc.desc: Test IsDragging behavior across entire state machine
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsDragging006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create a table of all status values and expected IsDragging result
     */
    struct StatusTest {
        Status status;
        bool expectedDragging;
    };

    std::vector<StatusTest> testCases = {
        {Status::NONE, false},
        {Status::DRAGGING, true},
        {Status::FLOATING, false},
        {Status::ON_DROP, false},
    };

    /**
     * @tc.steps: step3. Test each case
     * @tc.expected: step3. IsDragging returns expected value for each status
     */
    for (const auto& testCase : testCases) {
        textPattern->status_ = testCase.status;
        EXPECT_EQ(textPattern->IsDragging(), testCase.expectedDragging);
    }
}

/**
 * @tc.name: IsMeasureBoundary001
 * @tc.desc: Test IsMeasureBoundary returns initial default value
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsMeasureBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Verify initial default value is false
     * @tc.expected: step2. isMeasureBoundary is false
     */
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
}

/**
 * @tc.name: MarkContentChange001
 * @tc.desc: Test MarkContentChange sets contChange_ to true
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, MarkContentChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Reset content change flag first
     */
    textPattern->ResetContChange();

    /**
     * @tc.steps: step3. Mark content as changed
     */
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step4. Verify content change flag is true
     * @tc.expected: step4. contChange is true
     */
    EXPECT_TRUE(textPattern->GetContChange());
}

/**
 * @tc.name: MarkContentChange002
 * @tc.desc: Test MarkContentChange doesn't affect other flags
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, MarkContentChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set some flags
     */
    textPattern->status_ = Status::FLOATING;
    textPattern->SetIsMeasureBoundary(false);
    textPattern->SetIsCustomFont(false);
    textPattern->ResetContChange();

    /**
     * @tc.steps: step3. Mark content change
     */
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step4. Verify other flags are not affected
     * @tc.expected: step4. Only contChange is true, other flags remain false
     */
    EXPECT_FALSE(textPattern->IsDragging());
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
    EXPECT_FALSE(textPattern->GetIsCustomFont());
    EXPECT_TRUE(textPattern->GetContChange());
}

/**
 * @tc.name: MeasureBoundaryFlag001
 * @tc.desc: Test measure boundary flag state transitions
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, MeasureBoundaryFlag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initial state: flag is false
     * @tc.expected: step2. isMeasureBoundary is false
     */
    EXPECT_FALSE(textPattern->IsMeasureBoundary());

    /**
     * @tc.steps: step3. Set to true
     * @tc.expected: step3. isMeasureBoundary is true
     */
    textPattern->SetIsMeasureBoundary(true);
    EXPECT_TRUE(textPattern->IsMeasureBoundary());

    /**
     * @tc.steps: step4. Set back to false
     * @tc.expected: step4. isMeasureBoundary is false
     */
    textPattern->SetIsMeasureBoundary(false);
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
}

/**
 * @tc.name: MeasureBoundaryFlag002
 * @tc.desc: Test SetIsMeasureBoundary with same value multiple times
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, MeasureBoundaryFlag002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set to true multiple times
     * @tc.expected: step2. isMeasureBoundary is true
     */
    textPattern->SetIsMeasureBoundary(true);
    EXPECT_TRUE(textPattern->IsMeasureBoundary());

    textPattern->SetIsMeasureBoundary(true);
    EXPECT_TRUE(textPattern->IsMeasureBoundary());

    /**
     * @tc.steps: step3. Set to false multiple times
     * @tc.expected: step3. isMeasureBoundary is false
     */
    textPattern->SetIsMeasureBoundary(false);
    EXPECT_FALSE(textPattern->IsMeasureBoundary());

    textPattern->SetIsMeasureBoundary(false);
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
}

/**
 * @tc.name: MeasureBoundaryFlag003
 * @tc.desc: Test IsMeasureBoundary returns correct value after multiple sets
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, MeasureBoundaryFlag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Toggle measure boundary flag multiple times
     * @tc.expected: step2. isMeasureBoundary toggles correctly
     */
    for (int i = 0; i < 10; i++) {
        textPattern->SetIsMeasureBoundary(i % 2 == 0);
        EXPECT_EQ(textPattern->IsMeasureBoundary(), i % 2 == 0);
    }
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test OnWindowHide with magnifierController_
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnWindowHide001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and initialize with magnifier and content modifier
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->GetOrCreateMagnifier();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    textPattern->CreateModifier();

    /**
     * @tc.steps: step2. Call OnWindowHide
     * @tc.expected: step2. Content modifier exists after OnWindowHide
     */
    textPattern->OnWindowHide();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: OnWindowHide002
 * @tc.desc: Test OnWindowHide without magnifierController_
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnWindowHide002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern with content modifier only (no magnifier)
     * @tc.expected: step1. TextPattern and content modifier are created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    textPattern->CreateModifier();

    /**
     * @tc.steps: step2. Call OnWindowHide without magnifier
     * @tc.expected: step2. No crash occurs and content modifier exists
     */
    textPattern->OnWindowHide();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: OnWindowHide003
 * @tc.desc: Test OnWindowHide with content modifier and magnifier
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnWindowHide003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Setup frame node, content modifier, and magnifier
     * @tc.expected: step2. All components are created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    textPattern->CreateModifier();
    textPattern->GetOrCreateMagnifier();

    /**
     * @tc.steps: step3. Verify all components exist
     * @tc.expected: step3. Content modifier is not nullptr
     */
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    /**
     * @tc.steps: step4. Call OnWindowHide multiple times
     * @tc.expected: step4. Content modifier exists after each call
     */
    textPattern->OnWindowHide();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    textPattern->OnWindowHide();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: OnWindowShow001
 * @tc.desc: Test OnWindowShow resumes content animation
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnWindowShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern with frame node and content modifier
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    textPattern->CreateModifier();

    /**
     * @tc.steps: step2. Call OnWindowShow
     * @tc.expected: step2. Content modifier exists after OnWindowShow
     */
    textPattern->OnWindowShow();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: OnWindowShow002
 * @tc.desc: Test OnWindowShow without content modifier
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnWindowShow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern with frame node only (no content modifier)
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;

    /**
     * @tc.steps: step2. Call OnWindowShow without content modifier
     * @tc.expected: step2. No crash occurs
     */
    textPattern->OnWindowShow();
}

/**
 * @tc.name: OnWindowShow003
 * @tc.desc: Test OnWindowShow with content modifier
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnWindowShow003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Setup frame node and content modifier
     * @tc.expected: step2. frameNode and content modifier are created successfully
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, textPattern);
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    textPattern->CreateModifier();

    /**
     * @tc.steps: step3. Call OnWindowShow multiple times
     * @tc.expected: step3. Content modifier exists after each call
     */
    textPattern->OnWindowShow();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    textPattern->OnWindowShow();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);

    textPattern->OnWindowShow();
    EXPECT_NE(textPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: ResetContChange001
 * @tc.desc: Test ResetContChange sets contChange_ to false
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ResetContChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Mark content as changed
     * @tc.expected: step2. contChange is true
     */
    textPattern->MarkContentChange();
    EXPECT_TRUE(textPattern->GetContChange());

    /**
     * @tc.steps: step3. Reset content change flag
     */
    textPattern->ResetContChange();

    /**
     * @tc.steps: step4. Verify flag is reset to false
     * @tc.expected: step4. contChange is false
     */
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: ResetContChange002
 * @tc.desc: Test ResetContChange when flag is already false
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ResetContChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Verify flag is false initially
     * @tc.expected: step2. contChange is false
     */
    EXPECT_FALSE(textPattern->GetContChange());

    /**
     * @tc.steps: step3. Reset content change flag when already false
     */
    textPattern->ResetContChange();

    /**
     * @tc.steps: step4. Verify flag remains false
     * @tc.expected: step4. contChange is false
     */
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: ResetContChange003
 * @tc.desc: Test ResetContChange doesn't affect other flags
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ResetContChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set all flags
     */
    textPattern->status_ = Status::DRAGGING;
    textPattern->SetIsMeasureBoundary(true);
    textPattern->SetIsCustomFont(true);
    textPattern->MarkContentChange();

    /**
     * @tc.steps: step3. Reset only content change
     */
    textPattern->ResetContChange();

    /**
     * @tc.steps: step4. Verify other flags are not affected
     * @tc.expected: step4. Only contChange is false, other flags remain true
     */
    EXPECT_TRUE(textPattern->IsDragging());
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
    EXPECT_TRUE(textPattern->GetIsCustomFont());
    EXPECT_FALSE(textPattern->GetContChange());
}

/**
 * @tc.name: SetIsCustomFont001
 * @tc.desc: Test SetIsCustomFont with true value
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, SetIsCustomFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set custom font to true
     */
    textPattern->SetIsCustomFont(true);

    /**
     * @tc.steps: step3. Verify value is set correctly
     * @tc.expected: step3. isCustomFont is true
     */
    EXPECT_TRUE(textPattern->GetIsCustomFont());
}

/**
 * @tc.name: SetIsCustomFont002
 * @tc.desc: Test SetIsCustomFont with false value
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, SetIsCustomFont002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set custom font to false
     */
    textPattern->SetIsCustomFont(false);

    /**
     * @tc.steps: step3. Verify value is set correctly
     * @tc.expected: step3. isCustomFont is false
     */
    EXPECT_FALSE(textPattern->GetIsCustomFont());
}

/**
 * @tc.name: SetIsMeasureBoundary001
 * @tc.desc: Test SetIsMeasureBoundary with true value
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, SetIsMeasureBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set measure boundary to true
     */
    textPattern->SetIsMeasureBoundary(true);

    /**
     * @tc.steps: step3. Verify value is set correctly
     * @tc.expected: step3. isMeasureBoundary is true
     */
    EXPECT_TRUE(textPattern->IsMeasureBoundary());
}

/**
 * @tc.name: SetIsMeasureBoundary002
 * @tc.desc: Test SetIsMeasureBoundary with false value
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, SetIsMeasureBoundary002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set measure boundary to false
     */
    textPattern->SetIsMeasureBoundary(false);

    /**
     * @tc.steps: step3. Verify value is set correctly
     * @tc.expected: step3. isMeasureBoundary is false
     */
    EXPECT_FALSE(textPattern->IsMeasureBoundary());
}

/**
 * @tc.name: StatusTransitions001
 * @tc.desc: Test status_ transitions from NONE to DRAGGING
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, StatusTransitions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Verify initial status
     * @tc.expected: step2. status is NONE and IsDragging is false
     */
    EXPECT_EQ(textPattern->status_, Status::NONE);
    EXPECT_FALSE(textPattern->IsDragging());

    /**
     * @tc.steps: step3. Transition to DRAGGING
     */
    textPattern->status_ = Status::DRAGGING;

    /**
     * @tc.steps: step4. Verify new status
     * @tc.expected: step4. IsDragging is true
     */
    EXPECT_TRUE(textPattern->IsDragging());
}

/**
 * @tc.name: StatusTransitions002
 * @tc.desc: Test status_ transitions from DRAGGING to FLOATING
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, StatusTransitions002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set initial status to DRAGGING
     * @tc.expected: step2. IsDragging is true
     */
    textPattern->status_ = Status::DRAGGING;
    EXPECT_TRUE(textPattern->IsDragging());

    /**
     * @tc.steps: step3. Transition to FLOATING
     */
    textPattern->status_ = Status::FLOATING;

    /**
     * @tc.steps: step4. Verify IsDragging returns false
     * @tc.expected: step4. IsDragging is false
     */
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: StatusTransitions003
 * @tc.desc: Test status_ transitions from FLOATING to ON_DROP
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, StatusTransitions003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set initial status to FLOATING
     * @tc.expected: step2. IsDragging is false
     */
    textPattern->status_ = Status::FLOATING;
    EXPECT_FALSE(textPattern->IsDragging());

    /**
     * @tc.steps: step3. Transition to ON_DROP
     */
    textPattern->status_ = Status::ON_DROP;

    /**
     * @tc.steps: step4. Verify IsDragging still returns false
     * @tc.expected: step4. IsDragging is false
     */
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: StatusTransitions004
 * @tc.desc: Test status_ transitions from ON_DROP back to NONE
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, StatusTransitions004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Set initial status to ON_DROP
     * @tc.expected: step2. IsDragging is false
     */
    textPattern->status_ = Status::ON_DROP;
    EXPECT_FALSE(textPattern->IsDragging());

    /**
     * @tc.steps: step3. Transition back to NONE
     */
    textPattern->status_ = Status::NONE;

    /**
     * @tc.steps: step4. Verify IsDragging returns false
     * @tc.expected: step4. IsDragging is false
     */
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: StatusTransitions005
 * @tc.desc: Test status_ transitions through all states
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, StatusTransitions005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Transition through all states: NONE -> DRAGGING -> FLOATING -> ON_DROP -> NONE
     * @tc.expected: step2. IsDragging returns correct value for each state
     */
    textPattern->status_ = Status::NONE;
    EXPECT_FALSE(textPattern->IsDragging());

    textPattern->status_ = Status::DRAGGING;
    EXPECT_TRUE(textPattern->IsDragging());

    textPattern->status_ = Status::FLOATING;
    EXPECT_FALSE(textPattern->IsDragging());

    textPattern->status_ = Status::ON_DROP;
    EXPECT_FALSE(textPattern->IsDragging());

    textPattern->status_ = Status::NONE;
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: StatusTransitions006
 * @tc.desc: Test status_ rapid transitions
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, StatusTransitions006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Rapid status transitions
     */
    for (int i = 0; i < 100; i++) {
        switch (i % 4) {
            case 0:
                textPattern->status_ = Status::NONE;
                break;
            case 1:
                textPattern->status_ = Status::DRAGGING;
                break;
            case 2:
                textPattern->status_ = Status::FLOATING;
                break;
            case 3:
                textPattern->status_ = Status::ON_DROP;
                break;
            default:
                break;
        }
    }

    /**
     * @tc.steps: step3. Final state should be ON_DROP (100 % 4 = 0, so NONE)
     * @tc.expected: step3. IsDragging is false
     */
    textPattern->status_ = Status::NONE;
    EXPECT_FALSE(textPattern->IsDragging());
}

/**
 * @tc.name: TextContentLength001
 * @tc.desc: Test text content length with various placeholder counts
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextContentLength001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Add a span to enable length calculation
     * @tc.expected: step2. Span is created successfully
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    textPattern->spans_.emplace_back(spanItem);

    /**
     * @tc.steps: step3. Test with zero placeholder count
     * @tc.expected: step3. Text content length is 4
     */
    textPattern->textForDisplay_ = u"Test";
    textPattern->placeholderCount_ = 0;
    EXPECT_EQ(textPattern->GetTextContentLength(), 4);

    /**
     * @tc.steps: step4. Test with non-zero placeholder count
     * @tc.expected: step4. Text content length is 7
     */
    textPattern->placeholderCount_ = 3;
    EXPECT_EQ(textPattern->GetTextContentLength(), 7);
}

/**
 * @tc.name: TextContentLength002
 * @tc.desc: Test text content length with empty text and placeholders
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextContentLength002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Add span
     * @tc.expected: step2. Span is created successfully
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    textPattern->spans_.emplace_back(spanItem);

    /**
     * @tc.steps: step3. Test with empty text but with placeholders
     * @tc.expected: step3. Text content length equals TEST_PLACEHOLDER_COUNT
     */
    textPattern->textForDisplay_ = u"";
    textPattern->placeholderCount_ = TEST_PLACEHOLDER_COUNT;
    EXPECT_EQ(textPattern->GetTextContentLength(), TEST_PLACEHOLDER_COUNT);
}

/**
 * @tc.name: TextContentLength003
 * @tc.desc: Test GetTextContentLength with zero text length
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextContentLength003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern
     * @tc.expected: step1. TextPattern is created successfully
     */
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Add span
     * @tc.expected: step2. Span is created successfully
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    textPattern->spans_.emplace_back(spanItem);

    /**
     * @tc.steps: step3. Test with zero text length and zero placeholder
     * @tc.expected: step3. Text content length is 0
     */
    textPattern->textForDisplay_ = u"";
    textPattern->placeholderCount_ = 0;
    EXPECT_EQ(textPattern->GetTextContentLength(), 0);
}

} // namespace OHOS::Ace::NG
