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

import { ArkImageComponent, ColorContent, ImageContent, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, ImageCompleteEvent, ImageErrorCallback, ResizableOptions, ImageRotateOrientation, ImageAttribute, ImageAlt, ContentTransitionEffect } from "../component/image";
import { ImageAnalyzerConfig, ImageAIOptions } from "../component/imageCommon"
import { ImageFit, ImageRepeat, CopyOptions, Color } from "../component/enums"
import { ArkBaseNode } from "./ArkBaseNode";
import { PointLightStyle } from "../component/common"
import { ColorMetrics } from "../Graphics"
import { PixelMap, DrawableDescriptor, AnimatedDrawableDescriptor, LayeredDrawableDescriptor } from "#external"
import { ResourceColor, ColorFilter, ResourceStr } from "../component/units"
import { Resource } from "global.resource"
import { default as drawing } from "@ohos.graphics.drawing"
import { default as matrix4 } from "@ohos.matrix4"
import { default as image } from "@ohos.multimedia.image"


export class ArkImageNode extends ArkBaseNode implements ImageAttribute {
    private component: ArkImageComponent = new ArkImageComponent()
    initialize(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent, options?: ImageAIOptions): this {
        this.component.setPeer(this.getPeer())
        this.setImageOptions(src, options)
        return this
    }
    public setImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent, options?: ImageAIOptions): this {
        this.component.setImageOptions(src)
        this.markDirty()
        return this
    }
    public alt(value: string | Resource | PixelMap | ImageAlt | undefined): this {
        this.component.alt(value)
        this.markDirty()
        return this
    }
    public matchTextDirection(value: boolean | undefined): this {
        this.component.matchTextDirection(value)
        this.markDirty()
        return this
    }
    public fitOriginalSize(value: boolean | undefined): this {
        this.component.fitOriginalSize(value)
        this.markDirty()
        return this
    }
    public fillColor(value: ResourceColor | ColorContent | ColorMetrics | undefined): this {
        this.component.fillColor(value)
        this.markDirty()
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        this.component.objectFit(value)
        this.markDirty()
        return this
    }
    public imageMatrix(value: matrix4.Matrix4Transit | undefined): this {

        this.component.imageMatrix(value)
        this.markDirty()
        return this
    }
    public objectRepeat(value: ImageRepeat | undefined): this {
        this.component.objectRepeat(value)
        this.markDirty()
        return this
    }
    public autoResize(value: boolean | undefined): this {
        this.component.autoResize(value)
        this.markDirty()
        return this
    }
    public renderMode(value: ImageRenderMode | undefined): this {
        this.component.renderMode(value)
        this.markDirty()
        return this
    }
    public dynamicRangeMode(value: DynamicRangeMode | undefined): this {

        this.component.dynamicRangeMode(value)

        this.markDirty()
        return this
    }
    public hdrBrightness(value: double | undefined): this {
        this.component.hdrBrightness(value)
        this.markDirty()
        return this
    }
    public interpolation(value: ImageInterpolation | undefined): this {
        this.component.interpolation(value)
        this.markDirty()
        return this
    }
    public sourceSize(value: ImageSourceSize | undefined): this {
        this.component.sourceSize(value)
        this.markDirty()
        return this
    }
    public syncLoad(value: boolean | undefined): this {
        this.component.syncLoad(value)
        this.markDirty()
        return this
    }
    public colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        this.component.colorFilter(value)
        this.markDirty()
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        this.component.copyOption(value)
        this.markDirty()
        return this
    }
    public draggable(value: boolean | undefined): this {
        this.component.draggable(value)
        this.markDirty()
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        this.component.pointLight(value)
        this.markDirty()
        return this
    }
    public edgeAntialiasing(value: number | undefined): this {
        this.component.edgeAntialiasing(value)
        this.markDirty()
        return this
    }
    public onComplete(value: ((event?: ImageCompleteEvent) => void) | undefined): this {
        this.component.onComplete(value)
        this.markDirty()
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        this.component.onError(value)
        this.markDirty()
        return this
    }
    public onFinish(value: (() => void) | undefined): this {
        this.component.onFinish(value)
        this.markDirty()
        return this
    }
    public enableAnalyzer(value: boolean | undefined): this {
        this.component.enableAnalyzer(value)
        this.markDirty()
        return this
    }
    public analyzerConfig(value: ImageAnalyzerConfig | undefined): this {
        this.component.analyzerConfig(value)
        this.markDirty()
        return this
    }
    public resizable(value: ResizableOptions | undefined): this {
        this.component.resizable(value)
        this.markDirty()
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        this.component.privacySensitive(value)
        this.markDirty()
        return this
    }
    public enhancedImageQuality(value: image.ResolutionQuality | undefined): this {
        this.component.enhancedImageQuality(value)
        this.markDirty()
        return this
    }
    public orientation(value: ImageRotateOrientation | undefined): this {
        this.component.orientation(value)
        this.markDirty()
        return this
    }
    public supportSvg2(value: boolean | undefined): this {
        this.component.supportSvg2(value)
        this.markDirty()
        return this
    }
    public contentTransition(value: ContentTransitionEffect | undefined): this {
        this.component.contentTransition(value)
        this.markDirty()
        return this
    }
    public markDirty(): void {
        // we call this function outside of class, so need to make it public
        super.markDirty()
    }
}                  