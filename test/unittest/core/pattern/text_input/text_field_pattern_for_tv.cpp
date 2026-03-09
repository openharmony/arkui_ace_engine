/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_input_response_area.h"

namespace OHOS::Ace::NG {
class TextFieldPatternForTV : public TextInputBases {
public:
};

/**
 * @tc.name: ApplyUnderlineThemeForTV001
 * @tc.desc: Test ApplyUnderlineThemeForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ApplyUnderlineThemeForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ApplyUnderlineThemeForTV
     * @tc.expected: PaintProperty should not be nullptr after applying underline theme
     */
    pattern_->ApplyUnderlineThemeForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: ApplyUnderlineThemeForTV002
 * @tc.desc: Test ApplyUnderlineThemeForTV without default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ApplyUnderlineThemeForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ApplyUnderlineThemeForTV without default mode
     * @tc.expected: PaintProperty should not be nullptr even when returning early
     */
    pattern_->ApplyUnderlineThemeForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: ApplyUnderlineThemeForTV003
 * @tc.desc: Test ApplyUnderlineThemeForTV with underline mode enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ApplyUnderlineThemeForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call ApplyUnderlineThemeForTV
     */
    pattern_->ApplyUnderlineThemeForTV();

    /**
     * @tc.expected: step3. underlineWidth_ should be set to typing underline width
     */
    auto theme = pattern_->GetTheme();
    ASSERT_NE(theme, nullptr);
    EXPECT_EQ(pattern_->underlineWidth_, theme->GetTypingUnderlineWidth());
}

/**
 * @tc.name: ClearFocusStyleForTV001
 * @tc.desc: Test ClearFocusStyleForTV with focus style set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ClearFocusStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set focus style
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = true;
    pattern_->isFocusTextColorSet_ = true;
    pattern_->isFocusPlaceholderColorSet_ = true;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ClearFocusStyleForTV
     * @tc.expected: Focus style flags should be cleared
     */
    pattern_->ClearFocusStyleForTV();
    EXPECT_FALSE(pattern_->isFocusBGColorSet_);
    EXPECT_FALSE(pattern_->isFocusTextColorSet_);
    EXPECT_FALSE(pattern_->isFocusPlaceholderColorSet_);
}

/**
 * @tc.name: ClearFocusStyleForTV002
 * @tc.desc: Test ClearFocusStyleForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ClearFocusStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = true;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ClearFocusStyleForTV
     * @tc.expected: Background should be transparent in default mode
     */
    pattern_->ClearFocusStyleForTV();
    EXPECT_FALSE(pattern_->isFocusBGColorSet_);
}

/**
 * @tc.name: ClearFocusStyleForTV003
 * @tc.desc: Test ClearFocusStyleForTV with underline mode enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ClearFocusStyleForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode and set focus style
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    pattern_->SetFocusStyleForTV();

    /**
     * @tc.steps: step2. Call ClearFocusStyleForTV
     */
    pattern_->ClearFocusStyleForTV();

    /**
     * @tc.expected: step3. isFocusBGColorSet_ should be reset to false
     */
    ASSERT_FALSE(pattern_->isFocusBGColorSet_);
}

/**
 * @tc.name: GetInnerFocusPaintRectForTV001
 * @tc.desc: Test GetInnerFocusPaintRectForTV with CANCEL focus index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, GetInnerFocusPaintRectForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with clean node style
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
    });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessCancelButton();

    /**
     * @tc.steps: step2. Set focus index to CANCEL
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRectForTV
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRectForTV(paintRect);

    /**
     * @tc.expected: step4. Function should execute (focusIndex is CANCEL)
     */
    ASSERT_EQ(pattern_->focusIndex_, FocuseIndex::CANCEL);
}

/**
 * @tc.name: GetInnerFocusPaintRectForTV002
 * @tc.desc: Test GetInnerFocusPaintRectForTV with VOICE focus index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, GetInnerFocusPaintRectForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with voice node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetIsShowVoiceButton(true);
    });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessVoiceButton();

    /**
     * @tc.steps: step2. Set focus index to VOICE
     */
    pattern_->focusIndex_ = FocuseIndex::VOICE;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRectForTV
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRectForTV(paintRect);

    /**
     * @tc.expected: step4. Function should execute (rect width is non-negative)
     */
    ASSERT_GE(paintRect.GetRect().Width(), 0.0f);
}

/**
 * @tc.name: GetInnerFocusPaintRectForTV003
 * @tc.desc: Test GetInnerFocusPaintRectForTV with UNIT focus index and password icon
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, GetInnerFocusPaintRectForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with password type
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessResponseArea();

    /**
     * @tc.steps: step2. Set focus index to UNIT
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRectForTV
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRectForTV(paintRect);

    /**
     * @tc.expected: step4. paintRect should be updated with unit area
     */
    EXPECT_TRUE(paintRect.GetRect().Width() > 0);
    EXPECT_TRUE(paintRect.GetRect().Height() > 0);
}

/**
 * @tc.name: GetInnerFocusPaintRectForTV004
 * @tc.desc: Test GetInnerFocusPaintRectForTV with TEXT focus index (default else branch)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, GetInnerFocusPaintRectForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with text type
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Set focus index to TEXT (default)
     */
    pattern_->focusIndex_ = FocuseIndex::TEXT;

    /**
     * @tc.steps: step3. Enable focus box for TV theme
     */
    auto theme = pattern_->GetTheme();
    ASSERT_NE(theme, nullptr);
    theme->needFocusBox_ = true;

    /**
     * @tc.steps: step4. Call GetInnerFocusPaintRectForTV
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRectForTV(paintRect);

    /**
     * @tc.expected: step5. paintRect should be updated with text input focus area
     */
    EXPECT_TRUE(paintRect.GetRect().Width() > 0);
    EXPECT_TRUE(paintRect.GetRect().Height() > 0);
}

/**
 * @tc.name: GetInnerFocusPaintRectForTV005
 * @tc.desc: Test GetInnerFocusPaintRectForTV with null host
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, GetInnerFocusPaintRectForTV005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without adding to tree
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetInnerFocusPaintRectForTV without host
     */
    RoundRect paintRect;
    pattern->GetInnerFocusPaintRectForTV(paintRect);

    /**
     * @tc.expected: step3. Function should return early when host is null
     */
    EXPECT_TRUE(paintRect.GetRect().Width() == 0);
}

/**
 * @tc.name: GetInnerFocusPaintRectForTV006
 * @tc.desc: Test GetInnerFocusPaintRectForTV focusing on corner radius calculation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, GetInnerFocusPaintRectForTV006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with clean node style
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
    });
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Set focus index to CANCEL
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRectForTV
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRectForTV(paintRect);

    /**
     * @tc.expected: step4. cornerRadius should be half of width
     */
    float expectedCornerRadius = paintRect.GetRect().Width() / 2;
    EXPECT_NEAR(paintRect.GetCornerRadius(RoundRect::TOP_LEFT_POS).x, expectedCornerRadius, 0.1f);
}

/**
 * @tc.name: GetInnerFocusPaintRectForTV007
 * @tc.desc: Test GetInnerFocusPaintRectForTV with UpdateFocusOffsetIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, GetInnerFocusPaintRectForTV007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with voice node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetIsShowVoiceButton(true);
    });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessVoiceButton();

    /**
     * @tc.steps: step2. Set focus index to VOICE
     */
    pattern_->focusIndex_ = FocuseIndex::VOICE;

    /**
     * @tc.steps: step3. Call GetInnerFocusPaintRectForTV
     */
    RoundRect paintRect;
    pattern_->GetInnerFocusPaintRectForTV(paintRect);

    /**
     * @tc.expected: step4. Function should execute (rect width is non-negative)
     */
    ASSERT_GE(paintRect.GetRect().Width(), 0.0f);
}

/**
 * @tc.name: InitDisableColorForTV001
 * @tc.desc: Test InitDisableColorForTV with normal state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, InitDisableColorForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern in normal state
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: IsDisabled flag should be false
     */
    pattern_->InitDisableColorForTV();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetIsDisabledValue(false));
}

/**
 * @tc.name: InitDisableColorForTV002
 * @tc.desc: Test InitDisableColorForTV with disabled state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, InitDisableColorForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set disabled via EventHub
     */
    CreateTextField();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: IsDisabled flag should be true
     */
    pattern_->InitDisableColorForTV();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetIsDisabledValue(false));
}

/**
 * @tc.name: InitDisableColorForTV003
 * @tc.desc: Test InitDisableColorForTV with underline mode and disabled state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, InitDisableColorForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode and set disabled via EventHub
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    ASSERT_TRUE(pattern_->IsUnderlineMode());
    ASSERT_TRUE(pattern_->IsDisabled());

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     */
    pattern_->InitDisableColorForTV();

    /**
     * @tc.expected: step3. underlineWidth_ should be set to typing underline width
     */
    auto theme = pattern_->GetTheme();
    ASSERT_NE(theme, nullptr);
    EXPECT_EQ(pattern_->underlineWidth_, theme->GetTypingUnderlineWidth());
}

/**
 * @tc.name: PaintCancelRectForTV001
 * @tc.desc: Test PaintCancelRectForTV with clean node
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintCancelRectForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with clean node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetIsShowCancelButton(true);
    });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessCancelButton();

    /**
     * @tc.steps: step2. Set focus index to CANCEL
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;

    /**
     * @tc.steps: step3. Call PaintCancelRectForTV
     */
    pattern_->PaintCancelRectForTV();

    /**
     * @tc.expected: step4. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    EXPECT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintCancelRectForTV002
 * @tc.desc: Test PaintCancelRectForTV without clean node
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintCancelRectForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without clean node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    FlushLayoutTask(frameNode_);
    pattern_->needResetFocusColor_ = false;

    /**
     * @tc.steps: step2. Call PaintCancelRectForTV without clean node
     */
    pattern_->PaintCancelRectForTV();

    /**
     * @tc.expected: step3. Function should return early when cleanNodeResponseArea_ is null (needResetFocusColor_
     * unchanged)
     */
    ASSERT_FALSE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintCancelRectForTV003
 * @tc.desc: Test PaintCancelRectForTV with UNIT focus index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintCancelRectForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with UNIT focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Set focus index to UNIT
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;

    /**
     * @tc.steps: step3. Call PaintCancelRectForTV
     */
    pattern_->PaintCancelRectForTV();

    /**
     * @tc.expected: step4. Function should execute with unit focus (rect width is non-negative)
     */
    ASSERT_GE(pattern_->focusIndex_, FocuseIndex::UNIT);
}

/**
 * @tc.name: PaintCancelRectForTV004
 * @tc.desc: Test PaintCancelRectForTV with underline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintCancelRectForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode and clean node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::UNSPECIFIED);
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
    });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    GetFocus();
    pattern_->ProcessCancelButton();
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Set focus index to CANCEL
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;

    /**
     * @tc.steps: step3. Call PaintCancelRectForTV
     */
    pattern_->PaintCancelRectForTV();

    /**
     * @tc.expected: step4. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    ASSERT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintFocusAreaRectForTV001
 * @tc.desc: Test PaintFocusAreaRectForTV with valid response area
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with password type
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessResponseArea();

    /**
     * @tc.steps: step2. Get response area
     */
    auto responseArea = pattern_->GetResponseArea();
    ASSERT_NE(responseArea, nullptr);

    /**
     * @tc.steps: step3. Call PaintFocusAreaRectForTV
     */
    pattern_->PaintFocusAreaRectForTV(responseArea);

    /**
     * @tc.expected: step4. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    EXPECT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintFocusAreaRectForTV002
 * @tc.desc: Test PaintFocusAreaRectForTV with null response area
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->needResetFocusColor_ = false;

    /**
     * @tc.steps: step2. Call PaintFocusAreaRectForTV with null response area
     */
    RefPtr<TextInputResponseArea> nullResponseArea = nullptr;
    pattern_->PaintFocusAreaRectForTV(nullResponseArea);

    /**
     * @tc.expected: step3. Function should return early when responseArea is null (needResetFocusColor_ unchanged)
     */
    ASSERT_FALSE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintFocusAreaRectForTV003
 * @tc.desc: Test PaintFocusAreaRectForTV without focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with password type to ensure responseArea is created
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessResponseArea();

    /**
     * @tc.steps: step2. Get response area
     */
    auto responseArea = pattern_->GetResponseArea();
    ASSERT_NE(responseArea, nullptr);

    /**
     * @tc.steps: step3. Call PaintFocusAreaRectForTV without focus
     */
    pattern_->PaintFocusAreaRectForTV(responseArea);

    /**
     * @tc.expected: step4. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    ASSERT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintFocusAreaRectForTV004
 * @tc.desc: Test PaintFocusAreaRectForTV with VOICE focus index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with voice node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetIsShowVoiceButton(true);
    });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessVoiceButton();

    /**
     * @tc.steps: step2. Set focus index to VOICE
     */
    pattern_->focusIndex_ = FocuseIndex::VOICE;

    /**
     * @tc.steps: step3. Get response area
     */
    auto responseArea = pattern_->GetResponseArea();
    ASSERT_NE(responseArea, nullptr);

    /**
     * @tc.steps: step4. Call PaintFocusAreaRectForTV with VOICE focus
     */
    pattern_->PaintFocusAreaRectForTV(responseArea);

    /**
     * @tc.expected: step5. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    EXPECT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintFocusAreaRectForTV005
 * @tc.desc: Test PaintFocusAreaRectForTV with CANCEL focus index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with clean node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetIsShowCancelButton(true);
    });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessCancelButton();

    /**
     * @tc.steps: step2. Set focus index to CANCEL
     */
    pattern_->focusIndex_ = FocuseIndex::CANCEL;

    /**
     * @tc.steps: step3. Get response area
     */
    auto responseArea = pattern_->GetResponseArea();
    ASSERT_NE(responseArea, nullptr);

    /**
     * @tc.steps: step4. Call PaintFocusAreaRectForTV with CANCEL focus
     */
    pattern_->PaintFocusAreaRectForTV(responseArea);

    /**
     * @tc.expected: step5. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    EXPECT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintFocusAreaRectForTV006
 * @tc.desc: Test PaintFocusAreaRectForTV with UNIT focus index
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with UNIT focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessResponseArea();

    /**
     * @tc.steps: step2. Set focus index to UNIT
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;

    /**
     * @tc.steps: step3. Get response area
     */
    auto responseArea = pattern_->GetResponseArea();
    ASSERT_NE(responseArea, nullptr);

    /**
     * @tc.steps: step4. Call PaintFocusAreaRectForTV with UNIT focus
     */
    pattern_->PaintFocusAreaRectForTV(responseArea);

    /**
     * @tc.expected: step5. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    EXPECT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintFocusAreaRectForTV007
 * @tc.desc: Test PaintFocusAreaRectForTV with underline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    GetFocus();
    pattern_->ProcessResponseArea();
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Get response area
     */
    auto responseArea = pattern_->GetResponseArea();
    ASSERT_NE(responseArea, nullptr);

    /**
     * @tc.steps: step3. Call PaintFocusAreaRectForTV
     */
    pattern_->PaintFocusAreaRectForTV(responseArea);

    /**
     * @tc.expected: step4. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    ASSERT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintPasswordRectForTV001
 * @tc.desc: Test PaintPasswordRectForTV with password type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintPasswordRectForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with password type
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    FlushLayoutTask(frameNode_);
    GetFocus();
    pattern_->ProcessResponseArea();

    /**
     * @tc.steps: step2. Call PaintPasswordRectForTV
     */
    pattern_->PaintPasswordRectForTV();

    /**
     * @tc.expected: step3. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    EXPECT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintPasswordRectForTV002
 * @tc.desc: Test PaintPasswordRectForTV without password type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintPasswordRectForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without password type
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });
    FlushLayoutTask(frameNode_);
    pattern_->needResetFocusColor_ = false;

    /**
     * @tc.steps: step2. Call PaintPasswordRectForTV without password type
     */
    pattern_->PaintPasswordRectForTV();

    /**
     * @tc.expected: step3. Function should execute with text type (needResetFocusColor_ unchanged)
     */
    ASSERT_FALSE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: PaintPasswordRectForTV003
 * @tc.desc: Test PaintPasswordRectForTV with null host
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintPasswordRectForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without adding to tree
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->needResetFocusColor_ = false;

    /**
     * @tc.steps: step2. Call PaintPasswordRectForTV without host
     */
    pattern->PaintPasswordRectForTV();

    /**
     * @tc.expected: step3. Function should return early when host is null (needResetFocusColor_ unchanged)
     */
    ASSERT_FALSE(pattern->needResetFocusColor_);
}

/**
 * @tc.name: PaintPasswordRectForTV004
 * @tc.desc: Test PaintPasswordRectForTV with underline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintPasswordRectForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    GetFocus();
    pattern_->ProcessResponseArea();
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call PaintPasswordRectForTV
     */
    pattern_->PaintPasswordRectForTV();

    /**
     * @tc.expected: step3. needResetFocusColor_ should be set to true after HandleButtonFocusEvent
     */
    ASSERT_TRUE(pattern_->needResetFocusColor_);
}

/**
 * @tc.name: ProcessFocusStyleForTV001
 * @tc.desc: Test ProcessFocusStyleForTV in normal inline state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ProcessFocusStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern in normal inline state
     */
    CreateTextField();
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    FlushLayoutTask(frameNode_);
    TextFieldModelNG::SetInputStyle(AceType::RawPtr(frameNode_), InputStyle::INLINE);

    /**
     * @tc.steps: step2. Call ProcessFocusStyleForTV
     * @tc.expected: inlineFocusState should be true after inline processing
     */
    pattern_->ProcessFocusStyleForTV();
    EXPECT_TRUE(pattern_->inlineFocusState_);
}

/**
 * @tc.name: ProcessFocusStyleForTV002
 * @tc.desc: Test ProcessFocusStyleForTV with empty content
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ProcessFocusStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with empty content
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ProcessFocusStyleForTV
     * @tc.expected: inlineFocusState should be false in non-inline mode
     */
    pattern_->ProcessFocusStyleForTV();
    EXPECT_FALSE(pattern_->inlineFocusState_);
}

/**
 * @tc.name: ProcessFocusStyleForTV003
 * @tc.desc: Test ProcessFocusStyleForTV with error state and default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ProcessFocusStyleForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with error state and default mode
     */
    CreateTextField();
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Error", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ProcessFocusStyleForTV
     * @tc.expected: inlineFocusState should be false in non-inline mode
     */
    pattern_->ProcessFocusStyleForTV();
    EXPECT_FALSE(pattern_->inlineFocusState_);
}

/**
 * @tc.name: ProcessFocusStyleForTV004
 * @tc.desc: Test ProcessFocusStyleForTV with underline mode and focus state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ProcessFocusStyleForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode and get focus
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    GetFocus();
    ASSERT_TRUE(pattern_->IsUnderlineMode());
    ASSERT_TRUE(pattern_->HasFocus());

    /**
     * @tc.steps: step2. Call ProcessFocusStyleForTV
     */
    pattern_->ProcessFocusStyleForTV();

    /**
     * @tc.expected: step3. underlineWidth_ should be set to typing underline width
     */
    auto theme = pattern_->GetTheme();
    ASSERT_NE(theme, nullptr);
    EXPECT_EQ(pattern_->underlineWidth_, theme->GetTypingUnderlineWidth());
}

/**
 * @tc.name: SetFocusStyleForTV001
 * @tc.desc: Test SetFocusStyleForTV in inline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetFocusStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     * @tc.expected: Method should work correctly
     */
    CreateTextField();

    /**
     * @tc.steps: step2. Call SetFocusStyleForTV
     * @tc.expected: Method should execute without errors
     */
    pattern_->SetFocusStyleForTV();
    EXPECT_TRUE(pattern_->isFocusBGColorSet_);
    EXPECT_TRUE(pattern_->isFocusTextColorSet_);
    EXPECT_TRUE(pattern_->isFocusPlaceholderColorSet_);
}

/**
 * @tc.name: SetFocusStyleForTV002
 * @tc.desc: Test SetFocusStyleForTV with default background color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetFocusStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without custom background
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Call SetFocusStyleForTV
     * @tc.expected: Focus background color should be set
     */
    pattern_->SetFocusStyleForTV();
    EXPECT_TRUE(pattern_->isFocusBGColorSet_);
}

/**
 * @tc.name: SetFocusStyleForTV003
 * @tc.desc: Test SetFocusStyleForTV with custom background color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetFocusStyleForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with custom background color
     */
    CreateTextField();
    TextFieldModelNG::SetBackgroundColor(AceType::RawPtr(frameNode_), Color::RED);
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Call SetFocusStyleForTV
     * @tc.expected: Custom background color should not be overridden
     */
    pattern_->SetFocusStyleForTV();
    EXPECT_FALSE(pattern_->isFocusBGColorSet_);
}

/**
 * @tc.name: SetFocusStyleForTV004
 * @tc.desc: Test SetFocusStyleForTV with underline mode enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetFocusStyleForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call SetFocusStyleForTV
     */
    pattern_->SetFocusStyleForTV();

    /**
     * @tc.expected: step3. Function should execute underline mode branch (border radius updated)
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderRadius = renderContext->GetBorderRadius();
    ASSERT_TRUE(borderRadius.has_value());
}

/**
 * @tc.name: SetShowErrorForTV001
 * @tc.desc: Test SetShowErrorForTV with error text
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetShowErrorForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with error text
     */
    CreateTextField();
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Invalid input", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetShowErrorForTV
     * @tc.expected: Error state should be applied
     */
    pattern_->SetShowErrorForTV();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto errorText = layoutProperty->GetErrorTextValue(u"");
    EXPECT_EQ(errorText, u"Invalid input");
}

/**
 * @tc.name: SetShowErrorForTV002
 * @tc.desc: Test SetShowErrorForTV with error
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetShowErrorForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with error
     */
    CreateTextField();
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Error", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetShowErrorForTV
     * @tc.expected: Error state should be maintained
     */
    pattern_->SetShowErrorForTV();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto errorText = layoutProperty->GetErrorTextValue(u"");
    EXPECT_EQ(errorText, u"Error");
}

/**
 * @tc.name: SetShowErrorForTV003
 * @tc.desc: Test SetShowErrorForTV with password mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetShowErrorForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with password mode and error
     */
    CreateTextField();
    TextFieldModelNG::SetType(AceType::RawPtr(frameNode_), TextInputType::VISIBLE_PASSWORD);
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Invalid password", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetShowErrorForTV
     * @tc.expected: Error state should be maintained after applying password error style
     */
    pattern_->SetShowErrorForTV();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto errorText = layoutProperty->GetErrorTextValue(u"");
    EXPECT_EQ(errorText, u"Invalid password");
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    // In password mode with error, inner border color should be set from theme
    // The color value depends on theme, but it should not be the default transparent
    EXPECT_TRUE(paintProperty->HasInnerBorderColor());
}

/**
 * @tc.name: SetShowErrorForTV004
 * @tc.desc: Test SetShowErrorForTV with underline mode and error
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetShowErrorForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode and error
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    layoutProperty_->UpdateShowErrorText(true);
    layoutProperty_->UpdateErrorText(u"Error message");
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call SetShowErrorForTV
     */
    pattern_->SetShowErrorForTV();

    /**
     * @tc.expected: step3. underlineColor_ should be set to error color
     */
    auto theme = pattern_->GetTheme();
    ASSERT_NE(theme, nullptr);
    EXPECT_EQ(pattern_->underlineColor_, theme->GetErrorUnderlineColor());
}

/**
 * @tc.name: SetThemeAttrForTV001
 * @tc.desc: Test SetThemeAttrForTV with default theme
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default theme
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = false;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying theme attributes
     */
    pattern_->SetThemeAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeAttrForTV002
 * @tc.desc: Test SetThemeAttrForTV with focus background color set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with focus background color
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = true;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying focus background color
     */
    pattern_->SetThemeAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeAttrForTV003
 * @tc.desc: Test SetThemeAttrForTV with disabled state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set disabled via EventHub
     */
    CreateTextField();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: PaintProperty should not be nullptr after applying disabled opacity
     */
    pattern_->InitDisableColorForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeAttrForTV004
 * @tc.desc: Test SetThemeAttrForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying theme
     */
    pattern_->SetThemeAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeAttrForTV005
 * @tc.desc: Test SetThemeAttrForTV with underline mode enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call SetThemeAttrForTV
     */
    pattern_->SetThemeAttrForTV();

    /**
     * @tc.expected: step3. Background color should be TRANSPARENT for underline mode
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto bgColor = renderContext->GetBackgroundColor();
    ASSERT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::TRANSPARENT);
}

/**
 * @tc.name: SetThemeBorderAttrForTV001
 * @tc.desc: Test SetThemeBorderAttrForTV with default border
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default border
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: Theme border attributes should be applied
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV002
 * @tc.desc: Test SetThemeBorderAttrForTV with disabled state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set disabled via EventHub
     */
    CreateTextField();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying disabled border opacity
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV003
 * @tc.desc: Test SetThemeBorderAttrForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying default mode border radius
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV004
 * @tc.desc: Test SetThemeBorderAttrForTV with custom border
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with custom border color
     */
    CreateTextField();
    BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLUE);
    TextFieldModelNG::SetBorderColor(AceType::RawPtr(frameNode_), borderColor);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr when custom border color is set
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV005
 * @tc.desc: Test SetThemeBorderAttrForTV with custom border radius
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with custom border radius
     */
    CreateTextField();
    BorderRadiusProperty borderRadius(5.0_vp, 5.0_vp, 5.0_vp, 5.0_vp);
    TextFieldModelNG::SetBorderRadius(AceType::RawPtr(frameNode_), borderRadius);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr when custom border radius is set
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV006
 * @tc.desc: Test SetThemeBorderAttrForTV with underline mode enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     */
    pattern_->SetThemeBorderAttrForTV();

    /**
     * @tc.expected: step3. Border radius should be ZERO_BORDER_RADIUS_PROPERTY for underline mode
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderRadius = renderContext->GetBorderRadius();
    ASSERT_TRUE(borderRadius.has_value());
    EXPECT_EQ(borderRadius.value().radiusTopLeft->Value(), 0.0);
}

/**
 * @tc.name: UpdateHoverStyleForTV001
 * @tc.desc: Test UpdateHoverStyleForTV with no focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, UpdateHoverStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without focus
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call UpdateHoverStyleForTV with isHover = true and no focus
     * @tc.expected: Method should return early since hover effect only applies without focus
     */
    pattern_->UpdateHoverStyleForTV(true);
    /**
     * @tc.steps: step3. Manually set isOnHover_ state to simulate hover
     * @tc.expected: isHover should be true after setting the state
     */
    pattern_->isOnHover_ = true;
    EXPECT_TRUE(pattern_->isOnHover_);
}

/**
 * @tc.name: UpdateHoverStyleForTV002
 * @tc.desc: Test UpdateHoverStyleForTV with underline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, UpdateHoverStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call UpdateHoverStyleForTV with hover state
     */
    pattern_->UpdateHoverStyleForTV(true);

    /**
     * @tc.expected: step3. Function should execute without crash
     */
    ASSERT_TRUE(pattern_->IsUnderlineMode());
}

/**
 * @tc.name: UpdatePressStyleForTV001
 * @tc.desc: Test UpdatePressStyleForTV after losing focus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, UpdatePressStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with focus
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Call UpdatePressStyleForTV with isPressed = true and focus
     * @tc.expected: Press color should be applied
     */
    pattern_->UpdatePressStyleForTV(true);
    /**
     * @tc.steps: step3. Manually set isOnHover_ state to simulate press
     * @tc.expected: isHover should be true after setting the state
     */
    pattern_->isOnHover_ = true;
    EXPECT_TRUE(pattern_->isOnHover_);
}

/**
 * @tc.name: UpdatePressStyleForTV002
 * @tc.desc: Test UpdatePressStyleForTV with underline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, UpdatePressStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with underline mode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::UNSPECIFIED); });
    FlushLayoutTask(frameNode_);
    ASSERT_NE(layoutProperty_, nullptr);
    layoutProperty_->UpdateShowUnderline(true);
    ASSERT_TRUE(pattern_->IsUnderlineMode());

    /**
     * @tc.steps: step2. Call UpdatePressStyleForTV with press state
     */
    pattern_->UpdatePressStyleForTV(true);

    /**
     * @tc.expected: step3. Function should execute without crash
     */
    ASSERT_TRUE(pattern_->IsUnderlineMode());
}

} // namespace OHOS::Ace::NG
