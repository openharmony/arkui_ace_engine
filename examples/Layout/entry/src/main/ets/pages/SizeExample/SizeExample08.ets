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
struct SizeExample8 {
  private data: number[] = (() => {
    let arr: number[] = [];
    for (let i = 1; i <= 30; i++) {
      arr.push(i);
    }
    return arr;
  })();

  @Builder
  private SizeWithExample(margin: Margin | Length | LocalizedMargin | undefined, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Row() {
        Row() {
          Row()
            .size({ width: '100%', height: '100%' })
            .backgroundColor(Color.Yellow)
        }
        .width(80)
        .height(80)
        .padding({
          top: 5,
          left: 10,
          bottom: 15,
          right: 20
        })
        .margin(margin)
        .backgroundColor(Color.Pink)
      }.backgroundColor(Color.Blue)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }
  build() {
    Scroll() {
      Column() {
        Text('margin Padding类型场景')
          .fontSize(20).fontWeight(FontWeight.Bold)
        Row(){
          this.SizeWithExample({ top: 5, left: 10, bottom: 15, right: 20 }, 'number:5,10,15,20')
          this.SizeWithExample({ top: '5', left: '10', bottom: '15', right: '20' }, 'string:5,10,15,20')
        }
        Divider()

        Row(){
          this.SizeWithExample({ top: '5px', left: '10px', bottom: '15px', right: '20px' }, '5px,10px,15px,20px')
          this.SizeWithExample({ top: '5vp', left: '10vp', bottom: '15vp', right: '20vp' }, '5vp,10vp,15vp,20vp')
        }
        Divider()

        Row(){
          this.SizeWithExample({ top: '5fp', left: '10fp', bottom: '15fp', right: '20fp' }, '5fp,10fp,15fp,20fp')
          this.SizeWithExample({
            top: '5lpx',
            left: '10lpx',
            bottom: '15lpx',
            right: '20lpx'
          }, '5lpx,10lpx,15lpx,20lpx')
        }
        Divider()

        Row(){
          this.SizeWithExample({ top: '2%', left: '4%', bottom: '6%', right: '8%' }, '2%,4%,6%,8%')
          this.SizeWithExample({ top: '', left: '', bottom: '', right: '' }, '空字符串')
        }
        Divider()

        Row(){
          this.SizeWithExample({
            top: $r('app.string.size1'),
            left: $r('app.string.size1'),
            bottom: $r('app.string.string'),
            right: $r('app.string.string')
          }, '正常和异常资源值')
          this.SizeWithExample({
            top: '$%&^^&FG',
            left: '$%&^^&FG',
            bottom: '$%&^^&FG',
            right: '$%&^^&FG'
          }, '$%&^^&FG')
        }
        this.SizeWithExample({ top: undefined, left: undefined, bottom: 10, right: 10 }, 'undefined,undefined,10,10')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}