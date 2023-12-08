/// <reference path='./import.ts' />
class ArkTabsComponent extends ArkComponent implements TabsAttribute {
  onAnimationStart(handler: (index: number, targetIndex: number, event: TabsAnimationEvent) => void): TabsAttribute {
    throw new Error('Method not implemented.');
  }
  onAnimationEnd(handler: (index: number, event: TabsAnimationEvent) => void): TabsAttribute {
    throw new Error('Method not implemented.');
  }
  onGestureSwipe(handler: (index: number, event: TabsAnimationEvent) => void): TabsAttribute {
    throw new Error('Method not implemented.');
  }
  vertical(value: boolean): TabsAttribute {
    modifier(this._modifiers, TabsVerticalModifier, value);
    return this;
  }
  barPosition(value: BarPosition): TabsAttribute {
      modifier(this._modifiers, BarPositionModifier, value);
    return this;
  }
  scrollable(value: boolean): TabsAttribute {
    modifier(this._modifiers, ScrollableModifier, value);
    return this;
  }
  barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, ScrollableBarModeOptionsModifier.identity,
      ScrollableBarModeOptionsModifier, options);
    modifierWithKey(this._modifiersWithKeys, TabBarModeModifier.identity, TabBarModeModifier, value);

    return this;
  }

  barWidth(value: Length): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarWidthModifier.identity, BarWidthModifier, value);

    return this;
  }
  barHeight(value: Length): TabsAttribute {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, value);
    }

    return this;
  }
  animationDuration(value: number): TabsAttribute {
    modifier(this._modifiers, AnimationDurationModifier, value);
    return this;
  }
  onChange(event: (index: number) => void): TabsAttribute {
    throw new Error('Method not implemented.');
  }
  onTabBarClick(event: (index: number) => void): TabsAttribute {
    throw new Error('Method not implemented.');
  }
  fadingEdge(value: boolean): TabsAttribute {
    modifier(this._modifiers, FadingEdgeModifier, value);
    return this;
  }
  divider(value: DividerStyle | null): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerModifier.identity, DividerModifier, value);
    return this;
  }
  barOverlap(value: boolean): TabsAttribute {
    modifier(this._modifiers, BarOverlapModifier, value);
    return this;
  }
  barBackgroundColor(value: ResourceColor): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarBackgroundColorModifier.identity, BarBackgroundColorModifier, value);
    return this;
  }
  barGridAlign(value: BarGridColumnOptions): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarGridAlignModifier.identity, BarGridAlignModifier, value);
    return this;
  }
}

class BarGridAlignModifier extends ModifierWithKey<BarGridColumnOptions> {
  static identity: Symbol = Symbol('barGridAlign');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetBarGridAlign(node);
    } else {
      GetUINativeModule().tabs.setBarGridAlign(node, this.value.sm,
        this.value.md, this.value.lg, this.value.gutter, this.value.margin);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.stageValue.sm === this.value.sm &&
      this.stageValue.md === this.value.md &&
      this.stageValue.lg === this.value.lg &&
      this.stageValue.gutter === this.value.gutter &&
      this.stageValue.margin === this.value.margin);
  }
}

class DividerModifier extends ModifierWithKey<DividerStyle> {
  static identity: Symbol = Symbol('Divider');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetDivider(node);
    } else {
      GetUINativeModule().tabs.setDivider(node, this.value.strokeWidth,
        this.value.color, this.value.startMargin, this.value.endMargin);
    }
  }

  checkObjectDiff(): boolean {
      return !(this.stageValue.strokeWidth === this.value.strokeWidth &&
        this.stageValue.color === this.value.color &&
        this.stageValue.startMargin === this.value.startMargin &&
        this.stageValue.endMargin === this.value.endMargin);
  }
}

class BarWidthModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('barWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetTabBarWidth(node);
    } else {
      GetUINativeModule().tabs.setTabBarWidth(node, this.value);
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

class BarAdaptiveHeightModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('barAdaptiveHeight');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetBarAdaptiveHeight(node);
    } else {
      GetUINativeModule().tabs.setBarAdaptiveHeight(node, this.value);
    }
  }
}

class BarHeightModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('barHeight');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetTabBarHeight(node);
    } else {
      GetUINativeModule().tabs.setTabBarHeight(node, this.value);
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

class BarOverlapModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('barOverlap');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetBarOverlap(node);
    } else {
      GetUINativeModule().tabs.setBarOverlap(node, this.value);
    }
  }
}

class TabsVerticalModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('vertical');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetIsVertical(node);
    } else {
      GetUINativeModule().tabs.setIsVertical(node, this.value);
    }
  }
}

class AnimationDurationModifier extends Modifier<number> {
  static identity: Symbol = Symbol('animationduration');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetAnimationDuration(node);
    } else {
      GetUINativeModule().tabs.setAnimationDuration(node, this.value);
    }
  }
}

class ScrollableModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('scrollable');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetScrollable(node);
    } else {
      GetUINativeModule().tabs.setScrollable(node, this.value);
    }
  }
}

class TabBarModeModifier extends ModifierWithKey<BarMode> {
  static identity: Symbol = Symbol('tabsbarMode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetTabBarMode(node);
    } else {
      GetUINativeModule().tabs.setTabBarMode(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.stageValue === this.value);
  }
}

class BarPositionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('barPosition');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetTabBarPosition(node);
    } else {
      GetUINativeModule().tabs.setTabBarPosition(node, this.value);
    }
  }
}

class TabsHideTitleBarModifier extends Modifier<string> {
  static identity: Symbol = Symbol('hideTitleBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetHideTitleBar(node);
    } else {
      GetUINativeModule().tabs.setHideTitleBar(node, this.value);
    }
  }
}

class BarBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('barbackgroundcolor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetBarBackgroundColor(node);
    } else {
      GetUINativeModule().tabs.setBarBackgroundColor(node, this.value);
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

class FadingEdgeModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('fadingedge');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetFadingEdge(node);
    } else {
      GetUINativeModule().tabs.setFadingEdge(node, this.value);
    }
  }
}

class ScrollableBarModeOptionsModifier extends ModifierWithKey<ScrollableBarModeOptions> {
  static identity: Symbol = Symbol('tabsscrollableBarModeOptions');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetScrollableBarModeOptions(node);
    } else {
      GetUINativeModule().tabs.setScrollableBarModeOptions(
        node,
        this.value['margin'],
        this.value['nonScrollableLayoutStyle']
      );
    }
  }

  checkObjectDiff(): boolean {
    return !(this.stageValue.margin === this.value.margin &&
      this.stageValue.nonScrollableLayoutStyle === this.value.nonScrollableLayoutStyle);
  }

}

// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTabsComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
};
