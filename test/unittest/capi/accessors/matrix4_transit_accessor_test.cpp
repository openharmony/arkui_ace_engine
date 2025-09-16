/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/matrix4_transit_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

// Converters from accessor implementation
namespace Converter {
template<> Point Convert(const Ark_matrix4_Matrix4TransformPoint& src);
void AssignArkValue(Ark_matrix4_Matrix4TransformPoint& dst, const Point& src, ConvContext *ctx);
} // namespace Converter

class Matrix4TransitAccessorTest : public AccessorTestBase<
    GENERATED_ArkUIMatrix4_Matrix4TransitAccessor,
    &GENERATED_ArkUIAccessors::getMatrix4_Matrix4TransitAccessor,
    matrix4_Matrix4TransitPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
    }
};

/**
 * @tc.name: copyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, copyTest, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateTranslate(7.0, 8.0, 0.0);

    matrix4_Matrix4TransitPeer* result = accessor_->copy(peer_);
    EXPECT_NE(result, peer_); // check that new object is created

    EXPECT_EQ(result->matrix, peer_->matrix);
}

/**
 * @tc.name: invertTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, invertTest, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateScale(4.0, 5.0, 1.0);

    matrix4_Matrix4TransitPeer* result = accessor_->invert(peer_);
    EXPECT_EQ(result, peer_);

    auto expected = Matrix4::CreateScale(0.25, 0.2, 1.0);
    EXPECT_EQ(result->matrix, expected);
}

/**
 * @tc.name: combineTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, combineTest, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateScale(3.0, 2.0, 1.0);
    matrix4_Matrix4TransitPeer* other = PeerUtils::CreatePeer<matrix4_Matrix4TransitPeer>();
    other->matrix = Matrix4::CreateTranslate(7.0, 8.0, 0.0);

    matrix4_Matrix4TransitPeer* result = accessor_->combine(peer_, other);
    EXPECT_EQ(result, peer_);

    Matrix4 expected(
        3.0, 0.0, 0.0, 7.0,
        0.0, 2.0, 0.0, 8.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    EXPECT_EQ(result->matrix, expected);
}

/**
 * @tc.name: translateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, translateTest, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    Ark_TranslateOptions options = {
        .x = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(5.0f),
        .y = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(7.0f)
    };

    matrix4_Matrix4TransitPeer* result = accessor_->translate(peer_, &options);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(0.0, 0.0);
    EXPECT_FLOAT_EQ(point.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 7.0f);

    point = result->matrix * Point(-2.0, 4.0);
    EXPECT_FLOAT_EQ(point.GetX(), 3.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 11.0f);
}

/**
 * @tc.name: translateTestExistingMatrixIsUsed
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, translateTestExistingMatrixIsUsed, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateScale(3.0, 2.0, 1.0);

    Ark_TranslateOptions options = {
        .x = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(5.0f),
        .y = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(7.0f)
    };

    matrix4_Matrix4TransitPeer* result = accessor_->translate(peer_, &options);
    EXPECT_EQ(result, peer_);

    Matrix4 expected(
        3.0, 0.0, 0.0, 5.0,
        0.0, 2.0, 0.0, 7.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    EXPECT_EQ(result->matrix, expected);
}

/**
 * @tc.name: scaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, scaleTest, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    Ark_ScaleOptions options = {
        .x = Converter::ArkValue<Opt_Number>(2.0f),
        .y = Converter::ArkValue<Opt_Number>(5.0f),
        .z = Converter::ArkValue<Opt_Number>(),
        .centerX = Converter::ArkValue<Opt_Union_Number_String>(),
        .centerY = Converter::ArkValue<Opt_Union_Number_String>(),
    };

    matrix4_Matrix4TransitPeer* result = accessor_->scale(peer_, &options);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(3.0, 2.0);
    EXPECT_FLOAT_EQ(point.GetX(), 6.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 10.0f);
}

/**
 * @tc.name: scaleTestExistingMatrixIsUsed
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, scaleTestExistingMatrixIsUsed, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateScale(3.0, 2.0, 1.0);

    Ark_ScaleOptions options = {
        .x = Converter::ArkValue<Opt_Number>(2.0f),
        .y = Converter::ArkValue<Opt_Number>(5.0f),
        .z = Converter::ArkValue<Opt_Number>(),
        .centerX = Converter::ArkValue<Opt_Union_Number_String>(),
        .centerY = Converter::ArkValue<Opt_Union_Number_String>(),
    };

    matrix4_Matrix4TransitPeer* result = accessor_->scale(peer_, &options);
    EXPECT_EQ(result, peer_);

    Matrix4 expected(
        6.0, 0.0, 0.0, 0.0,
        0.0, 10.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    EXPECT_EQ(result->matrix, expected);
}

/**
 * @tc.name: scaleTestCenterSpecified
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, scaleTestCenterSpecified, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    Ark_ScaleOptions options = {
        .x = Converter::ArkValue<Opt_Number>(2.0f),
        .y = Converter::ArkValue<Opt_Number>(0.5f),
        .z = Converter::ArkValue<Opt_Number>(),
        .centerX = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(1.0f),
        .centerY = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(2.0f),
    };

    matrix4_Matrix4TransitPeer* result = accessor_->scale(peer_, &options);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(3.0, 1.0);
    EXPECT_FLOAT_EQ(point.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 1.5f);
}

/**
 * @tc.name: skewTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, skewTest, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    auto factorX = Converter::ArkValue<Ark_Number>(2.0f);
    auto factorY = Converter::ArkValue<Ark_Number>(3.0f);

    matrix4_Matrix4TransitPeer* result = accessor_->skew(peer_, &factorX, &factorY);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(5.0, 7.0);
    EXPECT_FLOAT_EQ(point.GetX(), 19.0f); // new_x == old_x + factorX * old_y
    EXPECT_FLOAT_EQ(point.GetY(), 22.0f); // new_y == old_y + factorY * old_x
}

/**
 * @tc.name: skewTestExistingMatrixIsUsed
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, skewTestExistingMatrixIsUsed, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateScale(3.0, 2.0, 1.0);

    auto factorX = Converter::ArkValue<Ark_Number>(4.0f);
    auto factorY = Converter::ArkValue<Ark_Number>(5.0f);

    matrix4_Matrix4TransitPeer* result = accessor_->skew(peer_, &factorX, &factorY);
    EXPECT_EQ(result, peer_);

    Matrix4 expected(
        3.0, 8.0, 0.0, 0.0,
        15.0, 2.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    EXPECT_EQ(result->matrix, expected);
}

/**
 * @tc.name: rotateTestAxisX
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, rotateTestAxisX, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    // Rotate by 30 degrees around X-axis
    Ark_RotateOptions options = {
        .x = Converter::ArkValue<Opt_Number>(1.0f),
        .y = Converter::ArkValue<Opt_Number>(),
        .z = Converter::ArkValue<Opt_Number>(),
        .centerX = Converter::ArkValue<Opt_Union_Number_String>(),
        .centerY = Converter::ArkValue<Opt_Union_Number_String>(),
        .angle = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(30.0f)
    };

    matrix4_Matrix4TransitPeer* result = accessor_->rotate(peer_, &options);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(2.0, 1.0);
    EXPECT_FLOAT_EQ(point.GetX(), 2.0);
    EXPECT_FLOAT_EQ(point.GetY(), std::sqrt(3) / 2);
}

/**
 * @tc.name: rotateTestAxisY
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, rotateTestAxisY, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    // Rotate by 30 degrees around Y-axis
    Ark_RotateOptions options = {
        .x = Converter::ArkValue<Opt_Number>(),
        .y = Converter::ArkValue<Opt_Number>(1.0f),
        .z = Converter::ArkValue<Opt_Number>(),
        .centerX = Converter::ArkValue<Opt_Union_Number_String>(),
        .centerY = Converter::ArkValue<Opt_Union_Number_String>(),
        .angle = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(30.0f)
    };

    matrix4_Matrix4TransitPeer* result = accessor_->rotate(peer_, &options);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(2.0, 1.0);
    EXPECT_FLOAT_EQ(point.GetX(), std::sqrt(3));
    EXPECT_FLOAT_EQ(point.GetY(), 1.0);
}

/**
 * @tc.name: rotateTestAxisZ
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, rotateTestAxisZ, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    // Rotate by 45 degrees around Z-axis
    Ark_RotateOptions options = {
        .x = Converter::ArkValue<Opt_Number>(),
        .y = Converter::ArkValue<Opt_Number>(),
        .z = Converter::ArkValue<Opt_Number>(1.0f),
        .centerX = Converter::ArkValue<Opt_Union_Number_String>(),
        .centerY = Converter::ArkValue<Opt_Union_Number_String>(),
        .angle = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(45.0f)
    };

    matrix4_Matrix4TransitPeer* result = accessor_->rotate(peer_, &options);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(1.0, 0.0);
    EXPECT_FLOAT_EQ(point.GetX(), 1 / std::sqrt(2));
    EXPECT_FLOAT_EQ(point.GetY(), 1 / std::sqrt(2));
}

/**
 * @tc.name: rotateTestExistingMatrixIsUsed
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, rotateTestExistingMatrixIsUsed, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateTranslate(7.0, 8.0, 0.0);

    // Rotate by 180 degrees around Z-axis
    Ark_RotateOptions options = {
        .x = Converter::ArkValue<Opt_Number>(),
        .y = Converter::ArkValue<Opt_Number>(),
        .z = Converter::ArkValue<Opt_Number>(1.0f),
        .centerX = Converter::ArkValue<Opt_Union_Number_String>(),
        .centerY = Converter::ArkValue<Opt_Union_Number_String>(),
        .angle = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(180.0f)
    };

    matrix4_Matrix4TransitPeer* result = accessor_->rotate(peer_, &options);
    EXPECT_EQ(result, peer_);

    Matrix4 expected(
        -1.0, 0.0, 0.0, -7.0,
        0.0, -1.0, 0.0, -8.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    EXPECT_EQ(result->matrix, expected);
}

/**
 * @tc.name: rotateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, rotateTestCenterSpecified, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateIdentity();

    // Rotate by 45 degrees around Z-axis
    Ark_RotateOptions options = {
        .x = Converter::ArkValue<Opt_Number>(),
        .y = Converter::ArkValue<Opt_Number>(),
        .z = Converter::ArkValue<Opt_Number>(1.0f),
        .centerX = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(2.0f),
        .centerY = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(1.0f),
        .angle = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(45.0f)
    };

    matrix4_Matrix4TransitPeer* result = accessor_->rotate(peer_, &options);
    EXPECT_EQ(result, peer_);

    Point point = result->matrix * Point(3.0, 1.0);
    EXPECT_FLOAT_EQ(point.GetX(), 2 + 1 / std::sqrt(2));
    EXPECT_FLOAT_EQ(point.GetY(), 1 + 1 / std::sqrt(2));
}

/**
 * @tc.name: transformPointTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Matrix4TransitAccessorTest, transformPointTest, TestSize.Level1)
{
    peer_->matrix = Matrix4::CreateTranslate(10.0, 20.0, 0.0);

    auto options = Converter::ArkValue<Ark_matrix4_Matrix4TransformPoint>(Point(3.0, 5.0));

    auto result = accessor_->transformPoint(peer_, &options);
    auto point = Converter::Convert<Point>(result);
    EXPECT_FLOAT_EQ(point.GetX(), 13.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 25.0f);
}

} // namespace OHOS::Ace::NG