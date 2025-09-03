import { runtimeType, RuntimeType, KPointer } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ColorMetrics, LengthMetrics } from "../Graphics"
import { Font } from "./units"
import { BlurStyle } from "./common"

export class ArcAlphabetIndexerExtender {
    public static SetColor(node: KPointer, color: ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.SetColor_serialize(node_casted, color_casted)
        return
    }
    public static SetSelectedColor(node: KPointer, color: ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.SetSelectedColor_serialize(node_casted, color_casted)
        return
    }
    public static SetPopupColor(node: KPointer, color: ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.SetPopupColor_serialize(node_casted, color_casted)
        return
    }
    public static SetSelectedBackgroundColor(node: KPointer, color: ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.SetSelectedBackgroundColor_serialize(node_casted, color_casted)
        return
    }
    public static SetPopupBackground(node: KPointer, color: ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.SetPopupBackground_serialize(node_casted, color_casted)
        return
    }
    public static SetUsePopup(node: KPointer, enabled: boolean | undefined): void {
        const node_casted = node as (KPointer)
        const enabled_casted = enabled as (boolean | undefined)
        ArcAlphabetIndexerExtender.SetUsePopup_serialize(node_casted, enabled_casted)
        return
    }
    public static SetSelectedFont(node: KPointer, font: Font | undefined): void {
        const node_casted = node as (KPointer)
        const font_casted = font as (Font | undefined)
        ArcAlphabetIndexerExtender.SetSelectedFont_serialize(node_casted, font_casted)
        return
    }
    public static SetPopupFont(node: KPointer, font: Font | undefined): void {
        const node_casted = node as (KPointer)
        const font_casted = font as (Font | undefined)
        ArcAlphabetIndexerExtender.SetPopupFont_serialize(node_casted, font_casted)
        return
    }
    public static SetFont(node: KPointer, font: Font | undefined): void {
        const node_casted = node as (KPointer)
        const font_casted = font as (Font | undefined)
        ArcAlphabetIndexerExtender.SetFont_serialize(node_casted, font_casted)
        return
    }
    public static SetItemSize(node: KPointer, size: LengthMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const size_casted = size as (LengthMetrics | undefined)
        ArcAlphabetIndexerExtender.SetItemSize_serialize(node_casted, size_casted)
        return
    }
    public static SetSelected(node: KPointer, index: number | undefined, bindableCallback: ((value0: number) => void) | undefined): void {
        const node_casted = node as (KPointer)
        const index_casted = index as (number | undefined)
        const bindableCallback_casted = bindableCallback as (((value0: number) => void) | undefined)
        ArcAlphabetIndexerExtender.SetSelected_serialize(node_casted, index_casted, bindableCallback_casted)
        return
    }
    public static SetAutoCollapse(node: KPointer, enable: boolean | undefined): void {
        const node_casted = node as (KPointer)
        const enable_casted = enable as (boolean | undefined)
        ArcAlphabetIndexerExtender.SetAutoCollapse_serialize(node_casted, enable_casted)
        return
    }
    public static SetOnSelect(node: KPointer, handler: ((value0: number) => void) | undefined): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (((value0: number) => void) | undefined)
        ArcAlphabetIndexerExtender.SetOnSelect_serialize(node_casted, handler_casted)
        return
    }
    public static SetPopupBackgroundBlurStyle(node: KPointer, style: BlurStyle | undefined): void {
        const node_casted = node as (KPointer)
        const style_casted = style as (BlurStyle | undefined)
        ArcAlphabetIndexerExtender.SetPopupBackgroundBlurStyle_serialize(node_casted, style_casted)
        return
    }
    public static ArcAlphabetIndexerConstruct(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return ArcAlphabetIndexerExtender.ArcAlphabetIndexerConstruct_serialize(id_casted, flags_casted)
    }
    public static SetConstructInfo(node: KPointer, arrayValue: Array<string>, selected: number, bindableCallback: ((value0: number) => void) | undefined): void {
        const node_casted = node as (KPointer)
        const arrayValue_casted = arrayValue as (Array<string>)
        const selected_casted = selected as (number)
        const bindableCallback_casted = bindableCallback as (((value0: number) => void) | undefined)
        ArcAlphabetIndexerExtender.SetConstructInfo_serialize(node_casted, arrayValue_casted, selected_casted, bindableCallback_casted)
        return
    }
    private static SetColor_serialize(node: KPointer, color: ColorMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        thisSerializer.writeInt8(color_type)
        if ((RuntimeType.UNDEFINED) != (color_type)) {
            const color_value  = color!
            thisSerializer.writeColorMetrics(color_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetSelectedColor_serialize(node: KPointer, color: ColorMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        thisSerializer.writeInt8(color_type)
        if ((RuntimeType.UNDEFINED) != (color_type)) {
            const color_value  = color!
            thisSerializer.writeColorMetrics(color_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetSelectedColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetPopupColor_serialize(node: KPointer, color: ColorMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        thisSerializer.writeInt8(color_type)
        if ((RuntimeType.UNDEFINED) != (color_type)) {
            const color_value  = color!
            thisSerializer.writeColorMetrics(color_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetPopupColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetSelectedBackgroundColor_serialize(node: KPointer, color: ColorMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        thisSerializer.writeInt8(color_type)
        if ((RuntimeType.UNDEFINED) != (color_type)) {
            const color_value  = color!
            thisSerializer.writeColorMetrics(color_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetSelectedBackgroundColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetPopupBackground_serialize(node: KPointer, color: ColorMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        thisSerializer.writeInt8(color_type)
        if ((RuntimeType.UNDEFINED) != (color_type)) {
            const color_value  = color!
            thisSerializer.writeColorMetrics(color_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetPopupBackground(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetUsePopup_serialize(node: KPointer, enabled: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let enabled_type : int32 = RuntimeType.UNDEFINED
        enabled_type = runtimeType(enabled)
        thisSerializer.writeInt8(enabled_type)
        if ((RuntimeType.UNDEFINED) != (enabled_type)) {
            const enabled_value  = enabled!
            thisSerializer.writeBoolean(enabled_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetUsePopup(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetSelectedFont_serialize(node: KPointer, font: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let font_type : int32 = RuntimeType.UNDEFINED
        font_type = runtimeType(font)
        thisSerializer.writeInt8(font_type)
        if ((RuntimeType.UNDEFINED) != (font_type)) {
            const font_value  = font!
            thisSerializer.writeFont(font_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetSelectedFont(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetPopupFont_serialize(node: KPointer, font: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let font_type : int32 = RuntimeType.UNDEFINED
        font_type = runtimeType(font)
        thisSerializer.writeInt8(font_type)
        if ((RuntimeType.UNDEFINED) != (font_type)) {
            const font_value  = font!
            thisSerializer.writeFont(font_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetPopupFont(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetFont_serialize(node: KPointer, font: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let font_type : int32 = RuntimeType.UNDEFINED
        font_type = runtimeType(font)
        thisSerializer.writeInt8(font_type)
        if ((RuntimeType.UNDEFINED) != (font_type)) {
            const font_value  = font!
            thisSerializer.writeFont(font_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetFont(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetItemSize_serialize(node: KPointer, size: LengthMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let size_type : int32 = RuntimeType.UNDEFINED
        size_type = runtimeType(size)
        thisSerializer.writeInt8(size_type)
        if ((RuntimeType.UNDEFINED) != (size_type)) {
            const size_value  = size!
            thisSerializer.writeLengthMetrics(size_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetItemSize(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetSelected_serialize(node: KPointer, index: number | undefined, bindableCallback: ((value0: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        if (index !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const indexTmpValue  = index!
            thisSerializer.writeNumber(indexTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (bindableCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const bindableCallbackTmpValue  = bindableCallback!
            thisSerializer.holdAndWriteCallback(bindableCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetSelected(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetAutoCollapse_serialize(node: KPointer, enable: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let enable_type : int32 = RuntimeType.UNDEFINED
        enable_type = runtimeType(enable)
        thisSerializer.writeInt8(enable_type)
        if ((RuntimeType.UNDEFINED) != (enable_type)) {
            const enable_value  = enable!
            thisSerializer.writeBoolean(enable_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetAutoCollapse(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetOnSelect_serialize(node: KPointer, handler: ((value0: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let handler_type : int32 = RuntimeType.UNDEFINED
        handler_type = runtimeType(handler)
        thisSerializer.writeInt8(handler_type)
        if ((RuntimeType.UNDEFINED) != (handler_type)) {
            const handler_value  = handler!
            thisSerializer.holdAndWriteCallback(handler_value)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetOnSelect(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetPopupBackgroundBlurStyle_serialize(node: KPointer, style: BlurStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as BlurStyle)
            thisSerializer.writeInt32(style_value.valueOf())
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetPopupBackgroundBlurStyle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static ArcAlphabetIndexerConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_ArcAlphabetIndexerConstruct(id, flags)
        return retval
    }
    private static SetConstructInfo_serialize(node: KPointer, arrayValue: Array<string>, selected: number, bindableCallback: ((value0: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32((arrayValue.length).toInt())
        for (let arrayValueCounterI = 0; arrayValueCounterI < arrayValue.length; arrayValueCounterI++) {
            const arrayValueTmpElement : string = arrayValue[arrayValueCounterI]
            thisSerializer.writeString(arrayValueTmpElement)
        }
        if (bindableCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const bindableCallbackTmpValue  = bindableCallback!
            thisSerializer.holdAndWriteCallback(bindableCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_SetConstructInfo(node, thisSerializer.asBuffer(), thisSerializer.length(), selected)
        thisSerializer.release()
    }
}
