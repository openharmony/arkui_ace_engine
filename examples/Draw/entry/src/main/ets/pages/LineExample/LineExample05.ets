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

class MyLineModifier implements AttributeModifier<LineAttribute> {
  applyNormalAttribute(instance: LineAttribute): void {
    // 一个起始点为（10, 10），终点为（120, 10）的直线，边框颜色#2787D9，边框间隙[20]，向左偏移15，线条两端样式为半圆，边框透明度0.5，边框宽度10，抗锯齿开启
    instance.startPoint([10, 10])
    instance.endPoint([120, 10])
    instance.stroke("#2787D9")
    instance.strokeDashArray([20])
    instance.strokeDashOffset("15")
    instance.strokeLineCap(LineCapStyle.Round)
    instance.strokeOpacity(0.5)
    instance.strokeWidth(10)
    instance.antiAlias(true)
  }
}

@Entry
@Component
struct LineExample05 {
  @State modifier: MyLineModifier = new MyLineModifier()

  build() {
    Column() {
      Line()
        .attributeModifier(this.modifier)
        .offset({ x: 20, y: 20 })
    }
  }
}