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

import { SelectionOptions } from "./ArkCommonInterfaces"
import { LayoutManager, LayoutManagerInternal } from "./ArkLayoutManagerMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface TextBaseController {
    setSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void
    closeSelectionMenu(): void
    getLayoutManager(): LayoutManager
}
export class TextBaseControllerInternal implements MaterializedBase,TextBaseController {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textbasecontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextBaseController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextBaseControllerInternal.ctor_textbasecontroller()
        this.peer = new Finalizable(ctorPtr, TextBaseControllerInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextBaseController_getFinalizer()
    }
    public setSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public closeSelectionMenu(): void {
        this.closeSelectionMenu_serialize()
        return
    }
    public getLayoutManager(): LayoutManager {
        return this.getLayoutManager_serialize()
    }
    private setSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextBaseController_setSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextBaseController_closeSelectionMenu(this.peer!.ptr)
    }
    private getLayoutManager_serialize(): LayoutManager {
        const retval  = ArkUIGeneratedNativeModule._TextBaseController_getLayoutManager(this.peer!.ptr)
        const obj : LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): TextBaseControllerInternal {
        const obj : TextBaseControllerInternal = new TextBaseControllerInternal()
        obj.peer = new Finalizable(ptr, TextBaseControllerInternal.getFinalizer())
        return obj
    }
}
