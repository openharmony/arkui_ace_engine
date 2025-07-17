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

#define KOALA_INTEROP_MODULE ArkUINativeModule

#include <string>
#include <atomic>
#include "common-interop.h"
#include "interop-logging.h"

#include "arkoala_api_generated.h"

// Improve: replace to OH_AnyAPI
const Ark_AnyAPI* GetAnyImpl(int kind, int version, std::string* result);

static const GENERATED_ArkUIExtendedNodeAPI* GetArkUIExtendedNodeAPI() {
    return reinterpret_cast<const GENERATED_ArkUIExtendedNodeAPI*>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_EXTENDED),
        GENERATED_ARKUI_EXTENDED_NODE_API_VERSION, nullptr));
}

// Improve: concurrent/locked map if multiple pipeline contexts.
static std::atomic<KVMDeferred*> currentVsyncDeferred(nullptr);

static KVMDeferred* takeCurrent(Ark_NativePointer pipelineContext) {
    KVMDeferred* current;
    do {
        current = currentVsyncDeferred.load();
    } while (!currentVsyncDeferred.compare_exchange_strong(current, nullptr));
    return current;
}

void vsyncCallback(Ark_PipelineContext context) {
    auto current = takeCurrent(context);
    if (current)
        current->resolve(current, nullptr, 0);
}

void impl_SetVsyncCallback(Ark_NativePointer pipelineContext) {
    Ark_PipelineContext pipelineContextCast = (Ark_PipelineContext) pipelineContext;
    GetArkUIExtendedNodeAPI()->setVsyncCallback(pipelineContextCast, vsyncCallback);
}
KOALA_INTEROP_V1(SetVsyncCallback, Ark_NativePointer)

KVMObjectHandle impl_VSyncAwait(KVMContext vmContext, Ark_NativePointer pipelineContext) {
    KVMObjectHandle result = nullptr;
    auto* current = takeCurrent(pipelineContext);
    if (current) {
        LOGE("%s", "Multiple unresolved vsync deferred");
        current->reject(current, "Wrong");
    }
    auto next = CreateDeferred(vmContext, &result);
    KVMDeferred* null = nullptr;
    while (!currentVsyncDeferred.compare_exchange_strong(null, next)) {}
    return result;
}
KOALA_INTEROP_CTX_1(VSyncAwait, KVMObjectHandle, Ark_NativePointer)

void impl_UnblockVsyncWait(Ark_NativePointer pipelineContext) {
    auto current = takeCurrent(pipelineContext);
    if (current) current->resolve(current, nullptr, 0);
}
KOALA_INTEROP_V1(UnblockVsyncWait, Ark_NativePointer)

Ark_NativePointer impl_GetPipelineContext(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIExtendedNodeAPI()->getPipelineContext(nodePtrCast);
}
KOALA_INTEROP_1(GetPipelineContext, Ark_NativePointer, Ark_NativePointer)
