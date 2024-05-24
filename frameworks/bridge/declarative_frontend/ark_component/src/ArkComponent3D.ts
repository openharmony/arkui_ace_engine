/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class ShaderInputBufferModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('shaderInputBuffer');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().component3D.resetShaderInputBuffer(node);
    } else {
      getUINativeModule().component3D.setShaderInputBuffer(node, this.value);
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

class ArkComponent3DComponent extends ArkComponent implements Component3DAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  environment(uri: Resource): Component3DAttribute {
    throw new Error('Method not implemented.');
  };
  customRender(uri: Resource, selfRenderUpdate: boolean): Component3DAttribute {
    throw new Error('Method not implemented.');
  };
  shader(uri: Resource): Component3DAttribute {
    throw new Error('Method not implemented.');
  };
  shaderImageTexture(uri: Resource): Component3DAttribute {
    throw new Error('Method not implemented.');
  };
  shaderInputBuffer(buffer: object): Component3DAttribute {
    modifierWithKey(this._modifiersWithKeys, ShaderInputBufferModifier.identity, ShaderInputBufferModifier, buffer);
    return this;
  };
  renderWidth(value: Dimension): Component3DAttribute {
    throw new Error('Method not implemented.');
  };
  renderHeight(value: Dimension): Component3DAttribute {
    throw new Error('Method not implemented.');
  };
}

// @ts-ignore
globalThis.Component3D.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkComponent3DComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.Component3DModifier(nativePtr, classType);
  });
};