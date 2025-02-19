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
class ArkTabsComponent extends ArkComponent implements TabsAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
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
  barHeight(value: Length): TabsAttribute {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, undefined);
    } else {
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, value);
    }

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
    throw new Error('Method not implemented.');
  }
  onSelected(event: (index: number) => void): TabsAttribute {
    modifierWithKey(this._modifiersWithKeys, TabsOnSelectedModifier.identity, TabsOnSelectedModifier, event);
    return this;
  }
  onTabBarClick(event: (index: number) => void): TabsAttribute {
    throw new Error('Method not implemented.');
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
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
      getUINativeModule().swiper.resetTabOnUnselected(node);
    } else {
      getUINativeModule().swiper.setTabOnUnselected(node, this.value);
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

// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkTabsComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TabsModifier(nativePtr, classType);
  });
};
