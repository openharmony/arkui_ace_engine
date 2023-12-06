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
    if (isNumber(value) && value >= BarPosition.Start && value <= BarPosition.End) {
      modifier(this._modifiers, BarPositionModifier, value);
    } else {
      modifier(this._modifiers, BarPositionModifier, BarPosition.Start);
    }
    return this;
  }
  scrollable(value: boolean): TabsAttribute {
    modifier(this._modifiers, ScrollableModifier, value);
    return this;
  }
  barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): TabsAttribute {
    let arkBarMode: ArkBarMode = new ArkBarMode();
    arkBarMode.barMode = value;
    arkBarMode.options = options;

    modifier(this._modifiers, TabBarModeModifier, arkBarMode);

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
    let arkDrivider = new ArkDivider();
    if (!!value) {
      arkDrivider.divider.strokeWidth = value?.strokeWidth;
      arkDrivider.divider.color = value?.color;
      arkDrivider.divider.startMargin = value?.startMargin;
      arkDrivider.divider.endMargin = value?.endMargin;
      modifier(this._modifiers, DividerModifier, arkDrivider);
    } else {
      modifier(this._modifiers, DividerModifier, undefined);
    }

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
    if (isObject(value)) {
      let arkBarGridAlign = new ArkBarGridAlign();
      arkBarGridAlign.barGridAlign = value;
      modifier(this._modifiers, BarGridAlignModifier, arkBarGridAlign);
    } else {
      modifier(this._modifiers, BarGridAlignModifier, undefined);
    }

    return this;
  }
}

class BarGridAlignModifier extends Modifier<ArkBarGridAlign> {
  static identity: Symbol = Symbol('barGridAlign');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetBarGridAlign(node);
    } else {
      GetUINativeModule().tabs.setBarGridAlign(node, this.value.barGridAlign.sm
        , this.value.barGridAlign?.md
        , this.value.barGridAlign?.lg
        , this.value.barGridAlign?.margin
        , this.value.barGridAlign?.gutter);
    }
  }
}

class DividerModifier extends Modifier<ArkDivider> {
  static identity: Symbol = Symbol('Divider');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetDivider(node);
    } else {
      GetUINativeModule().tabs.setDivider(node, this.value.divider.strokeWidth
        , this.value.divider.color
        , this.value.divider.startMargin
        , this.value.divider.endMargin);
    }
  }
}

class BarWidthModifier extends Modifier<Length> {
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

class BarHeightModifier extends Modifier<Length> {
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

class TabBarModeModifier extends Modifier<ArkBarMode> {
  static identity: Symbol = Symbol('tabsbarMode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetTabBarMode(node);
    } else {
      GetUINativeModule().tabs.setTabBarMode(node, this.value.barMode,
        this.value.options?.margin,
        this.value.options?.nonScrollableLayoutStyle);
    }
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

class BarBackgroundColorModifier extends Modifier<ResourceColor> {
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
