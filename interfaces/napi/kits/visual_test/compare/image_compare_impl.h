#ifndef HEADLESS_IMAGE_COMPARE_IMAGE_COMPARE_IMPL_H
#define HEADLESS_IMAGE_COMPARE_IMAGE_COMPARE_IMPL_H

#include "imagecompare.h"

namespace imagecompare {

class ImageCompareImpl : public ImageCompare {
public:
    static ImageCompareImpl& Instance();

    DiffResult Compare(const Image& actual, const Image& golden,
                       double threshold = 0.95) override;

    Image DecodePNG(const uint8_t* data, size_t size) override;
    Image DecodePNGFile(const std::string& path) override;
    std::vector<uint8_t> EncodePNG(const Image& img) override;

    void WritePNG(const Image& img, const std::string& path) override;
    void WriteDiff(const Image& actual, const Image& golden,
                   const std::string& path) override;

    void WriteManifest(const std::string& json, const std::string& path) override;

private:
    ImageCompareImpl() = default;

    struct PixelColor {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;

        PixelColor() = default;
        PixelColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        double Luminance() const;
        void ToLAB(double& L, double& a, double& bVal) const;
        double LabDistance(const PixelColor& o) const;
    };
};

}  // namespace imagecompare

#endif  // HEADLESS_IMAGE_COMPARE_IMAGE_COMPARE_IMPL_H
