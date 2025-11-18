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

#ifndef ARKUI_CAPI_DEMO_WATERFLOW_COMPONENT_H
#define ARKUI_CAPI_DEMO_WATERFLOW_COMPONENT_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_node.h>

#include "components/component.h"
#include "components/waterflow/FlowItem.h"
#include "components/node_adapter.h"

namespace ArkUICApiDemo {
using OnWillScroll = std::function<void(float, int32_t, int32_t)>;
using OnReachStart = std::function<void()>;
using OnReachEnd = std::function<void()>;
using OnScrollStop = std::function<void()>;
using OnDidScroll = std::function<void(float, int32_t)>;
using OnScrollFrameBegin = std::function<float(float, int32_t)>;
using OnScrollIndex = std::function<void(int32_t, int32_t)>;

struct WaterFlowSection {
    int32_t itemsCount = 0;
    int32_t crossCount;
    float columnsGap;
    float rowsGap;
    // top right bottom left
    ArkUI_Margin margin { 0, 0, 0, 0 };
    float (*onGetItemMainSizeByIndex)(int32_t itemIndex);
    void* userData;
};

class WaterFlowSectionOption {
public:
    WaterFlowSectionOption() : _option(OH_ArkUI_WaterFlowSectionOption_Create()) {}
    ~WaterFlowSectionOption()
    {
        OH_ArkUI_WaterFlowSectionOption_Dispose(_option);
    }
    void SetSection(int32_t index, WaterFlowSection section);
    WaterFlowSection GetSection(int32_t index);

    void SetSize(int32_t size);
    int32_t GetSize();
    ArkUI_WaterFlowSectionOption* GetOption()
    {
        return _option;
    }

private:
    ArkUI_WaterFlowSectionOption* _option;
};

class WaterFlowComponent : public Component {
public:
    WaterFlowComponent() : Component(ARKUI_NODE_WATER_FLOW) {}
    explicit WaterFlowComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    // 引入懒加载模块。
    void SetLazyAdapter(const std::shared_ptr<ItemAdapter<FlowItemComponent>>& adapter)
    {
        ArkUI_AttributeItem item { nullptr, 0, nullptr, adapter->GetAdapter() };
        _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_NODE_ADAPTER, &item);
        _adapter = adapter;
    }
    void SetLayoutDirection(int32_t layoutDirection);
    void SetColumnsTemplate(const std::string& str);
    void SetRowsTemplate(const std::string& str);
    void SetWaterFlowColumnsGap(float val);
    void SetWaterFlowRowsGap(float val);
    void SetWaterFlowSectionOption(int32_t start, const std::shared_ptr<WaterFlowSectionOption>& option);
    void SetWaterFlowCachedCount(int32_t cachedCount);
    void SetWaterFlowFooter(ArkUI_NodeHandle node);
    void SetWaterFlowScrollToIndex(int32_t index);
    void SetWaterFlowScrollToIndex(int32_t index, int32_t animation);
    void SetWaterFlowScrollToIndex(int32_t index, int32_t animation, int32_t alignment);
    void SetItemConstraintSize(float minWidth, float maxWidth, float minHeight, float maxHeight);
    void SetWaterFlowNestedScroll(int32_t forward, int32_t backward);
    void SetWaterFlowScrollBar(int32_t barState);
    void SetWaterFlowScrollBarWidth(float width);
    void SetWaterFlowScrollBarColor(uint32_t color);
    void SetWaterFlowEnableScrollInteraction(bool enableScrollInteraction);
    void SetWaterFlowFriction(float friction);
    void SetWaterFlowEdgeEffect(int32_t edgeEffect, bool alwaysEnabled);
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
    void SetScrollEdge(int32_t type);
    void SetScrollPage(bool next);
    void SetScrollPage(bool next, bool animation);
    void SetScrollBy(float hDistance, float vDistance);

    void OnNodeEvent(ArkUI_NodeEvent* event) override;
    void SetOnWillScroll(OnWillScroll onWillScroll);
    void SetOnReachStart(OnReachStart onReachStart);
    void SetOnReachEnd(OnReachEnd onReachEnd);
    void SetOnScrollStop(OnScrollStop onScrollStop);
    void SetOnDidScroll(OnDidScroll onDidScroll);
    void SetOnScrollFrameBegin(OnScrollFrameBegin onScrollFrameBegin);
    void SetOnScrollIndex(OnScrollIndex onScrollIndex);

    std::shared_ptr<ItemAdapter<FlowItemComponent>> GetAdapter() const
    {
        return _adapter;
    }
    std::shared_ptr<WaterFlowSectionOption> GetSectionOption() const
    {
        return _sectionsOption;
    }
    void ReleaseSectionOption()
    {
        _sectionsOption.reset();
    }

private:
    std::shared_ptr<WaterFlowSectionOption> _sectionsOption;
    std::shared_ptr<ItemAdapter<FlowItemComponent>> _adapter;
};
} // namespace ArkUICApiDemo

#endif // ARKUI_CAPI_DEMO_WATERFLOW_COMPONENT_H
