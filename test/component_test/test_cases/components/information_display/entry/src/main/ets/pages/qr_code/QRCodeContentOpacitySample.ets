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
import qRCodeContentOpacityTest from '../MyTest/QRCodeContentOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct QRCodeContentOpacitySample {
  private value: string = 'hello world'
  @State contentOpacityStatus: number | Resource = 0.5

  aboutToAppear(): void {
    loadComponentTestEntry(qRCodeContentOpacityTest)
  }

  build() {
    Column({ space: 5 }) {
      QRCode(this.value)
        .contentOpacity(this.contentOpacityStatus)
        .id('qRCodeContentOpacity')

      Button('QRCodeContentOpacity')
        .onClick(() => {
          this.contentOpacityStatus = $r('app.float.qr_code_contentOpacity')
        })
    }
  }
}