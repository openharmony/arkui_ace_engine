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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { DismissDialogAction, DismissDialogAction_serializer } from "./actionSheet"
import { CustomBuilder } from "./builder"
import { ExtendableComponent, ExtendableComponent_serializer } from "./extendableComponent"
import { DialogAlignment } from "./alertDialog"
import { Offset, ResourceColor, Dimension, BorderRadiuses, EdgeWidths, EdgeColors, EdgeStyles, Offset_serializer, BorderRadiuses_serializer, EdgeWidths_serializer, EdgeColors_serializer, EdgeStyles_serializer } from "./units"
import { Color, BorderStyle } from "./enums"
import { Resource, Resource_serializer } from "./../generated/resource"
import { Rectangle, AnimateParam, ShadowOptions, ShadowStyle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, KeyboardAvoidMode, HoverModeAreaType, Rectangle_serializer, AnimateParam_serializer, ShadowOptions_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer } from "./common"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { LevelMode, ImmersiveMode, LevelOrder, LevelOrder_serializer } from "./../generated/ohos.promptAction"
export class CustomDialogControllerInternal {
    public static fromPtr(ptr: KPointer): CustomDialogController {
        return new CustomDialogController(false, ptr)
    }
}
export class CustomDialogController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CustomDialogController.getFinalizer())
    }
    constructor(value: CustomDialogControllerOptions) {
        this(false, CustomDialogController.construct(value))
    }
    static construct(value: CustomDialogControllerOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CustomDialogControllerOptions_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._CustomDialogController_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CustomDialogController_getFinalizer()
    }
    public open(): void {
        this.open_serialize()
        return
    }
    public close(): void {
        this.close_serialize()
        return
    }
    private open_serialize(): void {
        ArkUIGeneratedNativeModule._CustomDialogController_open(this.peer!.ptr)
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._CustomDialogController_close(this.peer!.ptr)
    }
}
export interface CustomDialogControllerOptions {
    builder: CustomBuilder | ExtendableComponent;
    cancel?: (() => void);
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: Offset;
    customStyle?: boolean;
    gridCount?: number;
    maskColor?: ResourceColor;
    maskRect?: Rectangle;
    openAnimation?: AnimateParam;
    closeAnimation?: AnimateParam;
    showInSubWindow?: boolean;
    backgroundColor?: ResourceColor;
    cornerRadius?: Dimension | BorderRadiuses;
    isModal?: boolean;
    onWillDismiss?: ((value0: DismissDialogAction) => void);
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths;
    borderColor?: ResourceColor | EdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    keyboardAvoidMode?: KeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    keyboardAvoidDistance?: LengthMetrics;
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
    focusable?: boolean;
}
export class CustomDialogController_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CustomDialogController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CustomDialogControllerInternal.fromPtr(ptr)
    }
}
export class CustomDialogControllerOptions_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogControllerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_builder  = value.builder
        let value_builder_type : int32 = RuntimeType.UNDEFINED
        value_builder_type = runtimeType(value_builder)
        if (RuntimeType.FUNCTION == value_builder_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_builder_0  = value_builder as CustomBuilder
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_builder_0))
        }
        else if (RuntimeType.OBJECT == value_builder_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_builder_1  = value_builder as ExtendableComponent
            ExtendableComponent_serializer.write(valueSerializer, value_builder_1)
        }
        const value_cancel  = value.cancel
        let value_cancel_type : int32 = RuntimeType.UNDEFINED
        value_cancel_type = runtimeType(value_cancel)
        valueSerializer.writeInt8((value_cancel_type).toChar())
        if ((value_cancel_type) != (RuntimeType.UNDEFINED)) {
            const value_cancel_value  = value_cancel!
            valueSerializer.holdAndWriteCallback(value_cancel_value)
        }
        const value_autoCancel  = value.autoCancel
        let value_autoCancel_type : int32 = RuntimeType.UNDEFINED
        value_autoCancel_type = runtimeType(value_autoCancel)
        valueSerializer.writeInt8((value_autoCancel_type).toChar())
        if ((value_autoCancel_type) != (RuntimeType.UNDEFINED)) {
            const value_autoCancel_value  = value_autoCancel!
            valueSerializer.writeBoolean(value_autoCancel_value)
        }
        const value_alignment  = value.alignment
        let value_alignment_type : int32 = RuntimeType.UNDEFINED
        value_alignment_type = runtimeType(value_alignment)
        valueSerializer.writeInt8((value_alignment_type).toChar())
        if ((value_alignment_type) != (RuntimeType.UNDEFINED)) {
            const value_alignment_value  = (value_alignment as DialogAlignment)
            valueSerializer.writeInt32(TypeChecker.DialogAlignment_ToNumeric(value_alignment_value))
        }
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        valueSerializer.writeInt8((value_offset_type).toChar())
        if ((value_offset_type) != (RuntimeType.UNDEFINED)) {
            const value_offset_value  = value_offset!
            Offset_serializer.write(valueSerializer, value_offset_value)
        }
        const value_customStyle  = value.customStyle
        let value_customStyle_type : int32 = RuntimeType.UNDEFINED
        value_customStyle_type = runtimeType(value_customStyle)
        valueSerializer.writeInt8((value_customStyle_type).toChar())
        if ((value_customStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_customStyle_value  = value_customStyle!
            valueSerializer.writeBoolean(value_customStyle_value)
        }
        const value_gridCount  = value.gridCount
        let value_gridCount_type : int32 = RuntimeType.UNDEFINED
        value_gridCount_type = runtimeType(value_gridCount)
        valueSerializer.writeInt8((value_gridCount_type).toChar())
        if ((value_gridCount_type) != (RuntimeType.UNDEFINED)) {
            const value_gridCount_value  = value_gridCount!
            valueSerializer.writeNumber(value_gridCount_value)
        }
        const value_maskColor  = value.maskColor
        let value_maskColor_type : int32 = RuntimeType.UNDEFINED
        value_maskColor_type = runtimeType(value_maskColor)
        valueSerializer.writeInt8((value_maskColor_type).toChar())
        if ((value_maskColor_type) != (RuntimeType.UNDEFINED)) {
            const value_maskColor_value  = value_maskColor!
            let value_maskColor_value_type : int32 = RuntimeType.UNDEFINED
            value_maskColor_value_type = runtimeType(value_maskColor_value)
            if (TypeChecker.isColor(value_maskColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_maskColor_value_0  = value_maskColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_maskColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_maskColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_maskColor_value_1  = value_maskColor_value as number
                valueSerializer.writeNumber(value_maskColor_value_1)
            }
            else if (RuntimeType.STRING == value_maskColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_maskColor_value_2  = value_maskColor_value as string
                valueSerializer.writeString(value_maskColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_maskColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_maskColor_value_3  = value_maskColor_value as Resource
                Resource_serializer.write(valueSerializer, value_maskColor_value_3)
            }
        }
        const value_maskRect  = value.maskRect
        let value_maskRect_type : int32 = RuntimeType.UNDEFINED
        value_maskRect_type = runtimeType(value_maskRect)
        valueSerializer.writeInt8((value_maskRect_type).toChar())
        if ((value_maskRect_type) != (RuntimeType.UNDEFINED)) {
            const value_maskRect_value  = value_maskRect!
            Rectangle_serializer.write(valueSerializer, value_maskRect_value)
        }
        const value_openAnimation  = value.openAnimation
        let value_openAnimation_type : int32 = RuntimeType.UNDEFINED
        value_openAnimation_type = runtimeType(value_openAnimation)
        valueSerializer.writeInt8((value_openAnimation_type).toChar())
        if ((value_openAnimation_type) != (RuntimeType.UNDEFINED)) {
            const value_openAnimation_value  = value_openAnimation!
            AnimateParam_serializer.write(valueSerializer, value_openAnimation_value)
        }
        const value_closeAnimation  = value.closeAnimation
        let value_closeAnimation_type : int32 = RuntimeType.UNDEFINED
        value_closeAnimation_type = runtimeType(value_closeAnimation)
        valueSerializer.writeInt8((value_closeAnimation_type).toChar())
        if ((value_closeAnimation_type) != (RuntimeType.UNDEFINED)) {
            const value_closeAnimation_value  = value_closeAnimation!
            AnimateParam_serializer.write(valueSerializer, value_closeAnimation_value)
        }
        const value_showInSubWindow  = value.showInSubWindow
        let value_showInSubWindow_type : int32 = RuntimeType.UNDEFINED
        value_showInSubWindow_type = runtimeType(value_showInSubWindow)
        valueSerializer.writeInt8((value_showInSubWindow_type).toChar())
        if ((value_showInSubWindow_type) != (RuntimeType.UNDEFINED)) {
            const value_showInSubWindow_value  = value_showInSubWindow!
            valueSerializer.writeBoolean(value_showInSubWindow_value)
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
        const value_cornerRadius  = value.cornerRadius
        let value_cornerRadius_type : int32 = RuntimeType.UNDEFINED
        value_cornerRadius_type = runtimeType(value_cornerRadius)
        valueSerializer.writeInt8((value_cornerRadius_type).toChar())
        if ((value_cornerRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_cornerRadius_value  = value_cornerRadius!
            let value_cornerRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_cornerRadius_value_type = runtimeType(value_cornerRadius_value)
            if ((RuntimeType.STRING == value_cornerRadius_value_type) || (RuntimeType.NUMBER == value_cornerRadius_value_type) || (RuntimeType.OBJECT == value_cornerRadius_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_cornerRadius_value_0  = value_cornerRadius_value as Dimension
                let value_cornerRadius_value_0_type : int32 = RuntimeType.UNDEFINED
                value_cornerRadius_value_0_type = runtimeType(value_cornerRadius_value_0)
                if (RuntimeType.STRING == value_cornerRadius_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_cornerRadius_value_0_0  = value_cornerRadius_value_0 as string
                    valueSerializer.writeString(value_cornerRadius_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_cornerRadius_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_cornerRadius_value_0_1  = value_cornerRadius_value_0 as number
                    valueSerializer.writeNumber(value_cornerRadius_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_cornerRadius_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_cornerRadius_value_0_2  = value_cornerRadius_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_cornerRadius_value_0_2)
                }
            }
            else if (TypeChecker.isBorderRadiuses(value_cornerRadius_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_cornerRadius_value_1  = value_cornerRadius_value as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, value_cornerRadius_value_1)
            }
        }
        const value_isModal  = value.isModal
        let value_isModal_type : int32 = RuntimeType.UNDEFINED
        value_isModal_type = runtimeType(value_isModal)
        valueSerializer.writeInt8((value_isModal_type).toChar())
        if ((value_isModal_type) != (RuntimeType.UNDEFINED)) {
            const value_isModal_value  = value_isModal!
            valueSerializer.writeBoolean(value_isModal_value)
        }
        const value_onWillDismiss  = value.onWillDismiss
        let value_onWillDismiss_type : int32 = RuntimeType.UNDEFINED
        value_onWillDismiss_type = runtimeType(value_onWillDismiss)
        valueSerializer.writeInt8((value_onWillDismiss_type).toChar())
        if ((value_onWillDismiss_type) != (RuntimeType.UNDEFINED)) {
            const value_onWillDismiss_value  = value_onWillDismiss!
            valueSerializer.holdAndWriteCallback(value_onWillDismiss_value)
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as string
                valueSerializer.writeString(value_width_value_0)
            }
            else if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_1)
            }
            else if (RuntimeType.OBJECT == value_width_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_width_value_2  = value_width_value as Resource
                Resource_serializer.write(valueSerializer, value_width_value_2)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as string
                valueSerializer.writeString(value_height_value_0)
            }
            else if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_1)
            }
            else if (RuntimeType.OBJECT == value_height_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_height_value_2  = value_height_value as Resource
                Resource_serializer.write(valueSerializer, value_height_value_2)
            }
        }
        const value_borderWidth  = value.borderWidth
        let value_borderWidth_type : int32 = RuntimeType.UNDEFINED
        value_borderWidth_type = runtimeType(value_borderWidth)
        valueSerializer.writeInt8((value_borderWidth_type).toChar())
        if ((value_borderWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_borderWidth_value  = value_borderWidth!
            let value_borderWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_borderWidth_value_type = runtimeType(value_borderWidth_value)
            if ((RuntimeType.STRING == value_borderWidth_value_type) || (RuntimeType.NUMBER == value_borderWidth_value_type) || (RuntimeType.OBJECT == value_borderWidth_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderWidth_value_0  = value_borderWidth_value as Dimension
                let value_borderWidth_value_0_type : int32 = RuntimeType.UNDEFINED
                value_borderWidth_value_0_type = runtimeType(value_borderWidth_value_0)
                if (RuntimeType.STRING == value_borderWidth_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_borderWidth_value_0_0  = value_borderWidth_value_0 as string
                    valueSerializer.writeString(value_borderWidth_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_borderWidth_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_borderWidth_value_0_1  = value_borderWidth_value_0 as number
                    valueSerializer.writeNumber(value_borderWidth_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_borderWidth_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_borderWidth_value_0_2  = value_borderWidth_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_borderWidth_value_0_2)
                }
            }
            else if (TypeChecker.isEdgeWidths(value_borderWidth_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderWidth_value_1  = value_borderWidth_value as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, value_borderWidth_value_1)
            }
        }
        const value_borderColor  = value.borderColor
        let value_borderColor_type : int32 = RuntimeType.UNDEFINED
        value_borderColor_type = runtimeType(value_borderColor)
        valueSerializer.writeInt8((value_borderColor_type).toChar())
        if ((value_borderColor_type) != (RuntimeType.UNDEFINED)) {
            const value_borderColor_value  = value_borderColor!
            let value_borderColor_value_type : int32 = RuntimeType.UNDEFINED
            value_borderColor_value_type = runtimeType(value_borderColor_value)
            if ((TypeChecker.isColor(value_borderColor_value)) || (RuntimeType.NUMBER == value_borderColor_value_type) || (RuntimeType.STRING == value_borderColor_value_type) || (RuntimeType.OBJECT == value_borderColor_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderColor_value_0  = value_borderColor_value as ResourceColor
                let value_borderColor_value_0_type : int32 = RuntimeType.UNDEFINED
                value_borderColor_value_0_type = runtimeType(value_borderColor_value_0)
                if (TypeChecker.isColor(value_borderColor_value_0)) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_borderColor_value_0_0  = value_borderColor_value_0 as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_borderColor_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_borderColor_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_borderColor_value_0_1  = value_borderColor_value_0 as number
                    valueSerializer.writeNumber(value_borderColor_value_0_1)
                }
                else if (RuntimeType.STRING == value_borderColor_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_borderColor_value_0_2  = value_borderColor_value_0 as string
                    valueSerializer.writeString(value_borderColor_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_borderColor_value_0_type) {
                    valueSerializer.writeInt8((3).toChar())
                    const value_borderColor_value_0_3  = value_borderColor_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_borderColor_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_borderColor_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderColor_value_1  = value_borderColor_value as EdgeColors
                EdgeColors_serializer.write(valueSerializer, value_borderColor_value_1)
            }
        }
        const value_borderStyle  = value.borderStyle
        let value_borderStyle_type : int32 = RuntimeType.UNDEFINED
        value_borderStyle_type = runtimeType(value_borderStyle)
        valueSerializer.writeInt8((value_borderStyle_type).toChar())
        if ((value_borderStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_borderStyle_value  = value_borderStyle!
            let value_borderStyle_value_type : int32 = RuntimeType.UNDEFINED
            value_borderStyle_value_type = runtimeType(value_borderStyle_value)
            if (TypeChecker.isBorderStyle(value_borderStyle_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderStyle_value_0  = value_borderStyle_value as BorderStyle
                valueSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(value_borderStyle_value_0))
            }
            else if (RuntimeType.OBJECT == value_borderStyle_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderStyle_value_1  = value_borderStyle_value as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, value_borderStyle_value_1)
            }
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
        const value_keyboardAvoidMode  = value.keyboardAvoidMode
        let value_keyboardAvoidMode_type : int32 = RuntimeType.UNDEFINED
        value_keyboardAvoidMode_type = runtimeType(value_keyboardAvoidMode)
        valueSerializer.writeInt8((value_keyboardAvoidMode_type).toChar())
        if ((value_keyboardAvoidMode_type) != (RuntimeType.UNDEFINED)) {
            const value_keyboardAvoidMode_value  = (value_keyboardAvoidMode as KeyboardAvoidMode)
            valueSerializer.writeInt32(TypeChecker.KeyboardAvoidMode_ToNumeric(value_keyboardAvoidMode_value))
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
        const value_keyboardAvoidDistance  = value.keyboardAvoidDistance
        let value_keyboardAvoidDistance_type : int32 = RuntimeType.UNDEFINED
        value_keyboardAvoidDistance_type = runtimeType(value_keyboardAvoidDistance)
        valueSerializer.writeInt8((value_keyboardAvoidDistance_type).toChar())
        if ((value_keyboardAvoidDistance_type) != (RuntimeType.UNDEFINED)) {
            const value_keyboardAvoidDistance_value  = value_keyboardAvoidDistance!
            LengthMetrics_serializer.write(valueSerializer, value_keyboardAvoidDistance_value)
        }
        const value_levelMode  = value.levelMode
        let value_levelMode_type : int32 = RuntimeType.UNDEFINED
        value_levelMode_type = runtimeType(value_levelMode)
        valueSerializer.writeInt8((value_levelMode_type).toChar())
        if ((value_levelMode_type) != (RuntimeType.UNDEFINED)) {
            const value_levelMode_value  = (value_levelMode as LevelMode)
            valueSerializer.writeInt32(TypeChecker.LevelMode_ToNumeric(value_levelMode_value))
        }
        const value_levelUniqueId  = value.levelUniqueId
        let value_levelUniqueId_type : int32 = RuntimeType.UNDEFINED
        value_levelUniqueId_type = runtimeType(value_levelUniqueId)
        valueSerializer.writeInt8((value_levelUniqueId_type).toChar())
        if ((value_levelUniqueId_type) != (RuntimeType.UNDEFINED)) {
            const value_levelUniqueId_value  = value_levelUniqueId!
            valueSerializer.writeNumber(value_levelUniqueId_value)
        }
        const value_immersiveMode  = value.immersiveMode
        let value_immersiveMode_type : int32 = RuntimeType.UNDEFINED
        value_immersiveMode_type = runtimeType(value_immersiveMode)
        valueSerializer.writeInt8((value_immersiveMode_type).toChar())
        if ((value_immersiveMode_type) != (RuntimeType.UNDEFINED)) {
            const value_immersiveMode_value  = (value_immersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(TypeChecker.ImmersiveMode_ToNumeric(value_immersiveMode_value))
        }
        const value_levelOrder  = value.levelOrder
        let value_levelOrder_type : int32 = RuntimeType.UNDEFINED
        value_levelOrder_type = runtimeType(value_levelOrder)
        valueSerializer.writeInt8((value_levelOrder_type).toChar())
        if ((value_levelOrder_type) != (RuntimeType.UNDEFINED)) {
            const value_levelOrder_value  = value_levelOrder!
            LevelOrder_serializer.write(valueSerializer, value_levelOrder_value)
        }
        const value_focusable  = value.focusable
        let value_focusable_type : int32 = RuntimeType.UNDEFINED
        value_focusable_type = runtimeType(value_focusable)
        valueSerializer.writeInt8((value_focusable_type).toChar())
        if ((value_focusable_type) != (RuntimeType.UNDEFINED)) {
            const value_focusable_value  = value_focusable!
            valueSerializer.writeBoolean(value_focusable_value)
        }
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const builder_buf_selector : int32 = valueDeserializer.readInt8()
        let builder_buf : CustomBuilder | ExtendableComponent | undefined
        if (builder_buf_selector == (0).toChar()) {
            const builder_buf_u_resource : CallbackResource = valueDeserializer.readCallbackResource()
            const builder_buf_u_call : KPointer = valueDeserializer.readPointer()
            const builder_buf_u_callSync : KPointer = valueDeserializer.readPointer()
            builder_buf = ():void => { 
    const builder_buf_u_argsSerializer : SerializerBase = SerializerBase.hold();
    builder_buf_u_argsSerializer.writeInt32(builder_buf_u_resource.resourceId);
    builder_buf_u_argsSerializer.writePointer(builder_buf_u_call);
    builder_buf_u_argsSerializer.writePointer(builder_buf_u_callSync);
    InteropNativeModule._CallCallback(737226752, builder_buf_u_argsSerializer.asBuffer(), builder_buf_u_argsSerializer.length());
    builder_buf_u_argsSerializer.release();
    return; }
        }
        else if (builder_buf_selector == (1).toChar()) {
            builder_buf = (ExtendableComponent_serializer.read(valueDeserializer) as ExtendableComponent)
        }
        else {
            throw new Error("One of the branches for builder_buf has to be chosen through deserialisation.")
        }
        const builder_result : CustomBuilder | ExtendableComponent = (builder_buf as CustomBuilder | ExtendableComponent)
        const cancel_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancel_buf : (() => void) | undefined
        if ((cancel_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const cancel_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const cancel_buf__call : KPointer = valueDeserializer.readPointer()
            const cancel_buf__callSync : KPointer = valueDeserializer.readPointer()
            cancel_buf = ():void => { 
    const cancel_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    cancel_buf__argsSerializer.writeInt32(cancel_buf__resource.resourceId);
    cancel_buf__argsSerializer.writePointer(cancel_buf__call);
    cancel_buf__argsSerializer.writePointer(cancel_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, cancel_buf__argsSerializer.asBuffer(), cancel_buf__argsSerializer.length());
    cancel_buf__argsSerializer.release();
    return; }
        }
        const cancel_result : (() => void) | undefined = cancel_buf
        const autoCancel_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoCancel_buf : boolean | undefined
        if ((autoCancel_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            autoCancel_buf = valueDeserializer.readBoolean()
        }
        const autoCancel_result : boolean | undefined = autoCancel_buf
        const alignment_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignment_buf : DialogAlignment | undefined
        if ((alignment_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            alignment_buf = TypeChecker.DialogAlignment_FromNumeric(valueDeserializer.readInt32())
        }
        const alignment_result : DialogAlignment | undefined = alignment_buf
        const offset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offset_buf : Offset | undefined
        if ((offset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            offset_buf = Offset_serializer.read(valueDeserializer)
        }
        const offset_result : Offset | undefined = offset_buf
        const customStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let customStyle_buf : boolean | undefined
        if ((customStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            customStyle_buf = valueDeserializer.readBoolean()
        }
        const customStyle_result : boolean | undefined = customStyle_buf
        const gridCount_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gridCount_buf : number | undefined
        if ((gridCount_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            gridCount_buf = (valueDeserializer.readNumber() as number)
        }
        const gridCount_result : number | undefined = gridCount_buf
        const maskColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskColor_buf : ResourceColor | undefined
        if ((maskColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const maskColor_buf__selector : int32 = valueDeserializer.readInt8()
            let maskColor_buf_ : Color | number | string | Resource | undefined
            if (maskColor_buf__selector == (0).toChar()) {
                maskColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (maskColor_buf__selector == (1).toChar()) {
                maskColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (maskColor_buf__selector == (2).toChar()) {
                maskColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (maskColor_buf__selector == (3).toChar()) {
                maskColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for maskColor_buf_ has to be chosen through deserialisation.")
            }
            maskColor_buf = (maskColor_buf_ as Color | number | string | Resource)
        }
        const maskColor_result : ResourceColor | undefined = maskColor_buf
        const maskRect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRect_buf : Rectangle | undefined
        if ((maskRect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maskRect_buf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRect_result : Rectangle | undefined = maskRect_buf
        const openAnimation_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let openAnimation_buf : AnimateParam | undefined
        if ((openAnimation_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            openAnimation_buf = AnimateParam_serializer.read(valueDeserializer)
        }
        const openAnimation_result : AnimateParam | undefined = openAnimation_buf
        const closeAnimation_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let closeAnimation_buf : AnimateParam | undefined
        if ((closeAnimation_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            closeAnimation_buf = AnimateParam_serializer.read(valueDeserializer)
        }
        const closeAnimation_result : AnimateParam | undefined = closeAnimation_buf
        const showInSubWindow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showInSubWindow_buf : boolean | undefined
        if ((showInSubWindow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            showInSubWindow_buf = valueDeserializer.readBoolean()
        }
        const showInSubWindow_result : boolean | undefined = showInSubWindow_buf
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
        const cornerRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cornerRadius_buf : Dimension | BorderRadiuses | undefined
        if ((cornerRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const cornerRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let cornerRadius_buf_ : Dimension | BorderRadiuses | undefined
            if (cornerRadius_buf__selector == (0).toChar()) {
                const cornerRadius_buf__u_selector : int32 = valueDeserializer.readInt8()
                let cornerRadius_buf__u : string | number | Resource | undefined
                if (cornerRadius_buf__u_selector == (0).toChar()) {
                    cornerRadius_buf__u = (valueDeserializer.readString() as string)
                }
                else if (cornerRadius_buf__u_selector == (1).toChar()) {
                    cornerRadius_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (cornerRadius_buf__u_selector == (2).toChar()) {
                    cornerRadius_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for cornerRadius_buf__u has to be chosen through deserialisation.")
                }
                cornerRadius_buf_ = (cornerRadius_buf__u as string | number | Resource)
            }
            else if (cornerRadius_buf__selector == (1).toChar()) {
                cornerRadius_buf_ = BorderRadiuses_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for cornerRadius_buf_ has to be chosen through deserialisation.")
            }
            cornerRadius_buf = (cornerRadius_buf_ as Dimension | BorderRadiuses)
        }
        const cornerRadius_result : Dimension | BorderRadiuses | undefined = cornerRadius_buf
        const isModal_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isModal_buf : boolean | undefined
        if ((isModal_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isModal_buf = valueDeserializer.readBoolean()
        }
        const isModal_result : boolean | undefined = isModal_buf
        const onWillDismiss_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDismiss_buf : ((value0: DismissDialogAction) => void) | undefined
        if ((onWillDismiss_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onWillDismiss_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismiss_buf__call : KPointer = valueDeserializer.readPointer()
            const onWillDismiss_buf__callSync : KPointer = valueDeserializer.readPointer()
            onWillDismiss_buf = (value0: DismissDialogAction):void => { 
    const onWillDismiss_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onWillDismiss_buf__argsSerializer.writeInt32(onWillDismiss_buf__resource.resourceId);
    onWillDismiss_buf__argsSerializer.writePointer(onWillDismiss_buf__call);
    onWillDismiss_buf__argsSerializer.writePointer(onWillDismiss_buf__callSync);
    DismissDialogAction_serializer.write(onWillDismiss_buf__argsSerializer, value0);
    InteropNativeModule._CallCallback(-2095828093, onWillDismiss_buf__argsSerializer.asBuffer(), onWillDismiss_buf__argsSerializer.length());
    onWillDismiss_buf__argsSerializer.release();
    return; }
        }
        const onWillDismiss_result : ((value0: DismissDialogAction) => void) | undefined = onWillDismiss_buf
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : Dimension | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : string | number | Resource | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (2).toChar()) {
                width_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as string | number | Resource)
        }
        const width_result : Dimension | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : Dimension | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : string | number | Resource | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (2).toChar()) {
                height_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as string | number | Resource)
        }
        const height_result : Dimension | undefined = height_buf
        const borderWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidth_buf : Dimension | EdgeWidths | undefined
        if ((borderWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let borderWidth_buf_ : Dimension | EdgeWidths | undefined
            if (borderWidth_buf__selector == (0).toChar()) {
                const borderWidth_buf__u_selector : int32 = valueDeserializer.readInt8()
                let borderWidth_buf__u : string | number | Resource | undefined
                if (borderWidth_buf__u_selector == (0).toChar()) {
                    borderWidth_buf__u = (valueDeserializer.readString() as string)
                }
                else if (borderWidth_buf__u_selector == (1).toChar()) {
                    borderWidth_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (borderWidth_buf__u_selector == (2).toChar()) {
                    borderWidth_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for borderWidth_buf__u has to be chosen through deserialisation.")
                }
                borderWidth_buf_ = (borderWidth_buf__u as string | number | Resource)
            }
            else if (borderWidth_buf__selector == (1).toChar()) {
                borderWidth_buf_ = EdgeWidths_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderWidth_buf_ has to be chosen through deserialisation.")
            }
            borderWidth_buf = (borderWidth_buf_ as Dimension | EdgeWidths)
        }
        const borderWidth_result : Dimension | EdgeWidths | undefined = borderWidth_buf
        const borderColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColor_buf : ResourceColor | EdgeColors | undefined
        if ((borderColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderColor_buf__selector : int32 = valueDeserializer.readInt8()
            let borderColor_buf_ : ResourceColor | EdgeColors | undefined
            if (borderColor_buf__selector == (0).toChar()) {
                const borderColor_buf__u_selector : int32 = valueDeserializer.readInt8()
                let borderColor_buf__u : Color | number | string | Resource | undefined
                if (borderColor_buf__u_selector == (0).toChar()) {
                    borderColor_buf__u = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                }
                else if (borderColor_buf__u_selector == (1).toChar()) {
                    borderColor_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (borderColor_buf__u_selector == (2).toChar()) {
                    borderColor_buf__u = (valueDeserializer.readString() as string)
                }
                else if (borderColor_buf__u_selector == (3).toChar()) {
                    borderColor_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for borderColor_buf__u has to be chosen through deserialisation.")
                }
                borderColor_buf_ = (borderColor_buf__u as Color | number | string | Resource)
            }
            else if (borderColor_buf__selector == (1).toChar()) {
                borderColor_buf_ = EdgeColors_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderColor_buf_ has to be chosen through deserialisation.")
            }
            borderColor_buf = (borderColor_buf_ as ResourceColor | EdgeColors)
        }
        const borderColor_result : ResourceColor | EdgeColors | undefined = borderColor_buf
        const borderStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderStyle_buf : BorderStyle | EdgeStyles | undefined
        if ((borderStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderStyle_buf__selector : int32 = valueDeserializer.readInt8()
            let borderStyle_buf_ : BorderStyle | EdgeStyles | undefined
            if (borderStyle_buf__selector == (0).toChar()) {
                borderStyle_buf_ = TypeChecker.BorderStyle_FromNumeric(valueDeserializer.readInt32())
            }
            else if (borderStyle_buf__selector == (1).toChar()) {
                borderStyle_buf_ = EdgeStyles_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderStyle_buf_ has to be chosen through deserialisation.")
            }
            borderStyle_buf = (borderStyle_buf_ as BorderStyle | EdgeStyles)
        }
        const borderStyle_result : BorderStyle | EdgeStyles | undefined = borderStyle_buf
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
        const keyboardAvoidMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let keyboardAvoidMode_buf : KeyboardAvoidMode | undefined
        if ((keyboardAvoidMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            keyboardAvoidMode_buf = TypeChecker.KeyboardAvoidMode_FromNumeric(valueDeserializer.readInt32())
        }
        const keyboardAvoidMode_result : KeyboardAvoidMode | undefined = keyboardAvoidMode_buf
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
        const onDidAppear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppear_buf : (() => void) | undefined
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
    InteropNativeModule._CallCallback(-1867723152, onDidAppear_buf__argsSerializer.asBuffer(), onDidAppear_buf__argsSerializer.length());
    onDidAppear_buf__argsSerializer.release();
    return; }
        }
        const onDidAppear_result : (() => void) | undefined = onDidAppear_buf
        const onDidDisappear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappear_buf : (() => void) | undefined
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
    InteropNativeModule._CallCallback(-1867723152, onDidDisappear_buf__argsSerializer.asBuffer(), onDidDisappear_buf__argsSerializer.length());
    onDidDisappear_buf__argsSerializer.release();
    return; }
        }
        const onDidDisappear_result : (() => void) | undefined = onDidDisappear_buf
        const onWillAppear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppear_buf : (() => void) | undefined
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
    InteropNativeModule._CallCallback(-1867723152, onWillAppear_buf__argsSerializer.asBuffer(), onWillAppear_buf__argsSerializer.length());
    onWillAppear_buf__argsSerializer.release();
    return; }
        }
        const onWillAppear_result : (() => void) | undefined = onWillAppear_buf
        const onWillDisappear_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappear_buf : (() => void) | undefined
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
    InteropNativeModule._CallCallback(-1867723152, onWillDisappear_buf__argsSerializer.asBuffer(), onWillDisappear_buf__argsSerializer.length());
    onWillDisappear_buf__argsSerializer.release();
    return; }
        }
        const onWillDisappear_result : (() => void) | undefined = onWillDisappear_buf
        const keyboardAvoidDistance_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let keyboardAvoidDistance_buf : LengthMetrics | undefined
        if ((keyboardAvoidDistance_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            keyboardAvoidDistance_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const keyboardAvoidDistance_result : LengthMetrics | undefined = keyboardAvoidDistance_buf
        const levelMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelMode_buf : LevelMode | undefined
        if ((levelMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            levelMode_buf = TypeChecker.LevelMode_FromNumeric(valueDeserializer.readInt32())
        }
        const levelMode_result : LevelMode | undefined = levelMode_buf
        const levelUniqueId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelUniqueId_buf : number | undefined
        if ((levelUniqueId_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            levelUniqueId_buf = (valueDeserializer.readNumber() as number)
        }
        const levelUniqueId_result : number | undefined = levelUniqueId_buf
        const immersiveMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let immersiveMode_buf : ImmersiveMode | undefined
        if ((immersiveMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            immersiveMode_buf = TypeChecker.ImmersiveMode_FromNumeric(valueDeserializer.readInt32())
        }
        const immersiveMode_result : ImmersiveMode | undefined = immersiveMode_buf
        const levelOrder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelOrder_buf : LevelOrder | undefined
        if ((levelOrder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            levelOrder_buf = (LevelOrder_serializer.read(valueDeserializer) as LevelOrder)
        }
        const levelOrder_result : LevelOrder | undefined = levelOrder_buf
        const focusable_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let focusable_buf : boolean | undefined
        if ((focusable_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            focusable_buf = valueDeserializer.readBoolean()
        }
        const focusable_result : boolean | undefined = focusable_buf
        let value : CustomDialogControllerOptions = ({builder: builder_result, cancel: cancel_result, autoCancel: autoCancel_result, alignment: alignment_result, offset: offset_result, customStyle: customStyle_result, gridCount: gridCount_result, maskColor: maskColor_result, maskRect: maskRect_result, openAnimation: openAnimation_result, closeAnimation: closeAnimation_result, showInSubWindow: showInSubWindow_result, backgroundColor: backgroundColor_result, cornerRadius: cornerRadius_result, isModal: isModal_result, onWillDismiss: onWillDismiss_result, width: width_result, height: height_result, borderWidth: borderWidth_result, borderColor: borderColor_result, borderStyle: borderStyle_result, shadow: shadow_result, backgroundBlurStyle: backgroundBlurStyle_result, backgroundBlurStyleOptions: backgroundBlurStyleOptions_result, backgroundEffect: backgroundEffect_result, keyboardAvoidMode: keyboardAvoidMode_result, enableHoverMode: enableHoverMode_result, hoverModeArea: hoverModeArea_result, onDidAppear: onDidAppear_result, onDidDisappear: onDidDisappear_result, onWillAppear: onWillAppear_result, onWillDisappear: onWillDisappear_result, keyboardAvoidDistance: keyboardAvoidDistance_result, levelMode: levelMode_result, levelUniqueId: levelUniqueId_result, immersiveMode: immersiveMode_result, levelOrder: levelOrder_result, focusable: focusable_result} as CustomDialogControllerOptions)
        return value
    }
}
