/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_image_span_modifier.h"

#include "core/common/dynamic_module_helper.h"
#include "core/components/image/image_event.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LOAD_ERROR_CODE = 401;
constexpr int32_t IMAGE_LOAD_STATUS_INDEX = 0;
constexpr int32_t IMAGE_WIDTH_INDEX = 1;
constexpr int32_t IMAGE_HEIGHT_INDEX = 2;
constexpr int32_t IMAGE_COMPONENT_WIDTH_INDEX = 3;
constexpr int32_t IMAGE_COMPONENT_HEIGHT_INDEX = 4;
constexpr int32_t IMAGE_CONTENT_OFFSET_X_INDEX = 5;
constexpr int32_t IMAGE_CONTENT_OFFSET_Y_INDEX = 6;
constexpr int32_t IMAGE_CONTENT_WIDTH_INDEX = 7;
constexpr int32_t IMAGE_CONTENT_HEIGHT_INDEX = 8;
} // namespace

namespace NodeModifier {
const ArkUIImageSpanModifier* GetImageSpanModifier()
{
    static const ArkUIImageSpanModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ImageSpan");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIImageSpanModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUIImageSpanModifier* GetCJUIImageSpanModifier()
{
    static const CJUIImageSpanModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ImageSpan");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIImageSpanModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUIImageSpanCustomModifier* GetImageSpanCustomModifier()
{
    static const ArkUIImageSpanCustomModifier* cachedCustomModifier = nullptr;
    if (cachedCustomModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ImageSpan");
        CHECK_NULL_RETURN(module, nullptr);
        cachedCustomModifier = reinterpret_cast<const ArkUIImageSpanCustomModifier*>(module->GetCustomModifier());
    }
    return cachedCustomModifier;
}

void SetImageSpanOnCompleteEvent(ArkUINodeHandle node, void* extraParam)
{
    auto modifier = GetImageSpanModifier();
    CHECK_NULL_VOID(modifier);
    auto onEvent = [node, extraParam](const LoadImageSuccessEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_SPAN_COMPLETE;
        event.componentAsyncEvent.data[IMAGE_LOAD_STATUS_INDEX].i32 = info.GetLoadingStatus();
        event.componentAsyncEvent.data[IMAGE_WIDTH_INDEX].f32 = info.GetWidth();
        event.componentAsyncEvent.data[IMAGE_HEIGHT_INDEX].f32 = info.GetHeight();
        event.componentAsyncEvent.data[IMAGE_COMPONENT_WIDTH_INDEX].f32 = info.GetComponentWidth();
        event.componentAsyncEvent.data[IMAGE_COMPONENT_HEIGHT_INDEX].f32 = info.GetComponentHeight();
        event.componentAsyncEvent.data[IMAGE_CONTENT_OFFSET_X_INDEX].f32 = info.GetContentOffsetX();
        event.componentAsyncEvent.data[IMAGE_CONTENT_OFFSET_Y_INDEX].f32 = info.GetContentOffsetY();
        event.componentAsyncEvent.data[IMAGE_CONTENT_WIDTH_INDEX].f32 = info.GetContentWidth();
        event.componentAsyncEvent.data[IMAGE_CONTENT_HEIGHT_INDEX].f32 = info.GetContentHeight();
        SendArkUISyncEvent(&event);
    };
    modifier->setImageSpanOnComplete(node, reinterpret_cast<void*>(&onEvent));
}

void SetImageSpanOnErrorEvent(ArkUINodeHandle node, void* extraParam)
{
    auto modifier = GetImageSpanModifier();
    CHECK_NULL_VOID(modifier);
    auto onEvent = [node, extraParam](const LoadImageFailEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_SPAN_ERROR;
        event.componentAsyncEvent.data[0].i32 = LOAD_ERROR_CODE;
        SendArkUISyncEvent(&event);
    };
    modifier->setImageSpanOnError(node, reinterpret_cast<void*>(&onEvent));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
