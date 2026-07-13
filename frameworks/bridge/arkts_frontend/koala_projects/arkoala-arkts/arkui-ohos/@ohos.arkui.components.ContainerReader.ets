/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { CommonMethod, ArkCommonMethodPeer, ArkCommonMethodComponent, AttributeModifier, Bindable } from 'arkui/component/common';
import { Size } from 'arkui/Graphics';
import { int32 } from '@koalaui/common';
import { KPointer } from "@koalaui/interop"
import { ComponentBase } from 'arkui/ComponentBase';
import { PeerNode } from 'arkui/PeerNode';
import { ContainerReaderExtender } from 'arkui/component/idlize';
import { NodeAttach, remember } from "@koalaui/runtime"
import { WidthBreakpoint, HeightBreakpoint } from 'arkui/component/enums';


export interface ContainerReaderInfo {
  size: Bindable<Size>;
  widthBreakpoint?: Bindable<WidthBreakpoint>;
  heightBreakpoint?: Bindable<HeightBreakpoint>;
}
export interface BreakpointOptions {
  width?: Array<double>;
  height?: Array<double>;
}
export class ArkContainerReaderPeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkContainerReaderPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ContainerReaderExtender.containerReaderConstructor(peerId)
        const _peer = new ArkContainerReaderPeer(_peerPtr, peerId, "ContainerReader", flags)
        component?.setPeer(_peer)
        return _peer
    }

    setContainerReaderOptionsAttribute(options: ContainerReaderInfo | undefined): void {
        ContainerReaderExtender.setContainerReaderOptions(this.peer.ptr, 
            options?.size!.value!, options?.size!.onChange!, options?.widthBreakpoint, options?.heightBreakpoint);
    }


    setBreakpointConfigAttribute(value?: BreakpointOptions): void {
        if (value) {
           ContainerReaderExtender.breakpointConfig(this.peer.ptr, value!.width, value!.height);
        }
    }
}

export interface ContainerReaderAttribute extends CommonMethod {
    setContainerReaderOptions(options: ContainerReaderInfo | undefined): this {
        throw new Error("Unimplemented method setContainerReaderOptions")
    }
    breakpointConfig(value?: BreakpointOptions): this {
        throw new Error("Unimplemented method breakpointConfig")
    }
    attributeModifier(value: AttributeModifier<ContainerReaderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}

export class ArkContainerReaderComponent extends ArkCommonMethodComponent implements ContainerReaderAttribute {
    getPeer(): ArkContainerReaderPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkContainerReaderPeer)
    }

    public setContainerReaderOptions(options: ContainerReaderInfo | undefined): this {
        if (this.checkPriority("setContainerReaderOptions")) {
            const options_casted = options as (ContainerReaderInfo | undefined)
            this.getPeer()?.setContainerReaderOptionsAttribute(options_casted)
            this.applyOptionsFinish('ContainerReaderAttribute');
            return this
        }
        return this
    }

    public breakpointConfig(value?: BreakpointOptions): this {
        if (this.checkPriority("breakpointConfig")) {
            const value_casted = value as (BreakpointOptions | undefined)
            this.getPeer()?.setBreakpointConfigAttribute(value_casted)
            return this
        }
        return this
    }

    public attributeModifier(value: AttributeModifier<ContainerReaderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        // hookContainerReaderAttributeModifier(this, value);
        return this
    }

    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }

    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ContainerReaderImpl(
    @memo
    style: ((attributes: ContainerReaderAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkContainerReaderComponent>((): ArkContainerReaderComponent => {
        return new ArkContainerReaderComponent()
    })
    NodeAttach<ArkContainerReaderPeer>((): ArkContainerReaderPeer => ArkContainerReaderPeer.create(receiver), (peer: ArkContainerReaderPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}