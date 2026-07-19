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

getUINativeModule().loadNativeModule('CommonShape');
let commonModule = globalThis.requireNapi('arkui.components.arkcommonshape');
commonModule.exportView();
commonModule.loadComponent();
commonModule.exportComponent();

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkLineComponent extends ArkCommonShapeComponent {
        constructor(nativePtr: any, classType: any) {
            super(nativePtr, classType);
        }
        startPoint(value: Array<any>): this {
            modifierWithKey(this._modifiersWithKeys, LineStartPointModifier.identity, LineStartPointModifier, value);
            return this;
        }
        endPoint(value: Array<any>): this {
            modifierWithKey(this._modifiersWithKeys, LineEndPointModifier.identity, LineEndPointModifier, value);
            return this;
        }
    }

    class LineStartPointModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('startPoint');
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().line.resetStartPoint(node);
            } else {
                getUINativeModule().line.setStartPoint(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }

    class LineEndPointModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        static identity: Symbol = Symbol('endPoint');
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().line.resetEndPoint(node);
            } else {
                getUINativeModule().line.setEndPoint(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }

    loadComponent.componentObj = {'component' : ArkLineComponent };
  }
  return loadComponent.componentObj;
}

class JSLine extends commonModule.CommonShape {
    static create(value: any): void {
        getUINativeModule().line.create(value);
    }
    static startPoint(value: any): void {
        getUINativeModule().line.setStartPoint(true, value);
    }
    static endPoint(value: any): void {
        getUINativeModule().line.setEndPoint(true, value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.LineModifier(nativePtr, classType);
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

function createComponent(nativePtr: any, classType: any): any {
    loadComponent();
    if (loadComponent.componentObj !== undefined) {
        return new loadComponent.componentObj.component(nativePtr, classType);
    }
    return undefined;
}

function exportComponent(): void {
    globalThis.ArkLineComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.Line = JSLine;
}

export default { loadComponent, createComponent, exportComponent, exportView };
