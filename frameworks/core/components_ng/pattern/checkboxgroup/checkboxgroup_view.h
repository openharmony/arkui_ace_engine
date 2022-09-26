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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_VIEW_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_event_hub.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CheckBoxGroupView {
public:
    static void Create(const std::optional<std::string>& groupName);
    static void SetSelectAll(bool isSelected);
    static void SetSelectedColor(Color color);
    static void SetOnChange(GroupChangeEvent&& onChange);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_VIEW_H
