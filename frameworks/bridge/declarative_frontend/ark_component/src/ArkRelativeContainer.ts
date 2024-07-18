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
class RelativeContainerGuideLineModifier extends ModifierWithKey<ArkRelativeContainerGuideLine> {
  constructor(value: ArkRelativeContainerGuideLine) {
    super(value);
  }
  static identity: Symbol = Symbol('relativeContainerGuideLine');
  applyPeer(node: KNode, reset: boolean): void {
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

class RelativeContainerBarrierModifier extends ModifierWithKey<ArkRelativeContainerBarrier> {
  constructor(value: ArkRelativeContainerBarrier) {
    super(value);
  }
  static identity: Symbol = Symbol('relativeContainerBarrier');
  applyPeer(node: KNode, reset: boolean): void {
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

class ArkRelativeContainerComponent extends ArkComponent implements RelativeContainerAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): RelativeContainerAttribute {
    return this;
  }
  guideLine(value: Array<GuideLineStyle>): RelativeContainerAttribute {
    let guideLineInfo = new ArkRelativeContainerGuideLine();
    guideLineInfo.ids = value.map(item => { return item.id; });
    guideLineInfo.directions = value.map(item => { return item.direction; });
    guideLineInfo.positions = new Array<Dimension>();
    for (let i = 0; i < value.length; i++) {
      guideLineInfo.positions.push(value[i].position.start);
      guideLineInfo.positions.push(value[i].position.end);
    }
    modifierWithKey(this._modifiersWithKeys, RelativeContainerGuideLineModifier.identity, RelativeContainerGuideLineModifier, guideLineInfo);
    return this;
  }
  barrier(value: Array<BarrierStyle>): RelativeContainerAttribute {
    let barrierInfo = new ArkRelativeContainerBarrier();
    barrierInfo.ids = value.map(item => { return item.id; });
    barrierInfo.directions = value.map(item => { return item.direction; });
    barrierInfo.referencedIds = value.map(item => { return item.referencedId; });
    modifierWithKey(this._modifiersWithKeys, RelativeContainerBarrierModifier.identity, RelativeContainerBarrierModifier, barrierInfo);
    return this;
  }
}

// @ts-ignore
globalThis.RelativeContainer.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRelativeContainerComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RelativeContainerModifier(nativePtr, classType);
  });
};
