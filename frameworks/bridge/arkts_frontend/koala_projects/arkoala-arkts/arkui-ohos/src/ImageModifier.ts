/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { AttributeModifier, CommonMethod, PointLightStyle } from "./component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Resource } from "global.resource"
import { PixelMap, PixelMapDrawableDescriptor, AnimatedDrawableDescriptor, LayeredDrawableDescriptor } from "#external"
import { ResourceColor, ColorFilter } from "./component/units"
import { Color, ImageFit, ImageRepeat, CopyOptions } from "./component/enums"
import { ColorContent, ImageAttribute, ArkImagePeer, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, ImageOnCompleteCallback, ImageCompleteEvent, ImageErrorCallback, ImageError, ResizableOptions, ImageRotateOrientation } from "./component/image"
import { ColorMetrics } from "./Graphics"
import { Matrix4Transit } from "./component/arkui-matrix4"
import { drawing } from "@ohos/graphics/drawing"
import { ImageAnalyzerConfig } from "./component/imageCommon"
import { ResolutionQuality } from "./component/arkui-external"

export class ImageModifier extends CommonMethodModifier implements ImageAttribute, AttributeModifier<ImageAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: ImageAttribute): void { }
    applyPressedAttribute(instance: ImageAttribute): void { }
    applyFocusedAttribute(instance: ImageAttribute): void { }
    applyDisabledAttribute(instance: ImageAttribute): void { }
    applySelectedAttribute(instance: ImageAttribute): void { }
    _alt_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alt_0_0value?: string | Resource | PixelMap | undefined
    _matchTextDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _matchTextDirection_0_0value?: boolean | undefined
    _fitOriginalSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fitOriginalSize_0_0value?: boolean | undefined
    _fillColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillColor_0_0value?: ResourceColor | ColorContent | ColorMetrics | undefined
    _objectFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectFit_0_0value?: ImageFit | undefined
    _imageMatrix_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _imageMatrix_0_0value?: Matrix4Transit | undefined
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
    _edgeAntialiasing_0_0value?: number | undefined
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
    _enhancedImageQuality_0_0value?: ResolutionQuality | undefined
    _orientation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _orientation_0_0value?: ImageRotateOrientation | undefined
    applyModifierPatch(peer: ArkImagePeer): void {
        super.applyModifierPatch(peer)
    }
    mergeModifier(modifier: ImageModifier): void {
        super.mergeModifier(modifier)
    }
    alt(value: string | Resource | PixelMap | undefined): this {
        if (((this._alt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._alt_0_flag = AttributeUpdaterFlag.UPDATE
            this._alt_0_0value = value
        } else {
            this._alt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    matchTextDirection(value: boolean | undefined): this {
        if (((this._matchTextDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._matchTextDirection_0_0value) !== (value))) {
            this._matchTextDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._matchTextDirection_0_0value = value
        } else {
            this._matchTextDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fitOriginalSize(value: boolean | undefined): this {
        if (((this._fitOriginalSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fitOriginalSize_0_0value) !== (value))) {
            this._fitOriginalSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fitOriginalSize_0_0value = value
        } else {
            this._fitOriginalSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        if (((this._fillColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._fillColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fillColor_0_0value = value
        } else {
            this._fillColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._objectFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._objectFit_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectFit_0_0value = value
        } else {
            this._objectFit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    imageMatrix(value: Matrix4Transit | undefined): this {
        if (((this._imageMatrix_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._imageMatrix_0_flag = AttributeUpdaterFlag.UPDATE
            this._imageMatrix_0_0value = value
        } else {
            this._imageMatrix_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectRepeat(value: ImageRepeat | undefined): this {
        if (((this._objectRepeat_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._objectRepeat_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectRepeat_0_0value = value
        } else {
            this._objectRepeat_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoResize(value: boolean | undefined): this {
        if (((this._autoResize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoResize_0_0value) !== (value))) {
            this._autoResize_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoResize_0_0value = value
        } else {
            this._autoResize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderMode(value: ImageRenderMode | undefined): this {
        if (((this._renderMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._renderMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderMode_0_0value = value
        } else {
            this._renderMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dynamicRangeMode(value: DynamicRangeMode | undefined): this {
        if (((this._dynamicRangeMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._dynamicRangeMode_0_0value = value
        } else {
            this._dynamicRangeMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    interpolation(value: ImageInterpolation | undefined): this {
        if (((this._interpolation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._interpolation_0_flag = AttributeUpdaterFlag.UPDATE
            this._interpolation_0_0value = value
        } else {
            this._interpolation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sourceSize(value: ImageSourceSize | undefined): this {
        if (((this._sourceSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._sourceSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._sourceSize_0_0value = value
        } else {
            this._sourceSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    syncLoad(value: boolean | undefined): this {
        if (((this._syncLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._syncLoad_0_0value) !== (value))) {
            this._syncLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._syncLoad_0_0value = value
        } else {
            this._syncLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (((this._colorFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._colorFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._colorFilter_0_0value = value
        } else {
            this._colorFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._copyOption_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._copyOption_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOption_0_0value = value
        } else {
            this._copyOption_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._draggable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._draggable_0_0value) !== (value))) {
            this._draggable_0_flag = AttributeUpdaterFlag.UPDATE
            this._draggable_0_0value = value
        } else {
            this._draggable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        if (((this._pointLight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._pointLight_0_flag = AttributeUpdaterFlag.UPDATE
            this._pointLight_0_0value = value
        } else {
            this._pointLight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeAntialiasing(value: number | undefined): this {
        if (((this._edgeAntialiasing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._edgeAntialiasing_0_0value) !== (value))) {
            this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeAntialiasing_0_0value = value
        } else {
            this._edgeAntialiasing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onComplete(value: ImageOnCompleteCallback | undefined): this {
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._onComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onComplete_0_0value = value
        } else {
            this._onComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._enableAnalyzer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnalyzer_0_0value) !== (value))) {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnalyzer_0_0value = value
        } else {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        if (((this._analyzerConfig_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.UPDATE
            this._analyzerConfig_0_0value = value
        } else {
            this._analyzerConfig_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    resizable(value: ResizableOptions | undefined): this {
        if (((this._resizable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._resizable_0_flag = AttributeUpdaterFlag.UPDATE
            this._resizable_0_0value = value
        } else {
            this._resizable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive_0_0value) !== (value))) {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive_0_0value = value
        } else {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enhancedImageQuality(value: ResolutionQuality | undefined): this {
        if (((this._enhancedImageQuality_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.UPDATE
            this._enhancedImageQuality_0_0value = value
        } else {
            this._enhancedImageQuality_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    orientation(value: ImageRotateOrientation | undefined): this {
        if (((this._orientation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true)) {
            this._orientation_0_flag = AttributeUpdaterFlag.UPDATE
            this._orientation_0_0value = value
        } else {
            this._orientation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
