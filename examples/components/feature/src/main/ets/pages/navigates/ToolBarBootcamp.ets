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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct ToolBarBootcamp {
  @Provide('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @State hideItemValue: boolean = false;
  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'menuItem1',
      icon: 'resources/base/media/icon.svg' // 图标资源路径
    },
    {
      value: 'menuItem2',
      icon: 'resources/base/media/icon.svg' // 图标资源路径
    },
    {
      value: 'menuItem3',
      icon: 'resources/base/media/icon.svg' // 图标资源路径
    },
  ]
  @State toolItems: Array<ToolbarItem> = [
    {
      value: 'toolItem1',
      icon: 'resources/base/media/icon.svg', // 图标资源路径
      status: ToolbarItemStatus.ACTIVE,
      activeIcon: 'resources/base/media/icon.svg',
      action: () => {
      }
    },
    {
      value: 'toolItem2',
      icon: 'resources/base/media/icon1.svg', // 图标资源路径
      status: ToolbarItemStatus.DISABLED,
      action: () => {
      }
    },
    {
      value: 'toolItem3',
      icon: 'resources/base/media/icon2.svg', // 图标资源路径
      activeIcon: 'resources/base/media/icon2.svg',
      action: () => {
      }
    },
    {
      value: 'toolItem4',
      icon: 'resources/base/media/text_bold.svg', // 图标资源路径
      activeIcon: 'resources/base/media/text_bold.svg',
      action: () => {
      }
    },
    {
      value: 'toolItem5',
      icon: 'resources/base/media/text_color.svg', // 图标资源路径
      activeIcon: 'resources/base/media/text_color.svg',
      action: () => {
      }
    },
    {
      value: 'toolItem6',
      icon: 'resources/base/media/text_title.svg', // 图标资源路径
      activeIcon: 'resources/base/media/text_title.svg',
      action: () => {
      }
    }
  ]

  @Require @Prop title: ResourceStr;
  @State navigationMode: NavigationMode = NavigationMode.Stack;
  @State enableToolBarAdaptation: boolean = false;
  @State showParameters: boolean = false;
  @State enableNavigationMode: boolean = false;
  @State enableAdaptation: boolean = false;
  @State enableHideItem: boolean = false;
  private scrollerForScroll: Scroller = new Scroller();

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Scroll(this.scrollerForScroll) {
      Column() {
        Navigation(this.navPathStack) {
          Column() {
            Text('我是Navigation主页面内容')
          }
        }
        .titleMode(NavigationTitleMode.Mini)
        .menus(this.menuItems)
        .toolbarConfiguration(this.toolItems, {backgroundBlurStyle: BlurStyle.Thick, hideItemValue:this.hideItemValue})
        .title('一级页面')
        .hideTitleBar(false)
        .enableToolBarAdaptation(this.enableToolBarAdaptation)
        .mode(this.navigationMode)
      }.width('100%').height('100%')
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '设置无字模式',
          isEnabled: this.enableHideItem,
          value: this.hideItemValue,
          dataSource: [{ label: '无字模式开', value: true }, { label: '无字模式关', value: false }]
        })

        RadioBlock({
          title: '是否开启自适应',
          isEnabled: this.enableAdaptation,
          value: this.enableToolBarAdaptation,
          dataSource: [{ label: '是', value: true }, { label: '否', value: false }]
        })

        RadioBlock({
          title: '选择navigation模式',
          isEnabled: this.enableNavigationMode,
          value: this.navigationMode,
          dataSource: [
            { label: '堆栈', value: NavigationMode.Stack },
            { label: '分栏', value: NavigationMode.Split },
            { label: '自动', value: NavigationMode.Auto }]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct ToolBarBootcampPreviewer {
  build() {
    ToolBarBootcamp({ title: '工具栏/ToolBar' })
  }
}