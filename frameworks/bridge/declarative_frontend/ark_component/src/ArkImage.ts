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

/// <reference path="./import.ts" />
class ImageColorFilterModifier extends ModifierWithKey<ColorFilter> {
  constructor(value: ColorFilter) {
    super(value);
  }
  static identity: Symbol = Symbol('imageColorFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetColorFilter(node);
    } else {
      GetUINativeModule().image.setColorFilter(node, this.value!);
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
      GetUINativeModule().image.resetFillColor(node);
    } else {
      GetUINativeModule().image.setFillColor(node, this.value!);
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
      GetUINativeModule().image.resetAlt(node);
    } else {
      GetUINativeModule().image.setAlt(node, this.value!);
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
      GetUINativeModule().image.resetCopyOption(node);
    } else {
      GetUINativeModule().image.setCopyOption(node, this.value!);
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
      GetUINativeModule().image.resetAutoResize(node);
    } else {
      GetUINativeModule().image.setAutoResize(node, this.value!);
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
      GetUINativeModule().image.resetFitOriginalSize(node);
    } else {
      GetUINativeModule().image.setFitOriginalSize(node, this.value!);
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
      GetUINativeModule().image.resetDraggable(node);
    } else {
      GetUINativeModule().image.setDraggable(node, this.value!);
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
      GetUINativeModule().image.resetImageInterpolation(node);
    } else {
      GetUINativeModule().image.setImageInterpolation(node, this.value!);
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
  static identity: Symbol = Symbol("imageSourceSize");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetSourceSize(node);
    } else {
      GetUINativeModule().image.setSourceSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue.width !== this.value.width ||
      this.stageValue.height !== this.value.height
  }
}

class ImageMatchTextDirectionModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('imageMatchTextDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetMatchTextDirection(node);
    } else {
      GetUINativeModule().image.setMatchTextDirection(node, this.value!);
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
      GetUINativeModule().image.resetObjectRepeat(node);
    } else {
      GetUINativeModule().image.setObjectRepeat(node, this.value!);
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
      GetUINativeModule().image.resetRenderMode(node);
    } else {
      GetUINativeModule().image.setRenderMode(node, this.value!);
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
      GetUINativeModule().image.resetSyncLoad(node);
    } else {
      GetUINativeModule().image.setSyncLoad(node, this.value!);
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
      GetUINativeModule().image.resetObjectFit(node);
    } else {
      GetUINativeModule().image.setObjectFit(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkImageComponent extends ArkComponent implements ImageAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback): this {
    throw new Error("Method not implemented.");
  }
  draggable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ImageDraggableModifier.identity, ImageDraggableModifier, value);
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

  colorFilter(value: ColorFilter): this {
    modifierWithKey(this._modifiersWithKeys, ImageColorFilterModifier.identity,
      ImageColorFilterModifier, value);
    return this;
  }
  copyOption(value: CopyOptions): this {
    modifierWithKey(this._modifiersWithKeys, ImageCopyOptionModifier.identity,
      ImageCopyOptionModifier, value);
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
    throw new Error('Method not implemented.');
  }

  onError(callback: (event: {
    componentWidth: number;
    componentHeight: number;
    message: string
  }) => void): this {
    throw new Error('Method not implemented.');
  }
  onFinish(event: () => void): this {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Image.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkImageComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}