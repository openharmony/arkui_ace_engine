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
export class WebContextMenuResultInternal {
    public static fromPtr(ptr: KPointer): WebContextMenuResult {
        const obj: WebContextMenuResult = new WebContextMenuResult()
        obj.peer = new Finalizable(ptr, WebContextMenuResult.getFinalizer())
        return obj
    }
}
export class WebContextMenuResult implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_webcontextmenuresult(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WebContextMenuResult_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = WebContextMenuResult.ctor_webcontextmenuresult()
        this.peer = new Finalizable(ctorPtr, WebContextMenuResult.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WebContextMenuResult_getFinalizer()
    }
    public closeContextMenu(): void {
        this?.closeContextMenu_serialize()
        return
    }
    public copyImage(): void {
        this?.copyImage_serialize()
        return
    }
    public copy(): void {
        this?.copy_serialize()
        return
    }
    public paste(): void {
        this?.paste_serialize()
        return
    }
    public cut(): void {
        this?.cut_serialize()
        return
    }
    public selectAll(): void {
        this?.selectAll_serialize()
        return
    }
    private closeContextMenu_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_closeContextMenu(this.peer!.ptr)
    }
    private copyImage_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_copyImage(this.peer!.ptr)
    }
    private copy_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_copy(this.peer!.ptr)
    }
    private paste_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_paste(this.peer!.ptr)
    }
    private cut_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_cut(this.peer!.ptr)
    }
    private selectAll_serialize(): void {
        ArkUIGeneratedNativeModule._WebContextMenuResult_selectAll(this.peer!.ptr)
    }
}
