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

class LazyArkTabsComponent extends ArkComponent {
  static module: TabsComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkTabsComponent.module === undefined) {
      LazyArkTabsComponent.module = globalThis.requireNapi('arkui.components.arktabs');
    }
    this.lazyComponent = LazyArkTabsComponent.module.createComponent(nativePtr, classType);
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

  onAnimationStart(handler: (index: number, targetIndex: number, event: TabsAnimationEvent) => void): this {
    this.lazyComponent.onAnimationStart(handler);
    return this;
  }

  onAnimationEnd(handler: (index: number, event: TabsAnimationEvent) => void): this {
    this.lazyComponent.onAnimationEnd(handler);
    return this;
  }

  onGestureSwipe(handler: (index: number, event: TabsAnimationEvent) => void): this {
    this.lazyComponent.onGestureSwipe(handler);
    return this;
  }

  vertical(value: boolean): this {
    this.lazyComponent.vertical(value);
    return this;
  }

  barPosition(value: BarPosition): this {
    this.lazyComponent.barPosition(value);
    return this;
  }

  scrollable(value: boolean): this {
    this.lazyComponent.scrollable(value);
    return this;
  }

  barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): this {
    this.lazyComponent.barMode(value, options);
    return this;
  }

  barWidth(value: Length): this {
    this.lazyComponent.barWidth(value);
    return this;
  }

  barHeight(value: Length, noMinHeightLimit?: boolean): this {
    this.lazyComponent.barHeight(value, noMinHeightLimit);
    return this;
  }

  animationCurve(value: Curve | ICurve): this {
    this.lazyComponent.animationCurve(value);
    return this;
  }

  animationDuration(value: number): this {
    this.lazyComponent.animationDuration(value);
    return this;
  }

  animationMode(value: AnimationMode): this {
    this.lazyComponent.animationMode(value);
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

  onTabBarClick(event: (index: number) => void): this {
    this.lazyComponent.onTabBarClick(event);
    return this;
  }

  onUnselected(event: (index: number) => void): this {
    this.lazyComponent.onUnselected(event);
    return this;
  }

  onContentDidScroll(handler: OnTabsContentDidScrollCallback | undefined): this {
    this.lazyComponent.onContentDidScroll(handler);
    return this;
  }

  fadingEdge(value: boolean): this {
    this.lazyComponent.fadingEdge(value);
    return this;
  }

  divider(value: DividerStyle | null): this {
    this.lazyComponent.divider(value);
    return this;
  }

  barOverlap(value: boolean): this {
    this.lazyComponent.barOverlap(value);
    return this;
  }

  barBackgroundColor(value: ResourceColor): this {
    this.lazyComponent.barBackgroundColor(value);
    return this;
  }

  barBackgroundBlurStyle(style: BlurStyle, options?: BackgroundBlurStyleOptions): this {
    this.lazyComponent.barBackgroundBlurStyle(style, options);
    return this;
  }

  barBackgroundEffect(options: BackgroundEffectOptions): this {
    this.lazyComponent.barBackgroundEffect(options);
    return this;
  }

  barGridAlign(value: BarGridColumnOptions): this {
    this.lazyComponent.barGridAlign(value);
    return this;
  }

  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    this.lazyComponent.clip(value);
    return this;
  }

  edgeEffect(value: EdgeEffect): this {
    this.lazyComponent.edgeEffect(value);
    return this;
  }

  nestedScroll(value: TabsNestedScrollMode): this {
    this.lazyComponent.nestedScroll(value);
    return this;
  }

  pageFlipMode(value: PageFlipMode): this {
    this.lazyComponent.pageFlipMode(value);
    return this;
  }

  width(value: Length): this {
    this.lazyComponent.width(value);
    return this;
  }

  height(value: Length): this {
    this.lazyComponent.height(value);
    return this;
  }

  cachedMaxCount(count: number, mode: TabsCacheMode): this {
    this.lazyComponent.cachedMaxCount(count, mode);
    return this;
  }

  customContentTransition(delegate: (from: number, to: number) => void): this {
    this.lazyComponent.customContentTransition(delegate);
    return this;
  }

  onContentWillChange(handler: (currentIndex: number, targetIndex: number) => void): this {
    this.lazyComponent.onContentWillChange(handler);
    return this;
  }
}

class TabsModifier extends LazyArkTabsComponent implements AttributeModifier<TabsAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: TabsAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<TabsAttribute, ArkTabsComponent, ArkComponent>(instance, this);
  }
}
