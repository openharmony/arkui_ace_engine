/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

#ifndef PIXMAP_H
#define PIXMAP_H

#include "image_info.h"
#include "utils/sampling_options.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Pixmap {
public:
    Pixmap();
    Pixmap(const ImageInfo& imageInfo, const void* addr, size_t rowBytes);
    virtual ~Pixmap() = default;
    ColorType GetColorType() const;
    AlphaType GetAlphaType() const;
    ColorQuad GetColor(int x, int y) const;
    size_t GetRowBytes() const;
    const void* GetAddr() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    bool ScalePixels(const Pixmap& dst, const SamplingOptions& options) const;
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
