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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
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
    textFieldPattern->unitNode_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
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
    textFieldPattern->lpxInfo_.lastLogicScale = 1.5f;
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
 * @tc.desc: Test OnUiMaterialParamUpdate with background color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnUiMaterialParamUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and pattern
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    /**
     * @tc.steps: step2. Create UiMaterialParam with background color
     */
    UiMaterialParam params;
    params.backgroundColor = Color::BLACK;

    /**
     * @tc.steps: step3. Call OnUiMaterialParamUpdate
     * @tc.expected: The paintProperty should be updated with background color
     */
    textFieldPattern->OnUiMaterialParamUpdate(params);

    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto defaultBGColor = Color::TRANSPARENT;
    auto bgColor = paintProperty->GetBackgroundColorValue(defaultBGColor);
    EXPECT_EQ(bgColor, Color::BLACK);
}

/**
 * @tc.name: HasFocus001
 * @tc.desc: Test HasFocus when focusHub is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HasFocus001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->HasFocus();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAttachInput001
 * @tc.desc: Test CheckAttachInput when context is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CheckAttachInput001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CheckAttachInput();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsTextArea001
 * @tc.desc: Test IsTextArea when not text area
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsTextArea001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsTextArea();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckSelectAreaVisible001
 * @tc.desc: Test CheckSelectAreaVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CheckSelectAreaVisible001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CheckSelectAreaVisible();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckBlurReason001
 * @tc.desc: Test CheckBlurReason when blurReason is WINDOW_BLUR
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CheckBlurReason001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->blurReason_ = BlurReason::WINDOW_BLUR;
    auto result = textFieldPattern->CheckBlurReason();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckBlurReason002
 * @tc.desc: Test CheckBlurReason when blurReason is FOCUS_SWITCH
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CheckBlurReason002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->blurReason_ = BlurReason::FOCUS_SWITCH;
    auto result = textFieldPattern->CheckBlurReason();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedCloseKeyboard001
 * @tc.desc: Test NeedCloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, NeedCloseKeyboard001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->isCustomKeyboardAttached_ = false;
    auto result = textFieldPattern->NeedCloseKeyboard();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedCloseKeyboard002
 * @tc.desc: Test NeedCloseKeyboard when custom keyboard attached
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, NeedCloseKeyboard002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->isCustomKeyboardAttached_ = true;
    textFieldPattern->customKeyboard_ =
        FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto result = textFieldPattern->NeedCloseKeyboard();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CanUndo001
 * @tc.desc: Test CanUndo when operationRecords is empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CanUndo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CanUndo();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasOperationRecords001
 * @tc.desc: Test HasOperationRecords when empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HasOperationRecords001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->HasOperationRecords();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasOperationRecords002
 * @tc.desc: Test HasOperationRecords when not empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HasOperationRecords002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->operationRecords_.push_back({ u"test", 0, 0 });
    auto result = textFieldPattern->HasOperationRecords();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CanRedo001
 * @tc.desc: Test CanRedo when redoOperationRecords is empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CanRedo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CanRedo();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CanRedo002
 * @tc.desc: Test CanRedo when redoOperationRecords is not empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CanRedo002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->redoOperationRecords_.push_back({ u"test", 0, 0 });
    auto result = textFieldPattern->CanRedo();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsShowTranslate001
 * @tc.desc: Test IsShowTranslate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsShowTranslate001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsShowTranslate();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowSearch001
 * @tc.desc: Test IsShowSearch
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsShowSearch001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsShowSearch();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAutoFill001
 * @tc.desc: Test IsShowAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsShowAutoFill001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsShowAutoFill();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsHandleDragging001
 * @tc.desc: Test IsHandleDragging
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsHandleDragging001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsHandleDragging();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetEditingBoxModel001
 * @tc.desc: Test GetEditingBoxModel
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, GetEditingBoxModel001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->GetEditingBoxModel();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CursorInContentRegion001
 * @tc.desc: Test CursorInContentRegion
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorInContentRegion001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentRect_ = RectF(0, 0, 100, 100);
    auto result = textFieldPattern->CursorInContentRegion();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OffsetInContentRegion001
 * @tc.desc: Test OffsetInContentRegion
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OffsetInContentRegion001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentRect_ = RectF(0, 0, 100, 100);
    Offset offset(50, 50);
    auto result = textFieldPattern->OffsetInContentRegion(offset);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OffsetInContentRegion002
 * @tc.desc: Test OffsetInContentRegion when outside
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OffsetInContentRegion002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentRect_ = RectF(0, 0, 100, 100);
    Offset offset(150, 150);
    auto result = textFieldPattern->OffsetInContentRegion(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetSelectDetectEnable001
 * @tc.desc: Test GetSelectDetectEnable
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, GetSelectDetectEnable001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->GetSelectDetectEnable();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AllowCopy001
 * @tc.desc: Test AllowCopy when copy options is None
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, AllowCopy001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    auto result = textFieldPattern->AllowCopy();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AllowCopy002
 * @tc.desc: Test AllowCopy when copy options is Local
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, AllowCopy002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    auto result = textFieldPattern->AllowCopy();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsDisabled001
 * @tc.desc: Test IsDisabled when not disabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsDisabled001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsDisabled();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsDisabled002
 * @tc.desc: Test IsDisabled when disabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsDisabled002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    eventHub->SetEnabled(false);
    auto result = textFieldPattern->IsDisabled();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsInPasswordMode001
 * @tc.desc: Test IsInPasswordMode when not password mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsInPasswordMode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    auto result = textFieldPattern->IsInPasswordMode();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsInPasswordMode002
 * @tc.desc: Test IsInPasswordMode when password mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsInPasswordMode002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    auto result = textFieldPattern->IsInPasswordMode();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsNormalInlineState001
 * @tc.desc: Test IsNormalInlineState when not inline
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsNormalInlineState001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsNormalInlineState();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsUnspecifiedOrTextType001
 * @tc.desc: Test IsUnspecifiedOrTextType when TEXT type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsUnspecifiedOrTextType001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    auto result = textFieldPattern->IsUnspecifiedOrTextType();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsUnspecifiedOrTextType002
 * @tc.desc: Test IsUnspecifiedOrTextType when NUMBER type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsUnspecifiedOrTextType002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    auto result = textFieldPattern->IsUnspecifiedOrTextType();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsStyledPlaceholder001
 * @tc.desc: Test IsStyledPlaceholder when not styled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsStyledPlaceholder001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsStyledPlaceholder();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAutoSave001
 * @tc.desc: Test CheckAutoSave
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CheckAutoSave001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    auto result = textFieldPattern->CheckAutoSave();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsTouchAtLeftOffset001
 * @tc.desc: Test IsTouchAtLeftOffset when at left offset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsTouchAtLeftOffset001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->textRect_ = RectF(0, 0, 100, 100);
    auto result = textFieldPattern->IsTouchAtLeftOffset(5.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsReachedBoundary001
 * @tc.desc: Test IsReachedBoundary when at left boundary
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsReachedBoundary001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->textRect_ = RectF(0, 0, 100, 100);
    textFieldPattern->contentRect_ = RectF(0, 0, 50, 100);
    auto result = textFieldPattern->IsReachedBoundary(-10.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetErrorTextState001
 * @tc.desc: Test GetErrorTextState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, GetErrorTextState001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->GetErrorTextState();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsAccessibilityClick001
 * @tc.desc: Test IsAccessibilityClick
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsAccessibilityClick001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsAccessibilityClick();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsOnUnitByPosition001
 * @tc.desc: Test IsOnUnitByPosition when not on unit
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsOnUnitByPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    Offset offset(50, 50);
    auto result = textFieldPattern->IsOnUnitByPosition(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsOnPasswordByPosition001
 * @tc.desc: Test IsOnPasswordByPosition when not on password
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsOnPasswordByPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    Offset offset(50, 50);
    auto result = textFieldPattern->IsOnPasswordByPosition(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsOnCleanNodeByPosition001
 * @tc.desc: Test IsOnCleanNodeByPosition when not on clean node
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsOnCleanNodeByPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    Offset offset(50, 50);
    auto result = textFieldPattern->IsOnCleanNodeByPosition(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsModalCovered001
 * @tc.desc: Test IsModalCovered
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsModalCovered001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsModalCovered();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedSetScrollRect001
 * @tc.desc: Test NeedSetScrollRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, NeedSetScrollRect001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->NeedSetScrollRect();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ParseCommand001
 * @tc.desc: Test ParseCommand with unknown command
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, ParseCommand001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    std::string command = "unknown_command";
    auto result = textFieldPattern->ParseCommand(command);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckMousePressedOverScrollBar001
 * @tc.desc: Test CheckMousePressedOverScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CheckMousePressedOverScrollBar001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    GestureEvent info;
    auto result = textFieldPattern->CheckMousePressedOverScrollBar(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BetweenSelectedPosition001
 * @tc.desc: Test BetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, BetweenSelectedPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    GestureEvent info;
    textFieldPattern->contentController_->SetTextValue(u"hello");
    textFieldPattern->selectController_->UpdateHandleIndex(1, 3);
    auto result = textFieldPattern->BetweenSelectedPosition(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CanChangeSelectState001
 * @tc.desc: Test CanChangeSelectState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CanChangeSelectState001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CanChangeSelectState();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnBackPressed001
 * @tc.desc: Test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnBackPressed001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->OnBackPressed();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsStopBackPress001
 * @tc.desc: Test IsStopBackPress
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsStopBackPress001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsStopBackPress();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsShowMenu001
 * @tc.desc: Test IsShowMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsShowMenu001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->IsShowMenu(std::nullopt, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Test OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnThemeScopeUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->OnThemeScopeUpdate(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BeforeIMEInsertValue001
 * @tc.desc: Test BeforeIMEInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, BeforeIMEInsertValue001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    std::u16string insertValue = u"test";
    int32_t offset = 0;
    auto result = textFieldPattern->BeforeIMEInsertValue(insertValue, offset);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FinishTextPreviewByPreview001
 * @tc.desc: Test FinishTextPreviewByPreview
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, FinishTextPreviewByPreview001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    std::u16string insertValue = u"test";
    auto result = textFieldPattern->FinishTextPreviewByPreview(insertValue);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CharLineChanged001
 * @tc.desc: Test CharLineChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CharLineChanged001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    auto result = textFieldPattern->CharLineChanged(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CursorMoveLeftOperation001
 * @tc.desc: Test CursorMoveLeftOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveLeftOperation001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveLeftOperation();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveRightOperation001
 * @tc.desc: Test CursorMoveRightOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveRightOperation001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveRightOperation();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveLeft001
 * @tc.desc: Test CursorMoveLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveLeft001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveLeft();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveRight001
 * @tc.desc: Test CursorMoveRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveRight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveRight();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveHome001
 * @tc.desc: Test CursorMoveHome
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveHome001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveHome();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveEnd001
 * @tc.desc: Test CursorMoveEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveEnd();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveUpOperation001
 * @tc.desc: Test CursorMoveUpOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveUpOperation001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test\ntest");
    textFieldPattern->selectController_->UpdateCaretIndex(5);
    auto result = textFieldPattern->CursorMoveUpOperation();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveDownOperation001
 * @tc.desc: Test CursorMoveDownOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveDownOperation001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test\ntest");
    textFieldPattern->selectController_->UpdateCaretIndex(5);
    auto result = textFieldPattern->CursorMoveDownOperation();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveLineBegin001
 * @tc.desc: Test CursorMoveLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveLineBegin001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveLineBegin();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CursorMoveLineEnd001
 * @tc.desc: Test CursorMoveLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CursorMoveLineEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    textFieldPattern->selectController_->UpdateCaretIndex(2);
    auto result = textFieldPattern->CursorMoveLineEnd();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetCaretOffset001
 * @tc.desc: Test SetCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, SetCaretOffset001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    auto result = textFieldPattern->SetCaretOffset(2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HasStateStyle001
 * @tc.desc: Test HasStateStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HasStateStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    UIState normalState = UI_STATE_NORMAL;
    auto result = textFieldPattern->HasStateStyle(normalState);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckIfNeedAvoidOnCaretChange001
 * @tc.desc: Test CheckIfNeedAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CheckIfNeedAvoidOnCaretChange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CheckIfNeedAvoidOnCaretChange(50.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FireOnTextChangeEvent001
 * @tc.desc: Test FireOnTextChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, FireOnTextChangeEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    auto result = textFieldPattern->FireOnTextChangeEvent();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResetObscureTickCountDown001
 * @tc.desc: Test ResetObscureTickCountDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, ResetObscureTickCountDown001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->ResetObscureTickCountDown();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleBetweenSelectedPosition001
 * @tc.desc: Test HandleBetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HandleBetweenSelectedPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    GestureEvent info;
    auto result = textFieldPattern->HandleBetweenSelectedPosition(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RequestKeyboard001
 * @tc.desc: Test RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, RequestKeyboard001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    textFieldPattern->contentController_->SetTextValue(u"test");
    auto result = textFieldPattern->RequestKeyboard(true, false, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CloseKeyboard001
 * @tc.desc: Test CloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CloseKeyboard001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CloseKeyboard(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CloseKeyboard002
 * @tc.desc: Test CloseKeyboard with force close
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CloseKeyboard002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CloseKeyboard(true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: RequestCustomKeyboard001
 * @tc.desc: Test RequestCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, RequestCustomKeyboard001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->RequestCustomKeyboard();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CloseCustomKeyboard001
 * @tc.desc: Test CloseCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, CloseCustomKeyboard001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->CloseCustomKeyboard();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldRequestFocus001
 * @tc.desc: Test TextFieldRequestFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, TextFieldRequestFocus001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->TextFieldRequestFocus(RequestFocusReason::UNKNOWN);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: RequestKeyboardNotByFocusSwitch001
 * @tc.desc: Test RequestKeyboardNotByFocusSwitch
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, RequestKeyboardNotByFocusSwitch001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::UNKNOWN, SourceType::NONE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleEditingEventCrossPlatform001
 * @tc.desc: Test HandleEditingEventCrossPlatform
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HandleEditingEventCrossPlatform001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto value = std::make_shared<TextEditingValue>();
    value->text = "test";
    auto result = textFieldPattern->HandleEditingEventCrossPlatform(value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InitValueText001
 * @tc.desc: Test InitValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, InitValueText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    std::u16string content = u"test";
    auto result = textFieldPattern->InitValueText(content);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ProcessFocusIndexAction001
 * @tc.desc: Test ProcessFocusIndexAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, ProcessFocusIndexAction001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->ProcessFocusIndexAction();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MaybeNeedShowSelectAIDetect001
 * @tc.desc: Test MaybeNeedShowSelectAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, MaybeNeedShowSelectAIDetect001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->MaybeNeedShowSelectAIDetect();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, OnScrollCallback001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->OnScrollCallback(10.0f, 0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsMoveFocusOutFromLeft001
 * @tc.desc: Test IsMoveFocusOutFromLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsMoveFocusOutFromLeft001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_LEFT;
    auto result = textFieldPattern->IsMoveFocusOutFromLeft(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsMoveFocusOutFromRight001
 * @tc.desc: Test IsMoveFocusOutFromRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, IsMoveFocusOutFromRight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    auto result = textFieldPattern->IsMoveFocusOutFromRight(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleOnEscape001
 * @tc.desc: Test HandleOnEscape
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HandleOnEscape001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->HandleOnEscape();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleOnTab001
 * @tc.desc: Test HandleOnTab backward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, HandleOnTab001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXTINPUT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    auto result = textFieldPattern->HandleOnTab(true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetBackBorderRadius001
 * @tc.desc: Test SetBackBorderRadius with LTR layout and default radius
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, SetBackBorderRadius001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node with LTR layout
     * @tc.expected: BorderRadiusFlagByUser should be set
     */
    CreateTextField("", "");

    /**
     * @tc.steps: step2. Set border radius with default value
     */
    pattern_->SetBackBorderRadius();

    /**
     * @tc.steps: step3. Verify border radius is set correctly
     * @tc.expected: BorderRadiusFlagByUser should be set to true
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasBorderRadiusFlagByUser());
}

/**
 * @tc.name: SetBackBorderRadius002
 * @tc.desc: Test SetBackBorderRadius with RTL layout
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, SetBackBorderRadius002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node with RTL layout
     * @tc.expected: Border radius should be mirrored correctly in RTL layout
     */
    CreateTextField("", "");

    /**
     * @tc.steps: step2. Set layout direction to RTL
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);

    /**
     * @tc.steps: step3. Set border radius in RTL layout
     */
    pattern_->SetBackBorderRadius();

    /**
     * @tc.steps: step4. Verify border radius is set correctly in RTL layout
     * @tc.expected: BorderRadiusFlagByUser should be set to true
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasBorderRadiusFlagByUser());
}

/**
 * @tc.name: SetBackBorderRadius003
 * @tc.desc: Test SetBackBorderRadius when border radius already set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, SetBackBorderRadius003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node
     * @tc.expected: BorderRadiusFlagByUser should already be set (already set)
     */
    CreateTextField("", "");

    /**
     * @tc.steps: step2. Set border radius
     */
    pattern_->SetBackBorderRadius();

    /**
     * @tc.steps: step3. Verify border radius flag is set
     * @tc.expected: BorderRadiusFlagByUser should be set to true (already set)
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasBorderRadiusFlagByUser());
}

/**
 * @tc.name: UpdateBorderResource001
 * @tc.desc: Test UpdateBorderResource with border radius enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, UpdateBorderResource001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and set border radius
     */
    CreateTextField("", "");
    FlushLayoutTask(frameNode_);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(5.0, DimensionUnit::VP));
    TextFieldModelNG::SetBorderRadius(AceType::RawPtr(frameNode_), borderRadius);

    /**
     * @tc.steps: step2. Call UpdateBorderResource and verify
     * @tc.expected: BorderRadiusFlagByUser should be set
     */
    pattern_->UpdateBorderResource();

    /**
     * @tc.steps: step3. Verify results
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasBorderRadiusFlagByUser());
}

/**
 * @tc.name: UpdateBorderResource002
 * @tc.desc: Test UpdateBorderResource with HasBorderRadius and HasBorderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, UpdateBorderResource002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and set border radius
     */
    CreateTextField("", "");
    FlushLayoutTask(frameNode_);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(5.0, DimensionUnit::VP));
    TextFieldModelNG::SetBorderRadius(AceType::RawPtr(frameNode_), borderRadius);

    /**
     * @tc.steps: step2. Set border color
     */
    BorderColorProperty borderColors;
    borderColors.leftColor = Color::RED;
    borderColors.rightColor = Color::RED;
    borderColors.topColor = Color::RED;
    borderColors.bottomColor = Color::RED;
    TextFieldModelNG::SetBorderColor(AceType::RawPtr(frameNode_), borderColors);

    /**
     * @tc.steps: step3. Call UpdateBorderResource and verify
     * @tc.expected: BorderColorFlagByUser should be set
     */
    pattern_->UpdateBorderResource();

    /**
     * @tc.steps: step4. Verify results
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasBorderRadiusFlagByUser());
    EXPECT_TRUE(paintProperty->HasBorderColorFlagByUser());
}

/**
 * @tc.name: UpdateBorderResource003
 * @tc.desc: Test UpdateBorderResource with HasBorderRadius, HasBorderColor and HasBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, UpdateBorderResource003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node and set border radius
     */
    CreateTextField("", "");
    FlushLayoutTask(frameNode_);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(5.0, DimensionUnit::VP));
    TextFieldModelNG::SetBorderRadius(AceType::RawPtr(frameNode_), borderRadius);

    /**
     * @tc.steps: step2. Set border color
     */
    BorderColorProperty borderColors;
    borderColors.leftColor = Color::RED;
    borderColors.rightColor = Color::RED;
    borderColors.topColor = Color::RED;
    borderColors.bottomColor = Color::RED;
    TextFieldModelNG::SetBorderColor(AceType::RawPtr(frameNode_), borderColors);

    /**
     * @tc.steps: step3. Set border width
     */
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(10.0, DimensionUnit::VP));
    TextFieldModelNG::SetBorderWidth(AceType::RawPtr(frameNode_), borderWidth);

    /**
     * @tc.steps: step4. Call UpdateBorderResource and verify
     * @tc.expected: All border property flags should be set
     */
    pattern_->UpdateBorderResource();

    /**
     * @tc.steps: step5. Verify results
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasBorderRadiusFlagByUser());
    EXPECT_TRUE(paintProperty->HasBorderColorFlagByUser());
    EXPECT_TRUE(paintProperty->HasBorderWidthFlagByUser());
}

/**
 * @tc.name: UpdateMarginResource001
 * @tc.desc: Test UpdateMarginResource with LTR layout
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, UpdateMarginResource001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node with LTR layout
     * @tc.expected: MarginByUser should be set
     */
    CreateTextField("", "");
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Set user margin in layout property
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    margin.top = CalcLength(10.0, DimensionUnit::VP);
    margin.bottom = CalcLength(5.0, DimensionUnit::VP);
    margin.left = CalcLength(3.0, DimensionUnit::VP);
    margin.right = CalcLength(3.0, DimensionUnit::VP);
    layoutProperty->UpdateMargin(margin);

    /**
     * @tc.steps: step3. Call UpdateMarginResource
     * @tc.expected: MarginByUser should be set
     */
    pattern_->UpdateMarginResource();

    /**
     * @tc.steps: step4. Verify results
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasMarginByUser());
}

/**
 * @tc.name: UpdateMarginResource002
 * @tc.desc: Test UpdateMarginResource with RTL layout
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, UpdateMarginResource002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node with RTL layout
     * @tc.expected: Margin should be mirrored correctly for RTL
     */
    CreateTextField("", "");
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Set layout direction to RTL
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);

    /**
     * @tc.steps: step3. Set user margin with start/end values
     */
    MarginProperty margin;
    margin.top = CalcLength(10.0, DimensionUnit::VP);
    margin.bottom = CalcLength(5.0, DimensionUnit::VP);
    margin.start = CalcLength(3.0, DimensionUnit::VP);
    margin.end = CalcLength(5.0, DimensionUnit::VP);
    layoutProperty->UpdateMargin(margin);

    /**
     * @tc.steps: step4. Call UpdateMarginResource
     * @tc.expected: MarginByUser should be set
     */
    pattern_->UpdateMarginResource();

    /**
     * @tc.steps: step5. Verify results
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasMarginByUser());
}

/**
 * @tc.name: UpdateMarginResource003
 * @tc.desc: Test UpdateMarginResource with existing user margin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTesteleven, UpdateMarginResource003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField node
     * @tc.expected: MarginByUser should be set
     */
    CreateTextField("", "");
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Set user margin
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    margin.top = CalcLength(8.0, DimensionUnit::VP);
    margin.bottom = CalcLength(12.0, DimensionUnit::VP);
    margin.left = CalcLength(4.0, DimensionUnit::VP);
    margin.right = CalcLength(16.0, DimensionUnit::VP);
    layoutProperty->UpdateMargin(margin);

    /**
     * @tc.steps: step3. Call UpdateMarginResource
     * @tc.expected: MarginByUser should be set
     */
    pattern_->UpdateMarginResource();

    /**
     * @tc.steps: step4. Verify results
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_TRUE(paintProperty->HasMarginByUser());
}
} // namespace OHOS::Ace::NG
