/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textBindSelectionMenuTest from '../MyTest/TextBindSelectionMenuTest'

@Entry
@Component
struct TextBindSelectionMenuSample {
  controller: TextController = new TextController()
  options: TextOptions = { controller: this.controller }
  @State textSpanTypeMenuValue: TextSpanType = TextSpanType.IMAGE
  @State textResponseType: TextResponseType = TextResponseType.LONG_PRESS

  aboutToAppear(): void {
    loadComponentTestEntry(textBindSelectionMenuTest)
  }

  build() {
    Column() {
      Text(undefined, this.options) {
        Span('test1')
        ImageSpan($r('app.media.startIcon'))
          .width('50px')
          .height('50px')
      }
      .copyOption(CopyOptions.InApp)
      .bindSelectionMenu(TextSpanType.IMAGE, this.testImageMenu, TextResponseType.RIGHT_CLICK, {
        onDisappear: () => {
          console.info(`自定义选择菜单关闭时回调`);

        },
        onAppear: () => {
          console.info(`自定义选择菜单弹出时回调`);
        }
      })
      .id('textBindSelectionMenu1')

      Button('TextBindSelectionMenu')
        .onClick(() => {
          this.textSpanTypeMenuValue = TextSpanType.MIXED
          this.textResponseType = TextResponseType.SELECT
        })
      Text('text2text2text2text2text2text2text2text2')
        .copyOption(CopyOptions.InApp)
        .bindSelectionMenu(TextSpanType.TEXT, this.testMenu, TextResponseType.LONG_PRESS)
        .id('textBindSelectionMenu2')
    }
  }

  @Builder
  testMenu() {
    Column() {
      Menu() {
        MenuItemGroup() {
          MenuItem({ content: "Menu1", labelInfo: "" })
          MenuItem({ content: "Menu2", labelInfo: "" })
        }
      }
    }
  }

  @Builder
  testImageMenu() {
    Column() {
      Menu() {
        MenuItemGroup() {
          MenuItem({ startIcon: $r('app.media.app_icon'), content: "Menu1", labelInfo: "" })
          MenuItem({ startIcon: $r('app.media.app_icon'), content: "Menu2", labelInfo: "" })
        }
      }
    }
  }
}