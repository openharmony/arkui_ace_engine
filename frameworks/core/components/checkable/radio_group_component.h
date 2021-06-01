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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_RADIO_GROUP_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_RADIO_GROUP_COMPONENT_H

#include "core/components/checkable/checkable_component.h"

namespace OHOS::Ace {

template<class T>
class RadioGroupComponent {
public:
    void AddRadio(const RefPtr<RadioComponent<T>>& radio)
    {
        if (radio) {
            radio->SetGroupValueChangedListener(groupValueChangedListener_);
            radios_.push_back(radio);
        }
    }

    void RemoveRadio(const RefPtr<RadioComponent<T>>& radio)
    {
        radios_.remove(radio);
    }

    bool IsEmpty()
    {
        return radios_.empty();
    }

private:
    const std::function<void(T)> groupValueChangedListener_ = [this](T newValue) {
        for (const auto& radio : radios_) {
            auto refPtr = radio.Upgrade();
            if (refPtr) {
                refPtr->SetGroupValue(newValue);
                refPtr->UpdateGroupValue(newValue);
            }
        }
    };
    std::list<WeakPtr<RadioComponent<T>>> radios_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_RADIO_GROUP_COMPONENT_H
