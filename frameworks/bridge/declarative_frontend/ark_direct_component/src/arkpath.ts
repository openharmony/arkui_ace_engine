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

getUINativeModule().loadNativeModule('CommonShape');
let commonModule = globalThis.requireNapi('arkui.components.arkcommonshape');
commonModule.exportView();
commonModule.loadComponent();
commonModule.exportComponent();

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkPathComponent extends ArkCommonShapeComponent {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
        this._needDiff = false;
      }
      allowChildCount() {
        return 0;
      }
      resetPathOptions() {
        modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
          CommonShapeWidthModifier, undefined);
        modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
          CommonShapeHeightModifier, undefined);
        modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity,
          CommandsModifier, undefined);
      }
      initialize(value: any) {
        if (value[0] === undefined || value[0] === null) {
          this.resetPathOptions();
          return this;
        }
        if (value[0].width !== undefined && value[0].width !== null) {
          modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
            CommonShapeWidthModifier, value[0].width);
        } else {
          modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
            CommonShapeWidthModifier, undefined);
        }
        if (value[0].height !== undefined && value[0].height !== null) {
          modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
            CommonShapeHeightModifier, value[0].height);
        } else {
          modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
            CommonShapeHeightModifier, undefined);
        }
        if (value[0].commands !== undefined && value[0].commands !== null) {
          modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity,
            CommandsModifier, value[0].commands);
        } else {
          modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity,
            CommandsModifier, undefined);
        }
        return this;
      }
      commands(value: any): this {
        modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity, CommandsModifier, value);
        return this;
      }
    }

    class CommandsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().path.resetPathCommands(node);
        } else {
          getUINativeModule().path.setPathCommands(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (CommandsModifier as any).identity = Symbol('commands');

    loadComponent.componentObj = {'component' : ArkPathComponent };
  }
  return loadComponent.componentObj;
}

class JSPath extends commonModule.CommonShape {
    constructor(value) {
      super();
      return new __Path__(value)
    }
    static create(params: any): void {
        getUINativeModule().path.create(params);
    }
    static commands(value: any): void {
        getUINativeModule().path.setPathCommands(true, value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.PathModifier(nativePtr, classType);
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
    static onTouch(value: any): void {
        __Common__.onTouch(value);
    }
    static onHover(value: any): void {
        __Common__.onHover(value);
    }
    static remoteMessage(value: any): void {
        __Common__.remoteMessage(value);
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
    globalThis.ArkPathComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.Path = JSPath;
}

export default { loadComponent, createComponent, exportComponent, exportView };

