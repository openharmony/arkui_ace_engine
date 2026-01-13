/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { MyComponent } from './MyComponenet'

@Builder
export function TipsAvoidBuilder(name: string, param: Object) {
  TipsAvoidExample()
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(11)
  .width('100%')
}
@Extend(Column)
function columnStyle() {
  .backgroundColor(Color.Pink)
  .width('100%')
  .padding(5)
  .borderWidth(1.0)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct TipsAvoidExample {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State rowHeight: number = 80
  @State rowWidth: number = 150
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Start
  @State columnAlignFlex: FlexAlign = FlexAlign.Start
  @State select_align_idx: number = -1
  @State select_align_value: string = ''
  @State targetCompWidth: number = 20
  @State tipsMesCount: number = 1
  @State tipsOpt: TipsOptions = {}
  @State bindSheetShow: boolean = false
  @State bindSheetHeight: Length = '60%'

  @Builder
  bindSheetBuilder() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text('悬浮气泡位置约束场景')
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`切换绑定组件的位置`)
            .paramTextStyle()
          Select([
            { value: 'TopStart' },
            { value: 'TopCenter' },
            { value: 'TopEnd' },
            { value: 'CenterStart' },
            { value: 'Center' },
            { value: 'CenterEnd' },
            { value: 'BottomStart' },
            { value: 'BottomCenter' },
            { value: 'BottomEnd' },
          ])
            .value('TopStart')
            .selected(0)
            .selectStyle()
            .selected(this.select_align_idx!!)
            .value(this.select_align_value!!)
            .onSelect((idx, value: string) => {
              this.select_align_idx = idx
              this.select_align_value = value
              switch (value) {
                case 'TopStart':
                  this.columnAlignFlex = FlexAlign.Start
                  this.columnAlignHorizontal = HorizontalAlign.Start
                  break;
                case 'TopCenter':
                  this.columnAlignFlex = FlexAlign.Start
                  this.columnAlignHorizontal = HorizontalAlign.Center
                  break;
                case 'TopEnd':
                  this.columnAlignFlex = FlexAlign.Start
                  this.columnAlignHorizontal = HorizontalAlign.End
                  break;
                case 'CenterStart':
                  this.columnAlignFlex = FlexAlign.Center
                  this.columnAlignHorizontal = HorizontalAlign.Start
                  break;
                case 'Center':
                  this.columnAlignFlex = FlexAlign.Center
                  this.columnAlignHorizontal = HorizontalAlign.Center
                  break;
                case 'CenterEnd':
                  this.columnAlignFlex = FlexAlign.Center
                  this.columnAlignHorizontal = HorizontalAlign.End
                  break;
                case 'BottomStart':
                  this.columnAlignFlex = FlexAlign.End
                  this.columnAlignHorizontal = HorizontalAlign.Start
                  break;
                case 'BottomCenter':
                  this.columnAlignFlex = FlexAlign.End
                  this.columnAlignHorizontal = HorizontalAlign.Center
                  break;
                case 'BottomEnd':
                  this.columnAlignFlex = FlexAlign.End
                  this.columnAlignHorizontal = HorizontalAlign.End
                  break;
              }
            })
            .key('select_targetCompPos')

          Text(`切换Tips跟随类型`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'TARGET', func: () => {
                this.tipsOpt.showAtAnchor = TipsAnchorType.TARGET
              }
            })
            MyComponent({
              title: 'CURSOR', func: () => {
                this.tipsOpt.showAtAnchor = TipsAnchorType.CURSOR
              }
            })
          }

          Text(`切换Tips文本长度`)
            .paramTextStyle()
          Counter() {
            Text(this.tipsMesCount.toString())
          }
          .key('tips_counter')
          .margin(10)
          .onInc(() => {
            this.tipsMesCount++;
          })
          .onDec(() => {
            if (this.tipsMesCount > 0) {
              this.tipsMesCount--;
            }
          })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .width('100%')
    .margin({ top: 32 })
    .padding(10)
    .align(Alignment.TopStart)
  }

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        // bindTips绑定组件区域
        Scroll() {
          Column() {
            Column() {
            }
            .backgroundColor(Color.Orange)
            .height(20).width(this.targetCompWidth)
            .bindTips('tips '.repeat(this.tipsMesCount), this.tipsOpt)
          }
          .alignItems(this.columnAlignHorizontal)
          .justifyContent(this.columnAlignFlex)
          .width('100%').height('100%')
        }
        .padding(10)
        .width('100%')
        .height('50%')
        .backgroundColor(Color.Transparent)

        // 控制区域
        Scroll(this.scroller) {
        }
        .margin(40)
        .padding(10)
        .width('80%')
        .height('20%')
        .borderRadius(20)
        .backgroundColor('#4D0A59F7')
        .bindSheet(this.bindSheetShow!!, this.bindSheetBuilder(), {
          height: this.bindSheetHeight
        })
        .onClick(() => {
          this.bindSheetShow = true
        })
      }.width('100%').margin({ top: 5 })
    }
    .title('TipsAvoidTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}