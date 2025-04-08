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
class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
  builder: WrappedBuilder<Object[]> | null = null;
  toggleNode: BuilderNode<[ToggleConfiguration]> | null = null;
  modifier: ContentModifier<ToggleConfiguration>;
  needRebuild: boolean = false;
  toggleType: ToggleType = ToggleType.Switch;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    if (this.toggleType === ToggleType.Button) {
      return 1;
    }
    return 0;
  }
  initialize(value: Object[]): this {
    if (!value.length) {
      return this;
    }
    if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
      this.toggleType = (value[0] as ToggleOptions).type;
      modifierWithKey(this._modifiersWithKeys, ToggleOptionsModifier.identity, ToggleOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, ToggleOptionsModifier.identity, ToggleOptionsModifier, undefined);
    }
    return this;
  }
  onChange(callback: (isOn: boolean) => void): this {
    modifierWithKey(this._modifiersWithKeys, ToggleOnChangeModifier.identity, ToggleOnChangeModifier, callback);
    return this;
  }
  selectedColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ToggleSelectedColorModifier.identity, ToggleSelectedColorModifier, value);
    return this;
  }
  switchPointColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ToggleSwitchPointColorModifier.identity, ToggleSwitchPointColorModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, ToggleHeightModifier.identity, ToggleHeightModifier, value);
    return this;
  }
  responseRegion(value: Rectangle | Rectangle[]): this {
    modifierWithKey(this._modifiersWithKeys, ToggleResponseRegionModifier.identity, ToggleResponseRegionModifier, value);
    return this;
  }
  padding(value: Padding | Length): this {
    modifierWithKey(this._modifiersWithKeys, TogglePaddingModifier.identity, TogglePaddingModifier, value);
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ToggleBackgroundColorModifier.identity, ToggleBackgroundColorModifier, value);
    return this;
  }
  hoverEffect(value: HoverEffect): this {
    modifierWithKey(this._modifiersWithKeys, ToggleHoverEffectModifier.identity, ToggleHoverEffectModifier, value);
    return this;
  }
  switchStyle(value: SwitchStyle): this {
    modifierWithKey(this._modifiersWithKeys, ToggleSwitchStyleModifier.identity, ToggleSwitchStyleModifier, value);
    return this;
  }
  contentModifier(value: ContentModifier<ToggleConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, ToggleContentModifier.identity, ToggleContentModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<ToggleConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().toggle.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().toggle.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, toggleConfiguration: ToggleConfiguration): FrameNode | null {
    toggleConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.toggleNode) || this.needRebuild) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.toggleNode = new xNode.BuilderNode(context);
      this.toggleNode.build(this.builder, toggleConfiguration);
      this.needRebuild = false;
    } else {
      this.toggleNode.update(toggleConfiguration);
    }
    return this.toggleNode.getFrameNode();
  }
}

class ToggleOnChangeModifier extends ModifierWithKey<(isOn:boolean) => void> {
  constructor(value: (isOn:boolean) => void) {
    super(value);
  }
  static identity = Symbol('toggleOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetOnChange(node);
    } else {
      getUINativeModule().toggle.setOnChange(node, this.value);
    }
  }
}

class ToggleSelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity = Symbol('toggleSelectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetSelectedColor(node);
    } else {
      getUINativeModule().toggle.setSelectedColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ToggleSwitchPointColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity = Symbol('toggleSwitchPointColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetSwitchPointColor(node);
    } else {
      getUINativeModule().toggle.setSwitchPointColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ToggleHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity = Symbol('toggleHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetHeight(node);
    } else {
      getUINativeModule().toggle.setHeight(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ToggleResponseRegionModifier extends ModifierWithKey<Rectangle | Array<Rectangle>> {
  constructor(value: Rectangle | Array<Rectangle>) {
    super(value);
  }
  static identity = Symbol('toggleResponseRegion');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetResponseRegion(node);
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
      getUINativeModule().toggle.setResponseRegion(node, responseRegion, responseRegion.length);
    }
  }
  checkObjectDiff(): boolean {
    if (Array.isArray(this.stageValue) && Array.isArray(this.value)) {
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
    } else if (typeof this.stageValue === 'object' && typeof this.value === 'object') {
      return !((this.stageValue as Rectangle).x === (this.value as Rectangle).x &&
        (this.stageValue as Rectangle).y === (this.value as Rectangle).y &&
        (this.stageValue as Rectangle).height === (this.value as Rectangle).height &&
        (this.stageValue as Rectangle).width === (this.value as Rectangle).width);
    } else {
      return true;
    }
  }
}
class TogglePaddingModifier extends ModifierWithKey<Padding | Length> {
  constructor(value: Padding | Length) {
    super(value);
  }
  static identity = Symbol('togglePadding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetPadding(node);
    } else {
      let top = undefined;
      let right = undefined;
      let bottom = undefined;
      let left = undefined;
      if (isLengthType(this.value) || isResource(this.value)) {
        top = this.value;
        right = this.value;
        bottom = this.value;
        left = this.value;
      } else if (typeof this.value === 'object') {
        top = (this.value as Padding).top;
        right = (this.value as Padding).right;
        bottom = (this.value as Padding).bottom;
        left = (this.value as Padding).left;
      }
      getUINativeModule().toggle.setPadding(node, top, right, bottom, left);
    }
  }
  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      if (typeof this.stageValue === 'object' && typeof this.value === 'object') {
        return !((this.stageValue as Padding).left === (this.value as Padding).left &&
        (this.stageValue as Padding).right === (this.value as Padding).right &&
        (this.stageValue as Padding).top === (this.value as Padding).top &&
        (this.stageValue as Padding).bottom === (this.value as Padding).bottom);
      } else {
        return !(this.stageValue === this.value);
      }
    }
    return true;
  }
}
class ToggleBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity = Symbol('toggleBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetBackgroundColor(node);
    } else {
      getUINativeModule().toggle.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ToggleHoverEffectModifier extends ModifierWithKey<HoverEffect> {
  constructor(value: HoverEffect) {
    super(value);
  }
  static identity = Symbol('toggleHoverEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetHoverEffect(node);
    } else {
      getUINativeModule().toggle.setHoverEffect(node, this.value);
    }
  }
}

class ToggleSwitchStyleModifier extends ModifierWithKey<SwitchStyle> {
  constructor(value: SwitchStyle) {
    super(value);
  }
  static identity = Symbol('toggleSwitchStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.resetSwitchStyle(node);
    } else {
      getUINativeModule().toggle.setSwitchStyle(node, this.value.pointRadius, this.value.unselectedColor,
        this.value.pointColor, this.value.trackBorderRadius);
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.pointRadius === this.value.pointRadius &&
        this.stageValue.unselectedColor === this.value.unselectedColor &&
        this.stageValue.pointColor === this.value.pointColor &&
        this.stageValue.trackBorderRadius === this.value.trackBorderRadius);
    } else {
      return true;
    }
  }
}

class ToggleContentModifier extends ModifierWithKey<ContentModifier<ToggleConfiguration>> {
  constructor(value: ContentModifier<ToggleConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('toggleContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent) {
    let toggleComponent = component as ArkToggleComponent;
    toggleComponent.setNodePtr(node);
    toggleComponent.setContentModifier(this.value);
  }
}
class ToggleOptionsModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('toggleOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().toggle.setToggleOptions(node, undefined);
    } else {
      getUINativeModule().toggle.setToggleOptions(node, this.value?.isOn);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.isOn, this.value.isOn);
  }
}
// @ts-ignore
globalThis.Toggle.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkToggleComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ToggleModifier(nativePtr, classType);
  });
};
// @ts-ignore
globalThis.Toggle.contentModifier = function (modifier): void {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkToggleComponent(nativeNode);
  });
  component.setNodePtr(nativeNode);
  component.setContentModifier(modifier);
};