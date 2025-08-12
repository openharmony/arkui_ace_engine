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

import { PositionWithAffinity, LineMetrics, TextRange, TextBox } from "./ArkTextCommonInterfaces"
import { RectWidthStyle, RectHeightStyle } from "./ArkArkuiExternalInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface LayoutManager {
    getLineCount(): number
    getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity
    getLineMetrics(lineNumber: number): LineMetrics
    getRectsForRange(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox>
}
export class LayoutManagerInternal implements MaterializedBase,LayoutManager {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_layoutmanager(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = LayoutManagerInternal.ctor_layoutmanager()
        this.peer = new Finalizable(ctorPtr, LayoutManagerInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LayoutManager_getFinalizer()
    }
    public getLineCount(): number {
        return this.getLineCount_serialize()
    }
    public getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.getGlyphPositionAtCoordinate_serialize(x_casted, y_casted)
    }
    public getLineMetrics(lineNumber: number): LineMetrics {
        const lineNumber_casted = lineNumber as (number)
        return this.getLineMetrics_serialize(lineNumber_casted)
    }
    public getRectsForRange(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> {
        const range_casted = range as (TextRange)
        const widthStyle_casted = widthStyle as (RectWidthStyle)
        const heightStyle_casted = heightStyle as (RectHeightStyle)
        return this.getRectsForRange_serialize(range_casted, widthStyle_casted, heightStyle_casted)
    }
    private getLineCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getLineCount(this.peer!.ptr)
        return retval
    }
    private getGlyphPositionAtCoordinate_serialize(x: number, y: number): PositionWithAffinity {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getGlyphPositionAtCoordinate(this.peer!.ptr, x, y)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : PositionWithAffinity = retvalDeserializer.readPositionWithAffinity()
        return returnResult
    }
    private getLineMetrics_serialize(lineNumber: number): LineMetrics {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getLineMetrics(this.peer!.ptr, lineNumber)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : LineMetrics = retvalDeserializer.readLineMetrics()
        return returnResult
    }
    private getRectsForRange_serialize(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextRange(range)
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getRectsForRange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), widthStyle.valueOf(), heightStyle.valueOf())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<TextBox> = new Array<TextBox>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readTextBox()
        }
        const returnResult : Array<TextBox> = buffer
        return returnResult
    }
    public static fromPtr(ptr: KPointer): LayoutManagerInternal {
        const obj : LayoutManagerInternal = new LayoutManagerInternal()
        obj.peer = new Finalizable(ptr, LayoutManagerInternal.getFinalizer())
        return obj
    }
}
