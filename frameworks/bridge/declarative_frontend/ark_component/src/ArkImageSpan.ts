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
        getUINativeModule().imageSpan.setTextBackgroundStyle(node, textBackgroundStyle.color, textBackgroundStyle.radius.topLeft, textBackgroundStyle.radius.topRight, textBackgroundStyle.radius.bottomLeft, textBackgroundStyle.radius.bottomRight);
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
  static identity = Symbol('imageSpanBaselineOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().imageSpan.resetBaselineOffset(node);
    } else {
      getUINativeModule().imageSpan.setBaselineOffset(node, this.value!);
    }
  }
}
class ArkImageSpanComponent extends ArkComponent implements ImageSpanAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  padding(value: Padding | Length): this {
    throw new Error('Method not implemented.');
  }
  margin(value: Margin | Length): this {
    throw new Error('Method not implemented.');
  }
  objectFit(value: ImageFit): ImageSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageSpanObjectFitModifier.identity, ImageSpanObjectFitModifier, value);
    return this;
  }
  verticalAlign(value: ImageSpanAlignment): ImageSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageSpanVerticalAlignModifier.identity, ImageSpanVerticalAlignModifier, value);
    return this;
  }
  textBackgroundStyle(value: TextBackgroundStyle): ImageSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageSpanTextBackgroundStyleModifier.identity, ImageSpanTextBackgroundStyleModifier, value);
    return this;
  }
  baselineOffset(value: LengthMetrics): ImageSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageSpanBaselineOffsetModifier.identity, ImageSpanBaselineOffsetModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.ImageSpan.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkImageSpanComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ImageSpanModifier(nativePtr, classType);
  });
};
