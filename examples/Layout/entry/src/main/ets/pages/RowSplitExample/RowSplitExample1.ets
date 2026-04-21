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
struct RowSplitExample1 {
  @Builder
  private ResizeableWithExample(resizeable: boolean | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      RowSplit() {
        Text('1').width('10%').height(100).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('2').width('10%').height(100).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('3').width('10%').height(100).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('4').width('10%').height(100).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('5').width('10%').height(100).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
      }
      .borderWidth(1)
      .resizeable(resizeable)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column() {
        Text('RowSplit通过resizeable设置分割线是否可拖拽')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.ResizeableWithExample(true, 'resizeable: true')
        this.ResizeableWithExample(false, 'resizeable: false')
        this.ResizeableWithExample(undefined, 'resizeable: undefined')
        this.ResizeableWithExample(null, 'resizeable: null')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}