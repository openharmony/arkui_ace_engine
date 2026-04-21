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

// xxx.ets
class MyColumnModifierBlurModify implements AttributeModifier<ColumnAttribute> {
  disable: boolean = true
  index: number = 1

  applyNormalAttribute(instance: ColumnAttribute): void {
    if (this.index === 1) {
      instance.blur(20, {grayscale: [30, 50]}, {disableSystemAdaptation: this.disable})
    } else if (this.index === 2) {
      instance.blur(20, {grayscale: [30, 50]}, undefined)
    } else  {
      instance.blur(20, {grayscale: [30, 50]}, { disableSystemAdaptation: undefined })
    }

  }
}

@Entry
@Component
struct BlurModify {
  @State modifier: MyColumnModifierBlurModify = new MyColumnModifierBlurModify()

  build() {
    Column() {
      Stack() {
        Column()
          .width(100)
          .height(100)
          .attributeModifier(this.modifier)
      }
      Column() {
        Button('change disableSystemAdaptation')
          .onClick(() => {
            this.modifier.index = 1;
            this.modifier.disable = !this.modifier.disable;
          })
        Text('blur设置在Column上面')
        if (this.modifier.index === 1) {
          Text(`disableSystemAdaptation：${this.modifier.disable}`)
        } else if (this.modifier.index === 2) {
          Text(`disableSystemAdaptation：sys undefined`)
        } else {
          Text(`disableSystemAdaptation：undefined`)
        }

        Button('sysOption-undefined')
          .onClick(() => {
            this.modifier.index = 2;
          })
        Button('disableSystemAdaptation-undefined')
          .onClick(() => {
            this.modifier.index = 3;
          })
      }
    }
    .height('100%')
  }
}