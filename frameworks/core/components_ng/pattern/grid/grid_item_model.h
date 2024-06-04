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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include "core/components_ng/pattern/grid/grid_item_theme.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT GridItemModel {
public:
    static GridItemModel* GetInstance();
    virtual ~GridItemModel() = default;

    virtual void Create(NG::GridItemStyle gridItemStyle) = 0;
    virtual void Create(
        std::function<void(int32_t)>&& deepRenderFunc, bool isLazy, NG::GridItemStyle gridItemStyle) = 0;
    virtual void SetRowStart(int32_t value) = 0;
    virtual void SetRowEnd(int32_t value) = 0;
    virtual void SetColumnStart(int32_t value) = 0;
    virtual void SetColumnEnd(int32_t value) = 0;
    virtual void SetForceRebuild(bool value) = 0;
    virtual void SetSelectable(bool value) = 0;
    virtual void SetSelected(bool selected) = 0;
    virtual void SetSelectChangeEvent(std::function<void(bool)>&& changeEvent) = 0;
    virtual void SetOnSelect(std::function<void(bool)>&& onSelect) = 0;

private:
    static std::unique_ptr<GridItemModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_MODEL_H
