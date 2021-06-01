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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_COMPONENT_H

#include <string>

#include "base/resource/internal_resource.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/pipeline/base/component_group.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/measurable.h"
#include "core/pipeline/base/render_component.h"

namespace OHOS::Ace {
// A component can show image.
class ACE_EXPORT ImageComponent : public RenderComponent, public Measurable {
    DECLARE_ACE_TYPE(ImageComponent, RenderComponent, Measurable);

public:
    explicit ImageComponent(const std::string& src = std::string());
    explicit ImageComponent(InternalResource::ResourceId resourceId) : resourceId_(resourceId) {}
    ~ImageComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetSrc(const std::string& src)
    {
        src_ = src;
    }

    const std::string& GetSrc() const
    {
        return src_;
    }

    void SetAlt(const std::string& alt)
    {
        alt_ = alt;
    }

    const std::string& GetAlt() const
    {
        return alt_;
    }

    void SetImageRepeat(ImageRepeat imageRepeat)
    {
        imageRepeat_ = imageRepeat;
    }

    ImageRepeat GetImageRepeat() const
    {
        return imageRepeat_;
    }

    void SetAlignment(const Alignment& alignment)
    {
        alignment_ = alignment;
    }

    const Alignment& GetAlignment() const
    {
        return alignment_;
    }

    void SetImageFit(ImageFit imageFit)
    {
        imageFit_ = imageFit;
    }

    ImageFit GetImageFit() const
    {
        return imageFit_;
    }

    void SetColor(const Color& color)
    {
        color_ = color;
        isColorSet_ = true;
    }

    const Color& GetColor() const
    {
        return color_;
    }

    void SetLoadSuccessEventId(const EventMarker& loadSuccessEventId)
    {
        loadSuccessEventId_ = loadSuccessEventId;
    }

    const EventMarker& GetLoadSuccessEventId() const
    {
        return loadSuccessEventId_;
    }

    void SetLoadFailEventId(const EventMarker& loadFailEventId)
    {
        loadFailEventId_ = loadFailEventId;
    }

    const EventMarker& GetLoadFailEventId() const
    {
        return loadFailEventId_;
    }

    InternalResource::ResourceId GetResourceId() const
    {
        return resourceId_;
    }

    void SetResourceId(InternalResource::ResourceId resourceId)
    {
        resourceId_ = resourceId;
    }

    void SetBorder(const Border& border)
    {
        border_ = border;
    }

    const Border& GetBorder() const
    {
        return border_;
    }

    bool GetFitMaxSize() const
    {
        return fitMaxSize_;
    }

    void SetFitMaxSize(bool fitMaxSize)
    {
        fitMaxSize_ = fitMaxSize;
    }

    bool IsMatchTextDirection() const
    {
        return matchTextDirection_;
    }

    void SetMatchTextDirection(bool matchTextDirection)
    {
        matchTextDirection_ = matchTextDirection;
    }

    bool IsColorSet() const
    {
        return isColorSet_;
    }

private:
    std::string src_;
    std::string alt_;
    Alignment alignment_ = Alignment::CENTER;
    ImageRepeat imageRepeat_ = ImageRepeat::NOREPEAT;
    ImageFit imageFit_ = ImageFit::COVER;
    Color color_ = Color::TRANSPARENT;
    bool isColorSet_ = false;
    EventMarker loadSuccessEventId_;
    EventMarker loadFailEventId_;
    InternalResource::ResourceId resourceId_ = InternalResource::ResourceId::NO_ID;
    Border border_;
    bool fitMaxSize_ = false;
    bool matchTextDirection_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_COMPONENT_H
