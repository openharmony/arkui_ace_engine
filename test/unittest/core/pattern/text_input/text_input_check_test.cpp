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

#include "text_input_base.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class TextInputCheckTest : public TextInputBases {
public:
};

/**
 * @tc.name: CheckAutoSave001
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and SetEnableAutoFill false.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(false);
        model.SetMaxLength(DEFAULT_TEXT.size());
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave002
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and SetEnableAutoFill true.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave003
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set textValue empty.
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave004
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextInputType USER_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::USER_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step4. set PasswordTextValue ne textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave005
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextInputType VISIBLE_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave006
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextInputType NEW_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::NEW_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave007
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType USER_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::USER_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave008
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType VISIBLE_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::VISIBLE_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave009
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType NEW_PASSWORD.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::NEW_PASSWORD);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0010
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType FULL_STREET_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::FULL_STREET_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0011
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType HOUSE_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::HOUSE_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0012
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType DISTRICT_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::DISTRICT_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0013
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType CITY_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::CITY_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0014
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PROVINCE_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PROVINCE_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0015
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType COUNTRY_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::COUNTRY_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0016
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PERSON_FULL_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PERSON_FULL_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0017
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PERSON_LAST_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PERSON_LAST_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0018
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PERSON_FIRST_NAME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PERSON_FIRST_NAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0019
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PHONE_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PHONE_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0020
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PHONE_COUNTRY_CODE.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PHONE_COUNTRY_CODE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0021
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType FULL_PHONE_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::FULL_PHONE_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0022
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType EMAIL_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::EMAIL_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0023
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType BANK_CARD_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::BANK_CARD_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0024
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType ID_CARD_NUMBER.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::ID_CARD_NUMBER);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0025
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType PRECISE_TIME.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::PRECISE_TIME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0026
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType HOUR_AND_MINUTE.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::HOUR_AND_MINUTE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0027
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType DATE.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::DATE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0028
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType MONTH.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::MONTH);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0029
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType YEAR.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::YEAR);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0030
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set NICKNAME YEAR.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::NICKNAME);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0031
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType DETAIL_INFO_WITHOUT_STREET.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::DETAIL_INFO_WITHOUT_STREET);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: CheckAutoSave0032
 * @tc.desc: Test the result after check autosave.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, CheckAutoSave0032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and set TextContentType FORMAT_ADDRESS.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetContentType(TextContentType::FORMAT_ADDRESS);
    });
    GetFocus();

    /**
     * @tc.steps: step2. call CheckAutoSave.
     * @tc.expected: return true
     */
    pattern_->lastAutoFillTextValue_ = "a";
    EXPECT_TRUE(pattern_->CheckAutoSave());
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step3. set PasswordTextValue eq textValue and call CheckAutoSave.
     * @tc.expected: return false
     */
    pattern_->lastAutoFillTextValue_ = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_FALSE(pattern_->CheckAutoSave());
}

/**
 * @tc.name: GetDragUpperLeftCoordinates001
 * @tc.desc: Test dragUpper left coordinates.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, GetDragUpperLeftCoordinates001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2.call GetDragUpperLeftCoordinates.
     * @tc.expected: return true
     */
    OffsetF localOffset(0.0f, 0.0f);
    EXPECT_EQ(pattern_->GetDragUpperLeftCoordinates(), localOffset);
}

/**
 * @tc.name: CheckTextAlignByDirection
 * @tc.desc: Test the methods for obtaining caret metrics.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputCheckTest, GetCaretMetrics, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call function GetCaretMetrics
     */
    CaretMetricsF caretMetrics;
    pattern_->GetCaretMetrics(caretMetrics);
    EXPECT_EQ(caretMetrics.offset, OffsetF(0, 0));
    EXPECT_EQ(caretMetrics.height, 50);
}
}