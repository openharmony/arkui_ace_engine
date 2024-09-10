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
import richEditorDataDetectorConfigTest from '../MyTest/RichEditorDataDetectorConfigTest'

@Entry
@Component
struct RichEditorDataDetectorConfigSample {
  controller: RichEditorController = new RichEditorController()
  options: RichEditorOptions = { controller: this.controller };
  @State dataDetectorConfigType: TextDataDetectorConfig = {
    types: [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL,
      TextDataDetectorType.ADDRESS],
    onDetectResultUpdate: (result: string) => {
    }
  }
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(richEditorDataDetectorConfigTest)
  }

  build() {
    Column() {
      RichEditor(this.options)
        .enableDataDetector(true)
        .dataDetectorConfig({ types: [], onDetectResultUpdate: null })
        .height(50)
        .id('richEditorDataDetectorConfig1')
      RichEditor(this.options)
        .enableDataDetector(true)
        .dataDetectorConfig(this.dataDetectorConfigType)
        .id('richEditorDataDetectorConfig2')
      Button('RichEditorDataDetectorConfig')
        .onClick(() => {
          this.dataDetectorConfigType = {
            types: [this.index],
            onDetectResultUpdate: (result: string) => {
            }
          }
          this.index++
          this.index %= 5
        })
    }
  }
}