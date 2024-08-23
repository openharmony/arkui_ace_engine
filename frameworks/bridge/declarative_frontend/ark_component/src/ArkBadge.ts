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
class ArkBadgeComponent extends ArkComponent implements BadgeAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 1;
  }
  initialize(value: Object[]): this {
    if (value.length === 1 && isObject(value[0])) {
      if (value[0]?.count !== undefined) {
        modifierWithKey(
          this._modifiersWithKeys, BadgeParamWithNumberModifier.identity, BadgeParamWithNumberModifier, value[0]);
      } else if (value[0]?.value !== undefined) {
        modifierWithKey(
          this._modifiersWithKeys, BadgeParamWithStringModifier.identity, BadgeParamWithStringModifier, value[0]);
      } else {
        modifierWithKey(
          this._modifiersWithKeys, BadgeParamWithNumberModifier.identity, BadgeParamWithNumberModifier, undefined);
      }
      return this;
    }
    modifierWithKey(
      this._modifiersWithKeys, BadgeParamWithNumberModifier.identity, BadgeParamWithNumberModifier, undefined);
    return this;
  }
}

class BadgeParamWithNumberModifier extends ModifierWithKey<BadgeParamWithNumber> {
  constructor(value: BadgeParamWithNumber) {
    super(value);
  }
  static identity: Symbol = Symbol('BadgeParamWithNumber');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().badge.setBadgeParamWithNumber(node, undefined, undefined, undefined,
        undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, 0, undefined);
    } else {
      if (this.value?.style === undefined) {
        getUINativeModule().badge.setBadgeParamWithNumber(node,
          isNumber(this.value?.position) ? this.value.position : undefined,
          isObject(this.value?.position) ? this.value.position?.x : undefined,
          isObject(this.value?.position) ? this.value.position?.y : undefined,
          undefined, undefined, undefined, undefined, undefined, undefined, undefined,
          isObject(this.value?.position) && !isNull(this.value?.position), this.value?.count, this.value?.maxCount);
      } else {
        getUINativeModule().badge.setBadgeParamWithNumber(node,
          isNumber(this.value?.position) ? this.value.position : undefined,
          isObject(this.value?.position) ? this.value.position?.x : undefined,
          isObject(this.value?.position) ? this.value.position?.y : undefined,
          this.value.style?.badgeColor, this.value.style?.badgeSize,
          this.value.style?.borderColor, this.value.style?.borderWidth,
          this.value.style?.color, this.value.style?.fontSize, this.value.style?.fontWeight,
          isObject(this.value?.position) && !isNull(this.value?.position), this.value?.count, this.value?.maxCount);
      }
    }
  }
  checkObjectDiff(): boolean {
    let positionResult: boolean = false;
    let badgeSizeResult: boolean = false;
    let borderWidthResult: boolean = false;
    let badgeColorResult: boolean = false;
    let borderColorResult: boolean = false;
    let colorResult: boolean = false;
    let fontSizeResult: boolean = false;
    let fontWeightResult: boolean = false;
    if (isNumber(this.stageValue?.position) && isNumber(this.value?.position)) {
      positionResult = !isBaseOrResourceEqual(this.stageValue.position, this.value.position);
    } else if (isObject(this.stageValue?.position) && isObject(this.value?.position)) {
      positionResult = !isBaseOrResourceEqual(this.stageValue.position?.x, this.value.position?.x) ||
        !isBaseOrResourceEqual(this.stageValue.position?.y, this.value.position?.y);
    } else if (this.stageValue?.position !== undefined || this.value?.position !== undefined) {
      positionResult = true;
    }
    if (isObject(this.stageValue?.style) && isObject(this.value?.style)) {
      badgeSizeResult = !isBaseOrResourceEqual(this.stageValue.style?.badgeSize, this.value.style?.badgeSize);
      borderWidthResult = !isBaseOrResourceEqual(this.stageValue.style?.borderWidth, this.value.style?.borderWidth);
      badgeColorResult = !isBaseOrResourceEqual(this.stageValue.style?.badgeColor, this.value.style?.badgeColor);
      borderColorResult = !isBaseOrResourceEqual(this.stageValue.style?.borderColor, this.value.style?.borderColor);
      colorResult = !isBaseOrResourceEqual(this.stageValue.style?.color, this.value.style?.color);
      fontSizeResult = !isBaseOrResourceEqual(this.stageValue.style?.fontSize, this.value.style?.fontSize);
      fontWeightResult = !isBaseOrResourceEqual(this.stageValue.style?.fontWeight, this.value.style?.fontWeight);
    } else if (this.stageValue?.style !== undefined || this.value?.style !== undefined) {
      badgeSizeResult = true;
      borderWidthResult = true;
      badgeColorResult = true;
      borderColorResult = true;
      colorResult = true;
      fontSizeResult = true;
      fontWeightResult = true;
    }
    return positionResult || badgeSizeResult || borderWidthResult || badgeColorResult || borderColorResult || colorResult ||
      fontSizeResult || fontWeightResult || !isBaseOrResourceEqual(this.stageValue?.count, this.value?.count) ||
      !isBaseOrResourceEqual(this.stageValue?.maxCount, this.value?.maxCount);
  }
}

class BadgeParamWithStringModifier extends ModifierWithKey<BadgeParamWithString> {
  constructor(value: BadgeParamWithString) {
    super(value);
  }
  static identity: Symbol = Symbol('BadgeParamWithString');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().badge.setBadgeParamWithString(node, undefined, undefined, undefined,
        undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined);
    } else {
      if (this.value?.style === undefined) {
        getUINativeModule().badge.setBadgeParamWithString(node,
          isNumber(this.value?.position) ? this.value.position : undefined,
          isObject(this.value?.position) ? this.value.position?.x : undefined,
          isObject(this.value?.position) ? this.value.position?.y : undefined,
          undefined, undefined, undefined, undefined, undefined, undefined, undefined,
          isObject(this.value?.position) && !isNull(this.value?.position), this.value?.value);
      } else {
        getUINativeModule().badge.setBadgeParamWithString(node,
          isNumber(this.value?.position) ? this.value.position : undefined,
          isObject(this.value?.position) ? this.value.position?.x : undefined,
          isObject(this.value?.position) ? this.value.position?.y : undefined,
          this.value.style?.badgeColor, this.value.style?.badgeSize,
          this.value.style?.borderColor, this.value.style?.borderWidth,
          this.value.style?.color, this.value.style?.fontSize, this.value.style?.fontWeight,
          isObject(this.value?.position) && !isNull(this.value?.position), this.value?.value);
      }
    }
  }
  checkObjectDiff(): boolean {
    let positionResult: boolean = false;
    let badgeSizeResult: boolean = false;
    let borderWidthResult: boolean = false;
    let badgeColorResult: boolean = false;
    let borderColorResult: boolean = false;
    let colorResult: boolean = false;
    let fontSizeResult: boolean = false;
    let fontWeightResult: boolean = false;
    if (isNumber(this.stageValue?.position) && isNumber(this.value?.position)) {
      positionResult = !isBaseOrResourceEqual(this.stageValue.position, this.value.position);
    } else if (isObject(this.stageValue?.position) && isObject(this.value?.position)) {
      positionResult = !isBaseOrResourceEqual(this.stageValue.position?.x, this.value.position?.x) ||
        !isBaseOrResourceEqual(this.stageValue.position?.y, this.value.position?.y);
    } else if (this.stageValue?.position !== undefined || this.value?.position !== undefined) {
      positionResult = true;
    }
    if (isObject(this.stageValue?.style) && isObject(this.value?.style)) {
      badgeSizeResult = !isBaseOrResourceEqual(this.stageValue.style?.badgeSize, this.value.style?.badgeSize);
      borderWidthResult = !isBaseOrResourceEqual(this.stageValue.style?.borderWidth, this.value.style?.borderWidth);
      badgeColorResult = !isBaseOrResourceEqual(this.stageValue.style?.badgeColor, this.value.style?.badgeColor);
      borderColorResult = !isBaseOrResourceEqual(this.stageValue.style?.borderColor, this.value.style?.borderColor);
      colorResult = !isBaseOrResourceEqual(this.stageValue.style?.color, this.value.style?.color);
      fontSizeResult = !isBaseOrResourceEqual(this.stageValue.style?.fontSize, this.value.style?.fontSize);
      fontWeightResult = !isBaseOrResourceEqual(this.stageValue.style?.fontWeight, this.value.style?.fontWeight);
    } else if (this.stageValue?.style !== undefined || this.value?.style !== undefined) {
      badgeSizeResult = true;
      borderWidthResult = true;
      badgeColorResult = true;
      borderColorResult = true;
      colorResult = true;
      fontSizeResult = true;
      fontWeightResult = true;
    }
    return positionResult || badgeSizeResult || borderWidthResult || badgeColorResult || borderColorResult || colorResult ||
      fontSizeResult || fontWeightResult || !isBaseOrResourceEqual(this.stageValue?.value, this.value?.value);
  }
}

// @ts-ignore
globalThis.Badge.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkBadgeComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CommonModifier(nativePtr, classType);
  });
};
