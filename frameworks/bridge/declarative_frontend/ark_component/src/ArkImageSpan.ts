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

class ImageSpanObjectFitModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('imageSpanObjectFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetObjectFit(node);
    } else {
      getUINativeModule().imageSpan.setObjectFit(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ImageSpanVerticalAlignModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('imageSpanVerticalAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetVerticalAlign(node);
    } else {
      getUINativeModule().imageSpan.setVerticalAlign(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ImageSpanTextBackgroundStyleModifier extends ModifierWithKey<TextBackgroundStyle> {
  constructor(value: TextBackgroundStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('imageSpanTextBackgroundStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetTextBackgroundStyle(node);
    }
    else {
      let textBackgroundStyle = new ArkTextBackGroundStyle();
      if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value)) {
        getUINativeModule().imageSpan.resetTextBackgroundStyle(node);
      }
      else {
        getUINativeModule().imageSpan.setTextBackgroundStyle(
          node, textBackgroundStyle.color, textBackgroundStyle.radius.topLeft,
          textBackgroundStyle.radius.topRight, textBackgroundStyle.radius.bottomLeft, textBackgroundStyle.radius.bottomRight);
      }
    }
  }
  checkObjectDiff(): boolean {
    let textBackgroundStyle = new ArkTextBackGroundStyle();
    let stageTextBackGroundStyle = new ArkTextBackGroundStyle();
    if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value) || !stageTextBackGroundStyle.convertTextBackGroundStyleOptions(this.stageValue)) {
      return false;
    }
    else {
      return textBackgroundStyle.checkObjectDiff(stageTextBackGroundStyle);
    }
  }
}
class ImageSpanBaselineOffsetModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity = Symbol('imagespanBaselineOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetBaselineOffset(node);
    } else {
      getUINativeModule().imageSpan.setBaselineOffset(node, this.value!);
    }
  }
}
class ImageSpanAltModifier extends ModifierWithKey<PixelMap> {
  constructor(value: PixelMap) {
    super(value);
  }
  static identity = Symbol('imagespanAlt');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetAlt(node);
    } else {
      getUINativeModule().imageSpan.setAlt(node, this.value!);
    }
  }
}
class ImageSpanOnCompleteModifier extends ModifierWithKey<(event?: {width: number; height: number; componentWidth: number; componentHeight: number; loadingStatus: number; contentWidth: number; contentHeight: number; contentOffsetX: number; contentOffsetY: number;}) => void> {
  constructor(value: (event?: {width: number; height: number; componentWidth: number; componentHeight: number; loadingStatus: number; contentWidth: number; contentHeight: number; contentOffsetX: number; contentOffsetY: number;}) => void) {
    super(value);
  }
  static identity = Symbol('imageSpanOnComplete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetOnComplete(node);
    } else {
      getUINativeModule().imageSpan.setOnComplete(node, this.value);
    }
  }
}
class ImageSpanOnErrorModifier extends ModifierWithKey<(result: {componentWidth: number; componentHeight: number; message: string}) => void> {
  constructor(value: (event: {componentWidth: number; componentHeight: number; message: string}) => void) {
    super(value);
  }
  static identity = Symbol('imageSpanOnError');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetOnError(node);
    } else {
      getUINativeModule().imageSpan.setOnError(node, this.value);
    }
  }
}
class ImageSpanColorFilterModifier extends ModifierWithKey<ColorFilter | DrawingColorFilter> {
  constructor(value: ColorFilter) {
    super(value);
  }
  static identity: Symbol = Symbol('ImageSpanColorFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetColorFilter(node);
    } else {
      getUINativeModule().imageSpan.setColorFilter(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
class ImageSpanSupportSvg2Modifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('supportSvg2');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetSupportSvg2(node);
    } else {
      getUINativeModule().imageSpan.setSupportSvg2(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
declare class Utils {
  static isApiVersionEQAbove(version: number): boolean;
}
class ImageSpanBorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses> {
  constructor(value: Length | BorderRadiuses) {
    super(value);
  }
  static identity: Symbol = Symbol('imageSpanBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().imageSpan.setBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        let keys = Object.keys(this.value);
        if (Utils.isApiVersionEQAbove(20) &&
          (keys.indexOf('topStart') >= 0 || keys.indexOf('topEnd') >= 0 ||
          keys.indexOf('bottomStart') >= 0 || keys.indexOf('bottomEnd') >= 0)) {
          let localizedBorderRadius = this.value as LocalizedBorderRadiuses;
          getUINativeModule().imageSpan.setBorderRadius(node, localizedBorderRadius.topStart,
            localizedBorderRadius.topEnd, localizedBorderRadius.bottomStart, localizedBorderRadius.bottomEnd);
        } else {
          getUINativeModule().imageSpan.setBorderRadius(node, (this.value as any).topLeft, (this.value as any).topRight,
            (this.value as any).bottomLeft, (this.value as any).bottomRight);
        }
      }
    }
  }
  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as any).topLeft === (this.value as any).topLeft &&
        (this.stageValue as any).topRight === (this.value as any).topRight &&
        (this.stageValue as any).bottomLeft === (this.value as any).bottomLeft &&
        (this.stageValue as any).bottomRight === (this.value as any).bottomRight);
    } else {
      return true;
    }
  }
}
class ImageSpanSrcModifier extends ModifierWithKey<ResourceStr | PixelMap> {
  constructor(value: ResourceStr | PixelMap) {
    super(value);
  }
  static identity: Symbol = Symbol('imageSpanShowSrc');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.setImageSpanSrc(node, '');
    } else {
      getUINativeModule().imageSpan.setImageSpanSrc(node, this.value);
    }
  }
}

class ArkImageSpanComponent extends ArkComponent {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanSrcModifier.identity, ImageSpanSrcModifier, value[0]);
    return this;
  }
  objectFit(value: ImageFit): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanObjectFitModifier.identity, ImageSpanObjectFitModifier, value);
    return this;
  }
  verticalAlign(value: ImageSpanAlignment): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanVerticalAlignModifier.identity, ImageSpanVerticalAlignModifier, value);
    return this;
  }
  textBackgroundStyle(value: TextBackgroundStyle): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanTextBackgroundStyleModifier.identity, ImageSpanTextBackgroundStyleModifier, value);
    return this;
  }
  baselineOffset(value: LengthMetrics): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanBaselineOffsetModifier.identity, ImageSpanBaselineOffsetModifier, value);
    return this;
  }
  alt(value: PixelMap): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanAltModifier.identity, ImageSpanAltModifier, value);
    return this;
  }
  colorFilter(value: ColorFilter | DrawingColorFilter): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanColorFilterModifier.identity,
      ImageSpanColorFilterModifier, value);
    return this;
  }
  supportSvg2(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanSupportSvg2Modifier.identity, ImageSpanSupportSvg2Modifier, value);
    return this;
  }
  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(
      this._modifiersWithKeys, ImageSpanBorderRadiusModifier.identity, ImageSpanBorderRadiusModifier, value);
    return this;
  }
  onComplete(
    callback: (result: {
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
    modifierWithKey(this._modifiersWithKeys, ImageSpanOnCompleteModifier.identity, ImageSpanOnCompleteModifier, callback);
    return this;
  }
  onError(callback: (error: {
    componentWidth: number;
    componentHeight: number;
    message: string
  }) => void): this {
    modifierWithKey(this._modifiersWithKeys, ImageSpanOnErrorModifier.identity, ImageSpanOnErrorModifier, callback);
    return this;
  }
}
// @ts-ignore
if (globalThis.ImageSpan !== undefined) {
  (globalThis as any).ImageSpan.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkImageSpanComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ImageSpanModifier(nativePtr, classType);
    });
  };
}
