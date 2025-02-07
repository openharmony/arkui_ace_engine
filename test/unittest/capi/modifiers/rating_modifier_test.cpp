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
    float rating;
    bool indicator;
};
struct RatingOptionsTestRow {
    RatingOptions result;
    RatingOptions input;
    RatingOptions expected;
};
RatingOptionsTestRow RatingOptionsTestRowCreate(
    RatingOptions result,
    RatingOptions input,
    RatingOptions expected)
{
    return {
        .result = result,
        .input = input,
        .expected = expected
    };
}
using TupleOptionsTest = std::tuple<RatingOptions, Opt_RatingOptions, RatingOptions>;
using VectorOptionsTest = std::vector<TupleOptionsTest>;

TupleOptionsTest getTestTuple(const RatingOptionsTestRow& src)
{
    Ark_RatingOptions arkInputValue = {
        .rating = Converter::ArkValue<Ark_Number>(src.input.rating),
        .indicator = Converter::ArkValue<Opt_Boolean>(src.input.indicator)
    };
    auto optInputValue = Converter::ArkValue<Opt_RatingOptions>(arkInputValue);
    return {src.result, optInputValue, src.expected};
}

namespace  {
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_NAME = "starStyle";
    const auto ATTRIBUTE_OPTIONS_RATING_NAME = "rating";
    const auto ATTRIBUTE_OPTIONS_RATING_DEFAULT_VALUE = Converter::ArkValue<Ark_Number>(0.0);
    const auto ATTRIBUTE_OPTIONS_INDICATOR_NAME = "indicator";
    const auto ATTRIBUTE_OPTIONS_INDICATOR_DEFAULT_VALUE = Converter::ArkValue<Opt_Boolean>(false);
    const auto ATTRIBUTE_STARS_NAME = "stars";
    const Ark_Number ATTRIBUTE_STARS_DEFAULT_VALUE = Converter::ArkValue<Ark_Number>(5);
    const auto ATTRIBUTE_STEP_SIZE_NAME = "stepSize";
    const auto ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE = 0.5;
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_NAME = "backgroundUri";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_NAME = "foregroundUri";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME = "secondaryUri";
    const auto ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_DEFAULT_VALUE = "";
    struct EventsTracker {
        static inline GENERATED_ArkUIRatingEventsReceiver ratingEventReceiver {};
        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getRatingEventsReceiver = [] () -> const GENERATED_ArkUIRatingEventsReceiver* {
                return &ratingEventReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class RatingModifierTest : public ModifierTestBase<GENERATED_ArkUIRatingModifier,
    &GENERATED_ArkUINodeModifiers::getRatingModifier, GENERATED_ARKUI_RATING> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
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
    auto rating = std::stod(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_OPTIONS_RATING_NAME));
    bool indicator{false};
    auto indicatorStr = GetAttrValue<std::string>(jsonNode, ATTRIBUTE_OPTIONS_INDICATOR_NAME);
    std::istringstream(indicatorStr) >> std::boolalpha >> indicator;
    double defaultRating = static_cast<double>(Converter::Convert<float>(ATTRIBUTE_OPTIONS_RATING_DEFAULT_VALUE));
    bool defaultIndicator = Converter::Convert<bool>(ATTRIBUTE_OPTIONS_INDICATOR_DEFAULT_VALUE.value);
    EXPECT_EQ(rating, defaultRating);
    EXPECT_EQ(indicator, defaultIndicator);
}

static VectorOptionsTest setRatingOptionsValidValues = {
    getTestTuple(RatingOptionsTestRowCreate({0.0, false}, {0.0, false}, {0.0, false})),
    getTestTuple(RatingOptionsTestRowCreate({0.0, true}, {0.0, true}, {0.0, true})),
    getTestTuple(RatingOptionsTestRowCreate({1.0, false}, {1.0, false}, {1.0, false})),
    getTestTuple(RatingOptionsTestRowCreate({1.0, true}, {1.0, true}, {1.0, true})),
    getTestTuple(RatingOptionsTestRowCreate({2.0, false}, {2.0, false}, {2.0, false})),
    getTestTuple(RatingOptionsTestRowCreate({2.0, true}, {2.0, true}, {2.0, true}))
};

/*
 * @tc.name: setRatingOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setRatingOptionsTestValidValues, TestSize.Level1)
{
    RatingOptions resultValue;
    RatingOptions expectedValue;
    std::unique_ptr<JsonValue> jsonNode;
    // Verifying attribute's  values
    for (auto validValue: setRatingOptionsValidValues) {
        Opt_RatingOptions& optInputValue = std::get<1>(validValue);
        expectedValue = std::get<2>(validValue);
        modifier_->setRatingOptions(node_, &optInputValue);
        jsonNode = GetJsonValue(node_);
        resultValue.rating = std::stod(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_OPTIONS_RATING_NAME));
        auto indicatorStr = GetAttrValue<std::string>(jsonNode, ATTRIBUTE_OPTIONS_INDICATOR_NAME);
        std::istringstream(indicatorStr) >> std::boolalpha >> resultValue.indicator;
        EXPECT_EQ(resultValue.rating, expectedValue.rating) << "Passed value is: " << expectedValue.rating;
        EXPECT_EQ(resultValue.indicator, expectedValue.indicator) << "Passed value is: " << expectedValue.indicator;
    }
}

// Invalid values for attribute 'options' of method 'setRatingOptions'
using TupleInvalidOptionsTest = std::tuple<double, bool, Opt_RatingOptions>;
using VectorInvalidOptionsTest = std::vector<TupleInvalidOptionsTest>;

static VectorOptionsTest setRatingOptionsInvalidValues = {
    {{0.0, false}, Converter::ArkValue<Opt_RatingOptions>(Ark_Empty()), {0.0, false}},
    getTestTuple(RatingOptionsTestRowCreate({0.0, false}, {0.0, false}, {0.0, false})),
    getTestTuple(RatingOptionsTestRowCreate({0.0, false}, {-0.1, false}, {0.0, false})),
    getTestTuple(RatingOptionsTestRowCreate({5.1, false}, {5.1, false}, {5.1, false})),
};

/*
 * @tc.name: setRatingOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setRatingOptionsTestInvalidValues, TestSize.Level1)
{
    RatingOptions resultValue;
    RatingOptions expectedValue;
    std::unique_ptr<JsonValue> jsonNode;
    // Verifying attribute's  values
    for (auto value: setRatingOptionsInvalidValues) {
        Opt_RatingOptions& optInputValue = std::get<1>(value);
        expectedValue = std::get<2>(value);
        modifier_->setRatingOptions(node_, &optInputValue);
        jsonNode = GetJsonValue(node_);
        resultValue.rating = std::stod(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_OPTIONS_RATING_NAME));
        auto indicatorStr = GetAttrValue<std::string>(jsonNode, ATTRIBUTE_OPTIONS_INDICATOR_NAME);
        std::istringstream(indicatorStr) >> std::boolalpha >> resultValue.indicator;
        EXPECT_EQ(resultValue.rating, expectedValue.rating) << "Passed value is: " << expectedValue.rating;
        EXPECT_EQ(resultValue.indicator, expectedValue.indicator) << "Passed value is: " << expectedValue.indicator;
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
    int32_t resultStars = std::stoi(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_STARS_NAME));
    int32_t defaultStars = Converter::Convert<int32_t>(ATTRIBUTE_STARS_DEFAULT_VALUE);

    EXPECT_EQ(resultStars, defaultStars);
}

// Valid values for attribute 'stars' of method 'stars'
static std::vector<std::tuple<int32_t, Ark_Number, int32_t>> starsStarsValidValues = {
    {0, Converter::ArkValue<Ark_Number>(0), 0},
    {1, Converter::ArkValue<Ark_Number>(1), 1},
    {5, Converter::ArkValue<Ark_Number>(5), 5}
};

/*
 * @tc.name: setStarsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    int32_t resultValue;
    int32_t expectedValue;
    Ark_Number inputValueStars;
    Ark_Number initValueStars;

    // Initial setup
    initValueStars = std::get<1>(starsStarsValidValues[0]);

    // Verifying attribute's  values
    inputValueStars = initValueStars;
    for (auto&& value: starsStarsValidValues) {
        inputValueStars = std::get<1>(value);
        modifier_->setStars(node_, &inputValueStars);
        jsonNode = GetJsonValue(node_);
        resultValue = std::stoi(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_STARS_NAME));
        expectedValue = std::get<2>(value);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'stars' of method 'stars'
static std::vector<std::tuple<int32_t, Ark_Number, int32_t>> starsStarsInvalidValues = {
    {5, Converter::ArkValue<Ark_Number>(-1), 5}
};

/*
 * @tc.name: setStarsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarsTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    int32_t resultValue;
    int32_t expectedValue;
    Ark_Number inputValueStars;
    Ark_Number initValueStars;

    // Initial setup
    initValueStars = std::get<1>(starsStarsInvalidValues[0]);

    // Verifying attribute's  values
    inputValueStars = initValueStars;
    for (auto&& value: starsStarsInvalidValues) {
        inputValueStars = std::get<1>(value);
        modifier_->setStars(node_, &inputValueStars);
        jsonNode = GetJsonValue(node_);
        resultValue = std::stoi(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_STARS_NAME));
        expectedValue = std::get<2>(value);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << std::get<0>(value);
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
    auto resultStr = std::stod(GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEP_SIZE_NAME));
    EXPECT_EQ(resultStr, ATTRIBUTE_STEP_SIZE_DEFAULT_VALUE);
}

// Valid values for attribute 'stepSize' of method 'stepSize'
using TupleStepSizeTest = std::tuple<float, Ark_Number, float>;
using VectorStepSizeTest = std::vector<TupleStepSizeTest>;
static VectorStepSizeTest stepSizeStepSizeValidValues = {
    {0.1, Converter::ArkValue<Ark_Number>(0.1), 0.1},
    {0.4, Converter::ArkValue<Ark_Number>(0.4), 0.4},
    {0.5, Converter::ArkValue<Ark_Number>(0.5), 0.5},
    {1.0, Converter::ArkValue<Ark_Number>(1.0), 1.0},
    {5.0, Converter::ArkValue<Ark_Number>(5.0), 5.0},
    {6.0, Converter::ArkValue<Ark_Number>(6.0), 6.0}
};

/*
 * @tc.name: setStepSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStepSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    float resultValue;
    float expectedValue;
    Ark_Number inputValueStepSize;
    Ark_Number initValueStepSize;

    // Initial setup
    initValueStepSize = std::get<1>(stepSizeStepSizeValidValues[0]);

    // Verifying attribute's  values
    inputValueStepSize = initValueStepSize;
    for (auto&& value: stepSizeStepSizeValidValues) {
        inputValueStepSize = std::get<1>(value);
        modifier_->setStepSize(node_, &inputValueStepSize);
        jsonNode = GetJsonValue(node_);
        resultValue = std::stof(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_STEP_SIZE_NAME));
        expectedValue = std::get<2>(value);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << std::get<0>(value);
    }
}

// Valid values for attribute 'stepSize' of method 'stepSize'
static VectorStepSizeTest setStepSizeTestInvalidValues = {
    {0.5, Converter::ArkValue<Ark_Number>(0.099), 0.5},
    {0.5, Converter::ArkValue<Ark_Number>(-0.5), 0.5}
};
/*
 * @tc.name: setStepSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStepSizeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonNode;
    float resultValue;
    float expectedValue;
    Ark_Number inputValueStepSize;
    Ark_Number initValueStepSize;

    // Initial setup
    initValueStepSize = std::get<1>(stepSizeStepSizeValidValues[0]);

    // Verifying attribute's  values
    inputValueStepSize = initValueStepSize;
    for (auto&& value: setStepSizeTestInvalidValues) {
        inputValueStepSize = std::get<1>(value);
        modifier_->setStepSize(node_, &inputValueStepSize);
        jsonNode = GetJsonValue(node_);
        resultValue = std::stof(GetAttrValue<std::string>(jsonNode, ATTRIBUTE_STEP_SIZE_NAME));
        expectedValue = std::get<2>(value);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStarStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setStarStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resStarStyleOptions =
                             GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_DEFAULT_VALUE);
}

// Valid values for attribute 'backgroundUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Ark_String, std::string>> starStyleBackgroundUriValidValues = {
    {"\"\"", Converter::ArkValue<Ark_String>(""), ""},
    {"\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc"},
};

// Valid values for attribute 'foregroundUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Ark_String, std::string>> starStyleForegroundUriValidValues = {
    {"\"\"", Converter::ArkValue<Ark_String>(""), ""},
    {"\"abc\"", Converter::ArkValue<Ark_String>("abc"), "abc"},
};

// Valid values for attribute 'secondaryUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Opt_String, std::string>> starStyleSecondaryUriValidValues = {
    {"\"\"", Converter::ArkValue<Opt_String>(""), ""},
    {"\"abc\"", Converter::ArkValue<Opt_String>("abc"), "abc"},
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
    std::string resultStr;
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
        modifier_->setStarStyle(node_, &inputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_BACKGROUND_URI_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'foregroundUri'  values
    inputValueStarStyleOptions = initValueStarStyleOptions;
    for (auto&& value: starStyleForegroundUriValidValues) {
        inputValueStarStyleOptions.foregroundUri = std::get<1>(value);
        modifier_->setStarStyle(node_, &inputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_FOREGROUND_URI_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'secondaryUri'  values
    inputValueStarStyleOptions = initValueStarStyleOptions;
    for (auto&& value: starStyleSecondaryUriValidValues) {
        inputValueStarStyleOptions.secondaryUri = std::get<1>(value);
        modifier_->setStarStyle(node_, &inputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'secondaryUri' of method 'starStyle'
static std::vector<std::tuple<std::string, Opt_String>> starStyleSecondaryUriInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_String>(Ark_Empty())},
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
    std::string resultStr;
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
        modifier_->setStarStyle(node_, &inputValueStarStyleOptions);
        inputValueStarStyleOptions.secondaryUri = std::get<1>(value);
        modifier_->setStarStyle(node_, &inputValueStarStyleOptions);
        jsonValue = GetJsonValue(node_);
        resStarStyleOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STAR_STYLE_OPTIONS_NAME);
        resultStr = GetAttrValue<std::string>(resStarStyleOptions, ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_NAME);
        expectedStr = ATTRIBUTE_STAR_STYLE_OPTIONS_SECONDARY_URI_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingModifierTest, setOnChangeTest, TestSize.Level1)
{
    Callback_Number_Void func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        float index;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::ratingEventReceiver.onChange = [](Ark_Int32 nodeId, const Ark_Number index)
    {
        checkEvent = {
            .nodeId = nodeId,
            .index = Converter::Convert<float>(index),
        };
    };
    modifier_->setOnChange(node_, &func);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireChangeEvent("55.5");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 55.5);
    eventHub->FireChangeEvent("0.0");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 0.0);
}

// /*
//  * @tc.name: DISABLED_setContentModifierTest
//  * @tc.desc:
//  * @tc.type: FUNC
//  */
HWTEST_F(RatingModifierTest, DISABLED_setContentModifierTest, TestSize.Level1)
{
    // CustomObjects is not implemented yet!
}
} // namespace OHOS::Ace::NG
