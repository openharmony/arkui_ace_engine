/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class LazyArkSwiperComponent extends ArkComponent {
  static module: SwiperComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkSwiperComponent.module === undefined) {
      LazyArkSwiperComponent.module = globalThis.requireNapi('arkui.components.arkswiper');
    }
    this.lazyComponent = LazyArkSwiperComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
    return this.lazyComponent.allowChildCount();
  }

  initialize(value: Object[]): this {
    this.lazyComponent.initialize(value);
    return this;
  }

  index(value: number): this {
    this.lazyComponent.index(value);
    return this;
  }

  autoPlay(autoPlay: boolean, options: AutoPlayOptions): this {
    this.lazyComponent.autoPlay(autoPlay, options);
    return this;
  }

  interval(value: number): this {
    this.lazyComponent.interval(value);
    return this;
  }

  indicator(value: boolean | DotIndicator | DigitIndicator): this {
    this.lazyComponent.indicator(value);
    return this;
  }

  displayArrow(value: boolean | ArrowStyle, isHoverShow?: boolean | undefined): this {
    this.lazyComponent.displayArrow(value, isHoverShow);
    return this;
  }

  loop(value: boolean): this {
    this.lazyComponent.loop(value);
    return this;
  }

  duration(value: number): this {
    this.lazyComponent.duration(value);
    return this;
  }

  vertical(value: boolean): this {
    this.lazyComponent.vertical(value);
    return this;
  }

  itemSpace(value: string | number): this {
    this.lazyComponent.itemSpace(value);
    return this;
  }

  displayMode(value: SwiperDisplayMode): this {
    this.lazyComponent.displayMode(value);
    return this;
  }

  cachedCount(value: number, isShown?: boolean): this {
    this.lazyComponent.cachedCount(value, isShown);
    return this;
  }

  displayCount(value: string | number | SwiperAutoFill | ItemFillPolicy, swipeByGroup?: boolean | undefined): this {
    this.lazyComponent.displayCount(value, swipeByGroup);
    return this;
  }

  effectMode(value: EdgeEffect): this {
    this.lazyComponent.effectMode(value);
    return this;
  }

  disableSwipe(value: boolean): this {
    this.lazyComponent.disableSwipe(value);
    return this;
  }

  curve(value: string | Curve | ICurve): this {
    this.lazyComponent.curve(value);
    return this;
  }

  onChange(event: (index: number) => void): this {
    this.lazyComponent.onChange(event);
    return this;
  }

  onSelected(event: (index: number) => void): this {
    this.lazyComponent.onSelected(event);
    return this;
  }

  indicatorStyle(value?: IndicatorStyle | undefined): this {
    this.lazyComponent.indicatorStyle(value);
    return this;
  }

  prevMargin(value: Length): this {
    this.lazyComponent.prevMargin(value);
    return this;
  }

  nextMargin(value: Length): this {
    this.lazyComponent.nextMargin(value);
    return this;
  }

  enabled(value: boolean): this {
    this.lazyComponent.enabled(value);
    return this;
  }

  onAnimationStart(event: (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void): this {
    this.lazyComponent.onAnimationStart(event);
    return this;
  }

  onAnimationEnd(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    this.lazyComponent.onAnimationEnd(event);
    return this;
  }

  onGestureSwipe(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    this.lazyComponent.onGestureSwipe(event);
    return this;
  }

  onUnselected(event: (index: number) => void): this {
    this.lazyComponent.onUnselected(event);
    return this;
  }

  nestedScroll(value: SwiperNestedScrollMode): this {
    this.lazyComponent.nestedScroll(value);
    return this;
  }

  indicatorInteractive(value: boolean): this {
    this.lazyComponent.indicatorInteractive(value);
    return this;
  }

  customContentTransition(transition: SwiperContentAnimatedTransition): this {
    this.lazyComponent.customContentTransition(transition);
    return this;
  }

  onContentDidScroll(handler: ContentDidScrollCallback): this {
    this.lazyComponent.onContentDidScroll(handler);
    return this;
  }

  pageFlipMode(value: PageFlipMode): this {
    this.lazyComponent.pageFlipMode(value);
    return this;
  }

  onContentWillScroll(handler: ContentWillScrollCallback): this {
    this.lazyComponent.onContentWillScroll(handler);
    return this;
  }

  maintainVisibleContentPosition(value: boolean): this {
    this.lazyComponent.maintainVisibleContentPosition(value);
    return this;
  }

  onScrollStateChanged(event: Callback<ScrollState>): this {
    this.lazyComponent.onScrollStateChanged(event);
    return this;
  }

  ignoreHiddenItem(value: boolean): this {
    this.lazyComponent.ignoreHiddenItem(value);
    return this;
  }
}

class SwiperModifier extends LazyArkSwiperComponent implements AttributeModifier<SwiperAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: SwiperAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<SwiperAttribute, ArkSwiperComponent, ArkComponent>(instance, this);
  }
}
