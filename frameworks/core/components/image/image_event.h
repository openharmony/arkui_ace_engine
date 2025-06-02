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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_EVENT_H

#include "base/image/image_defines.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {

class ACE_EXPORT LoadImageSuccessEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadImageSuccessEvent, BaseEventInfo);

public:
    LoadImageSuccessEvent(double width, double height, double componentWidth, double componentHeight,
        int32_t loadingStatus = 1, double contentWidth = 0.0, double contentHeight = 0.0, double contentOffsetX = 0.0,
        double contentOffsetY = 0.0) : BaseEventInfo("LoadImageSuccessEvent"), width_(width), height_(height),
        componentWidth_(componentWidth), componentHeight_(componentHeight), loadingStatus_(loadingStatus),
        contentWidth_(contentWidth), contentHeight_(contentHeight), contentOffsetX_(contentOffsetX),
        contentOffsetY_(contentOffsetY) {}

    ~LoadImageSuccessEvent() = default;

    double GetWidth() const
    {
        return width_;
    }

    double GetHeight() const
    {
        return height_;
    }

    double GetComponentWidth() const
    {
        return componentWidth_;
    }

    double GetComponentHeight() const
    {
        return componentHeight_;
    }

    int32_t GetLoadingStatus() const
    {
        return loadingStatus_;
    }

    double GetContentWidth() const
    {
        return contentWidth_;
    }

    double GetContentHeight() const
    {
        return contentHeight_;
    }

    double GetContentOffsetX() const
    {
        return contentOffsetX_;
    }

    double GetContentOffsetY() const
    {
        return contentOffsetY_;
    }

private:
    double width_ = 0.0;
    double height_ = 0.0;
    double componentWidth_ = 0.0;
    double componentHeight_ = 0.0;
    int32_t loadingStatus_ = 1; // [0] means [done layout], [1] means [load success]

    double contentWidth_ = 0.0;
    double contentHeight_ = 0.0;
    double contentOffsetX_ = 0.0;
    double contentOffsetY_ = 0.0;
};

class ACE_EXPORT LoadImageFailEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadImageFailEvent, BaseEventInfo);

public:
    LoadImageFailEvent(double componentWidth, double componentHeight, std::string errorMessage)
        : BaseEventInfo("LoadImageFailEvent"), componentWidth_(componentWidth), componentHeight_(componentHeight),
          errorMessage_(std::move(errorMessage))
    {}
    LoadImageFailEvent(
        double componentWidth, double componentHeight, std::string errorMessage, const ImageErrorInfo& errorInfo)
        : BaseEventInfo("LoadImageFailEvent"), componentWidth_(componentWidth), componentHeight_(componentHeight),
          errorMessage_(std::move(errorMessage)), errorInfo_(errorInfo)
    {}
    ~LoadImageFailEvent() override = default;

    double GetComponentWidth() const
    {
        return componentWidth_;
    }

    double GetComponentHeight() const
    {
        return componentHeight_;
    }

    const std::string& GetErrorMessage() const
    {
        return errorMessage_;
    }

    ImageErrorInfo GetErrorInfo() const
    {
        return errorInfo_;
    }

private:
    double componentWidth_ = 0.0;
    double componentHeight_ = 0.0;
    std::string errorMessage_;
    ImageErrorInfo errorInfo_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_EVENT_H
