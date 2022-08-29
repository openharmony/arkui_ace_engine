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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_VIEW_H

#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RowView {
public:
    static void Create(const std::optional<Dimension>& space);
    static void AlignItems(FlexAlign flexAlign);
    static void JustifyContent(FlexAlign flexAlign);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_VIEW_H
