/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

class TextFieldPatternOnWillTest : public TextInputBases {
    struct OnWillOrder {
        int time;
        int willInsert;
        int didInsert;
        int willDelete;
        int didDelete;
        int willChange;
        int onChange;

        bool operator==(const OnWillOrder& other) const
        {
            return (time == other.time) && (willInsert == other.willInsert) && (didInsert == other.didInsert) &&
                   (willDelete == other.willDelete) && (didDelete == other.didDelete) &&
                   (willChange == other.willChange) && (onChange == other.onChange);
        }

        bool operator!=(const OnWillOrder& other) const
        {
            return !(*this == other);
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const OnWillOrder& order)
    {
        os << "OnWillOrder{time: " << order.time << ", willInsert: " << order.willInsert
           << ", didInsert: " << order.didInsert << ", willDelete: " << order.willDelete
           << ", didDelete: " << order.didDelete << ", willChange: " << order.willChange
           << ", onChange: " << order.onChange << "}";
        return os;
    }

    void CreateTextFieldWithCallback(OnWillOrder& order, const std::string& text = "", bool callbackValue = true)
    {
        auto callbackWillInsert = [&order, callbackValue](const InsertValueInfo& info) mutable {
            order.willInsert = ++order.time;
            return callbackValue;
        };
        auto callbackDidInsert = [&order, callbackValue](const InsertValueInfo& info) mutable {
            order.didInsert = ++order.time;
            return callbackValue;
        };
        auto callbackWillDelete = [&order, callbackValue](const DeleteValueInfo& info) mutable {
            order.willDelete = ++order.time;
            return callbackValue;
        };
        auto callbackDidDelete = [&order, callbackValue](const DeleteValueInfo& info) mutable {
            order.didDelete = ++order.time;
            return callbackValue;
        };
        auto callbackWillChange = [&order, callbackValue](const ChangeValueInfo& info) mutable {
            order.willChange = ++order.time;
            return callbackValue;
        };
        auto callbackChange = [&order, callbackValue](const ChangeValueInfo& info) mutable {
            order.onChange = ++order.time;
            return callbackValue;
        };
        CreateTextField(text, "",
            [&callbackWillInsert, &callbackDidInsert, &callbackWillDelete, &callbackDidDelete, &callbackWillChange,
                &callbackChange](TextFieldModelNG& model) {
                model.SetOnWillInsertValueEvent(std::move(callbackWillInsert));
                model.SetOnDidInsertValueEvent(std::move(callbackDidInsert));
                model.SetOnWillDeleteEvent(std::move(callbackWillDelete));
                model.SetOnDidDeleteEvent(std::move(callbackDidDelete));
                model.SetOnWillChangeEvent(std::move(callbackWillChange));
                model.SetOnChange(std::move(callbackChange));
            });
    }
};

/**
 * @tc.name: OnWillChange001
 * @tc.desc: Test TextPattern insert one number, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */

    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->InsertValue("1", true);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 4;
    expectOrder.willInsert = 1;
    expectOrder.willChange = 2;
    expectOrder.didInsert = 3;
    expectOrder.onChange = 4;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent002
 * @tc.desc: Test TextPattern delete one number, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->DeleteBackward(1);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 5;
    expectOrder.willDelete = 2;
    expectOrder.willChange = 3;
    expectOrder.didDelete = 4;
    expectOrder.onChange = 5;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent003
 * @tc.desc: Test TextPattern move cursor, insert one word, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 1, false);
    pattern_->InsertValue("a", true);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 5;
    expectOrder.willInsert = 2;
    expectOrder.willChange = 3;
    expectOrder.didInsert = 4;
    expectOrder.onChange = 5;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent004
 * @tc.desc: Test TextPattern select words, insert one word, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 3, false);
    pattern_->InsertValue("a", true);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 7;
    expectOrder.willInsert = 2;
    expectOrder.willDelete = 3;
    expectOrder.willChange = 4;
    expectOrder.didInsert = 6;
    expectOrder.didDelete = 5;
    expectOrder.onChange = 7;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent005
 * @tc.desc: Test TextPattern move cursor, delete backward, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 1, false);
    pattern_->DeleteBackward(1);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 5;
    expectOrder.willDelete = 2;
    expectOrder.willChange = 3;
    expectOrder.didDelete = 4;
    expectOrder.onChange = 5;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent006
 * @tc.desc: Test TextPattern select words, delete backward, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 3, false);
    pattern_->DeleteBackward(1);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 5;
    expectOrder.willDelete = 2;
    expectOrder.willChange = 3;
    expectOrder.didDelete = 4;
    expectOrder.onChange = 5;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent007
 * @tc.desc: Test TextPattern move cursor, delete forward, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 1, false);
    pattern_->DeleteForward(1);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 5;
    expectOrder.willDelete = 2;
    expectOrder.willChange = 3;
    expectOrder.didDelete = 4;
    expectOrder.onChange = 5;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent008
 * @tc.desc: Test TextPattern select words, delete forward, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 3, false);
    pattern_->DeleteForward(1);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 5;
    expectOrder.willDelete = 2;
    expectOrder.willChange = 3;
    expectOrder.didDelete = 4;
    expectOrder.onChange = 5;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent009
 * @tc.desc: Test TextPattern select words, copy, move cursor, then paste, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 3, false);
    pattern_->HandleOnCopy();
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 1;
    expectOrder.onChange = 1;
    EXPECT_EQ(order, expectOrder);

    pattern_->SetCaretPosition(0);
    pattern_->HandleOnPaste();
    FlushLayoutTask(frameNode_);
    expectOrder.time = 3;
    expectOrder.willChange = 2;
    expectOrder.onChange = 3;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent010
 * @tc.desc: Test TextPattern select words, copy, then select words, paste. The order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(1, 3, false);
    pattern_->HandleOnCopy();
    FlushLayoutTask(frameNode_);

    pattern_->HandleSetSelection(4, 6, false);
    pattern_->HandleOnPaste();
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 3;
    expectOrder.willChange = 2;
    expectOrder.onChange = 3;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent011
 * @tc.desc: Test TextPattern select words, cut, then select words, paste. The order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123456");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->HandleSetSelection(4, 6, false);
    pattern_->HandleOnCut();
    FlushLayoutTask(frameNode_);

    pattern_->HandleSetSelection(1, 3, false);
    pattern_->HandleOnPaste();
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 5;
    expectOrder.willChange = 4;
    expectOrder.onChange = 5;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent012
 * @tc.desc: Test TextPattern is empty, delete backward. The order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "");
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->DeleteBackward(1);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 2;
    expectOrder.willDelete = 1;
    expectOrder.didDelete = 2;
    EXPECT_EQ(order, expectOrder);

    pattern_->DeleteForward(1);
    FlushLayoutTask(frameNode_);
    expectOrder.time = 4;
    expectOrder.willDelete = 3;
    expectOrder.didDelete = 4;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent013
 * @tc.desc: Test TextPattern insert one number, callback return false, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */

    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "", false);
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->InsertValue("1", true);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 1;
    expectOrder.willInsert = 1;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: OnWillEvent014
 * @tc.desc: Test TextPattern delete one number, callback return false, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillEvent014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode textInput and add onWillEvent callback
     */
    OnWillOrder order = { 0, 0, 0, 0, 0, 0, 0 };
    CreateTextFieldWithCallback(order, "123", false);
    GetFocus();

    /**
     * @tc.steps: step2. insert text, trigger callbacks
     */
    pattern_->DeleteBackward(1);
    FlushLayoutTask(frameNode_);
    OnWillOrder expectOrder = { 0, 0, 0, 0, 0, 0, 0 };
    expectOrder.time = 2;
    expectOrder.willDelete = 2;
    expectOrder.onChange = 1;
    EXPECT_EQ(order, expectOrder);
}

/**
 * @tc.name: UpdateObscure001
 * @tc.desc: Test is textarea, UpdateObscure(), case TextInputType::UNSPECIFIED
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, UpdateObscure001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    pattern_->textObscured_ = false;
    pattern_->UpdateObscure(u"1", true);
    EXPECT_EQ(pattern_->nakedCharPosition_, -1);
}

/**
 * @tc.name: UpdateObscure002
 * @tc.desc: Test is textarea, UpdateObscure(), case TextInputType::NEW_PASSWORD
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, UpdateObscure002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::NEW_PASSWORD); });
    pattern_->textObscured_ = false;
    pattern_->UpdateObscure(u"1", true);
    EXPECT_EQ(pattern_->nakedCharPosition_, -1);
}

/**
 * @tc.name: UpdateObscure003
 * @tc.desc: Test is textarea, UpdateObscure(), case textObscured_ = true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, UpdateObscure003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::NEW_PASSWORD); });
    pattern_->textObscured_ = true;
    pattern_->UpdateObscure(u"2", true);
    EXPECT_EQ(pattern_->nakedCharPosition_, -1);
}

/**
 * @tc.name: UpdateObscure004
 * @tc.desc: Test is textarea, UpdateObscure(), case insert value not number
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, UpdateObscure004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::NUMBER_PASSWORD); });
    pattern_->textObscured_ = true;
    pattern_->UpdateObscure(u"a", true);
    EXPECT_EQ(pattern_->nakedCharPosition_, -1);
}

/**
 * @tc.name: UpdateObscure005
 * @tc.desc: Test is textarea, UpdateObscure(), case insert value size != 1
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, UpdateObscure005, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::NUMBER_PASSWORD); });
    pattern_->textObscured_ = true;
    pattern_->UpdateObscure(u"aa", true);
    EXPECT_EQ(pattern_->nakedCharPosition_, -1);
}

} // namespace OHOS::Ace::NG