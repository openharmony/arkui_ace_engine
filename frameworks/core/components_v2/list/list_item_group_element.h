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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GROUP_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GROUP_ELEMENT_H

#include "core/components_v2/list/list_item_element.h"

#include "core/components_v2/common/element_proxy.h"
#include "core/components_v2/list/render_list_item_group.h"
#include "core/components_v2/list/list_item_generator.h"
#include "core/focus/focus_node.h"
#include "core/pipeline/base/render_element.h"

namespace OHOS::Ace::V2 {

class ListItemGroupElement : public RenderElement,
                             public FlushEvent,
                             private ListItemGenerator,
                             private ElementProxyHost {
    DECLARE_ACE_TYPE(V2::ListItemGroupElement, RenderElement, FlushEvent);

public:
    ListItemGroupElement() = default;
    ~ListItemGroupElement() override = default;

    void PerformBuild() override;
    RefPtr<RenderListItem> RequestListItem(size_t index) override;
    RefPtr<RenderNode> RequestListItemHeader(void) override;
    RefPtr<RenderNode> RequestListItemFooter(void) override;
    RefPtr<Element> GetListItemBySlot(size_t index);
    void RecycleListItem(size_t index) override;
    size_t TotalCount() override;
    void OnPostFlush() override;
private:
    RefPtr<Element> OnUpdateElement(const RefPtr<Element>& element, const RefPtr<Component>& component) override;
    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Component> OnMakeEmptyComponent() override;
    void OnDataSourceUpdated(size_t startIndex) override;

    RefPtr<RenderListItemGroup> renderListItemGroup_;
    RefPtr<Element> headerElement_;
    RefPtr<Element> footerElement_;
    ACE_DISALLOW_COPY_AND_MOVE(ListItemGroupElement);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GROUP_ELEMENT_H
