/// <reference path='./import.ts' />

class ArkNavigatorComponent extends ArkComponent implements NavigatorAttribute {
  active(value: boolean): NavigatorAttribute {
    modifier(this._modifiers, ActiveModifier, value);
    return this;
  }
  type(value: NavigationType): NavigatorAttribute {
    modifier(this._modifiers, TypeModifier, value);
    return this;
  }
  target(value: string): NavigatorAttribute {
    modifier(this._modifiers, TargetModifier, value);
    return this;
  }
  params(value: object): NavigatorAttribute {
    modifier(this._modifiers, ParamsModifier, JSON.stringify(value));
    return this;
  }
}

class ParamsModifier extends Modifier<string> {
  static identity: Symbol = Symbol('params');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetParams(node);
    } else {
      GetUINativeModule().navigator.setParams(node, this.value);
    }
  }
}

class TypeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('type');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetType(node);
    } else {
      GetUINativeModule().navigator.setType(node, this.value);
    }
  }
}

class ActiveModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('active');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetActive(node);
    } else {
      GetUINativeModule().navigator.setActive(node, this.value);
    }
  }
}

class TargetModifier extends Modifier<string> {
  static identity: Symbol = Symbol('target');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetTarget(node);
    } else {
      GetUINativeModule().navigator.setTarget(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Navigator.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavigatorComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
