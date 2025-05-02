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

#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

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

/**
 * @tc.name: AdjustSelectedBlankLineWidth001
 * @tc.desc: Test TextFieldPattern AdjustSelectedBlankLineWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, AdjustSelectedBlankLineWidth001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();

    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = textFieldNode->GetAccessibilityProperty<AccessibilityProperty>();

    RectF rect;
    pattern->AdjustSelectedBlankLineWidth(rect);
    ASSERT_EQ(NearZero(rect.GetX()), true);
    ASSERT_EQ(NearZero(rect.GetY()), true);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate001
 * @tc.desc: Test TextFieldPattern GetGlyphPositionAtCoordinate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, GetGlyphPositionAtCoordinate001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto positionWithAffinity = pattern->GetGlyphPositionAtCoordinate(1, 1);
    EXPECT_EQ(positionWithAffinity.position_, 0);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility001
 * @tc.desc: Test TextFieldPattern UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, UpdateSelectionAndHandleVisibility001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateSelectionAndHandleVisibility();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateTextDragInfo001
 * @tc.desc: Test TextFieldPattern CreateTextDragInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, CreateTextDragInfo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dragInfo = pattern->CreateTextDragInfo();
    ASSERT_EQ(NearZero(dragInfo.maxSelectedWidth), true);
}

/**
 * @tc.name: UpdateTextFieldInfo001
 * @tc.desc: Test TextFieldPattern UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, UpdateTextFieldInfo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateTextFieldInfo();
    ASSERT_EQ(pattern->IsNeedProcessAutoFill(), true);
}

/**
 * @tc.name: ConvertTouchOffsetToTextOffset001
 * @tc.desc: Test TextFieldPattern ConvertTouchOffsetToTextOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, ConvertTouchOffsetToTextOffset001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset temp;
    auto ret = pattern->ConvertTouchOffsetToTextOffset(temp);
    ASSERT_EQ(NearZero(ret.GetX()), true);
    ASSERT_EQ(NearZero(ret.GetY()), true);
}

/**
 * @tc.name: ExpandDefaultResponseRegion001
 * @tc.desc: Test TextFieldPattern ExpandDefaultResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, ExpandDefaultResponseRegion001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    RectF rect;
    auto ret = pattern->ExpandDefaultResponseRegion(rect);
    ASSERT_EQ(NearZero(ret.GetX()), true);
    ASSERT_EQ(NearZero(ret.GetY()), false);
}

/**
 * @tc.name: CheckPreviewTextValidate001
 * @tc.desc: Test TextFieldPattern CheckPreviewTextValidate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, CheckPreviewTextValidate001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    const std::string previewValue = "hhh";
    PreviewRange range;
    range.Set(0, 1);
    auto ret = pattern->CheckPreviewTextValidate(previewValue, range);
    ASSERT_EQ(ret, 0);
}

/**
 * @tc.name: SetPreviewText001
 * @tc.desc: Test TextFieldPattern SetPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, SetPreviewText001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frameNode
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    const std::string previewValue = "hhh";
    PreviewRange range;
    range.Set(0, 1);
    auto ret = pattern->SetPreviewText(previewValue, range);
    ASSERT_EQ(ret, 0);
}

/**
 * @tc.name: ProcessThemePadding001
 * @tc.desc: test testInput text ProcessThemePadding
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestSeven, ProcessThemePadding001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    auto themePadding = pattern->IsUnderlineMode()
        ? pattern->GetUnderlinePadding(textFieldTheme, true, false) : textFieldTheme->GetPadding();
    ASSERT_EQ(themePadding.Left(), theme->GetPadding().Left());
}
}