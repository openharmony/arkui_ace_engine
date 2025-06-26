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
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
export class IUIContext {
    public static freezeUINode(id: string | number, isFrozen: boolean): void {
        const id_type = runtimeType(id)
        const isFrozen_type = runtimeType(isFrozen)
        if (RuntimeType.STRING == id_type) {
            const id_casted = id as (string)
            const isFrozen_casted = isFrozen as (boolean)
            IUIContext.freezeUINode0_serialize(id_casted, isFrozen_casted)
            return
        }
        if (RuntimeType.NUMBER == id_type) {
            const id_casted = id as (number)
            const isFrozen_casted = isFrozen as (boolean)
            IUIContext.freezeUINode1_serialize(id_casted, isFrozen_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    private static freezeUINode0_serialize(id: string, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode0(id, isFrozen ? 1 : 0)
    }
    private static freezeUINode1_serialize(id: number, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode1(id, isFrozen ? 1 : 0)
    }
}
