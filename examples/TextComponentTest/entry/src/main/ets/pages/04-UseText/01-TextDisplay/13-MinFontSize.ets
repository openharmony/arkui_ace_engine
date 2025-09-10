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

@Entry
@Component
struct MinFontSize {
  build() {
    Column() {
      Text('我的最大字号为30，最小字号为5，宽度为250，maxLines为1')
        .width(250)
        .maxLines(1)
        .maxFontSize(30)
        .minFontSize(5)
        .border({ width: 1 })
        .padding(10)
        .margin(5)
      Text('我的最大字号为30，最小字号为5，宽度为250，maxLines为2')
        .width(250)
        .maxLines(2)
        .maxFontSize(30)
        .minFontSize(5)
        .border({ width: 1 })
        .padding(10)
        .margin(5)
      Text('我的最大字号为30，最小字号为15，宽度为250,高度为50')
        .width(250)
        .height(50)
        .maxFontSize(30)
        .minFontSize(15)
        .border({ width: 1 })
        .padding(10)
        .margin(5)
      Text('我的最大字号为30，最小字号为15，宽度为250,高度为100')
        .width(250)
        .height(100)
        .maxFontSize(30)
        .minFontSize(15)
        .border({ width: 1 })
        .padding(10)
        .margin(5)
    }
  }
}