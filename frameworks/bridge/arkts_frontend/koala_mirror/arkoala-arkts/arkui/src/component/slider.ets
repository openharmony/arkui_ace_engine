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
import { Resource_serializer, Resource } from "./../generated/resource"
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { SizeOptions_serializer, ResourceColor, Length, Dimension, SizeOptions, ResourceStr } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, Bindable, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier, Bindable_Number_serializer } from "./common"
import { Color, CrownSensitivity, Axis } from "./enums"
import { ContentModifier, AttributeModifier, hookSliderContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkSliderPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setBlockColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof Color) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0ForIdx0))
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toChar())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof LinearGradient) {
                thisSerializer.writeInt8((1).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof Color) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0ForIdx0))
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toChar())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof LinearGradient) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as LinearGradient
                LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowStepsAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setShowSteps(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackThicknessAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setTrackThickness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value: number,mode: SliderChangeMode) => void) | undefined): void {
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
            thisSerializer.writeInt32(TypeChecker.SliderInteraction_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSliderInteractionMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinResponsiveDistanceAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
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
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(valueTmpValue))
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
                thisSerializer.writeInt8((0).toChar())
                const contentTmpValueForIdx0  = contentTmpValue as string
                thisSerializer.writeString(contentTmpValueForIdx0)
            } else if (contentTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
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
    from?: number;
    to?: number;
}
export interface SliderOptions {
    value?: number | Bindable<number> | undefined;
    min?: number;
    max?: number;
    step?: number;
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
}
export type SliderTriggerChangeCallback = (value: number, mode: SliderChangeMode) => void;
export interface SliderConfiguration extends CommonConfiguration<SliderConfiguration> {
    value: number;
    min: number;
    max: number;
    step: number;
    triggerChange: SliderTriggerChangeCallback;
}
export interface SliderAttribute extends CommonMethod {
    blockColor(value: ResourceColor | undefined): this {
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
    onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
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
    minResponsiveDistance(value: number | undefined): this {
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
    showTips(value: boolean | undefined, content?: ResourceStr): this {
        throw new Error("Unimplemented method showTips")
    }
    attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSliderStyle extends ArkCommonMethodStyle implements SliderAttribute {
    blockColor_value?: ResourceColor | undefined
    trackColor_value?: ResourceColor | LinearGradient | undefined
    selectedColor_value?: ResourceColor | LinearGradient | undefined
    showSteps_value?: boolean | undefined
    trackThickness_value?: Length | undefined
    onChange_value?: ((value: number,mode: SliderChangeMode) => void) | undefined
    blockBorderColor_value?: ResourceColor | undefined
    blockBorderWidth_value?: Length | undefined
    stepColor_value?: ResourceColor | undefined
    trackBorderRadius_value?: Length | undefined
    selectedBorderRadius_value?: Dimension | undefined
    blockSize_value?: SizeOptions | undefined
    blockStyle_value?: SliderBlockStyle | undefined
    stepSize_value?: Length | undefined
    sliderInteractionMode_value?: SliderInteraction | undefined
    minResponsiveDistance_value?: number | undefined
    contentModifier_value?: ContentModifier<SliderConfiguration> | undefined
    slideRange_value?: SlideRange | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined
    public blockColor(value: ResourceColor | undefined): this {
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public showSteps(value: boolean | undefined): this {
        return this
    }
    public trackThickness(value: Length | undefined): this {
        return this
    }
    public onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        return this
    }
    public blockBorderColor(value: ResourceColor | undefined): this {
        return this
    }
    public blockBorderWidth(value: Length | undefined): this {
        return this
    }
    public stepColor(value: ResourceColor | undefined): this {
        return this
    }
    public trackBorderRadius(value: Length | undefined): this {
        return this
    }
    public selectedBorderRadius(value: Dimension | undefined): this {
        return this
    }
    public blockSize(value: SizeOptions | undefined): this {
        return this
    }
    public blockStyle(value: SliderBlockStyle | undefined): this {
        return this
    }
    public stepSize(value: Length | undefined): this {
        return this
    }
    public sliderInteractionMode(value: SliderInteraction | undefined): this {
        return this
    }
    public minResponsiveDistance(value: number | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        return this
    }
    public slideRange(value: SlideRange | undefined): this {
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public showTips(value: boolean | undefined, content?: ResourceStr): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkSliderComponent extends ArkCommonMethodComponent implements SliderAttribute {
    getPeer(): ArkSliderPeer {
        return (this.peer as ArkSliderPeer)
    }
    public setSliderOptions(options?: SliderOptions): this {
        if (this.checkPriority("setSliderOptions")) {
            const options_casted = options as (SliderOptions | undefined)
            this.getPeer()?.setSliderOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public blockColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("blockColor")) {
            const value_casted = value as (ResourceColor | undefined)
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
            this.getPeer()?.setShowStepsAttribute(value_casted)
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
    public onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: number,mode: SliderChangeMode) => void) | undefined)
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
    public minResponsiveDistance(value: number | undefined): this {
        if (this.checkPriority("minResponsiveDistance")) {
            const value_casted = value as (number | undefined)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Slider(
    @memo
    style: ((attributes: SliderAttribute) => void) | undefined,
    options?: SliderOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSliderComponent>((): ArkSliderComponent => {
        return new ArkSliderComponent()
    })
    NodeAttach<ArkSliderPeer>((): ArkSliderPeer => ArkSliderPeer.create(receiver), (_: ArkSliderPeer): void => {
        receiver.setSliderOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class SliderModifier extends CommonMethodModifier implements SliderAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _blockColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockColor_0_0value?: ResourceColor | undefined
    _trackColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackColor_0_0value?: ResourceColor | LinearGradient | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | LinearGradient | undefined
    _showSteps_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showSteps_0_0value?: boolean | undefined
    _trackThickness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackThickness_0_0value?: Length | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value: number,mode: SliderChangeMode) => void) | undefined
    _blockBorderColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockBorderColor_0_0value?: ResourceColor | undefined
    _blockBorderWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockBorderWidth_0_0value?: Length | undefined
    _stepColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stepColor_0_0value?: ResourceColor | undefined
    _trackBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackBorderRadius_0_0value?: Length | undefined
    _selectedBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBorderRadius_0_0value?: Dimension | undefined
    _blockSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockSize_0_0value?: SizeOptions | undefined
    _blockStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockStyle_0_0value?: SliderBlockStyle | undefined
    _stepSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stepSize_0_0value?: Length | undefined
    _sliderInteractionMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sliderInteractionMode_0_0value?: SliderInteraction | undefined
    _minResponsiveDistance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minResponsiveDistance_0_0value?: number | undefined
    _slideRange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _slideRange_0_0value?: SlideRange | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _showTips_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showTips_0_0value?: boolean | undefined
    _showTips_0_1value?: ResourceStr | undefined
    applyModifierPatch(peer: ArkSliderPeer): void {
        super.applyModifierPatch(peer)
        if (this._blockColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockColorAttribute((this._blockColor_0_0value as ResourceColor | undefined));
                    this._blockColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._trackColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackColorAttribute((this._trackColor_0_0value as ResourceColor | LinearGradient | undefined));
                    this._trackColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | LinearGradient | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._showSteps_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showSteps_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowStepsAttribute((this._showSteps_0_0value as boolean | undefined));
                    this._showSteps_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showSteps_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showSteps_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowStepsAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._trackThickness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackThickness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackThicknessAttribute((this._trackThickness_0_0value as Length | undefined));
                    this._trackThickness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackThickness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackThickness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackThicknessAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value: number,mode: SliderChangeMode) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value: number,mode: SliderChangeMode) => void) | undefined));
                }
            }
        }
        if (this._blockBorderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockBorderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockBorderColorAttribute((this._blockBorderColor_0_0value as ResourceColor | undefined));
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockBorderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._blockBorderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockBorderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockBorderWidthAttribute((this._blockBorderWidth_0_0value as Length | undefined));
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockBorderWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._stepColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStepColorAttribute((this._stepColor_0_0value as ResourceColor | undefined));
                    this._stepColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStepColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._trackBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackBorderRadiusAttribute((this._trackBorderRadius_0_0value as Length | undefined));
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackBorderRadiusAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._selectedBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedBorderRadiusAttribute((this._selectedBorderRadius_0_0value as Dimension | undefined));
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedBorderRadiusAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._blockSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockSizeAttribute((this._blockSize_0_0value as SizeOptions | undefined));
                    this._blockSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (this._blockStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockStyleAttribute((this._blockStyle_0_0value as SliderBlockStyle | undefined));
                    this._blockStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockStyleAttribute((undefined as SliderBlockStyle | undefined));
                }
            }
        }
        if (this._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStepSizeAttribute((this._stepSize_0_0value as Length | undefined));
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStepSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._sliderInteractionMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sliderInteractionMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSliderInteractionModeAttribute((this._sliderInteractionMode_0_0value as SliderInteraction | undefined));
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSliderInteractionModeAttribute((undefined as SliderInteraction | undefined));
                }
            }
        }
        if (this._minResponsiveDistance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minResponsiveDistance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinResponsiveDistanceAttribute((this._minResponsiveDistance_0_0value as number | undefined));
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinResponsiveDistanceAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._slideRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._slideRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSlideRangeAttribute((this._slideRange_0_0value as SlideRange | undefined));
                    this._slideRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._slideRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._slideRange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSlideRangeAttribute((undefined as SlideRange | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._showTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowTipsAttribute((this._showTips_0_0value as boolean | undefined), (this._showTips_0_1value as ResourceStr | undefined));
                    this._showTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showTips_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowTipsAttribute((undefined as boolean | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SliderModifier): void {
        super.mergeModifier(modifier)
        if (modifier._blockColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockColor(modifier._blockColor_0_0value);
                    break;
                }
                default: {
                    this.blockColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._trackColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackColor(modifier._trackColor_0_0value);
                    break;
                }
                default: {
                    this.trackColor((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (modifier._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (modifier._showSteps_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showSteps_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showSteps(modifier._showSteps_0_0value);
                    break;
                }
                default: {
                    this.showSteps((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._trackThickness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackThickness_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackThickness(modifier._trackThickness_0_0value);
                    break;
                }
                default: {
                    this.trackThickness((undefined as Length | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value: number,mode: SliderChangeMode) => void) | undefined));
                }
            }
        }
        if (modifier._blockBorderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockBorderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockBorderColor(modifier._blockBorderColor_0_0value);
                    break;
                }
                default: {
                    this.blockBorderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._blockBorderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockBorderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockBorderWidth(modifier._blockBorderWidth_0_0value);
                    break;
                }
                default: {
                    this.blockBorderWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._stepColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stepColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stepColor(modifier._stepColor_0_0value);
                    break;
                }
                default: {
                    this.stepColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._trackBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackBorderRadius(modifier._trackBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.trackBorderRadius((undefined as Length | undefined));
                }
            }
        }
        if (modifier._selectedBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedBorderRadius(modifier._selectedBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.selectedBorderRadius((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._blockSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockSize(modifier._blockSize_0_0value);
                    break;
                }
                default: {
                    this.blockSize((undefined as SizeOptions | undefined));
                }
            }
        }
        if (modifier._blockStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockStyle(modifier._blockStyle_0_0value);
                    break;
                }
                default: {
                    this.blockStyle((undefined as SliderBlockStyle | undefined));
                }
            }
        }
        if (modifier._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stepSize(modifier._stepSize_0_0value);
                    break;
                }
                default: {
                    this.stepSize((undefined as Length | undefined));
                }
            }
        }
        if (modifier._sliderInteractionMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sliderInteractionMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sliderInteractionMode(modifier._sliderInteractionMode_0_0value);
                    break;
                }
                default: {
                    this.sliderInteractionMode((undefined as SliderInteraction | undefined));
                }
            }
        }
        if (modifier._minResponsiveDistance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minResponsiveDistance_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minResponsiveDistance(modifier._minResponsiveDistance_0_0value);
                    break;
                }
                default: {
                    this.minResponsiveDistance((undefined as number | undefined));
                }
            }
        }
        if (modifier._slideRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._slideRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.slideRange(modifier._slideRange_0_0value);
                    break;
                }
                default: {
                    this.slideRange((undefined as SlideRange | undefined));
                }
            }
        }
        if (modifier._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._showTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showTips(modifier._showTips_0_0value, modifier._showTips_0_1value);
                    break;
                }
                default: {
                    this.showTips((undefined as boolean | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
    }
    blockColor(value: ResourceColor | undefined): this {
        if (((this._blockColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockColor_0_0value = value
        } else
        {
            this._blockColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackColor(value: ResourceColor | LinearGradient | undefined): this {
        if (((this._trackColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackColor_0_0value = value
        } else
        {
            this._trackColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        if (((this._selectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedColor_0_0value = value
        } else
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showSteps(value: boolean | undefined): this {
        if (((this._showSteps_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showSteps_0_0value) !== (value)))
        {
            this._showSteps_0_flag = AttributeUpdaterFlag.UPDATE
            this._showSteps_0_0value = value
        } else
        {
            this._showSteps_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackThickness(value: Length | undefined): this {
        if (((this._trackThickness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackThickness_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackThickness_0_0value = value
        } else
        {
            this._trackThickness_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockBorderColor(value: ResourceColor | undefined): this {
        if (((this._blockBorderColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockBorderColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockBorderColor_0_0value = value
        } else
        {
            this._blockBorderColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockBorderWidth(value: Length | undefined): this {
        if (((this._blockBorderWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockBorderWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockBorderWidth_0_0value = value
        } else
        {
            this._blockBorderWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stepColor(value: ResourceColor | undefined): this {
        if (((this._stepColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._stepColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._stepColor_0_0value = value
        } else
        {
            this._stepColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackBorderRadius(value: Length | undefined): this {
        if (((this._trackBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackBorderRadius_0_0value = value
        } else
        {
            this._trackBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedBorderRadius(value: Dimension | undefined): this {
        if (((this._selectedBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBorderRadius_0_0value = value
        } else
        {
            this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockSize(value: SizeOptions | undefined): this {
        if (((this._blockSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockSize_0_0value = value
        } else
        {
            this._blockSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockStyle(value: SliderBlockStyle | undefined): this {
        if (((this._blockStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockStyle_0_0value = value
        } else
        {
            this._blockStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stepSize(value: Length | undefined): this {
        if (((this._stepSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._stepSize_0_0value = value
        } else
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sliderInteractionMode(value: SliderInteraction | undefined): this {
        if (((this._sliderInteractionMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._sliderInteractionMode_0_0value = value
        } else
        {
            this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minResponsiveDistance(value: number | undefined): this {
        if (((this._minResponsiveDistance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minResponsiveDistance_0_0value) !== (value)))
        {
            this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.UPDATE
            this._minResponsiveDistance_0_0value = value
        } else
        {
            this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    slideRange(value: SlideRange | undefined): this {
        if (((this._slideRange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._slideRange_0_flag = AttributeUpdaterFlag.UPDATE
            this._slideRange_0_0value = value
        } else
        {
            this._slideRange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._digitalCrownSensitivity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.UPDATE
            this._digitalCrownSensitivity_0_0value = value
        } else
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showTips(value: boolean | undefined, content?: ResourceStr): this {
        if (((this._showTips_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showTips_0_0value) !== (value)) || (true))
        {
            this._showTips_0_flag = AttributeUpdaterFlag.UPDATE
            this._showTips_0_0value = value
            this._showTips_0_1value = content
        } else
        {
            this._showTips_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SlideRange_serializer {
    public static write(buffer: SerializerBase, value: SlideRange): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFrom  = value.from
        if (valueHolderForFrom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFromTmpValue  = valueHolderForFrom!
            valueSerializer.writeNumber(valueHolderForFromTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTo  = value.to
        if (valueHolderForTo !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForToTmpValue  = valueHolderForTo!
            valueSerializer.writeNumber(valueHolderForToTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SlideRange {
        let valueDeserializer : DeserializerBase = buffer
        const fromTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fromTmpBuf : number | undefined
        if ((fromTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fromTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const fromTmpResult : number | undefined = fromTmpBuf
        const toTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let toTmpBuf : number | undefined
        if ((toTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            toTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const toTmpResult : number | undefined = toTmpBuf
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
        valueSerializer.writeNumber(valueHolderForValue)
        const valueHolderForMin  = value.min
        valueSerializer.writeNumber(valueHolderForMin)
        const valueHolderForMax  = value.max
        valueSerializer.writeNumber(valueHolderForMax)
        const valueHolderForStep  = value.step
        valueSerializer.writeNumber(valueHolderForStep)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): SliderConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<SliderConfiguration> = (valueDeserializer.readObject() as ContentModifier<SliderConfiguration>)
        const valueTmpResult : number = (valueDeserializer.readNumber() as number)
        const minTmpResult : number = (valueDeserializer.readNumber() as number)
        const maxTmpResult : number = (valueDeserializer.readNumber() as number)
        const stepTmpResult : number = (valueDeserializer.readNumber() as number)
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpResult : SliderTriggerChangeCallback = (value: number, mode: SliderChangeMode):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeNumber(value);
            triggerChangeTmpBufBufArgsSerializer.writeInt32(TypeChecker.SliderChangeMode_ToNumeric(mode));
            InteropNativeModule._CallCallback(711649376, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        let value : SliderConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, value: valueTmpResult, min: minTmpResult, max: maxTmpResult, step: stepTmpResult, triggerChange: triggerChangeTmpResult} as SliderConfiguration)
        return value
    }
}
export class SliderBlockStyle_serializer {
    public static write(buffer: SerializerBase, value: SliderBlockStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(TypeChecker.SliderBlockType_ToNumeric(valueHolderForType))
        const valueHolderForImage  = value.image
        if (valueHolderForImage !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageTmpValue  = valueHolderForImage!
            if (valueHolderForImageTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForImageTmpValueForIdx0  = valueHolderForImageTmpValue as string
                valueSerializer.writeString(valueHolderForImageTmpValueForIdx0)
            } else if (valueHolderForImageTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForImageTmpValueForIdx1  = valueHolderForImageTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForImageTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SliderBlockStyle {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : SliderBlockType = TypeChecker.SliderBlockType_FromNumeric(valueDeserializer.readInt32())
        const imageTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let imageTmpBuf : ResourceStr | undefined
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
        let value : SliderBlockStyle = ({type: typeTmpResult, image: imageTmpResult} as SliderBlockStyle)
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
            if (valueHolderForValueTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as number
                valueSerializer.writeNumber(valueHolderForValueTmpValueForIdx0)
            } else if (valueHolderForValueTmpValue instanceof Bindable<number>) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as Bindable<number>
                Bindable_Number_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMin  = value.min
        if (valueHolderForMin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinTmpValue  = valueHolderForMin!
            valueSerializer.writeNumber(valueHolderForMinTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMax  = value.max
        if (valueHolderForMax !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxTmpValue  = valueHolderForMax!
            valueSerializer.writeNumber(valueHolderForMaxTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStep  = value.step
        if (valueHolderForStep !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStepTmpValue  = valueHolderForStep!
            valueSerializer.writeNumber(valueHolderForStepTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as SliderStyle)
            valueSerializer.writeInt32(TypeChecker.SliderStyle_ToNumeric(valueHolderForStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDirection  = value.direction
        if (valueHolderForDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDirectionTmpValue  = (valueHolderForDirection as Axis)
            valueSerializer.writeInt32(TypeChecker.Axis_ToNumeric(valueHolderForDirectionTmpValue))
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
        let valueTmpBuf : number | Bindable<number> | undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBuf_ : number | Bindable<number> | undefined
            if (valueTmpBuf_UnionSelector == (0).toChar()) {
                valueTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (valueTmpBuf_UnionSelector == (1).toChar()) {
                valueTmpBuf_ = Bindable_Number_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for valueTmpBuf_ has to be chosen through deserialisation.")
            }
            valueTmpBuf = (valueTmpBuf_ as number | Bindable<number>)
        }
        const valueTmpResult : number | Bindable<number> | undefined = valueTmpBuf
        const minTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minTmpBuf : number | undefined
        if ((minTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            minTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const minTmpResult : number | undefined = minTmpBuf
        const maxTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxTmpBuf : number | undefined
        if ((maxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const maxTmpResult : number | undefined = maxTmpBuf
        const stepTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stepTmpBuf : number | undefined
        if ((stepTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stepTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const stepTmpResult : number | undefined = stepTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : SliderStyle | undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = TypeChecker.SliderStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const styleTmpResult : SliderStyle | undefined = styleTmpBuf
        const directionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let directionTmpBuf : Axis | undefined
        if ((directionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            directionTmpBuf = TypeChecker.Axis_FromNumeric(valueDeserializer.readInt32())
        }
        const directionTmpResult : Axis | undefined = directionTmpBuf
        const reverseTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let reverseTmpBuf : boolean | undefined
        if ((reverseTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            reverseTmpBuf = valueDeserializer.readBoolean()
        }
        const reverseTmpResult : boolean | undefined = reverseTmpBuf
        let value : SliderOptions = ({value: valueTmpResult, min: minTmpResult, max: maxTmpResult, step: stepTmpResult, style: styleTmpResult, direction: directionTmpResult, reverse: reverseTmpResult} as SliderOptions)
        return value
    }
}
