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

import window from '@ohos.window';
import base from '@ohos.base';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';

@Entry
@Component
export struct Navigation70 {
  private myWindow: window.Window | null = null;
  @State icon1: SymbolGlyphModifier= new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))

  createWindow() {
    try {
      window.createWindow({name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/NavigationAdaptationImage/Navigation6', ls)
              .then(() => {
                console.log(`testTag success to loadContent`)
              }).catch((e: base.BusinessError) => {
              console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
            })
          }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
          });
        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }

  build() {
    Column() {
      Navigation() {
        Button("createWindow").onClick(() => {
          this.createWindow();
        })
      }
      .title('Navigation5')
      .titleMode(NavigationTitleMode.Mini)
      .backButtonIcon(this.icon1)
      .subTitle("subtitle")
      .menus([
        {
          icon: 'resources/base/media/startIcon.png',
          value: 'item1',
        },
        {
          value: 'item2',
          icon: 'resources/base/media/startIcon.png',
        }
      ])
      .toolbarConfiguration([
        {
          value: 'first',
          icon: $r('app.media.startIcon')
        },
        {
          value: 'second',
          icon: $r('app.media.startIcon')
        },
        {
          value: 'third',
          icon: $r('app.media.startIcon')
        },
        {
          value: '44444',
          icon: $r('app.media.startIcon')
        },
        {
          value: '55555',
          icon: $r('app.media.startIcon')
        },
        {
          value: '66666',
          icon: $r('app.media.startIcon')
        },
        {
          value: '77777',
          icon: $r('app.media.startIcon')
        }
      ])
      .hideTitleBar(false)
      .hideToolBar(false)
      .onTitleModeChange((titleModel: NavigationTitleMode) => {
        console.info('titleMode' + titleModel)
      })
    }
  }
}

