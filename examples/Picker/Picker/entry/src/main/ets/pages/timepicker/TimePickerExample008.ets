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
 
class AttributeModifierBase implements AttributeModifier<TimePickerAttribute> {
  canloop: boolean = false

  // constructor function
  constructor(loop: boolean) {
    this.canloop =  loop
  }

  applyNormalAttribute(instance: TimePickerAttribute): void {
    instance.loop(this.canloop)
    if (!this.canloop) {
      instance.textStyle({color: Color.Red})
    } else {
      instance.textStyle({color: Color.Green})
    }
  }
}
// derived class
class MyAttributeModifier extends AttributeModifierBase {
  constructor(loop: boolean) {
    super(loop)
  }

  applyNormalAttribute(instance: TimePickerAttribute): void {
    super.applyNormalAttribute(instance)
    console.info("call derived function")
  }
}

@Entry
@Component
struct TimePickerExample008 {
  // 定义状态变量
  @State modifier: MyAttributeModifier = new MyAttributeModifier(false);

  build() {
    Column() {
      Button("change loop")
        .onClick(() => {
          this.modifier.canloop = !this.modifier.canloop
        })
      TimePicker()
        .attributeModifier(this.modifier)
    }
    .width('100%')
    .height('100%')
  }
}