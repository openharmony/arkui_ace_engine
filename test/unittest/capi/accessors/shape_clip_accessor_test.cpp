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
#include "accessor_test_utils.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/interfaces/native/implementation/shape_clip_peer.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const float DEFAULT_FLOAT_VALUE = 74.32f;
// test plan
const std::vector<std::tuple<Ark_Number, Dimension>> numberTestPlan = {
    { Converter::ArkValue<Ark_Number>(100.0f), Dimension(100.0f) },
    { Converter::ArkValue<Ark_Number>(0.0f), Dimension(0.0f) },
    { Converter::ArkValue<Ark_Number>(-100.0f), Dimension(-100.0f) },
    { Converter::ArkValue<Ark_Number>(12.34f), Dimension(12.34f) },
    { Converter::ArkValue<Ark_Number>(-56.73f), Dimension(-56.73f) },
};
std::vector<std::tuple<Ark_String, std::string>> stringTestPlan = {
    { Converter::ArkValue<Ark_String>("string text"), "string text" },
    { Converter::ArkValue<Ark_String>(""), "" },
    { Converter::ArkValue<Ark_String>("123"), "123" },
    { Converter::ArkValue<Ark_String>("value %2"), "value %2" },
    { Converter::ArkValue<Ark_String>("echo(%10)"), "echo(%10)" },
};
} // namespace
class ShapeClipAccessorTest : public AccessorTestBase<GENERATED_ArkUIShapeClipAccessor,
                                  &GENERATED_ArkUIAccessors::getShapeClipAccessor, ShapeClipPeer> {};

/**
 * @tc.name: setRectShapeTopLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, setRectShapeTopLeftTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setRectShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualX, expectedX] : numberTestPlan) {
        for (const auto& [actualY, expectedY] : numberTestPlan) {
            auto rect = Ark_common2D_Rect {
                .left = actualX,
                .top = actualY,
                .right = valD,
                .bottom = valD,
            };
            accessor_->setRectShape(peer_, &rect);

            auto expectedW = Dimension(DEFAULT_FLOAT_VALUE - expectedX.Value());
            auto expectedH = Dimension(DEFAULT_FLOAT_VALUE - expectedY.Value());
            ASSERT_NE(peer_->rect, nullptr);
            EXPECT_EQ(peer_->rect->GetPosition().GetX(), expectedX);
            EXPECT_EQ(peer_->rect->GetPosition().GetY(), expectedY);
            EXPECT_EQ(peer_->rect->GetWidth(), expectedW);
            EXPECT_EQ(peer_->rect->GetHeight(), expectedH);
            EXPECT_EQ(peer_->roundRect, nullptr);
            EXPECT_EQ(peer_->circle, nullptr);
            EXPECT_EQ(peer_->oval, nullptr);
            EXPECT_EQ(peer_->path, std::nullopt);
        }
    }
}

/**
 * @tc.name: setRectShapeRightBottomTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, setRectShapeRightBottomTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setRectShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualX, expectedX] : numberTestPlan) {
        for (const auto& [actualY, expectedY] : numberTestPlan) {
            auto rect = Ark_common2D_Rect {
                .left = valD,
                .top = valD,
                .right = actualX,
                .bottom = actualY,
            };
            accessor_->setRectShape(peer_, &rect);

            auto expectedW = Dimension(expectedX.Value() - DEFAULT_FLOAT_VALUE);
            auto expectedH = Dimension(expectedY.Value() - DEFAULT_FLOAT_VALUE);
            auto expectedD = Dimension(DEFAULT_FLOAT_VALUE);
            ASSERT_NE(peer_->rect, nullptr);
            EXPECT_EQ(peer_->rect->GetPosition().GetX(), expectedD);
            EXPECT_EQ(peer_->rect->GetPosition().GetY(), expectedD);
            EXPECT_EQ(peer_->rect->GetWidth(), expectedW);
            EXPECT_EQ(peer_->rect->GetHeight(), expectedH);
            EXPECT_EQ(peer_->roundRect, nullptr);
            EXPECT_EQ(peer_->circle, nullptr);
            EXPECT_EQ(peer_->oval, nullptr);
            EXPECT_EQ(peer_->path, std::nullopt);
        }
    }
}

/**
 * @tc.name: setRoundRectShapeTopLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, DISABLED_setRoundRectShapeTopLeftTest, TestSize.Level1)
{
#ifdef WRONG_GEN
    ASSERT_NE(accessor_->setRoundRectShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualX, expectedX] : numberTestPlan) {
        for (const auto& [actualY, expectedY] : numberTestPlan) {
            auto rect = Ark_common2D_Rect {
                .left = actualX,
                .top = actualY,
                .right = valD,
                .bottom = valD,
            };
            auto corners = Ark_CornerRadius {
                .topLeft = Ark_Vector2 { .x = actualX, .y = actualY },
                .topRight = Ark_Vector2 { .x = valD, .y = valD },
                .bottomLeft = Ark_Vector2 { .x = actualX, .y = actualY },
                .bottomRight = Ark_Vector2 { .x = valD, .y = valD },
            };
            auto roundRect = Ark_RoundRect {
                .rect = rect,
                .corners = corners,
            };
            accessor_->setRoundRectShape(peer_, &roundRect);

            auto expectedW = Dimension(DEFAULT_FLOAT_VALUE - expectedX.Value());
            auto expectedH = Dimension(DEFAULT_FLOAT_VALUE - expectedY.Value());
            auto expectedD = Dimension(DEFAULT_FLOAT_VALUE);
            ASSERT_NE(peer_->roundRect, nullptr);
            EXPECT_EQ(peer_->roundRect->GetPosition().GetX(), expectedX);
            EXPECT_EQ(peer_->roundRect->GetPosition().GetY(), expectedY);
            EXPECT_EQ(peer_->roundRect->GetWidth(), expectedW);
            EXPECT_EQ(peer_->roundRect->GetHeight(), expectedH);
            EXPECT_EQ(peer_->roundRect->GetTopLeftRadius().GetX(), expectedX);
            EXPECT_EQ(peer_->roundRect->GetTopLeftRadius().GetY(), expectedY);
            EXPECT_EQ(peer_->roundRect->GetTopRightRadius().GetX(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetTopRightRadius().GetY(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetBottomLeftRadius().GetX(), expectedX);
            EXPECT_EQ(peer_->roundRect->GetBottomLeftRadius().GetY(), expectedY);
            EXPECT_EQ(peer_->roundRect->GetBottomRightRadius().GetX(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetBottomRightRadius().GetY(), expectedD);

            EXPECT_EQ(peer_->rect, nullptr);
            EXPECT_EQ(peer_->circle, nullptr);
            EXPECT_EQ(peer_->oval, nullptr);
            EXPECT_EQ(peer_->path, std::nullopt);
        }
    }
#endif
}

/**
 * @tc.name: setRoundRectShapeTopLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, DISABLED_setRoundRectShapeRightBottomTest, TestSize.Level1)
{
#ifdef WRONG_GEN
    ASSERT_NE(accessor_->setRoundRectShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualX, expectedX] : numberTestPlan) {
        for (const auto& [actualY, expectedY] : numberTestPlan) {
            auto rect = Ark_common2D_Rect {
                .left = valD,
                .top = valD,
                .right = actualX,
                .bottom = actualY,
            };
            auto corners = Ark_CornerRadius {
                .topLeft = Ark_Vector2 { .x = valD, .y = valD },
                .topRight = Ark_Vector2 { .x = actualX, .y = actualY },
                .bottomLeft = Ark_Vector2 { .x = valD, .y = valD },
                .bottomRight = Ark_Vector2 { .x = actualX, .y = actualY },
            };
            auto roundRect = Ark_RoundRect {
                .rect = rect,
                .corners = corners,
            };
            accessor_->setRoundRectShape(peer_, &roundRect);

            auto expectedW = Dimension(expectedX.Value() - DEFAULT_FLOAT_VALUE);
            auto expectedH = Dimension(expectedY.Value() - DEFAULT_FLOAT_VALUE);
            auto expectedD = Dimension(DEFAULT_FLOAT_VALUE);
            ASSERT_NE(peer_->roundRect, nullptr);
            EXPECT_EQ(peer_->roundRect->GetPosition().GetX(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetPosition().GetY(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetWidth(), expectedW);
            EXPECT_EQ(peer_->roundRect->GetHeight(), expectedH);
            EXPECT_EQ(peer_->roundRect->GetTopLeftRadius().GetX(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetTopLeftRadius().GetY(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetTopRightRadius().GetX(), expectedX);
            EXPECT_EQ(peer_->roundRect->GetTopRightRadius().GetY(), expectedY);
            EXPECT_EQ(peer_->roundRect->GetBottomLeftRadius().GetX(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetBottomLeftRadius().GetY(), expectedD);
            EXPECT_EQ(peer_->roundRect->GetBottomRightRadius().GetX(), expectedX);
            EXPECT_EQ(peer_->roundRect->GetBottomRightRadius().GetY(), expectedY);

            EXPECT_EQ(peer_->rect, nullptr);
            EXPECT_EQ(peer_->circle, nullptr);
            EXPECT_EQ(peer_->oval, nullptr);
            EXPECT_EQ(peer_->path, std::nullopt);
        }
    }
#endif
}

/**
 * @tc.name: setCircleShapeXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, setCircleShapeXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setCircleShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualX, expectedX] : numberTestPlan) {
        for (const auto& [actualY, expectedY] : numberTestPlan) {
            auto circle = Ark_Circle {
                .centerX = actualX,
                .centerY = actualY,
                .radius = valD,
            };
            accessor_->setCircleShape(peer_, &circle);

            auto expectedD = Dimension(DEFAULT_FLOAT_VALUE);
            ASSERT_NE(peer_->circle, nullptr);
            EXPECT_EQ(peer_->circle->GetPosition().GetX(), expectedX);
            EXPECT_EQ(peer_->circle->GetPosition().GetY(), expectedY);
            EXPECT_EQ(peer_->circle->GetRadius(), expectedD);
            EXPECT_EQ(peer_->rect, nullptr);
            EXPECT_EQ(peer_->roundRect, nullptr);
            EXPECT_EQ(peer_->oval, nullptr);
            EXPECT_EQ(peer_->path, std::nullopt);
        }
    }
}

/**
 * @tc.name: setCircleShapeRadiusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, setCircleShapeRadiusTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setCircleShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualR, expectedR] : numberTestPlan) {
        auto circle = Ark_Circle {
            .centerX = valD,
            .centerY = valD,
            .radius = actualR,
        };
        accessor_->setCircleShape(peer_, &circle);

        auto expectedD = Dimension(DEFAULT_FLOAT_VALUE);
        ASSERT_NE(peer_->circle, nullptr);
        EXPECT_EQ(peer_->circle->GetPosition().GetX(), expectedD);
        EXPECT_EQ(peer_->circle->GetPosition().GetY(), expectedD);
        if (expectedR.IsValid()) {
            EXPECT_EQ(peer_->circle->GetRadius(), expectedR);
        }
        EXPECT_EQ(peer_->rect, nullptr);
        EXPECT_EQ(peer_->roundRect, nullptr);
        EXPECT_EQ(peer_->oval, nullptr);
        EXPECT_EQ(peer_->path, std::nullopt);
    }
}

/**
 * @tc.name: setOvalShapeTopLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, setOvalShapeTopLeftTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setOvalShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualX, expectedX] : numberTestPlan) {
        for (const auto& [actualY, expectedY] : numberTestPlan) {
            auto rect = Ark_common2D_Rect {
                .left = actualX,
                .top = actualY,
                .right = valD,
                .bottom = valD,
            };
            accessor_->setOvalShape(peer_, &rect);

            auto expectedW = Dimension(DEFAULT_FLOAT_VALUE - expectedX.Value());
            auto expectedH = Dimension(DEFAULT_FLOAT_VALUE - expectedY.Value());
            ASSERT_NE(peer_->oval, nullptr);
            EXPECT_EQ(peer_->oval->GetPosition().GetX(), expectedX);
            EXPECT_EQ(peer_->oval->GetPosition().GetY(), expectedY);
            EXPECT_EQ(peer_->oval->GetWidth(), expectedW);
            EXPECT_EQ(peer_->oval->GetHeight(), expectedH);
            EXPECT_EQ(peer_->rect, nullptr);
            EXPECT_EQ(peer_->roundRect, nullptr);
            EXPECT_EQ(peer_->circle, nullptr);
            EXPECT_EQ(peer_->path, std::nullopt);
        }
    }
}

/**
 * @tc.name: setOvalShapeRightBottomTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, setOvalShapeRightBottomTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setOvalShape, nullptr);

    auto valD = Converter::ArkValue<Ark_Number>(DEFAULT_FLOAT_VALUE);
    for (const auto& [actualX, expectedX] : numberTestPlan) {
        for (const auto& [actualY, expectedY] : numberTestPlan) {
            auto rect = Ark_common2D_Rect {
                .left = valD,
                .top = valD,
                .right = actualX,
                .bottom = actualY,
            };
            accessor_->setOvalShape(peer_, &rect);

            auto expectedW = Dimension(expectedX.Value() - DEFAULT_FLOAT_VALUE);
            auto expectedH = Dimension(expectedY.Value() - DEFAULT_FLOAT_VALUE);
            auto expectedD = Dimension(DEFAULT_FLOAT_VALUE);
            ASSERT_NE(peer_->oval, nullptr);
            EXPECT_EQ(peer_->oval->GetPosition().GetX(), expectedD);
            EXPECT_EQ(peer_->oval->GetPosition().GetY(), expectedD);
            EXPECT_EQ(peer_->oval->GetWidth(), expectedW);
            EXPECT_EQ(peer_->oval->GetHeight(), expectedH);
            EXPECT_EQ(peer_->rect, nullptr);
            EXPECT_EQ(peer_->roundRect, nullptr);
            EXPECT_EQ(peer_->circle, nullptr);
            EXPECT_EQ(peer_->path, std::nullopt);
        }
    }
}

/**
 * @tc.name: setCommandPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ShapeClipAccessorTest, setCommandPathTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setCommandPath, nullptr);

    for (const auto& [actualP, expectedP] : stringTestPlan) {
        auto path = Ark_CommandPath {
            .commands = actualP,
        };
        accessor_->setCommandPath(peer_, &path);

        ASSERT_NE(peer_->path, std::nullopt);
        EXPECT_EQ(peer_->path.value(), expectedP);
        EXPECT_EQ(peer_->rect, nullptr);
        EXPECT_EQ(peer_->roundRect, nullptr);
        EXPECT_EQ(peer_->circle, nullptr);
        EXPECT_EQ(peer_->oval, nullptr);
    }
}
} // namespace OHOS::Ace::NG