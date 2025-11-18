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

import { Constants } from './Utils/Constants'

@Entry
@Component
struct attributeDemo {
  @State privacySensitive: boolean = true
  @State str: string = "true"
  caseText: string = 'ArkUI&HDS_Text__privacySensitive_'
  caseImage: string = 'ArkUI&HDS_Image__privacySensitive_'

  build() {
    Column() {
      Text("【基础能力】Text/Image控件支持卡片隐私遮罩框架")
      Button("privacySensitive 取反(用于测试动态切换)").onClick(() => {
        this.privacySensitive = !this.privacySensitive;
      }).borderColor(Color.Pink)
        .height("10%")
      List({ space: 5 }) {

        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseText, 1))
              .margin({ top: 15 })
            Text("Text 加载中文、英文、数字、换行符合与特殊符号 privacySensitive: " + this.privacySensitive.valueOf())
              .margin({ top: 15 })
            Text(`
111
222中
文333中${"\n"}333
444
ABC中
文!@#
$%^${"\n"}&*(
)_+
`)
              .privacySensitive(this.privacySensitive)
              .margin({ top: 15, bottom: 15 })
              .fontColor($r('app.color.text_font_color'))
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')

        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseText, 2))
              .margin({ top: 15 })
            Text('Text privacySensitive: ' + !this.privacySensitive.valueOf())
              .margin({ top: 15 })
            Text('Hello World')
              .privacySensitive(!this.privacySensitive)
              .margin({ top: 15, bottom: 15 })
              .fontColor($r('app.color.text_font_color'))
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')

        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseText, 3))
              .margin({ top: 15 })
            Text('Text 下划线样式 privacySensitive: ' + this.privacySensitive.valueOf())
              .margin({ top: 15 })
            Text('Hello World')
              .privacySensitive(this.privacySensitive)
              .margin({ top: 15, bottom: 15 })
              .decoration({
                type: TextDecorationType.Underline,
                color: Color.Red
              })
              .fontColor($r('app.color.text_font_color'))
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')


        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseText, 4))
              .margin({ top: 15 })
            Text('Text 展示省略号 privacySensitive: ' + this.privacySensitive.valueOf())
              .margin({ top: 15 })
            // 超出maxLines展示省略号
            Text('This is set textOverflow to Ellipsis text content This is set textOverflow to Ellipsis text content.'.split('')
              .join('\u200B'))
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .maxLines(1)
              .fontSize(12)
              .border({ width: 1 })
              .padding(10)
              .privacySensitive(this.privacySensitive)
              .margin({ top: 15, bottom: 15 })
              .fontColor($r('app.color.text_font_color'))
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')


        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseImage, 1))
              .margin({ top: 15 })
            Text("Image privacySensitive: " + this.privacySensitive.valueOf())
              .margin({ top: 15 })
            Image($r("app.media.icon"))
              .borderWidth(1)
              .width(100)
              .height(100)
              .privacySensitive(this.privacySensitive)
              .margin({ top: 15, bottom: 15 })
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')

        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseImage, 2))
              .margin({ top: 15 })
            Text("Image privacySensitive: " + !this.privacySensitive.valueOf())
              .margin({ top: 15 })
            Image($r("app.media.icon"))
              .borderWidth(1)
              .width(100)
              .height(100)
              .privacySensitive(!this.privacySensitive)
              .margin({ top: 15, bottom: 15 })
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')

        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseImage, 3))
              .margin({ top: 15 })
            Text("Image 加载动图 privacySensitive: " + this.privacySensitive.valueOf())
              .margin({ top: 15 })
            Image($r("app.media.gif"))
              .width(100)
              .height(100)
              .privacySensitive(this.privacySensitive)
              .borderWidth(1)
              .margin({ top: 15, bottom: 15 })
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')

        ListItem() {
          Column() {
            Text(Constants.getCaseName(this.caseImage, 4))
              .margin({ top: 15 })
            Text("Image  使用alt加载图片 privacySensitive: " + this.privacySensitive.valueOf())
              .margin({ top: 15 })
            Image("https://www.example.com/xxx.png")// 直接加载网络地址，请填写一个具体的网络图片地址
              .alt($r('app.media.icon'))// 使用alt，在网络图片加载成功前使用占位图
              .width(100)
              .height(100)
              .privacySensitive(this.privacySensitive)
              .borderWidth(1)
              .margin({ top: 15, bottom: 15 })
          }
        }
        .borderWidth(1).borderColor(Color.Green)
        .margin({ top: 15 })
        .width('90%')
      }.height("90%")
      .alignListItem(ListItemAlign.Center)
    }
    .backgroundColor(Color.Orange)
  }
}