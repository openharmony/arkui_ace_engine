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

import Want from '@ohos.app.ability.Want';
import { ComponentContent } from '@kit.ArkUI';

@Builder
export function NavIndexBuilder(name: string, param: Object) {
  UIExtensionTest()
}

interface Rect {
  x: number;
  y: number;
  w: number;
  h: number;
}

interface RectMap {
  top: Rect,
  bottom: Rect,
  left: Rect,
  right: Rect,
  full: Rect
}

type rectName = keyof RectMap

const RECTS: RectMap = {
  top: { x: 0, y: 0, w: 100, h: 50 },
  bottom: { x: 0, y: 50, w: 100, h: 50 },
  left: { x: 0, y: 0, w: 50, h: 100 },
  right: { x: 50, y: 0, w: 50, h: 100 },
  full: { x: 0, y: 0, w: 100, h: 100 },
};

@Component
struct ButtonRect {
  text: string = ''
  @Prop selected: boolean = false
  onClickCallback: () => void = () => {}

  build() {
    Button(this.text)
      .type(ButtonType.ROUNDED_RECTANGLE)
      .borderRadius(2)
      .size({ width: 80, height: 40 })
      .margin(5)
      .backgroundColor(this.selected ? Color.Blue : Color.Pink)
      .onClick(this.onClickCallback)
  }
}

@Component
struct UIExtensionConfig {
  onConfirm: (rect: Rect) => void = () => {};

  @State rectKey: rectName = 'full';
  @State rect: Rect = RECTS.full

  updateSelectRect(key: rectName, rect: Rect) {
    this.rectKey = key
    this.rect = rect
  }


  build() {
    Stack() {
      Column()
        .border({width: 1, color: Color.Red })
        .offset({ x: `${this.rect.x}%`, y: `${this.rect.y}%`})
        .width(`${this.rect.w}%`)
        .height(`${this.rect.h}%`)

      Column() {
        Text('设置UIExtension显示区域')
          .fontWeight(FontWeight.Bold)

        Row() {
          ButtonRect({
            text: 'full',
            selected: this.rectKey === 'full',
            onClickCallback: () => {
              this.updateSelectRect('full', RECTS.full)
            }
          })

          ButtonRect({
            text: 'top',
            selected: this.rectKey === 'top',
            onClickCallback: () => {
              this.updateSelectRect('top', RECTS.top)
            }
          })

          ButtonRect({
            text: 'bottom',
            selected: this.rectKey === 'bottom',
            onClickCallback: () => {
              this.updateSelectRect('bottom', RECTS.bottom)
            }
          })

          ButtonRect({
            text: 'left',
            selected: this.rectKey === 'left',
            onClickCallback: () => {
              this.updateSelectRect('left', RECTS.left)
            }
          })

          ButtonRect({
            text: 'right',
            selected: this.rectKey === 'right',
            onClickCallback: () => {
              this.updateSelectRect('right', RECTS.right)
            }
          })
        }
        .margin({  top: 20, bottom: 20 })

        Button('进入UIExtension页面')
          .type(ButtonType.Capsule)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.onConfirm(this.rect)
          })
      }
      .height('100%')
      .width('100%')
      .justifyContent(FlexAlign.Center)

    }
    .width('100%')
    .height('100%')
    .alignContent(Alignment.TopStart)
  }
}

class Params {}

@Builder
function loadingBuilder(params: Params) {
  Column() {
    LoadingProgress()
      .color(Color.Blue)
      .width(200)
      .height(200)
  }
}

@Component
struct UIExtensionPage {
  private want: Want = {
    bundleName : 'com.example.overlay',
    abilityName: 'UIExtensionProvider',
    parameters: {
      'ability.want.params.uiExtensionType': 'sys/commonUI'
    }
  }
  private initPlaceholder = new ComponentContent(this.getUIContext(), wrapBuilder(loadingBuilder), new Params);

  build() {
    UIExtensionComponent(this.want, {
        placeholder: this.initPlaceholder,
      })
      .width('100%')
      .height('100%')
      .border({width: 1, color: Color.Red})
      .onReceive((data) => {
        console.info('Lee onReceive, for test')
      })
      .onTerminated((info) => {
        console.info('onTerminated: code =' + info.code + ', want = ' + JSON.stringify(info.want));
      })
      .onRemoteReady((proxy) => {
        console.info('onRemoteReady, for test')
      })
      .onError((err) => {
        AlertDialog.show({
          message: `Start ui extension ability failed, code: ${err.code}`
        })
        console.info('onError: err =' + JSON.stringify(err));
      })
  }
}

@Entry
@Component
struct UIExtensionTest {
  pathStack: NavPathStack = new NavPathStack()
  uiExtRect: Rect = { x: 0, y: 0, w: 100, h: 100 }

  @State isInit: boolean = false

  build() {
    NavDestination() {
      Column() {
        if (!this.isInit) {
          UIExtensionConfig({ onConfirm: (rect: Rect) => {
            this.isInit = true;
            this.uiExtRect = rect
          }})
        } else {
          UIExtensionPage()
            .border({width: 1, color: Color.Red })
            .offset({ x: `${this.uiExtRect.x}%`, y: `${this.uiExtRect.y}%`})
            .width(`${this.uiExtRect.w}%`)
            .height(`${this.uiExtRect.h}%`)
        }
      }
      .justifyContent(FlexAlign.Start)
      .alignItems(HorizontalAlign.Start)
    }
    .title('UEC')
    .height('100%')
    .width('100%')
    .hideTitleBar(this.isInit)
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}