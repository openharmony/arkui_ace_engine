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

import { ResourceColor, ResourceStr } from "./ArkUnitsInterfaces"
import { FontStyle, Color, FontWeight } from "./ArkEnumsInterfaces"
import { TextStyleInterface } from "./ArkStyledStringInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class TextStyle_styled_stringInternal {
    public static fromPtr(ptr: KPointer): TextStyle_styled_string {
        const obj: TextStyle_styled_string = new TextStyle_styled_string(undefined)
        obj.peer = new Finalizable(ptr, TextStyle_styled_string.getFinalizer())
        return obj
    }
}
export class TextStyle_styled_string implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get fontColor(): ResourceColor {
        throw new Error("Not implemented")
    }
    get fontFamily(): string {
        return this.getFontFamily()
    }
    get fontSize(): number {
        return this.getFontSize()
    }
    get fontWeight(): number {
        return this.getFontWeight()
    }
    get fontStyle(): FontStyle {
        return this.getFontStyle()
    }
    static ctor_textstyle_styled_string(value?: TextStyleInterface): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeTextStyleInterface(value_value)
        }
        const retval = ArkUIGeneratedNativeModule._TextStyle_styled_string_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(value?: TextStyleInterface) {
        const ctorPtr: KPointer = TextStyle_styled_string.ctor_textstyle_styled_string((value)!)
        this.peer = new Finalizable(ctorPtr, TextStyle_styled_string.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextStyle_styled_string_getFinalizer()
    }
    private getFontFamily(): string {
        return this.getFontFamily_serialize()
    }
    private getFontSize(): number {
        return this.getFontSize_serialize()
    }
    private getFontWeight(): number {
        return this.getFontWeight_serialize()
    }
    private getFontStyle(): FontStyle {
        return this.getFontStyle_serialize()
    }
    private getFontFamily_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontFamily(this.peer!.ptr)
        return retval
    }
    private getFontSize_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontSize(this.peer!.ptr)
        return retval
    }
    private getFontWeight_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontWeight(this.peer!.ptr)
        return retval
    }
    private getFontStyle_serialize(): FontStyle {
        const retval = ArkUIGeneratedNativeModule._TextStyle_styled_string_getFontStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
