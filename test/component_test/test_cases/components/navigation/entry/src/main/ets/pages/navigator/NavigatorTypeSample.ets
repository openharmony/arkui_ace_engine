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
import navigatorTypeTest from '../MyTest/NavigatorTypeTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct NavigatorTypeSample {
  @State targetType: NavigationType = NavigationType.Replace

  aboutToAppear(): void {
    loadComponentTestEntry(navigatorTypeTest);
  }

  build() {
    Column() {
      Navigator({ target: 'pages/navigator/NavigatorActiveTypeDetail' }) {
        Text('NavigatorType1')
          .width('100%')
      }
      .type(NavigationType.Push)
      .id('NavigatorType1')

      Navigator({ target: 'pages/navigator/NavigatorActiveTypeDetail' }) {
        Text('NavigatorType2')
          .width('100%')
      }
      .type(this.targetType)
      .id('NavigatorType2')

      Button('NavigatorType')
        .onClick(() => {
          this.targetType = NavigationType.Back
        })
    }
  }
}