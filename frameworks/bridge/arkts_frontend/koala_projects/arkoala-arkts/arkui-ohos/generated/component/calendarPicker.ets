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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, Callback as arkui_component_common_Callback, DateRange, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, PickerDialogButtonStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, DateRange_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, PickerDialogButtonStyle_serializer, ShadowOptions_serializer } from './common'
import { Offset_serializer, Offset, Length, Resource as arkui_component_units_Resource, VoidCallback, ResourceColor } from './units'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { AttributeModifier, hookCalendarPickerAttributeModifier, AttributeUpdater } from '#handwritten'
import { Resource as global_resource_Resource } from 'global.resource'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Color as arkui_component_enums_Color } from './enums'
import { CalendarPickerModifier } from './../CalendarPickerModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class CalendarPickerDialogInternal {
    public static fromPtr(ptr: KPointer): CalendarPickerDialog {
        return new CalendarPickerDialog(MaterializedBaseTag.NOP, ptr)
    }
}
export class CalendarPickerDialog implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CalendarPickerDialog.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, CalendarPickerDialog.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CalendarPickerDialog_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CalendarPickerDialog_getFinalizer()
    }
    public static show(options?: CalendarDialogOptions): void {
        const options_casted = options as (CalendarDialogOptions | undefined)
        CalendarPickerDialog.show_serialize(options_casted)
        return
    }
    private static show_serialize(options?: CalendarDialogOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            CalendarDialogOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CalendarPickerDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkCalendarPickerPeer extends ArkCommonMethodPeer {
    attributeSet?: CalendarPickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCalendarPickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CalendarPicker_construct(peerId, flags)
        const _peer  = new ArkCalendarPickerPeer(_peerPtr, peerId, 'CalendarPicker', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCalendarPickerOptionsAttribute(options?: CalendarOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            CalendarOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CalendarPickerInterface_setCalendarPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: arkui_component_common_Callback<Date, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarkTodayAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_setMarkToday(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeAlignAttribute(alignType: CalendarAlign | undefined, offset?: Offset): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (alignType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignTypeTmpValue  = (alignType as CalendarAlign)
            thisSerializer.writeInt32(alignTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (offset !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const offsetTmpValue  = offset!
            Offset_serializer.write(thisSerializer, offsetTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_setEdgeAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum CalendarAlign {
    START = 0,
    CENTER = 1,
    END = 2
}
export interface CalendarOptions {
    hintRadius?: double | global_resource_Resource;
    selected?: Date;
    start?: Date;
    end?: Date;
    disabledDateRange?: Array<DateRange>;
}
export interface CalendarPickerAttribute extends CommonMethod {
    setCalendarPickerOptions(options?: CalendarOptions): this {
        throw new Error('Unimplemented method setCalendarPickerOptions')
    }
    textStyle(value: PickerTextStyle | undefined): this {
        throw new Error('Unimplemented method textStyle')
    }
    onChange(value: arkui_component_common_Callback<Date, void> | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    markToday(value: boolean | undefined): this {
        throw new Error('Unimplemented method markToday')
    }
    edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        throw new Error('Unimplemented method edgeAlign')
    }
    attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface CalendarDialogOptions extends CalendarOptions {
    onAccept?: arkui_component_common_Callback<Date, void>;
    onCancel?: VoidCallback;
    onChange?: arkui_component_common_Callback<Date, void>;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    markToday?: boolean;
}

export class ArkCalendarPickerComponent extends ArkCommonMethodComponent implements CalendarPickerAttribute {
    getPeer(): ArkCalendarPickerPeer {
        return (this.peer as ArkCalendarPickerPeer)
    }
    public setCalendarPickerOptions(options?: CalendarOptions): this {
        if (this.checkPriority('setCalendarPickerOptions')) {
            const options_casted = options as (CalendarOptions | undefined)
            this.getPeer()?.setCalendarPickerOptionsAttribute(options_casted)
            this.applyOptionsFinish('CalendarPickerAttribute');
            return this
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority('textStyle')) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: arkui_component_common_Callback<Date, void> | undefined): this {
        if (this.checkPriority('onChange')) {
            const value_casted = value as (arkui_component_common_Callback<Date, void> | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public markToday(value: boolean | undefined): this {
        if (this.checkPriority('markToday')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMarkTodayAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        if (this.checkPriority('edgeAlign')) {
            const alignType_casted = alignType as (CalendarAlign | undefined)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.setEdgeAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookCalendarPickerAttributeModifier(this, value);
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
export function CalendarPickerImpl(
    @memo @memo_skip
    style: ((attributes: CalendarPickerAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkCalendarPickerComponent>((): ArkCalendarPickerComponent => {
        return new ArkCalendarPickerComponent()
    })
    NodeAttach<ArkCalendarPickerPeer>((): ArkCalendarPickerPeer => ArkCalendarPickerPeer.create(receiver), (_: ArkCalendarPickerPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class CalendarPickerDialog_serializer {
    public static write(buffer: SerializerBase, value: CalendarPickerDialog): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CalendarPickerDialog {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CalendarPickerDialogInternal.fromPtr(ptr)
    }
}
export class CalendarOptions_serializer {
    public static write(buffer: SerializerBase, value: CalendarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHintRadius  = value.hintRadius
        if (valueHolderForHintRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHintRadiusTmpValue  = valueHolderForHintRadius!
            if (valueHolderForHintRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHintRadiusTmpValueForIdx0  = valueHolderForHintRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHintRadiusTmpValueForIdx0)
            } else if (valueHolderForHintRadiusTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHintRadiusTmpValueForIdx1  = valueHolderForHintRadiusTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForHintRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            valueSerializer.writeInt64(valueHolderForSelectedTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDisabledDateRange  = value.disabledDateRange
        if (valueHolderForDisabledDateRange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDisabledDateRangeTmpValue  = valueHolderForDisabledDateRange!
            valueSerializer.writeInt32((valueHolderForDisabledDateRangeTmpValue.length).toInt())
            for (let valueHolderForDisabledDateRangeTmpValueCounterI = 0; valueHolderForDisabledDateRangeTmpValueCounterI < valueHolderForDisabledDateRangeTmpValue.length; valueHolderForDisabledDateRangeTmpValueCounterI++) {
                const valueHolderForDisabledDateRangeTmpValueTmpElement : DateRange = valueHolderForDisabledDateRangeTmpValue[valueHolderForDisabledDateRangeTmpValueCounterI]
                DateRange_serializer.write(valueSerializer, valueHolderForDisabledDateRangeTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CalendarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const hintRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hintRadiusTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((hintRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const hintRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let hintRadiusTmpBufOpt : double | global_resource_Resource | undefined
            if (hintRadiusTmpBufOptUnionSelector == (0).toByte()) {
                hintRadiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (hintRadiusTmpBufOptUnionSelector == (1).toByte()) {
                hintRadiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for hintRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            hintRadiusTmpBuf = (hintRadiusTmpBufOpt as double | global_resource_Resource)
        }
        const hintRadiusTmpResult : double | global_resource_Resource | undefined = hintRadiusTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTmpBuf : Date | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const selectedTmpResult : Date | undefined = selectedTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : Date | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const disabledDateRangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let disabledDateRangeTmpBuf : Array<DateRange> | undefined = undefined
        if ((disabledDateRangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const disabledDateRangeTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let disabledDateRangeTmpBufOpt : Array<DateRange> = new Array<DateRange>(disabledDateRangeTmpBufOptLength)
            for (let disabledDateRangeTmpBufOptBufCounterI = 0; disabledDateRangeTmpBufOptBufCounterI < disabledDateRangeTmpBufOptLength; disabledDateRangeTmpBufOptBufCounterI++) {
                disabledDateRangeTmpBufOpt[disabledDateRangeTmpBufOptBufCounterI] = DateRange_serializer.read(valueDeserializer)
            }
            disabledDateRangeTmpBuf = disabledDateRangeTmpBufOpt
        }
        const disabledDateRangeTmpResult : Array<DateRange> | undefined = disabledDateRangeTmpBuf
        let value : CalendarOptions = ({hintRadius: hintRadiusTmpResult, selected: selectedTmpResult, start: startTmpResult, end: endTmpResult, disabledDateRange: disabledDateRangeTmpResult} as CalendarOptions)
        return value
    }
}
export class CalendarDialogOptions_serializer {
    public static write(buffer: SerializerBase, value: CalendarDialogOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHintRadius  = value.hintRadius
        if (valueHolderForHintRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHintRadiusTmpValue  = valueHolderForHintRadius!
            if (valueHolderForHintRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHintRadiusTmpValueForIdx0  = valueHolderForHintRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHintRadiusTmpValueForIdx0)
            } else if (valueHolderForHintRadiusTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHintRadiusTmpValueForIdx1  = valueHolderForHintRadiusTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForHintRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            valueSerializer.writeInt64(valueHolderForSelectedTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDisabledDateRange  = value.disabledDateRange
        if (valueHolderForDisabledDateRange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDisabledDateRangeTmpValue  = valueHolderForDisabledDateRange!
            valueSerializer.writeInt32((valueHolderForDisabledDateRangeTmpValue.length).toInt())
            for (let valueHolderForDisabledDateRangeTmpValueCounterI = 0; valueHolderForDisabledDateRangeTmpValueCounterI < valueHolderForDisabledDateRangeTmpValue.length; valueHolderForDisabledDateRangeTmpValueCounterI++) {
                const valueHolderForDisabledDateRangeTmpValueTmpElement : DateRange = valueHolderForDisabledDateRangeTmpValue[valueHolderForDisabledDateRangeTmpValueCounterI]
                DateRange_serializer.write(valueSerializer, valueHolderForDisabledDateRangeTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnAccept  = value.onAccept
        if (valueHolderForOnAccept !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnAcceptTmpValue  = valueHolderForOnAccept!
            valueSerializer.holdAndWriteCallback(valueHolderForOnAcceptTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnCancel  = value.onCancel
        if (valueHolderForOnCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnCancelTmpValue  = valueHolderForOnCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForOnCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnChange  = value.onChange
        if (valueHolderForOnChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnChangeTmpValue  = valueHolderForOnChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAcceptButtonStyle  = value.acceptButtonStyle
        if (valueHolderForAcceptButtonStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAcceptButtonStyleTmpValue  = valueHolderForAcceptButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, valueHolderForAcceptButtonStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCancelButtonStyle  = value.cancelButtonStyle
        if (valueHolderForCancelButtonStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelButtonStyleTmpValue  = valueHolderForCancelButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, valueHolderForCancelButtonStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear  = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue  = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear  = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue  = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear  = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue  = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear  = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue  = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea  = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue  = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMarkToday  = value.markToday
        if (valueHolderForMarkToday !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarkTodayTmpValue  = valueHolderForMarkToday!
            valueSerializer.writeBoolean(valueHolderForMarkTodayTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CalendarDialogOptions {
        let valueDeserializer : DeserializerBase = buffer
        const hintRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hintRadiusTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((hintRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const hintRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let hintRadiusTmpBufOpt : double | global_resource_Resource | undefined
            if (hintRadiusTmpBufOptUnionSelector == (0).toByte()) {
                hintRadiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (hintRadiusTmpBufOptUnionSelector == (1).toByte()) {
                hintRadiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for hintRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            hintRadiusTmpBuf = (hintRadiusTmpBufOpt as double | global_resource_Resource)
        }
        const hintRadiusTmpResult : double | global_resource_Resource | undefined = hintRadiusTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTmpBuf : Date | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const selectedTmpResult : Date | undefined = selectedTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : Date | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const disabledDateRangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let disabledDateRangeTmpBuf : Array<DateRange> | undefined = undefined
        if ((disabledDateRangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const disabledDateRangeTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let disabledDateRangeTmpBufOpt : Array<DateRange> = new Array<DateRange>(disabledDateRangeTmpBufOptLength)
            for (let disabledDateRangeTmpBufOptBufCounterI = 0; disabledDateRangeTmpBufOptBufCounterI < disabledDateRangeTmpBufOptLength; disabledDateRangeTmpBufOptBufCounterI++) {
                disabledDateRangeTmpBufOpt[disabledDateRangeTmpBufOptBufCounterI] = DateRange_serializer.read(valueDeserializer)
            }
            disabledDateRangeTmpBuf = disabledDateRangeTmpBufOpt
        }
        const disabledDateRangeTmpResult : Array<DateRange> | undefined = disabledDateRangeTmpBuf
        const onAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onAcceptTmpBuf : arkui_component_common_Callback<Date, void> | undefined = undefined
        if ((onAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAcceptTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAcceptTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBufOptClosure  = (data: Date):void => {
                const onAcceptTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAcceptTmpBufOptBufArgsSerializer.writeInt32(onAcceptTmpBufOptBufResource.resourceId);
                onAcceptTmpBufOptBufArgsSerializer.writePointer(onAcceptTmpBufOptBufCall);
                onAcceptTmpBufOptBufArgsSerializer.writePointer(onAcceptTmpBufOptBufCallSync);
                onAcceptTmpBufOptBufArgsSerializer.writeInt64(data.getTime()!.toLong());
                InteropNativeModule._CallCallbackSync(10, -1865664613, onAcceptTmpBufOptBufArgsSerializer.asBuffer(), onAcceptTmpBufOptBufArgsSerializer.length());
                onAcceptTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onAcceptTmpBufOptClosure, onAcceptTmpBufOptBufResource)
            onAcceptTmpBuf = onAcceptTmpBufOptClosure
        }
        const onAcceptTmpResult : arkui_component_common_Callback<Date, void> | undefined = onAcceptTmpBuf
        const onCancelTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onCancelTmpBuf : VoidCallback | undefined = undefined
        if ((onCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCancelTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancelTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBufOptClosure  = ():void => {
                const onCancelTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onCancelTmpBufOptBufArgsSerializer.writeInt32(onCancelTmpBufOptBufResource.resourceId);
                onCancelTmpBufOptBufArgsSerializer.writePointer(onCancelTmpBufOptBufCall);
                onCancelTmpBufOptBufArgsSerializer.writePointer(onCancelTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onCancelTmpBufOptBufArgsSerializer.asBuffer(), onCancelTmpBufOptBufArgsSerializer.length());
                onCancelTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onCancelTmpBufOptClosure, onCancelTmpBufOptBufResource)
            onCancelTmpBuf = onCancelTmpBufOptClosure
        }
        const onCancelTmpResult : VoidCallback | undefined = onCancelTmpBuf
        const onChangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onChangeTmpBuf : arkui_component_common_Callback<Date, void> | undefined = undefined
        if ((onChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onChangeTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChangeTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBufOptClosure  = (data: Date):void => {
                const onChangeTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onChangeTmpBufOptBufArgsSerializer.writeInt32(onChangeTmpBufOptBufResource.resourceId);
                onChangeTmpBufOptBufArgsSerializer.writePointer(onChangeTmpBufOptBufCall);
                onChangeTmpBufOptBufArgsSerializer.writePointer(onChangeTmpBufOptBufCallSync);
                onChangeTmpBufOptBufArgsSerializer.writeInt64(data.getTime()!.toLong());
                InteropNativeModule._CallCallbackSync(10, -1865664613, onChangeTmpBufOptBufArgsSerializer.asBuffer(), onChangeTmpBufOptBufArgsSerializer.length());
                onChangeTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onChangeTmpBufOptClosure, onChangeTmpBufOptBufResource)
            onChangeTmpBuf = onChangeTmpBufOptClosure
        }
        const onChangeTmpResult : arkui_component_common_Callback<Date, void> | undefined = onChangeTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (backgroundColorTmpBufOptUnionSelector == (0).toByte()) {
                backgroundColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBufOptUnionSelector == (1).toByte()) {
                backgroundColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (backgroundColorTmpBufOptUnionSelector == (2).toByte()) {
                backgroundColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBufOptUnionSelector == (3).toByte()) {
                backgroundColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for backgroundColorTmpBufOpt has to be chosen through deserialisation.')
            }
            backgroundColorTmpBuf = (backgroundColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const acceptButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let acceptButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((acceptButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            acceptButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyleTmpResult : PickerDialogButtonStyle | undefined = acceptButtonStyleTmpBuf
        const cancelButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let cancelButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((cancelButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            cancelButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyleTmpResult : PickerDialogButtonStyle | undefined = cancelButtonStyleTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDidAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptClosure  = ():void => {
                const onDidAppearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBufOptBufArgsSerializer.writeInt32(onDidAppearTmpBufOptBufResource.resourceId);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCall);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onDidAppearTmpBufOptBufArgsSerializer.asBuffer(), onDidAppearTmpBufOptBufArgsSerializer.length());
                onDidAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidAppearTmpBufOptClosure, onDidAppearTmpBufOptBufResource)
            onDidAppearTmpBuf = onDidAppearTmpBufOptClosure
        }
        const onDidAppearTmpResult : VoidCallback | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDidDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptClosure  = ():void => {
                const onDidDisappearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBufOptBufArgsSerializer.writeInt32(onDidDisappearTmpBufOptBufResource.resourceId);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCall);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onDidDisappearTmpBufOptBufArgsSerializer.asBuffer(), onDidDisappearTmpBufOptBufArgsSerializer.length());
                onDidDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidDisappearTmpBufOptClosure, onDidDisappearTmpBufOptBufResource)
            onDidDisappearTmpBuf = onDidDisappearTmpBufOptClosure
        }
        const onDidDisappearTmpResult : VoidCallback | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onWillAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptClosure  = ():void => {
                const onWillAppearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBufOptBufArgsSerializer.writeInt32(onWillAppearTmpBufOptBufResource.resourceId);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCall);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onWillAppearTmpBufOptBufArgsSerializer.asBuffer(), onWillAppearTmpBufOptBufArgsSerializer.length());
                onWillAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillAppearTmpBufOptClosure, onWillAppearTmpBufOptBufResource)
            onWillAppearTmpBuf = onWillAppearTmpBufOptClosure
        }
        const onWillAppearTmpResult : VoidCallback | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onWillDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptClosure  = ():void => {
                const onWillDisappearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBufOptBufArgsSerializer.writeInt32(onWillDisappearTmpBufOptBufResource.resourceId);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCall);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onWillDisappearTmpBufOptBufArgsSerializer.asBuffer(), onWillDisappearTmpBufOptBufArgsSerializer.length());
                onWillDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillDisappearTmpBufOptClosure, onWillDisappearTmpBufOptBufResource)
            onWillDisappearTmpBuf = onWillDisappearTmpBufOptClosure
        }
        const onWillDisappearTmpResult : VoidCallback | undefined = onWillDisappearTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBufOpt : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBufOptUnionSelector == (0).toByte()) {
                shadowTmpBufOpt = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBufOptUnionSelector == (1).toByte()) {
                shadowTmpBufOpt = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for shadowTmpBufOpt has to be chosen through deserialisation.')
            }
            shadowTmpBuf = (shadowTmpBufOpt as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const markTodayTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let markTodayTmpBuf : boolean | undefined = undefined
        if ((markTodayTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            markTodayTmpBuf = valueDeserializer.readBoolean()
        }
        const markTodayTmpResult : boolean | undefined = markTodayTmpBuf
        let value : CalendarDialogOptions = ({hintRadius: hintRadiusTmpResult, selected: selectedTmpResult, start: startTmpResult, end: endTmpResult, disabledDateRange: disabledDateRangeTmpResult, onAccept: onAcceptTmpResult, onCancel: onCancelTmpResult, onChange: onChangeTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, markToday: markTodayTmpResult} as CalendarDialogOptions)
        return value
    }
}
