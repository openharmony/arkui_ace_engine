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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { LayoutPolicy_serializer, LayoutPolicy, LayoutPolicyInternal } from "./../component/common"
import { Padding_serializer, LocalizedPadding_serializer, BorderOptions_serializer, EdgeWidths_serializer, LocalizedEdgeWidths_serializer, EdgeColors_serializer, LocalizedEdgeColors_serializer, EdgeStyles_serializer, BorderRadiuses_serializer, LocalizedBorderRadiuses_serializer, ResourceStr, Length, Padding, LocalizedPadding, BorderOptions, EdgeWidths, LocalizedEdgeWidths, ResourceColor, EdgeColors, LocalizedEdgeColors, EdgeStyles, BorderRadiuses, LocalizedBorderRadiuses } from "./../component/units"
import { Color, BorderStyle } from "./../component/enums"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class TextFieldOps {
    private static registerTextFieldValueCallback_serialize(node: KPointer, value: ResourceStr, callback: TextFieldValueCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as Resource
            Resource_serializer.write(thisSerializer, value_1)
        }
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_registerTextFieldValueCallback(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetWidth_serialize(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Length
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_2)
                }
            }
            else if (TypeChecker.isLayoutPolicy(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as LayoutPolicy
                LayoutPolicy_serializer.write(thisSerializer, value_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetHeight_serialize(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Length
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_2)
                }
            }
            else if (TypeChecker.isLayoutPolicy(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as LayoutPolicy
                LayoutPolicy_serializer.write(thisSerializer, value_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetHeight(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetPadding_serialize(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Padding
                Padding_serializer.write(thisSerializer, value_value_0)
            }
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Length
                let value_value_1_type : int32 = RuntimeType.UNDEFINED
                value_value_1_type = runtimeType(value_value_1)
                if (RuntimeType.STRING == value_value_1_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_1_0  = value_value_1 as string
                    thisSerializer.writeString(value_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_value_1_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_1_1  = value_value_1 as number
                    thisSerializer.writeNumber(value_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_value_1_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_1_2  = value_value_1 as Resource
                    Resource_serializer.write(thisSerializer, value_value_1_2)
                }
            }
            else if (TypeChecker.isLocalizedPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as LocalizedPadding
                LocalizedPadding_serializer.write(thisSerializer, value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetPadding(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetMargin_serialize(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Padding
                Padding_serializer.write(thisSerializer, value_value_0)
            }
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Length
                let value_value_1_type : int32 = RuntimeType.UNDEFINED
                value_value_1_type = runtimeType(value_value_1)
                if (RuntimeType.STRING == value_value_1_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_1_0  = value_value_1 as string
                    thisSerializer.writeString(value_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_value_1_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_1_1  = value_value_1 as number
                    thisSerializer.writeNumber(value_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_value_1_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_1_2  = value_value_1 as Resource
                    Resource_serializer.write(thisSerializer, value_value_1_2)
                }
            }
            else if (TypeChecker.isLocalizedPadding(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as LocalizedPadding
                LocalizedPadding_serializer.write(thisSerializer, value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetMargin(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorder_serialize(node: KPointer, value?: BorderOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            BorderOptions_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorder(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderWidth_serialize(node: KPointer, value?: Length | EdgeWidths | LocalizedEdgeWidths): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Length
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_2)
                }
            }
            else if (TypeChecker.isEdgeWidths(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as EdgeWidths
                EdgeWidths_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeWidths(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(thisSerializer, value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderColor_serialize(node: KPointer, value?: ResourceColor | EdgeColors | LocalizedEdgeColors): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((3).toChar())
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as EdgeColors
                EdgeColors_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isLocalizedEdgeColors(value_value, true, false, true, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(thisSerializer, value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderStyle_serialize(node: KPointer, value?: BorderStyle | EdgeStyles): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isBorderStyle(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as BorderStyle
                thisSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_value_0))
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as EdgeStyles
                EdgeStyles_serializer.write(thisSerializer, value_value_1)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderStyle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBorderRadius_serialize(node: KPointer, value?: Length | BorderRadiuses | LocalizedBorderRadiuses): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Length
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_2)
                }
            }
            else if (TypeChecker.isBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as BorderRadiuses
                BorderRadiuses_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isLocalizedBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(thisSerializer, value_value_2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderRadius(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static textFieldOpsSetBackgroundColor_serialize(node: KPointer, value?: ResourceColor): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBackgroundColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
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
}
export type TextFieldValueCallback = (value: ResourceStr) => void;
