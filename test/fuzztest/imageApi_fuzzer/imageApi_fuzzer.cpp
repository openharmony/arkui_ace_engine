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

#include "imageApi_fuzzer.h"

#include "core/image/image_cache.h"
#include "core/image/image_compressor.h"
#include "core/image/image_loader.h"
#include "core/image/image_object.h"
#include "core/image/image_provider.h"

namespace OHOS::Ace {
const uint32_t u16m = 65535;
void MinorTest(const uint8_t* data, size_t size)
{
    OHOS::Ace::ImageSourceInfo i;
#ifndef USE_ROSEN_DRAWING
    const sk_sp<SkImage> rawImage;
#else
    const std::shared_ptr<RSImage> rawImage;
#endif
    auto ri = size % u16m;
    std::string s(reinterpret_cast<const char*>(data), ri);
    i = ImageSourceInfo(s);
    ImageSourceInfo::IsSVGSource(s, InternalResource::ResourceId::SVG_START);
    ImageSourceInfo::IsPngSource(s, InternalResource::ResourceId::SVG_START);
    ImageSourceInfo::ResolveURIType(s);
    ImageSourceInfo::IsValidBase64Head(s, "example");
    ImageSourceInfo::IsUriOfDataAbilityEncoded(s, "example");
    auto k = ImageCompressor::GetInstance();
    Size s2;
    ImageProvider::ResizeSkImage(rawImage, s, s2) ;
#ifndef USE_ROSEN_DRAWING
    SkPixmap  pixmap;
    sk_sp<SkData> compressdImage;
#else
    RSBitmap rsBitmap;
    std::shared_ptr<RSData> compressdImage;
#endif
#ifdef FUZZTEST
    k->PartDoing();
#endif
    k->GpuCompress(s, pixmap, 0, 0);
}
} // namespace OHOS::Ace

using namespace OHOS;
using namespace OHOS::Ace;
/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    MinorTest(data, size);
    return 0;
}
