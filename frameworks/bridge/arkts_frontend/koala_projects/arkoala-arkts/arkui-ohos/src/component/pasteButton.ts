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
import { ArkSecurityComponentMethodPeer, SecurityComponentMethod, ArkSecurityComponentMethodComponent, ArkSecurityComponentMethodStyle } from "./securityComponent"
import { ClickEvent } from "./common"
import { BusinessError } from "#external"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ButtonType } from "./button"

export class ArkPasteButtonPeer extends ArkSecurityComponentMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkPasteButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._PasteButton_construct(peerId, flags)
        const _peer  = new ArkPasteButtonPeer(_peerPtr, peerId, "PasteButton", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPasteButtonOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._PasteButtonInterface_setPasteButtonOptions0(this.peer.ptr)
    }
    setPasteButtonOptions1Attribute(options: PasteButtonOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePasteButtonOptions(options)
        ArkUIGeneratedNativeModule._PasteButtonInterface_setPasteButtonOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClickAttribute(value: PasteButtonCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PasteButtonAttribute_onClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum PasteIconStyle {
    LINES = 0
}
export enum PasteDescription {
    PASTE = 0
}
export interface PasteButtonOptions {
    icon?: PasteIconStyle;
    text?: PasteDescription;
    buttonType?: ButtonType;
}
export enum PasteButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export type PasteButtonCallback = (event: ClickEvent, result: PasteButtonOnClickResult, error?: BusinessError<void>) => void;
export interface PasteButtonAttribute extends SecurityComponentMethod {
    onClick(value: PasteButtonCallback | undefined): this
}
export class ArkPasteButtonStyle extends ArkSecurityComponentMethodStyle implements PasteButtonAttribute {
    onClick_value?: PasteButtonCallback | undefined
    public onClick(value: PasteButtonCallback | undefined): this {
        return this
        }
}
export class ArkPasteButtonComponent extends ArkSecurityComponentMethodComponent implements PasteButtonAttribute {
    getPeer(): ArkPasteButtonPeer {
        return (this.peer as ArkPasteButtonPeer)
    }
    public setPasteButtonOptions(options?: PasteButtonOptions): this {
        if (options) {
            const options_type = runtimeType(options)
            this.getPeer()?.setPasteButtonOptions1Attribute(options as PasteButtonOptions)
            return this
        }
        this.getPeer()?.setPasteButtonOptions0Attribute()
        return this
    }
    public onClick(value: PasteButtonCallback | undefined): this {
        if (this.checkPriority("onClick")) {
            const value_casted = value as (PasteButtonCallback | undefined)
            this.getPeer()?.onClickAttribute(value_casted)
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
export function PasteButton(
    /** @memo */
    style: ((attributes: PasteButtonAttribute) => void) | undefined,
    options?: PasteButtonOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkPasteButtonComponent()
    })
    NodeAttach<ArkPasteButtonPeer>((): ArkPasteButtonPeer => ArkPasteButtonPeer.create(receiver), (_: ArkPasteButtonPeer) => {
        receiver.setPasteButtonOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
