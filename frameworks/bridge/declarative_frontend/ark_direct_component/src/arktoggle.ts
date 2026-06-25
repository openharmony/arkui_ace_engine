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
    class ArkToggleComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      allowChildCount(): number {
        if (this.toggleType === ToggleType.Button) {
          return 1;
        }
        return 0;
      }
      initialize(value: any): this {
        if (!value.length) {
          return this;
        }
        if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
          this.toggleType = value[0].type;
          modifierWithKey(this._modifiersWithKeys, ToggleOptionsModifier.identity, ToggleOptionsModifier, value[0]);
        } else {
          modifierWithKey(this._modifiersWithKeys, ToggleOptionsModifier.identity, ToggleOptionsModifier, undefined);
        }
        return this;
      }
      onChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleOnChangeModifier.identity, ToggleOnChangeModifier, callback);
        return this;
      }
      selectedColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleSelectedColorModifier.identity, ToggleSelectedColorModifier, value);
        return this;
      }
      switchPointColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleSwitchPointColorModifier.identity, ToggleSwitchPointColorModifier, value);
        return this;
      }
      height(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleHeightModifier.identity, ToggleHeightModifier, value);
        return this;
      }
      responseRegion(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleResponseRegionModifier.identity, ToggleResponseRegionModifier, value);
        return this;
      }
      padding(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TogglePaddingModifier.identity, TogglePaddingModifier, value);
        return this;
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleBackgroundColorModifier.identity, ToggleBackgroundColorModifier, value);
        return this;
      }
      hoverEffect(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleHoverEffectModifier.identity, ToggleHoverEffectModifier, value);
        return this;
      }
      switchStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleSwitchStyleModifier.identity, ToggleSwitchStyleModifier, value);
        return this;
      }
      margin(value: any): this {
        let arkValue = new ArkPadding();
        if (value !== null && value !== undefined) {
          if (isLengthType(value) || isResource(value)) {
            arkValue.top = value;
            arkValue.right = value;
            arkValue.bottom = value;
            arkValue.left = value;
          }
          else {
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
          modifierWithKey(this._modifiersWithKeys, ToggleMarginModifier.identity, ToggleMarginModifier, arkValue);
        }
        else {
          modifierWithKey(this._modifiersWithKeys, ToggleMarginModifier.identity, ToggleMarginModifier, undefined);
        }
        return this;
      }
      contentModifier(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ToggleContentModifier.identity, ToggleContentModifier, value);
        return this;
      }
      setContentModifier(modifier: any): void {
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
      makeContentModifierNode(context: any, toggleConfiguration: any): any {
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
    class ToggleOnChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetOnChange(node);
        }
        else {
          getUINativeModule().toggle.setOnChange(node, this.value);
        }
      }
    }
    (ToggleOnChangeModifier as any).identity = Symbol('toggleOnChange');
    class ToggleSelectedColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetSelectedColor(node);
        }
        else {
          getUINativeModule().toggle.setSelectedColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ToggleSelectedColorModifier as any).identity = Symbol('toggleSelectedColor');
    class ToggleSwitchPointColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetSwitchPointColor(node);
        }
        else {
          getUINativeModule().toggle.setSwitchPointColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ToggleSwitchPointColorModifier as any).identity = Symbol('toggleSwitchPointColor');
    class ToggleHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetHeight(node);
        }
        else {
          getUINativeModule().toggle.setHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ToggleHeightModifier as any).identity = Symbol('toggleHeight');
    class ToggleResponseRegionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        let _a: any, _b: any, _c: any, _d: any, _e: any, _f: any, _g: any, _h: any;
        if (reset) {
          getUINativeModule().toggle.resetResponseRegion(node);
        }
        else {
          let responseRegion: any[] = [];
          if (Array.isArray(this.value)) {
            for (let i = 0; i < this.value.length; i++) {
              responseRegion.push((_a = this.value[i].x) !== null && _a !== void 0 ? _a : 'PLACEHOLDER');
              responseRegion.push((_b = this.value[i].y) !== null && _b !== void 0 ? _b : 'PLACEHOLDER');
              responseRegion.push((_c = this.value[i].width) !== null && _c !== void 0 ? _c : 'PLACEHOLDER');
              responseRegion.push((_d = this.value[i].height) !== null && _d !== void 0 ? _d : 'PLACEHOLDER');
            }
          }
          else {
            responseRegion.push((_e = this.value.x) !== null && _e !== void 0 ? _e : 'PLACEHOLDER');
            responseRegion.push((_f = this.value.y) !== null && _f !== void 0 ? _f : 'PLACEHOLDER');
            responseRegion.push((_g = this.value.width) !== null && _g !== void 0 ? _g : 'PLACEHOLDER');
            responseRegion.push((_h = this.value.height) !== null && _h !== void 0 ? _h : 'PLACEHOLDER');
          }
          getUINativeModule().toggle.setResponseRegion(node, responseRegion, responseRegion.length);
        }
      }
      checkObjectDiff(): boolean {
        if (Array.isArray(this.stageValue) && Array.isArray(this.value)) {
          if (this.value.length !== this.stageValue.length) {
            return true;
          }
          else {
            for (let i = 0; i < this.value.length; i++) {
              if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
                isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
                isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
                isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height))) {
                return true;
              }
            }
            return false;
          }
        }
        else if (typeof this.stageValue === 'object' && typeof this.value === 'object') {
          return !(this.stageValue.x === this.value.x &&
            this.stageValue.y === this.value.y &&
            this.stageValue.height === this.value.height &&
            this.stageValue.width === this.value.width);
        }
        else {
          return true;
        }
      }
    }
    (ToggleResponseRegionModifier as any).identity = Symbol('toggleResponseRegion');
    class TogglePaddingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetPadding(node);
        }
        else {
          let top: any = undefined;
          let right: any = undefined;
          let bottom: any = undefined;
          let left: any = undefined;
          if (isLengthType(this.value) || isResource(this.value)) {
            top = this.value;
            right = this.value;
            bottom = this.value;
            left = this.value;
          }
          else if (typeof this.value === 'object') {
            top = this.value.top;
            right = this.value.right;
            bottom = this.value.bottom;
            left = this.value.left;
          }
          getUINativeModule().toggle.setPadding(node, top, right, bottom, left);
        }
      }
      checkObjectDiff(): boolean {
        if (!isResource(this.stageValue) && !isResource(this.value)) {
          if (typeof this.stageValue === 'object' && typeof this.value === 'object') {
            return !(this.stageValue.left === this.value.left &&
              this.stageValue.right === this.value.right &&
              this.stageValue.top === this.value.top &&
              this.stageValue.bottom === this.value.bottom);
          }
          else {
            return !(this.stageValue === this.value);
          }
        }
        return true;
      }
    }
    (TogglePaddingModifier as any).identity = Symbol('togglePadding');
    class ToggleBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetBackgroundColor(node);
        }
        else {
          getUINativeModule().toggle.setBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ToggleBackgroundColorModifier as any).identity = Symbol('toggleBackgroundColor');
    class ToggleHoverEffectModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetHoverEffect(node);
        }
        else {
          getUINativeModule().toggle.setHoverEffect(node, this.value);
        }
      }
    }
    (ToggleHoverEffectModifier as any).identity = Symbol('toggleHoverEffect');
    class ToggleSwitchStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetSwitchStyle(node);
        }
        else {
          getUINativeModule().toggle.setSwitchStyle(node, this.value.pointRadius, this.value.unselectedColor, this.value.pointColor, this.value.trackBorderRadius);
        }
      }
      checkObjectDiff(): boolean {
        if (isUndefined(this.stageValue.pointRadius) || isUndefined(this.stageValue.unselectedColor) ||
          isUndefined(this.stageValue.pointColor) || isUndefined(this.stageValue.trackBorderRadius)) {
          return true;
        }
        if (!isResource(this.stageValue) && !isResource(this.value)) {
          return !isBaseOrResourceEqual(this.stageValue.pointRadius, this.value.pointRadius) ||
            !isBaseOrResourceEqual(this.stageValue.unselectedColor, this.value.unselectedColor) ||
            !isBaseOrResourceEqual(this.stageValue.pointColor, this.value.pointColor) ||
            !isBaseOrResourceEqual(this.stageValue.trackBorderRadius, this.value.trackBorderRadius);
        }
        else {
          return true;
        }
      }
    }
    (ToggleSwitchStyleModifier as any).identity = Symbol('toggleSwitchStyle');
    class ToggleMarginModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().toggle.resetMargin(node);
        }
        else {
          getUINativeModule().toggle.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
          !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
          !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
          !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
      }
    }
    (ToggleMarginModifier as any).identity = Symbol('toggleMargin');
    class ToggleContentModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean, component: any): void {
        let toggleComponent = component;
        toggleComponent.setNodePtr(node);
        toggleComponent.setContentModifier(this.value);
      }
    }
    (ToggleContentModifier as any).identity = Symbol('toggleContentModifier');
    class ToggleOptionsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
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
    (ToggleOptionsModifier as any).identity = Symbol('toggleOptions');
    loadComponent.componentObj = { 'component': ArkToggleComponent };
  }
  return loadComponent.componentObj;
}
class JSToggle extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().toggle.create(params);
  }
  static onChange(callback: any): void {
    getUINativeModule().toggle.setOnChange(true, callback);
  }
  static selectedColor(value: any): void {
    getUINativeModule().toggle.setSelectedColor(true, value);
  }
  static switchPointColor(value: any): void {
    getUINativeModule().toggle.setSwitchPointColor(true, value);
  }
  static height(value: any): void {
    if (Utils.isApiVersionEQAbove(12)) {
      JSViewAbstract.height(value);
    } else {
      getUINativeModule().toggle.setHeight(true, value);
    }
  }
  static width(value: any): void {
    if (Utils.isApiVersionEQAbove(12)) {
      JSViewAbstract.width(value);
    } else {
      getUINativeModule().toggle.setWidth(true, value);
    }
  }
  static size(value: any): void {
    if (Utils.isApiVersionEQAbove(12)) {
      JSViewAbstract.size(value);
    } else {
      getUINativeModule().toggle.setSize(true, value);
    }
  }
  static responseRegion(value: any): void {
    getUINativeModule().toggle.setResponseRegion(true, value);
  }
  static padding(value: any): void {
    getUINativeModule().toggle.setPadding(true, value);
  }
  static backgroundColor(value: any): void {
    if (ViewStackProcessor.UsesNewPipeline()) {
      getUINativeModule().toggle.setBackgroundColor(true, value);
    } else {
      JSViewAbstract.backgroundColor(value);
    }
  }
  static hoverEffect(value: any): void {
    getUINativeModule().toggle.setHoverEffect(true, value);
  }
  static switchStyle(value: any): void {
    getUINativeModule().toggle.setSwitchStyle(true, value);
  }
  static margin(value: any): void {
    getUINativeModule().toggle.setMargin(true, value);
    JSViewAbstract.margin(value);
  }
  static pop(): void {
    getUINativeModule().toggle.pop();
  }
  static borderRadius(value: any): void {
    getUINativeModule().toggle.setBorderRadius(value);
  }
  static border(value: any): void {
    JSViewAbstract.border(value);
    getUINativeModule().toggle.setBorder(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.ToggleModifier(nativePtr, classType);
    });
  }
  static contentModifier(modifier: any): void {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'toggle');
    });
    if (component !== undefined && component !== null) {
      component.setNodePtr(nativeNode);
      component.setContentModifier(modifier);
    }
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
  globalThis.ArkToggleComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Toggle = JSToggle;
}

export default { loadComponent, createComponent, exportComponent, exportView };
