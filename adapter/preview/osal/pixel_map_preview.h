/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_PIXEL_MAP_PREVIEW_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_PIXEL_MAP_PREVIEW_H

#include "base/image/pixel_map.h"

namespace OHOS::Ace {
class PixelMapPreview : public PixelMap {
    DECLARE_ACE_TYPE(PixelMapPreview, PixelMap)

public:
    explicit PixelMapPreview(std::shared_ptr<Media::PixelMap> pixmap) : pixmap_(std::move(pixmap)) {}
    static RefPtr<PixelMap> CreatePixelMap(void* sptrAddr);
    static RefPtr<PixelMap> CreatePixelMapFromDataAbility(void* uniquePtr);
    static RefPtr<PixelMap> ConvertSkImageToPixmap(
        const uint32_t* colors, uint32_t colorLength, int32_t width, int32_t height);
    int32_t GetWidth() const override;
    int32_t GetHeight() const override;
    bool GetPixelsVec(std::vector<uint8_t>& data) const override;
    const uint8_t* GetPixels() const override;
    PixelFormat GetPixelFormat() const override;
    AlphaType GetAlphaType() const override;
    int32_t GetRowStride() const override;
    int32_t GetRowBytes() const override;
    int32_t GetByteCount() const override;
    void* GetPixelManager() const override;
    void* GetRawPixelMapPtr() const override;
    std::string GetId() override;
    std::string GetModifyId() override;
    void Scale(float xAxis, float yAxis) override;
    void Scale(float xAxis, float yAxis, const AceAntiAliasingOption &option) override;
    std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() override
    {
        return pixmap_;
    }
    bool EncodeTlv(std::vector<uint8_t>& buff) override;

private:
    std::shared_ptr<Media::PixelMap> pixmap_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_PIXEL_MAP_PREVIEW_H
