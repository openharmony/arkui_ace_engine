/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />

interface TabsOptionsParam {
  barPosition?: BarPosition;
  index?: number;
  controller?: TabsController;
  barModifier?: CommonModifier;
}

class ArkTabsComponent extends ArkComponent implements TabsAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(options: Object[]) {
    if ((options[0] as TabsOptionsParam).barPosition !== undefined) {
      modifierWithKey(this._modifiersWithKeys, BarPositionModifier.identity, BarPositionModifier, options[0].barPosition);
    } else {
      modifierWithKey(this._modifiersWithKeys, BarPositionModifier.identity, BarPositionModifier, undefined);
    }
    if ((options[0] as TabsOptionsParam).index !== undefined) {
      modifierWithKey(this._modifiersWithKeys, TabsOptionsIndexModifier.identity, TabsOptionsIndexModifier, options[0].index);
    } else {
      modifierWithKey(this._modifiersWithKeys, TabsOptionsIndexModifier.identity, TabsOptionsIndexModifier, undefined);
    }
    if ((options[0] as TabsOptionsParam).controller !== undefined) {
      modifierWithKey(this._modifiersWithKeys, TabsOptionsControllerModifier.identity, TabsOptionsControllerModifier, options[0].controller);
    } else {
      modifierWithKey(this._modifiersWithKeys, TabsOptionsControllerModifier.identity, TabsOptionsControllerModifier, undefined);
    }
    if ((options[0] as TabsOptionsParam).barModifier !== undefined) {
      modifierWithKey(this._modifiersWithKeys, TabsOptionsBarModifierModifier.identity, TabsOptionsBarModifierModifier, options[0].barModifier);
    } else {
      modifierWithKey(this._modifiersWithKeys, TabsOptionsBarModifierModifier.identity, TabsOptionsBarModifierModifier, undefined);
    }
    return this;
  }
  onAnimationStart(handler: (index: number, targetIndex: number, event: TabsAnimationEvent) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsAnimationStartModifier.identity, TabsAnimationStartModifier, handler);
    return this;
  }
  onAnimationEnd(handler: (index: number, event: TabsAnimationEvent) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsAnimationEndModifier.identity, TabsAnimationEndModifier, handler);
    return this;
  }
  onGestureSwipe(handler: (index: number, event: TabsAnimationEvent) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsGestureSwipeModifier.identity, TabsGestureSwipeModifier, handler);
    return this;
  }
  vertical(value: boolean): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsVerticalModifier.identity, TabsVerticalModifier, value);
    return this;
  }
  barPosition(value: BarPosition): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarPositionModifier.identity, BarPositionModifier, value);
    return this;
  }
  scrollable(value: boolean): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, ScrollableModifier.identity, ScrollableModifier, value);
    return this;
  }
  barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): TabsAttribute {
    let arkBarMode = new ArkBarMode();
    arkBarMode.barMode = value;
    arkBarMode.options = options;
    modifierWithKey(this._modifiersWithKeys, TabBarModeModifier.identity, TabBarModeModifier, arkBarMode);
    return this;
  }

  barWidth(value: Length): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarWidthModifier.identity, BarWidthModifier, value);

    return this;
  }
  barHeight(value: Length, noMinHeightLimit?: boolean): TabsAttribute {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, undefined);
    } else {
      let adaptiveHeight = false;
      if (value === 'auto') {
        adaptiveHeight = true;
        modifierWithKey(this._modifiersWithKeys, BarAdaptiveHeightModifier.identity, BarAdaptiveHeightModifier, adaptiveHeight);
      } else {
        modifierWithKey(this._modifiersWithKeys, BarAdaptiveHeightModifier.identity, BarAdaptiveHeightModifier, undefined);
      }
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, value);
    }

    if (isNull(noMinHeightLimit) || isUndefined(noMinHeightLimit)) {
      modifierWithKey(this._modifiersWithKeys, NoMinHeightLimitModifier.identity, NoMinHeightLimitModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, NoMinHeightLimitModifier.identity, NoMinHeightLimitModifier, noMinHeightLimit);
    }
    return this;
  }
  animationCurve(value: Curve | ICurve): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsAnimationCurveModifier.identity, TabsAnimationCurveModifier, value);
    return this;
  }
  animationDuration(value: number): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, AnimationDurationModifier.identity, AnimationDurationModifier, value);
    return this;
  }
  animationMode(value: AnimationMode): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, AnimationModeModifier.identity, AnimationModeModifier, value);
    return this;
  }
  onChange(event: (index: number) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsOnChangeModifier.identity, TabsOnChangeModifier, event);
    return this;
  }
  onSelected(event: (index: number) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsOnSelectedModifier.identity, TabsOnSelectedModifier, event);
    return this;
  }
  onTabBarClick(event: (index: number) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsOnTabBarClick.identity, TabsOnTabBarClick, event);
    return this;
  }
  onUnselected(event: (index: number) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsOnUnselectedModifier.identity, TabsOnUnselectedModifier, event);
    return this;
  }
  fadingEdge(value: boolean): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, FadingEdgeModifier.identity, FadingEdgeModifier, value);
    return this;
  }
  divider(value: DividerStyle | null): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsDividerModifier.identity, TabsDividerModifier, value);
    return this;
  }
  barOverlap(value: boolean): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarOverlapModifier.identity, BarOverlapModifier, value);
    return this;
  }
  barBackgroundColor(value: ResourceColor): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarBackgroundColorModifier.identity, BarBackgroundColorModifier, value);
    return this;
  }
  barBackgroundBlurStyle(value: BlurStyle): TabsAttribute {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, BarBackgroundBlurStyleModifier.identity, BarBackgroundBlurStyleModifier, undefined);
      return this;
    }
    let arkBackgroundBlurStyle = new ArkBackgroundBlurStyle();
    arkBackgroundBlurStyle.blurStyle = value;
    modifierWithKey(this._modifiersWithKeys, BarBackgroundBlurStyleModifier.identity, BarBackgroundBlurStyleModifier, arkBackgroundBlurStyle);
    return this;
  }
  barBackgroundBlurStyle(style: BlurStyle, options: BackgroundBlurStyleOptions): TabsAttribute {
    if (isUndefined(style)) {
      modifierWithKey(this._modifiersWithKeys, BarBackgroundBlurStyleModifier.identity, BarBackgroundBlurStyleModifier, undefined);
      return this;
    }
    let arkBackgroundBlurStyle = new ArkBackgroundBlurStyle();
    arkBackgroundBlurStyle.blurStyle = style;
    if (typeof options === 'object') {
      arkBackgroundBlurStyle.colorMode = options.colorMode;
      arkBackgroundBlurStyle.adaptiveColor = options.adaptiveColor;
      arkBackgroundBlurStyle.scale = options.scale;
      arkBackgroundBlurStyle.blurOptions = options.blurOptions;
      arkBackgroundBlurStyle.policy = options.policy;
      arkBackgroundBlurStyle.inactiveColor = options.inactiveColor;
      arkBackgroundBlurStyle.type = options.type;
    }
    modifierWithKey(this._modifiersWithKeys, BarBackgroundBlurStyleModifier.identity, BarBackgroundBlurStyleModifier, arkBackgroundBlurStyle);
    return this;
  }
  barBackgroundEffect(options: BackgroundEffectOptions): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarBackgroundEffectModifier.identity, BarBackgroundEffectModifier, options);
    return this;
  }
  barGridAlign(value: BarGridColumnOptions): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, BarGridAlignModifier.identity, BarGridAlignModifier, value);
    return this;
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, TabClipModifier.identity, TabClipModifier, value);
    return this;
  }
  edgeEffect(value: EdgeEffect): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabEdgeEffectModifier.identity, TabEdgeEffectModifier, value);
    return this;
  }
  pageFlipMode(value: PageFlipMode): this {
    modifierWithKey(this._modifiersWithKeys, TabPageFlipModeModifier.identity, TabPageFlipModeModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TabWidthModifier.identity, TabWidthModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, TabHeightModifier.identity, TabHeightModifier, value);
    return this;
  }
  cachedMaxCount(count: number, mode: TabsCacheMode): this {
    let arkTabsCachedMaxCount = new ArkTabsCachedMaxCount();
    arkTabsCachedMaxCount.count = count;
    arkTabsCachedMaxCount.mode = mode;
    modifierWithKey(this._modifiersWithKeys, CachedMaxCountModifier.identity, CachedMaxCountModifier, arkTabsCachedMaxCount);
    return this;
  }
  customContentTransition(delegate: (from: number, to: number) => void) : TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsCustomContentTransition.identity, TabsCustomContentTransition, delegate);
    return this;
  }
  onContentWillChange(handler: (currentIndex: number, targetIndex: number) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsOnContentWillChange.identity, TabsOnContentWillChange, handler);
    return this;
  }
}

class BarGridAlignModifier extends ModifierWithKey<BarGridColumnOptions> {
  constructor(value: BarGridColumnOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('barGridAlign');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetBarGridAlign(node);
    } else {
      getUINativeModule().tabs.setBarGridAlign(node, this.value.sm,
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

class TabsDividerModifier extends ModifierWithKey<DividerStyle> {
  constructor(value: DividerStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('tabsDivider');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetDivider(node);
    } else {
      getUINativeModule().tabs.setDivider(node, this.value.strokeWidth,
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
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('barWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabBarWidth(node);
    } else {
      getUINativeModule().tabs.setTabBarWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BarAdaptiveHeightModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('barAdaptiveHeight');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetBarAdaptiveHeight(node);
    } else {
      getUINativeModule().tabs.setBarAdaptiveHeight(node, this.value);
    }
  }
}

class NoMinHeightLimitModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('noMinHeightLimit');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetNoMinHeightLimit(node);
    } else {
      getUINativeModule().tabs.setNoMinHeightLimit(node, this.value);
    }
  }
}
class BarHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('barHeight');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabBarHeight(node);
    } else {
      getUINativeModule().tabs.setTabBarHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BarOverlapModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('barOverlap');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetBarOverlap(node);
    } else {
      getUINativeModule().tabs.setBarOverlap(node, this.value);
    }
  }
}

class TabsVerticalModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('vertical');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetIsVertical(node);
    } else {
      getUINativeModule().tabs.setIsVertical(node, this.value);
    }
  }
}

class TabsAnimationCurveModifier extends ModifierWithKey<Curve | ICurve> {
  static identity: Symbol = Symbol('tabsAnimationCurve');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetAnimationCurve(node);
    } else {
      if (typeof this.value === 'number') {
        const curveMap = {
          [0]: 'linear',
          [1]: 'ease',
          [2]: 'ease-in',
          [3]: 'ease-out',
          [4]: 'ease-in-out',
          [5]: 'fast-out-slow-in',
          [6]: 'linear-out-slow-in',
          [7]: 'fast-out-linear-in',
          [8]: 'extreme-deceleration',
          [9]: 'sharp',
          [10]: 'rhythm',
          [11]: 'smooth',
          [12]: 'friction'
        };
        if (this.value in curveMap) {
          this.value = curveMap[this.value];
        } else {
          this.value = this.value.toString();
        }
      }
      getUINativeModule().tabs.setAnimationCurve(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class AnimationDurationModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('animationduration');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetAnimationDuration(node);
    } else {
      getUINativeModule().tabs.setAnimationDuration(node, this.value);
    }
  }
}


class AnimationModeModifier extends ModifierWithKey<AnimationMode> {
  constructor(value: AnimationMode) {
    super(value);
  }
  static identity: Symbol = Symbol('animationMode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetAnimateMode(node);
    } else {
      getUINativeModule().tabs.setAnimateMode(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ScrollableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('scrollable');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetScrollable(node);
    } else {
      getUINativeModule().tabs.setScrollable(node, this.value);
    }
  }
}

class TabBarModeModifier extends ModifierWithKey<ArkBarMode> {
  constructor(value: ArkBarMode) {
    super(value);
  }
  static identity: Symbol = Symbol('tabsbarMode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabBarMode(node);
    } else {
      getUINativeModule().tabs.setTabBarMode(node, this.value.barMode
        , this.value.options?.margin
        , this.value.options?.nonScrollableLayoutStyle);
    }
  }

  checkObjectDiff(): boolean {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.value.barMode === this.stageValue.barMode &&
        this.value.options?.margin === this.stageValue.options?.margin &&
        this.value.options?.nonScrollableLayoutStyle === this.stageValue.options?.nonScrollableLayoutStyle);
    } else {
      return true;
    }
  }
}

class BarPositionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('barPosition');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabBarPosition(node);
    } else {
      getUINativeModule().tabs.setTabBarPosition(node, this.value);
    }
  }
}

class TabsOptionsIndexModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('tabsOptionsIndex');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOptionsIndex(node);
    } else {
      getUINativeModule().tabs.setTabsOptionsIndex(node, this.value);
    }
  }
}

class TabsOptionsControllerModifier extends ModifierWithKey<TabsController> {
  constructor(value: TabsController) {
    super(value);
  }
  static identity: Symbol = Symbol('tabsOptionsController');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOptionsController(node);
    } else {
      getUINativeModule().tabs.setTabsOptionsController(node, this.value);
    }
  }
}

class TabsOptionsBarModifierModifier extends ModifierWithKey<CommonModifier> {
  constructor(value: CommonModifier) {
    super(value);
  }
  static identity: Symbol = Symbol('tabsOptionsBarModifier');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOptionsBarModifier(node);
    } else {
      getUINativeModule().tabs.setTabsOptionsBarModifier(node, this.value);
    }
  }
}

class TabsHideTitleBarModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('hideTitleBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetHideTitleBar(node);
    } else {
      getUINativeModule().tabs.setHideTitleBar(node, this.value);
    }
  }
}

class BarBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('barbackgroundcolor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetBarBackgroundColor(node);
    } else {
      getUINativeModule().tabs.setBarBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class BarBackgroundBlurStyleModifier extends ModifierWithKey<ArkBackgroundBlurStyle> {
  constructor(value: ArkBackgroundBlurStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('barbackgroundblurstyle');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetBarBackgroundBlurStyle(node);
    } else {
      getUINativeModule().tabs.setBarBackgroundBlurStyle(node,
        this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale,
        this.value.blurOptions?.grayscale, this.value.policy, this.value.inactiveColor, this.value.type);
    }
  }
}

class BarBackgroundEffectModifier extends ModifierWithKey<BackgroundEffectOptions> {
  constructor(options: BackgroundEffectOptions) {
    super(options);
  }
  static identity: Symbol = Symbol('barBackgroundEffect');
  applyPeer(node: KNode, reset: boolean): void {
    let _a;
    if (reset) {
      getUINativeModule().tabs.resetBarBackgroundEffect(node);
    } else {
      getUINativeModule().tabs.setBarBackgroundEffect(node, this.value.radius, this.value.saturation,
        this.value.brightness, this.value.color, this.value.adaptiveColor,
        (_a = this.value.blurOptions) === null || _a === void 0 ? void 0 : _a.grayscale,
        this.value.policy, this.value.inactiveColor, this.value.type);
    }
  }

  checkObjectDiff(): boolean {
    let _a;
    let _b;
    return !(this.value.radius === this.stageValue.radius && this.value.saturation === this.stageValue.saturation &&
      this.value.brightness === this.stageValue.brightness &&
      isBaseOrResourceEqual(this.stageValue.color, this.value.color) &&
      this.value.adaptiveColor === this.stageValue.adaptiveColor &&
      this.value.policy === this.stageValue.policy &&
      this.value.inactiveColor === this.stageValue.inactiveColor &&
      this.value.type === this.stageValue.type &&
      ((_a = this.value.blurOptions) === null || _a === void 0 ? void 0 : _a.grayscale) === ((_b = this.stageValue.blurOptions) === null ||
      _b === void 0 ? void 0 : _b.grayscale));
  }
}

class TabsOnUnselectedModifier extends ModifierWithKey<Callback<number>> {
  constructor(value: Callback<number>) {
    super(value);
  }
  static identity: Symbol = Symbol('tabOnUnselected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabOnUnselected(node);
    } else {
      getUINativeModule().tabs.setTabOnUnselected(node, this.value);
    }
  }
}

class FadingEdgeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('fadingedge');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetFadingEdge(node);
    } else {
      getUINativeModule().tabs.setFadingEdge(node, this.value);
    }
  }
}

class TabClipModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('tabclip');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabClip(node);
    } else {
      getUINativeModule().tabs.setTabClip(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return true;
  }
}

class TabEdgeEffectModifier extends ModifierWithKey<EdgeEffect> {
  constructor(value: EdgeEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('tabedgeEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabEdgeEffect(node);
    } else {
      getUINativeModule().tabs.setTabEdgeEffect(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TabPageFlipModeModifier extends ModifierWithKey<PageFlipMode> {
  constructor(value: PageFlipMode) {
    super(value);
  }
  static identity: Symbol = Symbol('tabPageFlipMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabPageFlipMode(node);
    } else {
      getUINativeModule().tabs.setTabPageFlipMode(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TabWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('tabWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabWidth(node);
    } else {
      getUINativeModule().tabs.setTabWidth(node, this.value);
    }
  }
}

class TabHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('tabHeight');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabHeight(node);
    } else {
      getUINativeModule().tabs.setTabHeight(node, this.value);
    }
  }
}

class TabsOnSelectedModifier extends ModifierWithKey<Callback<number>> {
  constructor(value: Callback<number>) {
    super(value);
  }
  static identity: Symbol = Symbol('tabsOnSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOnSelected(node);
    } else {
      getUINativeModule().tabs.setTabsOnSelected(node, this.value);
    }
  }
}

class CachedMaxCountModifier extends ModifierWithKey<ArkTabsCachedMaxCount> {
  constructor(value: ArkTabsCachedMaxCount) {
    super(value);
  }
  static identity: Symbol = Symbol('cachedMaxCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetCachedMaxCount(node);
    } else {
      getUINativeModule().tabs.setCachedMaxCount(node, this.value.count, this.value.mode);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.value.count === this.stageValue.count && this.value.mode === this.stageValue.mode);
  }
}

class TabsOnChangeModifier extends ModifierWithKey<(index: number) => void> {
  constructor(value: (index: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onChange');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOnChange(node);
    } else {
      getUINativeModule().tabs.setTabsOnChange(node, this.value);
    }
  }
}

class TabsOnTabBarClick extends ModifierWithKey<(index: number) => void> {
  constructor(value: (index: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onTabBarClick');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOnTabBarClick(node);
    } else {
      getUINativeModule().tabs.setTabsOnTabBarClick(node, this.value);
    }
  }
}

class TabsAnimationStartModifier extends ModifierWithKey<(index: number, targetIndex: number, event: TabsAnimationEvent) => void> {
  constructor(value: (index: number, targetIndex: number, event: TabsAnimationEvent) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onAnimationStart');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOnAnimationStart(node);
    } else {
      getUINativeModule().tabs.setTabsOnAnimationStart(node, this.value);
    }
  }
}    

class TabsAnimationEndModifier extends ModifierWithKey<(index: number, event: TabsAnimationEvent) => void> {
  constructor(value: (index: number, event: TabsAnimationEvent) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onAnimationEnd');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOnAnimationEnd(node);
    } else {
      getUINativeModule().tabs.setTabsOnAnimationEnd(node, this.value);
    }
  }
}

class TabsGestureSwipeModifier extends ModifierWithKey<(index: number, event: TabsAnimationEvent) => void> {
  constructor(value: (index: number, event: TabsAnimationEvent) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onGestureSwipe');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOnGestureSwipe(node);
    } else {
      getUINativeModule().tabs.setTabsOnGestureSwipe(node, this.value);
    }
  }
}

class TabsOnContentWillChange extends ModifierWithKey<(currentIndex: number, targetIndex: number) => void> {
  constructor(value: (currentIndex: number, targetIndex: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onContentWillChange');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsOnContentWillChange(node);
    } else {
      getUINativeModule().tabs.setTabsOnContentWillChange(node, this.value);
    }
  }
} 

class TabsCustomContentTransition extends ModifierWithKey<(from: number, to: number) => void> {
  constructor(value: (from: number, to: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('ccustomContentTransition');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().tabs.resetTabsCustomContentTransition(node);
    } else {
      getUINativeModule().tabs.setTabsCustomContentTransition(node, this.value);
    }
  }
} 


// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTabsComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TabsModifier(nativePtr, classType);
  });
};

globalThis.Tabs.onChange = function (value: (index: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsOnChange(nodePtr, value);
};
globalThis.Tabs.onTabBarClick = function (value: (index: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsOnTabBarClick(nodePtr, value);
};
globalThis.Tabs.onSelected = function (value: Callback<number>): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsOnSelected(nodePtr, value);
};
globalThis.Tabs.onUnselected = function (value: Callback<number>): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabOnUnselected(nodePtr, value);
};
globalThis.Tabs.onAnimationStart = function (value: (index: number, targetIndex: number, event: TabsAnimationEvent) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsOnAnimationStart(nodePtr, value);
};
globalThis.Tabs.onAnimationEnd = function (value: (index: number, event: TabsAnimationEvent) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsOnAnimationEnd(nodePtr, value);
};
globalThis.Tabs.onGestureSwipe = function (value: (index: number, event: TabsAnimationEvent) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsOnGestureSwipe(nodePtr, value);
};
globalThis.Tabs.customContentTransition = function (value: (from: number, to: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsCustomContentTransition(nodePtr, value);
};
globalThis.Tabs.onContentWillChange = function (value: (currentIndex: number, targetIndex: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().tabs.setTabsOnContentWillChange(nodePtr, value);
};
