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
#include "core/interfaces/native/implementation/rect_shape_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class RectShapeAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIRectShapeAccessor,
        &GENERATED_ArkUIAccessors::getRectShapeAccessor, RectShapePeer> {
public:
    void* CreatePeerInstance() override
    {
        auto options = Converter::ArkValue<Opt_Union_RectShapeOptions_RoundRectShapeOptions>();
        return this->accessor_->construct(&options);
    }
};

/**
 * @tc.name: CtorTestRectShapeOptions
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, CtorTestRectShapeOptions, TestSize.Level1)
{
    const auto testWidth = 15.2;
    const auto testRadius = 5.;
    auto unionWidth = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testWidth);
    auto unionHeight = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("30px");
    auto unionRadius = Converter::ArkUnion<Ark_Union_Number_String_Array_Union_Number_String, Ark_Number>(testRadius);
    Ark_RectShapeOptions rectShapeOptions = {
        .width = Converter::ArkValue<Opt_Union_Number_String>(unionWidth),
        .height = Converter::ArkValue<Opt_Union_Number_String>(unionHeight),
        .radius = Converter::ArkValue<Opt_Union_Number_String_Array_Union_Number_String>(unionRadius),
    };
    auto unionOptions = Converter::ArkUnion<Ark_Union_RectShapeOptions_RoundRectShapeOptions, Ark_RectShapeOptions>(
        rectShapeOptions);
    auto options = Converter::ArkValue<Opt_Union_RectShapeOptions_RoundRectShapeOptions>(unionOptions);
    RectShapePeer* peer = accessor_->construct(&options);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->shape, nullptr);
    EXPECT_EQ(peer->shape->GetWidth(), Dimension(testWidth, DimensionUnit::VP));
    EXPECT_EQ(peer->shape->GetHeight(), Dimension(30, DimensionUnit::PX));

    auto expected = AnimatableDimension(testRadius, DimensionUnit::VP);
    EXPECT_EQ(peer->shape->GetTopLeftRadius().GetX(), expected);
    EXPECT_EQ(peer->shape->GetTopLeftRadius().GetY(), expected);
    EXPECT_EQ(peer->shape->GetTopRightRadius().GetX(), expected);
    EXPECT_EQ(peer->shape->GetTopRightRadius().GetY(), expected);
    EXPECT_EQ(peer->shape->GetBottomRightRadius().GetX(), expected);
    EXPECT_EQ(peer->shape->GetBottomRightRadius().GetY(), expected);
    EXPECT_EQ(peer->shape->GetBottomLeftRadius().GetX(), expected);
    EXPECT_EQ(peer->shape->GetBottomLeftRadius().GetY(), expected);
}

/**
 * @tc.name: CtorTestRectShapeOptionsArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, CtorTestRectShapeOptionsArray, TestSize.Level1)
{
    const auto testRadius1 = 12.6;
    const auto testRadius2 = 7.4;
    const auto testRadius3 = 9.2;
    const auto testRadius4 = 10.;
    auto item1 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius1);
    auto item2 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius2);
    auto item3 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius3);
    auto item4 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius4);
    std::vector<Ark_Union_Number_String> vectorRadius = { item1, item2, item3, item4 };
    Array_Union_Number_String arrayRadius = {
        .array = vectorRadius.data(),
        .length = vectorRadius.size()
    };
    auto unionRadius = Converter::ArkUnion<Ark_Union_Number_String_Array_Union_Number_String,
        Array_Union_Number_String>(arrayRadius);
    Ark_RectShapeOptions rectShapeOptions = {
        .width = Converter::ArkValue<Opt_Union_Number_String>(),
        .height = Converter::ArkValue<Opt_Union_Number_String>(),
        .radius = Converter::ArkValue<Opt_Union_Number_String_Array_Union_Number_String>(unionRadius),
    };

    auto unionOptions = Converter::ArkUnion<Ark_Union_RectShapeOptions_RoundRectShapeOptions, Ark_RectShapeOptions>(
        rectShapeOptions);
    auto options = Converter::ArkValue<Opt_Union_RectShapeOptions_RoundRectShapeOptions>(unionOptions);
    RectShapePeer* peer = accessor_->construct(&options);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->shape, nullptr);

    auto expectedTopLeft = AnimatableDimension(testRadius1, DimensionUnit::VP);
    auto expectedTopRight = AnimatableDimension(testRadius2, DimensionUnit::VP);
    auto expectedBottomRight = AnimatableDimension(testRadius3, DimensionUnit::VP);
    auto expectedBottomLeft = AnimatableDimension(testRadius4, DimensionUnit::VP);
    EXPECT_EQ(peer->shape->GetTopLeftRadius().GetX(), expectedTopLeft);
    EXPECT_EQ(peer->shape->GetTopLeftRadius().GetY(), expectedTopLeft);
    EXPECT_EQ(peer->shape->GetTopRightRadius().GetX(), expectedTopRight);
    EXPECT_EQ(peer->shape->GetTopRightRadius().GetY(), expectedTopRight);
    EXPECT_EQ(peer->shape->GetBottomRightRadius().GetX(), expectedBottomRight);
    EXPECT_EQ(peer->shape->GetBottomRightRadius().GetY(), expectedBottomRight);
    EXPECT_EQ(peer->shape->GetBottomLeftRadius().GetX(), expectedBottomLeft);
    EXPECT_EQ(peer->shape->GetBottomLeftRadius().GetY(), expectedBottomLeft);
}

/**
 * @tc.name: CtorTestRoundRectShapeOptions
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, CtorTestRoundRectShapeOptions, TestSize.Level1)
{
    const auto testWidth = 17.4;
    const auto testHeight = 20.5;
    const auto testRadiusWidth = 5.3;
    const auto testRadiusHeight = 4.1;

    auto unionWidth = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testWidth);
    auto unionHeight = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testHeight);
    auto unionRadiusWidth = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadiusWidth);
    auto unionRadiusHeight = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadiusHeight);

    Ark_RoundRectShapeOptions roundRectShapeOptions = {
        .width = Converter::ArkValue<Opt_Union_Number_String>(unionWidth),
        .height = Converter::ArkValue<Opt_Union_Number_String>(unionHeight),
        .radiusWidth = Converter::ArkValue<Opt_Union_Number_String>(unionRadiusWidth),
        .radiusHeight = Converter::ArkValue<Opt_Union_Number_String>(unionRadiusHeight),
    };

    auto unionOptions = Converter::ArkUnion<Ark_Union_RectShapeOptions_RoundRectShapeOptions,
        Ark_RoundRectShapeOptions>(roundRectShapeOptions);
    auto options = Converter::ArkValue<Opt_Union_RectShapeOptions_RoundRectShapeOptions>(unionOptions);
    RectShapePeer* peer = accessor_->construct(&options);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->shape, nullptr);
    EXPECT_EQ(peer->shape->GetWidth(), Dimension(testWidth, DimensionUnit::VP));
    EXPECT_EQ(peer->shape->GetHeight(), Dimension(testHeight, DimensionUnit::VP));

    auto expectedWidth = AnimatableDimension(testRadiusWidth, DimensionUnit::VP);
    auto expectedHeight = AnimatableDimension(testRadiusHeight, DimensionUnit::VP);
    EXPECT_EQ(peer->shape->GetTopLeftRadius().GetX(), expectedWidth);
    EXPECT_EQ(peer->shape->GetTopLeftRadius().GetY(), expectedHeight);
    EXPECT_EQ(peer->shape->GetTopRightRadius().GetX(), expectedWidth);
    EXPECT_EQ(peer->shape->GetTopRightRadius().GetY(), expectedHeight);
    EXPECT_EQ(peer->shape->GetBottomRightRadius().GetX(), expectedWidth);
    EXPECT_EQ(peer->shape->GetBottomRightRadius().GetY(), expectedHeight);
    EXPECT_EQ(peer->shape->GetBottomLeftRadius().GetX(), expectedWidth);
    EXPECT_EQ(peer->shape->GetBottomLeftRadius().GetY(), expectedHeight);
}

/**
 * @tc.name: offsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, offsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->offset, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Position offset {
        .x = Converter::ArkValue<Opt_Length>(5.),
        .y = Converter::ArkValue<Opt_Length>(8.)
    };
    EXPECT_EQ(accessor_->offset(peer_, &offset), peer_);

    auto expected = DimensionOffset(Dimension(5.f, DimensionUnit::VP), Dimension(8.f, DimensionUnit::VP));
    EXPECT_EQ(peer_->shape->GetOffset(), expected);

    Ark_Position offset2 {
        .x = Converter::ArkValue<Opt_Length>(20.),
        .y = Converter::ArkValue<Opt_Length>(10.)
    };
    EXPECT_EQ(accessor_->offset(peer_, &offset2), peer_);

    auto expected2 = DimensionOffset(Dimension(20.f, DimensionUnit::VP), Dimension(10.f, DimensionUnit::VP));
    EXPECT_EQ(peer_->shape->GetOffset(), expected2);

    EXPECT_EQ(accessor_->offset(nullptr, &offset), nullptr);
    EXPECT_EQ(accessor_->offset(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->offset(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetOffset(), expected2);
}

/**
 * @tc.name: fillTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, fillTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->fill, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x12345678);
    auto expected = Color(0x12345678);
    EXPECT_EQ(accessor_->fill(peer_, &color), peer_);
    EXPECT_EQ(peer_->shape->GetColor(), expected);

    EXPECT_EQ(accessor_->fill(nullptr, &color), nullptr);
    EXPECT_EQ(accessor_->fill(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->fill(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetColor(), expected);
}

/**
 * @tc.name: positionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, positionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->position, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Position position {
        .x = Converter::ArkValue<Opt_Length>(5.),
        .y = Converter::ArkValue<Opt_Length>(8.)
    };
    EXPECT_EQ(accessor_->position(peer_, &position), peer_);

    auto expected = DimensionOffset(Dimension(5.f, DimensionUnit::VP), Dimension(8.f, DimensionUnit::VP));
    EXPECT_EQ(peer_->shape->GetPosition(), expected);

    Ark_Position position2 {
        .x = Converter::ArkValue<Opt_Length>(20.),
        .y = Converter::ArkValue<Opt_Length>(10.)
    };
    EXPECT_EQ(accessor_->position(peer_, &position2), peer_);

    auto expected2 = DimensionOffset(Dimension(20.f, DimensionUnit::VP), Dimension(10.f, DimensionUnit::VP));
    EXPECT_EQ(peer_->shape->GetPosition(), expected2);

    EXPECT_EQ(accessor_->position(nullptr, &position), nullptr);
    EXPECT_EQ(accessor_->position(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->position(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetPosition(), expected2);
}

/**
 * @tc.name: widthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, widthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->width, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Length width = Converter::ArkValue<Ark_Length>(96.);
    auto expected = Dimension(96.f, DimensionUnit::VP);
    EXPECT_EQ(accessor_->width(peer_, &width), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expected);

    width = Converter::ArkValue<Ark_Length>(-64.);
    EXPECT_EQ(accessor_->width(peer_, &width), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expected);

    width = Converter::ArkValue<Ark_Length>(3.);
    EXPECT_EQ(accessor_->width(nullptr, &width), nullptr);
    EXPECT_EQ(accessor_->width(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->width(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expected);
}

/**
 * @tc.name: heightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, heightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->height, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Length height = Converter::ArkValue<Ark_Length>(96.);
    auto expected = Dimension(96.f, DimensionUnit::VP);
    EXPECT_EQ(accessor_->height(peer_, &height), peer_);
    EXPECT_EQ(peer_->shape->GetHeight(), expected);

    height = Converter::ArkValue<Ark_Length>(-64.);
    EXPECT_EQ(accessor_->height(peer_, &height), peer_);
    EXPECT_EQ(peer_->shape->GetHeight(), expected);

    height = Converter::ArkValue<Ark_Length>(3.);
    EXPECT_EQ(accessor_->height(nullptr, &height), nullptr);
    EXPECT_EQ(accessor_->height(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->height(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetHeight(), expected);
}

/**
 * @tc.name: sizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, sizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->size, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_SizeOptions size {
        .width = Converter::ArkValue<Opt_Length>(5.),
        .height = Converter::ArkValue<Opt_Length>(8.)
    };
    EXPECT_EQ(accessor_->size(peer_, &size), peer_);

    auto expectedWidth = Dimension(5.f, DimensionUnit::VP);
    auto expectedHeight = Dimension(8.f, DimensionUnit::VP);
    EXPECT_EQ(peer_->shape->GetWidth(), expectedWidth);
    EXPECT_EQ(peer_->shape->GetHeight(), expectedHeight);

    Ark_SizeOptions size2 {
        .width = Converter::ArkValue<Opt_Length>(20.),
        .height = Converter::ArkValue<Opt_Length>(10.)
    };
    EXPECT_EQ(accessor_->size(peer_, &size2), peer_);

    auto expectedWidth2 = Dimension(20.f, DimensionUnit::VP);
    auto expectedHeight2 = Dimension(10.f, DimensionUnit::VP);
    EXPECT_EQ(peer_->shape->GetWidth(), expectedWidth2);
    EXPECT_EQ(peer_->shape->GetHeight(), expectedHeight2);

    EXPECT_EQ(accessor_->size(nullptr, &size), nullptr);
    EXPECT_EQ(accessor_->size(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->size(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expectedWidth2);
    EXPECT_EQ(peer_->shape->GetHeight(), expectedHeight2);
}

/**
 * @tc.name: radiusWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, radiusWidthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->radiusWidth, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    auto check = [](const RefPtr<ShapeRect>& shape, const Dimension& expected) {
        EXPECT_EQ(shape->GetTopLeftRadius().GetX(), expected);
        EXPECT_EQ(shape->GetTopRightRadius().GetX(), expected);
        EXPECT_EQ(shape->GetBottomRightRadius().GetX(), expected);
        EXPECT_EQ(shape->GetBottomLeftRadius().GetX(), expected);
    };

    auto width = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(96);
    auto expected = Dimension(96.f, DimensionUnit::VP);
    EXPECT_EQ(accessor_->radiusWidth(peer_, &width), peer_);
    check(peer_->shape, expected);

    width = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(-64);
    EXPECT_EQ(accessor_->radiusWidth(peer_, &width), peer_);
    check(peer_->shape, expected);

    width = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(3);
    EXPECT_EQ(accessor_->radiusWidth(nullptr, &width), nullptr);
    EXPECT_EQ(accessor_->radiusWidth(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->radiusWidth(peer_, nullptr), peer_);
    check(peer_->shape, expected);
}

/**
 * @tc.name: radiusHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, radiusHeightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->radiusHeight, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    auto check = [](const RefPtr<ShapeRect>& shape, const Dimension& expected) {
        EXPECT_EQ(shape->GetTopLeftRadius().GetY(), expected);
        EXPECT_EQ(shape->GetTopRightRadius().GetY(), expected);
        EXPECT_EQ(shape->GetBottomRightRadius().GetY(), expected);
        EXPECT_EQ(shape->GetBottomLeftRadius().GetY(), expected);
    };

    auto width = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(96);
    auto expected = Dimension(96.f, DimensionUnit::VP);
    EXPECT_EQ(accessor_->radiusHeight(peer_, &width), peer_);
    check(peer_->shape, expected);

    width = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(-64);
    EXPECT_EQ(accessor_->radiusHeight(peer_, &width), peer_);
    check(peer_->shape, expected);

    width = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(3);
    EXPECT_EQ(accessor_->radiusHeight(nullptr, &width), nullptr);
    EXPECT_EQ(accessor_->radiusHeight(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->radiusHeight(peer_, nullptr), peer_);
    check(peer_->shape, expected);
}

/**
 * @tc.name: RadiusTestNull
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, RadiusTestNull, TestSize.Level1)
{
    ASSERT_NE(accessor_->radius, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    auto unionRadius = Converter::ArkUnion<Ark_Union_Number_String_Array_Union_Number_String, Ark_Number>(10.);
    EXPECT_EQ(accessor_->radius(nullptr, &unionRadius), nullptr);
    EXPECT_EQ(accessor_->radius(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->radius(peer_, nullptr), peer_);
}

/**
 * @tc.name: RadiusTestNumber
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, RadiusTestNumber, TestSize.Level1)
{
    ASSERT_NE(accessor_->radius, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    const auto testRadius = 5.;
    auto unionRadius = Converter::ArkUnion<Ark_Union_Number_String_Array_Union_Number_String, Ark_Number>(testRadius);

    EXPECT_EQ(accessor_->radius(peer_, &unionRadius), peer_);

    auto expected = AnimatableDimension(testRadius, DimensionUnit::VP);
    EXPECT_EQ(peer_->shape->GetTopLeftRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetTopLeftRadius().GetY(), expected);
    EXPECT_EQ(peer_->shape->GetTopRightRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetTopRightRadius().GetY(), expected);
    EXPECT_EQ(peer_->shape->GetBottomRightRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetBottomRightRadius().GetY(), expected);
    EXPECT_EQ(peer_->shape->GetBottomLeftRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetBottomLeftRadius().GetY(), expected);
}

/**
 * @tc.name: RadiusTestString
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, RadiusTestString, TestSize.Level1)
{
    ASSERT_NE(accessor_->radius, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    auto unionRadius = Converter::ArkUnion<Ark_Union_Number_String_Array_Union_Number_String, Ark_String>("7.4px");

    EXPECT_EQ(accessor_->radius(peer_, &unionRadius), peer_);

    auto expected = AnimatableDimension(7.4, DimensionUnit::PX);
    EXPECT_EQ(peer_->shape->GetTopLeftRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetTopLeftRadius().GetY(), expected);
    EXPECT_EQ(peer_->shape->GetTopRightRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetTopRightRadius().GetY(), expected);
    EXPECT_EQ(peer_->shape->GetBottomRightRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetBottomRightRadius().GetY(), expected);
    EXPECT_EQ(peer_->shape->GetBottomLeftRadius().GetX(), expected);
    EXPECT_EQ(peer_->shape->GetBottomLeftRadius().GetY(), expected);
}

/**
 * @tc.name: RadiusTestArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RectShapeAccessorTest, RadiusTestArray, TestSize.Level1)
{
    ASSERT_NE(accessor_->radius, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    const auto testRadius1 = 12.6;
    const auto testRadius2 = 7.4;
    const auto testRadius3 = 9.2;
    const auto testRadius4 = 10.;
    auto item1 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius1);
    auto item2 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius2);
    auto item3 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius3);
    auto item4 = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testRadius4);
    std::vector<Ark_Union_Number_String> vectorRadius = { item1, item2, item3, item4 };
    Array_Union_Number_String arrayRadius = {
        .array = vectorRadius.data(),
        .length = vectorRadius.size()
    };
    auto unionRadius = Converter::ArkUnion<Ark_Union_Number_String_Array_Union_Number_String,
        Array_Union_Number_String>(arrayRadius);
    EXPECT_EQ(accessor_->radius(peer_, &unionRadius), peer_);

    auto expectedTopLeft = AnimatableDimension(testRadius1, DimensionUnit::VP);
    auto expectedTopRight = AnimatableDimension(testRadius2, DimensionUnit::VP);
    auto expectedBottomRight = AnimatableDimension(testRadius3, DimensionUnit::VP);
    auto expectedBottomLeft = AnimatableDimension(testRadius4, DimensionUnit::VP);
    EXPECT_EQ(peer_->shape->GetTopLeftRadius().GetX(), expectedTopLeft);
    EXPECT_EQ(peer_->shape->GetTopLeftRadius().GetY(), expectedTopLeft);
    EXPECT_EQ(peer_->shape->GetTopRightRadius().GetX(), expectedTopRight);
    EXPECT_EQ(peer_->shape->GetTopRightRadius().GetY(), expectedTopRight);
    EXPECT_EQ(peer_->shape->GetBottomRightRadius().GetX(), expectedBottomRight);
    EXPECT_EQ(peer_->shape->GetBottomRightRadius().GetY(), expectedBottomRight);
    EXPECT_EQ(peer_->shape->GetBottomLeftRadius().GetX(), expectedBottomLeft);
    EXPECT_EQ(peer_->shape->GetBottomLeftRadius().GetY(), expectedBottomLeft);
}
} // namespace OHOS::Ace::NG