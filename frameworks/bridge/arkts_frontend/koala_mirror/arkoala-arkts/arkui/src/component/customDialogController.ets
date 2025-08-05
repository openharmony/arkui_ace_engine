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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
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
        const valueHolderForBuilder  = value.builder
        if (valueHolderForBuilder instanceof CustomBuilder) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForBuilderForIdx0  = valueHolderForBuilder as CustomBuilder
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForBuilderForIdx0))
        } else if (valueHolderForBuilder instanceof ExtendableComponent) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForBuilderForIdx1  = valueHolderForBuilder as ExtendableComponent
            ExtendableComponent_serializer.write(valueSerializer, valueHolderForBuilderForIdx1)
        }
        const valueHolderForCancel  = value.cancel
        if (valueHolderForCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelTmpValue  = valueHolderForCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
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
            valueSerializer.writeInt32(TypeChecker.DialogAlignment_ToNumeric(valueHolderForAlignmentTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCustomStyle  = value.customStyle
        if (valueHolderForCustomStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomStyleTmpValue  = valueHolderForCustomStyle!
            valueSerializer.writeBoolean(valueHolderForCustomStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGridCount  = value.gridCount
        if (valueHolderForGridCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGridCountTmpValue  = valueHolderForGridCount!
            valueSerializer.writeNumber(valueHolderForGridCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskColor  = value.maskColor
        if (valueHolderForMaskColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskColorTmpValue  = valueHolderForMaskColor!
            if (valueHolderForMaskColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForMaskColorTmpValueForIdx0  = valueHolderForMaskColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForMaskColorTmpValueForIdx0))
            } else if (valueHolderForMaskColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForMaskColorTmpValueForIdx1  = valueHolderForMaskColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForMaskColorTmpValueForIdx1)
            } else if (valueHolderForMaskColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForMaskColorTmpValueForIdx2  = valueHolderForMaskColorTmpValue as string
                valueSerializer.writeString(valueHolderForMaskColorTmpValueForIdx2)
            } else if (valueHolderForMaskColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForMaskColorTmpValueForIdx3  = valueHolderForMaskColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMaskColorTmpValueForIdx3)
            }
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
        const valueHolderForOpenAnimation  = value.openAnimation
        if (valueHolderForOpenAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOpenAnimationTmpValue  = valueHolderForOpenAnimation!
            AnimateParam_serializer.write(valueSerializer, valueHolderForOpenAnimationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCloseAnimation  = value.closeAnimation
        if (valueHolderForCloseAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCloseAnimationTmpValue  = valueHolderForCloseAnimation!
            AnimateParam_serializer.write(valueSerializer, valueHolderForCloseAnimationTmpValue)
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
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBackgroundColorTmpValueForIdx0))
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCornerRadius  = value.cornerRadius
        if (valueHolderForCornerRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCornerRadiusTmpValue  = valueHolderForCornerRadius!
            if (valueHolderForCornerRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForCornerRadiusTmpValueForIdx0  = valueHolderForCornerRadiusTmpValue as Dimension
                if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx0  = valueHolderForCornerRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForCornerRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx1  = valueHolderForCornerRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForCornerRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toChar())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx2  = valueHolderForCornerRadiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForCornerRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForCornerRadiusTmpValueForIdx1  = valueHolderForCornerRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx1)
            }
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
        const valueHolderForOnWillDismiss  = value.onWillDismiss
        if (valueHolderForOnWillDismiss !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDismissTmpValue  = valueHolderForOnWillDismiss!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDismissTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as Dimension
                if (valueHolderForBorderWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx0  = valueHolderForBorderWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx1  = valueHolderForBorderWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toChar())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx2  = valueHolderForBorderWidthTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as ResourceColor
                if (valueHolderForBorderColorTmpValueForIdx0 instanceof Color) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx0  = valueHolderForBorderColorTmpValueForIdx0 as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForBorderColorTmpValueForIdx0ForIdx0))
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx1  = valueHolderForBorderColorTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toChar())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx2  = valueHolderForBorderColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((3).toChar())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx3  = valueHolderForBorderColorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForBorderColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderStyle  = value.borderStyle
        if (valueHolderForBorderStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderStyleTmpValue  = valueHolderForBorderStyle!
            if (valueHolderForBorderStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBorderStyleTmpValueForIdx0  = valueHolderForBorderStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(TypeChecker.BorderStyle_ToNumeric(valueHolderForBorderStyleTmpValueForIdx0))
            } else if (valueHolderForBorderStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((1).toChar())
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(TypeChecker.ShadowStyle_ToNumeric(valueHolderForShadowTmpValueForIdx1))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(valueHolderForBackgroundBlurStyleTmpValue))
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
        const valueHolderForKeyboardAvoidMode  = value.keyboardAvoidMode
        if (valueHolderForKeyboardAvoidMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForKeyboardAvoidModeTmpValue  = (valueHolderForKeyboardAvoidMode as KeyboardAvoidMode)
            valueSerializer.writeInt32(TypeChecker.KeyboardAvoidMode_ToNumeric(valueHolderForKeyboardAvoidModeTmpValue))
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
            valueSerializer.writeInt32(TypeChecker.HoverModeAreaType_ToNumeric(valueHolderForHoverModeAreaTmpValue))
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
        const valueHolderForKeyboardAvoidDistance  = value.keyboardAvoidDistance
        if (valueHolderForKeyboardAvoidDistance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForKeyboardAvoidDistanceTmpValue  = valueHolderForKeyboardAvoidDistance!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForKeyboardAvoidDistanceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelMode  = value.levelMode
        if (valueHolderForLevelMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelModeTmpValue  = (valueHolderForLevelMode as LevelMode)
            valueSerializer.writeInt32(TypeChecker.LevelMode_ToNumeric(valueHolderForLevelModeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelUniqueId  = value.levelUniqueId
        if (valueHolderForLevelUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelUniqueIdTmpValue  = valueHolderForLevelUniqueId!
            valueSerializer.writeNumber(valueHolderForLevelUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImmersiveMode  = value.immersiveMode
        if (valueHolderForImmersiveMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImmersiveModeTmpValue  = (valueHolderForImmersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(TypeChecker.ImmersiveMode_ToNumeric(valueHolderForImmersiveModeTmpValue))
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
        const valueHolderForFocusable  = value.focusable
        if (valueHolderForFocusable !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFocusableTmpValue  = valueHolderForFocusable!
            valueSerializer.writeBoolean(valueHolderForFocusableTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const builderTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let builderTmpBuf : CustomBuilder | ExtendableComponent | undefined
        if (builderTmpBufUnionSelector == (0).toChar()) {
            const builderTmpBufBufUBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const builderTmpBufBufUBufCall : KPointer = valueDeserializer.readPointer()
            const builderTmpBufBufUBufCallSync : KPointer = valueDeserializer.readPointer()
            builderTmpBuf = ():void => {
                const builderTmpBufBufUBufArgsSerializer : SerializerBase = SerializerBase.hold();
                builderTmpBufBufUBufArgsSerializer.writeInt32(builderTmpBufBufUBufResource.resourceId);
                builderTmpBufBufUBufArgsSerializer.writePointer(builderTmpBufBufUBufCall);
                builderTmpBufBufUBufArgsSerializer.writePointer(builderTmpBufBufUBufCallSync);
                InteropNativeModule._CallCallback(737226752, builderTmpBufBufUBufArgsSerializer.asBuffer(), builderTmpBufBufUBufArgsSerializer.length());
                builderTmpBufBufUBufArgsSerializer.release();
                return;
            }
        } else if (builderTmpBufUnionSelector == (1).toChar()) {
            builderTmpBuf = (ExtendableComponent_serializer.read(valueDeserializer) as ExtendableComponent)
        } else {
            throw new Error("One of the branches for builderTmpBuf has to be chosen through deserialisation.")
        }
        const builderTmpResult : CustomBuilder | ExtendableComponent = (builderTmpBuf as CustomBuilder | ExtendableComponent)
        const cancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelTmpBuf : (() => void) | undefined
        if ((cancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const cancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const cancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            cancelTmpBuf = ():void => {
                const cancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                cancelTmpBuf_BufArgsSerializer.writeInt32(cancelTmpBuf_BufResource.resourceId);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCall);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, cancelTmpBuf_BufArgsSerializer.asBuffer(), cancelTmpBuf_BufArgsSerializer.length());
                cancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const cancelTmpResult : (() => void) | undefined = cancelTmpBuf
        const autoCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoCancelTmpBuf : boolean | undefined
        if ((autoCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoCancelTmpBuf = valueDeserializer.readBoolean()
        }
        const autoCancelTmpResult : boolean | undefined = autoCancelTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignmentTmpBuf : DialogAlignment | undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = TypeChecker.DialogAlignment_FromNumeric(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Offset | undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const customStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let customStyleTmpBuf : boolean | undefined
        if ((customStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            customStyleTmpBuf = valueDeserializer.readBoolean()
        }
        const customStyleTmpResult : boolean | undefined = customStyleTmpBuf
        const gridCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gridCountTmpBuf : number | undefined
        if ((gridCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gridCountTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const gridCountTmpResult : number | undefined = gridCountTmpBuf
        const maskColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskColorTmpBuf : ResourceColor | undefined
        if ((maskColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maskColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maskColorTmpBuf_ : Color | number | string | Resource | undefined
            if (maskColorTmpBuf_UnionSelector == (0).toChar()) {
                maskColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (maskColorTmpBuf_UnionSelector == (1).toChar()) {
                maskColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (maskColorTmpBuf_UnionSelector == (2).toChar()) {
                maskColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (maskColorTmpBuf_UnionSelector == (3).toChar()) {
                maskColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for maskColorTmpBuf_ has to be chosen through deserialisation.")
            }
            maskColorTmpBuf = (maskColorTmpBuf_ as Color | number | string | Resource)
        }
        const maskColorTmpResult : ResourceColor | undefined = maskColorTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRectTmpBuf : Rectangle | undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const openAnimationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let openAnimationTmpBuf : AnimateParam | undefined
        if ((openAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            openAnimationTmpBuf = AnimateParam_serializer.read(valueDeserializer)
        }
        const openAnimationTmpResult : AnimateParam | undefined = openAnimationTmpBuf
        const closeAnimationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let closeAnimationTmpBuf : AnimateParam | undefined
        if ((closeAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            closeAnimationTmpBuf = AnimateParam_serializer.read(valueDeserializer)
        }
        const closeAnimationTmpResult : AnimateParam | undefined = closeAnimationTmpBuf
        const showInSubWindowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showInSubWindowTmpBuf : boolean | undefined
        if ((showInSubWindowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInSubWindowTmpBuf = valueDeserializer.readBoolean()
        }
        const showInSubWindowTmpResult : boolean | undefined = showInSubWindowTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
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
        const cornerRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cornerRadiusTmpBuf : Dimension | BorderRadiuses | undefined
        if ((cornerRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cornerRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let cornerRadiusTmpBuf_ : Dimension | BorderRadiuses | undefined
            if (cornerRadiusTmpBuf_UnionSelector == (0).toChar()) {
                const cornerRadiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let cornerRadiusTmpBuf_BufU : string | number | Resource | undefined
                if (cornerRadiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    cornerRadiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for cornerRadiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                cornerRadiusTmpBuf_ = (cornerRadiusTmpBuf_BufU as string | number | Resource)
            } else if (cornerRadiusTmpBuf_UnionSelector == (1).toChar()) {
                cornerRadiusTmpBuf_ = BorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for cornerRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            cornerRadiusTmpBuf = (cornerRadiusTmpBuf_ as Dimension | BorderRadiuses)
        }
        const cornerRadiusTmpResult : Dimension | BorderRadiuses | undefined = cornerRadiusTmpBuf
        const isModalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isModalTmpBuf : boolean | undefined
        if ((isModalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isModalTmpBuf = valueDeserializer.readBoolean()
        }
        const isModalTmpResult : boolean | undefined = isModalTmpBuf
        const onWillDismissTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDismissTmpBuf : ((value0: DismissDialogAction) => void) | undefined
        if ((onWillDismissTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDismissTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismissTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDismissTmpBuf = (value0: DismissDialogAction):void => {
                const onWillDismissTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDismissTmpBuf_BufArgsSerializer.writeInt32(onWillDismissTmpBuf_BufResource.resourceId);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCall);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCallSync);
                DismissDialogAction_serializer.write(onWillDismissTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallback(-2095828093, onWillDismissTmpBuf_BufArgsSerializer.asBuffer(), onWillDismissTmpBuf_BufArgsSerializer.length());
                onWillDismissTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDismissTmpResult : ((value0: DismissDialogAction) => void) | undefined = onWillDismissTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Dimension | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Dimension | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Dimension | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | number | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | number | Resource)
        }
        const heightTmpResult : Dimension | undefined = heightTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidthTmpBuf : Dimension | EdgeWidths | undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBuf_ : Dimension | EdgeWidths | undefined
            if (borderWidthTmpBuf_UnionSelector == (0).toChar()) {
                const borderWidthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderWidthTmpBuf_BufU : string | number | Resource | undefined
                if (borderWidthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderWidthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderWidthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderWidthTmpBuf_ = (borderWidthTmpBuf_BufU as string | number | Resource)
            } else if (borderWidthTmpBuf_UnionSelector == (1).toChar()) {
                borderWidthTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            borderWidthTmpBuf = (borderWidthTmpBuf_ as Dimension | EdgeWidths)
        }
        const borderWidthTmpResult : Dimension | EdgeWidths | undefined = borderWidthTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColorTmpBuf : ResourceColor | EdgeColors | undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBuf_ : ResourceColor | EdgeColors | undefined
            if (borderColorTmpBuf_UnionSelector == (0).toChar()) {
                const borderColorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderColorTmpBuf_BufU : Color | number | string | Resource | undefined
                if (borderColorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderColorTmpBuf_BufU = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                } else if (borderColorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderColorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderColorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    borderColorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderColorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderColorTmpBuf_ = (borderColorTmpBuf_BufU as Color | number | string | Resource)
            } else if (borderColorTmpBuf_UnionSelector == (1).toChar()) {
                borderColorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderColorTmpBuf_ has to be chosen through deserialisation.")
            }
            borderColorTmpBuf = (borderColorTmpBuf_ as ResourceColor | EdgeColors)
        }
        const borderColorTmpResult : ResourceColor | EdgeColors | undefined = borderColorTmpBuf
        const borderStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderStyleTmpBuf : BorderStyle | EdgeStyles | undefined
        if ((borderStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderStyleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderStyleTmpBuf_ : BorderStyle | EdgeStyles | undefined
            if (borderStyleTmpBuf_UnionSelector == (0).toChar()) {
                borderStyleTmpBuf_ = TypeChecker.BorderStyle_FromNumeric(valueDeserializer.readInt32())
            } else if (borderStyleTmpBuf_UnionSelector == (1).toChar()) {
                borderStyleTmpBuf_ = EdgeStyles_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderStyleTmpBuf_ has to be chosen through deserialisation.")
            }
            borderStyleTmpBuf = (borderStyleTmpBuf_ as BorderStyle | EdgeStyles)
        }
        const borderStyleTmpResult : BorderStyle | EdgeStyles | undefined = borderStyleTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = TypeChecker.ShadowStyle_FromNumeric(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const keyboardAvoidModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let keyboardAvoidModeTmpBuf : KeyboardAvoidMode | undefined
        if ((keyboardAvoidModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            keyboardAvoidModeTmpBuf = TypeChecker.KeyboardAvoidMode_FromNumeric(valueDeserializer.readInt32())
        }
        const keyboardAvoidModeTmpResult : KeyboardAvoidMode | undefined = keyboardAvoidModeTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = TypeChecker.HoverModeAreaType_FromNumeric(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : (() => void) | undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : (() => void) | undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const keyboardAvoidDistanceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let keyboardAvoidDistanceTmpBuf : LengthMetrics | undefined
        if ((keyboardAvoidDistanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            keyboardAvoidDistanceTmpBuf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const keyboardAvoidDistanceTmpResult : LengthMetrics | undefined = keyboardAvoidDistanceTmpBuf
        const levelModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelModeTmpBuf : LevelMode | undefined
        if ((levelModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelModeTmpBuf = TypeChecker.LevelMode_FromNumeric(valueDeserializer.readInt32())
        }
        const levelModeTmpResult : LevelMode | undefined = levelModeTmpBuf
        const levelUniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelUniqueIdTmpBuf : number | undefined
        if ((levelUniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelUniqueIdTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const levelUniqueIdTmpResult : number | undefined = levelUniqueIdTmpBuf
        const immersiveModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let immersiveModeTmpBuf : ImmersiveMode | undefined
        if ((immersiveModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            immersiveModeTmpBuf = TypeChecker.ImmersiveMode_FromNumeric(valueDeserializer.readInt32())
        }
        const immersiveModeTmpResult : ImmersiveMode | undefined = immersiveModeTmpBuf
        const levelOrderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelOrderTmpBuf : LevelOrder | undefined
        if ((levelOrderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelOrderTmpBuf = (LevelOrder_serializer.read(valueDeserializer) as LevelOrder)
        }
        const levelOrderTmpResult : LevelOrder | undefined = levelOrderTmpBuf
        const focusableTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let focusableTmpBuf : boolean | undefined
        if ((focusableTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            focusableTmpBuf = valueDeserializer.readBoolean()
        }
        const focusableTmpResult : boolean | undefined = focusableTmpBuf
        let value : CustomDialogControllerOptions = ({builder: builderTmpResult, cancel: cancelTmpResult, autoCancel: autoCancelTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, customStyle: customStyleTmpResult, gridCount: gridCountTmpResult, maskColor: maskColorTmpResult, maskRect: maskRectTmpResult, openAnimation: openAnimationTmpResult, closeAnimation: closeAnimationTmpResult, showInSubWindow: showInSubWindowTmpResult, backgroundColor: backgroundColorTmpResult, cornerRadius: cornerRadiusTmpResult, isModal: isModalTmpResult, onWillDismiss: onWillDismissTmpResult, width: widthTmpResult, height: heightTmpResult, borderWidth: borderWidthTmpResult, borderColor: borderColorTmpResult, borderStyle: borderStyleTmpResult, shadow: shadowTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, keyboardAvoidMode: keyboardAvoidModeTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, keyboardAvoidDistance: keyboardAvoidDistanceTmpResult, levelMode: levelModeTmpResult, levelUniqueId: levelUniqueIdTmpResult, immersiveMode: immersiveModeTmpResult, levelOrder: levelOrderTmpResult, focusable: focusableTmpResult} as CustomDialogControllerOptions)
        return value
    }
}
