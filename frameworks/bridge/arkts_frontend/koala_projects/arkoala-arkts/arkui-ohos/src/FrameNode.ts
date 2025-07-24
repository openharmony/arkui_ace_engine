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
import { Position as Position } from "./Graphics"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer,
    MaterializedBase, NativeBuffer, nullptr, pointer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./component"
import { ArkUIAniModule } from "arkui.ani"
import { RenderNode, RenderNodeInternal } from "./RenderNode"
import { CommonAttribute, ArkCommonMethodPeer, CommonMethod } from './component/common'
import { ArkBaseNode } from './handwritten/modifiers/ArkBaseNode'
import { ArkListNode } from './handwritten/modifiers/ArkListNode'
import { ModifierType } from './handwritten/modifiers/ArkCommonModifier'
import { ListOptions, ListAttribute, ArkListPeer } from './component/list'
import { Deserializer } from "./component/peers/Deserializer";

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
    constructor() {}
    public static instance_: FrameNodeFinalizationRegisterProxy = new FrameNodeFinalizationRegisterProxy();
    public static ElementIdToOwningFrameNode_ = new Map<number, FrameNode>();

}

export class FrameNodeInternal {
    public static fromPtr(ptr: KPointer): FrameNode {
        const obj : FrameNode = new FrameNode(undefined)
        obj.peer = new Finalizable(ptr, FrameNode.getFinalizer())
        return obj
    }
}
export class FrameNode implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    uiContext: UIContext | undefined = undefined
    renderNode_: RenderNode | undefined = undefined
    instanceId_?: number;
    _nodeId: number = -1;
    protected _commonAttribute: CommonAttribute | undefined = undefined;
    getType(): string {
        return 'CustomFrameNode';
    }

    checkValid(node:FrameNode): boolean {
        return true;
    }
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_framenode(): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        const retval  = ArkUIGeneratedNativeModule._FrameNode_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(uiContext?: UIContext, type?: string, ptr?: KPointer) {
        if ((uiContext) !== (undefined))
        {
            this.uiContext = uiContext;
            this.instanceId_ = uiContext.instanceId_;
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
            const instanceId = this.instanceId_ as (int32);
            ArkUIAniModule._Common_Sync_InstanceId(instanceId);
            if (this.getType() === undefined || this.getType() === "CustomFrameNode") {
                this.renderNode_ = new RenderNode('CustomFrameNode')
                const ctorPtr: KPointer = FrameNode.ctor_framenode()
                this.peer = new Finalizable(ctorPtr, FrameNode.getFinalizer())
            } else {
                const retval  = ArkUIGeneratedNativeModule._FrameNode_createTypedFrameNode(type as string);
                this.peer = new Finalizable(retval, FrameNode.getFinalizer());
            }
            this.renderNode_?.setFrameNode(new WeakRef<FrameNode>(this))

            this._nodeId = this.getIdByFrameNode_serialize(this);
            ArkUIAniModule._Common_Restore_InstanceId();
            FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.set(this._nodeId, this);
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FrameNode_getFinalizer();
    }
    public isModifiable(): boolean {
        return this.isModifiable_serialize();
    }
    public appendChild(node: FrameNode): void {
        if (node.getType() === 'ProxyFrameNode' || !this.checkValid(node)) {
            throw Error("The FrameNode is not modifiable.");
        }
        const node_casted = node as (FrameNode)
        this.appendChild_serialize(node_casted)
        return
    }
    public insertChildAfter(child: FrameNode, sibling: FrameNode | null): void {
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
            const instanceId = this.instanceId_ as (int32);
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
        let expand_casted : number = 1;
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
        this.dispose_serialize();
        return
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
    private isModifiable_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_isModifiable(this.peer!.ptr)
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
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getChild(this.peer!.ptr, index, expandMode);
        if (retval) {
            const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getFirstChild_serialize(): FrameNode | null {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFirstChild(this.peer!.ptr);
        if (retval) {
            const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getNextSibling_serialize(): FrameNode | null {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getNextSibling(this.peer!.ptr);
        if (retval) {
            const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getPreviousSibling_serialize(): FrameNode | null {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getPreviousSibling(this.peer!.ptr);
        if (retval) {
            const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getParent_serialize(): FrameNode | null {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getParent(this.peer!.ptr);
        if (retval) {
            const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
            return obj;
        } else {
            return null;
        }
    }
    private getChildrenCount_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getChildrenCount(this.peer!.ptr);
        return retval;
    }
    private dispose_serialize(): void {
        ArkUIGeneratedNativeModule._FrameNode_dispose(this.peer!.ptr);
    }
    private getOpacity_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getOpacity(this.peer!.ptr);
        return retval;
    }
    private getPositionToWindowWithTransform_serialize(): Position {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getPositionToWindowWithTransform(this.peer!.ptr) as FixedArray<byte>;
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>;
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]));
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32);
        const returnResult : Position = retvalDeserializer.readGraphicsPosition();
        return returnResult;
    }
    private static getFrameNodeByKey_serialize(name: string): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(name)
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
    public getIdByFrameNode(node: FrameNode): number {
        const node_casted = node as (FrameNode);
        return this.getIdByFrameNode_serialize(node_casted);
    }
    private getIdByFrameNode_serialize(node: FrameNode): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(this.peer!.ptr, toPeerPtr(node));
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
        if (oldParent && !oldParent.isModifiable() || !targetParent.isModifiable()) {
            throw Error("The FrameNode is not modifiable.");
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
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFirstChildIndexWithoutExpand(this.peer!.ptr);
        return retval;
    }
    private getLastChildIndexWithoutExpand_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getLastChildIndexWithoutExpand(this.peer!.ptr);
        return retval;
    }
    public static getAttachedFrameNodeById(id: string): FrameNode {
        const id_casted = id as (string);
        return FrameNode.getAttachedFrameNodeById_serialize(id_casted);
    }
    public static getFrameNodeById(id: number): FrameNode {
        const id_casted = id as (number);
        return FrameNode.getFrameNodeById_serialize(id_casted);
    }
    public static getFrameNodeByUniqueId(id: number): FrameNode {
        const id_casted = id as (number);
        return FrameNode.getFrameNodeByUniqueId_serialize(id_casted);
    }
	private static getAttachedFrameNodeById_serialize(id: string): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getAttachedFrameNodeById(id);
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
        return obj;
    }
    private static getFrameNodeById_serialize(id: number): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeById(id);
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
        return obj;
    }
    private static getFrameNodeByUniqueId_serialize(id: number): FrameNode {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByUniqueId(id);
        const obj : FrameNode = FrameNodeInternal.fromPtr(retval);
        return obj;
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
        const retval = ArkUIGeneratedNativeModule._FrameNode_getRenderNode(this.peer!.ptr)
        return RenderNodeInternal.fromPtr(retval)
    }
    public static getFrameNodePtr(node: FrameNode): KPointer {
        const node_casted = node as (FrameNode)
        return FrameNode.getFrameNodePtr_serialize(node_casted)
    }
    private static getFrameNodePtr_serialize(node: FrameNode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node))
        return retval
    }
    get commonAttribute(): CommonMethod {
        if (this._commonAttribute === undefined) {
            let baseNode = new ArkBaseNode();
            const retval  = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(this))
            let peer = new ArkFrameNodePeer(retval, this._nodeId as int32, "FrameNode", 0);
            baseNode.setPeer(peer);
            this._commonAttribute = baseNode as CommonAttribute;
        }
        return this._commonAttribute!;
    }
    public static createTypedFrameNode(type: string): FrameNode {
        const type_casted = type as (string)
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
        throw Error("The FrameNode is not modifiable.");
    }
    insertChildAfter(child: FrameNode, sibling: FrameNode | null): void {
        throw Error("The FrameNode is not modifiable.");
    }
    removeChild(node: FrameNode): void {
        throw Error("The FrameNode is not modifiable.");
    }
    clearChildren(): void {
        throw Error("The FrameNode is not modifiable.");
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
        throw Error("The FrameNode is not modifiable.");
    }
  }
export interface ResultFrameNode {
    nodeId: int32;
    frameNode: FrameNode;
}
export class FrameNodeUtils {
    static searchNodeInRegisterProxy(ptr: KPointer): FrameNode | null {
        const nodeId  = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(ptr, ptr);
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
        const nodeId  = ArkUIGeneratedNativeModule._FrameNode_getIdByFrameNode(ptr, ptr);
        if (nodeId !== -1 && !ArkUIGeneratedNativeModule._FrameNode_isModifiable(ptr)) {
            let frameNode = new ProxyFrameNode(uiContext, "ProxyFrameNode", ptr);
            frameNode._nodeId = nodeId;
            frameNode!.peer!.ptr = ptr;
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
    class ListFrameNode extends TypedFrameNode<ArkListNode> {
        constructor(uiContext: UIContext, type: string, attrCreator: (node: FrameNode, type: ModifierType) => ArkListNode) {
            super(uiContext, type, attrCreator);
        }
        initialize(options: ListOptions): ListAttribute {
            let arkListNode = this.attribute as ArkListNode;
            return arkListNode!.initialize(options);
        }
    }

    // @ts-ignore
    function createNode(context: UIContext, type: string): ListFrameNode {
        return new ListFrameNode(context, 'List', (node: FrameNode, type: ModifierType): ArkListNode => {
            let arknode = new ArkListNode();
            const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodePtr(toPeerPtr(node));
            const peer = new ArkListPeer(retval, node._nodeId as int32, "List", 0);
            arknode.setPeer(peer);
            return arknode;
        });
    }
}