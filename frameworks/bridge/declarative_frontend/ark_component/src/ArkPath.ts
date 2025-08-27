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
interface PathOptionsParam {
  width?: Length;
  height?: Length;
  commands?: ResourceStr;
}
class ArkPathComponent extends ArkCommonShapeComponent implements PathAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  commands(value: ResourceStr): this {
    modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity, CommandsModifier, value);
    return this;
  }
  resetPathOptions(): void {
    modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
      CommonShapeWidthModifier, undefined);
    modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
      CommonShapeHeightModifier, undefined);
    modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity,
      CommandsModifier, undefined);
  }
  initialize(value: Object[]): this {
    if (isUndefined(value[0]) || isNull(value[0])) {
      this.resetPathOptions();
      return this;
    }
    const value_casted = value[0] as PathOptionsParam;
    if (!isUndefined(value_casted.width) && !isNull(value_casted.width)) {
      modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
        CommonShapeWidthModifier, value_casted.width);
    } else {
      modifierWithKey(this._modifiersWithKeys, CommonShapeWidthModifier.identity,
        CommonShapeWidthModifier, undefined);
    }
    if (!isUndefined(value_casted.height) && !isNull(value_casted.height)) {
      modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
        CommonShapeHeightModifier, value_casted.height);
    } else {
      modifierWithKey(this._modifiersWithKeys, CommonShapeHeightModifier.identity,
        CommonShapeHeightModifier, undefined);
    }
    if (!isUndefined(value_casted.commands) && !isNull(value_casted.commands)) {
      modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity,
        CommandsModifier, value_casted.commands);
    } else {
      modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity,
        CommandsModifier, undefined);
    }
    return this;
  }
}

class CommandsModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('commands');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().path.resetPathCommands(node);
    } else {
      getUINativeModule().path.setPathCommands(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.Path.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkPathComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.PathModifier(nativePtr, classType);
  });
};
