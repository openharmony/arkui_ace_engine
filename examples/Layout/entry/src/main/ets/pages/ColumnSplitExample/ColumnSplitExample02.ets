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
struct ColumnSplitExample2 {
  @Builder
  private DividerWithExample(divider: ColumnSplitDividerStyle | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      ColumnSplit() {
        Text('1').width('100%').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('2').width('100%').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('3').width('100%').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('4').width('100%').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('5').width('100%').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
      }
      .borderWidth(1)
      .divider(divider)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column() {
        Text('ColumnSplit通过divider设置分割线的margin')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.DividerWithExample({ startMargin: '10vp', endMargin: '5vp' }, 'divider: \'10vp,5vp\'')
        this.DividerWithExample({ startMargin: 10, endMargin: 5 }, 'divider: 10,5')
        this.DividerWithExample({ startMargin: '5px', endMargin: '10px' }, 'divider: \'5px,10px\'')
        this.DividerWithExample({ startMargin: '10fp', endMargin: '5fp' }, 'divider: \'10fp,5fp\'')
        this.DividerWithExample({ startMargin: '5lpx', endMargin: '10lpx' }, 'divider: \'5lpx,10lpx\'')
        this.DividerWithExample({ startMargin: '10%', endMargin: '5%' }, 'divider: \'10%,5%\'')
        this.DividerWithExample({ startMargin: $r('app.string.stringSpace'), endMargin: $r('app.string.stringSpace') }, 'divider: $r(\'app.string.stringSpace\')')
        this.DividerWithExample(undefined, 'divider: undefined')
        this.DividerWithExample(null, 'divider: null')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}