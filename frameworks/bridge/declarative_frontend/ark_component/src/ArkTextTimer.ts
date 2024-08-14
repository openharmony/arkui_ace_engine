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
  builder: WrappedBuilder<Object[]> | null = null;
  textTimerNode: BuilderNode<[TextTimerConfiguration]> | null = null;
  modifier: ContentModifier<TextTimerConfiguration>;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): this {
    if (value.length === 1 && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, TextTimerOptionsModifier.identity, TextTimerOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, TextTimerOptionsModifier.identity, TextTimerOptionsModifier, undefined);
    }
    return this;
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

  textShadow(value: ShadowOptions): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerTextShadowModifier.identity, TextTimerTextShadowModifier, value);
    return this;
  }

  contentModifier(value: ContentModifier<TextTimerConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, TextTimerContentModifier.identity, TextTimerContentModifier, value);
    return this;
  }

  setContentModifier(modifier: ContentModifier<TextTimerConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().textTimer.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().textTimer.setContentModifierBuilder(this.nativePtr, this);
  }

  makeContentModifierNode(context: UIContext, textTimerConfiguration: TextTimerConfiguration): FrameNode | null {
    textTimerConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.textTimerNode)) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.textTimerNode = new xNode.BuilderNode(context);
      this.textTimerNode.build(this.builder, textTimerConfiguration);
    } else {
      this.textTimerNode.update(textTimerConfiguration);
    }
    return this.textTimerNode.getFrameNode();
  }


  onTimer(event: (utc: number, elapsedTime: number) => void): this {
    throw new Error('Method not implemented.');
  }
}

class TextTimerOptionsModifier extends ModifierWithKey<TextTimerOptions> {
  constructor(value: TextTimerOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textTimerOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textTimer.setTextTimerOptions(node, undefined, undefined, undefined);
    } else {
      getUINativeModule().textTimer.setTextTimerOptions(node, this.value?.isCountDown, this.value?.count, this.value?.controller);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.isCountDown, this.value?.isCountDown) ||
          !isBaseOrResourceEqual(this.stageValue?.count, this.value?.count) ||
          !isBaseOrResourceEqual(this.stageValue?.controller, this.value?.controller);
  }
}

class TextTimerFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textTimer.resetFontColor(node);
    } else {
      getUINativeModule().textTimer.setFontColor(node, this.value);
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
      getUINativeModule().textTimer.resetFontSize(node);
    } else {
      getUINativeModule().textTimer.setFontSize(node, this.value);
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
      getUINativeModule().textTimer.resetFontWeight(node);
    } else {
      getUINativeModule().textTimer.setFontWeight(node, this.value);
    }
  }
}

class TextTimerFontStyleModifier extends ModifierWithKey<FontStyle> {
  static identity: Symbol = Symbol('fontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textTimer.resetFontStyle(node);
    } else {
      getUINativeModule().textTimer.setFontStyle(node, this.value);
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
      getUINativeModule().textTimer.resetFontFamily(node);
    } else {
      getUINativeModule().textTimer.setFontFamily(node, this.value);
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
      getUINativeModule().textTimer.resetFormat(node);
    } else {
      getUINativeModule().textTimer.setFormat(node, this.value);
    }
  }
}

class TextTimerContentModifier extends ModifierWithKey<ContentModifier<TextTimerConfiguration>> {
  constructor(value: ContentModifier<TextTimerConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('textTimerContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent) {
    let textTimerComponent = component as ArkTextTimerComponent;
    textTimerComponent.setContentModifier(this.value);
  }
}

class TextTimerTextShadowModifier extends ModifierWithKey<ShadowOptions | Array<ShadowOptions>> {
  constructor(value: ShadowOptions | Array<ShadowOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('textTimerTextShadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textTimer.resetTextShadow(node);
    } else {
      getUINativeModule().textTimer.setTextShadow(node, this.value!);
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

// @ts-ignore
globalThis.TextTimer.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTextTimerComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TextTimerModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.TextTimer.contentModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextTimerComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};