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

import { common, ConfigurationConstant } from '@kit.AbilityKit'

@Entry
@Component
struct AiPreview {
  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller };
  @State text: string[] = ["我的qq邮箱:12345678@qq.com", "网址:www.baidu.com", "备用手机:17824828800",
    "我的地址:江苏省南京市南研所232423453546", "日期：2025年6月12日"]
  @State enableDataDetectorArr: boolean[] = [true, false]
  @State enableDataDetectorNum: number = 0
  @State TextDataDetectorTypeVariable: TextDataDetectorType[] =
    [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL,
      TextDataDetectorType.ADDRESS, TextDataDetectorType.DATE_TIME]
  @State decorationAll: TextDecorationType[] =
    [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.Overline, TextDecorationType.LineThrough]
  @State decorationAllStr: string[] = ['None', 'Underline', 'Overline', 'LineThrough']
  @State decoration: number = 0
  @State fontColor: number = 0
  @State fontStyleAll: FontStyle[] = [FontStyle.Normal, FontStyle.Italic]
  @State fontStyleAllStr: string[] = ['FontStyle.Normal', 'FontStyle.Italic']
  @State fontStyle: number = 0
  @State fontSize: number = 0
  @State fontWeightAll: (FontWeight | string | number)[] =
    [FontWeight.Normal, FontWeight.Lighter, FontWeight.Regular, FontWeight.Medium, FontWeight.Bold, FontWeight.Bolder,
      300, 700, '11']
  @State fontWeightAllStr: (string | number)[] =
    ['Normal', 'Lighter', 'Regular', 'Medium', 'Bold', 'Bolder', 300, 700, '"11"']
  @State fontWeight: number = 0
  @State decorationColor: number = 0
  @State widthStr: number = 380
  @State copyOptionsArr: CopyOptions[] =
    [CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE, CopyOptions.None]
  @State copyOptionsStr: string[] =
    ['CopyOptions.InApp', 'CopyOptions.LocalDevice', 'CopyOptions.CROSS_DEVICE', 'CopyOptions.None']
  @State copyOptionsSum: number = 0
  @State AiPreview: boolean = true
  richEditorStyledStringController: RichEditorStyledStringController = new RichEditorStyledStringController()
  context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  ctx: common.ApplicationContext = this.context.getApplicationContext();

  build() {
    Column() {
      Scroll() {
        Column() {

          Row({ space: 10 }) {
            Button(this.enableDataDetectorArr[this.enableDataDetectorNum] == true ? '开启AI分析' : '关闭AI分析')
              .onClick(() => {
                this.enableDataDetectorNum++
                if (this.enableDataDetectorNum > (this.enableDataDetectorArr.length - 1)) {
                  this.enableDataDetectorNum = 0
                }
              })
            Button("Ai预览：" + this.AiPreview)
              .onClick(() => {
                this.AiPreview = !this.AiPreview
              })
            Button('识别电话号码').onClick(() => {
              this.TextDataDetectorTypeVariable = [TextDataDetectorType.PHONE_NUMBER]
            })
          }

          Row({ space: 10 }) {
            Button('识别网址').onClick(() => {
              this.TextDataDetectorTypeVariable = [TextDataDetectorType.URL]
            })
            Button('识别邮箱').onClick(() => {
              this.TextDataDetectorTypeVariable = [TextDataDetectorType.EMAIL]
            })
          }

          Row({ space: 10 }) {
            Button('识别地址').onClick(() => {
              this.TextDataDetectorTypeVariable = [TextDataDetectorType.ADDRESS]
            })
            Button('识别电话号码、网址').onClick(() => {
              this.TextDataDetectorTypeVariable = [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL]
            })
          }

          Row({ space: 10 }) {
            Button('识别电话、网址、邮箱').onClick(() => {
              this.TextDataDetectorTypeVariable =
                [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL]
            })

          }

          Row({ space: 10 }) {
            Button('识别电话、网址、邮箱、地址').onClick(() => {
              this.TextDataDetectorTypeVariable =
                [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL,
                  TextDataDetectorType.ADDRESS]
            })
          }

          Row({ space: 10 }) {
            Button('识别电话、网址、邮箱、地址、时间').onClick(() => {
              this.TextDataDetectorTypeVariable =
                [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL,
                  TextDataDetectorType.ADDRESS, TextDataDetectorType.DATE_TIME]
            })
          }

          Row({ space: 10 }) {
            Button("字体粗细" + this.fontWeightAllStr[this.fontWeight]).onClick(() => {
              this.fontWeight++
              if (this.fontWeight > (this.fontWeightAll.length - 1)) {
                this.fontWeight = 0
              }
            })
            Button('减小文本框宽度').onClick(() => {
              this.widthStr = this.widthStr - 10
            })
          }

          Row({ space: 10 }) {
            Button("复制类型" + this.copyOptionsStr[this.copyOptionsSum]).onClick(() => {
              this.copyOptionsSum++
              if (this.copyOptionsSum > (this.copyOptionsStr.length - 1)) {
                this.copyOptionsSum = 0
              }

            })
          }

          Row() {
            Button('深色：').onClick(() => {
              this.ctx.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK)
            })
            Button('浅色：').onClick(() => {
              this.ctx.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT)
            })

          }
        }
      }.borderWidth(1)
      .borderColor(Color.Red)
      .width("100%")
      .height("30%")


      RichEditor(this.options)
        .padding(20)
        .placeholder("非属性字符串模式富文本组件")
        .copyOptions(this.copyOptionsArr[this.copyOptionsSum])
        // .copyOptions(CopyOptions.None)
        .width(this.widthStr)
        .enableDataDetector(this.enableDataDetectorArr[this.enableDataDetectorNum])
        .dataDetectorConfig({
          types: this.TextDataDetectorTypeVariable,
          onDetectResultUpdate: (result: string) => {
            console.log("###FSM: result = " + result);
          },
          enablePreviewMenu: this.AiPreview
        })
        .onReady(() => {
          this.controller.addTextSpan(this.text[1] + '\n' + this.text[0],
            {
              style:
              {
                fontColor: Color.Black,
                fontSize: 20
              }
            })
          this.controller.addTextSpan(this.text[3] + ', ' + this.text[2] + '\n',
            {
              style:
              {
                fontColor: Color.Black,
                fontSize: 20
              }
            })
        })
        .borderWidth(2)
        .borderColor(Color.Green)
        .height("30%")
      RichEditor({ controller: this.richEditorStyledStringController })
        .padding(20)
        .placeholder("属性字符串富文本")
        .copyOptions(this.copyOptionsArr[this.copyOptionsSum])
        // .copyOptions(CopyOptions.None)
        .width(this.widthStr)
        .enableDataDetector(this.enableDataDetectorArr[this.enableDataDetectorNum])
        .dataDetectorConfig({
          types: [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL,
            TextDataDetectorType.ADDRESS, TextDataDetectorType.DATE_TIME],
          color: Color.Yellow,
          decoration: {
            type: TextDecorationType.Overline
          },
          enablePreviewMenu: this.AiPreview
        })
        .borderWidth(2)
        .borderColor(Color.Black)
        .height("30%")
      Text("普通文本 13253817323")
        .fontSize(30)
        .enableDataDetector(true)
        .dataDetectorConfig({
          types: [],
          enablePreviewMenu: this.AiPreview
        })
        .copyOption(this.copyOptionsArr[this.copyOptionsSum])
        .borderWidth(2)
        .borderColor(Color.Blue)
    }.borderWidth(1)
    .borderColor(Color.Red)
    .width("100%")
    .height("100%")
  }
}
