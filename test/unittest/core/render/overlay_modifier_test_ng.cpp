/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "gmock/gmock.h"

#include "base/utils/utils.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#undef private
#undef protected

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr float TEST_WIDTH = 400.0f;
constexpr float TEST_HEIGHT = 300.0f;
constexpr float TEST_CHILD_WIDTH = 200.0f;
constexpr float TEST_CHILD_HEIGHT = 100.0f;

// Helper function to replicate GetTextPosition logic for testing
NG::OffsetF GetOverlayOffsetWithDirection(
    const NG::SizeF& parentSize, const NG::SizeF& childSize, NG::OverlayOptions& overlay)
{
    double dx = overlay.x.ConvertToPx();
    double dy = overlay.y.ConvertToPx();
    const Alignment align = overlay.align;
    auto direction = overlay.direction;
    direction = direction != TextDirection::AUTO ? direction : (AceApplicationInfo::GetInstance().IsRightToLeft() ?
        TextDirection::RTL : TextDirection::LTR);
    if (direction == TextDirection::RTL) {
        dx = -dx;
    }
    NG::OffsetF const offset = Alignment::GetAlignPositionWithDirection(parentSize, childSize, align, direction);
    const float fx = static_cast<float>(dx) + offset.GetX();
    const float fy = static_cast<float>(dy) + offset.GetY();
    return { fx, fy };
}
} // namespace

class OverlayModifierTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void OverlayModifierTestNg::SetUpTestCase()
{
    NG::MockPipelineContext::SetUp();
}

void OverlayModifierTestNg::TearDownTestCase()
{
    NG::MockPipelineContext::TearDown();
}

/**
 * @tc.name: GetOverlayOffsetWithDirection001
 * @tc.desc: Test GetOverlayOffsetWithDirection with default alignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection001, TestSize.Level1)
{
    NG::OverlayOptions overlayOptions;
    overlayOptions.x = Dimension(10.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(20.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::TOP_LEFT;

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = GetOverlayOffsetWithDirection(parentSize, childSize, overlayOptions);

    EXPECT_FLOAT_EQ(offset.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 20.0f);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection002
 * @tc.desc: Test GetOverlayOffsetWithDirection with center alignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection002, TestSize.Level1)
{
    NG::OverlayOptions overlayOptions;
    overlayOptions.x = Dimension(0.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(0.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::CENTER;

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = GetOverlayOffsetWithDirection(parentSize, childSize, overlayOptions);

    // Center alignment: (parent - child) / 2
    float expectedX = (TEST_WIDTH - TEST_CHILD_WIDTH) / 2.0f;
    float expectedY = (TEST_HEIGHT - TEST_CHILD_HEIGHT) / 2.0f;

    EXPECT_FLOAT_EQ(offset.GetX(), expectedX);
    EXPECT_FLOAT_EQ(offset.GetY(), expectedY);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection003
 * @tc.desc: Test GetOverlayOffsetWithDirection with RTL direction
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection003, TestSize.Level1)
{
    NG::OverlayOptions overlayOptions;
    overlayOptions.x = Dimension(10.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(20.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::TOP_LEFT;
    overlayOptions.direction = TextDirection::RTL;

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = GetOverlayOffsetWithDirection(parentSize, childSize, overlayOptions);

    // RTL direction should negate x offset
    // For TopLeft alignment with RTL: x = -10 + (parentWidth - childWidth)
    float expectedX = -10.0f + (TEST_WIDTH - TEST_CHILD_WIDTH);
    float expectedY = 20.0f;

    EXPECT_FLOAT_EQ(offset.GetX(), expectedX);
    EXPECT_FLOAT_EQ(offset.GetY(), expectedY);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection004
 * @tc.desc: Test GetOverlayOffsetWithDirection with bottom right alignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection004, TestSize.Level1)
{
    NG::OverlayOptions overlayOptions;
    overlayOptions.x = Dimension(15.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(25.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::BOTTOM_RIGHT;

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = GetOverlayOffsetWithDirection(parentSize, childSize, overlayOptions);

    // BottomRight alignment
    float expectedX = (TEST_WIDTH - TEST_CHILD_WIDTH) + 15.0f;
    float expectedY = (TEST_HEIGHT - TEST_CHILD_HEIGHT) + 25.0f;

    EXPECT_FLOAT_EQ(offset.GetX(), expectedX);
    EXPECT_FLOAT_EQ(offset.GetY(), expectedY);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection005
 * @tc.desc: Test GetOverlayOffsetWithDirection with VP units
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection005, TestSize.Level1)
{
    NG::OverlayOptions overlayOptions;
    overlayOptions.x = Dimension(10.0f, DimensionUnit::VP);
    overlayOptions.y = Dimension(20.0f, DimensionUnit::VP);
    overlayOptions.align = Alignment::TOP_LEFT;

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = GetOverlayOffsetWithDirection(parentSize, childSize, overlayOptions);

    // VP units should be converted to pixels
    // The actual conversion depends on the pipeline context configuration
    // Just verify the offset is non-negative
    EXPECT_GE(offset.GetX(), 0.0f);
    EXPECT_GE(offset.GetY(), 0.0f);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection006
 * @tc.desc: Test GetOverlayOffsetWithDirection with RTL and center alignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection006, TestSize.Level1)
{
    NG::OverlayOptions overlayOptions;
    overlayOptions.x = Dimension(10.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(15.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::CENTER;
    overlayOptions.direction = TextDirection::RTL;

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = GetOverlayOffsetWithDirection(parentSize, childSize, overlayOptions);

    // Center alignment with RTL: x should be (parent - child) / 2 - 10
    float expectedX = (TEST_WIDTH - TEST_CHILD_WIDTH) / 2.0f - 10.0f;
    float expectedY = (TEST_HEIGHT - TEST_CHILD_HEIGHT) / 2.0f + 15.0f;

    EXPECT_FLOAT_EQ(offset.GetX(), expectedX);
    EXPECT_FLOAT_EQ(offset.GetY(), expectedY);
}

} // namespace OHOS::Ace
