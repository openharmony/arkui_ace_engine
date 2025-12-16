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

#include <algorithm>
#include "accessor_test_base.h"
#include "accessor_test_utils.h"
#include "core/interfaces/native/implementation/linear_gradient_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    std::vector<std::pair<std::string, float>> validValues = {
        std::make_pair("#FF0000FF", 0.5f),
        std::make_pair("#FFFF0000", 1.f),
    };

    std::vector<std::pair<Ark_Color, float>> validValues2 = {
        std::make_pair(Ark_Color::ARK_COLOR_BLUE, 0.5f),
        std::make_pair(Ark_Color::ARK_COLOR_RED, 1.f),
    };

    std::vector<std::pair<int32_t, float>> validValues3 = {
        std::make_pair(0xFF0000FF, 0.5f),
        std::make_pair(0xFFFF0000, 1.f),

    };

    const auto TEST_COLOR_BLUE = Color::BLUE;
    const auto TEST_COLOR_RED = Color::RED;
    const auto COLOR_RES_NAME_BLUE = "color_res_name_blue";
    const auto COLOR_RES_NAME_RED = "color_res_name_red";

    std::vector<std::pair<Ark_Resource, float>> validValues4 = {
        std::make_pair(CreateResource(COLOR_RES_NAME_BLUE, ResourceType::COLOR), 0.5f),
        std::make_pair(CreateResource(COLOR_RES_NAME_RED, ResourceType::COLOR), 1.f),

    };

    std::vector<std::pair<std::string, float>> invalidValues = {
        std::make_pair("", -0.5f),
        std::make_pair("", 5.f),
    };
}

class LinearGradientAccessorTest
    : public AccessorTestBaseParent<GENERATED_ArkUILinearGradientAccessor,
        &GENERATED_ArkUIAccessors::getLinearGradientAccessor, LinearGradientPeer> {
public:
    static void SetUpTestCase()
    {
        AccessorTestBaseParent::SetUpTestCase();
        AddResource(COLOR_RES_NAME_BLUE, TEST_COLOR_BLUE);
        AddResource(COLOR_RES_NAME_RED, TEST_COLOR_RED);
    }

    void FinalizePeer()
    {
        if (peer_) {
            ASSERT_NE(finalyzer_, nullptr);
            finalyzer_(peer_);
            peer_ = nullptr;
        }
    }
};

/**
 * @tc.name: CtorColorArkStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LinearGradientAccessorTest, CtorColorArkStringTest, TestSize.Level1)
{
    std::vector<Ark_ColorStop> vectorData;
    for (const auto& pairItem : validValues) {
        auto colorStop = Ark_ColorStop {
            .color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<0>(pairItem)),
            .offset = Converter::ArkValue<Opt_Length>(std::get<1>(pairItem)),
        };
        vectorData.push_back(colorStop);
    }

    Converter::ArkArrayHolder<Array_ColorStop> vectorHolder(vectorData);
    Array_ColorStop colorStopArray = vectorHolder.ArkValue();
    peer_ = reinterpret_cast<LinearGradientPeer*>(accessor_->construct(&colorStopArray));
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStops = peer_->colorStops;

    for (size_t idx = 0; idx < validValues.size(); idx++) {
        ASSERT_TRUE(std::get<0>(colorStops.at(idx)).has_value());
        EXPECT_EQ(std::get<0>(colorStops.at(idx)).value().ToString(), std::get<0>(validValues.at(idx)));
        EXPECT_EQ(std::get<1>(colorStops.at(idx)).Value(), std::get<1>(validValues.at(idx)));
    }
}

/**
 * @tc.name: CtorColorArkColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LinearGradientAccessorTest, CtorColorArkColorTest, TestSize.Level1)
{
    std::vector<Ark_ColorStop> vectorData;
    for (const auto& pairItem : validValues2) {
        auto colorStop = Ark_ColorStop {
            .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<0>(pairItem)),
            .offset = Converter::ArkValue<Opt_Length>(std::get<1>(pairItem)),
        };
        vectorData.push_back(colorStop);
    }

    Converter::ArkArrayHolder<Array_ColorStop> vectorHolder(vectorData);
    Array_ColorStop colorStopArray = vectorHolder.ArkValue();
    peer_ = reinterpret_cast<LinearGradientPeer*>(accessor_->construct(&colorStopArray));
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStops = peer_->colorStops;

    for (size_t idx = 0; idx < validValues2.size(); idx++) {
        ASSERT_TRUE(std::get<0>(colorStops.at(idx)).has_value());
        EXPECT_EQ(std::get<0>(colorStops.at(idx)).value().ToString(), std::get<0>(validValues.at(idx)));
        EXPECT_EQ(std::get<1>(colorStops.at(idx)).Value(), std::get<1>(validValues.at(idx)));
    }
}

/**
 * @tc.name: CtorColorArkNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LinearGradientAccessorTest, CtorColorArkNumberTest, TestSize.Level1)
{
    std::vector<Ark_ColorStop> vectorData;
    for (const auto& pairItem : validValues3) {
        auto colorStop = Ark_ColorStop {
            .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(std::get<0>(pairItem)),
            .offset = Converter::ArkValue<Opt_Length>(std::get<1>(pairItem)),
        };
        vectorData.push_back(colorStop);
    }

    Converter::ArkArrayHolder<Array_ColorStop> vectorHolder(vectorData);
    Array_ColorStop colorStopArray = vectorHolder.ArkValue();
    peer_ = reinterpret_cast<LinearGradientPeer*>(accessor_->construct(&colorStopArray));
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStops = peer_->colorStops;

    for (size_t idx = 0; idx < validValues3.size(); idx++) {
        ASSERT_TRUE(std::get<0>(colorStops.at(idx)).has_value());
        EXPECT_EQ(std::get<0>(colorStops.at(idx)).value().ToString(), std::get<0>(validValues.at(idx)));
        EXPECT_EQ(std::get<1>(colorStops.at(idx)).Value(), std::get<1>(validValues.at(idx)));
    }
}

/**
 * @tc.name: CtorColorArkResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LinearGradientAccessorTest, CtorColorArkResourceTest, TestSize.Level1)
{
    std::vector<Ark_ColorStop> vectorData;
    for (const auto& pairItem : validValues4) {
        auto colorStop = Ark_ColorStop {
            .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(std::get<0>(pairItem)),
            .offset = Converter::ArkValue<Opt_Length>(std::get<1>(pairItem)),
        };
        vectorData.push_back(colorStop);
    }

    Converter::ArkArrayHolder<Array_ColorStop> vectorHolder(vectorData);
    Array_ColorStop colorStopArray = vectorHolder.ArkValue();
    peer_ = reinterpret_cast<LinearGradientPeer*>(accessor_->construct(&colorStopArray));
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStops = peer_->colorStops;

    for (size_t idx = 0; idx < validValues4.size(); idx++) {
        ASSERT_TRUE(std::get<0>(colorStops.at(idx)).has_value());
        EXPECT_EQ(std::get<0>(colorStops.at(idx)).value().ToString(), std::get<0>(validValues.at(idx)));
        EXPECT_EQ(std::get<1>(colorStops.at(idx)).Value(), std::get<1>(validValues.at(idx)));
    }
}

/**
 * @tc.name: CtorInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LinearGradientAccessorTest, CtorInvalidValuesTest, TestSize.Level1)
{
    std::vector<Ark_ColorStop> vectorData;

    for (const auto& pairItem : invalidValues) {
        auto colorStop = Ark_ColorStop {
            .color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(std::get<0>(pairItem)),
            .offset = Converter::ArkValue<Opt_Length>(std::get<1>(pairItem)),
        };
        vectorData.push_back(colorStop);
    }

    Converter::ArkArrayHolder<Array_ColorStop> vectorHolder(vectorData);
    Array_ColorStop colorStopArray = vectorHolder.ArkValue();
    peer_ = reinterpret_cast<LinearGradientPeer*>(accessor_->construct(&colorStopArray));
    std::vector<std::pair<std::optional<Color>, Dimension>> colorStops = peer_->colorStops;

    for (size_t idx = 0; idx < invalidValues.size(); idx++) {
        EXPECT_FALSE(std::get<0>(colorStops.at(idx)).has_value());
        EXPECT_EQ(std::get<1>(colorStops.at(idx)).Value(), std::clamp(std::get<1>(invalidValues.at(idx)), 0.f, 1.f));
    }
}
}
