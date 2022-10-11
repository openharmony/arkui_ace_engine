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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H

#include <functional>
#include <memory>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace {

class ListItemModel {
public:
    static ListItemModel* GetInstance();
    virtual ~ListItemModel() = default;

    virtual void Create() = 0;
    virtual void Create(std::function<void(int32_t)>&& deepRenderFunc) = 0;
    virtual void SetBorderRadius(const Dimension& borderRadius) = 0;
    virtual void SetType(const std::string& type) = 0;
    virtual void SetIsLazyCreating(bool isLazy) = 0;
    virtual void SetSticky(V2::StickyMode stickyMode) = 0;
    virtual void SetEditMode(uint32_t editMode) = 0;
    virtual void SetSelectable(bool selectable) = 0;
    virtual void SetSwiperAction(
        std::function<void()>&& startAction, std::function<void()>&& endAction, V2::SwipeEdgeEffect edgeEffect) = 0;
    virtual void SetSelectCallback(OnSelectFunc&& selectCallback) = 0;
    virtual void SetOnDragStart(OnDragFunc&& onDragStart) = 0;

private:
    static std::unique_ptr<ListItemModel> instance_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H
