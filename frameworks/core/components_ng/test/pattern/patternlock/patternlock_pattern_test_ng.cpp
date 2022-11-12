/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const Dimension SIDE_LENGTH = 300.0_vp;
const Dimension CIRCLE_RADIUS = 14.0_vp;
const Color REGULAR_COLOR = Color::BLACK;
const Color SELECTED_COLOR = Color::BLACK;
const Color ACTIVE_COLOR = Color::BLACK;
const Color PATH_COLOR = Color::BLUE;
const Dimension PATH_STROKE_WIDTH = 34.0_vp;
} // namespace

struct TestProperty {
    std::optional<Dimension> sideLength = std::nullopt;
    std::optional<Dimension> circleRadius = std::nullopt;
    std::optional<Color> regularColor = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> activeColor = std::nullopt;
    std::optional<Color> pathColor = std::nullopt;
    std::optional<Dimension> strokeWidth = std::nullopt;
    std::optional<bool> autoReset = std::nullopt;
};

class PatternLockPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void PatternLockPropertyTestNg::SetUpTestCase() {}
void PatternLockPropertyTestNg::TearDownTestCase() {}
void PatternLockPropertyTestNg::SetUp() {}
void PatternLockPropertyTestNg::TearDown() {}

/**
 * @tc.name: PatternLockPaintPropertyTest001
 * @tc.desc: Set PatternLock value into PatternLockPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPropertyTestNg, PatternLockPaintPropertyTest001, TestSize.Level1)
{
    PatternLockModelNG patternLockModelNG;
    auto controller = patternLockModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    TestProperty testProperty;
    testProperty.sideLength = std::make_optional(SIDE_LENGTH);
    testProperty.circleRadius = std::make_optional(CIRCLE_RADIUS);
    testProperty.regularColor = std::make_optional(REGULAR_COLOR);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.activeColor = std::make_optional(ACTIVE_COLOR);
    testProperty.pathColor = std::make_optional(PATH_COLOR);
    testProperty.strokeWidth = std::make_optional(PATH_STROKE_WIDTH);
    testProperty.autoReset = std::make_optional(true);
    EXPECT_TRUE(testProperty.sideLength.has_value());
    patternLockModelNG.SetSideLength(testProperty.sideLength.value());
    patternLockModelNG.SetCircleRadius(testProperty.circleRadius.value());
    patternLockModelNG.SetRegularColor(testProperty.regularColor.value());
    patternLockModelNG.SetSelectedColor(testProperty.selectedColor.value());
    patternLockModelNG.SetActiveColor(testProperty.activeColor.value());
    patternLockModelNG.SetPathColor(testProperty.pathColor.value());
    patternLockModelNG.SetStrokeWidth(testProperty.strokeWidth.value());
    patternLockModelNG.SetAutoReset(testProperty.autoReset.value());

    auto patternLockPaintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    EXPECT_FALSE(patternLockPaintProperty == nullptr);
    EXPECT_EQ(patternLockPaintProperty->GetSideLengthValue(), SIDE_LENGTH);
    EXPECT_EQ(patternLockPaintProperty->GetCircleRadiusValue(), CIRCLE_RADIUS);
    EXPECT_EQ(patternLockPaintProperty->GetRegularColorValue(), REGULAR_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetSelectedColorValue(), SELECTED_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetActiveColorValue(), ACTIVE_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetPathColorValue(), PATH_COLOR);
    EXPECT_EQ(patternLockPaintProperty->GetPathStrokeWidthValue(), PATH_STROKE_WIDTH);
    EXPECT_EQ(patternLockPaintProperty->GetAutoResetValue(), true);
}

} // namespace OHOS::Ace::NG