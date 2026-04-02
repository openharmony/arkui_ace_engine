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

class LazyArkWaterFlowComponent extends ArkScrollable {
  static module: WaterFlowComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkWaterFlowComponent.module === undefined) {
     LazyArkWaterFlowComponent.module = globalThis.requireNapi('arkui.components.arkwaterflow');
   }

   this.lazyComponent = LazyArkWaterFlowComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value) {
    this.lazyComponent.initialize(value);
    return this;
  }

  columnsGap(value: Length): this {
   this.lazyComponent.columnsGap(value);
   return this;
  }

  rowsGap(value: Length): this {
   this.lazyComponent.rowsGap(value);
   return this;
  }

  layoutDirection(value: FlexDirection): this {
   this.lazyComponent.layoutDirection(value);
   return this;
  }

  columnsTemplate(value: string): this {
   this.lazyComponent.columnsTemplate(value);
   return this;
  }

  itemConstraintSize(value: ConstraintSizeOptions): this {
   this.lazyComponent.itemConstraintSize(value);
   return this;
  }

  rowsTemplate(value: string): this {
   this.lazyComponent.rowsTemplate(value);
   return this;
  }

  nestedScroll(value: NestedScrollOptions): this {
   this.lazyComponent.nestedScroll(value);
   return this;
  }

  enableScrollInteraction(value: boolean): this {
   this.lazyComponent.enableScrollInteraction(value);
   return this;
  }

  friction(value: number | Resource): this {
   this.lazyComponent.friction(value);
   return this;
  }

  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
   this.lazyComponent.clip(value);
   return this;
  }

  cachedCount(count: number, show?: boolean): this {
   this.lazyComponent.cachedCount(count, show);
   return this;
  }

  edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this {
   this.lazyComponent.edgeEffect(edgeEffect, options);
   return this;
  }

  syncLoad(value: boolean): this {
   this.lazyComponent.syncLoad(value);
   return this;
  }

  scrollBar(value: BarState): this {
   this.lazyComponent.scrollBar(value);
   return this;
  }

  scrollBarWidth(value: string | number): this {
   this.lazyComponent.scrollBarWidth(value);
   return this;
  }

  scrollBarColor(value: string | number | Color | Resource): this {
   this.lazyComponent.scrollBarColor(value);
   return this;
  }

  onScroll(value: (scrollOffset: number, scrollState: ScrollState) => void): this {
   this.lazyComponent.onScroll(value);
   return this;
  }

  onScrollStart(value: () => void): this {
   this.lazyComponent.onScrollStart(value);
   return this;
  }

  onScrollStop(value: () => void): this {
   this.lazyComponent.onScrollStop(value);
   return this;
  }

  onScrollIndex(value: (first: number, last: number) => void): this {
   this.lazyComponent.onScrollIndex(value);
   return this;
  }

  onReachStart(value: () => void): this {
   this.lazyComponent.onReachStart(value);
   return this;
  }

  onReachEnd(value: () => void): this {
   this.lazyComponent.onReachEnd(value);
   return this;
  }

  onScrollFrameBegin(value: OnScrollFrameBeginCallback): this {
   this.lazyComponent.onScrollFrameBegin(value);
   return this;
  }

  remoteMessage(value: Object): this {
   this.lazyComponent.remoteMessage(value);
   return this;
  }

  onClick(value: (event: ClickEvent) => void): this {
   this.lazyComponent.onClick(value);
   return this;
  }

  onTouch(value: (event: TouchEvent) => void): this {
   this.lazyComponent.onTouch(value);
   return this;
  }

  onHover(value: (isHover: boolean, event: HoverEvent) => void): this {
   this.lazyComponent.onHover(value);
   return this;
  }

  onKeyEvent(value: (event: KeyEvent) => void): this {
   this.lazyComponent.onKeyEvent(value);
   return this;
  }

  onDeleteEvent(value: (event: KeyEvent) => void): this {
   this.lazyComponent.onDeleteEvent(value);
   return this;
  }

  onAttach(value: () => void): this {
   this.lazyComponent.onAttach(value);
   return this;
  }

  onAppear(value: () => void): this {
   this.lazyComponent.onAppear(value);
   return this;
  }

  onDetach(value: () => void): this {
   this.lazyComponent.onDetach(value);
   return this;
  }

  onDisAppear(value: () => void): this {
   this.lazyComponent.onDisAppear(value);
   return this;
  }

  attributeModifier(modifier: AttributeModifier<WaterFlowAttribute>): this {
   this.lazyComponent.attributeModifier(modifier);
   return this;
  }

  onWillStopDragging(value: (event: DragEvent) => void): this {
   this.lazyComponent.onWillStopDragging(value);
   return this;
  }

  onWillStartDragging(value: (event: DragEvent) => void): this {
   this.lazyComponent.onWillStartDragging(value);
   return this;
  }

  onDidStopDragging(value: (event: DragEvent) => void): this {
   this.lazyComponent.onDidStopDragging(value);
   return this;
  }

  onWillStartFling(value: (event: any) => void): this {
   this.lazyComponent.onWillStartFling(value);
   return this;
  }

  onDidStopFling(value: (event: any) => void): this {
   this.lazyComponent.onDidStopFling(value);
   return this;
  }
}class WaterFlowModifier extends LazyArkWaterFlowComponent implements AttributeModifier<WaterFlowAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: WaterFlowAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<WaterFlowAttribute, ArkWaterFlowComponent, ArkComponent>(instance, this);
  }
}
