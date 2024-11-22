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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_COL_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_COL_MODEL_H

#include <memory>
#include <mutex>

#include "frameworks/core/components_v2/grid_layout/grid_container_util_class.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT GridColModel {
public:
    static GridColModel* GetInstance();
    virtual ~GridColModel() = default;

    virtual void Create() = 0;
    virtual void Create(const V2::GridContainerSize& span, const V2::GridContainerSize& offset,
        const V2::GridContainerSize& order) = 0;
    virtual void SetSpan(const V2::GridContainerSize& span) = 0;
    virtual void SetOffset(const V2::GridContainerSize& offset) = 0;
    virtual void SetOrder(const V2::GridContainerSize& order) = 0;
};
} // namespace OHOS::Ace
#endif