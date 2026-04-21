/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct LayoutExample4 {
  @Builder
  ColumnChildrenText() {
    Text('=====Text=====Text=====Text=====Text=====Text=====Text=====Text=====Text' )
      .fontSize(16).fontColor(Color.Black)
      .borderWidth(2).backgroundColor('#fff8dc')
      .width(LayoutPolicy.fixAtIdealSize) // 设置子组件宽度不受到父组件限制。
      .height(LayoutPolicy.fixAtIdealSize)  // 设置子组件高度不受到父组件限制。
  }

  build() {
    Column() {
      Column() {
        CustomLayoutText({ builder: this.ColumnChildrenText })
          .backgroundColor('#f0ffff').borderRadius(20).margin(10)
      }
      .width(300)
      .height(150)
      .margin(10)
      .backgroundColor(Color.Pink)
    }
    .width(350)
    .height(680)
    .margin(20)
    .alignItems(HorizontalAlign.Center)
  }
}

@Component
struct CustomLayoutText {
  @Builder
  doSomethingBuilder() {
  };

  @BuilderParam
  builder: () => void = this.doSomethingBuilder;
  result: SizeResult = {
    width: 0,
    height: 0
  };
  // 自定义组件进行自定义布局。
  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions) {
    let posY = 20;
    children.forEach((child) => {
      let posX = (selfLayoutInfo.width - child.measureResult.width) / 2;
      child.layout({ x: posX, y: posY })
      posY += child.measureResult.height + 30;
    })
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions) {
    children.forEach((child) => {
      let result: MeasureResult = child.measure({ maxWidth: 335, maxHeight: 50 }) // 设置自定义组件子组件大小的限制。
    })
    this.result.width = 200;
    this.result.height = 130;
    return this.result;
  }

  build() {
    this.builder()
  }
}