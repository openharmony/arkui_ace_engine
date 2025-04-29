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
#include "core/interfaces/native/implementation/hover_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;

class HoverEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIHoverEventAccessor,
        &GENERATED_ArkUIAccessors::getHoverEventAccessor, HoverEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        eventInfo_ = std::make_unique<HoverInfo>();
        ASSERT_EQ(peer_->GetEventInfo(), nullptr);
        peer_->SetEventInfo(eventInfo_.get());
    }

    std::unique_ptr<HoverInfo> eventInfo_;
};

/**
 * @tc.name: GetStopPropagationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, GetStopPropagationTest, TestSize.Level1)
{
    HoverInfo* eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    Callback_Void callback = accessor_->getStopPropagation(peer_);
    auto callbackHelper = CallbackHelper(callback);
    eventInfo->SetStopPropagation(false);
    EXPECT_FALSE(eventInfo->IsStopPropagation());
    callbackHelper.Invoke();
    EXPECT_TRUE(eventInfo->IsStopPropagation());
    CallbackKeeper::ReleaseReverseCallback<Callback_Void>(callback);
}

/**
 * @tc.name: setXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, setXTestValidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, setXTestInvalidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, getXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetLocalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetX(newValue);
        eventInfo_->SetLocalLocation(location);
        auto result = Converter::OptConvert<double>(accessor_->getX(peer_));
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(result.value(), expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, getXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getX, nullptr);
    auto result = Converter::OptConvert<double>(accessor_->getX(nullptr));
    ASSERT_FALSE(result.has_value());

    peer_->SetEventInfo(nullptr);
    result = Converter::OptConvert<double>(accessor_->getX(peer_));
    ASSERT_FALSE(result.has_value());
}

/**
 * @tc.name: setYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, setYTestValidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, setYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->setY, nullptr);
    auto value = Converter::ArkValue<Ark_Number>(5.0);
    auto value2 = Converter::ArkValue<Ark_Number>(3.0);
    auto expected = 5.0;
    accessor_->setY(peer_, &value);
    auto location = eventInfo_->GetLocalLocation();
    auto result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setY(nullptr, &value2);
    location = eventInfo_->GetLocalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
    accessor_->setY(peer_, nullptr);
    location = eventInfo_->GetLocalLocation();
    result = PipelineBase::Px2VpWithCurrentDensity(location.GetY());
    EXPECT_FLOAT_EQ(result, expected);
}

/**
 * @tc.name: getYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, getYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetLocalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetY(newValue);
        eventInfo_->SetLocalLocation(location);
        auto result = Converter::OptConvert<double>(accessor_->getY(peer_));
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(result.value(), expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, getYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getY, nullptr);
    auto result = Converter::OptConvert<double>(accessor_->getY(nullptr));
    ASSERT_FALSE(result.has_value());

    peer_->SetEventInfo(nullptr);
    result = Converter::OptConvert<double>(accessor_->getY(peer_));
    ASSERT_FALSE(result.has_value());
}

/**
 * @tc.name: setWindowXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, setWindowXTestValidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, setWindowXTestInvalidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, getWindowXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetGlobalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetX(newValue);
        eventInfo_->SetGlobalLocation(location);
        auto result = Converter::OptConvert<double>(accessor_->getWindowX(peer_));
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(result.value(), expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getWindowXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, getWindowXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowX, nullptr);
    auto result = Converter::OptConvert<double>(accessor_->getWindowX(nullptr));
    ASSERT_FALSE(result.has_value());

    peer_->SetEventInfo(nullptr);
    result = Converter::OptConvert<double>(accessor_->getWindowX(peer_));
    ASSERT_FALSE(result.has_value());
}

/**
 * @tc.name: setWindowYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, setWindowYTestValidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, setWindowYTestInvalidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, getWindowYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetGlobalLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetY(newValue);
        eventInfo_->SetGlobalLocation(location);
        auto result = Converter::OptConvert<double>(accessor_->getWindowY(peer_));
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(result.value(), expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getWindowYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, getWindowYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getWindowY, nullptr);
    auto result = Converter::OptConvert<double>(accessor_->getWindowY(nullptr));
    ASSERT_FALSE(result.has_value());

    peer_->SetEventInfo(nullptr);
    result = Converter::OptConvert<double>(accessor_->getWindowY(peer_));
    ASSERT_FALSE(result.has_value());
}

/**
 * @tc.name: setDisplayXTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, setDisplayXTestValidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, setDisplayXTestInvalidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, getDisplayXTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayX, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetScreenLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetX(newValue);
        eventInfo_->SetScreenLocation(location);
        auto result = Converter::OptConvert<double>(accessor_->getDisplayX(peer_));
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(result.value(), expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getDisplayXTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, getDisplayXTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayX, nullptr);
    auto result = Converter::OptConvert<double>(accessor_->getDisplayX(nullptr));
    ASSERT_FALSE(result.has_value());

    peer_->SetEventInfo(nullptr);
    result = Converter::OptConvert<double>(accessor_->getDisplayX(peer_));
    ASSERT_FALSE(result.has_value());
}

/**
 * @tc.name: setDisplayYTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, setDisplayYTestValidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, setDisplayYTestInvalidValues, TestSize.Level1)
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
HWTEST_F(HoverEventAccessorTest, getDisplayYTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayY, nullptr);

    for (auto& [input, value, expected] : testFixtureNumberDoubleValues) {
        Offset location = eventInfo_->GetScreenLocation();
        const auto convValue = Converter::Convert<double>(value);
        const auto newValue = PipelineBase::Vp2PxWithCurrentDensity(convValue);
        location.SetY(newValue);
        eventInfo_->SetScreenLocation(location);
        auto result = Converter::OptConvert<double>(accessor_->getDisplayY(peer_));
        ASSERT_TRUE(result.has_value());
        EXPECT_FLOAT_EQ(result.value(), expected) << "Input value is: " << input;
    }
}

/**
 * @tc.name: getDisplayYTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HoverEventAccessorTest, getDisplayYTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDisplayY, nullptr);
    auto result = Converter::OptConvert<double>(accessor_->getDisplayY(nullptr));
    ASSERT_FALSE(result.has_value());

    peer_->SetEventInfo(nullptr);
    result = Converter::OptConvert<double>(accessor_->getDisplayY(peer_));
    ASSERT_FALSE(result.has_value());
}
}