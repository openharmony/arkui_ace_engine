/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ProgressModifier } from '@ohos.arkui.modifier';
import { TestAttributes, testData } from './common/ProgressTestData';

class CustomModifier extends ProgressModifier {
  applyNormalAttribute(instance: ProgressAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  applyChange(testData: TestAttributes): void {
    this
      .style(testData.style)
      .color(testData.color)
      .value(testData.value)
  }
}

@Component
struct ModifierComponent {
  @Link customModifier: ProgressModifier

  build() {
    Column({ space: 10 }) {
      Progress({ value: 20, total: 100, type: ProgressType.Eclipse })
        .attributeModifier(this.customModifier as CustomModifier)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.Linear })
        .attributeModifier(this.customModifier as CustomModifier)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.Ring })
        .attributeModifier(this.customModifier as CustomModifier)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.ScaleRing })
        .attributeModifier(this.customModifier as CustomModifier)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.Capsule })
        .attributeModifier(this.customModifier as CustomModifier)
        .height(80);
    }
  }
}

@Component
struct MyCustomComponent {
  @Prop testData: TestAttributes

  build() {
    Column({ space: 10 }) {
      Progress({ value: 20, total: 100, type: ProgressType.Eclipse })
        .style(this.testData.style)
        .color(this.testData.color)
        .value(this.testData.value)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.Linear })
        .style(this.testData.style)
        .color(this.testData.color)
        .value(this.testData.value)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.Ring })
        .style(this.testData.style)
        .color(this.testData.color)
        .value(this.testData.value)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.ScaleRing })
        .style(this.testData.style)
        .color(this.testData.color)
        .value(this.testData.value)
        .height(80);

      Progress({ value: 20, total: 100, type: ProgressType.Capsule })
        .style(this.testData.style)
        .color(this.testData.color)
        .value(this.testData.value)
        .height(80);
    }
  }
}

@Entry
@Component
struct ProgressLevel1_4 {
  @State index: number = 0
  @State testData: TestAttributes[] = testData
  @State customModifier: ProgressAttribute = new CustomModifier()
    .style(this.testData[this.index].style)
    .color(this.testData[this.index].color)
    .value(this.testData[this.index].value)

  @Builder
  nativeBuilder() {
    Column() {
      // 这里是原生属性UI
      Column({ space: 10 }) {
        Progress({ value: 20, total: 100, type: ProgressType.Eclipse })
          .style(this.testData[this.index].style)
          .color(this.testData[this.index].color)
          .value(this.testData[this.index].value)
          .height(80);

        Progress({ value: 20, total: 100, type: ProgressType.Linear })
          .style(this.testData[this.index].style)
          .color(this.testData[this.index].color)
          .value(this.testData[this.index].value)
          .height(80);

        Progress({ value: 20, total: 100, type: ProgressType.Ring })
          .style(this.testData[this.index].style)
          .color(this.testData[this.index].color)
          .value(this.testData[this.index].value)
          .height(80);

        Progress({ value: 20, total: 100, type: ProgressType.ScaleRing })
          .style(this.testData[this.index].style)
          .color(this.testData[this.index].color)
          .value(this.testData[this.index].value)
          .height(80);

        Progress({ value: 20, total: 100, type: ProgressType.Capsule })
          .style(this.testData[this.index].style)
          .color(this.testData[this.index].color)
          .value(this.testData[this.index].value)
          .height(80);
      }
    }
  }

  @Builder
  modifierBuilder() {
    Column() {
      // 这里是Modifier属性UI
      ModifierComponent({ customModifier: this.customModifier })
    }
  }

  build() {
    Column() {
      Row() {
        Text('原生属性')
          .fontSize('32fp')
          .margin({ top: 20, bottom: 20 })
          .fontWeight(FontWeight.Bold)

        Blank().width('5%')

        Text('Modifier')
          .fontSize('32fp')
          .margin({ top: 20, bottom: 20 })
          .fontWeight(FontWeight.Bold)
      }

      Row() {
        Column() {
          this.nativeBuilder()
        }.width('50%').height('100%').key('testArea0')

        Column() {
          this.modifierBuilder()
        }.width('50%').height('100%').key('testArea1')
      }
      .key('testArea')
      .width('100%')
      .height('60%')
      .justifyContent(FlexAlign.Center)

      // 更新数据按钮
      Column() {
        Row({ space: 2 }) {
          Text(`${this.index + 1}`)
          Text('/')
          Text(`${this.testData?.length}`).key('Progress14_cycles')
        }

        Text(JSON.stringify(this.testData[this.index]))
          .height('calc(100% - 180vp)')
          .shadow({
            radius: 5,
            color: Color.Gray,
            offsetX: 5,
            offsetY: 5
          })
          .backgroundColor(Color.White)

        Row({ space: 2 }) {
          Button('Index++')
            .margin({ left: 10, right: 10 })
            .onClick(() => {
              this.index = (this.index + 1) % (this.testData?.length);
              (this.customModifier as CustomModifier).applyChange(this.testData[this.index]);
            })

          Button('Index--')
            .margin({ left: 10, right: 10 })
            .onClick(() => {
              if (this.index <= 0) {
                this.index = this.testData?.length - 1
              } else {
                this.index--
              }
              (this.customModifier as CustomModifier).applyChange(this.testData[this.index]);
            })
        }.padding({ top: 20, bottom: 100 })
      }
      .height('40%')
      .alignItems(HorizontalAlign.Center)
      .width('100%')
    }.width('100%')
    .height('100%')
  }
}