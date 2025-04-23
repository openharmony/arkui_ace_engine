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
struct struct_10_textMarquee {
  @State index: number = 0
  @State overflows: TextOverflow[] = [TextOverflow.MARQUEE]

  build() {
    Scroll() {
      Column() {
        Text('操作： 滑倒底部，动态切换为跑马灯的场景，在手机页面开启关怀模式到6档，然后切回该页面')
        Text('预期： 跑马灯文字变大，正常显示')
        Column().height(1000)
        Text('预期： 跑马灯文字变大，正常显示1234567899876543210123456789')
          .textOverflow({ overflow: TextOverflow.MARQUEE })
          .width(100)
      }
      .width('100%')
    }.height('100%')
  }
}