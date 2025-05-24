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

import { Position, Rect, Circle, RoundRect, CommandPath, Size, Frame, Vector2, Vector3, Matrix4, Edges, Corners, ShapeMask, ShapeClip, LengthMetricsUnit, DrawContext } from "./Graphics"
import { BorderStyle } from "./component/enums"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, InteropNativeModule } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./component/peers/Serializer"
import { CallbackKind } from "./component/peers/CallbackKind"
import { Deserializer } from "./component/peers/Deserializer"
import { CallbackTransformer } from "./component/peers/CallbackTransformer"
import { PeerNode } from "./PeerNode"
import { FrameNode } from "./FrameNode"
import { Utils } from "@ohos/arkui/graphics"
import { ArkUIAniModule } from "arkui.ani"
export type DrawCallback = (context: DrawContext) => void;
export class RenderNodeInternal {
    public static fromPtr(ptr: KPointer): RenderNode {
        const obj : RenderNode = new RenderNode()
        obj.peer = new Finalizable(ptr, RenderNode.getFinalizer())
        return obj
    }
}
export class RenderNode implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    private childrenList: RenderNode[] = []
    private parentRenderNode: WeakRef<RenderNode> | null = null
    private lengthMetricsUnitValue: LengthMetricsUnit = LengthMetricsUnit.DEFAULT
    private borderStyleValue: Edges<BorderStyle> | null = null
    private borderWidthValue: Edges<number> = { left: 0, top: 0, right: 0, bottom: 0 }
    private borderColorValue: Edges<number> = { left: 0XFF000000, top: 0XFF000000, right: 0XFF000000, bottom: 0XFF000000 }
    private borderRadiusValue: Corners<number> = { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 }
    private shapeMaskValue: ShapeMask | null = null
    private shapeClipValue: ShapeClip | null = null
    private backgroundColorValue: number = 0
    private clipToFrameValue: boolean = true
    private frameValue: Frame = { x: 0, y: 0, width: 0, height: 0 }
    private opacityValue: number = 1.0
    private pivotValue: Vector2 = { x: 0.5, y: 0.5 }
    private rotationValue: Vector3 = { x: 0, y: 0, z: 0 }
    private scaleValue: Vector2 = { x: 1.0, y: 1.0 }
    private shadowColorValue: number = 0
    private shadowOffsetValue: Vector2 = { x: 0, y: 0 }
    private labelValue: string = ""
    private shadowAlphaValue: number = 0
    private shadowElevationValue: number = 0
    private shadowRadiusValue: number = 0
    private transformValue: Matrix4 = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]
    private translationValue: Vector2 = { x: 0, y: 0 }
    private markNodeGroupValue: boolean = false
    private frameNode_: WeakRef<FrameNode> | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    checkUndefinedOrNullWithDefaultValue<T>(arg: T | undefined, defaultValue: T): T {
        if (arg === undefined || arg === null) {
            return defaultValue
        }
        return arg as T
    }
    get backgroundColor(): number {
        return this.backgroundColorValue
    }
    set backgroundColor(backgroundColor: number) {
        this.backgroundColorValue = this.checkUndefinedOrNullWithDefaultValue<number>(backgroundColor, 0)
        this.setBackgroundColor(this.backgroundColorValue)
    }
    get clipToFrame(): boolean {
        return this.clipToFrameValue
    }
    set clipToFrame(clipToFrame: boolean) {
        this.clipToFrameValue = this.checkUndefinedOrNullWithDefaultValue<boolean>(clipToFrame, true)
        this.setClipToFrame(this.clipToFrameValue)
    }
    get opacity(): number {
        return this.opacityValue
    }
    set opacity(opacity: number) {
        this.opacityValue = this.checkUndefinedOrNullWithDefaultValue<number>(opacity, 1.0)
        this.setOpacity(this.opacityValue)
    }
    get size(): Size {
        return { width: this.frameValue.width, height: this.frameValue.height }
    }
    set size(size: Size) {
        if (size === undefined || size === null) {
            this.frameValue.width = 0
            this.frameValue.height = 0
        } else {
            this.frameValue.width = this.checkUndefinedOrNullWithDefaultValue<number>(size.width, 0)
            this.frameValue.height = this.checkUndefinedOrNullWithDefaultValue<number>(size.height, 0)
        }
        const size_casted: Size = { width: this.frameValue.width, height: this.frameValue.height }
        this.setSize(size_casted)
    }
    get position(): Position {
        return { x: this.frameValue.x, y: this.frameValue.y }
    }
    set position(position: Position) {
        if (position === undefined || position === null) {
            this.frameValue.x = 0;
            this.frameValue.y = 0;
        } else {
            this.frameValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(position.x, 0) as number
            this.frameValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(position.y, 0) as number
        }
        const position_casted: Position = { x: this.frameValue.x, y: this.frameValue.y }
        this.setPosition(position_casted)
    }
    get frame(): Frame {
        return this.frameValue
    }
    set frame(frame: Frame) {
        if (frame === undefined || frame === null) {
            this.frameValue = { x: 0, y: 0, width: 0, height: 0 }
        } else {
            this.size = { width: frame.width, height: frame.height }
            this.position = { x: frame.x, y: frame.y };
        }
    }
    get pivot(): Vector2 {
        return this.pivotValue
    }
    set pivot(pivot: Vector2) {
        if (pivot === undefined || pivot === null) {
            this.pivotValue = { x: 0.5, y: 0.5 };
          } else {
            this.pivotValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(pivot.x, 0.5);
            this.pivotValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(pivot.y, 0.5);
          }
        this.setPivot(pivot)
    }
    get scale(): Vector2 {
        return this.scaleValue
    }
    set scale(scale: Vector2) {
        if (scale === undefined || scale === null) {
            this.scaleValue = { x: 1.0, y: 1.0 };
        } else {
            this.scaleValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(scale.x, 1.0);
            this.scaleValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(scale.y, 1.0);
        }
        const scale_casted: Vector2 = { x: this.scaleValue.x, y: this.scaleValue.y }
        this.setScale(scale_casted)
    }
    get translation(): Vector2 {
        return this.translationValue
    }
    set translation(translation: Vector2) {
        if (translation === undefined || translation === null) {
            this.translationValue = { x: 0, y: 0 };
        } else {
            this.translationValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(translation.x, 0);
            this.translationValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(translation.y, 0);
        }
        const translation_casted: Vector2 = { x: this.translationValue.x, y: this.translationValue.y }
        this.setTranslation(translation_casted)
    }
    get rotation(): Vector3 {
        return this.rotationValue
    }
    set rotation(rotation: Vector3) {
        if (rotation === undefined || rotation === null) {
            this.rotationValue = { x: 0, y: 0, z: 0 };
        } else {
            this.rotationValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.x, 0);
            this.rotationValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.y, 0);
            this.rotationValue.z = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.z, 0);
        }
        const rotation_casted: Vector3 = { x: this.rotationValue.x, y: this.rotationValue.y, z: this.rotationValue.z }
        this.setRotation(rotation_casted)
    }
    get transform(): Matrix4 {
        return this.transformValue
    }
    set transform(transform: Matrix4) {
        if (transform === undefined || transform === null) {
            this.transformValue = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]
        } else {
            this.transformValue = transform
        }
        this.setTransform(this.transformValue);
    }
    get shadowColor(): number {
        return this.shadowColorValue
    }
    set shadowColor(shadowColor: number) {
        this.shadowColorValue = this.checkUndefinedOrNullWithDefaultValue<number>(shadowColor, 0)
        this.setShadowColor(this.shadowColorValue)
    }
    get shadowOffset(): Vector2 {
        return { x: this.shadowOffsetValue.x, y: this.shadowOffsetValue.y }
    }
    set shadowOffset(shadowOffset: Vector2) {
        if (shadowOffset === undefined || shadowOffset === null) {
            this.shadowOffsetValue = { x: 0, y: 0 };
        } else {
            this.shadowOffsetValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(shadowOffset.x, 0);
            this.shadowOffsetValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(shadowOffset.y, 0);
        }
        const shadowOffset_casted: Vector2 = { x: this.shadowOffsetValue.x, y: this.shadowOffsetValue.y }
        this.setShadowOffset(shadowOffset_casted)
    }
    get label(): string {
        return this.labelValue
    }
    set label(label: string) {
        this.labelValue = this.checkUndefinedOrNullWithDefaultValue<string>(label, '')
        this.setLabel(this.labelValue)
    }
    get shadowAlpha(): number {
        return this.shadowAlphaValue
    }
    set shadowAlpha(shadowAlpha: number) {
        this.shadowAlphaValue = this.checkUndefinedOrNullWithDefaultValue<number>(shadowAlpha, 0)
        this.setShadowAlpha(this.shadowAlphaValue)
    }
    get shadowElevation(): number {
        return this.shadowElevationValue
    }
    set shadowElevation(shadowElevation: number) {
        this.shadowElevationValue = this.checkUndefinedOrNullWithDefaultValue<number>(shadowElevation, 0)
        this.setShadowElevation(this.shadowElevationValue)
    }
    get shadowRadius(): number {
        return this.shadowRadiusValue
    }
    set shadowRadius(shadowRadius: number) {
        this.shadowRadiusValue = this.checkUndefinedOrNullWithDefaultValue<number>(shadowRadius, 0)
        this.setShadowRadius(this.shadowRadiusValue)
    }
    get borderStyle(): Edges<BorderStyle> {
        return this.borderStyleValue!
    }
    set borderStyle(borderStyle: Edges<BorderStyle>) {
        if (borderStyle === undefined || borderStyle === null) {
            this.borderStyleValue = null;
        } else {
            this.borderStyleValue = borderStyle;
        }
        this.setBorderStyle(borderStyle!)
    }
    get borderWidth(): Edges<number> {
        return this.borderWidthValue
    }
    set borderWidth(borderWidth: Edges<number>) {
        if (borderWidth === undefined || borderWidth === null) {
            this.borderWidthValue = { left: 0, top: 0, right: 0, bottom: 0 } as Edges<number>
        } else {
            this.borderWidthValue = borderWidth;
        }
        const borderWidth_casted = this.borderWidthValue as Edges<number>
        this.setBorderWidth(borderWidth_casted)
    }
    get borderColor(): Edges<number> {
        return this.borderColorValue
    }
    set borderColor(borderColor: Edges<number>) {
        if (borderColor === undefined || borderColor === null) {
            this.borderColorValue = { left: 0XFF000000, top: 0XFF000000, right: 0XFF000000, bottom: 0XFF000000 };
        } else {
            this.borderColorValue = borderColor;
        }
        const borderColor_casted = this.borderColorValue as Edges<number>
        this.setBorderColor(borderColor_casted)
    }
    get borderRadius(): Corners<number> {
        return this.borderRadiusValue
    }
    set borderRadius(borderRadius: Corners<number>) {
        if (borderRadius === undefined || borderRadius === null) {
            this.borderRadiusValue = { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 };
          } else {
            this.borderRadiusValue = borderRadius;
          }
          const borderRadius_casted = this.borderRadiusValue as Corners<number>
        this.setBorderRadius(borderRadius_casted)
    }
    get shapeMask(): ShapeMask {
        return this.shapeMaskValue!
    }
    set shapeMask(shapeMask: ShapeMask) {
        this.setShapeMask(shapeMask)
    }
    get shapeClip(): ShapeClip {
        return this.shapeClipValue!
    }
    set shapeClip(shapeClip: ShapeClip) {
        this.setShapeClip(shapeClip)
    }
    get markNodeGroup(): boolean {
        return this.markNodeGroupValue
    }
    set markNodeGroup(markNodeGroup: boolean) {
        this.setMarkNodeGroup(markNodeGroup)
    }
    get lengthMetricsUnit(): LengthMetricsUnit {
        return this.lengthMetricsUnitValue
    }
    set lengthMetricsUnit(lengthMetricsUnit: LengthMetricsUnit) {
        this.setLengthMetricsUnit(lengthMetricsUnit)
    }
    static ctor_rendernode(id: int32, callback: DrawCallback): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._RenderNode_ctor(id, thisSerializer.asBuffer(), thisSerializer.length())
        return retval
    }
    constructor(type?: string) {
        if (type === 'BuilderRootFrameNode' || type === 'CustomFrameNode') {
            return
        }
        const peerId = PeerNode.nextId()
        const ctorPtr: KPointer = RenderNode.ctor_rendernode(peerId, this.draw)
        ArkUIAniModule._SetDrawCallback(ctorPtr, this.draw)
        this.peer = new Finalizable(ctorPtr, RenderNode.getFinalizer())
        this.setClipToFrame(true)
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RenderNode_getFinalizer()
    }
    public appendChild(node: RenderNode): void {
        const node_casted = node as (RenderNode)
        if (this.childrenList.findIndex(element => element === node_casted) !== -1) {
            return
        }
        this.childrenList.push(node)
        node.parentRenderNode = new WeakRef<RenderNode>(this)
        this.appendChild_serialize(node_casted)
        return
    }
    public insertChildAfter(child: RenderNode, sibling: RenderNode | null): void {
        const child_casted = child as (RenderNode)
        InteropNativeModule._NativeLog("FFZZYY insertChildAfter 111")
        let indexOfNode = this.childrenList.findIndex(element => element === child_casted)
        if (indexOfNode !== -1) {
            return
        }
        InteropNativeModule._NativeLog("FFZZYY insertChildAfter 222")
        child.parentRenderNode = new WeakRef<RenderNode>(this);
        InteropNativeModule._NativeLog("FFZZYY insertChildAfter 333")
        let indexOfSibling = this.childrenList.findIndex(element => element === sibling)
        if (indexOfSibling === -1) {
            return
        }
        InteropNativeModule._NativeLog("FFZZYY insertChildAfter 444")
        if (sibling === undefined || sibling === null) {
            this.childrenList.splice(0, 0, child)
        } else {
            this.childrenList.splice(indexOfSibling + 1, 0, child)
        }
        InteropNativeModule._NativeLog("FFZZYY insertChildAfter 555")
        const sibling_casted = sibling as (RenderNode | undefined)
        this.insertChildAfter_serialize(child_casted, sibling_casted)
        InteropNativeModule._NativeLog("FFZZYY insertChildAfter 666")
        return
    }
    public removeChild(node: RenderNode): void {
        const node_casted = node as (RenderNode)
        const index = this.childrenList.findIndex(element => element === node_casted);
        if (index === -1) {
            return
        }
        const child = this.childrenList[index]
        child.parentRenderNode = null
        this.childrenList.splice(index, 1)
        this.removeChild_serialize(node_casted)
        return
    }
    public clearChildren(): void {
        this.childrenList = []
        this.clearChildren_serialize()
        return
    }
    public getChild(index: number): RenderNode | null {
        if (this.childrenList.length > index && index >= 0) {
            return this.childrenList[index]
        }
        return null
    }
    public getFirstChild(): RenderNode | null {
        if (this.childrenList.length > 0) {
            return this.childrenList[0]
        }
        return null
    }
    public getNextSibling(): RenderNode | null {
        if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
            return null
        }
        let parent = this.parentRenderNode!.deref()
        if (parent === undefined || parent === null) {
            return null
        }
        let siblingList = parent!.childrenList
        const index = siblingList.findIndex(element => element === this)
        if (index === -1) {
            return null
        }
        return parent!.getChild(index + 1)
    }
    public getPreviousSibling(): RenderNode | null {
        if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
            return null
        }
        let parent = this.parentRenderNode!.deref()
        if (parent === undefined || parent === null) {
            return null
        }
        let siblingList = parent!.childrenList
        const index = siblingList.findIndex(element => element === this)
        if (index === -1) {
            return null
        }
        return parent!.getChild(index - 1)
    }
    public draw(context: DrawContext): void {
        InteropNativeModule._NativeLog("RenderNode Draw")
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    dispose() {
        this.frameNode_?.deref()?.dispose()
        this.peer?.release()
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
    private getPosition(): Position {
        return { x: this.frameValue.x, y: this.frameValue.y }
    }
    private setPosition(position: Position): void {
        const position_casted = position as (Position)
        this.setPosition_serialize(position_casted)
        return
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
    private getTransform(): Matrix4 {
        return this.getTransform_serialize()
    }
    private setTransform(transform: Matrix4): void {
        const transform_casted = transform as (Matrix4)
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
    // private getBorderStyle(): EdgeStyles {
    //     return this.getBorderStyle_serialize()
    // }
    private setBorderStyle(borderStyle: Edges<BorderStyle>): void {
        const borderStyle_casted = borderStyle as (Edges<BorderStyle>)
        this.setBorderStyle_serialize(borderStyle_casted)
        return
    }
    private getBorderWidth(): Edges<number> {
        return this.getBorderWidth_serialize()
    }
    private setBorderWidth(borderWidth: Edges<number>): void {
        const borderWidth_casted = borderWidth as (Edges<number>)
        this.setBorderWidth_serialize(borderWidth_casted)
        return
    }
    private getBorderColor(): Edges<number> {
        return this.getBorderColor_serialize()
    }
    private setBorderColor(borderColor: Edges<number>): void {
        const borderColor_casted = borderColor as (Edges<number>)
        this.setBorderColor_serialize(borderColor_casted)
        return
    }
    // private getBorderRadius(): Corners<number> {
    //     return this.getBorderRadius_serialize()
    // }
    private setBorderRadius(borderRadius: Corners<number>): void {
        const borderRadius_casted = borderRadius as (Corners<number>)
        this.setBorderRadius_serialize(borderRadius_casted)
        return
    }
    private getShapeMask(): ShapeMask {
        return this.shapeMaskValue!
    }
    private setShapeMask(shapeMask: ShapeMask): void {
        const shapeMask_casted = shapeMask as (ShapeMask)
        if (shapeMask_casted === undefined || shapeMask_casted === null) {
            this.shapeMaskValue = new ShapeMask();
        } else {
            this.shapeMaskValue = shapeMask_casted;
        }
        if (this.shapeMaskValue!.rect !== null) {
            this.setRectMask_serialize(this.shapeMaskValue!.rect!, this.shapeMaskValue!.fillColor, this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth)
        } else if (this.shapeMaskValue!.circle !== null) {
            this.setCircleMask_serialize(this.shapeMaskValue!.circle!, this.shapeMaskValue!.fillColor, this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        } else if (this.shapeMaskValue!.roundRect !== null) {
            this.setRoundRectMask_serialize(this.shapeMask!.roundRect!, this.shapeMaskValue!.fillColor, this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        } else if (this.shapeMaskValue!.oval !== null) {
            this.setOvalMask_serialize(this.shapeMaskValue!.oval!, this.shapeMaskValue!.fillColor, this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        } else if (this.shapeMaskValue!.path !== null) {
            this.setPath_serialize(this.shapeMaskValue!.path!, this.shapeMaskValue!.fillColor, this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        }
    }
    private getShapeClip(): ShapeClip {
        return this.shapeClipValue!
    }
    private setShapeClip(shapeClip: ShapeClip): void {
        if (shapeClip === undefined || shapeClip === null) {
            this.shapeClipValue = new ShapeClip();
        } else {
            this.shapeClipValue = shapeClip;
        }
        if (this.shapeClipValue!.rect !== null) {
            const rectClip = this.shapeClipValue!.rect;
            this.setRectClip_serialize(rectClip!)
        } else if (this.shapeClipValue!.circle !== null) {
            const circle = this.shapeClipValue!.circle;
            this.setCircleClip_serialize(circle!)
        } else if (this.shapeClipValue!.roundRect !== null) {
            const roundRect = this.shapeClipValue!.roundRect;
            this.setRoundRectClip_serialize(roundRect!)
        } else if (this.shapeClipValue!.oval !== null) {
            const oval = this.shapeClipValue!.oval;
            this.setOvalClip_serialize(oval!)
        } else if (this.shapeClipValue!.path !== null) {
            const path = this.shapeClipValue!.path;
            this.setPathClip_serialize(path!)
        }
    }
    private getMarkNodeGroup(): boolean {
        return this.markNodeGroupValue
    }
    private setMarkNodeGroup(markNodeGroup: boolean): void {
        this.markNodeGroupValue = markNodeGroup;
        const markNodeGroup_casted = this.markNodeGroupValue as (boolean)
        this.setMarkNodeGroup_serialize(markNodeGroup_casted)
        return
    }
    private getLengthMetricsUnit(): LengthMetricsUnit {
        return this.getLengthMetricsUnit_serialize()
    }
    private setLengthMetricsUnit(lengthMetricsUnit: LengthMetricsUnit): void {
        this.lengthMetricsUnitValue = lengthMetricsUnit
        return
    }
    private appendChild_serialize(node: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNode_appendChild(this.peer!.ptr, toPeerPtr(node))
    }
    private insertChildAfter_serialize(child: RenderNode, sibling: RenderNode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let sibling_type : int32 = RuntimeType.UNDEFINED
        sibling_type = runtimeType(sibling)
        if (RuntimeType.OBJECT == sibling_type) {
            thisSerializer.writeInt8(0 as int32)
            const sibling_0  = sibling as RenderNode
            thisSerializer.writeRenderNode(sibling_0)
        }
        else if (RuntimeType.UNDEFINED == sibling_type) {
            thisSerializer.writeInt8(1 as int32)
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
        const retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const retvalType  = retvalDeserializer.readInt8()
        if ((retvalType) == (0))
            return retvalDeserializer.readRenderNode()
        return undefined
    }
    private getFirstChild_serialize(): RenderNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getFirstChild(this.peer!.ptr)
        const retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const retvalType  = retvalDeserializer.readInt8()
        if ((retvalType) == (0))
            return retvalDeserializer.readRenderNode()
        return undefined
    }
    private getNextSibling_serialize(): RenderNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getNextSibling(this.peer!.ptr)
        const retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const retvalType  = retvalDeserializer.readInt8()
        if ((retvalType) == (0))
            return retvalDeserializer.readRenderNode()
        return undefined
    }
    private getPreviousSibling_serialize(): RenderNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getPreviousSibling(this.peer!.ptr)
        const retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const retvalType  = retvalDeserializer.readInt8()
        if ((retvalType) == (0))
            return retvalDeserializer.readRenderNode()
        return undefined
    }
    private draw_serialize(context: DrawContext): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(context)
        ArkUIGeneratedNativeModule._RenderNode_draw(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Size = retvalDeserializer.readSize()
        return returnResult
    }
    private setSize_serialize(size: Size): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSize(size)
        thisSerializer.writeInt32(this.lengthMetricsUnitValue)
        ArkUIGeneratedNativeModule._RenderNode_setSize(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setPosition_serialize(position: Position): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGraphicsPosition(position)
        thisSerializer.writeInt32(this.lengthMetricsUnitValue)
        ArkUIGeneratedNativeModule._RenderNode_setPosition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFrame_serialize(): Frame {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getFrame(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Frame = retvalDeserializer.readFrame()
        return returnResult
    }
    private setFrame_serialize(frame: Frame): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFrame(frame)
        thisSerializer.writeInt32(this.lengthMetricsUnitValue)
        ArkUIGeneratedNativeModule._RenderNode_setFrame(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getPivot_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getPivot(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Vector2 = retvalDeserializer.readVector2()
        return returnResult
    }
    private setPivot_serialize(pivot: Vector2): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVector2(pivot)
        ArkUIGeneratedNativeModule._RenderNode_setPivot(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getScale_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getScale(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Vector2 = retvalDeserializer.readVector2()
        return returnResult
    }
    private setScale_serialize(scale: Vector2): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVector2(scale)
        ArkUIGeneratedNativeModule._RenderNode_setScale(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTranslation_serialize(): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getTranslation(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Vector2 = retvalDeserializer.readVector2()
        return returnResult
    }
    private setTranslation_serialize(translation: Vector2): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVector2(translation)
        ArkUIGeneratedNativeModule._RenderNode_setTranslation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getRotation_serialize(): Vector3 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getRotation(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Vector3 = retvalDeserializer.readVector3()
        return returnResult
    }
    private setRotation_serialize(rotation: Vector3): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVector3(rotation)
        thisSerializer.writeInt32(this.lengthMetricsUnitValue)
        ArkUIGeneratedNativeModule._RenderNode_setRotation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTransform_serialize(): Matrix4 {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getTransform(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
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
        const returnResult : Matrix4 = ([buffer_value0, buffer_value1, buffer_value2, buffer_value3, buffer_value4, buffer_value5, buffer_value6, buffer_value7, buffer_value8, buffer_value9, buffer_value10, buffer_value11, buffer_value12, buffer_value13, buffer_value14, buffer_value15] as Matrix4)
        return returnResult
    }
    private setTransform_serialize(transform: Matrix4): void {
        const thisSerializer : Serializer = Serializer.hold()
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Vector2 = retvalDeserializer.readVector2()
        return returnResult
    }
    private setShadowOffset_serialize(shadowOffset: Vector2): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeVector2(shadowOffset)
        thisSerializer.writeInt32(this.lengthMetricsUnitValue)
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
    // private getBorderStyle_serialize(): EdgeStyles {
    //     const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderStyle(this.peer!.ptr)
    //     let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
    //     const returnResult : EdgeStyles = retvalDeserializer.readEdgeStyles()
    //     return returnResult
    // }
    private setBorderStyle_serialize(borderStyle: Edges<BorderStyle>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGraphicsEdgeStyles(borderStyle)
        ArkUIGeneratedNativeModule._RenderNode_setBorderStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getBorderWidth_serialize(): Edges<number> {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderWidth(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Edges<number> = retvalDeserializer.readEdgesNumber()
        return returnResult
    }
    private setBorderWidth_serialize(borderWidth: Edges<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEdgesNumber(borderWidth)
        thisSerializer.writeInt32(this.lengthMetricsUnitValue)
        ArkUIGeneratedNativeModule._RenderNode_setBorderWidth(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getBorderColor_serialize(): Edges<number> {
        const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderColor(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Edges<number> = retvalDeserializer.readEdgesNumber()
        return returnResult
    }
    private setBorderColor_serialize(borderColor: Edges<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEdgesNumber(borderColor)
        ArkUIGeneratedNativeModule._RenderNode_setBorderColor(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    // private getBorderRadius_serialize(): BorderRadiuses_graphics {
    //     const retval  = ArkUIGeneratedNativeModule._RenderNode_getBorderRadius(this.peer!.ptr)
    //     let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
    //     const returnResult : BorderRadiuses_graphics = retvalDeserializer.readBorderRadiuses_graphics()
    //     return returnResult
    // }
    private setBorderRadius_serialize(borderRadius: Corners<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBorderRadiuses_graphics(borderRadius)
        thisSerializer.writeInt32(this.lengthMetricsUnitValue)
        ArkUIGeneratedNativeModule._RenderNode_setBorderRadius(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setShapeMask_serialize(shapeMask: ShapeMask): void {

        ArkUIGeneratedNativeModule._RenderNode_setShapeMask(this.peer!.ptr, toPeerPtr(shapeMask))
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
    private setRectMask_serialize(rect: Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(rect)
        ArkUIGeneratedNativeModule._RenderNode_setRectMask(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private setCircleMask_serialize(circle: Circle, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCircle(circle)
        ArkUIGeneratedNativeModule._RenderNode_setCircleMask(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private setRoundRectMask_serialize(roundRect: RoundRect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRoundRect(roundRect)
        ArkUIGeneratedNativeModule._RenderNode_setRoundRectMask(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private setOvalMask_serialize(rect: Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(rect)
        ArkUIGeneratedNativeModule._RenderNode_setOvalMask(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private setPath_serialize(path: CommandPath, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCommandPath(path)
        ArkUIGeneratedNativeModule._RenderNode_setPath(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private setRectClip_serialize(rect: Rect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(rect)
        ArkUIGeneratedNativeModule._RenderNode_setRectClip(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setCircleClip_serialize(circle: Circle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCircle(circle)
        ArkUIGeneratedNativeModule._RenderNode_setCircleClip(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setRoundRectClip_serialize(roundRect: RoundRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRoundRect(roundRect)
        ArkUIGeneratedNativeModule._RenderNode_setRoundRectClip(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOvalClip_serialize(rect: Rect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRect(rect)
        ArkUIGeneratedNativeModule._RenderNode_setOvalClip(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setPathClip_serialize(path: CommandPath): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCommandPath(path)
        ArkUIGeneratedNativeModule._RenderNode_setPathClip(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFrameNode(frameNode: WeakRef<FrameNode>) {
        this.frameNode_ = frameNode;
    }
}
