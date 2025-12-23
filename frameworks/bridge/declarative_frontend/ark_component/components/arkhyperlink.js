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
  static create(params) {
    if (params !== undefined) {
      getUINativeModule().hyperlink.create(params.address, params.content);
    } else {
      getUINativeModule().hyperlink.create('', '');
    }
  }

  static setColor(color) {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.setColor(node, color);
  }

  static resetColor() {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.resetColor(node);
  }

  static setDraggable(draggable) {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.setDraggable(node, draggable);
  }

  static resetDraggable() {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.resetDraggable(node);
  }

  static setResponseRegion(region) {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.setResponseRegion(node, region);
  }

  static resetResponseRegion() {
    let node = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().hyperlink.resetResponseRegion(node);
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