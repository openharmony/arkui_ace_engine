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

export class ArkRichTextPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRichTextPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichText_construct(peerId, flags)
        const _peer  = new ArkRichTextPeer(_peerPtr, peerId, "RichText", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichTextOptionsAttribute(content: string): void {
        ArkUIGeneratedNativeModule._RichTextInterface_setRichTextOptions(this.peer.ptr, content)
    }
    onStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichTextAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCompleteAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichTextAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type RichTextInterface = (content: string) => RichTextAttribute;
export interface RichTextAttribute extends CommonMethod {
    onStart(value: (() => void) | undefined): this
    onComplete(value: (() => void) | undefined): this
}
export class ArkRichTextStyle extends ArkCommonMethodStyle implements RichTextAttribute {
    onStart_value?: (() => void) | undefined
    onComplete_value?: (() => void) | undefined
    public onStart(value: (() => void) | undefined): this {
        return this
    }
    public onComplete(value: (() => void) | undefined): this {
        return this
        }
}
export class ArkRichTextComponent extends ArkCommonMethodComponent implements RichTextAttribute {
    getPeer(): ArkRichTextPeer {
        return (this.peer as ArkRichTextPeer)
    }
    public setRichTextOptions(content: string): this {
        if (this.checkPriority("setRichTextOptions")) {
            const content_casted = content as (string)
            this.getPeer()?.setRichTextOptionsAttribute(content_casted)
            return this
        }
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: (() => void) | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onCompleteAttribute(value_casted)
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
export function RichText(
    /** @memo */
    style: ((attributes: RichTextAttribute) => void) | undefined,
    content: string,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRichTextComponent()
    })
    NodeAttach<ArkRichTextPeer>((): ArkRichTextPeer => ArkRichTextPeer.create(receiver), (_: ArkRichTextPeer) => {
        receiver.setRichTextOptions(content)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
