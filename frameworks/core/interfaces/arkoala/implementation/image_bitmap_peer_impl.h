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
#pragma once

#include "base/utils/utils.h"
#include "base/memory/referenced.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/components_ng/image_provider/image_loading_context.h"

struct ImageBitmapPeer {
public:
    ImageBitmapPeer() = default;
    virtual ~ImageBitmapPeer() = default;
    
    void Close();
    Ark_Int32 GetHeight();
    Ark_Int32 GetWidth();

    void LoadImage(const std::string& src);
    void SetCloseCallback(std::function<void()>&& callback);

    const OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasImage>& GetCanvasImage() const
    {
        return image_;
    }
    const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& GetPixelMap() const
    {
        return pixelMap_;
    }

private:
    void LoadImage(const OHOS::Ace::ImageSourceInfo& sourceInfo);

    void OnImageDataReady();
    void OnImageLoadSuccess();
    void OnImageLoadFail(const std::string& errorMsg);

protected:
    std::string src_;
    double width_ = 0;
    double height_ = 0;
    OHOS::Ace::ImageSourceInfo sourceInfo_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ImageLoadingContext> loadingCtx_;
    std::list<std::function<void()>> closeCallbacks_;

    OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasImage> image_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ImageObject> imageObj_;
    OHOS::Ace::RefPtr<OHOS::Ace::PixelMap> pixelMap_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SvgDomBase> svgDom_;
    OHOS::Ace::ImageFit imageFit_ = OHOS::Ace::ImageFit::NONE;
    OHOS::Ace::NG::SizeF imageSize_;
    size_t bindingSize_ = 0;
};