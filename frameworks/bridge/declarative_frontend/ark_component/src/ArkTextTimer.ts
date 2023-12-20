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
class ArkTextTimerComponent extends ArkComponent implements TextTimerAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  fontColor(value: any): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontColorModifier.identity, TextTimerFontColorModifier, value);
    return this;
  }

  fontSize(value: any): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontSizeModifier.identity, TextTimerFontSizeModifier, value);
    return this;
  }

  fontWeight(value: number | FontWeight | string): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontWeightModifier.identity, TextTimerFontWeightModifier, value);
    return this;
  }

  fontStyle(value: FontStyle): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontStyleModifier.identity, TextTimerFontStyleModifier, value);
    return this;
  }

  fontFamily(value: string | Resource): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontFamilyModifier.identity, TextTimerFontFamilyModifier, value);
    return this;
  }

  format(value: string): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerFormatModifier.identity, TextTimerFormatModifier, value);
    return this;
  }

  onTimer(event: (utc: number, elapsedTime: number) => void): this {
    throw new Error('Method not implemented.');
  }
}

class TextTimerFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textTimer.resetFontColor(node);
    } else {
      GetUINativeModule().textTimer.setFontColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTimerFontSizeModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('fontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textTimer.resetFontSize(node);
    } else {
      GetUINativeModule().textTimer.setFontSize(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTimerFontWeightModifier extends ModifierWithKey<number | FontWeight | string> {
  static identity: Symbol = Symbol('fontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textTimer.resetFontWeight(node);
    } else {
      GetUINativeModule().textTimer.setFontWeight(node, this.value);
    }
  }
}

class TextTimerFontStyleModifier extends ModifierWithKey<FontStyle> {
  static identity: Symbol = Symbol('fontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textTimer.resetFontStyle(node);
    } else {
      GetUINativeModule().textTimer.setFontStyle(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTimerFontFamilyModifier extends ModifierWithKey<string | Resource> {
  static identity: Symbol = Symbol('fontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textTimer.resetFontFamily(node);
    } else {
      GetUINativeModule().textTimer.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextTimerFormatModifier extends ModifierWithKey<string> {
  static identity: Symbol = Symbol('textTimerFormat');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textTimer.resetFormat(node);
    }
    else {
      GetUINativeModule().textTimer.setFormat(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.TextTimer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextTimerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
