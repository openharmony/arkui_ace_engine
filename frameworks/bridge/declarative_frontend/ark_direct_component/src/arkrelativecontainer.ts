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
const LOCALIZED_BARRIER_DIRECTION_START = 4;
const BARRIER_DIRECTION_RIGHT = 3;

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkRelativeContainerComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }

      initialize(value: any): this {
        return this;
      }

      guideLine(value: any): this {
        let guideLineInfo = new ArkRelativeContainerGuideLine();
        guideLineInfo.ids = value.map(item => { return item.id; });
        guideLineInfo.directions = value.map(item => { return item.direction; });
        guideLineInfo.positions = new Array();
        for (let i = 0; i < value.length; i++) {
          guideLineInfo.positions.push(value[i].position.start);
          guideLineInfo.positions.push(value[i].position.end);
        }
        modifierWithKey(this._modifiersWithKeys, RelativeContainerGuideLineModifier.identity, RelativeContainerGuideLineModifier, guideLineInfo);
        return this;
      }

      barrier(value: any): this {
        let barrierInfo = new ArkRelativeContainerBarrier();
        barrierInfo.ids = value.map(item => { return item.id; });
        barrierInfo.directions = value.map(item => { return item.direction; });
        barrierInfo.referencedIds = value.map(item => { return item.referencedId; });
        modifierWithKey(this._modifiersWithKeys, RelativeContainerBarrierModifier.identity, RelativeContainerBarrierModifier, barrierInfo);
        return this;
      }
    }

    class RelativeContainerGuideLineModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
    
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().relativeContainer.resetGuideLine(node);
        } else {
          getUINativeModule().relativeContainer.setGuideLine(node,
            this.value.ids, this.value.directions, this.value.positions);
        }
      }
    
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.ids, this.value.ids) ||
          !isBaseOrResourceEqual(this.stageValue.directions, this.value.directions) ||
          !isBaseOrResourceEqual(this.stageValue.positions, this.value.positions);
      }
    }
    (RelativeContainerGuideLineModifier as any).identity = Symbol('relativeContainerGuideLine');
    
    class RelativeContainerBarrierModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
    
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().relativeContainer.resetBarrier(node);
        } else {
          getUINativeModule().relativeContainer.setBarrier(node,
            this.value.ids, this.value.directions, this.value.referencedIds);
        }
      }
    
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.ids, this.value.ids) ||
          !isBaseOrResourceEqual(this.stageValue.directions, this.value.directions) ||
          !isBaseOrResourceEqual(this.stageValue.referencedIds, this.value.referencedIds);
      }
    }
    (RelativeContainerBarrierModifier as any).identity = Symbol('relativeContainerBarrier');

    loadComponent.componentObj = { 'component': ArkRelativeContainerComponent };
  }
  return loadComponent.componentObj;
}

class JSRelativeContainer extends JSContainerBase {
  static create(): void {
    getUINativeModule().relativeContainer.create();
  }

  static guideLine(value: any): void {
    getUINativeModule().relativeContainer.setGuideLine(true, value);
  }

  static barrier(value: any): void {
    getUINativeModule().relativeContainer.setBarrier(true, value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr, undefined);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.RelativeContainerModifier(nativePtr, classType);
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

  static remoteMessage(value: any): void {
    __Common__.remoteMessage(value);
  }
}

class ArkRelativeContainerGuideLine {
  ids: any;
  directions: any;
  positions: any;

  constructor() {
    this.ids = undefined;
    this.directions = undefined;
    this.positions = undefined;
  }

  isEqual(another: ArkRelativeContainerGuideLine): boolean {
    return this.ids === another.ids && this.directions === another.directions && this.positions === another.positions;
  }
}

class ArkRelativeContainerBarrier {
  ids: any;
  directions: any;
  referencedIds: any;

  constructor() {
    this.ids = undefined;
    this.directions = undefined;
    this.referencedIds = undefined;
  }

  isEqual(another: ArkRelativeContainerBarrier): boolean {
    return this.ids === another.ids && this.directions === another.directions &&
      this.referencedIds === another.referencedIds;
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
  globalThis.ArkRelativeContainerComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.RelativeContainer = JSRelativeContainer;
}

export default { loadComponent, createComponent, exportComponent, exportView };