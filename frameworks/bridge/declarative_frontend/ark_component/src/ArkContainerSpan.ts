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
class ContainerSpanTextBackgroundStyleModifier extends ModifierWithKey<TextBackgroundStyle> {
  constructor(value: TextBackgroundStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('containerSpanTextBackgroundStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().containerSpan.resetTextBackgroundStyle(node);
    } else {
      let textBackgroundStyle = new ArkTextBackGroundStyle();
      if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value)) {
        getUINativeModule().containerSpan.resetTextBackgroundStyle(node);
      } else {
        getUINativeModule().containerSpan.setTextBackgroundStyle(node,
          textBackgroundStyle.color, textBackgroundStyle.radius.topLeft,
          textBackgroundStyle.radius.topRight,
          textBackgroundStyle.radius.bottomLeft,
          textBackgroundStyle.radius.bottomRight);
      }
    }
  }
  checkObjectDiff(): boolean {
    let textBackgroundStyle = new ArkTextBackGroundStyle();
    let stageTextBackGroundStyle = new ArkTextBackGroundStyle();
    if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value) ||
      !stageTextBackGroundStyle.convertTextBackGroundStyleOptions(this.stageValue)) {
      return false;
    } else {
      return textBackgroundStyle.checkObjectDiff(stageTextBackGroundStyle);
    }
  }
}

class ArkContainerSpanComponent extends ArkComponent implements ContainerSpanAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  textBackgroundStyle(value: TextBackgroundStyle): ContainerSpanAttribute {
    modifierWithKey(this._modifiersWithKeys,
      ContainerSpanTextBackgroundStyleModifier.identity, ContainerSpanTextBackgroundStyleModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.ContainerSpan.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkContainerSpanComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ContainerSpanModifier(nativePtr, classType);
  });
};
  