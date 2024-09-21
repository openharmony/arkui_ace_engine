/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textInputPasswordIconTest from '../MyTest/TextInputPasswordIconTest'

@Entry
@Component
struct TextInputPasswordIconSample {
  @State text: string = ''
  @State passwordIconType: PasswordIcon = { onIconSrc: $r('app.media.startIcon') }
  @State passwordIconType2: PasswordIcon = { onIconSrc: "../../../resources/base/media/icon.png" }
  controller: TextInputController = new TextInputController()

  aboutToAppear(): void {
    loadComponentTestEntry(textInputPasswordIconTest)
  }

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .type(InputType.Password)
        .passwordIcon(this.passwordIconType)
        .id('textInputPasswordIcon')
      Button('TextInputPasswordIcon')
        .onClick(() => {
          this.passwordIconType = { offIconSrc: $r('app.media.startIcon') }
        })
    }
  }
}