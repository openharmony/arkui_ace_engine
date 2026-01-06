/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
class ArkHyperlinkComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, HyperlinkColorModifier.identity, HyperlinkColorModifier, value);
    return this;
  }
  draggable(value) {
    modifierWithKey(this._modifiersWithKeys, HyperlinkDraggableModifier.identity, HyperlinkDraggableModifier, value);
    return this;
  }
  responseRegion(value) {
    modifierWithKey(this._modifiersWithKeys, HyperlinkResponseRegionModifier.identity, HyperlinkResponseRegionModifier, value);
    return this;
  }
}
class HyperlinkColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().hyperlink.resetColor(node);
    }
    else {
      getUINativeModule().hyperlink.setColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
HyperlinkColorModifier.identity = Symbol('hyperlinkColor');
class HyperlinkDraggableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().hyperlink.resetDraggable(node);
    }
    else {
      getUINativeModule().hyperlink.setDraggable(node, this.value);
    }
  }
}
HyperlinkDraggableModifier.identity = Symbol('hyperlinkDraggable');
class HyperlinkResponseRegionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().hyperlink.resetResponseRegion(node);
    }
    else {
      let responseRegion = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push((_a = this.value[i].x) !== null && _a !== void 0 ? _a : 'PLACEHOLDER');
          responseRegion.push((_b = this.value[i].y) !== null && _b !== void 0 ? _b : 'PLACEHOLDER');
          responseRegion.push((_c = this.value[i].width) !== null && _c !== void 0 ? _c : 'PLACEHOLDER');
          responseRegion.push((_d = this.value[i].height) !== null && _d !== void 0 ? _d : 'PLACEHOLDER');
        }
      }
      else {
        responseRegion.push((_e = this.value.x) !== null && _e !== void 0 ? _e : 'PLACEHOLDER');
        responseRegion.push((_f = this.value.y) !== null && _f !== void 0 ? _f : 'PLACEHOLDER');
        responseRegion.push((_g = this.value.width) !== null && _g !== void 0 ? _g : 'PLACEHOLDER');
        responseRegion.push((_h = this.value.height) !== null && _h !== void 0 ? _h : 'PLACEHOLDER');
      }
      getUINativeModule().hyperlink.setResponseRegion(node, responseRegion, responseRegion.length);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
HyperlinkResponseRegionModifier.identity = Symbol('hyperlinkResponseRegion');

class JSHyperlink extends JSViewAbstract {
  static create(address, content) {
    console.log("[Hyperlink] JSHyperlink::create")
    if (address !== undefined) {
      console.log(`[Hyperlink] JSHyperlink::create ${typeof address}: ${address}, ${typeof content}: ${content}`)
      getUINativeModule().hyperlink.create(address, content);
    } else {
      console.log("[Hyperlink] JSHyperlink::create params undefined")
      getUINativeModule().hyperlink.create('', '');
    }
    console.log("[Hyperlink] JSHyperlink::create end");
  }

  static color(color) {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.color(node, color);
  }

  static draggable(draggable) {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.draggable(node, draggable);
  }

  static responseRegion() {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.responseRegion(node);
  }

  static pop() {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.pop(node);
  }

  static onAttach(value) {
    __Common__.onAttach(value);
  }

  static onAppear(value) {
    __Common__.onAppear(value);
  }

  static onDetach(value) {
    __Common__.onDetach(value);
  }

  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }

  static onTouch(value) {
    __Common__.onTouch(value);
  }

  static onHover(value) {
    __Common__.onHover(value);
  }

  static onKeyEvent(value) {
    __Common__.onKeyEvent(value);
  }

  static onDeleteEvent(value) {
    __Common__.onKeyEvent(value);
  }

  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkHyperlinkComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.HyperlinkModifier(nativePtr, classType);
    });
  }
}

function createComponent(nativePtr, classType) {
  return new ArkHyperlinkComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkHyperlinkComponent = ArkHyperlinkComponent;
}

function exportView() {
  globalThis.Hyperlink = JSHyperlink;
}

export default { ArkHyperlinkComponent, createComponent, exportComponent, exportView };