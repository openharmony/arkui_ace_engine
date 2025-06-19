/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { MyComponent } from '../base/MyComponent';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function ButtonLevel3Builder(name: string, param: Object) {
  ButtonLevel3Example()
}

ThemeControl.setDefaultTheme(undefined);

interface setsObject {
  label1: string,
  labelStyle: labelStyle,
  align1?: Alignment
}

interface labelStyle {
  overflow?: TextOverflow,
  maxLines?: number,
  maxFontSize?: Length,
  minFontSize?: Length,
  heightAdaptivePolicy?: TextHeightAdaptivePolicy,
  font?: Font
}

@Entry
@Component
struct ButtonLevel3Example {
  pathStack: NavPathStack = new NavPathStack()
  @State label1: string = '文字会变'
  @State label2: string = 'A'
  @State clip1?: boolean = undefined
  @State align1?: Alignment = undefined
  @State labelStyle?: LabelStyle = undefined
  private index: number = 0
  private lastIndex: number = -1
  @State info?: string = undefined
  @State show: boolean = false
  private sets: Array<setsObject> = [
    {
      // 预期在满足最大行数为2的基础上，从最大字体往最小字体调整，直到最小字体还不满足生效超长裁切属性。若button内空间有富余，则生效align属性
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.Ellipsis, //文本超长后的裁剪方式
        maxLines: 2, //文本最大行数
        maxFontSize: 30, // 最大字号
        minFontSize: 9, // 最小字号
        heightAdaptivePolicy: TextHeightAdaptivePolicy.MAX_LINES_FIRST,
        font: { size: 20 }
      },
      align1: Alignment.TopStart
    },
    {
      // 预期优先以最小字体去按1行来部署，若部不下，则增加1行，用尽量小的字体去部署。最多不超过2行。仍部不下，则生效裁切
      label1: '新文本111',
      labelStyle: {
        overflow: TextOverflow.Clip,
        maxLines: 2, //文本最大行数
        maxFontSize: 32, // 最大字号
        minFontSize: 25, // 最小字号
        heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
        font: { size: undefined }
      },
      align1: Alignment.BottomEnd
    },
    {
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.MARQUEE, // button内不生效，预期需要生效或者走默认值Eclipse
        maxLines: 1,
        maxFontSize: 30,
        minFontSize: 25,
        heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
        font: { size: undefined }
      },
      align1: Alignment.Start
    },
    {
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.MARQUEE,
        maxLines: 2,
        maxFontSize: 30,
        minFontSize: 30,
        heightAdaptivePolicy: TextHeightAdaptivePolicy.MAX_LINES_FIRST,
        font: { size: 16 }
      },
      align1: Alignment.End
    },
    {
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.None, //文本超长后的裁剪方式
        maxLines: 2, //文本最大行数
        maxFontSize: 32, // 最大字号
        minFontSize: 20, // 最小字号
        heightAdaptivePolicy: TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST,
        font: { size: 30 }
      },
      align1: undefined
    },
    {
      // minFontSize>maxFontSize时生效font
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.Ellipsis, //文本超长后的裁剪方式
        maxLines: 2, //文本最大行数
        maxFontSize: 20, // 最大字号
        minFontSize: 32, // 最小字号
        heightAdaptivePolicy: TextHeightAdaptivePolicy.MAX_LINES_FIRST,
        font: { size: 9 }
      },
      align1: Alignment.Center
    },
    {
      // minFontSize<0时生效font
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.Ellipsis, //文本超长后的裁剪方式
        maxLines: 2, //文本最大行数
        maxFontSize: 20, // 最大字号
        minFontSize: -2, // 最小字号
        heightAdaptivePolicy: TextHeightAdaptivePolicy.MAX_LINES_FIRST,
        font: { size: 9 }
      },
      align1: Alignment.Center
    },
    {
      // 验证maxLines font默认值
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.Ellipsis, //文本超长后的裁剪方式
        maxLines: -2, //文本最大行数
        maxFontSize: 20, // 最大字号
        minFontSize: 36, // 最小字号
        heightAdaptivePolicy: TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST,
        font: { size: undefined }
      },
      align1: Alignment.Center
    },
    {
      // 验证maxFontSize和minFontSize异常值
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.Ellipsis, //文本超长后的裁剪方式
        maxLines: -2, //文本最大行数
        maxFontSize: undefined, // 最大字号
        minFontSize: undefined, // 最小字号
        heightAdaptivePolicy: TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST,
        font: { size: undefined }
      },
      align1: Alignment.Center
    },
    {
      // 验证maxFontSize和minFontSize不传入时的场景
      label1: '新文本',
      labelStyle: {
        overflow: TextOverflow.Ellipsis, //文本超长后的裁剪方式
        maxLines: -2, //文本最大行数
        heightAdaptivePolicy: TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST,
        font: { size: undefined }
      },
      align1: Alignment.Center
    },
  ]

  private setParam(): void {
    // 1. 参数赋值
    this.label1 = this.sets[this.index].label1
    this.labelStyle = this.sets[this.index].labelStyle
    this.align1 = this.sets[this.index].align1
    // 2. 参数打印
    try {
      this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
        '\nlabel1: ' + this.label1 + '\nlabelStyle-overflow: ' + TextOverflow[this.labelStyle.overflow!] +
        '\nlabelStyle-maxLines-maxFont-minFont: ' +
      this.labelStyle.maxLines + '; ' + this.labelStyle.maxFontSize + '; ' + this.labelStyle.minFontSize +
        '\nlabelStyle-heightAdaptivePolicy: ' +
      TextHeightAdaptivePolicy[this.labelStyle.heightAdaptivePolicy!] + '\nlabelStyle-font: ' +
      this.labelStyle.font!.size + '\nalign: ' + Alignment[this.align1!]
    } catch (e) {
      this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
        '\nlabel1: ' + this.label1 + '\nlabelStyle: ' + 'undefined' + '\nalign: ' + Alignment[this.align1!]
    }
    console.log('setParam done')
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('切换测试参数,显示参数=' + this.show)
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .onClick(() => {
              this.show = !this.show
              try {
                this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.lastIndex + 1) +
                  '\nlabel1: ' + this.label1 + '\nlabelStyle-overflow: ' + TextOverflow[this.labelStyle!.overflow!] +
                  '\nlabelStyle-maxLines-maxFont-minFont: ' +
                this.labelStyle!.maxLines + '; ' + this.labelStyle!.maxFontSize + '; ' + this.labelStyle!.minFontSize +
                  '\nlabelStyle-heightAdaptivePolicy: ' +
                TextHeightAdaptivePolicy[this.labelStyle!.heightAdaptivePolicy!] + '\nlabelStyle-font: ' +
                this.labelStyle!.font!.size + '\nalign: ' + Alignment[this.align1!]
              } catch (e) {
                this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
                  '\nlabel1: ' + this.label1 + '\nlabelStyle: ' + 'undefined' + '\nalign: ' + Alignment[this.align1!]
              }
              console.log('this is done')
            })
          Row({ space: 2 }) {
            Text(`${this.sets.length}`)
              .key('button11')
            MyComponent({
              title: 'Test++', func: () => {
                this.setParam()
                this.lastIndex = this.index
                // 控制循环
                this.index++
                if (this.index == this.sets.length) {
                  this.index = 0
                }
              }
            })

            MyComponent({
              title: 'Test--', func: () => {
                // 控制循环
                this.index--
                if (this.index == -1) {
                  this.index = this.sets.length - 1
                }
                this.setParam()
                this.lastIndex = this.index
              }
            })
          }

          Divider()
            .strokeWidth('1px')

          Text('参照字号')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            Text('主题')
            Text('16文本').fontSize(16)
            Text('9文本').fontSize(9)
            Text('20文本').fontSize(20)
            Text('25文本').fontSize(25)
            Text('30文本').fontSize(30)
          }

          Divider()
            .strokeWidth('1px')
          Text('1 不使用labelStyle时')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 5 }) {
            Button('短文本')
            Button('1文本截断').width(80)
            Button('2百分比尺寸文字变小').width('20%')
            Button(this.label1)
              .width('30%')
              .aspectRatio(3)
          }

          Text('2 使用labelStyle时, button1不设宽高，button2只设宽，button3设置宽高，button4只设置宽支持点击改变内容，button5设置宽高支持点击改变内容')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          // button1 不设置宽高，预期会自适应，上下左右有正常的内边距
          Button('长文本长文本长文本长文本长文本长文本长文本长文本长文本长文本长文本长文本长文本长文本长文本长文本')
            .labelStyle(this.labelStyle)
          //.labelStyle({ maxLines: 2, maxFontSize: 30, minFontSize: 20 })
          Button('文本文本文文本文文本文本文文本文本文')//一行能放5个30号字体，8个20号字体
            .width('60%')
            .labelStyle(this.labelStyle)
          Text('下边这个配合align使用')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Button('文本文本文本文本')
            .width('60%')//一行能放5个30号字体，8个20号字体
            .labelStyle(this.labelStyle)
            .align(this.align1)
          //.labelStyle({ 'overflow': TextOverflow.Marquee, 'maxLines': 2, 'maxFontSize': 30, 'minFontSize': 30 })
          Button(this.label2)
            .width(100)
            .backgroundColor(Color.Orange)
            .margin(5)
          Text('下边这个配合align使用,点击button支持改变button的label内容')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Button(this.label2)
            .id('button_aa')
            .backgroundColor(Color.Orange)
            .align(this.align1)
            .onClick(() => {
              this.label2 = this.label2 + 'The expert in anything was once a beginner.'
              this.align1 = Alignment.End
            })
            .aspectRatio(3)
            .height('10%')
            .labelStyle({
              'maxLines': 2,
              'maxFontSize': 30,
              'minFontSize': 20,
              heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST
            })
          Divider()
            .strokeWidth('1px')
          if (this.show) {
            Text(this.info)
              .fontSize(9)
              .width('60%')
          }
        }
        .padding(10)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel3')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}