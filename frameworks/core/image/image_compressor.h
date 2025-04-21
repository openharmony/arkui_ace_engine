/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_COMPRESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_COMPRESSOR_H

#include <atomic>
#include <mutex>
#include <set>

#include "base/geometry/size.h"
#ifdef ENABLE_OPENCL
#define USE_OPENCL_WRAPPER
#include "opencl_wrapper.h"
#endif // ENABLE_OPENCL
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace {
#define MAGIC_FILE_CONSTANT 0x5CA1AB13
#define DIM 4
typedef struct {
    uint8_t magic[4];
    uint8_t blockdimX;
    uint8_t blockdimY;
    uint8_t blockdimZ;
    uint8_t xsize[3];
    uint8_t ysize[3];
    uint8_t zsize[3];
} AstcHeader;

class ImageCompressor {
public:
    static std::shared_ptr<ImageCompressor> GetInstance();
    static const int32_t releaseTimeMs = 1000;

    bool CanCompress();
    std::shared_ptr<RSData> GpuCompress(std::string key, RSBitmap& bitmap, int32_t width, int32_t height);
    std::function<void()> ScheduleReleaseTask();
    void WriteToFile(std::string key, std::shared_ptr<RSData> compressdImage, Size size);
    static std::shared_ptr<RSData> StripFileHeader(std::shared_ptr<RSData> fileData);
#ifdef FUZZTEST
    void PartDoing();
#endif
private:
    static std::shared_ptr<ImageCompressor> instance_;
    static std::mutex instanceMutex_;

    bool clOk_;
    bool switch_;
    void Init();
#ifdef ENABLE_OPENCL
    static const int32_t maxSize_ = 100000;
    int32_t maxErr_;
    int32_t psnr_;
    const std::string shader_path_ = "/system/bin/astc.bin";
    std::atomic<int32_t> refCount_;
    cl_context context_;
    cl_command_queue queue_;
    cl_kernel kernel_;

    cl_program LoadShaderBin(cl_context context, cl_device_id device_id);
    bool CreateKernel();
    void ReleaseResource();
    bool CheckImageQuality(std::string key, uint32_t sumErr, uint32_t maxErr, int32_t width, int32_t height);
    bool IsFailedImage(std::string key);
#endif
    int32_t partitions_[73] = {
        2, 5, 9, 14, 16, 17, 20, 24, 25, 28, 36, 39, 43, 48, 49, 50, 51, 53, 55, 61, 72, 78, 107, 113, 116, 149, 156,
        198, 204, 210, 216, 226, 232, 239, 269, 273, 293, 324, 344, 348, 359, 389, 394, 441, 443, 475, 476, 479, 496,
        511, 567, 593, 594, 600, 601, 666, 684, 703, 726, 730, 732, 756, 796, 799, 828, 958, 959, 988, 993
    };
    struct PartInfo {
        int32_t partid;
        uint32_t bitmaps[2];
    };
    void InitPartition();
    bool InitPartitionInfo(PartInfo *partInfo, int32_t partIndex, int32_t partCount);
    std::vector<PartInfo> parts_;
    std::string compileOption_;

    std::mutex recordsMutex_;
    std::set<std::string> failedRecords_;
    std::string recordsPath_;
    void InitRecords();
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_COMPRESSOR_H
