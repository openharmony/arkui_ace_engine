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

export class ArkSaveButtonPeer extends ArkSecurityComponentMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSaveButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SaveButton_construct(peerId, flags)
        const _peer  = new ArkSaveButtonPeer(_peerPtr, peerId, "SaveButton", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSaveButtonOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._SaveButtonInterface_setSaveButtonOptions0(this.peer.ptr)
    }
    setSaveButtonOptions1Attribute(options: SaveButtonOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSaveButtonOptions(options)
        ArkUIGeneratedNativeModule._SaveButtonInterface_setSaveButtonOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onClickAttribute(value: SaveButtonCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_onClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SaveIconStyle {
    FULL_FILLED = 0,
    LINES = 1,
    PICTURE = 2
}
export enum SaveDescription {
    DOWNLOAD = 0,
    DOWNLOAD_FILE = 1,
    SAVE = 2,
    SAVE_IMAGE = 3,
    SAVE_FILE = 4,
    DOWNLOAD_AND_SHARE = 5,
    RECEIVE = 6,
    CONTINUE_TO_RECEIVE = 7,
    SAVE_TO_GALLERY = 8,
    EXPORT_TO_GALLERY = 9,
    QUICK_SAVE_TO_GALLERY = 10,
    RESAVE_TO_GALLERY = 11,
    SAVE_ALL = 12
}
export interface SaveButtonOptions {
    icon?: SaveIconStyle;
    text?: SaveDescription;
    buttonType?: ButtonType;
}
export enum SaveButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export type SaveButtonCallback = (event: ClickEvent, result: SaveButtonOnClickResult, error?: BusinessError<void>) => void;
export interface SaveButtonAttribute extends SecurityComponentMethod {
    onClick(value: SaveButtonCallback | undefined): this
}
export class ArkSaveButtonStyle extends ArkSecurityComponentMethodStyle implements SaveButtonAttribute {
    onClick_value?: SaveButtonCallback | undefined
    public onClick(value: SaveButtonCallback | undefined): this {
        return this
        }
}
export class ArkSaveButtonComponent extends ArkSecurityComponentMethodComponent implements SaveButtonAttribute {
    getPeer(): ArkSaveButtonPeer {
        return (this.peer as ArkSaveButtonPeer)
    }
    public setSaveButtonOptions(options?: SaveButtonOptions): this {
        if (options) {
            const options_type = runtimeType(options)
            this.getPeer()?.setSaveButtonOptions1Attribute(options as SaveButtonOptions)
            return this
        }
        this.getPeer()?.setSaveButtonOptions0Attribute()
        return this
    }
    public onClick(value: SaveButtonCallback | undefined): this {
        if (this.checkPriority("onClick")) {
            const value_casted = value as (SaveButtonCallback | undefined)
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
export function SaveButton(
    /** @memo */
    style: ((attributes: SaveButtonAttribute) => void) | undefined,
    options?: SaveButtonOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkSaveButtonComponent()
    })
    NodeAttach<ArkSaveButtonPeer>((): ArkSaveButtonPeer => ArkSaveButtonPeer.create(receiver), (_: ArkSaveButtonPeer) => {
        receiver.setSaveButtonOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
