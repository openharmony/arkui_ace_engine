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
class ArkImageSpanComponent extends ArkComponent implements ImageSpanAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  objectFit(value: ImageFit): ImageSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageSpanObjectFitModifier.identity, ImageSpanObjectFitModifier, value);
    return this;
  }
  verticalAlign(value: ImageSpanAlignment): ImageSpanAttribute {
    modifierWithKey(this._modifiersWithKeys, ImageSpanVerticalAlignModifier.identity, ImageSpanVerticalAlignModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.ImageSpan.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkImageSpanComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
