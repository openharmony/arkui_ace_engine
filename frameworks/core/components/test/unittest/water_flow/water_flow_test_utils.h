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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_WATER_FLOW_WARER_FLOW_TEST_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_WATER_FLOW_WARER_FLOW_TEST_UTILS_H

#include "core/components_v2/water_flow/water_flow_component.h"
#include "core/components_v2/water_flow/render_water_flow.h"
#include "core/components_v2/water_flow/water_flow_item_component.h"
#include "core/components/box/render_box.h"
#include "core/components/image/render_image.h"
#include "core/components/image/image_component.h"

namespace OHOS::Ace {
namespace {
using WaterFlowCallback = std::function<void(const std::string&, const std::string&)>;
class MockEventHandler : public AceEventHandler {
    void HandleAsyncEvent(const EventMarker& eventMarker) override {};
    void HandleAsyncEvent(const EventMarker& eventMarker, int32_t param) override {};
    void HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info) override {};
    void HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param) override {};
    void HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& keyEvent) override {};
    void HandleSyncEvent(const EventMarker& eventMarker, bool& result) override {};
    void HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result) override {};
    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& param, std::string& result) override {};
    void HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& keyEvent, bool& result) override {};
    void HandleSyncEvent(
        const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId) override {};
};

class TestGridEventHander : public MockEventHandler {
public:
    explicit TestGridEventHander(WaterFlowCallback eventCallback) : eventCallback_(eventCallback) {};
    ~TestGridEventHander() = default;

    void HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param)
    {
        if (eventCallback_) {
            eventCallback_(eventMarker.GetData().eventId, param);
        }
    };

private:
    WaterFlowCallback eventCallback_;
};
} // namespace

class WaterFlowTestUtils {
public:
    static RefPtr<RenderNode> CreateRenderItem(
        double width, double height, int32_t rowspan, int32_t colspan, const RefPtr<PipelineContext>& context);
    static RefPtr<V2::RenderWaterFlowItem> CreateRenderItem(
        int32_t rowspan, int32_t colspan, int32_t index, const RefPtr<PipelineContext>& contex);
    static RefPtr<Component> CreateComponent(FlexDirection direction, int32_t cols);
    static RefPtr<Component> CreateComponentItem(const int32_t& itemMainSpan, const int32_t& itemCrossSpan);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEST_UNITTEST_WATER_FLOW_WARER_FLOW_TEST_UTILS_H
