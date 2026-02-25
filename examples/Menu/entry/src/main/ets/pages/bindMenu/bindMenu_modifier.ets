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

class MyPickerModifier1 implements AttributeModifier<ButtonAttribute> {
  isDark: boolean = false
  applyNormalAttribute(instance: ButtonAttribute): void {
    instance.bindMenu([
      {
        value: 'Menu1',
        action: () => {
          console.info('handle Menu1 select');
        }
      },
      {
        value: 'Menu2',
        action: () => {
          console.info('handle Menu2 select');
        }
      },
    ])
  }
}

@Entry
@Component
struct BindMenu_modifier {
  @State message: string = 'bindMenu';
  @State modifier1: MyPickerModifier1 = new MyPickerModifier1()

  build() {
    Column() {
      Column() {
        Text('bindMenu通过配置MenuElement弹出普通菜单')
        Button(this.message)
          .fontSize($r('app.float.page_text_font_size'))
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.message = 'Welcome';
          })
          .attributeModifier(this.modifier1)
      }
      .width('100%')
    }
    .height('100%')
  }
}