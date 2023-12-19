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
class ArkTextClockComponent extends ArkComponent implements TextClockAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  format(value: string): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFormatModifier.identity, TextClockFormatModifier, value);
    return this;
  }
  onDateChange(event: (value: number) => void): this {
    throw new Error('Method not implemented.');
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontColorModifier.identity, TextClockFontColorModifier, value);
    return this;
  }
  fontSize(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontSizeModifier.identity, TextClockFontSizeModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontStyleModifier.identity, TextClockFontStyleModifier, value);
    return this;
  }
  fontWeight(value: string | number | FontWeight): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontWeightModifier.identity, TextClockFontWeightModifier, value);
    return this;
  }
  fontFamily(value: ResourceStr): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontFamilyModifier.identity, TextClockFontFamilyModifier, value);
    return this;
  }
  textShadow(value: ShadowOptions): this {
    throw new Error('Method not implemented.');
  }
  fontFeature(value: string): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class TextClockFormatModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFormat');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFormat(node);
    } else {
      GetUINativeModule().textClock.setFormat(node, this.value);
    }
  }
}

class TextClockFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontColor(node);
    } else {
      GetUINativeModule().textClock.setFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontSize(node);
    } else {
      GetUINativeModule().textClock.setFontSize(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockFontStyleModifier extends ModifierWithKey<FontStyle> {
  constructor(value: FontStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontStyle(node);
    } else {
      GetUINativeModule().textClock.setFontStyle(node, this.value!);
    }
  }
}

class TextClockFontWeightModifier extends ModifierWithKey<number | FontWeight | string> {
  constructor(value: number | FontWeight | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontWeight(node);
    } else {
      GetUINativeModule().textClock.setFontWeight(node, this.value!);
    }
  }
}

class TextClockFontFamilyModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textClock.resetFontFamily(node);
    } else {
      GetUINativeModule().textClock.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.TextClock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextClockComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
