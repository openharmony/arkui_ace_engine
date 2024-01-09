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
class ArkDataPanelComponent extends ArkComponent implements DataPanelAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  closeEffect(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelCloseEffectModifier.identity, DataPanelCloseEffectModifier, value);
    return this;
  }
  valueColors(value: Array<ResourceColor | LinearGradient>): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelValueColorsModifier.identity, DataPanelValueColorsModifier, value);
    return this;
  }
  trackBackgroundColor(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelTrackBackgroundColorModifier.identity, DataPanelTrackBackgroundColorModifier, value);
    return this;
  }
  strokeWidth(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelStrokeWidthModifier.identity, DataPanelStrokeWidthModifier, value);
    return this;
  }
  trackShadow(value: DataPanelShadowOptions): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelTrackShadowModifier.identity, DataPanelTrackShadowModifier, value);
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class DataPanelStrokeWidthModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('dataPanelStrokeWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().dataPanel.resetDataPanelStrokeWidth(node);
    } else {
      getUINativeModule().dataPanel.setDataPanelStrokeWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class DataPanelCloseEffectModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('dataPanelCloseEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().dataPanel.resetCloseEffect(node);
    } else {
      getUINativeModule().dataPanel.setCloseEffect(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class DataPanelTrackBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('dataPanelTrackBackgroundColorModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().dataPanel.resetDataPanelTrackBackgroundColor(node);
    } else {
      getUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class DataPanelTrackShadowModifier extends ModifierWithKey<DataPanelShadowOptions> {
  static identity = Symbol('dataPanelTrackShadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      if (this.value === null) {
        getUINativeModule().dataPanel.setDataPanelTrackShadow(node, null);
      }
      getUINativeModule().dataPanel.resetDataPanelTrackShadow(node);
    } else {
      getUINativeModule().dataPanel.setDataPanelTrackShadow(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
class DataPanelValueColorsModifier extends ModifierWithKey<Array<ResourceColor | LinearGradient>> {
  static identity = Symbol('dataPanelValueColors');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().dataPanel.resetDataPanelValueColors(node);
      return;
    } else {
      getUINativeModule().dataPanel.setDataPanelValueColors(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
// @ts-ignore
globalThis.DataPanel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkDataPanelComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
