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

#ifndef YUV_INFO_H
#define YUV_INFO_H

namespace OHOS {
namespace Rosen {
namespace Drawing {

class YUVInfo {
public:
    enum class PlaneConfig {
        UNKNOWN = 0,
        Y_UV,      // Plane 0: Y, Plane 1: UV
        Y_VU,      // Plane 0: Y, Plane 1: VU
    };

    enum class SubSampling {
        UNKNOWN = 0,
        K420,      // 1 set of UV values for each 2x2 block of Y values.
    };

    enum YUVColorSpace : int32_t {
        JPEG_FULL_YUVCOLORSPACE = 0,      // describes full range
        BT2020_10BIT_LIMITED_YUVCOLORSPACE,
        IDENTITY_YUVCOLORSPACE,       // maps Y->R, U->G, V->B
        LASTENUM_YUVCOLORSPACE = IDENTITY_YUVCOLORSPACE      // last valid value
    };

    enum class YUVDataType {
        UNORM_8 = 0,
        UNORM_16,
    };

    YUVInfo() = default;
    YUVInfo(int width, int height, PlaneConfig config, SubSampling sampling, YUVColorSpace colorSpace, YUVDataType type)
        : width_(width), height_(height), planeConfig_(config), subSampling_(sampling),
          yuvColorSpace_(colorSpace), type_(type) {}
    ~YUVInfo() = default;

    int GetWidth() const
    {
        return width_;
    }

    int GetHeight() const
    {
        return height_;
    }

    PlaneConfig GetConfig() const
    {
        return planeConfig_;
    }

    SubSampling GetSampling() const
    {
        return subSampling_;
    }

    YUVColorSpace GetColorSpace() const
    {
        return yuvColorSpace_;
    }

    YUVDataType GetDataType() const
    {
        return type_;
    }

private:
    int width_ = 0;
    int height_ = 0;
    PlaneConfig planeConfig_ = PlaneConfig::UNKNOWN;
    SubSampling subSampling_ = SubSampling::UNKNOWN;
    YUVColorSpace yuvColorSpace_ = YUVColorSpace::IDENTITY_YUVCOLORSPACE;
    YUVDataType type_ = YUVDataType::UNORM_8;
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
