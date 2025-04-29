/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/canvas/canvas_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/custom_paint/custom_paint_component.h"

namespace OHOS::Ace::Framework {
RefPtr<AceType> CanvasModelImpl::Create()
{
    auto paintChild = AceType::MakeRefPtr<OHOS::Ace::CustomPaintComponent>();
    if (!paintChild) {
        return nullptr;
    }
    ViewStackProcessor::GetInstance()->ClaimElementId(paintChild);
    ViewStackProcessor::GetInstance()->Push(paintChild);
    return AceType::DynamicCast<OHOS::Ace::CustomPaintComponent>(paintChild)->GetTaskPool();
}

void CanvasModelImpl::SetOnReady(std::function<void(uint32_t)>&& readyEvent)
{
    auto container = Container::Current();
    if (!container) {
        LOGE("No container");
        return;
    }
    auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        LOGE("No PipelineContext");
        return;
    }
    auto component = AceType::DynamicCast<CustomPaintComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGE("No CustomPaintComponent");
        return;
    }

    auto elmtId = component->GetElementId();
    auto fun = readyEvent;
    auto onReadEvent = [fun, elmtId]() { fun(elmtId); };

    auto onReadyEvent = EventMarker(std::move(onReadEvent));

    component->SetOnReadyEvent(onReadyEvent, context);
}
} // namespace OHOS::Ace::Framework
