import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  $r,
  LengthMetrics,
  Entry,
  Builder,
  PopInfo,
  SheetOptions,
  BlurStyleActivePolicy,
  SheetSize,
  SheetMode,
  AdaptiveColor,
  NavBarPosition,
  NavDestinationCustomTitle,
  Resource,
  ResourceStr,
  CustomBuilder,
  BlurStyle,
  AnimateParam,
  ResourceColor,
  NavigationAnimatedTransition,
  NavigationTransitionProxy,
  NavContentInfo,
  NavigationOperation,
  NavigationTitleOptions,
  NavigationInterception,
  NavigationCustomTitle,
  ToolbarItemStatus,
  Callback,
  Text,
  ToolbarItem,
  TextAttribute,
  SymbolGlyphModifier,
  BarStyle,
  Image,
  Color,
  Row,
  Column,
  NavDestinationCommonTitle,
  Component,
  Button,
  ButtonAttribute,
  Scroll,
  ClickEvent,
  UserView,
  Curve,
  NavPathStack,
  Navigation,
  LayoutSafeAreaEdge,
  LaunchMode,
  NavigationMenuItem,
  NavPathInfo,
  NavDestination,
  LayoutSafeAreaType,
  NavigationMode,
  NavigationOptions,
  NavigationTitleMode,
  NavigationCommonTitle,
  NavDestinationMode,
  NavDestinationContext,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import { UIContext } from '@ohos.arkui.UIContext'

import { routerParam, NavigationParam, pathStack } from './BaseDataMode'

@Component
export struct PageTwo {
  build() {
    NavDestination() {
      Column(undefined) {
        Button('replacePath pageOne').onClick((e?: ClickEvent) => {
          let info: NavPathInfo = new NavPathInfo('pageOne', new NavigationParam('pageOne '))
          pathStack.replacePath(info, {animated: true} as NavigationOptions)
        })
      }
    }
    .title('PageTwo')
  }
}

@Component
export struct PageOne {
  build() {
    NavDestination() {
      Column(undefined) {
        Text('Text测试')
          .fontSize(12)
      }
    }
    .title('PageOne')
  }
}

@Entry
@Component
export struct NavigationTest {
  build() {
    NavDestination() {
      Column(undefined) {
        Button('push path pageTwo').onClick((e?: ClickEvent) => {
          let info: NavPathInfo = new NavPathInfo('pageTwo', new NavigationParam('pageTwo'))
          pathStack.pushPath(info, undefined)
        })
      }
    }
    .title('导航类组件测试001')
  }
}

