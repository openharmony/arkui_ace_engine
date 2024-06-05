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

class TextFieldAlgorithmTest : public TextInputBases {
public:
};

/**
 * @tc.name: IsAdaptExceedLimit
 * @tc.desc: Test the function IsAdaptExceedLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, IsAdaptExceedLimit, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    SizeF size(50.0f, 460.0f);
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_FALSE(textInputLayoutAlgorithm->IsAdaptExceedLimit(size));
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak001
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), TextOverflow::CLIP);

    layoutProperty_->UpdateTextOverflow(OVERFLOW_ELLIPSIS);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), OVERFLOW_ELLIPSIS);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak002
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_ELLIPSIS);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), TextOverflow::CLIP);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak003
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_MARQUEE);
    layoutProperty_->UpdateWordBreak(WORDBREAK_ALL);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetWordBreak(), WORDBREAK_ALL);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak004
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_MARQUEE);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, false, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), OVERFLOW_ELLIPSIS);
}

/**
 * @tc.name: UpdateCounterNode
 * @tc.desc: Test the function UpdateCounterNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateCounterNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutProperty_->UpdateTextAlign(TextAlign::END);
    textInputLayoutAlgorithm->UpdateCounterNode(50, 460, layoutConstraint, &layoutWrapper);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::END);
}

/**
 * @tc.name: CounterLayout001
 * @tc.desc: Test the function CounterLayout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    layoutWrapper.GetGeometryNode()->SetContentSize({ 40.0f, 40.0f });

    textInputLayoutAlgorithm->CounterLayout(&layoutWrapper);
    EXPECT_FALSE(pattern_->IsTextArea());
}

/**
 * @tc.name: CounterLayout002
 * @tc.desc: Test the function CounterLayout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(false);
    });
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);

    textInputLayoutAlgorithm->CounterLayout(&layoutWrapper);
    EXPECT_FALSE(pattern_->IsTextArea());
}

/**
 * @tc.name: CounterLayout003
 * @tc.desc: Test the function CounterLayout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(false);
    });
    pattern_->AddCounterNode();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    layoutWrapper.GetGeometryNode()->SetContentSize({ 40.0f, 40.0f });

    textInputLayoutAlgorithm->CounterLayout(&layoutWrapper);
    EXPECT_FALSE(pattern_->IsTextArea());
}

/**
 * @tc.name: CounterNodeMeasure
 * @tc.desc: Test the function CounterNodeMeasure.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterNodeMeasure, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounterBorder(true);
        model.SetShowPasswordIcon(false);
    });
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    EXPECT_EQ(textInputLayoutAlgorithm->CounterNodeMeasure(1.0f, &layoutWrapper), 0.0);
}

/**
 * @tc.name: CreateParagraph001
 * @tc.desc: Test the function CreateParagraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CreateParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    std::vector<std::string> strVec = { "0", "1", "2" };
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_ELLIPSIS);
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, "content", true, true);
}

/**
 * @tc.name: CreateParagraph002
 * @tc.desc: Test the function CreateParagraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CreateParagraph002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    std::vector<std::string> strVec = { "0", "1", "2" };
    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::LEFT);
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, "content", false, false);
    EXPECT_NE(textInputLayoutAlgorithm->paragraph_, nullptr);
}
} // namespace OHOS::Ace::NG
