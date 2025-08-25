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
#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/axis_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"


namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;

namespace {
    const std::vector<std::tuple<std::string, Ark_AxisAction, AxisAction>> testFixtureAxisValidValues = {
        { "ARK_AXIS_ACTION_NONE", ARK_AXIS_ACTION_NONE, AxisAction::NONE },
        { "ARK_AXIS_ACTION_BEGIN", ARK_AXIS_ACTION_BEGIN, AxisAction::BEGIN },
        { "ARK_AXIS_ACTION_UPDATE", ARK_AXIS_ACTION_UPDATE, AxisAction::UPDATE },
        { "ARK_AXIS_ACTION_END", ARK_AXIS_ACTION_END, AxisAction::END },
        { "ARK_AXIS_ACTION_CANCEL", ARK_AXIS_ACTION_CANCEL, AxisAction::CANCEL },
    };
    const std::vector<std::tuple<std::string, Ark_AxisAction, AxisAction>> testFixtureAxisInvalidValues = {
        { "ARK_AXIS_INVALID", Converter::INVALID_ENUM_VAL<Ark_AxisAction>, AxisAction::NONE },
    };
} // namespace

class AxisEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIAxisEventAccessor,
        &GENERATED_ArkUIAccessors::getAxisEventAccessor, AxisEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        eventInfo_ = std::make_unique<AxisInfo>();
        ASSERT_EQ(peer_->GetEventInfo(), nullptr);
        peer_->SetEventInfo(eventInfo_.get());
    }

    std::unique_ptr<AxisInfo> eventInfo_;
};

/**
 * @tc.name: GetPropagationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, GetPropagationTest, TestSize.Level1)
{
    AxisInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    ASSERT_NE(accessor_->getPropagation, nullptr);
    Callback_Void callback = accessor_->getPropagation(peer_);
    auto callbackHelper = CallbackHelper(callback);
    eventInfo->SetStopPropagation(true);
    EXPECT_TRUE(eventInfo->IsStopPropagation());
    callbackHelper.Invoke();
    EXPECT_FALSE(eventInfo->IsStopPropagation());
    CallbackKeeper::ReleaseReverseCallback<Callback_Void>(callback);
}

/**
 * @tc.name: setXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        accessor_->setX(peer_, &value);
        const auto location = eventInfo_->GetLocalLocation();
        const auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setX, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5.0);
    auto value2 = Converter::ArkValue<Ark_Number>(3.0);
    auto expected = 5.0;
    accessor_->setX(peer_, &value);
    auto location = eventInfo_->GetLocalLocation();
    auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setX(nullptr, &value2);
    location = eventInfo_->GetLocalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setX(peer_, nullptr);
    location = eventInfo_->GetLocalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
}

/**
 * @tc.name: getXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetLocalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetX(newValue);
        eventInfo_->SetLocalLocation(location);
        auto result = Converter::Convert<double>(accessor_->getX(peer_));
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getX, nullptr);
    const auto defaultValue = Converter::ArkValue<Ark_Number>(0);
    auto result = Converter::Convert<double>(accessor_->getX(nullptr));
    EXPECT_FLOAT_EQ(result, Converter::Convert<double>(defaultValue));

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<double>(accessor_->getX(peer_));
    EXPECT_FLOAT_EQ(result, Converter::Convert<double>(defaultValue));
}

/**
 * @tc.name: setYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        accessor_->setY(peer_, &value);
        const auto location = eventInfo_->GetLocalLocation();
        const auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setY, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5.0);
    auto value2 = Converter::ArkValue<Ark_Number>(3.0);
    auto expected = 5.0;
    accessor_->setY(peer_, &value);
    auto location = eventInfo_->GetLocalLocation();
    auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected) << "Input value is: 5.0";
    accessor_->setY(nullptr, &value2);
    location = eventInfo_->GetLocalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected) << "Input value is: 3.0";
    accessor_->setY(peer_, nullptr);
    location = eventInfo_->GetLocalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected) << "Input value is: nullptr";
}

/**
 * @tc.name: getYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetLocalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetY(newValue);
        eventInfo_->SetLocalLocation(location);
        auto result = Converter::Convert<double>(accessor_->getY(peer_));
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getY, nullptr);
    const auto defaultValue = Converter::ArkValue<Ark_Number>(0);
    auto result = Converter::Convert<double>(accessor_->getY(nullptr));
    EXPECT_FLOAT_EQ(result, Converter::Convert<double>(defaultValue));

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<double>(accessor_->getY(peer_));
    EXPECT_FLOAT_EQ(result, Converter::Convert<double>(defaultValue));
}

/**
 * @tc.name: setWindowXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setWindowXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWindowX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        accessor_->setWindowX(peer_, &value);
        const auto location = eventInfo_->GetGlobalLocation();
        const auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setWindowXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setWindowXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWindowX, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5.0);
    auto value2 = Converter::ArkValue<Ark_Number>(3.0);
    auto expected = 5.0;
    accessor_->setWindowX(peer_, &value);
    auto location = eventInfo_->GetGlobalLocation();
    auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setWindowX(nullptr, &value2);
    location = eventInfo_->GetGlobalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setWindowX(peer_, nullptr);
    location = eventInfo_->GetGlobalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
}

/**
 * @tc.name: getWindowXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getWindowXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetGlobalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetX(newValue);
        eventInfo_->SetGlobalLocation(location);
        auto result = Converter::Convert<double>(accessor_->getWindowX(peer_));
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getWindowXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getWindowXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowX, nullptr);
    auto result = Converter::Convert<double>(accessor_->getWindowX(nullptr));
    EXPECT_FLOAT_EQ(result, 0.0);

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<double>(accessor_->getWindowX(peer_));
    EXPECT_FLOAT_EQ(result, 0.0);
}

/**
 * @tc.name: setWindowYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setWindowYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWindowY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        accessor_->setWindowY(peer_, &value);
        const auto location = eventInfo_->GetGlobalLocation();
        const auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setWindowYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setWindowYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setWindowY, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5.0);
    auto value2 = Converter::ArkValue<Ark_Number>(3.0);
    auto expected = 5.0;
    accessor_->setWindowY(peer_, &value);
    auto location = eventInfo_->GetGlobalLocation();
    auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setWindowY(nullptr, &value2);
    location = eventInfo_->GetGlobalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setWindowY(peer_, nullptr);
    location = eventInfo_->GetGlobalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
}

/**
 * @tc.name: getWindowYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getWindowYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetGlobalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetY(newValue);
        eventInfo_->SetGlobalLocation(location);
        auto result = Converter::Convert<double>(accessor_->getWindowY(peer_));
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getWindowYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getWindowYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowY, nullptr);
    auto result = Converter::Convert<double>(accessor_->getWindowY(nullptr));
    EXPECT_FLOAT_EQ(result, 0.0);

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<double>(accessor_->getWindowY(peer_));
    EXPECT_FLOAT_EQ(result, 0.0);
}

/**
 * @tc.name: setDisplayXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setDisplayXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDisplayX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        accessor_->setDisplayX(peer_, &value);
        const auto location = eventInfo_->GetScreenLocation();
        const auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setDisplayXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setDisplayXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDisplayX, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5.0);
    auto value2 = Converter::ArkValue<Ark_Number>(3.0);
    auto expected = 5.0;
    accessor_->setDisplayX(peer_, &value);
    auto location = eventInfo_->GetScreenLocation();
    auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setDisplayX(nullptr, &value2);
    location = eventInfo_->GetScreenLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setDisplayX(peer_, nullptr);
    location = eventInfo_->GetScreenLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetX());
    EXPECT_FLOAT_EQ(result, expected);
}

/**
 * @tc.name: getDisplayXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getDisplayXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetScreenLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetX(newValue);
        eventInfo_->SetScreenLocation(location);
        auto result = Converter::Convert<double>(accessor_->getDisplayX(peer_));
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getDisplayXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getDisplayXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayX, nullptr);
    auto result = Converter::Convert<double>(accessor_->getDisplayX(nullptr));
    EXPECT_FLOAT_EQ(result, 0.0);

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<double>(accessor_->getDisplayX(peer_));
    EXPECT_FLOAT_EQ(result, 0.0);
}

/**
 * @tc.name: setDisplayYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setDisplayYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDisplayY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        accessor_->setDisplayY(peer_, &value);
        const auto location = eventInfo_->GetScreenLocation();
        const auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setDisplayYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setDisplayYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDisplayY, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5.0);
    auto value2 = Converter::ArkValue<Ark_Number>(3.0);
    auto expected = 5.0;
    accessor_->setDisplayY(peer_, &value);
    auto location = eventInfo_->GetScreenLocation();
    auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setDisplayY(nullptr, &value2);
    location = eventInfo_->GetScreenLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setDisplayY(peer_, nullptr);
    location = eventInfo_->GetScreenLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
}

/**
 * @tc.name: getDisplayYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getDisplayYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetScreenLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetY(newValue);
        eventInfo_->SetScreenLocation(location);
        auto result = Converter::Convert<double>(accessor_->getDisplayY(peer_));
        EXPECT_FLOAT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getDisplayYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getDisplayYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayY, nullptr);
    auto result = Converter::Convert<double>(accessor_->getDisplayY(nullptr));
    EXPECT_FLOAT_EQ(result, 0.0);

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<double>(accessor_->getDisplayY(peer_));
    EXPECT_FLOAT_EQ(result, 0.0);
}

/**
 * @tc.name: setScrollStepTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setScrollStepTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setScrollStep, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberInt32Values) {
        accessor_->setScrollStep(peer_, &value);
        const auto result = eventInfo_->GetScrollStep();
        EXPECT_EQ(result, 0) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setScrollStepTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setScrollStepTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setScrollStep, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5);
    auto value2 = Converter::ArkValue<Ark_Number>(3);
    auto expected = 0;
    accessor_->setScrollStep(peer_, &value);
    auto result = eventInfo_->GetScrollStep();
    EXPECT_EQ(result, expected);
    accessor_->setScrollStep(nullptr, &value2);
    result = eventInfo_->GetScrollStep();
    EXPECT_EQ(result, expected);
    accessor_->setScrollStep(peer_, nullptr);
    result = eventInfo_->GetScrollStep();
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: getScrollStepTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getScrollStepTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScrollStep, nullptr);
    auto result = Converter::OptConvert<int32_t>(accessor_->getScrollStep(peer_));
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 0);
}

/**
 * @tc.name: getScrollStepTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getScrollStepTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScrollStep, nullptr);
    auto result = Converter::OptConvert<int32_t>(accessor_->getScrollStep(nullptr));
    ASSERT_FALSE(result.has_value());

    peer_->SetEventInfo(nullptr);
    result = Converter::OptConvert<int32_t>(accessor_->getScrollStep(peer_));
    ASSERT_FALSE(result.has_value());
}


/**
 * @tc.name: getHorizontalAxisValueTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getHorizontalAxisValueTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getHorizontalAxisValue, nullptr);

    for (auto& [input, expected, value] : testFixtureNumberDoubleValues) {
        eventInfo_->SetHorizontalAxis(value);
        auto result = Converter::Convert<float>(accessor_->getHorizontalAxisValue(peer_));
        EXPECT_FLOAT_EQ(result, Converter::Convert<float>(expected)) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getHorizontalAxisValueTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getHorizontalAxisValueTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getHorizontalAxisValue, nullptr);
    auto result = Converter::Convert<float>(accessor_->getHorizontalAxisValue(nullptr));
    EXPECT_FLOAT_EQ(result, 0);

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<float>(accessor_->getHorizontalAxisValue(peer_));
    EXPECT_FLOAT_EQ(result, 0);
}

/**
 * @tc.name: getVerticalAxisValueTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getVerticalAxisValueTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getVerticalAxisValue, nullptr);

    for (auto& [input, expected, value] : testFixtureNumberDoubleValues) {
        eventInfo_->SetVerticalAxis(value);
        auto result = Converter::Convert<float>(accessor_->getVerticalAxisValue(peer_));
        EXPECT_FLOAT_EQ(result, Converter::Convert<float>(expected)) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getVerticalAxisValueTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getVerticalAxisValueTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getVerticalAxisValue, nullptr);
    auto result = Converter::Convert<float>(accessor_->getVerticalAxisValue(nullptr));
    EXPECT_FLOAT_EQ(result, 0);

    peer_->SetEventInfo(nullptr);
    result = Converter::Convert<float>(accessor_->getVerticalAxisValue(peer_));
    EXPECT_FLOAT_EQ(result, 0);
}

/**
 * @tc.name: setActionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setActionTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setAction, nullptr);

    for (auto& [input, value, expected] : testFixtureAxisValidValues) {
        accessor_->setAction(peer_, value);
        const auto result = eventInfo_->GetAction();
        EXPECT_EQ(result, expected) << "Input value is: " << input;
    }

    for (auto& [input, value, expected] : testFixtureAxisInvalidValues) {
        accessor_->setAction(peer_, value);
        const auto result = eventInfo_->GetAction();
        EXPECT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: setActionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, setActionTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setAction, nullptr);
    auto expected = AxisAction::BEGIN;
    accessor_->setAction(peer_, ARK_AXIS_ACTION_BEGIN);
    auto result = eventInfo_->GetAction();
    EXPECT_EQ(result, expected);
    accessor_->setAction(nullptr, ARK_AXIS_ACTION_UPDATE);
    result = eventInfo_->GetAction();
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: getActionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getActionTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getAction, nullptr);

    for (auto& [input, expected, value] : testFixtureAxisValidValues) {
        eventInfo_->SetAction(value);
        auto result = accessor_->getAction(peer_);
        EXPECT_EQ(result, expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getActionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AxisEventAccessorTest, getActionTestInvalidValues, TestSize.Level1)
{
    auto expected = static_cast<Ark_AxisAction>(-1);
    auto invalidEnumValue = static_cast<AxisAction>(1000);
    eventInfo_->SetAction(invalidEnumValue);
    ASSERT_NE(accessor_->getAction, nullptr);
    auto result = accessor_->getAction(peer_);
    EXPECT_EQ(result, expected);

    result = accessor_->getAction(nullptr);
    EXPECT_EQ(result, expected);

    peer_->SetEventInfo(nullptr);
    result = accessor_->getAction(peer_);
    EXPECT_EQ(result, expected);
}
}