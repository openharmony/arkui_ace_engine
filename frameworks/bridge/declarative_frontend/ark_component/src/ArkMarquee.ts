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
const MarqueeFontWeightMap = {
  0: 'lighter',
  1: 'normal',
  2: 'regular',
  3: 'medium',
  4: 'bold',
  5: 'bolder',
  100: '100',
  200: '200',
  300: '300',
  400: '400',
  500: '500',
  600: '600',
  700: '700',
  800: '800',
  900: '900',
}

class ArkMarqueeComponent extends ArkComponent implements MarqueeAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  fontSize(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontSizeModifier.identity, MarqueeFontSizeModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontColorModifier.identity, MarqueeFontColorModifier, value);
    return this;
  }
  allowScale(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeAllowScaleModifier.identity, MarqueeAllowScaleModifier, value);
    return this;
  }
  fontWeight(value: string | number | FontWeight): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontWeightModifier.identity, MarqueeFontWeightModifier, value);
    return this;
  }
  fontFamily(value: any): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontFamilyModifier.identity, MarqueeFontFamilyModifier, value as string);
    return this;
  }
  onStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onBounce(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onFinish(event: () => void): this {
    throw new Error('Method not implemented.');
  }
}

class MarqueeFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetFontColor(node);
    } else {
      GetUINativeModule().marquee.setFontColor(node, this.value);
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
class MarqueeFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol("fontSize");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetFontSize(node);
    }
    else {
      GetUINativeModule().marquee.setFontSize(node, this.value);
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
class MarqueeAllowScaleModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('allowScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetAllowScale(node);
    }
    else {
      GetUINativeModule().marquee.setAllowScale(node, this.value);
    }
  }
}
class MarqueeFontWeightModifier extends ModifierWithKey<string | number | FontWeight> {
  constructor(value: string | number | FontWeight) {
    super(value);
  }
  static identity: Symbol = Symbol('fontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetFontWeight(node);
    }
    else {
      let fontWeightStr = 'normal';
      if (typeof this.value === "string") {
        fontWeightStr = this.value;
      } else {
        if (this.value in MarqueeFontWeightMap) {
          fontWeightStr = MarqueeFontWeightMap[this.value];
        }
      }
      GetUINativeModule().marquee.setFontWeight(node, fontWeightStr);
    }
  }
}
class MarqueeFontFamilyModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('fontFamily');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
        GetUINativeModule().marquee.resetFontFamily(node);
      }
      else {
        GetUINativeModule().marquee.setFontFamily(node, this.value);
      }
  }
}
// @ts-ignore
globalThis.Marquee.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkMarqueeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
