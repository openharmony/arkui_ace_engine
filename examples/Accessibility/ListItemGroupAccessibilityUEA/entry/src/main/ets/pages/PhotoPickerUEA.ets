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

// 扩展Ability入口页面文件extension.ets
import { UIExtensionContentSession } from '@kit.AbilityKit';
import { router } from '@kit.ArkUI';

@Entry()
@Component
struct Extension {
  @State text: string = "快捷键测试"

  build() {
    Column() {
      Text("PhotoPickerUEA").fontSize(20).fontWeight(FontWeight.Bold)
      Button(this.text)

        .keyboardShortcut(FunctionKey.F1, [], () => {
          console.info('kswTest_mutableStr styledValue ');
          this.text = "F1"
        })
        .keyboardShortcut(FunctionKey.F1, [ModifierKey.SHIFT], () => {
          this.text = "F1 + SHIFT"
        })
    }
    .height('100%')
    .width('100%')
  }
}