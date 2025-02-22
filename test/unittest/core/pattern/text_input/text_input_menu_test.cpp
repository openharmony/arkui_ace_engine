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

#include "test/unittest/core/pattern/text_input/mock/mock_text_field_select_overlay.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextInputMenuTestNg : public TextInputBases {
public:
};

/**
 * @tc.name: SelectTextShowMenu001
 * @tc.desc: Test SetSelectionFlag when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu002
 * @tc.desc: Test SetSelectionFlag when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu003
 * @tc.desc: Test SetSelectionFlag when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu pops up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu pops up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SelectTextShowMenu004
 * @tc.desc: Test SetSelectionFlag when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu005
 * @tc.desc: Test SetSelectionFlag when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu006
 * @tc.desc: Test SetSelectionFlag when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu007
 * @tc.desc: Test SetSelectionFlag in inline mode when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
        model.SetInputStyle(InputStyle::INLINE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu008
 * @tc.desc: Test SetSelectionFlag in inline mode when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
        model.SetInputStyle(InputStyle::INLINE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu009
 * @tc.desc: Test SetSelectionFlag in inline mode when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
        model.SetInputStyle(InputStyle::INLINE);
    });
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu pops up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu pops up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SelectTextShowMenu010
 * @tc.desc: Test SetSelectionFlag in inline mode when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
        model.SetInputStyle(InputStyle::INLINE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu011
 * @tc.desc: Test SetSelectionFlag in inline mode when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
        model.SetInputStyle(InputStyle::INLINE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu012
 * @tc.desc: Test SetSelectionFlag in inline mode when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SelectTextShowMenu012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
        model.SetInputStyle(InputStyle::INLINE);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: The menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection001
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    /**
     * @tc.step: step2. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection002
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();

    /**
     * @tc.step: step2. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection003
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection004
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with menu pop up
     * @tc.expected: The menu still pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection005
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with menu pop up
     * @tc.expected: The menu still pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection006
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(false);
    });
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with menu pop up
     * @tc.expected: The menu still pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection007
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
    });
    GetFocus();

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu doesn't pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection008
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
    });
    GetFocus();

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu doesn't pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection009
 * @tc.desc: Test SetTextSelection when setting selectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextInputMenuTestNg, SetTextSelection009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetSelectionMenuHidden(true);
    });
    GetFocus();

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu doesn't pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG