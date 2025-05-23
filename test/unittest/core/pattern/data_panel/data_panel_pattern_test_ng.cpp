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

#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"

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
#include "test/mock/core/common/mock_container.h"
#include "test/unittest/core/pattern/test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::vector<double> VALUES = { 1.0, 2.0, 3.0, 4.0 };
constexpr double MAX = 200.0;
constexpr double VALUE = 200.0;
const std::vector<double> SINGLE_VALUES = { 1.0 };
const std::vector<double> FULL_VALUES = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
const std::vector<double> LONG_VALUES = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
constexpr size_t TYPE_LINE = 1;
constexpr float MAX_WIDTH = 400.0f;
constexpr float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float MAX_PERCENT_WIDTH = 200.0f;
constexpr float MAX_PERCENT_HEIGHT = 200.0f;
const SizeF MAX_PERCENT_SIZE(MAX_PERCENT_WIDTH, MAX_PERCENT_HEIGHT);
constexpr float MAX_INFINITE = 1000000.0f;
const SizeF MAX_INFINITE_SIZE(MAX_INFINITE, MAX_INFINITE);
const OffsetF OFFSET = { 1.0f, 1.0f };
} // namespace

class DataPanelTestNg : public testing::Test {
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

/**
 * @tc.name: DataPanelPatternTest001
 * @tc.desc: Test UpdateTrackBackground
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create data panel and get frameNode
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. get pattern and test UpdateTrackBackground
     */
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);
    
    Color testColor = Color::RED;
    pattern->UpdateTrackBackground(testColor, true); // isFirstLoad = true
    
    /**
     * @tc.expected: step3. property updated and node marked dirty when rerenderable
     */
    auto paintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetTrackBackground(), testColor);
    
    // Test with isFirstLoad = false
    Color testColor2 = Color::BLUE;
    pattern->UpdateTrackBackground(testColor2, false);
    EXPECT_EQ(paintProperty->GetTrackBackground(), testColor); // should not update
}

/**
 * @tc.name: DataPanelPatternTest002
 * @tc.desc: Test UpdateStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelTestNg, DataPanelPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create data panel and get frameNode
     */
    DataPanelModelNG dataPanel;
    dataPanel.Create(VALUES, MAX, TYPE_LINE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. get pattern and test UpdateStrokeWidth
     */
    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);
    
    CalcDimension strokeWidth(VALUE);
    pattern->UpdateStrokeWidth(strokeWidth, true); // isFirstLoad = true
    
    /**
     * @tc.expected: step3. property updated and node marked dirty when rerenderable
     */
    auto paintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetStrokeWidth(), strokeWidth);
    
    // Test with isFirstLoad = false
    CalcDimension strokeWidth2(VALUE);
    pattern->UpdateStrokeWidth(strokeWidth2, false);
    EXPECT_EQ(paintProperty->GetStrokeWidth(), strokeWidth); // should not update
}
} // namespace OHOS::Ace::NG