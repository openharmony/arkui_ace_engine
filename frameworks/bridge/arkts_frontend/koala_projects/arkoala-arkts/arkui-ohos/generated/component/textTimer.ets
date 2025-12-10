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
import { ShadowOptions_serializer, ArkCommonMethodPeer, CommonMethod, ShadowOptions, CommonConfiguration, ArkCommonMethodComponent } from './common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ResourceColor, Resource as arkui_component_units_Resource, Length, ResourceStr as arkui_component_units_ResourceStr } from './units'
import { Color as arkui_component_enums_Color, FontStyle, FontWeight } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { ContentModifier, AttributeModifier, hookTextTimerContentModifier, hookTextTimerAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { TextTimerModifier } from './../TextTimerModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class TextTimerControllerInternal {
    public static fromPtr(ptr: KPointer): TextTimerController {
        return new TextTimerController(MaterializedBaseTag.NOP, ptr)
    }
}
export class TextTimerController implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextTimerController.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TextTimerController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextTimerController_getFinalizer()
    }
    public start(): void {
        this.start_serialize()
        return
    }
    public pause(): void {
        this.pause_serialize()
        return
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    private start_serialize(): void {
        ArkUIGeneratedNativeModule._TextTimerController_start(this.peer!.ptr)
    }
    private pause_serialize(): void {
        ArkUIGeneratedNativeModule._TextTimerController_pause(this.peer!.ptr)
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._TextTimerController_reset(this.peer!.ptr)
    }
}
export class ArkTextTimerPeer extends ArkCommonMethodPeer {
    attributeSet?: TextTimerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextTimerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextTimer_construct(peerId, flags)
        const _peer  = new ArkTextTimerPeer(_peerPtr, peerId, 'TextTimer', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextTimerOptionsAttribute(options?: TextTimerOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            TextTimerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextTimerInterface_setTextTimerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFormatAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFormat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | arkui_component_units_ResourceStr | undefined): void {
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
            } else if (valueTmpValue instanceof arkui_component_units_ResourceStr) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_ResourceStr
                if (valueTmpValueForIdx2 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx2ForIdx0  = valueTmpValueForIdx2 as string
                    thisSerializer.writeString(valueTmpValueForIdx2ForIdx0)
                } else if (valueTmpValueForIdx2 instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx2ForIdx1  = valueTmpValueForIdx2 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2ForIdx1)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTimerAttribute(value: TimerCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextTimerAttribute_setOnTimer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextTimerAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextTimerConfiguration extends CommonConfiguration<TextTimerConfiguration> {
    count: int64;
    isCountDown: boolean;
    started: boolean;
    elapsedTime: int64;
}
export interface TextTimerOptions {
    isCountDown?: boolean;
    count?: int64;
    controller?: TextTimerController;
}
export type TimerCallback = (utc: int64, elapsedTime: int64) => void;
export interface TextTimerAttribute extends CommonMethod {
    setTextTimerOptions(options?: TextTimerOptions): this {
        throw new Error('Unimplemented method setTextTimerOptions')
    }
    format(value: string | undefined): this {
        throw new Error('Unimplemented method format')
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
    fontWeight(value: int32 | FontWeight | arkui_component_units_ResourceStr | undefined): this {
        throw new Error('Unimplemented method fontWeight')
    }
    fontFamily(value: arkui_component_units_ResourceStr | undefined): this {
        throw new Error('Unimplemented method fontFamily')
    }
    onTimer(value: TimerCallback | undefined): this {
        throw new Error('Unimplemented method onTimer')
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error('Unimplemented method textShadow')
    }
    contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkTextTimerComponent extends ArkCommonMethodComponent implements TextTimerAttribute {
    getPeer(): ArkTextTimerPeer {
        return (this.peer as ArkTextTimerPeer)
    }
    public setTextTimerOptions(options?: TextTimerOptions): this {
        if (this.checkPriority('setTextTimerOptions')) {
            const options_casted = options as (TextTimerOptions | undefined)
            this.getPeer()?.setTextTimerOptionsAttribute(options_casted)
            this.applyOptionsFinish('TextTimerAttribute');
            return this
        }
        return this
    }
    public format(value: string | undefined): this {
        if (this.checkPriority('format')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFormatAttribute(value_casted)
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
    public fontWeight(value: int32 | FontWeight | arkui_component_units_ResourceStr | undefined): this {
        if (this.checkPriority('fontWeight')) {
            const value_casted = value as (int32 | FontWeight | arkui_component_units_ResourceStr | undefined)
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
    public onTimer(value: TimerCallback | undefined): this {
        if (this.checkPriority('onTimer')) {
            const value_casted = value as (TimerCallback | undefined)
            this.getPeer()?.setOnTimerAttribute(value_casted)
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
    public contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookTextTimerContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextTimerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookTextTimerAttributeModifier(this, value);
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
export function TextTimerImpl(
    @memo @memo_skip
    style: ((attributes: TextTimerAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkTextTimerComponent>((): ArkTextTimerComponent => {
        return new ArkTextTimerComponent()
    })
    NodeAttach<ArkTextTimerPeer>((): ArkTextTimerPeer => ArkTextTimerPeer.create(receiver), (_: ArkTextTimerPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class TextTimerConfiguration_serializer {
    public static write(buffer: SerializerBase, value: TextTimerConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForCount  = value.count
        valueSerializer.writeInt64(valueHolderForCount)
        const valueHolderForIsCountDown  = value.isCountDown
        valueSerializer.writeBoolean(valueHolderForIsCountDown)
        const valueHolderForStarted  = value.started
        valueSerializer.writeBoolean(valueHolderForStarted)
        const valueHolderForElapsedTime  = value.elapsedTime
        valueSerializer.writeInt64(valueHolderForElapsedTime)
    }
    public static read(buffer: DeserializerBase): TextTimerConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<TextTimerConfiguration> = (valueDeserializer.readObject() as ContentModifier<TextTimerConfiguration>)
        const countTmpResult : int64 = valueDeserializer.readInt64()
        const isCountDownTmpResult : boolean = valueDeserializer.readBoolean()
        const startedTmpResult : boolean = valueDeserializer.readBoolean()
        const elapsedTimeTmpResult : int64 = valueDeserializer.readInt64()
        let value : TextTimerConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, count: countTmpResult, isCountDown: isCountDownTmpResult, started: startedTmpResult, elapsedTime: elapsedTimeTmpResult} as TextTimerConfiguration)
        return value
    }
}
export class TextTimerController_serializer {
    public static write(buffer: SerializerBase, value: TextTimerController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextTimerController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextTimerControllerInternal.fromPtr(ptr)
    }
}
export class TextTimerOptions_serializer {
    public static write(buffer: SerializerBase, value: TextTimerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIsCountDown  = value.isCountDown
        if (valueHolderForIsCountDown !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsCountDownTmpValue  = valueHolderForIsCountDown!
            valueSerializer.writeBoolean(valueHolderForIsCountDownTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCount  = value.count
        if (valueHolderForCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCountTmpValue  = valueHolderForCount!
            valueSerializer.writeInt64(valueHolderForCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForController  = value.controller
        if (valueHolderForController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControllerTmpValue  = valueHolderForController!
            TextTimerController_serializer.write(valueSerializer, valueHolderForControllerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextTimerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const isCountDownTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let isCountDownTmpBuf : boolean | undefined = undefined
        if ((isCountDownTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isCountDownTmpBuf = valueDeserializer.readBoolean()
        }
        const isCountDownTmpResult : boolean | undefined = isCountDownTmpBuf
        const countTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let countTmpBuf : int64 | undefined = undefined
        if ((countTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            countTmpBuf = valueDeserializer.readInt64()
        }
        const countTmpResult : int64 | undefined = countTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let controllerTmpBuf : TextTimerController | undefined = undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (TextTimerController_serializer.read(valueDeserializer) as TextTimerController)
        }
        const controllerTmpResult : TextTimerController | undefined = controllerTmpBuf
        let value : TextTimerOptions = ({isCountDown: isCountDownTmpResult, count: countTmpResult, controller: controllerTmpResult} as TextTimerOptions)
        return value
    }
}
