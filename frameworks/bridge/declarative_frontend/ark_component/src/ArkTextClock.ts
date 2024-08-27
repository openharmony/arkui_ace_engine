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
  builder: WrappedBuilder<Object[]> | null = null;
  textClockNode: BuilderNode<[TextClockConfiguration]> | null = null;
  modifier: ContentModifier<TextClockConfiguration>;
  needRebuild: Boolean = false;

  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): this {
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
    modifierWithKey(this._modifiersWithKeys, TextClockTextShadowModifier.identity, TextClockTextShadowModifier, value);
    return this;
  }
  fontFeature(value: string): this {
    modifierWithKey(this._modifiersWithKeys, TextClockFontFeatureModifier.identity, TextClockFontFeatureModifier, value);
    return this;
  }
  contentModifier(value: ContentModifier<TextClockConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, TextClockContentModifier.identity, TextClockContentModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<TextClockConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().textClock.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().textClock.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, textClockConfiguration: TextClockConfiguration): FrameNode | null {
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
  dateTimeOptions(value: DateTimeOptions): this {
    modifierWithKey(this._modifiersWithKeys, TextClockDateTimeOptionsModifier.identity,
      TextClockDateTimeOptionsModifier, value);
    return this;
  }
}

class TextClockTimeZoneOffsetModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockTimeZoneOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textClock.setTextClockTimeZoneOffset(node, undefined);
    } else {
      getUINativeModule().textClock.setTextClockTimeZoneOffset(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockControllerModifier extends ModifierWithKey<TextClockController> {
  constructor(value: TextClockController) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockController');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textClock.setTextClockController(node, undefined);
    } else {
      getUINativeModule().textClock.setTextClockController(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockFormatModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFormat');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textClock.resetFormat(node);
    } else {
      getUINativeModule().textClock.setFormat(node, this.value);
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
      getUINativeModule().textClock.resetFontColor(node);
    } else {
      getUINativeModule().textClock.setFontColor(node, this.value);
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
      getUINativeModule().textClock.resetFontSize(node);
    } else {
      getUINativeModule().textClock.setFontSize(node, this.value);
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
      getUINativeModule().textClock.resetFontStyle(node);
    } else {
      getUINativeModule().textClock.setFontStyle(node, this.value!);
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
      getUINativeModule().textClock.resetFontWeight(node);
    } else {
      getUINativeModule().textClock.setFontWeight(node, this.value!);
    }
  }
}

class TextClockTextShadowModifier extends ModifierWithKey<ShadowOptions | Array<ShadowOptions>> {
  constructor(value: ShadowOptions | Array<ShadowOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockTextShadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textClock.resetTextShadow(node);
    } else {
      getUINativeModule().textClock.setTextShadow(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    let checkDiff = true;
    let arkShadow = new ArkShadowInfoToArray();
    if (Object.getPrototypeOf(this.stageValue).constructor === Object &&
      Object.getPrototypeOf(this.value).constructor === Object) {
      checkDiff = arkShadow.checkDiff(<ShadowOptions> this.stageValue, <ShadowOptions> this.value);
    } else if (Object.getPrototypeOf(this.stageValue).constructor === Array &&
      Object.getPrototypeOf(this.value).constructor === Array &&
      (<Array<ShadowOptions>> this.stageValue).length === (<Array<ShadowOptions>> this.value).length) {
      let isDiffItem = false;
      for (let i: number = 0; i < (<Array<ShadowOptions>> this.value).length; i++) {
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

class TextClockFontFeatureModifier extends ModifierWithKey<FontFeature> {
  constructor(value: FontFeature) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFontFeature');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textClock.resetFontFeature(node);
    } else {
      getUINativeModule().textClock.setFontFeature(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockContentModifier extends ModifierWithKey<ContentModifier<TextClockConfiguration>> {
  constructor(value: ContentModifier<TextClockConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent) {
    let textClockComponent = component as ArkTextClockComponent;
    textClockComponent.setContentModifier(this.value);
  }
}

class TextClockFontFamilyModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textClock.resetFontFamily(node);
    } else {
      getUINativeModule().textClock.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextClockDateTimeOptionsModifier extends ModifierWithKey<DateTimeOptions> {
  constructor(value: DateTimeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textClockDateTimeOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textClock.resetDateTimeOptions(node);
    } else {
      getUINativeModule().textClock.setDateTimeOptions(node, this.value.hour);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.TextClock.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTextClockComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TextClockModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.TextClock.contentModifier = function (modifier: ContentModifier<TextClockConfiguration>) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextClockComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};
