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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ArkThemeScopeManager } from "#arktheme"
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, DateRange, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, PickerDialogButtonStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, DateRange_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, PickerDialogButtonStyle_serializer, ShadowOptions_serializer } from "./common"
import { Offset_serializer, Offset, Length, VoidCallback, ResourceColor } from "./units"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { AttributeModifier, hookCalendarPickerAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Color } from "./enums"
import { CalendarPickerModifier } from "./../CalendarPickerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
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
    static show_serialize(options?: CalendarDialogOptions): void {
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
    public static show(options?: CalendarDialogOptions): void {
        const options_casted = options as (CalendarDialogOptions | undefined)
        CalendarPickerDialog.show_serialize(options_casted)
        return
    }
}
export class ArkCalendarPickerPeer extends ArkCommonMethodPeer {
    attributeSet?: CalendarPickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setOnChangeAttribute(value: ((value0: Date) => void) | undefined): void {
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
    hintRadius?: number | Resource;
    selected?: Date;
    start?: Date;
    end?: Date;
    disabledDateRange?: Array<DateRange>;
}
export interface CalendarPickerAttribute extends CommonMethod {
    setCalendarPickerOptions(options?: CalendarOptions): this {
        throw new Error("Unimplemented method setCalendarPickerOptions")
    }
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
    setCalendarPickerOptions(options?: CalendarOptions): this {
        return this
    }
    textStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    onChange(value: ((value0: Date) => void) | undefined): this {
        return this
    }
    markToday(value: boolean | undefined): this {
        return this
    }
    edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkCalendarPickerPeer)
    }
    public setCalendarPickerOptions(options?: CalendarOptions): this {
        if (this.checkPriority("setCalendarPickerOptions")) {
            const options_casted = options as (CalendarOptions | undefined)
            this.getPeer()?.setCalendarPickerOptionsAttribute(options_casted)
            this.applyOptionsFinish('CalendarPickerAttribute');
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
    @memo
    style: ((attributes: CalendarPickerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCalendarPickerComponent>((): ArkCalendarPickerComponent => {
        return new ArkCalendarPickerComponent()
    })
    NodeAttach<ArkCalendarPickerPeer>((): ArkCalendarPickerPeer => ArkCalendarPickerPeer.create(receiver), (peer: ArkCalendarPickerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
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
            if (valueHolderForHintRadiusTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHintRadiusTmpValueForIdx0  = valueHolderForHintRadiusTmpValue as number
                valueSerializer.writeNumber(valueHolderForHintRadiusTmpValueForIdx0)
            } else if (valueHolderForHintRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHintRadiusTmpValueForIdx1  = valueHolderForHintRadiusTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHintRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            valueSerializer.writeInt64(valueHolderForSelectedTmpValue.getTime().toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime().toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime().toLong())
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
        const hintRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hintRadiusTmpBuf : number | Resource | undefined = undefined
        if ((hintRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const hintRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let hintRadiusTmpBuf_ : number | Resource | undefined
            if (hintRadiusTmpBuf_UnionSelector == (0).toChar()) {
                hintRadiusTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (hintRadiusTmpBuf_UnionSelector == (1).toChar()) {
                hintRadiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for hintRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            hintRadiusTmpBuf = (hintRadiusTmpBuf_ as number | Resource)
        }
        const hintRadiusTmpResult : number | Resource | undefined = hintRadiusTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTmpBuf : Date | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const selectedTmpResult : Date | undefined = selectedTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : Date | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const disabledDateRangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disabledDateRangeTmpBuf : Array<DateRange> | undefined = undefined
        if ((disabledDateRangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const disabledDateRangeTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let disabledDateRangeTmpBuf_ : Array<DateRange> = new Array<DateRange>(disabledDateRangeTmpBuf_Length)
            for (let disabledDateRangeTmpBuf_BufCounterI = 0; disabledDateRangeTmpBuf_BufCounterI < disabledDateRangeTmpBuf_Length; disabledDateRangeTmpBuf_BufCounterI++) {
                disabledDateRangeTmpBuf_[disabledDateRangeTmpBuf_BufCounterI] = DateRange_serializer.read(valueDeserializer)
            }
            disabledDateRangeTmpBuf = disabledDateRangeTmpBuf_
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
            if (valueHolderForHintRadiusTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHintRadiusTmpValueForIdx0  = valueHolderForHintRadiusTmpValue as number
                valueSerializer.writeNumber(valueHolderForHintRadiusTmpValueForIdx0)
            } else if (valueHolderForHintRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHintRadiusTmpValueForIdx1  = valueHolderForHintRadiusTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHintRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            valueSerializer.writeInt64(valueHolderForSelectedTmpValue.getTime().toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime().toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime().toLong())
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
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
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
        const hintRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hintRadiusTmpBuf : number | Resource | undefined = undefined
        if ((hintRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const hintRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let hintRadiusTmpBuf_ : number | Resource | undefined
            if (hintRadiusTmpBuf_UnionSelector == (0).toChar()) {
                hintRadiusTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (hintRadiusTmpBuf_UnionSelector == (1).toChar()) {
                hintRadiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for hintRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            hintRadiusTmpBuf = (hintRadiusTmpBuf_ as number | Resource)
        }
        const hintRadiusTmpResult : number | Resource | undefined = hintRadiusTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTmpBuf : Date | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const selectedTmpResult : Date | undefined = selectedTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : Date | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const disabledDateRangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disabledDateRangeTmpBuf : Array<DateRange> | undefined = undefined
        if ((disabledDateRangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const disabledDateRangeTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let disabledDateRangeTmpBuf_ : Array<DateRange> = new Array<DateRange>(disabledDateRangeTmpBuf_Length)
            for (let disabledDateRangeTmpBuf_BufCounterI = 0; disabledDateRangeTmpBuf_BufCounterI < disabledDateRangeTmpBuf_Length; disabledDateRangeTmpBuf_BufCounterI++) {
                disabledDateRangeTmpBuf_[disabledDateRangeTmpBuf_BufCounterI] = DateRange_serializer.read(valueDeserializer)
            }
            disabledDateRangeTmpBuf = disabledDateRangeTmpBuf_
        }
        const disabledDateRangeTmpResult : Array<DateRange> | undefined = disabledDateRangeTmpBuf
        const onAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAcceptTmpBuf : ((value0: Date) => void) | undefined = undefined
        if ((onAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAcceptTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAcceptTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onAcceptTmpBuf = (value0: Date):void => {
                const onAcceptTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAcceptTmpBuf_BufArgsSerializer.writeInt32(onAcceptTmpBuf_BufResource.resourceId);
                onAcceptTmpBuf_BufArgsSerializer.writePointer(onAcceptTmpBuf_BufCall);
                onAcceptTmpBuf_BufArgsSerializer.writePointer(onAcceptTmpBuf_BufCallSync);
                onAcceptTmpBuf_BufArgsSerializer.writeInt64(value0.getTime().toLong());
                InteropNativeModule._CallCallbackSync(10, 1405382363, onAcceptTmpBuf_BufArgsSerializer.asBuffer(), onAcceptTmpBuf_BufArgsSerializer.length());
                onAcceptTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onAcceptTmpResult : ((value0: Date) => void) | undefined = onAcceptTmpBuf
        const onCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onCancelTmpBuf : VoidCallback | undefined = undefined
        if ((onCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onCancelTmpBuf = ():void => {
                const onCancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onCancelTmpBuf_BufArgsSerializer.writeInt32(onCancelTmpBuf_BufResource.resourceId);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCall);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onCancelTmpBuf_BufArgsSerializer.asBuffer(), onCancelTmpBuf_BufArgsSerializer.length());
                onCancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onCancelTmpResult : VoidCallback | undefined = onCancelTmpBuf
        const onChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onChangeTmpBuf : ((value0: Date) => void) | undefined = undefined
        if ((onChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onChangeTmpBuf = (value0: Date):void => {
                const onChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onChangeTmpBuf_BufArgsSerializer.writeInt32(onChangeTmpBuf_BufResource.resourceId);
                onChangeTmpBuf_BufArgsSerializer.writePointer(onChangeTmpBuf_BufCall);
                onChangeTmpBuf_BufArgsSerializer.writePointer(onChangeTmpBuf_BufCallSync);
                onChangeTmpBuf_BufArgsSerializer.writeInt64(value0.getTime().toLong());
                InteropNativeModule._CallCallbackSync(10, 1405382363, onChangeTmpBuf_BufArgsSerializer.asBuffer(), onChangeTmpBuf_BufArgsSerializer.length());
                onChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onChangeTmpResult : ((value0: Date) => void) | undefined = onChangeTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const acceptButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let acceptButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((acceptButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            acceptButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyleTmpResult : PickerDialogButtonStyle | undefined = acceptButtonStyleTmpBuf
        const cancelButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((cancelButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            cancelButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyleTmpResult : PickerDialogButtonStyle | undefined = cancelButtonStyleTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : VoidCallback | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : VoidCallback | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : VoidCallback | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : VoidCallback | undefined = onWillDisappearTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const markTodayTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let markTodayTmpBuf : boolean | undefined = undefined
        if ((markTodayTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            markTodayTmpBuf = valueDeserializer.readBoolean()
        }
        const markTodayTmpResult : boolean | undefined = markTodayTmpBuf
        let value : CalendarDialogOptions = ({hintRadius: hintRadiusTmpResult, selected: selectedTmpResult, start: startTmpResult, end: endTmpResult, disabledDateRange: disabledDateRangeTmpResult, onAccept: onAcceptTmpResult, onCancel: onCancelTmpResult, onChange: onChangeTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, markToday: markTodayTmpResult} as CalendarDialogOptions)
        return value
    }
}
