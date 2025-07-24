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

import { TextContentControllerBase, TextContentControllerBaseInternal } from "./ArkTextContentControllerBaseMaterialized"
import { CaretOffset, RectResult, SelectionOptions } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class SearchControllerInternal {
    public static fromPtr(ptr: KPointer): SearchController {
        const obj : SearchController = new SearchController()
        obj.peer = new Finalizable(ptr, SearchController.getFinalizer())
        return obj
    }
}
export class SearchController extends TextContentControllerBase implements MaterializedBase {
    static ctor_searchcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SearchController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = SearchController.ctor_searchcontroller()
        this.peer = new Finalizable(ctorPtr, SearchController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SearchController_getFinalizer()
    }
    public caretPosition(value: number): void {
        const value_casted = value as (number)
        this.caretPosition_serialize(value_casted)
        return
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    private caretPosition_serialize(value: number): void {
        ArkUIGeneratedNativeModule._SearchController_caretPosition(this.peer!.ptr, value)
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._SearchController_stopEditing(this.peer!.ptr)
    }
    private setTextSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._SearchController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
