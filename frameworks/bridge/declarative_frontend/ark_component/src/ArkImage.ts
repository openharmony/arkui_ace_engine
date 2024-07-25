/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />
class ImageColorFilterModifier extends ModifierWithKey<ColorFilter | DrawingColorFilter> {
  constructor(value: ColorFilter) {
    super(value);
  }
  static identity: Symbol = Symbol('imageColorFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetColorFilter(node);
    } else {
      getUINativeModule().image.setColorFilter(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ImageFillColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('imageFillColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetFillColor(node);
    } else {
      getUINativeModule().image.setFillColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ImageAltModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAlt');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetAlt(node);
    } else {
      getUINativeModule().image.setAlt(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ImageCopyOptionModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('imageCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetCopyOption(node);
    } else {
      getUINativeModule().image.setCopyOption(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageAutoResizeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageAutoResize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetAutoResize(node);
    } else {
      getUINativeModule().image.setAutoResize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageFitOriginalSizeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageFitOriginalSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetFitOriginalSize(node);
    } else {
      getUINativeModule().image.setFitOriginalSize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageDraggableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageDraggable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetDraggable(node);
    } else {
      getUINativeModule().image.setDraggable(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageEdgeAntialiasingModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('edgeAntialiasing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetSourceSize(node);
    } else {
      getUINativeModule().image.setSourceSize(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageResizableModifier extends ModifierWithKey<ResizableOptions> {
  constructor(value: ResizableOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('resizable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetResizable(node);
    } else {
      if (!isUndefined(this.value.lattice)) {
        getUINativeModule().image.setResizableLattice(node, this.value.lattice);
      }
      if (!isUndefined(this.value.slice)) {
        let sliceTop: Length | undefined;
        let sliceRight: Length | undefined;
        let sliceBottom: Length | undefined;
        let sliceLeft: Length | undefined;
        let tmpSlice = this.value.slice as EdgeWidths;
        sliceTop = tmpSlice.top;
        sliceRight = tmpSlice.right;
        sliceBottom = tmpSlice.bottom;
        sliceLeft = tmpSlice.left;
        getUINativeModule().image.setResizable(node, sliceTop, sliceRight, sliceBottom, sliceLeft);
      }
    }
  }
}

class ImageDynamicRangeModeModifier extends ModifierWithKey<DynamicRangeMode> {
  constructor(value: DynamicRangeMode) {
    super(value);
  }
  static identity: Symbol = Symbol('dynamicRangeMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetDynamicRangeMode(node);
    } else {
      getUINativeModule().image.setDynamicRangeMode(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageEnhancedImageQualityModifier extends ModifierWithKey<AIImageQuality> {
  constructor(value: ResolutionQuality) {
    super(value);
  }
  static identity: Symbol = Symbol('enhancedImageQuality');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetEnhancedImageQuality(node);
    } else {
      getUINativeModule().image.setEnhancedImageQuality(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageInterpolationModifier extends ModifierWithKey<ImageInterpolation> {
  constructor(value: ImageInterpolation) {
    super(value);
  }
  static identity: Symbol = Symbol('imageInterpolation');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetImageInterpolation(node);
    } else {
      getUINativeModule().image.setImageInterpolation(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageSourceSizeModifier extends ModifierWithKey<{ width: number; height: number }> {
  constructor(value: { width: number; height: number }) {
    super(value);
  }
  static identity: Symbol = Symbol('imageSourceSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetSourceSize(node);
    } else {
      getUINativeModule().image.setSourceSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue.width !== this.value.width ||
      this.stageValue.height !== this.value.height;
  }
}

class ImageMatchTextDirectionModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageMatchTextDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetMatchTextDirection(node);
    } else {
      getUINativeModule().image.setMatchTextDirection(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageObjectRepeatModifier extends ModifierWithKey<ImageRepeat> {
  constructor(value: ImageRepeat) {
    super(value);
  }
  static identity: Symbol = Symbol('imageObjectRepeat');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetObjectRepeat(node);
    } else {
      getUINativeModule().image.setObjectRepeat(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageRenderModeModifier extends ModifierWithKey<ImageRenderMode> {
  constructor(value: ImageRenderMode) {
    super(value);
  }
  static identity: Symbol = Symbol('imageRenderMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetRenderMode(node);
    } else {
      getUINativeModule().image.setRenderMode(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageSyncLoadModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageSyncLoad');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetSyncLoad(node);
    } else {
      getUINativeModule().image.setSyncLoad(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ImageObjectFitModifier extends ModifierWithKey<ImageFit> {
  constructor(value: ImageFit) {
    super(value);
  }
  static identity: Symbol = Symbol('imageObjectFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetObjectFit(node);
    } else {
      getUINativeModule().image.setObjectFit(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ImageBorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses> {
  constructor(value: Length | BorderRadiuses) {
    super(value);
  }
  static identity: Symbol = Symbol('imageBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().image.setBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        let keys = Object.keys(this.value);
        if (keys.indexOf('topStart') >= 0 || keys.indexOf('topEnd') >= 0 ||
          keys.indexOf('bottomStart') >= 0 || keys.indexOf('bottomEnd') >= 0) {
            let localizedBorderRadius = this.value as LocalizedBorderRadiuses;
            getUINativeModule().image.setBorderRadius(node, localizedBorderRadius.topStart,
              localizedBorderRadius.topEnd, localizedBorderRadius.bottomStart,
              localizedBorderRadius.bottomEnd);
        } else {
          let borderRadius = this.value as BorderRadiuses;
          getUINativeModule().image.setBorderRadius(node,
            borderRadius.topLeft, borderRadius.topRight,
            borderRadius.bottomLeft, borderRadius.bottomRight);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}
class ImageBorderModifier extends ModifierWithKey<BorderOptions> {
  constructor(value: BorderOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('imageBorder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetImageBorder(node);
    } else {
      let widthLeft;
      let widthRight;
      let widthTop;
      let widthBottom;
      if (!isUndefined(this.value.width) && this.value.width !== null) {
        if (isNumber(this.value.width) || isString(this.value.width) || isResource(this.value.width)) {
          widthLeft = this.value.width;
          widthRight = this.value.width;
          widthTop = this.value.width;
          widthBottom = this.value.width;
        } else {
          widthLeft = (this.value.width as EdgeWidths).left;
          widthRight = (this.value.width as EdgeWidths).right;
          widthTop = (this.value.width as EdgeWidths).top;
          widthBottom = (this.value.width as EdgeWidths).bottom;
        }
      }
      let leftColor;
      let rightColor;
      let topColor;
      let bottomColor;
      if (!isUndefined(this.value.color) && this.value.color !== null) {
        if (isNumber(this.value.color) || isString(this.value.color) || isResource(this.value.color)) {
          leftColor = this.value.color;
          rightColor = this.value.color;
          topColor = this.value.color;
          bottomColor = this.value.color;
        } else {
          leftColor = (this.value.color as EdgeColors).left;
          rightColor = (this.value.color as EdgeColors).right;
          topColor = (this.value.color as EdgeColors).top;
          bottomColor = (this.value.color as EdgeColors).bottom;
        }
      }
      let topLeft;
      let topRight;
      let bottomLeft;
      let bottomRight;
      if (!isUndefined(this.value.radius) && this.value.radius !== null) {
        if (isNumber(this.value.radius) || isString(this.value.radius) || isResource(this.value.radius)) {
          topLeft = this.value.radius;
          topRight = this.value.radius;
          bottomLeft = this.value.radius;
          bottomRight = this.value.radius;
        } else {
          topLeft = (this.value.radius as BorderRadiuses).topLeft;
          topRight = (this.value.radius as BorderRadiuses).topRight;
          bottomLeft = (this.value.radius as BorderRadiuses).bottomLeft;
          bottomRight = (this.value.radius as BorderRadiuses).bottomRight;
        }
      }
      let styleTop;
      let styleRight;
      let styleBottom;
      let styleLeft;
      if (!isUndefined(this.value.style) && this.value.style != null) {
        if (isNumber(this.value.style) || isString(this.value.style) || isResource(this.value.style)) {
          styleTop = this.value.style;
          styleRight = this.value.style;
          styleBottom = this.value.style;
          styleLeft = this.value.style;
        } else {
          styleTop = (this.value.style as EdgeStyles).top;
          styleRight = (this.value.style as EdgeStyles).right;
          styleBottom = (this.value.style as EdgeStyles).bottom;
          styleLeft = (this.value.style as EdgeStyles).left;
        }
      }
      getUINativeModule().image.setImageBorder(
        node,
        widthLeft,
        widthRight,
        widthTop,
        widthBottom,
        leftColor,
        rightColor,
        topColor,
        bottomColor,
        topLeft,
        topRight,
        bottomLeft,
        bottomRight,
        styleTop,
        styleRight,
        styleBottom,
        styleLeft
      );
    }
  }

  checkObjectDiff(): boolean {
    return (
      !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.radius, this.value.radius) ||
      !isBaseOrResourceEqual(this.stageValue.style, this.value.style)
    );
  }
}

class ImageOpacityModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('imageOpacity');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetImageOpacity(node);
    } else {
      getUINativeModule().image.setImageOpacity(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ImageTransitionModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('imageTransition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetImageTransition(node);
    } else {
      getUINativeModule().image.setImageTransition(node, this.value);
    }
  }
}

class ImageSrcModifier extends ModifierWithKey<ResourceStr | PixelMap | DrawableDescriptor | ImageContent> {
  constructor(value: ResourceStr | PixelMap | DrawableDescriptor | ImageContent) {
    super(value);
  }
  static identity: Symbol = Symbol('imageShowSrc');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.setImageShowSrc(node, "");
    }
    else {
      getUINativeModule().image.setImageShowSrc(node, this.value);
    }
  }
}

class ImageEnableAnalyzerModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('enableAnalyzer');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.enableAnalyzer(node);
    } else {
      getUINativeModule().image.enableAnalyzer(node, this.value!);
    }
  }
}

class ImagePrivacySensitiveModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imagePrivacySensitive');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetPrivacySensitive(node);
    } else {
      getUINativeModule().image.setPrivacySensitive(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ImageAnalyzerConfigModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('analyzerConfig');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.analyzerConfig(node, '');
    } else {
      getUINativeModule().image.analyzerConfig(node, this.value!);
    }
  }
}

class ImageOnErrorModifier extends ModifierWithKey<(result: {componentWidth: number; componentHeight: number; message: string}) => void> {
    constructor(value: (event: {componentWidth: number; componentHeight: number; message: string}) => void) {
    super(value);
  }
  static identity = Symbol('imageOnError');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetOnError(node);
    } else {
      getUINativeModule().image.setOnError(node, this.value);
    }
  }
}

class ImageOnFinishModifier extends ModifierWithKey<VoidCallback> {
    constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('imageOnFinish');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetOnFinish(node);
    } else {
      getUINativeModule().image.setOnFinish(node, this.value);
    }
  }
}

class ImagePointLightModifier extends ModifierWithKey<PointLightStyle> {
  constructor(value: PointLightStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('imagePointLight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX: Dimension | undefined;
      let positionY: Dimension | undefined;
      let positionZ: Dimension | undefined;
      let intensity: number | undefined;
      let color: ResourceColor | undefined;
      let illuminated: number | undefined;
      let bloom: number | undefined;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}
class ImageOnCompleteModifier extends ModifierWithKey<(event?: {
  width: number;
  height: number;
  componentWidth: number;
  componentHeight: number;
  loadingStatus: number;
  contentWidth: number;
  contentHeight: number;
  contentOffsetX: number;
  contentOffsetY: number;
}) => void> {
  constructor(value: (event?: {
    width: number;
    height: number;
    componentWidth: number;
    componentHeight: number;
    loadingStatus: number;
    contentWidth: number;
    contentHeight: number;
    contentOffsetX: number;
    contentOffsetY: number;
  }) => void) {
    super(value);
  }
  static identity = Symbol('imageOnComplete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().image.resetOnComplete(node);
    } else {
      getUINativeModule().image.setOnComplete(node, this.value);
    }
  }
}
class ArkImageComponent extends ArkComponent implements ImageAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): this {
    modifierWithKey(this._modifiersWithKeys, ImageSrcModifier.identity, ImageSrcModifier, value[0]);
    return this;
  }
  allowChildCount(): number {
    return 0;
  }
  draggable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageDraggableModifier.identity, ImageDraggableModifier, value);
    return this;
  }
  edgeAntialiasing(value: number): this {
    modifierWithKey(this._modifiersWithKeys, ImageEdgeAntialiasingModifier.identity, ImageEdgeAntialiasingModifier, value);
    return this;
  }
  alt(value: ResourceStr): this {
    modifierWithKey(this._modifiersWithKeys, ImageAltModifier.identity, ImageAltModifier, value);
    return this;
  }
  matchTextDirection(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageMatchTextDirectionModifier.identity, ImageMatchTextDirectionModifier, value);
    return this;
  }
  fitOriginalSize(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageFitOriginalSizeModifier.identity, ImageFitOriginalSizeModifier, value);
    return this;
  }
  pointLight(value: PointLightStyle): this {
    modifierWithKey(this._modifiersWithKeys, ImagePointLightModifier.identity, ImagePointLightModifier, value);
    return this;
  }
  fillColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ImageFillColorModifier.identity,
      ImageFillColorModifier, value);
    return this;
  }
  objectFit(value: ImageFit): this {
    modifierWithKey(this._modifiersWithKeys, ImageObjectFitModifier.identity,
      ImageObjectFitModifier, value);
    return this;
  }
  objectRepeat(value: ImageRepeat): this {
    modifierWithKey(this._modifiersWithKeys, ImageObjectRepeatModifier.identity,
      ImageObjectRepeatModifier, value);
    return this;
  }
  autoResize(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageAutoResizeModifier.identity,
      ImageAutoResizeModifier, value);
    return this;
  }
  renderMode(value: ImageRenderMode): this {
    modifierWithKey(this._modifiersWithKeys, ImageRenderModeModifier.identity,
      ImageRenderModeModifier, value);
    return this;
  }
  interpolation(value: ImageInterpolation): this {
    modifierWithKey(this._modifiersWithKeys, ImageInterpolationModifier.identity,
      ImageInterpolationModifier, value);
    return this;
  }
  sourceSize(value: { width: number; height: number }): this {
    modifierWithKey(this._modifiersWithKeys, ImageSourceSizeModifier.identity,
      ImageSourceSizeModifier, value);
    return this;
  }
  syncLoad(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageSyncLoadModifier.identity,
      ImageSyncLoadModifier, value);
    return this;
  }

  colorFilter(value: ColorFilter | DrawingColorFilter): this {
    modifierWithKey(this._modifiersWithKeys, ImageColorFilterModifier.identity,
      ImageColorFilterModifier, value);
    return this;
  }
  copyOption(value: CopyOptions): this {
    modifierWithKey(this._modifiersWithKeys, ImageCopyOptionModifier.identity,
      ImageCopyOptionModifier, value);
    return this;
  }
  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, ImageBorderRadiusModifier.identity, ImageBorderRadiusModifier, value);
    return this;
  }
  onComplete(
    callback: (event?: {
      width: number;
      height: number;
      componentWidth: number;
      componentHeight: number;
      loadingStatus: number;
      contentWidth: number;
      contentHeight: number;
      contentOffsetX: number;
      contentOffsetY: number;
    }) => void,
  ): this {
    modifierWithKey(this._modifiersWithKeys, ImageOnCompleteModifier.identity, ImageOnCompleteModifier, value);
    return this;
  }
  onError(callback: (event: {
    componentWidth: number;
    componentHeight: number;
    message: string
  }) => void): this {
    modifierWithKey(this._modifiersWithKeys, ImageOnErrorModifier.identity, ImageOnErrorModifier, callback);
    return this;
  }
  onFinish(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, ImageOnFinishModifier.identity, ImageOnFinishModifier, event);
    return this;
  }
  border(value: BorderOptions): this {
    modifierWithKey(this._modifiersWithKeys, ImageBorderModifier.identity, ImageBorderModifier, value);
    return this;
  }
  opacity(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, ImageOpacityModifier.identity, ImageOpacityModifier, value);
    return this;
  }
  transition(value: TransitionOptions | TransitionEffect): this {
    modifierWithKey(this._modifiersWithKeys, ImageTransitionModifier.identity, ImageTransitionModifier, value);
    return this;
  }
  dynamicRangeMode(value: DynamicRangeMode): this {
    modifierWithKey(
      this._modifiersWithKeys, ImageDynamicRangeModeModifier.identity, ImageDynamicRangeModeModifier, value);
    return this;
  }
  enhancedImageQuality(value: ResolutionQuality): this {
    modifierWithKey(
      this._modifiersWithKeys, ImageDynamicRangeModeModifier.identity, ImageDynamicRangeModeModifier, value);
    return this;
  }
  enableAnalyzer(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageEnableAnalyzerModifier.identity, ImageEnableAnalyzerModifier, value);
    return this;
  }
  privacySensitive(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageEnableAnalyzerModifier.identity, ImageEnableAnalyzerModifier, value);
    return this;
  }
  analyzerConfig(value: object): this {
    modifierWithKey(this._modifiersWithKeys, ImageAnalyzerConfigModifier.identity, ImageAnalyzerConfigModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Image.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkImageComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ImageModifier(nativePtr, classType);
  });
};
