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
class MyColumnModifierBackgroundEffect implements AttributeModifier<ColumnAttribute> {
  index: number = 1

  applyNormalAttribute(instance: ColumnAttribute): void {
    if (this.index === 1) {
      instance.backgroundEffect({ radius: 20, brightness: 0.6, saturation: 15 }, {disableSystemAdaptation: undefined})
    } else if (this.index === 2) {
      instance.backgroundEffect({ radius: 20, brightness: 0.6, saturation: 15 }, {disableSystemAdaptation: true})
    } else if (this.index === 3) {
      instance.backgroundEffect({ radius: 20, brightness: 0.6, saturation: 15 }, {disableSystemAdaptation: false})
    } else {
      instance.backgroundEffect({ radius: 20, brightness: 0.6, saturation: 15 }, undefined)
    }
  }
}

@Entry
@Component
struct BackgroundEffectModify {
  @State modifier: MyColumnModifierBackgroundEffect = new MyColumnModifierBackgroundEffect()

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
            if (this.modifier.index === 4) {
              this.modifier.index = 1;
            } else {
              this.modifier.index++;
            }
          })
        Text('backgroundEffect设置在Column上面')
        if (this.modifier.index === 1) {
          Text(`disableSystemAdaptation：undefined`)
        } else if (this.modifier.index === 2) {
          Text(`disableSystemAdaptation：true`)
        } else if (this.modifier.index === 3) {
          Text(`disableSystemAdaptation：false`)
        } else {
          Text(`disableSystemAdaptation：sys undefined`)
        }
      }
    }
    .height('100%')
  }
}