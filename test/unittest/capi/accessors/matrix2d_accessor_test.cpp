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

std::vector<std::vector<double>>
    ARRAY_NUMBER_TEST_PLAN = {
        { 100, 10.25, 2.35, 5.42, 12.34, 56.73 },
        { 100, 10.25, 0, 5.42, 12.34, 56.73 },
        { 100, -10.25, 0, -5.42, 12.34, -56.73 },
        { 0, 0, 0, 0, 0, 0 },
        { -100, -10.25, -2.35, -5.42, -12.34, -56.73 },
    };

std::vector<double> NUMBER_TEST_PLAN = {
    100, 0, -0.54, 0.98, 1.00, 1.01, -100, -151, -10.25, -2.35, -5.42, -12.34, -56.73, 151
};
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

        accessor_->identity(peer_);

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
        auto param = peer_->transform;

        accessor_->invert(peer_);

        auto result = std::all_of(actual.begin(), actual.end(), [](double i) { return i == TRANSFORM_ZERO_VALUE; });
        if (result) {
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.scaleX, peer_->transform.scaleX));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.scaleY, peer_->transform.scaleY));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.skewX, peer_->transform.skewX));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.skewY, peer_->transform.skewY));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.translateX, peer_->transform.translateX));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->transform.translateY, peer_->transform.translateY));
            continue;
        }
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
        peer_->transform.translateX = param[1];
        peer_->transform.translateY = param[5];
        auto expectedX = (peer_->transform.translateX + actual) * peer_->GetDensity();
        auto expectedY = (peer_->transform.translateY + TRANSFORM_ZERO_VALUE) * peer_->GetDensity();
        auto tx = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        auto ty = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_ZERO_VALUE));
        accessor_->translate(peer_, &tx, &ty);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateX, expectedX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateY, expectedY));
    }
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.translateX = param[1];
        peer_->transform.translateY = param[5];
        auto expectedX = (peer_->transform.translateX + TRANSFORM_ZERO_VALUE) * peer_->GetDensity();
        auto expectedY = (peer_->transform.translateY + actual) * peer_->GetDensity();
        auto tx = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_ZERO_VALUE));
        auto ty = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        accessor_->translate(peer_, &tx, &ty);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateX, expectedX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateY, expectedY));
    }
}

/**
 * @tc.name: scaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, scaleTest, TestSize.Level1)
{
    auto param = ARRAY_NUMBER_TEST_PLAN[0];
    ASSERT_NE(accessor_->scale, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.scaleX = param[1];
        peer_->transform.scaleY = param[5];
        auto expectedX = (peer_->transform.scaleX * actual);
        auto expectedY = (peer_->transform.scaleY * TRANSFORM_UNITY_VALUE);
        auto sx = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        auto sy = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        accessor_->scale(peer_, &sx, &sy);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleX, expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleY, expectedY, 0.01f));
    }
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.scaleX = param[1];
        peer_->transform.scaleY = param[5];
        auto expectedX = (peer_->transform.scaleX * TRANSFORM_UNITY_VALUE);
        auto expectedY = (peer_->transform.scaleY * actual);
        auto sx = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        auto sy = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        accessor_->scale(peer_, &sx, &sy);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleX, expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleY, expectedY, 0.01f));
    }
}

/**
 * @tc.name: getScaleXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, getScaleXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScaleX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.scaleX = actual;
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = accessor_->getScaleX(peer_);
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: setScaleXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, setScaleXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setScaleX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        auto sx = Converter::ArkValue<Ark_Number>(static_cast<float>(actual));
        auto expected = actual;
        accessor_->setScaleX(peer_, &sx);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleX, expected));
    }
}

/**
 * @tc.name: getRotateYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, getRotateYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRotateY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.skewY = actual;
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = accessor_->getRotateY(peer_);
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: getRotateXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, getRotateXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRotateX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.skewX = actual;
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = accessor_->getRotateX(peer_);
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: getScaleYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, getScaleYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScaleY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.scaleY = actual;
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = accessor_->getScaleY(peer_);
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: setScaleYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, setScaleYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setScaleY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        auto sy = Converter::ArkValue<Ark_Number>(static_cast<float>(actual));
        auto expected = actual;
        accessor_->setScaleY(peer_, &sy);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.scaleY, expected));
    }
}

/**
 * @tc.name: getTranslateXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, getTranslateXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTranslateX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.translateX = actual;
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = accessor_->getTranslateX(peer_);
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: getTranslateYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, getTranslateYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTranslateY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->transform.translateY = actual;
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = accessor_->getTranslateY(peer_);
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}
} // namespace OHOS::Ace::NG
