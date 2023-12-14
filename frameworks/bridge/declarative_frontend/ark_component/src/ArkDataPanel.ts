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
      GetUINativeModule().dataPanel.resetDataPanelStrokeWidth(node);
    } else {
      GetUINativeModule().dataPanel.setDataPanelStrokeWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class DataPanelCloseEffectModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('dataPanelCloseEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().dataPanel.resetCloseEffect(node);
    } else {
      GetUINativeModule().dataPanel.setCloseEffect(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class DataPanelTrackBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('dataPanelTrackBackgroundColorModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().dataPanel.resetDataPanelTrackBackgroundColor(node);
    } else {
      GetUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}
class DataPanelTrackShadowModifier extends ModifierWithKey<DataPanelShadowOptions> {
  static identity = Symbol('dataPanelTrackShadow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().dataPanel.resetDataPanelTrackShadow(node);
    } else {
      GetUINativeModule().dataPanel.setDataPanelTrackShadow(node, this.value!);
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
      GetUINativeModule().dataPanel.resetDataPanelValueColors(node);
    } else {
      GetUINativeModule().dataPanel.setDataPanelValueColors(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
// @ts-ignore
globalThis.DataPanel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkDataPanelComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
