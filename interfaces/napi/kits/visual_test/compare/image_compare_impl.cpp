#include "image_compare_impl.h"

#include <png.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <algorithm>

namespace imagecompare {

// ---- Constants ----

constexpr int COLOR_CHANNEL_RGBA = 4;
constexpr int CH_G = 1;
constexpr int CH_B = 2;
constexpr int MAX_PIXEL_VALUE = 255;
constexpr int SSIM_WINDOW = 8;
constexpr int SSIM_MIN_DIM = 8;
constexpr double SSIM_C1_K = 0.01;
constexpr double SSIM_C2_K = 0.03;
constexpr double SSIM_MUL = 2.0;

constexpr double LAB_SCALE_A = 500.0;
constexpr double LAB_SCALE_B = 200.0;
constexpr double LAB_L_START = 116.0;
constexpr double LAB_L_OFFSET = 16.0;
constexpr double LAB_Z_DIV = 1.08883;
constexpr double LAB_XYN = 0.95047;
constexpr double LAB_RX = 0.4124;
constexpr double LAB_GX = 0.3576;
constexpr double LAB_BX = 0.1805;
constexpr double LAB_RY = 0.2126;
constexpr double LAB_GY = 0.7152;
constexpr double LAB_BY = 0.0722;
constexpr double LAB_RZ = 0.0193;
constexpr double LAB_GZ = 0.1192;
constexpr double LAB_BZ = 0.9505;

constexpr double LUM_R = 0.299;
constexpr double LUM_G = 0.587;
constexpr double LUM_B = 0.114;

void SafeFclose(FILE*& fp)
{
    if (fp) {
        int rc = fclose(fp);
        (void)rc;
        fp = nullptr;
    }
}

// ---------------------------------------------------------------------------
// PixelColor — sRGB ↔ CIELAB helpers
// ---------------------------------------------------------------------------

namespace {

double SrgbToLinear(double c)
{
    return c <= 0.04045 ? c / 12.92 : std::pow((c + 0.055) / 1.055, 2.4);
}

double LabF(double t)
{
    return t > 0.008856 ? std::cbrt(t) : 7.787 * t + 16.0 / 116.0;
}

}  // namespace

double ImageCompareImpl::PixelColor::Luminance() const
{
    return LUM_R * r + LUM_G * g + LUM_B * b;
}

void ImageCompareImpl::PixelColor::ToLAB(double& l, double& a, double& bVal) const
{
    double rl = SrgbToLinear(r / static_cast<double>(MAX_PIXEL_VALUE));
    double gl = SrgbToLinear(g / static_cast<double>(MAX_PIXEL_VALUE));
    double bl = SrgbToLinear(b / static_cast<double>(MAX_PIXEL_VALUE));
    double x = rl * LAB_RX + gl * LAB_GX + bl * LAB_BX;
    double y = rl * LAB_RY + gl * LAB_GY + bl * LAB_BY;
    double z = rl * LAB_RZ + gl * LAB_GZ + bl * LAB_BZ;
    x /= LAB_XYN;
    y /= 1.0;
    z /= LAB_Z_DIV;
    double fx = LabF(x);
    double fy = LabF(y);
    double fz = LabF(z);
    l = LAB_L_START * fy - LAB_L_OFFSET;
    a = LAB_SCALE_A * (fx - fy);
    bVal = LAB_SCALE_B * (fy - fz);
}

double ImageCompareImpl::PixelColor::LabDistance(const PixelColor& o) const
{
    double l1 = 0;
    double a1 = 0;
    double b1 = 0;
    double l2 = 0;
    double a2 = 0;
    double b2 = 0;
    ToLAB(l1, a1, b1);
    o.ToLAB(l2, a2, b2);
    return std::sqrt((l1 - l2) * (l1 - l2) + (a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2));
}

// ---------------------------------------------------------------------------
// Singleton
// ---------------------------------------------------------------------------

ImageCompareImpl& ImageCompareImpl::Instance()
{
    static ImageCompareImpl instance;
    return instance;
}

ImageCompare& ImageCompare::Get()
{
    return ImageCompareImpl::Instance();
}

// ---------------------------------------------------------------------------
// SSIM comparison — 8×8 sliding window, luminance channel
// ---------------------------------------------------------------------------

DiffResult ImageCompareImpl::Compare(const Image& actual, const Image& golden, double threshold)
{
    DiffResult result;
    if (actual.width != golden.width || actual.height != golden.height) {
        printf("[ImageCompare] size mismatch: actual %dx%d vs golden %dx%d\n",
               actual.width, actual.height, golden.width, golden.height);
        result.pass = false;
        result.score = 0.0;
        result.error = "SIZE_MISMATCH";
        return result;
    }
    int32_t w = actual.width;
    int32_t h = actual.height;
    if (w < SSIM_MIN_DIM || h < SSIM_MIN_DIM) {
        printf("[ImageCompare] image too small: %dx%d\n", w, h);
        result.pass = false;
        result.score = 0.0;
        return result;
    }
    size_t expectedSize = static_cast<size_t>(w) * static_cast<size_t>(h) * COLOR_CHANNEL_RGBA;
    if (actual.data.size() < expectedSize || golden.data.size() < expectedSize) {
        printf("[ImageCompare] data too small: actual %zu, golden %zu, expected %zu\n",
               actual.data.size(), golden.data.size(), expectedSize);
        result.pass = false;
        result.score = 0.0;
        result.error = "DATA_TOO_SMALL";
        return result;
    }
    auto getLum = [](const uint8_t* data, int x, int y, int stride) -> double {
        size_t idx = (static_cast<size_t>(y) * static_cast<size_t>(stride) +
                      static_cast<size_t>(x)) * COLOR_CHANNEL_RGBA;
        return LUM_R * data[idx] + LUM_G * data[idx + CH_G] + LUM_B * data[idx + CH_B];
    };
    const double c1 = (SSIM_C1_K * MAX_PIXEL_VALUE) * (SSIM_C1_K * MAX_PIXEL_VALUE);
    const double c2 = (SSIM_C2_K * MAX_PIXEL_VALUE) * (SSIM_C2_K * MAX_PIXEL_VALUE);
    double totalSSIM = 0.0;
    int windowCount = 0;
    const uint8_t* a = actual.data.data();
    const uint8_t* g = golden.data.data();
    for (int wy = 0; wy + SSIM_WINDOW <= h; wy += SSIM_WINDOW) {
        for (int wx = 0; wx + SSIM_WINDOW <= w; wx += SSIM_WINDOW) {
            double sumA = 0;
            double sumG = 0;
            for (int dy = 0; dy < SSIM_WINDOW; dy++) {
                for (int dx = 0; dx < SSIM_WINDOW; dx++) {
                    sumA += getLum(a, wx + dx, wy + dy, w);
                    sumG += getLum(g, wx + dx, wy + dy, w);
                }
            }
            int windowPixels = SSIM_WINDOW * SSIM_WINDOW;
            double meanA = sumA / windowPixels;
            double meanG = sumG / windowPixels;
            double varA = 0;
            double varG = 0;
            double cov = 0;
            for (int dy = 0; dy < SSIM_WINDOW; dy++) {
                for (int dx = 0; dx < SSIM_WINDOW; dx++) {
                    double da = getLum(a, wx + dx, wy + dy, w) - meanA;
                    double dg = getLum(g, wx + dx, wy + dy, w) - meanG;
                    varA += da * da;
                    varG += dg * dg;
                    cov += da * dg;
                }
            }
            varA /= (windowPixels - 1);
            varG /= (windowPixels - 1);
            cov /= (windowPixels - 1);
            double ssim = ((SSIM_MUL * meanA * meanG + c1) * (SSIM_MUL * cov + c2)) /
                          ((meanA * meanA + meanG * meanG + c1) * (varA + varG + c2));
            totalSSIM += ssim;
            windowCount++;
        }
    }
    result.score = windowCount > 0 ? totalSSIM / windowCount : 0.0;
    result.pass = result.score >= threshold;
    return result;
}

// ---------------------------------------------------------------------------
// PNG decode from memory buffer
// ---------------------------------------------------------------------------

namespace {

struct ReadContext {
    const uint8_t* data;
    size_t size;
    size_t offset;
};

void ReadFromMemory(png_structp png, png_bytep out, png_size_t len)
{
    ReadContext* ctx = static_cast<ReadContext*>(png_get_io_ptr(png));
    if (ctx->offset + len > ctx->size) {
        png_error(png, "ReadFromMemory: out of bounds");
        return;
    }
    std::memcpy(out, ctx->data + ctx->offset, len);
    ctx->offset += len;
}

struct WriteContext {
    std::vector<uint8_t> buffer;
};

void WriteToMemory(png_structp png, png_bytep data, png_size_t len)
{
    WriteContext* ctx = static_cast<WriteContext*>(png_get_io_ptr(png));
    size_t prev = ctx->buffer.size();
    ctx->buffer.resize(prev + len);
    std::memcpy(ctx->buffer.data() + prev, data, len);
}

void FlushMemory(png_structp /*png*/)
{
    // no-op: everything is already in the buffer
}

}  // namespace

Image ImageCompareImpl::DecodePNGFile(const std::string& path)
{
    FILE* fp = fopen(path.c_str(), "rb");
    if (!fp) {
        printf("[ImageCompare] DecodePNGFile: not found: %s\n", path.c_str());
        return Image{};
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        printf("[ImageCompare] DecodePNGFile: fseek failed: %s\n", path.c_str());
        fclose(fp);
        return Image{};
    }
    long tellResult = ftell(fp);
    if (tellResult < 0) {
        printf("[ImageCompare] DecodePNGFile: ftell failed: %s\n", path.c_str());
        fclose(fp);
        return Image{};
    }
    size_t size = static_cast<size_t>(tellResult);
    if (fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        return Image{};
    }
    std::vector<uint8_t> buf(size);
    size_t readBytes = fread(buf.data(), 1, size, fp);
    fclose(fp);
    if (readBytes != size) {
        printf("[ImageCompare] DecodePNGFile: short read %zu/%zu: %s\n",
               readBytes, size, path.c_str());
        return Image{};
    }
    return DecodePNG(buf.data(), size);
}

Image ImageCompareImpl::DecodePNG(const uint8_t* data, size_t size)
{
    Image result;
    if (!data || size == 0) {
        printf("[ImageCompare] DecodePNG: empty input\n");
        return result;
    }
    if (png_sig_cmp(data, 0, std::min<size_t>(8, size))) {
        printf("[ImageCompare] DecodePNG: not a valid PNG\n");
        return result;
    }
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        printf("[ImageCompare] DecodePNG: failed to create read struct\n");
        return result;
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        return result;
    }
    if (setjmp(png_jmpbuf(png))) {
        printf("[ImageCompare] DecodePNG: libpng error\n");
        png_destroy_read_struct(&png, &info, nullptr);
        return result;
    }
    ReadContext ctx = { data, size, 0 };
    png_set_read_fn(png, &ctx, ReadFromMemory);
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
    result.data.resize(rowBytes * height);
    std::vector<png_bytep> rows(height);
    for (int y = 0; y < height; y++) {
        rows[y] = result.data.data() + y * rowBytes;
    }
    png_read_image(png, rows.data());
    png_destroy_read_struct(&png, &info, nullptr);
    result.width = width;
    result.height = height;
    printf("[ImageCompare] DecodePNG: %dx%d, %zu bytes from %zu-byte buffer\n",
           width, height, result.data.size(), size);
    return result;
}

// ---------------------------------------------------------------------------
// PNG encode to memory buffer
// ---------------------------------------------------------------------------

std::vector<uint8_t> ImageCompareImpl::EncodePNG(const Image& img)
{
    std::vector<uint8_t> result;
    if (img.data.empty() || img.width <= 0 || img.height <= 0) {
        printf("[ImageCompare] EncodePNG: invalid input\n");
        return result;
    }
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        return result;
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        return result;
    }
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        return result;
    }
    WriteContext ctx;
    png_set_write_fn(png, &ctx, WriteToMemory, FlushMemory);
    png_set_IHDR(png, info, img.width, img.height, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    std::vector<uint8_t> rgbRow(img.width * 3);
    for (int32_t y = 0; y < img.height; y++) {
        for (int32_t x = 0; x < img.width; x++) {
            size_t src = (static_cast<size_t>(y) * static_cast<size_t>(img.width) +
                          static_cast<size_t>(x)) * 4;
            size_t dst = static_cast<size_t>(x) * 3;
            rgbRow[dst]     = img.data[src];
            rgbRow[dst + CH_G] = img.data[src + CH_G];
            rgbRow[dst + CH_B] = img.data[src + CH_B];
        }
        png_write_row(png, rgbRow.data());
    }
    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    result = std::move(ctx.buffer);
    printf("[ImageCompare] EncodePNG: %dx%d -> %zu bytes PNG\n",
           img.width, img.height, result.size());
    return result;
}

// ---------------------------------------------------------------------------
// File I/O
// ---------------------------------------------------------------------------

namespace {

void MakeParentDir(const std::string& path)
{
    size_t pos = path.rfind('/');
    if (pos == std::string::npos) return;
    std::string dir = path.substr(0, pos);
    if (dir.empty()) return;
    for (size_t i = 1; i <= dir.size(); i++) {
        if (dir[i] == '/' || i == dir.size()) {
            std::string segment = dir.substr(0, i);
            mkdir(segment.c_str(), 0755);
        }
    }
}

}  // namespace

void ImageCompareImpl::WritePNG(const Image& img, const std::string& path)
{
    if (img.data.empty() || img.width <= 0 || img.height <= 0) {
        printf("[ImageCompare] WritePNG: invalid input\n");
        return;
    }
    MakeParentDir(path);
    FILE* fp = fopen(path.c_str(), "wb");
    if (!fp) {
        printf("[ImageCompare] WritePNG: cannot open %s\n", path.c_str());
        return;
    }
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return;
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        return;
    }
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return;
    }
    png_init_io(png, fp);
    png_set_IHDR(png, info, img.width, img.height, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    std::vector<uint8_t> rgbRow(img.width * 3);
    for (int32_t y = 0; y < img.height; y++) {
        for (int32_t x = 0; x < img.width; x++) {
            size_t src = (static_cast<size_t>(y) * static_cast<size_t>(img.width) +
                          static_cast<size_t>(x)) * 4;
            size_t dst = static_cast<size_t>(x) * 3;
            rgbRow[dst]     = img.data[src];
            rgbRow[dst + CH_G] = img.data[src + CH_G];
            rgbRow[dst + CH_B] = img.data[src + CH_B];
        }
        png_write_row(png, rgbRow.data());
    }
    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    printf("[ImageCompare] WritePNG: %dx%d -> %s\n", img.width, img.height, path.c_str());
}

void ImageCompareImpl::WriteDiff(const Image& actual, const Image& golden, const std::string& path)
{
    if (actual.width != golden.width || actual.height != golden.height) {
        printf("[ImageCompare] WriteDiff: size mismatch %dx%d vs %dx%d\n",
               actual.width, actual.height, golden.width, golden.height);
        return;
    }
    MakeParentDir(path);
    int32_t w = actual.width;
    int32_t h = actual.height;
    FILE* fp = fopen(path.c_str(), "wb");
    if (!fp) {
        printf("[ImageCompare] WriteDiff: cannot open %s\n", path.c_str());
        return;
    }
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return;
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        return;
    }
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return;
    }
    png_init_io(png, fp);
    png_set_IHDR(png, info, w, h, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    std::vector<uint8_t> rgbRow(w * 3);
    for (int32_t y = 0; y < h; y++) {
        for (int32_t x = 0; x < w; x++) {
            size_t idx = (static_cast<size_t>(y) * static_cast<size_t>(w) +
                          static_cast<size_t>(x)) * 4;
            PixelColor pa(actual.data[idx], actual.data[idx + CH_G], actual.data[idx + CH_B]);
            PixelColor pg(golden.data[idx], golden.data[idx + CH_G], golden.data[idx + CH_B]);
            double dist = pa.LabDistance(pg);
            int dst = x * 3;
            if (dist > 0.5) {
                rgbRow[dst]     = 255;
                rgbRow[dst + CH_G] = 0;
                rgbRow[dst + CH_B] = 0;
            } else {
                rgbRow[dst]     = 0;
                rgbRow[dst + CH_G] = 0;
                rgbRow[dst + CH_B] = 0;
            }
        }
        png_write_row(png, rgbRow.data());
    }
    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    printf("[ImageCompare] WriteDiff: %dx%d -> %s\n", w, h, path.c_str());
}

void ImageCompareImpl::WriteManifest(const std::string& json, const std::string& path)
{
    MakeParentDir(path);
    FILE* f = fopen(path.c_str(), "w");
    if (!f) {
        printf("[ImageCompare] WriteManifest: cannot open %s\n", path.c_str());
        return;
    }
    fwrite(json.data(), 1, json.size(), f);
    fclose(f);
    printf("[ImageCompare] WriteManifest: %zu bytes -> %s\n", json.size(), path.c_str());
}

}  // namespace imagecompare
