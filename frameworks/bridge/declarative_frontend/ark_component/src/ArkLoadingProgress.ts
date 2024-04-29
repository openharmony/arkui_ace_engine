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
class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
  builder: WrappedBuilder<Object[]> | null = null;
  loadingProgressNode: BuilderNode<[LoadingProgressConfiguration]> | null = null;
  modifier: ContentModifier<LoadingProgressConfiguration>;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
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
    modifierWithKey(this._modifiersWithKeys, LoadingProgressForegroundColorModifier.identity,
      LoadingProgressForegroundColorModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<LoadingProgressConfiguration>): this {
    if (modifier === undefined || modifier === null) {
        return;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().loadingProgress.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, loadingProgressConfiguration: LoadingProgressConfiguration): FrameNode | null {
    loadingProgressConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.loadingProgressNode)) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.loadingProgressNode = new xNode.BuilderNode(context);
      this.loadingProgressNode.build(this.builder, loadingProgressConfiguration);
    } else {
      this.loadingProgressNode.update(loadingProgressConfiguration);
    }
    return this.loadingProgressNode.getFrameNode();
  }
}

class LoadingProgressColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('loadingProgressColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().loadingProgress.resetColor(node);
    } else {
      getUINativeModule().loadingProgress.setColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LoadingProgressForegroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('loadingProgressForegroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().loadingProgress.resetForegroundColor(node);
    } else {
      getUINativeModule().loadingProgress.setForegroundColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LoadingProgressEnableLoadingModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('loadingProgressEnableLoading');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().loadingProgress.resetEnableLoading(node);
    } else {
      getUINativeModule().loadingProgress.setEnableLoading(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.LoadingProgress.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkLoadingProgressComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.LoadingProgressModifier(nativePtr, classType);
  });
};


// @ts-ignore
globalThis.LoadingProgress.contentModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkLoadingProgressComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};
