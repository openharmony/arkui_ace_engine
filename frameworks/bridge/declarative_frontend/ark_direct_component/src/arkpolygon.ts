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
const ARRAY_LENGTH = 2;

getUINativeModule().loadNativeModule('CommonShape');
let commonModule = globalThis.requireNapi('arkui.components.arkcommonshape');
commonModule.exportView();
commonModule.loadComponent();
commonModule.exportComponent();

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkPolygonComponent extends ArkCommonShapeComponent {
        constructor(nativePtr: any, classType: any) {
            super(nativePtr, classType);
        }
        points(value: Array<any>): this {
            modifierWithKey(this._modifiersWithKeys, PolygonPointsModifier.identity, PolygonPointsModifier, value);
            return this;
        }
    }

    class PolygonPointsModifier extends ModifierWithKey<Array<any>> {
        constructor(value: Array<any>) {
            super(value);
        }
        static identity: Symbol = Symbol('polygonPoints');
        applyPeer(node: any, reset: boolean): void {
            let xPoint: any[] = [];
            let yPoint: any[] = [];
            if (Array.isArray(this.value)) {
                for (let i = 0; i < this.value.length; i++) {
                    let item = this.value[i];
                    if (!Array.isArray(item)) {
                        continue;
                    }
                    if (item.length < ARRAY_LENGTH || isUndefined(item[0]) || isUndefined(item[1])) {
                        reset = true;
                        break;
                    }
                    xPoint.push(item[0]);
                    yPoint.push(item[1]);
                }
            } else {
                reset = true;
            }
            if (reset) {
                getUINativeModule().polygon.resetPolygonPoints(node);
            } else {
                getUINativeModule().polygon.setPolygonPoints(node, xPoint, yPoint);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }

    loadComponent.componentObj = {'component' : ArkPolygonComponent };
  }
  return loadComponent.componentObj;
}

class JSPolygon extends commonModule.CommonShape {
    static create(params?: any): void {
        getUINativeModule().polygon.create(params);
    }
    static points(value: any): void {
        let xPoint: any[] = [];
        let yPoint: any[] = [];
        if (Array.isArray(value)) {
            for (let i = 0; i < value.length; i++) {
                let item = value[i];
                if (!Array.isArray(item)) {
                    continue;
                }
                if (item.length < ARRAY_LENGTH || isUndefined(item[0]) || isUndefined(item[1])) {
                    break;
                }
                xPoint.push(item[0]);
                yPoint.push(item[1]);
            }
        }
        getUINativeModule().polygon.setPolygonPoints(true, xPoint, yPoint);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.PolygonModifier(nativePtr, classType);
        });
    }

    static onClick(value: any): void {
        __Common__.onClick(value);
    }
    static onKeyEvent(value: any): void {
        __Common__.onKeyEvent(value);
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
    globalThis.ArkPolygonComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.Polygon = JSPolygon;
}

export default { loadComponent, createComponent, exportComponent, exportView };
