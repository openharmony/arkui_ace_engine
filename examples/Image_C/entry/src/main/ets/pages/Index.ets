/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

class MyMod < T extends SearchAttribute> implements  AttributeModifier<SearchAttribute> {
  private index: number = 0;

  applyNormalAttribute(instance: T) {
    instance.textFont({weight: undefined, style: undefined});
    instance.placeholderFont({weight: undefined, style: undefined});
  }
}

@Entry
@Component
struct Index {
  @State mod: MyMod<SearchAttribute> = new MyMod()
  @State fontStyle: FontStyle = FontStyle.Italic
  @State inputType: boolean = false
  // controller: TextInputController = new TextInputController()
  build() {
    Column() {
      Stack() {
        TextInput({placeholder: 'test', text: 'text'})
          .fontStyle(this.fontStyle).showUnderline(this.inputType).padding(20)
      }

      Button('click').onClick((event: ClickEvent) => {
        this.inputType = !this.inputType;
      })

    }
  }
}