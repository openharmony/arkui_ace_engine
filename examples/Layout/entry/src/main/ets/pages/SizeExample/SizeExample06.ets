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

import { LengthMetrics, LengthUnit  } from '@kit.ArkUI'

@Entry
@Component
struct SizeExample6 {
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
        Text('padding LocalizedPadding类型场景')
          .fontSize(20).fontWeight(FontWeight.Bold)

        Row(){
          this.SizeWithExample({
            top: LengthMetrics.px(5),
            bottom: LengthMetrics.px(15),
            start: LengthMetrics.px(10),
            end: LengthMetrics.px(20)
          }, '5px,10px,15px,20px')
          this.SizeWithExample({
            top: LengthMetrics.vp(5),
            bottom: LengthMetrics.vp(15),
            start: LengthMetrics.vp(10),
            end: LengthMetrics.vp(20)
          }, '5vp,10vp,15vp,20vp')
        }
        Divider()

        Row(){
          this.SizeWithExample({
            top: LengthMetrics.fp(5),
            bottom: LengthMetrics.fp(15),
            start: LengthMetrics.fp(10),
            end: LengthMetrics.fp(20)
          }, '5fp,10fp,15fp,20fp')
          this.SizeWithExample({
            top: LengthMetrics.lpx(5),
            bottom: LengthMetrics.lpx(15),
            start: LengthMetrics.lpx(10),
            end: LengthMetrics.lpx(20)
          }, '5lpx,10lpx,15lpx,20lpx')
        }
        Divider()

        Row(){
          this.SizeWithExample({
            top: LengthMetrics.percent(0.02),
            bottom: LengthMetrics.percent(0.04),
            start: LengthMetrics.percent(0.06),
            end: LengthMetrics.percent(0.08)
          }, '2%,4%,6%,8%')
          this.SizeWithExample({
            top: new LengthMetrics(5, LengthUnit.VP),
            bottom: new LengthMetrics(10, LengthUnit.PX),
            start: new LengthMetrics(15, LengthUnit.FP),
            end: new LengthMetrics(20, LengthUnit.LPX),
          }, '5vp,10px,15fp,20lpx')
        }
        this.SizeWithExample({
          top: LengthMetrics.resource($r('app.string.size1')),
          bottom: LengthMetrics.resource($r('app.string.size1')),
          start: LengthMetrics.resource($r('app.string.string')),
          end: LengthMetrics.resource($r('app.string.string'))
        }, '正常和异常资源值')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}