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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/ellipse_shape_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class EllipseShapeAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIEllipseShapeAccessor,
    &GENERATED_ArkUIAccessors::getEllipseShapeAccessor, EllipseShapePeer> {
public:
    void *CreatePeerInstance() override
    {
        Ark_ShapeSize shapeSize {
            .width = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(100),
            .height = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(200),
        };
        Opt_ShapeSize shapeSizeOpt = Converter::ArkValue<Opt_ShapeSize>(shapeSize);
        return accessor_->construct(&shapeSizeOpt);
    }
};

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseShapeAccessorTest, ctorTest, TestSize.Level1)
{
    ASSERT_NE(peer_->shape, nullptr);
    EXPECT_EQ(peer_->shape->GetWidth(), CalcDimension(100.f, DimensionUnit::VP));
    EXPECT_EQ(peer_->shape->GetHeight(), CalcDimension(200.f, DimensionUnit::VP));
}

/**
 * @tc.name: offsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseShapeAccessorTest, offsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->offset, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Position offset {
        .x = Converter::ArkValue<Opt_Length>("5px"),
        .y = Converter::ArkValue<Opt_Length>("8px")
    };
    EXPECT_EQ(accessor_->offset(peer_, &offset), peer_);

    auto expected = DimensionOffset(Dimension(5.f, DimensionUnit::PX), Dimension(8.f, DimensionUnit::PX));
    EXPECT_EQ(peer_->shape->GetOffset(), expected);

    Ark_Position offset2 {
        .x = Converter::ArkValue<Opt_Length>("10px"),
        .y = Converter::ArkValue<Opt_Length>(Ark_Empty())
    };
    EXPECT_EQ(accessor_->offset(peer_, &offset2), peer_);
    EXPECT_EQ(peer_->shape->GetOffset(), expected);

    Ark_Position offset3 {
        .x = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .y = Converter::ArkValue<Opt_Length>("10px")
    };
    EXPECT_EQ(accessor_->offset(peer_, &offset3), peer_);
    EXPECT_EQ(peer_->shape->GetOffset(), expected);
    EXPECT_EQ(accessor_->offset(nullptr, &offset3), nullptr);
    EXPECT_EQ(accessor_->offset(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->offset(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetOffset(), expected);
}

/**
 * @tc.name: fillTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseShapeAccessorTest, fillTest, TestSize.Level1)
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
HWTEST_F(EllipseShapeAccessorTest, positionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->position, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Position position {
        .x = Converter::ArkValue<Opt_Length>("5px"),
        .y = Converter::ArkValue<Opt_Length>("8px")
    };
    EXPECT_EQ(accessor_->position(peer_, &position), peer_);

    auto expected = DimensionOffset(Dimension(5.f, DimensionUnit::PX), Dimension(8.f, DimensionUnit::PX));
    EXPECT_EQ(peer_->shape->GetPosition(), expected);

    Ark_Position position2 {
        .x = Converter::ArkValue<Opt_Length>("10px"),
        .y = Converter::ArkValue<Opt_Length>(Ark_Empty())
    };
    expected = DimensionOffset();
    auto x = Dimension(10.f, DimensionUnit::PX);
    expected.SetX(x);
    EXPECT_EQ(accessor_->position(peer_, &position2), peer_);
    EXPECT_EQ(peer_->shape->GetPosition(), expected);

    Ark_Position position3 {
        .x = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .y = Converter::ArkValue<Opt_Length>("10px")
    };
    expected = DimensionOffset();
    auto y = Dimension(10.f, DimensionUnit::PX);
    expected.SetY(y);
    EXPECT_EQ(accessor_->position(peer_, &position3), peer_);
    EXPECT_EQ(peer_->shape->GetPosition(), expected);
    EXPECT_EQ(accessor_->position(nullptr, &position3), nullptr);
    EXPECT_EQ(accessor_->position(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->position(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetPosition(), expected);
}

/**
 * @tc.name: widthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EllipseShapeAccessorTest, widthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->width, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Length width = Converter::ArkValue<Ark_Length>("96px");
    auto expected = Dimension(96.f, DimensionUnit::PX);
    EXPECT_EQ(accessor_->width(peer_, &width), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expected);

    width = Converter::ArkValue<Ark_Length>("-64px");
    EXPECT_EQ(accessor_->width(peer_, &width), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expected);

    width = Converter::ArkValue<Ark_Length>("3px");
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
HWTEST_F(EllipseShapeAccessorTest, heightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->height, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_Length height = Converter::ArkValue<Ark_Length>("96px");
    auto expected = Dimension(96.f, DimensionUnit::PX);
    EXPECT_EQ(accessor_->height(peer_, &height), peer_);
    EXPECT_EQ(peer_->shape->GetHeight(), expected);

    height = Converter::ArkValue<Ark_Length>("-64px");
    EXPECT_EQ(accessor_->height(peer_, &height), peer_);
    EXPECT_EQ(peer_->shape->GetHeight(), expected);

    height = Converter::ArkValue<Ark_Length>("3px");
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
HWTEST_F(EllipseShapeAccessorTest, sizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->size, nullptr);
    ASSERT_NE(peer_->shape, nullptr);

    Ark_SizeOptions size {
        .width = Converter::ArkValue<Opt_Length>("5px"),
        .height = Converter::ArkValue<Opt_Length>("8px")
    };
    EXPECT_EQ(accessor_->size(peer_, &size), peer_);

    auto expectedWidth = Dimension(5.f, DimensionUnit::PX);
    auto expectedHeight = Dimension(8.f, DimensionUnit::PX);
    EXPECT_EQ(peer_->shape->GetWidth(), expectedWidth);
    EXPECT_EQ(peer_->shape->GetHeight(), expectedHeight);

    Ark_SizeOptions size2 {
        .width = Converter::ArkValue<Opt_Length>("10px"),
        .height = Converter::ArkValue<Opt_Length>(Ark_Empty())
    };
    expectedWidth = Dimension(10.f, DimensionUnit::PX);
    EXPECT_EQ(accessor_->size(peer_, &size2), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expectedWidth);
    EXPECT_EQ(peer_->shape->GetHeight(), expectedHeight);

    Ark_SizeOptions size3 {
        .width = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .height = Converter::ArkValue<Opt_Length>("15px")
    };
    expectedHeight = Dimension(15.f, DimensionUnit::PX);
    EXPECT_EQ(accessor_->size(peer_, &size3), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expectedWidth);
    EXPECT_EQ(peer_->shape->GetHeight(), expectedHeight);
    EXPECT_EQ(accessor_->size(nullptr, &size3), nullptr);
    EXPECT_EQ(accessor_->size(nullptr, nullptr), nullptr);
    EXPECT_EQ(accessor_->size(peer_, nullptr), peer_);
    EXPECT_EQ(peer_->shape->GetWidth(), expectedWidth);
    EXPECT_EQ(peer_->shape->GetHeight(), expectedHeight);
}

} // namespace OHOS::Ace::NG