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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#define private public
#define protected public
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#undef private
#undef protected

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/components_ng/render/adapter/overlay_modifier.h"
#include "core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr float TEST_WIDTH = 400.0f;
constexpr float TEST_HEIGHT = 300.0f;
constexpr float TEST_CHILD_WIDTH = 200.0f;
constexpr float TEST_CHILD_HEIGHT = 100.0f;
} // namespace

class OverlayModifierTestNg : public testing::Test {};

/**
 * @tc.name: GetOverlayOffsetWithDirection001
 * @tc.desc: Test GetOverlayOffsetWithDirection with TOP_LEFT alignment and PX offset
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection001, TestSize.Level1)
{
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "test";
    overlayOptions.x = Dimension(10.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(20.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::TOP_LEFT;
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = modifier->GetOverlayOffsetWithDirection(parentSize, childSize);

    EXPECT_FLOAT_EQ(offset.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 20.0f);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection002
 * @tc.desc: Test GetOverlayOffsetWithDirection with CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection002, TestSize.Level1)
{
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "test";
    overlayOptions.x = Dimension(0.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(0.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::CENTER;
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = modifier->GetOverlayOffsetWithDirection(parentSize, childSize);

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
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "test";
    overlayOptions.x = Dimension(10.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(20.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::TOP_LEFT;
    overlayOptions.direction = TextDirection::RTL;
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = modifier->GetOverlayOffsetWithDirection(parentSize, childSize);

    float expectedX = -10.0f + (TEST_WIDTH - TEST_CHILD_WIDTH);
    float expectedY = 20.0f;

    EXPECT_FLOAT_EQ(offset.GetX(), expectedX);
    EXPECT_FLOAT_EQ(offset.GetY(), expectedY);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection004
 * @tc.desc: Test GetOverlayOffsetWithDirection with BOTTOM_RIGHT alignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection004, TestSize.Level1)
{
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "test";
    overlayOptions.x = Dimension(15.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(25.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::BOTTOM_RIGHT;
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = modifier->GetOverlayOffsetWithDirection(parentSize, childSize);

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
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "test";
    overlayOptions.x = Dimension(10.0f, DimensionUnit::VP);
    overlayOptions.y = Dimension(20.0f, DimensionUnit::VP);
    overlayOptions.align = Alignment::TOP_LEFT;
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = modifier->GetOverlayOffsetWithDirection(parentSize, childSize);

    EXPECT_GE(offset.GetX(), 0.0f);
    EXPECT_GE(offset.GetY(), 0.0f);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection006
 * @tc.desc: Test GetOverlayOffsetWithDirection with RTL and CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection006, TestSize.Level1)
{
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "test";
    overlayOptions.x = Dimension(10.0f, DimensionUnit::PX);
    overlayOptions.y = Dimension(15.0f, DimensionUnit::PX);
    overlayOptions.align = Alignment::CENTER;
    overlayOptions.direction = TextDirection::RTL;
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = modifier->GetOverlayOffsetWithDirection(parentSize, childSize);

    float expectedX = (TEST_WIDTH - TEST_CHILD_WIDTH) / 2.0f - 10.0f;
    float expectedY = (TEST_HEIGHT - TEST_CHILD_HEIGHT) / 2.0f + 15.0f;

    EXPECT_FLOAT_EQ(offset.GetX(), expectedX);
    EXPECT_FLOAT_EQ(offset.GetY(), expectedY);
}

/**
 * @tc.name: GetOverlayOffsetWithDirection007
 * @tc.desc: Test GetOverlayOffsetWithDirection returns zero offset when property is null
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetOverlayOffsetWithDirection007, TestSize.Level1)
{
    auto modifier = std::make_shared<NG::OverlayTextModifier>();

    NG::SizeF parentSize(TEST_WIDTH, TEST_HEIGHT);
    NG::SizeF childSize(TEST_CHILD_WIDTH, TEST_CHILD_HEIGHT);

    auto offset = modifier->GetOverlayOffsetWithDirection(parentSize, childSize);

    EXPECT_FLOAT_EQ(offset.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 0.0f);
}

/**
 * @tc.name: GetParagraphEmptyContent001
 * @tc.desc: Test GetParagraph returns nullptr for empty content
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetParagraphEmptyContent001, TestSize.Level1)
{
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "";
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    auto paragraph = modifier->GetParagraph(400.0);
    EXPECT_EQ(paragraph, nullptr);
}

/**
 * @tc.name: GetParagraphSizeEmptyContent001
 * @tc.desc: Test GetParagraphSize returns empty SizeF for empty content
 * @tc.type: FUNC
 */
HWTEST_F(OverlayModifierTestNg, GetParagraphSizeEmptyContent001, TestSize.Level1)
{
    auto modifier = std::make_shared<NG::OverlayTextModifier>();
    NG::OverlayOptions overlayOptions;
    overlayOptions.content = "";
    modifier->SetCustomData(NG::OverlayTextData(overlayOptions));

    auto size = modifier->GetParagraphSize(400.0);
    EXPECT_FLOAT_EQ(size.Width(), 0.0f);
    EXPECT_FLOAT_EQ(size.Height(), 0.0f);
}

} // namespace OHOS::Ace
