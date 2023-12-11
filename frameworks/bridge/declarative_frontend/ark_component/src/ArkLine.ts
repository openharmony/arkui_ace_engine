/// <reference path='./import.ts' />
/// <reference path='./ArkCommonShape.ts' />
class ArkLineComponent extends ArkCommonShapeComponent implements LineAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  startPoint(value: Array<Length>): this {
    modifierWithKey(this._modifiersWithKeys, LineStartPointModifier.identity, LineStartPointModifier, value);
    return this;
  }
  endPoint(value: Array<Length>): this {
    modifierWithKey(this._modifiersWithKeys, LineEndPointModifier.identity, LineEndPointModifier, value);
    return this;
  }
}

class LineStartPointModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('startPoint');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().line.resetStartPoint(node);
    } else {
      GetUINativeModule().line.setStartPoint(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class LineEndPointModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('endPoint');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().line.resetEndPoint(node);
    } else {
      GetUINativeModule().line.setEndPoint(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

// @ts-ignore
globalThis.Line.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkLineComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
