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
struct SizeExample3 {
  private data: number[] = (() => {
    let arr: number[] = [];
    for (let i = 1; i <= 30; i++) {
      arr.push(i);
    }
    return arr;
  })();

  @Builder
  private SizeWithExample(size: SizeOptions | undefined, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Row() {
        Row() {
          Row()
            .size(size)
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
        .margin(20)
        .backgroundColor(Color.White)
      }.backgroundColor(Color.Blue)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column() {
        Text('size 可滚动场景')
          .fontSize(20).fontWeight(FontWeight.Bold)
        Row(){
          this.SizeWithExample({ width: 20, height: 20 }, 'number:20')
          this.SizeWithExample({ width: '20', height: '20' }, 'string:20')
        }
        Divider()

        Row(){
          this.SizeWithExample({ width: '30px', height: '30px' }, '30px')
          this.SizeWithExample({ width: '30vp', height: '30vp' }, '30vp')
        }
        Divider()

        Row(){
          this.SizeWithExample({ width: '30fp', height: '30fp' }, '30fp')
          this.SizeWithExample({ width: '30lpx', height: '30lpx' }, '30lpx')
        }
        Divider()

        Row(){
          this.SizeWithExample({ width: '100%', height: '100%' }, '100%')
          this.SizeWithExample({ width: '', height: '' }, '空字符串')
        }
        Divider()

        Row(){
          this.SizeWithExample({ width: $r('app.string.size'), height: $r('app.string.size') }, '正常资源值')
          this.SizeWithExample({ width: $r('app.string.string'), height: $r('app.string.string') }, '异常资源值')
        }
        Divider()

        Row(){
          this.SizeWithExample(undefined, 'undefined')
          this.SizeWithExample({ width: undefined, height: undefined }, '分别传入undefined')
        }
        this.SizeWithExample({ width: '$%&^^&FG', height: '$%&^^&FG' }, '$%&^^&FG')

        Divider()
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}