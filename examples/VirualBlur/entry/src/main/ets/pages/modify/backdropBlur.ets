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
class MyColumnModifierBackDropBlurModify implements AttributeModifier<ColumnAttribute> {
  index: number = 1

  applyNormalAttribute(instance: ColumnAttribute): void {
    if (this.index === 1) {
      instance.backdropBlur(20, { grayscale: [30, 50] }, {disableSystemAdaptation: false})
    } else if (this.index === 2) {
      instance.backdropBlur(20, { grayscale: [30, 50] }, undefined)
    } else if (this.index === 3) {
      instance.backdropBlur(20, { grayscale: [30, 50] }, {disableSystemAdaptation: true})
    } else {
      instance.backdropBlur(20, { grayscale: [30, 50] }, { disableSystemAdaptation: undefined })
    }
  }
}

@Entry
@Component
struct BackDropBlurModify {
  @State modifier: MyColumnModifierBackDropBlurModify = new MyColumnModifierBackDropBlurModify()

  build() {
    Column() {
      // backdropBlur 只能设置模糊半径和灰阶参数
      Stack() {
        Column()
          .width(100)
          .height(100)
          .attributeModifier(this.modifier)
      }
      Column() {
        Button('change disableSystemAdaptation')
          .onClick(() => {
            if (this.modifier.index === 4) {
              this.modifier.index = 1;
            } else {
              this.modifier.index++;
            }
          })
        Text('backdropBlur设置在Column上面')
        if (this.modifier.index === 1) {
          Text(`disableSystemAdaptation：false`)
        } else if (this.modifier.index === 2) {
          Text(`disableSystemAdaptation：sys undefined`)
        } else if (this.modifier.index === 3) {
          Text(`disableSystemAdaptation：true`)
        } else {
          Text(`disableSystemAdaptation：undefined`)
        }
      }
    }
    .height('100%')
  }
}