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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_SEARCH_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_SEARCH_COMPONENT_H

#include "base/resource/internal_resource.h"
#include "base/utils/utils.h"
#include "core/components/image/image_component.h"
#include "core/components/text_field/text_field_component.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class SearchComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(SearchComponent, SoleChildComponent);

public:
    SearchComponent() = default;
    ~SearchComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetCloseIconSize(const Dimension& closeIconSize)
    {
        closeIconSize_ = closeIconSize;
    }

    const Dimension& GetCloseIconSize() const
    {
        return closeIconSize_;
    }

    void SetCloseIconHotZoneHorizontal(const Dimension& closeIconHotZoneHorizontal)
    {
        closeIconHotZoneHorizontal_ = closeIconHotZoneHorizontal;
    }

    const Dimension& GetCloseIconHotZoneHorizontal() const
    {
        return closeIconHotZoneHorizontal_;
    }

    const std::string& GetSearchText() const
    {
        return searchText_;
    }

    void SetSearchText(const std::string& searchText)
    {
        searchText_ = searchText;
    }

    const std::string& GetCloseIconSrc() const
    {
        return closeIconSrc_;
    }

    void SetCloseIconSrc(const std::string& closeIconSrc)
    {
        closeIconSrc_ = closeIconSrc;
    }

    void SetChangeEventId(const EventMarker& changeEventId)
    {
        changeEventId_ = changeEventId;
    }

    const EventMarker& GetChangeEventId() const
    {
        return changeEventId_;
    }

    void SetSubmitEventId(const EventMarker& submitEventId)
    {
        submitEventId_ = submitEventId;
    }

    const EventMarker& GetSubmitEventId() const
    {
        return submitEventId_;
    }

    const RefPtr<TextEditController>& GetTextEditController() const
    {
        return textEditController_;
    }

    void SetTextEditController(const RefPtr<TextEditController>& controller)
    {
        textEditController_ = controller;
    }

    void SetSubmitEvent(const std::function<void(const std::string&)>& event)
    {
        submitEvent_ = event;
    }

    const std::function<void(const std::string&)>& GetSubmitEvent() const
    {
        return submitEvent_;
    }

    RefPtr<Decoration> GetDecoration() const
    {
        return decoration_;
    }

    void SetDecoration(const RefPtr<Decoration>& decoration)
    {
        decoration_ = decoration;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    void SetHoverColor(const Color& hoverColor)
    {
        hoverColor_ = hoverColor;
    }

    const Color& GetPressColor() const
    {
        return pressColor_;
    }

    void SetPressColor(const Color& pressColor)
    {
        pressColor_ = pressColor;
    }

private:
    Dimension closeIconSize_;
    Dimension closeIconHotZoneHorizontal_;
    std::string searchText_;
    std::string closeIconSrc_;
    EventMarker changeEventId_;
    EventMarker submitEventId_;
    RefPtr<TextEditController> textEditController_;
    std::function<void(const std::string&)> submitEvent_;
    RefPtr<Decoration> decoration_;
    Color hoverColor_;
    Color pressColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_SEARCH_COMPONENT_H
