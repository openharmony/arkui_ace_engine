#ifndef HEADLESS_IMAGE_COMPARE_IMAGECOMPARE_H
#define HEADLESS_IMAGE_COMPARE_IMAGECOMPARE_H

#include <cstdint>
#include <string>
#include <vector>

namespace imagecompare {

struct Image {
    std::vector<uint8_t> data;
    int32_t width = 0;
    int32_t height = 0;
};

struct DiffResult {
    bool pass = false;
    double score = 0.0;
    const char* error = nullptr;
};

class ImageCompare {
public:
    virtual ~ImageCompare() = default;

    virtual DiffResult Compare(const Image& actual, const Image& golden,
                               double threshold = 0.95) = 0;

    virtual Image DecodePNG(const uint8_t* data, size_t size) = 0;
    virtual Image DecodePNGFile(const std::string& path) = 0;
    virtual std::vector<uint8_t> EncodePNG(const Image& img) = 0;

    virtual void WritePNG(const Image& img, const std::string& path) = 0;
    virtual void WriteDiff(const Image& actual, const Image& golden,
                           const std::string& path) = 0;

    virtual void WriteManifest(const std::string& json, const std::string& path) = 0;

    static ImageCompare& Get();
};

}  // namespace imagecompare

#endif  // HEADLESS_IMAGE_COMPARE_IMAGECOMPARE_H
