/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

class TextFieldAutoFillControllerTest : public TextInputBases {
public:
};

/**
 * @tc.name: StartAutoFillAnimation001
 * @tc.desc: test testInput text StartAutoFillAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, StartAutoFillAnimation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Set the paragraph_ property to null so that the InitAutoFillParagraph method returns false.
     */
    pattern_->paragraph_ = nullptr;

    std::function<void()> onFinishCallback = []() {};
    std::u16string content = u"123";

    /**
     * @tc.steps: step3. Set the onFinishCallback parameter to null
     */
    autoFillController->StartAutoFillAnimation(nullptr, content);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);

    /**
     * @tc.steps: step4. Set the onFinishCallback parameter to not null
     */
    autoFillController->StartAutoFillAnimation(onFinishCallback, content);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: StartAutoFillAnimation002
 * @tc.desc: test testInput text StartAutoFillAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, StartAutoFillAnimation002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    std::function<void()> onFinishCallback = []() {};
    std::u16string content = u"";

    /**
     * @tc.steps: step2. Set contentRect_ width to zero so that the GetAutoFillContentLengthMode method returns INVALID
     */
    RectF rect;
    pattern_->contentRect_ = rect;

    /**
     * @tc.steps: step3. Set the onFinishCallback parameter to null
     */
    autoFillController->StartAutoFillAnimation(nullptr, content);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);

    /**
     * @tc.steps: step4. Set the onFinishCallback parameter to not null
     */
    autoFillController->StartAutoFillAnimation(onFinishCallback, content);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: StartAutoFillAnimation003
 * @tc.desc: test testInput text StartAutoFillAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, StartAutoFillAnimation003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    std::function<void()> onFinishCallback = []() {};
    std::u16string content = u"123";

    /**
     * @tc.steps: step2. Set contentRect_ width less than paragraph longestLine so that the
     * GetAutoFillContentLengthMode method returns EXTRA_LONG
     */
    RectF rect(0.0f, 0.0f, 20.0f, 20.0f);
    pattern_->contentRect_ = rect;

    /**
     * @tc.steps: step3. Call StartAutoFillAnimation
     */
    autoFillController->StartAutoFillAnimation(onFinishCallback, content);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: StartAutoFillAnimation004
 * @tc.desc: test testInput text StartAutoFillAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, StartAutoFillAnimation004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    std::function<void()> onFinishCallback = []() {};
    std::u16string content = u"123";

    /**
     * @tc.steps: step2. Call StartAutoFillAnimation
     */
    autoFillController->StartAutoFillAnimation(onFinishCallback, content);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: GetAutoFillContentLengthMode001
 * @tc.desc: test testInput text GetAutoFillContentLengthMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, GetAutoFillContentLengthMode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Call GetAutoFillContentLengthMode
     */
    ASSERT_EQ(autoFillController->GetAutoFillContentLengthMode(), AutoFillContentLengthMode::INVALID);
}

/**
 * @tc.name: GetAutoFillContentLengthMode002
 * @tc.desc: test testInput text GetAutoFillContentLengthMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, GetAutoFillContentLengthMode002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Set content width less than paragraph longestLine
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    RectF rect(0.0f, 0.0f, 100.0f, 20.0f);
    pattern_->contentRect_ = rect;

    /**
     * @tc.steps: step3. Call GetAutoFillContentLengthMode
     */
    ASSERT_EQ(autoFillController->GetAutoFillContentLengthMode(), AutoFillContentLengthMode::EXTRA_LONG);
}

/**
 * @tc.name: GetAutoFillContentLengthMode003
 * @tc.desc: test testInput text GetAutoFillContentLengthMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, GetAutoFillContentLengthMode003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Set paragraph longestLine less than 1/3 of content width
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    RectF rect(0.0f, 0.0f, 1400.0f, 20.0f);
    pattern_->contentRect_ = rect;

    /**
     * @tc.steps: step3. Call GetAutoFillContentLengthMode
     */
    ASSERT_EQ(autoFillController->GetAutoFillContentLengthMode(), AutoFillContentLengthMode::SHORT);
}

/**
 * @tc.name: GetAutoFillContentLengthMode004
 * @tc.desc: test testInput text GetAutoFillContentLengthMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, GetAutoFillContentLengthMode004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Set paragraph longestLine less than 2/3 of content width
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    RectF rect(0.0f, 0.0f, 920.0f, 20.0f);
    pattern_->contentRect_ = rect;

    /**
     * @tc.steps: step3. Call GetAutoFillContentLengthMode
     */
    ASSERT_EQ(autoFillController->GetAutoFillContentLengthMode(), AutoFillContentLengthMode::MEDIUM);
}

/**
 * @tc.name: GetAutoFillContentLengthMode005
 * @tc.desc: test testInput text GetAutoFillContentLengthMode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, GetAutoFillContentLengthMode005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField("123", "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Set paragraph longestLine less than 3/3 of content width
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    RectF rect(0.0f, 0.0f, 500.0f, 20.0f);
    pattern_->contentRect_ = rect;

    /**
     * @tc.steps: step3. Call GetAutoFillContentLengthMode
     */
    ASSERT_EQ(autoFillController->GetAutoFillContentLengthMode(), AutoFillContentLengthMode::LONG);
}

/**
 * @tc.name: PlayAutoFillDefaultCharAnimation001
 * @tc.desc: test testInput text PlayAutoFillDefaultCharAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillDefaultCharAnimation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Call PlayAutoFillDefaultCharAnimation
     */
    autoFillController->PlayAutoFillDefaultCharAnimation(AutoFillContentLengthMode::LONG);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: PlayAutoFillTranslationAnimation001
 * @tc.desc: test testInput text PlayAutoFillTranslationAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillTranslationAnimation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Call PlayAutoFillTranslationAnimation
     */
    autoFillController->PlayAutoFillTranslationAnimation(AutoFillContentLengthMode::LONG);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: PlayAutoFillTranslationAnimation002
 * @tc.desc: test testInput text PlayAutoFillTranslationAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillTranslationAnimation002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    EXPECT_EQ(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);

    /**
     * @tc.steps: step2. Init autoFillParagraph_ and autoFillIconNode_
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    autoFillController->CreateAutoFillIcon();

    /**
     * @tc.steps: step3. Call PlayAutoFillTranslationAnimation
     */
    autoFillController->PlayAutoFillTranslationAnimation(AutoFillContentLengthMode::LONG);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::TRANSLATION);
}

/**
 * @tc.name: PlayAutoFillTextScrollAnimation001
 * @tc.desc: test testInput text PlayAutoFillTextScrollAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillTextScrollAnimation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Call PlayAutoFillTextScrollAnimation
     */
    autoFillController->PlayAutoFillTextScrollAnimation();
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: PlayAutoFillTextScrollAnimation002
 * @tc.desc: test testInput text PlayAutoFillTextScrollAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillTextScrollAnimation002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Init autoFillParagraph_ and autoFillIconNode_
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    autoFillController->CreateAutoFillIcon();

    /**
     * @tc.steps: step3. Call PlayAutoFillTextScrollAnimation
     */
    autoFillController->PlayAutoFillTextScrollAnimation();
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::TRANSLATION);
}

/**
 * @tc.name: PlayAutoFillTextScrollAnimation003
 * @tc.desc: test testInput text PlayAutoFillTextScrollAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillTextScrollAnimation003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    EXPECT_EQ(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);

    /**
     * @tc.steps: step2. Init autoFillParagraph_ and autoFillIconNode_
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    autoFillController->CreateAutoFillIcon();

    /**
     * @tc.steps: step3. Call PlayAutoFillTextScrollAnimation
     */
    autoFillController->PlayAutoFillTextScrollAnimation();
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::TRANSLATION);
}

/**
 * @tc.name: PlayAutoFillIconHideAnimation001
 * @tc.desc: test testInput text PlayAutoFillIconHideAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillIconHideAnimation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Call PlayAutoFillIconHideAnimation
     */
    std::function<void()> onFinishCallback = []() {};
    autoFillController->PlayAutoFillIconHideAnimation(onFinishCallback, AutoFillContentLengthMode::MEDIUM);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: PlayAutoFillIconHideAnimation002
 * @tc.desc: test testInput text PlayAutoFillIconHideAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillIconHideAnimation002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. init autoFillParagraph_ and autoFillIconNode_
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    autoFillController->CreateAutoFillIcon();

    /**
     * @tc.steps: step3. Call PlayAutoFillIconHideAnimation
     */
    std::function<void()> onFinishCallback = []() {};
    autoFillController->PlayAutoFillIconHideAnimation(onFinishCallback, AutoFillContentLengthMode::MEDIUM);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: PlayAutoFillIconHideAnimation003
 * @tc.desc: test testInput text PlayAutoFillIconHideAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, PlayAutoFillIconHideAnimation003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;

    /**
     * @tc.steps: step2. Init autoFillParagraph_ and autoFillIconNode_
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    autoFillController->CreateAutoFillIcon();

    /**
     * @tc.steps: step3. Call PlayAutoFillIconHideAnimation
     */
    std::function<void()> onFinishCallback = []() {};
    autoFillController->PlayAutoFillIconHideAnimation(onFinishCallback, AutoFillContentLengthMode::EXTRA_LONG);
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}

/**
 * @tc.name: ResetAutoFillAnimationStatus001
 * @tc.desc: test testInput text ResetAutoFillAnimationStatus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAutoFillControllerTest, ResetAutoFillAnimationStatus001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetEnableAutoFill(true);
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    EXPECT_EQ(layoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);

    /**
     * @tc.steps: step2. Init autoFillParagraph_ and autoFillIconNode_
     */
    std::u16string content = u"123";
    autoFillController->InitAutoFillParagraph(content);
    autoFillController->CreateAutoFillIcon();

    /**
     * @tc.steps: step3. Call PlayAutoFillTextScrollAnimation
     */
    autoFillController->PlayAutoFillTextScrollAnimation();
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::TRANSLATION);

    /**
     * @tc.steps: step4. Call ResetAutoFillAnimationStatus
     */
    autoFillController->ResetAutoFillAnimationStatus();
    ASSERT_EQ(autoFillController->GetAutoFillAnimationStatus(), AutoFillAnimationStatus::INIT);
}
} // namespace OHOS::Ace::NG