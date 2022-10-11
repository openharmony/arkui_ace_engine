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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_COL_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_COL_VIEW_H

#include "base/utils/macros.h"
#include "frameworks/core/components_v2/grid_layout/grid_container_util_class.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridColView {
public:
    static void Create();
    static void Create(const RefPtr<V2::GridContainerSize>& span, const RefPtr<V2::GridContainerSize>& offset,
        const RefPtr<V2::GridContainerSize>& order);
    static void SetSpan(const RefPtr<V2::GridContainerSize>& span);
    static void SetOffset(const RefPtr<V2::GridContainerSize>& offset);
    static void SetOrder(const RefPtr<V2::GridContainerSize>& order);
};
} // namespace OHOS::Ace::NG

#endif