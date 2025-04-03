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

import { TextDecorationType, TextDecorationStyle, Color } from "./ArkEnumsInterfaces"
import { ResourceColor } from "./ArkUnitsInterfaces"
import { DecorationStyleInterface } from "./ArkStyledStringInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class DecorationStyleInternal {
    public static fromPtr(ptr: KPointer): DecorationStyle {
        const obj : DecorationStyle = new DecorationStyle(undefined)
        obj.peer = new Finalizable(ptr, DecorationStyle.getFinalizer())
        return obj
    }
}
export class DecorationStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get type(): TextDecorationType {
        return this.getType()
    }
    get color(): ResourceColor | undefined {
        throw new Error("Not implemented")
    }
    get style(): TextDecorationStyle | undefined {
        return this.getStyle()
    }
    static ctor_decorationstyle(value: DecorationStyleInterface): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDecorationStyleInterface(value)
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(value?: DecorationStyleInterface) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = DecorationStyle.ctor_decorationstyle((value)!)
            this.peer = new Finalizable(ctorPtr, DecorationStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DecorationStyle_getFinalizer()
    }
    private getType(): TextDecorationType {
        return this.getType_serialize()
    }
    private getColor(): ResourceColor {
        return this.getColor_serialize()
    }
    private getStyle(): TextDecorationStyle {
        return this.getStyle_serialize()
    }
    private getType_serialize(): TextDecorationType {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getType(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getColor_serialize(): ResourceColor {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getColor(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getStyle_serialize(): TextDecorationStyle {
        const retval  = ArkUIGeneratedNativeModule._DecorationStyle_getStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
