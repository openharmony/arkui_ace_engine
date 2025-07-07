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

#define protected public
#define private public

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>
#include "core/image/image_file_cache.h"
#include "core/image/image_loader.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

const std::string CACHE_FILE_PATH = "/data";
class ImageLoaderTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: LoadDataFromCachedFile001
 * @tc.desc: write data into cacheFilePath success.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLoaderTest, LoadDataFromCachedFile001, TestSize.Level1)
{
    std::vector<uint8_t> imageData = { 1, 2, 3, 4, 5, 6 };
    std::string url = "http://testfilecache002/image";

    ImageFileCache::GetInstance().SetImageCacheFilePath(CACHE_FILE_PATH);
    auto imageFileCache = ImageLoader::LoadDataFromCachedFile(url);
    EXPECT_NE(imageFileCache, nullptr);

    std::string cacheFilePath(PATH_MAX + 1, 'a');
    ImageFileCache::GetInstance().SetImageCacheFilePath(cacheFilePath);

    imageFileCache = ImageLoader::LoadDataFromCachedFile(url);
    EXPECT_EQ(imageFileCache, nullptr);

    cacheFilePath = "";
    ImageFileCache::GetInstance().SetImageCacheFilePath(cacheFilePath);
    imageFileCache = ImageLoader::LoadDataFromCachedFile(url);
    EXPECT_EQ(imageFileCache, nullptr);
}
} // namespace OHOS::Ace