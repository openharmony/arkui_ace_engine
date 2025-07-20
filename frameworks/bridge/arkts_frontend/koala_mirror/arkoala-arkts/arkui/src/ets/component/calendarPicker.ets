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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, DateRange, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, PickerDialogButtonStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet, DateRange_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, PickerDialogButtonStyle_serializer, ShadowOptions_serializer } from "./common"
import { Offset_serializer, Offset, Length, VoidCallback, ResourceColor } from "./units"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { Resource, Resource_serializer } from "./../generated/resource"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Color } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
export class CalendarPickerDialogInternal {
    public static fromPtr(ptr: KPointer): CalendarPickerDialog {
        return new CalendarPickerDialog(ptr)
    }
}
export class CalendarPickerDialog implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CalendarPickerDialog.getFinalizer())
    }
    constructor() {
        this(CalendarPickerDialog.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CalendarPickerDialog_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CalendarPickerDialog_getFinalizer()
    }
    private static show_serialize(options?: CalendarDialogOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            CalendarDialogOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static show(options?: CalendarDialogOptions): void {
        const options_casted = options as (CalendarDialogOptions | undefined)
        CalendarPickerDialog.show_serialize(options_casted)
        return
    }
}
export class ArkCalendarPickerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCalendarPickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CalendarPicker_construct(peerId, flags)
        const _peer  = new ArkCalendarPickerPeer(_peerPtr, peerId, "CalendarPicker", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCalendarPickerOptionsAttribute(options?: CalendarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            CalendarOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerInterface_setCalendarPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: Date) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarkTodayAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerAttribute_setMarkToday(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeAlignAttribute(alignType: CalendarAlign | undefined, offset?: Offset): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8((alignType_type).toChar())
        if ((alignType_type) != (RuntimeType.UNDEFINED)) {
            const alignType_value  = (alignType as CalendarAlign)
            thisSerializer.writeInt32(TypeChecker.CalendarAlign_ToNumeric(alignType_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8((offset_type).toChar())
        if ((offset_type) != (RuntimeType.UNDEFINED)) {
            const offset_value  = offset!
            Offset_serializer.write(thisSerializer, offset_value)
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
    hintRadius?: number | Resource;
    selected?: Date;
    start?: Date;
    end?: Date;
    disabledDateRange?: Array<DateRange>;
}
export interface CalendarPickerAttribute extends CommonMethod {
    textStyle(value: PickerTextStyle | undefined): this {
        throw new Error("Unimplemented method textStyle")
    }
    onChange(value: ((value0: Date) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    markToday(value: boolean | undefined): this {
        throw new Error("Unimplemented method markToday")
    }
    edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        throw new Error("Unimplemented method edgeAlign")
    }
    attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCalendarPickerStyle extends ArkCommonMethodStyle implements CalendarPickerAttribute {
    textStyle_value?: PickerTextStyle | undefined
    onChange_value?: ((value0: Date) => void) | undefined
    markToday_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined
    public textStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public onChange(value: ((value0: Date) => void) | undefined): this {
        return this
    }
    public markToday(value: boolean | undefined): this {
        return this
    }
    public edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: CalendarPickerAttribute): void {
        super.apply(target)
        if (this.textStyle_value !== undefined)
            target.textStyle(this.textStyle_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.markToday_value !== undefined)
            target.markToday(this.markToday_value!)
    }
}
export interface CalendarDialogOptions extends CalendarOptions {
    onAccept?: ((value0: Date) => void);
    onCancel?: VoidCallback;
    onChange?: ((value0: Date) => void);
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
        if (this.checkPriority("setCalendarPickerOptions")) {
            const options_casted = options as (CalendarOptions | undefined)
            this.getPeer()?.setCalendarPickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value0: Date) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: Date) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public markToday(value: boolean | undefined): this {
        if (this.checkPriority("markToday")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMarkTodayAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        if (this.checkPriority("edgeAlign")) {
            const alignType_casted = alignType as (CalendarAlign | undefined)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.setEdgeAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withCalendarPickerStyle(receiver: CalendarPickerAttribute, modifier: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkCalendarPickerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("CalendarPicker")
// export function CalendarPicker(
//     options?: CalendarOptions,
//     @memo
//     content_?: () => void,
// ): CalendarPickerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function CalendarPicker(
    @memo
    style: ((attributes: CalendarPickerAttribute) => void) | undefined,
    options?: CalendarOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCalendarPickerComponent>((): ArkCalendarPickerComponent => {
        return new ArkCalendarPickerComponent()
    })
    NodeAttach<ArkCalendarPickerPeer>((): ArkCalendarPickerPeer => ArkCalendarPickerPeer.create(receiver), (_: ArkCalendarPickerPeer): void => {
        receiver.setCalendarPickerOptions(options)
        style?.(receiver)
        withCalendarPickerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkCalendarPickerSet extends ArkCommonMethodSet implements CalendarPickerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _textStyle_flag?: boolean
    _textStyle0_value?: PickerTextStyle | undefined
    _onChange_flag?: boolean
    _onChange0_value?: ((value0: Date) => void) | undefined
    _markToday_flag?: boolean
    _markToday0_value?: boolean | undefined
    _edgeAlign_flag?: boolean
    _edgeAlign0_value?: CalendarAlign | undefined
    _edgeAlign1_value?: Offset | undefined
    applyModifierPatch(component: CalendarPickerAttribute): void {
        if (this._textStyle_flag)
            component.textStyle((this._textStyle0_value as PickerTextStyle | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((value0: Date) => void) | undefined))
        if (this._markToday_flag)
            component.markToday((this._markToday0_value as boolean | undefined))
        if (this._edgeAlign_flag)
            component.edgeAlign((this._edgeAlign0_value as CalendarAlign | undefined), (this._edgeAlign1_value as Offset | undefined))
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        this._textStyle_flag = true
        this._textStyle0_value = value
        return this
    }
    public onChange(value: ((value0: Date) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public markToday(value: boolean | undefined): this {
        this._markToday_flag = true
        this._markToday0_value = value
        return this
    }
    public edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        this._edgeAlign_flag = true
        this._edgeAlign0_value = alignType
        this._edgeAlign1_value = offset
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        const value_hintRadius  = value.hintRadius
        let value_hintRadius_type : int32 = RuntimeType.UNDEFINED
        value_hintRadius_type = runtimeType(value_hintRadius)
        valueSerializer.writeInt8((value_hintRadius_type).toChar())
        if ((value_hintRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_hintRadius_value  = value_hintRadius!
            let value_hintRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_hintRadius_value_type = runtimeType(value_hintRadius_value)
            if (RuntimeType.NUMBER == value_hintRadius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_hintRadius_value_0  = value_hintRadius_value as number
                valueSerializer.writeNumber(value_hintRadius_value_0)
            }
            else if (RuntimeType.OBJECT == value_hintRadius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_hintRadius_value_1  = value_hintRadius_value as Resource
                Resource_serializer.write(valueSerializer, value_hintRadius_value_1)
            }
        }
        const value_selected  = value.selected
        let value_selected_type : int32 = RuntimeType.UNDEFINED
        value_selected_type = runtimeType(value_selected)
        valueSerializer.writeInt8((value_selected_type).toChar())
        if ((value_selected_type) != (RuntimeType.UNDEFINED)) {
            const value_selected_value  = value_selected!
            valueSerializer.writeInt64(value_selected_value.getTime().toLong())
        }
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            valueSerializer.writeInt64(value_start_value.getTime().toLong())
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            valueSerializer.writeInt64(value_end_value.getTime().toLong())
        }
        const value_disabledDateRange  = value.disabledDateRange
        let value_disabledDateRange_type : int32 = RuntimeType.UNDEFINED
        value_disabledDateRange_type = runtimeType(value_disabledDateRange)
        valueSerializer.writeInt8((value_disabledDateRange_type).toChar())
        if ((value_disabledDateRange_type) != (RuntimeType.UNDEFINED)) {
            const value_disabledDateRange_value  = value_disabledDateRange!
            valueSerializer.writeInt32((value_disabledDateRange_value.length).toInt())
            for (let value_disabledDateRange_value_counter_i = 0; value_disabledDateRange_value_counter_i < value_disabledDateRange_value.length; value_disabledDateRange_value_counter_i++) {
                const value_disabledDateRange_value_element : DateRange = value_disabledDateRange_value[value_disabledDateRange_value_counter_i]
                DateRange_serializer.write(valueSerializer, value_disabledDateRange_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): CalendarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const hintRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hintRadius_buf : number | Resource | undefined
        if ((hintRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const hintRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let hintRadius_buf_ : number | Resource | undefined
            if (hintRadius_buf__selector == (0).toChar()) {
                hintRadius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (hintRadius_buf__selector == (1).toChar()) {
                hintRadius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for hintRadius_buf_ has to be chosen through deserialisation.")
            }
            hintRadius_buf = (hintRadius_buf_ as number | Resource)
        }
        const hintRadius_result : number | Resource | undefined = hintRadius_buf
        const selected_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selected_buf : Date | undefined
        if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            selected_buf = new Date(valueDeserializer.readInt64())
        }
        const selected_result : Date | undefined = selected_buf
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : Date | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = new Date(valueDeserializer.readInt64())
        }
        const start_result : Date | undefined = start_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : Date | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            end_buf = new Date(valueDeserializer.readInt64())
        }
        const end_result : Date | undefined = end_buf
        const disabledDateRange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disabledDateRange_buf : Array<DateRange> | undefined
        if ((disabledDateRange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const disabledDateRange_buf__length : int32 = valueDeserializer.readInt32()
            let disabledDateRange_buf_ : Array<DateRange> = new Array<DateRange>(disabledDateRange_buf__length)
            for (let disabledDateRange_buf__i = 0; disabledDateRange_buf__i < disabledDateRange_buf__length; disabledDateRange_buf__i++) {
                disabledDateRange_buf_[disabledDateRange_buf__i] = DateRange_serializer.read(valueDeserializer)
            }
            disabledDateRange_buf = disabledDateRange_buf_
        }
        const disabledDateRange_result : Array<DateRange> | undefined = disabledDateRange_buf
        let value : CalendarOptions = ({hintRadius: hintRadius_result, selected: selected_result, start: start_result, end: end_result, disabledDateRange: disabledDateRange_result} as CalendarOptions)
        return value
    }
}
export class CalendarDialogOptions_serializer {
    public static write(buffer: SerializerBase, value: CalendarDialogOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_hintRadius  = value.hintRadius
        let value_hintRadius_type : int32 = RuntimeType.UNDEFINED
        value_hintRadius_type = runtimeType(value_hintRadius)
        valueSerializer.writeInt8((value_hintRadius_type).toChar())
        if ((value_hintRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_hintRadius_value  = value_hintRadius!
            let value_hintRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_hintRadius_value_type = runtimeType(value_hintRadius_value)
            if (RuntimeType.NUMBER == value_hintRadius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_hintRadius_value_0  = value_hintRadius_value as number
                valueSerializer.writeNumber(value_hintRadius_value_0)
            }
            else if (RuntimeType.OBJECT == value_hintRadius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_hintRadius_value_1  = value_hintRadius_value as Resource
                Resource_serializer.write(valueSerializer, value_hintRadius_value_1)
            }
        }
        const value_selected  = value.selected
        let value_selected_type : int32 = RuntimeType.UNDEFINED
        value_selected_type = runtimeType(value_selected)
        valueSerializer.writeInt8((value_selected_type).toChar())
        if ((value_selected_type) != (RuntimeType.UNDEFINED)) {
            const value_selected_value  = value_selected!
            valueSerializer.writeInt64(value_selected_value.getTime().toLong())
        }
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            valueSerializer.writeInt64(value_start_value.getTime().toLong())
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            valueSerializer.writeInt64(value_end_value.getTime().toLong())
        }
        const value_disabledDateRange  = value.disabledDateRange
        let value_disabledDateRange_type : int32 = RuntimeType.UNDEFINED
        value_disabledDateRange_type = runtimeType(value_disabledDateRange)
        valueSerializer.writeInt8((value_disabledDateRange_type).toChar())
        if ((value_disabledDateRange_type) != (RuntimeType.UNDEFINED)) {
            const value_disabledDateRange_value  = value_disabledDateRange!
            valueSerializer.writeInt32((value_disabledDateRange_value.length).toInt())
            for (let value_disabledDateRange_value_counter_i = 0; value_disabledDateRange_value_counter_i < value_disabledDateRange_value.length; value_disabledDateRange_value_counter_i++) {
                const value_disabledDateRange_value_element : DateRange = value_disabledDateRange_value[value_disabledDateRange_value_counter_i]
                DateRange_serializer.write(valueSerializer, value_disabledDateRange_value_element)
            }
        }
        const value_onAccept  = value.onAccept
        let value_onAccept_type : int32 = RuntimeType.UNDEFINED
        value_onAccept_type = runtimeType(value_onAccept)
        valueSerializer.writeInt8((value_onAccept_type).toChar())
        if ((value_onAccept_type) != (RuntimeType.UNDEFINED)) {
            const value_onAccept_value  = value_onAccept!
            valueSerializer.holdAndWriteCallback(value_onAccept_value)
        }
        const value_onCancel  = value.onCancel
        let value_onCancel_type : int32 = RuntimeType.UNDEFINED
        value_onCancel_type = runtimeType(value_onCancel)
        valueSerializer.writeInt8((value_onCancel_type).toChar())
        if ((value_onCancel_type) != (RuntimeType.UNDEFINED)) {
            const value_onCancel_value  = value_onCancel!
            valueSerializer.holdAndWriteCallback(value_onCancel_value)
        }
        const value_onChange  = value.onChange
        let value_onChange_type : int32 = RuntimeType.UNDEFINED
        value_onChange_type = runtimeType(value_onChange)
        valueSerializer.writeInt8((value_onChange_type).toChar())
        if ((value_onChange_type) != (RuntimeType.UNDEFINED)) {
            const value_onChange_value  = value_onChange!
            valueSerializer.holdAndWriteCallback(value_onChange_value)
        }
        const value_backgroundColor  = value.backgroundColor
        let value_backgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_backgroundColor_type = runtimeType(value_backgroundColor)
        valueSerializer.writeInt8((value_backgroundColor_type).toChar())
        if ((value_backgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundColor_value  = value_backgroundColor!
            let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
            if (TypeChecker.isColor(value_backgroundColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_backgroundColor_value_0  = value_backgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_backgroundColor_value_1  = value_backgroundColor_value as number
                valueSerializer.writeNumber(value_backgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_backgroundColor_value_2  = value_backgroundColor_value as string
                valueSerializer.writeString(value_backgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundColor_value_3)
            }
        }
        const value_backgroundBlurStyle  = value.backgroundBlurStyle
        let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
        valueSerializer.writeInt8((value_backgroundBlurStyle_type).toChar())
        if ((value_backgroundBlurStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8((value_backgroundBlurStyleOptions_type).toChar())
        if ((value_backgroundBlurStyleOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8((value_backgroundEffect_type).toChar())
        if ((value_backgroundEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
        const value_acceptButtonStyle  = value.acceptButtonStyle
        let value_acceptButtonStyle_type : int32 = RuntimeType.UNDEFINED
        value_acceptButtonStyle_type = runtimeType(value_acceptButtonStyle)
        valueSerializer.writeInt8((value_acceptButtonStyle_type).toChar())
        if ((value_acceptButtonStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_acceptButtonStyle_value  = value_acceptButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, value_acceptButtonStyle_value)
        }
        const value_cancelButtonStyle  = value.cancelButtonStyle
        let value_cancelButtonStyle_type : int32 = RuntimeType.UNDEFINED
        value_cancelButtonStyle_type = runtimeType(value_cancelButtonStyle)
        valueSerializer.writeInt8((value_cancelButtonStyle_type).toChar())
        if ((value_cancelButtonStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_cancelButtonStyle_value  = value_cancelButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, value_cancelButtonStyle_value)
        }
        const value_onDidAppear  = value.onDidAppear
        let value_onDidAppear_type : int32 = RuntimeType.UNDEFINED
        value_onDidAppear_type = runtimeType(value_onDidAppear)
        valueSerializer.writeInt8((value_onDidAppear_type).toChar())
        if ((value_onDidAppear_type) != (RuntimeType.UNDEFINED)) {
            const value_onDidAppear_value  = value_onDidAppear!
            valueSerializer.holdAndWriteCallback(value_onDidAppear_value)
        }
        const value_onDidDisappear  = value.onDidDisappear
        let value_onDidDisappear_type : int32 = RuntimeType.UNDEFINED
        value_onDidDisappear_type = runtimeType(value_onDidDisappear)
        valueSerializer.writeInt8((value_onDidDisappear_type).toChar())
        if ((value_onDidDisappear_type) != (RuntimeType.UNDEFINED)) {
            const value_onDidDisappear_value  = value_onDidDisappear!
            valueSerializer.holdAndWriteCallback(value_onDidDisappear_value)
        }
        const value_onWillAppear  = value.onWillAppear
        let value_onWillAppear_type : int32 = RuntimeType.UNDEFINED
        value_onWillAppear_type = runtimeType(value_onWillAppear)
        valueSerializer.writeInt8((value_onWillAppear_type).toChar())
        if ((value_onWillAppear_type) != (RuntimeType.UNDEFINED)) {
            const value_onWillAppear_value  = value_onWillAppear!
            valueSerializer.holdAndWriteCallback(value_onWillAppear_value)
        }
        const value_onWillDisappear  = value.onWillDisappear
        let value_onWillDisappear_type : int32 = RuntimeType.UNDEFINED
        value_onWillDisappear_type = runtimeType(value_onWillDisappear)
        valueSerializer.writeInt8((value_onWillDisappear_type).toChar())
        if ((value_onWillDisappear_type) != (RuntimeType.UNDEFINED)) {
            const value_onWillDisappear_value  = value_onWillDisappear!
            valueSerializer.holdAndWriteCallback(value_onWillDisappear_value)
        }
        const value_shadow  = value.shadow
        let value_shadow_type : int32 = RuntimeType.UNDEFINED
        value_shadow_type = runtimeType(value_shadow)
        valueSerializer.writeInt8((value_shadow_type).toChar())
        if ((value_shadow_type) != (RuntimeType.UNDEFINED)) {
            const value_shadow_value  = value_shadow!
            let value_shadow_value_type : int32 = RuntimeType.UNDEFINED
            value_shadow_value_type = runtimeType(value_shadow_value)
            if (RuntimeType.OBJECT == value_shadow_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_shadow_value_0  = value_shadow_value as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, value_shadow_value_0)
            }
            else if (TypeChecker.isShadowStyle(value_shadow_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_shadow_value_1  = value_shadow_value as ShadowStyle
                valueSerializer.writeInt32(TypeChecker.ShadowStyle_ToNumeric(value_shadow_value_1))
            }
        }
        const value_enableHoverMode  = value.enableHoverMode
        let value_enableHoverMode_type : int32 = RuntimeType.UNDEFINED
        value_enableHoverMode_type = runtimeType(value_enableHoverMode)
        valueSerializer.writeInt8((value_enableHoverMode_type).toChar())
        if ((value_enableHoverMode_type) != (RuntimeType.UNDEFINED)) {
            const value_enableHoverMode_value  = value_enableHoverMode!
            valueSerializer.writeBoolean(value_enableHoverMode_value)
        }
        const value_hoverModeArea  = value.hoverModeArea
        let value_hoverModeArea_type : int32 = RuntimeType.UNDEFINED
        value_hoverModeArea_type = runtimeType(value_hoverModeArea)
        valueSerializer.writeInt8((value_hoverModeArea_type).toChar())
        if ((value_hoverModeArea_type) != (RuntimeType.UNDEFINED)) {
            const value_hoverModeArea_value  = (value_hoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(TypeChecker.HoverModeAreaType_ToNumeric(value_hoverModeArea_value))
        }
        const value_markToday  = value.markToday
        let value_markToday_type : int32 = RuntimeType.UNDEFINED
        value_markToday_type = runtimeType(value_markToday)
        valueSerializer.writeInt8((value_markToday_type).toChar())
        if ((value_markToday_type) != (RuntimeType.UNDEFINED)) {
            const value_markToday_value  = value_markToday!
            valueSerializer.writeBoolean(value_markToday_value)
        }
    }
    public static read(buffer: DeserializerBase): CalendarDialogOptions {
        let valueDeserializer : DeserializerBase = buffer
        const hintRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hintRadius_buf : number | Resource | undefined
        if ((hintRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const hintRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let hintRadius_buf_ : number | Resource | undefined
            if (hintRadius_buf__selector == (0).toChar()) {
                hintRadius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (hintRadius_buf__selector == (1).toChar()) {
                hintRadius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for hintRadius_buf_ has to be chosen through deserialisation.")
            }
            hintRadius_buf = (hintRadius_buf_ as number | Resource)
        }
        const hintRadius_result : number | Resource | undefined = hintRadius_buf
        const selected_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selected_buf : Date | undefined
        if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            selected_buf = new Date(valueDeserializer.readInt64())
        }
        const selected_result : Date | undefined = selected_buf
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : Date | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = new Date(valueDeserializer.readInt64())
        }
        const start_result : Date | undefined = start_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : Date | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            end_buf = new Date(valueDeserializer.readInt64())
        }
        const end_result : Date | undefined = end_buf
        const disabledDateRange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disabledDateRange_buf : Array<DateRange> | undefined
        if ((disabledDateRange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const disabledDateRange_buf__length : int32 = valueDeserializer.readInt32()
            let disabledDateRange_buf_ : Array<DateRange> = new Array<DateRange>(disabledDateRange_buf__length)
            for (let disabledDateRange_buf__i = 0; disabledDateRange_buf__i < disabledDateRange_buf__length; disabledDateRange_buf__i++) {
                disabledDateRange_buf_[disabledDateRange_buf__i] = DateRange_serializer.read(valueDeserializer)
            }
            disabledDateRange_buf = disabledDateRange_buf_
        }
        const disabledDateRange_result : Array<DateRange> | undefined = disabledDateRange_buf
        const onAccept_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAccept_buf : ((value0: Date) => void) | undefined
        if ((onAccept_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onAccept_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAccept_buf__call : KPointer = valueDeserializer.readPointer()
            const onAccept_buf__callSync : KPointer = valueDeserializer.readPointer()
            onAccept_buf = (value0: Date):void => { 
    const onAccept_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onAccept_buf__argsSerializer.writeInt32(onAccept_buf__resource.resourceId);
    onAccept_buf__argsSerializer.writePointer(onAccept_buf__call);
    onAccept_buf__argsSerializer.writePointer(onAccept_buf__callSync);
    onAccept_buf__argsSerializer.writeInt64(value0.getTime().toLong());
    InteropNativeModule._CallCallback(1405382363, onAccept_buf__argsSerializer.asBuffer(), onAccept_buf__argsSerializer.length());
    onAccept_buf__argsSerializer.release();
    return; }
        }
        const onAccept_result : ((value0: Date) => void) | undefined = onAccept_buf
        const onCancel_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onCancel_buf : VoidCallback | undefined
        if ((onCancel_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onCancel_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancel_buf__call : KPointer = valueDeserializer.readPointer()
            const onCancel_buf__callSync : KPointer = valueDeserializer.readPointer()
            onCancel_buf = ():void => { 
    const onCancel_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onCancel_buf__argsSerializer.writeInt32(onCancel_buf__resource.resourceId);
    onCancel_buf__argsSerializer.writePointer(onCancel_buf__call);
    onCancel_buf__argsSerializer.writePointer(onCancel_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, onCancel_buf__argsSerializer.asBuffer(), onCancel_buf__argsSerializer.length());
    onCancel_buf__argsSerializer.release();
    return; }
        }
        const onCancel_result : VoidCallback | undefined = onCancel_buf
        const onChange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onChange_buf : ((value0: Date) => void) | undefined
        if ((onChange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onChange_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChange_buf__call : KPointer = valueDeserializer.readPointer()
            const onChange_buf__callSync : KPointer = valueDeserializer.readPointer()
            onChange_buf = (value0: Date):void => { 
    const onChange_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onChange_buf__argsSerializer.writeInt32(onChange_buf__resource.resourceId);
    onChange_buf__argsSerializer.writePointer(onChange_buf__call);
    onChange_buf__argsSerializer.writePointer(onChange_buf__callSync);
    onChange_buf__argsSerializer.writeInt64(value0.getTime().toLong());
    InteropNativeModule._CallCallback(1405382363, onChange_buf__argsSerializer.asBuffer(), onChange_buf__argsSerializer.length());
    onChange_buf__argsSerializer.release();
    return; }
        }
        const onChange_result : ((value0: Date) => void) | undefined = onChange_buf
        const backgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColor_buf : ResourceColor | undefined
        if ((backgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const backgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundColor_buf_ : Color | number | string | Resource | undefined
            if (backgroundColor_buf__selector == (0).toChar()) {
                backgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (backgroundColor_buf__selector == (1).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundColor_buf__selector == (2).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundColor_buf__selector == (3).toChar()) {
                backgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundColor_buf_ has to be chosen through deserialisation.")
            }
            backgroundColor_buf = (backgroundColor_buf_ as Color | number | string | Resource)
        }
        const backgroundColor_result : ResourceColor | undefined = backgroundColor_buf
        const backgroundBlurStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((backgroundBlurStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((backgroundBlurStyleOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((backgroundEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundEffect_buf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffect_result : BackgroundEffectOptions | undefined = backgroundEffect_buf
        const acceptButtonStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let acceptButtonStyle_buf : PickerDialogButtonStyle | undefined
        if ((acceptButtonStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            acceptButtonStyle_buf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyle_result : PickerDialogButtonStyle | undefined = acceptButtonStyle_buf
        const cancelButtonStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelButtonStyle_buf : PickerDialogButtonStyle | undefined
        if ((cancelButtonStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            cancelButtonStyle_buf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyle_result : PickerDialogButtonStyle | undefined = cancelButtonStyle_buf
        const onDidAppear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppear_buf : VoidCallback | undefined
        if ((onDidAppear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onDidAppear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppear_buf__call : KPointer = valueDeserializer.readPointer()
            const onDidAppear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDidAppear_buf = ():void => { 
    const onDidAppear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDidAppear_buf__argsSerializer.writeInt32(onDidAppear_buf__resource.resourceId);
    onDidAppear_buf__argsSerializer.writePointer(onDidAppear_buf__call);
    onDidAppear_buf__argsSerializer.writePointer(onDidAppear_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, onDidAppear_buf__argsSerializer.asBuffer(), onDidAppear_buf__argsSerializer.length());
    onDidAppear_buf__argsSerializer.release();
    return; }
        }
        const onDidAppear_result : VoidCallback | undefined = onDidAppear_buf
        const onDidDisappear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappear_buf : VoidCallback | undefined
        if ((onDidDisappear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onDidDisappear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappear_buf__call : KPointer = valueDeserializer.readPointer()
            const onDidDisappear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDidDisappear_buf = ():void => { 
    const onDidDisappear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDidDisappear_buf__argsSerializer.writeInt32(onDidDisappear_buf__resource.resourceId);
    onDidDisappear_buf__argsSerializer.writePointer(onDidDisappear_buf__call);
    onDidDisappear_buf__argsSerializer.writePointer(onDidDisappear_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, onDidDisappear_buf__argsSerializer.asBuffer(), onDidDisappear_buf__argsSerializer.length());
    onDidDisappear_buf__argsSerializer.release();
    return; }
        }
        const onDidDisappear_result : VoidCallback | undefined = onDidDisappear_buf
        const onWillAppear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppear_buf : VoidCallback | undefined
        if ((onWillAppear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onWillAppear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppear_buf__call : KPointer = valueDeserializer.readPointer()
            const onWillAppear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onWillAppear_buf = ():void => { 
    const onWillAppear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onWillAppear_buf__argsSerializer.writeInt32(onWillAppear_buf__resource.resourceId);
    onWillAppear_buf__argsSerializer.writePointer(onWillAppear_buf__call);
    onWillAppear_buf__argsSerializer.writePointer(onWillAppear_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, onWillAppear_buf__argsSerializer.asBuffer(), onWillAppear_buf__argsSerializer.length());
    onWillAppear_buf__argsSerializer.release();
    return; }
        }
        const onWillAppear_result : VoidCallback | undefined = onWillAppear_buf
        const onWillDisappear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappear_buf : VoidCallback | undefined
        if ((onWillDisappear_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onWillDisappear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappear_buf__call : KPointer = valueDeserializer.readPointer()
            const onWillDisappear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onWillDisappear_buf = ():void => { 
    const onWillDisappear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onWillDisappear_buf__argsSerializer.writeInt32(onWillDisappear_buf__resource.resourceId);
    onWillDisappear_buf__argsSerializer.writePointer(onWillDisappear_buf__call);
    onWillDisappear_buf__argsSerializer.writePointer(onWillDisappear_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, onWillDisappear_buf__argsSerializer.asBuffer(), onWillDisappear_buf__argsSerializer.length());
    onWillDisappear_buf__argsSerializer.release();
    return; }
        }
        const onWillDisappear_result : VoidCallback | undefined = onWillDisappear_buf
        const shadow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadow_buf : ShadowOptions | ShadowStyle | undefined
        if ((shadow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const shadow_buf__selector : int32 = valueDeserializer.readInt8()
            let shadow_buf_ : ShadowOptions | ShadowStyle | undefined
            if (shadow_buf__selector == (0).toChar()) {
                shadow_buf_ = ShadowOptions_serializer.read(valueDeserializer)
            }
            else if (shadow_buf__selector == (1).toChar()) {
                shadow_buf_ = TypeChecker.ShadowStyle_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for shadow_buf_ has to be chosen through deserialisation.")
            }
            shadow_buf = (shadow_buf_ as ShadowOptions | ShadowStyle)
        }
        const shadow_result : ShadowOptions | ShadowStyle | undefined = shadow_buf
        const enableHoverMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverMode_buf : boolean | undefined
        if ((enableHoverMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableHoverMode_buf = valueDeserializer.readBoolean()
        }
        const enableHoverMode_result : boolean | undefined = enableHoverMode_buf
        const hoverModeArea_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeArea_buf : HoverModeAreaType | undefined
        if ((hoverModeArea_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            hoverModeArea_buf = TypeChecker.HoverModeAreaType_FromNumeric(valueDeserializer.readInt32())
        }
        const hoverModeArea_result : HoverModeAreaType | undefined = hoverModeArea_buf
        const markToday_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let markToday_buf : boolean | undefined
        if ((markToday_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            markToday_buf = valueDeserializer.readBoolean()
        }
        const markToday_result : boolean | undefined = markToday_buf
        let value : CalendarDialogOptions = ({hintRadius: hintRadius_result, selected: selected_result, start: start_result, end: end_result, disabledDateRange: disabledDateRange_result, onAccept: onAccept_result, onCancel: onCancel_result, onChange: onChange_result, backgroundColor: backgroundColor_result, backgroundBlurStyle: backgroundBlurStyle_result, backgroundBlurStyleOptions: backgroundBlurStyleOptions_result, backgroundEffect: backgroundEffect_result, acceptButtonStyle: acceptButtonStyle_result, cancelButtonStyle: cancelButtonStyle_result, onDidAppear: onDidAppear_result, onDidDisappear: onDidDisappear_result, onWillAppear: onWillAppear_result, onWillDisappear: onWillDisappear_result, shadow: shadow_result, enableHoverMode: enableHoverMode_result, hoverModeArea: hoverModeArea_result, markToday: markToday_result} as CalendarDialogOptions)
        return value
    }
}
