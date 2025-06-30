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

import { ResourceStr, Length, Padding, LocalizedPadding, BorderOptions, EdgeWidths, LocalizedEdgeWidths, ResourceColor, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, EdgeStyles } from "./units"
import { LayoutPolicy } from "./common"
import { BorderStyle, Color } from "./enums"
import { Resource } from "global.resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextFieldOps {
    public static registerTextFieldValueCallback(node: KPointer, value: ResourceStr, callback: TextFieldValueCallback): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (ResourceStr)
        const callback_casted = callback as (TextFieldValueCallback)
        return TextFieldOps.registerTextFieldValueCallback_serialize(node_casted, value_casted, callback_casted)
    }
    public static textFieldOpsSetWidth(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (Length | LayoutPolicy | undefined)
        return TextFieldOps.textFieldOpsSetWidth_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetHeight(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (Length | LayoutPolicy | undefined)
        return TextFieldOps.textFieldOpsSetHeight_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetPadding(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (Padding | Length | LocalizedPadding | undefined)
        return TextFieldOps.textFieldOpsSetPadding_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetMargin(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (Padding | Length | LocalizedPadding | undefined)
        return TextFieldOps.textFieldOpsSetMargin_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetBorder(node: KPointer, value?: BorderOptions): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (BorderOptions | undefined)
        return TextFieldOps.textFieldOpsSetBorder_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetBorderWidth(node: KPointer, value?: Length | EdgeWidths | LocalizedEdgeWidths): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (Length | EdgeWidths | LocalizedEdgeWidths | undefined)
        return TextFieldOps.textFieldOpsSetBorderWidth_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetBorderColor(node: KPointer, value?: ResourceColor | EdgeColors | LocalizedEdgeColors): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (ResourceColor | EdgeColors | LocalizedEdgeColors | undefined)
        return TextFieldOps.textFieldOpsSetBorderColor_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetBorderStyle(node: KPointer, value?: BorderStyle | EdgeStyles): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (BorderStyle | EdgeStyles | undefined)
        return TextFieldOps.textFieldOpsSetBorderStyle_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetBorderRadius(node: KPointer, value?: Length | BorderRadiuses | LocalizedBorderRadiuses): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (Length | BorderRadiuses | LocalizedBorderRadiuses | undefined)
        return TextFieldOps.textFieldOpsSetBorderRadius_serialize(node_casted, value_casted)
    }
    public static textFieldOpsSetBackgroundColor(node: KPointer, value?: ResourceColor): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (ResourceColor | undefined)
        return TextFieldOps.textFieldOpsSetBackgroundColor_serialize(node_casted, value_casted)
    }
    private static registerTextFieldValueCallback_serialize(node: KPointer, value: ResourceStr, callback: TextFieldValueCallback): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_registerTextFieldValueCallback(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetWidth_serialize(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isLayoutPolicy(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LayoutPolicy
                thisSerializer.writeLayoutPolicy(value_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetHeight_serialize(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isLayoutPolicy(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LayoutPolicy
                thisSerializer.writeLayoutPolicy(value_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetHeight(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetPadding_serialize(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Padding
                const value_value_0_top  = value_value_0.top
                let value_value_0_top_type : int32 = RuntimeType.UNDEFINED
                value_value_0_top_type = runtimeType(value_value_0_top)
                thisSerializer.writeInt8(value_value_0_top_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_top_type)) {
                    const value_value_0_top_value  = value_value_0_top!
                    thisSerializer.writeLength(value_value_0_top_value)
                }
                const value_value_0_right  = value_value_0.right
                let value_value_0_right_type : int32 = RuntimeType.UNDEFINED
                value_value_0_right_type = runtimeType(value_value_0_right)
                thisSerializer.writeInt8(value_value_0_right_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_right_type)) {
                    const value_value_0_right_value  = value_value_0_right!
                    thisSerializer.writeLength(value_value_0_right_value)
                }
                const value_value_0_bottom  = value_value_0.bottom
                let value_value_0_bottom_type : int32 = RuntimeType.UNDEFINED
                value_value_0_bottom_type = runtimeType(value_value_0_bottom)
                thisSerializer.writeInt8(value_value_0_bottom_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_bottom_type)) {
                    const value_value_0_bottom_value  = value_value_0_bottom!
                    thisSerializer.writeLength(value_value_0_bottom_value)
                }
                const value_value_0_left  = value_value_0.left
                let value_value_0_left_type : int32 = RuntimeType.UNDEFINED
                value_value_0_left_type = runtimeType(value_value_0_left)
                thisSerializer.writeInt8(value_value_0_left_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_left_type)) {
                    const value_value_0_left_value  = value_value_0_left!
                    thisSerializer.writeLength(value_value_0_left_value)
                }
            }
            else if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Length
                thisSerializer.writeLength(value_value_1)
            }
            else if (TypeChecker.isLocalizedPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedPadding
                thisSerializer.writeLocalizedPadding(value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetPadding(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetMargin_serialize(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Padding
                const value_value_0_top  = value_value_0.top
                let value_value_0_top_type : int32 = RuntimeType.UNDEFINED
                value_value_0_top_type = runtimeType(value_value_0_top)
                thisSerializer.writeInt8(value_value_0_top_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_top_type)) {
                    const value_value_0_top_value  = value_value_0_top!
                    thisSerializer.writeLength(value_value_0_top_value)
                }
                const value_value_0_right  = value_value_0.right
                let value_value_0_right_type : int32 = RuntimeType.UNDEFINED
                value_value_0_right_type = runtimeType(value_value_0_right)
                thisSerializer.writeInt8(value_value_0_right_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_right_type)) {
                    const value_value_0_right_value  = value_value_0_right!
                    thisSerializer.writeLength(value_value_0_right_value)
                }
                const value_value_0_bottom  = value_value_0.bottom
                let value_value_0_bottom_type : int32 = RuntimeType.UNDEFINED
                value_value_0_bottom_type = runtimeType(value_value_0_bottom)
                thisSerializer.writeInt8(value_value_0_bottom_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_bottom_type)) {
                    const value_value_0_bottom_value  = value_value_0_bottom!
                    thisSerializer.writeLength(value_value_0_bottom_value)
                }
                const value_value_0_left  = value_value_0.left
                let value_value_0_left_type : int32 = RuntimeType.UNDEFINED
                value_value_0_left_type = runtimeType(value_value_0_left)
                thisSerializer.writeInt8(value_value_0_left_type as int32)
                if ((RuntimeType.UNDEFINED) != (value_value_0_left_type)) {
                    const value_value_0_left_value  = value_value_0_left!
                    thisSerializer.writeLength(value_value_0_left_value)
                }
            }
            else if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Length
                thisSerializer.writeLength(value_value_1)
            }
            else if (TypeChecker.isLocalizedPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedPadding
                thisSerializer.writeLocalizedPadding(value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetMargin(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorder_serialize(node: KPointer, value?: BorderOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBorderOptions(value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorder(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderWidth_serialize(node: KPointer, value?: Length | EdgeWidths | LocalizedEdgeWidths): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isEdgeWidths(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeWidths
                thisSerializer.writeEdgeWidths(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeWidths(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdgeWidths
                thisSerializer.writeLocalizedEdgeWidths(value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderColor_serialize(node: KPointer, value?: ResourceColor | EdgeColors | LocalizedEdgeColors): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeColors
                thisSerializer.writeEdgeColors(value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedEdgeColors
                thisSerializer.writeLocalizedEdgeColors(value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderStyle_serialize(node: KPointer, value?: BorderStyle | EdgeStyles): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isBorderStyle(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as BorderStyle
                thisSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_value_0))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as EdgeStyles
                thisSerializer.writeEdgeStyles(value_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderStyle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderRadius_serialize(node: KPointer, value?: Length | BorderRadiuses | LocalizedBorderRadiuses): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Length
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as BorderRadiuses
                thisSerializer.writeBorderRadiuses(value_value_1)
            }
            else if (TypeChecker.isLocalizedBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as LocalizedBorderRadiuses
                thisSerializer.writeLocalizedBorderRadiuses(value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderRadius(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBackgroundColor_serialize(node: KPointer, value?: ResourceColor): KPointer {
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
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBackgroundColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export type TextFieldValueCallback = (value: ResourceStr) => void;
