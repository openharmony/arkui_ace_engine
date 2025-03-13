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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/i_curve_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockCurve : public Curve {
public:
    MOCK_METHOD(float, MoveInternal, (float));
};
} // namespace

class ICurveAccessorTest : public AccessorTestBase<GENERATED_ArkUIICurveAccessor,
    &GENERATED_ArkUIAccessors::getICurveAccessor, ICurvePeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockCurve>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockCurve> mockHandler_ = nullptr;
};

/**
 * @tc.name: interpolateValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ICurveAccessorTest, interpolateValidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->interpolate, nullptr);

    float fraction1 = 0.0f;
    float fraction2 = 0.33f;
    float fraction3 = 0.854f;
    float fraction4 = 1.0f;

    float result1 = 0.5f;
    float result2 = 2.36f;
    float result3 = 5.654f;
    float result4 = 0.3456f;

    Ark_Number arkFraction1 = Converter::ArkValue<Ark_Number>(fraction1);
    Ark_Number arkFraction2 = Converter::ArkValue<Ark_Number>(fraction2);
    Ark_Number arkFraction3 = Converter::ArkValue<Ark_Number>(fraction3);
    Ark_Number arkFraction4 = Converter::ArkValue<Ark_Number>(fraction4);

    EXPECT_CALL(*mockHandler_, MoveInternal(fraction1)).Times(1).WillOnce(Return(result1));
    EXPECT_NEAR(Converter::Convert<float>(accessor_->interpolate(peer_, &arkFraction1)), result1, FLT_EPSILON);

    EXPECT_CALL(*mockHandler_, MoveInternal(fraction2)).Times(1).WillOnce(Return(result2));
    EXPECT_NEAR(Converter::Convert<float>(accessor_->interpolate(peer_, &arkFraction2)), result2, FLT_EPSILON);

    EXPECT_CALL(*mockHandler_, MoveInternal(fraction3)).Times(1).WillOnce(Return(result3));
    EXPECT_NEAR(Converter::Convert<float>(accessor_->interpolate(peer_, &arkFraction3)), result3, FLT_EPSILON);

    EXPECT_CALL(*mockHandler_, MoveInternal(fraction4)).Times(1).WillOnce(Return(result4));
    EXPECT_NEAR(Converter::Convert<float>(accessor_->interpolate(peer_, &arkFraction4)), result4, FLT_EPSILON);
}

/**
 * @tc.name: interpolateInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ICurveAccessorTest, interpolateInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->interpolate, nullptr);

    float fraction1 = -0.1f;
    float fraction2 = 1.1f;

    float expectedFraction1 = 0.0f;
    float expectedFraction2 = 1.0f;

    float result = 0.5f;
    float resultInvalid = 0.0f;

    Ark_Number arkFraction1 = Converter::ArkValue<Ark_Number>(fraction1);
    Ark_Number arkFraction2 = Converter::ArkValue<Ark_Number>(fraction2);

    EXPECT_CALL(*mockHandler_, MoveInternal(expectedFraction1)).Times(1).WillOnce(Return(result));
    EXPECT_NEAR(Converter::Convert<float>(accessor_->interpolate(peer_, &arkFraction1)), result, FLT_EPSILON);

    EXPECT_CALL(*mockHandler_, MoveInternal(expectedFraction2)).Times(1).WillOnce(Return(result));
    EXPECT_NEAR(Converter::Convert<float>(accessor_->interpolate(peer_, &arkFraction2)), result, FLT_EPSILON);

    EXPECT_NEAR(Converter::Convert<float>(accessor_->interpolate(peer_, nullptr)), resultInvalid, FLT_EPSILON);
}

} // namespace OHOS::Ace::NG