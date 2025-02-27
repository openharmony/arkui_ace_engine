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
#include "core/interfaces/native/implementation/canvas_pattern_peer.h"
#include "core/interfaces/native/implementation/canvas_gradient_peer.h"
#include "core/interfaces/native/implementation/matrix2d_peer_impl.h"
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
        peer_->SetScaleX(actual[0]);
        peer_->SetScaleY(actual[1]);
        peer_->SetRotateX(actual[2]);
        peer_->SetRotateY(actual[3]);
        peer_->SetTranslateX(actual[4]);
        peer_->SetTranslateY(actual[5]);

        accessor_->identity(peer_);

        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleX(), TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleY(), TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateX(), TRANSFORM_UNITY_VALUE));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateY(), TRANSFORM_UNITY_VALUE));
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
        peer_->SetScaleX(actual[0]);
        peer_->SetScaleY(actual[1]);
        peer_->SetRotateX(actual[2]);
        peer_->SetRotateY(actual[3]);
        peer_->SetTranslateX(actual[4]);
        peer_->SetTranslateY(actual[5]);
        auto param = peer_->GetTransform();

        accessor_->invert(peer_);

        auto result = std::all_of(actual.begin(), actual.end(), [](double i) { return i == TRANSFORM_ZERO_VALUE; });
        if (result) {
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->GetScaleX(), TRANSFORM_ZERO_VALUE));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->GetScaleY(), TRANSFORM_ZERO_VALUE));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->GetRotateX(), TRANSFORM_ZERO_VALUE));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->GetRotateY(), TRANSFORM_ZERO_VALUE));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->GetTranslateX(), TRANSFORM_ZERO_VALUE));
            EXPECT_FALSE(LessOrEqualCustomPrecision(peer_->GetTranslateY(), TRANSFORM_ZERO_VALUE));
            continue;
        }
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleX(), param.scaleY));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleY(), param.scaleX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), param.skewY));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), param.skewX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateX(), param.translateY));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateY(), param.translateX));
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
        peer_->SetTranslateX(param[1]);
        peer_->SetTranslateY(param[5]);
        auto expectedX = (peer_->GetTranslateX() + actual) * peer_->GetDensity();
        auto expectedY = (peer_->GetTranslateY() + TRANSFORM_ZERO_VALUE) * peer_->GetDensity();
        auto tx = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        auto ty = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_ZERO_VALUE));
        accessor_->translate(peer_, &tx, &ty);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateX(), expectedX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateY(), expectedY));
    }
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetTranslateX(param[1]);
        peer_->SetTranslateY(param[5]);
        auto expectedX = (peer_->GetTranslateX() + TRANSFORM_ZERO_VALUE) * peer_->GetDensity();
        auto expectedY = (peer_->GetTranslateY() + actual) * peer_->GetDensity();
        auto tx = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_ZERO_VALUE));
        auto ty = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        accessor_->translate(peer_, &tx, &ty);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateX(), expectedX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateY(), expectedY));
    }
}

/**
 * @tc.name: scaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, DISABLED_scaleTest, TestSize.Level1)
{
    auto param = ARRAY_NUMBER_TEST_PLAN[0];
    ASSERT_NE(accessor_->scale, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetScaleX(param[1]);
        peer_->SetScaleY(param[5]);
        auto expectedX = (peer_->GetScaleX() * actual);
        auto expectedY = (peer_->GetScaleY() * TRANSFORM_UNITY_VALUE);
        auto sx = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        auto sy = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        accessor_->scale(peer_, &sx, &sy);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleX(), expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleY(), expectedY, 0.01f));
    }
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetScaleX(param[1]);
        peer_->SetScaleY(param[5]);
        auto expectedX = (peer_->GetScaleX() * TRANSFORM_UNITY_VALUE);
        auto expectedY = (peer_->GetScaleY() * actual);
        auto sx = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        auto sy = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        accessor_->scale(peer_, &sx, &sy);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleX(), expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleY(), expectedY, 0.01f));
    }
}

/**
 * @tc.name: getScaleXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, DISABLED_getScaleXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScaleX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetScaleX(actual);
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = Converter::Convert<float>(accessor_->getScaleX(peer_));
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
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleX(), expected));
    }
}

/**
 * @tc.name: getRotateYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, DISABLED_getRotateYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRotateY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetRotateY(actual);
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = Converter::Convert<float>(accessor_->getRotateY(peer_));
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: getRotateXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, DISABLED_getRotateXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getRotateX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetRotateX(actual);
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = Converter::Convert<float>(accessor_->getRotateX(peer_));
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: getScaleYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, DISABLED_getScaleYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScaleY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetScaleY(actual);
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = Converter::Convert<float>(accessor_->getScaleY(peer_));
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: getTranslateXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, DISABLED_getTranslateXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTranslateX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetTranslateX(actual);
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = Converter::Convert<float>(accessor_->getTranslateX(peer_));
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: getTranslateYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, DISABLED_getTranslateYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTranslateY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetTranslateY(actual);
        auto expected = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(actual));
        auto result = Converter::Convert<float>(accessor_->getTranslateY(peer_));
        EXPECT_TRUE(LessOrEqualCustomPrecision(result, expected));
    }
}

/**
 * @tc.name: rotate1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest,  rotate1Test, TestSize.Level1)
{
    auto param = ARRAY_NUMBER_TEST_PLAN[0];
    ASSERT_NE(accessor_->rotate1, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetRotateX(param[1]);
        peer_->SetRotateY(param[5]);
        auto expectedX = (peer_->GetRotateX() * actual);
        auto expectedY = (peer_->GetRotateY() * actual);
        auto degree = Converter::ArkValue<Ark_Number>(static_cast<float>(actual));
        auto rx = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        auto ry = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        accessor_->rotate1(peer_, &degree, &rx, &ry);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), expectedY, 0.01f));
    }
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetRotateX(param[1]);
        peer_->SetRotateY(param[5]);
        auto expectedX = (peer_->GetRotateX() * actual);
        auto expectedY = (peer_->GetRotateY());
        auto degree = Converter::ArkValue<Ark_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        auto rx = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        auto ry = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        accessor_->rotate1(peer_, &degree, &rx, &ry);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), expectedY, 0.01f));
    }
    for (const auto& actual : NUMBER_TEST_PLAN) {
        peer_->SetRotateX(param[1]);
        peer_->SetRotateY(param[5]);
        auto expectedX = (peer_->GetRotateX());
        auto expectedY = (peer_->GetRotateY() * actual);
        auto degree = Converter::ArkValue<Ark_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        auto rx = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        auto ry = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        accessor_->rotate1(peer_, &degree, &rx, &ry);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), expectedY, 0.01f));
    }
}

/**
 * @tc.name: rotate1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest,  rotate1InvalidValuesTest, TestSize.Level1)
{
    auto param = ARRAY_NUMBER_TEST_PLAN[0];
    ASSERT_NE(accessor_->rotate1, nullptr);
        peer_->SetRotateX(param[1]);
        peer_->SetRotateY(param[5]);
        auto expectedX = TRANSFORM_ZERO_VALUE;
        auto expectedY = (peer_->GetRotateY());
        auto degree = Converter::ArkValue<Ark_Number>(TRANSFORM_UNITY_VALUE);
        auto rx = Converter::ArkValue<Opt_Number>();
        auto ry = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        accessor_->rotate1(peer_, &degree, &rx, &ry);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), expectedY, 0.01f));
        expectedX = (peer_->GetRotateX());
        expectedY = TRANSFORM_ZERO_VALUE;
        rx = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_UNITY_VALUE));
        ry = Converter::ArkValue<Opt_Number>();
        accessor_->rotate1(peer_, &degree, &rx, &ry);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), expectedX, 0.01f));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), expectedY, 0.01f));
}

/**
 * @tc.name: setRotateYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, setRotateYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setRotateY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        auto sy = Converter::ArkValue<Ark_Number>(static_cast<float>(actual));
        accessor_->setRotateY(peer_, &sy);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateY(), actual));
    }
}

/**
 * @tc.name: setRotateXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, setRotateXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setRotateX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        auto sx = Converter::ArkValue<Ark_Number>(static_cast<float>(actual));
        accessor_->setRotateX(peer_, &sx);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetRotateX(), actual));
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
        accessor_->setScaleY(peer_, &sy);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetScaleY(), actual));
    }
}

/**
 * @tc.name: setTranslateXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, setTranslateXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTranslateX, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        auto tx = Converter::ArkValue<Ark_Number>(static_cast<float>(actual));
        accessor_->setTranslateX(peer_, &tx);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateX(), actual));
    }
}

/**
 * @tc.name: setTranslateYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix2DAccessorTest, setTranslateYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTranslateY, nullptr);
    for (const auto& actual : NUMBER_TEST_PLAN) {
        auto ty = Converter::ArkValue<Ark_Number>(static_cast<float>(actual));
        accessor_->setTranslateY(peer_, &ty);
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->GetTranslateY(), actual));
    }
}
} // namespace OHOS::Ace::NG
