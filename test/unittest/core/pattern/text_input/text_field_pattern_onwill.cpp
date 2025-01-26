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
    };
    void CreateTextFieldWithCallback(OnWillOrder& order, const std::string& text = "")
    {
        auto callbackWillInsert = [&order](const InsertValueInfo& info) mutable {
            order.willInsert = ++order.time;
            return order.time;
        };
        auto callbackDidInsert = [&order](const InsertValueInfo& info) mutable {
            order.didInsert = ++order.time;
            return order.time;
        };
        auto callbackWillDelete = [&order](const DeleteValueInfo& info) mutable {
            order.willDelete = ++order.time;
            return order.time;
        };
        auto callbackDidDelete = [&order](const DeleteValueInfo& info) mutable {
            order.didDelete = ++order.time;
            return order.time;
        };
        auto callbackWillChange = [&order](const ChangeValueInfo& info) mutable {
            order.willChange = ++order.time;
            return order.time;
        };
        auto callbackChange = [&order](const ChangeValueInfo& info) mutable {
            order.onChange = ++order.time;
            return order.time;
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
    EXPECT_EQ(order.time, 4);
    EXPECT_EQ(order.willInsert, 1);
    EXPECT_EQ(order.willChange, 2);
    EXPECT_EQ(order.didInsert, 3);
    EXPECT_EQ(order.onChange, 4);
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
    EXPECT_EQ(order.time, 5);
    EXPECT_EQ(order.willDelete, 2);
    EXPECT_EQ(order.willChange, 3);
    EXPECT_EQ(order.didDelete, 4);
    EXPECT_EQ(order.onChange, 5);
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
    EXPECT_EQ(order.time, 5);
    EXPECT_EQ(order.willDelete, 0);
    EXPECT_EQ(order.willChange, 3);
    EXPECT_EQ(order.didDelete, 0);
    EXPECT_EQ(order.onChange, 5);
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
    EXPECT_EQ(order.time, 7);
    EXPECT_EQ(order.willDelete, 3);
    EXPECT_EQ(order.willChange, 4);
    EXPECT_EQ(order.didDelete, 5);
    EXPECT_EQ(order.onChange, 7);
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
    EXPECT_EQ(order.time, 5);
    EXPECT_EQ(order.willDelete, 2);
    EXPECT_EQ(order.willChange, 3);
    EXPECT_EQ(order.didDelete, 4);
    EXPECT_EQ(order.onChange, 5);
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
    EXPECT_EQ(order.time, 5);
    EXPECT_EQ(order.willDelete, 2);
    EXPECT_EQ(order.willChange, 3);
    EXPECT_EQ(order.didDelete, 4);
    EXPECT_EQ(order.onChange, 5);
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
    EXPECT_EQ(order.time, 5);
    EXPECT_EQ(order.willDelete, 2);
    EXPECT_EQ(order.willChange, 3);
    EXPECT_EQ(order.didDelete, 4);
    EXPECT_EQ(order.onChange, 5);
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
    EXPECT_EQ(order.time, 5);
    EXPECT_EQ(order.willDelete, 2);
    EXPECT_EQ(order.willChange, 3);
    EXPECT_EQ(order.didDelete, 4);
    EXPECT_EQ(order.onChange, 5);
}
} // namespace OHOS::Ace::NG