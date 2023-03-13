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

#include "core/components_ng/pattern/grid/grid_accessibility_property.h"

namespace OHOS::Ace::NG {
bool GridAccessibilityProperty::IsScrollable() const
{
    return false;
}

bool GridAccessibilityProperty::IsEditable() const
{
    return false;
}

int32_t GridAccessibilityProperty::GetBeginIndex() const
{
    return -1;
}

int32_t GridAccessibilityProperty::GetEndIndex() const
{
    return -1;
}

int32_t GridAccessibilityProperty::GetCollectionItemCounts() const
{
    return 0;
}

AceCollectionInfo GridAccessibilityProperty::GetCollectionInfo() const
{
    return AceCollectionInfo();
}
} // namespace OHOS::Ace::NG
