/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 
import { TextModifier } from '@ohos.arkui.modifier'


class TextModifierTest extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    instance.minFontScale(2).maxFontScale(5)
  }
}

@Entry
@Component
struct ImageTest1 {
  TextModifierTest : TextModifier = new TextModifierTest ()

  build() {
    Column({ space: 8 }) {
      Text('蜀道难难难难难难难难难难难难难难难难难难难难难！！！！！！').borderWidth(1)
        .attributeModifier(this.TextModifierTest as TextModifierTest)
    }
    .borderWidth(2)
    .padding(5)
    .height('100%')
    .width("100%")
    .backgroundColor(Color.Pink)
  }
}