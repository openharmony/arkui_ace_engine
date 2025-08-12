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

import { UIContext } from "@ohos/arkui/UIContext"
import { UIContextImpl } from "arkui/handwritten/UIContextImpl"
import { Position, Edges, Size, LengthMetrics, SizeT } from "./Graphics"
import { ArkUIGeneratedNativeModule } from "#components"
import {
    Finalizable, toPeerPtr, KPointer, MaterializedBase, nullptr, KSerializerBuffer, KUint8ArrayPtr, InteropNativeModule
} from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { Serializer } from "./component"
import { ArkUIAniModule } from "arkui.ani"
import { RenderNode, RenderNodeInternal } from "./RenderNode"
import {
    CommonAttribute, ArkCommonMethodPeer, CommonMethod, UIGestureEvent, UICommonEvent, UICommonEventInternal,
    CustomProperty
} from './component/common'
import { ArkBaseNode } from './handwritten/modifiers/ArkBaseNode'
import { ArkQRCodeNode } from './handwritten/modifiers/ArkQRCodeNode'
import { ArkBadgeNode } from './handwritten/modifiers/ArkBadgeNode'
import { ArkProgressNode } from './handwritten/modifiers/ArkProgressNode'
import { ArkLoadingProgressNode } from './handwritten/modifiers/ArkLoadingProgressNode'
import { ArkTextClockNode } from './handwritten/modifiers/ArkTextClockNode'
import { ArkTextTimerNode } from './handwritten/modifiers/ArkTextTimerNode'
import { ArkImageNode } from './handwritten/modifiers/ArkImageNode'
import { ArkListNode } from './handwritten/modifiers/ArkListNode'
import { ArkListItemNode } from './handwritten/modifiers/ArkListItemNode'
import { ArkListItemGroupNode } from './handwritten/modifiers/ArkListItemGroupNode'
import { ArkScrollNode } from './handwritten/modifiers/ArkScrollNode'
import { ArkGridNode } from './handwritten/modifiers/ArkGridNode'
import { ArkGridItemNode } from './handwritten/modifiers/ArkGridItemNode'
import { ArkWaterFlowNode } from './handwritten/modifiers/ArkWaterFlowNode'
import { ArkFlowItemNode } from './handwritten/modifiers/ArkFlowItemNode'
import { ArkColumnNode } from './handwritten/modifiers/ArkColumnNode'
import { ArkRowNode } from './handwritten/modifiers/ArkRowNode'
import { ArkStackNode } from './handwritten/modifiers/ArkStackNode'
import { ArkFlexNode } from './handwritten/modifiers/ArkFlexNode'
import { ArkGridRowNode } from './handwritten/modifiers/ArkGridRowNode'
import { ArkGridColNode } from './handwritten/modifiers/ArkGridColNode'
import { ArkDividerNode } from './handwritten/modifiers/ArkDividerNode'
import { ArkBlankNode } from './handwritten/modifiers/ArkBlankNode'
import { ArkRelativeContainerNode } from './handwritten/modifiers/ArkRelativeContainerNode'
import { ArkSearchNode } from './handwritten/modifiers/ArkSearchNode'
import { ArkSwiperNode } from "./handwritten/modifiers/ArkSwiperNode";
import { ArkTextAreaNode } from './handwritten/modifiers/ArkTextAreaNode'
import { ArkTextInputNode } from './handwritten/modifiers/ArkTextInputNode'
import { ArkXComponentNode } from "./handwritten/modifiers/ArkXComponentNode"
import { ModifierType } from './handwritten/modifiers/ArkCommonModifier'
import { ListOptions, ListAttribute, ArkListPeer } from './component/list'
import { ListItemOptions, ListItemAttribute, ArkListItemPeer } from './component/listItem'
import { ListItemGroupOptions, ListItemGroupAttribute, ArkListItemGroupPeer } from './component/listItemGroup'
import { Scroller, ScrollAttribute, ArkScrollPeer } from './component/scroll'
import { GridLayoutOptions, GridAttribute, ArkGridPeer } from './component/grid'
import { GridItemOptions, GridItemAttribute, ArkGridItemPeer } from './component/gridItem'
import { WaterFlowOptions, WaterFlowAttribute, ArkWaterFlowPeer } from './component/waterFlow'
import { FlowItemAttribute, ArkFlowItemPeer } from './component/flowItem'
import { ColumnOptions, ColumnAttribute, ArkColumnPeer } from './component/column'
import { RowOptions, RowAttribute, ArkRowPeer } from './component/row'
import { StackOptions, StackAttribute, ArkStackPeer } from './component/stack'
import { FlexOptions, FlexAttribute, ArkFlexPeer } from './component/flex'
import { RelativeContainerAttribute, ArkRelativeContainerPeer } from './component/relativeContainer'
import { GridRowOptions, GridRowAttribute, ArkGridRowPeer } from './component/gridRow'
import { ResourceColor, ResourceStr } from "./component/units"
import { ImageAnalyzerConfig, ImageAIOptions } from "./component/imageCommon"
import { PixelMap, DrawableDescriptor } from "#external"
import { ArkImagePeer, ImageContent, ImageAttribute } from "./component/image";
import { BadgeAttribute, ArkBadgePeer, BadgeParamWithNumber, BadgeParamWithString } from "./component/badge";
import { QRCodeAttribute, ArkQRCodePeer } from './component/qrcode'
import { ProgressOptions, ProgressAttribute, ArkProgressPeer } from './component/progress'
import { LoadingProgressAttribute, ArkLoadingProgressPeer } from './component/loadingProgress'
import { TextClockOptions, TextClockAttribute, ArkTextClockPeer } from './component/textClock'
import { TextTimerOptions, ArkTextTimerPeer, TextTimerAttribute } from './component/textTimer'
import { GridColOptions, GridColAttribute, ArkGridColPeer } from './component/gridCol'
import { DividerAttribute, ArkDividerPeer } from './component/divider'
import { BlankAttribute, ArkBlankPeer } from './component/blank'
import { SearchOptions, SearchAttribute, ArkSearchPeer } from './component/search'
import { SwiperController, SwiperAttribute, ArkSwiperPeer } from './component/swiper'
import { TextAreaOptions, TextAreaAttribute, ArkTextAreaPeer } from './component/textArea'
import { TextInputOptions, TextInputAttribute, ArkTextInputPeer } from './component/textInput'
import { ArkTextNode } from './handwritten/modifiers/ArkTextNode'
import { TextOptions, TextAttribute, ArkTextPeer } from './component/text'
import { XComponentParameters, XComponentOptions, NativeXComponentParameters, XComponentAttribute, TypedXComponentPeerInternal } from "./component/xcomponent"
import { XComponentType } from './component/enums'
import { Deserializer } from "./component/peers/Deserializer";
import { ComponentContent } from './ComponentContent';
import { DrawContext } from './Graphics';
import { JSBuilderNode } from "./BuilderNode"
import { BusinessError } from '#external';
import { Resource } from 'global.resource';
import { ElementIdToCustomProperties } from './handwritten/CommonHandWritten'

export interface CrossLanguageOptions {
    attributeSetting?: boolean;
}
export interface LayoutConstraint {
    maxSize: Size;
    minSize: Size;
    percentReference: Size;
}

export class ArkFrameNodePeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
}

export enum ExpandMode {
    NOT_EXPAND = 0,
    EXPAND = 1,
    LAZY_EXPAND = 2,
}
export class FrameNodeFinalizationRegisterProxy {
    constructor() { }
    public static instance_: FrameNodeFinalizationRegisterProxy = new FrameNodeFinalizationRegisterProxy();
    public static ElementIdToOwningFrameNode_ = new Map<number, FrameNode>();

}

export class FrameNodeInternal {
    public static fromPtr(ptr: KPointer): FrameNode {
        const obj: FrameNode = new FrameNode(undefined)
        obj.peer = new Finalizable(ptr, FrameNode.getFinalizer())
        return obj
    }
}

// @ts-ignore
function GetExactRetValue(data: KSerializerBuffer | KUint8ArrayPtr): Array<byte> {
    // @ts-ignore
    const retval = data as FixedArray<byte>;
    // @ts-ignore
    let exactRetValue: byte[] = new Array<byte>();
    for (let i = 0; i < retval.length; i++) {
        // @ts-ignore
        exactRetValue.push(new Byte(retval[i]));
    }
    return exactRetValue;
}

export class FrameNode implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    uiContext: UIContextImpl | undefined = undefined
    renderNode_: RenderNode | undefined = undefined
    instanceId_?: number;
    // the name of "nodePtr_" is used in ace_engine/interfaces/native/node/native_node_ani.cpp.
    nodePtr_: KPointer | undefined;
    public _nodeId: number = -1;
    protected _commonAttribute: CommonAttribute | undefined = undefined;
    protected _gestureEvent: UIGestureEvent | undefined = undefined;
    nodeType_?: string | undefined = undefined;

    getType(): string {
        return 'CustomFrameNode';
    }

    checkValid(node: FrameNode): boolean {
        return true;
    }
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get commonEvent(): UICommonEvent {
        return this.getCommonEvent()
    }
    get gestureEvent(): UIGestureEvent {
        if (this._gestureEvent === undefined) {
            this._gestureEvent = new UIGestureEvent();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(this))
            let peer = new ArkFrameNodePeer(retval, this._nodeId as int32, "FrameNode", 0);
            this._gestureEvent!.setPeer(peer);
        }
        return this._gestureEvent as UIGestureEvent;
    }
    static ctor_framenode(): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        const retval = ArkUIGeneratedNativeModule._FrameNode_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(uiContext?: UIContext, type?: string, ptr?: KPointer) {
        if ((uiContext) !== (undefined)) {
            this.uiContext = uiContext as UIContextImpl;
            this.instanceId_ = this.uiContext!.instanceId_;
            this.nodeType_ = type;
            if (type === 'ProxyFrameNode') {
                if (ptr) {
                    this.peer = new Finalizable(ptr, FrameNode.getFinalizer());
                    this.nodePtr_ = this.peer?.ptr
                }
                return;
            }
            if (this.getType() === 'BuilderRootFrameNode') {
                this.renderNode_ = new RenderNode(this.getType());
                this.renderNode_!.setFrameNode(new WeakRef<FrameNode>(this));
                return;
            }
            const instanceId = this.instanceId_!.toInt();
            ArkUIAniModule._Common_Sync_InstanceId(instanceId);
            if (this.getType() === undefined || this.getType() === "CustomFrameNode") {
                this.renderNode_ = new RenderNode('CustomFrameNode')
                const ctorPtr: KPointer = ptr ? ptr : FrameNode.ctor_framenode()
                this.peer = new Finalizable(ctorPtr, FrameNode.getFinalizer())
                this.nodePtr_ = this.peer?.ptr
            } else {
                const retval = ptr ? ptr : ArkUIGeneratedNativeModule._FrameNode_createTypedFrameNode(type as string);
                this.peer = new Finalizable(retval, FrameNode.getFinalizer());
                this.nodePtr_ = this.peer?.ptr
            }
            this.renderNode_?.setFrameNode(new WeakRef<FrameNode>(this))
            if (this.renderNode_ && this.getType() === "CustomFrameNode") {
                this.renderNode_!.peer = new Finalizable(ArkUIGeneratedNativeModule._FrameNode_getRenderNode(this.peer!.ptr), RenderNode.getFinalizer());
            }
            this._nodeId = this.getIdByFrameNode_serialize(this);
            ArkUIAniModule._Common_Restore_InstanceId();
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, this);
            this.onDraw_serialize(this.onDraw);
            ArkUIAniModule._SetCustomCallback(this!.peer!.ptr, this.onMeasureInner, this.onLayoutInner);
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FrameNode_getFinalizer();
    }
    public isModifiable(): boolean {
        return this.isModifiable_serialize();
    }
    private onDraw_serialize(drawCallBack: (context: DrawContext) => void): void {
        const thisSerializer: Serializer = Serializer.hold();
        const event_value = drawCallBack;
        thisSerializer.holdAndWriteCallback(event_value);
        ArkUIGeneratedNativeModule._FrameNode_onDraw(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    public appendChild(node: FrameNode): void {
        if (node.getType() === 'ProxyFrameNode' || !this.checkValid(node)) {
            const error = Error('The FrameNode is not modifiable.');
            throw new BusinessError(100021, error);
        }
        const node_casted = node as (FrameNode)
        this.appendChild_serialize(node_casted)
        return
    }
    public addComponentContent<T = undefined>(content: ComponentContent<T>) {
        if (content === undefined || content === null || content.getFrameNode() == undefined ||
            content.getFrameNode() == null || content.getNodePtr() == undefined) {
            return;
        }
        if (!this.isModifiable()) {
            throw Error("The FrameNode is not modifiable.");
        }
        const instanceId = this.instanceId_!.toInt();
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        let node = content.getNodeWithoutProxy();
        if (this.peer?.ptr && node) {
            ArkUIAniModule._AddComponent_ToFrameNode(this.peer!.ptr, node!);
            content.setAttachedParent(new WeakRef<FrameNode>(this));
        }
        ArkUIAniModule._Common_Restore_InstanceId();
    }
    public removeComponentContent<T = undefined>(content: ComponentContent<T>) {
        if (content === undefined || content === null || content.getFrameNode() === undefined ||
            content.getFrameNode() === null || content.getNodeWithoutProxy() === undefined || content.getNodeWithoutProxy() === nullptr) {
            return;
        }
        const instanceId = this.instanceId_!.toInt();
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        let node = content.getNodeWithoutProxy();
        if (this.peer?.ptr && node) {
            ArkUIAniModule._RemoveComponent_FromFrameNode(this.peer!.ptr, node!);
            content.setAttachedParent(undefined);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
    }
    public insertChildAfter(child: FrameNode, sibling: FrameNode | null): void {
        if (child === undefined || child === null) {
            return;
        }
        if (child.getType() === 'ProxyFrameNode' || !this.checkValid(child)) {
            const error = Error('The FrameNode is not modifiable.');
            throw new BusinessError(100021, error);
        }
        const child_casted = child as (FrameNode);
        if (sibling === null || sibling === undefined) {
            this.insertChildAfter_serialize(child_casted, null);
        } else {
            const sibling_casted = sibling as (FrameNode);
            this.insertChildAfter_serialize(child_casted, sibling_casted);
        }
        return
    }
    public removeChild(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        this.removeChild_serialize(node_casted)
        return
    }
    public clearChildren(): void {
        this.clearChildren_serialize()
        return
    }
    convertToFrameNode(node: FrameNode, nodeId: number = -1): FrameNode {
        if (nodeId === -1) {
            const instanceId = this.instanceId_!.toInt();
            ArkUIAniModule._Common_Sync_InstanceId(instanceId);
            nodeId = this.getIdByFrameNode_serialize(node);
            ArkUIAniModule._Common_Restore_InstanceId();
        }
        if (nodeId !== -1 && !node.isModifiable()) {
            node._nodeId = nodeId;
            node.uiContext = this.uiContext;
            node.instanceId_ = this.instanceId_;
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(node._nodeId, node);
        }
        return node;
    }
    public getChild(index: number, expandMode?: ExpandMode | undefined): FrameNode | null {
        const index_casted = index as (number);
        let expand_casted: number = 1;
        if (expandMode !== undefined && expandMode !== null) {
            expand_casted = expandMode;
        }
        const child = this.getChild_serialize(index_casted, expand_casted);
        if (child) {
            const nodeId = this.getIdByFrameNode_serialize(child);
            if (nodeId === -1) {
                return null;
            }
            if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                const node = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
                return node === undefined ? null : node;
            }
            return this.convertToFrameNode(child, nodeId);
        }
        return null;
    }
    public getFirstChild(): FrameNode | null {
        const child = this.getFirstChild_serialize();
        if (child) {
            const nodeId = this.getIdByFrameNode_serialize(child);
            if (nodeId === -1) {
                return null;
            }
            if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                const node = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
                return node === undefined ? null : node;
            }
            return this.convertToFrameNode(child, nodeId);
        }
        return null;
    }
    public getNextSibling(): FrameNode | null {
        const child = this.getNextSibling_serialize();
        if (child) {
            const nodeId = this.getIdByFrameNode_serialize(child);
            if (nodeId === -1) {
                return null;
            }
            if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                const node = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
                return node === undefined ? null : node;
            }
            return this.convertToFrameNode(child, nodeId);
        }
        return null;
    }
    public getPreviousSibling(): FrameNode | null {
        const child = this.getPreviousSibling_serialize();
        if (child) {
            const nodeId = this.getIdByFrameNode_serialize(child);
            if (nodeId === -1) {
                return null;
            }
            if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                const node = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
                return node === undefined ? null : node;
            }
            return this.convertToFrameNode(child, nodeId);
        }
        return null;
    }
    public getParent(): FrameNode | null {
        const parent = this.getParent_serialize();
        if (parent) {
            const nodeId = this.getIdByFrameNode_serialize(parent);
            if (nodeId === -1) {
                return null;
            }
            if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                const node = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
                return node === undefined ? null : node;
            }
            return this.convertToFrameNode(parent, nodeId);
        }
        return null;
    }
    public getChildrenCount(): number {
        return this.getChildrenCount_serialize();
    }
    public dispose(): void {
        if (this.peer?.ptr) {
            this.peer?.close();
        }
        this.nodePtr_ = undefined;
        this.renderNode_?.resetNodePtr();
    }
    public resetNodePtr(): void {
        if (this.peer?.ptr) {
            this.peer?.close();
        }
    }
    public getOpacity(): number {
        return this.getOpacity_serialize();
    }
    public getPositionToWindowWithTransform(): Position {
        return this.getPositionToWindowWithTransform_serialize();
    }
    public static getFrameNodeByKey(name: string): FrameNode {
        const name_casted = name as (string);
        return FrameNode.getFrameNodeByKey_serialize(name_casted);
    }
    public getPositionToParent(): Position {
        return this.getPositionToParent_serialize()
    }
    public getPositionToScreen(): Position {
        return this.getPositionToScreen_serialize()
    }
    public getPositionToWindow(): Position {
        return this.getPositionToWindow_serialize()
    }
    public getPositionToParentWithTransform(): Position {
        return this.getPositionToParentWithTransform_serialize()
    }
    public getPositionToScreenWithTransform(): Position {
        return this.getPositionToScreenWithTransform_serialize()
    }
    public getMeasuredSize(): Size {
        return this.getMeasuredSize_serialize()
    }
    public getLayoutPosition(): Position {
        return this.getLayoutPosition_serialize()
    }
    public getUserConfigBorderWidth(): Edges<LengthMetrics> {
        return this.getUserConfigBorderWidth_serialize()
    }
    public getUserConfigPadding(): Edges<LengthMetrics> {
        return this.getUserConfigPadding_serialize()
    }
    public getUserConfigMargin(): Edges<LengthMetrics> {
        return this.getUserConfigMargin_serialize()
    }
    public getUserConfigSize(): SizeT<LengthMetrics> {
        return this.getUserConfigSize_serialize()
    }
    public getId(): string {
        return ArkUIGeneratedNativeModule._FrameNode_getId(this.peer!.ptr);
    }
    public getUniqueId(): number {
        return ArkUIGeneratedNativeModule._FrameNode_getUniqueId(this.peer!.ptr);
    }
    public isVisible(): boolean {
        return ArkUIGeneratedNativeModule._FrameNode_isVisible(this.peer!.ptr);
    }
    public isClipToFrame(): boolean {
        return ArkUIGeneratedNativeModule._FrameNode_isClipToFrame(this.peer!.ptr);
    }
    public isAttached(): boolean {
        return ArkUIGeneratedNativeModule._FrameNode_isAttached(this.peer!.ptr);
    }
    public getInspectorInfo(): Object {
        return ArkUIGeneratedNativeModule._FrameNode_getInspectorInfo(this.peer!.ptr);
    }
    public onDraw(context: DrawContext): void {
    }
    public onMeasureInner(width1: number, height1: number, width2: number, height2: number,
        width3: number, height3: number): void {
        const maxSize: Size = { width: width1, height: height1 };
        const minSize: Size = { width: width2, height: height2 };
        const percentReference: Size = { width: width3, height: height3 };
        const constraint: LayoutConstraint = { maxSize: maxSize, minSize: minSize, percentReference: percentReference };
        this.onMeasure(constraint);
    }
    public onMeasure(constraint: LayoutConstraint): void {
        ArkUIAniModule._OnMeasure_InnerMeasure(this!.peer!.ptr);
    }
    public onLayoutInner(x: number, y: number): void {
        const position: Position = { x: x, y: y };
        this.onLayout(position);
    }
    public onLayout(position: Position): void {
        ArkUIAniModule._OnLayout_InnerLayout(this!.peer!.ptr);
    }
    public setMeasuredSize(size: Size): void {
        const width = Math.max(size.width, 0);
        const height = Math.max(size.height, 0);
        const size_casted = { width: width, height: height } as (Size);
        this.setMeasuredSize_serialize(size_casted);
        return;
    }
    public setLayoutPosition(position: Position): void {
        const position_casted = position as (Position);
        this.setLayoutPosition_serialize(position_casted);
        return;
    }
    public measure(constraint: LayoutConstraint): void {
        const constraint_casted = constraint as (LayoutConstraint);
        const instanceId = this.instanceId_!.toInt();
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        this.measure_serialize(constraint_casted);
        ArkUIAniModule._Common_Restore_InstanceId();
        return;
    }
    public layout(position: Position): void {
        const position_casted = position as (Position);
        const instanceId = this.instanceId_!.toInt();
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        this.layout_serialize(position_casted);
        ArkUIAniModule._Common_Restore_InstanceId();
        return;
    }
    private setMeasuredSize_serialize(size: Size): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.writeSize(size);
        ArkUIGeneratedNativeModule._FrameNode_setMeasuredSize(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private setLayoutPosition_serialize(position: Position): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.writeGraphicsPosition(position);
        ArkUIGeneratedNativeModule._FrameNode_setLayoutPosition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private measure_serialize(constraint: LayoutConstraint): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.writeLayoutConstraint(constraint);
        ArkUIGeneratedNativeModule._FrameNode_measure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    private layout_serialize(position: Position): void {
        const thisSerializer: Serializer = Serializer.hold();
        thisSerializer.writeGraphicsPosition(position);
        ArkUIGeneratedNativeModule._FrameNode_layout(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    public setNeedsLayout(): void {
        this.setNeedsLayout_serialize();
        return;
    }
    private setNeedsLayout_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_setNeedsLayout(this.peer!.ptr);
    }
    public invalidate(): void {
        ArkUIGeneratedNativeModule._FrameNode_invalidate(this.peer!.ptr);
    };
    public disposeTree(): void {
        ArkUIGeneratedNativeModule._FrameNode_disposeTree(this.peer!.ptr);
    };
    public setCrossLanguageOptions(options: CrossLanguageOptions): void {
        let setting: boolean = options.attributeSetting ? options.attributeSetting! : false;
        ArkUIGeneratedNativeModule._FrameNode_setCrossLanguageOptions(this.peer!.ptr, setting);
    }
    public getCrossLanguageOptions(): CrossLanguageOptions {
        let option: boolean = ArkUIGeneratedNativeModule._FrameNode_getCrossLanguageOptions(this.peer!.ptr);
        const crossLanguageOptions: CrossLanguageOptions = {
            attributeSetting: option,
        };
        return crossLanguageOptions;
    }
    public isTransferred(): boolean {
        return false;
    }
    private getCommonEvent(): UICommonEvent {
        return this.getCommonEvent_serialize()
    }
    private getCommonEvent_serialize(): UICommonEvent {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getCommonEvent(this.peer!.ptr)
        const obj: UICommonEvent = UICommonEventInternal.fromPtr(retval)
        return obj
    }
    private isModifiable_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNode_isModifiable(this.peer!.ptr)
        return retval
    }
    private appendChild_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_appendChild(this.peer!.ptr, toPeerPtr(node))
    }
    private insertChildAfter_serialize(child: FrameNode, sibling: FrameNode | null): void {
        if (sibling === null || sibling === undefined) {
            ArkUIGeneratedNativeModule._FrameNode_insertChildAfter(this.peer!.ptr, toPeerPtr(child), nullptr);
        } else {
            ArkUIGeneratedNativeModule._FrameNode_insertChildAfter(this.peer!.ptr, toPeerPtr(child),
                toPeerPtr(sibling!));
        }
    }
    private removeChild_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_removeChild(this.peer!.ptr, toPeerPtr(node));
    }
    private clearChildren_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_clearChildren(this.peer!.ptr);
    }
    private getChild_serialize(index: number, expandMode: number): FrameNode | null {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getChild(this.peer!.ptr, index, expandMode);
        if (retval) {
            const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getFirstChild_serialize(): FrameNode | null {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFirstChild(this.peer!.ptr);
        if (retval) {
            const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getNextSibling_serialize(): FrameNode | null {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getNextSibling(this.peer!.ptr);
        if (retval) {
            const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getPreviousSibling_serialize(): FrameNode | null {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPreviousSibling(this.peer!.ptr);
        if (retval) {
            const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getParent_serialize(): FrameNode | null {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getParent(this.peer!.ptr);
        if (retval) {
            const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getChildrenCount_serialize(): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getChildrenCount(this.peer!.ptr);
        return retval;
    }
    private dispose_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_dispose(this.peer!.ptr);
    }
    private getOpacity_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getOpacity(this.peer!.ptr);
        return retval;
    }
    private getPositionToWindowWithTransform_serialize(): Position {
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPositionToWindowWithTransform(this.peer!.ptr) as FixedArray<byte>;
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>;
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]));
        }
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length!.toInt());
        const returnResult: Position = retvalDeserializer.readGraphicsPosition();
        return returnResult;
    }
    private static getFrameNodeByKey_serialize(name: string): FrameNode {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(name)
        const obj: FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    public getIdByFrameNode(node: FrameNode): number {
        const node_casted = node as (FrameNode);
        return this.getIdByFrameNode_serialize(node_casted);
    }
    private getIdByFrameNode_serialize(node: FrameNode): number {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(this.peer!.ptr, toPeerPtr(node));
        return retval;
    }
    public moveTo(targetParent: FrameNode, index?: number): void {
        if (targetParent === undefined || targetParent === null) {
            return;
        }
        let index_casted: number = -1;
        if (index !== undefined && index !== null) {
            index_casted = index;
        }
        const oldParent = this.getParent();
        if (oldParent && !oldParent.isModifiable() || !targetParent.isModifiable() || !targetParent.checkValid(this)) {
            const error = Error('The FrameNode is not modifiable.');
            throw new BusinessError(100021, error);
        }
        const targetParent_casted = targetParent as (FrameNode);
        this.moveTo_serialize(targetParent_casted, index_casted);
        return;
    }
    private moveTo_serialize(targetParent: FrameNode, index: number): void {
        ArkUIGeneratedNativeModule._FrameNode_moveTo(this.peer!.ptr, toPeerPtr(targetParent), index);
    }

    public getFirstChildIndexWithoutExpand(): number {
        return this.getFirstChildIndexWithoutExpand_serialize();
    }
    public getLastChildIndexWithoutExpand(): number {
        return this.getLastChildIndexWithoutExpand_serialize();
    }

    private getFirstChildIndexWithoutExpand_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFirstChildIndexWithoutExpand(this.peer!.ptr);
        return retval;
    }
    private getLastChildIndexWithoutExpand_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getLastChildIndexWithoutExpand(this.peer!.ptr);
        return retval;
    }
    public static getAttachedFrameNodeById(id: string): FrameNode {
        const id_casted = id;
        return FrameNode.getAttachedFrameNodeById_serialize(id_casted);
    }
    public static getFrameNodeById(id: number): FrameNode {
        const id_casted = id;
        return FrameNode.getFrameNodeById_serialize(id_casted);
    }
    public static getFrameNodeByUniqueId(id: number): FrameNode {
        const id_casted = id;
        return FrameNode.getFrameNodeByUniqueId_serialize(id_casted);
    }
    private static getAttachedFrameNodeById_serialize(id: string): FrameNode {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getAttachedFrameNodeById(id);
        const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
        return obj;
    }
    private static getFrameNodeById_serialize(id: number): FrameNode {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeById(id);
        const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
        return obj;
    }
    private static getFrameNodeByUniqueId_serialize(id: number): FrameNode {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByUniqueId(id);
        const obj: FrameNode = FrameNodeInternal.fromPtr(retval);
        return obj;
    }
    private getPositionToParent_serialize(): Position {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPositionToParent(this.peer!.ptr);
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Position = retvalDeserializer.readGraphicsPosition();
        return returnResult;
    }
    private getPositionToScreen_serialize(): Position {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPositionToScreen(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult: Position = retvalDeserializer.readGraphicsPosition()
        return returnResult
    }
    private getPositionToWindow_serialize(): Position {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPositionToWindow(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Position = retvalDeserializer.readGraphicsPosition()
        return returnResult
    }
    private getPositionToParentWithTransform_serialize(): Position {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPositionToParentWithTransform(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Position = retvalDeserializer.readGraphicsPosition()
        return returnResult
    }
    private getPositionToScreenWithTransform_serialize(): Position {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPositionToScreenWithTransform(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Position = retvalDeserializer.readGraphicsPosition()
        return returnResult
    }
    private getPositionToWindowWithTransform1_serialize(): Position {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getPositionToWindowWithTransform1(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Position = retvalDeserializer.readGraphicsPosition()
        return returnResult
    }
    private getMeasuredSize_serialize(): Size {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getMeasuredSize(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Size = retvalDeserializer.readSize()
        return returnResult
    }
    private getLayoutPosition_serialize(): Position {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getLayoutPosition(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Position = retvalDeserializer.readGraphicsPosition()
        return returnResult
    }
    private getUserConfigBorderWidth_serialize(): Edges<LengthMetrics> {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getUserConfigBorderWidth(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Edges<LengthMetrics> = retvalDeserializer.readEdgesLengthMetrics()
        return returnResult
    }
    private getUserConfigPadding_serialize(): Edges<LengthMetrics> {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getUserConfigPadding(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Edges<LengthMetrics> = retvalDeserializer.readEdgesLengthMetrics()
        return returnResult
    }
    private getUserConfigMargin_serialize(): Edges<LengthMetrics> {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getUserConfigMargin(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: Edges<LengthMetrics> = retvalDeserializer.readEdgesLengthMetrics()
        return returnResult
    }
    private getUserConfigSize_serialize(): SizeT<LengthMetrics> {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getUserConfigSize(this.peer!.ptr)
        const exactRetValue = GetExactRetValue(retval);
        let retvalDeserializer: Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult: SizeT<LengthMetrics> = retvalDeserializer.readSizeLengthMetrics()
        return returnResult
    }
    public reuse(): void {
        this.reuse_serialize()
        return
    }
    public recycle(): void {
        this.recycle_serialize()
        return
    }
    private reuse_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_reuse(this.peer!.ptr);
    }
    private recycle_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_recycle(this.peer!.ptr);
    }
    public getRenderNode(): RenderNode | null {
        return this.renderNode_ ? this.renderNode_! : null;
    }
    public static getFrameNodePtr(node: FrameNode): KPointer {
        const node_casted = node as (FrameNode)
        return FrameNode.getFrameNodePtr_serialize(node_casted)
    }
    private static getFrameNodePtr_serialize(node: FrameNode): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node))
        return retval
    }
    get commonAttribute(): CommonMethod {
        if (this._commonAttribute === undefined) {
            let baseNode = new ArkBaseNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(this))
            let peer = new ArkFrameNodePeer(retval, this._nodeId!.toInt(), "FrameNode", 0);
            baseNode.setPeer(peer);
            this._commonAttribute = baseNode as CommonAttribute;
        }
        return this._commonAttribute!;
    }
    public static createTypedFrameNode(type: string): FrameNode {
        const type_casted = type
        return FrameNode.createTypedFrameNode_serialize(type_casted)
    }
    private static createTypedFrameNode_serialize(type: string): FrameNode {
        const retval = ArkUIGeneratedNativeModule._FrameNode_createTypedFrameNode(type)
        const obj: FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    public getNodeType(): string {
        return this.getNodeType_serialize()
    }
    private getNodeType_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._FrameNode_getNodeType(this.peer!.ptr)
        return retval
    }
    public getCustomProperty(name: string): CustomProperty {
        const name_casted = name as (string);
        const nodeId = this._nodeId;
        if (ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
            const customProperties = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
            if (customProperties) {
                return customProperties.get(name_casted);
            }
        }
        return ArkUIAniModule._Common_getCustomProperty(this!.peer!.ptr, name_casted);
    }
}
class ImmutableFrameNode extends FrameNode {
    constructor(uiContext: UIContext, type: string, ptr?: KPointer) {
        super(uiContext, type, ptr);
    }
    isModifiable(): boolean {
        return false;
    }
    invalidate(): void {
        return;
    }
    appendChild(node: FrameNode): void {
        const error = Error('The FrameNode is not modifiable.');
        throw new BusinessError(100021, error);
    }
    insertChildAfter(child: FrameNode, sibling: FrameNode | null): void {
        const error = Error('The FrameNode is not modifiable.');
        throw new BusinessError(100021, error);
    }
    removeChild(node: FrameNode): void {
        const error = Error('The FrameNode is not modifiable.');
        throw new BusinessError(100021, error);
    }
    clearChildren(): void {
        const error = Error('The FrameNode is not modifiable.');
        throw new BusinessError(100021, error);
    }
}

export class ProxyFrameNode extends ImmutableFrameNode {
    constructor(uiContext: UIContext, type: string = 'ProxyFrameNode', ptr?: KPointer) {
        super(uiContext, type, ptr);
    }
    getType(): string {
        return 'ProxyFrameNode';
    }
    moveTo(targetParent: FrameNode, index?: number): void {
        const error = Error('The FrameNode is not modifiable.');
        throw new BusinessError(100021, error);
    }
    public getRenderNode(): RenderNode | null {
        return null;
    }
}
export class BuilderRootFrameNode<T> extends ImmutableFrameNode {
    private __BuilderNodeOpt: JSBuilderNode<T> | undefined = undefined;
    constructor(uiContext: UIContext, type: string = 'BuilderRootFrameNode', ptr?: KPointer) {
        super(uiContext, type, ptr);
        if (!ptr) {
            return;
        }
        this.peer = new Finalizable(ptr!, FrameNode.getFinalizer());
        this.nodePtr_ = this.peer?.ptr;
        if (this.renderNode_) {
            this.renderNode_!.peer = new Finalizable(ArkUIGeneratedNativeModule._FrameNode_getRenderNode(ptr), RenderNode.getFinalizer());
        }
    }
    getType(): string {
        return 'BuilderRootFrameNode';
    }
    setJsBuilderNode(weak?: JSBuilderNode<T>) {
        this.__BuilderNodeOpt = weak;
    }
    public resetNodePtr(): void {
        super.resetNodePtr();
        this.__BuilderNodeOpt?.disposeNode();
        this.__BuilderNodeOpt = undefined;
        this._nodeId = -1;
    }
    public disposeNode(): void {
        super.dispose();
        this.__BuilderNodeOpt = undefined;
        this._nodeId = -1;
    }
    public dispose(): void {
        super.dispose();
        this.__BuilderNodeOpt?.disposeNode();
        this.__BuilderNodeOpt = undefined;
        this._nodeId = -1;
    }
}
export interface ResultFrameNode {
    nodeId: int32;
    frameNode: FrameNode;
}
export class FrameNodeUtils {
    static searchNodeInRegisterProxy(ptr: KPointer): FrameNode | null {
        const nodeId = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(ptr, ptr);
        if (nodeId === -1) {
            return null;
        }
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            const node = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
            return node === undefined ? null : node;
        }
        return null;
    }
    static createFrameNode(uiContext: UIContext, ptr: KPointer): FrameNode | null {
        const nodeId = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(ptr, ptr);
        if (nodeId !== -1 && !ArkUIGeneratedNativeModule._FrameNode_isModifiable(ptr)) {
            let frameNode = new ProxyFrameNode(uiContext, "ProxyFrameNode", ptr);
            frameNode._nodeId = nodeId;
            frameNode!.peer!.ptr = ptr;
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(nodeId, frameNode);
            return frameNode;
        }
        return null;
    }
    static createBuilderRootFrameNode<T = undefined>(uiContext: UIContext, ptr: KPointer): BuilderRootFrameNode<T> | null {
        const nodeId = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(ptr, ptr);
        if (nodeId !== -1 && !ArkUIGeneratedNativeModule._FrameNode_isModifiable(ptr)) {
            let frameNode = new BuilderRootFrameNode<T>(uiContext, "BuilderRootFrameNode", ptr);
            frameNode._nodeId = nodeId;
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(nodeId, frameNode);
            return frameNode;
        }
        return null;
    }
}

abstract class TypedFrameNode<T extends Object> extends FrameNode {
    attribute_: T | undefined = undefined;
    attrCreator_: (node: FrameNode, type: ModifierType) => T
    type_: string = "";

    constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => T) {
        super(uiContext, type, nullptr);
        this.attrCreator_ = attrCreator;
        this.type_ = type;
    }
    getType(): string {
        return this.type_;
    }
    checkValid(node?: FrameNode): boolean {
        if (this.attribute_ === undefined) {
            this.attribute_ = this.attrCreator_(this, ModifierType.FRAME_NODE);
        }
        const a = this.attribute_ as Object as ArkBaseNode;
        const allowCount: number = a.allowChildCount();
        const childrenCount = this.getChildrenCount();
        if (allowCount != -1) {
            if (childrenCount >= allowCount) {
                return false;
            }
        }

        if (node !== undefined) {
            const childType = node!.getNodeType();
            const allowTypes = a.allowChildTypes();
            if (allowTypes === undefined) {
                return true;
            }
            let isValid = false;
            allowTypes!.forEach((nodeType: string) => {
                if (nodeType === childType) {
                    isValid = true;
                }
            });
            return isValid;
        }
        return true;
    }
    get attribute(): T {
        if (this.attribute_ === undefined) {
            this.attribute_ = this.attrCreator_(this, ModifierType.FRAME_NODE);
        }
        return this.attribute_!;
    }
}

export namespace typeNode {

    class ColumnFrameNode extends TypedFrameNode<ArkColumnNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkColumnNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: ColumnOptions): ColumnAttribute {
            let arkColumnNode = this.attribute as ArkColumnNode;
            return arkColumnNode!.initialize(options);
        }
    }

    class RowFrameNode extends TypedFrameNode<ArkRowNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkRowNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: RowOptions): RowAttribute {
            let arkRowNode = this.attribute as ArkRowNode;
            return arkRowNode!.initialize(options);
        }
    }

    class StackFrameNode extends TypedFrameNode<ArkStackNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkStackNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: StackOptions): StackAttribute {
            let arkStackNode = this.attribute as ArkStackNode;
            return arkStackNode!.initialize(options);
        }
    }

    class FlexFrameNode extends TypedFrameNode<ArkFlexNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkFlexNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: FlexOptions): FlexAttribute {
            let arkFlexNode = this.attribute as ArkFlexNode;
            return arkFlexNode!.initialize(options);
        }
    }

    class GridRowFrameNode extends TypedFrameNode<ArkGridRowNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkGridRowNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: GridRowOptions): GridRowAttribute {
            let arkGridRowNode = this.attribute as ArkGridRowNode;
            return arkGridRowNode!.initialize(options);
        }
    }

    class GridColFrameNode extends TypedFrameNode<ArkGridColNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkGridColNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: GridColOptions): GridColAttribute {
            let arkGridColNode = this.attribute as ArkGridColNode;
            return arkGridColNode!.initialize(options);
        }
    }

    class DividerFrameNode extends TypedFrameNode<ArkDividerNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkDividerNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(): DividerAttribute {
            let arkDividerNode = this.attribute as ArkDividerNode;
            return arkDividerNode!.initialize();
        }
    }

    class BlankFrameNode extends TypedFrameNode<ArkBlankNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkBlankNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(): BlankAttribute {
            let arkBlankNode = this.attribute as ArkBlankNode;
            return arkBlankNode!.initialize();
        }
    }

    class RelativeContainerFrameNode extends TypedFrameNode<ArkRelativeContainerNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkRelativeContainerNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(): RelativeContainerAttribute {
            let arkRelativeContainerNode = this.attribute as ArkRelativeContainerNode;
            return arkRelativeContainerNode!.initialize();
        }
    }

    class ListFrameNode extends TypedFrameNode<ArkListNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkListNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: ListOptions): ListAttribute {
            let arkListNode = this.attribute as ArkListNode;
            return arkListNode!.initialize(options);
        }
    }

    class ListItemFrameNode extends TypedFrameNode<ArkListItemNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkListItemNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: ListItemOptions): ListItemAttribute {
            let arkListItemNode = this.attribute as ArkListItemNode;
            return arkListItemNode!.initialize(options);
        }
    }

    class ListItemGroupFrameNode extends TypedFrameNode<ArkListItemGroupNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkListItemGroupNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: ListItemGroupOptions): ListItemGroupAttribute {
            let arkListItemGroupNode = this.attribute as ArkListItemGroupNode;
            return arkListItemGroupNode!.initialize(options);
        }
    }

    class ScrollFrameNode extends TypedFrameNode<ArkScrollNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkScrollNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(scroller: Scroller): ScrollAttribute {
            let arkScrollNode = this.attribute as ArkScrollNode;
            return arkScrollNode!.initialize(scroller);
        }
    }

    class GridFrameNode extends TypedFrameNode<ArkGridNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkGridNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(scroller: Scroller, layoutOptions: GridLayoutOptions): GridAttribute {
            let arkGridNode = this.attribute as ArkGridNode;
            return arkGridNode!.initialize(scroller, layoutOptions);
        }
    }

    class GridItemFrameNode extends TypedFrameNode<ArkGridItemNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkGridItemNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: GridItemOptions): GridItemAttribute {
            let arkGridItemNode = this.attribute as ArkGridItemNode;
            return arkGridItemNode!.initialize(options);
        }
    }

    class WaterFlowFrameNode extends TypedFrameNode<ArkWaterFlowNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkWaterFlowNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: WaterFlowOptions): WaterFlowAttribute {
            let arkWaterFlowNode = this.attribute as ArkWaterFlowNode;
            return arkWaterFlowNode!.initialize(options);
        }
    }

    class FlowItemFrameNode extends TypedFrameNode<ArkFlowItemNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkFlowItemNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(): FlowItemAttribute {
            let arkFlowItemNode = this.attribute as ArkFlowItemNode;
            return arkFlowItemNode!.initialize();
        }
    }

    class SearchFrameNode extends TypedFrameNode<ArkSearchNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkSearchNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: SearchOptions): SearchAttribute {
            let arkSearchNode = this.attribute as ArkSearchNode;
            return arkSearchNode!.initialize(options);
        }
    }

    class SwiperFrameNode extends TypedFrameNode<ArkSwiperNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkSwiperNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(controller?: SwiperController): SwiperAttribute {
            let arkSwiperNode = this.attribute as ArkSwiperNode;
            return arkSwiperNode!.initialize(controller);
        }
    }

    class TextAreaFrameNode extends TypedFrameNode<ArkTextAreaNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkTextAreaNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: TextAreaOptions): TextAreaAttribute {
            let arkTextAreaNode = this.attribute as ArkTextAreaNode;
            return arkTextAreaNode!.initialize(options);
        }
    }

    class TextInputFrameNode extends TypedFrameNode<ArkTextInputNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkTextInputNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: TextInputOptions): TextInputAttribute {
            let arkTextInputNode = this.attribute as ArkTextInputNode;
            return arkTextInputNode!.initialize(options);
        }
    }

    class TextFrameNode extends TypedFrameNode<ArkTextNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkTextNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(content?: string | Resource, value?: TextOptions): TextAttribute {
            let arkTextNode = this.attribute as ArkTextNode;
            return arkTextNode!.initialize(content, value);
        }
    }

    class XComponentFrameNode extends TypedFrameNode<ArkXComponentNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkXComponentNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(value: XComponentParameters): XComponentAttribute {
            let arkXComponentNode = this.attribute as ArkXComponentNode;
            return arkXComponentNode!.initialize(value);
        }
        initialize(value: XComponentOptions): XComponentAttribute {
            let arkXComponentNode = this.attribute as ArkXComponentNode;
            return arkXComponentNode!.initialize(value);
        }
        initialize(value: NativeXComponentParameters): XComponentAttribute {
            let arkXComponentNode = this.attribute as ArkXComponentNode;
            return arkXComponentNode!.initialize(value);
        }
    }

    class ImageFrameNode extends TypedFrameNode<ArkImageNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkImageNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent, options?: ImageAIOptions): ImageAttribute {
            let arkImageNode = this.attribute as ArkImageNode;
            return arkImageNode!.initialize(src);
        }
    }

    class QRCodeFrameNode extends TypedFrameNode<ArkQRCodeNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkQRCodeNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(value: string): QRCodeAttribute {
            let arkQRCodeNode = this.attribute as ArkQRCodeNode;
            return arkQRCodeNode!.initialize(value);
        }
    }

    class BadgeFrameNode extends TypedFrameNode<ArkBadgeNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkBadgeNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(value: BadgeParamWithNumber | BadgeParamWithString): BadgeAttribute {
            let arkBadgeNode = this.attribute as ArkBadgeNode;
            return arkBadgeNode!.initialize(value);
        }
    }

    class ProgressFrameNode extends TypedFrameNode<ArkProgressNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkProgressNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: ProgressOptions): ProgressAttribute {
            let arkProgressNode = this.attribute as ArkProgressNode;
            return arkProgressNode!.initialize(options);
        }
    }

    class LoadingProgressFrameNode extends TypedFrameNode<ArkLoadingProgressNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkLoadingProgressNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(): LoadingProgressAttribute {
            let arkLoadingProgressNode = this.attribute as ArkLoadingProgressNode;
            return arkLoadingProgressNode!.initialize();
        }
    }

    class TextClockFrameNode extends TypedFrameNode<ArkTextClockNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkTextClockNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options?: TextClockOptions): TextClockAttribute {
            let arkTextClockNode = this.attribute as ArkTextClockNode;
            return arkTextClockNode!.initialize(options);
        }
    }

    class TextTimerFrameNode extends TypedFrameNode<ArkTextTimerNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkTextTimerNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options?: TextTimerOptions): TextTimerAttribute {
            let arkTextTimerNode = this.attribute as ArkTextTimerNode;
            return arkTextTimerNode!.initialize(options);
        }
    }

    overload createNode {
        createColumnNode, createRowNode, createStackNode, createFlexNode, createGridRowNode,
        createGridColNode, createDividerNode, createBlankNode, createRelativeContainerNode, createListNode,
        createSearchNode, createTextAreaNode, createTextInputNode, createTextNode, createXComponentNode,
        createXComponentNodeWithOptions, createXComponentNodeWithParameters, createSwiperNode, createBadgeNode,
        createQRCodeNode, createProgressNode, createLoadingProgressNode, createTextClockNode, createTextTimerNode,createImageNode
    }

    // @ts-ignore
    export function createColumnNode(context: UIContext, type: 'Column'): ColumnFrameNode {
        return new ColumnFrameNode(context, 'Column', (node: FrameNode, type: ModifierType): ArkColumnNode => {
            let arknode = new ArkColumnNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkColumnPeer(retval, node._nodeId!.toInt(), "Column", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createRowNode(context: UIContext, type: 'Row'): RowFrameNode {
        return new RowFrameNode(context, 'Row', (node: FrameNode, type: ModifierType): ArkRowNode => {
            let arknode = new ArkRowNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkRowPeer(retval, node._nodeId!.toInt(), "Row", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createStackNode(context: UIContext, type: 'Stack'): StackFrameNode {
        return new StackFrameNode(context, 'Stack', (node: FrameNode, type: ModifierType): ArkStackNode => {
            let arknode = new ArkStackNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkStackPeer(retval, node._nodeId!.toInt(), "Stack", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createFlexNode(context: UIContext, type: 'Flex'): FlexFrameNode {
        return new FlexFrameNode(context, 'Flex', (node: FrameNode, type: ModifierType): ArkFlexNode => {
            let arknode = new ArkFlexNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkFlexPeer(retval, node._nodeId!.toInt(), "Flex", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridRowNode(context: UIContext, type: 'GridRow'): GridRowFrameNode {
        return new GridRowFrameNode(context, 'GridRow', (node: FrameNode, type: ModifierType): ArkGridRowNode => {
            let arknode = new ArkGridRowNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkGridRowPeer(retval, node._nodeId!.toInt(), "GridRow", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridColNode(context: UIContext, type: 'GridCol'): GridColFrameNode {
        return new GridColFrameNode(context, 'GridCol', (node: FrameNode, type: ModifierType): ArkGridColNode => {
            let arknode = new ArkGridColNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkGridColPeer(retval, node._nodeId!.toInt(), "GridCol", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createDividerNode(context: UIContext, type: 'Divider'): DividerFrameNode {
        return new DividerFrameNode(context, 'Divider', (node: FrameNode, type: ModifierType): ArkDividerNode => {
            let arknode = new ArkDividerNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkDividerPeer(retval, node._nodeId!.toInt(), "Divider", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createBlankNode(context: UIContext, type: 'Blank'): BlankFrameNode {
        return new BlankFrameNode(context, 'Blank', (node: FrameNode, type: ModifierType): ArkBlankNode => {
            let arknode = new ArkBlankNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkBlankPeer(retval, node._nodeId!.toInt(), "Blank", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createRelativeContainerNode(context: UIContext, type: 'RelativeContainer'): RelativeContainerFrameNode {
        return new RelativeContainerFrameNode(context, 'RelativeContainer', (node: FrameNode, type: ModifierType): ArkRelativeContainerNode => {
            let arknode = new ArkRelativeContainerNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkRelativeContainerPeer(retval, node._nodeId!.toInt(), "RelativeContainer", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createListNode(context: UIContext, type: 'List'): ListFrameNode {
        return new ListFrameNode(context, 'List', (node: FrameNode, type: ModifierType): ArkListNode => {
            let arknode = new ArkListNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkListPeer(retval, node._nodeId!.toInt(), "List", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createListItemNode(context: UIContext, type: 'ListItem'): ListItemFrameNode {
        return new ListItemFrameNode(context, 'ListItem', (node: FrameNode, type: ModifierType): ArkListItemNode => {
            let arknode = new ArkListItemNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkListItemPeer(retval, node._nodeId!.toInt(), "ListItem", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createListItemGroupNode(context: UIContext, type: 'ListItemGroup'): ListItemGroupFrameNode {
        return new ListItemGroupFrameNode(context, 'ListItemGroup', (node: FrameNode, type: ModifierType): ArkListItemGroupNode => {
            let arknode = new ArkListItemGroupNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkListItemGroupPeer(retval, node._nodeId!.toInt(), "ListItemGroup", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createScrollNode(context: UIContext, type: 'Scroll'): ScrollFrameNode {
        return new ScrollFrameNode(context, 'Scroll', (node: FrameNode, type: ModifierType): ArkScrollNode => {
            let arknode = new ArkScrollNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkScrollPeer(retval, node._nodeId!.toInt(), "Scroll", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridNode(context: UIContext, type: 'Grid'): GridFrameNode {
        return new GridFrameNode(context, 'Grid', (node: FrameNode, type: ModifierType): ArkGridNode => {
            let arknode = new ArkGridNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkGridPeer(retval, node._nodeId!.toInt(), "Grid", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridItemNode(context: UIContext, type: 'GridItem'): GridItemFrameNode {
        return new GridItemFrameNode(context, 'GridItem', (node: FrameNode, type: ModifierType): ArkGridItemNode => {
            let arknode = new ArkGridItemNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkGridItemPeer(retval, node._nodeId!.toInt(), "GridItem", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createWaterFlowNode(context: UIContext, type: 'WaterFlow'): WaterFlowFrameNode {
        return new WaterFlowFrameNode(context, 'WaterFlow', (node: FrameNode, type: ModifierType): ArkWaterFlowNode => {
            let arknode = new ArkWaterFlowNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkWaterFlowPeer(retval, node._nodeId!.toInt(), "WaterFlow", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createFlowItemNode(context: UIContext, type: 'FlowItem'): FlowItemFrameNode {
        return new FlowItemFrameNode(context, 'FlowItem', (node: FrameNode, type: ModifierType): ArkFlowItemNode => {
            let arknode = new ArkFlowItemNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkFlowItemPeer(retval, node._nodeId!.toInt(), "FlowItem", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createSearchNode(context: UIContext, type: string): SearchFrameNode {
        return new SearchFrameNode(context, 'Search', (node: FrameNode, type: ModifierType): ArkSearchNode => {
            let arknode = new ArkSearchNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkSearchPeer(retval, node._nodeId as int32, "Search", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createSwiperNode(context: UIContext, type: string): SwiperFrameNode {
        return new SwiperFrameNode(context, 'Swiper', (node: FrameNode, type: ModifierType): ArkSwiperNode => {
            let arknode = new ArkSwiperNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkSwiperPeer(retval, node._nodeId!.toInt(), "Swiper", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextAreaNode(context: UIContext, type: string): TextAreaFrameNode {
        return new TextAreaFrameNode(context, 'TextArea', (node: FrameNode, type: ModifierType): ArkTextAreaNode => {
            let arknode = new ArkTextAreaNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkTextAreaPeer(retval, node._nodeId as int32, "TextArea", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextInputNode(context: UIContext, type: string): TextInputFrameNode {
        return new TextInputFrameNode(context, 'TextInput', (node: FrameNode, type: ModifierType): ArkTextInputNode => {
            let arknode = new ArkTextInputNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkTextInputPeer(retval, node._nodeId as int32, "TextInput", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextNode(context: UIContext, type: 'Text'): TextFrameNode {
        return new TextFrameNode(context, 'Text', (node: FrameNode, type: ModifierType): ArkTextNode => {
            let arknode = new ArkTextNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkTextPeer(retval, node._nodeId as int32, "Text", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createXComponentNode(context: UIContext, type: string): XComponentFrameNode {
        let xcFrameNode = new XComponentFrameNode(context, 'XComponent', (node: FrameNode, type: ModifierType): ArkXComponentNode => {
            let arknode = new ArkXComponentNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new TypedXComponentPeerInternal(retval, node._nodeId as int32, "XComponent", 0);
            arknode.setPeer(peer);
            return arknode;
        });
        xcFrameNode.initialize({ type: XComponentType.SURFACE } as NativeXComponentParameters);
        return xcFrameNode;
    }

    // @ts-ignore
    function createXComponentNodeWithOptions(context: UIContext, type: string, options: XComponentOptions): XComponentFrameNode {
        let xcFrameNode = new XComponentFrameNode(context, 'XComponent', (node: FrameNode, type: ModifierType): ArkXComponentNode => {
            let arknode = new ArkXComponentNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new TypedXComponentPeerInternal(retval, node._nodeId as int32, "XComponent", 0);
            arknode.setPeer(peer);
            return arknode;
        });
        xcFrameNode.initialize(options);
        return xcFrameNode;
    }

    // @ts-ignore
    function createXComponentNodeWithParameters(context: UIContext, type: string, parameters: NativeXComponentParameters): XComponentFrameNode {
        let xcFrameNode = new XComponentFrameNode(context, 'XComponent', (node: FrameNode, type: ModifierType): ArkXComponentNode => {
            let arknode = new ArkXComponentNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new TypedXComponentPeerInternal(retval, node._nodeId as int32, "XComponent", 0);
            arknode.setPeer(peer);
            return arknode;
        });
        xcFrameNode.initialize(parameters);
        return xcFrameNode;
    }

    // @ts-ignore
    function createImageNode(context: UIContext, type: 'Image'): ImageFrameNode {
        return new ImageFrameNode(context, 'Image', (node: FrameNode, type: ModifierType): ArkImageNode => {
            let arknode = new ArkImageNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkImagePeer(retval, node._nodeId as int32, 'Image', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createBadgeNode(context: UIContext, type: 'Badge'): BadgeFrameNode {
        return new BadgeFrameNode(context, 'Badge', (node: FrameNode, type: ModifierType): ArkBadgeNode => {
            let arknode = new ArkBadgeNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkBadgePeer(retval, node._nodeId as int32, 'Badge', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createQRCodeNode(context: UIContext, type: 'QRCode'): QRCodeFrameNode {
        return new QRCodeFrameNode(context, 'QRCode', (node: FrameNode, type: ModifierType): ArkQRCodeNode => {
            let arknode = new ArkQRCodeNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkQRCodePeer(retval, node._nodeId as int32, 'QRCode', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createProgressNode(context: UIContext, type: 'Progress'): ProgressFrameNode {
        return new ProgressFrameNode(context, 'Progress', (node: FrameNode, type: ModifierType): ArkProgressNode => {
            let arknode = new ArkProgressNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkProgressPeer(retval, node._nodeId as int32, 'Progress', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createLoadingProgressNode(context: UIContext, type: 'LoadingProgress'): LoadingProgressFrameNode {
        return new LoadingProgressFrameNode(context, 'LoadingProgress', (node: FrameNode, type: ModifierType): ArkLoadingProgressNode => {
            let arknode = new ArkLoadingProgressNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkLoadingProgressPeer(retval, node._nodeId as int32, 'LoadingProgress', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextClockNode(context: UIContext, type: 'TextClock'): TextClockFrameNode {
        return new TextClockFrameNode(context, 'TextClock', (node: FrameNode, type: ModifierType): ArkTextClockNode => {
            let arknode = new ArkTextClockNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkTextClockPeer(retval, node._nodeId as int32, 'TextClock', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextTimerNode(context: UIContext, type: 'TextTimer'): TextTimerFrameNode {
        return new TextTimerFrameNode(context, 'TextTimer', (node: FrameNode, type: ModifierType): ArkTextTimerNode => {
            let arknode = new ArkTextTimerNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkTextTimerPeer(retval, node._nodeId as int32, 'TextTimer', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }
}
