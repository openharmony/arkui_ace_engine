/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { image_PixelMap_serializer } from './../framework/ohos.multimedia.image'
import { global_resource_Resource_serializer } from './../framework/resource'
import { DrawableDescriptor_serializer } from './../framework/ohos.arkui.drawableDescriptor'
import { ImageAIOptions_serializer, ImageAnalyzerConfig_serializer, ImageAnalyzerConfig, ImageAIOptions } from './imageCommon'
import { ColorMetricsExt, ColorMetricsExt_serializer, BusinessErrorInterface, BusinessErrorInterface_Void_serializer } from './idlize'
import { extractors, AttributeModifier, hookImageOnError, hookImageAttributeModifier, AttributeUpdater } from '#handwritten'
import { matrix4_Matrix4Transit_serializer } from './../framework/ohos.matrix4'
import { ColorFilter_serializer, ResourceColor, Resource as arkui_component_units_Resource, ColorMetrics as arkui_component_units_ColorMetrics, ColorFilter, VoidCallback, ResourceStr, EdgeWidths, EdgeWidths_serializer } from './units'
import { drawing_ColorFilter_serializer, drawing_Lattice_serializer } from './../framework/ohos.graphics.drawing'
import { PointLightStyle_serializer, ContentTransitionEffect_serializer, ArkCommonMethodPeer, CommonMethod, PixelMap, PointLightStyle, ContentTransitionEffect, ArkCommonMethodComponent } from './common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { Resource as global_resource_Resource } from 'global.resource'
import { default as image } from '@ohos.multimedia.image'
import { Color as arkui_component_enums_Color, ImageFit, ImageRepeat, CopyOptions } from './enums'
import { ColorMetrics as arkui_Graphics_ColorMetrics } from 'arkui.Graphics'
import { default as matrix4 } from '@ohos.matrix4'
import { default as drawing } from '@ohos.graphics.drawing'
import { DrawableDescriptor } from '@ohos.arkui.drawableDescriptor'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { default as cacheDownload } from '@ohos.request.cacheDownload'
import { BusinessError } from '@ohos.base'
import { ImageModifier } from './../ImageModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { cacheDownload_DownloadInfo_serializer } from './../framework/ohos.request.cacheDownload'
export class ColorContentInternal {
    public static fromPtr(ptr: KPointer): ColorContent {
        return new ColorContent(MaterializedBaseTag.NOP, ptr)
    }
}
export class ColorContent implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public static readonly ORIGIN: ColorContent = ColorContent.getORIGIN()
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ColorContent.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ColorContent.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ColorContent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorContent_getFinalizer()
    }
    private static getORIGIN(): ColorContent {
        return ColorContent.getORIGIN_serialize()
    }
    private static getORIGIN_serialize(): ColorContent {
        const retval = ArkUIGeneratedNativeModule._ColorContent_getORIGIN()
        const obj: ColorContent = ColorContentInternal.fromPtr(retval)
        return obj
    }
}
export class ArkImagePeer extends ArkCommonMethodPeer {
    attributeSet?: ImageModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImagePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Image_construct(peerId, flags)
        const _peer = new ArkImagePeer(_peerPtr, peerId, 'Image', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageOptionsAttribute(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (src !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const srcTmpValue = src!
            if (srcTmpValue instanceof PixelMap) {
                thisSerializer.writeInt8((0).toByte())
                const srcTmpValueForIdx0 = srcTmpValue as PixelMap
                image_PixelMap_serializer.write(thisSerializer, srcTmpValueForIdx0)
            } else if (srcTmpValue instanceof ResourceStr) {
                thisSerializer.writeInt8((1).toByte())
                const srcTmpValueForIdx1 = srcTmpValue as ResourceStr
                if (srcTmpValueForIdx1 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const srcTmpValueForIdx1ForIdx0 = srcTmpValueForIdx1 as string
                    thisSerializer.writeString(srcTmpValueForIdx1ForIdx0)
                } else if (srcTmpValueForIdx1 instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((1).toByte())
                    const srcTmpValueForIdx1ForIdx1 = srcTmpValueForIdx1 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, srcTmpValueForIdx1ForIdx1)
                }
            } else if (srcTmpValue instanceof DrawableDescriptor) {
                thisSerializer.writeInt8((2).toByte())
                const srcTmpValueForIdx2 = srcTmpValue as DrawableDescriptor
                DrawableDescriptor_serializer.write(thisSerializer, srcTmpValueForIdx2)
            } else if (srcTmpValue instanceof ImageContent) {
                thisSerializer.writeInt8((3).toByte())
                const srcTmpValueForIdx3 = srcTmpValue as ImageContent
                thisSerializer.writeInt32(srcTmpValueForIdx3.valueOf())
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (imageAIOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const imageAIOptionsTmpValue = imageAIOptions!
            ImageAIOptions_serializer.write(thisSerializer, imageAIOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAltAttribute(value: string | global_resource_Resource | PixelMap | ImageAlt | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof PixelMap) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2 = valueTmpValue as PixelMap
                image_PixelMap_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof ImageAlt) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3 = valueTmpValue as ImageAlt
                ImageAlt_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setAlt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMatchTextDirectionAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setMatchTextDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFitOriginalSizeAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setFitOriginalSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillColorAttribute(value: ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof ResourceColor) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof arkui_component_enums_Color) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0 = valueTmpValueForIdx0 as arkui_component_enums_Color
                    thisSerializer.writeInt32((valueTmpValueForIdx0ForIdx0.getOrdinal()) % (12))
                } else if (valueTmpValueForIdx0 instanceof int32) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1 = valueTmpValueForIdx0 as int32
                    thisSerializer.writeInt32(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2 = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueForIdx0ForIdx3 = valueTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof ColorContent) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as ColorContent
                ColorContent_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_ColorMetrics) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2 = valueTmpValue as arkui_component_units_ColorMetrics
                const valueTmpValueForIdx2Transformed: ColorMetricsExt = extractors.transform_Ark_ColorMetrics_to_Ark_ColorMetricsExt(valueTmpValueForIdx2)
                ColorMetricsExt_serializer.write(thisSerializer, valueTmpValueForIdx2Transformed)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setFillColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as ImageFit)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setObjectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageMatrixAttribute(value: ImageMatrix | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            matrix4_Matrix4Transit_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setImageMatrix(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectRepeatAttribute(value: ImageRepeat | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as ImageRepeat)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setObjectRepeat(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoResizeAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setAutoResize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderModeAttribute(value: ImageRenderMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as ImageRenderMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setRenderMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDynamicRangeModeAttribute(value: DynamicRangeMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as DynamicRangeMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setDynamicRangeMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHdrBrightnessAttribute(value: double | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setHdrBrightness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInterpolationAttribute(value: ImageInterpolation | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as ImageInterpolation)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setInterpolation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSourceSizeAttribute(value: ImageSourceSize | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            ImageSourceSize_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setSourceSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSyncLoadAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setSyncLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorFilterAttribute(value: ColorFilter | DrawingColorFilter | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof ColorFilter) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as ColorFilter
                ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof DrawingColorFilter) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as DrawingColorFilter
                drawing_ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setColorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as CopyOptions)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDraggableAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setDraggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            PointLightStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeAntialiasingAttribute(value: double | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setEdgeAntialiasing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCompleteAttribute(value: ImageOnCompleteCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ImageErrorCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFinishAttribute(value: VoidCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOnFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnalyzerAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setEnableAnalyzer(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnalyzerConfigAttribute(value: ImageAnalyzerConfig | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            ImageAnalyzerConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setAnalyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setResizableAttribute(value: ResizableOptions | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            ResizableOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setResizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnhancedImageQualityAttribute(value: ResolutionQuality | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as ResolutionQuality)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setEnhancedImageQuality(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOrientationAttribute(value: ImageRotateOrientation | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as ImageRotateOrientation)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setOrientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSupportSvg2Attribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setSupportSvg2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentTransitionAttribute(value: ContentTransitionEffect | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            ContentTransitionEffect_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAntialiasedAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_setAntialiased(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type DrawingColorFilter = drawing.ColorFilter;
export type ResolutionQuality = image.ResolutionQuality;
export type DrawingLattice = drawing.Lattice;
export type ImageMatrix = matrix4.Matrix4Transit;
export type RequestDownloadInfo = cacheDownload.DownloadInfo;
export enum ImageRenderMode {
    Original = 0,
    Template = 1
}
export enum ImageContent {
    EMPTY = 0
}
export enum DynamicRangeMode {
    HIGH = 0,
    CONSTRAINT = 1,
    STANDARD = 2
}
export enum ImageInterpolation {
    None = 0,
    Low = 1,
    Medium = 2,
    High = 3
}
export enum ImageRotateOrientation {
    AUTO = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
    UP_MIRRORED = 5,
    RIGHT_MIRRORED = 6,
    DOWN_MIRRORED = 7,
    LEFT_MIRRORED = 8
}
export interface ImageCompleteEvent {
    width: int32;
    height: int32;
    componentWidth: int32;
    componentHeight: int32;
    loadingStatus: int32;
    contentWidth: int32;
    contentHeight: int32;
    contentOffsetX: int32;
    contentOffsetY: int32;
}
export interface ImageSourceSize {
    width: double;
    height: double;
}
export interface ImageAlt {
    placeholder?: ResourceStr | PixelMap;
    error?: ResourceStr | PixelMap;
}
export interface ImageAttribute extends CommonMethod {
    setImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): this {
        throw new Error('Unimplemented method setImageOptions')
    }
    alt(value: string | global_resource_Resource | PixelMap | ImageAlt | undefined): this {
        throw new Error('Unimplemented method alt')
    }
    matchTextDirection(value: boolean | undefined): this {
        throw new Error('Unimplemented method matchTextDirection')
    }
    fitOriginalSize(value: boolean | undefined): this {
        throw new Error('Unimplemented method fitOriginalSize')
    }
    fillColor(value: ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined): this {
        throw new Error('Unimplemented method fillColor')
    }
    objectFit(value: ImageFit | undefined): this {
        throw new Error('Unimplemented method objectFit')
    }
    imageMatrix(value: ImageMatrix | undefined): this {
        throw new Error('Unimplemented method imageMatrix')
    }
    objectRepeat(value: ImageRepeat | undefined): this {
        throw new Error('Unimplemented method objectRepeat')
    }
    autoResize(value: boolean | undefined): this {
        throw new Error('Unimplemented method autoResize')
    }
    renderMode(value: ImageRenderMode | undefined): this {
        throw new Error('Unimplemented method renderMode')
    }
    dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        throw new Error('Unimplemented method dynamicRangeMode')
    }
    hdrBrightness(value: double | undefined): this {
        throw new Error('Unimplemented method hdrBrightness')
    }
    interpolation(value: ImageInterpolation | undefined): this {
        throw new Error('Unimplemented method interpolation')
    }
    sourceSize(value: ImageSourceSize | undefined): this {
        throw new Error('Unimplemented method sourceSize')
    }
    syncLoad(value: boolean | undefined): this {
        throw new Error('Unimplemented method syncLoad')
    }
    colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        throw new Error('Unimplemented method colorFilter')
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error('Unimplemented method copyOption')
    }
    draggable(value: boolean | undefined): this
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error('Unimplemented method pointLight')
    }
    edgeAntialiasing(value: double | undefined): this {
        throw new Error('Unimplemented method edgeAntialiasing')
    }
    onComplete(value: ImageOnCompleteCallback | undefined): this {
        throw new Error('Unimplemented method onComplete')
    }
    onError(value: ImageErrorCallback | undefined): this {
        throw new Error('Unimplemented method onError')
    }
    onFinish(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onFinish')
    }
    enableAnalyzer(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableAnalyzer')
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        throw new Error('Unimplemented method analyzerConfig')
    }
    resizable(value: ResizableOptions | undefined): this {
        throw new Error('Unimplemented method resizable')
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error('Unimplemented method privacySensitive')
    }
    enhancedImageQuality(value: ResolutionQuality | undefined): this {
        throw new Error('Unimplemented method enhancedImageQuality')
    }
    orientation(value: ImageRotateOrientation | undefined): this {
        throw new Error('Unimplemented method orientation')
    }
    supportSvg2(value: boolean | undefined): this {
        throw new Error('Unimplemented method supportSvg2')
    }
    contentTransition(value: ContentTransitionEffect | undefined): this {
        throw new Error('Unimplemented method contentTransition')
    }
    antialiased(value: boolean | undefined): this {
        throw new Error('Unimplemented method antialiased')
    }
    attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export type ImageErrorCallback = (error: ImageError) => void;
export type ImageOnCompleteCallback = (loadEvent?: ImageCompleteEvent) => void;
export interface ImageError {
    componentWidth: int32;
    componentHeight: int32;
    message: string;
    error?: BusinessError<void>;
    downloadInfo?: RequestDownloadInfo;
}
export interface ResizableOptions {
    slice?: EdgeWidths;
    lattice?: DrawingLattice;
}

export class ArkImageComponent extends ArkCommonMethodComponent implements ImageAttribute {
    getPeer(): ArkImagePeer {
        return (this.peer as ArkImagePeer)
    }
    public setImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined, imageAIOptions?: ImageAIOptions): this {
        const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined)
        const imageAIOptions_casted = imageAIOptions as (ImageAIOptions | undefined)
        this.getPeer()?.setImageOptionsAttribute(src_casted, imageAIOptions_casted)
        this.applyOptionsFinish('ImageAttribute');
        return this
    }
    public alt(value: string | global_resource_Resource | PixelMap | ImageAlt | undefined): this {
        const value_casted = value as (string | global_resource_Resource | PixelMap | ImageAlt | undefined)
        this.getPeer()?.setAltAttribute(value_casted)
        return this
    }
    public matchTextDirection(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMatchTextDirectionAttribute(value_casted)
        return this
    }
    public fitOriginalSize(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setFitOriginalSizeAttribute(value_casted)
        return this
    }
    public fillColor(value: ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined): this {
        const value_casted = value as (ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined)
        this.getPeer()?.setFillColorAttribute(value_casted)
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        const value_casted = value as (ImageFit | undefined)
        this.getPeer()?.setObjectFitAttribute(value_casted)
        return this
    }
    public imageMatrix(value: ImageMatrix | undefined): this {
        const value_casted = value as (ImageMatrix | undefined)
        this.getPeer()?.setImageMatrixAttribute(value_casted)
        return this
    }
    public objectRepeat(value: ImageRepeat | undefined): this {
        const value_casted = value as (ImageRepeat | undefined)
        this.getPeer()?.setObjectRepeatAttribute(value_casted)
        return this
    }
    public autoResize(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setAutoResizeAttribute(value_casted)
        return this
    }
    public renderMode(value: ImageRenderMode | undefined): this {
        const value_casted = value as (ImageRenderMode | undefined)
        this.getPeer()?.setRenderModeAttribute(value_casted)
        return this
    }
    public dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        const value_casted = value as (DynamicRangeMode | undefined)
        this.getPeer()?.setDynamicRangeModeAttribute(value_casted)
        return this
    }
    public hdrBrightness(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setHdrBrightnessAttribute(value_casted)
        return this
    }
    public interpolation(value: ImageInterpolation | undefined): this {
        const value_casted = value as (ImageInterpolation | undefined)
        this.getPeer()?.setInterpolationAttribute(value_casted)
        return this
    }
    public sourceSize(value: ImageSourceSize | undefined): this {
        const value_casted = value as (ImageSourceSize | undefined)
        this.getPeer()?.setSourceSizeAttribute(value_casted)
        return this
    }
    public syncLoad(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setSyncLoadAttribute(value_casted)
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        const value_casted = value as (ColorFilter | DrawingColorFilter | undefined)
        this.getPeer()?.setColorFilterAttribute(value_casted)
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        const value_casted = value as (CopyOptions | undefined)
        this.getPeer()?.setCopyOptionAttribute(value_casted)
        return this
    }
    public draggable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setDraggableAttribute(value_casted)
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        const value_casted = value as (PointLightStyle | undefined)
        this.getPeer()?.setPointLightAttribute(value_casted)
        return this
    }
    public edgeAntialiasing(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setEdgeAntialiasingAttribute(value_casted)
        return this
    }
    public onComplete(value: ImageOnCompleteCallback | undefined): this {
        const value_casted = value as (ImageOnCompleteCallback | undefined)
        this.getPeer()?.setOnCompleteAttribute(value_casted)
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        hookImageOnError(this, value)
        const value_casted = value as (ImageErrorCallback | undefined)
        this.getPeer()?.setOnErrorAttribute(value_casted)
        return this
    }
    public onFinish(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnFinishAttribute(value_casted)
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableAnalyzerAttribute(value_casted)
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        const value_casted = value as (ImageAnalyzerConfig | undefined)
        this.getPeer()?.setAnalyzerConfigAttribute(value_casted)
        return this
    }
    public resizable(value: ResizableOptions | undefined): this {
        const value_casted = value as (ResizableOptions | undefined)
        this.getPeer()?.setResizableAttribute(value_casted)
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
        return this
    }
    public enhancedImageQuality(value: ResolutionQuality | undefined): this {
        const value_casted = value as (ResolutionQuality | undefined)
        this.getPeer()?.setEnhancedImageQualityAttribute(value_casted)
        return this
    }
    public orientation(value: ImageRotateOrientation | undefined): this {
        const value_casted = value as (ImageRotateOrientation | undefined)
        this.getPeer()?.setOrientationAttribute(value_casted)
        return this
    }
    public supportSvg2(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setSupportSvg2Attribute(value_casted)
        return this
    }
    public contentTransition(value: ContentTransitionEffect | undefined): this {
        const value_casted = value as (ContentTransitionEffect | undefined)
        this.getPeer()?.setContentTransitionAttribute(value_casted)
        return this
    }
    public antialiased(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setAntialiasedAttribute(value_casted)
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookImageAttributeModifier(this, value);
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
export function ImageImpl(
    @memo @memo_skip
    style: ((attributes: ImageAttribute) => void) | undefined,
): void {
    const receiver = remember<ArkImageComponent>((): ArkImageComponent => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (_: ArkImagePeer): void => {
        style?.(receiver)
    })
}

export class ColorContent_serializer {
    public static write(buffer: SerializerBase, value: ColorContent): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ColorContent {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ColorContentInternal.fromPtr(ptr)
    }
}
export class ImageSourceSize_serializer {
    public static write(buffer: SerializerBase, value: ImageSourceSize): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForWidth = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): ImageSourceSize {
        let valueDeserializer: DeserializerBase = buffer
        const widthTmpResult: double = valueDeserializer.readFloat64()
        const heightTmpResult: double = valueDeserializer.readFloat64()
        let value: ImageSourceSize = ({width: widthTmpResult, height: heightTmpResult} as ImageSourceSize)
        return value
    }
}
export class ImageCompleteEvent_serializer {
    public static write(buffer: SerializerBase, value: ImageCompleteEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForWidth = value.width
        valueSerializer.writeInt32(valueHolderForWidth)
        const valueHolderForHeight = value.height
        valueSerializer.writeInt32(valueHolderForHeight)
        const valueHolderForComponentWidth = value.componentWidth
        valueSerializer.writeInt32(valueHolderForComponentWidth)
        const valueHolderForComponentHeight = value.componentHeight
        valueSerializer.writeInt32(valueHolderForComponentHeight)
        const valueHolderForLoadingStatus = value.loadingStatus
        valueSerializer.writeInt32(valueHolderForLoadingStatus)
        const valueHolderForContentWidth = value.contentWidth
        valueSerializer.writeInt32(valueHolderForContentWidth)
        const valueHolderForContentHeight = value.contentHeight
        valueSerializer.writeInt32(valueHolderForContentHeight)
        const valueHolderForContentOffsetX = value.contentOffsetX
        valueSerializer.writeInt32(valueHolderForContentOffsetX)
        const valueHolderForContentOffsetY = value.contentOffsetY
        valueSerializer.writeInt32(valueHolderForContentOffsetY)
    }
    public static read(buffer: DeserializerBase): ImageCompleteEvent {
        let valueDeserializer: DeserializerBase = buffer
        const widthTmpResult: int32 = valueDeserializer.readInt32()
        const heightTmpResult: int32 = valueDeserializer.readInt32()
        const componentWidthTmpResult: int32 = valueDeserializer.readInt32()
        const componentHeightTmpResult: int32 = valueDeserializer.readInt32()
        const loadingStatusTmpResult: int32 = valueDeserializer.readInt32()
        const contentWidthTmpResult: int32 = valueDeserializer.readInt32()
        const contentHeightTmpResult: int32 = valueDeserializer.readInt32()
        const contentOffsetXTmpResult: int32 = valueDeserializer.readInt32()
        const contentOffsetYTmpResult: int32 = valueDeserializer.readInt32()
        let value: ImageCompleteEvent = ({width: widthTmpResult, height: heightTmpResult, componentWidth: componentWidthTmpResult, componentHeight: componentHeightTmpResult, loadingStatus: loadingStatusTmpResult, contentWidth: contentWidthTmpResult, contentHeight: contentHeightTmpResult, contentOffsetX: contentOffsetXTmpResult, contentOffsetY: contentOffsetYTmpResult} as ImageCompleteEvent)
        return value
    }
}
export class ImageAlt_serializer {
    public static write(buffer: SerializerBase, value: ImageAlt): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForPlaceholder = value.placeholder
        if (valueHolderForPlaceholder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPlaceholderTmpValue = valueHolderForPlaceholder!
            if (valueHolderForPlaceholderTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPlaceholderTmpValueForIdx0 = valueHolderForPlaceholderTmpValue as ResourceStr
                if (valueHolderForPlaceholderTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForPlaceholderTmpValueForIdx0ForIdx0 = valueHolderForPlaceholderTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForPlaceholderTmpValueForIdx0ForIdx0)
                } else if (valueHolderForPlaceholderTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForPlaceholderTmpValueForIdx0ForIdx1 = valueHolderForPlaceholderTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderForPlaceholderTmpValue instanceof PixelMap) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPlaceholderTmpValueForIdx1 = valueHolderForPlaceholderTmpValue as PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForError = value.error
        if (valueHolderForError !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForErrorTmpValue = valueHolderForError!
            if (valueHolderForErrorTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForErrorTmpValueForIdx0 = valueHolderForErrorTmpValue as ResourceStr
                if (valueHolderForErrorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForErrorTmpValueForIdx0ForIdx0 = valueHolderForErrorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForErrorTmpValueForIdx0ForIdx0)
                } else if (valueHolderForErrorTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForErrorTmpValueForIdx0ForIdx1 = valueHolderForErrorTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForErrorTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderForErrorTmpValue instanceof PixelMap) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForErrorTmpValueForIdx1 = valueHolderForErrorTmpValue as PixelMap
                image_PixelMap_serializer.write(valueSerializer, valueHolderForErrorTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageAlt {
        let valueDeserializer: DeserializerBase = buffer
        const placeholderTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let placeholderTmpBuf: ResourceStr | PixelMap | undefined = undefined
        if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const placeholderTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let placeholderTmpBufOpt: ResourceStr | PixelMap | undefined
            if (placeholderTmpBufOptUnionSelector == (0).toByte()) {
                const placeholderTmpBufOptBufUUnionSelector: int32 = valueDeserializer.readInt8()
                let placeholderTmpBufOptBufU: string | arkui_component_units_Resource | undefined
                if (placeholderTmpBufOptBufUUnionSelector == (0).toByte()) {
                    placeholderTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (placeholderTmpBufOptBufUUnionSelector == (1).toByte()) {
                    placeholderTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for placeholderTmpBufOptBufU has to be chosen through deserialisation.')
                }
                placeholderTmpBufOpt = (placeholderTmpBufOptBufU as string | arkui_component_units_Resource)
            } else if (placeholderTmpBufOptUnionSelector == (1).toByte()) {
                placeholderTmpBufOpt = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            } else {
                throw new Error('One of the branches for placeholderTmpBufOpt has to be chosen through deserialisation.')
            }
            placeholderTmpBuf = (placeholderTmpBufOpt as ResourceStr | PixelMap)
        }
        const placeholderTmpResult: ResourceStr | PixelMap | undefined = placeholderTmpBuf
        const errorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let errorTmpBuf: ResourceStr | PixelMap | undefined = undefined
        if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const errorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let errorTmpBufOpt: ResourceStr | PixelMap | undefined
            if (errorTmpBufOptUnionSelector == (0).toByte()) {
                const errorTmpBufOptBufUUnionSelector: int32 = valueDeserializer.readInt8()
                let errorTmpBufOptBufU: string | arkui_component_units_Resource | undefined
                if (errorTmpBufOptBufUUnionSelector == (0).toByte()) {
                    errorTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (errorTmpBufOptBufUUnionSelector == (1).toByte()) {
                    errorTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for errorTmpBufOptBufU has to be chosen through deserialisation.')
                }
                errorTmpBufOpt = (errorTmpBufOptBufU as string | arkui_component_units_Resource)
            } else if (errorTmpBufOptUnionSelector == (1).toByte()) {
                errorTmpBufOpt = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
            } else {
                throw new Error('One of the branches for errorTmpBufOpt has to be chosen through deserialisation.')
            }
            errorTmpBuf = (errorTmpBufOpt as ResourceStr | PixelMap)
        }
        const errorTmpResult: ResourceStr | PixelMap | undefined = errorTmpBuf
        let value: ImageAlt = ({placeholder: placeholderTmpResult, error: errorTmpResult} as ImageAlt)
        return value
    }
}
export class ImageError_serializer {
    public static write(buffer: SerializerBase, value: ImageError): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForComponentWidth = value.componentWidth
        valueSerializer.writeInt32(valueHolderForComponentWidth)
        const valueHolderForComponentHeight = value.componentHeight
        valueSerializer.writeInt32(valueHolderForComponentHeight)
        const valueHolderForMessage = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForError = value.error
        if (valueHolderForError !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForErrorTmpValue = valueHolderForError!
            const valueHolderForErrorTmpValueTransformed: BusinessErrorInterface<void> = extractors.transform_Ark_BusinessError_Void_to_Ark_BusinessErrorInterface_Void(valueHolderForErrorTmpValue)
            BusinessErrorInterface_Void_serializer.write(valueSerializer, valueHolderForErrorTmpValueTransformed)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDownloadInfo = value.downloadInfo
        if (valueHolderForDownloadInfo !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDownloadInfoTmpValue = valueHolderForDownloadInfo!
            cacheDownload_DownloadInfo_serializer.write(valueSerializer, valueHolderForDownloadInfoTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageError {
        let valueDeserializer: DeserializerBase = buffer
        const componentWidthTmpResult: int32 = valueDeserializer.readInt32()
        const componentHeightTmpResult: int32 = valueDeserializer.readInt32()
        const messageTmpResult: string = (valueDeserializer.readString() as string)
        const errorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let errorTmpBuf: BusinessError<void> | undefined = undefined
        if ((errorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const errorTmpBufOptDeserialized: BusinessErrorInterface<void> = BusinessErrorInterface_Void_serializer.read(valueDeserializer)
            errorTmpBuf = extractors.transform_Ark_BusinessErrorInterface_Void_to_Ark_BusinessError_Void(errorTmpBufOptDeserialized)
        }
        const errorTmpResult: BusinessError<void> | undefined = errorTmpBuf
        const downloadInfoTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let downloadInfoTmpBuf: RequestDownloadInfo | undefined = undefined
        if ((downloadInfoTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            downloadInfoTmpBuf = cacheDownload_DownloadInfo_serializer.read(valueDeserializer)
        }
        const downloadInfoTmpResult: RequestDownloadInfo | undefined = downloadInfoTmpBuf
        let value: ImageError = ({componentWidth: componentWidthTmpResult, componentHeight: componentHeightTmpResult, message: messageTmpResult, error: errorTmpResult, downloadInfo: downloadInfoTmpResult} as ImageError)
        return value
    }
}
export class ResizableOptions_serializer {
    public static write(buffer: SerializerBase, value: ResizableOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSlice = value.slice
        if (valueHolderForSlice !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSliceTmpValue = valueHolderForSlice!
            EdgeWidths_serializer.write(valueSerializer, valueHolderForSliceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLattice = value.lattice
        if (valueHolderForLattice !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLatticeTmpValue = valueHolderForLattice!
            drawing_Lattice_serializer.write(valueSerializer, valueHolderForLatticeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ResizableOptions {
        let valueDeserializer: DeserializerBase = buffer
        const sliceTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let sliceTmpBuf: EdgeWidths | undefined = undefined
        if ((sliceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sliceTmpBuf = EdgeWidths_serializer.read(valueDeserializer)
        }
        const sliceTmpResult: EdgeWidths | undefined = sliceTmpBuf
        const latticeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let latticeTmpBuf: DrawingLattice | undefined = undefined
        if ((latticeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            latticeTmpBuf = (drawing_Lattice_serializer.read(valueDeserializer) as drawing.Lattice)
        }
        const latticeTmpResult: DrawingLattice | undefined = latticeTmpBuf
        let value: ResizableOptions = ({slice: sliceTmpResult, lattice: latticeTmpResult} as ResizableOptions)
        return value
    }
}
