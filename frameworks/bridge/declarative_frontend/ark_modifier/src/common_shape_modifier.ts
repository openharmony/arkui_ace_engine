/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

class LazyArkCommonShapeComponent extends ArkCommonShapeComponent {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  stroke(value: ResourceColor): this {
    this.lazyComponent.stroke(value);
    return this;
  }

  fill(value: ResourceColor): this {
    this.lazyComponent.fill(value);
    return this;
  }

  strokeDashOffset(value: Length): this {
    this.lazyComponent.strokeDashOffset(value);
    return this;
  }

  strokeLineCap(value: LineCapStyle): this {
    this.lazyComponent.strokeLineCap(value);
    return this;
  }

  strokeLineJoin(value: LineJoinStyle): this {
    this.lazyComponent.strokeLineJoin(value);
    return this;
  }

  strokeMiterLimit(value: Length): this {
    this.lazyComponent.strokeMiterLimit(value);
    return this;
  }

  strokeOpacity(value: number | string | Resource): this {
    this.lazyComponent.strokeOpacity(value);
    return this;
  }

  fillOpacity(value: number | string | Resource): this {
    this.lazyComponent.fillOpacity(value);
    return this;
  }

  strokeWidth(value: Length): this {
    this.lazyComponent.strokeWidth(value);
    return this;
  }

  antiAlias(value: boolean): this {
    this.lazyComponent.antiAlias(value);
    return this;
  }

  strokeDashArray(value: any[]): this {
    this.lazyComponent.strokeDashArray(value);
    return this;
  }

  height(value: Length): this {
    this.lazyComponent.height(value);
    return this;
  }

  width(value: Length): this {
    this.lazyComponent.width(value);
    return this;
  }

  foregroundColor(value: string | number | Resource | Color): this {
    this.lazyComponent.foregroundColor(value);
    return this;
  }
}
