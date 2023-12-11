/// <reference path='./import.ts' />
const MarqueeFontWeightMap = {
  0: 'lighter',
  1: 'normal',
  2: 'regular',
  3: 'medium',
  4: 'bold',
  5: 'bolder',
  100: '100',
  200: '200',
  300: '300',
  400: '400',
  500: '500',
  600: '600',
  700: '700',
  800: '800',
  900: '900',
}

class ArkMarqueeComponent extends ArkComponent implements MarqueeAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  fontSize(value: Length): MarqueeAttribute {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontSizeModifier.identity, MarqueeFontSizeModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): MarqueeAttribute {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontColorModifier.identity, MarqueeFontColorModifier, value);
    return this;
  }
  allowScale(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys,MarqueeAllowScaleModifier.identity,MarqueeAllowScaleModifier, value);
    return this;
  }
  fontWeight(value: string | number | FontWeight): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontWeightModifier.identity,MarqueeFontWeightModifier, value);
    return this;
  }
  fontFamily(value: any): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontFamilyModifier.identity,MarqueeFontFamilyModifier, value as string);
    return this;
  }
  onStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onBounce(event: () => void): this {
    throw new Error('Method not implemented.');
  }
}

class MarqueeFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetFontColor(node);
    } else {
      GetUINativeModule().marquee.setFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}
class MarqueeFontSizeModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol("fontSize");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetFontSize(node);
    }
    else {
      GetUINativeModule().marquee.setFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}
class MarqueeAllowScaleModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('allowScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetAllowScale(node);
    }
    else {
      GetUINativeModule().marquee.setAllowScale(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class MarqueeFontWeightModifier extends ModifierWithKey<string | number | FontWeight> {
  static identity: Symbol = Symbol('fontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().marquee.resetFontWeight(node);
    }
    else {
      let fontWeightStr = 'normal';
      if (typeof this.value === "string") {
        fontWeightStr = this.value;
      } else {
        if (this.value in MarqueeFontWeightMap) {
          fontWeightStr = MarqueeFontWeightMap[this.value];
        }
      }
      GetUINativeModule().marquee.setFontWeight(node, fontWeightStr);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class MarqueeFontFamilyModifier extends ModifierWithKey<string> {
  static identity: Symbol = Symbol('fontFamily');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
        GetUINativeModule().marquee.resetFontFamily(node);
      }
      else {
        GetUINativeModule().marquee.setFontFamily(node, this.value);
      }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
// @ts-ignore
globalThis.Marquee.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkMarqueeComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
