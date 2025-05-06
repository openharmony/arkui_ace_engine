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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string TEXT_TIMER_FORMAT = "HH:mm:ss.SSS";
} // namespace

struct TestProperty {
    std::optional<std::string> format = std::make_optional(TEXT_TIMER_FORMAT);;
    std::optional<double> inputCount = std::nullopt;
    std::optional<bool> isCountDown = std::nullopt;
    std::optional<Dimension> fontSize = std::nullopt;
    std::optional<Color> textColor = std::nullopt;
    std::optional<std::vector<Shadow>> textShadow = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyle = std::nullopt;
    std::optional<Ace::FontWeight> fontWeight = std::nullopt;
    std::optional<std::vector<std::string>> fontFamily = std::nullopt;
};

class TextTimerBuilderTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateTextTimerParagraph(const TestProperty& testProperty);
};

void TextTimerBuilderTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockParagraph::GetOrCreateMockParagraph();
}

void TextTimerBuilderTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockParagraph::TearDown();
}

RefPtr<FrameNode> TextTimerBuilderTestNg::CreateTextTimerParagraph(const TestProperty& testProperty)
{
    TextTimerModelNG textTimerModel;
    textTimerModel.Create();
    if (testProperty.format.has_value()) {
        textTimerModel.SetFormat(testProperty.format.value());
    }
    if (testProperty.inputCount.has_value()) {
        textTimerModel.SetInputCount(testProperty.inputCount.value());
    }
    if (testProperty.isCountDown.has_value()) {
        textTimerModel.SetIsCountDown(testProperty.isCountDown.value());
    }
    if (testProperty.fontSize.has_value()) {
        textTimerModel.SetFontSize(testProperty.fontSize.value());
    }
    if (testProperty.textColor.has_value()) {
        textTimerModel.SetTextColor(testProperty.textColor.value());
    }
    if (testProperty.textShadow.has_value()) {
        textTimerModel.SetTextShadow(testProperty.textShadow.value());
    }
    if (testProperty.italicFontStyle.has_value()) {
        textTimerModel.SetItalicFontStyle(testProperty.italicFontStyle.value());
    }
    if (testProperty.fontWeight.has_value()) {
        textTimerModel.SetFontWeight(testProperty.fontWeight.value());
    }
    if (testProperty.fontFamily.has_value()) {
        textTimerModel.SetFontFamily(testProperty.fontFamily.value());
    }
    return AceType::Claim<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode()); // TextTimerView pop
}

/**
 * @tc.name: TextTimerTest015
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(100.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(100.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest016
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(150.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(150.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest017
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(200.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(200.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest018
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(250.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(250.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest019
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(300.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(300.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest020
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(350.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(350.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest021
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(400.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(400.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest022
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(450.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(450.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest023
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(500.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(500.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest024
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(550.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(550.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest025
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(600.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(600.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest026
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(650.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(650.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest027
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(700.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(700.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest028
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(750.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(750.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest029
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(800.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(800.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest030
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(850.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(850.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest031
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(900.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(900.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest032
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(950.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(950.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest033
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1000.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1000.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest034
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1050.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1050.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest035
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1100.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1100.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest036
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1150.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1150.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest037
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1200.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1200.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest038
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1250.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1250.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest039
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1300.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1300.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest040
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1350.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1350.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest041
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1400.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1400.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest042
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1450.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1450.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: TextTimerTest043
 * @tc.desc: Test the SetBuilderFunc and get value.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerBuilderTestNg, TextTimerTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create texttimer frameNode.
     */
    TestProperty testProperty;
    testProperty.inputCount = std::make_optional(20000.0);
    testProperty.isCountDown = std::make_optional(true);
    auto frameNode = CreateTextTimerParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitTimerDisplay();

    /**
     * @tc.steps: step2. make builderFunc callback
     */
    auto node = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_EQ(false, config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step3. set parameters to pattern builderFunc and call BuildContentModifierNode
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();

    /**
     * @tc.steps: step4. make nextNode callback
     */
    auto nextNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(true, config.isCountDown_);
                EXPECT_EQ(20000.0, config.count_);
                EXPECT_TRUE(config.started_);
                return nullptr;
            };

    /**
     * @tc.steps: step5. start timer and check value.
     */
    pattern->HandleStart();
    pattern->SetBuilderFunc(nextNode);
    pattern->BuildContentModifierNode();
    /**
     * @tc.steps: step5. make thirdNode callback
     */
    auto thirdNode = [](TextTimerConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(1500.0, config.elapsedTime_);
                return nullptr;
            };

    /**
     * @tc.steps: step6. Tick timer and check value.
     */
    pattern->Tick(1500.0);
    pattern->SetBuilderFunc(thirdNode);
    pattern->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG
