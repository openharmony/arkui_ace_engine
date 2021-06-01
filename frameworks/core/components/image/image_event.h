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

namespace OHOS::Ace {

class ACE_EXPORT LoadImageSuccessEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadImageSuccessEvent, BaseEventInfo);

public:
    LoadImageSuccessEvent(double width, double height)
        : BaseEventInfo("LoadImageSuccessEvent"), width_(width), height_(height) {}

    ~LoadImageSuccessEvent() = default;

    double GetWidth() const
    {
        return width_;
    }

    double GetHeight() const
    {
        return height_;
    }

private:
    double width_ = 0;
    double height_ = 0;
};

class ACE_EXPORT LoadImageFailEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadImageFailEvent, BaseEventInfo);

public:
    LoadImageFailEvent() : BaseEventInfo("LoadImageFailEvent") {}
    ~LoadImageFailEvent() = default;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_IMAGE_IMAGE_EVENT_H
