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

import { CaretOffset, RectResult } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class TextContentControllerBaseInternal {
    public static fromPtr(ptr: KPointer): TextContentControllerBase {
        const obj : TextContentControllerBase = new TextContentControllerBase()
        obj.peer = new Finalizable(ptr, TextContentControllerBase.getFinalizer())
        return obj
    }
}
export class TextContentControllerBase implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textcontentcontrollerbase(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextContentControllerBase.ctor_textcontentcontrollerbase()
        this.peer = new Finalizable(ctorPtr, TextContentControllerBase.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextContentControllerBase_getFinalizer()
    }
    public getCaretOffset(): CaretOffset {
        return this.getCaretOffset_serialize()
    }
    public getTextContentRect(): RectResult {
        return this.getTextContentRect_serialize()
    }
    public getTextContentLineCount(): number {
        return this.getTextContentLineCount_serialize()
    }
    private getCaretOffset_serialize(): CaretOffset {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getCaretOffset(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : CaretOffset = retvalDeserializer.readCaretOffset()
        return returnResult
    }
    private getTextContentRect_serialize(): RectResult {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getTextContentRect(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : RectResult = retvalDeserializer.readRectResult()
        return returnResult
    }
    private getTextContentLineCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TextContentControllerBase_getTextContentLineCount(this.peer!.ptr)
        return retval
    }
}
