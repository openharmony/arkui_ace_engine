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

#ifndef SAMPLING_OPTIONS_H
#define SAMPLING_OPTIONS_H

#include <string>

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class FilterMode {
    NEAREST,
    LINEAR,
};

enum class MipmapMode {
    NONE,
    NEAREST,
    LINEAR,
};

struct CubicResampler {
    float cubicCoffB = 0;
    float cubicCoffC = 0;
    static constexpr CubicResampler Mitchell()
    {
        return { 1 / 3.0f, 1 / 3.0f };
    }
    static constexpr CubicResampler CatmullRom()
    {
        return { 0.0f, 1 / 2.0f };
    }
};

class SamplingOptions {
public:
    inline SamplingOptions() noexcept;
    inline explicit SamplingOptions(FilterMode fm) noexcept;
    inline SamplingOptions(FilterMode fm, MipmapMode mm) noexcept;
    inline explicit SamplingOptions(const CubicResampler& c) noexcept;
    inline SamplingOptions(const SamplingOptions& other) noexcept = default;

    inline ~SamplingOptions() {}

    inline bool GetUseCubic() const;
    inline FilterMode GetFilterMode() const;
    inline MipmapMode GetMipmapMode() const;
    inline float GetCubicCoffB() const;
    inline float GetCubicCoffC() const;

    friend inline bool operator==(const SamplingOptions& a, const SamplingOptions& b);
    friend inline bool operator!=(const SamplingOptions& a, const SamplingOptions& b);
private:
    bool useCubic = false;
    CubicResampler cubic = {0, 0};
    FilterMode filter = FilterMode::NEAREST;
    MipmapMode mipmap = MipmapMode::NONE;
};

inline SamplingOptions::SamplingOptions() noexcept
    : useCubic(false), filter(FilterMode::NEAREST), mipmap(MipmapMode::NONE)
{}

inline SamplingOptions::SamplingOptions(FilterMode fm) noexcept : useCubic(false), filter(fm), mipmap(MipmapMode::NONE)
{}

inline SamplingOptions::SamplingOptions(FilterMode fm, MipmapMode mm) noexcept : useCubic(false), filter(fm), mipmap(mm)
{}

inline SamplingOptions::SamplingOptions(const CubicResampler& c) noexcept : useCubic(true), cubic(c) {}

inline bool SamplingOptions::GetUseCubic() const
{
    return useCubic;
}

inline FilterMode SamplingOptions::GetFilterMode() const
{
    return filter;
}

inline MipmapMode SamplingOptions::GetMipmapMode() const
{
    return mipmap;
}

inline float SamplingOptions::GetCubicCoffB() const
{
    return cubic.cubicCoffB;
}

inline float SamplingOptions::GetCubicCoffC() const
{
    return cubic.cubicCoffC;
}

inline bool operator==(const SamplingOptions& a, const SamplingOptions& b)
{
    return a.useCubic == b.useCubic && a.cubic.cubicCoffB == b.cubic.cubicCoffB &&
        a.cubic.cubicCoffC == b.cubic.cubicCoffC && a.filter == b.filter && a.mipmap == b.mipmap;
}

inline bool operator!=(const SamplingOptions& a, const SamplingOptions& b)
{
    return !(a == b);
}
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
