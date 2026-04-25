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

class LazyArkPatternLockComponent extends ArkComponent {
  static module: PatternLockComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkPatternLockComponent.module === undefined) {
     LazyArkPatternLockComponent.module = globalThis.requireNapi('arkui.components.arkpatternlock');
   }

   this.lazyComponent = LazyArkPatternLockComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  sideLength(value: Length): LazyArkPatternLockComponent {
   this.lazyComponent.sideLength(value);
   return this;
  }

  circleRadius(value: Length): LazyArkPatternLockComponent {
   this.lazyComponent.circleRadius(value);
   return this;
  }

  regularColor(value: ResourceColor): LazyArkPatternLockComponent {
   this.lazyComponent.regularColor(value);
   return this;
  }

  selectedColor(value: ResourceColor): LazyArkPatternLockComponent {
   this.lazyComponent.selectedColor(value);
   return this;
  }

  activeColor(value: ResourceColor): LazyArkPatternLockComponent {
   this.lazyComponent.activeColor(value);
   return this;
  }

  pathColor(value: ResourceColor): LazyArkPatternLockComponent {
   this.lazyComponent.pathColor(value);
   return this;
  }

  pathStrokeWidth(value: number | string): LazyArkPatternLockComponent {
   this.lazyComponent.pathStrokeWidth(value);
   return this;
  }

  autoReset(value: boolean): LazyArkPatternLockComponent {
   this.lazyComponent.autoReset(value);
   return this;
  }

  activateCircleStyle(value: Optional<CircleStyleOptions>): LazyArkPatternLockComponent {
   this.lazyComponent.activateCircleStyle(value);
   return this;
  }

  skipUnselectedPoint(value: boolean): LazyArkPatternLockComponent {
   this.lazyComponent.skipUnselectedPoint(value);
   return this;
  }

  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }

  onPatternComplete(callback: (input: Array<number>) => void): LazyArkPatternLockComponent {
   this.lazyComponent.onPatternComplete(callback);
   return this;
  }

  onDotConnect(callback: Callback<number>): this {
   this.lazyComponent.onDotConnect(callback);
   return this;
  }
}

class PatternLockModifier extends LazyArkPatternLockComponent implements AttributeModifier<PatternLockAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: PatternLockAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<PatternLockAttribute, ArkPatternLockComponent, ArkComponent>(instance, this);
  }
}
