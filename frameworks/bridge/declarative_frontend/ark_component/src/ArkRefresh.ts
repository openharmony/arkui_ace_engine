/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
class ArkRefreshComponent extends ArkComponent implements RefreshAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onStateChange(callback: (state: RefreshStatus) => void): this {
    modifierWithKey(this._modifiersWithKeys, RefreshOnStateChangeModifier.identity, RefreshOnStateChangeModifier, callback);
    return this;
  }
  onRefreshing(callback: () => void): this {
    modifierWithKey(this._modifiersWithKeys, RefreshOnRefreshingModifier.identity, RefreshOnRefreshingModifier, callback);
    return this;
  }
  refreshOffset(value: number): this {
    modifierWithKey(this._modifiersWithKeys, RefreshOffsetModifier.identity, RefreshOffsetModifier, value);
    return this;
  }
  pullToRefresh(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, PullToRefreshModifier.identity, PullToRefreshModifier, value);
    return this;
  }
  pullDownRatio(value: number): this {
    modifierWithKey(this._modifiersWithKeys, PullDownRatioModifier.identity, PullDownRatioModifier, value);
    return this;
  }
  onOffsetChange(callback: Callback<number>): this {
    modifierWithKey(this._modifiersWithKeys, RefreshOnOffsetChangeModifier.identity, RefreshOnOffsetChangeModifier, callback);
    return this;
  }
}

class RefreshOffsetModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('refreshOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().refresh.resetRefreshOffset(node);
    } else {
      getUINativeModule().refresh.setRefreshOffset(node, this.value);
    }
  }
}
class PullToRefreshModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('pullToRefresh');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().refresh.resetPullToRefresh(node);
    } else {
      getUINativeModule().refresh.setPullToRefresh(node, this.value);
    }
  }
}
class PullDownRatioModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('pullDownRatio');
  applyPeer(node: KNode, reset: boolean): void {
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
class RefreshOnOffsetChangeModifier extends ModifierWithKey<Callback<number>> {
  constructor(value: Callback<number>) {
    super(value);
  }
  static identity: Symbol = Symbol('onOffsetChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().refresh.resetOnOffsetChange(node);
    } else {
      getUINativeModule().refresh.setOnOffsetChange(node, this.value);
    }
  }
}
class RefreshOnStateChangeModifier extends ModifierWithKey<(state: RefreshStatus) => void> {
  constructor(value: (state: RefreshStatus) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onStateChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().refresh.resetOnStateChange(node);
    } else {
      getUINativeModule().refresh.setOnStateChange(node, this.value);
    }
  }
}
class RefreshOnRefreshingModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onRefreshing');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().refresh.resetOnRefreshing(node);
    } else {
      getUINativeModule().refresh.setOnRefreshing(node, this.value);
    }
  }
}
// @ts-ignore
globalThis.Refresh.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRefreshComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RefreshModifier(nativePtr, classType);
  });
};
