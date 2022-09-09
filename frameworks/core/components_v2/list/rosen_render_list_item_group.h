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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_ROSEN_RENDER_LIST_ITEM_GROUP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_ROSEN_RENDER_LIST_ITEM_GROUP_H

#include "base/utils/noncopyable.h"
#include "core/components_v2/list/render_list_item_group.h"

namespace OHOS::Ace::V2 {

class RosenRenderListItemGroup : public RenderListItemGroup {
    DECLARE_ACE_TYPE(V2::RosenRenderListItemGroup, RenderListItemGroup);

public:
    RosenRenderListItemGroup() = default;
    ~RosenRenderListItemGroup() override = default;

protected:
    void PaintDivider(RenderContext& context) override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(RosenRenderListItemGroup);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_ROSEN_RENDER_LIST_ITEM_GROUP_H
