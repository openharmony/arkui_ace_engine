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
struct SizeExample4 {
  private data: number[] = (() => {
    let arr: number[] = [];
    for (let i = 1; i <= 30; i++) {
      arr.push(i);
    }
    return arr;
  })();

  @Builder
  private SizeWithExample(padding: Padding | Length | LocalizedPadding | undefined, tip: string) {
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
        .padding(padding)
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
        Text('padding Length类型场景')
          .fontSize(20).fontWeight(FontWeight.Bold)
        Row(){
          this.SizeWithExample(20, 'number:20')
          this.SizeWithExample('20', 'string:20')
        }
        Divider()

        Row(){
          this.SizeWithExample('20px', '20px')
          this.SizeWithExample('20vp', '20vp')
        }
        Divider()

        Row(){
          this.SizeWithExample('20fp', '20fp')
          this.SizeWithExample('20lpx', '20lpx')
        }
        Divider()

        Row(){
          this.SizeWithExample('10%', '10%')
          this.SizeWithExample('', '空字符串')
        }
        Divider()

        Row(){
          this.SizeWithExample($r('app.string.size'), '正常资源值')
          this.SizeWithExample($r('app.string.string'), '异常资源值')
        }
        Divider()

        Row(){
          this.SizeWithExample(undefined, 'undefined')
          this.SizeWithExample('$%&^^&FG', '$%&^^&FG')
        }
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}