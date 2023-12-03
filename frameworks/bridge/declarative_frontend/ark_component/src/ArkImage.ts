/// <reference path="./import.ts" />
class ImageColorFilterModifier extends Modifier<string> {
  static identity: Symbol = Symbol('imageColorFilter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetColorFilter(node);
    } else {
      GetUINativeModule().image.setColorFilter(node, JSON.parse(this.value!));
    }
  }
}

class ImageFillColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('imageFillColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetFillColor(node);
    } else {
      GetUINativeModule().image.setFillColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class ImageAltModifier extends ModifierWithKey<ResourceColor | string> {
  static identity: Symbol = Symbol('imageAlt');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetAlt(node);
    } else {
      if (isString(this.value) || isResource(this.value)) {
        GetUINativeModule().image.setAlt(node, this.value!);
      } else {
        GetUINativeModule().image.resetAlt(node);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ImageCopyOptionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetCopyOption(node);
    } else {
      GetUINativeModule().image.setCopyOption(node, this.value!);
    }
  }
}

class ImageAutoResizeModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('imageAutoResize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetAutoResize(node);
    } else {
      GetUINativeModule().image.setAutoResize(node, this.value!);
    }
  }
}

class ImageFitOriginalSizeModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('imageFitOriginalSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetFitOriginalSize(node);
    } else {
      GetUINativeModule().image.setFitOriginalSize(node, this.value!);
    }
  }
}

class ImageDraggableModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('imageDraggable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetDraggable(node);
    } else {
      GetUINativeModule().image.setDraggable(node, this.value!);
    }
  }
}

class ImageInterpolationModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageInterpolation');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetImageInterpolation(node);
    } else {
      GetUINativeModule().image.setImageInterpolation(node, this.value!);
    }
  }
}

class ImageSourceSizeModifier extends Modifier<string> {
  static identity: Symbol = Symbol("imageSourceSize");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetSourceSize(node);
    } else {
      let values = this.value!.split("|");
      let w = parseFloat(values[0]);
      let h = parseFloat(values[1]);
      GetUINativeModule().image.setSourceSize(node, w, h);
    }
  }
}

class ImageMatchTextDirectionModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('imageMatchTextDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetMatchTextDirection(node);
    } else {
      GetUINativeModule().image.setMatchTextDirection(node, this.value!);
    }
  }
}

class ImageObjectRepeatModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageObjectRepeat');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetObjectRepeat(node);
    } else {
      GetUINativeModule().image.setObjectRepeat(node, this.value!);
    }
  }
}

class ImageRenderModeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageRenderMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetRenderMode(node);
    } else {
      GetUINativeModule().image.setRenderMode(node, this.value!);
    }
  }
}

class ImageSyncLoadModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('imageSyncLoad');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetSyncLoad(node);
    } else {
      GetUINativeModule().image.setSyncLoad(node, this.value!);
    }
  }
}

class ImageObjectFitModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageObjectFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().image.resetObjectFit(node);
    } else {
      GetUINativeModule().image.setObjectFit(node, this.value!);
    }
  }
}

class ArkImageComponent extends ArkComponent implements ImageAttribute {
  onGestureJudgeBegin(callback): this {
    throw new Error("Method not implemented.");
  }
  draggable(value: boolean): this {
    if (isBoolean(value)) {
      modifier(this._modifiers, ImageDraggableModifier, value);
    } else {
      modifier(this._modifiers, ImageDraggableModifier, undefined);
    }
    return this;
  }
  alt(value: ResourceStr): this {
    modifierWithKey(this._modifiersWithKeys, ImageAltModifier.identity, ImageAltModifier, value);
    return this;
  }
  matchTextDirection(value: boolean): this {
    if (isBoolean(value)) {
      modifier(this._modifiers, ImageMatchTextDirectionModifier, value);
    } else {
      modifier(this._modifiers, ImageMatchTextDirectionModifier, undefined);
    }
    return this;
  }
  fitOriginalSize(value: boolean): this {
    if (isBoolean(value)) {
      modifier(this._modifiers, ImageFitOriginalSizeModifier, value);
    } else {
      modifier(this._modifiers, ImageFitOriginalSizeModifier, undefined);
    }

    return this;
  }
  fillColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ImageFillColorModifier.identity,
      ImageFillColorModifier, value);
    return this;
  }
  objectFit(value: ImageFit): this {
    if (value in ImageFit) {
      modifier(this._modifiers, ImageObjectFitModifier, value);
    } else {
      modifier(this._modifiers, ImageObjectFitModifier, undefined);
    }
    return this;
  }
  objectRepeat(value: ImageRepeat): this {
    if (value) {
      modifier(this._modifiers, ImageObjectRepeatModifier, value);
    } else {
      modifier(this._modifiers, ImageObjectRepeatModifier, undefined);
    }
    return this;
  }
  autoResize(value: boolean): this {
    if (isBoolean(value)) {
      modifier(this._modifiers, ImageAutoResizeModifier, value);
    } else {
      modifier(this._modifiers, ImageAutoResizeModifier, undefined);
    }
    return this;
  }
  renderMode(value: ImageRenderMode): this {
    if (value) {
      modifier(this._modifiers, ImageRenderModeModifier, value);
    } else {
      modifier(this._modifiers, ImageRenderModeModifier, undefined);
    }
    return this;
  }
  interpolation(value: ImageInterpolation): this {
    if (value) {
      modifier(this._modifiers, ImageInterpolationModifier, value);
    } else {
      modifier(this._modifiers, ImageInterpolationModifier, undefined);
    }
    return this;
  }
  sourceSize(value: { width: number; height: number }): this {
    let w = undefined;
    let h = undefined;
    if (isNumber(value.width)) {
      w = value.width.toString();
    }
    if (isNumber(value.height)) {
      h = value.height.toString();
    }
    modifier(this._modifiers, ImageSourceSizeModifier, w + "|" + h);
    return this;
  }
  syncLoad(value: boolean): this {
    if (isBoolean(value)) {
      modifier(this._modifiers, ImageSyncLoadModifier, value);
    } else {
      modifier(this._modifiers, ImageSyncLoadModifier, undefined);
    }
    return this;
  }

  colorFilter(value: ColorFilter): this {
    if (isUndefined(value) || Object.prototype.toString.call(value) !== '[object Array]') {
      modifier(this._modifiers, ImageColorFilterModifier, undefined);
      return this;
    }
    if (Object.prototype.toString.call(value) === '[object Array]') {
      let _value: number[] = <number[]>value;
      if (_value.length !== 20) {
        modifier(this._modifiers, ImageColorFilterModifier, undefined);
        return this;
      }
    }
    modifier(this._modifiers, ImageColorFilterModifier, JSON.stringify(value));
    return this;
  }
  copyOption(value: CopyOptions): this {
    if (value in CopyOptions) {
      modifier(this._modifiers, ImageCopyOptionModifier, value);
    } else {
      modifier(this._modifiers, ImageCopyOptionModifier, undefined);
    }
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
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}