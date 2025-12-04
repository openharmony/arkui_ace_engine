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


import { ComponentBase } from "./../ComponentBase"
import { PeerNode, RootPeerType } from "./../PeerNode"
import { ArkCustomComponent } from "./../ArkCustomComponent"

import { ArkUIGeneratedNativeModule } from "#components"
import { ArkUIAniModule, ArkUIAniCustomNodeModule } from "arkui.ani"

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { IExtendableComponent } from './extendableComponent';
import { destroyUiDetachedRoot } from 'arkui/ArkUIEntry';
import { UIContextImpl } from 'arkui/base/UIContextImpl';
import { ArkUINativeModule } from '#components';

export class ArkRootPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Root_construct(peerId, flags)
        const _peer  = new ArkRootPeer(_peerPtr, peerId, "Root", flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkComponentRootPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags, RootPeerType)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkComponentRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ComponentRoot_construct(peerId, flags)
        const _peer  = new ArkComponentRootPeer(_peerPtr, peerId, "ComponentRoot", flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkCustomComponentRootPeer extends PeerNode {
    private component?: IExtendableComponent;
    private childPeerPtr: KPointer = nullptr;
    private buildFunc?: () => Long;
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags, RootPeerType)
    }
    setComponent(component: IExtendableComponent) {
        this.component = component;
        this.component!.__addMeToParent__IExtendableComponent_Internal();
    }
    getComponent(): IExtendableComponent | undefined {
        return this.component;
    }
    public static create(component: ArkCustomComponent, flags: int32 = 0): ArkCustomComponentRootPeer {
        const peerId  = PeerNode.nextId();
        if (component.isCustomLayout) {
            const _peerPtr = ArkUIAniCustomNodeModule._CustomNode_Construct(peerId, component);
            if (!_peerPtr) {
                throw new Error("create CustomComponent fail"); 
            }
            const _peer  = new ArkCustomComponentRootPeer(_peerPtr, peerId, "CustomComponent", flags);
            component.setPeer(_peer);
            _peer.setComponent(component as IExtendableComponent);
            return _peer;
        } else {
            const _peerPtr = ArkUIAniModule._CustomNode_Construct(peerId, component);
            if (!_peerPtr) {
                throw new Error("create CustomComponent fail"); 
            }
            const _peer  = new ArkCustomComponentRootPeer(_peerPtr, peerId, "CustomComponent", flags);
            component.setPeer(_peer);
            _peer.setComponent(component as IExtendableComponent);
            return _peer;
         }
    }
    dispose() {
        if (this.childPeerPtr !== nullptr) {
            destroyUiDetachedRoot(this.childPeerPtr, (this.component!.getUIContext() as UIContextImpl).getInstanceId());
            this.childPeerPtr = nullptr;
        }
        this.component?.__removeChildWhenDispose__IExtendableComponent_Internal();
        super.dispose();
    }

    setBuildFunction(buildFunc: () => Long): void {
        this.buildFunc = buildFunc;
        ArkUIAniCustomNodeModule._CustomNode_SetBuildFunction(this.peer.ptr, buildFunc);
    }

    setChildPeerPtr(childPeerPtr: KPointer): void {
        this.childPeerPtr = childPeerPtr;
        if (this.component instanceof ArkCustomComponent && (this.component as ArkCustomComponent).isCustomLayout) {
            ArkUINativeModule._AddChild(this.peer.ptr, childPeerPtr);
            ArkUINativeModule._MarkDirty(this.peer.ptr, 0);
        }
    }
}
export interface Root {
}
export interface UIRoot {
}
export class ArkRootStyle implements Root {
    
}
export interface ComponentRoot {
}
export interface UIComponentRoot {
}
export class ArkComponentRootStyle implements ComponentRoot {
}
export class ArkRootComponent extends ComponentBase implements UIRoot {
    getPeer(): ArkRootPeer {
        return (this.peer as ArkRootPeer)
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkComponentRootComponent extends ComponentBase implements UIComponentRoot {
    getPeer(): ArkComponentRootPeer {
        return (this.peer as ArkComponentRootPeer)
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
