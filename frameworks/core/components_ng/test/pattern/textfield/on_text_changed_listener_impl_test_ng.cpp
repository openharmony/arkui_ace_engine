/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "textfield_test_ng_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class OnTextChangedListenerImplTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    void CreatOnTextChangedListenerImplInstance();
    std::shared_ptr<OnTextChangedListenerImpl> textChangedListenerImpl_;
    RefPtr<FrameNode> host_;
};

void OnTextChangedListenerImplTestNg::SetUp()
{
    CreatOnTextChangedListenerImplInstance();
}

void OnTextChangedListenerImplTestNg::TearDown()
{
    textChangedListenerImpl_ = nullptr;
    host_ = nullptr;
}

void OnTextChangedListenerImplTestNg::CreatOnTextChangedListenerImplInstance()
{
    host_ = TextFieldTestNgUtils::CreatTextFieldNode();
    if (!host_) {
        GTEST_LOG_(INFO) << "create textfield node failed!";
        return;
    }
    auto pattern = host_->GetPattern<TextFieldPattern>();
    if (!pattern) {
        GTEST_LOG_(INFO) << "Get TextFieldPattern failed!";
        return;
    }
    WeakPtr<TextFieldPattern> textFieldPattern(pattern);
    textChangedListenerImpl_ = std::make_shared<OnTextChangedListenerImpl>(textFieldPattern);
}

/**
 * @tc.name: InsertText001
 * @tc.desc: Test insert Text Field
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, InsertText001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    const std::string default_text = "X";
    textChangedListenerImpl_->InsertText(to_utf16(default_text));
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: InsertText002
 * @tc.desc: Test to insert an empty text field
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, InsertText002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    std::string emptyString;
    textChangedListenerImpl_->InsertText(to_utf16(emptyString));
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteBackward001
 * @tc.desc: Test to delete 8 length text fields backward
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, DeleteBackward001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t length = 8;
    textChangedListenerImpl_->DeleteBackward(length);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteBackward002
 * @tc.desc: Test to delete a text field with illegal length backwards
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, DeleteBackward002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t errLength = -1;
    textChangedListenerImpl_->DeleteBackward(errLength);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteForward001
 * @tc.desc: Test to delete a text field with a length of 8 forward
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, DeleteForward001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t length = 8;
    textChangedListenerImpl_->DeleteForward(length);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: DeleteForward002
 * @tc.desc: Test to delete the text field with illegal length forward
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, DeleteForward002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    int32_t errLength = -1;
    textChangedListenerImpl_->DeleteForward(errLength);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: SetKeyboardStatus001
 * @tc.desc: test set KeyboardStatus
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, SetKeyboardStatus001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->SetKeyboardStatus(true);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: SendKeyboardInfo001
 * @tc.desc: Test the valid FunctionKey parameter of send
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, SendKeyboardInfo001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    MiscServices::KeyboardInfo info;
    int32_t index = 1;
    info.SetFunctionKey(index);
    textChangedListenerImpl_->SendKeyboardInfo(info);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: SendKeyboardInfo002
 * @tc.desc: Test the invalid FunctionKey parameter of send
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, SendKeyboardInfo002, TestSize.Level2)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    MiscServices::KeyboardInfo info;
    int32_t index = -1;
    info.SetFunctionKey(index);
    textChangedListenerImpl_->SendKeyboardInfo(info);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor001
 * @tc.desc: Test moving the cursor up
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, MoveCursor001, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::UP);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor002
 * @tc.desc: Test moving the cursor up
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, MoveCursor002, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::DOWN);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor003
 * @tc.desc: Test moving the cursor left
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, MoveCursor003, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::LEFT);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}

/**
 * @tc.name: MoveCursor004
 * @tc.desc: Test moving the cursor right
 * @tc.type: FUNC
 */
HWTEST_F(OnTextChangedListenerImplTestNg, MoveCursor004, TestSize.Level1)
{
    if (!textChangedListenerImpl_) {
        EXPECT_TRUE(textChangedListenerImpl_);
        return;
    }
    textChangedListenerImpl_->MoveCursor(MiscServices::Direction::RIGHT);
    EXPECT_TRUE(textChangedListenerImpl_);
    EXPECT_TRUE(host_->GetPattern<TextFieldPattern>());
}
} // namespace OHOS::Ace::NG
