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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

class TextFieldPatternAIPatternTest : public TextInputBases {};

/**
 * @tc.name: HandleAIMenuOption001
 * @tc.desc: Test HandleAIMenuOption with empty aiMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, HandleAIMenuOption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and call HandleAIMenuOption with empty options
     * @tc.expected: Method should execute without crash when aiMenuOptions is empty
     */
    CreateTextField("", "");
    pattern_->aiMenuOptions_.clear();
    pattern_->HandleAIMenuOption("");
    /**
     * @tc.steps: step2. Verify aiMenuOptions is cleared
     * @tc.expected: aiMenuOptions should be empty after clear operation
     */
    EXPECT_TRUE(pattern_->aiMenuOptions_.empty());
    EXPECT_EQ(pattern_->aiMenuOptions_.size(), static_cast<size_t>(0));
}

/**
 * @tc.name: HandleAIMenuOption002
 * @tc.desc: Test HandleAIMenuOption with one menu option
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, HandleAIMenuOption002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set aiMenuOptions_ with one item and call HandleAIMenuOption
     * @tc.expected: Method should execute and process the menu option
     */
    CreateTextField("", "");
    AISpan aiSpan = { 0, 10, "1234567890", TextDataDetectType::PHONE_NUMBER };
    pattern_->aiMenuOptions_[TextDataDetectType::PHONE_NUMBER] = aiSpan;
    pattern_->HandleAIMenuOption("Phone");
    /**
     * @tc.steps: step2. Verify aiMenuOptions is correctly set
     * @tc.expected: aiMenuOptions should contain the PHONE_NUMBER span
     */
    EXPECT_FALSE(pattern_->aiMenuOptions_.empty());
    EXPECT_EQ(pattern_->aiMenuOptions_.size(), static_cast<size_t>(1));
    EXPECT_TRUE(pattern_->aiMenuOptions_.find(TextDataDetectType::PHONE_NUMBER) != pattern_->aiMenuOptions_.end());
    auto& phoneSpan = pattern_->aiMenuOptions_[TextDataDetectType::PHONE_NUMBER];
    EXPECT_EQ(phoneSpan.start, 0);
    EXPECT_EQ(phoneSpan.end, 10);
    EXPECT_EQ(phoneSpan.content, "1234567890");
    EXPECT_EQ(phoneSpan.type, TextDataDetectType::PHONE_NUMBER);
}

/**
 * @tc.name: PrepareAIMenuOptions001
 * @tc.desc: Test PrepareAIMenuOptions when selectDetectEnabled is false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Disable select detection and call PrepareAIMenuOptions
     * @tc.expected: Method should return false when selectDetectEnabled is false
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = false;
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PrepareAIMenuOptions002
 * @tc.desc: Test PrepareAIMenuOptions with empty aiSpanMap_
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Enable select detection and clear aiSpanMap_, then call PrepareAIMenuOptions
     * @tc.expected: Method should return false when aiSpanMap_ is empty
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    auto adapter = pattern_->GetSelectDetectorAdapter();
    adapter->aiSpanMap_.clear();
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PrepareAIMenuOptions003
 * @tc.desc: Test PrepareAIMenuOptions with one aiSpan in aiSpanMap_
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set one aiSpan in aiSpanMap_ and call PrepareAIMenuOptions
     * @tc.expected: Method should return true and populate aiMenuOptions with span
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"1234567890");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan aiSpan = { 0, 10, "1234567890", TextDataDetectType::PHONE_NUMBER };
    adapter->aiSpanMap_[0] = aiSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 3);
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PrepareAIMenuOptions004
 * @tc.desc: Test PrepareAIMenuOptions with single aiSpan in aiSpanMap_
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set single aiSpan in aiSpanMap_ and call PrepareAIMenuOptions
     * @tc.expected: Method should return true and populate aiMenuOptions with the single type
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"1234567890");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan phoneSpan = { 0, 10, "1234567890", TextDataDetectType::PHONE_NUMBER };
    adapter->aiSpanMap_[0] = phoneSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 3);
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MaybeNeedShowSelectAIDetect001
 * @tc.desc: Test MaybeNeedShowSelectAIDetect when selectDetectEnabled is false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, MaybeNeedShowSelectAIDetect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Disable select detection and call MaybeNeedShowSelectAIDetect
     * @tc.expected: Method should return false when selectDetectEnabled is false
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = false;
    auto result = pattern_->MaybeNeedShowSelectAIDetect();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MaybeNeedShowSelectAIDetect002
 * @tc.desc: Test MaybeNeedShowSelectAIDetect with empty aiSpanMap_
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, MaybeNeedShowSelectAIDetect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Enable select detection with empty aiSpanMap_ and call MaybeNeedShowSelectAIDetect
     * @tc.expected: Method should return false when aiSpanMap_ is empty
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    auto adapter = pattern_->GetSelectDetectorAdapter();
    adapter->aiSpanMap_.clear();
    adapter->StartAITask(true);
    auto result = pattern_->MaybeNeedShowSelectAIDetect();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PrepareAIMenuOptions005
 * @tc.desc: Test PrepareAIMenuOptions with URL type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set URL aiSpan in aiSpanMap_ and call PrepareAIMenuOptions
     * @tc.expected: Method should return true and populate aiMenuOptions with URL type
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"https://www.example.com");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan urlSpan = { 0, 23, "https://www.example.com", TextDataDetectType::URL };
    adapter->aiSpanMap_[0] = urlSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 5);
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_TRUE(result);
    EXPECT_EQ(aiMenuOptions.size(), static_cast<size_t>(1));
    EXPECT_TRUE(aiMenuOptions.find(TextDataDetectType::URL) != aiMenuOptions.end());
}

/**
 * @tc.name: PrepareAIMenuOptions006
 * @tc.desc: Test PrepareAIMenuOptions with EMAIL type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set EMAIL aiSpan in aiSpanMap_ and call PrepareAIMenuOptions
     * @tc.expected: Method should return true and populate aiMenuOptions with EMAIL type
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"test@example.com");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan emailSpan = { 0, 16, "test@example.com", TextDataDetectType::EMAIL };
    adapter->aiSpanMap_[0] = emailSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 5);
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_TRUE(result);
    EXPECT_EQ(aiMenuOptions.size(), static_cast<size_t>(1));
    EXPECT_TRUE(aiMenuOptions.find(TextDataDetectType::EMAIL) != aiMenuOptions.end());
}

/**
 * @tc.name: PrepareAIMenuOptions007
 * @tc.desc: Test PrepareAIMenuOptions with valid type that overlaps with selection
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set phone aiSpan that overlaps with selection
     * @tc.expected: Method should return true and populate aiMenuOptions with phone type
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"1234567890");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan phoneSpan = { 0, 10, "1234567890", TextDataDetectType::PHONE_NUMBER };
    adapter->aiSpanMap_[0] = phoneSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 5);
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_TRUE(result);
    EXPECT_EQ(aiMenuOptions.size(), static_cast<size_t>(1));
    EXPECT_TRUE(aiMenuOptions.find(TextDataDetectType::PHONE_NUMBER) != aiMenuOptions.end());
}

/**
 * @tc.name: PrepareAIMenuOptions008
 * @tc.desc: Test PrepareAIMenuOptions with email type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set email aiSpan in aiSpanMap_ and call PrepareAIMenuOptions
     * @tc.expected: Method should return true and populate aiMenuOptions with email type
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"test@example.com");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan emailSpan = { 0, 16, "test@example.com", TextDataDetectType::EMAIL };
    adapter->aiSpanMap_[0] = emailSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(0, 16);
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_TRUE(result);
    EXPECT_EQ(aiMenuOptions.size(), static_cast<size_t>(1));
    EXPECT_TRUE(aiMenuOptions.find(TextDataDetectType::EMAIL) != aiMenuOptions.end());
}

/**
 * @tc.name: PrepareAIMenuOptions009
 * @tc.desc: Test PrepareAIMenuOptions when no selection is made
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, PrepareAIMenuOptions009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set aiSpan but with no valid selection (same start and end)
     * @tc.expected: Method should return false when selection is invalid
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"1234567890");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan phoneSpan = { 0, 10, "1234567890", TextDataDetectType::PHONE_NUMBER };
    adapter->aiSpanMap_[0] = phoneSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 1); // Selection 1-1, invalid selection
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto result = pattern_->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MaybeNeedShowSelectAIDetect003
 * @tc.desc: Test MaybeNeedShowSelectAIDetect with URL type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, MaybeNeedShowSelectAIDetect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set URL aiSpan and call MaybeNeedShowSelectAIDetect
     * @tc.expected: Method should return true when URL type is present
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"https://www.example.com");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan urlSpan = { 0, 23, "https://www.example.com", TextDataDetectType::URL };
    adapter->aiSpanMap_[0] = urlSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 5);
    auto result = pattern_->MaybeNeedShowSelectAIDetect();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MaybeNeedShowSelectAIDetect004
 * @tc.desc: Test MaybeNeedShowSelectAIDetect with ADDRESS type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, MaybeNeedShowSelectAIDetect004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ADDRESS aiSpan and call MaybeNeedShowSelectAIDetect
     * @tc.expected: Method should return true when ADDRESS type is present
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"Beijing, China");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan addressSpan = { 0, 5, "Beijing, China", TextDataDetectType::ADDRESS };
    adapter->aiSpanMap_[0] = addressSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 5);
    auto result = pattern_->MaybeNeedShowSelectAIDetect();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MaybeNeedShowSelectAIDetect005
 * @tc.desc: Test MaybeNeedShowSelectAIDetect with DATETIME type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, MaybeNeedShowSelectAIDetect005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DATETIME aiSpan and call MaybeNeedShowSelectAIDetect
     * @tc.expected: Method should return true when DATETIME type is present
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"2024-03-15 10:30");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan datetimeSpan = { 0, 16, "2024-03-15 10:30", TextDataDetectType::DATE_TIME };
    adapter->aiSpanMap_[0] = datetimeSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(1, 5);
    auto result = pattern_->MaybeNeedShowSelectAIDetect();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UpdateAIMenuOptions001
 * @tc.desc: Test UpdateAIMenuOptions clears previous menu options
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternAIPatternTest, UpdateAIMenuOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set aiMenuOptions and call UpdateAIMenuOptions
     * @tc.expected: Method should populate aiMenuOptions with valid spans
     */
    CreateTextField("", "");
    pattern_->selectDetectEnabled_ = true;
    pattern_->contentController_->SetTextValue(u"1234567890");
    FlushLayoutTask(frameNode_);
    auto adapter = pattern_->GetSelectDetectorAdapter();
    AISpan phoneSpan = { 0, 10, "1234567890", TextDataDetectType::PHONE_NUMBER };
    adapter->aiSpanMap_[0] = phoneSpan;
    adapter->StartAITask(true);
    pattern_->selectController_->UpdateHandleIndex(0, 10);
    pattern_->UpdateAIMenuOptions();
    EXPECT_TRUE(pattern_->isShowAIMenuOption_);
    EXPECT_EQ(pattern_->aiMenuOptions_.size(), static_cast<size_t>(1));
}

} // namespace OHOS::Ace::NG
