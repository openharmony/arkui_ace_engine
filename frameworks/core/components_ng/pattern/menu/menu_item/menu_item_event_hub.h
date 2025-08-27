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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_EVENT_HUB_H

#include <cstdint>

#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
using MenuJSCallback = std::function<void()>;
using OnSelectEvent = std::function<void(int32_t)>;

class MenuItemEventHub : public EventHub {
    DECLARE_ACE_TYPE(MenuItemEventHub, EventHub);

public:
    MenuItemEventHub() = default;
    ~MenuItemEventHub() override = default;

    inline void SetOnChange(const std::function<void(bool)>& onChange)
    {
        onChange_ = onChange;
    }

    inline std::function<void(bool)>&& GetOnChange()
    {
        return std::move(onChange_);
    }

    inline void SetSelectedChangeEvent(const std::function<void(bool)>& selectedChangeEvent)
    {
        selectedChangeEvent_ = selectedChangeEvent;
    }

    inline std::function<void(bool)>&& GetSelectedChangeEvent()
    {
        return std::move(selectedChangeEvent_);
    }

    inline void SetMenuOnClick(const std::function<void()>& onClickFunc)
    {
        menuOnClick_ = onClickFunc;
    }

    inline MenuJSCallback GetJsCallback()
    {
        return menuOnClick_;
    }

    inline void SetOnSelect(const OnSelectEvent& onSelect)
    {
        onSelect_ = onSelect;
    }

    inline OnSelectEvent GetOnSelect()
    {
        return onSelect_;
    }

private:
    // callback of menuItem
    std::function<void(bool)> onChange_;
    std::function<void(bool)> selectedChangeEvent_;
    MenuJSCallback menuOnClick_;
    // callback of select component
    OnSelectEvent onSelect_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemEventHub);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_EVENT_HUB_H
