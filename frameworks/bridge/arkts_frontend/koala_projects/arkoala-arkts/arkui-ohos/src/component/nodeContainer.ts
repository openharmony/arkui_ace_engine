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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, pointer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, TouchEvent } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { NodeController } from "../NodeController"
import { UIContext } from "@ohos/arkui/UIContext"
import { FrameNode } from "../FrameNode"
import { Size } from "../Graphics"
export type NodeContainer_AboutToResizeCallback = (size: Size) => void;
export class ArkNodeContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkNodeContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._NodeContainer_construct(peerId, flags)
        const _peer  = new ArkNodeContainerPeer(_peerPtr, peerId, "NodeContainer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNodeContainerOptionsAttribute(controller: NodeController): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNodeController(controller)
        ArkUIGeneratedNativeModule._NodeContainerInterface_setNodeContainerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    addNodeContainerRootNode(child: FrameNode | null) {
        if (!child) {
            ArkUIGeneratedNativeModule._NodeContainerInterface_addNodeContainerRootNode(this.peer.ptr, 0)
            return
        }
        ArkUIGeneratedNativeModule._NodeContainerInterface_addNodeContainerRootNode(this.peer.ptr, child.getPeer()?.ptr as pointer)
    }
    aboutToAppearAttribute(value: (() => void)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerInterface_setAboutToAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToDisappearAttribute(value: (() => void)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerInterface_setAboutToDisappear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToResizeAttribute(value: ((size: Size) => void)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerInterface_setAboutToResize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAttachAttribute(value: (() => void)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerInterface_setOnAttach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDetachAttribute(value: (() => void)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerInterface_setOnDetach(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTouchEventAttribute(value: ((event: TouchEvent) => void)) {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NodeContainerInterface_setOnTouchEvent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type NodeContainerInterface = (controller: NodeController) => NodeContainerAttribute;
export interface NodeContainerAttribute extends CommonMethod {
}
export class ArkNodeContainerStyle extends ArkCommonMethodStyle implements NodeContainerAttribute {
}
export class ArkNodeContainerComponent extends ArkCommonMethodComponent implements NodeContainerAttribute {
    private controller: NodeController | null = null;
    getPeer(): ArkNodeContainerPeer {
        return (this.peer as ArkNodeContainerPeer)
    }
    public setNodeContainerOptions(controller: NodeController): this {
        if (this.checkPriority("setNodeContainerOptions")) {
            if (this.controller) {
                this.controller!.onWillUnbind(this.getPeer().getId())
                this.controller!.resetInternalField()
                this.controller!.onUnbind(this.getPeer().getId())
                this.controller = null
            }
            controller.onWillBind(this.getPeer().getId())
            this.controller = controller
            this.controller!.setNodeContainer(this)
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

            controller.onBind(this.getPeer().getId())
            // makeNode
            const makeNodeFunc = controller.__makeNode__
            const child = makeNodeFunc(new UIContext(100000))
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
            const child = makeNodeFunc(new UIContext(100000))
            this.getPeer().addNodeContainerRootNode(child)
        }
    }
}
/** @memo */
export function NodeContainer(
    /** @memo */
    style: ((attributes: NodeContainerAttribute) => void) | undefined,
    controller: NodeController,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkNodeContainerComponent()
    })
    NodeAttach<ArkNodeContainerPeer>((): ArkNodeContainerPeer => ArkNodeContainerPeer.create(receiver), (_: ArkNodeContainerPeer) => {
        receiver.setNodeContainerOptions(controller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
