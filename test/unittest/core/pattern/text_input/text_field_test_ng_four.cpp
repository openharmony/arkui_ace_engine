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
#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldTestNgFour : public TextInputBases {
public:
};

/**
 * @tc.name: ChangeTextCallbackTest015
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->DeleteForward(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"harmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 4);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest016
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->DeleteForward(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest017
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->DeleteBackward(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"harmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 4);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest018
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->DeleteBackward(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest019
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    bool fireOnWillChange = false;
    auto onWillChange = [&fireOnWillChange](const ChangeValueInfo& info) {
        fireOnWillChange = true;
        return true;
    };

    bool fireOnWillInsert = false;
    auto onWillInsert = [&fireOnWillInsert](const InsertValueInfo& info) {
        fireOnWillInsert = true;
        return false;
    };

    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    eventHub_->SetOnWillInsertValueEvent(std::move(onWillInsert));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    auto property = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    property->UpdateWidthAuto(true);
    Dimension width;
    width.SetValue(50);
    width.SetUnit(DimensionUnit::PERCENT);
    property->UpdateTextIndent(width);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    InsertCommandInfo info;
    info.insertValue = u"2";
    info.reason = InputReason::IME;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_EQ(fireOnWillChange, false);
    EXPECT_EQ(fireOnWillInsert, true);
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest020
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    bool fireOnWillChange = false;
    auto onWillChange = [&fireOnWillChange](const ChangeValueInfo& info) {
        fireOnWillChange = true;
        return false;
    };

    bool fireOnWillInsert = false;
    auto onWillInsert = [&fireOnWillInsert](const InsertValueInfo& info) {
        fireOnWillInsert = true;
        return true;
    };

    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    eventHub_->SetOnWillInsertValueEvent(std::move(onWillInsert));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    InsertCommandInfo info;
    info.insertValue = u"2";
    info.reason = InputReason::IME;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_EQ(fireOnWillChange, true);
    EXPECT_EQ(fireOnWillInsert, true);
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest021
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    bool fireOnWillChange = false;
    auto onWillChange = [&fireOnWillChange](const ChangeValueInfo& info) {
        fireOnWillChange = true;
        return false;
    };

    bool fireOnWillDelete = false;
    auto onWillDelete = [&fireOnWillDelete](const DeleteValueInfo& info) {
        fireOnWillDelete = true;
        return true;
    };

    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    eventHub_->SetOnWillDeleteEvent(std::move(onWillDelete));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    pattern_->DeleteBackward(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(fireOnWillChange, true);
    EXPECT_EQ(fireOnWillDelete, true);
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest022
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    bool fireOnWillChange = false;
    auto onWillChange = [&fireOnWillChange](const ChangeValueInfo& info) {
        fireOnWillChange = true;
        return true;
    };

    bool fireOnWillDelete = false;
    auto onWillDelete = [&fireOnWillDelete](const DeleteValueInfo& info) {
        fireOnWillDelete = true;
        return false;
    };

    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    eventHub_->SetOnWillDeleteEvent(std::move(onWillDelete));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    pattern_->DeleteBackward(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(fireOnWillChange, false);
    EXPECT_EQ(fireOnWillDelete, true);
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest023
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    bool fireOnWillChange = false;
    auto onWillChange = [&fireOnWillChange](const ChangeValueInfo& info) {
        fireOnWillChange = true;
        return true;
    };

    bool fireOnWillInsert = false;
    auto onWillInsert = [&fireOnWillInsert](const InsertValueInfo& info) {
        fireOnWillInsert = true;
        return false;
    };

    bool fireOnWillDelete = false;
    auto onWillDelete = [&fireOnWillDelete](const DeleteValueInfo& info) {
        fireOnWillDelete = true;
        return true;
    };

    bool fireOnDidInsert = false;
    auto onDidInsert = [&fireOnDidInsert](const InsertValueInfo& info) {
        fireOnDidInsert = true;
    };

    bool fireOnDidDelete = false;
    auto onDidDelete = [&fireOnDidDelete](const DeleteValueInfo& info) {
        fireOnDidDelete = true;
    };

    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    eventHub_->SetOnWillInsertValueEvent(std::move(onWillInsert));
    eventHub_->SetOnWillDeleteEvent(std::move(onWillDelete));
    eventHub_->SetOnDidInsertValueEvent(std::move(onDidInsert));
    eventHub_->SetOnDidDeleteEvent(std::move(onDidDelete));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);
    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    InsertCommandInfo info;
    info.insertValue = u"2";
    info.reason = InputReason::IME;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_EQ(fireOnWillChange, false);
    EXPECT_EQ(fireOnWillInsert, true);
    EXPECT_EQ(fireOnWillDelete, false);
    EXPECT_EQ(fireOnDidInsert, false);
    EXPECT_EQ(fireOnDidDelete, false);
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest024
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    bool fireOnWillChange = false;
    auto onWillChange = [&fireOnWillChange](const ChangeValueInfo& info) {
        fireOnWillChange = true;
        return true;
    };

    bool fireOnWillInsert = false;
    auto onWillInsert = [&fireOnWillInsert](const InsertValueInfo& info) {
        fireOnWillInsert = true;
        return true;
    };

    bool fireOnWillDelete = false;
    auto onWillDelete = [&fireOnWillDelete](const DeleteValueInfo& info) {
        fireOnWillDelete = true;
        return false;
    };

    bool fireOnDidInsert = false;
    auto onDidInsert = [&fireOnDidInsert](const InsertValueInfo& info) {
        fireOnDidInsert = true;
    };

    bool fireOnDidDelete = false;
    auto onDidDelete = [&fireOnDidDelete](const DeleteValueInfo& info) {
        fireOnDidDelete = true;
    };

    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    eventHub_->SetOnWillInsertValueEvent(std::move(onWillInsert));
    eventHub_->SetOnWillDeleteEvent(std::move(onWillDelete));
    eventHub_->SetOnDidInsertValueEvent(std::move(onDidInsert));
    eventHub_->SetOnDidDeleteEvent(std::move(onDidDelete));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);
    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    InsertCommandInfo info;
    info.insertValue = u"2";
    info.reason = InputReason::IME;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_EQ(fireOnWillChange, true);
    EXPECT_EQ(fireOnWillInsert, true);
    EXPECT_EQ(fireOnWillDelete, true);
    EXPECT_EQ(fireOnDidInsert, true);
    EXPECT_EQ(fireOnDidDelete, false);
    EXPECT_EQ(pattern_->GetTextValue().compare("2openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest025
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    bool fireOnWillChange = false;
    auto onWillChange = [&fireOnWillChange](const ChangeValueInfo& info) {
        fireOnWillChange = true;
        return false;
    };

    bool fireOnWillInsert = false;
    auto onWillInsert = [&fireOnWillInsert](const InsertValueInfo& info) {
        fireOnWillInsert = true;
        return true;
    };

    bool fireOnWillDelete = false;
    auto onWillDelete = [&fireOnWillDelete](const DeleteValueInfo& info) {
        fireOnWillDelete = true;
        return true;
    };

    bool fireOnDidInsert = false;
    auto onDidInsert = [&fireOnDidInsert](const InsertValueInfo& info) {
        fireOnDidInsert = true;
    };

    bool fireOnDidDelete = false;
    auto onDidDelete = [&fireOnDidDelete](const DeleteValueInfo& info) {
        fireOnDidDelete = true;
    };

    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    eventHub_->SetOnWillInsertValueEvent(std::move(onWillInsert));
    eventHub_->SetOnWillDeleteEvent(std::move(onWillDelete));
    eventHub_->SetOnDidInsertValueEvent(std::move(onDidInsert));
    eventHub_->SetOnDidDeleteEvent(std::move(onDidDelete));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);
    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    InsertCommandInfo info;
    info.insertValue = u"2";
    info.reason = InputReason::IME;
    pattern_->ExecuteInsertValueCommand(info);
    EXPECT_EQ(fireOnWillChange, true);
    EXPECT_EQ(fireOnWillInsert, true);
    EXPECT_EQ(fireOnWillDelete, true);
    EXPECT_EQ(fireOnDidInsert, false);
    EXPECT_EQ(fireOnDidDelete, false);
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest026
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->DeleteRange(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->HandleOnUndoAction();
    EXPECT_EQ(changeValueInfo.oldContent, u"harmony");
    EXPECT_EQ(changeValueInfo.value, u"openharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 7);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 11);
}

/**
 * @tc.name: ChangeTextCallbackTest027
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->DeleteRange(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->HandleOnUndoAction();
    pattern_->HandleOnRedoAction();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"harmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 7);
}

/**
 * @tc.name: ChangeTextCallbackTest028
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);
    pattern_->HandleOnCopy();
    pattern_->HandleSetSelection(0, 2, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->HandleOnPaste();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"openenharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 2);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 4);
}

/**
 * @tc.name: ChangeTextCallbackTest029
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);
    pattern_->HandleOnCopy();
    pattern_->HandleSetSelection(0, 2, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->HandleOnPaste();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"openenharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 2);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 4);
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest030
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->HandleOnCut();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"harmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 4);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 0);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, -1);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"");
    EXPECT_EQ(changeValueInfo.previewText.offset, -1);
    EXPECT_EQ(changeValueInfo.previewText.value, u"");
    EXPECT_EQ(pattern_->GetTextValue().compare("harmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest031
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);
    pattern_->HandleSetSelection(0, 4, false);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->HandleOnCut();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"harmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 4);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 0);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, -1);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"");
    EXPECT_EQ(changeValueInfo.previewText.offset, -1);
    EXPECT_EQ(changeValueInfo.previewText.value, u"");
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest032
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->CleanNodeResponseKeyEvent();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 0);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, -1);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"");
    EXPECT_EQ(changeValueInfo.previewText.offset, -1);
    EXPECT_EQ(changeValueInfo.previewText.value, u"");
    EXPECT_EQ(pattern_->GetTextValue().compare(""), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest033
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */
    pattern_->CleanNodeResponseKeyEvent();
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 0);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, -1);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"");
    EXPECT_EQ(changeValueInfo.previewText.offset, -1);
    EXPECT_EQ(changeValueInfo.previewText.value, u"");
    EXPECT_EQ(pattern_->GetTextValue().compare("openharmony"), 0);
}

/**
 * @tc.name: ChangeTextCallbackTest034
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    const std::u16string previewTextStr = u"hhh";
    PreviewRange range = { -1, -1 };
    pattern_->SetPreviewText(previewTextStr, range);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"openharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 11);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, -1);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"");
    EXPECT_EQ(changeValueInfo.previewText.offset, 11);
    EXPECT_EQ(changeValueInfo.previewText.value, u"hhh");
}

/**
 * @tc.name: ChangeTextCallbackTest035
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));

    bool fireOnWillInsert = false;
    auto onWillInsert = [&fireOnWillInsert](const InsertValueInfo& info) {
        fireOnWillInsert = true;
        return true;
    };
    eventHub_->SetOnWillInsertValueEvent(std::move(onWillInsert));
    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    const std::u16string previewTextStr = u"hhh";
    PreviewRange range = { -1, -1 };
    pattern_->SetPreviewText(previewTextStr, range);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"");
    EXPECT_EQ(changeValueInfo.value, u"");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 0);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 0);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 0);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, -1);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"");
    EXPECT_EQ(changeValueInfo.previewText.offset, 0);
    EXPECT_EQ(changeValueInfo.previewText.value, u"hhh");
}

/**
 * @tc.name: ChangeTextCallbackTest036
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return true;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    const std::u16string oldPreviewTextStr = u"hhh";
    const std::u16string newPreviewTextStr = u"hh";
    PreviewRange range = { -1, -1 };
    pattern_->SetPreviewText(oldPreviewTextStr, range);
    pattern_->SetPreviewText(newPreviewTextStr, range);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"openharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 11);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"hhh");
    EXPECT_EQ(changeValueInfo.previewText.offset, 11);
    EXPECT_EQ(changeValueInfo.previewText.value, u"hh");
}

/**
 * @tc.name: ChangeTextCallbackTest037
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    const std::u16string oldPreviewTextStr = u"hhh";
    const std::u16string newPreviewTextStr = u"hh";
    PreviewRange range = { -1, -1 };
    pattern_->SetPreviewText(oldPreviewTextStr, range);
    pattern_->SetPreviewText(newPreviewTextStr, range);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"openharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 11);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"hhh");
    EXPECT_EQ(changeValueInfo.previewText.offset, 11);
    EXPECT_EQ(changeValueInfo.previewText.value, u"hh");
    EXPECT_EQ(pattern_->GetPreviewTextValue(), u"hh");
}

/**
 * @tc.name: ChangeTextCallbackTest038
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    const std::u16string oldPreviewTextStr = u"hhh";
    const std::u16string newPreviewTextStr = u"hh";
    PreviewRange range = { -1, -1 };
    pattern_->SetPreviewText(oldPreviewTextStr, range);
    pattern_->SetPreviewText(newPreviewTextStr, range);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"openharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 11);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"hhh");
    EXPECT_EQ(changeValueInfo.previewText.offset, 11);
    EXPECT_EQ(changeValueInfo.previewText.value, u"hh");
    EXPECT_EQ(pattern_->GetPreviewTextValue(), u"hh");
}

/**
 * @tc.name: ChangeTextCallbackTest039
 * @tc.desc: test for callback SetOnWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, ChangeTextCallbackTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();
    ChangeValueInfo changeValueInfo;
    auto onWillChange = [&changeValueInfo](const ChangeValueInfo& info) {
        changeValueInfo = info;
        return false;
    };
    eventHub_->SetOnWillChangeEvent(std::move(onWillChange));
    std::u16string content = u"openharmony";
    pattern_->InitEditingValueText(content);

    /**
     * @tc.steps: step2. change text with ExecuteInsertValueCommand
     * @tc.expected: return value is valid
     */

    const std::u16string oldPreviewTextStr = u"hhh";
    const std::u16string newPreviewTextStr = u"a";
    PreviewRange rangeBefore = { -1, -1 };
    PreviewRange rangeAfter = { 11, 13 };
    pattern_->SetPreviewText(oldPreviewTextStr, rangeBefore);
    pattern_->SetPreviewText(newPreviewTextStr, rangeAfter);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(changeValueInfo.oldContent, u"openharmony");
    EXPECT_EQ(changeValueInfo.value, u"openharmony");
    EXPECT_EQ(changeValueInfo.rangeBefore.start, 11);
    EXPECT_EQ(changeValueInfo.rangeBefore.end, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.start, 11);
    EXPECT_EQ(changeValueInfo.rangeAfter.end, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.offset, 11);
    EXPECT_EQ(changeValueInfo.oldPreviewText.value, u"hhh");
    EXPECT_EQ(changeValueInfo.previewText.offset, 11);
    EXPECT_EQ(changeValueInfo.previewText.value, u"ah");
}

/**
 * @tc.name: GetAccessibilityText001
 * @tc.desc: test CounterDecorator GetAccessibilityText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFour, GetAccessibilityText001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text field node
     */
    CreateTextField(DEFAULT_TEXT);

    /**
     * @tc.step: step2. call AddCounterNode
     */
    ASSERT_NE(pattern_, nullptr);
    pattern_->AddCounterNode();
    auto counter = pattern_->GetCounterDecorator();
    ASSERT_NE(counter, nullptr);
    auto result = AceType::DynamicCast<CounterDecorator>(counter)->GetAccessibilityText(10, 20);
    EXPECT_EQ(result, "");
}

} // namespace OHOS::Ace::NG
