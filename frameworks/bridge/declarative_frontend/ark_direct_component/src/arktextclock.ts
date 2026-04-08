/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
    class ArkTextClockComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      allowChildCount(): number {
        return 0;
      }
      initialize(value: any): this {
        if (value.length === 1 && isObject(value[0])) {
          if (value[0]?.timeZoneOffset !== undefined) {
            modifierWithKey(this._modifiersWithKeys, TextClockTimeZoneOffsetModifier.identity, TextClockTimeZoneOffsetModifier, value[0].timeZoneOffset);
          } else {
            modifierWithKey(this._modifiersWithKeys, TextClockTimeZoneOffsetModifier.identity, TextClockTimeZoneOffsetModifier, undefined);
          }
          if (value[0]?.controller !== undefined) {
            modifierWithKey(this._modifiersWithKeys, TextClockControllerModifier.identity, TextClockControllerModifier, value[0].controller);
          } else {
            modifierWithKey(this._modifiersWithKeys, TextClockControllerModifier.identity, TextClockControllerModifier, undefined);
          }
        } else {
          modifierWithKey(this._modifiersWithKeys, TextClockTimeZoneOffsetModifier.identity, TextClockTimeZoneOffsetModifier, undefined);
          modifierWithKey(this._modifiersWithKeys, TextClockControllerModifier.identity, TextClockControllerModifier, undefined);
        }
        return this;
      }
      format(value: string): this {
        modifierWithKey(this._modifiersWithKeys, TextClockFormatModifier.identity, TextClockFormatModifier, value);
        return this;
      }
      onDateChange(event: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockOnDateChangeModifier.identity, TextClockOnDateChangeModifier, event);
        return this;
      }
      fontColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockFontColorModifier.identity, TextClockFontColorModifier, value);
        return this;
      }
      fontSize(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockFontSizeModifier.identity, TextClockFontSizeModifier, value);
        return this;
      }
      fontStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockFontStyleModifier.identity, TextClockFontStyleModifier, value);
        return this;
      }
      fontWeight(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockFontWeightModifier.identity, TextClockFontWeightModifier, value);
        return this;
      }
      fontFamily(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockFontFamilyModifier.identity, TextClockFontFamilyModifier, value);
        return this;
      }
      textShadow(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockTextShadowModifier.identity, TextClockTextShadowModifier, value);
        return this;
      }
      fontFeature(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockFontFeatureModifier.identity, TextClockFontFeatureModifier, value);
        return this;
      }
      contentModifier(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockContentModifier.identity, TextClockContentModifier, value);
        return this;
      }
      setContentModifier(modifier: any): this {
        if (modifier === undefined || modifier === null) {
          getUINativeModule().textclock.setContentModifierBuilder(this.nativePtr, false);
          return this;
        }
        this.needRebuild = false;
        if (this.builder !== modifier.applyContent()) {
          this.needRebuild = true;
        }
        this.builder = modifier.applyContent();
        this.modifier = modifier;
        getUINativeModule().textclock.setContentModifierBuilder(this.nativePtr, this);
        return this;
      }
      makeContentModifierNode(context: any, textClockConfiguration: any): any {
        textClockConfiguration.contentModifier = this.modifier;
        if (isUndefined(this.textClockNode) || this.needRebuild) {
          const xNode = globalThis.requireNapi('arkui.node');
          this.textClockNode = new xNode.BuilderNode(context);
          this.textClockNode.build(this.builder, textClockConfiguration);
          this.needRebuild = false;
        } else {
          this.textClockNode.update(textClockConfiguration);
        }
        return this.textClockNode.getFrameNode();
      }
      dateTimeOptions(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TextClockDateTimeOptionsModifier.identity, TextClockDateTimeOptionsModifier, value);
        return this;
      }
    }

    class TextClockOnDateChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetTextClockOnDateChange(node);
        } else {
          getUINativeModule().textclock.setTextClockOnDateChange(node, this.value);
        }
      }
    }
    (TextClockOnDateChangeModifier as any).identity = Symbol('textClockOnDateChange');

    class TextClockTimeZoneOffsetModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.setTextClockTimeZoneOffset(node, undefined);
        } else {
          getUINativeModule().textclock.setTextClockTimeZoneOffset(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextClockTimeZoneOffsetModifier as any).identity = Symbol('textClockTimeZoneOffset');

    class TextClockControllerModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.setTextClockController(node, undefined);
        } else {
          getUINativeModule().textclock.setTextClockController(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextClockControllerModifier as any).identity = Symbol('textClockController');

    class TextClockFormatModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetFormat(node);
        }
        else {
          getUINativeModule().textclock.setFormat(node, this.value);
        }
      }
    }
    (TextClockFormatModifier as any).identity = Symbol('textClockFormat');

    class TextClockFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetFontColor(node);
        }
        else {
          getUINativeModule().textclock.setFontColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextClockFontColorModifier as any).identity = Symbol('textClockFontColor');

    class TextClockFontSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetFontSize(node);
        }
        else {
          getUINativeModule().textclock.setFontSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextClockFontSizeModifier as any).identity = Symbol('textClockFontSize');

    class TextClockFontStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetFontStyle(node);
        }
        else {
          getUINativeModule().textclock.setFontStyle(node, this.value);
        }
      }
    }
    (TextClockFontStyleModifier as any).identity = Symbol('textClockFontStyle');

    class TextClockFontWeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetFontWeight(node);
        }
        else {
          getUINativeModule().textclock.setFontWeight(node, this.value);
        }
      }
    }
    (TextClockFontWeightModifier as any).identity = Symbol('textClockFontWeight');

    class TextClockFontFamilyModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetFontFamily(node);
        }
        else {
          getUINativeModule().textclock.setFontFamily(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextClockFontFamilyModifier as any).identity = Symbol('textClockFontFamily');

    class TextClockFontFeatureModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetFontFeature(node);
        }
        else {
          getUINativeModule().textclock.setFontFeature(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextClockFontFeatureModifier as any).identity = Symbol('textClockFontFeature');

    class TextClockContentModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean, component: any): void {
        let textClockComponent = component;
        textClockComponent.setContentModifier(this.value);
      }
    }
    (TextClockContentModifier as any).identity = Symbol('textClockContentModifier');

    class TextClockTextShadowModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetTextShadow(node);
        }
        else {
          let shadow = new ArkShadowInfoToArray();
          if (!shadow.convertShadowOptions(this.value)) {
            getUINativeModule().textclock.resetTextShadow(node);
          }
          else {
            getUINativeModule().textclock.setTextShadow(node, shadow.radius, shadow.type, shadow.color,
              shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
          }
        }
      }
      checkObjectDiff(): boolean {
        let checkDiff = true;
        let arkShadow = new ArkShadowInfoToArray();
        if (Object.getPrototypeOf(this.stageValue).constructor === Object &&
          Object.getPrototypeOf(this.value).constructor === Object) {
          checkDiff = arkShadow.checkDiff(this.stageValue, this.value);
        }
        else if (Object.getPrototypeOf(this.stageValue).constructor === Array &&
          Object.getPrototypeOf(this.value).constructor === Array &&
          this.stageValue.length === this.value.length) {
          let isDiffItem = false;
          for (let i = 0; i < this.value.length; i++) {
            if (arkShadow.checkDiff(this.stageValue[i], this.value[1])) {
              isDiffItem = true;
              break;
            }
          }
          if (!isDiffItem) {
            checkDiff = false;
          }
        }
        return checkDiff;
      }
    }
    (TextClockTextShadowModifier as any).identity = Symbol('textClockTextShadow');

    class TextClockDateTimeOptionsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().textclock.resetDateTimeOptions(node);
        }
        else {
          getUINativeModule().textclock.setDateTimeOptions(node, this.value.hour);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (TextClockDateTimeOptionsModifier as any).identity = Symbol('textClockDateTimeOptions');

    loadComponent.componentObj = {'component' : ArkTextClockComponent };
  }
  return loadComponent.componentObj;
}

class JSTextClock extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().textclock.create(params);
  }
  static format(value: any): void {
    getUINativeModule().textclock.setFormat(true, value);
  }
  static onDateChange(event: any): void {
    getUINativeModule().textclock.setTextClockOnDateChange(true, event);
  }
  static fontColor(value: any): void {
    getUINativeModule().textclock.setFontColor(true, value);
  }
  static fontSize(value: any): void {
    getUINativeModule().textclock.setFontSize(true, value);
  }
  static fontStyle(value: any): void {
    getUINativeModule().textclock.setFontStyle(true, value);
  }
  static fontWeight(value: any): void {
    getUINativeModule().textclock.setFontWeight(true, value);
  }
  static fontFamily(value: any): void {
    getUINativeModule().textclock.setFontFamily(true, value);
  }
  static textShadow(value: any): void {
    let shadow = new ArkShadowInfoToArray();
    if (value !== undefined && value !== null) {
      shadow.convertShadowOptions(value);
    }
    getUINativeModule().textclock.setTextShadow(true, shadow.radius, shadow.type, shadow.color,
      shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
  }
  static fontFeature(value: any): void {
    getUINativeModule().textclock.setFontFeature(true, value);
  }
  static contentModifier(modifier: any): void {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'textclock');
    });
    component.setContentModifier(modifier);
  }
  static dateTimeOptions(dateTimeOptions: any): void {
    getUINativeModule().textclock.setDateTimeOptions(true, dateTimeOptions);
  }

  static onClick(value: any): void {
    __Common__.onClick(value);
  }
  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }
  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }
  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }
  static onDetach(value: any): void {
    __Common__.onAttach(value);
  }
  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.TextClockModifier(nativePtr, classType);
    });
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
  globalThis.ArkTextClockComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.TextClock = JSTextClock;
}

export default { loadComponent, createComponent, exportComponent, exportView };
