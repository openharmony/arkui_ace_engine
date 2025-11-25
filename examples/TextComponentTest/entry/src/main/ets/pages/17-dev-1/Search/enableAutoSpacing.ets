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

@Component
struct enableAutoSpacingExample1 {
  build() {
    Column() {
      Column() {
        Text('开启中西文自动间距').margin(5)
        Search({ value: '中西文Auto Spacing自动间距' })
          .enableAutoSpacing(true)
      }.borderRadius(2).borderWidth(2)

      Column() {
        Text('关闭中西文自动间距').margin(5)
        Search({ value: '中西文Auto Spacing自动间距' })
          .enableAutoSpacing(false)
      }.borderRadius(2).borderWidth(2)
    }
  }
}

@Component
export struct SearchEnableAutoSpacing {
  build() {
    NavDestination() {
      enableAutoSpacingExample1()
    }.hideBackButton(true)
  }
}