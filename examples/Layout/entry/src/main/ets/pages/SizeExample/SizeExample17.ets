/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
struct SizeExample17 {
  build() {
    Column({ space: 10 }) {
      Text('calc:')
        .fontSize(12)
        .fontColor(0xCCCCCC)
        .width('90%')
      Column() {
        Row() {
          Text('width 50%')
            .fontSize(14)
            .borderWidth(1)
            .textAlign(TextAlign.Center)
            .size({ width: '50%', height: 50 })
          Text('width 50vp')
            .fontSize(14)
            .borderWidth(1)
            .textAlign(TextAlign.Center)
            .size({ width: '50vp', height: 50 })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('width:calc(50% + 50vp), height:calc(50%)')
          .fontSize(14)
          .borderWidth(1)
          .fontWeight(FontWeight.Bold)
          .backgroundColor(0xFFFAF0)
          .textAlign(TextAlign.Center)
          .size({ width: 'calc(50% + 50vp)', height: 'calc(50%)' })
        // width和height设置百分比时，以父容器的width和height作为基础值。calc的宽度计算结果与上方的两个text宽度之和相等。
      }.width("100%").height(100)
    }
    .width('100%')
    .margin({ top: 5 })
  }
}