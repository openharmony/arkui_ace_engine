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

import { DismissReason, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, Callback as arkui_component_common_Callback, TransitionEffect, ShadowOptions, ShadowStyle, HoverModeAreaType, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, TransitionEffect_serializer, ShadowOptions_serializer } from './common'
import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Resource as global_resource_Resource } from 'global.resource'
import { VoidCallback, ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource, ResourceColor, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles, BorderRadiuses_serializer, LocalizedBorderRadiuses_serializer, EdgeWidths_serializer, LocalizedEdgeWidths_serializer, EdgeColors_serializer, LocalizedEdgeColors_serializer, EdgeStyles_serializer } from './units'
import { DialogButtonStyle, Color as arkui_component_enums_Color, BorderStyle } from './enums'
import { DialogAlignment } from './alertDialog'
import { LevelMode, ImmersiveMode, LevelOrder } from '@ohos.promptAction'
import { extractors } from '#handwritten'
import { global_resource_Resource_serializer } from './../framework/resource'
import { LevelOrder_serializer } from './../framework/ohos.promptAction'
export interface DismissDialogAction {
    reason: DismissReason
    dismiss(): void
}
export class DismissDialogActionInternal implements MaterializedBase,DismissDialogAction {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public reason: DismissReason
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DismissDialogActionInternal.getFinalizer())
        this.reason = this.getReason()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, DismissDialogActionInternal.construct())
        this.reason = this.getReason()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DismissDialogAction_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DismissDialogAction_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): DismissDialogActionInternal {
        return new DismissDialogActionInternal(MaterializedBaseTag.NOP, ptr)
    }
    public dismiss(): void {
        this.dismiss_serialize()
        return
    }
    private getReason(): DismissReason {
        return this.getReason_serialize()
    }
    private setReason(reason: DismissReason): void {
        const reason_casted = reason as (DismissReason)
        this.setReason_serialize(reason_casted)
        return
    }
    private dismiss_serialize(): void {
        ArkUIGeneratedNativeModule._DismissDialogAction_dismiss(this.peer!.ptr)
    }
    private getReason_serialize(): DismissReason {
        const retval  = ArkUIGeneratedNativeModule._DismissDialogAction_getReason(this.peer!.ptr)
        return DismissReason.fromValue(retval)
    }
    private setReason_serialize(reason: DismissReason): void {
        ArkUIGeneratedNativeModule._DismissDialogAction_setReason(this.peer!.ptr, reason.valueOf())
    }
}
export interface SheetInfo {
    title: string | global_resource_Resource;
    icon?: string | global_resource_Resource;
    action: VoidCallback;
}
export interface ActionSheetButtonOptions {
    enabled?: boolean;
    defaultFocus?: boolean;
    style?: DialogButtonStyle;
    value: string | global_resource_Resource;
    action: VoidCallback;
}
export interface ActionSheetOffset {
    dx: double | string | global_resource_Resource;
    dy: double | string | global_resource_Resource;
}
export interface ActionSheetOptions {
    title: string | global_resource_Resource;
    subtitle?: arkui_component_units_ResourceStr;
    message: string | global_resource_Resource;
    confirm?: ActionSheetButtonOptions;
    cancel?: VoidCallback;
    sheets: Array<SheetInfo>;
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: ActionSheetOffset;
    maskRect?: Rectangle;
    showInSubWindow?: boolean;
    isModal?: boolean;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onWillDismiss?: arkui_component_common_Callback<DismissDialogAction, void>;
    transition?: TransitionEffect;
    cornerRadius?: Dimension | BorderRadiuses | LocalizedBorderRadiuses;
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    levelMode?: LevelMode;
    levelUniqueId?: int32;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
}
export class DismissDialogAction_serializer {
    public static write(buffer: SerializerBase, value: DismissDialogAction): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DismissDialogAction {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DismissDialogActionInternal.fromPtr(ptr)
    }
}
export class ActionSheetButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: ActionSheetButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        if (valueHolderForEnabled !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnabledTmpValue  = valueHolderForEnabled!
            valueSerializer.writeBoolean(valueHolderForEnabledTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDefaultFocus  = value.defaultFocus
        if (valueHolderForDefaultFocus !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDefaultFocusTmpValue  = valueHolderForDefaultFocus!
            valueSerializer.writeBoolean(valueHolderForDefaultFocusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as DialogButtonStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof global_resource_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForAction  = value.action
        valueSerializer.holdAndWriteCallback(valueHolderForAction)
    }
    public static read(buffer: DeserializerBase): ActionSheetButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enabledTmpBuf : boolean | undefined = undefined
        if ((enabledTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enabledTmpBuf = valueDeserializer.readBoolean()
        }
        const enabledTmpResult : boolean | undefined = enabledTmpBuf
        const defaultFocusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let defaultFocusTmpBuf : boolean | undefined = undefined
        if ((defaultFocusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            defaultFocusTmpBuf = valueDeserializer.readBoolean()
        }
        const defaultFocusTmpResult : boolean | undefined = defaultFocusTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : DialogButtonStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = DialogButtonStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : DialogButtonStyle | undefined = styleTmpBuf
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | global_resource_Resource | undefined
        if (valueTmpBufUnionSelector == (0).toByte()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toByte()) {
            valueTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
        }
        const valueTmpResult : string | global_resource_Resource = (valueTmpBuf as string | global_resource_Resource)
        const actionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const actionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const actionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const actionTmpBufClosure  = ():void => {
            const actionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            actionTmpBufBufArgsSerializer.writeInt32(actionTmpBufBufResource.resourceId);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCall);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCallSync);
            InteropNativeModule._CallCallbackSync(10, 553494831, actionTmpBufBufArgsSerializer.asBuffer(), actionTmpBufBufArgsSerializer.length());
            actionTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(actionTmpBufClosure, actionTmpBufBufResource)
        const actionTmpResult : VoidCallback = actionTmpBufClosure
        let value : ActionSheetButtonOptions = ({enabled: enabledTmpResult, defaultFocus: defaultFocusTmpResult, style: styleTmpResult, value: valueTmpResult, action: actionTmpResult} as ActionSheetButtonOptions)
        return value
    }
}
export class ActionSheetOffset_serializer {
    public static write(buffer: SerializerBase, value: ActionSheetOffset): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForDx  = value.dx
        if (valueHolderForDx instanceof double) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForDxForIdx0  = valueHolderForDx as double
            valueSerializer.writeFloat64(valueHolderForDxForIdx0)
        } else if (valueHolderForDx instanceof string) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForDxForIdx1  = valueHolderForDx as string
            valueSerializer.writeString(valueHolderForDxForIdx1)
        } else if (valueHolderForDx instanceof global_resource_Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForDxForIdx2  = valueHolderForDx as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForDxForIdx2)
        }
        const valueHolderForDy  = value.dy
        if (valueHolderForDy instanceof double) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForDyForIdx0  = valueHolderForDy as double
            valueSerializer.writeFloat64(valueHolderForDyForIdx0)
        } else if (valueHolderForDy instanceof string) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForDyForIdx1  = valueHolderForDy as string
            valueSerializer.writeString(valueHolderForDyForIdx1)
        } else if (valueHolderForDy instanceof global_resource_Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForDyForIdx2  = valueHolderForDy as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForDyForIdx2)
        }
    }
    public static read(buffer: DeserializerBase): ActionSheetOffset {
        let valueDeserializer : DeserializerBase = buffer
        const dxTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let dxTmpBuf : double | string | global_resource_Resource | undefined
        if (dxTmpBufUnionSelector == (0).toByte()) {
            dxTmpBuf = valueDeserializer.readFloat64()
        } else if (dxTmpBufUnionSelector == (1).toByte()) {
            dxTmpBuf = (valueDeserializer.readString() as string)
        } else if (dxTmpBufUnionSelector == (2).toByte()) {
            dxTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for dxTmpBuf has to be chosen through deserialisation.')
        }
        const dxTmpResult : double | string | global_resource_Resource = (dxTmpBuf as double | string | global_resource_Resource)
        const dyTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let dyTmpBuf : double | string | global_resource_Resource | undefined
        if (dyTmpBufUnionSelector == (0).toByte()) {
            dyTmpBuf = valueDeserializer.readFloat64()
        } else if (dyTmpBufUnionSelector == (1).toByte()) {
            dyTmpBuf = (valueDeserializer.readString() as string)
        } else if (dyTmpBufUnionSelector == (2).toByte()) {
            dyTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for dyTmpBuf has to be chosen through deserialisation.')
        }
        const dyTmpResult : double | string | global_resource_Resource = (dyTmpBuf as double | string | global_resource_Resource)
        let value : ActionSheetOffset = ({dx: dxTmpResult, dy: dyTmpResult} as ActionSheetOffset)
        return value
    }
}
export class SheetInfo_serializer {
    public static write(buffer: SerializerBase, value: SheetInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTitle  = value.title
        if (valueHolderForTitle instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForTitleForIdx0  = valueHolderForTitle as string
            valueSerializer.writeString(valueHolderForTitleForIdx0)
        } else if (valueHolderForTitle instanceof global_resource_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForTitleForIdx1  = valueHolderForTitle as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForTitleForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAction  = value.action
        valueSerializer.holdAndWriteCallback(valueHolderForAction)
    }
    public static read(buffer: DeserializerBase): SheetInfo {
        let valueDeserializer : DeserializerBase = buffer
        const titleTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let titleTmpBuf : string | global_resource_Resource | undefined
        if (titleTmpBufUnionSelector == (0).toByte()) {
            titleTmpBuf = (valueDeserializer.readString() as string)
        } else if (titleTmpBufUnionSelector == (1).toByte()) {
            titleTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for titleTmpBuf has to be chosen through deserialisation.')
        }
        const titleTmpResult : string | global_resource_Resource = (titleTmpBuf as string | global_resource_Resource)
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf : string | global_resource_Resource | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBufOpt : string | global_resource_Resource | undefined
            if (iconTmpBufOptUnionSelector == (0).toByte()) {
                iconTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (iconTmpBufOptUnionSelector == (1).toByte()) {
                iconTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for iconTmpBufOpt has to be chosen through deserialisation.')
            }
            iconTmpBuf = (iconTmpBufOpt as string | global_resource_Resource)
        }
        const iconTmpResult : string | global_resource_Resource | undefined = iconTmpBuf
        const actionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const actionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const actionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const actionTmpBufClosure  = ():void => {
            const actionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            actionTmpBufBufArgsSerializer.writeInt32(actionTmpBufBufResource.resourceId);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCall);
            actionTmpBufBufArgsSerializer.writePointer(actionTmpBufBufCallSync);
            InteropNativeModule._CallCallbackSync(10, 553494831, actionTmpBufBufArgsSerializer.asBuffer(), actionTmpBufBufArgsSerializer.length());
            actionTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(actionTmpBufClosure, actionTmpBufBufResource)
        const actionTmpResult : VoidCallback = actionTmpBufClosure
        let value : SheetInfo = ({title: titleTmpResult, icon: iconTmpResult, action: actionTmpResult} as SheetInfo)
        return value
    }
}
export class ActionSheetOptions_serializer {
    public static write(buffer: SerializerBase, value: ActionSheetOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTitle  = value.title
        if (valueHolderForTitle instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForTitleForIdx0  = valueHolderForTitle as string
            valueSerializer.writeString(valueHolderForTitleForIdx0)
        } else if (valueHolderForTitle instanceof global_resource_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForTitleForIdx1  = valueHolderForTitle as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForTitleForIdx1)
        }
        const valueHolderForSubtitle  = value.subtitle
        if (valueHolderForSubtitle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSubtitleTmpValue  = valueHolderForSubtitle!
            if (valueHolderForSubtitleTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSubtitleTmpValueForIdx0  = valueHolderForSubtitleTmpValue as string
                valueSerializer.writeString(valueHolderForSubtitleTmpValueForIdx0)
            } else if (valueHolderForSubtitleTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSubtitleTmpValueForIdx1  = valueHolderForSubtitleTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSubtitleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMessage  = value.message
        if (valueHolderForMessage instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForMessageForIdx0  = valueHolderForMessage as string
            valueSerializer.writeString(valueHolderForMessageForIdx0)
        } else if (valueHolderForMessage instanceof global_resource_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForMessageForIdx1  = valueHolderForMessage as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForMessageForIdx1)
        }
        const valueHolderForConfirm  = value.confirm
        if (valueHolderForConfirm !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConfirmTmpValue  = valueHolderForConfirm!
            ActionSheetButtonOptions_serializer.write(valueSerializer, valueHolderForConfirmTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCancel  = value.cancel
        if (valueHolderForCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelTmpValue  = valueHolderForCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSheets  = value.sheets
        valueSerializer.writeInt32((valueHolderForSheets.length).toInt())
        for (let valueHolderForSheetsCounterI = 0; valueHolderForSheetsCounterI < valueHolderForSheets.length; valueHolderForSheetsCounterI++) {
            const valueHolderForSheetsTmpElement : SheetInfo = valueHolderForSheets[valueHolderForSheetsCounterI]
            SheetInfo_serializer.write(valueSerializer, valueHolderForSheetsTmpElement)
        }
        const valueHolderForAutoCancel  = value.autoCancel
        if (valueHolderForAutoCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAutoCancelTmpValue  = valueHolderForAutoCancel!
            valueSerializer.writeBoolean(valueHolderForAutoCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment  = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue  = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            ActionSheetOffset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect  = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue  = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowInSubWindow  = value.showInSubWindow
        if (valueHolderForShowInSubWindow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowInSubWindowTmpValue  = valueHolderForShowInSubWindow!
            valueSerializer.writeBoolean(valueHolderForShowInSubWindowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsModal  = value.isModal
        if (valueHolderForIsModal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsModalTmpValue  = valueHolderForIsModal!
            valueSerializer.writeBoolean(valueHolderForIsModalTmpValue)
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
        const valueHolderForOnWillDismiss  = value.onWillDismiss
        if (valueHolderForOnWillDismiss !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDismissTmpValue  = valueHolderForOnWillDismiss!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDismissTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        if (valueHolderForTransition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTransitionTmpValue  = valueHolderForTransition!
            TransitionEffect_serializer.write(valueSerializer, valueHolderForTransitionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCornerRadius  = value.cornerRadius
        if (valueHolderForCornerRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCornerRadiusTmpValue  = valueHolderForCornerRadius!
            if (valueHolderForCornerRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx0  = valueHolderForCornerRadiusTmpValue as Dimension
                if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx0  = valueHolderForCornerRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForCornerRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx1  = valueHolderForCornerRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForCornerRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx2  = valueHolderForCornerRadiusTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForCornerRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx1  = valueHolderForCornerRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx1)
            } else if (valueHolderForCornerRadiusTmpValue instanceof LocalizedBorderRadiuses) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx2  = valueHolderForCornerRadiusTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as Dimension
                if (valueHolderForBorderWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx0  = valueHolderForBorderWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx1  = valueHolderForBorderWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx2  = valueHolderForBorderWidthTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx1)
            } else if (valueHolderForBorderWidthTmpValue instanceof LocalizedEdgeWidths) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderWidthTmpValueForIdx2  = valueHolderForBorderWidthTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as ResourceColor
                if (valueHolderForBorderColorTmpValueForIdx0 instanceof arkui_component_enums_Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx0  = valueHolderForBorderColorTmpValueForIdx0 as arkui_component_enums_Color
                    valueSerializer.writeInt32((valueHolderForBorderColorTmpValueForIdx0ForIdx0.getOrdinal()) % (12))
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx1  = valueHolderForBorderColorTmpValueForIdx0 as int32
                    valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx2  = valueHolderForBorderColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx3  = valueHolderForBorderColorTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForBorderColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx1)
            } else if (valueHolderForBorderColorTmpValue instanceof LocalizedEdgeColors) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderColorTmpValueForIdx2  = valueHolderForBorderColorTmpValue as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderStyle  = value.borderStyle
        if (valueHolderForBorderStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderStyleTmpValue  = valueHolderForBorderStyle!
            if (valueHolderForBorderStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderStyleTmpValueForIdx0  = valueHolderForBorderStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(valueHolderForBorderStyleTmpValueForIdx0.valueOf())
            } else if (valueHolderForBorderStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderStyleTmpValueForIdx1  = valueHolderForBorderStyleTmpValue as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, valueHolderForBorderStyleTmpValueForIdx1)
            }
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
        const valueHolderForLevelMode  = value.levelMode
        if (valueHolderForLevelMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelModeTmpValue  = (valueHolderForLevelMode as LevelMode)
            valueSerializer.writeInt32(valueHolderForLevelModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelUniqueId  = value.levelUniqueId
        if (valueHolderForLevelUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelUniqueIdTmpValue  = valueHolderForLevelUniqueId!
            valueSerializer.writeInt32(valueHolderForLevelUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImmersiveMode  = value.immersiveMode
        if (valueHolderForImmersiveMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImmersiveModeTmpValue  = (valueHolderForImmersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(valueHolderForImmersiveModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelOrder  = value.levelOrder
        if (valueHolderForLevelOrder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelOrderTmpValue  = valueHolderForLevelOrder!
            LevelOrder_serializer.write(valueSerializer, valueHolderForLevelOrderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ActionSheetOptions {
        let valueDeserializer : DeserializerBase = buffer
        const titleTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let titleTmpBuf : string | global_resource_Resource | undefined
        if (titleTmpBufUnionSelector == (0).toByte()) {
            titleTmpBuf = (valueDeserializer.readString() as string)
        } else if (titleTmpBufUnionSelector == (1).toByte()) {
            titleTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for titleTmpBuf has to be chosen through deserialisation.')
        }
        const titleTmpResult : string | global_resource_Resource = (titleTmpBuf as string | global_resource_Resource)
        const subtitleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let subtitleTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((subtitleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const subtitleTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let subtitleTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (subtitleTmpBufOptUnionSelector == (0).toByte()) {
                subtitleTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (subtitleTmpBufOptUnionSelector == (1).toByte()) {
                subtitleTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for subtitleTmpBufOpt has to be chosen through deserialisation.')
            }
            subtitleTmpBuf = (subtitleTmpBufOpt as string | arkui_component_units_Resource)
        }
        const subtitleTmpResult : arkui_component_units_ResourceStr | undefined = subtitleTmpBuf
        const messageTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let messageTmpBuf : string | global_resource_Resource | undefined
        if (messageTmpBufUnionSelector == (0).toByte()) {
            messageTmpBuf = (valueDeserializer.readString() as string)
        } else if (messageTmpBufUnionSelector == (1).toByte()) {
            messageTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for messageTmpBuf has to be chosen through deserialisation.')
        }
        const messageTmpResult : string | global_resource_Resource = (messageTmpBuf as string | global_resource_Resource)
        const confirmTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let confirmTmpBuf : ActionSheetButtonOptions | undefined = undefined
        if ((confirmTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            confirmTmpBuf = ActionSheetButtonOptions_serializer.read(valueDeserializer)
        }
        const confirmTmpResult : ActionSheetButtonOptions | undefined = confirmTmpBuf
        const cancelTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let cancelTmpBuf : VoidCallback | undefined = undefined
        if ((cancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cancelTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const cancelTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const cancelTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const cancelTmpBufOptClosure  = ():void => {
                const cancelTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                cancelTmpBufOptBufArgsSerializer.writeInt32(cancelTmpBufOptBufResource.resourceId);
                cancelTmpBufOptBufArgsSerializer.writePointer(cancelTmpBufOptBufCall);
                cancelTmpBufOptBufArgsSerializer.writePointer(cancelTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, cancelTmpBufOptBufArgsSerializer.asBuffer(), cancelTmpBufOptBufArgsSerializer.length());
                cancelTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(cancelTmpBufOptClosure, cancelTmpBufOptBufResource)
            cancelTmpBuf = cancelTmpBufOptClosure
        }
        const cancelTmpResult : VoidCallback | undefined = cancelTmpBuf
        const sheetsTmpBufLength : int32 = valueDeserializer.readInt32()
        let sheetsTmpBuf : Array<SheetInfo> = new Array<SheetInfo>(sheetsTmpBufLength)
        for (let sheetsTmpBufBufCounterI = 0; sheetsTmpBufBufCounterI < sheetsTmpBufLength; sheetsTmpBufBufCounterI++) {
            sheetsTmpBuf[sheetsTmpBufBufCounterI] = SheetInfo_serializer.read(valueDeserializer)
        }
        const sheetsTmpResult : Array<SheetInfo> = sheetsTmpBuf
        const autoCancelTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let autoCancelTmpBuf : boolean | undefined = undefined
        if ((autoCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoCancelTmpBuf = valueDeserializer.readBoolean()
        }
        const autoCancelTmpResult : boolean | undefined = autoCancelTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : ActionSheetOffset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = ActionSheetOffset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : ActionSheetOffset | undefined = offsetTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const showInSubWindowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let showInSubWindowTmpBuf : boolean | undefined = undefined
        if ((showInSubWindowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInSubWindowTmpBuf = valueDeserializer.readBoolean()
        }
        const showInSubWindowTmpResult : boolean | undefined = showInSubWindowTmpBuf
        const isModalTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let isModalTmpBuf : boolean | undefined = undefined
        if ((isModalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isModalTmpBuf = valueDeserializer.readBoolean()
        }
        const isModalTmpResult : boolean | undefined = isModalTmpBuf
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
        const onWillDismissTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onWillDismissTmpBuf : arkui_component_common_Callback<DismissDialogAction, void> | undefined = undefined
        if ((onWillDismissTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDismissTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismissTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBufOptClosure  = (data: DismissDialogAction):void => {
                const onWillDismissTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDismissTmpBufOptBufArgsSerializer.writeInt32(onWillDismissTmpBufOptBufResource.resourceId);
                onWillDismissTmpBufOptBufArgsSerializer.writePointer(onWillDismissTmpBufOptBufCall);
                onWillDismissTmpBufOptBufArgsSerializer.writePointer(onWillDismissTmpBufOptBufCallSync);
                DismissDialogAction_serializer.write(onWillDismissTmpBufOptBufArgsSerializer, data);
                InteropNativeModule._CallCallbackSync(10, -1862816733, onWillDismissTmpBufOptBufArgsSerializer.asBuffer(), onWillDismissTmpBufOptBufArgsSerializer.length());
                onWillDismissTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillDismissTmpBufOptClosure, onWillDismissTmpBufOptBufResource)
            onWillDismissTmpBuf = onWillDismissTmpBufOptClosure
        }
        const onWillDismissTmpResult : arkui_component_common_Callback<DismissDialogAction, void> | undefined = onWillDismissTmpBuf
        const transitionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let transitionTmpBuf : TransitionEffect | undefined = undefined
        if ((transitionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            transitionTmpBuf = (TransitionEffect_serializer.read(valueDeserializer) as TransitionEffect)
        }
        const transitionTmpResult : TransitionEffect | undefined = transitionTmpBuf
        const cornerRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let cornerRadiusTmpBuf : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = undefined
        if ((cornerRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cornerRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let cornerRadiusTmpBufOpt : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined
            if (cornerRadiusTmpBufOptUnionSelector == (0).toByte()) {
                const cornerRadiusTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let cornerRadiusTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (cornerRadiusTmpBufOptBufUUnionSelector == (0).toByte()) {
                    cornerRadiusTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (cornerRadiusTmpBufOptBufUUnionSelector == (1).toByte()) {
                    cornerRadiusTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (cornerRadiusTmpBufOptBufUUnionSelector == (2).toByte()) {
                    cornerRadiusTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for cornerRadiusTmpBufOptBufU has to be chosen through deserialisation.')
                }
                cornerRadiusTmpBufOpt = (cornerRadiusTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (cornerRadiusTmpBufOptUnionSelector == (1).toByte()) {
                cornerRadiusTmpBufOpt = BorderRadiuses_serializer.read(valueDeserializer)
            } else if (cornerRadiusTmpBufOptUnionSelector == (2).toByte()) {
                cornerRadiusTmpBufOpt = LocalizedBorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for cornerRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            cornerRadiusTmpBuf = (cornerRadiusTmpBufOpt as Dimension | BorderRadiuses | LocalizedBorderRadiuses)
        }
        const cornerRadiusTmpResult : Dimension | BorderRadiuses | LocalizedBorderRadiuses | undefined = cornerRadiusTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : string | number | global_resource_Resource | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBufOptUnionSelector == (2).toByte()) {
                widthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as string | number | global_resource_Resource)
        }
        const widthTmpResult : Dimension | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : Dimension | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : string | number | global_resource_Resource | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBufOptUnionSelector == (2).toByte()) {
                heightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as string | number | global_resource_Resource)
        }
        const heightTmpResult : Dimension | undefined = heightTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderWidthTmpBuf : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBufOpt : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined
            if (borderWidthTmpBufOptUnionSelector == (0).toByte()) {
                const borderWidthTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderWidthTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (borderWidthTmpBufOptBufUUnionSelector == (0).toByte()) {
                    borderWidthTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (borderWidthTmpBufOptBufUUnionSelector == (1).toByte()) {
                    borderWidthTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (borderWidthTmpBufOptBufUUnionSelector == (2).toByte()) {
                    borderWidthTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for borderWidthTmpBufOptBufU has to be chosen through deserialisation.')
                }
                borderWidthTmpBufOpt = (borderWidthTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (borderWidthTmpBufOptUnionSelector == (1).toByte()) {
                borderWidthTmpBufOpt = EdgeWidths_serializer.read(valueDeserializer)
            } else if (borderWidthTmpBufOptUnionSelector == (2).toByte()) {
                borderWidthTmpBufOpt = LocalizedEdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            borderWidthTmpBuf = (borderWidthTmpBufOpt as Dimension | EdgeWidths | LocalizedEdgeWidths)
        }
        const borderWidthTmpResult : Dimension | EdgeWidths | LocalizedEdgeWidths | undefined = borderWidthTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderColorTmpBuf : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBufOpt : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
            if (borderColorTmpBufOptUnionSelector == (0).toByte()) {
                const borderColorTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderColorTmpBufOptBufU : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
                if (borderColorTmpBufOptBufUUnionSelector == (0).toByte()) {
                    borderColorTmpBufOptBufU = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
                } else if (borderColorTmpBufOptBufUUnionSelector == (1).toByte()) {
                    borderColorTmpBufOptBufU = valueDeserializer.readInt32()
                } else if (borderColorTmpBufOptBufUUnionSelector == (2).toByte()) {
                    borderColorTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (borderColorTmpBufOptBufUUnionSelector == (3).toByte()) {
                    borderColorTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for borderColorTmpBufOptBufU has to be chosen through deserialisation.')
                }
                borderColorTmpBufOpt = (borderColorTmpBufOptBufU as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
            } else if (borderColorTmpBufOptUnionSelector == (1).toByte()) {
                borderColorTmpBufOpt = EdgeColors_serializer.read(valueDeserializer)
            } else if (borderColorTmpBufOptUnionSelector == (2).toByte()) {
                borderColorTmpBufOpt = LocalizedEdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderColorTmpBufOpt has to be chosen through deserialisation.')
            }
            borderColorTmpBuf = (borderColorTmpBufOpt as ResourceColor | EdgeColors | LocalizedEdgeColors)
        }
        const borderColorTmpResult : ResourceColor | EdgeColors | LocalizedEdgeColors | undefined = borderColorTmpBuf
        const borderStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderStyleTmpBuf : BorderStyle | EdgeStyles | undefined = undefined
        if ((borderStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderStyleTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderStyleTmpBufOpt : BorderStyle | EdgeStyles | undefined
            if (borderStyleTmpBufOptUnionSelector == (0).toByte()) {
                borderStyleTmpBufOpt = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else if (borderStyleTmpBufOptUnionSelector == (1).toByte()) {
                borderStyleTmpBufOpt = EdgeStyles_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderStyleTmpBufOpt has to be chosen through deserialisation.')
            }
            borderStyleTmpBuf = (borderStyleTmpBufOpt as BorderStyle | EdgeStyles)
        }
        const borderStyleTmpResult : BorderStyle | EdgeStyles | undefined = borderStyleTmpBuf
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
        const levelModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let levelModeTmpBuf : LevelMode | undefined = undefined
        if ((levelModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelModeTmpBuf = LevelMode.fromValue(valueDeserializer.readInt32())
        }
        const levelModeTmpResult : LevelMode | undefined = levelModeTmpBuf
        const levelUniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let levelUniqueIdTmpBuf : int32 | undefined = undefined
        if ((levelUniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelUniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const levelUniqueIdTmpResult : int32 | undefined = levelUniqueIdTmpBuf
        const immersiveModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let immersiveModeTmpBuf : ImmersiveMode | undefined = undefined
        if ((immersiveModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            immersiveModeTmpBuf = ImmersiveMode.fromValue(valueDeserializer.readInt32())
        }
        const immersiveModeTmpResult : ImmersiveMode | undefined = immersiveModeTmpBuf
        const levelOrderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let levelOrderTmpBuf : LevelOrder | undefined = undefined
        if ((levelOrderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelOrderTmpBuf = (LevelOrder_serializer.read(valueDeserializer) as LevelOrder)
        }
        const levelOrderTmpResult : LevelOrder | undefined = levelOrderTmpBuf
        let value : ActionSheetOptions = ({title: titleTmpResult, subtitle: subtitleTmpResult, message: messageTmpResult, confirm: confirmTmpResult, cancel: cancelTmpResult, sheets: sheetsTmpResult, autoCancel: autoCancelTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, maskRect: maskRectTmpResult, showInSubWindow: showInSubWindowTmpResult, isModal: isModalTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onWillDismiss: onWillDismissTmpResult, transition: transitionTmpResult, cornerRadius: cornerRadiusTmpResult, width: widthTmpResult, height: heightTmpResult, borderWidth: borderWidthTmpResult, borderColor: borderColorTmpResult, borderStyle: borderStyleTmpResult, shadow: shadowTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, levelMode: levelModeTmpResult, levelUniqueId: levelUniqueIdTmpResult, immersiveMode: immersiveModeTmpResult, levelOrder: levelOrderTmpResult} as ActionSheetOptions)
        return value
    }
}
