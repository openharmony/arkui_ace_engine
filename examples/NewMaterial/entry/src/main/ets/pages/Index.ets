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

@Entry
@Component
struct Index {
  build() {
    Column() {
      Text("UnionContainer")
      Button("ets")
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({ url: "pages/PageEts" })
        })
      Button("modifier")
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({ url: "pages/PageModifier" })
        })
      Button("property")
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({ url: "pages/PageProperty" })
        })
      Button("ux")
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({ url: "pages/PageUx" })
        })

      Button("page1")
        .width(200)
        .height(100)
        .onClick(() => {
          let router = this.getUIContext().getRouter();
          router.pushUrl({ url: "pages/Page1" });
        })
      Button("page2")
        .width(200)
        .height(100)
        .onClick(() => {
          let router = this.getUIContext().getRouter();
          router.pushUrl({ url: "pages/Page2" });
        })
      Button("page3")
        .width(200)
        .height(100)
        .onClick(() => {
          let router = this.getUIContext().getRouter();
          router.pushUrl({ url: "pages/Page3" });
        })
      Button("textInput")
        .width(200)
        .height(100)
        .onClick(() => {
          let router = this.getUIContext().getRouter();
          router.pushUrl({ url: "pages/PageTextInput" });
        })
      Button("docs")
        .width(200)
        .height(100)
        .onClick(() => {
          let router = this.getUIContext().getRouter();
          router.pushUrl({ url: "pages/PageDocs" });
        })

      Button("page11")
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({ url: "pages/Page11" });
        })
      Button("pageBlender")
        .onClick(() => {
          this.getUIContext().getRouter().pushUrl({ url: "pages/PageBlender" });
        })
    }
    .height('100%')
    .width('100%')
  }
}