/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class SystemOps {
    public static StartFrame(): KPointer {
        return SystemOps.StartFrame_serialize()
    }
    public static EndFrame(root: KPointer): void {
        const root_casted = root as (KPointer)
        SystemOps.EndFrame_serialize(root_casted)
        return
    }
    public static syncInstanceId(instanceId: int32): void {
        const instanceId_casted = instanceId as (int32)
        SystemOps.syncInstanceId_serialize(instanceId_casted)
        return
    }
    public static restoreInstanceId(): void {
        SystemOps.restoreInstanceId_serialize()
        return
    }
    private static StartFrame_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SystemOps_StartFrame()
        return retval
    }
    private static EndFrame_serialize(root: KPointer): void {
        ArkUIGeneratedNativeModule._SystemOps_EndFrame(root)
    }
    private static syncInstanceId_serialize(instanceId: int32): void {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(instanceId)
    }
    private static restoreInstanceId_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId()
    }
}
