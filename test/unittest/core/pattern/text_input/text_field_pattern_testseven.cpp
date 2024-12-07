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

#include <memory>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/mock/base/mock_task_executor.h"
#include "text_input_base.h"

#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestSeven : public TextInputBases {
public:
};

/**
 * @tc.name: ResetPreviewTextState001
 * @tc.desc: test testInput text ResetPreviewTextState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, ResetPreviewTextState001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->hasPreviewText_ = true;
    pattern->ResetPreviewTextState();
    EXPECT_TRUE(textFieldNode->isLayoutDirtyMarked_);
}

/**
 * @tc.name: UpdateSelectionByLongPress001
 * @tc.desc: test testInput text UpdateSelectionByLongPress
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, UpdateSelectionByLongPress001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentController_->Reset();

    Offset offset(1.0, 1.0);
    pattern->magnifierController_->magnifierNodeExist_ = false;
    pattern->UpdateSelectionByLongPress(1, 1, offset);
    EXPECT_FALSE(pattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: UpdateSelectionByLongPress002
 * @tc.desc: test testInput text UpdateSelectionByLongPress
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, UpdateSelectionByLongPress002, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset offset(1.0, 1.0);
    pattern->longPressFingerNum_ = 0;
    pattern->magnifierController_->magnifierNodeExist_ = false;
    pattern->UpdateSelectionByLongPress(1, 1, offset);
    EXPECT_FALSE(pattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: SetAccessibilityUnitAction001
 * @tc.desc: test testInput text SetAccessibilityUnitAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, SetAccessibilityUnitAction001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = textFieldNode->GetAccessibilityProperty<AccessibilityProperty>();

    pattern->unitNode_ = nullptr;
    pattern->responseArea_ = nullptr;
    pattern->SetAccessibilityUnitAction();
    EXPECT_FALSE(accessibilityProperty->accessibilityLevel_.has_value());
}

/**
 * @tc.name: SetAccessibilityUnitAction002
 * @tc.desc: test testInput text SetAccessibilityUnitAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, SetAccessibilityUnitAction002, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = textFieldNode->GetAccessibilityProperty<AccessibilityProperty>();

    pattern->unitNode_ = nullptr;
    auto unitResponseArea =
        AceType::MakeRefPtr<UnitResponseArea>(AceType::WeakClaim(AceType::RawPtr(pattern)), textFieldNode);
    ASSERT_NE(unitResponseArea, nullptr);
    pattern->responseArea_ = std::move(unitResponseArea);
    pattern->SetAccessibilityUnitAction();
    EXPECT_FALSE(accessibilityProperty->accessibilityLevel_.has_value());
}
}