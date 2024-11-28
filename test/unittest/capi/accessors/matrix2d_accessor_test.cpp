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
const auto EXPECTED_NUMBER_OF_CALLS = 3;
const auto ALPHA_LIMIT_MIN = 0.0;
const auto ALPHA_LIMIT_MAX = 1.0;
const auto SIZE_LIMIT_MIN = 0.0;
const auto SEGMENT_LIMIT_MIN = 0.0;
const auto SCALE_LIMIT_MIN = 0.0;
const auto EXPECTED_TRUE = true;
const auto EXPECTED_FALSE = false;

const double DEFAULT_DOUBLE_VALUE = 10.0;
const double DEFAULT_SCALE_VALUE = 1.0;
const std::string DEFAULT_STRING_VALUE = "text";
const std::string INVALID_STRING_VALUE = "";

// test plan
std::vector<std::tuple<Ark_Number, double>> ARK_NUMBER_TEST_PLAN = {
    { Converter::ArkValue<Ark_Number>(100), 100 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(-100), -100 },
    { Converter::ArkValue<Ark_Number>(12.34), 12.34 },
    { Converter::ArkValue<Ark_Number>(-56.73), -56.73 },
};

std::vector<std::tuple<Ark_Number, double>> ARK_NUMBER_ALPHA_TEST_PLAN = {
    { Converter::ArkValue<Ark_Number>(100), 100 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(-0.54), -0.54 },
    { Converter::ArkValue<Ark_Number>(0.98), 0.98 },
    { Converter::ArkValue<Ark_Number>(1.00), 1.00 },
    { Converter::ArkValue<Ark_Number>(1.01), 1.01 },
    { Converter::ArkValue<Ark_Number>(-100), -100 },
};

std::vector<std::vector<double>> ARRAY_NUMBER_TEST_PLAN = {
    { 100, 10.25, 2.35, 5.42, 12.34 },
    { 100, 10.25, 0, 5.42, 12.34 },
    { 100, -10.25, 0, -5.42, 12.34 },
    { 0, 0, 0, 0, 0 },
    { -100, -10.25, -2.35, -5.42, -12.34 },
    {},
};

std::vector<std::tuple<Opt_Number, std::optional<double>>> OPT_NUMBER_TEST_PLAN = {
    { Converter::ArkValue<Opt_Number>(100), 100 },
    { Converter::ArkValue<Opt_Number>(0), 0 },
    { Converter::ArkValue<Opt_Number>(-100), -100 },
    { Converter::ArkValue<Opt_Number>(12.34), 12.34 },
    { Converter::ArkValue<Opt_Number>(-56.73), -56.73 },
    { Converter::ArkValue<Opt_Number>(Ark_Empty()), std::make_optional<double>() },
};

std::vector<double> NUMBER_ALPHA_TEST_PLAN = {
    100, 0, -0.54, 0.98, 1.00, 1.01, -100,
};

std::vector<double> NUMBER_TEST_PLAN = {
    100, 0, -100, 12.34, -56.73,
};

std::vector<int32_t> INT32_TEST_PLAN = {
    100, 0, -100, 12, -56,
};


} // namespace

class CanvasRendererAccessorTest
    : public AccessorTestBase<GENERATED_ArkUICanvasRendererAccessor,
    &GENERATED_ArkUIAccessors::getCanvasRendererAccessor, CanvasRendererPeer> {
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
 * @tc.name: beginPathTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, beginPathTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->beginPath, nullptr);

    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);
    accessor_->beginPath(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: stroke0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, stroke0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->stroke0, nullptr);

    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);
    accessor_->stroke0(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);

    holder->TearDown();
}

/**
 * @tc.name: setLineDashTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineDashTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->setLineDash, nullptr);

    for (const auto& expected : ARRAY_NUMBER_TEST_PLAN) {
        holder->SetUp();

        Converter::ArkArrayHolder<Array_Number> arrayHolder(expected);
        const auto segments = arrayHolder.ArkValue();

        accessor_->setLineDash(peer_, &segments);
        bool isNegative = false;
        if (expected.size() == SIZE_LIMIT_MIN) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        for (const auto& value : expected) {
            if (value < SEGMENT_LIMIT_MIN) {
                isNegative = true;
                break;
            }
        }
        if (isNegative) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(expected.size(), holder->segments.size());
        for (size_t i = 0; i < expected.size(); i++) {
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->segments[i], expected[i]));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: clearRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, clearRectTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->clearRect, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->clearRect(peer_, &x, &y, &arkD, &arkD);
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetY(), expectedY));
        }
    }
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->clearRect(peer_, &arkD, &arkD, &w, &h);
            if (!(expectedW > SIZE_LIMIT_MIN && expectedH > SIZE_LIMIT_MIN)) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Width(), expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Height(), expectedH));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: fillRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, fillRectTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->fillRect, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->fillRect(peer_, &x, &y, &arkD, &arkD);
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetY(), expectedY));
        }
    }
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->fillRect(peer_, &arkD, &arkD, &w, &h);
            if (!(expectedW > SIZE_LIMIT_MIN && expectedH > SIZE_LIMIT_MIN)) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Width(), expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Height(), expectedH));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: strokeRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, strokeRectTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    ASSERT_NE(accessor_->strokeRect, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->strokeRect(peer_, &x, &y, &arkD, &arkD);
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetX(), expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetOffset().GetY(), expectedY));
        }
    }
    for (const auto& [w, expectedW] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [h, expectedH] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->strokeRect(peer_, &arkD, &arkD, &w, &h);
            if (!(expectedW > SIZE_LIMIT_MIN && expectedH > SIZE_LIMIT_MIN)) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Width(), expectedW));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->rect.GetSize().Height(), expectedH));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: restoreTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, restoreTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->restore, nullptr);

    accessor_->restore(peer_);
    accessor_->restore(peer_);
    accessor_->restore(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}

/**
 * @tc.name: saveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, saveTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->save, nullptr);

    accessor_->save(peer_);
    accessor_->save(peer_);
    accessor_->save(peer_);

    EXPECT_EQ(holder->counter, EXPECTED_NUMBER_OF_CALLS);
    holder->TearDown();
}



/**
 * @tc.name: setTransform0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform0Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform0, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkS = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_SCALE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_ALPHA_TEST_PLAN) {
            holder->SetUp();
            accessor_->setTransform0(peer_, &x, &arkD, &arkD, &y, &arkD, &arkD);

            if (expectedX < SCALE_LIMIT_MIN || expectedY < SCALE_LIMIT_MIN) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->setTransform0(peer_, &arkS, &x, &y, &arkS, &arkD, &arkD);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->setTransform0(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: transformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, transformTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->transform, nullptr);

    auto arkD = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_DOUBLE_VALUE));
    auto arkS = Converter::ArkValue<Ark_Number>(static_cast<float>(DEFAULT_SCALE_VALUE));

    for (const auto& [x, expectedX] : ARK_NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_ALPHA_TEST_PLAN) {
            holder->SetUp();
            accessor_->transform(peer_, &x, &arkD, &arkD, &y, &arkD, &arkD);

            if (expectedX < SCALE_LIMIT_MIN || expectedY < SCALE_LIMIT_MIN) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->transform(peer_, &arkS, &x, &y, &arkS, &arkD, &arkD);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewY, expectedY));
        }
    }
    for (const auto& [x, expectedX] : ARK_NUMBER_TEST_PLAN) {
        for (const auto& [y, expectedY] : ARK_NUMBER_TEST_PLAN) {
            holder->SetUp();
            accessor_->transform(peer_, &arkS, &arkD, &arkD, &arkS, &x, &y);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setGlobalCompositeOperationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setGlobalCompositeOperationTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setGlobalCompositeOperation, nullptr);

    for (const auto& [actual, expected] : ARK_COMPOSITE_TEST_PLAN) {
        holder->SetUp();
        accessor_->setGlobalCompositeOperation(peer_, &actual);

        if (expected == INVALID_COMPOSITE_VALUE) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->composite, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFilterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFilterTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFilter, nullptr);

    for (const auto& [actual, expected] : ARK_STRING_TEST_PLAN) {
        holder->SetUp();
        accessor_->setFilter(peer_, &actual);

        if (expected == INVALID_STRING_VALUE) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->text, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setImageSmoothingEnabledTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setImageSmoothingEnabledTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setImageSmoothingEnabled, nullptr);

    for (const auto& [actual, expected] : ARK_BOOL_TEST_PLAN) {
        holder->SetUp();

        accessor_->setImageSmoothingEnabled(peer_, actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->enabled, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setLineDashOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineDashOffsetTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setLineDashOffset, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setLineDashOffset(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setLineWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setLineWidthTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setLineWidth, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setLineWidth(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setMiterLimitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setMiterLimitTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setMiterLimit, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setMiterLimit(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowBlurTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowBlurTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowBlur, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setShadowBlur(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowColorTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowColor, nullptr);

    for (const auto& [actual, expected] : ARK_STRING_COLOR_TEST_PLAN) {
        holder->SetUp();
        accessor_->setShadowColor(peer_, &actual);

        if (expected == Color::BLACK) {
            EXPECT_FALSE(holder->isCalled);
            continue;
        }

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(holder->color.ToString(), expected.ToString());
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowOffsetXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowOffsetXTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowOffsetX, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setShadowOffsetX(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: setShadowOffsetYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setShadowOffsetYTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setShadowOffsetY, nullptr);

    for (const auto& [actual, expected] : ARK_NUMBER_TEST_PLAN) {
        holder->SetUp();

        accessor_->setShadowOffsetY(peer_, &actual);
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(LessOrEqualCustomPrecision(holder->value, expected));
    }
    holder->TearDown();
}

/**
 * @tc.name: stroke1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, stroke1Test, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->stroke1, nullptr);

    Ark_Materialized arkPath;
    auto peer = new CanvasPathPeer();
    arkPath.ptr = peer;

    for (const auto& expected : PATH2D_TEST_PLAN) {
        holder->SetUp();
        auto path = AceType::MakeRefPtr<CanvasPath2D>();
        auto cmd = std::get<0>(expected);
        auto x = std::get<1>(expected);
        auto y = std::get<2>(expected);

        if (cmd == PathCmd::MOVE_TO) {
            path->MoveTo(x, y);
        } else {
            path->LineTo(x, y);
        }
        peer->SetCanvasPath2D(path);

        accessor_->stroke1(peer_, &arkPath);

        auto result = holder->path->GetCaches();
        auto rcmd = result[0].first;
        auto rx = result[0].second.para1;
        auto ry = result[0].second.para2;

        EXPECT_TRUE(holder->isCalled);
        EXPECT_EQ(rcmd, cmd);
        EXPECT_TRUE(LessOrEqualCustomPrecision(rx, x));
        EXPECT_TRUE(LessOrEqualCustomPrecision(ry, y));
    }
    holder->TearDown();
}

/**
 * @tc.name: setTransform1ScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1ScaleTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform1, nullptr);

    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix.ptr = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);

    auto valD = DEFAULT_DOUBLE_VALUE;

    for (const auto& expectedX : NUMBER_ALPHA_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_ALPHA_TEST_PLAN) {
            auto param = std::make_shared<OHOS::Ace::TransformParam>();
            param->scaleX = expectedX;
            param->scaleY = expectedY;
            param->skewX = valD;
            param->skewY = valD;
            param->translateX = valD;
            param->translateY = valD;
            peer->SetTransformParam(param);

            holder->SetUp();
            accessor_->setTransform1(peer_, &optMatrix);

            if (expectedX < SCALE_LIMIT_MIN || expectedY < SCALE_LIMIT_MIN) {
                EXPECT_FALSE(holder->isCalled);
                continue;
            }
            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->scaleY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setTransform1SkewTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1SkewTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform1, nullptr);

    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix.ptr = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);

    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valS = DEFAULT_SCALE_VALUE;

    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto param = std::make_shared<OHOS::Ace::TransformParam>();
            param->scaleX = valS;
            param->scaleY = valS;
            param->skewX = expectedX;
            param->skewY = expectedY;
            param->translateX = valD;
            param->translateY = valD;
            peer->SetTransformParam(param);

            holder->SetUp();
            accessor_->setTransform1(peer_, &optMatrix);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->skewY, expectedY));
        }
    }
    holder->TearDown();
}

/**
 * @tc.name: setTransform1TranslateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setTransform1TranslateTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setTransform1, nullptr);

    Ark_Matrix2D arkMatrix;
    auto peer = new Matrix2DPeer();
    arkMatrix.ptr = peer;
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(arkMatrix);

    auto valD = DEFAULT_DOUBLE_VALUE;
    auto valS = DEFAULT_SCALE_VALUE;

    for (const auto& expectedX : NUMBER_TEST_PLAN) {
        for (const auto& expectedY : NUMBER_TEST_PLAN) {
            auto param = std::make_shared<OHOS::Ace::TransformParam>();
            param->scaleX = valS;
            param->scaleY = valS;
            param->skewX = valD;
            param->skewY = valD;
            param->translateX = expectedX;
            param->translateY = expectedY;
            peer->SetTransformParam(param);

            holder->SetUp();
            accessor_->setTransform1(peer_, &optMatrix);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->transY, expectedY));
        }
    }
    holder->TearDown();
}

#ifdef PIXEL_MAP_SUPPORTED
/**
 * @tc.name: transferFromImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_transferFromImageBitmapTest, TestSize.Level1) {}
#else

/**
 * @tc.name: transferFromImageBitmapTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_transferFromImageBitmapTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->transferFromImageBitmap, nullptr);

    Ark_Materialized arkBitmap;
    auto peer = new ImageBitmapPeer();
    arkBitmap.ptr = peer;

    for (const auto& expectedX : INT32_TEST_PLAN) {
        for (const auto& expectedY : INT32_TEST_PLAN) {
            auto imageData = std::make_shared<OHOS::Ace::ImageData>();
            imageData->x = expectedX;
            imageData->y = expectedY;
            peer->SetImageData(imageData);

            holder->SetUp();
            accessor_->transferFromImageBitmap(peer_, &arkBitmap);

            EXPECT_TRUE(holder->isCalled);
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->imageData->x, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(holder->imageData->y, expectedY));
        }
    }
    holder->TearDown();
}
#endif

/**
 * @tc.name: setFontStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontStyleTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto size = FONT_SIZE_PX_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_STYLE_TEST_PLAN) {
        auto font = actual + " " + weight + " " + size + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontStyle, expected);
    }

    holder->TearDown();
}

/**
 * @tc.name: setFontWeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontWeightTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto size = FONT_SIZE_PX_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_WEIGHT_TEST_PLAN) {
        auto font = style + " " + actual + " " + size + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontWeight, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFontSizePxTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontSizePxTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_SIZE_PX_TEST_PLAN) {
        auto font = style + " " + weight + " " + actual + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        if (expected == Dimension(-100)) {
            EXPECT_FALSE(holder->isCalled3);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontSize, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFontSizeVpTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, DISABLED_setFontSizeVpTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto family = FONT_FAMILIES_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_SIZE_VP_TEST_PLAN) {
        auto font = style + " " + weight + " " + actual + " " + family;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        if (expected == Dimension(-100)) {
            EXPECT_FALSE(holder->isCalled3);
            continue;
        }
        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontSize, expected);
    }
    holder->TearDown();
}

/**
 * @tc.name: setFontFamiliesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererAccessorTest, setFontFamiliesTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();

    ASSERT_NE(accessor_->setFont, nullptr);

    auto style = FONT_STYLE_TEST_PLAN[0].first;
    auto weight = FONT_WEIGHT_TEST_PLAN[0].first;
    auto size = FONT_SIZE_PX_TEST_PLAN[0].first;

    for (const auto& [actual, expected] : FONT_FAMILIES_TEST_PLAN) {
        auto font = style + " " + weight + " " + size + " " + actual;
        auto arkFont = Converter::ArkValue<Ark_String>(font);

        holder->SetUp();
        accessor_->setFont(peer_, &arkFont);

        if (expected.size() == 0) {
            EXPECT_FALSE(holder->isCalled4);
            continue;
        }

        EXPECT_TRUE(holder->isCalled);
        EXPECT_TRUE(holder->isCalled2);
        EXPECT_TRUE(holder->isCalled3);
        EXPECT_TRUE(holder->isCalled4);
        EXPECT_EQ(holder->fontFamilies, expected);
    }
    holder->TearDown();
}

} // namespace OHOS::Ace::NG
