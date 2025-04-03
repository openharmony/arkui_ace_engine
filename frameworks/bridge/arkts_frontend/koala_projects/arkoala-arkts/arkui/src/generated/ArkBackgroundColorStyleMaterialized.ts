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

import { TextBackgroundStyle } from "./ArkSpanInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class BackgroundColorStyleInternal {
    public static fromPtr(ptr: KPointer): BackgroundColorStyle {
        const obj : BackgroundColorStyle = new BackgroundColorStyle(undefined)
        obj.peer = new Finalizable(ptr, BackgroundColorStyle.getFinalizer())
        return obj
    }
}
export class BackgroundColorStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get textBackgroundStyle(): TextBackgroundStyle {
        throw new Error("Not implemented")
    }
    static ctor_backgroundcolorstyle(textBackgroundStyle: TextBackgroundStyle): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextBackgroundStyle(textBackgroundStyle)
        const retval  = ArkUIGeneratedNativeModule._BackgroundColorStyle_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(textBackgroundStyle?: TextBackgroundStyle) {
        if ((textBackgroundStyle) !== (undefined))
        {
            const ctorPtr : KPointer = BackgroundColorStyle.ctor_backgroundcolorstyle((textBackgroundStyle)!)
            this.peer = new Finalizable(ctorPtr, BackgroundColorStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BackgroundColorStyle_getFinalizer()
    }
    private getTextBackgroundStyle(): TextBackgroundStyle {
        return this.getTextBackgroundStyle_serialize()
    }
    private getTextBackgroundStyle_serialize(): TextBackgroundStyle {
        const retval  = ArkUIGeneratedNativeModule._BackgroundColorStyle_getTextBackgroundStyle(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : TextBackgroundStyle = retvalDeserializer.readTextBackgroundStyle()
        return returnResult
    }
}
