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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkFormLinkPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkFormLinkPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FormLink_construct(peerId, flags)
        const _peer  = new ArkFormLinkPeer(_peerPtr, peerId, "FormLink", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFormLinkOptionsAttribute(options: FormLinkOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFormLinkOptions(options)
        ArkUIGeneratedNativeModule._FormLinkInterface_setFormLinkOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface FormLinkOptions {
    action: string;
    moduleName?: string;
    bundleName?: string;
    abilityName?: string;
    uri?: string;
    params?: Object;
}
export type FormLinkInterface = (options: FormLinkOptions) => FormLinkAttribute;
export interface FormLinkAttribute extends CommonMethod {
}
export class ArkFormLinkStyle extends ArkCommonMethodStyle implements FormLinkAttribute {
}
export class ArkFormLinkComponent extends ArkCommonMethodComponent implements FormLinkAttribute {
    getPeer(): ArkFormLinkPeer {
        return (this.peer as ArkFormLinkPeer)
    }
    public setFormLinkOptions(options: FormLinkOptions): this {
        if (this.checkPriority("setFormLinkOptions")) {
            const options_casted = options as (FormLinkOptions)
            this.getPeer()?.setFormLinkOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function FormLink(
    /** @memo */
    style: ((attributes: FormLinkAttribute) => void) | undefined,
    options: FormLinkOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkFormLinkComponent()
    })
    NodeAttach<ArkFormLinkPeer>((): ArkFormLinkPeer => ArkFormLinkPeer.create(receiver), (_: ArkFormLinkPeer) => {
        receiver.setFormLinkOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
