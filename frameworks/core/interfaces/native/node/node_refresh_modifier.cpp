/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_refresh_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/node/node_api.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace::NG {

namespace NodeModifier {

const ArkUIRefreshModifier* GetRefreshModifier()
{
    static const ArkUIRefreshModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Refresh");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIRefreshModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUIRefreshModifier* GetCJUIRefreshModifier()
{
    static const CJUIRefreshModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Refresh");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIRefreshModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

void SetRefreshOnStateChange(ArkUINodeHandle node, void* extraParam)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->setRefreshOnStateChangeCallback);
    
    std::function<void(const int32_t)> onEvent = [node, extraParam](const int32_t value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_STATE_CHANGE;
        event.componentAsyncEvent.data[0].i32 = value;
        SendArkUISyncEvent(&event);
    };
    modifier->setRefreshOnStateChangeCallback(node, reinterpret_cast<void*>(&onEvent));
}

void SetOnRefreshing(ArkUINodeHandle node, void* extraParam)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->setOnRefreshingCallback);
    
    std::function<void()> onEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_REFRESHING;
        SendArkUISyncEvent(&event);
    };
    modifier->setOnRefreshingCallback(node, reinterpret_cast<void*>(&onEvent));
}

void SetRefreshOnOffsetChange(ArkUINodeHandle node, void* extraParam)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->setRefreshOnOffsetChangeCallback);
    
    std::function<void(const float)> onEvent = [node, extraParam](const float value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_ON_OFFSET_CHANGE;
        event.componentAsyncEvent.data[0].f32 = value;
        SendArkUISyncEvent(&event);
    };
    modifier->setRefreshOnOffsetChangeCallback(node, reinterpret_cast<void*>(&onEvent));
}

void SetRefreshChangeEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->setOnChangeEvent);
    
    std::function<void(const std::string&)> onEvent = [node, extraParam](const std::string& value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_CHANGE_EVENT;
        bool newValue = value == "true";
        event.componentAsyncEvent.data[0].u32 = newValue;
        SendArkUISyncEvent(&event);
    };
    modifier->setOnChangeEvent(node, reinterpret_cast<void*>(&onEvent));
}

void ResetRefreshOnStateChange(ArkUINodeHandle node)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->resetRefreshOnStateChangeCallback);
    modifier->resetRefreshOnStateChangeCallback(node);
}

void ResetOnRefreshing(ArkUINodeHandle node)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->resetOnRefreshingCallback);
    modifier->resetOnRefreshingCallback(node);
}

void ResetRefreshOnOffsetChange(ArkUINodeHandle node)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->resetRefreshOnOffsetChangeCallback);
    modifier->resetRefreshOnOffsetChangeCallback(node);
}

void ResetRefreshChangeEvent(ArkUINodeHandle node)
{
    auto* modifier = GetRefreshModifier();
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(modifier->resetOnChangeEvent);
    modifier->resetOnChangeEvent(node);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
