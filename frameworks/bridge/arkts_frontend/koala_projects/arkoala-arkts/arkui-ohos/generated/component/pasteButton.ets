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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkSecurityComponentMethodPeer, SecurityComponentMethod, ArkSecurityComponentMethodComponent, ArkSecurityComponentMethodStyle } from "./securityComponent"
import { ClickEvent } from "./common"
import { extractors, hookPasteButtonAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { BusinessError } from "@ohos.base"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ButtonType } from "./button"
import { PasteButtonModifier } from "./../PasteButtonModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkPasteButtonPeer extends ArkSecurityComponentMethodPeer {
    attributeSet?: PasteButtonModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPasteButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._PasteButton_construct(peerId, flags)
        const _peer  = new ArkPasteButtonPeer(_peerPtr, peerId, 'PasteButton', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPasteButtonOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._PasteButtonInterface_setPasteButtonOptions(this.peer.ptr)
    }
    setOnClickAttribute(value: PasteButtonCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._PasteButtonAttribute_setOnClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export type PasteButtonCallback = (event: ClickEvent, result: PasteButtonOnClickResult, error?: BusinessError) => void;
export interface PasteButtonAttribute extends SecurityComponentMethod {
    setPasteButtonOptions(): this {
        throw new Error("Unimplemented method setPasteButtonOptions")
    }
    onClick(value: PasteButtonCallback | undefined): this {
        throw new Error("Unimplemented method onClick")
    }
    attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkPasteButtonStyle extends ArkSecurityComponentMethodStyle implements PasteButtonAttribute {
    onClick_value?: PasteButtonCallback | undefined
    setPasteButtonOptions(): this {
        return this
    }
    onClick(value: PasteButtonCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkPasteButtonComponent extends ArkSecurityComponentMethodComponent implements PasteButtonAttribute {
    getPeer(): ArkPasteButtonPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkPasteButtonPeer)
    }
    public setPasteButtonOptions(): this {
        if (this.checkPriority("setPasteButtonOptions")) {
            this.getPeer()?.setPasteButtonOptionsAttribute()
            return this
        }
        return this
    }
    public onClick(value: PasteButtonCallback | undefined): this {
        if (this.checkPriority("onClick")) {
            const value_casted = value as (PasteButtonCallback | undefined)
            this.getPeer()?.setOnClickAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        hookPasteButtonAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function PasteButtonImpl(
    @memo
    style: ((attributes: PasteButtonAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPasteButtonComponent>((): ArkPasteButtonComponent => {
        return new ArkPasteButtonComponent()
    })
    NodeAttach<ArkPasteButtonPeer>((): ArkPasteButtonPeer => ArkPasteButtonPeer.create(receiver), (peer: ArkPasteButtonPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

