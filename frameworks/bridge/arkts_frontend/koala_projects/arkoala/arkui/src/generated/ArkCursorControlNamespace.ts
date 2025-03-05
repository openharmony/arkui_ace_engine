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

import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export namespace cursorControl {
    export class GlobalScope_cursorControl_common {
        public static setCursor(value: PointerStyle): void {
            const value_casted = value as (PointerStyle)
            GlobalScope_cursorControl_common.setCursor_serialize(value_casted)
            return
        }
        public static restoreDefault(): void {
            GlobalScope_cursorControl_common.restoreDefault_serialize()
            return
        }
        private static setCursor_serialize(value: PointerStyle): void {
            ArkUIGeneratedNativeModule._GlobalScope_cursorControl_common_setCursor(value)
        }
        private static restoreDefault_serialize(): void {
            ArkUIGeneratedNativeModule._GlobalScope_cursorControl_common_restoreDefault()
        }
    }
}
export namespace cursorControl {
    export function setCursor(value: PointerStyle): void {
        GlobalScope_cursorControl_common.setCursor(value)
    }
    export function restoreDefault(): void {
        GlobalScope_cursorControl_common.restoreDefault()
    }
}
