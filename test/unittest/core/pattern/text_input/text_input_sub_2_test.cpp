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
 * @tc.name: testUnderlineColor007
 * @tc.desc: test testInput underlineColor detailed, TextInput is more other properties 3
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
        model.SetMaxLength(10);
        model.SetMaxLines(5);
        model.SetFontSize(Dimension(20));
        model.SetShowError("error", false);

    /**
     * @tc.step: step1. Set UnderlineColor is null
     */
        UserUnderlineColor userColor;
        model.SetUserUnderlineColor(userColor);
    });
    frameNode_->MarkModifyDone();

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

    eventHub_->SetEnabled(false);
    
    /**
     * @tc.step: step18. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
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
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
}
} // namespace OHOS::Ace::NG