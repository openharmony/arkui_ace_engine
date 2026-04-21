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

class LazyArkRatingComponent extends ArkComponent {
  static module: RatingComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkRatingComponent.module === undefined) {
     LazyArkRatingComponent.module = globalThis.requireNapi('arkui.components.arkrating');
   }

   this.lazyComponent = LazyArkRatingComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value) {
    this.lazyComponent.initialize(value);
    return this;
  }

  stars(value: number): this {
   this.lazyComponent.stars(value);
   return this;
  }

  stepSize(angle: number): this {
   this.lazyComponent.stepSize(angle);
   return this;
  }

  starStyle(angle: StarStyleOptions): this {
   this.lazyComponent.starStyle(angle);
   return this;
  }

  onChange(angle: OnRatingChangeCallback): this {
   this.lazyComponent.onChange(angle);
   return this;
  }

  contentModifier(value: ContentModifier<RatingConfiguration>): this {
   this.lazyComponent.contentModifier(value);
   return this;
  }
}
class RatingModifier extends LazyArkRatingComponent implements AttributeModifier<RatingAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: RatingAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<RatingAttribute, ArkRatingComponent, ArkComponent>(instance, this);
  }
}
