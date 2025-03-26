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

import { JSON } from '@kit.ArkTS'

class TabsModifier implements AttributeModifier<TabsAttribute> {
  public index: number = 0

  public testData: (BlurStyle | null | undefined)[] = [
    undefined,
    null,
    BlurStyle.Thin,
    BlurStyle.Regular,
    BlurStyle.Thick,
    BlurStyle.BACKGROUND_THIN,
    BlurStyle.BACKGROUND_REGULAR,
    BlurStyle.BACKGROUND_THICK,
    BlurStyle.BACKGROUND_ULTRA_THICK,
    BlurStyle.NONE,
    BlurStyle.COMPONENT_ULTRA_THIN,
    BlurStyle.COMPONENT_THIN,
    BlurStyle.COMPONENT_REGULAR,
    BlurStyle.COMPONENT_THICK,
    BlurStyle.COMPONENT_ULTRA_THICK,
    -1,
    5,
    0
  ]

  applyNormalAttribute(instance: TabsAttribute): void {
    instance.barBackgroundBlurStyle(this.testData[this.index])
  }

  onInc() {
    this.index = (this.index + 1) % this.testData.length
  }

  onDec() {
    if (this.index === 0) {
      this.index = this.testData.length - 1
    } else {
      this.index--
    }
  }
}

@Entry
@Component
struct BarBackgroundBlurStyle {
  @State myModifier: TabsModifier = new TabsModifier()

  @Builder
  nature() {
    Stack() {
      Image($r('app.media.startIcon'))

      // 原生属性UI
      Tabs() {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar('green')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Blue)
        }.tabBar('blue')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Yellow)
        }.tabBar('yellow')
      }
      .borderWidth(5)
      .barBackgroundBlurStyle(this.myModifier.testData[this.myModifier.index])
    }
    .height(300)
  }

  @Builder
  modifier() {
    Stack() {
      Image($r('app.media.startIcon'))

      // Modifier属性UI
      Tabs() {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar('green')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Blue)
        }.tabBar('blue')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Yellow)
        }.tabBar('yellow')
      }
      .borderWidth(5)
      .attributeModifier(this.myModifier)
    }
    .height(300)
  }

  build() {
    Column() {
      Row() {
        Column() {
          Text('原生属性').fontSize('32fp').margin({ top: 20, bottom: 20 }).fontWeight(FontWeight.Bold)
          this.nature()
        }.width('50%').height('100%')

        Column() {
          Text('Modifier').fontSize('32fp').margin({ top: 20, bottom: 20 }).fontWeight(FontWeight.Bold)
          this.modifier()
        }.width('50%').height('100%')
      }
      .width('100%')
      .height('calc(70% - 80vp)')
      .justifyContent(FlexAlign.Center)

      Column() {
        Text(`${this.myModifier.index + 1} / ${this.myModifier.testData.length + 1}`)

        Text(JSON.stringify(this.myModifier.testData[this.myModifier.index]))
          .height('calc(100% - 180vp)')
          .shadow({ radius: 5, color: Color.Gray, offsetX: 5, offsetY: 5 })
          .backgroundColor(Color.White)

        Row({ space: 2 }) {
          Button('index++')
            .margin({ left: 10, right: 10 })
            .onClick(() => {
              this.myModifier.onInc()
            })

          Button('index--')
            .margin({ left: 10, right: 10 })
            .onClick(() => {
              this.myModifier.onDec()
            })
        }.padding({ top: 20 })
      }
      .width('100%')
      .height('30%')
      .alignItems(HorizontalAlign.Center)
      .position({ x: 0, y: '70%' })
    }
    .width('100%')
    .height('100%')
  }
}