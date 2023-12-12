/// <reference path='./import.ts' />
class ArkPathComponent extends ArkCommonShapeComponent implements PathAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  commands(value: string): this {
    modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity, CommandsModifier, value);
    return this;
  }
}

class CommandsModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('commands');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().path.resetPathCommands(node);
    } else {
      GetUINativeModule().path.setPathCommands(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isString(this.stageValue) && isString(this.value)) {
      return this.stageValue !== this.value;
    } else {
      return true;
    }
  }
}

// @ts-ignore
globalThis.Path.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPathComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
