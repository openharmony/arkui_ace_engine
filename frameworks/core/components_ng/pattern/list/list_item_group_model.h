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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_MODEL_H

#include <functional>
#include <memory>
#include <mutex>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ListItemGroupModel {
public:
    static ListItemGroupModel* GetInstance();
    virtual ~ListItemGroupModel() = default;

    virtual void Create(V2::ListItemGroupStyle listItemGroupStyle) = 0;
    virtual void SetSpace(const Dimension& space) = 0;
    virtual void SetDivider(const V2::ItemDivider& divider) = 0;
    virtual void SetHeader(std::function<void()>&& header) = 0;
    virtual void SetFooter(std::function<void()>&& footer) = 0;
    virtual RefPtr<NG::ListChildrenMainSize> GetOrCreateListChildrenMainSize()
    {
        return nullptr;
    }
    virtual void SetHeaderComponent(const RefPtr<NG::UINode>& headerComponent)
    {
        return;
    }
    virtual void SetFooterComponent(const RefPtr<NG::UINode>& footerComponent)
    {
        return;
    }
    virtual void RemoveHeader()
    {
        return;
    }
    virtual void RemoveFooter()
    {
        return;
    }

private:
    static std::unique_ptr<ListItemGroupModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H
