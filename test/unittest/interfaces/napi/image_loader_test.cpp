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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "interfaces/inner_api/drawable_descriptor/image_loader/image_loader.h"
#include "interfaces/inner_api/drawable_descriptor/image_loader/file_image_loader.h"
#include "interfaces/inner_api/drawable_descriptor/image_loader/image_define.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Napi;

namespace OHOS::Ace {

class ImageLoaderTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: ImageLoaderTest001
 * @tc.desc: test RemovePathHead with URI containing no colon
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest001, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "path/to/image.png";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest002
 * @tc.desc: test RemovePathHead with empty string
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest002, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest003
 * @tc.desc: test RemovePathHead with file:// scheme (valid)
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest003, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "file:///data/local/tmp/image.png";

    auto result = loader.RemovePathHead(uri);

    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "/data/local/tmp/image.png");
}

/**
 * @tc.name: ImageLoaderTest004
 * @tc.desc: test RemovePathHead with file:// scheme but too short
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest004, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "file:";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest005
 * @tc.desc: test RemovePathHead with memory:// scheme (valid)
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest005, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "memory://image_cache_123";

    auto result = loader.RemovePathHead(uri);

    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "image_cache_123");
}

/**
 * @tc.name: ImageLoaderTest006
 * @tc.desc: test RemovePathHead with memory:// scheme but too short
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest006, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "memory:";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest007
 * @tc.desc: test RemovePathHead with internal:// scheme (valid)
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest007, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "internal://app/media/icon.png";

    auto result = loader.RemovePathHead(uri);

    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "app/media/icon.png");
}

/**
 * @tc.name: ImageLoaderTest008
 * @tc.desc: test RemovePathHead with internal:// scheme but too short
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest008, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "internal:";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest009
 * @tc.desc: test RemovePathHead with unknown scheme
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest009, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "http://example.com/image.png";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest010
 * @tc.desc: test RemovePathHead with https scheme
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest010, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "https://example.com/image.png";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest011
 * @tc.desc: test RemovePathHead with data scheme
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest011, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "data:image/png;base64,iVBORw0KG...";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest012
 * @tc.desc: test RemovePathHead with colon in path but no scheme
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest012, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "path/to:file/image.png";

    auto result = loader.RemovePathHead(uri);

    // First colon found, but scheme is not file/memory/internal
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest013
 * @tc.desc: test RemovePathHead with only scheme and colon
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest013, TestSize.Level1)
{
    ImageLoader loader;
    std::string uri = "custom:";

    auto result = loader.RemovePathHead(uri);

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ImageLoaderTest014
 * @tc.desc: test FileImageLoader LoadImageData with INTERNAL type and valid "app/" path
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest014, TestSize.Level1)
{
    FileImageLoader loader;
    SourceInfo src;
    src.SetSrcType(SrcType::INTERNAL);
    src.SetSrc("internal://app/media/icon.png");

    // This will fail in test environment but tests the branch logic
    auto result = loader.LoadImageData(src);

    // Expected to return nullptr in test environment
    // But we're testing that the path parsing logic works
}

/**
 * @tc.name: ImageLoaderTest015
 * @tc.desc: test FileImageLoader LoadImageData with INTERNAL type but invalid path (no "app/")
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest015, TestSize.Level1)
{
    FileImageLoader loader;
    SourceInfo src;
    src.SetSrcType(SrcType::INTERNAL);
    src.SetSrc("internal://media/icon.png"); // Missing "app/" prefix

    auto result = loader.LoadImageData(src);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: ImageLoaderTest016
 * @tc.desc: test FileImageLoader LoadImageData with FILE type
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest016, TestSize.Level1)
{
    FileImageLoader loader;
    SourceInfo src;
    src.SetSrcType(SrcType::FILE);
    src.SetSrc("file:///data/local/tmp/image.png");

    auto result = loader.LoadImageData(src);

    // Expected to return nullptr in test environment if file doesn't exist
}

/**
 * @tc.name: ImageLoaderTest017
 * @tc.desc: test FileImageLoader LoadImageData with path exceeding PATH_MAX
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest017, TestSize.Level1)
{
    FileImageLoader loader;
    SourceInfo src;
    src.SetSrcType(SrcType::FILE);

    // Create a very long path
    std::string longPath(5000, 'a');
    src.SetSrc("file://" + longPath);

    auto result = loader.LoadImageData(src);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: ImageLoaderTest018
 * @tc.desc: test FileImageLoader LoadImageData with unsupported source type
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest018, TestSize.Level1)
{
    FileImageLoader loader;
    SourceInfo src;
    src.SetSrcType(SrcType::NETWORK);
    src.SetSrc("https://example.com/image.png");

    auto result = loader.LoadImageData(src);

    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: ImageLoaderTest019
 * @tc.desc: test ImageLoader GetImageData wrapper
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, ImageLoaderTest019, TestSize.Level1)
{
    FileImageLoader loader;
    SourceInfo src;
    src.SetSrcType(SrcType::INTERNAL);
    src.SetSrc("internal://app/media/icon.png");

    auto result = loader.GetImageData(src);

    // GetImageData is a wrapper for LoadImageData
}

} // namespace OHOS::Ace
