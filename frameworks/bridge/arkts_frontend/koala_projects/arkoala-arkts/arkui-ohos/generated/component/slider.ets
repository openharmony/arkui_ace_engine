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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer } from "./../framework/resource"
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { SizeOptions_serializer, ResourceColor, Length, Dimension, SizeOptions, ResourceStr } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, Bindable, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_F64_serializer } from "./common"
import { Color, CrownSensitivity, Axis } from "./enums"
import { Resource } from "global.resource"
import { ContentModifier, AttributeModifier, extractors, WrappedBuilder, hookSliderContentModifier, hookSliderSetPrefixMethod, hookSliderSetSuffixMethod, hookSliderAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { ComponentContent, ComponentContentBase } from "arkui.ComponentContent"
import { UIContext } from "@ohos.arkui.UIContext"
import { CustomBuilder, CustomBuilderT } from "./builder"
import { BuildOptions } from "arkui.BuilderNode"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { CircleShape, EllipseShape, PathShape, RectShape } from "@ohos.arkui.shape"
import { SliderModifier } from "./../SliderModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { CircleShape_serializer, EllipseShape_serializer, PathShape_serializer, RectShape_serializer } from "./../framework/ohos.arkui.shape"
export class ArkSliderPeer extends ArkCommonMethodPeer {
    attributeSet?: SliderModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSliderPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Slider_construct(peerId, flags)
        const _peer  = new ArkSliderPeer(_peerPtr, peerId, 'Slider', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSliderOptionsAttribute(options?: SliderOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SliderOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderInterface_setSliderOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
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
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof LinearGradient) {
                 thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as LinearGradient
                LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx1)
             }
         } else {
             thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
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
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof LinearGradient) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as LinearGradient
                LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setTrackColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
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
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof LinearGradient) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as LinearGradient
                LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowSteps0Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setShowSteps0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackThicknessAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setTrackThickness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value: double,mode: SliderChangeMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockBorderColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
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
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockBorderWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockBorderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStepColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
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
        ArkUIGeneratedNativeModule._SliderAttribute_setStepColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackBorderRadiusAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setTrackBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBorderRadiusAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSelectedBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockSizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SizeOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockStyleAttribute(value: SliderBlockStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SliderBlockStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStepSizeAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setStepSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSliderInteractionModeAttribute(value: SliderInteraction | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SliderInteraction)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSliderInteractionMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinResponsiveDistanceAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setMinResponsiveDistance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSlideRangeAttribute(value: SlideRange | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SlideRange_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSlideRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDigitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CrownSensitivity)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowSteps1Attribute(value: boolean | undefined, options?: SliderShowStepOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SliderShowStepOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setShowSteps1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowTipsAttribute(value: boolean | undefined, content?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (content !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contentTmpValue  = content!
            if (contentTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const contentTmpValueForIdx0  = contentTmpValue as string
                thisSerializer.writeString(contentTmpValueForIdx0)
            } else if (contentTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const contentTmpValueForIdx1  = contentTmpValue as Resource
                Resource_serializer.write(thisSerializer, contentTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setShowTips(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SliderStyle {
    OUT_SET = 0,
    OutSet = 0,
    IN_SET = 1,
    InSet = 1,
    NONE = 2
}
export enum SliderChangeMode {
    BEGIN = 0,
    Begin = 0,
    MOVING = 1,
    Moving = 1,
    END = 2,
    End = 2,
    CLICK = 3,
    Click = 3
}
export enum SliderInteraction {
    SLIDE_AND_CLICK = 0,
    SLIDE_ONLY = 1,
    SLIDE_AND_CLICK_UP = 2
}
export interface SlideRange {
    from?: double;
    to?: double;
}
export interface SliderOptions {
    value?: double | Bindable<double> | undefined;
    min?: double;
    max?: double;
    step?: double;
    style?: SliderStyle;
    direction?: Axis;
    reverse?: boolean;
}
export enum SliderBlockType {
    DEFAULT = 0,
    IMAGE = 1,
    SHAPE = 2
}
export interface SliderBlockStyle {
    type: SliderBlockType;
    image?: ResourceStr;
    shape?: CircleShape | EllipseShape | PathShape | RectShape;
}
export type SliderTriggerChangeCallback = (value: double, mode: SliderChangeMode) => void;
export interface SliderConfiguration extends CommonConfiguration<SliderConfiguration> {
    value: double;
    min: double;
    max: double;
    step: double;
    triggerChange: SliderTriggerChangeCallback;
}
export interface SliderCustomContentOptions {
    accessibilityText?: ResourceStr;
    accessibilityDescription?: ResourceStr;
    accessibilityLevel?: string;
    accessibilityGroup?: boolean;
}
export interface SliderPrefixOptions extends SliderCustomContentOptions {
}
export interface SliderSuffixOptions extends SliderCustomContentOptions {
}
export interface SliderStepItemAccessibility {
    text?: ResourceStr;
}
export interface SliderShowStepOptions {
    stepsAccessibility?: Map<number, SliderStepItemAccessibility>;
}
export interface SliderAttribute extends CommonMethod {
    setSliderOptions(options?: SliderOptions): this {
        throw new Error("Unimplemented method setSliderOptions")
    }
    blockColor(value: ResourceColor | LinearGradient | undefined): this {
        throw new Error("Unimplemented method blockColor")
    }
    trackColor(value: ResourceColor | LinearGradient | undefined): this {
        throw new Error("Unimplemented method trackColor")
    }
    selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    showSteps(value: boolean | undefined): this {
        throw new Error("Unimplemented method showSteps")
    }
    trackThickness(value: Length | undefined): this {
        throw new Error("Unimplemented method trackThickness")
    }
    onChange(value: ((value: double,mode: SliderChangeMode) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    blockBorderColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method blockBorderColor")
    }
    blockBorderWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method blockBorderWidth")
    }
    stepColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method stepColor")
    }
    trackBorderRadius(value: Length | undefined): this {
        throw new Error("Unimplemented method trackBorderRadius")
    }
    selectedBorderRadius(value: Dimension | undefined): this {
        throw new Error("Unimplemented method selectedBorderRadius")
    }
    blockSize(value: SizeOptions | undefined): this {
        throw new Error("Unimplemented method blockSize")
    }
    blockStyle(value: SliderBlockStyle | undefined): this {
        throw new Error("Unimplemented method blockStyle")
    }
    stepSize(value: Length | undefined): this {
        throw new Error("Unimplemented method stepSize")
    }
    sliderInteractionMode(value: SliderInteraction | undefined): this {
        throw new Error("Unimplemented method sliderInteractionMode")
    }
    minResponsiveDistance(value: double | undefined): this {
        throw new Error("Unimplemented method minResponsiveDistance")
    }
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    slideRange(value: SlideRange | undefined): this {
        throw new Error("Unimplemented method slideRange")
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error("Unimplemented method digitalCrownSensitivity")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    showSteps(value: boolean | undefined, options?: SliderShowStepOptions): this {
        throw new Error("Unimplemented method showSteps")
    }
    prefix(content: ComponentContent | undefined, options?: SliderPrefixOptions): this {
        throw new Error("Unimplemented method prefix")
    }
    suffix(content: ComponentContent | undefined, options?: SliderSuffixOptions): this {
        throw new Error("Unimplemented method suffix")
    }
    showTips(value: boolean | undefined, content?: ResourceStr): this {
        throw new Error("Unimplemented method showTips")
    }
    attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSliderStyle extends ArkCommonMethodStyle implements SliderAttribute {
    blockColor_value?: ResourceColor | LinearGradient | undefined
    trackColor_value?: ResourceColor | LinearGradient | undefined
    selectedColor_value?: ResourceColor | LinearGradient | undefined
    showSteps_value?: boolean | undefined
    trackThickness_value?: Length | undefined
    onChange_value?: ((value: double,mode: SliderChangeMode) => void) | undefined
    blockBorderColor_value?: ResourceColor | undefined
    blockBorderWidth_value?: Length | undefined
    stepColor_value?: ResourceColor | undefined
    trackBorderRadius_value?: Length | undefined
    selectedBorderRadius_value?: Dimension | undefined
    blockSize_value?: SizeOptions | undefined
    blockStyle_value?: SliderBlockStyle | undefined
    stepSize_value?: Length | undefined
    sliderInteractionMode_value?: SliderInteraction | undefined
    minResponsiveDistance_value?: double | undefined
    contentModifier_value?: ContentModifier<SliderConfiguration> | undefined
    slideRange_value?: SlideRange | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined
    setSliderOptions(options?: SliderOptions): this {
        return this
    }
    blockColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    trackColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    showSteps(value: boolean | undefined): this {
        return this
    }
    trackThickness(value: Length | undefined): this {
        return this
    }
    onChange(value: ((value: double,mode: SliderChangeMode) => void) | undefined): this {
        return this
    }
    blockBorderColor(value: ResourceColor | undefined): this {
        return this
    }
    blockBorderWidth(value: Length | undefined): this {
        return this
    }
    stepColor(value: ResourceColor | undefined): this {
        return this
    }
    trackBorderRadius(value: Length | undefined): this {
        return this
    }
    selectedBorderRadius(value: Dimension | undefined): this {
        return this
    }
    blockSize(value: SizeOptions | undefined): this {
        return this
    }
    blockStyle(value: SliderBlockStyle | undefined): this {
        return this
    }
    stepSize(value: Length | undefined): this {
        return this
    }
    sliderInteractionMode(value: SliderInteraction | undefined): this {
        return this
    }
    minResponsiveDistance(value: double | undefined): this {
        return this
    }
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        return this
    }
    slideRange(value: SlideRange | undefined): this {
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    showSteps(value: boolean | undefined, options?: SliderShowStepOptions): this {
        return this
    }
    prefix(content: ComponentContent | undefined, options?: SliderPrefixOptions): this {
        return this
    }
    suffix(content: ComponentContent | undefined, options?: SliderSuffixOptions): this {
        return this
    }
    showTips(value: boolean | undefined, content?: ResourceStr): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkSliderComponent extends ArkCommonMethodComponent implements SliderAttribute {
    getPeer(): ArkSliderPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkSliderPeer)
    }
    public setSliderOptions(options?: SliderOptions): this {
        if (this.checkPriority("setSliderOptions")) {
            const options_casted = options as (SliderOptions | undefined)
            this.getPeer()?.setSliderOptionsAttribute(options_casted)
            this.applyOptionsFinish('SliderAttribute');
            return this
        }
        return this
    }
    public blockColor(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("blockColor")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.setBlockColorAttribute(value_casted)
            return this
        }
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("trackColor")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.setTrackColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public showSteps(value: boolean | undefined): this {
        if (this.checkPriority("showSteps")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setShowSteps0Attribute(value_casted)
            return this
        }
        return this
    }
    public trackThickness(value: Length | undefined): this {
        if (this.checkPriority("trackThickness")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setTrackThicknessAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value: double,mode: SliderChangeMode) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: double,mode: SliderChangeMode) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public blockBorderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("blockBorderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBlockBorderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public blockBorderWidth(value: Length | undefined): this {
        if (this.checkPriority("blockBorderWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setBlockBorderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public stepColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("stepColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setStepColorAttribute(value_casted)
            return this
        }
        return this
    }
    public trackBorderRadius(value: Length | undefined): this {
        if (this.checkPriority("trackBorderRadius")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setTrackBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBorderRadius(value: Dimension | undefined): this {
        if (this.checkPriority("selectedBorderRadius")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setSelectedBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public blockSize(value: SizeOptions | undefined): this {
        if (this.checkPriority("blockSize")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.setBlockSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public blockStyle(value: SliderBlockStyle | undefined): this {
        if (this.checkPriority("blockStyle")) {
            const value_casted = value as (SliderBlockStyle | undefined)
            this.getPeer()?.setBlockStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public stepSize(value: Length | undefined): this {
        if (this.checkPriority("stepSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStepSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public sliderInteractionMode(value: SliderInteraction | undefined): this {
        if (this.checkPriority("sliderInteractionMode")) {
            const value_casted = value as (SliderInteraction | undefined)
            this.getPeer()?.setSliderInteractionModeAttribute(value_casted)
            return this
        }
        return this
    }
    public minResponsiveDistance(value: double | undefined): this {
        if (this.checkPriority("minResponsiveDistance")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setMinResponsiveDistanceAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookSliderContentModifier(this, value)
        }
        return this
    }
    public slideRange(value: SlideRange | undefined): this {
        if (this.checkPriority("slideRange")) {
            const value_casted = value as (SlideRange | undefined)
            this.getPeer()?.setSlideRangeAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public showSteps(value: boolean | undefined, options?: SliderShowStepOptions): this {
        if (this.checkPriority("showSteps")) {
            const value_casted = value as (boolean | undefined)
            const options_casted = options as (SliderShowStepOptions | undefined)
            this.getPeer()?.setShowSteps1Attribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public prefix(content: ComponentContent | undefined, options?: SliderPrefixOptions): this {
        if (this.checkPriority("prefix")) {
            hookSliderSetPrefixMethod(this, content, options)
        }
        return this
    }
    public suffix(content: ComponentContent | undefined, options?: SliderSuffixOptions): this {
        if (this.checkPriority("suffix")) {
            hookSliderSetSuffixMethod(this, content, options)
        }
        return this
    }
    public showTips(value: boolean | undefined, content?: ResourceStr): this {
        if (this.checkPriority("showTips")) {
            const value_casted = value as (boolean | undefined)
            const content_casted = content as (ResourceStr | undefined)
            this.getPeer()?.setShowTipsAttribute(value_casted, content_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookSliderAttributeModifier(this, value);
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
export function SliderImpl(
    @memo
    style: ((attributes: SliderAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSliderComponent>((): ArkSliderComponent => {
        return new ArkSliderComponent()
    })
    NodeAttach<ArkSliderPeer>((): ArkSliderPeer => ArkSliderPeer.create(receiver), (peer: ArkSliderPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class SlideRange_serializer {
    public static write(buffer: SerializerBase, value: SlideRange): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFrom  = value.from
        if (valueHolderForFrom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFromTmpValue  = valueHolderForFrom!
            valueSerializer.writeFloat64(valueHolderForFromTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTo  = value.to
        if (valueHolderForTo !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForToTmpValue  = valueHolderForTo!
            valueSerializer.writeFloat64(valueHolderForToTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SlideRange {
        let valueDeserializer : DeserializerBase = buffer
        const fromTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fromTmpBuf : double | undefined = undefined
        if ((fromTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fromTmpBuf = valueDeserializer.readFloat64()
        }
        const fromTmpResult : double | undefined = fromTmpBuf
        const toTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let toTmpBuf : double | undefined = undefined
        if ((toTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            toTmpBuf = valueDeserializer.readFloat64()
        }
        const toTmpResult : double | undefined = toTmpBuf
        let value : SlideRange = ({from: fromTmpResult, to: toTmpResult} as SlideRange)
        return value
    }
}
export class SliderConfiguration_serializer {
    public static write(buffer: SerializerBase, value: SliderConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForValue  = value.value
        valueSerializer.writeFloat64(valueHolderForValue)
        const valueHolderForMin  = value.min
        valueSerializer.writeFloat64(valueHolderForMin)
        const valueHolderForMax  = value.max
        valueSerializer.writeFloat64(valueHolderForMax)
        const valueHolderForStep  = value.step
        valueSerializer.writeFloat64(valueHolderForStep)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): SliderConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<SliderConfiguration> = (valueDeserializer.readObject() as ContentModifier<SliderConfiguration>)
        const valueTmpResult : double = valueDeserializer.readFloat64()
        const minTmpResult : double = valueDeserializer.readFloat64()
        const maxTmpResult : double = valueDeserializer.readFloat64()
        const stepTmpResult : double = valueDeserializer.readFloat64()
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpResult : SliderTriggerChangeCallback = (value: double, mode: SliderChangeMode):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeFloat64(value);
            triggerChangeTmpBufBufArgsSerializer.writeInt32(mode.valueOf());
            InteropNativeModule._CallCallbackSync(10, 711649376, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        let value : SliderConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, value: valueTmpResult, min: minTmpResult, max: maxTmpResult, step: stepTmpResult, triggerChange: triggerChangeTmpResult} as SliderConfiguration)
        return value
    }
}
export class SliderShowStepOptions_serializer {
    public static write(buffer: SerializerBase, value: SliderShowStepOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStepsAccessibility  = value.stepsAccessibility
        if (valueHolderForStepsAccessibility !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStepsAccessibilityTmpValue  = valueHolderForStepsAccessibility!
            valueSerializer.writeInt32((valueHolderForStepsAccessibilityTmpValue.size).toInt())
            for (const pair of valueHolderForStepsAccessibilityTmpValue) {
                const valueHolderForStepsAccessibilityTmpValueKeyVar = pair[0]
                const valueHolderForStepsAccessibilityTmpValueValueVar = pair[1]
                valueSerializer.writeNumber(valueHolderForStepsAccessibilityTmpValueKeyVar)
                SliderStepItemAccessibility_serializer.write(valueSerializer, valueHolderForStepsAccessibilityTmpValueValueVar)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SliderShowStepOptions {
        let valueDeserializer : DeserializerBase = buffer
        const stepsAccessibilityTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stepsAccessibilityTmpBuf : Map<number, SliderStepItemAccessibility> | undefined = undefined
        if ((stepsAccessibilityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const stepsAccessibilityTmpBuf_SizeVar : int32 = valueDeserializer.readInt32()
            let stepsAccessibilityTmpBuf_ : Map<number, SliderStepItemAccessibility> = new Map<number, SliderStepItemAccessibility>()
            // TODO: TS map resize
            for (let stepsAccessibilityTmpBuf_IVar = 0; stepsAccessibilityTmpBuf_IVar < stepsAccessibilityTmpBuf_SizeVar; stepsAccessibilityTmpBuf_IVar++) {
                const stepsAccessibilityTmpBuf_KeyVar : number = (valueDeserializer.readNumber() as number)
                const stepsAccessibilityTmpBuf_ValueVar : SliderStepItemAccessibility = SliderStepItemAccessibility_serializer.read(valueDeserializer)
                stepsAccessibilityTmpBuf_.set(stepsAccessibilityTmpBuf_KeyVar, stepsAccessibilityTmpBuf_ValueVar)
            }
            stepsAccessibilityTmpBuf = stepsAccessibilityTmpBuf_
        }
        const stepsAccessibilityTmpResult : Map<number, SliderStepItemAccessibility> | undefined = stepsAccessibilityTmpBuf
        let value : SliderShowStepOptions = ({stepsAccessibility: stepsAccessibilityTmpResult} as SliderShowStepOptions)
        return value
    }
}
export class SliderBlockStyle_serializer {
    public static write(buffer: SerializerBase, value: SliderBlockStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForImage  = value.image
        if (valueHolderForImage !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageTmpValue  = valueHolderForImage!
            if (valueHolderForImageTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForImageTmpValueForIdx0  = valueHolderForImageTmpValue as string
                valueSerializer.writeString(valueHolderForImageTmpValueForIdx0)
            } else if (valueHolderForImageTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForImageTmpValueForIdx1  = valueHolderForImageTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForImageTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShape  = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue  = valueHolderForShape!
            if (valueHolderForShapeTmpValue instanceof CircleShape) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShapeTmpValueForIdx0  = valueHolderForShapeTmpValue as CircleShape
                CircleShape_serializer.write(valueSerializer, valueHolderForShapeTmpValueForIdx0)
            } else if (valueHolderForShapeTmpValue instanceof EllipseShape) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShapeTmpValueForIdx1  = valueHolderForShapeTmpValue as EllipseShape
                EllipseShape_serializer.write(valueSerializer, valueHolderForShapeTmpValueForIdx1)
            } else if (valueHolderForShapeTmpValue instanceof PathShape) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForShapeTmpValueForIdx2  = valueHolderForShapeTmpValue as PathShape
                PathShape_serializer.write(valueSerializer, valueHolderForShapeTmpValueForIdx2)
            } else if (valueHolderForShapeTmpValue instanceof RectShape) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForShapeTmpValueForIdx3  = valueHolderForShapeTmpValue as RectShape
                RectShape_serializer.write(valueSerializer, valueHolderForShapeTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SliderBlockStyle {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : SliderBlockType = SliderBlockType.fromValue(valueDeserializer.readInt32())
        const imageTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageTmpBuf : ResourceStr | undefined = undefined
        if ((imageTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const imageTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let imageTmpBuf_ : string | Resource | undefined
            if (imageTmpBuf_UnionSelector == (0).toChar()) {
                imageTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (imageTmpBuf_UnionSelector == (1).toChar()) {
                imageTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for imageTmpBuf_ has to be chosen through deserialisation.")
            }
            imageTmpBuf = (imageTmpBuf_ as string | Resource)
        }
        const imageTmpResult : ResourceStr | undefined = imageTmpBuf
        const shapeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shapeTmpBuf : CircleShape | EllipseShape | PathShape | RectShape | undefined = undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shapeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shapeTmpBuf_ : CircleShape | EllipseShape | PathShape | RectShape | undefined
            if (shapeTmpBuf_UnionSelector == (0).toChar()) {
                shapeTmpBuf_ = (CircleShape_serializer.read(valueDeserializer) as CircleShape)
            } else if (shapeTmpBuf_UnionSelector == (1).toChar()) {
                shapeTmpBuf_ = (EllipseShape_serializer.read(valueDeserializer) as EllipseShape)
            } else if (shapeTmpBuf_UnionSelector == (2).toChar()) {
                shapeTmpBuf_ = (PathShape_serializer.read(valueDeserializer) as PathShape)
            } else if (shapeTmpBuf_UnionSelector == (3).toChar()) {
                shapeTmpBuf_ = (RectShape_serializer.read(valueDeserializer) as RectShape)
            } else {
                throw new Error("One of the branches for shapeTmpBuf_ has to be chosen through deserialisation.")
            }
            shapeTmpBuf = (shapeTmpBuf_ as CircleShape | EllipseShape | PathShape | RectShape)
        }
        const shapeTmpResult : CircleShape | EllipseShape | PathShape | RectShape | undefined = shapeTmpBuf
        let value : SliderBlockStyle = ({type: typeTmpResult, image: imageTmpResult, shape: shapeTmpResult} as SliderBlockStyle)
        return value
    }
}
export class SliderOptions_serializer {
    public static write(buffer: SerializerBase, value: SliderOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            if (valueHolderForValueTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as double
                valueSerializer.writeFloat64(valueHolderForValueTmpValueForIdx0)
            } else if (valueHolderForValueTmpValue instanceof Bindable<double>) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as Bindable<double>
                Bindable_F64_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMin  = value.min
        if (valueHolderForMin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinTmpValue  = valueHolderForMin!
            valueSerializer.writeFloat64(valueHolderForMinTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMax  = value.max
        if (valueHolderForMax !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxTmpValue  = valueHolderForMax!
            valueSerializer.writeFloat64(valueHolderForMaxTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStep  = value.step
        if (valueHolderForStep !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStepTmpValue  = valueHolderForStep!
            valueSerializer.writeFloat64(valueHolderForStepTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as SliderStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDirection  = value.direction
        if (valueHolderForDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDirectionTmpValue  = (valueHolderForDirection as Axis)
            valueSerializer.writeInt32(valueHolderForDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForReverse  = value.reverse
        if (valueHolderForReverse !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForReverseTmpValue  = valueHolderForReverse!
            valueSerializer.writeBoolean(valueHolderForReverseTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SliderOptions {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let valueTmpBuf : double | Bindable<double> | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBuf_ : double | Bindable<double> | undefined
            if (valueTmpBuf_UnionSelector == (0).toChar()) {
                valueTmpBuf_ = valueDeserializer.readFloat64()
            } else if (valueTmpBuf_UnionSelector == (1).toChar()) {
                valueTmpBuf_ = Bindable_F64_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for valueTmpBuf_ has to be chosen through deserialisation.")
            }
            valueTmpBuf = (valueTmpBuf_ as double | Bindable<double>)
        }
        const valueTmpResult : double | Bindable<double> | undefined = valueTmpBuf
        const minTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minTmpBuf : double | undefined = undefined
        if ((minTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            minTmpBuf = valueDeserializer.readFloat64()
        }
        const minTmpResult : double | undefined = minTmpBuf
        const maxTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxTmpBuf : double | undefined = undefined
        if ((maxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxTmpBuf = valueDeserializer.readFloat64()
        }
        const maxTmpResult : double | undefined = maxTmpBuf
        const stepTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stepTmpBuf : double | undefined = undefined
        if ((stepTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stepTmpBuf = valueDeserializer.readFloat64()
        }
        const stepTmpResult : double | undefined = stepTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : SliderStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = SliderStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : SliderStyle | undefined = styleTmpBuf
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let directionTmpBuf : Axis | undefined = undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = Axis.fromValue(valueDeserializer.readInt32())
        }
        const directionTmpResult : Axis | undefined = directionTmpBuf
        const reverseTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let reverseTmpBuf : boolean | undefined = undefined
        if ((reverseTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            reverseTmpBuf = valueDeserializer.readBoolean()
        }
        const reverseTmpResult : boolean | undefined = reverseTmpBuf
        let value : SliderOptions = ({value: valueTmpResult, min: minTmpResult, max: maxTmpResult, step: stepTmpResult, style: styleTmpResult, direction: directionTmpResult, reverse: reverseTmpResult} as SliderOptions)
        return value
    }
}
export class SliderPrefixOptions_serializer {
    public static write(buffer: SerializerBase, value: SliderPrefixOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAccessibilityText  = value.accessibilityText
        if (valueHolderForAccessibilityText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityTextTmpValue  = valueHolderForAccessibilityText!
            if (valueHolderForAccessibilityTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAccessibilityTextTmpValueForIdx0  = valueHolderForAccessibilityTextTmpValue as string
                valueSerializer.writeString(valueHolderForAccessibilityTextTmpValueForIdx0)
            } else if (valueHolderForAccessibilityTextTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAccessibilityTextTmpValueForIdx1  = valueHolderForAccessibilityTextTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForAccessibilityTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityDescription  = value.accessibilityDescription
        if (valueHolderForAccessibilityDescription !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityDescriptionTmpValue  = valueHolderForAccessibilityDescription!
            if (valueHolderForAccessibilityDescriptionTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAccessibilityDescriptionTmpValueForIdx0  = valueHolderForAccessibilityDescriptionTmpValue as string
                valueSerializer.writeString(valueHolderForAccessibilityDescriptionTmpValueForIdx0)
            } else if (valueHolderForAccessibilityDescriptionTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAccessibilityDescriptionTmpValueForIdx1  = valueHolderForAccessibilityDescriptionTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForAccessibilityDescriptionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityLevel  = value.accessibilityLevel
        if (valueHolderForAccessibilityLevel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityLevelTmpValue  = valueHolderForAccessibilityLevel!
            valueSerializer.writeString(valueHolderForAccessibilityLevelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityGroup  = value.accessibilityGroup
        if (valueHolderForAccessibilityGroup !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityGroupTmpValue  = valueHolderForAccessibilityGroup!
            valueSerializer.writeBoolean(valueHolderForAccessibilityGroupTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SliderPrefixOptions {
        let valueDeserializer : DeserializerBase = buffer
        const accessibilityTextTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityTextTmpBuf : ResourceStr | undefined = undefined
        if ((accessibilityTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const accessibilityTextTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let accessibilityTextTmpBuf_ : string | Resource | undefined
            if (accessibilityTextTmpBuf_UnionSelector == (0).toChar()) {
                accessibilityTextTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (accessibilityTextTmpBuf_UnionSelector == (1).toChar()) {
                accessibilityTextTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for accessibilityTextTmpBuf_ has to be chosen through deserialisation.")
            }
            accessibilityTextTmpBuf = (accessibilityTextTmpBuf_ as string | Resource)
        }
        const accessibilityTextTmpResult : ResourceStr | undefined = accessibilityTextTmpBuf
        const accessibilityDescriptionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityDescriptionTmpBuf : ResourceStr | undefined = undefined
        if ((accessibilityDescriptionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const accessibilityDescriptionTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let accessibilityDescriptionTmpBuf_ : string | Resource | undefined
            if (accessibilityDescriptionTmpBuf_UnionSelector == (0).toChar()) {
                accessibilityDescriptionTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (accessibilityDescriptionTmpBuf_UnionSelector == (1).toChar()) {
                accessibilityDescriptionTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for accessibilityDescriptionTmpBuf_ has to be chosen through deserialisation.")
            }
            accessibilityDescriptionTmpBuf = (accessibilityDescriptionTmpBuf_ as string | Resource)
        }
        const accessibilityDescriptionTmpResult : ResourceStr | undefined = accessibilityDescriptionTmpBuf
        const accessibilityLevelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityLevelTmpBuf : string | undefined = undefined
        if ((accessibilityLevelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accessibilityLevelTmpBuf = (valueDeserializer.readString() as string)
        }
        const accessibilityLevelTmpResult : string | undefined = accessibilityLevelTmpBuf
        const accessibilityGroupTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityGroupTmpBuf : boolean | undefined = undefined
        if ((accessibilityGroupTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accessibilityGroupTmpBuf = valueDeserializer.readBoolean()
        }
        const accessibilityGroupTmpResult : boolean | undefined = accessibilityGroupTmpBuf
        let value : SliderPrefixOptions = ({accessibilityText: accessibilityTextTmpResult, accessibilityDescription: accessibilityDescriptionTmpResult, accessibilityLevel: accessibilityLevelTmpResult, accessibilityGroup: accessibilityGroupTmpResult} as SliderPrefixOptions)
        return value
    }
}
export class SliderStepItemAccessibility_serializer {
    public static write(buffer: SerializerBase, value: SliderStepItemAccessibility): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForText  = value.text
        if (valueHolderForText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextTmpValue  = valueHolderForText!
            if (valueHolderForTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextTmpValueForIdx0  = valueHolderForTextTmpValue as string
                valueSerializer.writeString(valueHolderForTextTmpValueForIdx0)
            } else if (valueHolderForTextTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextTmpValueForIdx1  = valueHolderForTextTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SliderStepItemAccessibility {
        let valueDeserializer : DeserializerBase = buffer
        const textTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textTmpBuf : ResourceStr | undefined = undefined
        if ((textTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textTmpBuf_ : string | Resource | undefined
            if (textTmpBuf_UnionSelector == (0).toChar()) {
                textTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (textTmpBuf_UnionSelector == (1).toChar()) {
                textTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for textTmpBuf_ has to be chosen through deserialisation.")
            }
            textTmpBuf = (textTmpBuf_ as string | Resource)
        }
        const textTmpResult : ResourceStr | undefined = textTmpBuf
        let value : SliderStepItemAccessibility = ({text: textTmpResult} as SliderStepItemAccessibility)
        return value
    }
}
export class SliderSuffixOptions_serializer {
    public static write(buffer: SerializerBase, value: SliderSuffixOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAccessibilityText  = value.accessibilityText
        if (valueHolderForAccessibilityText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityTextTmpValue  = valueHolderForAccessibilityText!
            if (valueHolderForAccessibilityTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAccessibilityTextTmpValueForIdx0  = valueHolderForAccessibilityTextTmpValue as string
                valueSerializer.writeString(valueHolderForAccessibilityTextTmpValueForIdx0)
            } else if (valueHolderForAccessibilityTextTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAccessibilityTextTmpValueForIdx1  = valueHolderForAccessibilityTextTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForAccessibilityTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityDescription  = value.accessibilityDescription
        if (valueHolderForAccessibilityDescription !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityDescriptionTmpValue  = valueHolderForAccessibilityDescription!
            if (valueHolderForAccessibilityDescriptionTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAccessibilityDescriptionTmpValueForIdx0  = valueHolderForAccessibilityDescriptionTmpValue as string
                valueSerializer.writeString(valueHolderForAccessibilityDescriptionTmpValueForIdx0)
            } else if (valueHolderForAccessibilityDescriptionTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAccessibilityDescriptionTmpValueForIdx1  = valueHolderForAccessibilityDescriptionTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForAccessibilityDescriptionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityLevel  = value.accessibilityLevel
        if (valueHolderForAccessibilityLevel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityLevelTmpValue  = valueHolderForAccessibilityLevel!
            valueSerializer.writeString(valueHolderForAccessibilityLevelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityGroup  = value.accessibilityGroup
        if (valueHolderForAccessibilityGroup !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityGroupTmpValue  = valueHolderForAccessibilityGroup!
            valueSerializer.writeBoolean(valueHolderForAccessibilityGroupTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SliderSuffixOptions {
        let valueDeserializer : DeserializerBase = buffer
        const accessibilityTextTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityTextTmpBuf : ResourceStr | undefined = undefined
        if ((accessibilityTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const accessibilityTextTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let accessibilityTextTmpBuf_ : string | Resource | undefined
            if (accessibilityTextTmpBuf_UnionSelector == (0).toChar()) {
                accessibilityTextTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (accessibilityTextTmpBuf_UnionSelector == (1).toChar()) {
                accessibilityTextTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for accessibilityTextTmpBuf_ has to be chosen through deserialisation.")
            }
            accessibilityTextTmpBuf = (accessibilityTextTmpBuf_ as string | Resource)
        }
        const accessibilityTextTmpResult : ResourceStr | undefined = accessibilityTextTmpBuf
        const accessibilityDescriptionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityDescriptionTmpBuf : ResourceStr | undefined = undefined
        if ((accessibilityDescriptionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const accessibilityDescriptionTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let accessibilityDescriptionTmpBuf_ : string | Resource | undefined
            if (accessibilityDescriptionTmpBuf_UnionSelector == (0).toChar()) {
                accessibilityDescriptionTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (accessibilityDescriptionTmpBuf_UnionSelector == (1).toChar()) {
                accessibilityDescriptionTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for accessibilityDescriptionTmpBuf_ has to be chosen through deserialisation.")
            }
            accessibilityDescriptionTmpBuf = (accessibilityDescriptionTmpBuf_ as string | Resource)
        }
        const accessibilityDescriptionTmpResult : ResourceStr | undefined = accessibilityDescriptionTmpBuf
        const accessibilityLevelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityLevelTmpBuf : string | undefined = undefined
        if ((accessibilityLevelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accessibilityLevelTmpBuf = (valueDeserializer.readString() as string)
        }
        const accessibilityLevelTmpResult : string | undefined = accessibilityLevelTmpBuf
        const accessibilityGroupTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accessibilityGroupTmpBuf : boolean | undefined = undefined
        if ((accessibilityGroupTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accessibilityGroupTmpBuf = valueDeserializer.readBoolean()
        }
        const accessibilityGroupTmpResult : boolean | undefined = accessibilityGroupTmpBuf
        let value : SliderSuffixOptions = ({accessibilityText: accessibilityTextTmpResult, accessibilityDescription: accessibilityDescriptionTmpResult, accessibilityLevel: accessibilityLevelTmpResult, accessibilityGroup: accessibilityGroupTmpResult} as SliderSuffixOptions)
        return value
    }
}
