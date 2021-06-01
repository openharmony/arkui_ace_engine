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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_RENDER_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_RENDER_IMAGE_H

#include "base/resource/internal_resource.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/radius.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

enum class ImageLoadingStatus {
    UNLOADED = 0,
    LOADING,
    UPDATING,
    LOAD_SUCCESS,
    LOAD_FAIL,
};

class RenderImage : public RenderNode {
    DECLARE_ACE_TYPE(RenderImage, RenderNode);

public:
    static RefPtr<RenderNode> Create();
    static bool IsSVG(const std::string& src, InternalResource::ResourceId resourceId);
    virtual Size Measure() = 0;
    void SetImageComponentSize(const Size& imageComponentSize)
    {
        imageComponentSize_ = imageComponentSize;
    }
    const Size& GetImageComponentSize() const
    {
        return imageComponentSize_;
    }
    void SetImageFit(ImageFit imageFit)
    {
        imageFit_ = imageFit;
    }
    void SetImageSrc(const std::string& imageSrc)
    {
        if (imageSrc != imageSrc_) {
            imageSrc_ = imageSrc;
            UpdateImageProvider();
        }
    }
    const std::list<Rect>& GetRectList() const
    {
        return rectList_;
    }
    void SetMatchTextDirection(bool matchTextDirection)
    {
        matchTextDirection_ = matchTextDirection;
    }
    void SetRotate(double rotate)
    {
        rotate_ = rotate;
    }

    void SetImageRepeat(const ImageRepeat& imageRepeat)
    {
        if (imageRepeat_ != imageRepeat) {
            imageRepeat_ = imageRepeat;
            MarkNeedLayout();
        }
    }

    void SetBgImageSize(BackgroundImageSizeType type, double value = FULL_IMG_SIZE, double directionX = true)
    {
        if (background_ && directionX) {
            if (type != imageSize_.GetSizeTypeX() || !NearEqual(value, imageSize_.GetSizeValueX())) {
                imageSize_.SetSizeTypeX(type);
                imageSize_.SetSizeValueX(value);
                MarkNeedLayout();
            }
        }
        if (background_ && !directionX) {
            if (type != imageSize_.GetSizeTypeY() || !NearEqual(value, imageSize_.GetSizeValueY())) {
                imageSize_.SetSizeTypeY(type);
                imageSize_.SetSizeValueY(value);
                MarkNeedLayout();
            }
        }
    }

    void SetBgImagePosition(const BackgroundImagePosition& imagePosition)
    {
        if (background_ && imagePosition != imagePosition_) {
            imagePosition_ = imagePosition;
            MarkNeedLayout();
        }
    }

    using ImageUpdateFunc = std::function<void()>;
    void RegisterImageUpdateFunc(const ImageUpdateFunc& imageUpdateFunc)
    {
        imageUpdateFunc_ = imageUpdateFunc;
    }

    void SetBackgroundImageFlag(bool backgroundImageFlag)
    {
        if (background_ != backgroundImageFlag) {
            background_ = backgroundImageFlag;
        }
    }

    bool GetBackgroundImageFlag() const
    {
        return background_;
    }

    void SetBgImageBoxPaintSize(const Size& boxPaintSize)
    {
        if (background_ && boxPaintSize_ != boxPaintSize) {
            boxPaintSize_ = boxPaintSize;
            MarkNeedLayout();
        }
    }

    void SetBgImageBoxMarginOffset(const Offset& boxMarginOffset)
    {
        if (background_ && boxMarginOffset_ != boxMarginOffset) {
            boxMarginOffset_ = boxMarginOffset;
            MarkNeedLayout();
        }
    }

    virtual void UpdateResourceId(InternalResource::ResourceId resourceId, bool onlySelfLayout)
    {
        resourceId_ = resourceId;
        MarkNeedLayout(onlySelfLayout);
    }

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void GenerateRepeatRects(const Rect& fundamentalRect, const Size& parentSize, const ImageRepeat& imageRepeat);
    virtual void UpdateImageProvider() {}

protected:
    void ApplyImageFit(Rect& srcRect, Rect& dstRect);
    void ApplyContain(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& imageComponentSize);
    void ApplyCover(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& imageComponentSize);
    void ApplyFitWidth(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& imageComponentSize);
    void ApplyFitHeight(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& imageComponentSize);
    void ApplyNone(Rect& srcRect, Rect& dstRect, const Size& rawPicSize, const Size& imageComponentSize);
    void FireLoadEvent(const Size& picSize) const;
    void SetRadius(const Border& border);
    void CalculateResizeTarget();
    bool NeedResize() const;

    // background image
    void PerformLayoutBgImage();
    void GenerateImageRects(const Size& srcSize, const BackgroundImageSize& imageSize, ImageRepeat imageRepeat,
                            const BackgroundImagePosition& imagePosition);
    Size CalculateImageRenderSize(const Size& srcSize, const BackgroundImageSize& imageSize) const;
    Size CalculateImageRenderSizeWithSingleParam(const Size& srcSize, const BackgroundImageSize& imageSize) const;
    Size CalculateImageRenderSizeWithDoubleParam(const Size& srcSize, const BackgroundImageSize& imageSize) const;
    void CalculateImageRenderPosition(const BackgroundImagePosition& imagePosition);
    void PrintImageLog(const Size& srcSize, const BackgroundImageSize& imageSize, ImageRepeat imageRepeat,
        const BackgroundImagePosition& imagePosition) const;
    Size CalculateBackupImageSize(const Size& pictureSize) const;
    virtual void ClearRenderObject() override;

    std::string imageSrc_;
    std::string imageAlt_;
    std::function<void(const std::string&)> loadSuccessEvent_;
    std::function<void(const std::string&)> loadFailEvent_;
    std::function<void(const std::shared_ptr<BaseEventInfo>&)> loadImgSuccessEvent_;
    std::function<void(const std::shared_ptr<BaseEventInfo>&)> loadImgFailEvent_;
    bool fitMaxSize_ = false;
    bool isImageSizeSet_ = false;
    bool rawImageSizeUpdated_ = false;
    bool matchTextDirection_ = false;
    Size previousLayoutSize_;
    Size imageComponentSize_;
    Size formerMaxSize_;
    Alignment alignment_ = Alignment::CENTER;
    ImageLoadingStatus imageLoadingStatus_ = ImageLoadingStatus::UNLOADED;

    // Real picture area with px.
    Rect srcRect_;
    Rect dstRect_;
    Rect currentSrcRect_;
    std::list<Rect> currentDstRectList_;
    ImageFit imageFit_ = ImageFit::COVER;
    ImageRepeat imageRepeat_ = ImageRepeat::NOREPEAT;
    std::list<Rect> rectList_;
    Color color_ = Color::TRANSPARENT;
    bool isColorSet_ = false;
    InternalResource::ResourceId resourceId_ = InternalResource::ResourceId::NO_ID;
    double singleWidth_ = 0.0;
    double displaySrcWidth_ = 0.0;
    double scale_ = 1.0;
    double paddingHorizontal_ = 0.0;
    double paddingVertical_ = 0.0;
    double horizontalRepeatNum_ = 1.0;
    double rotate_ = 0.0;
    bool keepOffsetZero_ = false;
    bool resizeCallLoadImage_ = false;
    int32_t frameCount_ = 0;
    Radius topLeftRadius_ = Radius(0.0);
    Radius topRightRadius_ = Radius(0.0);
    Radius bottomLeftRadius_ = Radius(0.0);
    Radius bottomRightRadius_ = Radius(0.0);
    Size resizeScale_;
    Size resizeTarget_;
    Size previousResizeTarget_;
    Size currentResizeScale_;
    Dimension width_;
    Dimension height_;
    Size rawImageSize_;
    RefPtr<RenderImage> renderAltImage_;

    // background image
    ImageUpdateFunc imageUpdateFunc_;
    bool background_ = false;
    Size boxPaintSize_;
    Offset boxMarginOffset_;
    BackgroundImageSize imageSize_;
    BackgroundImagePosition imagePosition_;
    // result for background image
    Size imageRenderSize_;
    Offset imageRenderPosition_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_RENDER_IMAGE_H
