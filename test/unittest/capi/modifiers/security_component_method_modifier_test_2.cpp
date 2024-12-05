/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "security_component_method_modifier_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace TestConst::SecurityComponentMethod;

typedef std::pair<Ark_Length, std::string> MarginPaddingOneTestStep;
static const std::vector<MarginPaddingOneTestStep> LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(1), "1.00px" },
    { Converter::ArkValue<Ark_Length>(-1), "-1.00px" },
    { Converter::ArkValue<Ark_Length>(0), "0.00px" },
    { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
    { Converter::ArkValue<Ark_Length>(-2.45f), "-2.45vp" },
    { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
    { Converter::ArkValue<Ark_Length>(-5.0_px), "-5.00px" },
    { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
    { Converter::ArkValue<Ark_Length>(-22.35_px), "-22.35px" },
    { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
    { Converter::ArkValue<Ark_Length>(-7.0_vp), "-7.00vp" },
    { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
    { Converter::ArkValue<Ark_Length>(-1.65_vp), "-1.65vp" },
    { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
    { Converter::ArkValue<Ark_Length>(-65.0_fp), "-65.00fp" },
    { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
    { Converter::ArkValue<Ark_Length>(-4.3_fp), "-4.30fp" },
    { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
    { { .type = ARK_TAG_RESOURCE, .resource = FLOAT_RES_0_ID }, "70.50px" },
};

using LengthMetrictsTestStep = std::pair<Ark_LengthMetrics, std::string>;
static const std::vector<LengthMetrictsTestStep> LENGTH_METRICS_ANY_TEST_PLAN = {
    { {.unit = ARK_LENGTH_UNIT_PX, .value = Converter::ArkValue<Ark_Number>(1)}, "1.00px" },
    { {.unit = ARK_LENGTH_UNIT_PX, .value = Converter::ArkValue<Ark_Number>(0)}, "0.00px" },
    { {.unit = ARK_LENGTH_UNIT_VP, .value = Converter::ArkValue<Ark_Number>(2.45f)}, "2.45vp" },
    { {.unit = ARK_LENGTH_UNIT_VP, .value = Converter::ArkValue<Ark_Number>(-7.f)}, "-7.00vp" },
    { {.unit = ARK_LENGTH_UNIT_FP, .value = Converter::ArkValue<Ark_Number>(-65.5f)}, "-65.50fp" },
};

/*
 * @tc.name: setOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
    auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
    EXPECT_EQ(xResult, ATTRIBUTE_OFFSET_X_DEFAULT_VALUE);
    auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
    EXPECT_EQ(yResult, ATTRIBUTE_OFFSET_Y_DEFAULT_VALUE);
}

/*
 * @tc.name: setOffsetTestValidPositionXValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidPositionXValues, TestSize.Level1)
{
    Ark_Position position;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        position.x = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        position.y = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
        EXPECT_EQ(xResult, expected);
        auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
        EXPECT_EQ(yResult, "0.00px");
    }
}

/*
 * @tc.name: setOffsetTestValidPositionYValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidPositionYValues, TestSize.Level1)
{
    Ark_Position position;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        position.x = Converter::ArkValue<Opt_Length>(Ark_Empty());
        position.y = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
        EXPECT_EQ(xResult, "0.00px");
        auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
        EXPECT_EQ(yResult, expected);
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesLeftValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesLeftValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, expected);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesTopValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesTopValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, expected);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesRightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesRightValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, expected);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesBottomValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesBottomValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, expected);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesStartValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesStartValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.start = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), defaultValue);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesEndValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesEndValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.end = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), defaultValue);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesTopValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesTopValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.top = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), defaultValue);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesBottomValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesBottomValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.bottom = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), expected);
    }
}
} // namespace OHOS::Ace::NG