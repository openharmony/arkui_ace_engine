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

#define KOALA_INTEROP_MODULE TestNativeModule

#include "common-interop.h"
#include "Serializers.h"
#include "arkoala_api_generated.h"

const OH_AnyAPI* GetAnyImpl(int kind, int version, std::string* result = nullptr);

static const GENERATED_ArkUIFullNodeAPI* GetFullImpl() {
    return reinterpret_cast<const GENERATED_ArkUIFullNodeAPI*>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_FULL),
        GENERATED_ARKUI_FULL_API_VERSION));
}

KNativePointer impl_TestGetManagedHolder() {
    return reinterpret_cast<KNativePointer>(holdManagedCallbackResource);
}
KOALA_INTEROP_0(TestGetManagedHolder, KNativePointer)

KNativePointer impl_TestGetManagedReleaser() {
    return reinterpret_cast<KNativePointer>(releaseManagedCallbackResource);
}
KOALA_INTEROP_0(TestGetManagedReleaser, KNativePointer)

KNativePointer impl_TestGetManagedCaller(KInt kind) {
    return getManagedCallbackCaller(static_cast<CallbackKind>(kind));
}
KOALA_INTEROP_1(TestGetManagedCaller, KNativePointer, KInt)
KNativePointer impl_TestGetManagedCallerSync(KInt kind) {
    return getManagedCallbackCallerSync(static_cast<CallbackKind>(kind));
}
KOALA_INTEROP_1(TestGetManagedCallerSync, KNativePointer, KInt)
