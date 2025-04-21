/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "search_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {

class SearchDecorationTestNg : public SearchBases {};

/**
 * @tc.name: LetterSpacingPattern002
 * @tc.desc: test search letterSpacing dump
 * @tc.type: FUNC
 */
HWTEST_F(SearchDecorationTestNg, LetterSpacingPattern002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.step: step2.  set letterSpacing 1.0_fp.
     */
    searchModelInstance.SetLetterSpacing(1.0_fp);
    frameNode->MarkModifyDone();
    /**
     * @tc.step: step3. test letterSpacing
     */
    pattern->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_EQ(textFieldLayoutProperty->GetLetterSpacing(), 1.0_fp);
}

/**
 * @tc.name: LineHeightPattern002
 * @tc.desc: test search lineHeight dump
 * @tc.type: FUNC
 */
HWTEST_F(SearchDecorationTestNg, LineHeightPattern002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.step: step2.  set lineHeight 2.0_fp.
     */
    searchModelInstance.SetLineHeight(2.0_fp);
    frameNode->MarkModifyDone();
    /**
     * @tc.step: step3. test lineHeight
     */
    pattern->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_EQ(textFieldLayoutProperty->GetLineHeight(), 2.0_fp);
}

/**
 * @tc.name: TextDecorationPattern002
 * @tc.desc: test search decoration dump
 * @tc.type: FUNC
 */
HWTEST_F(SearchDecorationTestNg, TextDecorationPattern002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.step: step2.  set decoration.
     */
    searchModelInstance.SetTextDecoration(Ace::TextDecoration::UNDERLINE);
    frameNode->MarkModifyDone();
    searchModelInstance.SetTextDecorationColor(Color::BLUE);
    frameNode->MarkModifyDone();
    searchModelInstance.SetTextDecorationStyle(Ace::TextDecorationStyle::DASHED);
    frameNode->MarkModifyDone();
    /**
     * @tc.step: step3. test decoration
     */
    pattern->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecoration(), Ace::TextDecoration::UNDERLINE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationColor(), Color::BLUE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationStyle(), Ace::TextDecorationStyle::DASHED);
}
} // namespace OHOS::Ace::NG
