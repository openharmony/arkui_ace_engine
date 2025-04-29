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

import setKeyboardAvoidModeTest from '../MyTest/SetKeyboardAvoidModeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SetKeyboardAvoidModeSample {
  aboutToAppear(): void {
    loadComponentTestEntry(setKeyboardAvoidModeTest)
  }

  build() {
    Column() {
      Row().height("30%").width("100%").backgroundColor(Color.Gray)
      TextArea().width("100%").borderWidth(1)
        .id('setKeyboardAvoidModeTextArea1')
      Text("I can see the text of the page")
        .width("100%")
        .layoutWeight(1)
        .textAlign(TextAlign.Center)
        .backgroundColor(Color.Pink)
    }.width('100%').height("100%")
  }
}
