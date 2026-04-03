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

class LazyArkMarqueeComponent extends ArkComponent {
  static module: MarqueeComponentModule | undefined = undefined;
  	constructor(nativePtr: KNode, classType: ModifierType) {
  	  super(nativePtr, classType);
  	  if (LazyArkMarqueeComponent.module === undefined) {
  	    LazyArkMarqueeComponent.module = globalThis.requireNapi('arkui.components.arkmarquee');
  	  }
  	  this.lazyComponent = LazyArkMarqueeComponent.module.createComponent(nativePtr, classType);
  	}
  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  fontSize(value: Length): LazyArkMarqueeComponent {
   this.lazyComponent.fontSize(value);
   return this;
  }

  fontColor(value: ResourceColor): LazyArkMarqueeComponent {
   this.lazyComponent.fontColor(value);
   return this;
  }

  allowScale(value: boolean): LazyArkMarqueeComponent {
   this.lazyComponent.allowScale(value);
   return this;
  }

  fontWeight(value: number | FontWeight | string): LazyArkMarqueeComponent {
   this.lazyComponent.fontWeight(value);
   return this;
  }

  fontFamily(value: string | Resource): LazyArkMarqueeComponent {
   this.lazyComponent.fontFamily(value);
   return this;
  }

  onStart(event: () => void): LazyArkMarqueeComponent {
   this.lazyComponent.onStart(event);
   return this;
  }

  onBounce(event: () => void): LazyArkMarqueeComponent {
   this.lazyComponent.onBounce(event);
   return this;
  }

  onFinish(event: () => void): LazyArkMarqueeComponent {
   this.lazyComponent.onFinish(event);
   return this;
  }

  marqueeUpdateStrategy(value: MarqueeUpdateStrategy): LazyArkMarqueeComponent {
   this.lazyComponent.marqueeUpdateStrategy(value);
   return this;
  }
}
class MarqueeModifier extends LazyArkMarqueeComponent implements AttributeModifier<MarqueeAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: MarqueeAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<MarqueeAttribute, ArkMarqueeComponent, ArkComponent>(instance, this);
  }
}
