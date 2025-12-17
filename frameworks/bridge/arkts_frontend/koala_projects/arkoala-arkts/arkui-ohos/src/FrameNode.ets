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
import { UIContextImpl } from "arkui/base/UIContextImpl"
import { NodePosition, NodeEdges, Size, LengthMetrics, SizeT } from "./Graphics"
import {
    Finalizable, toPeerPtr, KPointer, MaterializedBase, nullptr, pointer, NativeThunk
} from "@koalaui/interop"
import { finalizerRegister, int32 } from "@koalaui/common"
import { ArkUIAniModule } from "arkui.ani"
import { RenderNode } from "./RenderNode"
import { CommonAttribute, ArkCommonMethodPeer, CommonMethod, UIGestureEvent, UICommonEvent, UICommonEventInternal,
    CustomProperty, AnimateParam } from './component/common';
import { ArkButtonNode } from './typedNode/ArkButtonNode'
import { ButtonOptions, ButtonAttribute, ArkButtonPeer} from './component/button'
import { ArkCheckboxNode } from './typedNode/ArkCheckboxNode'
import { CheckboxOptions, CheckboxAttribute, ArkCheckboxPeer} from './component/checkbox'
import { ArkCheckboxGroupNode } from './typedNode/ArkCheckboxGroupNode'
import { CheckboxGroupOptions, CheckboxGroupAttribute, ArkCheckboxGroupPeer} from './component/checkboxgroup'
import { ArkRadioNode } from './typedNode/ArkRadioNode'
import { RadioOptions, RadioAttribute, ArkRadioPeer} from './component/radio'
import { ArkRatingNode } from './typedNode/ArkRatingNode'
import { RatingOptions, RatingAttribute, ArkRatingPeer} from './component/rating'
import { ArkSelectNode } from './typedNode/ArkSelectNode'
import { SelectOption, SelectAttribute, ArkSelectPeer} from './component/select'
import { ArkSliderNode } from './typedNode/ArkSliderNode'
import { SliderOptions, SliderAttribute, ArkSliderPeer} from './component/slider'
import { ArkToggleNode } from './typedNode/ArkToggleNode'
import { ToggleOptions, ToggleAttribute, ArkTogglePeer} from './component/toggle'
import { ArkBaseNode } from './typedNode/ArkBaseNode'
import { ArkQRCodeNode } from './typedNode/ArkQRCodeNode'
import { ArkBadgeNode } from './typedNode/ArkBadgeNode'
import { ArkProgressNode } from './typedNode/ArkProgressNode'
import { ArkLoadingProgressNode } from './typedNode/ArkLoadingProgressNode'
import { ArkTextClockNode } from './typedNode/ArkTextClockNode'
import { ArkTextTimerNode } from './typedNode/ArkTextTimerNode'
import { ArkImageNode } from './typedNode/ArkImageNode'
import { ArkListNode } from './typedNode/ArkListNode'
import { ArkListItemNode } from './typedNode/ArkListItemNode'
import { ArkListItemGroupNode } from './typedNode/ArkListItemGroupNode'
import { ArkScrollNode } from './typedNode/ArkScrollNode'
import { ArkGridNode } from './typedNode/ArkGridNode'
import { ArkGridItemNode } from './typedNode/ArkGridItemNode'
import { ArkWaterFlowNode } from './typedNode/ArkWaterFlowNode'
import { ArkFlowItemNode } from './typedNode/ArkFlowItemNode'
import { ArkColumnNode } from './typedNode/ArkColumnNode'
import { ArkRowNode } from './typedNode/ArkRowNode'
import { ArkStackNode } from './typedNode/ArkStackNode'
import { ArkFlexNode } from './typedNode/ArkFlexNode'
import { ArkGridRowNode } from './typedNode/ArkGridRowNode'
import { ArkGridColNode } from './typedNode/ArkGridColNode'
import { ArkDividerNode } from './typedNode/ArkDividerNode'
import { ArkBlankNode } from './typedNode/ArkBlankNode'
import { ArkRelativeContainerNode } from './typedNode/ArkRelativeContainerNode'
import { ArkSearchNode } from './typedNode/ArkSearchNode'
import { ArkSwiperNode } from "./typedNode/ArkSwiperNode";
import { ArkTextAreaNode } from './typedNode/ArkTextAreaNode'
import { ArkTextInputNode } from './typedNode/ArkTextInputNode'
import { ArkTextNode } from './typedNode/ArkTextNode'
import { ArkMarqueeNode } from './typedNode/ArkMarqueeNode'
import { ArkSymbolGlyphNode } from './typedNode/ArkSymbolGlyphNode'
import { ArkXComponentNode } from "./typedNode/ArkXComponentNode"
import { ModifierType } from './typedNode/ArkCommonModifier'
import { ListOptions, ListAttribute, ArkListPeer } from './component/list'
import { ListItemOptions, ListItemAttribute, ArkListItemPeer } from './component/listItem'
import { ListItemGroupOptions, ListItemGroupAttribute, ArkListItemGroupPeer } from './component/listItemGroup'
import { Scroller, ScrollAttribute, ArkScrollPeer } from './component/scroll'
import { GridLayoutOptions, GridAttribute, ArkGridPeer } from './component/grid'
import { GridItemOptions, GridItemAttribute, ArkGridItemPeer } from './component/gridItem'
import { WaterFlowOptions, WaterFlowAttribute, ArkWaterFlowPeer } from './component/waterFlow'
import { FlowItemAttribute, ArkFlowItemPeer } from './component/flowItem'
import { ColumnOptions, ColumnOptionsV2, ColumnAttribute, ArkColumnPeer } from './component/column'
import { RowOptions, RowOptionsV2, RowAttribute, ArkRowPeer } from './component/row'
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
import { TextOptions, TextAttribute, ArkTextPeer } from './component/text'
import { MarqueeOptions, MarqueeAttribute, ArkMarqueePeer } from './component/marquee'
import { SymbolGlyphAttribute, ArkSymbolGlyphPeer } from './component/symbolglyph'
import { XComponentParameters, XComponentOptions, NativeXComponentParameters, XComponentAttribute, TypedXComponentPeerInternal } from "./component/xcomponent"
import { XComponentType, AnimationPropertyType } from './component/enums'
import { ComponentContent } from './ComponentContent';
import { DrawContext } from './Graphics';
import { JSBuilderNode } from "./BuilderNode"
import { BusinessError } from '#external';
import { Resource } from 'global.resource';
import { ElementIdToCustomProperties } from "#handwritten"
import { ObjectLinkDecoratedVariable } from "./stateManagement/decoratorImpl/decoratorObjectLink"
import { FrameNodeExtender, SizeTLengthMetrics, NodeEdgesLengthMetrics } from './framework';
import { extractors } from "#handwritten";
import { PeerNode } from './PeerNode';
import hilog from '@ohos.hilog';
import { Vector2 } from "./Graphics.ets"

export interface CrossLanguageOptions {
    attributeSetting?: boolean;
}
export interface LayoutConstraint {
    maxSize: Size;
    minSize: Size;
    percentReference: Size;
}

export class LayoutConstraintImpl implements LayoutConstraint {
    maxSize: Size;
    minSize: Size;
    percentReference: Size;
    constructor(maxSizeWidth: double, maxSizeHeight: double,
        minSizeWidth: double, minSizeHeight: double,
        percentReferenceWidth: double, percentReferenceHeight: double) {
        this.maxSize = { width: maxSizeWidth, height: maxSizeHeight };
        this.minSize = { width: minSizeWidth, height: minSizeHeight };
        this.percentReference = { width: percentReferenceWidth, height: percentReferenceHeight };
    }
}

export class NodePositionImpl implements NodePosition{
    x: double;
    y: double;
    constructor(x: double, y: double) {
        this.x = x;
        this.y = y;
    }
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

const ERROR_CODE_NODE_IS_ADOPTED = 106206;
const ERROR_CODE_NODE_HAS_PARENT = 106207;
const ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED = 106208;
const ERROR_CODE_NODE_CAN_NOT_ADOPT_TO = 106209;
const ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN = 106210;

const errorMap_: Map<number, string> = new Map<number, string>();
errorMap_.set(ERROR_CODE_NODE_IS_ADOPTED, "The parameter 'child' is invalid: the node has already been adopted.");
errorMap_.set(ERROR_CODE_NODE_HAS_PARENT, "The parameter 'child' is invalid: the child already has a parent node.");
errorMap_.set(ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED, "The parameter 'child' is invalid: the node cannot be adopted.");
errorMap_.set(ERROR_CODE_NODE_CAN_NOT_ADOPT_TO, 'Current node is invalid: the node cannot adopt children.');
errorMap_.set(ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN, "The parameter 'child' is invalid: the node is not adopted by the parent node.");

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
    public nodeType_?: string | undefined = undefined;
    private nodeAdapterRef_ ?: NodeAdapter;

    getType(): string {
        return 'CustomFrameNode';
    }

    setAdapterRef(adapter :NodeAdapter | undefined){
        this.nodeAdapterRef_ = adapter;
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
            this._gestureEvent!.setPeer(PeerNode.findPeerByNativeId(this.peer!.ptr as KPointer));
        }
        return this._gestureEvent as UIGestureEvent;
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
                const ctorPtr: KPointer = ptr ? ptr : FrameNodeExtender.constructorFrameNode()
                this.peer = new Finalizable(ctorPtr, FrameNode.getFinalizer())
                this.nodePtr_ = this.peer?.ptr
                ArkUIAniModule._SetCustomCallbackWithCheck(this!.peer!.ptr, this);  
            } else {
                const retval = ptr ? ptr : FrameNodeExtender.createTypedFrameNode(type as string);
                this.peer = new Finalizable(retval, FrameNode.getFinalizer());
                this.nodePtr_ = this.peer?.ptr
            }
            this.renderNode_?.setFrameNode(new WeakRef<FrameNode>(this))
            if (this.renderNode_ && this.getType() === "CustomFrameNode") {
                this.renderNode_!.peer = new Finalizable(FrameNodeExtender.getRenderNode(this.peer!.ptr), RenderNode.getFinalizer());
            }
            this._nodeId = FrameNodeExtender.getIdByFrameNode(this.peer!.ptr);
            ArkUIAniModule._Common_Restore_InstanceId();
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, this);
        }
    }
    static getFinalizer(): KPointer {
        return FrameNodeExtender.getDestroy();
    }
    public isModifiable(): boolean {
        return FrameNodeExtender.isModifiable(this.peer!.ptr);
    }
    public appendChild(node: FrameNode): void {
        if (node.getType() === 'ProxyFrameNode' || !this.checkValid(node)) {
            const error = Error('The FrameNode is not modifiable.');
            throw new BusinessError(100021, error);
        }
        const node_casted = node as (FrameNode);
        let flag = FrameNodeExtender.appendChild(this, node_casted);
        if (flag === ERROR_CODE_NODE_IS_ADOPTED) {
            const error = Error("The parameter 'node' is invalid: the node has already been adopted.");
            throw new BusinessError(100025, error);
        }
        return
    }
    public addComponentContent<T = undefined>(content: ComponentContent<T>) {
        if (content === undefined || content === null || content.getFrameNode() == undefined ||
            content.getFrameNode() == null || content.getNodePtr() == undefined) {
            return;
        }
        if (!this.isModifiable()) {
            const error = Error('The FrameNode is not modifiable.');
            throw new BusinessError(100021, error);
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
        let flag: number = 0;
        if (sibling === null || sibling === undefined) {
            flag = FrameNodeExtender.insertChildAfter(this.peer!.ptr, toPeerPtr(child), nullptr);
        } else {
            flag = FrameNodeExtender.insertChildAfter(this.peer!.ptr, toPeerPtr(child), toPeerPtr(sibling!));
        }
        if (flag === ERROR_CODE_NODE_IS_ADOPTED) {
            const error = Error("The parameter 'child' is invalid: the node has already been adopted.");
            throw new BusinessError(100025, error);
        }
        return
    }
    public removeChild(node: FrameNode): void {
        const node_casted = node as (FrameNode)
        FrameNodeExtender.removeChild(this, node_casted)
        return
    }
    public clearChildren(): void {
        FrameNodeExtender.clearChildren(this)
        return
    }
    convertToFrameNode(node: FrameNode, nodeId: number = -1): FrameNode {
        if (nodeId === -1) {
            const instanceId = this.instanceId_!.toInt();
            ArkUIAniModule._Common_Sync_InstanceId(instanceId);
            nodeId = FrameNodeExtender.getIdByFrameNode(toPeerPtr(node));
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
    public getChild(index: int32, expandMode?: ExpandMode | undefined): FrameNode | null {
        let expand_casted: number = 1;
        if (expandMode !== undefined && expandMode !== null) {
            expand_casted = expandMode;
        }
        const retval = FrameNodeExtender.getChild(this, index, expand_casted);
        if (retval !== nullptr) {
            let child = extractors.fromFrameNodePtr(retval);
            const nodeId = FrameNodeExtender.getIdByFrameNode(toPeerPtr(child));
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
        const retval = FrameNodeExtender.getFirstChild(this);
        if (retval !== nullptr) {
            let child = extractors.fromFrameNodePtr(retval);
            const nodeId = FrameNodeExtender.getIdByFrameNode(toPeerPtr(child));
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
        const retval = FrameNodeExtender.getNextSibling(this);
        if (retval !== nullptr) {
            let child = extractors.fromFrameNodePtr(retval);
            const nodeId = FrameNodeExtender.getIdByFrameNode(toPeerPtr(child));
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
        const retval = FrameNodeExtender.getPreviousSibling(this);
        if (retval !== nullptr) {
            let child = extractors.fromFrameNodePtr(retval);
            const nodeId = FrameNodeExtender.getIdByFrameNode(toPeerPtr(child));
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
        const retval = FrameNodeExtender.getParent(this);
        if (retval !== nullptr) {
            let parent = extractors.fromFrameNodePtr(retval);
            const nodeId = FrameNodeExtender.getIdByFrameNode(toPeerPtr(parent));
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
    public getChildrenCount(): int {
        return FrameNodeExtender.getChildrenCount(this);
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
    public getOpacity(): double {
        return FrameNodeExtender.getOpacity(this);
    }
    public getPositionToWindowWithTransform(): NodePosition {
        return FrameNodeExtender.getPositionToWindowWithTransform(this);
    }
    public getPositionToParent(): NodePosition {
        return FrameNodeExtender.getPositionToParent(this);
    }
    public getPositionToScreen(): NodePosition {
        return FrameNodeExtender.getPositionToScreen(this);
    }
    public getPositionToWindow(): NodePosition {
        return FrameNodeExtender.getPositionToWindow(this);
    }
    public getPositionToParentWithTransform(): NodePosition {
        return FrameNodeExtender.getPositionToParentWithTransform(this);
    }
    public getPositionToScreenWithTransform(): NodePosition {
        return FrameNodeExtender.getPositionToScreenWithTransform(this);
    }
    public getMeasuredSize(): Size {
        return FrameNodeExtender.getMeasuredSize(this)
    }
    public getLayoutPosition(): NodePosition {
        return FrameNodeExtender.getLayoutPosition(this);
    }
    public getUserConfigBorderWidth(): NodeEdges<LengthMetrics> {
        let borderWidth = FrameNodeExtender.getUserConfigBorderWidth_serialize(this);
        return {
            top: borderWidth.top, left: borderWidth.left,
            bottom: borderWidth.bottom, right: borderWidth.right
        };
    }
    public getUserConfigPadding(): NodeEdges<LengthMetrics> {
        let padding = FrameNodeExtender.getUserConfigPadding_serialize(this)
        return {
            top: padding.top, left: padding.left,
            bottom: padding.bottom, right: padding.right
        }
    }
    public getUserConfigMargin(): NodeEdges<LengthMetrics> {
        let margin = FrameNodeExtender.getUserConfigMargin_serialize(this)
        return {
            top: margin.top, left: margin.left,
            bottom: margin.bottom, right: margin.right
        }
    }
    public getUserConfigSize(): SizeT<LengthMetrics> {
        let size = FrameNodeExtender.getUserConfigSize_serialize(this)
        return { width: size.width, height: size.height }
    }
    public getId(): string {
        return FrameNodeExtender.getId(this);
    }
    public getUniqueId(): int {
        return FrameNodeExtender.getUniqueId(this);
    }
    public isVisible(): boolean {
        return FrameNodeExtender.isVisible(this);
    }
    public isClipToFrame(): boolean {
        return FrameNodeExtender.isClipToFrame(this);
    }
    public isAttached(): boolean {
        return FrameNodeExtender.isAttached(this);
    }
    public getInspectorInfo(): Object {
        return FrameNodeExtender.getInspectorInfo(this);
    }
    public onDrawWrapper(context: DrawContext): void {
        context.canvas.clipRect({
            left: 0,
            top: 0,
            right: this.uiContext!.vp2px(context.size.width),
            bottom: this.uiContext!.vp2px(context.size.height)
        })
    }
    public setMeasuredSize(size: Size): void {
        const width = Math.max(size.width, 0);
        const height = Math.max(size.height, 0);
        const size_casted = { width: width, height: height } as (Size);
        FrameNodeExtender.setMeasuredSize(this, size_casted);
        return;
    }
    public setLayoutPosition(position: NodePosition): void {
        FrameNodeExtender.setLayoutPosition(this, position);
        return;
    }
    public measure(constraint: LayoutConstraint): void {
        const constraint_casted = constraint as (LayoutConstraint);
        const instanceId = this.instanceId_!.toInt();
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        FrameNodeExtender.measure(this, constraint_casted);
        ArkUIAniModule._Common_Restore_InstanceId();
        return;
    }
    public layout(position: NodePosition): void {
        const instanceId = this.instanceId_!.toInt();
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        FrameNodeExtender.layout(this, position);
        ArkUIAniModule._Common_Restore_InstanceId();
        return;
    }
    public setNeedsLayout(): void {
        FrameNodeExtender.setNeedsLayout(this);
        return;
    }
    public invalidate(): void {
        FrameNodeExtender.invalidate(this);
    };
    public disposeTree(): void {
        FrameNodeExtender.disposeTree(this);
    };
    public setCrossLanguageOptions(options: CrossLanguageOptions): void {
        let errorMessage: string = 'The FrameNode cannot be set whether to support cross-language common attribute setting.';
        const error = Error(errorMessage);
        if (!this.isModifiable()) {
            throw new BusinessError(100022, error);
        }
        let setting: boolean = options.attributeSetting ? options.attributeSetting! : false;
        let isSupport = FrameNodeExtender.setCrossLanguageOptions(this, setting);
        if (!isSupport) {
            throw new BusinessError(100022, error);
        }
    }
    public getCrossLanguageOptions(): CrossLanguageOptions {
        let option: boolean = FrameNodeExtender.getCrossLanguageOptions(this);
        const crossLanguageOptions: CrossLanguageOptions = {
            attributeSetting: option,
        };
        return crossLanguageOptions;
    }
    public isTransferred(): boolean {
        return false;
    }
    adoptChild(child: FrameNode): void{
    if (child === undefined || child === null) {
        const error = Error("The parameter 'child' is invalid: the child node is undefined or null.");
        throw new BusinessError(100025, error);
    }
    if (!this.isModifiable()) {
        const error = Error('The FrameNode is not modifiable.');
        throw new BusinessError(100021, error);
    }
    if (child.getType() === 'ProxyFrameNode' || !this.checkValid(child)) {
        const error = Error("The parameter 'child' is invalid: the child node is not modifiable.");
        throw new BusinessError(100025, error);
    }
    const child_casted = child as (FrameNode);
    let result = FrameNodeExtender.adoptChild(this, child_casted);
    let errorInfo = errorMap_.get(result);
    if (errorInfo !== undefined) {
        const error = Error(errorInfo);
        throw new BusinessError(100025, error);
    }
  }
    removeAdoptedChild(child: FrameNode): void {
    if (child === undefined || child === null) {
        const error = Error("The parameter 'child' is invalid: the child node is undefined or null.");
        throw new BusinessError(100025, error);
    }
    if (!this.isModifiable()) {
        const error = Error('The FrameNode is not modifiable.');
        throw new BusinessError(100021, error);
    }
    if (child.getType() === 'ProxyFrameNode' || !this.checkValid(child)) {
        const error = Error("The parameter 'child' is invalid: the child node is not modifiable.");
        throw new BusinessError(100025, error);
    }
    const child_casted = child as (FrameNode);
    let result = FrameNodeExtender.removeAdoptedChild(this, child_casted);
    let errorInfo = errorMap_.get(result);
    if (errorInfo !== undefined) {
        const error = Error(errorInfo);
        throw new BusinessError(100025, error);
    }
  }
    private getCommonEvent(): UICommonEvent {
        return FrameNodeExtender.getCommonEvent(this);
    }
    public getIdByFrameNode(node: FrameNode): number {
        const node_casted = node as (FrameNode);
        return FrameNodeExtender.getIdByFrameNode(toPeerPtr(node_casted));
    }
    public moveTo(targetParent: FrameNode, index?: int): void {
        if (targetParent === undefined || targetParent === null) {
            return;
        }
        let index_casted: int = -1;
        if (index !== undefined && index !== null) {
            index_casted = index;
        }
        const oldParent = this.getParent();
        if (oldParent && !oldParent.isModifiable() || !targetParent.isModifiable() || !targetParent.checkValid(this)) {
            const error = Error('The FrameNode is not modifiable.');
            throw new BusinessError(100021, error);
        }
        const targetParent_casted = targetParent as (FrameNode);
        let result = FrameNodeExtender.moveTo(this, targetParent_casted, index_casted);
        if (result === ERROR_CODE_NODE_IS_ADOPTED) {
            const error = Error('The current node has already been adopted.');
            throw new BusinessError(100027, error);
        }
        return;
    }

    public getFirstChildIndexWithoutExpand(): int {
        return FrameNodeExtender.getFirstChildIndexWithoutExpand(this);
    }
    public getLastChildIndexWithoutExpand(): int {
        return FrameNodeExtender.getLastChildIndexWithoutExpand(this);
    }
    public reuse(): void {
        FrameNodeExtender.reuse(this)
        return
    }
    public recycle(): void {
        FrameNodeExtender.recycle(this)
        return
    }
    public createAnimation(property: AnimationPropertyType, startValue: Array<double> | undefined, endValue: Array<double>, param: AnimateParam): boolean {
        const property_casted = property as (AnimationPropertyType)
        const startValue_casted = startValue as (Array<double> | undefined)
        const endValue_casted = endValue as (Array<double>)
        const param_casted = param as (AnimateParam)
        return FrameNodeExtender.createAnimation(this, property_casted, startValue_casted, endValue_casted, param_casted);
    }
    public cancelAnimations(properties: Array<AnimationPropertyType>): boolean {
        const properties_casted = properties as (Array<AnimationPropertyType>)
        return FrameNodeExtender.cancelAnimations(this, properties_casted);
    }
    public getNodePropertyValue(property: AnimationPropertyType): Array<double> {
        const property_casted = property as (AnimationPropertyType)
        return FrameNodeExtender.getNodePropertyValue(this, property_casted);
    }
    public getRenderNode(): RenderNode | null {
        return (this.renderNode_ && this.renderNode_?.peer?.ptr) ? this.renderNode_! : null;
    }
    public static getFrameNodePtr(node: FrameNode): KPointer {
        const node_casted = node as (FrameNode)
        return FrameNodeExtender.getFrameNodePtr(node_casted)
    }
    get commonAttribute(): CommonMethod {
        if (this._commonAttribute === undefined) {
            let baseNode = new ArkBaseNode();
            const retval = FrameNodeExtender.getFrameNodePtr(this)
            let peer = new ArkFrameNodePeer(retval, this._nodeId!.toInt(), "FrameNode", 0);
            baseNode.setPeer(peer);
            this._commonAttribute = baseNode as CommonAttribute;
        }
        return this._commonAttribute!;
    }
    public getNodeType(): string {
        return FrameNodeExtender.getNodeType(this)
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
    public convertPosition(position: NodePosition, targetNode: FrameNode): NodePosition {
        if (targetNode === null) {
            const error = Error("The parameter 'targetNode' is invalid: it cannot be null. Please pass a non-null FrameNode object.");
            throw new BusinessError(100025, error);
        }
        if (targetNode === undefined) {
            const error = Error("The parameter 'targetNode' is invalid: it cannot be undefined.");
            throw new BusinessError(100025, error);
        }
        if (position === undefined) {
            const error = Error("The parameter 'position' is invalid: it cannot be undefined. Provide a valid position object with x and y properties.");
            throw new BusinessError(100025, error);
        }
        if (position === null) {
            const error = Error("The parameter 'position' is invalid: it cannot be null. Provide a non-null position object.");
            throw new BusinessError(100025, error);
        }
        const instanceId = this.instanceId_!.toInt();
        let chanels: Array<number> = [];
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        chanels = FrameNodeExtender.convertPoint(this, targetNode, position);
        ArkUIAniModule._Common_Restore_InstanceId();
        if (chanels.length < 3) {
            const error = new Error("The current FrameNode and the target FrameNode do not have a common ancestor node.");
            throw new BusinessError(100024, error);
        }
        const x = chanels[1];
        const y = chanels[2];
        return { x: x, y: y } as NodePosition;
    }
    public convertPositionToWindow(positionByLocal: NodePosition): NodePosition {
        if (positionByLocal === undefined) {
            const error = Error("The parameter 'positionByLocal' is invalid: it cannot be undefined. Provide a valid position object with x and y properties.");
            throw new BusinessError(401, error);
        }
        if (positionByLocal === null) {
            const error = Error("The parameter 'positionByLocal' is invalid: it cannot be null. Provide a valid position object with x and y properties.");
            throw new BusinessError(401, error);
        }
        if (this.nodePtr_ == undefined) {
            const error = Error("The current FrameNode has been disposed.");
            throw new BusinessError(10026, error);
        }
        const instanceId = this.instanceId_!.toInt();
        let channels: Array<number> = [];
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        channels = FrameNodeExtender.convertPositionToWindow(this, positionByLocal);
        ArkUIAniModule._Common_Restore_InstanceId();
        if (channels.length < 3 || channels[0] === 0) {
            const error = new Error("The current FrameNode is not on the main tree.");
            throw new BusinessError(10028, error);
        }
        const x = channels[1];
        const y = channels[2];
        return { x: x, y: y } as NodePosition;
    }
    public convertPositionFromWindow(positionByWindow: NodePosition): NodePosition {
        if (positionByWindow === undefined) {
            const error = Error("The parameter 'positionByWindow' is invalid: it cannot be undefined. Provide a valid position object with x and y properties.");
            throw new BusinessError(401, error);
        }
        if (positionByWindow === null) {
            const error = Error("The parameter 'positionByWindow' is invalid: it cannot be null. Provide a valid position object with x and y properties.");
            throw new BusinessError(401, error);
        }
        if (this.nodePtr_ == undefined) {
            const error = Error("The current FrameNode has been disposed.");
            throw new BusinessError(10026, error);
        }
        const instanceId = this.instanceId_!.toInt();
        let channels: Array<number> = [];
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        channels = FrameNodeExtender.convertPositionFromWindow(this, positionByWindow);
        ArkUIAniModule._Common_Restore_InstanceId();
        if (channels.length < 3 || channels[0] === 0) {
            const error = new Error("The current FrameNode is not on the main tree.");
            throw new BusinessError(10028, error);
        }
        const x = channels[1];
        const y = channels[2];
        return { x: x, y: y } as NodePosition;
    }
    public isInRenderState(): boolean {
        return FrameNodeExtender.isOnRenderTree(this);
    }
    public isOnMainTree(): boolean {
        return FrameNodeExtender.isOnMainTree(this);
    }
      public invalidateAttributes(): void {
        FrameNodeExtender.applyAttributesFinish(this);
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
    moveTo(targetParent: FrameNode, index?: int): void {
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
            this.renderNode_!.peer = new Finalizable(FrameNodeExtender.getRenderNode(ptr), RenderNode.getFinalizer());
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
        const nodeId = FrameNodeExtender.getIdByFrameNode(ptr);
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
        const nodeId = FrameNodeExtender.getIdByFrameNode(ptr);
        if (nodeId !== -1 && !FrameNodeExtender.isModifiable(ptr)) {
            let frameNode = new ProxyFrameNode(uiContext, "ProxyFrameNode", ptr);
            frameNode._nodeId = nodeId;
            frameNode!.peer!.ptr = ptr;
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(nodeId, frameNode);
            return frameNode;
        }
        return null;
    }
    static createBuilderRootFrameNode<T = undefined>(uiContext: UIContext, ptr: KPointer): BuilderRootFrameNode<T> | null {
        const nodeId = FrameNodeExtender.getIdByFrameNode(ptr);
        if (nodeId !== -1 && !FrameNodeExtender.isModifiable(ptr)) {
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

    public isModifiable() : boolean {
        return true;
    }

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
        initialize(options: ColumnOptions | ColumnOptionsV2): ColumnAttribute {
            let arkColumnNode = this.attribute as ArkColumnNode;
            return arkColumnNode!.initialize(options);
        }
    }

    class RowFrameNode extends TypedFrameNode<ArkRowNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkRowNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: RowOptions | RowOptionsV2): RowAttribute {
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
        initialize(min: double | string): BlankAttribute {
            let arkBlankNode = this.attribute as ArkBlankNode;
            return arkBlankNode!.initialize(min);
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
        initialize(value?: SearchOptions): SearchAttribute {
            let arkSearchNode = this.attribute as ArkSearchNode;
            return arkSearchNode!.initialize(value);
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
        initialize(value?: TextAreaOptions): TextAreaAttribute {
            let arkTextAreaNode = this.attribute as ArkTextAreaNode;
            return arkTextAreaNode!.initialize(value);
        }
    }

    class TextInputFrameNode extends TypedFrameNode<ArkTextInputNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkTextInputNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(value?: TextInputOptions): TextInputAttribute {
            let arkTextInputNode = this.attribute as ArkTextInputNode;
            return arkTextInputNode!.initialize(value);
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

    class MarqueeFrameNode extends TypedFrameNode<ArkMarqueeNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkMarqueeNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(value: MarqueeOptions): MarqueeAttribute {
            let arkMarqueeNode = this.attribute as ArkMarqueeNode;
            return arkMarqueeNode!.initialize(value);
        }
    }

    class SymbolGlyphFrameNode extends TypedFrameNode<ArkSymbolGlyphNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkSymbolGlyphNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(value?: Resource): SymbolGlyphAttribute {
            let arkSymbolGlyphNode = this.attribute as ArkSymbolGlyphNode;
            return arkSymbolGlyphNode!.initialize(value);
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
        initialize(src: PixelMap | ResourceStr | DrawableDescriptor): ImageAttribute {
            let arkImageNode = this.attribute as ArkImageNode;
            return arkImageNode!.initialize(src);
        }
        initialize(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent): ImageAttribute {
            let arkImageNode = this.attribute as ArkImageNode;
            return arkImageNode!.initialize(src);
        }
        initialize(src: PixelMap | ResourceStr | DrawableDescriptor, options: ImageAIOptions): ImageAttribute {
            let arkImageNode = this.attribute as ArkImageNode;
            return arkImageNode!.initialize(src, options);
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
        initialize(value: BadgeParamWithNumber): BadgeAttribute {
            let arkBadgeNode = this.attribute as ArkBadgeNode;
            return arkBadgeNode!.initialize(value);
        }
        initialize(value: BadgeParamWithString): BadgeAttribute {
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


    class ButtonFrameNode extends TypedFrameNode<ArkButtonNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkButtonNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(): ButtonAttribute {
            let arkButtonNode = this.attribute as ArkButtonNode;
            return arkButtonNode!.initialize();
        }
        initialize(options: ButtonOptions): ButtonAttribute {
            let arkButtonNode = this.attribute as ArkButtonNode;
            return arkButtonNode!.initializeWithChild(options);
        }
        initialize(label: ResourceStr, options?: ButtonOptions): ButtonAttribute {
            let arkButtonNode = this.attribute as ArkButtonNode;
            return arkButtonNode!.initializeWithLabel(label, options);
        }
    }

    class CheckboxFrameNode extends TypedFrameNode<ArkCheckboxNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkCheckboxNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: CheckboxOptions): CheckboxAttribute {
            let arkCheckboxNode = this.attribute as ArkCheckboxNode;
            return arkCheckboxNode!.initialize(options);
        }
    }

    class CheckboxGroupFrameNode extends TypedFrameNode<ArkCheckboxGroupNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkCheckboxGroupNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: CheckboxGroupOptions): CheckboxGroupAttribute {
            let arkCheckboxGroupNode = this.attribute as ArkCheckboxGroupNode;
            return arkCheckboxGroupNode!.initialize(options);
        }
    }

    class RadioFrameNode extends TypedFrameNode<ArkRadioNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkRadioNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: RadioOptions): RadioAttribute {
            let arkRadioNode = this.attribute as ArkRadioNode;
            return arkRadioNode!.initialize(options);
        }
    }

    class RatingFrameNode extends TypedFrameNode<ArkRatingNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkRatingNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: RatingOptions): RatingAttribute {
            let arkRatingNode = this.attribute as ArkRatingNode;
            return arkRatingNode!.initialize(options);
        }
    }

    class SelectFrameNode extends TypedFrameNode<ArkSelectNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkSelectNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: Array<SelectOption>): SelectAttribute {
            let arkSelectNode = this.attribute as ArkSelectNode;
            return arkSelectNode!.initialize(options);
        }
    }

    class SliderFrameNode extends TypedFrameNode<ArkSliderNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkSliderNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: SliderOptions): SliderAttribute {
            let arkSliderNode = this.attribute as ArkSliderNode;
            return arkSliderNode!.initialize(options);
        }
    }

    class ToggleFrameNode extends TypedFrameNode<ArkToggleNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkToggleNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: ToggleOptions): ToggleAttribute {
            let arkToggleNode = this.attribute as ArkToggleNode;
            return arkToggleNode!.initialize(options);
        }
    }

    overload createNode { createListNode,
        createSearchNode, createTextAreaNode, createTextInputNode, createTextNode, createXComponentNodeDefault,
        createXComponentNodeWithOptions, createXComponentNodeWithNativeParameters, createSwiperNode, createBadgeNode,
        createQRCodeNode, createProgressNode, createLoadingProgressNode, createTextClockNode, createTextTimerNode,
        createButtonNode, createCheckboxNode, createCheckboxGroupNode, createRadioNode, createRatingNode,
        createSelectNode, createSliderNode, createToggleNode
    }

    // @ts-ignore
    export function createColumnNode(context: UIContext): ColumnFrameNode {
        return new ColumnFrameNode(context, 'Column', (node: FrameNode, type: ModifierType): ArkColumnNode => {
            let arknode = new ArkColumnNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkColumnPeer(retval, node._nodeId!.toInt(), "Column", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createRowNode(context: UIContext): RowFrameNode {
        return new RowFrameNode(context, 'Row', (node: FrameNode, type: ModifierType): ArkRowNode => {
            let arknode = new ArkRowNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkRowPeer(retval, node._nodeId!.toInt(), "Row", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createStackNode(context: UIContext): StackFrameNode {
        return new StackFrameNode(context, 'Stack', (node: FrameNode, type: ModifierType): ArkStackNode => {
            let arknode = new ArkStackNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkStackPeer(retval, node._nodeId!.toInt(), "Stack", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createFlexNode(context: UIContext): FlexFrameNode {
        return new FlexFrameNode(context, 'Flex', (node: FrameNode, type: ModifierType): ArkFlexNode => {
            let arknode = new ArkFlexNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkFlexPeer(retval, node._nodeId!.toInt(), "Flex", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridRowNode(context: UIContext): GridRowFrameNode {
        return new GridRowFrameNode(context, 'GridRow', (node: FrameNode, type: ModifierType): ArkGridRowNode => {
            let arknode = new ArkGridRowNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkGridRowPeer(retval, node._nodeId!.toInt(), "GridRow", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridColNode(context: UIContext): GridColFrameNode {
        return new GridColFrameNode(context, 'GridCol', (node: FrameNode, type: ModifierType): ArkGridColNode => {
            let arknode = new ArkGridColNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkGridColPeer(retval, node._nodeId!.toInt(), "GridCol", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createDividerNode(context: UIContext): DividerFrameNode {
        return new DividerFrameNode(context, 'Divider', (node: FrameNode, type: ModifierType): ArkDividerNode => {
            let arknode = new ArkDividerNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkDividerPeer(retval, node._nodeId!.toInt(), "Divider", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createBlankNode(context: UIContext): BlankFrameNode {
        return new BlankFrameNode(context, 'Blank', (node: FrameNode, type: ModifierType): ArkBlankNode => {
            let arknode = new ArkBlankNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkBlankPeer(retval, node._nodeId!.toInt(), "Blank", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createRelativeContainerNode(context: UIContext): RelativeContainerFrameNode {
        return new RelativeContainerFrameNode(context, 'RelativeContainer', (node: FrameNode, type: ModifierType): ArkRelativeContainerNode => {
            let arknode = new ArkRelativeContainerNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkRelativeContainerPeer(retval, node._nodeId!.toInt(), "RelativeContainer", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createListNode(context: UIContext): ListFrameNode {
        return new ListFrameNode(context, 'List', (node: FrameNode, type: ModifierType): ArkListNode => {
            let arknode = new ArkListNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkListPeer(retval, node._nodeId!.toInt(), "List", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createListItemNode(context: UIContext): ListItemFrameNode {
        return new ListItemFrameNode(context, 'ListItem', (node: FrameNode, type: ModifierType): ArkListItemNode => {
            let arknode = new ArkListItemNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkListItemPeer(retval, node._nodeId!.toInt(), "ListItem", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createListItemGroupNode(context: UIContext): ListItemGroupFrameNode {
        return new ListItemGroupFrameNode(context, 'ListItemGroup', (node: FrameNode, type: ModifierType): ArkListItemGroupNode => {
            let arknode = new ArkListItemGroupNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkListItemGroupPeer(retval, node._nodeId!.toInt(), "ListItemGroup", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createScrollNode(context: UIContext): ScrollFrameNode {
        return new ScrollFrameNode(context, 'Scroll', (node: FrameNode, type: ModifierType): ArkScrollNode => {
            let arknode = new ArkScrollNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkScrollPeer(retval, node._nodeId!.toInt(), "Scroll", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridNode(context: UIContext): GridFrameNode {
        return new GridFrameNode(context, 'Grid', (node: FrameNode, type: ModifierType): ArkGridNode => {
            let arknode = new ArkGridNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkGridPeer(retval, node._nodeId!.toInt(), "Grid", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createGridItemNode(context: UIContext): GridItemFrameNode {
        return new GridItemFrameNode(context, 'GridItem', (node: FrameNode, type: ModifierType): ArkGridItemNode => {
            let arknode = new ArkGridItemNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkGridItemPeer(retval, node._nodeId!.toInt(), "GridItem", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createWaterFlowNode(context: UIContext): WaterFlowFrameNode {
        return new WaterFlowFrameNode(context, 'WaterFlow', (node: FrameNode, type: ModifierType): ArkWaterFlowNode => {
            let arknode = new ArkWaterFlowNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkWaterFlowPeer(retval, node._nodeId!.toInt(), "WaterFlow", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createFlowItemNode(context: UIContext): FlowItemFrameNode {
        return new FlowItemFrameNode(context, 'FlowItem', (node: FrameNode, type: ModifierType): ArkFlowItemNode => {
            let arknode = new ArkFlowItemNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkFlowItemPeer(retval, node._nodeId!.toInt(), "FlowItem", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createSearchNode(context: UIContext): SearchFrameNode {
        return new SearchFrameNode(context, 'Search', (node: FrameNode, type: ModifierType): ArkSearchNode => {
            let arknode = new ArkSearchNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkSearchPeer(retval, node._nodeId as int32, "Search", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createSwiperNode(context: UIContext): SwiperFrameNode {
        return new SwiperFrameNode(context, 'Swiper', (node: FrameNode, type: ModifierType): ArkSwiperNode => {
            let arknode = new ArkSwiperNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkSwiperPeer(retval, node._nodeId!.toInt(), "Swiper", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextAreaNode(context: UIContext): TextAreaFrameNode {
        return new TextAreaFrameNode(context, 'TextArea', (node: FrameNode, type: ModifierType): ArkTextAreaNode => {
            let arknode = new ArkTextAreaNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkTextAreaPeer(retval, node._nodeId as int32, "TextArea", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextInputNode(context: UIContext): TextInputFrameNode {
        return new TextInputFrameNode(context, 'TextInput', (node: FrameNode, type: ModifierType): ArkTextInputNode => {
            let arknode = new ArkTextInputNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkTextInputPeer(retval, node._nodeId as int32, "TextInput", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextNode(context: UIContext): TextFrameNode {
        return new TextFrameNode(context, 'Text', (node: FrameNode, type: ModifierType): ArkTextNode => {
            let arknode = new ArkTextNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkTextPeer(retval, node._nodeId as int32, "Text", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    class ArkMarqueePeerCustom extends ArkMarqueePeer {
        constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
            super(peerPtr, id, name, flags)
        }
    }
    // @ts-ignore
    function createMarqueeNode(context: UIContext): MarqueeFrameNode {
        return new MarqueeFrameNode(context, 'Marquee', (node: FrameNode, type: ModifierType): ArkMarqueeNode => {
            let arknode = new ArkMarqueeNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkMarqueePeerCustom(retval, node._nodeId as int32, "Marquee", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    class ArkSymbolGlyphPeerCustom extends ArkSymbolGlyphPeer {
        constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
            super(peerPtr, id, name, flags)
        }
    }
    // @ts-ignore
    function createSymbolGlyphNode(context: UIContext): SymbolGlyphFrameNode {
        return new SymbolGlyphFrameNode(context, 'SymbolGlyph', (node: FrameNode, type: ModifierType): ArkSymbolGlyphNode => {
            let arknode = new ArkSymbolGlyphNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkSymbolGlyphPeerCustom(retval, node._nodeId as int32, "SymbolGlyph", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createXComponentNodeDefault(context: UIContext): XComponentFrameNode {
        let xcFrameNode = new XComponentFrameNode(context, 'XComponent', (node: FrameNode, type: ModifierType): ArkXComponentNode => {
            let arknode = new ArkXComponentNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new TypedXComponentPeerInternal(retval, node._nodeId as int32, "XComponent", 0);
            arknode.setPeer(peer);
            return arknode;
        });
        xcFrameNode.initialize({ type: XComponentType.SURFACE } as NativeXComponentParameters);
        return xcFrameNode;
    }

    // @ts-ignore
    function createXComponentNodeWithOptions(context: UIContext, options: XComponentOptions): XComponentFrameNode {
        let xcFrameNode = new XComponentFrameNode(context, 'XComponent', (node: FrameNode, type: ModifierType): ArkXComponentNode => {
            let arknode = new ArkXComponentNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new TypedXComponentPeerInternal(retval, node._nodeId as int32, "XComponent", 0);
            arknode.setPeer(peer);
            return arknode;
        });
        xcFrameNode.initialize(options);
        return xcFrameNode;
    }

    // @ts-ignore
    function createXComponentNodeWithNativeParameters(context: UIContext, parameters: NativeXComponentParameters): XComponentFrameNode {
        let xcFrameNode = new XComponentFrameNode(context, 'XComponent', (node: FrameNode, type: ModifierType): ArkXComponentNode => {
            let arknode = new ArkXComponentNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new TypedXComponentPeerInternal(retval, node._nodeId as int32, "XComponent", 0);
            arknode.setPeer(peer);
            return arknode;
        });
        xcFrameNode.initialize(parameters);
        return xcFrameNode;
    }

    // @ts-ignore
    function createImageNode(context: UIContext): ImageFrameNode {
        return new ImageFrameNode(context, 'Image', (node: FrameNode, type: ModifierType): ArkImageNode => {
            let arknode = new ArkImageNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkImagePeer(retval, node._nodeId as int32, 'Image', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function getImageAttribute(node: FrameNode): ImageAttribute | undefined {
        if (node.getType() !== 'Image') {
            return undefined
        }
        let imageNode = node as ImageFrameNode
        if (imageNode !== undefined) {
            return imageNode.attribute
        }
        return undefined
    }

    // @ts-ignore
    function createBadgeNode(context: UIContext): BadgeFrameNode {
        return new BadgeFrameNode(context, 'Badge', (node: FrameNode, type: ModifierType): ArkBadgeNode => {
            let arknode = new ArkBadgeNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkBadgePeer(retval, node._nodeId as int32, 'Badge', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createQRCodeNode(context: UIContext): QRCodeFrameNode {
        return new QRCodeFrameNode(context, 'QRCode', (node: FrameNode, type: ModifierType): ArkQRCodeNode => {
            let arknode = new ArkQRCodeNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkQRCodePeer(retval, node._nodeId as int32, 'QRCode', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createProgressNode(context: UIContext): ProgressFrameNode {
        return new ProgressFrameNode(context, 'Progress', (node: FrameNode, type: ModifierType): ArkProgressNode => {
            let arknode = new ArkProgressNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkProgressPeer(retval, node._nodeId as int32, 'Progress', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createLoadingProgressNode(context: UIContext): LoadingProgressFrameNode {
        return new LoadingProgressFrameNode(context, 'LoadingProgress', (node: FrameNode, type: ModifierType): ArkLoadingProgressNode => {
            let arknode = new ArkLoadingProgressNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkLoadingProgressPeer(retval, node._nodeId as int32, 'LoadingProgress', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextClockNode(context: UIContext): TextClockFrameNode {
        return new TextClockFrameNode(context, 'TextClock', (node: FrameNode, type: ModifierType): ArkTextClockNode => {
            let arknode = new ArkTextClockNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkTextClockPeer(retval, node._nodeId as int32, 'TextClock', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    function createTextTimerNode(context: UIContext): TextTimerFrameNode {
        return new TextTimerFrameNode(context, 'TextTimer', (node: FrameNode, type: ModifierType): ArkTextTimerNode => {
            let arknode = new ArkTextTimerNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkTextTimerPeer(retval, node._nodeId as int32, 'TextTimer', 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createButtonNode(context: UIContext): ButtonFrameNode {
        return new ButtonFrameNode(context, 'Button', (node: FrameNode, type: ModifierType): ArkButtonNode => {
            let arknode = new ArkButtonNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkButtonPeer(retval, node._nodeId as int32, "Button", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createCheckboxNode(context: UIContext): CheckboxFrameNode {
        return new CheckboxFrameNode(context, 'Checkbox', (node: FrameNode, type: ModifierType): ArkCheckboxNode => {
            let arknode = new ArkCheckboxNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkCheckboxPeer(retval, node._nodeId as int32, "Checkbox", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createCheckboxGroupNode(context: UIContext): CheckboxGroupFrameNode {
        return new CheckboxGroupFrameNode(context, 'CheckboxGroup', (node: FrameNode, type: ModifierType): ArkCheckboxGroupNode => {
            let arknode = new ArkCheckboxGroupNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkCheckboxGroupPeer(retval, node._nodeId as int32, "CheckboxGroup", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createRadioNode(context: UIContext): RadioFrameNode {
        return new RadioFrameNode(context, 'Radio', (node: FrameNode, type: ModifierType): ArkRadioNode => {
            let arknode = new ArkRadioNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkRadioPeer(retval, node._nodeId as int32, "Radio", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createRatingNode(context: UIContext): RatingFrameNode {
        return new RatingFrameNode(context, 'Rating', (node: FrameNode, type: ModifierType): ArkRatingNode => {
            let arknode = new ArkRatingNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkRatingPeer(retval, node._nodeId as int32, "Rating", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createSelectNode(context: UIContext): SelectFrameNode {
        return new SelectFrameNode(context, 'Select', (node: FrameNode, type: ModifierType): ArkSelectNode => {
            let arknode = new ArkSelectNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkSelectPeer(retval, node._nodeId as int32, "Select", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createSliderNode(context: UIContext): SliderFrameNode {
        return new SliderFrameNode(context, 'Slider', (node: FrameNode, type: ModifierType): ArkSliderNode => {
            let arknode = new ArkSliderNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkSliderPeer(retval, node._nodeId as int32, "Slider", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }

    // @ts-ignore
    export function createToggleNode(context: UIContext, options?: ToggleOptions): ToggleFrameNode {
        let toggleNode = new ToggleFrameNode(context, 'Toggle', (node: FrameNode, type: ModifierType): ArkToggleNode => {
            let arknode = new ArkToggleNode();
            const retval = FrameNodeExtender.getFrameNodePtr(node);
            const peer = new ArkTogglePeer(retval, node._nodeId as int32, "Toggle", 0);
            arknode.setPeer(peer);
            return arknode;
        });
        toggleNode.initialize(options as ToggleOptions);
        return toggleNode;
    }
}

class NodeAdapterThunk extends NativeThunk {
    private ptr?: pointer;

    constructor(obj: pointer) {
        super(obj, nullptr);
    }

    clean(): void {
        if (this.ptr) {
            ArkUIAniModule._NodeAdapter_Dispose(this.ptr!);
        }
    }
}

class NodeAdapterFinalizable extends Finalizable {
    constructor(ptr: pointer) {
        super(ptr, nullptr, false);
        this.init(ptr)
    }

    init(ptr: pointer): void {
        this.ptr = ptr
        const thunk = new NodeAdapterThunk(ptr)
        finalizerRegister(this, thunk)
        this.cleaner = thunk
    }
}

export class NodeAdapter implements MaterializedBase {
    private peer?: Finalizable | undefined = undefined;
    private attachedNodeRef_?: WeakRef<FrameNode>;
    private count_: int = 0;
    private nodeRefs_: Array<FrameNode> = new Array<FrameNode>();

    onDisposeChild(index: int32, node: FrameNode) {

    }

    onUpdateChild(index: int32, node: FrameNode) {

    }

    onCreateChild(index: int): FrameNode {
        return new FrameNode(undefined);
    }

    constructor() {
        const retval = ArkUIAniModule._NodeAdapter_Construct(this);
        this.peer = new NodeAdapterFinalizable(retval);
    }
    getPeer(): Finalizable | undefined {
        return this.peer;
    }

    dispose() {
        let hostNode = this.attachedNodeRef_?.deref();
        if (hostNode !== undefined) {
            NodeAdapter.detachNodeAdapter(hostNode);
        }
        if (this.peer?.ptr) {
            this.peer?.close();
        }
    }

    set totalNodeCount(count: int) {
        if (count < 0) {
            return;
        }
        ArkUIAniModule._NodeAdapter_SetTotalNodeCount(this.peer!.ptr!, count);
        this.count_ = count;
    }

    get totalNodeCount() {
        return this.count_;
    }

    reloadAllItems() {
        ArkUIAniModule._NodeAdapter_NotifyItemReloaded(this.peer!.ptr!);
    }
    reloadItem(start: int32, count: int32) {
        if (start < 0 || count < 0) {
            return;
        }
        ArkUIAniModule._NodeAdapter_NotifyItemChanged(this.peer!.ptr!, start, count);
    }
    removeItem(start: int32, count: int32) {
        if (start < 0 || count < 0) {
            return;
        }
        ArkUIAniModule._NodeAdapter_NotifyItemRemoved(this.peer!.ptr!, start, count);
    }
    insertItem(start: int32, count: int32) {
        if (start < 0 || count < 0) {
            return;
        }
        ArkUIAniModule._NodeAdapter_NotifyItemInserted(this.peer!.ptr!, start, count);
    }
    moveItem(from: int32, to: int32) {
        if (from < 0 || to < 0) {
            return;
        }
        ArkUIAniModule._NodeAdapter_NotifyItemMoved(this.peer!.ptr!, from, to);
    }
    getAllAvailableItems(): Array<FrameNode> {
        let result = new Array<FrameNode>();
        let nodes = ArkUIAniModule._NodeAdapter_GetAllItems(this.peer!.ptr!);
        if (nodes !== undefined) {
            nodes.forEach((nodeId: number, index: int, arr: Array<number>) => {
                if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                    let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
                    result.push(frameNode!);
                }
            });
        }
        return result;
    }
    onAttachToNodePtr(nodeId: number) {
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
            if (frameNode === undefined) {
                return;
            }
            frameNode.setAdapterRef(this);
            this.attachedNodeRef_ = new WeakRef<FrameNode>(frameNode);
            if (this.onAttachToNode !== undefined) {
                this.onAttachToNode(frameNode);
            }
        }
    }
    onAttachToNode(frameNode: FrameNode): void {

    }
    onDetachFromNode(): void {

    }
    onDetachFromNodePtr() {
        if (this === undefined) {
            return;
        }
        if (this.onDetachFromNode !== undefined) {
            this.onDetachFromNode();
        }
        let attachedNode = this.attachedNodeRef_?.deref();
        if (attachedNode !== undefined) {
            attachedNode.setAdapterRef(undefined);
        }
        this.nodeRefs_.splice(0, this.nodeRefs_.length);
    }
    onCreateNewNodePtr(index: number): pointer {
        if (this.onCreateChild !== undefined) {
            let frameNode = this.onCreateChild(index as int32);
            if (!this.nodeRefs_.find((node) => {
                return node === frameNode;
            })) {
                this.nodeRefs_.push(frameNode);
            }
            if (frameNode?.peer?.ptr) {
                return frameNode!.peer!.ptr!;
            }
        }
        return nullptr;
    }

    onDisposeNodePtr(index: number, nodeId: number) {
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
            if (this.onDisposeChild !== undefined && frameNode !== undefined) {
                this.onDisposeChild((index as int32), frameNode);
                let index2 = this.nodeRefs_.indexOf(frameNode);
                if (index2 > -1) {
                    this.nodeRefs_.splice(index2, 1);
                }
            }
        }
    }

    onUpdateNodePtr(index: number, nodeId: number) {
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId);
            if (this.onUpdateChild !== undefined && frameNode !== undefined) {
                this.onUpdateChild((index as int32), frameNode!);
            }
        }
    }

    static detachNodeAdapter(node: FrameNode) {
        ArkUIAniModule._NodeAdapter_DetachNodeAdapter(node.peer!.ptr!);
    }

    static attachNodeAdapter(adapter: NodeAdapter, node: FrameNode) {
        return ArkUIAniModule._NodeAdapter_AttachNodeAdapter(adapter.peer!.ptr!, node.peer!.ptr!);
    }
}
