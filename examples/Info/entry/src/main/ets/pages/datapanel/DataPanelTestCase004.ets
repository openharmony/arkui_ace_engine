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

// 引入需要的Modifier
import { DataPanelModifier } from '@ohos.arkui.modifier';
import { TestAttributes, testData } from './DataPanelTestData';
import { Utils } from './Utils';

// 修改基类
class CustomModifier extends DataPanelModifier {
  applyNormalAttribute(instance: DataPanelModifier): void {
    super.applyNormalAttribute?.(instance);
  }

  applyChange(testData: TestAttributes): void {
    this
      .trackShadow(testData.trackShadow)
      .strokeWidth(testData.strokeWidth)
      .trackBackgroundColor(testData.trackBackgroundColor)
      .valueColors(testData.valueColors)
      .closeEffect(testData.closeEffect)

  }
}

@Component
struct MyCustomComponent {
  @Prop testData: TestAttributes
  valueColorsLinear =
    [new LinearGradient([{ color: '#ffeca908', offset: -10 }, { color: 'rgba(49, 239, 16, 1.00)', offset: 11 }]),
      new LinearGradient([{ color: '#FF67F9D4', offset: '0.6' },
        { color: '#FFFF9554', offset: $r('app.color.rColor1') }]), '#00FF00', '#20FF0000']
  trackShadowLinear: DataPanelShadowOptions = {
    radius: $r('app.string.rRadius'),
    offsetX: $r('app.string.rOffset'),
    offsetY: $r('app.string.rOffset'),
    colors: [new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#65EF629F', offset: 1 }]),
      new LinearGradient([{ color: $r('app.color.yellow'), offset: 0 }, { color: 0x65efbd0, offset: 10 }]),
      new LinearGradient([{ color: '#6572B513', offset: 0 }, { color: '#6508efa6', offset: 0.41 }]),
      new LinearGradient([{ color: '#65ed08f5', offset: 0 }, { color: '#65ef0849', offset: 1 }])
    ]
  }

  build() {
    Column({ space: 10 }) {
      DataPanel({ values: [15, 20, 25, 30], max: 100, type: DataPanelType.Line })
        .height('25%')
        .width('50%')
        .trackShadow(this.testData.linearGradient ? this.trackShadowLinear : this.testData.trackShadow)
        .strokeWidth(this.testData.strokeWidth)
        .trackBackgroundColor(this.testData.trackBackgroundColor)
        .valueColors(this.testData.linearGradient ? this.valueColorsLinear : this.testData.valueColors)
        .closeEffect(this.testData.closeEffect)
      DataPanel({ values: [15, 20, 25, 30], max: 100, type: DataPanelType.Circle })
        .height('25%')
        .width('50%')
        .trackShadow(this.testData.linearGradient ? this.trackShadowLinear : this.testData.trackShadow)
        .strokeWidth(this.testData.strokeWidth)
        .trackBackgroundColor(this.testData.trackBackgroundColor)
        .valueColors(this.testData.linearGradient ? this.valueColorsLinear : this.testData.valueColors)
        .closeEffect(this.testData.closeEffect)
    }
  }
}

// modifier-自定义组件
@Component
struct ModifierComponent {
  @Link customModifier: DataPanelModifier

  build() {
    Column({ space: 10 }) {
      DataPanel({ values: [15, 20, 25, 30], max: 100, type: DataPanelType.Line })
        .height('25%')
        .width('50%')
        .attributeModifier(this.customModifier as CustomModifier)
      DataPanel({ values: [15, 20, 25, 30], max: 100, type: DataPanelType.Circle })
        .height('25%')
        .width('50%')
        .attributeModifier(this.customModifier as CustomModifier)
    }
  }
}

@Entry
@Component
struct TestPage {
  @State index: number = 0
  @State testData: TestAttributes[] = testData
  @State customModifier: DataPanelAttribute = new CustomModifier()
    .trackShadow(this.testData[this.index].trackShadow)
    .strokeWidth(this.testData[this.index].strokeWidth)
    .trackBackgroundColor(this.testData[this.index].trackBackgroundColor)
    .valueColors(this.testData[this.index].valueColors)
    .closeEffect(this.testData[this.index].closeEffect)

  @Builder
  nativeBuilder() {
    Column() {
      // 这里是原生属性UI
      MyCustomComponent({
        testData: this.testData[this.index]
      })
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
        Column() {
          Text('原生属性')
            .fontSize('32fp')
            .margin({ top: 20, bottom: 20 })
            .fontWeight(FontWeight.Bold)
          this.nativeBuilder()
        }.width('50%').height('100%')

        Column() {
          Text('Modifier')
            .fontSize('32fp')
            .margin({ top: 20, bottom: 20 })
            .fontWeight(FontWeight.Bold)
          this.modifierBuilder()
        }
        .width('50%').height('100%')
      }
      .width('100%')
      .height('calc(60% - 80vp)')
      .justifyContent(FlexAlign.Center)

      // 更新数据按钮
      Column() {
        Text(`${this.index + 1} / ${this.testData?.length}`)

        Text(Utils.deepCopy(this.testData[this.index]))
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
      .position({ x: 0, y: '70%' })
      .width('100%')
    }.width('100%')
    .height('100%')
  }
}