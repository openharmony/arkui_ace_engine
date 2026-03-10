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
class MyColumnModifierForegroundEffectModify implements AttributeModifier<ColumnAttribute> {
  disable: boolean = true

  applyNormalAttribute(instance: ColumnAttribute): void {
    instance.foregroundEffect({ radius: 20 }, {disableSystemAdaptation: this.disable})
  }
}

@Entry
@Component
struct ForegroundEffectModify {
  @State modifier: MyColumnModifierForegroundEffectModify = new MyColumnModifierForegroundEffectModify()

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
            this.modifier.disable = !this.modifier.disable;
          })
        Text('foregroundEffect设置在Column上面')
        Text(`disableSystemAdaptation：${this.modifier.disable}`)
      }
    }
    .height('100%')
  }
}