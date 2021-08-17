/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_GRID_LAYOUT_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_GRID_LAYOUT_ELEMENT_H

#include <unordered_map>

#include "core/components_v2/foreach/lazy_foreach_component.h"
#include "core/pipeline/base/component_group_element.h"

namespace OHOS::Ace {

class GridLayoutElement : public ComponentGroupElement, public FocusGroup {
    DECLARE_ACE_TYPE(GridLayoutElement, ComponentGroupElement, FocusGroup);

public:
    void Update() override;
    bool RequestNextFocus(bool vertical, bool reverse, const Rect& rect) override;
    void Prepare(const WeakPtr<Element>& parent) override;

    bool BuildChildByIndex(int32_t index);
    void DeleteChildByIndex(int32_t index);

    void OnReload();
    void OnItemAdded(int32_t index);
    void OnItemDeleted(int32_t index);
    void OnItemChanged(int32_t index);
    void OnItemMoved(int32_t from, int32_t to);

private:
    RefPtr<RenderNode> CreateRenderNode() override;
    void ApplyRenderChild(const RefPtr<RenderElement>& renderChild) override;

    std::unordered_map<int32_t, RefPtr<Element>> lazyChildItems_;

    RefPtr<V2::LazyForEachComponent> lazyForEachComponent_;
    RefPtr<V2::DataChangeListener> listener;
    bool isUseLazyForEach_ = false;
};

class GridItemDataChangeListener : virtual public V2::DataChangeListener {
public:
    GridItemDataChangeListener(const WeakPtr<GridLayoutElement>& element) : element_(element) {}

    void OnDataReloaded() override;
    void OnDataAdded(size_t index) override;
    void OnDataDeleted(size_t index) override;
    void OnDataChanged(size_t index) override;
    void OnDataMoved(size_t from, size_t to) override;

private:
    WeakPtr<GridLayoutElement> element_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_GRID_LAYOUT_ELEMENT_H
