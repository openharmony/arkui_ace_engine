/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/log/ace_trace.h"
#include "core/common/container.h"
#include "core/components_ng/base/ui_node.h"

#include <iostream>

namespace OHOS::Ace {

void AceTraceBegin(const char* name) {}

void AceTraceEnd() {}

void AceTraceBeginCommercial(const char* name) {}

void AceTraceEndCommercial() {}

void AceAsyncTraceBegin(int32_t taskId, const char* name, bool isAnimationTrace) {}

void AceAsyncTraceEnd(int32_t taskId, const char* name, bool isAnimationTrace) {}

void AceAsyncTraceBeginCommercial(int32_t taskId, const char* name, bool isAnimationTrace) {}

void AceAsyncTraceEndCommercial(int32_t taskId, const char* name, bool isAnimationTrace) {}

void AceCountTrace(const char* key, int32_t count) {}

bool AceTraceBeginWithArgv(const char* /* format */, va_list /* args */)
{
    return false;
}

bool AceTraceBeginWithArgs(const char* /* format */, ...)
{
    return false;
}

void AceCountTraceWidthArgs(int32_t count, const char* format, ...) {}

AceScopedTrace::AceScopedTrace(const char* /* format */, ...) {}

AceScopedTrace::~AceScopedTrace() = default;

AceScopedTraceCommercial::AceScopedTraceCommercial(const char* format, ...) {}

AceScopedTraceCommercial::~AceScopedTraceCommercial() {}

AceScopedTraceFlag::AceScopedTraceFlag(bool /* flag */, const char* /* format */, ...) {}

AceScopedTraceFlag::~AceScopedTraceFlag() {}

std::string ACE_EXPORT AceAsyncTraceBeginWithArgv(int32_t /* taskId */, const char* /* format */, va_list /* args */)
{
    return {};
}

std::string ACE_EXPORT AceAsyncTraceBeginWithArgs(int32_t /* taskId */, char* /* format */, ...)
{
    return {};
}

std::atomic<std::int32_t> AceAsyncScopedTrace::id_ = 0;

AceAsyncScopedTrace::AceAsyncScopedTrace(const char* /* format */, ...) {}

AceAsyncScopedTrace::~AceAsyncScopedTrace() = default;

void AceSetResTraceId(uint32_t traceType, uint64_t traceId, uint32_t* pOldTraceType, uint64_t* pOldTraceId)
{
    thread_local uint32_t gTraceType;
    thread_local uint64_t gTraceId;
    *pOldTraceType = gTraceType;
    *pOldTraceId = gTraceId;
    gTraceType = traceType;
    gTraceId = traceId;
    std::clog << __func__ << ": traceType=" << traceType << " traceId=" << traceId
              << " oldTraceType=" << (*pOldTraceType) << " oldTraceId=" << (*pOldTraceId) << std::endl;
}

ResTracer::ResTracer(uint32_t traceType, uint64_t traceId)
{
    AceSetResTraceId(traceType, traceId, &traceType_, &traceId_);
}

ResTracer::~ResTracer()
{
    uint32_t traceType;
    uint64_t traceId;
    AceSetResTraceId(traceType_, traceId_, &traceType, &traceId);
}

ContainerTracer::ContainerTracer(const Container* container)
    : ContainerTracer(container ? container->GetInstanceId() : INSTANCE_ID_UNDEFINED)
{}

ContainerTracer::ContainerTracer()
    : ContainerTracer(Container::CurrentId())
{}

UINodeTracer::UINodeTracer(const NG::UINode* uiNode)
    : UINodeTracer(uiNode ? uiNode->GetId() : ElementRegister::UndefinedElementId)
{
    std::clog << "UINodeTracer: nodeTag=" << (uiNode ? uiNode->GetTag() : "")
              << " nodeId=" << (uiNode ? uiNode->GetId() : ElementRegister::UndefinedElementId) << std::endl;
}
} // namespace OHOS::Ace
