/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "interfaces/inner_api/drawable_descriptor/animated_drawable_descriptor.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Napi;

namespace OHOS::Ace {

class AnimatedDrawableDescriptorTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AnimatedDrawableDescriptorTest001
 * @tc.desc: test GetPixelMap with empty pixelMapList_
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest001, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetPixelMap();

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest002
 * @tc.desc: test GetPixelMap with non-empty pixelMapList_
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest002, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());

    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetPixelMap();

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, pixelMaps[0]);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest003
 * @tc.desc: test GetDrawableType returns ANIMATED
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest003, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetDrawableType();

    EXPECT_EQ(result, DrawableDescriptor::DrawableType::ANIMATED);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest004
 * @tc.desc: test GetPixelMapList returns correct list
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest004, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());

    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetPixelMapList();

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], pixelMaps[0]);
    EXPECT_EQ(result[1], pixelMaps[1]);
    EXPECT_EQ(result[2], pixelMaps[2]);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest005
 * @tc.desc: test GetDuration with duration_ <= 0 (empty list)
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest005, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetDuration();

    // duration_ = -1 <= 0, so duration_ = DEFAULT_DURATION * size() = 1000 * 0 = 0
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest006
 * @tc.desc: test GetDuration with duration_ <= 0 (non-empty list)
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest006, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());

    int32_t duration = -1;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetDuration();

    // duration_ = -1 <= 0, so duration_ = DEFAULT_DURATION * size() = 1000 * 3 = 3000
    EXPECT_EQ(result, 3000);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest007
 * @tc.desc: test GetDuration with duration_ > 0
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest007, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 5000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetDuration();

    // duration_ = 5000 > 0, so return duration_ as is
    EXPECT_EQ(result, 5000);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest008
 * @tc.desc: test GetDuration with duration_ == 0
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest008, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());

    int32_t duration = 0;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetDuration();

    // duration_ = 0 <= 0, so duration_ = DEFAULT_DURATION * size() = 1000 * 1 = 1000
    EXPECT_EQ(result, 1000);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest009
 * @tc.desc: test GetIterations with iterations_ < -1
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest009, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = -5;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetIterations();

    // iterations_ = -5 < -1, so iterations_ = 1
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest010
 * @tc.desc: test GetIterations with iterations_ == -1 (infinite)
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest010, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = -1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetIterations();

    // iterations_ = -1 is valid (infinite iterations)
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest011
 * @tc.desc: test GetIterations with iterations_ == 0
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest011, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 0;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetIterations();

    // iterations_ = 0 >= -1, so return as is
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest012
 * @tc.desc: test GetIterations with iterations_ > 0
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest012, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 5;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    auto result = drawable.GetIterations();

    // iterations_ = 5 >= -1, so return as is
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest013
 * @tc.desc: test SetDuration with duration <= 0 (empty list)
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest013, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    drawable.SetDuration(-100);

    // duration = -100 <= 0, so duration_ = DEFAULT_DURATION * size() = 1000 * 0 = 0
    EXPECT_EQ(drawable.duration_, 0);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest014
 * @tc.desc: test SetDuration with duration <= 0 (non-empty list)
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest014, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());
    pixelMaps.push_back(std::make_shared<Media::PixelMap>());

    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    drawable.SetDuration(0);

    // duration = 0 <= 0, so duration_ = DEFAULT_DURATION * size() = 1000 * 2 = 2000
    EXPECT_EQ(drawable.duration_, 2000);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest015
 * @tc.desc: test SetDuration with duration > 0
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest015, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    drawable.SetDuration(8000);

    // duration = 8000 > 0, so duration_ = 8000
    EXPECT_EQ(drawable.duration_, 8000);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest016
 * @tc.desc: test SetIterations with iterations < -1
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest016, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    drawable.SetIterations(-10);

    // iterations = -10 < -1, so iterations_ = 1
    EXPECT_EQ(drawable.iterations_, 1);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest017
 * @tc.desc: test SetIterations with iterations == -1 (infinite)
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest017, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    drawable.SetIterations(-1);

    // iterations = -1 is valid (infinite iterations)
    EXPECT_EQ(drawable.iterations_, -1);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest018
 * @tc.desc: test SetIterations with iterations >= -1
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest018, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 1;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    drawable.SetIterations(10);

    // iterations = 10 >= -1, so iterations_ = 10
    EXPECT_EQ(drawable.iterations_, 10);
}

/**
 * @tc.name: AnimatedDrawableDescriptorTest019
 * @tc.desc: test SetIterations with iterations == 0
 * @tc.type: FUNC
 */
HWTEST_F(AnimatedDrawableDescriptorTest, AnimatedDrawableDescriptorTest019, TestSize.Level1)
{
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    int32_t duration = 1000;
    int32_t iterations = 5;

    AnimatedDrawableDescriptor drawable(pixelMaps, duration, iterations);

    drawable.SetIterations(0);

    // iterations = 0 >= -1, so iterations_ = 0
    EXPECT_EQ(drawable.iterations_, 0);
}

} // namespace OHOS::Ace
