/// <reference path="./import.ts" />
class PatternLockActiveColorModifier extends Modifier<number> {
  static identity: Symbol = Symbol('patternLockActiveColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetActiveColor(node);
    } else {
      GetUINativeModule().patternLock.setActiveColor(node, this.value!);
    }
  }
}

class PatternLockSelectedColorModifier extends Modifier<number> {
  static identity: Symbol = Symbol('patternLockSelectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetSelectedColor(node);
    } else {
      GetUINativeModule().patternLock.setSelectedColor(node, this.value!);
    }
  }
}

class PatternLockPathColorModifier extends Modifier<number> {
  static identity: Symbol = Symbol('patternLockPathColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetPathColor(node);
    } else {
      GetUINativeModule().patternLock.setPathColor(node, this.value!);
    }
  }
}

class PatternLockRegularColorModifier extends Modifier<number> {
  static identity: Symbol = Symbol('patternLockRegularColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetRegularColor(node);
    } else {
      GetUINativeModule().patternLock.setRegularColor(node, this.value!);
    }
  }
}

class PatternLockSideLengthModifier extends Modifier<number|string> {
  static identity: Symbol = Symbol('patternLockSideLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetSideLength(node);
    } else {
      GetUINativeModule().patternLock.setSideLength(node, this.value!);
    }
  }
}

class PatternLockPathStrokeModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('patternLockPathStroke');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetPathStrokeWidth(node);
    } else {
      GetUINativeModule().patternLock.setPathStrokeWidth(node, this.value!);
    }
  }
}

class PatternLockCircleRadiusModifier extends Modifier<number> {
  static identity: Symbol = Symbol('patternLockCircleRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetCircleRadius(node);
    } else {
      GetUINativeModule().patternLock.setCircleRadius(node, this.value!);
    }
  }
}

class PatternLockAutoResetModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('patternlockautoreset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().patternLock.resetAutoReset(node);
    } else {
      GetUINativeModule().patternLock.setAutoReset(node, this.value!);
    }
  }
}

class ArkPatternLockComponent extends ArkComponent implements PatternLockAttribute {
  sideLength(value: Length): PatternLockAttribute {
    let arkValue = 288;
    if (isLengthType(value)) {
      let _value :number|string = <number | string>value;
      modifier(this._modifiers, PatternLockSideLengthModifier, _value);
    }else{
      modifier(this._modifiers, PatternLockSideLengthModifier, arkValue);
    }
    return this;
  }
  circleRadius(value: Length): PatternLockAttribute {
    let arkValue = 6;
    if (isLengthType(value)) {
      let _value :number|string = <number | string>value;
      modifier(this._modifiers, PatternLockSideLengthModifier, _value);
    } else {
      modifier(this._modifiers, PatternLockCircleRadiusModifier, arkValue);
    }
    return this;
  }
  regularColor(value: ResourceColor): PatternLockAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, PatternLockRegularColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, PatternLockRegularColorModifier, undefined);
    }
    return this;
  }
  selectedColor(value: ResourceColor): PatternLockAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, PatternLockSelectedColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, PatternLockSelectedColorModifier, undefined);
    }
    return this;
  }
  activeColor(value: ResourceColor): PatternLockAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, PatternLockActiveColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, PatternLockActiveColorModifier, undefined);
    }
    return this;
  }
  pathColor(value: ResourceColor): PatternLockAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, PatternLockPathColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, PatternLockPathColorModifier, undefined);
    }
    return this;
  }
  pathStrokeWidth(value: number | string): PatternLockAttribute {
    let arkValue = 12;
    if (isLengthType(value)) {
      let _value :number|string = <number | string>value;
      modifier(this._modifiers, PatternLockPathStrokeModifier, _value);
    } else {
      modifier(this._modifiers, PatternLockPathStrokeModifier, arkValue);
    }
    
    return this;
  } 

  autoReset(value: boolean): PatternLockAttribute {
    let arkValue = false;
    if (isBoolean(value)) {
      arkValue = value;
    }
    modifier(this._modifiers, PatternLockAutoResetModifier, arkValue);
    return this;
  }  onPatternComplete(callback: (input: Array<number>) => void): PatternLockAttribute {
    throw new Error('Method not implemented.');
  }
  onDotConnect(callback: import('../../../../../../../../../openharmony/out/sdk/ohos-sdk/windows/ets/api/@ohos.base').Callback<number>): PatternLockAttribute{
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.PatternLock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPatternLockComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}