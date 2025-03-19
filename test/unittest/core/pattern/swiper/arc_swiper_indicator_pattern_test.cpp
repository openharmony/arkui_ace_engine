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

#include <gtest/gtest.h>
#include "swiper_test_ng.h"
#define PRIVATE_PUBLIC public
#include "core/components_ng/pattern/swiper_indicator/indicator_common/arc_swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/base/frame_node.h"
#undef PRIVATE_PUBLIC
using namespace OHOS::Ace::NG;

class ArcSwiperIndicatorPatternTest : public SwiperTestNg {
protected:
    void SetUp() override
    {
        arcSwiperIndicatorPattern_ = ArcSwiperIndicatorPattern::MakeRefPtr<ArcSwiperIndicatorPattern>();
    }
    OHOS::Ace::RefPtr<ArcSwiperIndicatorPattern> arcSwiperIndicatorPattern_;
};

/**
 * @tc.name: GetEndAngle001
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle001, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = true;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::UNKNOWN;
    arcSwiperIndicatorPattern_->GetEndAngle(center, point, -60.0f);
    EXPECT_EQ(arcSwiperIndicatorPattern_->direction_, SwiperDirection::LEFT);
}

/**
 * @tc.name: GetEndAngle002
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle002, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = true;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::UNKNOWN;
    arcSwiperIndicatorPattern_->GetEndAngle(center, point, 60.0f);
    EXPECT_EQ(arcSwiperIndicatorPattern_->direction_, SwiperDirection::RIGHT);
}

/**
 * @tc.name: GetEndAngle003
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle003, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = true;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::UNKNOWN;
    auto angle = arcSwiperIndicatorPattern_->GetEndAngle(center, point, 0.0f);
    EXPECT_EQ(angle, 0);
}

/**
 * @tc.name: GetEndAngle004
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle004, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = false;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::LEFT;
    arcSwiperIndicatorPattern_->oldEndAngle_ = -60.0f;
    arcSwiperIndicatorPattern_->GetEndAngle(center, point, 30.0f);
    EXPECT_EQ(arcSwiperIndicatorPattern_->oldEndAngle_, 0.0f);
}

/**
 * @tc.name: GetEndAngle005
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle005, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = false;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::LEFT;
    arcSwiperIndicatorPattern_->oldEndAngle_ = 60.0f;
    auto angle = arcSwiperIndicatorPattern_->GetEndAngle(center, point, 30.0f);
    EXPECT_EQ(angle, 30);
}

/**
 * @tc.name: GetEndAngle006
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle006, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = false;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::LEFT;
    arcSwiperIndicatorPattern_->oldEndAngle_ = 60.0f;
    auto angle = arcSwiperIndicatorPattern_->GetEndAngle(center, point, -30.0f);
    EXPECT_EQ(angle, 0);
}

/**
 * @tc.name: GetEndAngle007
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle007, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = false;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::RIGHT;
    arcSwiperIndicatorPattern_->oldEndAngle_ = 1.0f;
    arcSwiperIndicatorPattern_->GetEndAngle(center, point, 30.0f);
    EXPECT_EQ(arcSwiperIndicatorPattern_->oldEndAngle_, 0.0f);
}

/**
 * @tc.name: GetEndAngle008
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle008, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = false;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::RIGHT;
    arcSwiperIndicatorPattern_->oldEndAngle_ = -10.0f;
    auto angle = arcSwiperIndicatorPattern_->GetEndAngle(center, point, 30.0f);
    EXPECT_EQ(angle, 0);
}

/**
 * @tc.name: GetEndAngle009
 * @tc.desc: Test GetEndAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorPatternTest, GetEndAngle009, TestSize.Level1)
{
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    arcSwiperIndicatorPattern_->isUpageStartAngle_ = false;
    arcSwiperIndicatorPattern_->direction_ = SwiperDirection::RIGHT;
    arcSwiperIndicatorPattern_->oldEndAngle_ = -10.0f;
    auto angle = arcSwiperIndicatorPattern_->GetEndAngle(center, point, -30.0f);
    EXPECT_EQ(angle, -30);
}