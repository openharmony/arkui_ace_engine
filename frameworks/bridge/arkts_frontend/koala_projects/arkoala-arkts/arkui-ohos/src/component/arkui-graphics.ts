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

import { Resource } from "global/resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { DrawingCanvas } from "./arkui-drawing"
import { Dimension } from "./units"
export class ShapeMaskInternal {
    public static fromPtr(ptr: KPointer): ShapeMask {
        const obj : ShapeMask = new ShapeMask()
        obj.peer = new Finalizable(ptr, ShapeMask.getFinalizer())
        return obj
    }
}
export class ShapeMask implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get fillColor(): number {
        return this.getFillColor()
    }
    set fillColor(fillColor: number) {
        this.setFillColor(fillColor)
    }
    get strokeColor(): number {
        return this.getStrokeColor()
    }
    set strokeColor(strokeColor: number) {
        this.setStrokeColor(strokeColor)
    }
    get strokeWidth(): number {
        return this.getStrokeWidth()
    }
    set strokeWidth(strokeWidth: number) {
        this.setStrokeWidth(strokeWidth)
    }
    static ctor_shapemask(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ShapeMask.ctor_shapemask()
        this.peer = new Finalizable(ctorPtr, ShapeMask.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ShapeMask_getFinalizer()
    }
    public setRectShape(rect: Rect): void {
        const rect_casted = rect as (Rect)
        this.setRectShape_serialize(rect_casted)
        return
    }
    public setRoundRectShape(roundRect: RoundRect): void {
        const roundRect_casted = roundRect as (RoundRect)
        this.setRoundRectShape_serialize(roundRect_casted)
        return
    }
    public setCircleShape(circle: Circle): void {
        const circle_casted = circle as (Circle)
        this.setCircleShape_serialize(circle_casted)
        return
    }
    public setOvalShape(oval: Rect): void {
        const oval_casted = oval as (Rect)
        this.setOvalShape_serialize(oval_casted)
        return
    }
    public setCommandPath(path: CommandPath): void {
        const path_casted = path as (CommandPath)
        this.setCommandPath_serialize(path_casted)
        return
    }
    private getFillColor(): number {
        return this.getFillColor_serialize()
    }
    private setFillColor(fillColor: number): void {
        const fillColor_casted = fillColor as (number)
        this.setFillColor_serialize(fillColor_casted)
        return
    }
    private getStrokeColor(): number {
        return this.getStrokeColor_serialize()
    }
    private setStrokeColor(strokeColor: number): void {
        const strokeColor_casted = strokeColor as (number)
        this.setStrokeColor_serialize(strokeColor_casted)
        return
    }
    private getStrokeWidth(): number {
        return this.getStrokeWidth_serialize()
    }
    private setStrokeWidth(strokeWidth: number): void {
        const strokeWidth_casted = strokeWidth as (number)
        this.setStrokeWidth_serialize(strokeWidth_casted)
        return
    }
    private setRectShape_serialize(rect: Rect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(rect)
        ArkUIGeneratedNativeModule._ShapeMask_setRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setRoundRectShape_serialize(roundRect: RoundRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRoundRect(roundRect)
        ArkUIGeneratedNativeModule._ShapeMask_setRoundRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCircleShape_serialize(circle: Circle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCircle(circle)
        ArkUIGeneratedNativeModule._ShapeMask_setCircleShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOvalShape_serialize(oval: Rect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(oval)
        ArkUIGeneratedNativeModule._ShapeMask_setOvalShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCommandPath_serialize(path: CommandPath): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCommandPath(path)
        ArkUIGeneratedNativeModule._ShapeMask_setCommandPath(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFillColor_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_getFillColor(this.peer!.ptr)
        return retval
    }
    private setFillColor_serialize(fillColor: number): void {
        ArkUIGeneratedNativeModule._ShapeMask_setFillColor(this.peer!.ptr, fillColor)
    }
    private getStrokeColor_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_getStrokeColor(this.peer!.ptr)
        return retval
    }
    private setStrokeColor_serialize(strokeColor: number): void {
        ArkUIGeneratedNativeModule._ShapeMask_setStrokeColor(this.peer!.ptr, strokeColor)
    }
    private getStrokeWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ShapeMask_getStrokeWidth(this.peer!.ptr)
        return retval
    }
    private setStrokeWidth_serialize(strokeWidth: number): void {
        ArkUIGeneratedNativeModule._ShapeMask_setStrokeWidth(this.peer!.ptr, strokeWidth)
    }
}
export class ShapeClipInternal {
    public static fromPtr(ptr: KPointer): ShapeClip {
        const obj : ShapeClip = new ShapeClip()
        obj.peer = new Finalizable(ptr, ShapeClip.getFinalizer())
        return obj
    }
}
export class ShapeClip implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_shapeclip(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ShapeClip_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = ShapeClip.ctor_shapeclip()
        this.peer = new Finalizable(ctorPtr, ShapeClip.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ShapeClip_getFinalizer()
    }
    public setRectShape(rect: Rect): void {
        const rect_casted = rect as (Rect)
        this.setRectShape_serialize(rect_casted)
        return
    }
    public setRoundRectShape(roundRect: RoundRect): void {
        const roundRect_casted = roundRect as (RoundRect)
        this.setRoundRectShape_serialize(roundRect_casted)
        return
    }
    public setCircleShape(circle: Circle): void {
        const circle_casted = circle as (Circle)
        this.setCircleShape_serialize(circle_casted)
        return
    }
    public setOvalShape(oval: Rect): void {
        const oval_casted = oval as (Rect)
        this.setOvalShape_serialize(oval_casted)
        return
    }
    public setCommandPath(path: CommandPath): void {
        const path_casted = path as (CommandPath)
        this.setCommandPath_serialize(path_casted)
        return
    }
    private setRectShape_serialize(rect: Rect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(rect)
        ArkUIGeneratedNativeModule._ShapeClip_setRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setRoundRectShape_serialize(roundRect: RoundRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRoundRect(roundRect)
        ArkUIGeneratedNativeModule._ShapeClip_setRoundRectShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCircleShape_serialize(circle: Circle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCircle(circle)
        ArkUIGeneratedNativeModule._ShapeClip_setCircleShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOvalShape_serialize(oval: Rect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(oval)
        ArkUIGeneratedNativeModule._ShapeClip_setOvalShape(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCommandPath_serialize(path: CommandPath): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCommandPath(path)
        ArkUIGeneratedNativeModule._ShapeClip_setCommandPath(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface Size {
    width: number;
    height: number;
}
export interface DrawContext {
    size: Size;
    sizeInPixel: Size;
    canvas: DrawingCanvas;
}
export interface Vector2 {
    x: number;
    y: number;
}
export interface Vector2T {
    x: number;
    y: number;
}
export interface Vector3 {
    x: number;
    y: number;
    z: number;
}
export type Matrix4 = [
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number
]
export interface Frame {
    x: number;
    y: number;
    width: number;
    height: number;
}
export interface Edges {
    top?: Dimension;
    left?: Dimension;
    bottom?: Dimension;
    right?: Dimension;
}
export enum LengthUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4
}
export enum LengthMetricsUnit {
    DEFAULT = 0,
    PX = 1
}
export interface CornerRadius {
    topLeft: Vector2;
    topRight: Vector2;
    bottomLeft: Vector2;
    bottomRight: Vector2;
}
export interface BorderRadiuses_graphics {
    topLeft: number;
    topRight: number;
    bottomLeft: number;
    bottomRight: number;
}
export interface Rect {
    left: number;
    top: number;
    right: number;
    bottom: number;
}
export interface RoundRect {
    rect: Rect;
    corners: CornerRadius;
}
export interface Circle {
    centerX: number;
    centerY: number;
    radius: number;
}
export interface CommandPath {
    commands: string;
}
export type Offset_graphics = Vector2;
export type Pivot = Vector2;
export type Scale = Vector2;
export type Translation = Vector2;
export type Rotation = Vector3;
