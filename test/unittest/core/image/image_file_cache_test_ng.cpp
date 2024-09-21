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

#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/image/image_file_cache.h"
#include "base/utils/system_properties.h"

#include "test/mock/base/mock_image_packer.h"
#include "test/mock/base/mock_image_source.h"
#include "test/mock/base/mock_pixel_map.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
const std::string ASTC_SUFFIX = ".astc";
const std::string CACHE_FILE_PATH = "/data/test/resource/imagecache/images";
const std::string SVG_FORMAT = "image/svg+xml";
class ImageFileCacheTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void WaitForAsyncTasks();

    void SetUp() override;
    void TearDown() override;
};

void ImageFileCacheTestNg::SetUpTestSuite()
{
    ImageFileCache::GetInstance().SetImageCacheFilePath(CACHE_FILE_PATH);
}

void ImageFileCacheTestNg::SetUp()
{
    SystemProperties::imageFileCacheConvertAstc_ = true;
    ImageFileCache::GetInstance().fileNameToFileInfoPos_.clear();
    ImageFileCache::GetInstance().cacheFileInfo_.clear();
    ImageFileCache::GetInstance().cacheFileSize_ = 0;
}

void ImageFileCacheTestNg::TearDown()
{
}
    
void ImageFileCacheTestNg::TearDownTestSuite()
{
    MockImagePacker::mockImagePacker_ = nullptr;
    MockImageSource::mockImageSource_ = nullptr;
}

// wait for load task to finish
void ImageFileCacheTestNg::WaitForAsyncTasks()
{
}

/**
 * @tc.name: WriteCacheFileFunc001
 * @tc.desc: Test WriteCacheFileFun with convert astc enabled.
 * @tc.type: FUNC
 */
HWTEST_F(ImageFileCacheTestNg, WriteCacheFileFunc001, TestSize.Level1)
{
    RefPtr<MockImagePacker> mockImagePacker = AceType::MakeRefPtr<MockImagePacker>();
    RefPtr<MockImageSource> mockImageSource = AceType::MakeRefPtr<MockImageSource>();
    RefPtr<MockPixelMap> mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    MockImagePacker::mockImagePacker_ = mockImagePacker;
    MockImageSource::mockImageSource_ = mockImageSource;
    /**
     * @tc.steps: step1. construct a data.
     */
    std::vector<uint8_t> imageData = {1, 2, 3, 4, 5, 6};
    std::string url = "http:/testfilecache002/image";
    std::string fileCacheKey = std::to_string(std::hash<std::string> {}(url));

    /**
     * @tc.steps: step2. call WriteCacheFile().
     */
    ImageFileCache::GetInstance().WriteCacheFile(url, imageData.data(), imageData.size());
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageData.size()));
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
    FileInfo fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
    size_t accessCount = fileInfo.accessCount;
    ASSERT_EQ(accessCount, 1);

    /**
     * @tc.steps: step3. call GetCacheFilePathInner(), each call will increase accessCount by one,
     *            when accessCount reaches convertAstcThreshold, ConvertToAstcAndWriteToFile() will be called.
     * @tc.expected: after ConvertToAstcAndWriteToFile() is called, fileInfo get updated, fileName contains ASTC_SUFFIX.
     */
    std::string filePath;
    auto convertAstcThreshold = SystemProperties::GetImageFileCacheConvertAstcThreshold();
    while (accessCount < convertAstcThreshold) {
        accessCount++;
        bool convertToAstc = accessCount == convertAstcThreshold;
        if (convertToAstc) {
            EXPECT_CALL(*mockImageSource, GetFrameCount()).WillOnce(Return(1));
            EXPECT_CALL(*mockImageSource, CreatePixelMap(_, AIImageQuality::NONE, false))
                .WillOnce(Return(mockPixelMap));
            EXPECT_CALL(*mockImagePacker, FinalizePacking(_))
                .WillOnce(DoAll(SetArgReferee<0>(imageData.size()), Return(0)));
        }
        filePath = ImageFileCache::GetInstance().GetCacheFilePathInner(url, "");
        ASSERT_EQ(filePath, ImageFileCache::GetInstance().ConstructCacheFilePath(fileCacheKey));
        if (convertToAstc) {
            sleep(1);
        }
        ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageData.size()));
        ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
        fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
        ASSERT_EQ(fileInfo.fileName, convertToAstc ? fileCacheKey + ASTC_SUFFIX : fileCacheKey);
        ASSERT_EQ(fileInfo.accessCount, accessCount);
    }
}

/**
 * @tc.name: WriteCacheFileFunc002
 * @tc.desc: Test WriteCacheFileFun with convert astc disabled.
 * @tc.type: FUNC
 */
HWTEST_F(ImageFileCacheTestNg, WriteCacheFileFunc002, TestSize.Level1)
{
    SystemProperties::imageFileCacheConvertAstc_ = false;

    /**
     * @tc.steps: step1. construct a data.
     */
    std::vector<uint8_t> imageData = {1, 2, 3, 4, 5, 6};
    std::string url = "http:/testfilecache002/image";
    std::string fileCacheKey = std::to_string(std::hash<std::string> {}(url));

    /**
     * @tc.steps: step2. call WriteCacheFile().
     */
    ImageFileCache::GetInstance().WriteCacheFile(url, imageData.data(), imageData.size());
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageData.size()));
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
    FileInfo fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
    size_t accessCount = fileInfo.accessCount;
    ASSERT_EQ(accessCount, 1);

    /**
     * @tc.steps: step3. call GetCacheFilePathInner(), each call will increase accessCount by one,
     *            when accessCount reaches convertAstcThreshold, ConvertToAstcAndWriteToFile() will not be called.
     * @tc.expected: fileInfo will not update, fileName does not contain ASTC_SUFFIX.
     */
    std::string filePath;
    auto convertAstcThreshold = SystemProperties::GetImageFileCacheConvertAstcThreshold();
    while (accessCount < convertAstcThreshold) {
        accessCount++;
        filePath = ImageFileCache::GetInstance().GetCacheFilePathInner(url, "");
        ASSERT_EQ(filePath, ImageFileCache::GetInstance().ConstructCacheFilePath(fileCacheKey));
        ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageData.size()));
        ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
        fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
        ASSERT_EQ(fileInfo.fileName, fileCacheKey);
        ASSERT_EQ(fileInfo.accessCount, accessCount);
    }
}

/**
 * @tc.name: WriteCacheFileFunc003
 * @tc.desc: Test WriteCacheFileFun with suffix.
 * @tc.type: FUNC
 */
HWTEST_F(ImageFileCacheTestNg, WriteCacheFileFunc003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a data.
     */
    std::vector<uint8_t> imageData = {1, 2, 3, 4, 5, 6};
    std::vector<uint8_t> imageDataWithSuffix = {1, 2, 3, 4, 5, 6, 7};
    std::string url = "http:/testfilecache002/image";
    std::string fileCacheKey = std::to_string(std::hash<std::string> {}(url));

    /**
     * @tc.steps: step2. call WriteCacheFile().
     */
    ImageFileCache::GetInstance().WriteCacheFile(url, imageData.data(), imageData.size());
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageData.size()));
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
    FileInfo fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
    ASSERT_EQ(fileInfo.fileName, fileCacheKey);
    ASSERT_EQ(fileInfo.accessCount, 1);

    /**
     * @tc.steps: step3. call WriteCacheFile() with suffix.
     * @tc.expected: fileInfo will update to imageDataWithSuffix.
     */
    std::string suffix = ".jpg";
    ImageFileCache::GetInstance().WriteCacheFile(url, imageDataWithSuffix.data(), imageDataWithSuffix.size(), suffix);
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageDataWithSuffix.size()));
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
    fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
    ASSERT_EQ(fileInfo.fileName, fileCacheKey + suffix);
    ASSERT_EQ(fileInfo.accessCount, 1);
}

/**
 * @tc.name: WriteCacheFileFunc004
 * @tc.desc: Test WriteCacheFileFun with svg.
 * @tc.type: FUNC
 */
HWTEST_F(ImageFileCacheTestNg, WriteCacheFileFunc004, TestSize.Level1)
{
    RefPtr<MockImageSource> mockImageSource = AceType::MakeRefPtr<MockImageSource>();
    MockImageSource::mockImageSource_ = mockImageSource;
    /**
     * @tc.steps: step1. construct a data.
     */
    std::vector<uint8_t> imageData = {1, 2, 3, 4, 5, 6};
    std::string url = "http:/testfilecache002/image";
    std::string fileCacheKey = std::to_string(std::hash<std::string> {}(url));

    /**
     * @tc.steps: step2. call WriteCacheFile().
     */
    ImageFileCache::GetInstance().WriteCacheFile(url, imageData.data(), imageData.size());
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageData.size()));
    ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
    FileInfo fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
    size_t accessCount = fileInfo.accessCount;
    ASSERT_EQ(accessCount, 1);

    /**
     * @tc.steps: step3. call GetCacheFilePathInner(), each call will increase accessCount by one,
     *            when accessCount reaches convertAstcThreshold, ConvertToAstcAndWriteToFile() will be called.
     * @tc.expected: because image is svg format, will not do the convert, fileInfo will not update,
     *               fileName does not contain ASTC_SUFFIX.
     */
    std::string filePath;
    auto convertAstcThreshold = SystemProperties::GetImageFileCacheConvertAstcThreshold();
    while (accessCount <= convertAstcThreshold) {
        accessCount++;
        bool convertToAstc = accessCount == convertAstcThreshold;
        if (convertToAstc) {
            EXPECT_CALL(*mockImageSource, GetFrameCount()).WillOnce(Return(1));
            EXPECT_CALL(*mockImageSource, GetEncodedFormat()).WillOnce(Return(SVG_FORMAT));
        }
        filePath = ImageFileCache::GetInstance().GetCacheFilePathInner(url, "");
        ASSERT_EQ(filePath, ImageFileCache::GetInstance().ConstructCacheFilePath(fileCacheKey));
        if (convertToAstc) {
            sleep(1);
        }
        ASSERT_EQ(ImageFileCache::GetInstance().cacheFileSize_, static_cast<int32_t>(imageData.size()));
        ASSERT_EQ(ImageFileCache::GetInstance().cacheFileInfo_.size(), 1);
        fileInfo = ImageFileCache::GetInstance().cacheFileInfo_.front();
        ASSERT_EQ(fileInfo.fileName, fileCacheKey);
        ASSERT_EQ(fileInfo.accessCount, accessCount);
    }
}
} // namespace OHOS::Ace::NG
