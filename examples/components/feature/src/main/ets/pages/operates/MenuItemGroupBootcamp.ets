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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { ColorBlock, IconBlock, RadioBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct MenuItemGroupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableStartIcon: boolean = false;
  @State startIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State enableEndIcon: boolean = false;
  @State endIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State labelNum: number = 2;
  @State enableLabelNum: boolean = false;
  @State showSecondaryMenu: boolean = false;
  @State enableMenuItemGroupRadius: boolean = false;
  @State menuItemGroupRadius: number = 0;
  @State enableMenuItemGroupBackgroundColor: boolean = false;
  @State menuItemGroupBackgroundColor: ResourceStr = '#E5000000';
  @State enableMenuItemGroupOpacity: boolean = false;
  @State menuItemGroupOpacity: number = 1;
  @State enableMenuItemGroupVisibility: boolean = true;
  @State menuItemGroupVisibility: Visibility = Visibility.Visible;
  @State enableMenuItemGroupPadding: boolean = false;
  @State menuItemGroupPadding: number = 0;
  @State enableMenuItemGroupMargin: boolean = false;
  @State menuItemGroupMargin: number = 0;
  @State enableMenuItemGroupWidth: boolean = false;
  @State menuItemGroupWidth: number = 100;
  @State enableMenuItemGroupHeight: boolean = false;
  @State menuItemGroupHeight: number = 250;

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
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({
        startIcon: useEnabled<ResourceStr>(this.enableStartIcon, this.startIcon),
        content: '菜单选项1',
        endIcon: useEnabled<ResourceStr>(this.enableEndIcon, this.endIcon),
        builder: useEnabled<CustomBuilder>(this.showSecondaryMenu,
          this.showSecondaryMenu ? (): void => this.SubMenu() : undefined),
      })
      MenuItemGroup({ header: '标题显示'
      ,footer:'尾部显示'}){
        MenuItem({
          startIcon: useEnabled<ResourceStr>(this.enableStartIcon, this.startIcon),
          content: '菜单选项2',
          endIcon: useEnabled<ResourceStr>(this.enableEndIcon, this.endIcon),
          builder: useEnabled<CustomBuilder>(this.showSecondaryMenu,
            this.showSecondaryMenu ? (): void => this.SubMenu() : undefined),
        })

        MenuItem({
          startIcon: useEnabled<ResourceStr>(this.enableStartIcon, this.startIcon),
          content: '菜单选项3',
          endIcon: useEnabled<ResourceStr>(this.enableEndIcon, this.endIcon),
          builder: useEnabled<CustomBuilder>(this.showSecondaryMenu,
            this.showSecondaryMenu ? (): void => this.SubMenu() : undefined),
        })
      }
      .borderRadius(useEnabled<number>(this.enableMenuItemGroupRadius, this.menuItemGroupRadius))
      .width(useEnabled<number>(this.enableMenuItemGroupWidth, this.menuItemGroupWidth))
      .height(useEnabled<number>(this.enableMenuItemGroupHeight, this.menuItemGroupHeight))
      .backgroundColor(useEnabled<ResourceStr>(this.enableMenuItemGroupBackgroundColor,
        this.menuItemGroupBackgroundColor))
      .opacity(useEnabled<number>(this.enableMenuItemGroupOpacity, this.menuItemGroupOpacity))
      .visibility(useEnabled<Visibility>(this.enableMenuItemGroupVisibility, this.menuItemGroupVisibility))
      .padding(useEnabled<number>(this.enableMenuItemGroupPadding, this.menuItemGroupPadding))
      .margin(useEnabled<number>(this.enableMenuItemGroupMargin, this.menuItemGroupMargin))
    }
  }

  @Builder
  Content() {
    Column() {
      Button(
        this.enableLabelNum ? '弹出菜单'.repeat(this.labelNum / 2) : '弹出菜单',
      )
        .bindMenu(this.MyMenu)
    }
    .onDragStart(() => {
      ContextMenu.close()
    })
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'secondaryMenu',
          isEnabled: this.showSecondaryMenu,
          value: this.showSecondaryMenu,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        IconBlock({
          title: 'startIcon',
          isEnabled: $enableStartIcon,
          icon: $startIcon,
        })

        IconBlock({
          title: 'endIcon',
          isEnabled: $enableEndIcon,
          icon: $endIcon,
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableMenuItemGroupRadius,
          value: $menuItemGroupRadius,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableMenuItemGroupWidth,
          value: $menuItemGroupWidth,
          min: 100,
          max: 150
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableMenuItemGroupHeight,
          value: $menuItemGroupHeight,
          min: 250,
          max: 450
        })

        SliderBlock({
          title: 'padding',
          isEnabled: $enableMenuItemGroupPadding,
          value: $menuItemGroupPadding,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableMenuItemGroupMargin,
          value: $menuItemGroupMargin,
          min: 0,
          max: 16
        })

        ColorBlock({
          title: 'BackgroundColor',
          isEnabled: $enableMenuItemGroupBackgroundColor,
          color: $menuItemGroupBackgroundColor,
        })

        SliderBlock({
          title: 'Opacity',
          isEnabled: $enableMenuItemGroupOpacity,
          value: $menuItemGroupOpacity,
          step: 0.1,
          min: 0,
          max: 1
        })

        RadioBlock({
          title: 'Visibility',
          isEnabled: $enableMenuItemGroupVisibility,
          value: $menuItemGroupVisibility,
          dataSource: [
            { label: 'Visible', value: Visibility.Visible },
            { label: 'Hidden', value: Visibility.Hidden }
          ]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct BindMenuBootcampPreviewer {
  build() {
    MenuItemGroupBootcamp({
      title: '菜单分组/MenuItemGroup'
    })
  }
}