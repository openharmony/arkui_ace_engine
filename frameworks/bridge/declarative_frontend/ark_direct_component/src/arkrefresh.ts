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
    class ArkRefreshComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      allowChildCount() {
        return 1;
      }
      initialize(value: any): this {
        if (value.length === 1 && isObject(value[0])) {
          modifierWithKey(this._modifiersWithKeys, RefreshInitializeModifier.identity, RefreshInitializeModifier, value[0]);
        } else {
          modifierWithKey(this._modifiersWithKeys, RefreshInitializeModifier.identity, RefreshInitializeModifier, undefined);
        }
        return this;
      }
      onStateChange(value: (state: RefreshStatus) => void): this {
        modifierWithKey(this._modifiersWithKeys, RefreshOnStateChangeModifier.identity, RefreshOnStateChangeModifier, value);
        return this;
      }
      onRefreshing(value: () => void): this {
        modifierWithKey(this._modifiersWithKeys, RefreshOnRefreshingModifier.identity, RefreshOnRefreshingModifier, value);
        return this;
      }
      refreshOffset(value: number | Resource): this {
        modifierWithKey(this._modifiersWithKeys, RefreshOffsetModifier.identity, RefreshOffsetModifier, value);
        return this;
      }
      pullToRefresh(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, PullToRefreshModifier.identity, PullToRefreshModifier, value);
        return this;
      }
      pullUpToCancelRefresh(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, PullUpToCancelRefreshModifier.identity, PullUpToCancelRefreshModifier, value);
        return this;
      }
      pullDownRatio(value: number): this {
        modifierWithKey(this._modifiersWithKeys, PullDownRatioModifier.identity, PullDownRatioModifier, value);
        return this;
      }
      onOffsetChange(value: Callback<number>): this {
        modifierWithKey(this._modifiersWithKeys, RefreshOnOffsetChangeModifier.identity, RefreshOnOffsetChangeModifier, value);
        return this;
      }
      maxPullDownDistance(value: number | Resource): this {
        modifierWithKey(this._modifiersWithKeys, MaxPullDownDistanceModifier.identity, MaxPullDownDistanceModifier, value);
        return this;
      }
    }

    class RefreshInitializeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          return;
        }
        getUINativeModule().refresh.create(node, this.value);
      }
    }
    (RefreshInitializeModifier as any).identity = Symbol('refreshInitialize');

    class RefreshOffsetModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetRefreshOffset(node);
        } else {
          getUINativeModule().refresh.setRefreshOffset(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (RefreshOffsetModifier as any).identity = Symbol('refreshOffset');

    class PullToRefreshModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetPullToRefresh(node);
        } else {
          getUINativeModule().refresh.setPullToRefresh(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PullToRefreshModifier as any).identity = Symbol('pullToRefresh');

    class PullUpToCancelRefreshModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetPullUpToCancelRefresh(node);
        } else {
          getUINativeModule().refresh.setPullUpToCancelRefresh(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PullUpToCancelRefreshModifier as any).identity = Symbol('pullUpToCancelRefresh');

    class PullDownRatioModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetPullDownRatio(node);
        } else {
          getUINativeModule().refresh.setPullDownRatio(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (PullDownRatioModifier as any).identity = Symbol('pullDownRatio');

    class RefreshOnStateChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetOnStateChange(node);
        } else {
          getUINativeModule().refresh.setOnStateChange(node, this.value);
        }
      }
    }
    (RefreshOnStateChangeModifier as any).identity = Symbol('onStateChange');

    class RefreshOnRefreshingModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetOnRefreshing(node);
        } else {
          getUINativeModule().refresh.setOnRefreshing(node, this.value);
        }
      }
    }
    (RefreshOnRefreshingModifier as any).identity = Symbol('onRefreshing');

    class RefreshOnOffsetChangeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetOnOffsetChange(node);
        } else {
          getUINativeModule().refresh.setOnOffsetChange(node, this.value);
        }
      }
    }
    (RefreshOnOffsetChangeModifier as any).identity = Symbol('onOffsetChange');

    class MaxPullDownDistanceModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().refresh.resetMaxPullDownDistance(node);
        } else {
          getUINativeModule().refresh.setMaxPullDownDistance(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (MaxPullDownDistanceModifier as any).identity = Symbol('maxPullDownDistance');

    loadComponent.componentObj = {'component' : ArkRefreshComponent };
  }
  return loadComponent.componentObj;
}

class JSRefresh extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().refresh.create(params);
  }

  static refreshOffset(value: any): void {
    getUINativeModule().refresh.setRefreshOffset(true, value);
  }

  static pullToRefresh(value: any): void {
    getUINativeModule().refresh.setPullToRefresh(true, value);
  }

  static pullUpToCancelRefresh(value: any): void {
    getUINativeModule().refresh.setPullUpToCancelRefresh(true, value);
  }

  static onStateChange(value: any): void {
    getUINativeModule().refresh.setOnStateChange(true, value);
  }

  static onRefreshing(value: any): void {
    getUINativeModule().refresh.setOnRefreshing(true, value);
  }

  static onOffsetChange(value: any): void {
    getUINativeModule().refresh.setOnOffsetChange(true, value);
  }

  static pullDownRatio(value: any): void {
    getUINativeModule().refresh.setPullDownRatio(true, value);
  }

  static maxPullDownDistance(value: any): void {
    getUINativeModule().refresh.setMaxPullDownDistance(true, value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.RefreshModifier(nativePtr, classType);
    });
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
  globalThis.ArkRefreshComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Refresh = JSRefresh;
}

export default { loadComponent, createComponent, exportComponent, exportView };
