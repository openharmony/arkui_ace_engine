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

import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureRecognizerState } from "./ArkGestureInterfaces"
import { EventTargetInfo, EventTargetInfoInternal } from "./ArkEventTargetInfoMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class GestureRecognizerInternal {
    public static fromPtr(ptr: KPointer): GestureRecognizer {
        const obj : GestureRecognizer = new GestureRecognizer()
        obj.peer = new Finalizable(ptr, GestureRecognizer.getFinalizer())
        return obj
    }
}
export class GestureRecognizer implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_gesturerecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = GestureRecognizer.ctor_gesturerecognizer()
        this.peer = new Finalizable(ctorPtr, GestureRecognizer.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureRecognizer_getFinalizer()
    }
    public getTag(): string {
        return this.getTag_serialize()
    }
    public getType(): GestureControl.GestureType {
        return this.getType_serialize()
    }
    public isBuiltIn(): boolean {
        return this.isBuiltIn_serialize()
    }
    public setEnabled(isEnabled: boolean): void {
        const isEnabled_casted = isEnabled as (boolean)
        this.setEnabled_serialize(isEnabled_casted)
        return
    }
    public isEnabled(): boolean {
        return this.isEnabled_serialize()
    }
    public getState(): GestureRecognizerState {
        return this.getState_serialize()
    }
    public getEventTargetInfo(): EventTargetInfo {
        return this.getEventTargetInfo_serialize()
    }
    public isValid(): boolean {
        return this.isValid_serialize()
    }
    private getTag_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getTag(this.peer!.ptr)
        return retval
    }
    private getType_serialize(): GestureControl.GestureType {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private isBuiltIn_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isBuiltIn(this.peer!.ptr)
        return retval
    }
    private setEnabled_serialize(isEnabled: boolean): void {
        ArkUIGeneratedNativeModule._GestureRecognizer_setEnabled(this.peer!.ptr, isEnabled ? 1 : 0)
    }
    private isEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isEnabled(this.peer!.ptr)
        return retval
    }
    private getState_serialize(): GestureRecognizerState {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getState(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getEventTargetInfo_serialize(): EventTargetInfo {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_getEventTargetInfo(this.peer!.ptr)
        const obj : EventTargetInfo = EventTargetInfoInternal.fromPtr(retval)
        return obj
    }
    private isValid_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureRecognizer_isValid(this.peer!.ptr)
        return retval
    }
}
