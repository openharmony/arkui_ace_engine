#define KOALA_INTEROP_MODULE ArkUINativeModule

#include "common-interop.h"
#include "interop-logging.h"

#include "arkoala_api_generated.h"

const GENERATED_ArkUIExtendedNodeAPI* GetArkUIExtendedNodeAPI();

// TODO: map if multiple pipeline contexts.
static KVMDeferred* currentVsyncDeferred = nullptr;

void vsyncCallback(Ark_PipelineContext context) {
    if (currentVsyncDeferred) {
        currentVsyncDeferred->resolve(currentVsyncDeferred, nullptr, 0);
        currentVsyncDeferred = nullptr;
    }
}

void impl_SetVsyncCallback(Ark_NativePointer pipelineContext) {
    Ark_PipelineContext pipelineContextCast = (Ark_PipelineContext)pipelineContext;
    auto api = GetArkUIExtendedNodeAPI();
    if (api) {
        api->setVsyncCallback(pipelineContextCast, vsyncCallback);
    }
}
KOALA_INTEROP_V1(SetVsyncCallback, Ark_NativePointer)

KVMObjectHandle impl_VSyncAwait(KVMContext vmContext, Ark_NativePointer pipelineContext)
{
    [[maybe_unused]] Ark_PipelineContext pipelineContextCast = (Ark_PipelineContext)pipelineContext;
    KVMObjectHandle result = nullptr;
    KVMDeferred* deferred = CreateDeferred(vmContext, &result);
    if (currentVsyncDeferred) {
        LOGE("%s", "Multiple unresolved vsync deferred");
        currentVsyncDeferred->reject(currentVsyncDeferred, "Wrong");
    }
    currentVsyncDeferred = deferred;
    return result;
}
KOALA_INTEROP_CTX_1(VSyncAwait, KVMObjectHandle, Ark_NativePointer)

void impl_UnblockVsyncWait(Ark_NativePointer pipelineContext)
{
    if (currentVsyncDeferred) {
        currentVsyncDeferred->resolve(currentVsyncDeferred, nullptr, 0);
        currentVsyncDeferred = nullptr;
    }
}
KOALA_INTEROP_V1(UnblockVsyncWait, Ark_NativePointer)

Ark_NativePointer impl_GetPipelineContext(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    auto api = GetArkUIExtendedNodeAPI();
    if (api) {
        return api->getPipelineContext(nodePtrCast);
    }
    return nullptr;
}
KOALA_INTEROP_1(GetPipelineContext, Ark_NativePointer, Ark_NativePointer)
