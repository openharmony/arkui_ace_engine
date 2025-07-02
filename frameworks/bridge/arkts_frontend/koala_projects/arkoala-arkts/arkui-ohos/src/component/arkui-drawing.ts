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

import { Color } from "./enums"
import { BlendMode } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { Rect } from "./../Graphics"
import { PixelMap, PixelMapInternal } from "./arkui-pixelmap"
import { NodeAttach, remember } from "@koalaui/runtime"
export class DrawingColorFilterInternal {
    public static fromPtr(ptr: KPointer): DrawingColorFilter {
        const obj : DrawingColorFilter = new DrawingColorFilter()
        obj.peer = new Finalizable(ptr, DrawingColorFilter.getFinalizer())
        return obj
    }
}
export class DrawingColorFilter implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_drawingcolorfilter(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = DrawingColorFilter.ctor_drawingcolorfilter()
        this.peer = new Finalizable(ctorPtr, DrawingColorFilter.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawingColorFilter_getFinalizer()
    }
    public static createBlendModeColorFilter(color: Color | number, mode: BlendMode): DrawingColorFilter {
        const color_type = runtimeType(color)
        const mode_type = runtimeType(mode)
        if ((TypeChecker.isColor(color)) && (TypeChecker.isBlendMode(mode))) {
            const color_casted = color as (Color)
            const mode_casted = mode as (BlendMode)
            return DrawingColorFilter.createBlendModeColorFilter0_serialize(color_casted, mode_casted)
        }
        if ((RuntimeType.NUMBER == color_type) && (TypeChecker.isBlendMode(mode))) {
            const color_casted = color as (number)
            const mode_casted = mode as (BlendMode)
            return DrawingColorFilter.createBlendModeColorFilter1_serialize(color_casted, mode_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public static createComposeColorFilter(outer: DrawingColorFilter, inner: DrawingColorFilter): DrawingColorFilter {
        const outer_casted = outer as (DrawingColorFilter)
        const inner_casted = inner as (DrawingColorFilter)
        return DrawingColorFilter.createComposeColorFilter_serialize(outer_casted, inner_casted)
    }
    public static createLinearToSRGBGamma(): DrawingColorFilter {
        return DrawingColorFilter.createLinearToSRGBGamma_serialize()
    }
    public static createSRGBGammaToLinear(): DrawingColorFilter {
        return DrawingColorFilter.createSRGBGammaToLinear_serialize()
    }
    public static createLumaColorFilter(): DrawingColorFilter {
        return DrawingColorFilter.createLumaColorFilter_serialize()
    }
    public static createMatrixColorFilter(matrix: Array<number>): DrawingColorFilter {
        const matrix_casted = matrix as (Array<number>)
        return DrawingColorFilter.createMatrixColorFilter_serialize(matrix_casted)
    }
    private static createBlendModeColorFilter0_serialize(color: Color, mode: BlendMode): DrawingColorFilter {
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_createBlendModeColorFilter0(TypeChecker.Color_ToNumeric(color), TypeChecker.BlendMode_ToNumeric(mode))
        const obj : DrawingColorFilter = DrawingColorFilterInternal.fromPtr(retval)
        return obj
    }
    private static createBlendModeColorFilter1_serialize(color: number, mode: BlendMode): DrawingColorFilter {
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_createBlendModeColorFilter1(color, TypeChecker.BlendMode_ToNumeric(mode))
        const obj : DrawingColorFilter = DrawingColorFilterInternal.fromPtr(retval)
        return obj
    }
    private static createComposeColorFilter_serialize(outer: DrawingColorFilter, inner: DrawingColorFilter): DrawingColorFilter {
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_createComposeColorFilter(toPeerPtr(outer), toPeerPtr(inner))
        const obj : DrawingColorFilter = DrawingColorFilterInternal.fromPtr(retval)
        return obj
    }
    private static createLinearToSRGBGamma_serialize(): DrawingColorFilter {
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_createLinearToSRGBGamma()
        const obj : DrawingColorFilter = DrawingColorFilterInternal.fromPtr(retval)
        return obj
    }
    private static createSRGBGammaToLinear_serialize(): DrawingColorFilter {
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_createSRGBGammaToLinear()
        const obj : DrawingColorFilter = DrawingColorFilterInternal.fromPtr(retval)
        return obj
    }
    private static createLumaColorFilter_serialize(): DrawingColorFilter {
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_createLumaColorFilter()
        const obj : DrawingColorFilter = DrawingColorFilterInternal.fromPtr(retval)
        return obj
    }
    private static createMatrixColorFilter_serialize(matrix: Array<number>): DrawingColorFilter {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(matrix.length as int32)
        for (let i = 0; i < matrix.length; i++) {
            const matrix_element : number = matrix[i]
            thisSerializer.writeNumber(matrix_element)
        }
        const retval  = ArkUIGeneratedNativeModule._DrawingColorFilter_createMatrixColorFilter(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : DrawingColorFilter = DrawingColorFilterInternal.fromPtr(retval)
        return obj
    }
}
export class DrawingLatticeInternal {
    public static fromPtr(ptr: KPointer): DrawingLattice {
        const obj : DrawingLattice = new DrawingLattice()
        obj.peer = new Finalizable(ptr, DrawingLattice.getFinalizer())
        return obj
    }
}
export class DrawingLattice implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_drawinglattice(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DrawingLattice_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = DrawingLattice.ctor_drawinglattice()
        this.peer = new Finalizable(ctorPtr, DrawingLattice.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawingLattice_getFinalizer()
    }
    public static createImageLattice(xDivs: Array<number>, yDivs: Array<number>, fXCount: number, fYCount: number, fBounds?: Rect, fRectTypes?: Array<RectType>, fColors?: Array<Color | number>): DrawingLattice {
        const xDivs_casted = xDivs as (Array<number>)
        const yDivs_casted = yDivs as (Array<number>)
        const fXCount_casted = fXCount as (number)
        const fYCount_casted = fYCount as (number)
        const fBounds_casted = fBounds as (Rect | undefined)
        const fRectTypes_casted = fRectTypes as (Array<RectType> | undefined)
        const fColors_casted = fColors as (Array<Color | number> | undefined)
        return DrawingLattice.createImageLattice_serialize(xDivs_casted, yDivs_casted, fXCount_casted, fYCount_casted, fBounds_casted, fRectTypes_casted, fColors_casted)
    }
    private static createImageLattice_serialize(xDivs: Array<number>, yDivs: Array<number>, fXCount: number, fYCount: number, fBounds?: Rect, fRectTypes?: Array<RectType>, fColors?: Array<Color | number>): DrawingLattice {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(xDivs.length as int32)
        for (let i = 0; i < xDivs.length; i++) {
            const xDivs_element : number = xDivs[i]
            thisSerializer.writeNumber(xDivs_element)
        }
        thisSerializer.writeInt32(yDivs.length as int32)
        for (let i = 0; i < yDivs.length; i++) {
            const yDivs_element : number = yDivs[i]
            thisSerializer.writeNumber(yDivs_element)
        }
        let fBounds_type : int32 = RuntimeType.UNDEFINED
        fBounds_type = runtimeType(fBounds)
        thisSerializer.writeInt8(fBounds_type as int32)
        if ((RuntimeType.UNDEFINED) != (fBounds_type)) {
            const fBounds_value  = fBounds!
            thisSerializer.writeRect(fBounds_value)
        }
        let fRectTypes_type : int32 = RuntimeType.UNDEFINED
        fRectTypes_type = runtimeType(fRectTypes)
        thisSerializer.writeInt8(fRectTypes_type as int32)
        if ((RuntimeType.UNDEFINED) != (fRectTypes_type)) {
            const fRectTypes_value  = fRectTypes!
            thisSerializer.writeInt32(fRectTypes_value.length as int32)
            for (let i = 0; i < fRectTypes_value.length; i++) {
                const fRectTypes_value_element : RectType = fRectTypes_value[i]
                thisSerializer.writeInt32(TypeChecker.RectType_ToNumeric(fRectTypes_value_element))
            }
        }
        let fColors_type : int32 = RuntimeType.UNDEFINED
        fColors_type = runtimeType(fColors)
        thisSerializer.writeInt8(fColors_type as int32)
        if ((RuntimeType.UNDEFINED) != (fColors_type)) {
            const fColors_value  = fColors!
            thisSerializer.writeInt32(fColors_value.length as int32)
            for (let i = 0; i < fColors_value.length; i++) {
                const fColors_value_element : Color | number = fColors_value[i]
                let fColors_value_element_type : int32 = RuntimeType.UNDEFINED
                fColors_value_element_type = runtimeType(fColors_value_element)
                if (TypeChecker.isColor(fColors_value_element)) {
                    thisSerializer.writeInt8(0 as int32)
                    const fColors_value_element_0  = fColors_value_element as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(fColors_value_element_0))
                }
                else if (RuntimeType.NUMBER == fColors_value_element_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const fColors_value_element_1  = fColors_value_element as number
                    thisSerializer.writeNumber(fColors_value_element_1)
                }
            }
        }
        const retval  = ArkUIGeneratedNativeModule._DrawingLattice_createImageLattice(thisSerializer.asBuffer(), thisSerializer.length(), fXCount, fYCount)
        thisSerializer.release()
        const obj : DrawingLattice = DrawingLatticeInternal.fromPtr(retval)
        return obj
    }
}
export class DrawingCanvasInternal {
    public static fromPtr(ptr: KPointer): DrawingCanvas {
        const obj : DrawingCanvas = new DrawingCanvas(undefined)
        obj.peer = new Finalizable(ptr, DrawingCanvas.getFinalizer())
        return obj
    }
}
export class DrawingCanvas implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_drawingcanvas(pixelmap: PixelMap): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DrawingCanvas_ctor(toPeerPtr(pixelmap))
        return retval
    }
    constructor(pixelmap?: PixelMap) {
        if ((pixelmap) !== (undefined))
        {
            const ctorPtr : KPointer = DrawingCanvas.ctor_drawingcanvas((pixelmap)!)
            this.peer = new Finalizable(ctorPtr, DrawingCanvas.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawingCanvas_getFinalizer()
    }
    public drawRect(left: number, top: number, right: number, bottom: number): void {
        const left_casted = left as (number)
        const top_casted = top as (number)
        const right_casted = right as (number)
        const bottom_casted = bottom as (number)
        this.drawRect_serialize(left_casted, top_casted, right_casted, bottom_casted)
        return
    }
    private drawRect_serialize(left: number, top: number, right: number, bottom: number): void {
        ArkUIGeneratedNativeModule._DrawingCanvas_drawRect(this.peer!.ptr, left, top, right, bottom)
    }
}
export enum RectType {
    DEFAULT = 0,
    TRANSPARENT = 1,
    FIXEDCOLOR = 2
}
