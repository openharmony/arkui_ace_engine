#define KOALA_INTEROP_MODULE TestNativeModule

#include "common-interop.h"
#include "Serializers.h"
#include "arkoala_api_generated.h"
#include "callbacks.h"

const OH_AnyAPI* GetAnyImpl(int kind, int version, std::string* result = nullptr);

static const GENERATED_ArkUIFullNodeAPI* GetFullImpl() {
    return reinterpret_cast<const GENERATED_ArkUIFullNodeAPI*>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_FULL),
        GENERATED_ARKUI_FULL_API_VERSION, nullptr));
}

KNativePointer impl_TestGetManagedCaller(KInt kind) {
    return getManagedCallbackCaller(static_cast<CallbackKind>(kind));
}
KOALA_INTEROP_DIRECT_1(TestGetManagedCaller, KNativePointer, KInt)

KNativePointer impl_TestGetManagedCallerSync(KInt kind) {
    return getManagedCallbackCallerSync(static_cast<CallbackKind>(kind));
}
KOALA_INTEROP_DIRECT_1(TestGetManagedCallerSync, KNativePointer, KInt)

KNativePointer impl_TestGetManagedHolder() {
    return reinterpret_cast<KNativePointer>(holdManagedCallbackResource);
}
KOALA_INTEROP_DIRECT_0(TestGetManagedHolder, KNativePointer)

KNativePointer impl_TestGetManagedReleaser() {
    return reinterpret_cast<KNativePointer>(releaseManagedCallbackResource);
}
KOALA_INTEROP_DIRECT_0(TestGetManagedReleaser, KNativePointer)
