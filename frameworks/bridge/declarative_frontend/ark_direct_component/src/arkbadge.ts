/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkBadgeComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
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

    class BadgeParamWithNumberModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().badge.setBadgeParamWithNumber(node, undefined, undefined, undefined,
            undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, 0,
            undefined, undefined, undefined, undefined);
        } else {
          if (this.value?.style === undefined) {
            getUINativeModule().badge.setBadgeParamWithNumber(node,
              isNumber(this.value?.position) ? this.value.position : undefined,
              isObject(this.value?.position) ? this.value.position?.x : undefined,
              isObject(this.value?.position) ? this.value.position?.y : undefined,
              undefined, undefined, undefined, undefined, undefined, undefined, undefined,
              isObject(this.value?.position) && !isNull(this.value?.position), this.value?.count,
              this.value?.maxCount, undefined, undefined, undefined);
          } else {
            getUINativeModule().badge.setBadgeParamWithNumber(node,
              isNumber(this.value?.position) ? this.value.position : undefined,
              isObject(this.value?.position) ? this.value.position?.x : undefined,
              isObject(this.value?.position) ? this.value.position?.y : undefined,
              this.value.style?.badgeColor, this.value.style?.badgeSize,
              this.value.style?.borderColor, this.value.style?.borderWidth,
              this.value.style?.color, this.value.style?.fontSize, this.value.style?.fontWeight,
              isObject(this.value?.position) && !isNull(this.value?.position), this.value?.count,
              this.value?.maxCount, this.value.style?.outerBorderColor,
              this.value.style?.outerBorderWidth, this.value.style?.enableAutoAvoidance);
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
        let outerBorderColorResult: boolean = false;
        let outerBorderWidthResult: boolean = false;
        let enableAutoAvoidanceResult: boolean = false;
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
          borderWidthResult = !isBaseOrResourceEqual(this.stageValue.style?.borderWidth,
            this.value.style?.borderWidth);
          badgeColorResult = !isBaseOrResourceEqual(this.stageValue.style?.badgeColor, this.value.style?.badgeColor);
          borderColorResult = !isBaseOrResourceEqual(this.stageValue.style?.borderColor,
            this.value.style?.borderColor);
          colorResult = !isBaseOrResourceEqual(this.stageValue.style?.color, this.value.style?.color);
          fontSizeResult = !isBaseOrResourceEqual(this.stageValue.style?.fontSize, this.value.style?.fontSize);
          fontWeightResult = !isBaseOrResourceEqual(this.stageValue.style?.fontWeight, this.value.style?.fontWeight);
          outerBorderColorResult = !isBaseOrResourceEqual(this.stageValue.style?.outerBorderColor,
            this.value.style?.outerBorderColor);
          outerBorderWidthResult = !isBaseOrResourceEqual(this.stageValue.style?.outerBorderWidth,
            this.value.style?.outerBorderWidth);
          enableAutoAvoidanceResult = !isBaseOrResourceEqual(this.stageValue.style?.enableAutoAvoidance,
            this.value.style?.enableAutoAvoidance);
        } else if (this.stageValue?.style !== undefined || this.value?.style !== undefined) {
          badgeSizeResult = true;
          borderWidthResult = true;
          badgeColorResult = true;
          borderColorResult = true;
          colorResult = true;
          fontSizeResult = true;
          fontWeightResult = true;
          outerBorderColorResult = true;
          outerBorderWidthResult = true;
          enableAutoAvoidanceResult = true;
        }
        return positionResult || badgeSizeResult || borderWidthResult || badgeColorResult || borderColorResult ||
          colorResult || fontSizeResult || fontWeightResult ||
          !isBaseOrResourceEqual(this.stageValue?.count, this.value?.count) ||
          !isBaseOrResourceEqual(this.stageValue?.maxCount, this.value?.maxCount) ||
          outerBorderColorResult || outerBorderWidthResult || enableAutoAvoidanceResult;
      }
    }
    (BadgeParamWithNumberModifier as any).identity = Symbol('badgeParamWithNumber');

    class BadgeParamWithStringModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().badge.setBadgeParamWithString(node, undefined, undefined, undefined,
            undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined,
            undefined, undefined, undefined);
        } else {
          if (this.value?.style === undefined) {
            getUINativeModule().badge.setBadgeParamWithString(node,
              isNumber(this.value?.position) ? this.value.position : undefined,
              isObject(this.value?.position) ? this.value.position?.x : undefined,
              isObject(this.value?.position) ? this.value.position?.y : undefined,
              undefined, undefined, undefined, undefined, undefined, undefined, undefined,
              isObject(this.value?.position) && !isNull(this.value?.position), this.value?.value,
              undefined, undefined, undefined);
          } else {
            getUINativeModule().badge.setBadgeParamWithString(node,
              isNumber(this.value?.position) ? this.value.position : undefined,
              isObject(this.value?.position) ? this.value.position?.x : undefined,
              isObject(this.value?.position) ? this.value.position?.y : undefined,
              this.value.style?.badgeColor, this.value.style?.badgeSize,
              this.value.style?.borderColor, this.value.style?.borderWidth,
              this.value.style?.color, this.value.style?.fontSize, this.value.style?.fontWeight,
              isObject(this.value?.position) && !isNull(this.value?.position), this.value?.value,
              this.value.style?.outerBorderColor, this.value.style?.outerBorderWidth,
              this.value.style?.enableAutoAvoidance);
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
        let outerBorderColorResult: boolean = false;
        let outerBorderWidthResult: boolean = false;
        let enableAutoAvoidanceResult: boolean = false;
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
          borderWidthResult = !isBaseOrResourceEqual(this.stageValue.style?.borderWidth,
            this.value.style?.borderWidth);
          badgeColorResult = !isBaseOrResourceEqual(this.stageValue.style?.badgeColor, this.value.style?.badgeColor);
          borderColorResult = !isBaseOrResourceEqual(this.stageValue.style?.borderColor,
            this.value.style?.borderColor);
          colorResult = !isBaseOrResourceEqual(this.stageValue.style?.color, this.value.style?.color);
          fontSizeResult = !isBaseOrResourceEqual(this.stageValue.style?.fontSize, this.value.style?.fontSize);
          fontWeightResult = !isBaseOrResourceEqual(this.stageValue.style?.fontWeight, this.value.style?.fontWeight);
          outerBorderColorResult = !isBaseOrResourceEqual(this.stageValue.style?.outerBorderColor,
            this.value.style?.outerBorderColor);
          outerBorderWidthResult = !isBaseOrResourceEqual(this.stageValue.style?.outerBorderWidth,
            this.value.style?.outerBorderWidth);
          enableAutoAvoidanceResult = !isBaseOrResourceEqual(this.stageValue.style?.enableAutoAvoidance,
            this.value.style?.enableAutoAvoidance);
        } else if (this.stageValue?.style !== undefined || this.value?.style !== undefined) {
          badgeSizeResult = true;
          borderWidthResult = true;
          badgeColorResult = true;
          borderColorResult = true;
          colorResult = true;
          fontSizeResult = true;
          fontWeightResult = true;
          outerBorderColorResult = true;
          outerBorderWidthResult = true;
          enableAutoAvoidanceResult = true;
        }
        return positionResult || badgeSizeResult || borderWidthResult || badgeColorResult || borderColorResult ||
          colorResult || fontSizeResult || fontWeightResult ||
          !isBaseOrResourceEqual(this.stageValue?.value, this.value?.value) ||
          outerBorderColorResult || outerBorderWidthResult || enableAutoAvoidanceResult;
      }
    }
    (BadgeParamWithStringModifier as any).identity = Symbol('badgeParamWithString');

    loadComponent.componentObj = {'component' : ArkBadgeComponent };
  }
  return loadComponent.componentObj;
}

class JSBadge extends JSContainerBase {
  static create(params: any): void {
    getUINativeModule().badge.create(params);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  }
  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }
  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }
  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }
  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkBadgeComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Badge = JSBadge;
}

export default { loadComponent, createComponent, exportComponent, exportView };
