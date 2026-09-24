/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/page_text_collector.h"

#include <cmath>
#include <iterator>
#include <new>

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/page_text_json.h"
#include "core/components_ng/pattern/page_translate/page_translate_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/native/native_type.h"

namespace OHOS::Ace::NG {
namespace {
#ifndef CROSS_PLATFORM
bool AppendCarrier(const RefPtr<FrameNode>& frame, const RefPtr<PageTranslateNode>& carrier,
    PageTextJson& json, bool& first)
{
    const auto text = carrier->GetPageTranslateTextForReport();
    if (text.empty()) {
        return true;
    }
    // Match GetArkUIPageTranslateText's ReportTranslateTextFrameNode eligibility.
    const auto visibleRect = frame->GetTransformRectRelativeToWindowOnlyVisible();
    if (LessOrEqual(visibleRect.Width(), 0.0f) || LessOrEqual(visibleRect.Height(), 0.0f)) {
        return true;
    }
    auto offset = frame->GetPaintRectGlobalOffsetWithTranslate(false, true).first;
    const auto& rect = frame->GetGeometryNode()->GetFrameRect();
    const float values[] = { offset.GetX(), offset.GetY(), rect.Width(), rect.Height() };
    for (auto value : values) {
        if (!std::isfinite(value)) {
            return json.Fail("Page text geometry contains a non-finite value.");
        }
    }
    if (rect.Width() < 0 || rect.Height() < 0) {
        return json.Fail("Page text geometry has a negative size.");
    }
    if (!first && !json.Append(",")) {
        return false;
    }
    first = false;
    if (!json.Append("{\"id\":") || !json.Number(frame->GetId()) || !json.Append(",\"rect\":[")) {
        return false;
    }
    for (size_t i = 0; i < std::size(values); ++i) {
        if ((i && !json.Append(",")) || !json.Number(values[i])) {
            return false;
        }
    }
    return json.Append("],\"content\":") && json.String(text) && json.Append("}");
}

#endif
} // namespace

int32_t CollectPageText(int32_t instanceId, char** data, uint32_t* size, const char** reason)
{
    *data = nullptr;
    *size = 0;
    auto container = Container::GetContainer(instanceId);
    // Container lookup can redirect plugin IDs to their parent; this API must not.
    if (container && container->GetInstanceId() != instanceId) {
        container.Reset();
    }
    auto pipeline = container ? AceType::DynamicCast<PipelineContext>(container->GetPipelineContext()) : nullptr;
    if (!pipeline || pipeline->IsDestroyed()) {
        *reason = "UI context is invalid or destroyed.";
        return ARKUI_ERROR_CODE_UI_CONTEXT_INVALID;
    }
    auto executor = container->GetTaskExecutor();
    if (!executor || !executor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        LOGF_ABORT("OH_ArkUI_NativeModule_UIAgentGetPageText must run on the target UI thread.");
    }
    ContainerScope scope(instanceId);
    *reason = "Page text serialization, allocation or size check failed.";
#ifdef __cpp_exceptions
    try {
#endif
        PageTextJson json;
        bool success = json.Append("{\"texts\":[");
#ifndef CROSS_PLATFORM
        bool first = true;
        auto manager = pipeline->GetUiTranslateManagerImpl();
        if (manager && success) {
            // Reuse the translation registry without starting reports or changing session state.
            manager->ForEachArkUITranslateFrameNode([&](const WeakPtr<FrameNode>& node) {
                if (!success) {
                    return;
                }
                auto frame = node.Upgrade();
                CHECK_NULL_VOID(frame);
                auto carrier = AceType::DynamicCast<PageTranslateNode>(frame->GetPattern());
                CHECK_NULL_VOID(carrier);
                success = AppendCarrier(frame, carrier, json, first);
            });
        }
#endif
        if (!success || !json.Append("]}")) {
            *reason = json.GetError();
            return ARKUI_ERROR_CODE_INTERNAL_ERROR;
        }
        *data = json.Release(*size);
        return ARKUI_ERROR_CODE_NO_ERROR;
#ifdef __cpp_exceptions
    } catch (const std::bad_alloc&) {
        return ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
#endif
}
} // namespace OHOS::Ace::NG
