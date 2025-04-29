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

#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/interfaces/native/implementation/canvas_pattern_peer.h"
#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/native/implementation/matrix2d_peer_impl.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const double DEFAULT_DOUBLE_VALUE = 10.0;
const std::string REPEAT_STRING = "repeat";
const double FLT_PRECISION = 0.001;

std::vector<double> numberTestPlan = {
    100, 0, -100, 12.34, -56.73
};

class MockCanvasRenderingContext2DModel : public NG::CanvasRenderingContext2DModelNG {
public:
    MockCanvasRenderingContext2DModel() = default;
    ~MockCanvasRenderingContext2DModel() override = default;

    MOCK_METHOD(void, SetTransform, (std::shared_ptr<Ace::Pattern>, const TransformParam&), (override));
};
} // namespace
class CanvasPatternAccessorTest : public AccessorTestBase<GENERATED_ArkUICanvasPatternAccessor,
    &GENERATED_ArkUIAccessors::getCanvasPatternAccessor, CanvasPatternPeer> {};

/**
 * @tc.name: setTransformScaleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPatternAccessorTest, setTransformScaleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform, nullptr);

    auto renderingModel_ = AceType::MakeRefPtr<NiceMock<MockCanvasRenderingContext2DModel>>();
    auto canvasPeer = Referenced::MakeRefPtr<CanvasRenderingContext2DPeer>();
    canvasPeer->SetRenderingContext2DModel(renderingModel_);
    auto bitmap = PeerUtils::CreatePeer<ImageBitmapPeer>();
    auto repeat = std::make_optional(REPEAT_STRING);
    canvasPeer->CreatePattern(bitmap, peer_, repeat);
    auto peer = PeerUtils::CreatePeer<Matrix2DPeer>();
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(peer);
    for (const auto& actualX : numberTestPlan) {
        for (const auto& actualY : numberTestPlan) {
            peer->SetScaleX(actualX);
            peer->SetScaleY(actualY);
            peer->SetRotateX(DEFAULT_DOUBLE_VALUE);
            peer->SetRotateY(DEFAULT_DOUBLE_VALUE);
            peer->SetTranslateX(DEFAULT_DOUBLE_VALUE);
            peer->SetTranslateY(DEFAULT_DOUBLE_VALUE);

            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(Matcher<std::shared_ptr<Ace::Pattern>>(testing::_), _))
                .WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->setTransform(peer_, &optMatrix);

            EXPECT_NEAR(target.scaleX, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, actualY, FLT_PRECISION);
            EXPECT_NEAR(target.skewX, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.translateX, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
        }
    }

    EXPECT_CALL(*renderingModel_, SetTransform(Matcher<std::shared_ptr<Ace::Pattern>>(testing::_), _)).Times(0);
    accessor_->setTransform(peer_, nullptr);
}
/**
 * @tc.name: setTransformRotateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPatternAccessorTest, setTransformRotateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform, nullptr);

    auto renderingModel_ = AceType::MakeRefPtr<NiceMock<MockCanvasRenderingContext2DModel>>();
    auto canvasPeer = Referenced::MakeRefPtr<CanvasRenderingContext2DPeer>();
    canvasPeer->SetRenderingContext2DModel(renderingModel_);
    auto bitmap = PeerUtils::CreatePeer<ImageBitmapPeer>();
    auto repeat = std::make_optional(REPEAT_STRING);
    canvasPeer->CreatePattern(bitmap, peer_, repeat);
    auto peer = PeerUtils::CreatePeer<Matrix2DPeer>();
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(peer);
    for (const auto& actualX : numberTestPlan) {
        for (const auto& actualY : numberTestPlan) {
            peer->SetScaleX(DEFAULT_DOUBLE_VALUE);
            peer->SetScaleY(DEFAULT_DOUBLE_VALUE);
            peer->SetRotateX(actualX);
            peer->SetRotateY(actualY);
            peer->SetTranslateX(DEFAULT_DOUBLE_VALUE);
            peer->SetTranslateY(DEFAULT_DOUBLE_VALUE);

            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(Matcher<std::shared_ptr<Ace::Pattern>>(testing::_), _))
                .WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->setTransform(peer_, &optMatrix);

            EXPECT_NEAR(target.scaleX, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.skewX, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, actualY, FLT_PRECISION);
            EXPECT_NEAR(target.translateX, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
        }
    }
}
/**
 * @tc.name: setTransformTranslateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPatternAccessorTest, setTransformTranslateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTransform, nullptr);

    auto renderingModel_ = AceType::MakeRefPtr<NiceMock<MockCanvasRenderingContext2DModel>>();
    auto canvasPeer = Referenced::MakeRefPtr<CanvasRenderingContext2DPeer>();
    canvasPeer->SetRenderingContext2DModel(renderingModel_);
    auto bitmap = PeerUtils::CreatePeer<ImageBitmapPeer>();
    auto repeat = std::make_optional(REPEAT_STRING);
    canvasPeer->CreatePattern(bitmap, peer_, repeat);
    auto peer = PeerUtils::CreatePeer<Matrix2DPeer>();
    auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(peer);
    for (const auto& actualX : numberTestPlan) {
        for (const auto& actualY : numberTestPlan) {
            peer->SetScaleX(DEFAULT_DOUBLE_VALUE);
            peer->SetScaleY(DEFAULT_DOUBLE_VALUE);
            peer->SetRotateX(DEFAULT_DOUBLE_VALUE);
            peer->SetRotateY(DEFAULT_DOUBLE_VALUE);
            peer->SetTranslateX(actualX);
            peer->SetTranslateY(actualY);

            TransformParam target;
            EXPECT_CALL(*renderingModel_, SetTransform(Matcher<std::shared_ptr<Ace::Pattern>>(testing::_), _))
                .WillOnce(DoAll(SaveArg<1>(&target)));
            accessor_->setTransform(peer_, &optMatrix);

            EXPECT_NEAR(target.scaleX, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.scaleY, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.skewX, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.skewY, DEFAULT_DOUBLE_VALUE, FLT_PRECISION);
            EXPECT_NEAR(target.translateX, actualX, FLT_PRECISION);
            EXPECT_NEAR(target.translateY, actualY, FLT_PRECISION);
        }
    }
}
} // namespace OHOS::Ace::NG
