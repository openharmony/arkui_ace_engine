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

import { ClickEvent, ClickEventInternal } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class EventEmulator {
    public static emitClickEvent(node: KPointer, event: ClickEvent): void {
        const node_casted = node as (KPointer)
        const event_casted = event as (ClickEvent)
        EventEmulator.emitClickEvent_serialize(node_casted, event_casted)
        return
    }
    public static emitTextInputEvent(node: KPointer, text: string): void {
        const node_casted = node as (KPointer)
        const text_casted = text as (string)
        EventEmulator.emitTextInputEvent_serialize(node_casted, text_casted)
        return
    }
    private static emitClickEvent_serialize(node: KPointer, event: ClickEvent): void {
        ArkUIGeneratedNativeModule._EventEmulator_emitClickEvent(node, toPeerPtr(event))
    }
    private static emitTextInputEvent_serialize(node: KPointer, text: string): void {
        ArkUIGeneratedNativeModule._EventEmulator_emitTextInputEvent(node, text)
    }
}
