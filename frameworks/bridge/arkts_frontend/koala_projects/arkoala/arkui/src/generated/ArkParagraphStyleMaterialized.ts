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

import { TextAlign, TextOverflow, WordBreak } from "./ArkEnumsInterfaces"
import { LeadingMarginPlaceholder } from "./ArkRichEditorInterfaces"
import { ParagraphStyleInterface } from "./ArkStyledStringInterfaces"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { Dimension } from "./ArkUnitsInterfaces"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ParagraphStyleInternal {
    public static fromPtr(ptr: KPointer): ParagraphStyle {
        const obj: ParagraphStyle = new ParagraphStyle(undefined)
        obj.peer = new Finalizable(ptr, ParagraphStyle.getFinalizer())
        return obj
    }
}
export class ParagraphStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get textAlign(): TextAlign {
        return this.getTextAlign()
    }
    get textIndent(): number {
        return this.getTextIndent()
    }
    get maxLines(): number {
        return this.getMaxLines()
    }
    get overflow(): TextOverflow {
        return this.getOverflow()
    }
    get wordBreak(): WordBreak {
        return this.getWordBreak()
    }
    get leadingMargin(): number | LeadingMarginPlaceholder {
        throw new Error("Not implemented")
    }
    static ctor_paragraphstyle(value?: ParagraphStyleInterface): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeParagraphStyleInterface(value_value)
        }
        const retval = ArkUIGeneratedNativeModule._ParagraphStyle_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(value?: ParagraphStyleInterface) {
        const ctorPtr: KPointer = ParagraphStyle.ctor_paragraphstyle((value)!)
        this.peer = new Finalizable(ctorPtr, ParagraphStyle.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ParagraphStyle_getFinalizer()
    }
    private getTextAlign(): TextAlign {
        return this.getTextAlign_serialize()
    }
    private getTextIndent(): number {
        return this.getTextIndent_serialize()
    }
    private getMaxLines(): number {
        return this.getMaxLines_serialize()
    }
    private getOverflow(): TextOverflow {
        return this.getOverflow_serialize()
    }
    private getWordBreak(): WordBreak {
        return this.getWordBreak_serialize()
    }
    private getTextAlign_serialize(): TextAlign {
        const retval = ArkUIGeneratedNativeModule._ParagraphStyle_getTextAlign(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getTextIndent_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ParagraphStyle_getTextIndent(this.peer!.ptr)
        return retval
    }
    private getMaxLines_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ParagraphStyle_getMaxLines(this.peer!.ptr)
        return retval
    }
    private getOverflow_serialize(): TextOverflow {
        const retval = ArkUIGeneratedNativeModule._ParagraphStyle_getOverflow(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getWordBreak_serialize(): WordBreak {
        const retval = ArkUIGeneratedNativeModule._ParagraphStyle_getWordBreak(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
