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

import { UIContext } from "@ohos/arkui/UIContext"
import { UIContextImpl } from "arkui/handwritten/UIContextImpl"
import { Position, Edges, Size, LengthMetrics, SizeT } from "./Graphics"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import {
    Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer,
    MaterializedBase, NativeBuffer, nullptr, pointer, KSerializerBuffer, KUint8ArrayPtr
} from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./component"
import { ArkUIAniModule } from "arkui.ani"
import { RenderNode, RenderNodeInternal } from "./RenderNode"
import { CommonAttribute, ArkCommonMethodPeer, CommonMethod, UIGestureEvent, UICommonEvent, UICommonEventInternal } from './component/common'
import { ArkBaseNode } from './handwritten/modifiers/ArkBaseNode'
import { ArkListNode } from './handwritten/modifiers/ArkListNode'
import { ArkSearchNode } from './handwritten/modifiers/ArkSearchNode'
import { ArkTextAreaNode } from './handwritten/modifiers/ArkTextAreaNode'
import { ArkTextInputNode } from './handwritten/modifiers/ArkTextInputNode'
import { ModifierType } from './handwritten/modifiers/ArkCommonModifier'
import { ListOptions, ListAttribute, ArkListPeer } from './component/list'
import { SearchOptions, SearchAttribute, ArkSearchPeer } from './component/search'
import { TextAreaOptions, TextAreaAttribute, ArkTextAreaPeer } from './component/textArea'
import { TextInputOptions, TextInputAttribute, ArkTextInputPeer } from './component/textInput'
import { ArkTextNode } from './handwritten/modifiers/ArkTextNode'
import { TextOptions, TextAttribute, ArkTextPeer } from './component/text'
import { Deserializer } from "./component/peers/Deserializer";
import { ComponentContent } from './ComponentContent';
import { DrawContext } from './Graphics';
import { JSBuilderNode } from "./BuilderNode"
import { BusinessError } from '#external';
import { Resource } from 'global.resource';

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
    public _nodeId: number = -1;
    protected _commonAttribute: CommonAttribute | undefined = undefined;
    protected _gestureEvent: UIGestureEvent | undefined = undefined;

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
            const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(this))
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
            if (type === 'ProxyFrameNode') {
                if (ptr) {
                    this.peer = new Finalizable(ptr, FrameNode.getFinalizer());
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
                const ctorPtr: KPointer = FrameNode.ctor_framenode()
                this.peer = new Finalizable(ctorPtr, FrameNode.getFinalizer())
            } else {
                const retval = ArkUIGeneratedNativeModule._FrameNode_createTypedFrameNode(type as string);
                this.peer = new Finalizable(retval, FrameNode.getFinalizer());
            }
            this.renderNode_?.setFrameNode(new WeakRef<FrameNode>(this))

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
        this.appendChild(content.getFrameNode()!);
        ArkUIAniModule._Common_Restore_InstanceId();
        content.setAttachedParent(new WeakRef<FrameNode>(this));
    }
    public removeComponentContent<T = undefined>(content: ComponentContent<T>) {
        if (content === undefined || content === null || content.getFrameNode() == undefined ||
            content.getFrameNode() == null || content.getNodePtr() == undefined) {
            return;
        }
        const instanceId = this.instanceId_!.toInt();
        ArkUIAniModule._Common_Sync_InstanceId(instanceId);
        this.removeChild(content.getFrameNode()!);
        ArkUIAniModule._Common_Restore_InstanceId();
        content.setAttachedParent(undefined);
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
    public getChild(index: number): FrameNode {
        const index_casted = index
        return this.getChild_serialize(index_casted)
    }
    public getFirstChild(): FrameNode {
        return this.getFirstChild_serialize()
    }
    public getNextSibling(): FrameNode {
        return this.getNextSibling_serialize()
    }
    public getPreviousSibling(): FrameNode {
        return this.getPreviousSibling_serialize()
    }
    public getParent(): FrameNode {
        return this.getParent_serialize()
    }
    public getChildrenCount(): int32 {
        return this.getChildrenCount_serialize()
    }
    public dispose(): void {
        this.dispose_serialize()
        return
    }
    public getOpacity(): number {
        return this.getOpacity_serialize()
    }
    public getPositionToWindowWithTransform(): Position {
        return this.getPositionToWindowWithTransform_serialize()
    }
    public static getFrameNodeByKey(name: string): FrameNode {
        const name_casted = name as (string)
        return FrameNode.getFrameNodeByKey_serialize(name_casted)
    }
    private isModifiable_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_isModifiable(this.peer!.ptr)
        return retval
    }
    private appendChild_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_appendChild(this.peer!.ptr, toPeerPtr(node))
    }
    private insertChildAfter_serialize(child: FrameNode, sibling: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_insertChildAfter(this.peer!.ptr, toPeerPtr(child), toPeerPtr(sibling))
    }
    private removeChild_serialize(node: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNode_removeChild(this.peer!.ptr, toPeerPtr(node))
    }
    private clearChildren_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_clearChildren(this.peer!.ptr)
    }
    private getChild_serialize(index: number): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getChild(this.peer!.ptr, index)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getFirstChild_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFirstChild(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getNextSibling_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getNextSibling(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getPreviousSibling_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getPreviousSibling(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getParent_serialize(): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getParent(this.peer!.ptr)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    private getChildrenCount_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getChildrenCount(this.peer!.ptr)
        return retval
    }
    private dispose_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_dispose(this.peer!.ptr)
    }
    private getOpacity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getOpacity(this.peer!.ptr)
        return retval
    }
    private getPositionToWindowWithTransform_serialize(): Position {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getPositionToWindowWithTransform(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length.toInt());
        const returnResult : Position = retvalDeserializer.readGraphicsPosition()
        return returnResult
    }
    private static getFrameNodeByKey_serialize(name: string): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(name)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
}
