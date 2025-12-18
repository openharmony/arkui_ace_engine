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

import { int32, int64, float32 } from '@koalaui/common';
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase,
    toPeerPtr, wrapCallback, NativeBuffer, pointer } from '@koalaui/interop';
import { ComponentBase } from './../ComponentBase';
import { PeerNode } from './../PeerNode';
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent,
    TouchEvent } from './common';
import { NodeAttach, remember } from '@koalaui/runtime';
import { NodeController } from '../NodeController';
import { UIContext } from '@ohos/arkui/UIContext';
import { UIContextImpl, ContextRecord } from 'arkui/base/UIContextImpl';
import { FrameNode } from 'arkui/FrameNode';
import { Size } from '../Graphics';
import { StateManager } from '@koalaui/runtime';
import { __context } from '@koalaui/runtime';
import { extractors, AttributeModifier, hookNodeContainerAttributeModifier } from '#handwritten';
import { NodeContainerOps } from './../framework';
import { ModifierStateManager } from '../CommonModifier';
import { NodeContainerModifier } from './../NodeContainerModifier';

export type NodeContainer_AboutToResizeCallback = (size: Size) => void;
export class ArkNodeContainerPeer extends ArkCommonMethodPeer {
    attributeSet?: NodeContainerModifier;
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkNodeContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = NodeContainerOps.nodeContainerOpsConstruct(peerId, flags)
        const _peer  = new ArkNodeContainerPeer(_peerPtr, peerId, "NodeContainer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNodeContainerOptionsAttribute(controller: NodeController): void {
        NodeContainerOps.nodeContainerSetNodeContainerOptions(this.peer.ptr, extractors.toNodeControllerPtr(controller))
    }
    addNodeContainerRootNode(child: FrameNode | null) {
        if (!child) {
            NodeContainerOps.addNodeContainerRootNode(this.peer.ptr, 0)
            return
        }
        NodeContainerOps.addNodeContainerRootNode(this.peer.ptr, child.getPeer()?.ptr as pointer)
    }
    aboutToAppearAttribute(value: (() => void)) {
        NodeContainerOps.setAboutToAppear(this.peer.ptr, value);
    }
    aboutToDisappearAttribute(value: (() => void)) {
        NodeContainerOps.setAboutToDisappear(this.peer.ptr, value);
    }
    aboutToResizeAttribute(value: ((size: Size) => void)) {
        NodeContainerOps.setAboutToResize(this.peer.ptr, value);
    }
    onAttachAttribute(value: (() => void)) {
        NodeContainerOps.setOnAttach(this.peer.ptr, value);
    }
    onDetachAttribute(value: (() => void)) {
        NodeContainerOps.setOnDetach(this.peer.ptr, value);
    }
    onTouchEventAttribute(value: ((event: TouchEvent) => void)) {
        NodeContainerOps.setOnTouchEvent(this.peer.ptr, value);
    }
    resetNodeControllerFunc(value: ((containerId: long) => void)) {
        NodeContainerOps.setOnDestoryEvent(this.peer.ptr, value);
    }
}
export type NodeContainerInterface = (controller: NodeController) => NodeContainerAttribute;
export interface NodeContainerAttribute extends CommonMethod {
    setNodeContainerOptions(controller: NodeController): this {
        return this
    }
    attributeModifier(value: AttributeModifier<NodeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this;
    }
}
export class ArkNodeContainerComponent extends ArkCommonMethodComponent implements NodeContainerAttribute {
    private controller: NodeController | null = null;
    private uiContext: UIContext
    constructor(uiContext: UIContext) {
        this.uiContext = uiContext
    }
    getPeer(): ArkNodeContainerPeer {
        return (this.peer as ArkNodeContainerPeer)
    }
    public setNodeContainerOptions(controller: NodeController): this {
        if (this.checkPriority("setNodeContainerOptions")) {
            if (this.controller) {
                if (this.controller !== controller) {
                    this.controller!.resetInternalField(this.getPeer().getId())
                } else {
                    return this;
                }
            }

            let nodeId = controller?._nodeContainer?.getPeer()?.getId();
            if(nodeId && nodeId! > 0){
                controller!.resetInternalField(nodeId);
            }
            this.controller = controller
            // aboutToAppear
            const aboutToAppearFunc = controller.aboutToAppear
            this.getPeer().aboutToAppearAttribute(aboutToAppearFunc)
            // aboutToDisappear
            const aboutToDisappearFunc = controller.aboutToDisappear
            this.getPeer().aboutToDisappearAttribute(aboutToDisappearFunc)
            // aboutToResize
            const aboutToResizeFunc = controller.aboutToResize
            this.getPeer().aboutToResizeAttribute(aboutToResizeFunc)
            // onTouchEvent
            const onTouchEventFunc = controller.onTouchEvent
            this.getPeer().onTouchEventAttribute(onTouchEventFunc)
            // onAttach
            const onAttach = controller.onAttach
            this.getPeer().onAttachAttribute(onAttach)
            // onDetach
            const onDetach = controller.onDetach
            this.getPeer().onDetachAttribute(onDetach)

            // resetInternalField
            this.getPeer().resetNodeControllerFunc(this.controller!.resetInternalField)
            this.controller!.onWillBind(this.getPeer().getId())
            this.controller!.setNodeContainer(this)
            this.controller!.onBind(this.getPeer().getId());

            // makeNode
            const makeNodeFunc = controller.__makeNode__
            const child = makeNodeFunc(this.uiContext)
            this.getPeer().addNodeContainerRootNode(child)
        }
        return this
    }

    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public rebuild(): void {
        if (this.controller) {
            const makeNodeFunc = this.controller!.__makeNode__
            const child = makeNodeFunc(this.uiContext)
            this.getPeer().addNodeContainerRootNode(child)
        }
    }
    public attributeModifier(value: AttributeModifier<NodeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
         ModifierStateManager.INSTANCE.scope(() => {
            hookNodeContainerAttributeModifier(this, value);
        })
        return this;
    }
}
/** @memo */
export function NodeContainerImpl(
    /** @memo */
    style: ((attributes: NodeContainerAttribute) => void) | undefined,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const context: StateManager = __context() as StateManager;
    const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
    let uiContext = data?.uiContext
    const receiver = remember(() => {
        return new ArkNodeContainerComponent(uiContext!)
    })
    NodeAttach<ArkNodeContainerPeer>((): ArkNodeContainerPeer => ArkNodeContainerPeer.create(receiver), (_: ArkNodeContainerPeer) => {
        style?.(receiver)
        content_?.()
    })
}
