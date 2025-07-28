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
import { Callback_Boolean_Void } from "./navigation"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { ResourceColor } from "./units"
import { Color } from "./enums"
import { Resource } from "global/resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkTogglePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkTogglePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Toggle_construct(peerId, flags)
        const _peer  = new ArkTogglePeer(_peerPtr, peerId, "Toggle", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setToggleOptionsAttribute(options: ToggleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeToggleOptions(options)
        ArkUIGeneratedNativeModule._ToggleInterface_setToggleOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    switchPointColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_switchPointColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    switchStyleAttribute(value: SwitchStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSwitchStyle(value_value)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_switchStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_isOnAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._ToggleAttribute__onChangeEvent_isOn(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ToggleType {
    CHECKBOX = 0,
    Checkbox = 0,
    SWITCH = 1,
    Switch = 1,
    BUTTON = 2,
    Button = 2
}
export interface SwitchStyle {
    pointRadius?: number | Resource;
    unselectedColor?: ResourceColor;
    pointColor?: ResourceColor;
    trackBorderRadius?: number | Resource;
}
export interface ToggleConfiguration extends CommonConfiguration {
    isOn: boolean;
    enabled: boolean;
    triggerChange: ((isVisible: boolean) => void);
}
export interface ToggleOptions {
    type: ToggleType;
    isOn?: boolean;
}
export type ToggleInterface = (options: ToggleOptions) => ToggleAttribute;
export interface ToggleAttribute extends CommonMethod {
    onChange(value: ((isVisible: boolean) => void) | undefined): this
    contentModifier(value: ContentModifier | undefined): this
    selectedColor(value: ResourceColor | undefined): this
    switchPointColor(value: ResourceColor | undefined): this
    switchStyle(value: SwitchStyle | undefined): this
    _onChangeEvent_isOn(callback: ((isVisible: boolean) => void)): void
}
export class ArkToggleStyle extends ArkCommonMethodStyle implements ToggleAttribute {
    onChange_value?: ((isVisible: boolean) => void) | undefined
    contentModifier_value?: ContentModifier | undefined
    selectedColor_value?: ResourceColor | undefined
    switchPointColor_value?: ResourceColor | undefined
    switchStyle_value?: SwitchStyle | undefined
    public onChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public switchPointColor(value: ResourceColor | undefined): this {
        return this
    }
    public switchStyle(value: SwitchStyle | undefined): this {
        return this
    }
    public _onChangeEvent_isOn(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkToggleComponent extends ArkCommonMethodComponent implements ToggleAttribute {
    getPeer(): ArkTogglePeer {
        return (this.peer as ArkTogglePeer)
    }
    public setToggleOptions(options: ToggleOptions): this {
        if (this.checkPriority("setToggleOptions")) {
            const options_casted = options as (ToggleOptions)
            this.getPeer()?.setToggleOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public onChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchPointColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("switchPointColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.switchPointColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchStyle(value: SwitchStyle | undefined): this {
        if (this.checkPriority("switchStyle")) {
            const value_casted = value as (SwitchStyle | undefined)
            this.getPeer()?.switchStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_isOn(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_isOn")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_isOnAttribute(callback_casted)
            return
        }
        return
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Toggle(
    /** @memo */
    style: ((attributes: ToggleAttribute) => void) | undefined,
    options: ToggleOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkToggleComponent()
    })
    NodeAttach<ArkTogglePeer>((): ArkTogglePeer => ArkTogglePeer.create(receiver), (_: ArkTogglePeer) => {
        receiver.setToggleOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
