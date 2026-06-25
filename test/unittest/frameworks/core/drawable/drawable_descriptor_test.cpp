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

#include "base/error/error_code.h"
#include "core/components_ng/render/drawing.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "test/mock/frameworks/base/image/mock_picture.h"

#define private public
#define protected public
#include "core/drawable/drawable_descriptor.h"
#include "core/drawable/drawable_descriptor_info.h"
#include "core/drawable/drawable_descriptor_loader.h"
#include "core/drawable/animated_drawable_descriptor.h"
#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"
#include "core/drawable/picture_drawable_descriptor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

const std::string FILE_PATH = "file://data/test.png";
const std::string BASE64_PATH = "data:image/png;base64,iVBORw0KGgo";
const std::string EMPTY_PATH = "";
const std::string INVALID_PATH = "invalid/path/test.png";

} // namespace

class DrawableDescriptorTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/*============================================================================
 * DrawableDescriptorInfo tests
 *============================================================================*/

/**
 * @tc.name: DrawableDescriptorInfoTest001
 * @tc.desc: Construct DrawableDescriptorInfo with file:// path → SrcType::FILE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest001, TestSize.Level1)
{
    DrawableDescriptorInfo info(FILE_PATH);
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::FILE);
    EXPECT_EQ(info.GetSrc(), FILE_PATH);
}

/**
 * @tc.name: DrawableDescriptorInfoTest002
 * @tc.desc: Construct DrawableDescriptorInfo with base64 data URI → SrcType::BASE64
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest002, TestSize.Level1)
{
    DrawableDescriptorInfo info(BASE64_PATH);
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::BASE64);
    EXPECT_EQ(info.GetSrc(), BASE64_PATH);
}

/**
 * @tc.name: DrawableDescriptorInfoTest003
 * @tc.desc: Construct DrawableDescriptorInfo with empty path → SrcType::UNDEFINED
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest003, TestSize.Level1)
{
    DrawableDescriptorInfo info(EMPTY_PATH);
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::UNDEFINED);
}

/**
 * @tc.name: DrawableDescriptorInfoTest004
 * @tc.desc: Construct DrawableDescriptorInfo with invalid path → SrcType::UNDEFINED
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest004, TestSize.Level1)
{
    DrawableDescriptorInfo info(INVALID_PATH);
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::UNDEFINED);
}

/**
 * @tc.name: DrawableDescriptorInfoTest005
 * @tc.desc: Construct DrawableDescriptorInfo with ResourceObject → SrcType::RESOURCE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest005, TestSize.Level1)
{
    auto resource = AceType::MakeRefPtr<ResourceObject>();
    DrawableDescriptorInfo info(resource);
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::RESOURCE);
    EXPECT_EQ(info.GetResource(), resource);
}

/**
 * @tc.name: DrawableDescriptorInfoTest006
 * @tc.desc: GetResource returns nullptr when constructed with path (no resource set)
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest006, TestSize.Level1)
{
    DrawableDescriptorInfo info(FILE_PATH);
    EXPECT_EQ(info.GetResource(), nullptr);
}

/**
 * @tc.name: DrawableDescriptorInfoTest007
 * @tc.desc: Base64 head with uppercase JPEG format → SrcType::BASE64
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest007, TestSize.Level1)
{
    DrawableDescriptorInfo info("data:image/JPEG;base64,/9j/4AAQ");
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::BASE64);
}

/**
 * @tc.name: DrawableDescriptorInfoTest008
 * @tc.desc: Base64 head with WEBP format → SrcType::BASE64
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest008, TestSize.Level1)
{
    DrawableDescriptorInfo info("data:image/webp;base64,UklGRiQAAABXRUJQ");
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::BASE64);
}

/**
 * @tc.name: DrawableDescriptorInfoTest009
 * @tc.desc: Base64 URI without comma → SrcType::UNDEFINED
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescriptorInfoTest009, TestSize.Level1)
{
    DrawableDescriptorInfo info("data:image/png;base64");
    EXPECT_EQ(info.GetSrcType(), DrawableDescriptorInfo::SrcType::UNDEFINED);
}

/*============================================================================
 * DrawableDescriptor base class tests
 *============================================================================*/

/**
 * @tc.name: DrawableDescBaseTest001
 * @tc.desc: GetPixelMap returns nullptr by default
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest001, TestSize.Level1)
{
    DrawableDescriptor desc;
    EXPECT_EQ(desc.GetPixelMap(), nullptr);
}

/**
 * @tc.name: DrawableDescBaseTest002
 * @tc.desc: GetDrawableType returns BASE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest002, TestSize.Level1)
{
    DrawableDescriptor desc;
    EXPECT_EQ(desc.GetDrawableType(), DrawableType::BASE);
}

/**
 * @tc.name: DrawableDescBaseTest003
 * @tc.desc: GetOriginalWidth/GetOriginalHeight return -1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest003, TestSize.Level1)
{
    DrawableDescriptor desc;
    EXPECT_EQ(desc.GetOriginalWidth(), -1);
    EXPECT_EQ(desc.GetOriginalHeight(), -1);
}

/**
 * @tc.name: DrawableDescBaseTest004
 * @tc.desc: LoadSync returns empty result
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest004, TestSize.Level1)
{
    DrawableDescriptor desc;
    auto result = desc.LoadSync();
    EXPECT_EQ(result.imageWidth_, 0);
    EXPECT_EQ(result.imageHeight_, 0);
    EXPECT_EQ(result.errorCode, 0);
}

/**
 * @tc.name: DrawableDescBaseTest005
 * @tc.desc: SetRawData stores data correctly
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest005, TestSize.Level1)
{
    DrawableDescriptor desc;
    auto data = std::make_unique<uint8_t[]>(16);
    desc.SetRawData(data.release(), 16);
    EXPECT_EQ(desc.rawData_.len, 16u);
    EXPECT_NE(desc.rawData_.data, nullptr);
}

/**
 * @tc.name: DrawableDescBaseTest006
 * @tc.desc: SetDrawableDescriptorInfo stores info correctly
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest006, TestSize.Level1)
{
    DrawableDescriptor desc;
    auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(FILE_PATH);
    desc.SetDrawableDescriptorInfo(info);
    EXPECT_EQ(desc.info_, info);
}

/**
 * @tc.name: DrawableDescBaseTest007
 * @tc.desc: LoadAsync with null callback does not crash
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest007, TestSize.Level1)
{
    DrawableDescriptor desc;
    EXPECT_NO_FATAL_FAILURE(desc.LoadAsync(nullptr));
    EXPECT_EQ(desc.GetPixelMap(), nullptr);
}

/**
 * @tc.name: DrawableDescBaseTest008
 * @tc.desc: RegisterUpdateCallback/UnRegisterUpdateCallback do not crash
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest008, TestSize.Level1)
{
    DrawableDescriptor desc;
    EXPECT_NO_FATAL_FAILURE(desc.RegisterUpdateCallback(1, nullptr));
    EXPECT_NO_FATAL_FAILURE(desc.UnRegisterUpdateCallback(1));
    EXPECT_EQ(desc.GetPixelMap(), nullptr);
}

/**
 * @tc.name: DrawableDescBaseTest009
 * @tc.desc: Invalidate does not crash on base class
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescBaseTest009, TestSize.Level1)
{
    DrawableDescriptor desc;
    EXPECT_NO_FATAL_FAILURE(desc.Invalidate());
    EXPECT_EQ(desc.GetPixelMap(), nullptr);
}

/*============================================================================
 * PixelMapDrawableDescriptor tests
 *============================================================================*/

/**
 * @tc.name: PixelMapDrawableDescTest001
 * @tc.desc: Default constructor → GetDrawableType PIXELMAP, pixelmap_ null
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PixelMapDrawableDescTest001, TestSize.Level1)
{
    PixelMapDrawableDescriptor desc;
    EXPECT_EQ(desc.GetDrawableType(), DrawableType::PIXELMAP);
    EXPECT_EQ(desc.pixelmap_, nullptr);
}

/**
 * @tc.name: PixelMapDrawableDescTest002
 * @tc.desc: Constructor with PixelMap stores reference
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PixelMapDrawableDescTest002, TestSize.Level1)
{
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(Return(100));
    PixelMapDrawableDescriptor desc(pixelMap);
    EXPECT_EQ(desc.pixelmap_, pixelMap);
}

/**
 * @tc.name: PixelMapDrawableDescTest003
 * @tc.desc: SetPixelMap replaces stored pixelmap
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PixelMapDrawableDescTest003, TestSize.Level1)
{
    PixelMapDrawableDescriptor desc;
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(Return(100));
    desc.SetPixelMap(pixelMap);
    EXPECT_EQ(desc.pixelmap_, pixelMap);
}

/**
 * @tc.name: PixelMapDrawableDescTest004
 * @tc.desc: GetPixelMap returns stored pixelmap
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PixelMapDrawableDescTest004, TestSize.Level1)
{
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(Return(100));
    PixelMapDrawableDescriptor desc(pixelMap);
    EXPECT_EQ(desc.GetPixelMap(), pixelMap);
}

/**
 * @tc.name: PixelMapDrawableDescTest005
 * @tc.desc: LoadSync with no data returns error
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PixelMapDrawableDescTest005, TestSize.Level1)
{
    PixelMapDrawableDescriptor desc;
    auto result = desc.LoadSync();
    EXPECT_EQ(result.errorCode, ERROR_CODE_DRAWABLE_LOADER_ERROR);
}

/*============================================================================
 * LayeredDrawableDescriptor tests
 *============================================================================*/

/**
 * @tc.name: LayeredDrawableDescTest001
 * @tc.desc: Default constructor → GetDrawableType LAYERED
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest001, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    EXPECT_EQ(desc.GetDrawableType(), DrawableType::LAYERED);
}

/**
 * @tc.name: LayeredDrawableDescTest002
 * @tc.desc: Constructor with foreground/background/mask sets members, blendMode -1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest002, TestSize.Level1)
{
    auto fg = AceType::MakeRefPtr<MockPixelMap>();
    auto bg = AceType::MakeRefPtr<MockPixelMap>();
    auto mask = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*fg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*fg, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*bg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*bg, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mask, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mask, GetHeight()).WillRepeatedly(Return(100));
    LayeredDrawableDescriptor desc(fg, bg, mask);
    EXPECT_EQ(desc.foreground_, fg);
    EXPECT_EQ(desc.background_, bg);
    EXPECT_EQ(desc.mask_, mask);
    EXPECT_FALSE(desc.foregroundOverBackground_);
    EXPECT_EQ(desc.blendMode_, -1);
}

/**
 * @tc.name: LayeredDrawableDescTest003
 * @tc.desc: Constructor with foregroundOverBackground=true → blendMode SRC_OVER
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest003, TestSize.Level1)
{
    auto fg = AceType::MakeRefPtr<MockPixelMap>();
    auto bg = AceType::MakeRefPtr<MockPixelMap>();
    auto mask = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*fg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*fg, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*bg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*bg, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mask, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mask, GetHeight()).WillRepeatedly(Return(100));
    LayeredDrawableDescriptor desc(fg, bg, mask, true);
    EXPECT_TRUE(desc.foregroundOverBackground_);
    EXPECT_EQ(desc.blendMode_, static_cast<int32_t>(RSBlendMode::SRC_OVER));
}

/**
 * @tc.name: LayeredDrawableDescTest004
 * @tc.desc: Constructor with foregroundOverBackground=false → blendMode stays -1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest004, TestSize.Level1)
{
    auto fg = AceType::MakeRefPtr<MockPixelMap>();
    auto bg = AceType::MakeRefPtr<MockPixelMap>();
    auto mask = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*fg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*fg, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*bg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*bg, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mask, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mask, GetHeight()).WillRepeatedly(Return(100));
    LayeredDrawableDescriptor desc(fg, bg, mask, false);
    EXPECT_FALSE(desc.foregroundOverBackground_);
    EXPECT_EQ(desc.blendMode_, -1);
}

/**
 * @tc.name: LayeredDrawableDescTest005
 * @tc.desc: SetForeground stores pixelmap, GetForeground returns it
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest005, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    auto fg = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*fg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*fg, GetHeight()).WillRepeatedly(Return(100));
    desc.SetForeground(fg);
    EXPECT_EQ(desc.foreground_, fg);
    EXPECT_EQ(desc.GetForeground(), fg);
}

/**
 * @tc.name: LayeredDrawableDescTest006
 * @tc.desc: SetBackground stores pixelmap, GetBackground returns it
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest006, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    auto bg = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*bg, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*bg, GetHeight()).WillRepeatedly(Return(100));
    desc.SetBackground(bg);
    EXPECT_EQ(desc.background_, bg);
    EXPECT_EQ(desc.GetBackground(), bg);
}

/**
 * @tc.name: LayeredDrawableDescTest007
 * @tc.desc: SetMask stores pixelmap, GetMask returns it
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest007, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    auto mask = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*mask, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*mask, GetHeight()).WillRepeatedly(Return(100));
    desc.SetMask(mask);
    EXPECT_EQ(desc.mask_, mask);
    EXPECT_EQ(desc.GetMask(), mask);
}

/**
 * @tc.name: LayeredDrawableDescTest008
 * @tc.desc: SetBlendMode with valid value sets blendMode and foregroundOverBackground
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest008, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    desc.SetBlendMode(static_cast<int32_t>(RSBlendMode::SRC_OVER));
    EXPECT_EQ(desc.blendMode_, static_cast<int32_t>(RSBlendMode::SRC_OVER));
    EXPECT_TRUE(desc.foregroundOverBackground_);
}

/**
 * @tc.name: LayeredDrawableDescTest009
 * @tc.desc: SetBlendMode with negative value out of range → no change
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest009, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    desc.blendMode_ = -1;
    desc.foregroundOverBackground_ = false;
    desc.SetBlendMode(-10);
    EXPECT_EQ(desc.blendMode_, -1);
    EXPECT_FALSE(desc.foregroundOverBackground_);
}

/**
 * @tc.name: LayeredDrawableDescTest010
 * @tc.desc: SetBlendMode with value > LUMINOSITY → no change
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest010, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    desc.blendMode_ = -1;
    auto invalidHigh = static_cast<int32_t>(RSBlendMode::LUMINOSITY) + 1;
    desc.SetBlendMode(invalidHigh);
    EXPECT_EQ(desc.blendMode_, -1);
}

/**
 * @tc.name: LayeredDrawableDescTest011
 * @tc.desc: InitBlendMode sets SRC_OVER when foregroundOverBackground_ is true
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest011, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    desc.foregroundOverBackground_ = true;
    desc.blendMode_ = -1;
    desc.InitBlendMode();
    EXPECT_EQ(desc.blendMode_, static_cast<int32_t>(RSBlendMode::SRC_OVER));
}

/**
 * @tc.name: LayeredDrawableDescTest012
 * @tc.desc: InitBlendMode no-op when foregroundOverBackground_ is false
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest012, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    desc.foregroundOverBackground_ = false;
    desc.blendMode_ = 100;
    desc.InitBlendMode();
    EXPECT_EQ(desc.blendMode_, 100);
}

/**
 * @tc.name: LayeredDrawableDescTest013
 * @tc.desc: SetForegroundData stores raw data
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest013, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    auto data = std::make_unique<uint8_t[]>(32);
    desc.SetForegroundData(data.release(), 32);
    EXPECT_EQ(desc.foregroundData_.len, 32u);
    EXPECT_NE(desc.foregroundData_.data, nullptr);
}

/**
 * @tc.name: LayeredDrawableDescTest014
 * @tc.desc: SetBackgroundData stores raw data
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest014, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    auto data = std::make_unique<uint8_t[]>(32);
    desc.SetBackgroundData(data.release(), 32);
    EXPECT_EQ(desc.backgroundData_.len, 32u);
    EXPECT_NE(desc.backgroundData_.data, nullptr);
}

/**
 * @tc.name: LayeredDrawableDescTest015
 * @tc.desc: SetMaskData stores raw data
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest015, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    auto data = std::make_unique<uint8_t[]>(16);
    desc.SetMaskData(data.release(), 16);
    EXPECT_EQ(desc.maskData_.len, 16u);
    EXPECT_NE(desc.maskData_.data, nullptr);
}

/**
 * @tc.name: LayeredDrawableDescTest016
 * @tc.desc: SetMaskPath stores path string
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest016, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    desc.SetMaskPath("/data/local/tmp/mask.png");
    EXPECT_EQ(desc.maskPath_, "/data/local/tmp/mask.png");
}

/**
 * @tc.name: LayeredDrawableDescTest017
 * @tc.desc: GetPixelMap with no data returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, LayeredDrawableDescTest017, TestSize.Level1)
{
    LayeredDrawableDescriptor desc;
    EXPECT_EQ(desc.GetPixelMap(), nullptr);
}

/*============================================================================
 * AnimatedDrawableDescriptor tests
 *============================================================================*/

/**
 * @tc.name: AnimatedDrawableDescTest001
 * @tc.desc: Default constructor → GetDrawableType ANIMATED
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest001, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_EQ(desc.GetDrawableType(), DrawableType::ANIMATED);
}

/**
 * @tc.name: AnimatedDrawableDescTest002
 * @tc.desc: SetAutoPlay/GetAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest002, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_TRUE(desc.GetAutoPlay());
    desc.SetAutoPlay(false);
    EXPECT_FALSE(desc.GetAutoPlay());
    desc.SetAutoPlay(true);
    EXPECT_TRUE(desc.GetAutoPlay());
}

/**
 * @tc.name: AnimatedDrawableDescTest003
 * @tc.desc: SetStopMode/GetStopMode
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest003, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_EQ(desc.GetStopMode(), AnimatedDrawableDescriptor::AnimationStopMode::FIRST_FRAME);
    desc.SetStopMode(AnimatedDrawableDescriptor::AnimationStopMode::LAST_FRAME);
    EXPECT_EQ(desc.GetStopMode(), AnimatedDrawableDescriptor::AnimationStopMode::LAST_FRAME);
}

/**
 * @tc.name: AnimatedDrawableDescTest004
 * @tc.desc: SetPixelMapList → GetPixelMapList + GetFrameCount
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest004, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    std::vector<RefPtr<PixelMap>> list;
    auto pm1 = AceType::MakeRefPtr<MockPixelMap>();
    auto pm2 = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm1, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm1, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetHeight()).WillRepeatedly(Return(100));
    list.push_back(pm1);
    list.push_back(pm2);
    desc.SetPixelMapList(list);
    EXPECT_EQ(desc.GetPixelMapList().size(), 2u);
    EXPECT_EQ(desc.GetFrameCount(), 2u);
}

/**
 * @tc.name: AnimatedDrawableDescTest005
 * @tc.desc: GetPixelMapList returns empty by default
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest005, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_TRUE(desc.GetPixelMapList().empty());
}

/**
 * @tc.name: AnimatedDrawableDescTest006
 * @tc.desc: GetIterations returns default 1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest006, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_EQ(desc.GetIterations(), 1);
}

/**
 * @tc.name: AnimatedDrawableDescTest007
 * @tc.desc: GetFrameCount returns 0 by default
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest007, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_EQ(desc.GetFrameCount(), 0u);
}

/**
 * @tc.name: AnimatedDrawableDescTest008
 * @tc.desc: SetPixelMapList with empty list → GetFrameCount 0
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest008, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    std::vector<RefPtr<PixelMap>> emptyList;
    desc.SetPixelMapList(emptyList);
    EXPECT_EQ(desc.GetFrameCount(), 0u);
    EXPECT_TRUE(desc.GetPixelMapList().empty());
}

/**
 * @tc.name: AnimatedDrawableDescTest009
 * @tc.desc: SetDurations stores durations, sets totalDuration_ to sum
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest009, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    std::vector<int32_t> durations = { 100, 200, 300 };
    desc.SetDurations(durations);
    EXPECT_EQ(desc.userDurations_, durations);
    EXPECT_TRUE(desc.isSetDurations_);
    EXPECT_EQ(desc.totalDuration_, 600);
}

/**
 * @tc.name: AnimatedDrawableDescTest010
 * @tc.desc: SetDurations with empty vector → no change
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest010, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.isSetDurations_ = false;
    desc.totalDuration_ = 100;
    std::vector<int32_t> empty;
    desc.SetDurations(empty);
    EXPECT_FALSE(desc.isSetDurations_);
    EXPECT_EQ(desc.totalDuration_, 100);
}

/**
 * @tc.name: AnimatedDrawableDescTest011
 * @tc.desc: GetDurations returns userDurations when set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest011, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetDurations({ 50, 50 });
    auto result = desc.GetDurations();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 50);
    EXPECT_EQ(result[1], 50);
}

/**
 * @tc.name: AnimatedDrawableDescTest012
 * @tc.desc: GetDurations with totalDuration_ set distributes evenly
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest012, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.frameCount_ = 4;
    desc.totalDuration_ = 400;
    auto result = desc.GetDurations();
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], 100);
}

/**
 * @tc.name: AnimatedDrawableDescTest013
 * @tc.desc: SetTotalDuration positive → stores value
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest013, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetTotalDuration(3000);
    EXPECT_EQ(desc.totalDuration_, 3000);
}

/**
 * @tc.name: AnimatedDrawableDescTest014
 * @tc.desc: SetTotalDuration negative → ignored
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest014, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.totalDuration_ = 100;
    desc.SetTotalDuration(-1);
    EXPECT_EQ(desc.totalDuration_, 100);
}

/**
 * @tc.name: AnimatedDrawableDescTest015
 * @tc.desc: SetTotalDuration when isSetDurations_=true → ignored
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest015, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.totalDuration_ = 100;
    desc.isSetDurations_ = true;
    desc.SetTotalDuration(5000);
    EXPECT_EQ(desc.totalDuration_, 100);
}

/**
 * @tc.name: AnimatedDrawableDescTest016
 * @tc.desc: GetTotalDuration returns stored value
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest016, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.totalDuration_ = 500;
    EXPECT_EQ(desc.GetTotalDuration(), 500);
}

/**
 * @tc.name: AnimatedDrawableDescTest017
 * @tc.desc: GetTotalDuration auto-calculated from pixelMapList size
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest017, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    std::vector<RefPtr<PixelMap>> list;
    auto pm1 = AceType::MakeRefPtr<MockPixelMap>();
    auto pm2 = AceType::MakeRefPtr<MockPixelMap>();
    auto pm3 = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm1, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm1, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm3, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm3, GetHeight()).WillRepeatedly(Return(100));
    list.push_back(pm1);
    list.push_back(pm2);
    list.push_back(pm3);
    desc.SetPixelMapList(list);
    EXPECT_EQ(desc.GetTotalDuration(), 3000);
}

/**
 * @tc.name: AnimatedDrawableDescTest018
 * @tc.desc: GetTotalDuration from selfDurations_ sum
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest018, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.totalDuration_ = -1;
    desc.selfDurations_ = { 50, 100, 150 };
    EXPECT_EQ(desc.GetTotalDuration(), 300);
}

/**
 * @tc.name: AnimatedDrawableDescTest019
 * @tc.desc: SetIterations with valid value
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest019, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetIterations(5);
    EXPECT_EQ(desc.GetIterations(), 5);
}

/**
 * @tc.name: AnimatedDrawableDescTest020
 * @tc.desc: SetIterations with iterations < -1 resets to 1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest020, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetIterations(-2);
    EXPECT_EQ(desc.GetIterations(), 1);
}

/**
 * @tc.name: AnimatedDrawableDescTest021
 * @tc.desc: GetOriginalWidth/Height with no pixelmap → -1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest021, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_EQ(desc.GetOriginalWidth(), -1);
    EXPECT_EQ(desc.GetOriginalHeight(), -1);
}

/**
 * @tc.name: AnimatedDrawableDescTest022
 * @tc.desc: GetControlledAnimator with empty animators → nullptr
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest022, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_EQ(desc.GetControlledAnimator(1), nullptr);
}

/**
 * @tc.name: AnimatedDrawableDescTest023
 * @tc.desc: RegisterUpdateCallback with zero frameCount → early return
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest023, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.frameCount_ = 0;
    desc.RegisterUpdateCallback(1, [](const RefPtr<PixelMap>&) {});
    EXPECT_TRUE(desc.animators_.empty());
}

/**
 * @tc.name: AnimatedDrawableDescTest024
 * @tc.desc: UnRegisterUpdateCallback with no matching animator → no crash
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest024, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_NO_FATAL_FAILURE(desc.UnRegisterUpdateCallback(999));
    EXPECT_TRUE(desc.animators_.empty());
}

/**
 * @tc.name: AnimatedDrawableDescTest025
 * @tc.desc: LoadSync with no data returns error
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest025, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto result = desc.LoadSync();
    EXPECT_EQ(result.errorCode, ERROR_CODE_DRAWABLE_LOADER_ERROR);
}

/**
 * @tc.name: AnimatedDrawableDescTest026
 * @tc.desc: LoadSync with cached imageSize_ returns cached values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest026, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(FILE_PATH);
    desc.SetDrawableDescriptorInfo(info);
    desc.imageSize_.width = 100;
    desc.imageSize_.height = 200;
    auto result = desc.LoadSync();
    EXPECT_EQ(result.imageWidth_, 100);
    EXPECT_EQ(result.imageHeight_, 200);
    EXPECT_EQ(result.errorCode, 0);
}

/**
 * @tc.name: AnimatedDrawableDescTest027
 * @tc.desc: GetDurations from pixelMapList when totalDuration_ < 0
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest027, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.totalDuration_ = -1;
    std::vector<RefPtr<PixelMap>> list;
    auto pm1 = AceType::MakeRefPtr<MockPixelMap>();
    auto pm2 = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm1, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm1, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetHeight()).WillRepeatedly(Return(100));
    list.push_back(pm1);
    list.push_back(pm2);
    desc.SetPixelMapList(list);
    auto result = desc.GetDurations();
    EXPECT_EQ(result.size(), 2u);
}

/**
 * @tc.name: AnimatedDrawableDescTest028
 * @tc.desc: GetDurations returns selfDurations_ when no user/total set
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest028, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.totalDuration_ = -1;
    desc.selfDurations_ = { 10, 20 };
    auto result = desc.GetDurations();
    EXPECT_EQ(result, desc.selfDurations_);
}

/**
 * @tc.name: AnimatedDrawableDescTest029
 * @tc.desc: GetTotalDuration via isSetDurations_ path
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest029, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.isSetDurations_ = true;
    desc.totalDuration_ = 888;
    EXPECT_EQ(desc.GetTotalDuration(), 888);
}

/**
 * @tc.name: AnimatedDrawableDescTest030
 * @tc.desc: SetIterations with -1 (infinite) sets -1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest030, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetIterations(-1);
    EXPECT_EQ(desc.GetIterations(), -1);
}

/**
 * @tc.name: AnimatedDrawableDescTest031
 * @tc.desc: SetIterations with 0 sets 0
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest031, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetIterations(0);
    EXPECT_EQ(desc.GetIterations(), 0);
}

/**
 * @tc.name: AnimatedDrawableDescTest032
 * @tc.desc: ToFillMode returns BACKWARDS for FIRST_FRAME stop mode
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest032, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetStopMode(AnimatedDrawableDescriptor::AnimationStopMode::FIRST_FRAME);
    EXPECT_EQ(desc.ToFillMode(), FillMode::BACKWARDS);
}

/**
 * @tc.name: AnimatedDrawableDescTest033
 * @tc.desc: ToFillMode returns FORWARDS for LAST_FRAME stop mode
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest033, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.SetStopMode(AnimatedDrawableDescriptor::AnimationStopMode::LAST_FRAME);
    EXPECT_EQ(desc.ToFillMode(), FillMode::FORWARDS);
}

/**
 * @tc.name: AnimatedDrawableDescTest034
 * @tc.desc: GetControlledAnimator(int32_t) with single animator returns it regardless of id
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest034, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    desc.animators_[1] = animator;
    EXPECT_EQ(desc.GetControlledAnimator(999), animator);
}

/**
 * @tc.name: AnimatedDrawableDescTest035
 * @tc.desc: GetControlledAnimator(int32_t) with multiple animators finds by id
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest035, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto animator1 = AceType::MakeRefPtr<ControlledAnimator>();
    auto animator2 = AceType::MakeRefPtr<ControlledAnimator>();
    desc.animators_[1] = animator1;
    desc.animators_[2] = animator2;
    EXPECT_EQ(desc.GetControlledAnimator(1), animator1);
    EXPECT_EQ(desc.GetControlledAnimator(2), animator2);
    EXPECT_EQ(desc.GetControlledAnimator(3), nullptr);
}

/**
 * @tc.name: AnimatedDrawableDescTest036
 * @tc.desc: GetFrameByIndex with pixelMapList returns correct frame
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest036, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto pm1 = AceType::MakeRefPtr<MockPixelMap>();
    auto pm2 = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm1, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm1, GetHeight()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm2, GetHeight()).WillRepeatedly(Return(100));
    desc.pixelMapList_ = { pm1, pm2 };
    EXPECT_EQ(desc.GetFrameByIndex(0, 1), pm1);
    EXPECT_EQ(desc.GetFrameByIndex(1, 1), pm2);
}

/**
 * @tc.name: AnimatedDrawableDescTest037
 * @tc.desc: FlushUpdateCallbacksByNodeId with negative index → no callback
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest037, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.frameCount_ = 3;
    bool called = false;
    desc.updateCallbacks_[1] = [&called](const RefPtr<PixelMap>&) { called = true; };
    desc.FlushUpdateCallbacksByNodeId(-1, 1);
    EXPECT_FALSE(called);
}

/**
 * @tc.name: AnimatedDrawableDescTest038
 * @tc.desc: FlushUpdateCallbacksByNodeId with out-of-range index → no callback
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest038, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.frameCount_ = 3;
    bool called = false;
    desc.updateCallbacks_[1] = [&called](const RefPtr<PixelMap>&) { called = true; };
    desc.FlushUpdateCallbacksByNodeId(3, 1);
    EXPECT_FALSE(called);
}

/**
 * @tc.name: AnimatedDrawableDescTest039
 * @tc.desc: FlushUpdateCallbacksByNodeId with unknown nodeId → no callback
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest039, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.frameCount_ = 3;
    auto pm = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm, GetHeight()).WillRepeatedly(Return(100));
    desc.pixelMapList_ = { pm };
    bool called = false;
    desc.updateCallbacks_[1] = [&called](const RefPtr<PixelMap>&) { called = true; };
    desc.FlushUpdateCallbacksByNodeId(0, 999);
    EXPECT_FALSE(called);
}

/**
 * @tc.name: AnimatedDrawableDescTest040
 * @tc.desc: FlushUpdateCallbacksByNodeId with valid params invokes callback
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest040, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto pm = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm, GetHeight()).WillRepeatedly(Return(100));
    desc.pixelMapList_ = { pm };
    desc.frameCount_ = 1;
    RefPtr<PixelMap> received;
    desc.updateCallbacks_[1] = [&received](const RefPtr<PixelMap>& p) { received = p; };
    desc.FlushUpdateCallbacksByNodeId(0, 1);
    EXPECT_EQ(received, pm);
}

/**
 * @tc.name: AnimatedDrawableDescTest041
 * @tc.desc: ControllAnimation with no animator for nodeId → early return, no crash
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest041, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_NO_FATAL_FAILURE(desc.ControllAnimation(1, true));
    EXPECT_NO_FATAL_FAILURE(desc.ControllAnimation(1, false));
    EXPECT_TRUE(desc.animators_.empty());
}

/**
 * @tc.name: AnimatedDrawableDescTest042
 * @tc.desc: ControllAnimation with play=true and autoPlay_=false → FlushUpdateCallbacksByNodeId(0)
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest042, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    desc.animators_[1] = animator;
    desc.autoPlay_ = false;
    auto pm = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm, GetWidth()).WillRepeatedly(Return(100));
    EXPECT_CALL(*pm, GetHeight()).WillRepeatedly(Return(100));
    desc.pixelMapList_ = { pm };
    desc.frameCount_ = 1;
    RefPtr<PixelMap> received;
    desc.updateCallbacks_[1] = [&received](const RefPtr<PixelMap>& p) { received = p; };
    desc.ControllAnimation(1, true);
    EXPECT_EQ(received, pm);
}

/**
 * @tc.name: AnimatedDrawableDescTest043
 * @tc.desc: ControllAnimation with play=false and animator not RUNNING → no pause
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest043, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    desc.animators_[1] = animator;
    desc.autoPlay_ = true;
    // Default ControlStatus is IDLE, so Pause should not be called
    auto statusBefore = animator->GetControlStatus();
    EXPECT_NO_FATAL_FAILURE(desc.ControllAnimation(1, false));
    EXPECT_EQ(animator->GetControlStatus(), statusBefore);
}

/**
 * @tc.name: AnimatedDrawableDescTest044
 * @tc.desc: GetDurations with frameCount_==0 and totalDuration_>=0 returns empty vector
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest044, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    desc.totalDuration_ = 100;
    desc.frameCount_ = 0;
    auto result = desc.GetDurations();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: AnimatedDrawableDescTest045
 * @tc.desc: GetPixelMap returns first frame from pixelMapList
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest045, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto pm1 = AceType::MakeRefPtr<MockPixelMap>();
    auto pm2 = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm1, GetWidth()).WillRepeatedly(Return(50));
    EXPECT_CALL(*pm1, GetHeight()).WillRepeatedly(Return(60));
    EXPECT_CALL(*pm2, GetWidth()).WillRepeatedly(Return(70));
    EXPECT_CALL(*pm2, GetHeight()).WillRepeatedly(Return(80));
    desc.pixelMapList_ = { pm1, pm2 };
    EXPECT_EQ(desc.GetPixelMap(), pm1);
}

/**
 * @tc.name: AnimatedDrawableDescTest046
 * @tc.desc: GetPixelMap with empty pixelMapList and no rawData returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest046, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    EXPECT_EQ(desc.GetPixelMap(), nullptr);
}

/**
 * @tc.name: AnimatedDrawableDescTest047
 * @tc.desc: GetOriginalWidth/Height with pixelMapList returns first frame dimensions
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, AnimatedDrawableDescTest047, TestSize.Level1)
{
    AnimatedDrawableDescriptor desc;
    auto pm = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pm, GetWidth()).WillRepeatedly(Return(200));
    EXPECT_CALL(*pm, GetHeight()).WillRepeatedly(Return(300));
    desc.pixelMapList_ = { pm };
    EXPECT_EQ(desc.GetOriginalWidth(), 200);
    EXPECT_EQ(desc.GetOriginalHeight(), 300);
}

/*============================================================================
 * PictureDrawableDescriptor tests
 *============================================================================*/

/**
 * @tc.name: PictureDrawableDescTest001
 * @tc.desc: Default constructor → GetDrawableType PICTURE
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest001, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    EXPECT_EQ(desc.GetDrawableType(), DrawableType::PICTURE);
}

/**
 * @tc.name: PictureDrawableDescTest002
 * @tc.desc: Constructor with Picture stores reference
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest002, TestSize.Level1)
{
    auto picture = AceType::MakeRefPtr<MockPicture>();
    EXPECT_CALL(*picture, GetMainPixel()).WillRepeatedly(Return(nullptr));
    PictureDrawableDescriptor desc(picture);
    EXPECT_EQ(desc.picture_, picture);
}

/**
 * @tc.name: PictureDrawableDescTest003
 * @tc.desc: SetPicture replaces stored picture
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest003, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    auto picture = AceType::MakeRefPtr<MockPicture>();
    EXPECT_CALL(*picture, GetMainPixel()).WillRepeatedly(Return(nullptr));
    desc.SetPicture(picture);
    EXPECT_EQ(desc.picture_, picture);
}

/**
 * @tc.name: PictureDrawableDescTest004
 * @tc.desc: GetPixelMap returns nullptr when no image loaded
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest004, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    EXPECT_EQ(desc.GetPixelMap(), nullptr);
}

/**
 * @tc.name: PictureDrawableDescTest005
 * @tc.desc: LoadSync with no picture → error -1
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest005, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    auto result = desc.LoadSync();
    EXPECT_EQ(result.imageWidth_, 0);
    EXPECT_EQ(result.imageHeight_, 0);
    EXPECT_EQ(result.errorCode, -1);
}

/**
 * @tc.name: PictureDrawableDescTest006
 * @tc.desc: SetHdrComposition stores config
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest006, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    HdrCompositionConfig config;
    config.rect.x = 10;
    config.rect.y = 20;
    config.rect.width = 100;
    config.rect.height = 200;
    desc.SetHdrComposition(config);
    EXPECT_EQ(desc.hdrConfig_.rect.x, 10);
    EXPECT_EQ(desc.hdrConfig_.rect.y, 20);
    EXPECT_EQ(desc.hdrConfig_.rect.width, 100);
    EXPECT_EQ(desc.hdrConfig_.rect.height, 200);
}

/**
 * @tc.name: PictureDrawableDescTest007
 * @tc.desc: RegisterUpdateCallback stores callback by nodeId
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest007, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    desc.RegisterUpdateCallback(42, [](const RefPtr<PixelMap>&) {});
    EXPECT_EQ(desc.updateCallbacks_.size(), 1u);
    EXPECT_NE(desc.updateCallbacks_.find(42), desc.updateCallbacks_.end());
}

/**
 * @tc.name: PictureDrawableDescTest008
 * @tc.desc: UnRegisterUpdateCallback removes callback by nodeId
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest008, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    desc.RegisterUpdateCallback(42, [](const RefPtr<PixelMap>&) {});
    EXPECT_EQ(desc.updateCallbacks_.size(), 1u);
    desc.UnRegisterUpdateCallback(42);
    EXPECT_EQ(desc.updateCallbacks_.size(), 0u);
}

/**
 * @tc.name: PictureDrawableDescTest009
 * @tc.desc: UnRegisterUpdateCallback with non-existent nodeId
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest009, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    desc.RegisterUpdateCallback(1, [](const RefPtr<PixelMap>&) {});
    desc.UnRegisterUpdateCallback(999);
    EXPECT_EQ(desc.updateCallbacks_.size(), 1u);
}

/**
 * @tc.name: PictureDrawableDescTest010
 * @tc.desc: IsHdrConfigValid returns false when rect has zero width/height
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest010, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    HdrCompositionConfig config;
    config.rect.width = 0;
    config.rect.height = 0;
    desc.SetHdrComposition(config);
    EXPECT_FALSE(desc.IsHdrConfigValid());
}

/**
 * @tc.name: PictureDrawableDescTest011
 * @tc.desc: IsHdrConfigValid returns true when rect has positive dimensions
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, PictureDrawableDescTest011, TestSize.Level1)
{
    PictureDrawableDescriptor desc;
    HdrCompositionConfig config;
    config.rect.width = 100;
    config.rect.height = 200;
    desc.SetHdrComposition(config);
    EXPECT_TRUE(desc.IsHdrConfigValid());
}

/*============================================================================
 * DrawableDescriptorLoader tests
 *============================================================================*/

/**
 * @tc.name: DrawableDescLoaderTest001
 * @tc.desc: GetInstance returns same instance (singleton)
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescLoaderTest001, TestSize.Level1)
{
    auto* instance1 = DrawableDescriptorLoader::GetInstance();
    auto* instance2 = DrawableDescriptorLoader::GetInstance();
    EXPECT_EQ(instance1, instance2);
}

/**
 * @tc.name: DrawableDescLoaderTest002
 * @tc.desc: LoadData with UNDEFINED src type → empty MediaData
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableDescLoaderTest002, TestSize.Level1)
{
    auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(EMPTY_PATH);
    auto result = DrawableDescriptorLoader::GetInstance()->LoadData(info);
    EXPECT_EQ(result.data, nullptr);
    EXPECT_EQ(result.len, 0u);
}

/*============================================================================
 * Enum and struct tests
 *============================================================================*/

/**
 * @tc.name: DrawableTypeTest001
 * @tc.desc: Verify DrawableType enum values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(DrawableType::BASE), 0);
    EXPECT_EQ(static_cast<int32_t>(DrawableType::LAYERED), 1);
    EXPECT_EQ(static_cast<int32_t>(DrawableType::ANIMATED), 2);
    EXPECT_EQ(static_cast<int32_t>(DrawableType::PIXELMAP), 3);
    EXPECT_EQ(static_cast<int32_t>(DrawableType::PICTURE), 4);
}

/**
 * @tc.name: DrawableTypeTest002
 * @tc.desc: Verify DrawableDescriptorInfo::SrcType enum values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest002, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(DrawableDescriptorInfo::SrcType::UNDEFINED), -1);
    EXPECT_EQ(static_cast<int32_t>(DrawableDescriptorInfo::SrcType::RESOURCE), 0);
    EXPECT_EQ(static_cast<int32_t>(DrawableDescriptorInfo::SrcType::BASE64), 1);
    EXPECT_EQ(static_cast<int32_t>(DrawableDescriptorInfo::SrcType::FILE), 2);
}

/**
 * @tc.name: DrawableTypeTest003
 * @tc.desc: Verify AnimationStopMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest003, TestSize.Level1)
{
    EXPECT_EQ(
        static_cast<int32_t>(AnimatedDrawableDescriptor::AnimationStopMode::FIRST_FRAME), 0);
    EXPECT_EQ(
        static_cast<int32_t>(AnimatedDrawableDescriptor::AnimationStopMode::LAST_FRAME), 1);
}

/**
 * @tc.name: DrawableTypeTest004
 * @tc.desc: Verify DrawableDescriptorLoadResult default values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest004, TestSize.Level1)
{
    DrawableDescriptorLoadResult result;
    EXPECT_EQ(result.imageWidth_, 0);
    EXPECT_EQ(result.imageHeight_, 0);
    EXPECT_EQ(result.errorCode, 0);
}

/**
 * @tc.name: DrawableTypeTest005
 * @tc.desc: Verify HdrCompositionConfig and Rectangle default values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest005, TestSize.Level1)
{
    HdrCompositionConfig config;
    EXPECT_EQ(config.rect.x, 0);
    EXPECT_EQ(config.rect.y, 0);
    EXPECT_EQ(config.rect.width, 0);
    EXPECT_EQ(config.rect.height, 0);
}

/**
 * @tc.name: DrawableTypeTest006
 * @tc.desc: Verify DrawableDescriptor::ImageSize default values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest006, TestSize.Level1)
{
    DrawableDescriptor::ImageSize size;
    EXPECT_EQ(size.width, 0);
    EXPECT_EQ(size.height, 0);
}

/**
 * @tc.name: DrawableTypeTest007
 * @tc.desc: Verify MediaData default values
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest007, TestSize.Level1)
{
    MediaData data;
    EXPECT_EQ(data.data, nullptr);
    EXPECT_EQ(data.len, 0u);
}

/**
 * @tc.name: DrawableTypeTest008
 * @tc.desc: Polymorphic GetDrawableType for each subclass
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest008, TestSize.Level1)
{
    DrawableDescriptor base;
    LayeredDrawableDescriptor layered;
    AnimatedDrawableDescriptor animated;
    PixelMapDrawableDescriptor pixelMap;
    PictureDrawableDescriptor picture;

    EXPECT_EQ(base.GetDrawableType(), DrawableType::BASE);
    EXPECT_EQ(layered.GetDrawableType(), DrawableType::LAYERED);
    EXPECT_EQ(animated.GetDrawableType(), DrawableType::ANIMATED);
    EXPECT_EQ(pixelMap.GetDrawableType(), DrawableType::PIXELMAP);
    EXPECT_EQ(picture.GetDrawableType(), DrawableType::PICTURE);
}

/**
 * @tc.name: DrawableTypeTest009
 * @tc.desc: AceType::MakeRefPtr works for all descriptor types
 * @tc.type: FUNC
 */
HWTEST_F(DrawableDescriptorTest, DrawableTypeTest009, TestSize.Level1)
{
    auto desc = AceType::MakeRefPtr<DrawableDescriptor>();
    EXPECT_EQ(desc->GetDrawableType(), DrawableType::BASE);

    auto layered = AceType::MakeRefPtr<LayeredDrawableDescriptor>();
    EXPECT_EQ(layered->GetDrawableType(), DrawableType::LAYERED);

    auto animated = AceType::MakeRefPtr<AnimatedDrawableDescriptor>();
    EXPECT_EQ(animated->GetDrawableType(), DrawableType::ANIMATED);

    auto pixelMap = AceType::MakeRefPtr<PixelMapDrawableDescriptor>();
    EXPECT_EQ(pixelMap->GetDrawableType(), DrawableType::PIXELMAP);

    auto picture = AceType::MakeRefPtr<PictureDrawableDescriptor>();
    EXPECT_EQ(picture->GetDrawableType(), DrawableType::PICTURE);
}
} // namespace OHOS::Ace
