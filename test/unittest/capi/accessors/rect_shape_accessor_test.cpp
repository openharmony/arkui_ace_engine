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
        return this->accessor_->ctor(&options);
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
    RectShapePeer* peer = accessor_->ctor(&options);
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
    RectShapePeer* peer = accessor_->ctor(&options);
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
    RectShapePeer* peer = accessor_->ctor(&options);
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
} // namespace OHOS::Ace::NG