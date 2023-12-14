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
const NAV_ROUTE_MODE_RANGE = 2;
const NAV_ROUTE_MODE_DEFAULT = 0;
class ArkNavRouterComponent extends ArkComponent implements NavRouterAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onStateChange(callback: (isActivated: boolean) => void): NavRouterAttribute {
    throw new Error('Method not implemented.');
  }
  mode(mode: NavRouteMode): NavRouterAttribute {
    if (isNumber(mode) && mode >= NAV_ROUTE_MODE_DEFAULT && mode <= NAV_ROUTE_MODE_RANGE) {
      modifier(this._modifiers, NavRouterModeModifier, mode);
    } else {
      modifier(this._modifiers, NavRouterModeModifier, NAV_ROUTE_MODE_DEFAULT);
    }
    return this;
  }
}

class NavRouterModeModifier extends Modifier<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('mode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navRouter.resetMode(node);
    } else {
      GetUINativeModule().navRouter.setMode(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.NavRouter.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavRouterComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}