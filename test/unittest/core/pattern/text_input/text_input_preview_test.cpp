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

class TextInputPreviewText : public TextInputBases {
public:
};

/**
 * @tc.name: CalculatePreviewingTextMoving001
 * @tc.desc: Test CalculatePreviewingTextMovingLimit
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, CalculatePreviewingTextMoving001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
        model.SetType(TextInputType::TEXT);
    });
    GetFocus();

    RoundRect paintRect;
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    pattern_->GetInnerFocusPaintRect(paintRect);
    pattern_->PaintResponseAreaRect();
    EXPECT_NE(pattern_->responseArea_, nullptr);
}

/**
 * @tc.name: CalculatePreviewingTextMoving002
 * @tc.desc: Test CalculatePreviewingTextMovingLimit
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, CalculatePreviewingTextMoving002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);

    GetFocus();
    pattern_->HandleSetSelection(5, 10, true);

    float offset = 1;
    pattern_->UpdateHandlesOffsetOnScroll(offset);
    EXPECT_EQ(offset, 1);

    pattern_->selectOverlay_->SetIsSingleHandle(false);
    pattern_->UpdateHandlesOffsetOnScroll(1);
    EXPECT_EQ(offset, 1);
}

/**
 * @tc.name: CheckPasswordAreaState
 * @tc.desc: Test CheckPasswordAreaState
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, CheckPasswordAreaState, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordText(true);
    });
    GetFocus();

    pattern_->CheckPasswordAreaState();
}

/**
 * @tc.name: UpdateFocusBackward005
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, UpdateFocusBackward005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Get clear node response area
     */
    pattern_->focusIndex_ = FocuseIndex::UNIT;
    EXPECT_TRUE(pattern_->UpdateFocusBackward());
}

/**
 * @tc.name: UpdateFocusForward001
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, UpdateFocusForward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetCancelButtonSymbol(false);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test Update clear node false
     */
    cleanNodeResponseArea->UpdateCleanNode(false);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_FALSE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateFocusForward002
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, UpdateFocusForward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::CONSTANT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCancelButtonSymbol(false);
    });
    GetFocus();

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test Update clear node false
     */
    cleanNodeResponseArea->UpdateCleanNode(false);
    pattern_->focusIndex_ = FocuseIndex::TEXT;
    EXPECT_TRUE(pattern_->UpdateFocusForward());
}

/**
 * @tc.name: UpdateCancelNode001
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, UpdateCancelNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test Update clear node true
     */
    cleanNodeResponseArea->UpdateCleanNode(true);
    pattern_->UpdateCancelNode();
    EXPECT_TRUE(cleanNodeResponseArea->IsShow());
}

/**
 * @tc.name: UpdateCancelNode002
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, UpdateCancelNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::INVISIBLE);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test Update clear node true
     */
    cleanNodeResponseArea->UpdateCleanNode(true);
    pattern_->UpdateCancelNode();
    EXPECT_FALSE(cleanNodeResponseArea->IsShow());
}

/**
 * @tc.name: UpdateCancelNode003
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, UpdateCancelNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetCleanNodeStyle(CleanNodeStyle::INPUT);
        model.SetIsShowCancelButton(true);
        model.SetCancelIconSize(Dimension(ICON_SIZE, DimensionUnit::PX));
        model.SetType(TextInputType::VISIBLE_PASSWORD);
        model.SetCancelButtonSymbol(false);
    });

    /**
     * @tc.steps: step2. Get clear node response area
     */
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    auto stackNode = cleanNodeResponseArea->cleanNode_;
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test Update clear node true
     */
    cleanNodeResponseArea->UpdateCleanNode(true);
    pattern_->UpdateCancelNode();
    EXPECT_FALSE(cleanNodeResponseArea->IsShow());
}

/**
 * @tc.name: OnObscuredChanged
 * @tc.desc: Test OnObscuredChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextInputPreviewText, OnObscuredChanged, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set textObscured_  true;
     */
    pattern_->textObscured_  = true;
    pattern_->OnObscuredChanged(false);
}
} // namespace OHOS::Ace::NG