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
    class ArkLoadingProgressComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      initialize(value: Object[]): LoadingProgressAttribute {
        return this;
      }
      allowChildCount(): number {
        return 0;
      }
      color(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, LoadingProgressColorModifier.identity, LoadingProgressColorModifier, value);
        return this;
      }
      enableLoading(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, LoadingProgressEnableLoadingModifier.identity, LoadingProgressEnableLoadingModifier, value);
        return this;
      }
      foregroundColor(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, LoadingProgressForegroundColorModifier.identity, LoadingProgressForegroundColorModifier, value);
        return this;
      }
      contentModifier(value: ContentModifier<LoadingProgressConfiguration>): this {
        modifierWithKey(this._modifiersWithKeys, LoadingProgressContentModifier.identity, LoadingProgressContentModifier, value);
        return this;
      }
      setContentModifier(modifier: any): this {
        if (modifier === undefined || modifier === null) {
          getUINativeModule().loadingProgress.setContentModifierBuilder(this.nativePtr, false);
          return this;
        }
        this.needRebuild = false;
        if (this.builder !== modifier.applyContent()) {
          this.needRebuild = true;
        }
        this.builder = modifier.applyContent();
        this.modifier = modifier;
        getUINativeModule().loadingProgress.setContentModifierBuilder(this.nativePtr, this);
        return this;
      }
      makeContentModifierNode(context: any, loadingProgressConfiguration: any): any {
        loadingProgressConfiguration.contentModifier = this.modifier;
        if (isUndefined(this.loadingProgressNode) || this.needRebuild) {
          let xNode = globalThis.requireNapi('arkui.node');
          this.loadingProgressNode = new xNode.BuilderNode(context);
          this.loadingProgressNode.build(this.builder, loadingProgressConfiguration);
          this.needRebuild = false;
        } else {
          this.loadingProgressNode.update(loadingProgressConfiguration);
        }
        return this.loadingProgressNode.getFrameNode();
      }
    }

    class LoadingProgressColorModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().loadingProgress.resetColor(node);
            }
            else {
                getUINativeModule().loadingProgress.setColor(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (LoadingProgressColorModifier as any).identity = Symbol('loadingProgressColor');

    

    class LoadingProgressForegroundColorModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().loadingProgress.resetForegroundColor(node);
            }
            else {
                getUINativeModule().loadingProgress.setForegroundColor(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (LoadingProgressForegroundColorModifier as any).identity = Symbol('loadingProgressForegroundColor');

    class LoadingProgressEnableLoadingModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().loadingProgress.resetEnableLoading(node);
            }
            else {
                getUINativeModule().loadingProgress.setEnableLoading(node, this.value);
            }
        }
    }
    (LoadingProgressEnableLoadingModifier as any).identity = Symbol('loadingProgressEnableLoading');

    class LoadingProgressContentModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean, component: any): void {
            let loadingProgressComponent = component;
            loadingProgressComponent.setContentModifier(this.value);
        }
    }
    (LoadingProgressContentModifier as any).identity = Symbol('loadingProgressContentModifier');

    loadComponent.componentObj = {'component' : ArkLoadingProgressComponent };
  }
  return loadComponent.componentObj;
}

class JSLoadingProgress extends JSViewAbstract {
    static create(): void {
        getUINativeModule().loadingProgress.create();
    }

    static color(value: any): void {
        getUINativeModule().loadingProgress.setColor(true, value);
    }
    static enableLoading(value: any): void {
        getUINativeModule().loadingProgress.setEnableLoading(true, value);
    }
    static foregroundColor(value: any): void {
        getUINativeModule().loadingProgress.setForegroundColor(true, value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.LoadingProgressModifier(nativePtr, classType);
        });
    }
    static contentModifier(modifier: any): void {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'loadingProgress');
        });
        component.setContentModifier(modifier);
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
    globalThis.ArkLoadingProgressComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.LoadingProgress = JSLoadingProgress;
}

export default { loadComponent, createComponent, exportComponent, exportView };
