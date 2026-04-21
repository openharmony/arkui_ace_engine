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

#include <gtest/gtest.h>
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include <tuple>
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_event_hub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct RatingOptions {
    double rating;
    bool indicator;
};
using TupleOptionsTest = std::tuple<RatingOptions, Opt_RatingOptions, RatingOptions>;
using VectorOptionsTest = std::vector<TupleOptionsTest>;

TupleOptionsTest getTestTuple(const RatingOptions& input, const RatingOptions& expected)
{
    Ark_RatingOptions arkInputValue = {
        .rating = Converter::ArkUnion<Opt_Union_F64_Bindable, Ark_Float64>(input.rating),
        .indicator = Converter::ArkValue<Opt_Boolean>(input.indicator)
    };
    auto optInputValue = Converter::ArkValue<Opt_RatingOptions>(arkInputValue);
    return {input, optInputValue, expected};
}

namespace  {
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_NAME = "starStyle";
    const auto ATTRIBUTE_OPTIONS_RATING_NAME = "rating";
    const auto ATTRIBUTE_OPTIONS_RATING_DEFAULT_VALUE = 0.0;
    const auto ATTRIBUTE_OPTIONS_INDICATOR_NAME = "indicator";
    const auto ATTRIBUTE_OPTIONS_INDICATOR_DEFAULT_VALUE = false;
    const auto ATTRIBUTE_STARS_NAME = "stars";
    const auto ATTRIBUTE_STARS_DEFAULT_VALUE = 5;
    const auto ATTRIBUTE_STEP_SIZE_NAME = "stepSize";
    const auto ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE = 0.5;
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_NAME = "backgroundUri";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_NAME = "foregroundUri";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME = "secondaryUri";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_DEFAULT_VALUE = "";
} // namespace

class RatingModifierTest : public ModifierTestBase<GENERATED_ArkUIRatingModifier,
    &GENERATED_ArkUINodeModifiers::getRatingModifier, GENERATED_ARKUI_RATING> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }

    void SetUp() override
    {
        if (modifier_ == nullptr) {
            GTEST_SKIP() << "Rating modifier not available (dynamic module 'Rating' not loaded in test environment)";
        }
        ModifierTestBase::SetUp();
    }

    void CheckDefaultStarStyle()
    {
        std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
        std::unique_ptr<JsonValue> resStarStyleOptions = GetAttrObject(jsonValue,
            ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resStarStyleOptions,
            ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_NAME);
        EXPECT_THAT(resultStr, Eq(ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_DEFAULT_VALUE));
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_NAME);
        EXPECT_THAT(resultStr, Eq(ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_DEFAULT_VALUE));
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME);
        EXPECT_THAT(resultStr, Eq(ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_DEFAULT_VALUE));
    }
};

/*
 * @tc.name: setRatingOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setRatingOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode = GetJsonValue(node_);
    auto rating = GetAttrValue<double>(jsonNode, ATTRIBUTE_OPTIONS_RATING_NAME);
    auto indicator = GetAttrValue<bool>(jsonNode, ATTRIBUTE_OPTIONS_INDICATOR_NAME);
    EXPECT_THAT(rating, Eq(ATTRIBUTE_OPTIONS_RATING_DEFAULT_VALUE));
    EXPECT_THAT(indicator, Eq(ATTRIBUTE_OPTIONS_INDICATOR_DEFAULT_VALUE));
}

static VectorOptionsTest setRatingOptionsValidValues = {
    getTestTuple({0.0, false}, {0.0, false}),
    getTestTuple({0.0, true}, {0.0, true}),
    getTestTuple({1.0, false}, {1.0, false}),
    getTestTuple({1.0, true}, {1.0, true}),
    getTestTuple({2.0, false}, {2.0, false}),
    getTestTuple({2.0, true}, {2.0, true}),
};

/*
 * @tc.name: setRatingOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setRatingOptionsTestValidValues, TestSize.Level1)
{
    RatingOptions expectedValue;
    std::unique_ptr<JsonValue> jsonNode;
    // Verifying attribute's  values
    for (auto validValue: setRatingOptionsValidValues) {
        Opt_RatingOptions& optInputValue = std::get<1>(validValue);
        expectedValue = std::get<2>(validValue);
        modifier_->setRatingOptions(node_, &optInputValue);
        jsonNode = GetJsonValue(node_);
        auto rating = GetAttrValue<double>(jsonNode, ATTRIBUTE_OPTIONS_RATING_NAME);
        auto indicator = GetAttrValue<bool>(jsonNode, ATTRIBUTE_OPTIONS_INDICATOR_NAME);
        auto input = std::get<0>(validValue);
        EXPECT_THAT(rating, Optional(DoubleEq(expectedValue.rating))) << "Passed value is: " << input.rating;
        EXPECT_THAT(indicator, Eq(expectedValue.indicator)) << "Passed value is: " << input.indicator;
    }
}

// Invalid values for attribute 'options' of method 'setRatingOptions'
using TupleInvalidOptionsTest = std::tuple<double, bool, Opt_RatingOptions>;
using VectorInvalidOptionsTest = std::vector<TupleInvalidOptionsTest>;

static VectorOptionsTest setRatingOptionsInvalidValues = {
    {{0.0, false}, Converter::ArkValue<Opt_RatingOptions>(Ark_Empty()), {0.0, false}},
    getTestTuple({0.0, false}, {0.0, false}),
    getTestTuple({-0.1, false}, {0.0, false}),
    getTestTuple({5.1, false}, {5.1, false}),
};

/*
 * @tc.name: setRatingOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setRatingOptionsTestInvalidValues, TestSize.Level1)
{
    // Verifying attribute's  values
    for (auto value: setRatingOptionsInvalidValues) {
        Opt_RatingOptions& optInputValue = std::get<1>(value);
        auto expectedValue = std::get<2>(value);
        modifier_->setRatingOptions(node_, &optInputValue);
        auto jsonNode = GetJsonValue(node_);
        auto rating = GetAttrValue<double>(jsonNode, ATTRIBUTE_OPTIONS_RATING_NAME);
        auto indicator = GetAttrValue<bool>(jsonNode, ATTRIBUTE_OPTIONS_INDICATOR_NAME);
        auto input = std::get<0>(value);
        EXPECT_THAT(rating, Optional(DoubleEq(expectedValue.rating))) << "Passed value is: " << input.rating;
        EXPECT_THAT(indicator, Eq(expectedValue.indicator)) << "Passed value is: " << input.indicator;
    }
}

/*
 * @tc.name: setStarsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode = GetJsonValue(node_);
    auto resultStars = GetAttrValue<int>(jsonNode, ATTRIBUTE_STARS_NAME);
    EXPECT_THAT(resultStars, Eq(ATTRIBUTE_STARS_DEFAULT_VALUE));
}

// Valid values for attribute 'stars' of method 'stars'
static std::vector<std::tuple<int32_t, Ark_Int32, int32_t>> starsStarsValidValues = {
    {0, Converter::ArkValue<Ark_Int32>(0), 0},
    {1, Converter::ArkValue<Ark_Int32>(1), 1},
    {5, Converter::ArkValue<Ark_Int32>(5), 5}
};

/*
 * @tc.name: setStarsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    std::optional<int> resultValue;
    int32_t expectedValue;

    // Verifying attribute's  values
    for (auto&& value: starsStarsValidValues) {
        auto optInputValueStars = Converter::ArkValue<Opt_Int32>(std::get<1>(value));
        modifier_->setStars(node_, &optInputValueStars);
        jsonNode = GetJsonValue(node_);
        resultValue = GetAttrValue<int>(jsonNode, ATTRIBUTE_STARS_NAME);
        expectedValue = std::get<2>(value);
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStarsTestNullValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarsTestNullValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    std::optional<int> resultValue;
    int32_t expectedValue = ATTRIBUTE_STARS_DEFAULT_VALUE;

    // Initial setup
    auto initValueStars = Converter::ArkValue<Opt_Int32>(std::get<1>(starsStarsValidValues[0]));
    modifier_->setStars(node_, &initValueStars);

    modifier_->setStars(node_, nullptr);
    jsonNode = GetJsonValue(node_);
    resultValue = GetAttrValue<int>(jsonNode, ATTRIBUTE_STARS_NAME);
    EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
}

// Invalid values for attribute 'stars' of method 'stars'
static std::vector<std::tuple<int32_t, Ark_Int32, int32_t>> starsStarsInvalidValues = {
    {ATTRIBUTE_STARS_DEFAULT_VALUE, Converter::ArkValue<Ark_Int32>(-1), ATTRIBUTE_STARS_DEFAULT_VALUE}
};

/*
 * @tc.name: setStarsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarsTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    std::optional<int> resultValue;
    int32_t expectedValue;

    // Verifying attribute's  values
    for (auto&& value: starsStarsInvalidValues) {
        auto optInputValueStars = Converter::ArkValue<Opt_Int32>(std::get<1>(value));
        modifier_->setStars(node_, &optInputValueStars);
        jsonNode = GetJsonValue(node_);
        resultValue = GetAttrValue<int>(jsonNode, ATTRIBUTE_STARS_NAME);
        expectedValue = std::get<2>(value);
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStepSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStepSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<double>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME);
    EXPECT_THAT(resultStr, Eq(ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE));
}

// Valid values for attribute 'stepSize' of method 'stepSize'
static std::vector<std::tuple<double, Ark_Float64, double>> stepSizeStepSizeValidValues = {
    {0.1, Converter::ArkValue<Ark_Float64>(0.1), 0.1},
    {0.4, Converter::ArkValue<Ark_Float64>(0.4), 0.4},
    {0.5, Converter::ArkValue<Ark_Float64>(0.5), 0.5},
    {1.0, Converter::ArkValue<Ark_Float64>(1.0), 1.0},
    {5.0, Converter::ArkValue<Ark_Float64>(5.0), 5.0},
    {6.0, Converter::ArkValue<Ark_Float64>(6.0), 6.0}
};

/*
 * @tc.name: setStepSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStepSizeTestValidValues, TestSize.Level1)
{
    // Verifying attribute's  values
    for (auto&& value: stepSizeStepSizeValidValues) {
        auto optInputValueStepSize = Converter::ArkValue<Opt_Float64>(std::get<1>(value));
        modifier_->setStepSize(node_, &optInputValueStepSize);
        auto jsonNode = GetJsonValue(node_);
        auto resultValue = GetAttrValue<double>(jsonNode, ATTRIBUTE_STEP_SIZE_NAME);
        auto expectedValue = std::get<2>(value);
        EXPECT_THAT(resultValue, Optional(DoubleEq(expectedValue))) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStepSizeTestNullValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStepSizeTestNullValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    std::optional<int> resultValue;
    int32_t expectedValue = ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE;

    modifier_->setStepSize(node_, nullptr);
    jsonNode = GetJsonValue(node_);
    resultValue = GetAttrValue<int>(jsonNode, ATTRIBUTE_STEP_SIZE_NAME);
    EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
}

// Valid values for attribute 'stepSize' of method 'stepSize'
static std::vector<std::tuple<float, Ark_Float64, double>> setStepSizeTestInvalidValues = {
    {0.5, Converter::ArkValue<Ark_Float64>(0.099), 0.5},
    {0.5, Converter::ArkValue<Ark_Float64>(-0.5), 0.5}
};
/*
 * @tc.name: setStepSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStepSizeTestInvalidValues, TestSize.Level1)
{
    // Verifying attribute's  values
    for (auto&& value: setStepSizeTestInvalidValues) {
        auto optInputValueStepSize = Converter::ArkValue<Opt_Float64>(std::get<1>(value));
        modifier_->setStepSize(node_, &optInputValueStepSize);
        auto jsonNode = GetJsonValue(node_);
        auto resultValue = GetAttrValue<double>(jsonNode, ATTRIBUTE_STEP_SIZE_NAME);
        auto expectedValue = std::get<2>(value);
        EXPECT_THAT(resultValue, Optional(DoubleEq(expectedValue))) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStarStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarStyleTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setStarStyle, nullptr);
    CheckDefaultStarStyle();
}

// Valid values for attribute 'backgroundUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Opt_ResourceStr, std::string>> starStyleBackgroundUriValidValues = {
    {"\"\"", Converter::ArkUnion<Opt_ResourceStr, Ark_String>(""), ""},
    {"\"abc\"", Converter::ArkUnion<Opt_ResourceStr, Ark_String>("abc"), "abc"},
};

// Valid values for attribute 'foregroundUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Opt_ResourceStr, std::string>> starStyleForegroundUriValidValues = {
    {"\"\"", Converter::ArkUnion<Opt_ResourceStr, Ark_String>(""), ""},
    {"\"abc\"", Converter::ArkUnion<Opt_ResourceStr, Ark_String>("abc"), "abc"},
};

// Valid values for attribute 'secondaryUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Opt_ResourceStr, std::string>> starStyleSecondaryUriValidValues = {
    {"\"\"", Converter::ArkUnion<Opt_ResourceStr, Ark_String>(""), ""},
    {"\"abc\"", Converter::ArkUnion<Opt_ResourceStr, Ark_String>("abc"), "abc"},
};

/*
 * @tc.name: setStarStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarStyleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resStarStyleOptions;
    std::optional<std::string> resultStr;
    std::string expectedStr;
    Ark_StarStyleOptions inputValueStarStyleOptions;
    Ark_StarStyleOptions initValueStarStyleOptions;

    // Initial setup
    initValueStarStyleOptions.backgroundUri = std::get<1>(starStyleBackgroundUriValidValues[0]);
    initValueStarStyleOptions.foregroundUri = std::get<1>(starStyleForegroundUriValidValues[0]);
    initValueStarStyleOptions.secondaryUri = std::get<1>(starStyleSecondaryUriValidValues[0]);

    // Verifying attribute's 'backgroundUri'  values
    inputValueStarStyleOptions = initValueStarStyleOptions;
    for (auto&& value: starStyleBackgroundUriValidValues) {
        inputValueStarStyleOptions.backgroundUri = std::get<1>(value);
        auto optInputValueStarStyleOptions = Converter::ArkValue<Opt_StarStyleOptions>(inputValueStarStyleOptions);
        modifier_->setStarStyle(node_, &optInputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrObject(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_THAT(resultStr, Eq(expectedStr)) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'foregroundUri'  values
    inputValueStarStyleOptions = initValueStarStyleOptions;
    for (auto&& value: starStyleForegroundUriValidValues) {
        inputValueStarStyleOptions.foregroundUri = std::get<1>(value);
        auto optInputValueStarStyleOptions = Converter::ArkValue<Opt_StarStyleOptions>(inputValueStarStyleOptions);
        modifier_->setStarStyle(node_, &optInputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrObject(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_THAT(resultStr, Eq(expectedStr)) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'secondaryUri'  values
    inputValueStarStyleOptions = initValueStarStyleOptions;
    for (auto&& value: starStyleSecondaryUriValidValues) {
        inputValueStarStyleOptions.secondaryUri = std::get<1>(value);
        auto optInputValueStarStyleOptions = Converter::ArkValue<Opt_StarStyleOptions>(inputValueStarStyleOptions);
        modifier_->setStarStyle(node_, &optInputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrObject(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_THAT(resultStr, Eq(expectedStr)) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStarStyleTestNullValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarStyleTestNullValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setStarStyle, nullptr);
    std::unique_ptr<JsonValue> jsonNode;
    modifier_->setStarStyle(node_, nullptr);
    CheckDefaultStarStyle();
}


// Invalid values for attribute 'secondaryUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Opt_ResourceStr>> starStyleSecondaryUriInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_ResourceStr>(Ark_Empty())},
};

/*
 * @tc.name: setStarStyleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarStyleTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resStarStyleOptions;
    std::optional<std::string> resultStr;
    std::string expectedStr;
    Ark_StarStyleOptions inputValueStarStyleOptions;
    Ark_StarStyleOptions initValueStarStyleOptions;

    // Initial setup
    initValueStarStyleOptions.backgroundUri = std::get<1>(starStyleBackgroundUriValidValues[0]);
    initValueStarStyleOptions.foregroundUri = std::get<1>(starStyleForegroundUriValidValues[0]);
    initValueStarStyleOptions.secondaryUri = std::get<1>(starStyleSecondaryUriValidValues[0]);

    // Verifying attribute's 'secondaryUri'  values
    for (auto&& value: starStyleSecondaryUriInvalidValues) {
        inputValueStarStyleOptions = initValueStarStyleOptions;
        auto optInputValueStarStyleOptions = Converter::ArkValue<Opt_StarStyleOptions >(inputValueStarStyleOptions);
        modifier_->setStarStyle(node_, &optInputValueStarStyleOptions);
        inputValueStarStyleOptions.secondaryUri = std::get<1>(value);
        optInputValueStarStyleOptions = Converter::ArkValue<Opt_StarStyleOptions >(inputValueStarStyleOptions);
        modifier_->setStarStyle(node_, &optInputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrObject(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME);
        expectedStr = ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_DEFAULT_VALUE;
        EXPECT_THAT(resultStr, Eq(expectedStr)) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setOnChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        float index;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    OnRatingChangeCallback onChangeCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Float64 index) {
            checkEvent = CheckEvent{
                .nodeId = nodeId,
                .index = Converter::Convert<float>(index)
            };
        }
    };
    auto optOnChangeCallback = Converter::ArkValue<Opt_OnRatingChangeCallback>(onChangeCallback);
    modifier_->setOnChange(node_, &optOnChangeCallback);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireChangeEvent("55.5");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_FLOAT_EQ(checkEvent->index, 55.5);
    eventHub->FireChangeEvent("0.0");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 0.0);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: set_onChangeEvent_ratingTestValidCallback
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, set_onChangeEvent_ratingTestValidCallback, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        float value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Number parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<float>(parameter)
        };
    };

    Callback_Number_Void arkCallback = Converter::ArkValue<Callback_Number_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_rating(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent("55.5");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_NEAR(checkEvent->value, 55.5f, FLT_EPSILON);
}
#endif
} // namespace OHOS::Ace::NG
