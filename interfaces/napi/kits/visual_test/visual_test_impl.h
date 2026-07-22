/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_INTERFACES_NAPI_KITS_VISUAL_TEST_VISUAL_TEST_IMPL_H
#define FOUNDATION_ACE_INTERFACES_NAPI_KITS_VISUAL_TEST_VISUAL_TEST_IMPL_H

#include <cstdint>
#include <string>
#include <vector>

namespace VisualTest {

struct CapturedFrame {
    std::vector<uint8_t> data;
    int32_t width = 0;
    int32_t height = 0;
};

struct CompareResult {
    bool pass = false;
    double score = 0.0;
};

struct ScreenSize {
    int32_t width = 0;
    int32_t height = 0;
};

void SetOutputDir(const std::string& dir);
std::string GetOutputDir();
void SetHapDir(const std::string& dir);
std::string GetHapDir();

ScreenSize GetScreenSize();
bool IsPreviewer();

CapturedFrame CaptureFrame();

CompareResult CompareImages(const uint8_t* actual, int32_t aw, int32_t ah,
                            const uint8_t* golden, int32_t gw, int32_t gh,
                            double threshold);

std::vector<uint8_t> ReadPNG(const std::string& path, int32_t* outW, int32_t* outH);
bool WritePNG(const uint8_t* rgba, int32_t w, int32_t h, const std::string& path);
bool WriteDiffPNG(const uint8_t* actual, const uint8_t* golden,
                  int32_t w, int32_t h, const std::string& path);
bool WriteFile(const std::string& path, const uint8_t* data, size_t size);

void RequestRenderStable();
bool IsRenderStable();
void CheckRenderStable();

void RegisterFrameData(const void* data, int32_t width, int32_t height);

void SetHeadlessDone();
bool IsHeadlessDone();

} // namespace VisualTest

#endif // FOUNDATION_ACE_INTERFACES_NAPI_KITS_VISUAL_TEST_VISUAL_TEST_IMPL_H
