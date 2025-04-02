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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_BITMAP_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_BITMAP_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/image_provider/image_loading_context.h"

struct ImageBitmapPeer : public OHOS::Ace::Referenced {
public:
    ImageBitmapPeer();
    virtual ~ImageBitmapPeer() = default;

    void SetOptions(const std::string& textString, const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& pixelMap = nullptr);
    void OnClose();
    double OnGetHeight();
    double OnGetWidth();

    double GetWidth();
    void SetWidth(double width);
    double GetHeight();
    void SetHeight(double height);
    std::string GetSrc();
    void SetCloseCallback(std::function<void()>&& callback);

    virtual OHOS::Ace::RefPtr<OHOS::Ace::PixelMap> GetPixelMap() const
    {
        return pixelMap_;
    }
    std::shared_ptr<OHOS::Ace::ImageData> GetImageData() const
    {
        return imageData_;
    }
    void SetImageData(const std::shared_ptr<OHOS::Ace::ImageData>& imageData)
    {
        imageData_ = imageData;
    }
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SvgDomBase> GetSvgDom()
    {
        return svgDom_;
    }
    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }
    int32_t GetInstanceId()
    {
        return instanceId_;
    }
    bool IsSvg()
    {
        return sourceInfo_.IsSvg();
    }
    OHOS::Ace::ImageFit GetImageFit()
    {
        return imageFit_;
    }
    OHOS::Ace::NG::SizeF GetImageSize()
    {
        return imageSize_;
    }
    void SetUnit(OHOS::Ace::CanvasUnit unit)
    {
        unit_ = unit;
    }
    OHOS::Ace::CanvasUnit GetUnit()
    {
        return unit_;
    }
    double GetDensity()
    {
        // double density = OHOS::Ace::PipelineBase::GetCurrentDensity();
        // return ((GetUnit() == OHOS::Ace::CanvasUnit::DEFAULT) && !OHOS::Ace::NearZero(density)) ? density : 1.0;
        return 0;
    }
    size_t GetBindingSize() const
    {
        return bindingSize_;
    }
    static void LoadImageConstructor(ImageBitmapPeer* bitmap, const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& pixmap)
    {
        CHECK_NULL_VOID(bitmap);
        bitmap->LoadImage(pixmap);
    }

private:
    void LoadImage(const std::string& src);
    void LoadImage(const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& pixmap);
    void LoadImage(const OHOS::Ace::ImageSourceInfo& sourceInfo);
    void OnImageDataReady();
    void OnImageLoadFail(const std::string& errorMsg);
    void OnImageLoadSuccess();
    static bool NotFormSupport(const std::string& textString);

    OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasImage> image_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ImageObject> imageObj_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ImageLoadingContext> loadingCtx_;
    OHOS::Ace::RefPtr<OHOS::Ace::PixelMap> pixelMap_;
    std::shared_ptr<OHOS::Ace::ImageData> imageData_;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SvgDomBase> svgDom_;
    OHOS::Ace::ImageSourceInfo sourceInfo_;
    OHOS::Ace::ImageFit imageFit_ = OHOS::Ace::ImageFit::NONE;
    OHOS::Ace::NG::SizeF imageSize_;

    std::string src_;
    std::list<std::function<void()>> closeCallbacks_;
    double width = 0;
    double height = 0;
    int32_t instanceId_ = 0;
    OHOS::Ace::CanvasUnit unit_ = OHOS::Ace::CanvasUnit::DEFAULT;
    size_t bindingSize_ = 0;
};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_BITMAP_PEER_IMPL_H
