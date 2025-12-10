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

import { CommonMethod, PixelMap, PointLightStyle } from './component/common'
import { Resource as global_resource_Resource } from 'global.resource'
import { extractors, AttributeModifier } from '#handwritten'
import { default as image } from '@ohos.multimedia.image'
import { ResourceColor, Resource as arkui_component_units_Resource, ColorMetrics as arkui_component_units_ColorMetrics, ColorFilter, VoidCallback } from './component/units'
import { Color as arkui_component_enums_Color, ImageFit, ImageRepeat, CopyOptions } from './component/enums'
import { ColorContent, ImageMatrix, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, DrawingColorFilter, ImageOnCompleteCallback, ImageCompleteEvent, ImageErrorCallback, ImageError, ResizableOptions, ResolutionQuality, ImageRotateOrientation, ImageAttribute } from './component/image'
import { ColorMetrics as arkui_Graphics_ColorMetrics } from '@arkui.Graphics'
import { default as matrix4 } from '@ohos.matrix4'
import { default as drawing } from '@ohos.graphics.drawing'
import { ImageAnalyzerConfig } from './component/imageCommon'
import { ImageModifier } from './ImageModifier'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkMediaCachedImagePeer, MediaCachedImageAttribute } from './component/mediaCachedImage'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
export class MediaCachedImageModifier extends CommonMethodModifier implements MediaCachedImageAttribute,AttributeModifier<MediaCachedImageAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: MediaCachedImageAttribute): void { }
    applyPressedAttribute(instance: MediaCachedImageAttribute): void { }
    applyFocusedAttribute(instance: MediaCachedImageAttribute): void { }
    applyDisabledAttribute(instance: MediaCachedImageAttribute): void { }
    applySelectedAttribute(instance: MediaCachedImageAttribute): void { }
    public _alt_0_0value?: string | global_resource_Resource | PixelMap | undefined
    public _matchTextDirection_0_0value?: boolean | undefined
    public _fitOriginalSize_0_0value?: boolean | undefined
    public _fillColor_0_0value?: ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined
    public _objectFit_0_0value?: ImageFit | undefined
    public _imageMatrix_0_0value?: ImageMatrix | undefined
    public _objectRepeat_0_0value?: ImageRepeat | undefined
    public _autoResize_0_0value?: boolean | undefined
    public _renderMode_0_0value?: ImageRenderMode | undefined
    public _dynamicRangeMode_0_0value?: DynamicRangeMode | undefined
    public _interpolation_0_0value?: ImageInterpolation | undefined
    public _sourceSize_0_0value?: ImageSourceSize | undefined
    public _syncLoad_0_0value?: boolean | undefined
    public _colorFilter_0_0value?: ColorFilter | DrawingColorFilter | undefined
    public _copyOption_0_0value?: CopyOptions | undefined
    public _draggable_0_0value?: boolean | undefined
    public _pointLight_0_0value?: PointLightStyle | undefined
    public _edgeAntialiasing_0_0value?: double | undefined
    public _onComplete_0_0value?: ImageOnCompleteCallback | undefined
    public _onError_0_0value?: ImageErrorCallback | undefined
    public _onFinish_0_0value?: VoidCallback | undefined
    public _enableAnalyzer_0_0value?: boolean | undefined
    public _analyzerConfig_0_0value?: ImageAnalyzerConfig | undefined
    public _resizable_0_0value?: ResizableOptions | undefined
    public _privacySensitive_0_0value?: boolean | undefined
    public _enhancedImageQuality_0_0value?: ResolutionQuality | undefined
    public _orientation_0_0value?: ImageRotateOrientation | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkMediaCachedImagePeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkMediaCachedImagePeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setAltAttribute((this._alt_0_0value as string | global_resource_Resource | PixelMap | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setAltAttribute((undefined as string | global_resource_Resource | PixelMap | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setMatchTextDirectionAttribute((this._matchTextDirection_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setMatchTextDirectionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setFitOriginalSizeAttribute((this._fitOriginalSize_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setFitOriginalSizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setFillColorAttribute((this._fillColor_0_0value as ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setFillColorAttribute((undefined as ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setImageMatrixAttribute((this._imageMatrix_0_0value as ImageMatrix | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setImageMatrixAttribute((undefined as ImageMatrix | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setObjectRepeatAttribute((this._objectRepeat_0_0value as ImageRepeat | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setObjectRepeatAttribute((undefined as ImageRepeat | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setAutoResizeAttribute((this._autoResize_0_0value as boolean | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setAutoResizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setRenderModeAttribute((this._renderMode_0_0value as ImageRenderMode | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setRenderModeAttribute((undefined as ImageRenderMode | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setDynamicRangeModeAttribute((this._dynamicRangeMode_0_0value as DynamicRangeMode | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setDynamicRangeModeAttribute((undefined as DynamicRangeMode | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setInterpolationAttribute((this._interpolation_0_0value as ImageInterpolation | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setInterpolationAttribute((undefined as ImageInterpolation | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setSourceSizeAttribute((this._sourceSize_0_0value as ImageSourceSize | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setSourceSizeAttribute((undefined as ImageSourceSize | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setSyncLoadAttribute((this._syncLoad_0_0value as boolean | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setSyncLoadAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setColorFilterAttribute((this._colorFilter_0_0value as ColorFilter | DrawingColorFilter | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setColorFilterAttribute((undefined as ColorFilter | DrawingColorFilter | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setCopyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setDraggableAttribute((this._draggable_0_0value as boolean | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setPointLightAttribute((this._pointLight_0_0value as PointLightStyle | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setPointLightAttribute((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setEdgeAntialiasingAttribute((this._edgeAntialiasing_0_0value as double | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setEdgeAntialiasingAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as ImageOnCompleteCallback | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setOnCompleteAttribute((undefined as ImageOnCompleteCallback | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ImageErrorCallback | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setOnErrorAttribute((undefined as ImageErrorCallback | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkMediaCachedImagePeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as VoidCallback | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setOnFinishAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setAnalyzerConfigAttribute((this._analyzerConfig_0_0value as ImageAnalyzerConfig | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setAnalyzerConfigAttribute((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setResizableAttribute((this._resizable_0_0value as ResizableOptions | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setResizableAttribute((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setEnhancedImageQualityAttribute((this._enhancedImageQuality_0_0value as ResolutionQuality | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setEnhancedImageQualityAttribute((undefined as ResolutionQuality | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setOrientationAttribute((this._orientation_0_0value as ImageRotateOrientation | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setOrientationAttribute((undefined as ImageRotateOrientation | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: MediaCachedImageModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: MediaCachedImageModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.alt(modifier._alt_0_0value);
                    break;
                }
                default: {
                    this.alt((undefined as string | global_resource_Resource | PixelMap | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.matchTextDirection(modifier._matchTextDirection_0_0value);
                    break;
                }
                default: {
                    this.matchTextDirection((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.fitOriginalSize(modifier._fitOriginalSize_0_0value);
                    break;
                }
                default: {
                    this.fitOriginalSize((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.fillColor(modifier._fillColor_0_0value);
                    break;
                }
                default: {
                    this.fillColor((undefined as ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.imageMatrix(modifier._imageMatrix_0_0value);
                    break;
                }
                default: {
                    this.imageMatrix((undefined as ImageMatrix | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.objectRepeat(modifier._objectRepeat_0_0value);
                    break;
                }
                default: {
                    this.objectRepeat((undefined as ImageRepeat | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.autoResize(modifier._autoResize_0_0value);
                    break;
                }
                default: {
                    this.autoResize((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.renderMode(modifier._renderMode_0_0value);
                    break;
                }
                default: {
                    this.renderMode((undefined as ImageRenderMode | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.dynamicRangeMode(modifier._dynamicRangeMode_0_0value);
                    break;
                }
                default: {
                    this.dynamicRangeMode((undefined as DynamicRangeMode | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.interpolation(modifier._interpolation_0_0value);
                    break;
                }
                default: {
                    this.interpolation((undefined as ImageInterpolation | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.sourceSize(modifier._sourceSize_0_0value);
                    break;
                }
                default: {
                    this.sourceSize((undefined as ImageSourceSize | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.syncLoad(modifier._syncLoad_0_0value);
                    break;
                }
                default: {
                    this.syncLoad((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.colorFilter(modifier._colorFilter_0_0value);
                    break;
                }
                default: {
                    this.colorFilter((undefined as ColorFilter | DrawingColorFilter | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.copyOption(modifier._copyOption_0_0value);
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.draggable(modifier._draggable_0_0value);
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.pointLight(modifier._pointLight_0_0value);
                    break;
                }
                default: {
                    this.pointLight((undefined as PointLightStyle | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.edgeAntialiasing(modifier._edgeAntialiasing_0_0value);
                    break;
                }
                default: {
                    this.edgeAntialiasing((undefined as double | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as ImageOnCompleteCallback | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ImageErrorCallback | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: MediaCachedImageModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.analyzerConfig(modifier._analyzerConfig_0_0value);
                    break;
                }
                default: {
                    this.analyzerConfig((undefined as ImageAnalyzerConfig | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.resizable(modifier._resizable_0_0value);
                    break;
                }
                default: {
                    this.resizable((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.enhancedImageQuality(modifier._enhancedImageQuality_0_0value);
                    break;
                }
                default: {
                    this.enhancedImageQuality((undefined as ResolutionQuality | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.orientation(modifier._orientation_0_0value);
                    break;
                }
                default: {
                    this.orientation((undefined as ImageRotateOrientation | undefined));
                }
            }
        }
    }
    alt(value: string | global_resource_Resource | PixelMap | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._alt_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    matchTextDirection(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._matchTextDirection_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._matchTextDirection_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    fitOriginalSize(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._fitOriginalSize_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._fitOriginalSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    fillColor(value: ResourceColor | ColorContent | arkui_component_units_ColorMetrics | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._fillColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._objectFit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    imageMatrix(value: ImageMatrix | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._imageMatrix_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    objectRepeat(value: ImageRepeat | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._objectRepeat_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    autoResize(value: boolean | undefined): this {
        if (((this._flagArray[7]) == (0)) || ((this._autoResize_0_0value) !== (value))) {
            this._flagArray[7] = 1
            this._autoResize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    renderMode(value: ImageRenderMode | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._renderMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._dynamicRangeMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    interpolation(value: ImageInterpolation | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._interpolation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    sourceSize(value: ImageSourceSize | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._sourceSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    syncLoad(value: boolean | undefined): this {
        if (((this._flagArray[12]) == (0)) || ((this._syncLoad_0_0value) !== (value))) {
            this._flagArray[12] = 1
            this._syncLoad_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._colorFilter_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._copyOption_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._flagArray[15]) == (0)) || ((this._draggable_0_0value) !== (value))) {
            this._flagArray[15] = 1
            this._draggable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._pointLight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    edgeAntialiasing(value: double | undefined): this {
        if (((this._flagArray[17]) == (0)) || ((this._edgeAntialiasing_0_0value) !== (value))) {
            this._flagArray[17] = 1
            this._edgeAntialiasing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    onComplete(value: ImageOnCompleteCallback | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._onComplete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._onError_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    onFinish(value: VoidCallback | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._onFinish_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._flagArray[21]) == (0)) || ((this._enableAnalyzer_0_0value) !== (value))) {
            this._flagArray[21] = 1
            this._enableAnalyzer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._analyzerConfig_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    resizable(value: ResizableOptions | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._resizable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._flagArray[24]) == (0)) || ((this._privacySensitive_0_0value) !== (value))) {
            this._flagArray[24] = 1
            this._privacySensitive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    enhancedImageQuality(value: ResolutionQuality | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._enhancedImageQuality_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    orientation(value: ImageRotateOrientation | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true)) {
            this._flagArray[26] = 1
            this._orientation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
