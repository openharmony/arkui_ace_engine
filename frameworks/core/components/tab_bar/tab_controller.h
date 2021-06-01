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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TAB_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TAB_CONTROLLER_H

#include <map>

#include "base/memory/ace_type.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {

class TabController : public AceType {
    DECLARE_ACE_TYPE(TabController, AceType);

public:
    explicit TabController(int32_t id);
    ~TabController() override = default;

    static RefPtr<TabController> GetController(int32_t id);

    void ValidateIndex(int32_t maxIndex);
    void SetPageReady(bool ready);
    void SetIndex(int32_t index);
    void SetIndexByScrollContent(int32_t index);
    int32_t GetIndex() const;
    void SetContentElement(const RefPtr<Element>& contentElement);
    void SetBarElement(const RefPtr<Element>& barElement);
    int32_t GetId() const;
    void ChangeDispatch(int32_t index);

private:
    int32_t id_ = -1;
    int32_t index_ = 0;
    bool pageReady_ = false;
    WeakPtr<Element> contentElement_;
    WeakPtr<Element> barElement_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TAB_CONTROLLER_H
