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
namespace {
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT = Color::TRANSPARENT;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND = Color::FOREGROUND;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE = Color::WHITE;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK = Color::BLACK;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN = Color::GREEN;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY = Color::GRAY;
} // namespace

class SearchUpdateTestNg : public SearchBases {};

/**
 * @tc.name: testSelectedBackgroundColor001
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testSelectedBackgroundColor002
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor002, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::FOREGROUND);
}

/**
 * @tc.name: testSelectedBackgroundColor003
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor003, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::WHITE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: testSelectedBackgroundColor004
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor004, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GREEN);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GRAY);
}

/**
 * @tc.name: testSelectedBackgroundColor005
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor005, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testSelectedBackgroundColor006
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor006, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::FOREGROUND);
}

/**
 * @tc.name: testSelectedBackgroundColor007
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::WHITE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: testSelectedBackgroundColor008
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor008, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GREEN);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GRAY);
}

/**
 * @tc.name: testSelectedBackgroundColor009
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor009, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_FILTER_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testSelectedBackgroundColor010
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor010, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_FILTER_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::FOREGROUND);
}

/**
 * @tc.name: testSelectedBackgroundColor011
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor011, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_FILTER_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::WHITE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: testSelectedBackgroundColor012
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor012, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_FILTER_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GREEN);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GRAY);
}

/**
 * @tc.name: testSelectedBackgroundColor013
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor013, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUMBER_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testSelectedBackgroundColor014
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor014, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUMBER_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::FOREGROUND);
}

/**
 * @tc.name: testSelectedBackgroundColor015
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor015, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUMBER_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::WHITE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: testSelectedBackgroundColor016
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor016, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUMBER_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GREEN);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GRAY);
}

/**
 * @tc.name: testSelectedBackgroundColor017
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor017, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUM_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testSelectedBackgroundColor018
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor018, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUM_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::FOREGROUND);
}

/**
 * @tc.name: testSelectedBackgroundColor019
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor019, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUM_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::WHITE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: testSelectedBackgroundColor020
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor020, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(NUM_FILTER_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GREEN);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GRAY);
}

/**
 * @tc.name: testSelectedBackgroundColor021
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor021, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(FILTER_NUM_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLUE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_RED);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
}

/**
 * @tc.name: testSelectedBackgroundColor022
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor022, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(FILTER_NUM_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::FOREGROUND);
}

/**
 * @tc.name: testSelectedBackgroundColor023
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor023, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(FILTER_NUM_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::WHITE);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: testSelectedBackgroundColor024
 * @tc.desc: test search selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchUpdateTestNg, testSelectedBackgroundColor024, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(FILTER_NUM_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();

    /**
     * @tc.step: step2. Set selectedBackgroundColor
     */
    searchModelInstance.SetSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GREEN);

    /**
     * @tc.step: step3. Set selectedBackgroundColor
     */
    paintProperty->UpdateSelectedBackgroundColor(DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY);
    frameNode->MarkModifyDone();
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::GRAY);
}

HWTEST_F(SearchUpdateTestNg, SearchTypeToString005, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
    searchModelInstance.SetType(TextInputType::ONE_TIME_CODE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    EXPECT_EQ(pattern->SearchTypeToString(), "SearchType.ONE_TIME_CODE");
}
} // namespace OHOS::Ace::NG