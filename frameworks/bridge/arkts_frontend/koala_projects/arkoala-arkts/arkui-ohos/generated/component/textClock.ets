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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { global_resource_Resource_serializer } from './../framework/resource'
import { ShadowOptions_serializer, ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, ShadowOptions, DateTimeOptions, CommonConfiguration, ArkCommonMethodComponent } from './common'
import { intl_DateTimeOptions_serializer } from './../framework/ohos.intl'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource, ResourceColor, Length } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { Color as arkui_component_enums_Color, FontStyle, FontWeight } from './enums'
import { ContentModifier, AttributeModifier, hookTextClockContentModifier, hookTextClockAttributeModifier, AttributeUpdater } from '#handwritten'
import { default as intl } from '@ohos.intl'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { TextClockModifier } from './../TextClockModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class TextClockControllerInternal {
    public static fromPtr(ptr: KPointer): TextClockController {
        return new TextClockController(MaterializedBaseTag.NOP, ptr)
    }
}
export class TextClockController implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextClockController.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TextClockController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextClockController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextClockController_getFinalizer()
    }
    public start(): void {
        this.start_serialize()
        return
    }
    public stop(): void {
        this.stop_serialize()
        return
    }
    private start_serialize(): void {
        ArkUIGeneratedNativeModule._TextClockController_start(this.peer!.ptr)
    }
    private stop_serialize(): void {
        ArkUIGeneratedNativeModule._TextClockController_stop(this.peer!.ptr)
    }
}
export class ArkTextClockPeer extends ArkCommonMethodPeer {
    attributeSet?: TextClockModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextClockPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextClock_construct(peerId, flags)
        const _peer  = new ArkTextClockPeer(_peerPtr, peerId, 'TextClock', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextClockOptionsAttribute(options?: TextClockOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            TextClockOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockInterface_setTextClockOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFormatAttribute(value: arkui_component_units_ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDateChangeAttribute(value: arkui_component_common_Callback<int64, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setOnDateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FontStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as FontWeight
                thisSerializer.writeInt32(valueTmpValueForIdx1.valueOf())
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: arkui_component_units_ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ShadowOptions) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ShadowOptions
                ShadowOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Array) {
                if (valueTmpValue.length == 0) {
                    thisSerializer.writeInt8((1).toByte())
                    thisSerializer.writeInt32(0)
                } else {
                    const valueTmpValueElem  = valueTmpValue[0]
                    if (valueTmpValueElem instanceof ShadowOptions) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueForIdx1  = valueTmpValue as Array<ShadowOptions>
                        thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                        for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                            const valueTmpValueForIdx1TmpElement : ShadowOptions = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                            ShadowOptions_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement)
                        }
                    }
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setFontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDateTimeOptionsAttribute(value: DateTimeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            intl_DateTimeOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextClockAttribute_setDateTimeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextClockConfiguration extends CommonConfiguration<TextClockConfiguration> {
    timeZoneOffset: double;
    started: boolean;
    timeValue: int64;
}
export interface TextClockOptions {
    timeZoneOffset?: double;
    controller?: TextClockController;
}
export interface TextClockAttribute extends CommonMethod {
    setTextClockOptions(options?: TextClockOptions): this {
        throw new Error('Unimplemented method setTextClockOptions')
    }
    format(value: arkui_component_units_ResourceStr | undefined): this {
        throw new Error('Unimplemented method format')
    }
    onDateChange(value: arkui_component_common_Callback<int64, void> | undefined): this {
        throw new Error('Unimplemented method onDateChange')
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method fontColor')
    }
    fontSize(value: Length | undefined): this {
        throw new Error('Unimplemented method fontSize')
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error('Unimplemented method fontStyle')
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        throw new Error('Unimplemented method fontWeight')
    }
    fontFamily(value: arkui_component_units_ResourceStr | undefined): this {
        throw new Error('Unimplemented method fontFamily')
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error('Unimplemented method textShadow')
    }
    fontFeature(value: string | undefined): this {
        throw new Error('Unimplemented method fontFeature')
    }
    contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    dateTimeOptions(value: DateTimeOptions | undefined): this {
        throw new Error('Unimplemented method dateTimeOptions')
    }
    attributeModifier(value: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkTextClockComponent extends ArkCommonMethodComponent implements TextClockAttribute {
    getPeer(): ArkTextClockPeer {
        return (this.peer as ArkTextClockPeer)
    }
    public setTextClockOptions(options?: TextClockOptions): this {
        if (this.checkPriority('setTextClockOptions')) {
            const options_casted = options as (TextClockOptions | undefined)
            this.getPeer()?.setTextClockOptionsAttribute(options_casted)
            this.applyOptionsFinish('TextClockAttribute');
            return this
        }
        return this
    }
    public format(value: arkui_component_units_ResourceStr | undefined): this {
        if (this.checkPriority('format')) {
            const value_casted = value as (arkui_component_units_ResourceStr | undefined)
            this.getPeer()?.setFormatAttribute(value_casted)
            return this
        }
        return this
    }
    public onDateChange(value: arkui_component_common_Callback<int64, void> | undefined): this {
        if (this.checkPriority('onDateChange')) {
            const value_casted = value as (arkui_component_common_Callback<int64, void> | undefined)
            this.getPeer()?.setOnDateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('fontColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority('fontSize')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority('fontStyle')) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (this.checkPriority('fontWeight')) {
            const value_casted = value as (int32 | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: arkui_component_units_ResourceStr | undefined): this {
        if (this.checkPriority('fontFamily')) {
            const value_casted = value as (arkui_component_units_ResourceStr | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (this.checkPriority('textShadow')) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
            this.getPeer()?.setTextShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority('fontFeature')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookTextClockContentModifier(this, value)
        }
        return this
    }
    public dateTimeOptions(value: DateTimeOptions | undefined): this {
        if (this.checkPriority('dateTimeOptions')) {
            const value_casted = value as (DateTimeOptions | undefined)
            this.getPeer()?.setDateTimeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextClockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookTextClockAttributeModifier(this, value);
        })
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
export function TextClockImpl(
    @memo @memo_skip
    style: ((attributes: TextClockAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkTextClockComponent>((): ArkTextClockComponent => {
        return new ArkTextClockComponent()
    })
    NodeAttach<ArkTextClockPeer>((): ArkTextClockPeer => ArkTextClockPeer.create(receiver), (_: ArkTextClockPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class TextClockConfiguration_serializer {
    public static write(buffer: SerializerBase, value: TextClockConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForTimeZoneOffset  = value.timeZoneOffset
        valueSerializer.writeFloat64(valueHolderForTimeZoneOffset)
        const valueHolderForStarted  = value.started
        valueSerializer.writeBoolean(valueHolderForStarted)
        const valueHolderForTimeValue  = value.timeValue
        valueSerializer.writeInt64(valueHolderForTimeValue)
    }
    public static read(buffer: DeserializerBase): TextClockConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<TextClockConfiguration> = (valueDeserializer.readObject() as ContentModifier<TextClockConfiguration>)
        const timeZoneOffsetTmpResult : double = valueDeserializer.readFloat64()
        const startedTmpResult : boolean = valueDeserializer.readBoolean()
        const timeValueTmpResult : int64 = valueDeserializer.readInt64()
        let value : TextClockConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, timeZoneOffset: timeZoneOffsetTmpResult, started: startedTmpResult, timeValue: timeValueTmpResult} as TextClockConfiguration)
        return value
    }
}
export class TextClockController_serializer {
    public static write(buffer: SerializerBase, value: TextClockController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextClockController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextClockControllerInternal.fromPtr(ptr)
    }
}
export class TextClockOptions_serializer {
    public static write(buffer: SerializerBase, value: TextClockOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTimeZoneOffset  = value.timeZoneOffset
        if (valueHolderForTimeZoneOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeZoneOffsetTmpValue  = valueHolderForTimeZoneOffset!
            valueSerializer.writeFloat64(valueHolderForTimeZoneOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForController  = value.controller
        if (valueHolderForController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControllerTmpValue  = valueHolderForController!
            TextClockController_serializer.write(valueSerializer, valueHolderForControllerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextClockOptions {
        let valueDeserializer : DeserializerBase = buffer
        const timeZoneOffsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let timeZoneOffsetTmpBuf : double | undefined = undefined
        if ((timeZoneOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeZoneOffsetTmpBuf = valueDeserializer.readFloat64()
        }
        const timeZoneOffsetTmpResult : double | undefined = timeZoneOffsetTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let controllerTmpBuf : TextClockController | undefined = undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (TextClockController_serializer.read(valueDeserializer) as TextClockController)
        }
        const controllerTmpResult : TextClockController | undefined = controllerTmpBuf
        let value : TextClockOptions = ({timeZoneOffset: timeZoneOffsetTmpResult, controller: controllerTmpResult} as TextClockOptions)
        return value
    }
}
