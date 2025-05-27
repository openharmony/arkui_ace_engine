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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Alignment, FoldStatus, AppRotation } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { WindowStatusType } from "./arkui-external"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkFolderStackPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFolderStackPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FolderStack_construct(peerId, flags)
        const _peer  = new ArkFolderStackPeer(_peerPtr, peerId, "FolderStack", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFolderStackOptionsAttribute(options?: FolderStackOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeFolderStackOptions(options_value)
        }
        ArkUIGeneratedNativeModule._FolderStackInterface_setFolderStackOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignContentAttribute(value: Alignment): void {
        ArkUIGeneratedNativeModule._FolderStackAttribute_alignContent(this.peer.ptr, TypeChecker.Alignment_ToNumeric(value))
    }
    onFolderStateChangeAttribute(value: OnFoldStatusChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._FolderStackAttribute_onFolderStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHoverStatusChangeAttribute(value: OnHoverStatusChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._FolderStackAttribute_onHoverStatusChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnimationAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._FolderStackAttribute_enableAnimation(this.peer.ptr, value ? 1 : 0)
    }
    autoHalfFoldAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._FolderStackAttribute_autoHalfFold(this.peer.ptr, value ? 1 : 0)
    }
}
export interface FolderStackOptions {
    upperItems?: Array<string>;
}

export interface OnFoldStatusChangeInfo {
    foldStatus: FoldStatus;
}
export type OnFoldStatusChangeCallback = (event: OnFoldStatusChangeInfo) => void;
export type OnHoverStatusChangeCallback = (param: HoverEventParam) => void;
export interface FolderStackAttribute extends CommonMethod {
    alignContent(value: Alignment): this
    onFolderStateChange(value: OnFoldStatusChangeCallback): this
    onHoverStatusChange(value: OnHoverStatusChangeCallback): this
    enableAnimation(value: boolean): this
    autoHalfFold(value: boolean): this
    attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIFolderStackAttribute extends UICommonMethod {
    /** @memo */
    alignContent(value: Alignment): this
    /** @memo */
    onFolderStateChange(value: OnFoldStatusChangeCallback): this
    /** @memo */
    onHoverStatusChange(value: OnHoverStatusChangeCallback): this
    /** @memo */
    enableAnimation(value: boolean): this
    /** @memo */
    autoHalfFold(value: boolean): this
    /** @memo */
    attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkFolderStackStyle extends ArkCommonMethodStyle implements FolderStackAttribute {
    alignContent_value?: Alignment
    onFolderStateChange_value?: OnFoldStatusChangeCallback
    onHoverStatusChange_value?: OnHoverStatusChangeCallback
    enableAnimation_value?: boolean
    autoHalfFold_value?: boolean
    public alignContent(value: Alignment): this {
        return this
    }
    public onFolderStateChange(value: OnFoldStatusChangeCallback): this {
        return this
    }
    public onHoverStatusChange(value: OnHoverStatusChangeCallback): this {
        return this
    }
    public enableAnimation(value: boolean): this {
        return this
    }
    public autoHalfFold(value: boolean): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface HoverEventParam {
    foldStatus: FoldStatus;
    isHoverMode: boolean;
    appRotation: AppRotation;
    windowStatusType: WindowStatusType;
}
/** @memo:stable */
export class ArkFolderStackComponent extends ArkCommonMethodComponent implements UIFolderStackAttribute {
    getPeer(): ArkFolderStackPeer {
        return (this.peer as ArkFolderStackPeer)
    }
    /** @memo */
    public setFolderStackOptions(options?: FolderStackOptions): this {
        if (this.checkPriority("setFolderStackOptions")) {
            const options_casted = options as (FolderStackOptions | undefined)
            this.getPeer()?.setFolderStackOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignContent(value: Alignment): this {
        if (this.checkPriority("alignContent")) {
            const value_casted = value as (Alignment)
            this.getPeer()?.alignContentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFolderStateChange(value: OnFoldStatusChangeCallback): this {
        if (this.checkPriority("onFolderStateChange")) {
            const value_casted = value as (OnFoldStatusChangeCallback)
            this.getPeer()?.onFolderStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHoverStatusChange(value: OnHoverStatusChangeCallback): this {
        if (this.checkPriority("onHoverStatusChange")) {
            const value_casted = value as (OnHoverStatusChangeCallback)
            this.getPeer()?.onHoverStatusChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAnimation(value: boolean): this {
        if (this.checkPriority("enableAnimation")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoHalfFold(value: boolean): this {
        if (this.checkPriority("autoHalfFold")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoHalfFoldAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkFolderStack(
    /** @memo */
    style: ((attributes: UIFolderStackAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options?: FolderStackOptions,
): void {
    const receiver = remember(() => {
        return new ArkFolderStackComponent()
    })
    NodeAttach<ArkFolderStackPeer>((): ArkFolderStackPeer => ArkFolderStackPeer.create(receiver), (_: ArkFolderStackPeer) => {
        receiver.setFolderStackOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
