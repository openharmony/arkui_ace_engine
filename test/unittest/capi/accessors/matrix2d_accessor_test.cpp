/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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


#include "test/mock/core/render/mock_matrix2d.h"
#include "accessor_test_base.h"
#include "gmock/gmock.h"

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/interfaces/native/implementation/canvas_renderer_peer_impl.h"
#include "core/interfaces/native/implementation/canvas_path_peer.h"
#include "core/interfaces/native/implementation/canvas_pattern_peer.h"
#include "core/interfaces/native/implementation/canvas_gradient_peer.h"
#include "core/interfaces/native/implementation/matrix2d_peer.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto TRANSFORM_UNITY_VALUE = 1.00;
const auto TRANSFORM_ZERO_VALUE = 0.00;



// const auto ALPHA_LIMIT_MIN = 0.0;
// const auto ALPHA_LIMIT_MAX = 1.0;
// const auto SIZE_LIMIT_MIN = 0.0;
// const auto SEGMENT_LIMIT_MIN = 0.0;
// const auto SCALE_LIMIT_MIN = 0.0;
// const auto EXPECTED_TRUE = true;
// const auto EXPECTED_FALSE = false;

// const double DEFAULT_DOUBLE_VALUE = 10.0;
// const double DEFAULT_SCALE_VALUE = 1.0;
// const std::string DEFAULT_STRING_VALUE = "text";
// const std::string INVALID_STRING_VALUE = "";

// test plan
// std::vector<std::tuple<Ark_Number, double>> ARK_NUMBER_TEST_PLAN = {
//     { Converter::ArkValue<Ark_Number>(100), 100 },
//     { Converter::ArkValue<Ark_Number>(0), 0 },
//     { Converter::ArkValue<Ark_Number>(-100), -100 },
//     { Converter::ArkValue<Ark_Number>(12.34), 12.34 },
//     { Converter::ArkValue<Ark_Number>(-56.73), -56.73 },
// };

// std::vector<std::tuple<Ark_Number, double>> ARK_NUMBER_ALPHA_TEST_PLAN = {
//     { Converter::ArkValue<Ark_Number>(100), 100 },
//     { Converter::ArkValue<Ark_Number>(0), 0 },
//     { Converter::ArkValue<Ark_Number>(-0.54), -0.54 },
//     { Converter::ArkValue<Ark_Number>(0.98), 0.98 },
//     { Converter::ArkValue<Ark_Number>(1.00), 1.00 },
//     { Converter::ArkValue<Ark_Number>(1.01), 1.01 },
//     { Converter::ArkValue<Ark_Number>(-100), -100 },
// };

std::vector<std::vector<double>>
    ARRAY_NUMBER_TEST_PLAN = {
        { 100, 10.25, 2.35, 5.42, 12.34, 56.73 },
        { 100, 10.25, 0, 5.42, 12.34, 56.73 },
        { 100, -10.25, 0, -5.42, 12.34, -56.73 },
        { 0, 0, 0, 0, 0, 0 },
        { -100, -10.25, -2.35, -5.42, -12.34, -56.73 },
    };

// std::vector<std::tuple<Opt_Number, std::optional<double>>> OPT_NUMBER_TEST_PLAN = {
//     { Converter::ArkValue<Opt_Number>(100), 100 },
//     { Converter::ArkValue<Opt_Number>(0), 0 },
//     { Converter::ArkValue<Opt_Number>(-100), -100 },
//     { Converter::ArkValue<Opt_Number>(12.34), 12.34 },
//     { Converter::ArkValue<Opt_Number>(-56.73), -56.73 },
//     { Converter::ArkValue<Opt_Number>(Ark_Empty()), std::make_optional<double>() },
// };

std::vector<double> NUMBER_TEST_PLAN = {
     100, 0, -0.54, 0.98, 1.00, 1.01, -100,
};

// std::vector<std::tuple<double, double>> TRANSLATE_TEST_PLAN = {
//     { 100, 156.73 },
//     { 0, 56.73 },
//     { -0.54, 56.19 },
//     { 0.98, 57.71 },
//     { 1.00, 57.73 },
//     { 1.01, 57.74 },
//     { -100, -43.27 },
// };

// std::vector<double> NUMBER_TEST_PLAN = {
//     100, 0, -100, 12.34, -56.73,
// };

// std::vector<int32_t> INT32_TEST_PLAN = {
//     100, 0, -100, 12, -56,
// };


} // namespace

class Matrix2DAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIMatrix2DAccessor,
    &GENERATED_ArkUIAccessors::getMatrix2DAccessor, Matrix2DPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
    }
};

/**
 * @tc.name: identityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, identityTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->identity, nullptr);
    for (const auto& actual : ARRAY_NUMBER_TEST_PLAN) {
        peer_->transform.scaleX = actual[0];
        peer_->transform.scaleY = actual[1];
        peer_->transform.skewX = actual[2];
        peer_->transform.skewY = actual[3];
        peer_->transform.translateX = actual[4];
        peer_->transform.translateY = actual[5];



    // test!!!
        auto param = peer_->transform;
        std::printf("identity: const transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", param.scaleX, param.scaleY,
            param.skewX, param.skewY, param.translateX, param.translateY);
    // test!!!


        accessor_->identity(peer_);


    // test!!!
        auto param2 =  peer_->transform;
        std::printf("identity: changed transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", param2.scaleX, param2.scaleY,
            param2.skewX, param2.skewY, param2.translateX, param2.translateY);
    // test!!!


        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleX, TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleY, TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.skewX, TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.skewY, TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateX, TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateY, TRANSFORM_UNITY_VALUE));
    }

}

/**
 * @tc.name: invertTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, invertTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->invert, nullptr);
    for (const auto& actual : ARRAY_NUMBER_TEST_PLAN) {
        peer_->transform.scaleX = actual[0];
        peer_->transform.scaleY = actual[1];
        peer_->transform.skewX = actual[2];
        peer_->transform.skewY = actual[3];
        peer_->transform.translateX = actual[4];
        peer_->transform.translateY = actual[5];


    // test!!!
        auto param = peer_->transform;
        std::printf("invert: const transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", param.scaleX, param.scaleY,
            param.skewX, param.skewY, param.translateX, param.translateY);
    // test!!!

        
        accessor_->invert(peer_);


        auto result = std::all_of(actual.begin(), actual.end(), [](double i) { return i == 0.00; });

        std::printf("invert: result : %d\n", result);

        if (result) {

            
            // test!!!
            std::printf("invert: changed false transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n",
                peer_->transform.scaleX, peer_->transform.scaleY, peer_->transform.skewX, peer_->transform.skewY,
                peer_->transform.translateX, peer_->transform.translateY);
            // test!!!

           
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.scaleX, peer_->transform.scaleX));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.scaleY, peer_->transform.scaleY));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.skewX, peer_->transform.skewX));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.skewY, peer_->transform.skewY));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.translateX, peer_->transform.translateX));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.translateY, peer_->transform.translateY));
            continue;
        }


    // test!!!
        std::printf("invert: changed true transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", peer_->transform.scaleX,
            peer_->transform.scaleY, peer_->transform.skewX, peer_->transform.skewX, peer_->transform.translateX,
            peer_->transform.translateY);
    // test!!!


        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleX, param.scaleY));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleY, param.scaleX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.skewX, param.skewY));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.skewY, param.skewX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateX, param.translateY));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateY, param.translateX));
    }
}

/**
 * @tc.name: translateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, translateTest, TestSize.Level1)
{
    auto param = ARRAY_NUMBER_TEST_PLAN[0];
    ASSERT_NE(accessor_->translate, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.scaleX = param[0];
        peer_->transform.scaleY = param[1];
        peer_->transform.skewX = param[2];
        peer_->transform.skewY = param[3];
        peer_->transform.translateX = param[4];
        peer_->transform.translateY = param[5];

        auto expectedX = (peer_->transform.translateX + actual) * peer_->GetDensity();
        auto expectedY = (peer_->transform.translateY + TRANSFORM_ZERO_VALUE) * peer_->GetDensity();

    // test!!!
        std::printf("translate: const transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", peer_->transform.scaleX,
            peer_->transform.scaleY, peer_->transform.skewX, peer_->transform.skewX, peer_->transform.translateX,
            peer_->transform.translateY);
    // test!!!
    // test!!!
        std::printf("translate: const2 transform: %.2f, %.2f, %.2f, %.2f\n", actual, TRANSFORM_ZERO_VALUE, expectedX, expectedY);
    // test!!!



        auto tx = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        auto ty = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_ZERO_VALUE));
        
        accessor_->translate(peer_, &tx, &ty);


    // test!!!
        std::printf("invert: changed true transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", peer_->transform.scaleX,
            peer_->transform.scaleY, peer_->transform.skewX, peer_->transform.skewX, peer_->transform.translateX,
            peer_->transform.translateY);
    // test!!!
        
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateX, expectedX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateY, expectedY));
    }
}

// /**
//  * @tc.name: translateTest
//  * @tc.desc:
//  * @tc.type: FUNC
//  */
// HWTEST_F(Matrix2DAccessorTest, translateTest, TestSize.Level1)
// {
//     auto holder = TestHolder::GetInstance();
//     ASSERT_NE(accessor_->translate, nullptr);

//     // auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

//     // for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
//     //     for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
//     //         holder->SetUp();
//     //         accessor_->clearRect(peer_, &x, &y, &arkD, &arkD);
//     //         EXPECT_TRUE(holder->isCalled);
//     //         EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetX(), expectedX));
//     //         EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetY(), expectedY));
//     //     }
//     // }
//     // for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
//     //     for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
//     //         holder->SetUp();
//     //         accessor_->clearRect(peer_, &arkD, &arkD, &w, &h);
//     //         if (!(expectedW > SIZE_LIMIT_MIN && expectedH > SIZE_LIMIT_MIN)) {
//     //             EXPECT_FALSE(holder->isCalled);
//     //             continue;
//     //         }
//     //         EXPECT_TRUE(holder->isCalled);
//     //         EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Width(), expectedW));
//     //         EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Height(), expectedH));
//     //     }
//     // }
//     holder->TearDown();
// }

// /**
//  * @tc.name: setLineWidthTest
//  * @tc.desc:
//  * @tc.type: FUNC
//  */
// HWTEST_F(Matrix2DAccessorTest, setLineWidthTest, TestSize.Level1)
// {
//     auto holder = TestHolder::GetInstance();
//     holder->SetUp();

//     ASSERT_NE(accessor_->setLineWidth, nullptr);

//     for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
//         holder->SetUp();

//         accessor_->setLineWidth(peer_, &actual);
//         EXPECT_TRUE(holder->isCalled);
//         EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
//     }
//     holder->TearDown();
// }
} // namespace OHOS::Ace::NG
