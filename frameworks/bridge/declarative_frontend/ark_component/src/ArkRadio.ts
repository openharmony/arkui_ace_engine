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

class ArkRadioComponent extends ArkComponent implements RadioAttribute {
  builder: WrappedBuilder<Object[]> | null = null;
  radioNode: BuilderNode<[RadioConfiguration]> | null = null;
  modifier: ContentModifier<RadioConfiguration>;
  needRebuild: boolean = false;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): this {
    if (!value.length) {
      return this;
    }
    if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, RadioOptionsModifier.identity, RadioOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, RadioOptionsModifier.identity, RadioOptionsModifier, undefined);
    }
    return this;
  }
  checked(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, RadioCheckedModifier.identity, RadioCheckedModifier, value);
    return this;
  }
  onChange(callback: (isChecked: boolean) => void): this {
    modifierWithKey(this._modifiersWithKeys, RadioOnChangeModifier.identity, RadioOnChangeModifier, callback);
    return this;
  }
  radioStyle(value: RadioStyle): this {
    modifierWithKey(this._modifiersWithKeys, RadioStyleModifier.identity, RadioStyleModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, RadioWidthModifier.identity, RadioWidthModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, RadioHeightModifier.identity, RadioHeightModifier, value);
    return this;
  }
  size(value: { width: Length; height: Length }): this {
    modifierWithKey(this._modifiersWithKeys, RadioSizeModifier.identity, RadioSizeModifier, value);
    return this;
  }
  hoverEffect(value: HoverEffect): this {
    modifierWithKey(this._modifiersWithKeys, RadioHoverEffectModifier.identity, RadioHoverEffectModifier, value);
    return this;
  }
  padding(value: Padding | Length): this {
    modifierWithKey(this._modifiersWithKeys, RadioPaddingModifier.identity, RadioPaddingModifier, value);
    return this;
  }
  responseRegion(value: Array<Rectangle> | Rectangle): this {
    modifierWithKey(this._modifiersWithKeys, RadioResponseRegionModifier.identity,
      RadioResponseRegionModifier, value);
    return this;
  }
  margin(value: Margin | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = value.top;
        arkValue.bottom = value.bottom;
        if (Object.keys(value).indexOf('right') >= 0) {
          arkValue.right = value.right;
        }
        if (Object.keys(value).indexOf('end') >= 0) {
          arkValue.right = value.end;
        }
        if (Object.keys(value).indexOf('left') >= 0) {
          arkValue.left = value.left;
        }
        if (Object.keys(value).indexOf('start') >= 0) {
          arkValue.left = value.start;
        }
      }
      modifierWithKey(this._modifiersWithKeys, RadioMarginModifier.identity, RadioMarginModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, RadioMarginModifier.identity, RadioMarginModifier, undefined);
    }
    return this;
  }
  contentModifier(value: ContentModifier<RadioConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, RadioContentModifier.identity, RadioContentModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<RadioConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().radio.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().radio.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, radioConfiguration: RadioConfiguration): FrameNode | null {
    radioConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.radioNode) || this.needRebuild) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.radioNode = new xNode.BuilderNode(context);
      this.radioNode.build(this.builder, radioConfiguration);
      this.needRebuild = false;
    } else {
      this.radioNode.update(radioConfiguration);
    }
    return this.radioNode.getFrameNode();
  }
}

class RadioOptionsModifier extends ModifierWithKey<RadioOptions> {
  constructor(value: RadioOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('radioOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.setRadioOptions(node, undefined, undefined, undefined);
    } else {
      getUINativeModule().radio.setRadioOptions(node, this.value.value, this.value.group, this.value.indicatorType);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.group, this.value.group) ||
      !isBaseOrResourceEqual(this.stageValue.indicatorType, this.value.indicatorType);
  }
}

class RadioCheckedModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('radioChecked');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioChecked(node);
    } else {
      getUINativeModule().radio.setRadioChecked(node, this.value!);
    }
  }
}

class RadioStyleModifier extends ModifierWithKey<RadioStyle> {
  constructor(value: RadioStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('radioStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioStyle(node);
    } else {
      getUINativeModule().radio.setRadioStyle(
        node, this.value.checkedBackgroundColor, this.value.uncheckedBorderColor, this.value.indicatorColor);
    }
  }

  checkObjectDiff(): boolean {
    let checkedBackgroundColorEQ =
      isBaseOrResourceEqual(this.stageValue.checkedBackgroundColor,
        this.value.checkedBackgroundColor);
    let uncheckedBorderColorEQ =
      isBaseOrResourceEqual(this.stageValue.uncheckedBorderColor,
        this.value.uncheckedBorderColor);
    let indicatorColorEQ =
      isBaseOrResourceEqual(this.stageValue.indicatorColor,
        this.value.indicatorColor);
    return !checkedBackgroundColorEQ ||
      !uncheckedBorderColorEQ ||
      !indicatorColorEQ;
  }
}

class RadioWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('radioWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioWidth(node);
    } else {
      getUINativeModule().radio.setRadioWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class RadioHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('radioHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioHeight(node);
    } else {
      getUINativeModule().radio.setRadioHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class RadioSizeModifier extends ModifierWithKey<{ width: Length; height: Length }> {
  constructor(value: { width: Length; height: Length }) {
    super(value);
  }
  static identity: Symbol = Symbol('radioSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioSize(node);
    } else {
      getUINativeModule().radio.setRadioSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}

class RadioHoverEffectModifier extends ModifierWithKey<HoverEffect> {
  constructor(value: HoverEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('radioHoverEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioHoverEffect(node);
    } else {
      getUINativeModule().radio.setRadioHoverEffect(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class RadioPaddingModifier extends ModifierWithKey<Padding | Length> {
  constructor(value: Padding | Length) {
    super(value);
  }
  static identity: Symbol = Symbol('radioPadding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioPadding(node);
    } else {
      let paddingTop: Length;
      let paddingRight: Length;
      let paddingBottom: Length;
      let paddingLeft: Length;
      if (this.value !== null && this.value !== undefined) {
        if (isLengthType(this.value) || isResource(this.value)) {
          paddingTop = <Length> this.value;
          paddingRight = <Length> this.value;
          paddingBottom = <Length> this.value;
          paddingLeft = <Length> this.value;
        } else {
          paddingTop = (<Padding> this.value).top;
          paddingRight = (<Padding> this.value).right;
          paddingBottom = (<Padding> this.value).bottom;
          paddingLeft = (<Padding> this.value).left;
        }
      }
      getUINativeModule().radio.setRadioPadding(node, paddingTop, paddingRight, paddingBottom, paddingLeft);
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as Padding).left === (this.value as Padding).left &&
        (this.stageValue as Padding).right === (this.value as Padding).right &&
        (this.stageValue as Padding).top === (this.value as Padding).top &&
        (this.stageValue as Padding).bottom === (this.value as Padding).bottom);
    } else {
      return true;
    }
  }
}

class RadioResponseRegionModifier extends ModifierWithKey<Array<Rectangle> | Rectangle> {
  constructor(value: Array<Rectangle> | Rectangle) {
    super(value);
  }
  static identity = Symbol('radioResponseRegion');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioResponseRegion(node);
    } else {
      let responseRegion: (number | string | Resource)[] = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push(this.value[i].x ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].y ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].width ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].height ?? 'PLACEHOLDER');
        }
      } else {
        responseRegion.push(this.value.x ?? 'PLACEHOLDER');
        responseRegion.push(this.value.y ?? 'PLACEHOLDER');
        responseRegion.push(this.value.width ?? 'PLACEHOLDER');
        responseRegion.push(this.value.height ?? 'PLACEHOLDER');
      }
      getUINativeModule().radio.setRadioResponseRegion(node, responseRegion, responseRegion.length);
    }
  }

  checkObjectDiff(): boolean {
    if (Array.isArray(this.value) && Array.isArray(this.stageValue)) {
      if (this.value.length !== this.stageValue.length) {
        return true;
      } else {
        for (let i = 0; i < this.value.length; i++) {
          if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
            isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
            isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
            isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height)
          )) {
            return true;
          }
        }
        return false;
      }
    } else if (!Array.isArray(this.value) && !Array.isArray(this.stageValue)) {
      return (!(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height)
      ));
    } else {
      return true;
    }
  }
}

class RadioContentModifier extends ModifierWithKey<ContentModifier<RadioConfiguration>> {
  constructor(value: ContentModifier<RadioConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('radioContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent): void {
    let radioComponent = component as ArkRadioComponent;
    radioComponent.setContentModifier(this.value); 
  }
}
class RadioOnChangeModifier extends ModifierWithKey<(isChecked: boolean) => void>{
  constructor(value:(isChecked: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('radioOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioOnChange(node);
    } else {
      getUINativeModule().radio.setRadioOnChange(node, this.value);
    }
  }
}

class RadioMarginModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('radioMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetMargin(node);
    } else {
      getUINativeModule().radio.setMargin(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

// @ts-ignore
globalThis.Radio.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRadioComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RadioModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.Radio.contentModifier = function (modifier): void {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRadioComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};
