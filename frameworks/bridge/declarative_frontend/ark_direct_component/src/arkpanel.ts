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
    class ArkPanelComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      mode(value: any, event?: any): any {
        modifierWithKey(this._modifiersWithKeys, PanelModeModifier.identity, PanelModeModifier, value);
        if (typeof event === 'function') {
          this.onChange((_: any, __: any, mode: any) => {
            event(mode);
          });
        }
        return this;
      }
      type(value: any): any {
        modifierWithKey(this._modifiersWithKeys, PanelTypeModifier.identity, PanelTypeModifier, value);
        return this;
      }
      dragBar(value: any): any {
        modifierWithKey(this._modifiersWithKeys, DragBarModifier.identity, DragBarModifier, value);
        return this;
      }
      customHeight(value: any): any {
        modifierWithKey(this._modifiersWithKeys, PanelCustomHeightModifier.identity, PanelCustomHeightModifier, value);
        return this;
      }
      fullHeight(value: any): any {
        modifierWithKey(this._modifiersWithKeys, PanelFullHeightModifier.identity, PanelFullHeightModifier, value);
        return this;
      }
      halfHeight(value: any): any {
        modifierWithKey(this._modifiersWithKeys, PanelHalfHeightModifier.identity, PanelHalfHeightModifier, value);
        return this;
      }
      miniHeight(value: any): any {
        modifierWithKey(this._modifiersWithKeys, PanelMiniHeightModifier.identity, PanelMiniHeightModifier, value);
        return this;
      }
      show(value: any): any {
        modifierWithKey(this._modifiersWithKeys, ShowModifier.identity, ShowModifier, value);
        return this;
      }
      backgroundMask(color: any): any {
        modifierWithKey(this._modifiersWithKeys, PanelBackgroundMaskModifier.identity, PanelBackgroundMaskModifier, color);
        return this;
      }
      showCloseIcon(value: any): any {
        modifierWithKey(this._modifiersWithKeys, ShowCloseIconModifier.identity, ShowCloseIconModifier, value);
        return this;
      }
      onChange(event: any): any {
        getUINativeModule().panel.setOnSizeChange(this.nativePtr, event);
        return this;
      }
      onHeightChange(callback: any): any {
        getUINativeModule().panel.setOnHeightChange(this.nativePtr, callback);
        return this;
      }
    }

    class PanelBackgroundMaskModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('panelBackgroundMask');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetPanelBackgroundMask(node);
        } else {
          getUINativeModule().panel.setPanelBackgroundMask(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class PanelModeModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('panelMode');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetPanelMode(node);
        } else {
          getUINativeModule().panel.setPanelMode(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class PanelTypeModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('panelType');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetPanelType(node);
        } else {
          getUINativeModule().panel.setPanelType(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class PanelCustomHeightModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('panelCustomHeight');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetPanelCustomHeight(node);
        } else {
          getUINativeModule().panel.setPanelCustomHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class PanelFullHeightModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('panelFullHeight');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetPanelFullHeight(node);
        } else {
          getUINativeModule().panel.setPanelFullHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class PanelHalfHeightModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('panelHalfHeight');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetPanelHalfHeight(node);
        } else {
          getUINativeModule().panel.setPanelHalfHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class PanelMiniHeightModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('panelMiniHeight');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetPanelMiniHeight(node);
        } else {
          getUINativeModule().panel.setPanelMiniHeight(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class ShowCloseIconModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('showCloseIcon');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetShowCloseIcon(node);
        } else {
          getUINativeModule().panel.setShowCloseIcon(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class DragBarModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('dragBar');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetDragBar(node);
        } else {
          getUINativeModule().panel.setDragBar(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    class ShowModifier extends ModifierWithKey<any> {
      static identity: Symbol = Symbol('show');
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().panel.resetShow(node);
        } else {
          getUINativeModule().panel.setShow(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }

    loadComponent.componentObj = { component: ArkPanelComponent };
  }
  return loadComponent.componentObj;
}

class JSPanel extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().panel.create(params);
  }

  static pop(): void {
    getUINativeModule().panel.pop();
  }

  static mode(value: any, event?: any): void {
    getUINativeModule().panel.setPanelMode(true, value, event);
  }

  static type(value: any): void {
    getUINativeModule().panel.setPanelType(true, value);
  }

  static dragBar(value: any): void {
    getUINativeModule().panel.setDragBar(true, value);
  }

  static customHeight(value: any): void {
    getUINativeModule().panel.setPanelCustomHeight(true, value);
  }

  static fullHeight(value: any): void {
    getUINativeModule().panel.setPanelFullHeight(true, value);
  }

  static halfHeight(value: any): void {
    getUINativeModule().panel.setPanelHalfHeight(true, value);
  }

  static miniHeight(value: any): void {
    getUINativeModule().panel.setPanelMiniHeight(true, value);
  }

  static show(value: any): void {
    getUINativeModule().panel.setShow(true, value);
  }

  static backgroundMask(value: any): void {
    getUINativeModule().panel.setPanelBackgroundMask(true, value);
  }

  static showCloseIcon(value: any): void {
    getUINativeModule().panel.setShowCloseIcon(true, value);
  }

  static backgroundColor(value: any): void {
    getUINativeModule().panel.setJsBackgroundColor(true, value);
  }

  static border(value: any): void {
    getUINativeModule().panel.setJsPanelBorder(true, value);
  }

  static borderWidth(value: any): void {
    getUINativeModule().panel.setJsPanelBorderWidth(true, value);
  }

  static borderColor(value: any): void {
    getUINativeModule().panel.setJsPanelBorderColor(true, value);
  }

  static borderStyle(value: any): void {
    getUINativeModule().panel.setJsPanelBorderStyle(true, value);
  }

  static borderRadius(value: any): void {
    getUINativeModule().panel.setJsPanelBorderRadius(true, value);
  }

  static onChange(event: any): void {
    getUINativeModule().panel.setOnSizeChange(true, event);
  }

  static onHeightChange(callback: any): void {
    getUINativeModule().panel.setOnHeightChange(true, callback);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.PanelModifier(nativePtr, classType);
    });
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
  static onHover(value: any): void {
    __Common__.onHover(value);
  }
}

function createComponent(nativePtr: any, classType?: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkPanelComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Panel = JSPanel;
}

export default { loadComponent, createComponent, exportComponent, exportView };
