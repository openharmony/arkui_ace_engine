/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {

class TextFieldPatternTesteleven : public TextInputBases {
public:
};

/**
 * @tc.name: GetIndependentControlKeyboard001
 * @tc.desc: Test GetIndependentControlKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, GetIndependentControlKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step3. Calling the GetIndependentControlKeyboard function
     * @tc.expected: textPattern->isRegisteredAreaCallback_ from nullptr to a valid function.
     */
    auto result = textFieldPattern->GetIndependentControlKeyboard();
    EXPECT_NE(result, true);
}

/**
 * @tc.name: SetAccessibilityUnitAction002
 * @tc.desc: Test SetAccessibilityUnitAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, SetAccessibilityUnitAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create a unitNode_ and responseArea_.
     */
    textFieldPattern->unitNode_ =  AceType::DynamicCast<NG::UINode>(
        AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(textFieldPattern->unitNode_, nullptr);
    textFieldPattern->responseArea_ =
        AceType::MakeRefPtr<PasswordResponseArea>(textFieldPattern, textFieldPattern->GetTextObscured());
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);

    /**
     * @tc.steps: step3. Calling the SetAccessibilityUnitAction function
     * @tc.expected: textPattern->isRegisteredAreaCallback_ from nullptr to a valid function.
     */
    textFieldPattern->SetAccessibilityUnitAction();
    EXPECT_NE(textFieldPattern->unitNode_->GetAccessibilityId(), true);
}
} // namespace OHOS::Ace::NG
