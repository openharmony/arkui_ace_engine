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

import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface SubmitEvent {
    text: string
    keepEditableState(): void
}
export class SubmitEventInternal implements MaterializedBase,SubmitEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get text(): string {
        return this.getText()
    }
    set text(text: string) {
        this.setText(text)
    }
    static ctor_submitevent(): KPointer {
        const retval = ArkUIGeneratedNativeModule._SubmitEvent_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = SubmitEventInternal.ctor_submitevent()
        this.peer = new Finalizable(ctorPtr, SubmitEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SubmitEvent_getFinalizer()
    }
    public keepEditableState(): void {
        this?.keepEditableState_serialize()
        return
    }
    private getText(): string {
        return this.getText_serialize()
    }
    private setText(text: string): void {
        const text_casted = text as (string)
        this?.setText_serialize(text_casted)
        return
    }
    private keepEditableState_serialize(): void {
        ArkUIGeneratedNativeModule._SubmitEvent_keepEditableState(this.peer!.ptr)
    }
    private getText_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._SubmitEvent_getText(this.peer!.ptr)
        return retval
    }
    private setText_serialize(text: string): void {
        ArkUIGeneratedNativeModule._SubmitEvent_setText(this.peer!.ptr, text)
    }
    public static fromPtr(ptr: KPointer): SubmitEventInternal {
        const obj: SubmitEventInternal = new SubmitEventInternal()
        obj.peer = new Finalizable(ptr, SubmitEventInternal.getFinalizer())
        return obj
    }
}
