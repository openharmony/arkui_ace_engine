/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct Cancel {
  @State message: string = 'Hello World';

  build() {
    Column() {
      Text(this.message)
        .id('HelloWorld') 
        .fontSize($r('app.float.page_text_font_size')) // 引用应用内浮点型字体大小资源
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
        .onClick(() => {
          this.message = 'Welcome';
        })

      // 图片1：固定位置(x:100,y:200)，小尺寸图标，点击修改文本为'OnClick1'
      Image($r("app.media.startIcon"))
        .position({ x: 100, y: 200 }) 
        .key("dsdsdsdsdsd") 
        .size({width:30,height:30}) 
        .backgroundColor("#ff9d9d9d") 
        .borderRadius(4.8) // 圆角4.8
        .padding(5)
        .draggable(false) // 禁止拖拽
        .focusable(true).focusOnTouch(true)
        .onClick((event: ClickEvent) => {
          this.message = "OnClick1"; // 点击修改文本内容
          console.error("____________________")
        })

      // 图片2：固定位置(x:200,y:430)，大尺寸图标，点击修改文本为'OnClick2'
      Image($r("app.media.ic_page_empty"))
        .position({ x: 200, y: 430 })
        .key("dsdsdsdsdsd")
        .size({width:150,height:150}) // 尺寸150x150
        .backgroundColor("#ff9d9d9d")
        .borderRadius(4.8)
        .borderWidth(1) // 边框宽度1
        .draggable(false)
        .focusable(true).focusOnTouch(true)
        .onClick((event: ClickEvent) => {
          this.message = "OnClick2";
          console.error("____________________")
        })

      // 图片3：固定位置(x:200,y:200)，大尺寸带内边距，点击修改文本为'OnClick3'
      Image($r("app.media.ic_page_empty"))
        .position({ x: 200, y: 200 })
        .key("dsdsdsdsdsd")
        .size({width:150,height:150})
        .backgroundColor("#ff9d9d9d")
        .borderRadius(4.8)
        .padding(50) // 内边距50（会挤压图片内容）
        .borderWidth(1)
        .draggable(false)
        .focusable(true).focusOnTouch(true)
        .onClick((event: ClickEvent) => {
          this.message = "OnClick3";
          console.error("____________________")
        })

      // 图片4：固定位置(x:300,y:200)，小尺寸图标，点击修改文本为'OnClick4'
      Image($r("app.media.startIcon"))
        .position({ x: 300, y: 200 })
        .key("dsdsdsdsdsd")
        .size({width:30,height:30})
        .backgroundColor("#ff9d9d9d")
        .borderRadius(4.8)
        .draggable(false)
        .focusable(true).focusOnTouch(true)
        .onClick((event: ClickEvent) => {
          this.message = "OnClick4";
          console.error("____________________")
        })
    }
    .height('100%')
    .width('100%')
  }
}