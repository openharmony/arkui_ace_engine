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
export struct BindMenuBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableAllowUse: boolean = false;
  @State allowUse: boolean = true;
  @State enableStartIcon: boolean = false;
  @State startIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State enableEndIcon: boolean = false;
  @State endIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State labelNum: number = 2;
  @State enableLabelNum: boolean = false;
  @State showSecondaryMenu: boolean = false;
  @State menuItemSelected: boolean = false;
  @State enableMenuItemSelected: boolean = false;
  @State menuItemSelectIcon: ResourceStr | boolean = false;
  @State enableMenuItemSelectIcon: boolean = false;
  @State menuItemContentFontSize: number = 16;
  @State enableMenuItemContentFontSize: boolean = false;
  @State menuItemContentFontWeight: FontWeight = FontWeight.Normal;
  @State enableMenuItemContentFontWeight: boolean = false;
  @State menuItemContentFontStyle: FontStyle = FontStyle.Normal;
  @State enableMenuItemContentFontStyle: boolean = false;
  @State menuItemContentFontColor: ResourceStr = '#E5000000';
  @State enableMenuItemContentFontColor: boolean = false;
  @State menuItemContentLabelFontColor: ResourceStr = '#99000000';
  @State enableMenuItemContentLabelFontColor: boolean = false;
  @State menuItemLabelFontSize: number = 16;
  @State enableMenuItemLabelFontSize: boolean = false;
  @State menuItemLabelFontWeight: FontWeight = FontWeight.Normal;
  @State enableMenuItemLabelFontWeight: boolean = false;
  @State menuItemLabelFontStyle: FontStyle = FontStyle.Normal;
  @State enableMenuItemLabelFontStyle: boolean = false;
  @State menuItemBackgroundColor: ResourceStr = '#E5000000';
  @State enableMenuItemBackgroundColor: boolean = false;
  @State menuItemOpacity: number = 1;
  @State enableMenuItemOpacity: boolean = false;
  @State menuItemVisibility: Visibility = Visibility.Visible;
  @State enableMenuItemVisibility: boolean = true;
  @State menuItemPadding: number = 0;
  @State enableMenuItemPadding: boolean = false;
  @State menuItemMargin: number = 0;
  @State enableMenuItemMargin: boolean = false;
  @State menuItemRadius: number = 0;
  @State enableMenuItemRadius: boolean = false;
  @State menuItemWidth: number = 100;
  @State enableMenuItemWidth: boolean = false;
  @State menuItemHeight: number = 250;
  @State enableMenuItemHeight: boolean = false;

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
        .selected(useEnabled<boolean>(this.enableMenuItemSelected, this.menuItemSelected))
        .selectIcon(useEnabled<ResourceStr | boolean>(this.enableMenuItemSelectIcon, this.menuItemSelectIcon))
        .contentFont({
          size: useEnabled<number>(this.enableMenuItemContentFontSize, this.menuItemContentFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemContentFontWeight, this.menuItemContentFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemContentFontStyle, this.menuItemContentFontStyle),
        })
        .contentFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentFontColor, this.menuItemContentFontColor))
        .labelFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentLabelFontColor,
          this.menuItemContentLabelFontColor))
        .labelFont({
          size: useEnabled<number>(this.enableMenuItemLabelFontSize, this.menuItemLabelFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemLabelFontWeight, this.menuItemLabelFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemLabelFontStyle, this.menuItemLabelFontStyle),
        })
        .width(useEnabled<number>(this.enableMenuItemWidth, this.menuItemWidth))
        .height(useEnabled<number>(this.enableMenuItemHeight, this.menuItemHeight))
        .padding(useEnabled<number>(this.enableMenuItemPadding, this.menuItemPadding))
        .margin(useEnabled<number>(this.enableMenuItemMargin, this.menuItemMargin))
        .visibility(useEnabled<Visibility>(this.enableMenuItemVisibility, this.menuItemVisibility))
        .opacity(useEnabled<number>(this.enableMenuItemOpacity, this.menuItemOpacity))
        .backgroundColor(useEnabled<ResourceStr>(this.enableMenuItemBackgroundColor, this.menuItemBackgroundColor))
        .borderRadius(useEnabled<number>(this.enableMenuItemRadius, this.menuItemRadius))
        .enabled(useEnabled<boolean>(this.enableAllowUse, this.allowUse))

      MenuItem({
        startIcon: useEnabled<ResourceStr>(this.enableStartIcon, this.startIcon),
        content: '菜单选项2',
        endIcon: useEnabled<ResourceStr>(this.enableEndIcon, this.endIcon),
        builder: useEnabled<CustomBuilder>(this.showSecondaryMenu,
          this.showSecondaryMenu ? (): void => this.SubMenu() : undefined),
      })
        .selected(useEnabled<boolean>(this.enableMenuItemSelected, this.menuItemSelected))
        .selectIcon(useEnabled<ResourceStr | boolean>(this.enableMenuItemSelectIcon, this.menuItemSelectIcon))
        .contentFont({
          size: useEnabled<number>(this.enableMenuItemContentFontSize, this.menuItemContentFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemContentFontWeight, this.menuItemContentFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemContentFontStyle, this.menuItemContentFontStyle),
        })
        .contentFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentFontColor, this.menuItemContentFontColor))
        .labelFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentLabelFontColor,
          this.menuItemContentLabelFontColor))
        .labelFont({
          size: useEnabled<number>(this.enableMenuItemLabelFontSize, this.menuItemLabelFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemLabelFontWeight, this.menuItemLabelFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemLabelFontStyle, this.menuItemLabelFontStyle),
        })
        .width(useEnabled<number>(this.enableMenuItemWidth, this.menuItemWidth))
        .height(useEnabled<number>(this.enableMenuItemHeight, this.menuItemHeight))
        .padding(useEnabled<number>(this.enableMenuItemPadding, this.menuItemPadding))
        .margin(useEnabled<number>(this.enableMenuItemMargin, this.menuItemMargin))
        .visibility(useEnabled<Visibility>(this.enableMenuItemVisibility, this.menuItemVisibility))
        .opacity(useEnabled<number>(this.enableMenuItemOpacity, this.menuItemOpacity))
        .backgroundColor(useEnabled<ResourceStr>(this.enableMenuItemBackgroundColor, this.menuItemBackgroundColor))
        .borderRadius(useEnabled<number>(this.enableMenuItemRadius, this.menuItemRadius))
      MenuItem({
        startIcon: useEnabled<ResourceStr>(this.enableStartIcon, this.startIcon),
        content: '菜单选项3',
        endIcon: useEnabled<ResourceStr>(this.enableEndIcon, this.endIcon),
        builder: useEnabled<CustomBuilder>(this.showSecondaryMenu,
          this.showSecondaryMenu ? (): void => this.SubMenu() : undefined),
      })
        .selected(useEnabled<boolean>(this.enableMenuItemSelected, this.menuItemSelected))
        .selectIcon(useEnabled<ResourceStr | boolean>(this.enableMenuItemSelectIcon, this.menuItemSelectIcon))
        .contentFont({
          size: useEnabled<number>(this.enableMenuItemContentFontSize, this.menuItemContentFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemContentFontWeight, this.menuItemContentFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemContentFontStyle, this.menuItemContentFontStyle),
        })
        .contentFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentFontColor, this.menuItemContentFontColor))
        .labelFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentLabelFontColor,
          this.menuItemContentLabelFontColor))
        .labelFont({
          size: useEnabled<number>(this.enableMenuItemLabelFontSize, this.menuItemLabelFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemLabelFontWeight, this.menuItemLabelFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemLabelFontStyle, this.menuItemLabelFontStyle),
        })
        .width(useEnabled<number>(this.enableMenuItemWidth, this.menuItemWidth))
        .height(useEnabled<number>(this.enableMenuItemHeight, this.menuItemHeight))
        .padding(useEnabled<number>(this.enableMenuItemPadding, this.menuItemPadding))
        .margin(useEnabled<number>(this.enableMenuItemMargin, this.menuItemMargin))
        .visibility(useEnabled<Visibility>(this.enableMenuItemVisibility, this.menuItemVisibility))
        .opacity(useEnabled<number>(this.enableMenuItemOpacity, this.menuItemOpacity))
        .backgroundColor(useEnabled<ResourceStr>(this.enableMenuItemBackgroundColor, this.menuItemBackgroundColor))
        .borderRadius(useEnabled<number>(this.enableMenuItemRadius, this.menuItemRadius))
      MenuItem({
        startIcon: useEnabled<ResourceStr>(this.enableStartIcon, this.startIcon),
        content: '菜单选项4',
        endIcon: useEnabled<ResourceStr>(this.enableEndIcon, this.endIcon),
        builder: useEnabled<CustomBuilder>(this.showSecondaryMenu,
          this.showSecondaryMenu ? (): void => this.SubMenu() : undefined),
      })
        .selected(useEnabled<boolean>(this.enableMenuItemSelected, this.menuItemSelected))
        .selectIcon(useEnabled<ResourceStr | boolean>(this.enableMenuItemSelectIcon, this.menuItemSelectIcon))
        .contentFont({
          size: useEnabled<number>(this.enableMenuItemContentFontSize, this.menuItemContentFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemContentFontWeight, this.menuItemContentFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemContentFontStyle, this.menuItemContentFontStyle),
        })
        .contentFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentFontColor, this.menuItemContentFontColor))
        .labelFontColor(useEnabled<ResourceStr>(this.enableMenuItemContentLabelFontColor,
          this.menuItemContentLabelFontColor))
        .labelFont({
          size: useEnabled<number>(this.enableMenuItemLabelFontSize, this.menuItemLabelFontSize),
          weight: useEnabled<FontWeight>(this.enableMenuItemLabelFontWeight, this.menuItemLabelFontWeight),
          family: 'HarmonyOS Sans',
          style: useEnabled<FontStyle>(this.enableMenuItemLabelFontStyle, this.menuItemLabelFontStyle),
        })
        .width(useEnabled<number>(this.enableMenuItemWidth, this.menuItemWidth))
        .height(useEnabled<number>(this.enableMenuItemHeight, this.menuItemHeight))
        .padding(useEnabled<number>(this.enableMenuItemPadding, this.menuItemPadding))
        .margin(useEnabled<number>(this.enableMenuItemMargin, this.menuItemMargin))
        .visibility(useEnabled<Visibility>(this.enableMenuItemVisibility, this.menuItemVisibility))
        .opacity(useEnabled<number>(this.enableMenuItemOpacity, this.menuItemOpacity))
        .backgroundColor(useEnabled<ResourceStr>(this.enableMenuItemBackgroundColor, this.menuItemBackgroundColor))
        .borderRadius(useEnabled<number>(this.enableMenuItemRadius, this.menuItemRadius))
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
          title: 'selected',
          isEnabled: $enableMenuItemSelected,
          value: $menuItemSelected,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        IconBlock({
          title: 'SelectIcon',
          isEnabled: $enableMenuItemSelectIcon,
          icon: $menuItemSelectIcon
        })

        SliderBlock({
          title: 'contentFont.size',
          isEnabled: $enableMenuItemContentFontSize,
          value: $menuItemContentFontSize,
          min: 16,
          max: 24
        })

        RadioBlock({
          title: 'contentFont.weight',
          isEnabled: $enableMenuItemContentFontWeight,
          value: $menuItemContentFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })

        RadioBlock({
          title: 'contentFont.style',
          isEnabled: $enableMenuItemContentFontStyle,
          value: $menuItemContentFontStyle,
          dataSource: [
            { label: 'Normal', value: FontWeight.Lighter },
            { label: 'Italic', value: FontWeight.Normal }
          ]
        })

        ColorBlock({
          title: 'contentFontColor',
          isEnabled: $enableMenuItemContentFontColor,
          color: $menuItemContentFontColor,
        })

        ColorBlock({
          title: 'labelFontColor',
          isEnabled: $enableMenuItemContentLabelFontColor,
          color: $menuItemContentLabelFontColor,
        })

        SliderBlock({
          title: 'labelFont.size',
          isEnabled: $enableMenuItemLabelFontSize,
          value: $menuItemLabelFontSize,
          min: 16,
          max: 24
        })

        RadioBlock({
          title: 'labelFont.weight',
          isEnabled: $enableMenuItemLabelFontWeight,
          value: $menuItemLabelFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })

        RadioBlock({
          title: 'labelFont.style',
          isEnabled: $enableMenuItemLabelFontStyle,
          value: $menuItemLabelFontStyle,
          dataSource: [
            { label: 'Normal', value: FontWeight.Lighter },
            { label: 'Italic', value: FontWeight.Normal }
          ]
        })

        RadioBlock({
          title: '是否可用菜单',
          isEnabled: this.enableAllowUse,
          value: this.allowUse,
          dataSource: [
            { label: '允许', value: true },
            { label: '禁止', value: false },
          ]
        })

        RadioBlock({
          title: '是否允许显示二级菜单',
          isEnabled: this.showSecondaryMenu,
          value: this.showSecondaryMenu,
          dataSource: [
            { label: '允许', value: true },
            { label: '禁止', value: false },
          ]
        })

        IconBlock({
          title: '是否显示前缀图标',
          isEnabled: this.enableStartIcon,
          icon: this.startIcon,
        })

        IconBlock({
          title: '是否显示后缀图标',
          isEnabled: this.enableEndIcon,
          icon: this.endIcon,
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableMenuItemRadius,
          value: $menuItemRadius,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableMenuItemWidth,
          value: $menuItemWidth,
          min: 100,
          max: 150
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableMenuItemHeight,
          value: $menuItemHeight,
          min: 250,
          max: 450
        })

        SliderBlock({
          title: 'padding',
          isEnabled: $enableMenuItemPadding,
          value: $menuItemPadding,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableMenuItemMargin,
          value: $menuItemMargin,
          min: 0,
          max: 16
        })

        ColorBlock({
          title: 'BackgroundColor',
          isEnabled: $enableMenuItemBackgroundColor,
          color: $menuItemBackgroundColor,
        })

        SliderBlock({
          title: 'Opacity',
          isEnabled: $enableMenuItemOpacity,
          value: $menuItemOpacity,
          step: 0.1,
          min: 0,
          max: 1
        })

        RadioBlock({
          title: 'Visibility',
          isEnabled: $enableMenuItemVisibility,
          value: $menuItemVisibility,
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
    BindMenuBootcamp({
      title: '菜单/Menu'
    })
  }
}