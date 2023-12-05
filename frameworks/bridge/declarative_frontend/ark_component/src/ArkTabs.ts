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
    modifier(this._modifiers, ScrollableModifier, isBoolean(value) ? value : true);
    return this;
  }
  barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): TabsAttribute {
    let barMode: number;
    let arkBarMode: ArkBarMode = new ArkBarMode();
    let arkScrollableBarModeOptions: ArkScrollableBarModeOptions = new ArkScrollableBarModeOptions();
    arkScrollableBarModeOptions.value = options;
    arkBarMode.barMode = barMode;
    arkBarMode.options = arkScrollableBarModeOptions;

    modifier(this._modifiers, ScrollableBarModeOptionsModifier, arkBarMode.options);

    modifier(this._modifiers, TabBarModeModifier, arkBarMode);

    return this;
  }

  barWidth(value: Length): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarWidthModifier.identity, BarWidthModifier, value);
    return this;
  }
  barHeight(value: Length): TabsAttribute {
    if (isUndefined(value) || isNull(value)) {
      return;
    }

    let adaptiveHeight: boolean = false;

    modifier(this._modifiers, BarAdaptiveHeightModifier, adaptiveHeight);
    modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, value);

    return this;
  }
  animationDuration(value: number): TabsAttribute {
    let time: number = isNumber(value) && value > 0 ? value : 300;
    modifier(this._modifiers, AnimationDurationModifier, time);
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
    if (!value) {
      arkDrivider.value.strokeWidth = undefined;
      arkDrivider.value.color = undefined;
      arkDrivider.value.startMargin = undefined;
      arkDrivider.value.endMargin = undefined;
    } else {
      arkDrivider.value = value;
    }

    modifier(this._modifiers, DividerModifier, arkDrivider);

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
    let arkBarGridAlign = new ArkBarGridAlign();
    if (isObject(value)) {
      modifier(this._modifiers, BarGridAlignModifier, arkBarGridAlign);
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
      GetUINativeModule().tabs.setBarGridAlign(node, this.value);
    }
  }
}

class DividerModifier extends Modifier<ArkDivider> {
  static identity: Symbol = Symbol('Divider');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetDivider(node);
    } else {
      GetUINativeModule().tabs.setDivider(node, this.value.value.strokeWidth,
        this.value.value.color, this.value.value.startMargin, this.value.value.endMargin);
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
      GetUINativeModule().tabs.setTabBarMode(node, this.value);
    }
  }
}

class BarPositionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('barPosition');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetBarPosition(node);
    } else {
      GetUINativeModule().tabs.setBarPosition(node, this.value);
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

class ScrollableBarModeOptionsModifier extends Modifier<ArkScrollableBarModeOptions> {
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
