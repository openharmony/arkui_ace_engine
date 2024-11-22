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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_MODEL_H

#include <functional>
#include <memory>
#include <mutex>

#include "core/components/common/layout/constants.h"
#include "frameworks/core/components_v2/grid_layout/grid_container_util_class.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT GridRowModel {
public:
    static GridRowModel* GetInstance();
    virtual ~GridRowModel() = default;

    virtual void Create() = 0;
    virtual void Create(const RefPtr<V2::GridContainerSize>& col, const RefPtr<V2::Gutter>& gutter,
        const RefPtr<V2::BreakPoints>& breakpoints, V2::GridRowDirection direction) = 0;
    virtual void SetOnBreakPointChange(std::function<void(const std::string)>&& onChange) = 0;
    virtual void SetHeight() {}
    virtual void SetAlignItems(FlexAlign alignItem) = 0;
};
} // namespace OHOS::Ace
#endif