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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/panel/sliding_panel_model.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const bool SLIDING_PANEL_LAYOUT_PROPERTY_SHOW = false;
constexpr PanelType PANEL_TYPE_VALUE = PanelType::MINI_BAR;
constexpr PanelMode PANEL_MODE_VALUE = PanelMode::FULL;
const bool SLIDING_PANEL_LAYOUT_PROPERTY_HAS_DRAG_BAR = false;
constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;

constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT_1 = 10.0_px;
constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT_2 = 50.0_px;
constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT_3 = 100.0_px;
const std::vector<Dimension> SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT = { SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT_1,
    SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT_2, SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT_3 };

constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT_1 = 200.0_px;
constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT_2 = 300.0_px;
constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT_3 = 400.0_px;
const std::vector<Dimension> SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT = { SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT_1,
    SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT_2, SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT_3 };

constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT_1 = 400.0_px;
constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT_2 = 600.0_px;
constexpr Dimension SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT_3 = 800.0_px;
const std::vector<Dimension> SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT = { SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT_1,
    SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT_2, SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT_3 };
} // namespace
class PanelPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: SlidingPanelLayoutPropertyTest001
 * @tc.desc: Set show value into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest001, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_LAYOUT_PROPERTY_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto slidingPanelLayoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
}

/**
 * @tc.name: SlidingPanelLayoutPropertyTest002
 * @tc.desc: set panelType value into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest002, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_LAYOUT_PROPERTY_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto slidingPanelLayoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
    EXPECT_EQ(slidingPanelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR), PANEL_TYPE_VALUE);
}

/**
 * @tc.name: SlidingPanelLayoutPropertyTest003
 * @tc.desc: set panelMode value into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest003, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_LAYOUT_PROPERTY_SHOW);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto slidingPanelLayoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
    EXPECT_EQ(slidingPanelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF), PANEL_MODE_VALUE);
}

/**
 * @tc.name: SlidingPanelLayoutPropertyTest004
 * @tc.desc: set hasDragBar value into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest004, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_LAYOUT_PROPERTY_SHOW);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_LAYOUT_PROPERTY_HAS_DRAG_BAR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    auto slidingPanelLayoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
    EXPECT_EQ(slidingPanelLayoutProperty->GetHasDragBar().value_or(true), SLIDING_PANEL_LAYOUT_PROPERTY_HAS_DRAG_BAR);
}

/**
 * @tc.name: SlidingPanelLayoutPropertyTest005
 * @tc.desc: set a lot of miniHeight values into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest005, TestSize.Level1)
{
    for (const auto& miniHeight : SLIDING_PANEL_LAYOUT_PROPERTY_MINI_HEIGHT) {
        SlidingPanelModelNG slidingPanelModelNG;
        slidingPanelModelNG.Create(SLIDING_PANEL_LAYOUT_PROPERTY_SHOW);
        slidingPanelModelNG.SetMiniHeight(miniHeight);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto slidingPanelLayoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
        EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
        EXPECT_EQ(slidingPanelLayoutProperty->GetMiniHeight().value_or(Dimension(BLANK_MIN_HEIGHT)).Value(),
            static_cast<int32_t>(miniHeight.Value()));
    }
}

/**
 * @tc.name: SlidingPanelLayoutPropertyTest006
 * @tc.desc: set a lot of halfHeight values into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest006, TestSize.Level1)
{
    for (const auto& halfHeight : SLIDING_PANEL_LAYOUT_PROPERTY_HALF_HEIGHT) {
        SlidingPanelModelNG slidingPanelModelNG;
        slidingPanelModelNG.Create(SLIDING_PANEL_LAYOUT_PROPERTY_SHOW);
        slidingPanelModelNG.SetHalfHeight(halfHeight);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto slidingPanelLayoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
        EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
        EXPECT_EQ(slidingPanelLayoutProperty->GetHalfHeight().value_or(Dimension(400)).Value(),
            static_cast<int32_t>(halfHeight.Value()));
    }
}

/**
 * @tc.name: SlidingPanelLayoutPropertyTest007
 * @tc.desc: set a lot of fullHeight values into SlidingPanelLayoutProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPropertyTestNg, SlidingPanelLayoutPropertyTest007, TestSize.Level1)
{
    for (const auto& fullHeight : SLIDING_PANEL_LAYOUT_PROPERTY_FULL_HEIGHT) {
        SlidingPanelModelNG slidingPanelModelNG;
        slidingPanelModelNG.Create(SLIDING_PANEL_LAYOUT_PROPERTY_SHOW);
        slidingPanelModelNG.SetFullHeight(fullHeight);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_EQ(frameNode == nullptr, false);
        auto slidingPanelLayoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
        EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
        EXPECT_EQ(slidingPanelLayoutProperty->GetFullHeight().value_or(Dimension(700)).Value(),
            static_cast<int32_t>(fullHeight.Value()));
    }
}
} // namespace OHOS::Ace::NG
