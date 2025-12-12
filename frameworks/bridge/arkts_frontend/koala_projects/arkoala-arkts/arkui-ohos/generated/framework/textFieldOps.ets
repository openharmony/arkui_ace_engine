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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { Resource_serializer } from "./resource"
import { LayoutPolicy_serializer, LayoutPolicy, LayoutPolicyInternal } from "./../component/common"
import { Padding_serializer, LocalizedPadding_serializer, BorderOptions_serializer, EdgeWidths_serializer, LocalizedEdgeWidths_serializer, EdgeColors_serializer, LocalizedEdgeColors_serializer, EdgeStyles_serializer, BorderRadiuses_serializer, LocalizedBorderRadiuses_serializer, ResourceStr, Length, Padding, LocalizedPadding, BorderOptions, EdgeWidths, LocalizedEdgeWidths, ResourceColor, EdgeColors, LocalizedEdgeColors, EdgeStyles, BorderRadiuses, LocalizedBorderRadiuses } from "./../component/units"
import { Resource } from "global.resource"
import { Color, BorderStyle } from "./../component/enums"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
export class TextFieldOps {
    static registerTextFieldValueCallback_serialize(node: KPointer, value: ResourceStr, callback: TextFieldValueCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as string
            thisSerializer.writeString(valueForIdx0)
        } else if (value instanceof Resource) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as Resource
            Resource_serializer.write(thisSerializer, valueForIdx1)
        }
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_registerTextFieldValueCallback(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetWidth_serialize(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Length
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof LayoutPolicy) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as LayoutPolicy
                LayoutPolicy_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetHeight_serialize(node: KPointer, value?: Length | LayoutPolicy): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Length
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof LayoutPolicy) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as LayoutPolicy
                LayoutPolicy_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetHeight(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetPadding_serialize(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Padding) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Padding
                Padding_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Length
                if (valueTmpValueForIdx1 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx1ForIdx0  = valueTmpValueForIdx1 as string
                    thisSerializer.writeString(valueTmpValueForIdx1ForIdx0)
                } else if (valueTmpValueForIdx1 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx1ForIdx1  = valueTmpValueForIdx1 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx1ForIdx1)
                } else if (valueTmpValueForIdx1 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx1ForIdx2  = valueTmpValueForIdx1 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx1ForIdx2)
                }
            } else if (valueTmpValue instanceof LocalizedPadding) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as LocalizedPadding
                LocalizedPadding_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetPadding(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetMargin_serialize(node: KPointer, value?: Padding | Length | LocalizedPadding): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Padding) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Padding
                Padding_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Length
                if (valueTmpValueForIdx1 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx1ForIdx0  = valueTmpValueForIdx1 as string
                    thisSerializer.writeString(valueTmpValueForIdx1ForIdx0)
                } else if (valueTmpValueForIdx1 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx1ForIdx1  = valueTmpValueForIdx1 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx1ForIdx1)
                } else if (valueTmpValueForIdx1 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx1ForIdx2  = valueTmpValueForIdx1 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx1ForIdx2)
                }
            } else if (valueTmpValue instanceof LocalizedPadding) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as LocalizedPadding
                LocalizedPadding_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetMargin(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetBorder_serialize(node: KPointer, value?: BorderOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            BorderOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorder(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetBorderWidth_serialize(node: KPointer, value?: Length | EdgeWidths | LocalizedEdgeWidths): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Length
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof EdgeWidths) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as EdgeWidths
                EdgeWidths_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof LocalizedEdgeWidths) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as LocalizedEdgeWidths
                LocalizedEdgeWidths_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetBorderColor_serialize(node: KPointer, value?: ResourceColor | EdgeColors | LocalizedEdgeColors): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ResourceColor) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof Color) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as Color
                    thisSerializer.writeInt32(valueTmpValueForIdx0ForIdx0.getOrdinal())
                } else if (valueTmpValueForIdx0 instanceof int32) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as int32
                    thisSerializer.writeInt32(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof EdgeColors) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as EdgeColors
                EdgeColors_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof LocalizedEdgeColors) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as LocalizedEdgeColors
                LocalizedEdgeColors_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetBorderStyle_serialize(node: KPointer, value?: BorderStyle | EdgeStyles): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof BorderStyle) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as BorderStyle
                thisSerializer.writeInt32(valueTmpValueForIdx0.valueOf())
            } else if (valueTmpValue instanceof EdgeStyles) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as EdgeStyles
                EdgeStyles_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderStyle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetBorderRadius_serialize(node: KPointer, value?: Length | BorderRadiuses | LocalizedBorderRadiuses): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Length
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as double
                    thisSerializer.writeFloat64(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof BorderRadiuses) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof LocalizedBorderRadiuses) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as LocalizedBorderRadiuses
                LocalizedBorderRadiuses_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_textFieldOpsSetBorderRadius(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static textFieldOpsSetBackgroundColor_serialize(node: KPointer, value?: ResourceColor): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
