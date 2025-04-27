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

import curves from '@ohos.curves';
import { Route, RouteGroup } from 'common/src/main/ets/common/route';
import { KeyboardAvoidMode } from '@kit.ArkUI';
import { blankAndDividerDestination, blankAndDividerRoute } from 'feature/src/main/ets/pages/BlankAndDivider';
import {
  rowsColumnsAndStackingDestination,
  rowsColumnsAndStackingRoute
} from 'feature/src/main/ets/pages/RowsColumnsAndStacking'
import {
  gridAndColumnLayoutDestination,
  gridAndColumnLayoutRoute
} from 'feature/src/main/ets/pages/GridAndColumnLayout'
import { scrollAndSwipeDestination, scrollAndSwipeRoute } from 'feature/src/main/ets/pages/ScrollAndSwipe'
import {
  navigationAndSwitchingDestination,
  navigationAndSwitchingRoute
} from 'feature/src/main/ets/pages/NavigationAndSwitching'
import {
  buttonsAndSelectionsDestination,
  buttonsAndSelectionsRoute
} from 'feature/src/main/ets/pages/ButtonsAndSelections'
import { textAndInputDestination, textAndInputRoute } from 'feature/src/main/ets/pages/TextAndInput'
import { imagesAndVideosDestination, imagesAndVideosRoute } from 'feature/src/main/ets/pages/ImagesAndVideos'
import { informationDisplayDestination, informationDisplayRoute } from 'feature/src/main/ets/pages/InformationDisplay'
import { menusDestination, menusRoute } from 'feature/src/main/ets/pages/Menus'
import { dialogBoxesDestination, dialogBoxesRoute } from 'feature/src/main/ets/pages/DialogBoxes'

@Styles
function CardPressedStyle() {
  .backgroundColor('rgba(0,0,0,0.1)')
  .opacity(1)
  .animation({ curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1), duration: 100 })
}

@Styles
function CardNormalStyle() {
  .backgroundColor('rgba(0,0,0,0)')
  .opacity(1)
  .animation({ curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1), duration: 100 })

}

@Styles
function CardDisabledStyle() {
  .backgroundColor('rgba(0,0,0,0)')
  .opacity(0.5)
  .animation({ curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1), duration: 100 })
}

@Builder
function Destination(name: string, route: Route) {
  if (name.startsWith('BlankAndDivider/')) {
    blankAndDividerDestination(name, route)
  } else if (name.startsWith('RowsColumnsAndStacking/')) {
    rowsColumnsAndStackingDestination(name, route)
  } else if (name.startsWith('GridAndColumnLayout/')) {
    gridAndColumnLayoutDestination(name, route)
  } else if (name.startsWith('ScrollAndSwipe/')) {
    scrollAndSwipeDestination(name, route)
  } else if (name.startsWith('NavigationAndSwitching/')) {
    navigationAndSwitchingDestination(name, route)
  } else if (name.startsWith('ButtonsAndSelections/')) {
    buttonsAndSelectionsDestination(name, route)
  } else if (name.startsWith('TextAndInput/')) {
    textAndInputDestination(name, route)
  } else if (name.startsWith('ImagesAndVideos/')) {
    imagesAndVideosDestination(name, route)
  } else if (name.startsWith('InformationDisplay/')) {
    informationDisplayDestination(name, route)
  } else if (name.startsWith('Menus/')) {
    menusDestination(name, route)
  } else if (name.startsWith('DialogBoxes/')) {
    dialogBoxesDestination(name, route)
  }
}

@Entry
@Component
struct Index {
  @Provide('router') router: NavPathStack = new NavPathStack();
  @State routes: RouteGroup[] = [
    blankAndDividerRoute,
    rowsColumnsAndStackingRoute,
    gridAndColumnLayoutRoute,
    scrollAndSwipeRoute,
    navigationAndSwitchingRoute,
    buttonsAndSelectionsRoute,
    textAndInputRoute,
    imagesAndVideosRoute,
    informationDisplayRoute,
    menusRoute,
    dialogBoxesRoute
  ];
  @State selection: string | null = null;

  @Builder
  ListItemGroupHeader(route: RouteGroup) {
    Row() {
      Text(route.label)
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .fontWeight(FontWeight.Medium)

      Blank()

      Text(`${route.children.length}`)
        .fontColor($r('sys.color.ohos_id_color_text_secondary'))
        .opacity(this.selection === route.name ? 0 : 1)

      Image($r('sys.media.ohos_ic_public_arrow_right'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(24)
        .width(24)
        .rotate({ angle: this.selection === route.name ? 90 : 0 })
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 30) })
    }
    .borderRadius(20)
    .width('100%')
    .padding({
      left: 8,
      right: 8,
      top: 18,
      bottom: 18
    })
    .enabled(!!route.children.length)
    .stateStyles({
      pressed: CardPressedStyle,
      normal: CardNormalStyle,
      disabled: CardDisabledStyle,
    })
    .onClick(() => {
      animateTo(
        { curve: curves.interpolatingSpring(0, 1, 228, 25) },
        () => {
          if (this.selection === route.name) {
            this.selection = null;
          } else {
            this.selection = route.name;
          }
        });
    })
  }

  aboutToAppear(): void {
    this.getUIContext().setKeyboardAvoidMode(KeyboardAvoidMode.RESIZE);
  }

  build() {
    Navigation(this.router) {
      Text('ArkUI 是 OpenHarmony 的控件底座，这是一个 ArkUI 控件检视应用，你可以查阅目前版本的控件能力与默认样式。')
        .fontSize(16)
        .margin({ left: 16, right: 10, bottom: 24 })

      List({ space: 12 }) {
        ForEach(this.routes, (routeGroup: RouteGroup) => {
          ListItemGroup({
            header: this.ListItemGroupHeader(routeGroup),
            style: ListItemGroupStyle.CARD,
          }) {
            if (routeGroup.name === this.selection) {
              ForEach(routeGroup.children, (route: Route) => {
                ListItem() {
                  Row() {
                    Text(route.label).fontSize(16)
                    Blank()
                    Image($r('sys.media.ohos_ic_public_arrow_right'))
                      .fillColor($r('sys.color.ohos_id_color_fourth'))
                      .height(24)
                      .width(24)
                  }
                  .stateStyles({
                    pressed: CardPressedStyle,
                    normal: CardNormalStyle,
                    disabled: CardDisabledStyle,
                  })
                  .borderRadius(20)
                  .padding({
                    left: 8,
                    right: 8,
                    top: 13,
                    bottom: 13
                  })
                  .transition(
                    TransitionEffect.OPACITY.animation({
                      curve: curves.interpolatingSpring(0, 1, 228, 30)
                    })
                  )
                  .width('100%')
                  .onClick(() => {
                    const name = `${routeGroup.name}/${route.name}`;
                    const pathNames = this.router.getAllPathName();
                    if (pathNames[pathNames.length-1] !== name) {
                      this.router.pushPath({ name, param: route });
                    }
                  })
                }
                .width('100%')
              })
            }
          }
          .padding(4)
          .divider({ strokeWidth: 0.5 })
        })
      }.padding({ bottom: 70 })
    }
    .title('Component')
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .navDestination(Destination)
  }
}