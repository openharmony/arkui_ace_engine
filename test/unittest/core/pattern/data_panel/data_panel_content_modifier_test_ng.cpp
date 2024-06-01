/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "gtest/internal/gtest-internal.h"

#define private public
#include "base/geometry/ng/offset_t.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_modifier.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/pipeline/base/constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr double MAX = 200.0;
constexpr double MAX_DEFAULT = 100.0;
constexpr double MAX_50 = 50.0;
constexpr double MAX_30 = 30.0;
const std::vector<double> VALUES = { 1.0, 2.0, 3.0, 4.0 };
const std::vector<double> LONG_VALUES = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
const std::vector<double> FULL_VALUES = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
const std::vector<double> SINGLE_VALUES = { 1.0 };
const std::vector<double> VALUES_20 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
const std::vector<double> BIG_VALUES = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0};
constexpr size_t TYPE_CYCLE = 0;
constexpr size_t TYPE_LINE = 1;
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float MAX_PERCENT_WIDTH = 200.0f;
constexpr float MAX_PERCENT_HEIGHT = 200.0f;
const SizeF MAX_PERCENT_SIZE(MAX_PERCENT_WIDTH, MAX_PERCENT_HEIGHT);
constexpr float MAX_INFINITE = 1000000.0f;
const SizeF MAX_INFINITE_SIZE(MAX_INFINITE, MAX_INFINITE);
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
const Color TRUE_COLOR = Color(0x00000000);
const Color ERROR_COLOR = Color();
constexpr double DEFAULT_SHADOW_VALUE = 5.0;
const OffsetF OFFSET = { 1.0f, 1.0f };
} // namespace

class DataPanelContentModifierTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void GradientColorSet(std::vector<Gradient>& valueColors, const int& length);
};

class DataPanelTheme : public Theme {
    DECLARE_ACE_TYPE(DataPanelTheme, Theme)
public:
    DataPanelTheme()
    {
        color.clear();
        for (size_t i = 0; i < MAX_COUNT; i++) {
            color.emplace_back(std::make_pair(Color::BLUE, Color::BLUE));
        }
    }
    ~DataPanelTheme() override = default;

    Dimension GetThickness() const
    {
        return 20.0_vp;
    }

    std::vector<std::pair<Color, Color>> GetColorsArray() const
    {
        return color;
    }

private:
    std::vector<std::pair<Color, Color>> color;
};

void DataPanelContentModifierTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void DataPanelContentModifierTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void DataPanelContentModifierTestNg::GradientColorSet(std::vector<Gradient>& valueColors, const int& length)
{
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    for (int i = 0; i < length; i++) {
        valueColors.push_back(gradient);
    }
}

/**
 * @tc.name: DataPanelPatternTest013
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX_DEFAULT, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX_DEFAULT, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };
    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest015
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;

    dataPanelModelNG.Create(FULL_VALUES, MAX_DEFAULT, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest016
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;

    dataPanelModelNG.Create(SINGLE_VALUES, MAX_DEFAULT, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest017
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest018
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest019
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(FULL_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest020
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(SINGLE_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest021
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX_DEFAULT, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest022
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX_DEFAULT, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest023
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(FULL_VALUES, MAX_DEFAULT, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest024
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(SINGLE_VALUES, MAX_DEFAULT, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest025
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest026
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest027
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(FULL_VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest028
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(SINGLE_VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest029
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(BIG_VALUES, MAX_DEFAULT, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(BIG_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest030
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(BIG_VALUES, MAX_DEFAULT, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(BIG_VALUES, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest031
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(BIG_VALUES, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(BIG_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest032
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(BIG_VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(BIG_VALUES, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest033
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX_50, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest034
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX_50, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest035
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(FULL_VALUES, MAX_50, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest036
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(SINGLE_VALUES, MAX_50, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest037
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(BIG_VALUES, MAX_50, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(BIG_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest038
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX_50, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest039
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX_50, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest040
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(FULL_VALUES, MAX_50, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest041
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(SINGLE_VALUES, MAX_50, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest042
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(BIG_VALUES, MAX_50, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(BIG_VALUES, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest043
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX_DEFAULT, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest044
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX_DEFAULT, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX_DEFAULT, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest045
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest046
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest047
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX_50, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest048
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX_50, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX_50, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest049
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX_30, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest050
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX_30, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest051
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(FULL_VALUES, MAX_30, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest052
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(SINGLE_VALUES, MAX_30, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest053
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX_30, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest054
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(BIG_VALUES, MAX_30, TYPE_CYCLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(BIG_VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest055
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX_30, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest056
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(LONG_VALUES, MAX_30, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(LONG_VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest057
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(FULL_VALUES, MAX_30, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(FULL_VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest058
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(SINGLE_VALUES, MAX_30, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(SINGLE_VALUES, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelPatternTest059
 * @tc.desc: SetBuilderFunc and get value when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPatternTest059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init DataPanel node
     */
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES_20, MAX_30, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Make builderFunc.
     */
    auto node = [](DataPanelConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUES_20, config.values_);
        EXPECT_EQ(MAX_30, config.maxValue_);
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: DataPanelTest011
 * @tc.desc: Test dataPanel pattern OnDirtyLayoutWrapperSwap function  when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPaintPropertyTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dataPanel and get frameNode.
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create dataPanel frameNode, get dataPanelPattern and dataPanelWrapper.
     * @tc.expected: step2. get dataPanelPattern success.
     */
    RefPtr<DataPanelPattern> dataPanelPattern = AceType::DynamicCast<DataPanelPattern>(frameNode->GetPattern());
    EXPECT_NE(dataPanelPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. call dataPanelPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    RefPtr<DataPanelLayoutAlgorithm> dataPanelLayoutAlgorithm = AceType::MakeRefPtr<DataPanelLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step4. call dataPanelPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *     case 1: LayoutWrapperNode::SkipMeasure = true , skipLayout = false;
     */
    bool first_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapperNode::SkipMeasure = false , skipLayout = false;
     */
    bool second_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dataPanelLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapperNode::SkipMeasure = true , skipLayout = false;
     */
    bool third_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(third_case);

    /**
     *     case 4: LayoutWrapperNode::SkipMeasure = false , skipLayout = false;
     */
    bool forth_case = dataPanelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forth_case);
}


/**
 * @tc.name: DataPanelTest012
 * @tc.desc: Test DataPanel PaintMethod SetTrackBackground when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPaintPropertyTest012, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_LINE);
    dataPanelModelNG.SetTrackBackground(TRUE_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetTrackBackgroundValue(), TRUE_COLOR);

    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_LINE);
    dataPanelModelNG2.SetTrackBackground(ERROR_COLOR);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetTrackBackgroundValue(), ERROR_COLOR);
}

/**
 * @tc.name: DataPanelTest013
 * @tc.desc: Test DataPanel PaintMethod SetStrokeWidth when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPaintPropertyTest013, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_LINE);
    Dimension strokeWidth = 50.0_vp;
    dataPanelModelNG.SetStrokeWidth(strokeWidth);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetStrokeWidthValue(), strokeWidth);

    // ErrorValue1
    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_LINE);
    Dimension strokeWidth2 = 0.0_vp;
    dataPanelModelNG2.SetStrokeWidth(strokeWidth2);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetStrokeWidthValue(), strokeWidth2);

    // ErrorValue2
    DataPanelModelNG dataPanelModelNG3;
    dataPanelModelNG3.Create(VALUES, MAX, TYPE_LINE);
    Dimension strokeWidth3 = 500.0_vp;
    dataPanelModelNG3.SetStrokeWidth(strokeWidth3);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode3, nullptr);
    auto dataPanelPaintProperty3 = frameNode3->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty3, nullptr);
    EXPECT_EQ(dataPanelPaintProperty3->GetStrokeWidthValue(), strokeWidth3);

    // ErrorValue3
    DataPanelModelNG dataPanelModelNG4;
    dataPanelModelNG4.Create(VALUES, MAX, TYPE_LINE);
    Dimension strokeWidth4 = -50.0_vp;
    dataPanelModelNG4.SetStrokeWidth(strokeWidth4);
    auto frameNode4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode4, nullptr);
    auto dataPanelPaintProperty4 = frameNode4->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty4, nullptr);
    EXPECT_EQ(dataPanelPaintProperty4->GetStrokeWidthValue(), strokeWidth4);
}

/**
 * @tc.name: DataPanelTest014
 * @tc.desc: Test DataPanel PaintMethod SetValueColors Normal when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPaintPropertyTest014, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_LINE);
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor::WHITE);
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor::BLACK);
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    std::vector<Gradient> valueColors;
    // test Solid color when the valueColors >0 and valueColors <=9
    int length = 2;
    for (int i = 0; i < length; i++) {
        valueColors.push_back(gradient);
    }
    dataPanelModelNG.SetValueColors(valueColors);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetValueColorsValue(), valueColors);
}

/**
 * @tc.name: DataPanelTest015
 * @tc.desc: Test DataPanel PaintMethod SetValueColors Normal2 when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPaintPropertyTest015, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_LINE);
    int length = 2;
    std::vector<Gradient> valueColors;
    GradientColorSet(valueColors, length);
    // test Gradient  color when the valueColors >0 and valueColors <=9
    dataPanelModelNG.SetValueColors(valueColors);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetValueColorsValue(), valueColors);

    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_LINE);
    std::vector<Gradient> valueColors2;
    GradientColorSet(valueColors2, 0);
    // test Gradient  color when the valueColors = 0
    dataPanelModelNG2.SetValueColors(valueColors2);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetValueColorsValue(), valueColors2);

    DataPanelModelNG dataPanelModelNG3;
    dataPanelModelNG3.Create(VALUES, MAX, TYPE_LINE);
    int length2 = 11;
    std::vector<Gradient> valueColors3;
    GradientColorSet(valueColors3, length2);
    // test Gradient  color when the valueColors > 9
    dataPanelModelNG3.SetValueColors(valueColors3);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode3, nullptr);
    auto dataPanelPaintProperty3 = frameNode3->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty3, nullptr);
    EXPECT_EQ(dataPanelPaintProperty3->GetValueColorsValue(), valueColors3);
}

/**
 * @tc.name: DataPanelTest016
 * @tc.desc: Test DataPanel PaintMethod SetShadowOption when type is line.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelContentModifierTestNg, DataPanelPaintPropertyTest016, TestSize.Level1)
{
    DataPanelModelNG dataPanelModelNG;
    dataPanelModelNG.Create(VALUES, MAX, TYPE_LINE);
    int length = 3;
    std::vector<Gradient> valueColors;
    GradientColorSet(valueColors, length);
    DataPanelShadow shadowOption { true, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE, DEFAULT_SHADOW_VALUE,
        valueColors };
    dataPanelModelNG.SetShadowOption(shadowOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto dataPanelPaintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty, nullptr);
    EXPECT_EQ(dataPanelPaintProperty->GetShadowOptionValue(), shadowOption);

    DataPanelModelNG dataPanelModelNG2;
    dataPanelModelNG2.Create(VALUES, MAX, TYPE_LINE);
    std::vector<Gradient> valueColors2;
    GradientColorSet(valueColors2, length);
    DataPanelShadow shadowOption2 { true, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE,
        valueColors2 };
    dataPanelModelNG2.SetShadowOption(shadowOption2);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto dataPanelPaintProperty2 = frameNode2->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty2, nullptr);
    EXPECT_EQ(dataPanelPaintProperty2->GetShadowOptionValue(), shadowOption2);

    DataPanelModelNG dataPanelModelNG3;
    dataPanelModelNG3.Create(VALUES, MAX, TYPE_LINE);
    int length2 = 12;
    std::vector<Gradient> valueColors3;
    GradientColorSet(valueColors3, length2);
    DataPanelShadow shadowOption3 { true, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE, -DEFAULT_SHADOW_VALUE,
        valueColors3 };
    dataPanelModelNG3.SetShadowOption(shadowOption3);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode3, nullptr);
    auto dataPanelPaintProperty3 = frameNode3->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty3, nullptr);
    EXPECT_EQ(dataPanelPaintProperty3->GetShadowOptionValue(), shadowOption3);

    DataPanelModelNG dataPanelModelNG4;
    dataPanelModelNG4.Create(VALUES, MAX, TYPE_LINE);
    int length3 = 8;
    std::vector<Gradient> valueColors4;
    GradientColorSet(valueColors4, length3);
    DataPanelShadow shadowOption4 { true, 0.0, 0.0, 0.0, valueColors4 };
    dataPanelModelNG4.SetShadowOption(shadowOption4);
    auto frameNode4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode4, nullptr);
    auto dataPanelPaintProperty4 = frameNode4->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(dataPanelPaintProperty4, nullptr);
    EXPECT_EQ(dataPanelPaintProperty4->GetShadowOptionValue(), shadowOption4);
}
} // namespace OHOS::Ace::NG