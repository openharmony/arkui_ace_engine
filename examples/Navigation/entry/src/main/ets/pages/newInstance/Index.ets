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

import router from '@ohos.router';
import common from '@ohos.app.ability.common';
import { uiObserver } from '@kit.ArkUI';
import { UIAbility, WantAgent, wantAgent, wantConstant } from '@kit.AbilityKit';

export class Tool {
  static count = 0;
}

@Entry
@Component
struct Index {
  @State count: number = Tool.count
  wantAgent = true
  ctx: common.UIAbilityContext | null = null

  aboutToAppear(): void {
    this.ctx = getContext(this) as common.UIAbilityContext;
    this.getUIContext().getUIObserver().on('routerPageUpdate', (info: uiObserver.RouterPageInfo) => {
      console.log('[observer] ' + info.name + '[' + info.index + ']' + ' state: ' + info.state)
    })
    this.getUIContext().getUIObserver().on('navDestinationUpdate', (info: uiObserver.NavDestinationInfo) => {
      console.log(JSON.stringify(info));
    })
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Column() {
        Text('Home Page')
          .fontSize(35)
          .fontWeight(FontWeight.Bold)
      }

      MyButton({
        text: 'new_instance Test',
        onClickFunction: () => {
          router.pushUrl({ url: 'pages/36-ssasdadsadsa/forcedNewInstance/NewInstance' })
        },
        backGdColor: Color.Pink
      })
    }
    .width('100%')
    .height('100%')
  }
}

@Component
export struct MyButton {
  text: string = ''
  onClickFunction: (event: ClickEvent) => void = ()=>{}
  backGdColor = '#ccc'

  build() {
    Button() {
      Text(this.text)
        .fontSize(25)
        .fontWeight(FontWeight.Bold)
    }.type(ButtonType.Capsule)
    .margin({ top: 20 })
    .onClick(this.onClickFunction)
    .backgroundColor(this.backGdColor)
  }
}

@Component
export struct PageOne {
  stack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Button('pop + push PageOne').onClick(() => {
        this.stack.pop()
        this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
      })
    }.title('Page One')
    .onReady((ctx) => {
      this.stack = ctx.pathStack
    })
  }
}
