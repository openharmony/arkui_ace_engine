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

import { curves } from '@kit.ArkUI';

export class ParamClass {
  public count: number = 10
  public onBackClicked?: () => void
}

@Component
export struct IndexImmersive {
  @Consume('pageInfos') pageInfos: NavPathStack;

  aboutToAppear() {
  }

  build() {
    NavDestination() {
      Column() {
        Column() {
          Row() {
            Text('==========操作==========\n' +
              '1、点击Search进入Search页面\n' +
              '2、点击“<”回退到主页面\n' +
              '3、重复操作1和2共3次\n' +
              '==========期望==========\n' +
              '1、Search页面时，Search组件的竖线，在搜索按钮前，不会在搜索按钮后面\n')
          }

          Row() {
            Search({ placeholder: '搜索' })
              .id('.Search.placeholder')
              .width(352)
              .height(40)
              .defaultFocus(false)
              .focusOnTouch(false)
              .focusable(false)
              .margin({ left: 16, right: 16 })
              .searchIcon({ color: '#99000000' })
              .backgroundColor('#00000000')
              .placeholderColor('#99000000')
              .backgroundBlurStyle(1, {
                colorMode: ThemeColorMode.LIGHT,
                adaptiveColor: AdaptiveColor.DEFAULT,
                scale: 0.5
              })
              .geometryTransition('transitionId123', { follow: true })
              .onClick(() => {
                this.handleSearchClicked('GRID_SEARCH_CLICK_ACTION', '搜索...')
              })
              .onPaste((value: string, event: PasteEvent) => {
                event.preventDefault!();
              })
          }
          .height(56)
          .margin({ top: 30 })
          .offset({ y: 0 })

        }
        .height('100%')
      }
      .width('100%')
      .height('100%')
      .backgroundColor(0xDCDCDC)
      .padding({ top: 5 })
      .transition(TransitionEffect.OPACITY)
    }
    .onBackPressed(() => {
      this.pageInfos.pop()
      return true;
    })
    .hideTitleBar(true)
    .transition(TransitionEffect.scale({ x: 0.999, y: 0.999 }))
  }

  transitionOpacity2(): TransitionEffect {
    return TransitionEffect.OPACITY
      .animation({ curve: curves.interpolatingSpring(0, 1, 342, 38) })
      .combine(TransitionEffect.OPACITY.animation({ curve: curves.cubicBezierCurve(0.4, 0, 0.2, 1), duration: 100 }))
  }

  onBackClicked() {
    animateTo({
      duration: 350,
    }, () => {
    });
  }

  handleSearchClicked(actionType: string, placeholder?: string) {
    animateTo({
      delay: 0,
      duration: 100,
      curve: curves.cubicBezierCurve(0.2, 0, 0.2, 1)
    }, () => {
    });

    animateTo({
      duration: 1000,
    }, () => {
      let tmp = new ParamClass()
      this.pageInfos.pushPathByName('searchIndex', tmp, false)
    });
  }
}