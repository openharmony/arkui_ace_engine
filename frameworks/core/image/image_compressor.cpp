/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifdef ENABLE_OPENCL
#include <securec.h>
#endif // ENABLE_OPENCL

#include "include/core/SkData.h"
#include "image/bitmap.h"
#include "utils/data.h"

#include "base/log/log.h"
#include "base/log/ace_trace.h"
#include "base/thread/background_task_executor.h"
#include "core/image/image_file_cache.h"
#include "core/image/image_compressor.h"

namespace OHOS::Ace {
__attribute__((constructor)) void load(void)
{
#ifdef ENABLE_OPENCL
#ifdef __MUSL__
    OHOS::InitOpenCL();
#endif
#endif
}

std::shared_ptr<ImageCompressor> ImageCompressor::instance_ = nullptr;
std::mutex ImageCompressor::instanceMutex_;
std::shared_ptr<ImageCompressor> ImageCompressor::GetInstance()
{
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(instanceMutex_);
        if (instance_ == nullptr) {
            instance_.reset(new ImageCompressor());
            instance_->Init();
        }
    }
    return instance_;
}

void ImageCompressor::Init()
{
#ifdef ENABLE_OPENCL
    switch_ = SystemProperties::IsAstcEnabled();
    if (switch_) {
        clOk_ = OHOS::InitOpenCL();
        maxErr_ = SystemProperties::GetAstcMaxError();
        psnr_ = SystemProperties::GetAstcPsnr();
        InitPartition();
        InitRecords();
    }
#endif // ENABLE_OPENCL
}

bool ImageCompressor::CanCompress()
{
#ifdef UPLOAD_GPU_DISABLED
    return false;
#else
    if (switch_ && clOk_) {
        return true;
    }
    return false;
#endif
}

#ifdef ENABLE_OPENCL
cl_program ImageCompressor::LoadShaderBin(cl_context context, cl_device_id device_id)
{
    ACE_FUNCTION_TRACE();
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(shader_path_.c_str(), "rb"), fclose);
    if (!file) {
        LOGE("load cl shader failed");
        return nullptr;
    }
    auto data = SkData::MakeFromFILE(file.get());
    if (!data) {
        return nullptr;
    }
    cl_int err;
    size_t len = data->size();
    auto ptr = (const unsigned char*) data->data();
    cl_program p = clCreateProgramWithBinary(context, 1, &device_id, &len, &ptr, NULL, &err);
    if (err) {
        return nullptr;
    }
    return p;
}

bool ImageCompressor::CreateKernel()
{
    if (!context_ || !kernel_) {
        cl_int err;
        cl_platform_id platform_id;
        cl_device_id device_id;
        clGetPlatformIDs(1, &platform_id, NULL);
        clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
        context_ = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
        queue_ = clCreateCommandQueueWithProperties(context_, device_id, 0, &err);

        cl_program program = LoadShaderBin(context_, device_id);
        clBuildProgram(program, 1, &device_id, compileOption_.c_str(), NULL, NULL);
        ACE_SCOPED_TRACE("clCreateKernel");
        kernel_ = clCreateKernel(program, "astc", &err);
        clReleaseProgram(program);
    }
    if (!context_ || !kernel_ || !queue_) {
        ReleaseResource();
        LOGE("build opencl program failed");
        clOk_ = false;
        return false;
    }
    refCount_++;
    return true;
}

bool ImageCompressor::CheckImageQuality(std::string key, uint32_t sumErr, uint32_t maxErr, int32_t width, int32_t height)
{
    bool isOk = true;
    float mse = (float)sumErr / (width * height);
    float psnr = 10 * log10(255 * 255 / mse);
    if (maxErr == 0 || psnr == 0 || maxErr > static_cast<uint32_t>(maxErr_)|| static_cast<int32_t>(psnr) < psnr_) {
        isOk = false;
        std::lock_guard<std::mutex> mLock(recordsMutex_);
        failedRecords_.insert(key);
    }
    LOGI("compress quality %{private}s [%{public}u, %{public}.2f] size(%{public}d×%{public}d) %{public}s",
        key.c_str(), maxErr, psnr, width, height, isOk ? "ok" : "no");
    return isOk;
}

void ImageCompressor::ReleaseResource()
{
    ACE_FUNCTION_TRACE();
    clReleaseKernel(kernel_);
    kernel_ = NULL;
    clReleaseCommandQueue(queue_);
    queue_ = NULL;
    clReleaseContext(context_);
    context_ = NULL;
}
#endif // ENABLE_OPENCL

std::shared_ptr<RSData> ImageCompressor::GpuCompress(std::string key, RSBitmap& bitmap, int32_t width, int32_t height)
{
#ifdef ENABLE_OPENCL
    std::lock_guard<std::mutex> lock(instanceMutex_);
    if (width <= 0 || height <= 0 || !clOk_ || IsFailedImage(key) || width > maxSize_ || height > maxSize_) {
        return nullptr;
    }
    if (!CreateKernel()) {
        return nullptr;
    }
    ACE_SCOPED_TRACE("GpuCompress %d×%d", width, height);

    cl_int err;

    // Number of work items in each local work group
    int32_t blockX = ceil((width + DIM - 1) / DIM);
    int32_t blockY = ceil((height + DIM - 1) / DIM);
    int32_t numBlocks = blockX * blockY;
    uint32_t uWidth = static_cast<uint32_t>(width);
    uint32_t uHeight = static_cast<uint32_t>(height);
    size_t local[] = { DIM, DIM };
    size_t global[2];
    global[0] = (uWidth % local[0] == 0 ? uWidth : (uWidth + local[0] - uWidth % local[0]));
    global[1] = (uHeight % local[1] == 0 ? uHeight : (uHeight + local[1] - uHeight % local[1]));

    size_t astc_size = static_cast<size_t>(numBlocks) * DIM * DIM;

    cl_image_format image_format = { CL_RGBA, CL_UNORM_INT8 };
    cl_image_desc desc = { CL_MEM_OBJECT_IMAGE2D, width, height };
    cl_mem inputImage = clCreateImage(context_, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        &image_format, &desc, bitmap.GetPixels(), &err);
    cl_mem astcResult = clCreateBuffer(context_, CL_MEM_ALLOC_HOST_PTR, astc_size, NULL, &err);
    cl_mem partInfos = clCreateBuffer(context_, CL_MEM_COPY_HOST_PTR,
        sizeof(PartInfo) * parts_.size(), &parts_[0], &err);

    uint32_t* blockErrs = new uint32_t[numBlocks]{0};
    cl_mem clErrs = clCreateBuffer(context_, CL_MEM_USE_HOST_PTR, sizeof(uint32_t) * numBlocks, blockErrs, &err);
    err |= clSetKernelArg(kernel_, 0, sizeof(cl_mem), &inputImage);
    err |= clSetKernelArg(kernel_, 1, sizeof(cl_mem), &astcResult);
    err |= clSetKernelArg(kernel_, 2, sizeof(cl_mem), &partInfos);
    err |= clSetKernelArg(kernel_, 3, sizeof(cl_mem), &clErrs);

    err = clEnqueueNDRangeKernel(queue_, kernel_, 2, NULL, global, local, 0, NULL, NULL);

    clFinish(queue_);

    uint32_t max_val = 0;
    uint32_t sum_val = 0;
    err = clEnqueueReadBuffer(queue_, clErrs, CL_TRUE, 0, sizeof(uint32_t) * numBlocks, blockErrs, 0, NULL, NULL);
    for (int32_t i = 0; i < numBlocks; i++) {
        sum_val += blockErrs[i];
        max_val = fmax(max_val, blockErrs[i]);
    }

    clReleaseMemObject(inputImage);
    clReleaseMemObject(partInfos);
    clReleaseMemObject(clErrs);
    delete[] blockErrs;

    if (!CheckImageQuality(key, sum_val, max_val, width, height)) {
        clReleaseMemObject(astcResult);
        return nullptr;
    }

    auto astc_data = std::make_shared<RSData>();
    astc_data->BuildUninitialized(astc_size);
    clEnqueueReadBuffer(queue_, astcResult, CL_TRUE, 0, astc_size, astc_data->WritableData(), 0, NULL, NULL);
    clReleaseMemObject(astcResult);
    return astc_data;
#else
    return nullptr;
#endif // ENABLE_OPENCL
}


std::function<void()> ImageCompressor::ScheduleReleaseTask()
{
#ifdef ENABLE_OPENCL
    std::function<void()> task = [this]() {
        if (refCount_ > 0 && clOk_) {
            refCount_--;
            if (refCount_ <= 0) {
                this->ReleaseResource();

                // save failed records
                std::ofstream saveFile(recordsPath_);
                if (!saveFile.is_open()) {
                    return;
                }
                std::lock_guard<std::mutex> mLock(recordsMutex_);
                for (auto s : failedRecords_) {
                    saveFile << s << "\n";
                }
                saveFile.close();
            }
        }
#else
    std::function<void()> task = []() {
#endif // ENABLE_OPENCL
    };

    return task;
}

void ImageCompressor::WriteToFile(std::string srcKey, std::shared_ptr<RSData> compressedData, Size imgSize)
{
    if (!compressedData || srcKey.empty()) {
        return;
    }
#ifdef ENABLE_OPENCL
    BackgroundTaskExecutor::GetInstance().PostTask(
        [srcKey, compressedData, imgSize]() {
            AstcHeader header;
            uint32_t xsize = static_cast<uint32_t>(imgSize.Width());
            uint32_t ysize = static_cast<uint32_t>(imgSize.Height());
            header.magic[0] = MAGIC_FILE_CONSTANT & 0xFF;
            header.magic[1] = (MAGIC_FILE_CONSTANT >> 8) & 0xFF;
            header.magic[2] = (MAGIC_FILE_CONSTANT >> 16) & 0xFF;
            header.magic[3] = (MAGIC_FILE_CONSTANT >> 24) & 0xFF;
            header.blockdimX = DIM;
            header.blockdimY = DIM;
            header.blockdimZ = 1;
            header.xsize[0] = xsize & 0xFF;
            header.xsize[1] = (xsize >> 8) & 0xFF;
            header.xsize[2] = (xsize >> 16) & 0xFF;
            header.ysize[0] = ysize & 0xFF;
            header.ysize[1] = (ysize >> 8) & 0xFF;
            header.ysize[2] = (ysize >> 16) & 0xFF;
            header.zsize[0] = 1;
            header.zsize[1] = 0;
            header.zsize[2] = 0;

            int32_t fileSize = compressedData->GetSize() + sizeof(header);
            auto toWrite = std::shared_ptr<RSData>();
            toWrite->BuildUninitialized(fileSize);
            uint8_t* toWritePtr = (uint8_t*) toWrite->WritableData();
            if (memcpy_s(toWritePtr, fileSize, &header, sizeof(header)) != EOK) {
                LOGE("astc write file failed");
                return;
            }
            if (memcpy_s(toWritePtr + sizeof(header), compressedData->GetSize(),
                    compressedData->GetData(), compressedData->GetSize()) != EOK) {
                LOGE("astc write file failed");
                return;
            }

            ImageFileCache::GetInstance().WriteCacheFile(srcKey, toWritePtr, fileSize, ".astc");
        }, BgTaskPriority::LOW);
#endif
}

std::shared_ptr<RSData> ImageCompressor::StripFileHeader(std::shared_ptr<RSData> fileData)
{
    if (fileData) {
        if (fileData->GetSize() <= sizeof(AstcHeader)) {
            return nullptr;
        }
        auto imageData = std::make_shared<RSData>();
        if (imageData->BuildWithCopy(static_cast<const uint8_t*>(fileData->GetData()) + sizeof(AstcHeader),
            fileData->GetSize() - sizeof(AstcHeader))) {
            return imageData;
        }
    }
    return nullptr;
}

/**
 * @brief Hash function used for procedural partition assignment.
 *
 * @param seed The hash seed.
 *
 * @return The hashed value.
 */
static uint32_t Hash52(uint32_t seed)
{
    seed ^= seed >> 15;

    // (2^4 + 1) * (2^7 + 1) * (2^17 - 1)
    seed *= 0xEEDE0891;
    seed ^= seed >> 5;
    seed += seed << 16;
    seed ^= seed >> 7;
    seed ^= seed >> 3;
    seed ^= seed << 6;
    seed ^= seed >> 17;
    return seed;
}

/**
 * @brief Select texel assignment for a single coordinate.
 *
 * @param seed              The seed - the partition index from the block.
 * @param x                 The texel X coordinate in the block.
 * @param y                 The texel Y coordinate in the block.
 * @param z                 The texel Z coordinate in the block.
 * @param partitionCount   The total partition count of this encoding.
 * @param smallBlock       @c true if the blockhas fewer than 32 texels.
 *
 * @return The assigned partition index for this texel.
 */
static uint8_t SelectPartition(int32_t seed, int32_t x, int32_t y, int32_t z, int32_t partitionCount, bool smallBlock)
{
    // For small blocks bias the coordinates to get better distribution
    if (smallBlock) {
        x *= 2;
        y *= 2;
        z *= 2;
    }

    seed += (partitionCount - 1) * 1024;

    uint32_t num = Hash52(seed);

    uint8_t seed1 = num & 0xF;
    uint8_t seed2 = (num >> 4) & 0xF;
    uint8_t seed3 = (num >> 8) & 0xF;
    uint8_t seed4 = (num >> 12) & 0xF;
    uint8_t seed5 = (num >> 16) & 0xF;
    uint8_t seed6 = (num >> 20) & 0xF;
    uint8_t seed7 = (num >> 24) & 0xF;
    uint8_t seed8 = (num >> 28) & 0xF;
    uint8_t seed9 = (num >> 18) & 0xF;
    uint8_t seed10 = (num >> 22) & 0xF;
    uint8_t seed11 = (num >> 26) & 0xF;
    uint8_t seed12 = ((num >> 30) | (num << 2)) & 0xF;

    // Squaring all the seeds in order to bias their distribution towards lower values.
    seed1 *= seed1;
    seed2 *= seed2;
    seed3 *= seed3;
    seed4 *= seed4;
    seed5 *= seed5;
    seed6 *= seed6;
    seed7 *= seed7;
    seed8 *= seed8;
    seed9 *= seed9;
    seed10 *= seed10;
    seed11 *= seed11;
    seed12 *= seed12;

    int32_t sh1, sh2;
    if (seed & 1) {
        sh1 = (seed & 2 ? 4 : 5);
        sh2 = (partitionCount == 3 ? 6 : 5);
    } else {
        sh1 = (partitionCount == 3 ? 6 : 5);
        sh2 = (seed & 2 ? 4 : 5);
    }

    int32_t sh3 = (seed & 0x10) ? sh1 : sh2;

    seed1 >>= sh1;
    seed2 >>= sh2;
    seed3 >>= sh1;
    seed4 >>= sh2;
    seed5 >>= sh1;
    seed6 >>= sh2;
    seed7 >>= sh1;
    seed8 >>= sh2;

    seed9 >>= sh3;
    seed10 >>= sh3;
    seed11 >>= sh3;
    seed12 >>= sh3;

    uint32_t a = static_cast<uint32_t>(seed1 * x + seed2 * y + seed11 * z + (num >> 14));
    uint32_t b = static_cast<uint32_t>(seed3 * x + seed4 * y + seed12 * z + (num >> 10));
    uint32_t c = static_cast<uint32_t>(seed5 * x + seed6 * y + seed9 * z + (num >> 6));
    uint32_t d = static_cast<uint32_t>(seed7 * x + seed8 * y + seed10 * z + (num >> 2));

    // Apply the saw
    a &= 0x3F;
    b &= 0x3F;
    c &= 0x3F;
    d &= 0x3F;

    // Remove some of the components if we are to output < 4 partitions_.
    if (partitionCount <= 3) {
        d = 0;
    }

    if (partitionCount <= 2) {
        c = 0;
    }

    if (partitionCount <= 1) {
        b = 0;
    }

    uint8_t partition;
    if (a >= b && a >= c && a >= d) {
        partition = 0;
    } else if (b >= c && b >= d) {
        partition = 1;
    } else if (c >= d) {
        partition = 2;
    } else {
        partition = 3;
    }

    return partition;
}

bool ImageCompressor::InitPartitionInfo(PartInfo *partInfos, int32_t part_index, int32_t part_count)
{
    int32_t texIdx = 0;
    int32_t counts[4] = {0};
    for (int32_t y = 0; y < DIM; y++) {
        for (int32_t x = 0; x < DIM; x++) {
            int32_t part = SelectPartition(part_index, x, y, 0, part_count, true);
            partInfos->bitmaps[part] |= 1u << texIdx;
            counts[part]++;
            texIdx++;
        }
    }
    int32_t realPartCount = 0;
    if (counts[0] == 0) {
        realPartCount = 0;
    } else if (counts[1] == 0) {
        realPartCount = 1;
    } else if (counts[2] == 0) {
        realPartCount = 2;
    } else if (counts[3] == 0) {
        realPartCount = 3;
    } else {
        realPartCount = 4;
    }
    if (realPartCount == part_count) {
        return true;
    }
    return false;
}

void ImageCompressor::InitPartition()
{
    parts_.clear();
    int32_t arrSize = sizeof(partitions_) / sizeof(partitions_[0]);
    for (int32_t i = 0; i < arrSize; i++) {
        PartInfo p = {};
        if (InitPartitionInfo(&p, partitions_[i], 2)) {
            p.partid = partitions_[i];
            parts_.push_back(p);
        }
    }
    compileOption_ = "-D PARTITION_SERACH_MAX=" + std::to_string(parts_.size());
}

#ifdef ENABLE_OPENCL
bool ImageCompressor::IsFailedImage(std::string key)
{
    std::lock_guard<std::mutex> mLock(recordsMutex_);
    return failedRecords_.find(key) != failedRecords_.end();
}
#endif

void ImageCompressor::InitRecords()
{
    recordsPath_ = ImageFileCache::GetInstance().GetImageCacheFilePath("record") + ".txt";
    std::ifstream openFile(recordsPath_);
    if (!openFile.is_open()) {
        return;
    }
    std::string line;
    std::lock_guard<std::mutex> mLock(recordsMutex_);
    while (!openFile.eof()) {
        std::getline(openFile, line);
        failedRecords_.insert(line);
    }
    openFile.close();
}
#ifdef FUZZTEST
void ImageCompressor::PartDoing()
{
    InitPartition();
    InitRecords();
}
#endif
} // namespace OHOS::Ace
