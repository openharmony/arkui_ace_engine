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

#include "core/components_ng/pattern/grid/grid_item_pattern.h"

#include "base/utils/utils.h"
namespace OHOS::Ace::NG {
void GridItemPattern::MarkIsSelected(bool isSelected)
{
    if (isSelected_ != isSelected) {
        isSelected_ = isSelected;
        auto eventHub = GetEventHub<GridItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnSelect(isSelected);
    }
}
} // namespace OHOS::Ace::NG