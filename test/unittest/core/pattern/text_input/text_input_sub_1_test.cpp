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

class TextFieldUXTest : public TextInputBases {
public:
};

/**
 * @tc.name: testUnderlineColor002
 * @tc.desc: test testInput underlineColor detailed, TextInput is normal or onfocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);

    /**
     * @tc.step: step1. Set UnderlineColor is null
     */
        UserUnderlineColor userColor;
        model.SetUserUnderlineColor(userColor);
    });
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    frameNode_->MarkModifyDone();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->SetShowKeyBoardOnFocus(false);
    layoutProperty_->UpdateShowUnderline(true);
    layoutProperty_->UpdateTextInputType(TextInputType::UNSPECIFIED);
    EXPECT_EQ(pattern_->IsUnderlineMode(), true);
    EXPECT_EQ(layoutProperty_->GetShowUnderlineValue(false), true);
    EXPECT_EQ(pattern_->IsUnspecifiedOrTextType(), true);
    EXPECT_EQ(pattern_->IsInlineMode(), false);

    /**
     * @tc.expected: UserUnderlineColor is null
     */
    EXPECT_EQ(pattern_->GetUserUnderlineColor().normal, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().typing, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().error, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().disable, std::nullopt);

    /**
     * @tc.step: step2. Set userUnderlineColor.normal is GREEN
     */
    UserUnderlineColor userColor;
    userColor.normal = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    UserUnderlineColor userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.normal is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    EXPECT_NE(layoutProperty_, nullptr);
    auto theme = GetTheme();
    EXPECT_NE(theme, nullptr);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    auto focusHub = pattern_->GetFocusHub();
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step3. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineTypingColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineTypingColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step4. Set userUnderlineColor.typing is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.typing = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step5. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is Color::GREEN()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step6. Set userUnderlineColor.error is GREEN
     */
    userColor.typing = std::nullopt;
    userColor.error = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step7. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineTypingColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineTypingColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step8. Set userUnderlineColor.disable is GREEN
     */
    userColor.error = std::nullopt;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step9. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineTypingColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineTypingColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step10. Set userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    userColor.normal = Color::BLUE;
    userColor.typing = Color::GREEN;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, Color::BLUE);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(false);
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);

    /**
     * @tc.step: step11. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is GREEN
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = Color::GREEN;
    userColor.typing = Color::BLUE;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step14. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step15. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step16. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    userColor.normal = Color::BLACK;
    userColor.error = Color::WHITE;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, Color::BLACK);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::WHITE);

    /**
     * @tc.expected: CurrentUnderlineColor is Color::BLACK
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLACK);

    /**
     * @tc.step: step17. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);
}

/**
 * @tc.name: testUnderlineColor003
 * @tc.desc: test testInput underlineColor detailed, TextInput is error or onfocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
        model.SetShowError(u"error", false);

    /**
     * @tc.step: step1. Set UnderlineColor is null
     */
        UserUnderlineColor userColor;
        model.SetUserUnderlineColor(userColor);
    });
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    frameNode_->MarkModifyDone();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->SetShowKeyBoardOnFocus(false);
    layoutProperty_->UpdateShowUnderline(true);
    layoutProperty_->UpdateErrorText(u"error");
    layoutProperty_->UpdateShowErrorText(true);
    EXPECT_EQ(pattern_->IsShowError(), true);
    
    /**
     * @tc.expected: UserUnderlineColor is null
     */
    EXPECT_EQ(pattern_->GetUserUnderlineColor().normal, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().typing, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().error, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().disable, std::nullopt);

    /**
     * @tc.step: step2. Set userUnderlineColor.normal is GREEN
     */
    UserUnderlineColor userColor;
    userColor.normal = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    UserUnderlineColor userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.normal is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    EXPECT_NE(layoutProperty_, nullptr);
    auto theme = GetTheme();
    EXPECT_NE(theme, nullptr);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    auto focusHub = pattern_->GetFocusHub();
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step3. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step4. Set userUnderlineColor.typing is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.typing = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step5. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is GetErrorUnderlineColor
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->HasFocus(), true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step6. Set userUnderlineColor.error is GREEN
     */
    userColor.typing = std::nullopt;
    userColor.error = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step7. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is Color::GREEN
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step8. Set userUnderlineColor.disable is GREEN
     */
    userColor.error = std::nullopt;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step9. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step10. Set userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    userColor.normal = Color::BLUE;
    userColor.typing = Color::GREEN;
    userColor.error = std::nullopt;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, Color::BLUE);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step11. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = Color::GREEN;
    userColor.typing = Color::BLUE;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is Color::GREEN
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step14. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step15. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step16. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    userColor.normal = Color::BLACK;
    userColor.error = Color::WHITE;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, Color::BLACK);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::WHITE);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step17. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is Color::WHITE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    pattern_->SetShowError();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::WHITE);
    pattern_->SetShowKeyBoardOnFocus(false);
}

/**
 * @tc.name: testUnderlineColor004
 * @tc.desc: test testInput underlineColor detailed, TextInput is disable
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
        model.SetShowError(u"error", false);

    /**
     * @tc.step: step1. Set UnderlineColor is null
     */
        UserUnderlineColor userColor;
        model.SetUserUnderlineColor(userColor);
    });
    frameNode_->MarkModifyDone();
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    frameNode_->MarkModifyDone();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->SetShowKeyBoardOnFocus(false);
    layoutProperty_->UpdateShowUnderline(true);
    layoutProperty_->UpdateErrorText(u"error");
    layoutProperty_->UpdateShowErrorText(true);
    EXPECT_EQ(pattern_->IsShowError(), true);
    eventHub_->SetEnabled(false);
    pattern_->InitDisableColor();
    EXPECT_EQ(pattern_->IsDisabled(), true);
    auto focusHub = pattern_->GetFocusHub();
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    /**
     * @tc.expected: UserUnderlineColor is null
     */
    EXPECT_EQ(pattern_->GetUserUnderlineColor().normal, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().typing, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().error, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().disable, std::nullopt);

    /**
     * @tc.step: step2. Set userUnderlineColor.normal is GREEN
     */
    UserUnderlineColor userColor;
    userColor.normal = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    UserUnderlineColor userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.normal is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    EXPECT_NE(layoutProperty_, nullptr);
    auto theme = GetTheme();
    EXPECT_NE(theme, nullptr);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetDisableUnderlineColor()
     */

    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetDisableUnderlineColor());

    /**
     * @tc.step: step3. Set userUnderlineColor.typing is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.typing = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetDisableUnderlineColor()
     */
    eventHub_->SetEnabled(false);
    pattern_->InitDisableColor();
    EXPECT_EQ(pattern_->IsDisabled(), true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetDisableUnderlineColor());

    /**
     * @tc.step: step4. Set userUnderlineColor.error is GREEN
     */
    userColor.typing = std::nullopt;
    userColor.error = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetDisableUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetDisableUnderlineColor());

    /**
     * @tc.step: step5. Set userUnderlineColor.disable is GREEN
     */
    userColor.error = std::nullopt;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is GREEN
     */
    eventHub_->SetEnabled(false);
    pattern_->InitDisableColor();
    EXPECT_EQ(pattern_->IsDisabled(), true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);

    /**
     * @tc.step: step6. Set userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    userColor.normal = Color::BLUE;
    userColor.typing = Color::GREEN;
    userColor.error = std::nullopt;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, Color::BLUE);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetDisableUnderlineColor()
     */
    eventHub_->SetEnabled(false);
    pattern_->InitDisableColor();
    EXPECT_EQ(pattern_->IsDisabled(), true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetDisableUnderlineColor());

    /**
     * @tc.step: step7. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = Color::GREEN;
    userColor.typing = Color::BLUE;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetDisableUnderlineColor()
     */
    eventHub_->SetEnabled(false);
    pattern_->InitDisableColor();
    EXPECT_EQ(pattern_->IsDisabled(), true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetDisableUnderlineColor());

    /**
     * @tc.step: step9. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is Color::GREEN
     */
    eventHub_->SetEnabled(false);
    pattern_->InitDisableColor();
    EXPECT_EQ(pattern_->IsDisabled(), true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);

    /**
     * @tc.step: step10. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    userColor.normal = Color::BLACK;
    userColor.error = Color::WHITE;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, Color::BLACK);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::WHITE);

    /**
     * @tc.expected: CurrentUnderlineColor is Color::GREEN
     */
    eventHub_->SetEnabled(false);
    pattern_->InitDisableColor();
    EXPECT_EQ(pattern_->IsDisabled(), true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);
}

/**
 * @tc.name: testUnderlineColor005
 * @tc.desc: test testInput underlineColor detailed, TextInput is more other properties 1
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
        model.SetMaxLength(50);
        model.SetTextColor(Color::RED);
        model.SetPlaceholderColor(Color::GRAY);

    /**
     * @tc.step: step1. Set UnderlineColor is null
     */
        UserUnderlineColor userColor;
        model.SetUserUnderlineColor(userColor);
    });
    frameNode_->MarkModifyDone();
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->SetShowKeyBoardOnFocus(false);
    layoutProperty_->UpdateShowUnderline(true);
    auto focusHub = pattern_->GetFocusHub();
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->HandleCounterBorder();

    /**
     * @tc.expected: UserUnderlineColor is null
     */
    EXPECT_EQ(pattern_->GetUserUnderlineColor().normal, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().typing, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().error, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().disable, std::nullopt);

    /**
     * @tc.step: step2. Set userUnderlineColor.normal is GREEN
     */
    UserUnderlineColor userColor;
    userColor.normal = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    UserUnderlineColor userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.normal is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    EXPECT_NE(layoutProperty_, nullptr);
    auto theme = GetTheme();
    EXPECT_NE(theme, nullptr);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);

    /**
     * @tc.step: step3. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineTypingColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineTypingColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step4. Set userUnderlineColor.typing is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.typing = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step5. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is Color::GREEN()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step6. Set userUnderlineColor.error is GREEN
     */
    userColor.typing = std::nullopt;
    userColor.error = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step7. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineTypingColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineTypingColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step8. Set userUnderlineColor.disable is GREEN
     */
    userColor.error = std::nullopt;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step9. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineTypingColor()
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineTypingColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step10. Set userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    userColor.normal = Color::BLUE;
    userColor.typing = Color::GREEN;
    userColor.error = std::nullopt;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, Color::BLUE);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);

    /**
     * @tc.step: step11. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is GREEN
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::GREEN);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = Color::GREEN;
    userColor.typing = Color::BLUE;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step14. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetUnderlineColor());

    /**
     * @tc.step: step15. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step16. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    userColor.normal = Color::BLACK;
    userColor.error = Color::WHITE;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, Color::BLACK);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::WHITE);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetUnderlineColor()
     */
    focusHub->SetFocusable(false);
    pattern_->SetShowKeyBoardOnFocus(false);
    EXPECT_EQ(pattern_->HasFocus(), false);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLACK);

    /**
     * @tc.step: step17. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is BLUE
     */
    focusHub->SetFocusable(true);
    focusHub->currentFocus_ = true;
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->HasFocus(), true);
    pattern_->ApplyUnderlineTheme();
    EXPECT_EQ(pattern_->GetUnderlineColor(), Color::BLUE);
    pattern_->SetShowKeyBoardOnFocus(false);
}

/**
 * @tc.name: testUnderlineColor006
 * @tc.desc: test testInput underlineColor detailed, TextInput is more other properties 2
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
        model.SetMaxLength(10);
        model.SetMaxLines(5);
        model.SetFontSize(Dimension(20));

    /**
     * @tc.step: step1. Set UnderlineColor is null
     */
        UserUnderlineColor userColor;
        model.SetUserUnderlineColor(userColor);
    });
    frameNode_->MarkModifyDone();
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->SetShowKeyBoardOnFocus(false);
    layoutProperty_->UpdateShowUnderline(true);
    layoutProperty_->UpdateErrorText(u"error");
    layoutProperty_->UpdateShowErrorText(true);
    EXPECT_EQ(pattern_->IsShowError(), true);
    pattern_->HandleCounterBorder();

    /**
     * @tc.expected: UserUnderlineColor is null
     */
    EXPECT_EQ(pattern_->GetUserUnderlineColor().normal, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().typing, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().error, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().disable, std::nullopt);

    /**
     * @tc.step: step2. Set userUnderlineColor.normal is GREEN
     */
    UserUnderlineColor userColor;
    userColor.normal = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    UserUnderlineColor userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.normal is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    EXPECT_NE(layoutProperty_, nullptr);
    auto theme = GetTheme();
    EXPECT_NE(theme, nullptr);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */

    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step3. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step4. Set userUnderlineColor.typing is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.typing = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step5. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is GetErrorUnderlineColor
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step6. Set userUnderlineColor.error is GREEN
     */
    userColor.typing = std::nullopt;
    userColor.error = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step7. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step8. Set userUnderlineColor.disable is GREEN
     */
    userColor.error = std::nullopt;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step9. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step10. Set userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    userColor.normal = Color::BLUE;
    userColor.typing = Color::GREEN;
    userColor.error = std::nullopt;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, Color::BLUE);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step11. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = Color::GREEN;
    userColor.typing = Color::BLUE;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step14. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step15. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step16. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    userColor.normal = Color::BLACK;
    userColor.error = Color::WHITE;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, Color::BLACK);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::WHITE);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step17. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);
}
} // namespace OHOS::Ace::NG