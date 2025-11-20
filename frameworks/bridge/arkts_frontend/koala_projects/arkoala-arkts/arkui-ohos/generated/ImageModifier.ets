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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkImagePeer, ColorContent, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, ImageOnCompleteCallback, ImageCompleteEvent, ImageErrorCallback, ImageError, ResizableOptions, ImageRotateOrientation, ImageAttribute } from "./component/image"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CommonMethod, PointLightStyle } from "./component/common"
import { Resource } from "global.resource"
import { default as image } from "@ohos.multimedia.image"
import { ResourceColor, ColorFilter } from "./component/units"
import { Color, ImageFit, ImageRepeat, CopyOptions } from "./component/enums"
import { ColorMetrics } from "arkui.Graphics"
import { default as matrix4 } from "@ohos.matrix4"
import { default as drawing } from "@ohos.graphics.drawing"
import { ImageAnalyzerConfig } from "./component/imageCommon"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./CallbackTransformer"
export class ImageModifier extends CommonMethodModifier implements ImageAttribute,AttributeModifier<ImageAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ImageAttribute): void { }
    applyPressedAttribute(instance: ImageAttribute): void { }
    applyFocusedAttribute(instance: ImageAttribute): void { }
    applyDisabledAttribute(instance: ImageAttribute): void { }
    applySelectedAttribute(instance: ImageAttribute): void { }
    _alt_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alt_0_0value?: string | Resource | image.PixelMap | undefined
    _matchTextDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _matchTextDirection_0_0value?: boolean | undefined
    _fitOriginalSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fitOriginalSize_0_0value?: boolean | undefined
    _fillColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillColor_0_0value?: ResourceColor | ColorContent | ColorMetrics | undefined
    _objectFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectFit_0_0value?: ImageFit | undefined
    _imageMatrix_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _imageMatrix_0_0value?: matrix4.Matrix4Transit | undefined
    _objectRepeat_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectRepeat_0_0value?: ImageRepeat | undefined
    _autoResize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoResize_0_0value?: boolean | undefined
    _renderMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderMode_0_0value?: ImageRenderMode | undefined
    _dynamicRangeMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dynamicRangeMode_0_0value?: DynamicRangeMode | undefined
    _interpolation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _interpolation_0_0value?: ImageInterpolation | undefined
    _sourceSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sourceSize_0_0value?: ImageSourceSize | undefined
    _syncLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _syncLoad_0_0value?: boolean | undefined
    _colorFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _colorFilter_0_0value?: ColorFilter | drawing.ColorFilter | undefined
    _copyOption_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOption_0_0value?: CopyOptions | undefined
    _draggable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _draggable_0_0value?: boolean | undefined
    _pointLight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pointLight_0_0value?: PointLightStyle | undefined
    _edgeAntialiasing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeAntialiasing_0_0value?: double | undefined
    _onComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onComplete_0_0value?: ImageOnCompleteCallback | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ImageErrorCallback | undefined
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: (() => void) | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    _analyzerConfig_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _analyzerConfig_0_0value?: ImageAnalyzerConfig | undefined
    _resizable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _resizable_0_0value?: ResizableOptions | undefined
    _privacySensitive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _privacySensitive_0_0value?: boolean | undefined
    _enhancedImageQuality_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enhancedImageQuality_0_0value?: image.ResolutionQuality | undefined
    _orientation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _orientation_0_0value?: ImageRotateOrientation | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkImagePeer;
        if (this._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAltAttribute((this._alt_0_0value as string | Resource | image.PixelMap | undefined));
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alt_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAltAttribute((undefined as string | Resource | image.PixelMap | undefined));
                }
            }
        }
        if (this._matchTextDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._matchTextDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMatchTextDirectionAttribute((this._matchTextDirection_0_0value as boolean | undefined));
                    this._matchTextDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._matchTextDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._matchTextDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMatchTextDirectionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fitOriginalSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fitOriginalSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFitOriginalSizeAttribute((this._fitOriginalSize_0_0value as boolean | undefined));
                    this._fitOriginalSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fitOriginalSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fitOriginalSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFitOriginalSizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fillColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fillColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFillColorAttribute((this._fillColor_0_0value as ResourceColor | ColorContent | ColorMetrics | undefined));
                    this._fillColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fillColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fillColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFillColorAttribute((undefined as ResourceColor | ColorContent | ColorMetrics | undefined));
                }
            }
        }
        if (this._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (this._imageMatrix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._imageMatrix_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setImageMatrixAttribute((this._imageMatrix_0_0value as matrix4.Matrix4Transit | undefined));
                    this._imageMatrix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._imageMatrix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._imageMatrix_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setImageMatrixAttribute((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (this._objectRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObjectRepeatAttribute((this._objectRepeat_0_0value as ImageRepeat | undefined));
                    this._objectRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectRepeat_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObjectRepeatAttribute((undefined as ImageRepeat | undefined));
                }
            }
        }
        if (this._autoResize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoResize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoResizeAttribute((this._autoResize_0_0value as boolean | undefined));
                    this._autoResize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoResize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoResize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoResizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._renderMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderModeAttribute((this._renderMode_0_0value as ImageRenderMode | undefined));
                    this._renderMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderModeAttribute((undefined as ImageRenderMode | undefined));
                }
            }
        }
        if (this._dynamicRangeMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dynamicRangeMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDynamicRangeModeAttribute((this._dynamicRangeMode_0_0value as DynamicRangeMode | undefined));
                    this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDynamicRangeModeAttribute((undefined as DynamicRangeMode | undefined));
                }
            }
        }
        if (this._interpolation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._interpolation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInterpolationAttribute((this._interpolation_0_0value as ImageInterpolation | undefined));
                    this._interpolation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._interpolation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._interpolation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInterpolationAttribute((undefined as ImageInterpolation | undefined));
                }
            }
        }
        if (this._sourceSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sourceSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSourceSizeAttribute((this._sourceSize_0_0value as ImageSourceSize | undefined));
                    this._sourceSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sourceSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sourceSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSourceSizeAttribute((undefined as ImageSourceSize | undefined));
                }
            }
        }
        if (this._syncLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._syncLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSyncLoadAttribute((this._syncLoad_0_0value as boolean | undefined));
                    this._syncLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._syncLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._syncLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSyncLoadAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorFilterAttribute((this._colorFilter_0_0value as ColorFilter | drawing.ColorFilter | undefined));
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorFilterAttribute((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (this._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCopyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (this._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDraggableAttribute((this._draggable_0_0value as boolean | undefined));
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._draggable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPointLightAttribute((this._pointLight_0_0value as PointLightStyle | undefined));
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPointLightAttribute((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (this._edgeAntialiasing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeAntialiasing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeAntialiasingAttribute((this._edgeAntialiasing_0_0value as double | undefined));
                    this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeAntialiasingAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as ImageOnCompleteCallback | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCompleteAttribute((undefined as ImageOnCompleteCallback | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ImageErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._analyzerConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._analyzerConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAnalyzerConfigAttribute((this._analyzerConfig_0_0value as ImageAnalyzerConfig | undefined));
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._analyzerConfig_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAnalyzerConfigAttribute((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (this._resizable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._resizable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setResizableAttribute((this._resizable_0_0value as ResizableOptions | undefined));
                    this._resizable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._resizable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._resizable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setResizableAttribute((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (this._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enhancedImageQuality_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enhancedImageQuality_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnhancedImageQualityAttribute((this._enhancedImageQuality_0_0value as image.ResolutionQuality | undefined));
                    this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnhancedImageQualityAttribute((undefined as image.ResolutionQuality | undefined));
                }
            }
        }
        if (this._orientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._orientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOrientationAttribute((this._orientation_0_0value as ImageRotateOrientation | undefined));
                    this._orientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._orientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._orientation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOrientationAttribute((undefined as ImageRotateOrientation | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ImageModifier): void {
        super.mergeModifier(modifier)
        if (modifier._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alt(modifier._alt_0_0value);
                    break;
                }
                default: {
                    this.alt((undefined as string | Resource | image.PixelMap | undefined));
                }
            }
        }
        if (modifier._matchTextDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._matchTextDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.matchTextDirection(modifier._matchTextDirection_0_0value);
                    break;
                }
                default: {
                    this.matchTextDirection((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fitOriginalSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fitOriginalSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fitOriginalSize(modifier._fitOriginalSize_0_0value);
                    break;
                }
                default: {
                    this.fitOriginalSize((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fillColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fillColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fillColor(modifier._fillColor_0_0value);
                    break;
                }
                default: {
                    this.fillColor((undefined as ResourceColor | ColorContent | ColorMetrics | undefined));
                }
            }
        }
        if (modifier._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (modifier._imageMatrix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._imageMatrix_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.imageMatrix(modifier._imageMatrix_0_0value);
                    break;
                }
                default: {
                    this.imageMatrix((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (modifier._objectRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._objectRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.objectRepeat(modifier._objectRepeat_0_0value);
                    break;
                }
                default: {
                    this.objectRepeat((undefined as ImageRepeat | undefined));
                }
            }
        }
        if (modifier._autoResize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoResize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoResize(modifier._autoResize_0_0value);
                    break;
                }
                default: {
                    this.autoResize((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._renderMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderMode(modifier._renderMode_0_0value);
                    break;
                }
                default: {
                    this.renderMode((undefined as ImageRenderMode | undefined));
                }
            }
        }
        if (modifier._dynamicRangeMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dynamicRangeMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dynamicRangeMode(modifier._dynamicRangeMode_0_0value);
                    break;
                }
                default: {
                    this.dynamicRangeMode((undefined as DynamicRangeMode | undefined));
                }
            }
        }
        if (modifier._interpolation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._interpolation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.interpolation(modifier._interpolation_0_0value);
                    break;
                }
                default: {
                    this.interpolation((undefined as ImageInterpolation | undefined));
                }
            }
        }
        if (modifier._sourceSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sourceSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sourceSize(modifier._sourceSize_0_0value);
                    break;
                }
                default: {
                    this.sourceSize((undefined as ImageSourceSize | undefined));
                }
            }
        }
        if (modifier._syncLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._syncLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.syncLoad(modifier._syncLoad_0_0value);
                    break;
                }
                default: {
                    this.syncLoad((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.colorFilter(modifier._colorFilter_0_0value);
                    break;
                }
                default: {
                    this.colorFilter((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (modifier._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOption(modifier._copyOption_0_0value);
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (modifier._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.draggable(modifier._draggable_0_0value);
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pointLight(modifier._pointLight_0_0value);
                    break;
                }
                default: {
                    this.pointLight((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (modifier._edgeAntialiasing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._edgeAntialiasing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeAntialiasing(modifier._edgeAntialiasing_0_0value);
                    break;
                }
                default: {
                    this.edgeAntialiasing((undefined as double | undefined));
                }
            }
        }
        if (modifier._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as ImageOnCompleteCallback | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._analyzerConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._analyzerConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.analyzerConfig(modifier._analyzerConfig_0_0value);
                    break;
                }
                default: {
                    this.analyzerConfig((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (modifier._resizable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._resizable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.resizable(modifier._resizable_0_0value);
                    break;
                }
                default: {
                    this.resizable((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (modifier._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enhancedImageQuality_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enhancedImageQuality_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enhancedImageQuality(modifier._enhancedImageQuality_0_0value);
                    break;
                }
                default: {
                    this.enhancedImageQuality((undefined as image.ResolutionQuality | undefined));
                }
            }
        }
        if (modifier._orientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._orientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.orientation(modifier._orientation_0_0value);
                    break;
                }
                default: {
                    this.orientation((undefined as ImageRotateOrientation | undefined));
                }
            }
        }
    }
    alt(value: string | Resource | image.PixelMap | undefined): this {
        if (((this._alt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alt_0_flag = AttributeUpdaterFlag.UPDATE
            this._alt_0_0value = value
        } else
        {
            this._alt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    matchTextDirection(value: boolean | undefined): this {
        if (((this._matchTextDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._matchTextDirection_0_0value) !== (value)))
        {
            this._matchTextDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._matchTextDirection_0_0value = value
        } else
        {
            this._matchTextDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fitOriginalSize(value: boolean | undefined): this {
        if (((this._fitOriginalSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fitOriginalSize_0_0value) !== (value)))
        {
            this._fitOriginalSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fitOriginalSize_0_0value = value
        } else
        {
            this._fitOriginalSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        if (((this._fillColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fillColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fillColor_0_0value = value
        } else
        {
            this._fillColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._objectFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectFit_0_0value = value
        } else
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    imageMatrix(value: matrix4.Matrix4Transit | undefined): this {
        if (((this._imageMatrix_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._imageMatrix_0_flag = AttributeUpdaterFlag.UPDATE
            this._imageMatrix_0_0value = value
        } else
        {
            this._imageMatrix_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectRepeat(value: ImageRepeat | undefined): this {
        if (((this._objectRepeat_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._objectRepeat_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectRepeat_0_0value = value
        } else
        {
            this._objectRepeat_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoResize(value: boolean | undefined): this {
        if (((this._autoResize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoResize_0_0value) !== (value)))
        {
            this._autoResize_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoResize_0_0value = value
        } else
        {
            this._autoResize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderMode(value: ImageRenderMode | undefined): this {
        if (((this._renderMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._renderMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderMode_0_0value = value
        } else
        {
            this._renderMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        if (((this._dynamicRangeMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._dynamicRangeMode_0_0value = value
        } else
        {
            this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    interpolation(value: ImageInterpolation | undefined): this {
        if (((this._interpolation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._interpolation_0_flag = AttributeUpdaterFlag.UPDATE
            this._interpolation_0_0value = value
        } else
        {
            this._interpolation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sourceSize(value: ImageSourceSize | undefined): this {
        if (((this._sourceSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sourceSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._sourceSize_0_0value = value
        } else
        {
            this._sourceSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    syncLoad(value: boolean | undefined): this {
        if (((this._syncLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._syncLoad_0_0value) !== (value)))
        {
            this._syncLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._syncLoad_0_0value = value
        } else
        {
            this._syncLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (((this._colorFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._colorFilter_0_0value = value
        } else
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._copyOption_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOption_0_0value = value
        } else
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._draggable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._draggable_0_0value) !== (value)))
        {
            this._draggable_0_flag = AttributeUpdaterFlag.UPDATE
            this._draggable_0_0value = value
        } else
        {
            this._draggable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        if (((this._pointLight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.UPDATE
            this._pointLight_0_0value = value
        } else
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeAntialiasing(value: double | undefined): this {
        if (((this._edgeAntialiasing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._edgeAntialiasing_0_0value) !== (value)))
        {
            this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeAntialiasing_0_0value = value
        } else
        {
            this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onComplete(value: ImageOnCompleteCallback | undefined): this {
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onComplete_0_0value = value
        } else
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._enableAnalyzer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnalyzer_0_0value) !== (value)))
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnalyzer_0_0value = value
        } else
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (((this._analyzerConfig_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.UPDATE
            this._analyzerConfig_0_0value = value
        } else
        {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    resizable(value: ResizableOptions | undefined): this {
        if (((this._resizable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._resizable_0_flag = AttributeUpdaterFlag.UPDATE
            this._resizable_0_0value = value
        } else
        {
            this._resizable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive_0_0value) !== (value)))
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive_0_0value = value
        } else
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        if (((this._enhancedImageQuality_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.UPDATE
            this._enhancedImageQuality_0_0value = value
        } else
        {
            this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    orientation(value: ImageRotateOrientation | undefined): this {
        if (((this._orientation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._orientation_0_flag = AttributeUpdaterFlag.UPDATE
            this._orientation_0_0value = value
        } else
        {
            this._orientation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ImageModifier_serializer {
    public static write(buffer: SerializerBase, value: ImageModifier): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toImageModifierPtr(value))
    }
    public static read(buffer: DeserializerBase): ImageModifier {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromImageModifierPtr(ptr)
    }
}
