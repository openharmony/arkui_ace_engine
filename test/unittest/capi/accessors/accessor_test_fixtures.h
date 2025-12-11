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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_ACCESSOR_TEST_FEATURES_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_ACCESSOR_TEST_FEATURES_H

#include <string>
#include <vector>

// sorted part of the code
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/theme/theme_style.h"
#include "core/gestures/drag_event.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG::AccessorTestFixtures {
enum ResAccessorID {
    DIMENSIONS_RES_NON_NEG_0_ID,
    DIMENSIONS_RES_NON_NEG_1_ID,
    DIMENSIONS_RES_NON_NEG_2_ID,
    DIMENSIONS_RES_NON_NEG_3_ID,
    DIMENSIONS_RES_NON_NEG_4_ID,
    DIMENSIONS_RES_NON_NEG_5_ID,
    DIMENSIONS_RES_NON_NEG_6_ID,
    DIMENSIONS_RES_NON_NEG_7_ID,
    DIMENSIONS_RES_NON_NEG_8_ID,
    DIMENSIONS_RES_NON_NEG_9_ID,
    DIMENSIONS_RES_NON_NEG_10_ID,
    DIMENSIONS_RES_NON_NEG_11_ID,
    DIMENSIONS_RES_NON_NEG_12_ID,
    DIMENSIONS_RES_NON_NEG_13_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_0_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_1_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_2_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_3_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_4_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_5_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_6_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_7_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_8_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_9_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_10_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_11_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_12_ID,
    DIMENSIONS_RES_NON_NEG_NON_PCT_13_ID,
    DIMENSIONS_RES_NON_PCT_0_ID,
    DIMENSIONS_RES_NON_PCT_1_ID,
    DIMENSIONS_RES_NON_PCT_2_ID,
    DIMENSIONS_RES_NON_PCT_3_ID,
    DIMENSIONS_RES_NON_PCT_4_ID,
    DIMENSIONS_RES_NON_PCT_5_ID,
    DIMENSIONS_RES_NON_PCT_6_ID,
    DIMENSIONS_RES_NON_PCT_7_ID,
    DIMENSIONS_RES_NON_PCT_8_ID,
    DIMENSIONS_RES_NON_PCT_9_ID,
    DIMENSIONS_RES_NON_PCT_10_ID,
    DIMENSIONS_RES_NON_PCT_11_ID,
    DIMENSIONS_RES_NON_PCT_12_ID,
    DIMENSIONS_RES_NON_PCT_13_ID,
};

inline constexpr auto DIMENSIONS_RES_NON_NEG_0_STR = "DIMENSIONS_RES_NON_NEG_0_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_1_STR = "DIMENSIONS_RES_NON_NEG_1_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_2_STR = "DIMENSIONS_RES_NON_NEG_2_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_3_STR = "DIMENSIONS_RES_NON_NEG_3_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_4_STR = "DIMENSIONS_RES_NON_NEG_4_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_5_STR = "DIMENSIONS_RES_NON_NEG_5_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_6_STR = "DIMENSIONS_RES_NON_NEG_6_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_7_STR = "DIMENSIONS_RES_NON_NEG_7_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_8_STR = "DIMENSIONS_RES_NON_NEG_8_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_9_STR = "DIMENSIONS_RES_NON_NEG_9_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_10_STR = "DIMENSIONS_RES_NON_NEG_10_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_11_STR = "DIMENSIONS_RES_NON_NEG_11_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_12_STR = "DIMENSIONS_RES_NON_NEG_12_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_13_STR = "DIMENSIONS_RES_NON_NEG_13_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR";
inline constexpr auto DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR = "DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_0_STR = "DIMENSIONS_RES_NON_PCT_0_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_1_STR = "DIMENSIONS_RES_NON_PCT_1_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_2_STR = "DIMENSIONS_RES_NON_PCT_2_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_3_STR = "DIMENSIONS_RES_NON_PCT_3_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_4_STR = "DIMENSIONS_RES_NON_PCT_4_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_5_STR = "DIMENSIONS_RES_NON_PCT_5_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_6_STR = "DIMENSIONS_RES_NON_PCT_6_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_7_STR = "DIMENSIONS_RES_NON_PCT_7_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_8_STR = "DIMENSIONS_RES_NON_PCT_8_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_9_STR = "DIMENSIONS_RES_NON_PCT_9_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_10_STR = "DIMENSIONS_RES_NON_PCT_10_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_11_STR = "DIMENSIONS_RES_NON_PCT_11_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_12_STR = "DIMENSIONS_RES_NON_PCT_12_STR";
inline constexpr auto DIMENSIONS_RES_NON_PCT_13_STR = "DIMENSIONS_RES_NON_PCT_13_STR";

using DimensionTestType = std::tuple<std::string, Ark_Number, std::string>;

// Fixture 'Boolean' for type 'Ark_Boolean'
extern const std::vector<std::tuple<std::string, Ark_Boolean, bool>> testFixtureBooleanValues;
extern const std::vector<std::tuple<std::string, Ark_DragBehavior, OHOS::Ace::DragBehavior>>
    testFixtureEnumDragBehaviorValues;
extern const std::vector<DimensionTestType> testFixturesDimensionWithPercentAndNegativeValues;
extern const std::vector<std::tuple<std::string, Ark_Int32, int32_t>> testFixtureInt32WithNegativeValues;
extern const std::vector<std::tuple<std::string, Ark_Number, int32_t>> testFixtureNumberInt32Values;
extern const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberDoubleRoundValues;
extern const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberDoubleValues;
extern const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberValues;
extern const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumber_2x_Values;
// Fixture 'LengthAny' for type 'Ark_Length'
extern const std::vector<std::tuple<std::string, Dimension, Ark_Length>> testFixtureLengthAnyValidValues;
extern const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32Values;
extern const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32_half_Values;
extern const std::vector<std::tuple<std::string, float, float>> testFixtureFloatFloat_half_Values;
extern const std::vector<std::tuple<std::string, double, double, Ark_Int32>> testFixtureVelocity_half_Values;
extern const std::vector<std::tuple<std::string, float, float, float>>
    testFixtureVelocityFloat_half_Values;
extern const std::vector<std::tuple<std::string, double, Ark_Number>> testFixtureNumberFloatAnythingValidValues;
extern const std::vector<std::tuple<std::string, double, Ark_Number>> testFixtureVelocityValues;
extern const std::vector<float> testFixtureFloatValues;
extern const std::vector<std::tuple<std::string, OHOS::Ace::DragBehavior, Ark_DragBehavior>>
    testFixtureEnumArkDragBehaviorValues;
extern const std::vector<std::tuple<int64_t, std::string, ResRawValue>> resourceInitTable;

extern const std::vector<std::tuple<std::string, Ark_ImageSpanAlignment, VerticalAlign>>
    testFixtureVerticalAlignValidValues;
extern const std::vector<std::tuple<std::string, Ark_ImageSpanAlignment, std::optional<VerticalAlign>>>
    testFixtureVerticalAlignInvalidValues;

extern const std::vector<std::tuple<std::string, Ark_ImageFit, ImageFit>> testFixtureObjectFitValidValues;
extern const std::vector<std::tuple<std::string, Ark_ImageFit, std::optional<ImageFit>>>
    testFixtureObjectFitInvalidValues;

extern const std::vector<std::tuple<std::string, Ark_Length, Dimension>> testFixtureDimensionAnyValidValues;

// Fixture 'String' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues;

// Fixture 'DimensionsNumAny' for type 'double'
extern std::vector<std::tuple<std::string, double, std::string>> testFixtureDimensionsNumAnyValidValues;

// Fixture 'DimensionsStrNonPerc' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonPercValidValues;

// Fixture 'DimensionsNumNonNeg' for type 'Ark_Float64'
extern std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureDimensionsNumNonNegValidValues;

// Fixture 'DimensionsStrNonNegNonPct' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonNegNonPctValidValues;

// Fixture 'FontFeature' for type 'Ark_String'
extern std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontFeatureValidValues;
} // namespace OHOS::Ace::NG::AccessorTestFixtures
#endif