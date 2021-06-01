/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/image/test/unittest/image_cache_test.h"

#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class ImageCacheTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}

    RefPtr<ImageCache> imageCache = ImageCache::Create();
};

/**
 * @tc.name: MemoryCache001
 * @tc.desc: new image success insert into cache with LRU.
 * @tc.type: FUNC
 */
HWTEST_F(ImageCacheTest, MemoryCache001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. cache images one by one.
     * @tc.expected: new item should at begin of cacheList_ and imagCache has right iters.
     */
    for (size_t i = 0; i < CACHE_FILES.size(); i++) {
        imageCache->CacheImage(FILE_KEYS[i], std::make_shared<CachedImage>(flutter::CanvasImage::Create()));
        std::string frontKey = (imageCache->cacheList_).front().imageKey;
        ASSERT_EQ(frontKey, FILE_KEYS[i]);
        ASSERT_EQ(frontKey, imageCache->imageCache_[FILE_KEYS[i]]->imageKey);
    }

    /**
     * @tc.steps: step2. cache a image already in cache for example FILE_KEYS[3] e.t. "key4".
     * @tc.expected: the cached item should at begin of cacheList_ and imagCache has right iters.
     */
    imageCache->CacheImage(FILE_KEYS[3], std::make_shared<CachedImage>(flutter::CanvasImage::Create()));
    ASSERT_EQ(imageCache->cacheList_.front().imageKey, FILE_KEYS[3]);
    ASSERT_EQ(imageCache->imageCache_[FILE_KEYS[3]]->imageKey, FILE_KEYS[3]);
}

/**
 * @tc.name: MemoryCache002
 * @tc.desc: get image success in cache with LRU.
 * @tc.type: FUNC
 */
HWTEST_F(ImageCacheTest, MemoryCache002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. cache images one by one.
     */
    for (size_t i = 0; i < CACHE_FILES.size(); i++) {
        imageCache->CacheImage(FILE_KEYS[i], std::make_shared<CachedImage>(flutter::CanvasImage::Create()));
        std::string frontKey = (imageCache->cacheList_).front().imageKey;
    }
    /**
     * @tc.steps: step2. find a image already in cache for example FILE_KEYS[2] e.t. "key3".
     * @tc.expected: the cached iterator should not at end() of cacheList_ and imagCache.
     *              after GetImageCache(), the item should at begin() of cacheList_.
     */
    auto iter = (imageCache->imageCache_).find(FILE_KEYS[2]);
    ASSERT_NE(iter, imageCache->imageCache_.end());
    imageCache->GetCacheImage(FILE_KEYS[2]);
    ASSERT_EQ(imageCache->cacheList_.front().imageKey, FILE_KEYS[2]);
    ASSERT_EQ(imageCache->imageCache_[FILE_KEYS[2]]->imageKey, FILE_KEYS[2]);

    /**
     * @tc.steps: step3. find a image not in cache for example "key8".
     * @tc.expected: return null.
     */
    auto image = imageCache->GetCacheImage("key8");
    ASSERT_EQ(image, nullptr);
}

/**
 * @tc.name: MemoryCache003
 * @tc.desc: Set memory cache capacity success.
 * @tc.type: FUNC
 */
HWTEST_F(ImageCacheTest, MemoryCache003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.check default capaticy
     */
    ASSERT_EQ(static_cast<int32_t>(imageCache->capacity_), 80);

    /**
     * @tc.steps: step2. call set capacity.
     * @tc.expected: capacity set to 1000.
     */
    imageCache->SetCapacity(1000);
    ASSERT_EQ(static_cast<int32_t>(imageCache->capacity_), 1000);
}

/**
 * @tc.name: FileCache001
 * @tc.desc: init cacheFilePath and cacheFileInfo success.
 * @tc.type: FUNC
 */
HWTEST_F(ImageCacheTest, FileCache001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.call SetImageCacheFilePath().
     * @tc.expected: cache file size init right and cache file Info init right.
     */
    ImageCache::SetImageCacheFilePath(CACHE_FILE_PATH);
    ASSERT_EQ(ImageCache::cacheFilePath_, CACHE_FILE_PATH);

    /**
     * @tc.steps: step2. call SetCacheFileInfo().
     * @tc.expected: file info init right.
     */
    ImageCache::SetCacheFileInfo();
    ASSERT_EQ(ImageCache::cacheFileSize_, FILE_SIZE);
    ASSERT_EQ(static_cast<int32_t>(ImageCache::cacheFileInfo_.size()), 5);
    size_t i = 0;
    auto iter = ImageCache::cacheFileInfo_.begin();
    while (i < TEST_COUNT - 1) {
        ASSERT_LE(iter->accessTime, (++iter)->accessTime);
        i++;
    }
}

/**
 * @tc.name: FileCache002
 * @tc.desc: write data into cacheFilePath success.
 * @tc.type: FUNC
 */
HWTEST_F(ImageCacheTest, FileCache002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.construct a data.
     */
    std::vector<uint8_t> imageData = { 1, 2, 3, 4, 5, 6 };
    std::string url = "http:/testfilecache002/image";

    /**
     * @tc.steps: step2. call WriteCacheFile().
     * @tc.expected: file write into filePath and file info update right.
     */
    ImageCache::WriteCacheFile(url, imageData);
    ASSERT_EQ(ImageCache::cacheFileSize_, static_cast<int32_t>(FILE_SIZE + imageData.size()));
    ASSERT_EQ(ImageCache::cacheFileInfo_.size(), TEST_COUNT + 1);
    auto iter = ImageCache::cacheFileInfo_.rbegin();

    ASSERT_EQ(iter->filePath, ImageCache::GetNetworkImageCacheFilePath(url));
}

/**
 * @tc.name: FileCache003
 * @tc.desc: Get data from cacheFilePath success with right url. but null with wrong url.
 * @tc.type: FUNC
 */
HWTEST_F(ImageCacheTest, FileCache003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set cacheFileLimit_ to 0.
     */
    std::string wrongFilePath = "/data/wrong_data";
    /**
     * @tc.steps: step2. call GetFromCacheFile().
     * @tc.expected:data != nullptr.
     */
    auto data = ImageCache::GetFromCacheFile(CACHE_IMAGE_FILE_2);
    ASSERT_TRUE(data);
    auto nullData = ImageCache::GetFromCacheFile(wrongFilePath);
    ASSERT_TRUE(!nullData);
}

/**
 * @tc.name: FileCache004
 * @tc.desc: clear files from cacheFilePath success while write file exceed limit.
 * @tc.type: FUNC
 */
HWTEST_F(ImageCacheTest, FileCache004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.set cacheFileLimit_ to 0.
     */
    ImageCache::SetCacheFileLimit(0);
    ASSERT_EQ(static_cast<int32_t>(ImageCache::cacheFileLimit_), 0);

    /**
     * @tc.steps: step2. call WriteCacheFile().
     * @tc.expected: file write into filePath and file info update right.
     */
    std::vector<uint8_t> imageData = { 1, 2, 3 };
    std::string url = "http:/testfilecache003/image";
    ImageCache::WriteCacheFile(url, imageData);
    float ratio = ImageCache::clearCacheFileRatio_;
    ASSERT_EQ(ImageCache::cacheFileInfo_.size(), static_cast<size_t>((TEST_COUNT + 2) * ratio + 1));
    ASSERT_LE(ImageCache::cacheFileSize_, FILE_SIZE);
}

} // namespace OHOS::Ace