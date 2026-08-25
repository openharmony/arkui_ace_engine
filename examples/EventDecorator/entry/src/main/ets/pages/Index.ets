/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
const TAG = '[Sample_EventDecorator]';
const DOMAIN = 0xF811;
const BUNDLE = 'EventDecorator_';

@Entry
@Component
struct Index {
  build() {
    Column({ space: 20 }) {
      Button('EventDecoratorTest1Button')
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({
            url: 'pages/EventDecoratorTest1',
          })
            .catch((error: BusinessError) => {
              hilog.error(DOMAIN, TAG, BUNDLE, `pushUrl failed, code is ${error.code}, message is ${error.message}`);
            })
        })
      Button('EventDecoratorTest2Button')
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({
            url: 'pages/EventDecoratorTest2',
          })
            .catch((error: BusinessError) => {
              hilog.error(DOMAIN, TAG, BUNDLE, `pushUrl failed, code is ${error.code}, message is ${error.message}`);
            })
        })

    }.height('100%')
    .width('100%')
  }
}
