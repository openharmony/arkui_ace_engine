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

#include "gtest/gtest.h"
#include "core/common/ime/text_input_action.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/animation/curves.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/edge.h"
#include "core/components/search/search_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_layout_algorithm.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/common/properties/text_style_parser.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::string EMPTY_VALUE;
const std::string PLACEHOLDER = "DEFAULT PLACEHOLDER";
const std::string SEARCH_SVG = "resource:///ohos_search.svg";
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_0 = ParseFontFeatureSettings("\"ss01\" 0");
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_BLUE = Color::BLUE;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_RED = Color::RED;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_TRANSPARENT = Color::TRANSPARENT;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_FOREGROUND = Color::FOREGROUND;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_WHITE = Color::WHITE;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_BLACK = Color::BLACK;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_GREEN = Color::GREEN;
const Color DEFAULT_SELECTED_BACKFROUND_COLOR_GRAY = Color::GRAY;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::string DEFAULT_FILTER_TEXT = "CabcdefgABhCDEFG0123a456A789";
const std::string NUMBER_FILTER = "^[0-9]*$";
const std::string NUM_FILTER = "[0-9]";
const std::string FILTER_NUM_TEXT = "0123456789";
} // namespace

class SearchUpdateTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void SearchUpdateTestNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    auto searchTheme = AceType::MakeRefPtr<SearchTheme>();
    searchTheme->iconHeight_ = 24.0_px;
    searchTheme->height_ = 60.0_px;
    searchTheme->searchButtonTextColor_ = Color::RED;
    searchTheme->placeholderColor_ = Color::RED;
    textFieldTheme->bgColor_ = Color::RED;
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == SearchTheme::TypeId()) {
            return searchTheme;
        }
        if (type == IconTheme::TypeId()) {
            return iconTheme;
        }
        return textFieldTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
}

void SearchUpdateTestNg::TearDownTestSuite()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

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
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_FILTER_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_FILTER_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_FILTER_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(DEFAULT_FILTER_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUMBER_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUMBER_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUMBER_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUMBER_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUM_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUM_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUM_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(NUM_FILTER, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(FILTER_NUM_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(FILTER_NUM_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(FILTER_NUM_TEXT, PLACEHOLDER, SEARCH_SVG);
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
    searchModelInstance.Create(FILTER_NUM_TEXT, PLACEHOLDER, SEARCH_SVG);
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
} // namespace OHOS::Ace::NG