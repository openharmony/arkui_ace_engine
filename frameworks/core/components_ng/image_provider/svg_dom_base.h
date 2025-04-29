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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_DOM_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_DOM_BASE_H

#include <optional>

#include "base/geometry/ng/size_t.h"
#include "base/geometry/size.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class SvgDomBase : public AceType {
    DECLARE_ACE_TYPE(SvgDomBase, AceType);

public:
    virtual SizeF GetContainerSize() const = 0;
    virtual void SetContainerSize(const SizeF& containerSize) = 0;
    virtual void SetFillColor(const std::optional<Color>& color) {}
    virtual void SetSmoothEdge(float value) {}
    virtual void SetColorFilter(const std::optional<ImageColorFilter>& colorFilter) {}
    virtual std::string GetDumpInfo() { return ""; }
    void SetRadius(const BorderRadiusArray& radiusXY)
    {
        if (!radius_) {
            radius_ = std::make_unique<BorderRadiusArray>(radiusXY);
        } else {
            *radius_ = radiusXY;
        }
    }

    virtual bool IsStatic()
    {
        return true;
    }

    virtual void SetAnimationCallback(std::function<void()>&& funcAnimateFlush, const WeakPtr<CanvasImage>& imagePtr) {}
    virtual void SetAnimationOnFinishCallback(const std::function<void()>& onFinishCallback) {}
    virtual void ControlAnimation(bool play) {}

    virtual void DrawImage(
        RSCanvas& canvas, const ImageFit& imageFit, const Size& layout) = 0;

    void ApplyImageFit(ImageFit imageFit, double& scaleX, double& scaleY)
    {
        switch (imageFit) {
            case ImageFit::FILL:
                ApplyFill(scaleX, scaleY);
                break;
            case ImageFit::NONE:
                break;
            case ImageFit::COVER:
                ApplyCover(scaleX, scaleY);
                break;
            case ImageFit::CONTAIN:
                ApplyContain(scaleX, scaleY);
                break;
            case ImageFit::SCALE_DOWN:
                if (svgSize_ > layout_ || svgSize_ == layout_) {
                    ApplyContain(scaleX, scaleY);
                }
                break;
            default:
                break;
        }
    }

    void ApplyFill(double& scaleX, double& scaleY)
    {
        if (!svgSize_.IsValid()) {
            return;
        }
        scaleX = layout_.Width() / svgSize_.Width();
        scaleY = layout_.Height() / svgSize_.Height();
    }

    void ApplyContain(double& scaleX, double& scaleY)
    {
        if (!svgSize_.IsValid()) {
            return;
        }
        if (Size::CalcRatio(svgSize_) > Size::CalcRatio(layout_)) {
            scaleX = layout_.Width() / svgSize_.Width();
            scaleY = scaleX;
        } else {
            scaleX = layout_.Height() / svgSize_.Height();
            scaleY = scaleX;
        }
    }

    void ApplyCover(double& scaleX, double& scaleY)
    {
        if (!svgSize_.IsValid()) {
            return;
        }
        if (Size::CalcRatio(svgSize_) > Size::CalcRatio(layout_)) {
            scaleX = layout_.Height() / svgSize_.Height();
            scaleY = scaleX;
        } else {
            scaleX = layout_.Width() / svgSize_.Width();
            scaleY = scaleX;
        }
    }

    Size layout_;  // layout size set by Image Component
    Size svgSize_; // self size specified in SVG file
    std::unique_ptr<BorderRadiusArray> radius_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_DOM_BASE_H
