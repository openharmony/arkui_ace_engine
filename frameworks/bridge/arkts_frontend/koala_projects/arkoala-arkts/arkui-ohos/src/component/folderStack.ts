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
import { Alignment, FoldStatus, AppRotation } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { WindowStatusType } from "./arkui-external"

export class ArkFolderStackPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkFolderStackPeer {
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
    alignContentAttribute(value: Alignment | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_alignContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFolderStateChangeAttribute(value: OnFoldStatusChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_onFolderStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHoverStatusChangeAttribute(value: OnHoverStatusChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_onHoverStatusChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_enableAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoHalfFoldAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_autoHalfFold(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface FolderStackOptions {
    upperItems?: Array<string>;
}
export type FolderStackInterface = (options?: FolderStackOptions) => FolderStackAttribute;
export interface OnFoldStatusChangeInfo {
    foldStatus: FoldStatus;
}
export type OnFoldStatusChangeCallback = (event: OnFoldStatusChangeInfo) => void;
export type OnHoverStatusChangeCallback = (param: HoverEventParam) => void;
export interface FolderStackAttribute extends CommonMethod {
    alignContent(value: Alignment | undefined): this
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this
    enableAnimation(value: boolean | undefined): this
    autoHalfFold(value: boolean | undefined): this
}
export class ArkFolderStackStyle extends ArkCommonMethodStyle implements FolderStackAttribute {
    alignContent_value?: Alignment | undefined
    onFolderStateChange_value?: OnFoldStatusChangeCallback | undefined
    onHoverStatusChange_value?: OnHoverStatusChangeCallback | undefined
    enableAnimation_value?: boolean | undefined
    autoHalfFold_value?: boolean | undefined
    public alignContent(value: Alignment | undefined): this {
        return this
    }
    public onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        return this
    }
    public onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        return this
    }
    public enableAnimation(value: boolean | undefined): this {
        return this
    }
    public autoHalfFold(value: boolean | undefined): this {
        return this
        }
}
export interface HoverEventParam {
    foldStatus: FoldStatus;
    isHoverMode: boolean;
    appRotation: AppRotation;
    windowStatusType: WindowStatusType;
}
export class ArkFolderStackComponent extends ArkCommonMethodComponent implements FolderStackAttribute {
    getPeer(): ArkFolderStackPeer {
        return (this.peer as ArkFolderStackPeer)
    }
    public setFolderStackOptions(options?: FolderStackOptions): this {
        if (this.checkPriority("setFolderStackOptions")) {
            const options_casted = options as (FolderStackOptions | undefined)
            this.getPeer()?.setFolderStackOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public alignContent(value: Alignment | undefined): this {
        if (this.checkPriority("alignContent")) {
            const value_casted = value as (Alignment | undefined)
            this.getPeer()?.alignContentAttribute(value_casted)
            return this
        }
        return this
    }
    public onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        if (this.checkPriority("onFolderStateChange")) {
            const value_casted = value as (OnFoldStatusChangeCallback | undefined)
            this.getPeer()?.onFolderStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        if (this.checkPriority("onHoverStatusChange")) {
            const value_casted = value as (OnHoverStatusChangeCallback | undefined)
            this.getPeer()?.onHoverStatusChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnimation(value: boolean | undefined): this {
        if (this.checkPriority("enableAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public autoHalfFold(value: boolean | undefined): this {
        if (this.checkPriority("autoHalfFold")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.autoHalfFoldAttribute(value_casted)
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
export function FolderStack(
    /** @memo */
    style: ((attributes: FolderStackAttribute) => void) | undefined,
    options?: FolderStackOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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
