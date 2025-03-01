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

#include "text_area_base.h"
namespace OHOS::Ace::NG {

class TextAreaTestTwo : public TextAreaBase {};

/**
 * @tc.name: CalculateBoundsRect001
 * @tc.desc: Test is textarea, showError(true) while showCounter.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLines(1);
        model.SetMaxLength(100);
        model.SetShowError(u"error", true);
    });
    auto height = pattern_->textFieldOverlayModifier_->rect_.Height();
    EXPECT_EQ(height, 116.0f);
}

/**
 * @tc.name: CalculateBoundsRect002
 * @tc.desc: Test is textarea, showError(false) while showCounter.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLines(1);
        model.SetMaxLength(100);
        model.SetShowError(u"error", false);
    });
    auto height = pattern_->textFieldOverlayModifier_->rect_.Height();
    EXPECT_EQ(height, 116.0f);
}

/**
 * @tc.name: CalculateBoundsRect003
 * @tc.desc: Test is textarea, showError(false).
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetShowError(u"error", true); });
    auto height = pattern_->textFieldOverlayModifier_->rect_.Height();
    EXPECT_EQ(height, 116.0f);
}

/**
 * @tc.name: CalculateBoundsRect004
 * @tc.desc: Test is textarea, showError(true).
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalculateBoundsRect004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetShowError(u"error", true); });
    pattern_->maxFrameOffsetY_ = 5.0f;
    auto host = pattern_->GetHost();
    auto geometryNode = host->GetGeometryNode();
    RectF textRect(5.0f, 5.0f, 10.0f, 10.0f);
    SizeF size(10.0f, 10.0f);
    OffsetF translate(5.0f, 5.0f);
    geometryNode->SetContentSize(size);
    geometryNode->SetContentOffset(translate);
    pattern_->CalculateBoundsRect();
    EXPECT_EQ(pattern_->maxFrameOffsetY_, 5.0f);
}

/**
 * @tc.name: HandleOnCut001
 * @tc.desc: Test is textarea, HandleOnCut, while index of first hanele > second hanele.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, HandleOnCut001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 5;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 0;
    pattern_->selectController_->firstHandleInfo_ = firstHandleInfo;
    pattern_->selectController_->secondHandleInfo_ = secondHandleInfo;
    pattern_->HandleOnCut();
    EXPECT_EQ(pattern_->selectController_->firstHandleInfo_.index, 0);
}

/**
 * @tc.name: CalcScrollRect001
 * @tc.desc: Test is textarea, CalcScrollRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CalcScrollRect001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetInputStyle(InputStyle::INLINE); });

    Rect inlineScrollRect(5.0f, 5.0f, 10.0f, 10.0f);
    pattern_->inlineMeasureItem_.inlineContentRectHeight = 1.0f;
    pattern_->CalcScrollRect(inlineScrollRect);
    EXPECT_EQ(inlineScrollRect.Height(), 2500);

    pattern_->inlineMeasureItem_.inlineContentRectHeight = 50.0f;
    pattern_->CalcScrollRect(inlineScrollRect);
    EXPECT_EQ(inlineScrollRect.Top(), -2450);
}

/**
 * @tc.name: CreateDisplayText003
 * @tc.desc: Test is textarea, CalcScrollRect at API 11;.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaTestTwo, CreateDisplayText003, TestSize.Level1)
{
    SystemProperties::debugEnabled_ = true;
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    std::u16string input = u"ال";
    auto res = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input, 3, true, true));
    EXPECT_EQ("••", res);

    int32_t lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    std::u16string input2 = u"اللغة العربية";
    auto res2 = StringUtils::Str16ToStr8(pattern_->CreateDisplayText(input2, 3, true, false));
    EXPECT_NE("••", res2);

    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
}

} // namespace OHOS::Ace::NG