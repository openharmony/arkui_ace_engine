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
class ArkFormComponentComponent extends ArkComponent implements FormComponentAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  size(value: { width: Length; height: Length }): this {
    modifierWithKey(this._modifiersWithKeys,
      FormComponentSizeModifier.identity, FormComponentSizeModifier, value);
    return this;
  }

  visibility(value: Visibility): this {
    modifierWithKey(this._modifiersWithKeys,
      FormComponentVisibilityModifier.identity, FormComponentVisibilityModifier, value);
    return this;
  }

  moduleName(value: string): this {
    modifierWithKey(this._modifiersWithKeys,
      FormComponentModuleNameModifier.identity, FormComponentModuleNameModifier, value);
    return this;
  }
  dimension(value: FormDimension): this {
    modifierWithKey(this._modifiersWithKeys,
      FormComponentDimensionModifier.identity, FormComponentDimensionModifier, value);
    return this;
  }
  allowUpdate(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys,
      FormComponentAllowUpdateModifier.identity, FormComponentAllowUpdateModifier, value);
    return this;
  }
  onAcquired(callback: (info: { id: number; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onError(callback: (info: { errcode: number; msg: string; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onRouter(callback: (info: any) => void): this {
    throw new Error('Method not implemented.');
  }
  onUninstall(callback: (info: { id: number; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onLoad(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
}

class FormComponentModuleNameModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('formComponentModuleName');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().formComponent.resetModuleName(node);
    } else {
      GetUINativeModule().formComponent.setModuleName(node, this.value!);
    }
  }
}

class FormComponentDimensionModifier extends ModifierWithKey<FormDimension> {
  constructor(value: FormDimension) {
    super(value);
  }
  static identity: Symbol = Symbol('formComponentDimension');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().formComponent.resetDimension(node);
    } else {
      GetUINativeModule().formComponent.setDimension(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class FormComponentAllowUpdateModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('formComponentAllowUpdate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().formComponent.resetAllowUpdate(node);
    } else {
      GetUINativeModule().formComponent.setAllowUpdate(node, this.value!);
    }
  }
}

class FormComponentSizeModifier extends ModifierWithKey<{ width: Length; height: Length }> {
  constructor(value: { width: Length; height: Length }) {
    super(value);
  }
  static identity: Symbol = Symbol('formComponentSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().formComponent.resetSize(node);
    } else {
      GetUINativeModule().formComponent.setSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    let widthEQ = isBaseOrResourceEqual(this.stageValue.width, this.value.width);
    let heightEQ = isBaseOrResourceEqual(this.stageValue.height, this.value.height);
    return !widthEQ || !heightEQ;
  }
}

class FormComponentVisibilityModifier extends ModifierWithKey<Visibility> {
  constructor(value: Visibility) {
    super(value);
  }
  static identity: Symbol = Symbol('formComponentVisibility');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().formComponent.resetVisibility(node);
    } else {
      GetUINativeModule().formComponent.setVisibility(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.FormComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkFormComponentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
