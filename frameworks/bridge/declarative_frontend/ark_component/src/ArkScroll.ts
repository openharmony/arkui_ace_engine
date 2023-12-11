/// <reference path='./import.ts' />
class ArkScrollComponent extends ArkComponent implements ScrollAttribute {
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  scrollable(value: ScrollDirection): this {
    modifierWithKey(this._modifiersWithKeys, ScrollScrollableModifier.identity, ScrollScrollableModifier, value);
    return this;
  }
  onScroll(event: (xOffset: number, yOffset: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollEdge(event: (side: Edge) => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollEnd(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollStop(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  scrollBar(barState: BarState): this {
    throw new Error('Method not implemented.');
  }
  scrollBarColor(color: any): this {
    modifierWithKey(this._modifiersWithKeys, ScrollScrollBarColorModifier.identity,ScrollScrollBarColorModifier, arkColor.color);
    return this;
  }
  scrollBarWidth(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, ScrollScrollBarWidthModifier.identity, ScrollScrollBarWidthModifier, value);
    return this;
  }
  edgeEffect(edgeEffect: EdgeEffect): this {
    modifierWithKey(this._modifiersWithKeys,ScrollEdgeEffectModifier.identity,ScrollEdgeEffectModifier,edgeEffect);
    return this;
  }
  onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value: NestedScrollOptions): this {
    throw new Error('Method not implemented.');
  }
  enableScrollInteraction(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  friction(value: any): this {
    throw new Error('Method not implemented.');
  }
  scrollSnap(value: ScrollSnapOptions): this {
    throw new Error('Method not implemented.');
  }
}
class ScrollScrollableModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('scrollable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().scroll.resetScrollable(node);
    }
    else {
      GetUINativeModule().scroll.setScrollable(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ScrollEdgeEffectModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol("edgeEffect");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().scroll.resetEdgeEffect(node);
    }
    else {
      GetUINativeModule().scroll.setEdgeEffect(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ScrollScrollBarWidthModifier extends ModifierWithKey<string | number> {
  static identity: Symbol = Symbol('scrollBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().scroll.resetScrollBarWidth(node);
    }
    else {
      let barWidthStr = '0';
      if (typeof this.value === 'string') {
        barWidthStr = this.value;
      } else {
        barWidthStr = String(this.value);
        }
      GetUINativeModule().scroll.setScrollBarWidth(node, barWidthStr);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ScrollScrollBarColorModifier extends ModifierWithKey<number | undefined> {
  static identity: Symbol = Symbol('scrollBarColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().scroll.resetScrollBarColor(node);
    }
    else {
      GetUINativeModule().scroll.setScrollBarColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
// @ts-ignore
globalThis.Scroll.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkScrollComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
