/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARKUI_CAPI_DEMO_GRID_COMPONENT_H
#define ARKUI_CAPI_DEMO_GRID_COMPONENT_H

#include "components/component.h"
#include "components/node_adapter.h"

namespace ArkUICApiDemo {

class GridItemComponent : public Component {
public:
    GridItemComponent() : Component(ARKUI_NODE_GRID_ITEM) {}
    explicit GridItemComponent(ArkUI_NodeHandle handle) : Component(handle) {}
};

class GridComponent : public Component {
public:
    GridComponent() : Component(ARKUI_NODE_GRID) {}
    explicit GridComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    void SetLazyAdapter(const std::shared_ptr<ItemAdapter<GridItemComponent>>& adapter)
    {
        ArkUI_AttributeItem item { nullptr, 0, nullptr, adapter->GetAdapter() };
        _nodeAPI->setAttribute(_component, NODE_GRID_NODE_ADAPTER, &item);
        _adapter = adapter;
    }
    void SetGridColumnsTemplate(const std::string& str);
    void SetGridRowsTemplate(const std::string& str);
    void SetGridColumnsGap(float val);
    void SetGridRowsGap(float val);
    void SetGridCachedCount(int32_t cachedCount);
    /**
     * @brief Set the scroll position to the specified offset.
     * @param hOffset horizontal scrolling offset
     * @param vOffset vertical scrolling offset
     * @param optionalParams
     * [0] scrolling duration, in milliseconds.
     * [1] scrolling curve. The parameter type is ArkUI_AnimationCurve.
     * [2] whether to enable the default spring animation.
     * [3] sets whether scrolling can cross the boundary.
     * [4] canOverScroll.
     */
    void SetScrollTo(float hOffset, float vOffset, const std::vector<int32_t>& optionalParams);

    std::shared_ptr<ItemAdapter<GridItemComponent>> GetAdapter() const
    {
        return _adapter;
    }
    void ReleaseAdapter()
    {
        return _adapter.reset();
    }

private:
    std::shared_ptr<ItemAdapter<GridItemComponent>> _adapter;
};

} // namespace ArkUICApiDemo
#endif // ARKUI_CAPI_DEMO_GRID_COMPONENT_H
