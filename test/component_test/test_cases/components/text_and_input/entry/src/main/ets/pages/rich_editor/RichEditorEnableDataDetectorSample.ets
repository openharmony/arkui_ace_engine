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
import richEditorEnableDataDetectorTest from '../MyTest/RichEditorEnableDataDetectorTest'

@Entry
@Component
struct RichEditorEnableDataDetectorSample {
  controller: RichEditorController = new RichEditorController()
  options: RichEditorOptions = { controller: this.controller };
  @State enableDataDetectorType: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(richEditorEnableDataDetectorTest)
  }

  build() {
    Column() {
      RichEditor(this.options)
        .enableDataDetector(this.enableDataDetectorType)
        .height(10)
        .id('richEditorEnableDataDetector1')
      Button('RichEditorEnableDataDetector')
        .onClick(() => {
          this.enableDataDetectorType = !this.enableDataDetectorType
        })
      RichEditor(this.options)
        .copyOptions(CopyOptions.None)
        .enableDataDetector(true)
        .id('richEditorEnableDataDetector2')
    }
  }
}