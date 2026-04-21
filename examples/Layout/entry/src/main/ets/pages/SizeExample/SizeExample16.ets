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

class MyModifier1 implements AttributeModifier<CommonAttribute> {
  applyNormalAttribute(instance: CommonAttribute): void {
    instance
      .width(LayoutPolicy.matchParent)
      .height(LayoutPolicy.matchParent)
  }
}
class MyModifier2 implements AttributeModifier<CommonAttribute> {
  applyNormalAttribute(instance: CommonAttribute): void {
    instance
      .width(LayoutPolicy.wrapContent)
      .height(LayoutPolicy.wrapContent)
  }
}
class MyModifier3 implements AttributeModifier<CommonAttribute> {
  applyNormalAttribute(instance: CommonAttribute): void {
    instance
      .width(LayoutPolicy.fixAtIdealSize)
      .height(LayoutPolicy.fixAtIdealSize)
  }
}

@Entry
@Component
struct SizeExample16 {
  @State private Modifier1: MyModifier1 = new MyModifier1
  @State private Modifier2: MyModifier2 = new MyModifier2
  @State private Modifier3: MyModifier3 = new MyModifier3
  build() {
    Column() {
      Column() {
        Text('matchParent Modifier')
        Flex()
          .backgroundColor('rgb(0, 74, 175)')
          .attributeModifier(this.Modifier1)
          .constraintSize({ maxWidth: 150, maxHeight: 150 })

        Text('wrapContent Modifier')
        Row() {
          Flex()
            .width(300)
            .height(300)
        }
        .backgroundColor('rgb(39, 135, 217)')
        .attributeModifier(this.Modifier2)
        .constraintSize({ maxWidth: 250, maxHeight: 250 })

        Text('fixAtIdealSize Modifier')

        Row() {
          Flex()
            .width(300)
            .height(300)
        }
        .backgroundColor('rgb(240, 250, 255)')
        .attributeModifier(this.Modifier3)
        .constraintSize({ maxWidth: 250, maxHeight: 250 })
      }
      .width(200)
      .height(200)
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}