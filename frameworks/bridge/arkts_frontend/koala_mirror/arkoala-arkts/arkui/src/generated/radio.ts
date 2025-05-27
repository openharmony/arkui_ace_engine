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
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Callback_Boolean_Void } from "./navigation"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ResourceColor } from "./units"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRadioPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRadioPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Radio_construct(peerId, flags)
        const _peer  = new ArkRadioPeer(_peerPtr, peerId, "Radio", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRadioOptionsAttribute(options: RadioOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRadioOptions(options)
        ArkUIGeneratedNativeModule._RadioInterface_setRadioOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    checkedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._RadioAttribute_checked(this.peer.ptr, value ? 1 : 0)
    }
    onChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RadioAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radioStyleAttribute(value: RadioStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRadioStyle(value_value)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_radioStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
        ArkUIGeneratedNativeModule._RadioAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_checkedAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._RadioAttribute__onChangeEvent_checked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum RadioIndicatorType {
    TICK = 0,
    DOT = 1,
    CUSTOM = 2
}
export interface RadioOptions {
    group: string;
    value: string;
    indicatorType?: RadioIndicatorType;
    indicatorBuilder?: CustomBuilder;
}
export interface RadioStyle {
    checkedBackgroundColor?: ResourceColor;
    uncheckedBorderColor?: ResourceColor;
    indicatorColor?: ResourceColor;
}

export interface RadioAttribute extends CommonMethod {
    checked(value: boolean): this
    onChange(value: ((isVisible: boolean) => void)): this
    radioStyle(value: RadioStyle | undefined): this
    contentModifier(value: ContentModifier): this
    _onChangeEvent_checked(callback: ((isVisible: boolean) => void)): void
    attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIRadioAttribute extends UICommonMethod {
    /** @memo */
    checked(value: boolean): this
    /** @memo */
    onChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    radioStyle(value: RadioStyle | undefined): this
    /** @memo */
    contentModifier(value: ContentModifier): this
    /** @memo */
    _onChangeEvent_checked(callback: ((isVisible: boolean) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkRadioStyle extends ArkCommonMethodStyle implements RadioAttribute {
    checked_value?: boolean
    onChange_value?: ((isVisible: boolean) => void)
    radioStyle_value?: RadioStyle
    contentModifier_value?: ContentModifier
    public checked(value: boolean): this {
        return this
    }
    public onChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public radioStyle(value: RadioStyle | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public _onChangeEvent_checked(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface RadioConfiguration extends CommonConfiguration {
    value: string;
    checked: boolean;
    triggerChange: ((isVisible: boolean) => void);
}
/** @memo:stable */
export class ArkRadioComponent extends ArkCommonMethodComponent implements UIRadioAttribute {
    getPeer(): ArkRadioPeer {
        return (this.peer as ArkRadioPeer)
    }
    /** @memo */
    public setRadioOptions(options: RadioOptions): this {
        if (this.checkPriority("setRadioOptions")) {
            const options_casted = options as (RadioOptions)
            this.getPeer()?.setRadioOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public checked(value: boolean): this {
        if (this.checkPriority("checked")) {
            const value_casted = value as (boolean)
            this.getPeer()?.checkedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public radioStyle(value: RadioStyle | undefined): this {
        if (this.checkPriority("radioStyle")) {
            const value_casted = value as (RadioStyle | undefined)
            this.getPeer()?.radioStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentModifier(value: ContentModifier): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_checked(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_checked")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_checkedAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkRadio(
    /** @memo */
    style: ((attributes: UIRadioAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options: RadioOptions,
): void {
    const receiver = remember(() => {
        return new ArkRadioComponent()
    })
    NodeAttach<ArkRadioPeer>((): ArkRadioPeer => ArkRadioPeer.create(receiver), (_: ArkRadioPeer) => {
        receiver.setRadioOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
