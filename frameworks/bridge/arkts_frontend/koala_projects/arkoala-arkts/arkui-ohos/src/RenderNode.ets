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

import { NodePosition, Rect, Circle, RoundRect, CommandPath, Size, Frame, Vector2, Vector3, Matrix4, NodeEdges, Corners, ShapeMask, ShapeClip, LengthMetricsUnit, DrawContext } from "./Graphics"
import { BorderStyle } from "./component/enums"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, InteropNativeModule } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { PeerNode } from "./PeerNode"
import { FrameNode } from "./FrameNode"
import { ArkUIAniModule } from "arkui.ani"
import { BusinessError } from '#external';
import hilog from '@ohos.hilog'
import { RenderNodeExtender, NodeEdgeStyles, EdgeNumber, BorderRadiuses_graphics } from "./framework";

export type DrawCallback = (context: DrawContext) => void;
export class RenderNodeInternal {
    public static fromPtr(ptr: KPointer): RenderNode {
        const obj : RenderNode = new RenderNode()
        obj.peer = new Finalizable(ptr, RenderNode.getFinalizer())
        return obj
    }
}

const ERROR_CODE_NODE_IS_ADOPTED = 106206;
const ERROR_CODE_NO_ERROR = 0;

export class RenderNode implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    private type?: string;  // use for transfer
    private childrenList: RenderNode[] = []
    private parentRenderNode: WeakRef<RenderNode> | null = null
    private lengthMetricsUnitValue: LengthMetricsUnit = LengthMetricsUnit.DEFAULT
    private borderStyleValue: NodeEdges<BorderStyle> | undefined = undefined
    private borderWidthValue: NodeEdges<number> | undefined = undefined;
    private borderColorValue: NodeEdges<number> | undefined = undefined;
    private borderRadiusValue: Corners<number> | undefined = undefined;
    private shapeMaskValue: ShapeMask | undefined = undefined;
    private shapeClipValue: ShapeClip | undefined = undefined;
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
    get position(): NodePosition {
        return { x: this.frameValue.x, y: this.frameValue.y }
    }
    set position(position: NodePosition) {
        if (position === undefined || position === null) {
            this.frameValue.x = 0;
            this.frameValue.y = 0;
        } else {
            this.frameValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(position.x, 0) as number
            this.frameValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(position.y, 0) as number
        }
        const position_casted: NodePosition = { x: this.frameValue.x, y: this.frameValue.y }
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
    get borderStyle(): NodeEdges<BorderStyle> | undefined {
        return this.borderStyleValue
    }
    set borderStyle(borderStyle: NodeEdges<BorderStyle>) {
        this.setBorderStyle(borderStyle);
        this.borderStyleValue = borderStyle;
    }
    get borderWidth(): NodeEdges<number> | undefined {
        return this.borderWidthValue
    }
    set borderWidth(borderWidth: NodeEdges<number>) {
        if (borderWidth === undefined || borderWidth === null) {
            this.borderWidthValue = { left: 0, top: 0, right: 0, bottom: 0 } as NodeEdges<number>
        } else {
            this.borderWidthValue = borderWidth;
        }
        const borderWidth_casted = this.borderWidthValue as NodeEdges<number>
        this.setBorderWidth(borderWidth_casted)
    }
    get borderColor(): NodeEdges<number> | undefined {
        return this.borderColorValue
    }
    set borderColor(borderColor: NodeEdges<number>) {
        if (borderColor === undefined || borderColor === null) {
            this.borderColorValue = { left: 0XFF000000, top: 0XFF000000, right: 0XFF000000, bottom: 0XFF000000 };
        } else {
            this.borderColorValue = borderColor;
        }
        const borderColor_casted = this.borderColorValue as NodeEdges<number>
        this.setBorderColor(borderColor_casted)
    }
    get borderRadius(): Corners<number> | undefined {
        return this.borderRadiusValue;
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
    get shapeMask(): ShapeMask | undefined {
        return this.shapeMaskValue;
    }
    set shapeMask(shapeMask: ShapeMask) {
        this.setShapeMask(shapeMask)
    }
    get shapeClip(): ShapeClip | undefined {
        return this.shapeClipValue;
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
        const retval  = RenderNodeExtender.constructorRenderNode(id)
        return retval
    }
    constructor(type?: string) {
        this.type = type;
        if (type === 'BuilderRootFrameNode' || type === 'CustomFrameNode') {
            return
        }
        const peerId = PeerNode.nextId()
        const peerPtr: KPointer = RenderNode.ctor_rendernode(peerId, this.draw)
        ArkUIAniModule._SetDrawCallback(peerPtr, this.draw)
        this.peer = new Finalizable(peerPtr, RenderNode.getFinalizer())
        this.setClipToFrame(true)
    }

    // KPointer
    constructor(nodePtr: KPointer, type?: string) {
        this.type = type;
        if (type === 'BuilderRootFrameNode' || type === 'CustomFrameNode') {
            return
        }
        const peerPtr: KPointer = ArkUIAniModule._CreateRenderNodePeerWithNodePtr(nodePtr);
        ArkUIAniModule._SetDrawCallback(peerPtr, this.draw)
        this.peer = new Finalizable(peerPtr, RenderNode.getFinalizer())
        this.setClipToFrame(true)
    }

    static getFinalizer(): KPointer {
        return RenderNodeExtender.getDestroy()
    }
    public getParentNode(): RenderNode | undefined {
        return this.parentRenderNode?.deref() ?? undefined;
    }
    public appendChild(node: RenderNode): void {
        const node_casted = node as (RenderNode)
        if (this.childrenList.findIndex(element => element === node_casted) !== -1) {
            return
        }
        let result = RenderNodeExtender.appendChild(this, node_casted);
        if (result === ERROR_CODE_NODE_IS_ADOPTED) {
            const error = Error("The parameter 'node' is invalid: its corresponding FrameNode cannot be adopted.");
            throw new BusinessError(100025, error);
        }
        this.childrenList.push(node)
        node.parentRenderNode = new WeakRef<RenderNode>(this)
        return
    }
    public insertChildAfter(child: RenderNode, sibling: RenderNode | null): void {
        let indexOfNode = this.childrenList.findIndex(element => element === child)
        if (indexOfNode !== -1) {
            return
        }
        let indexOfSibling = this.childrenList.findIndex(element => element === sibling)
        if (indexOfSibling === -1) {
            sibling = null;
        }
        let result = ERROR_CODE_NO_ERROR;
        let childrenListStartPosition: number = 0;
        if (sibling === undefined || sibling === null) {
            result = RenderNodeExtender.insertChild(this, child);
        } else {
            result = RenderNodeExtender.insertChildAfter(this, child, sibling!);
            childrenListStartPosition = indexOfSibling + 1;
        }
        if (result === ERROR_CODE_NODE_IS_ADOPTED) {
            const error = Error("The parameter 'child' is invalid: its corresponding FrameNode cannot be adopted.");
            throw new BusinessError(100025, error);
        }
        this.childrenList.splice(childrenListStartPosition, 0, child);
        child.parentRenderNode = new WeakRef<RenderNode>(this);
        return
    }
    public removeChild(node: RenderNode): void {
        const node_casted = node as (RenderNode)
        const index = this.childrenList.findIndex(element => element === node_casted);
        if (index === -1) {
            return
        }
        const child = this.childrenList[index as int32]
        child.parentRenderNode = null
        this.childrenList.splice(index, 1)
        RenderNodeExtender.removeChild(this, node_casted)
        return
    }
    public clearChildren(): void {
        this.childrenList = []
        RenderNodeExtender.clearChildren(this)
        return
    }
    public getChild(index: number): RenderNode | null {
        if (this.childrenList.length > index && index >= 0) {
            return this.childrenList[index as int32]
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
        RenderNodeExtender.invalidate(this)
        return
    }
    dispose() {
        this.frameNode_?.deref()?.resetNodePtr()
        if (this.peer?.ptr) {
            this.peer?.close();
        }
    }
    resetNodePtr() {
        if (this.peer?.ptr) {
            this.peer?.close();
        }
    }
    private setBackgroundColor(backgroundColor: number): void {
        RenderNodeExtender.setBackgroundColor(this, backgroundColor)
        return
    }
    private setClipToFrame(clipToFrame: boolean): void {
        RenderNodeExtender.setClipToFrame(this, clipToFrame)
        return
    }
    private setOpacity(opacity: number): void {
        RenderNodeExtender.setOpacity(this, opacity)
        return
    }
    private setSize(size: Size): void {
        const lengthMetricsUnitValue = this.lengthMetricsUnitValue as int32;
        RenderNodeExtender.setSize(this, size, lengthMetricsUnitValue)
        return
    }
    private setPosition(position: NodePosition): void {
        const position_casted = position as (Vector2)
        const lengthMetricsUnitValue = this.lengthMetricsUnitValue as int32;
        RenderNodeExtender.setPosition(this, position_casted, lengthMetricsUnitValue)
        return
    }
    private setPivot(pivot: Vector2): void {
        RenderNodeExtender.setPivot(this, pivot)
        return
    }
    private setScale(scale: Vector2): void {
        RenderNodeExtender.setScale(this, scale)
        return
    }
    private setTranslation(translation: Vector2): void {
        RenderNodeExtender.setTranslation(this, translation)
        return
    }
    private setRotation(rotation: Vector3): void {
        const lengthMetricsUnitValue = this.lengthMetricsUnitValue as int32;
        RenderNodeExtender.setRotation(this, rotation, lengthMetricsUnitValue)
        return
    }
    private setTransform(transform: Matrix4): void {
        RenderNodeExtender.setTransform(this, transform)
        return
    }
    private setShadowColor(shadowColor: number): void {
        RenderNodeExtender.setShadowColor(this, shadowColor)
        return
    }
    private setShadowOffset(shadowOffset: Vector2): void {
        const lengthMetricsUnitValue = this.lengthMetricsUnitValue as int32;
        RenderNodeExtender.setShadowOffset(this, shadowOffset, lengthMetricsUnitValue)
        return
    }
    private setLabel(label: string): void {
        RenderNodeExtender.setLabel(this, label)
        return
    }
    private setShadowAlpha(shadowAlpha: number): void {
        RenderNodeExtender.setShadowAlpha(this, shadowAlpha)
        return
    }
    private setShadowElevation(shadowElevation: number): void {
        RenderNodeExtender.setShadowElevation(this, shadowElevation)
        return
    }
    private setShadowRadius(shadowRadius: number): void {
        RenderNodeExtender.setShadowRadius(this, shadowRadius)
        return
    }
    private setBorderStyle(borderStyle: NodeEdges<BorderStyle>): void {
        const top = (borderStyle.top === null || undefined) ? BorderStyle.Dotted : borderStyle.top;
        const left = (borderStyle.left === null || undefined) ? BorderStyle.Dotted : borderStyle.left;
        const bottom = (borderStyle.bottom === null || undefined) ? BorderStyle.Dotted : borderStyle.bottom;
        const right = (borderStyle.right === null || undefined) ? BorderStyle.Dotted : borderStyle.right;
        const edgesBorderStyle = { top: top!, left: left!, bottom: bottom!, right: right! } as NodeEdgeStyles;
        RenderNodeExtender.setBorderStyle(this, edgesBorderStyle);
        return
    }
    private setBorderWidth(borderWidth: NodeEdges<number>): void {
        const top = (borderWidth.top === null || undefined) ? 0.0 : borderWidth.top;
        const left = (borderWidth.left === null || undefined) ? 0.0 : borderWidth.left;
        const bottom = (borderWidth.bottom === null || undefined) ? 0.0 : borderWidth.bottom;
        const right = (borderWidth.right === null || undefined) ? 0.0 : borderWidth.right;
        const edgesBorderWidth = { top: top!, left: left!, bottom: bottom!, right: right! } as EdgeNumber;
        const lengthMetricsUnitValue = this.lengthMetricsUnitValue as int32;
        RenderNodeExtender.setBorderWidth(this, edgesBorderWidth, lengthMetricsUnitValue);
        return
    }
    private setBorderColor(borderColor: NodeEdges<number>): void {
        const top = ((borderColor.top === null || undefined) ? 0xFF000000 : borderColor.top) as number;
        const left = ((borderColor.left === null || undefined) ? 0xFF000000 : borderColor.left) as number;
        const bottom = ((borderColor.bottom === null || undefined) ? 0xFF000000 : borderColor.bottom) as number;
        const right = ((borderColor.right === null || undefined) ? 0xFF000000 : borderColor.right) as number;
        const edgesBorderColor = { top: top!, left: left!, bottom: bottom!, right: right! } as EdgeNumber;
        RenderNodeExtender.setBorderColor(this, edgesBorderColor);
        return
    }
    private setBorderRadius(borderRadius: Corners<number>): void {
        const cornersBorderRadius = { topLeft: borderRadius.topLeft, topRight: borderRadius.topRight,
            bottomLeft: borderRadius.bottomLeft, bottomRight: borderRadius.bottomRight } as BorderRadiuses_graphics;
        const lengthMetricsUnitValue = this.lengthMetricsUnitValue as int32;
        RenderNodeExtender.setBorderRadius(this, cornersBorderRadius, lengthMetricsUnitValue);
        return
    }
    private setShapeMask(shapeMask: ShapeMask): void {
        const shapeMask_casted = shapeMask as (ShapeMask)
        if (shapeMask_casted === undefined || shapeMask_casted === null) {
            this.shapeMaskValue = new ShapeMask();
        } else {
            this.shapeMaskValue = shapeMask_casted;
        }
        if (this.shapeMaskValue!.rect !== null) {
            RenderNodeExtender.setRectMask(this, this.shapeMaskValue!.rect!, this.shapeMaskValue!.fillColor,
                this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        } else if (this.shapeMaskValue!.circle !== null) {
            RenderNodeExtender.setCircleMask(this, this.shapeMaskValue!.circle!, this.shapeMaskValue!.fillColor,
                this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        } else if (this.shapeMaskValue!.roundRect !== null) {
            RenderNodeExtender.setRoundRectMask(this, this.shapeMaskValue!.roundRect!, this.shapeMaskValue!.fillColor,
                this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        } else if (this.shapeMaskValue!.oval !== null) {
            RenderNodeExtender.setOvalMask(this, this.shapeMaskValue!.oval!, this.shapeMaskValue!.fillColor,
                this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        } else if (this.shapeMaskValue!.path !== null) {
            RenderNodeExtender.setPath(this, this.shapeMaskValue!.path!, this.shapeMaskValue!.fillColor,
                this.shapeMaskValue!.strokeColor, this.shapeMaskValue!.strokeWidth);
        }
    }
    private setShapeClip(shapeClip: ShapeClip): void {
        if (shapeClip === undefined || shapeClip === null) {
            this.shapeClipValue = new ShapeClip();
        } else {
            this.shapeClipValue = shapeClip;
        }
        if (this.shapeClipValue!.rect !== null) {
            const rectClip = this.shapeClipValue!.rect;
            RenderNodeExtender.setRectClip(this, this.shapeClipValue!.rect!);
        } else if (this.shapeClipValue!.circle !== null) {
            RenderNodeExtender.setCircleClip(this, this.shapeClipValue!.circle!);
        } else if (this.shapeClipValue!.roundRect !== null) {
            RenderNodeExtender.setRoundRectClip(this, this.shapeClipValue!.roundRect!);
        } else if (this.shapeClipValue!.oval !== null) {
            RenderNodeExtender.setOvalClip(this, this.shapeClipValue!.oval!);
        } else if (this.shapeClipValue!.path !== null) {
            RenderNodeExtender.setPathClip(this, this.shapeClipValue!.path!);
        }
    }
    private setMarkNodeGroup(markNodeGroup: boolean): void {
        RenderNodeExtender.setMarkNodeGroup(this, markNodeGroup)
        return
    }
    private setLengthMetricsUnit(lengthMetricsUnit: LengthMetricsUnit): void {
        this.lengthMetricsUnitValue = lengthMetricsUnit
        return
    }
    setFrameNode(frameNode: WeakRef<FrameNode>) {
        this.frameNode_ = frameNode;
    }
}
