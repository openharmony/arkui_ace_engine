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
import promptAction from '@ohos.promptAction';

@Entry
@Component
struct Index {
  @State message: string = 'PromptAction Test';
  @State resultText: string = 'Ready to test...';

  build() {
    Column({ space: 20 }) {
      Text(this.message)
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Text(this.resultText)
        .fontSize(14)
        .width('90%')
        .height(180)
        .backgroundColor('#f0f0f0')
        .padding(12)
        .borderRadius(8)
        .textAlign(TextAlign.Start)

      Button('调用 showToast()')
        .width('80%')
        .height(50)
        .onClick(() => {
          this.testShowToast();
        })

      Button('调用 showDialog()')
        .width('80%')
        .height(50)
        .onClick(() => {
          this.testShowDialog();
        })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }

  testShowToast() {
    console.info('[PromptTest] Calling showToast()');
    this.resultText = 'Calling promptAction.showToast()...\n';
    try {
      promptAction.showToast({
        message: 'Toast Show Test',
        duration: 2000
      });
      this.resultText += 'showToast() called successfully';
      console.info('[PromptTest] showToast() returned');
    } catch (e) {
      const err = e as Error;
      this.resultText += 'Error: ' + err.message;
      console.error('[PromptTest] showToast() error: ' + err.message);
    }
  }

  testShowDialog() {
    console.info('[PromptTest] Calling showDialog()');
    this.resultText = 'Calling promptAction.showDialog()...\n';
    try {
      promptAction.showDialog({
        title: 'Dialog Title',
        message: 'Dialog Show Test'
      });
      this.resultText += 'showDialog() called successfully';
      console.info('[PromptTest] showDialog() returned');
    } catch (e) {
      const err = e as Error;
      this.resultText += 'Error: ' + err.message;
      console.error('[PromptTest] showDialog() error: ' + err.message);
    }
  }
}