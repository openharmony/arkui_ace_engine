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

#include "accessor_test_fixtures.h"
#include "accessor_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::AccessorTestFixtures {
using namespace Converter;
// Fixture 'Boolean' for type 'Ark_Boolean'
const std::vector<std::tuple<std::string, Ark_Boolean, bool>> testFixtureBooleanValues = {
    { "true", ArkValue<Ark_Boolean>(true), true },
    { "false", ArkValue<Ark_Boolean>(false), false },
};

const std::vector<float> testFixtureFloatValues = { 1.24f, 0.f, 100.f, -20.65f };

const std::vector<std::tuple<std::string, Ark_Int32, int32_t>> testFixtureInt32WithNegativeValues = {
    { "0", ArkValue<Ark_Int32>(0), 0 },
    { "INT32_MIN", ArkValue<Ark_Int32>(INT32_MIN), INT32_MIN },
    { "32", ArkValue<Ark_Int32>(32), 32 },
    { "-1", ArkValue<Ark_Int32>(-1), -1 },
    { "INT32_MAX", ArkValue<Ark_Int32>(INT32_MAX), INT32_MAX },
};

const std::vector<std::tuple<std::string, Ark_Number, int32_t>> testFixtureNumberInt32Values = {
    { "0", ArkValue<Ark_Number>(0), 0 },
    { "INT32_MIN", ArkValue<Ark_Number>(INT32_MIN), INT32_MIN },
    { "32", ArkValue<Ark_Number>(32), 32 },
    { "-1", ArkValue<Ark_Number>(-1), -1 },
    { "INT32_MAX", ArkValue<Ark_Number>(INT32_MAX), INT32_MAX },
};

const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberDoubleRoundValues = {
    { "5.0", Converter::ArkValue<Ark_Number>(5), 5.0 },
    { "2.4", Converter::ArkValue<Ark_Number>(2.4), 2.0 },
    { "1.0", Converter::ArkValue<Ark_Number>(1), 1.0 },
    { "0.0", Converter::ArkValue<Ark_Number>(0), 0.0 },
    { "-1.0", Converter::ArkValue<Ark_Number>(-1), -1.0 },
    { "-2.4", Converter::ArkValue<Ark_Number>(-2.4), -2.0 },
    { "-5.0", Converter::ArkValue<Ark_Number>(-5), -5.0 },
};

const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberDoubleValues = {
    { "5.0", Converter::ArkValue<Ark_Number>(5), 5.0 },
    { "2.4", Converter::ArkValue<Ark_Number>(2.4), 2.4 },
    { "1.0", Converter::ArkValue<Ark_Number>(1), 1.0 },
    { "0.0", Converter::ArkValue<Ark_Number>(0), 0.0 },
    { "-1.0", Converter::ArkValue<Ark_Number>(-1), -1.0 },
    { "-2.4", Converter::ArkValue<Ark_Number>(-2.4), -2.4 },
    { "-5.0", Converter::ArkValue<Ark_Number>(-5), -5.0 },
};

const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumberValues = {
    { "1.24", ArkValue<Ark_Number>(1.24), 1.24 },
    { "0", ArkValue<Ark_Number>(0), 0 },
    { "100", ArkValue<Ark_Number>(100), 100 },
    { "-20.65", ArkValue<Ark_Number>(-20.65), -20.65 },
};

const std::vector<std::tuple<std::string, Ark_Number, double>> testFixtureNumber_2x_Values = {
    { "1.24", ArkValue<Ark_Number>(1.24), 2.48 },
    { "0", ArkValue<Ark_Number>(0), 0 },
    { "100", ArkValue<Ark_Number>(100), 200 },
    { "-20.65", ArkValue<Ark_Number>(-20.65), -41.30 },
};

const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32Values = {
    { "1.24", 1.24, ArkValue<Ark_Int32>(1) },
    { "0", 0, ArkValue<Ark_Int32>(0) },
    { "100", 100, ArkValue<Ark_Int32>(100) },
    { "-20.65", -20.65, ArkValue<Ark_Int32>(-20) },
};

const std::vector<std::tuple<std::string, double, Ark_Int32>> testFixtureDoubleArkInt32_half_Values = {
    { "4.4", 4.4, ArkValue<Ark_Int32>(2) },
    { "0", 0, ArkValue<Ark_Int32>(0) },
    { "100", 100, ArkValue<Ark_Int32>(50) },
    { "-20.65", -20.65, ArkValue<Ark_Int32>(-10) },
};

const std::vector<std::tuple<std::string, float, float>> testFixtureFloatFloat_half_Values = {
    { "100.", 100., 50. },
    { "0.", 0., 0. },
    { "-100.", -100., -50. },
    { "12.34", 12.34, 6.17 },
    { "-56.73", -56.73, -28.365 },
};

const std::vector<std::tuple<std::string, double, double, Ark_Int32>> testFixtureVelocity_half_Values = {
    { "[30., 40.]", 30., 40., ArkValue<Ark_Int32>(25) },
    { "[-30., 0.]", 30., 0., ArkValue<Ark_Int32>(15) },
    { "[0., 40.]", 0., 40., ArkValue<Ark_Int32>(20) },
    { "[0., 0.]", 0., 0., ArkValue<Ark_Int32>(0) },
};

const std::vector<std::tuple<std::string, float, float, float>> testFixtureVelocityFloat_half_Values = {
    { "[30., 40.]", 30., 40., 25. },
    { "[-30., 0.]", 30., 0., 15. },
    { "[0., 40.]", 0., 40., 20. },
    { "[0., 0.]", 0., 0., 0. },
};

const std::vector<std::tuple<std::string, double, Ark_Number>> testFixtureNumberFloatAnythingValidValues = {
    { "100.", 100., ArkValue<Ark_Number>(100.) },
    { "0.", 0., ArkValue<Ark_Number>(0.) },
    { "-100.", -100., ArkValue<Ark_Number>(-100.) },
    { "12.34", 12.34, ArkValue<Ark_Number>(12.34) },
    { "-56.73", -56.73, ArkValue<Ark_Number>(-56.73) },
};

const std::vector<std::tuple<std::string, double, Ark_Number>> testFixtureVelocityValues = {
    { "100", 100, ArkValue<Ark_Number>(std::sqrt((100 * 100) + (100 * 100))) },
    { "0", 0, ArkValue<Ark_Number>(0) },
    { "-100", -100, ArkValue<Ark_Number>(std::sqrt((100 * 100) + (100 * 100))) },
    { "12.34", 12.34, ArkValue<Ark_Number>(std::sqrt((12.34 * 12.34) + (12.34 * 12.34))) },
    { "-56.73", -56.34, ArkValue<Ark_Number>(std::sqrt((56.34 * 56.34) + (56.34 * 56.34))) },
};

const std::vector<std::tuple<std::string, Ark_DragBehavior, OHOS::Ace::DragBehavior>>
    testFixtureEnumDragBehaviorValues = {
    { "ARK_DRAG_BEHAVIOR_MOVE", ARK_DRAG_BEHAVIOR_MOVE, OHOS::Ace::DragBehavior::MOVE },
    { "ARK_DRAG_BEHAVIOR_COPY", ARK_DRAG_BEHAVIOR_COPY, OHOS::Ace::DragBehavior::COPY },
    { "-1", static_cast<Ark_DragBehavior>(OHOS::Ace::DragBehavior::UNKNOWN), OHOS::Ace::DragBehavior::COPY },
};

const std::vector<std::tuple<std::string, OHOS::Ace::DragBehavior, Ark_DragBehavior>>
    testFixtureEnumArkDragBehaviorValues = {
    { "ARK_DRAG_BEHAVIOR_COPY", OHOS::Ace::DragBehavior::COPY, ARK_DRAG_BEHAVIOR_COPY },
    { "ARK_DRAG_BEHAVIOR_MOVE", OHOS::Ace::DragBehavior::MOVE, ARK_DRAG_BEHAVIOR_MOVE },
    { "-1", OHOS::Ace::DragBehavior::UNKNOWN, ARK_DRAG_BEHAVIOR_COPY },
};

// Fixture 'ImageSpanVerticalAlign' for type 'Ark_ImageSpanAlignment'
const std::vector<std::tuple<std::string, Ark_ImageSpanAlignment, VerticalAlign>>
    testFixtureVerticalAlignValidValues = {
        { "ARK_IMAGE_SPAN_ALIGNMENT_TOP", ARK_IMAGE_SPAN_ALIGNMENT_TOP, VerticalAlign::TOP },
        { "ARK_IMAGE_SPAN_ALIGNMENT_CENTER", ARK_IMAGE_SPAN_ALIGNMENT_CENTER, VerticalAlign::CENTER },
        { "ARK_IMAGE_SPAN_ALIGNMENT_BOTTOM", ARK_IMAGE_SPAN_ALIGNMENT_BOTTOM, VerticalAlign::BOTTOM },
        { "ARK_IMAGE_SPAN_ALIGNMENT_BASELINE", ARK_IMAGE_SPAN_ALIGNMENT_BASELINE, VerticalAlign::BASELINE },
    };

const std::vector<std::tuple<std::string, Ark_ImageSpanAlignment, std::optional<VerticalAlign>>>
    testFixtureVerticalAlignInvalidValues = {
        { "ARK_IMAGE_SPAN_ALIGNMENT_INVALID", INVALID_ENUM_VAL<Ark_ImageSpanAlignment>, std::nullopt }
};

// Valid values for attribute 'objectFit' of method 'objectFit'
const std::vector<std::tuple<std::string, Ark_ImageFit, ImageFit>> testFixtureObjectFitValidValues = {
    { "ARK_IMAGE_FIT_CONTAIN", ARK_IMAGE_FIT_CONTAIN, ImageFit::CONTAIN },
    { "ARK_IMAGE_FIT_COVER", ARK_IMAGE_FIT_COVER, ImageFit::COVER },
    { "ARK_IMAGE_FIT_AUTO", ARK_IMAGE_FIT_AUTO, ImageFit::FITWIDTH },
    { "ARK_IMAGE_FIT_FILL", ARK_IMAGE_FIT_FILL, ImageFit::FILL },
    { "ARK_IMAGE_FIT_SCALE_DOWN", ARK_IMAGE_FIT_SCALE_DOWN, ImageFit::SCALE_DOWN },
    { "ARK_IMAGE_FIT_NONE", ARK_IMAGE_FIT_NONE, ImageFit::NONE },
    { "ARK_IMAGE_FIT_TOP_START", ARK_IMAGE_FIT_TOP_START, ImageFit::TOP_LEFT },
    { "ARK_IMAGE_FIT_TOP", ARK_IMAGE_FIT_TOP, ImageFit::TOP },
    { "ARK_IMAGE_FIT_TOP_END", ARK_IMAGE_FIT_TOP_END, ImageFit::TOP_END },
    { "ARK_IMAGE_FIT_START", ARK_IMAGE_FIT_START, ImageFit::START },
    { "ARK_IMAGE_FIT_CENTER", ARK_IMAGE_FIT_CENTER, ImageFit::CENTER },
    { "ARK_IMAGE_FIT_END", ARK_IMAGE_FIT_END, ImageFit::END },
    { "ARK_IMAGE_FIT_BOTTOM_START", ARK_IMAGE_FIT_BOTTOM_START,
        ImageFit::BOTTOM_START },
    { "ARK_IMAGE_FIT_BOTTOM", ARK_IMAGE_FIT_BOTTOM, ImageFit::BOTTOM },
    { "ARK_IMAGE_FIT_BOTTOM_END", ARK_IMAGE_FIT_BOTTOM_END, ImageFit::BOTTOM_END },
};

// Invalid values for attribute 'objectFit' of method 'objectFit'
const std::vector<std::tuple<std::string, Ark_ImageFit, std::optional<ImageFit>>> testFixtureObjectFitInvalidValues = {
    {"static_cast<Ark_ImageFit>(-1)", INVALID_ENUM_VAL<Ark_ImageFit>, std::nullopt },
};

const std::vector<std::tuple<std::string, Ark_Length, Dimension>> testFixtureDimensionAnyValidValues = {
    { "123.0vp", Converter::ArkValue<Ark_Length>("123.0vp"), 123.0_vp },
    { "0.0vp", Converter::ArkValue<Ark_Length>("0.0vp"), 0.0_vp },
    { "1.23vp", Converter::ArkValue<Ark_Length>("1.23vp"), 1.23_vp },
    { "123.0fp", Converter::ArkValue<Ark_Length>("123.0fp"), 123.0_fp },
    { "0.0fp", Converter::ArkValue<Ark_Length>("0.0fp"), 0.0_fp },
    { "1.23fp", Converter::ArkValue<Ark_Length>("1.23fp"), 1.23_fp },
    { "123.0px", Converter::ArkValue<Ark_Length>("123.0px"), 123.0_px },
    { "0.0px", Converter::ArkValue<Ark_Length>("0.0px"), 0.0_px },
    { "1.23px", Converter::ArkValue<Ark_Length>("1.23px"), 1.23_px },
    { "-2.3vp", Converter::ArkValue<Ark_Length>("-2.3vp"), -2.3_vp },
    { "-4.5fp", Converter::ArkValue<Ark_Length>("-4.5fp"), -4.5_fp },
    { "-5.6px", Converter::ArkValue<Ark_Length>("-5.6px"), -5.6_px },
    { "50%", Converter::ArkValue<Ark_Length>("50%"), 0.5_pct },
    { "0%", Converter::ArkValue<Ark_Length>("0%"), 0.0_pct },
    { "-80%", Converter::ArkValue<Ark_Length>("-80%"), -0.8_pct }
};

const std::vector<std::tuple<int64_t, std::string, ResRawValue>> resourceInitTable = {
    { DIMENSIONS_RES_NON_NEG_0_ID, DIMENSIONS_RES_NON_NEG_0_STR, 123._vp },
    { DIMENSIONS_RES_NON_NEG_1_ID, DIMENSIONS_RES_NON_NEG_1_STR, 0._vp },
    { DIMENSIONS_RES_NON_NEG_2_ID, DIMENSIONS_RES_NON_NEG_2_STR, 1.23_vp },
    { DIMENSIONS_RES_NON_NEG_3_ID, DIMENSIONS_RES_NON_NEG_3_STR, 123._fp },
    { DIMENSIONS_RES_NON_NEG_4_ID, DIMENSIONS_RES_NON_NEG_4_STR, 0._fp },
    { DIMENSIONS_RES_NON_NEG_5_ID, DIMENSIONS_RES_NON_NEG_5_STR, 1.23_fp },
    { DIMENSIONS_RES_NON_NEG_6_ID, DIMENSIONS_RES_NON_NEG_6_STR, 123._px },
    { DIMENSIONS_RES_NON_NEG_7_ID, DIMENSIONS_RES_NON_NEG_7_STR, 0._px },
    { DIMENSIONS_RES_NON_NEG_8_ID, DIMENSIONS_RES_NON_NEG_8_STR, 1.23_px },
    { DIMENSIONS_RES_NON_NEG_9_ID, DIMENSIONS_RES_NON_NEG_9_STR, 0.2_pct },
    { DIMENSIONS_RES_NON_NEG_10_ID, DIMENSIONS_RES_NON_NEG_10_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_11_ID, DIMENSIONS_RES_NON_NEG_11_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_12_ID, DIMENSIONS_RES_NON_NEG_12_STR, -123._px },
    { DIMENSIONS_RES_NON_NEG_13_ID, DIMENSIONS_RES_NON_NEG_13_STR, -0.2_pct },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_0_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_0_STR, 123._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_1_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_1_STR, 0._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_2_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_2_STR, 1.23_vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_3_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_3_STR, 123._fp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_4_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_4_STR, 0._fp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_5_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_5_STR, 1.23_fp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_6_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_6_STR, 123._px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_7_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_7_STR, 0._px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_8_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_8_STR, 1.23_px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_9_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_9_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_10_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_10_STR, -123._vp },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_11_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_11_STR, -123._px },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_12_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_12_STR, 0.2_pct },
    { DIMENSIONS_RES_NON_NEG_NON_PCT_13_ID, DIMENSIONS_RES_NON_NEG_NON_PCT_13_STR, -0.2_pct },
    { DIMENSIONS_RES_NON_PCT_0_ID, DIMENSIONS_RES_NON_PCT_0_STR, 123._vp },
    { DIMENSIONS_RES_NON_PCT_1_ID, DIMENSIONS_RES_NON_PCT_1_STR, 0._vp },
    { DIMENSIONS_RES_NON_PCT_2_ID, DIMENSIONS_RES_NON_PCT_2_STR, 1.23_vp },
    { DIMENSIONS_RES_NON_PCT_3_ID, DIMENSIONS_RES_NON_PCT_3_STR, 123._fp },
    { DIMENSIONS_RES_NON_PCT_4_ID, DIMENSIONS_RES_NON_PCT_4_STR, 0._fp },
    { DIMENSIONS_RES_NON_PCT_5_ID, DIMENSIONS_RES_NON_PCT_5_STR, 1.23_fp },
    { DIMENSIONS_RES_NON_PCT_6_ID, DIMENSIONS_RES_NON_PCT_6_STR, 123._px },
    { DIMENSIONS_RES_NON_PCT_7_ID, DIMENSIONS_RES_NON_PCT_7_STR, 0._px },
    { DIMENSIONS_RES_NON_PCT_8_ID, DIMENSIONS_RES_NON_PCT_8_STR, 1.23_px },
    { DIMENSIONS_RES_NON_PCT_9_ID, DIMENSIONS_RES_NON_PCT_9_STR, -123._vp },
    { DIMENSIONS_RES_NON_PCT_10_ID, DIMENSIONS_RES_NON_PCT_10_STR, -123._fp },
    { DIMENSIONS_RES_NON_PCT_11_ID, DIMENSIONS_RES_NON_PCT_11_STR, -123._px },
    { DIMENSIONS_RES_NON_PCT_12_ID, DIMENSIONS_RES_NON_PCT_12_STR, 0.2_pct },
    { DIMENSIONS_RES_NON_PCT_13_ID, DIMENSIONS_RES_NON_PCT_13_STR, -0.2_pct },
};

const std::vector<DimensionTestType> testFixturesDimensionWithPercentAndNegativeValues = {
    { "1.24", ArkValue<Ark_Number>(1.24f), "1.24px" },
    { "0", ArkValue<Ark_Number>(0), "0.00px" },
    { "100", ArkValue<Ark_Number>(100), "100.00px" },
    { "-20.65", ArkValue<Ark_Number>(-20.65), "-20.65px" },
};

const std::vector<std::tuple<std::string, Dimension, Ark_Length>> testFixtureLengthAnyValidValues = {
    { "123.0_vp", 123.0_vp, Converter::ArkValue<Ark_Length>("123.0vp") },
    { "0.0_vp", 0.0_vp, Converter::ArkValue<Ark_Length>("0.0vp") },
    { "1.23_vp", 1.23_vp, Converter::ArkValue<Ark_Length>("1.23vp") },
    { "123.0_fp", 123.0_fp, Converter::ArkValue<Ark_Length>("123.0fp") },
    { "0.0_fp", 0.0_fp, Converter::ArkValue<Ark_Length>("0.0fp") },
    { "1.23_fp", 1.23_fp, Converter::ArkValue<Ark_Length>("1.23fp") },
    { "123.0_px", 123.0_px, Converter::ArkValue<Ark_Length>("123.0px") },
    { "0.0_px", 0.0_px, Converter::ArkValue<Ark_Length>("0.0px") },
    { "1.23_px", 1.23_px, Converter::ArkValue<Ark_Length>("1.23px") },
    { "-2.3_vp", -2.3_vp, Converter::ArkValue<Ark_Length>("-2.3vp") },
    { "-4.5_fp", -4.5_fp, Converter::ArkValue<Ark_Length>("-4.5fp") },
    { "-5.6_px", -5.6_px, Converter::ArkValue<Ark_Length>("-5.6px") },
    { "0.5_pct", 0.5_pct, Converter::ArkValue<Ark_Length>("50%") },
    { "0.0_pct", 0.0_pct, Converter::ArkValue<Ark_Length>("0%") },
    { "-0.8_pct", -0.8_pct, Converter::ArkValue<Ark_Length>("-80%") },
};

// Fixture 'String' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc" },
    { "\"\"", Converter::ArkValue<Ark_String>(""), "" },
    { "\"xyz\"", Converter::ArkValue<Ark_String>("xyz"), "xyz" },
};

// Fixture 'DimensionsNumAny' for type 'double'
std::vector<std::tuple<std::string, double, std::string>> testFixtureDimensionsNumAnyValidValues = {
    { "123", 123, "123.00vp" },
    { "0", 0, "0.00vp" },
    { "1.23", 1.23, "1.23vp" },
    { "-2", -2, "-2.00vp" },
    { "-3.45", -3.45, "-3.45vp" },
};

// Fixture 'DimensionsStrNonPerc' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonPercValidValues = {
    { "\"123vp\"", Converter::ArkValue<Ark_String>("123vp"), "123.00vp" },
    { "\"0_fp\"", Converter::ArkValue<Ark_String>("0fp"), "0.00fp" },
    { "\"1.23_fp\"", Converter::ArkValue<Ark_String>("1.23fp"), "1.23fp" },
};

// Fixture 'DimensionsNumNonNeg' for type 'Ark_Float64'
std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureDimensionsNumNonNegValidValues = {
    { "123", 123, "123.00vp" },
    { "0", 0, "0.00vp" },
    { "1.23", 1.23, "1.23vp" },
};

// Fixture 'DimensionsStrNonNegNonPct' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureDimensionsStrNonNegNonPctValidValues = {
    { "\"123vp\"", Converter::ArkValue<Ark_String>("123vp"), "123.00vp" },
    { "\"0vp\"", Converter::ArkValue<Ark_String>("0vp"), "0.00vp" },
    { "\"1.23vp\"", Converter::ArkValue<Ark_String>("1.23vp"), "1.23vp" },
    { "\"123fp\"", Converter::ArkValue<Ark_String>("123fp"), "123.00fp" },
    { "\"0fp\"", Converter::ArkValue<Ark_String>("0fp"), "0.00fp" },
    { "\"1.23fp\"", Converter::ArkValue<Ark_String>("1.23fp"), "1.23fp" },
    { "\"123px\"", Converter::ArkValue<Ark_String>("123px"), "123.00px" },
    { "\"0px\"", Converter::ArkValue<Ark_String>("0px"), "0.00px" },
    { "\"1.23px\"", Converter::ArkValue<Ark_String>("1.23px"), "1.23px" },
    { "\"123lpx\"", Converter::ArkValue<Ark_String>("123lpx"), "123.00lpx" },
    { "\"0lpx\"", Converter::ArkValue<Ark_String>("0lpx"), "0.00lpx" },
    { "\"1.23lpx\"", Converter::ArkValue<Ark_String>("1.23lpx"), "1.23lpx" },
};

// Fixture 'FontFeature' for type 'Ark_String'
std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFontFeatureValidValues = {
    { "\"'ss01' on\"", Converter::ArkValue<Ark_String>("'ss01' on"), "'ss01' 1" },
    { "\"'ss01' off\"", Converter::ArkValue<Ark_String>("'ss01' off"), "'ss01' 0" },
    { "\"'ss01' 1\"", Converter::ArkValue<Ark_String>("'ss01' 1"), "'ss01' 1" },
    { "\"'ss01' 0\"", Converter::ArkValue<Ark_String>("'ss01' 0"), "'ss01' 0" },
    { "\"'ss01' on, 'ss02' on\"", Converter::ArkValue<Ark_String>("'ss01' on, 'ss02' on"), "'ss01' 1,'ss02' 1" },
    { "\"'ss01' on, 'ss02' off\"", Converter::ArkValue<Ark_String>("'ss01' on, 'ss02' off"), "'ss01' 1,'ss02' 0" },
    { "\"'ss01' on, ss02 off\"", Converter::ArkValue<Ark_String>("'ss01' on, ss02 off"), "'ss01' 1" },
    { "\"'ss01' on\"", Converter::ArkValue<Ark_String>("'ss01' on"), "'ss01' 1" },
};
} // namespace OHOS::Ace::NG::AccessorTestFixtures
