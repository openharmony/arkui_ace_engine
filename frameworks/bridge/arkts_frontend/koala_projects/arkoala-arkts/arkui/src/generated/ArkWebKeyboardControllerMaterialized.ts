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
export class WebKeyboardControllerInternal {
    public static fromPtr(ptr: KPointer): WebKeyboardController {
        const obj : WebKeyboardController = new WebKeyboardController()
        obj.peer = new Finalizable(ptr, WebKeyboardController.getFinalizer())
        return obj
    }
}
export class WebKeyboardController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webkeyboardcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WebKeyboardController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WebKeyboardController.ctor_webkeyboardcontroller()
        this.peer = new Finalizable(ctorPtr, WebKeyboardController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebKeyboardController_getFinalizer()
    }
    public insertText(text: string): void {
        const text_casted = text as (string)
        this.insertText_serialize(text_casted)
        return
    }
    public deleteForward(length: number): void {
        const length_casted = length as (number)
        this.deleteForward_serialize(length_casted)
        return
    }
    public deleteBackward(length: number): void {
        const length_casted = length as (number)
        this.deleteBackward_serialize(length_casted)
        return
    }
    public sendFunctionKey(key: number): void {
        const key_casted = key as (number)
        this.sendFunctionKey_serialize(key_casted)
        return
    }
    public close(): void {
        this.close_serialize()
        return
    }
    private insertText_serialize(text: string): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_insertText(this.peer!.ptr, text)
    }
    private deleteForward_serialize(length: number): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_deleteForward(this.peer!.ptr, length)
    }
    private deleteBackward_serialize(length: number): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_deleteBackward(this.peer!.ptr, length)
    }
    private sendFunctionKey_serialize(key: number): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_sendFunctionKey(this.peer!.ptr, key)
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._WebKeyboardController_close(this.peer!.ptr)
    }
}
