/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

class LazyArkImageSpanComponent extends ArkComponent {
  static module: ImageSpanComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkImageSpanComponent.module === undefined) {
     LazyArkImageSpanComponent.module = globalThis.requireNapi('arkui.components.arkimagespan');
   }

   this.lazyComponent = LazyArkImageSpanComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value: [Resource | undefined]): LazyArkImageSpanComponent {
   this.lazyComponent.initialize(value);
   return this;
  }

  alt(value: PixelMap): LazyArkImageSpanComponent {
    this.lazyComponent.alt(value);
    return this;
  }

  objectFit(value: ImageFit): LazyArkImageSpanComponent {
    this.lazyComponent.objectFit(value);
    return this;
  }

  verticalAlign(value: ImageSpanAlignment): LazyArkImageSpanComponent {
    this.lazyComponent.verticalAlign(value);
    return this;
  }

  textBackgroundStyle(value: TextBackgroundStyle): LazyArkImageSpanComponent {
    this.lazyComponent.textBackgroundStyle(value);
    return this;
  }

  onComplete(callback: (result: {
      width: number;
      height: number;
      componentWidth: number;
      componentHeight: number;
      loadingStatus: number;
      contentWidth: number;
      contentHeight: number;
      contentOffsetX: number;
      contentOffsetY: number;
    }) => void): LazyArkImageSpanComponent {
    this.lazyComponent.onComplete(callback);
    return this;
  }

  onError(callback: (error: {
    componentWidth: number;
    componentHeight: number;
    message: string
  }) => void): LazyArkImageSpanComponent {
    this.lazyComponent.onError(callback);
    return this;
  }

  borderRadius(value: Length | BorderRadiuses): this {
    this.lazyComponent.borderRadius(value);
    return this;
  }

  colorFilter(value: ColorFilter | DrawingColorFilter): LazyArkImageSpanComponent {
    this.lazyComponent.colorFilter(value);
    return this;
  }

  baselineOffset(value: LengthMetrics): LazyArkImageSpanComponent {
    this.lazyComponent.baselineOffset(value);
    return this;
  }

  supportSvg2(value: boolean): LazyArkImageSpanComponent {
    this.lazyComponent.supportSvg2(value);
    return this;
  }
}

class ImageSpanModifier extends LazyArkImageSpanComponent implements AttributeModifier<ImageSpanAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ImageSpanAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<ImageSpanAttribute, ArkImageSpanComponent, ArkComponent>(instance, this);
  }
}
