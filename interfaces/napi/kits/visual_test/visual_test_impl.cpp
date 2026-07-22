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

#include "visual_test_impl.h"

#include <png.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <atomic>
#include <mutex>
#include <functional>
#include <sys/stat.h>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

#ifdef PREVIEW
// Previewer: no ace_engine pipeline access needed
#else
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/window.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/components_ng/render/snapshot_param.h"
#include "base/image/pixel_map.h"
#endif

namespace VisualTest {

namespace {

#ifdef PREVIEW
std::string g_outputDir = "./output";
#else
std::string g_outputDir = "/tmp/output";
#endif
std::mutex g_frameMutex;
CapturedFrame g_lastFrame;
std::atomic<bool> g_renderStableFlag{false};
std::atomic<bool> g_renderStableRequested{false};
int g_stableFrameCount = 0;
const int STABLE_FRAME_THRESHOLD = 1;
#ifdef PREVIEW
std::atomic<bool> s_hasFrame{false};
std::atomic<bool> g_headlessDone{false};
#endif

struct PixelColor {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    PixelColor() = default;
    PixelColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

    double Luminance() const
    {
        return 0.299 * r + 0.587 * g + 0.114 * b;
    }

    void ToLAB(double& L, double& a, double& b) const
    {
        auto srgb = [](uint8_t c) {
            double v = c / 255.0;
            return v <= 0.04045 ? v / 12.92 : std::pow((v + 0.055) / 1.055, 2.4);
        };
        double rl = srgb(r), gl = srgb(g), bl = srgb(b);
        double X = rl * 0.4124 + gl * 0.3576 + bl * 0.1805;
        double Y = rl * 0.2126 + gl * 0.7152 + bl * 0.0722;
        double Z = rl * 0.0193 + gl * 0.1192 + bl * 0.9505;
        X /= 0.95047;
        Y /= 1.0;
        Z /= 1.08883;
        auto f = [](double t) { return t > 0.008856 ? std::cbrt(t) : 7.787 * t + 16.0 / 116.0; };
        double fx = f(X), fy = f(Y), fz = f(Z);
        L = 116.0 * fy - 16.0;
        a = 500.0 * (fx - fy);
        b = 200.0 * (fy - fz);
    }

    double LabDistance(const PixelColor& o) const
    {
        double L1, a1, b1, L2, a2, b2;
        ToLAB(L1, a1, b1);
        o.ToLAB(L2, a2, b2);
        return std::sqrt((L1 - L2) * (L1 - L2) + (a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2));
    }
};

} // namespace

void SetOutputDir(const std::string& dir)
{
    g_outputDir = dir;
}

std::string GetOutputDir()
{
    return g_outputDir;
}

namespace {
std::string g_hapDir;
}

void SetHapDir(const std::string& dir)
{
    g_hapDir = dir;
}

std::string GetHapDir()
{
    return g_hapDir;
}

bool IsPreviewer()
{
#ifdef PREVIEW
    return true;
#else
    return false;
#endif
}

ScreenSize GetScreenSize()
{
    std::lock_guard<std::mutex> lock(g_frameMutex);
    return { g_lastFrame.width, g_lastFrame.height };
}

void RegisterFrameData(const void* data, int32_t width, int32_t height)
{
    std::lock_guard<std::mutex> lock(g_frameMutex);
    size_t size = static_cast<size_t>(width) * height * 4;
    g_lastFrame.data.assign(static_cast<const uint8_t*>(data), static_cast<const uint8_t*>(data) + size);
    g_lastFrame.width = width;
    g_lastFrame.height = height;
#ifdef PREVIEW
    s_hasFrame = true;
#endif
}

CapturedFrame CaptureFrame()
{
#ifdef PREVIEW
    std::lock_guard<std::mutex> lock(g_frameMutex);
    return g_lastFrame;
#else
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    if (pipeline) {
        auto root = pipeline->GetRootElement();
        if (root) {
            OHOS::Ace::NG::SnapshotOptions options;
            options.scale = 1.0f;
            options.waitUntilRenderFinished = true;
            auto [code, pixelMap] = OHOS::Ace::NG::ComponentSnapshot::GetSync(root, options);
            if (code == 0 && pixelMap) {
                auto acePM = OHOS::Ace::PixelMap::Create(pixelMap);
                if (acePM) {
                    std::lock_guard<std::mutex> lock(g_frameMutex);
                    const uint8_t* src = acePM->GetPixels();
                    int32_t count = acePM->GetByteCount();
                    g_lastFrame.data.assign(src, src + count);
                    g_lastFrame.width = acePM->GetWidth();
                    g_lastFrame.height = acePM->GetHeight();
                    return g_lastFrame;
                }
            }
        }
    }
    {
        std::lock_guard<std::mutex> lock(g_frameMutex);
        return g_lastFrame;
    }
#endif
}

#ifdef VISUAL_TEST_FILE_IO_POSIX
#define FOPEN_READ(path) fdopen(open(path, O_RDONLY), "rb")
#define FOPEN_WRITE(path) fdopen(open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644), "wb")
#else
#define FOPEN_READ(path) fopen(path, "rb")
#define FOPEN_WRITE(path) fopen(path, "wb")
#endif

std::vector<uint8_t> ReadPNG(const std::string& path, int32_t* outW, int32_t* outH)
{
    FILE* fp = FOPEN_READ(path.c_str());
    if (!fp) {
        *outW = *outH = 0;
        return {};
    }
    png_byte sig[8];
    if (fread(sig, 1, 8, fp) != 8 || png_sig_cmp(sig, 0, 8)) {
        fclose(fp);
        return {};
    }
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return {};
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(fp);
        return {};
    }
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return {};
    }
    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);
    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte colorType = png_get_color_type(png, info);
    png_byte bitDepth = png_get_bit_depth(png, info);
    if (bitDepth == 16) {
        png_set_strip_16(png);
    }
    if (colorType == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
    }
    if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
        png_set_expand_gray_1_2_4_to_8(png);
    }
    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }
    if (colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY) {
        png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
    }
    if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png);
    }
    png_read_update_info(png, info);
    size_t rowBytes = png_get_rowbytes(png, info);
    std::vector<uint8_t> imageData(rowBytes * height);
    std::vector<png_bytep> rows(height);
    for (int y = 0; y < height; y++) {
        rows[y] = imageData.data() + y * rowBytes;
    }
    png_read_image(png, rows.data());
    png_destroy_read_struct(&png, &info, nullptr);
    fclose(fp);
    *outW = width;
    *outH = height;
    return imageData;
}

static bool MkdirRecursive(const std::string& dir)
{
    if (dir.empty() || dir == "/") return true;
    // Try to create the full path first (fast path if parent exists)
    if (mkdir(dir.c_str(), 0777) == 0) return true;
    if (errno == EEXIST) return true;
    if (errno != ENOENT) return false;
    // Parent doesn't exist — create it recursively
    auto slash = dir.rfind('/');
    if (slash == std::string::npos || slash == 0) return false;
    if (!MkdirRecursive(dir.substr(0, slash))) return false;
    return mkdir(dir.c_str(), 0777) == 0 || errno == EEXIST;
}

static void EnsureParentDir(const std::string& filePath)
{
    auto pos = filePath.rfind('/');
    if (pos == std::string::npos) return;
    std::string dir = filePath.substr(0, pos);
    if (dir.empty() || dir == "/") return;
    MkdirRecursive(dir);
}

bool WritePNG(const uint8_t* rgba, int32_t w, int32_t h, const std::string& path)
{
    EnsureParentDir(path);
    FILE* fp = FOPEN_WRITE(path.c_str());
    if (!fp) {
        fprintf(stderr, "[VisualTest] WritePNG fopen failed: %s (errno=%d)\n", path.c_str(), errno);
        return false;
    }
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) { fclose(fp); return false; }
    png_infop info = png_create_info_struct(png);
    if (!info) { png_destroy_write_struct(&png, nullptr); fclose(fp); return false; }
    if (setjmp(png_jmpbuf(png))) { png_destroy_write_struct(&png, &info); fclose(fp); return false; }
    png_init_io(png, fp);
    png_set_IHDR(png, info, w, h, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    std::vector<uint8_t> rgbRow(w * 3);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int src = (y * w + x) * 4;
            int dst = x * 3;
            rgbRow[dst] = rgba[src];
            rgbRow[dst + 1] = rgba[src + 1];
            rgbRow[dst + 2] = rgba[src + 2];
        }
        png_write_row(png, rgbRow.data());
    }
    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    return true;
}

bool WriteDiffPNG(const uint8_t* actual, const uint8_t* golden,
                  int32_t w, int32_t h, const std::string& path)
{
    EnsureParentDir(path);
    FILE* fp = FOPEN_WRITE(path.c_str());
    if (!fp) { fprintf(stderr, "[VisualTest] WriteDiffPNG fopen failed: %s\n", path.c_str()); return false; }
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) { fclose(fp); return false; }
    png_infop info = png_create_info_struct(png);
    if (!info) { png_destroy_write_struct(&png, nullptr); fclose(fp); return false; }
    if (setjmp(png_jmpbuf(png))) { png_destroy_write_struct(&png, &info); fclose(fp); return false; }
    png_init_io(png, fp);
    png_set_IHDR(png, info, w, h, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    std::vector<uint8_t> rgbRow(w * 3);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = (y * w + x) * 4;
            PixelColor pa(actual[idx], actual[idx + 1], actual[idx + 2]);
            PixelColor pg(golden[idx], golden[idx + 1], golden[idx + 2]);
            double dist = pa.LabDistance(pg);
            int dst = x * 3;
            if (dist > 0.5) {
                rgbRow[dst] = 255;
                rgbRow[dst + 1] = 0;
                rgbRow[dst + 2] = 0;
            } else {
                rgbRow[dst] = 0;
                rgbRow[dst + 1] = 0;
                rgbRow[dst + 2] = 0;
            }
        }
        png_write_row(png, rgbRow.data());
    }
    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    return true;
}

bool WriteFile(const std::string& path, const uint8_t* data, size_t size)
{
    EnsureParentDir(path);
#ifdef VISUAL_TEST_FILE_IO_POSIX
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "[VisualTest] WriteFile open failed: %s (errno=%d)\n", path.c_str(), errno);
        return false;
    }
    ssize_t written = write(fd, data, size);
    fsync(fd);
    close(fd);
    return written == static_cast<ssize_t>(size);
#else
    FILE* fp = fopen(path.c_str(), "wb");
    if (!fp) {
        fprintf(stderr, "[VisualTest] WriteFile fopen failed: %s (errno=%d)\n", path.c_str(), errno);
        return false;
    }
    size_t written = fwrite(data, 1, size, fp);
    fclose(fp);
    return written == size;
#endif
}

CompareResult CompareImages(const uint8_t* actual, int32_t aw, int32_t ah,
                            const uint8_t* golden, int32_t gw, int32_t gh,
                            double threshold)
{
    CompareResult result;
    if (aw != gw || ah != gh) {
        printf("[VisualTest] FAIL: size mismatch: actual %dx%d vs golden %dx%d\n",
               aw, ah, gw, gh);
        result.score = 0.0;
        return result;
    }
    int32_t w = aw, h = ah;
    if (w < 8 || h < 8) {
        printf("[VisualTest] FAIL: image too small %dx%d\n", w, h);
        return result;
    }
    auto getLum = [](const uint8_t* data, int x, int y, int w) -> double {
        int idx = (y * w + x) * 4;
        return 0.299 * data[idx] + 0.587 * data[idx + 1] + 0.114 * data[idx + 2];
    };
    const double c1 = (0.01 * 255) * (0.01 * 255);
    const double c2 = (0.03 * 255) * (0.03 * 255);
    const int windowSize = 8;
    double totalSSIM = 0.0;
    int windowCount = 0;
    for (int wy = 0; wy + windowSize <= h; wy += windowSize) {
        for (int wx = 0; wx + windowSize <= w; wx += windowSize) {
            double sumA = 0, sumG = 0;
            for (int dy = 0; dy < windowSize; dy++) {
                for (int dx = 0; dx < windowSize; dx++) {
                    sumA += getLum(actual, wx + dx, wy + dy, w);
                    sumG += getLum(golden, wx + dx, wy + dy, w);
                }
            }
            int n = windowSize * windowSize;
            double meanA = sumA / n;
            double meanG = sumG / n;
            double varA = 0, varG = 0, cov = 0;
            for (int dy = 0; dy < windowSize; dy++) {
                for (int dx = 0; dx < windowSize; dx++) {
                    double a = getLum(actual, wx + dx, wy + dy, w) - meanA;
                    double g = getLum(golden, wx + dx, wy + dy, w) - meanG;
                    varA += a * a;
                    varG += g * g;
                    cov += a * g;
                }
            }
            varA /= (n - 1);
            varG /= (n - 1);
            cov /= (n - 1);
            double ssim = ((2 * meanA * meanG + c1) * (2 * cov + c2)) /
                          ((meanA * meanA + meanG * meanG + c1) * (varA + varG + c2));
            totalSSIM += ssim;
            windowCount++;
        }
    }
    result.score = windowCount > 0 ? totalSSIM / windowCount : 0.0;
    result.pass = result.score >= threshold;
    return result;
}

void RequestRenderStable()
{
    g_renderStableFlag = false;
    g_renderStableRequested = true;
    g_stableFrameCount = 0;
}

bool IsRenderStable()
{
#ifndef PREVIEW
    CheckRenderStable();
#endif
    return g_renderStableFlag.load();
}

#ifdef PREVIEW
void CheckRenderStable()
{
    if (!g_renderStableRequested.load()) {
        return;
    }
    if (!s_hasFrame.load()) {
        return;
    }
    g_stableFrameCount++;
    if (g_stableFrameCount >= STABLE_FRAME_THRESHOLD) {
        g_renderStableFlag = true;
        g_renderStableRequested = false;
    }
}
#else
void CheckRenderStable()
{
    if (!g_renderStableRequested.load()) {
        return;
    }
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    if (!pipeline) return;
    bool isStable = pipeline->IsDirtyNodesEmpty() &&
                    pipeline->IsDirtyLayoutNodesEmpty() &&
                    pipeline->IsDirtyPropertyNodesEmpty();
    auto window = pipeline->GetWindow();
    if (window && window->HasUIRunningAnimation()) {
        isStable = false;
    }
    if (isStable) {
        g_stableFrameCount++;
        if (g_stableFrameCount >= STABLE_FRAME_THRESHOLD) {
            g_renderStableFlag = true;
            g_renderStableRequested = false;
        }
    } else {
        g_stableFrameCount = 0;
    }
}
#endif

void SetHeadlessDone()
{
#ifdef PREVIEW
    g_headlessDone = true;
#endif
}

bool IsHeadlessDone()
{
#ifdef PREVIEW
    return g_headlessDone.load();
#else
    return false;
#endif
}

} // namespace VisualTest

#ifdef PREVIEW
extern "C" __attribute__((visibility("default"))) void VisualTest_OnFrameData(const void* data, int32_t width, int32_t height)
{
    VisualTest::RegisterFrameData(data, width, height);
    VisualTest::CheckRenderStable();
}

extern "C" __attribute__((visibility("default"))) void VisualTest_SetHapDir(const char* dir)
{
    VisualTest::SetHapDir(dir ? std::string(dir) : std::string());
}

extern "C" __attribute__((visibility("default"))) void VisualTest_SetOutputDir(const char* dir)
{
    VisualTest::SetOutputDir(dir ? std::string(dir) : std::string());
}

extern "C" __attribute__((visibility("default"))) bool VisualTest_IsHeadlessDone()
{
    return VisualTest::IsHeadlessDone();
}
#endif
