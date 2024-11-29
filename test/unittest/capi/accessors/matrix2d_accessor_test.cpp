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
     100, 0, -0.54, 0.98, 1.00, 1.01, -100,
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
        peer_->transform.scaleX = param[0];
        peer_->transform.scaleY = param[1];
        peer_->transform.skewX = param[2];
        peer_->transform.skewY = param[3];
        peer_->transform.translateX = param[4];
        peer_->transform.translateY = param[5];

        auto expectedX = (peer_->transform.translateX + actual) * peer_->GetDensity();
        auto expectedY = (peer_->transform.translateY + TRANSFORM_ZERO_VALUE) * peer_->GetDensity();
        auto tx = Converter::ArkValue<Opt_Number>(static_cast<float>(actual));
        auto ty = Converter::ArkValue<Opt_Number>(static_cast<float>(TRANSFORM_ZERO_VALUE));

        accessor_->translate(peer_, &tx, &ty);

        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateX, expectedX));
        EXPECT_TRUE(LessOrEqualCustomPrecision(peer_->transform.translateY, expectedY));
    }
}
} // namespace OHOS::Ace::NG
