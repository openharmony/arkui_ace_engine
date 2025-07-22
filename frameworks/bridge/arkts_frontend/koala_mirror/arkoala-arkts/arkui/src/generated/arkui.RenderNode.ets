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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Size_serializer, Vector2_serializer, Frame_serializer, Vector3_serializer, Size, Vector2, Frame, Vector3, ShapeMask, ShapeMaskInternal, ShapeClip, ShapeClipInternal, LengthMetricsUnit, DrawContext, DrawContextInternal } from "./arkui.Graphics"
import { EdgeStyles_serializer, Edges_serializer, EdgeStyles, Edges } from "./../component/units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export interface RenderNode {
    backgroundColor: number
    clipToFrame: boolean
    opacity: number
    size: Size
    position: Vector2
    frame: Frame
    pivot: Vector2
    scale: Vector2
    translation: Vector2
    rotation: Vector3
    transform: [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ]
    shadowColor: number
    shadowOffset: Vector2
    label: string
    shadowAlpha: number
    shadowElevation: number
    shadowRadius: number
    borderStyle: EdgeStyles
    borderWidth: Edges
    borderColor: Edges
    borderRadius: BorderRadiuses_graphics
    shapeMask: ShapeMask
    shapeClip: ShapeClip
    markNodeGroup: boolean
    lengthMetricsUnit: LengthMetricsUnit
    appendChild(node: RenderNode): void
    insertChildAfter(child: RenderNode, sibling: RenderNode | undefined): void
    removeChild(node: RenderNode): void
    clearChildren(): void
    getChild(index: number): RenderNode | undefined
    getFirstChild(): RenderNode | undefined
    getNextSibling(): RenderNode | undefined
    getPreviousSibling(): RenderNode | undefined
    draw(context: DrawContext): void
    invalidate(): void
    dispose(): void
}
export class RenderNodeInternal implements MaterializedBase,RenderNode {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get backgroundColor(): number {
        return this.getBackgroundColor()
    }
    set backgroundColor(backgroundColor: number) {
        this.setBackgroundColor(backgroundColor)
    }
    get clipToFrame(): boolean {
        return this.getClipToFrame()
    }
    set clipToFrame(clipToFrame: boolean) {
        this.setClipToFrame(clipToFrame)
    }
    get opacity(): number {
        return this.getOpacity()
    }
    set opacity(opacity: number) {
        this.setOpacity(opacity)
    }
    get size(): Size {
        return this.getSize()
    }
    set size(size: Size) {
        this.setSize(size)
    }
    get position(): Vector2 {
        return this.getPosition()
    }
    set position(position: Vector2) {
        this.setPosition(position)
    }
    get frame(): Frame {
        return this.getFrame()
    }
    set frame(frame: Frame) {
        this.setFrame(frame)
    }
    get pivot(): Vector2 {
        return this.getPivot()
    }
    set pivot(pivot: Vector2) {
        this.setPivot(pivot)
    }
    get scale(): Vector2 {
        return this.getScale()
    }
    set scale(scale: Vector2) {
        this.setScale(scale)
    }
    get translation(): Vector2 {
        return this.getTranslation()
    }
    set translation(translation: Vector2) {
        this.setTranslation(translation)
    }
    get rotation(): Vector3 {
        return this.getRotation()
    }
    set rotation(rotation: Vector3) {
        this.setRotation(rotation)
    }
    get transform(): [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ] {
        return this.getTransform()
    }
    set transform(transform: [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ]) {
        this.setTransform(transform)
    }
    get shadowColor(): number {
        return this.getShadowColor()
    }
    set shadowColor(shadowColor: number) {
        this.setShadowColor(shadowColor)
    }
    get shadowOffset(): Vector2 {
        return this.getShadowOffset()
    }
    set shadowOffset(shadowOffset: Vector2) {
        this.setShadowOffset(shadowOffset)
    }
    get label(): string {
        return this.getLabel()
    }
    set label(label: string) {
        this.setLabel(label)
    }
    get shadowAlpha(): number {
        return this.getShadowAlpha()
    }
    set shadowAlpha(shadowAlpha: number) {
        this.setShadowAlpha(shadowAlpha)
    }
    get shadowElevation(): number {
        return this.getShadowElevation()
    }
    set shadowElevation(shadowElevation: number) {
        this.setShadowElevation(shadowElevation)
    }
    get shadowRadius(): number {
        return this.getShadowRadius()
    }
    set shadowRadius(shadowRadius: number) {
        this.setShadowRadius(shadowRadius)
    }
    get borderStyle(): EdgeStyles {
        return this.getBorderStyle()
    }
    set borderStyle(borderStyle: EdgeStyles) {
        this.setBorderStyle(borderStyle)
    }
    get borderWidth(): Edges {
        return this.getBorderWidth()
    }
    set borderWidth(borderWidth: Edges) {
        this.setBorderWidth(borderWidth)
    }
    get borderColor(): Edges {
        return this.getBorderColor()
    }
    set borderColor(borderColor: Edges) {
        this.setBorderColor(borderColor)
    }
    get borderRadius(): BorderRadiuses_graphics {
        return this.getBorderRadius()
    }
    set borderRadius(borderRadius: BorderRadiuses_graphics) {
        this.setBorderRadius(borderRadius)
    }
    get shapeMask(): ShapeMask {
        return this.getShapeMask()
    }
    set shapeMask(shapeMask: ShapeMask) {
        this.setShapeMask(shapeMask)
    }
    get shapeClip(): ShapeClip {
        return this.getShapeClip()
    }
    set shapeClip(shapeClip: ShapeClip) {
        this.setShapeClip(shapeClip)
    }
    get markNodeGroup(): boolean {
        return this.getMarkNodeGroup()
    }
    set markNodeGroup(markNodeGroup: boolean) {
        this.setMarkNodeGroup(markNodeGroup)
    }
    get lengthMetricsUnit(): LengthMetricsUnit {
        return this.getLengthMetricsUnit()
    }
    set lengthMetricsUnit(lengthMetricsUnit: LengthMetricsUnit) {
        this.setLengthMetricsUnit(lengthMetricsUnit)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RenderNodeInternal.getFinalizer())
    }
    constructor() {
        this(RenderNodeInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RenderNode_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): RenderNodeInternal {
        return new RenderNodeInternal(ptr)
    }
    public appendChild(node: RenderNode): void {
        const node_casted = node as (RenderNode)
        this.appendChild_serialize(node_casted)
        return
    }
    public insertChildAfter(child: RenderNode, sibling: RenderNode | undefined): void {
        const child_casted = child as (RenderNode)
        const sibling_casted = sibling as (RenderNode | undefined)
        this.insertChildAfter_serialize(child_casted, sibling_casted)
        return
    }
    public removeChild(node: RenderNode): void {
        const node_casted = node as (RenderNode)
        this.removeChild_serialize(node_casted)
        return
    }
    public clearChildren(): void {
        this.clearChildren_serialize()
        return
    }
    public getChild(index: number): RenderNode | undefined {
        const index_casted = index as (number)
        return this.getChild_serialize(index_casted)
    }
    public getFirstChild(): RenderNode | undefined {
        return this.getFirstChild_serialize()
    }
    public getNextSibling(): RenderNode | undefined {
        return this.getNextSibling_serialize()
    }
    public getPreviousSibling(): RenderNode | undefined {
        return this.getPreviousSibling_serialize()
    }
    public draw(context: DrawContext): void {
        const context_casted = context as (DrawContext)
        this.draw_serialize(context_casted)
        return
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    public dispose(): void {
        this.dispose_serialize()
        return
    }
    private getBackgroundColor(): number {
        return this.getBackgroundColor_serialize()
    }
    private setBackgroundColor(backgroundColor: number): void {
        const backgroundColor_casted = backgroundColor as (number)
        this.setBackgroundColor_serialize(backgroundColor_casted)
        return
    }
    private getClipToFrame(): boolean {
        return this.getClipToFrame_serialize()
    }
    private setClipToFrame(clipToFrame: boolean): void {
        const clipToFrame_casted = clipToFrame as (boolean)
        this.setClipToFrame_serialize(clipToFrame_casted)
        return
    }
    private getOpacity(): number {
        return this.getOpacity_serialize()
    }
    private setOpacity(opacity: number): void {
        const opacity_casted = opacity as (number)
        this.setOpacity_serialize(opacity_casted)
        return
    }
    private getSize(): Size {
        return this.getSize_serialize()
    }
    private setSize(size: Size): void {
        const size_casted = size as (Size)
        this.setSize_serialize(size_casted)
        return
    }
    private getPosition(): Vector2 {
        return this.getPosition_serialize()
    }
    private setPosition(position: Vector2): void {
        const position_casted = position as (Vector2)
        this.setPosition_serialize(position_casted)
        return
    }
    private getFrame(): Frame {
        return this.getFrame_serialize()
    }
    private setFrame(frame: Frame): void {
        const frame_casted = frame as (Frame)
        this.setFrame_serialize(frame_casted)
        return
    }
    private getPivot(): Vector2 {
        return this.getPivot_serialize()
    }
    private setPivot(pivot: Vector2): void {
        const pivot_casted = pivot as (Vector2)
        this.setPivot_serialize(pivot_casted)
        return
    }
    private getScale(): Vector2 {
        return this.getScale_serialize()
    }
    private setScale(scale: Vector2): void {
        const scale_casted = scale as (Vector2)
        this.setScale_serialize(scale_casted)
        return
    }
    private getTranslation(): Vector2 {
        return this.getTranslation_serialize()
    }
    private setTranslation(translation: Vector2): void {
        const translation_casted = translation as (Vector2)
        this.setTranslation_serialize(translation_casted)
        return
    }
    private getRotation(): Vector3 {
        return this.getRotation_serialize()
    }
    private setRotation(rotation: Vector3): void {
        const rotation_casted = rotation as (Vector3)
        this.setRotation_serialize(rotation_casted)
        return
    }
    private getTransform(): [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ] {
        return this.getTransform_serialize()
    }
    private setTransform(transform: [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ]): void {
        const transform_casted = transform as ([ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ])
        this.setTransform_serialize(transform_casted)
        return
    }
    private getShadowColor(): number {
        return this.getShadowColor_serialize()
    }
    private setShadowColor(shadowColor: number): void {
        const shadowColor_casted = shadowColor as (number)
        this.setShadowColor_serialize(shadowColor_casted)
        return
    }
    private getShadowOffset(): Vector2 {
        return this.getShadowOffset_serialize()
    }
    private setShadowOffset(shadowOffset: Vector2): void {
        const shadowOffset_casted = shadowOffset as (Vector2)
        this.setShadowOffset_serialize(shadowOffset_casted)
        return
    }
    private getLabel(): string {
        return this.getLabel_serialize()
    }
    private setLabel(label: string): void {
        const label_casted = label as (string)
        this.setLabel_serialize(label_casted)
        return
    }
    private getShadowAlpha(): number {
        return this.getShadowAlpha_serialize()
    }
    private setShadowAlpha(shadowAlpha: number): void {
        const shadowAlpha_casted = shadowAlpha as (number)
        this.setShadowAlpha_serialize(shadowAlpha_casted)
        return
    }
    private getShadowElevation(): number {
        return this.getShadowElevation_serialize()
    }
    private setShadowElevation(shadowElevation: number): void {
        const shadowElevation_casted = shadowElevation as (number)
        this.setShadowElevation_serialize(shadowElevation_casted)
        return
    }
    private getShadowRadius(): number {
        return this.getShadowRadius_serialize()
    }
    private setShadowRadius(shadowRadius: number): void {
        const shadowRadius_casted = shadowRadius as (number)
        this.setShadowRadius_serialize(shadowRadius_casted)
        return
    }
    private getBorderStyle(): EdgeStyles {
        return this.getBorderStyle_serialize()
    }
    private setBorderStyle(borderStyle: EdgeStyles): void {
        const borderStyle_casted = borderStyle as (EdgeStyles)
        this.setBorderStyle_serialize(borderStyle_casted)
        return
    }
    private getBorderWidth(): Edges {
        return this.getBorderWidth_serialize()
    }
    private setBorderWidth(borderWidth: Edges): void {
        const borderWidth_casted = borderWidth as (Edges)
        this.setBorderWidth_serialize(borderWidth_casted)
        return
    }
    private getBorderColor(): Edges {
        return this.getBorderColor_serialize()
    }
    private setBorderColor(borderColor: Edges): void {
        const borderColor_casted = borderColor as (Edges)
        this.setBorderColor_serialize(borderColor_casted)
        return
    }
    private getBorderRadius(): BorderRadiuses_graphics {
        return this.getBorderRadius_serialize()
    }
    private setBorderRadius(borderRadius: BorderRadiuses_graphics): void {
        const borderRadius_casted = borderRadius as (BorderRadiuses_graphics)
        this.setBorderRadius_serialize(borderRadius_casted)
        return
    }
    private getShapeMask(): ShapeMask {
        return this.getShapeMask_serialize()
    }
    private setShapeMask(shapeMask: ShapeMask): void {
        const shapeMask_casted = shapeMask as (ShapeMask)
        this.setShapeMask_serialize(shapeMask_casted)
        return
    }
    private getShapeClip(): ShapeClip {
        return this.getShapeClip_serialize()
    }
    private setShapeClip(shapeClip: ShapeClip): void {
        const shapeClip_casted = shapeClip as (ShapeClip)
        this.setShapeClip_serialize(shapeClip_casted)
        return
    }
    private getMarkNodeGroup(): boolean {
        return this.getMarkNodeGroup_serialize()
    }
    private setMarkNodeGroup(markNodeGroup: boolean): void {
        const markNodeGroup_casted = markNodeGroup as (boolean)
        this.setMarkNodeGroup_serialize(markNodeGroup_casted)
        return
    }
    private getLengthMetricsUnit(): LengthMetricsUnit {
        return this.getLengthMetricsUnit_serialize()
    }
    private setLengthMetricsUnit(lengthMetricsUnit: LengthMetricsUnit): void {
        const lengthMetricsUnit_casted = lengthMetricsUnit as (LengthMetricsUnit)
        this.setLengthMetricsUnit_serialize(lengthMetricsUnit_casted)
        return
    }
    private appendChild_serialize(node: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNode_appendChild(this.peer!.ptr, toPeerPtr(node))
    }
    private insertChildAfter_serialize(child: RenderNode, sibling: RenderNode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let sibling_type : int32 = RuntimeType.UNDEFINED
        sibling_type = runtimeType(sibling)
        thisSerializer.writeInt8((sibling_type).toChar())
        if ((sibling_type) != (RuntimeType.UNDEFINED)) {
            const sibling_value  = sibling!
            RenderNode_serializer.write(thisSerializer, sibling_value)
        }
        ArkUIGeneratedNativeModule._RenderNode_insertChildAfter(this.peer!.ptr, toPeerPtr(child), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeChild_serialize(node: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNode_removeChild(this.peer!.ptr, toPeerPtr(node))
    }
    private clearChildren_serialize(): void {
        ArkUIGeneratedNativeModule._RenderNode_clearChildren(this.peer!.ptr)
    }
    private getChild_serialize(index: number): RenderNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getChild(this.peer!.ptr, index)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RenderNode | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (RenderNode_serializer.read(retvalDeserializer) as RenderNode)
        }
        const returnResult : RenderNode | undefined = buffer
        return returnResult
    }
    private getFirstChild_serialize(): RenderNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getFirstChild(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RenderNode | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (RenderNode_serializer.read(retvalDeserializer) as RenderNode)
        }
        const returnResult : RenderNode | undefined = buffer
        return returnResult
    }
    private getNextSibling_serialize(): RenderNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getNextSibling(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RenderNode | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (RenderNode_serializer.read(retvalDeserializer) as RenderNode)
        }
        const returnResult : RenderNode | undefined = buffer
        return returnResult
    }
    private getPreviousSibling_serialize(): RenderNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getPreviousSibling(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RenderNode | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (RenderNode_serializer.read(retvalDeserializer) as RenderNode)
        }
        const returnResult : RenderNode | undefined = buffer
        return returnResult
    }
    private draw_serialize(context: DrawContext): void {
        ArkUIGeneratedNativeModule._RenderNode_draw(this.peer!.ptr, toPeerPtr(context))
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._RenderNode_invalidate(this.peer!.ptr)
    }
    private dispose_serialize(): void {
        ArkUIGeneratedNativeModule._RenderNode_dispose(this.peer!.ptr)
    }
    private getBackgroundColor_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getBackgroundColor(this.peer!.ptr)
        return retval
    }
    private setBackgroundColor_serialize(backgroundColor: number): void {
        ArkUIGeneratedNativeModule._RenderNode_setBackgroundColor(this.peer!.ptr, backgroundColor)
    }
    private getClipToFrame_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getClipToFrame(this.peer!.ptr)
        return retval
    }
    private setClipToFrame_serialize(clipToFrame: boolean): void {
        ArkUIGeneratedNativeModule._RenderNode_setClipToFrame(this.peer!.ptr, clipToFrame ? 1 : 0)
    }
    private getOpacity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getOpacity(this.peer!.ptr)
        return retval
    }
    private setOpacity_serialize(opacity: number): void {
        ArkUIGeneratedNativeModule._RenderNode_setOpacity(this.peer!.ptr, opacity)
    }
    private getSize_serialize(): Size {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getSize(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Size = Size_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setSize_serialize(size: Size): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Size_serializer.write(thisSerializer, size)
        ArkUIGeneratedNativeModule._RenderNode_setSize(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getPosition_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getPosition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setPosition_serialize(position: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._RenderNode_setPosition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFrame_serialize(): Frame {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getFrame(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Frame = Frame_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setFrame_serialize(frame: Frame): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Frame_serializer.write(thisSerializer, frame)
        ArkUIGeneratedNativeModule._RenderNode_setFrame(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getPivot_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getPivot(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setPivot_serialize(pivot: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, pivot)
        ArkUIGeneratedNativeModule._RenderNode_setPivot(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getScale_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getScale(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setScale_serialize(scale: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, scale)
        ArkUIGeneratedNativeModule._RenderNode_setScale(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTranslation_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getTranslation(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setTranslation_serialize(translation: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, translation)
        ArkUIGeneratedNativeModule._RenderNode_setTranslation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getRotation_serialize(): Vector3 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getRotation(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector3 = Vector3_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setRotation_serialize(rotation: Vector3): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector3_serializer.write(thisSerializer, rotation)
        ArkUIGeneratedNativeModule._RenderNode_setRotation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTransform_serialize(): [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ] {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getTransform(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_value0 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value1 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value2 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value3 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value4 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value5 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value6 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value7 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value8 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value9 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value10 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value11 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value12 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value13 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value14 : number = (retvalDeserializer.readNumber() as number)
        const buffer_value15 : number = (retvalDeserializer.readNumber() as number)
        const returnResult : [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ] = ([buffer_value0, buffer_value1, buffer_value2, buffer_value3, buffer_value4, buffer_value5, buffer_value6, buffer_value7, buffer_value8, buffer_value9, buffer_value10, buffer_value11, buffer_value12, buffer_value13, buffer_value14, buffer_value15] as [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ])
        return returnResult
    }
    private setTransform_serialize(transform: [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ]): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const transform_0  = transform[0]
        thisSerializer.writeNumber(transform_0)
        const transform_1  = transform[1]
        thisSerializer.writeNumber(transform_1)
        const transform_2  = transform[2]
        thisSerializer.writeNumber(transform_2)
        const transform_3  = transform[3]
        thisSerializer.writeNumber(transform_3)
        const transform_4  = transform[4]
        thisSerializer.writeNumber(transform_4)
        const transform_5  = transform[5]
        thisSerializer.writeNumber(transform_5)
        const transform_6  = transform[6]
        thisSerializer.writeNumber(transform_6)
        const transform_7  = transform[7]
        thisSerializer.writeNumber(transform_7)
        const transform_8  = transform[8]
        thisSerializer.writeNumber(transform_8)
        const transform_9  = transform[9]
        thisSerializer.writeNumber(transform_9)
        const transform_10  = transform[10]
        thisSerializer.writeNumber(transform_10)
        const transform_11  = transform[11]
        thisSerializer.writeNumber(transform_11)
        const transform_12  = transform[12]
        thisSerializer.writeNumber(transform_12)
        const transform_13  = transform[13]
        thisSerializer.writeNumber(transform_13)
        const transform_14  = transform[14]
        thisSerializer.writeNumber(transform_14)
        const transform_15  = transform[15]
        thisSerializer.writeNumber(transform_15)
        ArkUIGeneratedNativeModule._RenderNode_setTransform(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getShadowColor_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getShadowColor(this.peer!.ptr)
        return retval
    }
    private setShadowColor_serialize(shadowColor: number): void {
        ArkUIGeneratedNativeModule._RenderNode_setShadowColor(this.peer!.ptr, shadowColor)
    }
    private getShadowOffset_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getShadowOffset(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setShadowOffset_serialize(shadowOffset: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, shadowOffset)
        ArkUIGeneratedNativeModule._RenderNode_setShadowOffset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getLabel_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getLabel(this.peer!.ptr)
        return retval
    }
    private setLabel_serialize(label: string): void {
        ArkUIGeneratedNativeModule._RenderNode_setLabel(this.peer!.ptr, label)
    }
    private getShadowAlpha_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getShadowAlpha(this.peer!.ptr)
        return retval
    }
    private setShadowAlpha_serialize(shadowAlpha: number): void {
        ArkUIGeneratedNativeModule._RenderNode_setShadowAlpha(this.peer!.ptr, shadowAlpha)
    }
    private getShadowElevation_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getShadowElevation(this.peer!.ptr)
        return retval
    }
    private setShadowElevation_serialize(shadowElevation: number): void {
        ArkUIGeneratedNativeModule._RenderNode_setShadowElevation(this.peer!.ptr, shadowElevation)
    }
    private getShadowRadius_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getShadowRadius(this.peer!.ptr)
        return retval
    }
    private setShadowRadius_serialize(shadowRadius: number): void {
        ArkUIGeneratedNativeModule._RenderNode_setShadowRadius(this.peer!.ptr, shadowRadius)
    }
    private getBorderStyle_serialize(): EdgeStyles {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : EdgeStyles = EdgeStyles_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setBorderStyle_serialize(borderStyle: EdgeStyles): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        EdgeStyles_serializer.write(thisSerializer, borderStyle)
        ArkUIGeneratedNativeModule._RenderNode_setBorderStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getBorderWidth_serialize(): Edges {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderWidth(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Edges = Edges_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setBorderWidth_serialize(borderWidth: Edges): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Edges_serializer.write(thisSerializer, borderWidth)
        ArkUIGeneratedNativeModule._RenderNode_setBorderWidth(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getBorderColor_serialize(): Edges {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderColor(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Edges = Edges_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setBorderColor_serialize(borderColor: Edges): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Edges_serializer.write(thisSerializer, borderColor)
        ArkUIGeneratedNativeModule._RenderNode_setBorderColor(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getBorderRadius_serialize(): BorderRadiuses_graphics {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderRadius(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : BorderRadiuses_graphics = BorderRadiuses_graphics_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setBorderRadius_serialize(borderRadius: BorderRadiuses_graphics): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        BorderRadiuses_graphics_serializer.write(thisSerializer, borderRadius)
        ArkUIGeneratedNativeModule._RenderNode_setBorderRadius(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getShapeMask_serialize(): ShapeMask {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getShapeMask(this.peer!.ptr)
        const obj : ShapeMask = ShapeMaskInternal.fromPtr(retval)
        return obj
    }
    private setShapeMask_serialize(shapeMask: ShapeMask): void {
        ArkUIGeneratedNativeModule._RenderNode_setShapeMask(this.peer!.ptr, toPeerPtr(shapeMask))
    }
    private getShapeClip_serialize(): ShapeClip {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getShapeClip(this.peer!.ptr)
        const obj : ShapeClip = ShapeClipInternal.fromPtr(retval)
        return obj
    }
    private setShapeClip_serialize(shapeClip: ShapeClip): void {
        ArkUIGeneratedNativeModule._RenderNode_setShapeClip(this.peer!.ptr, toPeerPtr(shapeClip))
    }
    private getMarkNodeGroup_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getMarkNodeGroup(this.peer!.ptr)
        return retval
    }
    private setMarkNodeGroup_serialize(markNodeGroup: boolean): void {
        ArkUIGeneratedNativeModule._RenderNode_setMarkNodeGroup(this.peer!.ptr, markNodeGroup ? 1 : 0)
    }
    private getLengthMetricsUnit_serialize(): LengthMetricsUnit {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getLengthMetricsUnit(this.peer!.ptr)
        return TypeChecker.LengthMetricsUnit_FromNumeric(retval)
    }
    private setLengthMetricsUnit_serialize(lengthMetricsUnit: LengthMetricsUnit): void {
        ArkUIGeneratedNativeModule._RenderNode_setLengthMetricsUnit(this.peer!.ptr, TypeChecker.LengthMetricsUnit_ToNumeric(lengthMetricsUnit))
    }
}
export type Offset_graphics = Vector2;
export interface BorderRadiuses_graphics {
    topLeft: number;
    topRight: number;
    bottomLeft: number;
    bottomRight: number;
}
export class BorderRadiuses_graphics_serializer {
    public static write(buffer: SerializerBase, value: BorderRadiuses_graphics): void {
        let valueSerializer : SerializerBase = buffer
        const value_topLeft  = value.topLeft
        valueSerializer.writeNumber(value_topLeft)
        const value_topRight  = value.topRight
        valueSerializer.writeNumber(value_topRight)
        const value_bottomLeft  = value.bottomLeft
        valueSerializer.writeNumber(value_bottomLeft)
        const value_bottomRight  = value.bottomRight
        valueSerializer.writeNumber(value_bottomRight)
    }
    public static read(buffer: DeserializerBase): BorderRadiuses_graphics {
        let valueDeserializer : DeserializerBase = buffer
        const topLeft_result : number = (valueDeserializer.readNumber() as number)
        const topRight_result : number = (valueDeserializer.readNumber() as number)
        const bottomLeft_result : number = (valueDeserializer.readNumber() as number)
        const bottomRight_result : number = (valueDeserializer.readNumber() as number)
        let value : BorderRadiuses_graphics = ({topLeft: topLeft_result, topRight: topRight_result, bottomLeft: bottomLeft_result, bottomRight: bottomRight_result} as BorderRadiuses_graphics)
        return value
    }
}
export class RenderNode_serializer {
    public static write(buffer: SerializerBase, value: RenderNode): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RenderNode {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RenderNodeInternal.fromPtr(ptr)
    }
}
