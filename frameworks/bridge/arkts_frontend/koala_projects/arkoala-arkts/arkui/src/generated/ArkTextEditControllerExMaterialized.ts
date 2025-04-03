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

import { TextBaseController, TextBaseControllerInternal } from "./ArkTextBaseControllerMaterialized"
import { SelectionOptions } from "./ArkCommonInterfaces"
import { LayoutManager, LayoutManagerInternal } from "./ArkLayoutManagerMaterialized"
import { PreviewText } from "./ArkTextCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface TextEditControllerEx {
    isEditing(): boolean
    stopEditing(): void
    setCaretOffset(offset: number): boolean
    getCaretOffset(): number
    getPreviewText(): PreviewText
}
export class TextEditControllerExInternal extends TextBaseControllerInternal implements MaterializedBase,TextEditControllerEx {
    static ctor_texteditcontrollerex(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TextEditControllerExInternal.ctor_texteditcontrollerex()
        this.peer = new Finalizable(ctorPtr, TextEditControllerExInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextEditControllerEx_getFinalizer()
    }
    public isEditing(): boolean {
        return this.isEditing_serialize()
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setCaretOffset(offset: number): boolean {
        const offset_casted = offset as (number)
        return this.setCaretOffset_serialize(offset_casted)
    }
    public getCaretOffset(): number {
        return this.getCaretOffset_serialize()
    }
    public getPreviewText(): PreviewText {
        return this.getPreviewText_serialize()
    }
    private isEditing_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_isEditing(this.peer!.ptr)
        return retval
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextEditControllerEx_stopEditing(this.peer!.ptr)
    }
    private setCaretOffset_serialize(offset: number): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_setCaretOffset(this.peer!.ptr, offset)
        return retval
    }
    private getCaretOffset_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_getCaretOffset(this.peer!.ptr)
        return retval
    }
    private getPreviewText_serialize(): PreviewText {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_getPreviewText(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : PreviewText = retvalDeserializer.readPreviewText()
        return returnResult
    }
    public static fromPtr(ptr: KPointer): TextEditControllerExInternal {
        const obj : TextEditControllerExInternal = new TextEditControllerExInternal()
        obj.peer = new Finalizable(ptr, TextEditControllerExInternal.getFinalizer())
        return obj
    }
}
