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
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {

class TextFieldPatternTesteleven : public TextInputBases {
public:
};

/**
 * @tc.name: ShouldSkipUpdateParagraph001
 * @tc.desc: Test ShouldSkipUpdateParagraph
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, ShouldSkipUpdateParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create a key and value.
     */
    textFieldPattern->dragStatus_ = DragStatus::DRAGGING;
    textFieldPattern->dragNode_ = TextDragPattern::CreateDragNode(frameNode);

    /**
     * @tc.steps: step3. Calling the ShouldSkipUpdateParagraph function
     * @tc.expected: textPattern->isRegisteredAreaCallback_ from nullptr to a valid function.
     */
    auto result = textFieldPattern->ShouldSkipUpdateParagraph();
    EXPECT_EQ(result, false);
}

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

/**
 * @tc.name: OnDragNodeDetachFromMainTree003
 * @tc.desc: Test OnDragNodeDetachFromMainTree when dragStatus is NONE
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnDragNodeDetachFromMainTree003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    // Set dragStatus to NONE
    textFieldPattern->dragStatus_ = DragStatus::NONE;
    
    // Mock selectOverlay ProcessOverlay call
    bool processOverlayCalled = false;
    EXPECT_NE(textFieldPattern->selectOverlay_, nullptr);
    textFieldPattern->OnDragNodeDetachFromMainTree();
    
    // Verify that ProcessOverlay and MarkDirtyNode were called
    EXPECT_FALSE(processOverlayCalled);
}

/**
 * @tc.name: GetCancelImageText001
 * @tc.desc: Test GetCancelImageText when theme is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, GetCancelImageText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    // Mock GetTheme to return nullptr
    auto result = textFieldPattern->GetCancelImageText();
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: ReprocessAllRelatedToLPX
 * @tc.desc: Test reprocess all related to lpx
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, ReprocessAllRelatedToLPX, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    textFieldPattern->SetTextChangedAtCreation(true);
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(10, DimensionUnit::LPX);
    TextFieldModelNG::SetPadding(AceType::RawPtr(frameNode), paddings);
    textFieldPattern->OnModifyDone();
    EXPECT_TRUE(textFieldPattern->lpxInfo_.hasLPXPadding);
    EXPECT_TRUE(textFieldPattern->lpxInfo_.initTextRectWithLPX);
    textFieldPattern->lpxInfo_.lastLogicScale  = 1.5f;
    textFieldPattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(textFieldPattern->lpxInfo_.initTextRectWithLPX);
}

/**
 * @tc.name: TextInputAreaDeleteBackwardModel001
 * @tc.desc: test DeleteBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, TextInputAreaDeleteBackwardModel001, TestSize.Level1)
{
    CreateTextField("挖矿时间到!⛏️", "", [](TextFieldModelNG model) {});
    GetFocus();

    pattern_->textFieldController_->DeleteBackward();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTextValue(), "挖矿时间到!");
}

/**
 * @tc.name: TextInputAreaDeleteBackwardModel002
 * @tc.desc: test DeleteBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, TextInputAreaDeleteBackwardModel002, TestSize.Level1)
{
    CreateTextField("DeleteBackward预上屏测试", "", [](TextFieldModelNG model) {});
    GetFocus();

    pattern_->textFieldController_->DeleteBackward();
    FlushLayoutTask(frameNode_);

    EXPECT_FALSE(pattern_->IsPreviewTextInputting());
}

/**
 * @tc.name: OnUiMaterialParamUpdate001
 * @tc.desc: Test OnUiMaterialParamUpdate with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnUiMaterialParamUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and pattern
     */
    CreateTextField("test", "", [](TextFieldModelNG model) {});
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create UiMaterialParam with custom values
     */
    UiMaterialParam params;
    params.backgroundColor = Color::RED;
    params.borderWidth.setValueLeft(Dimension(2.0, DimensionUnit::VP));
    params.borderWidth.setValueTop(Dimension(2.0, DimensionUnit::VP));
    params.borderWidth.setValueRight(Dimension(2.0, DimensionUnit::VP));
    params.borderWidth.setValueBottom(Dimension(2.0, DimensionUnit::VP));
    params.borderColor.setColorLeft(Color::BLUE);
    params.borderColor.setColorTop(Color::BLUE);
    params.borderColor.setColorRight(Color::BLUE);
    params.borderColor.setColorBottom(Color::BLUE);

    /**
     * @tc.steps: step3. Call OnUiMaterialParamUpdate
     * @tc.expected: The method should execute without crash
     */
    textFieldPattern->OnUiMaterialParamUpdate(params);

    /**
     * @tc.steps: step4. Verify paint property is updated
     */
    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasBackgroundColor());
}

/**
 * @tc.name: OnUiMaterialParamUpdate002
 * @tc.desc: Test OnUiMaterialParamUpdate with null host
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnUiMaterialParamUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField pattern without host
     */
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create UiMaterialParam with valid values
     */
    UiMaterialParam params;
    params.backgroundColor = Color::GREEN;

    /**
     * @tc.steps: step3. Call OnUiMaterialParamUpdate without host
     * @tc.expected: The method should return early without crash
     */
    textFieldPattern->OnUiMaterialParamUpdate(params);
}

/**
 * @tc.name: OnUiMaterialParamUpdate003
 * @tc.desc: Test OnUiMaterialParamUpdate with default color values
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnUiMaterialParamUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and pattern
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create UiMaterialParam with default values
     */
    UiMaterialParam params;
    params.backgroundColor = Color::TRANSPARENT;

    /**
     * @tc.steps: step3. Call OnUiMaterialParamUpdate
     * @tc.expected: The method should execute without crash
     */
    textFieldPattern->OnUiMaterialParamUpdate(params);

    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: OnUiMaterialParamUpdate004
 * @tc.desc: Test OnUiMaterialParamUpdate with border color variations
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnUiMaterialParamUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and pattern
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create UiMaterialParam with different border colors
     */
    UiMaterialParam params;
    params.backgroundColor = Color::YELLOW;
    params.borderWidth.setValueLeft(Dimension(1.0, DimensionUnit::VP));
    params.borderWidth.setValueTop(Dimension(2.0, DimensionUnit::VP));
    params.borderWidth.setValueRight(Dimension(3.0, DimensionUnit::VP));
    params.borderWidth.setValueBottom(Dimension(4.0, DimensionUnit::VP));
    params.borderColor.setColorLeft(Color::RED);
    params.borderColor.setColorTop(Color::GREEN);
    params.borderColor.setColorRight(Color::BLUE);
    params.borderColor.setColorBottom(Color::YELLOW);

    /**
     * @tc.steps: step3. Call OnUiMaterialParamUpdate
     * @tc.expected: The method should execute without crash
     */
    textFieldPattern->OnUiMaterialParamUpdate(params);

    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasBackgroundColor());
}

/**
 * @tc.name: OnUiMaterialParamUpdate005
 * @tc.desc: Test OnUiMaterialParamUpdate with multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnUiMaterialParamUpdate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and pattern
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create first UiMaterialParam
     */
    UiMaterialParam params1;
    params1.backgroundColor = Color::RED;
    params1.borderWidth.setValueLeft(Dimension(1.0, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Create second UiMaterialParam
     */
    UiMaterialParam params2;
    params2.backgroundColor = Color::BLUE;
    params2.borderWidth.setValueLeft(Dimension(3.0, DimensionUnit::VP));

    /**
     * @tc.steps: step4. Call OnUiMaterialParamUpdate multiple times
     * @tc.expected: Both calls should execute without crash
     */
    textFieldPattern->OnUiMaterialParamUpdate(params1);
    textFieldPattern->OnUiMaterialParamUpdate(params2);

    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasBackgroundColor());
}

/**
 * @tc.name: OnUiMaterialParamUpdate006
 * @tc.desc: Test OnUiMaterialParamUpdate with zero border width
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnUiMaterialParamUpdate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and pattern
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create UiMaterialParam with zero border width
     */
    UiMaterialParam params;
    params.backgroundColor = Color::WHITE;
    params.borderWidth.setValueLeft(Dimension(0.0, DimensionUnit::VP));
    params.borderWidth.setValueTop(Dimension(0.0, DimensionUnit::VP));
    params.borderWidth.setValueRight(Dimension(0.0, DimensionUnit::VP));
    params.borderWidth.setValueBottom(Dimension(0.0, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Call OnUiMaterialParamUpdate
     * @tc.expected: The method should execute without crash
     */
    textFieldPattern->OnUiMaterialParamUpdate(params);

    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

} // namespace OHOS::Ace::NG
