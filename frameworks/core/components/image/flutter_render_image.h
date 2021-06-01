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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_FLUTTER_RENDER_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_FLUTTER_RENDER_IMAGE_H

#include "experimental/svg/model/SkSVGDOM.h"
#include "flutter/fml/memory/ref_counted.h"
#include "flutter/lib/ui/painting/image.h"

#include "core/components/image/render_image.h"
#include "core/image/animated_image_player.h"
#include "core/image/image_provider.h"
#include "core/pipeline/base/scoped_canvas_state.h"
#include "core/pipeline/layers/offset_layer.h"

namespace OHOS::Ace {

class FlutterRenderImage final : public RenderImage, public LoadImageCallback {
    DECLARE_ACE_TYPE(FlutterRenderImage, RenderImage);

public:
    FlutterRenderImage();
    ~FlutterRenderImage() override = default;

    void Update(const RefPtr<Component>& component) override;
    void Paint(RenderContext& context, const Offset& offset) override;

    void OnLoadSuccess(
        const sk_sp<SkImage>& image, const RefPtr<ImageProvider>& imageProvider, const std::string& key) override;

    void OnLoadGPUImageSuccess(
        const fml::RefPtr<flutter::CanvasImage>& image, const RefPtr<ImageProvider>& imageProvider) override;

    void OnAnimateImageSuccess(const RefPtr<ImageProvider>& provider, const std::unique_ptr<SkCodec> codec) override;

    void OnLoadFail(const RefPtr<ImageProvider>& imageProvider) override;

    void OnLoadImageSize(
        Size imageSize,
        const std::string& imageSrc,
        const RefPtr<ImageProvider>& imageProvider,
        bool syncMode) override;

    void OnChangeProvider(const RefPtr<ImageProvider>& provider) override;

    void MarkNeedReload() override
    {
        needReload_ = true;
    }

    bool IsRepaintBoundary() const override
    {
        return imageProvider_ && (imageProvider_->GetTotalFrames() > 1);
    }

    RenderLayer GetRenderLayer() override
    {
        if (IsRepaintBoundary()) {
            if (!layer_) {
                layer_ = AceType::MakeRefPtr<Flutter::OffsetLayer>();
            }
        } else {
            layer_ = nullptr;
        }
        return AceType::RawPtr(layer_);
    }

    void OnHiddenChanged(bool hidden) override;

    void FetchImageData();

    void PaintBgImage(const flutter::Paint& paint, const flutter::PaintData& paint_data, const Offset& offset,
                      const ScopedCanvas& canvas) const;

    void UpdateImageProvider() override;

    void UpdateResourceId(InternalResource::ResourceId resourceId, bool onlySelfLayout) override
    {
        resourceId_ = resourceId;
        MarkNeedLayout(onlySelfLayout);
        UpdateImageProvider();
    }

    bool SupportOpacity() override
    {
        return true;
    }

protected:
    virtual bool MaybeRelease() override;
    virtual void ClearRenderObject() override;

private:
    Size Measure() override;
    void UpdateRenderAltImage(bool needAltImage);
    void SetSkRadii(const Radius& radius, SkVector& radii);
    void SetClipRadius();
    void CanvasDrawImageRect(const flutter::Paint& paint, const flutter::PaintData& paint_data, const Offset& offset,
        const ScopedCanvas& canvas);
    bool IsSVG(const std::string& src, InternalResource::ResourceId resourceId) const;
    void LoadSVGImage(const RefPtr<ImageProvider>& imageProvider, bool onlyLayoutSelf = false);
    void DrawSVGImage(const Offset& offset, ScopedCanvas& canvas);
    void UpdateLoadSuccessState();
    Rect RecalculateSrcRect(const Size& realImageSize);
    void UploadToGPUForRender(
        const sk_sp<SkImage>& image,
        const std::function<void(flutter::SkiaGPUObject<SkImage>)>& callback);

    sk_sp<SkSVGDOM> skiaDom_;
    bool isNetworkSrc_ = false;
    bool isSVG_ = false;
    bool needReload_ = false;
    std::string curImageSrc_;
    InternalResource::ResourceId curResourceId_ = InternalResource::ResourceId::NO_ID;
    fml::RefPtr<flutter::CanvasImage> image_;
    RefPtr<ImageProvider> imageProvider_;
    RefPtr<AnimatedImagePlayer> animatedPlayer_;
    RefPtr<Flutter::OffsetLayer> layer_;
    SkVector radii_[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    Size formerRawImageSize_;
    fml::RefPtr<flutter::SkiaUnrefQueue> unrefQueue_;
    fml::WeakPtr<flutter::IOManager> ioManager_;
    bool imageDataNotReady_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_FLUTTER_RENDER_IMAGE_H
