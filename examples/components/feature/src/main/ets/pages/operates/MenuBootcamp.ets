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
import { LengthMetrics } from '@kit.ArkUI';

@Component
export struct MenuBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableStartIcon: boolean = false;
  @State startIcon: boolean = false;
  @State startIconStr: ResourceStr = $r('app.media.startIcon');
  @State enableEndIcon: boolean = false;
  @State endIcon: boolean = false;
  @State endIconStr: ResourceStr = $r('sys.media.ohos_ic_public_arrow_right');
  @State enableSelect: boolean = false;
  @State select: boolean = false;
  @State enableSelect2: boolean = false;
  @State select2: boolean = false;
  @State enableSelect3: boolean = false;
  @State select3: boolean = false;
  @State enableSelect4: boolean = false;
  @State select4: boolean = false;
  @State enableDirection: boolean = false;
  @State comDirection: Direction = Direction.Auto;
  @State enableSelectIcon: boolean = false;
  @State selectIcon: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableSelectIcon2: boolean = false;
  @State selectIcon2: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableSelectIcon3: boolean = false;
  @State selectIcon3: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableSelectIcon4: boolean = false;
  @State selectIcon4: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableMenuFontSize: boolean = false;
  @State menuFontSize: number = 16;
  @State enableMenuFontWeight: boolean = false;
  @State menuFontWeight: FontWeight = FontWeight.Medium;
  @State enableMenuFontStyle: boolean = false;
  @State menuFontStyle: FontStyle = FontStyle.Normal;
  @State enableMenuFontColor: boolean = false;
  @State menuFontColor: ResourceStr = '#E5000000';
  @State enableMenuRadius: boolean = false;
  @State menuRadius: number = 0;
  @State enableMenuWidth: boolean = false;
  @State menuWidth: number = 100;
  @State enableMenuHeight: boolean = false;
  @State menuHeight: number = 250;
  @State enableMenuItemDividerStrokeWidth: boolean = false;
  @State menuItemDividerStrokeWidth: number = 1;
  @State enableMenuItemDividerColor: boolean = false;
  @State menuItemDividerColor: ResourceStr = '#E5000000';
  @State enableMenuItemDividerStartMargin: boolean = false;
  @State menuItemDividerStartMargin: number = 16;
  @State enableMenuItemDividerEndMargin: boolean = false;
  @State menuItemDividerEndMargin: number = 16;
  @State enableMenuItemGroupDividerStrokeWidth: boolean = false;
  @State menuItemGroupDividerStrokeWidth: number = 1;
  @State enableMenuItemGroupDividerColor: boolean = false;
  @State menuItemGroupDividerColor: ResourceStr = '#E5000000';
  @State enableMenuItemGroupDividerStartMargin: boolean = false;
  @State menuItemGroupDividerStartMargin: number = 16;
  @State enableMenuItemGroupDividerEndMargin: boolean = false;
  @State menuItemGroupDividerEndMargin: number = 16;
  @State enableSubMenuExpandingMode: boolean = false;
  @State subMenuExpandingMode: SubMenuExpandingMode = SubMenuExpandingMode.SIDE_EXPAND;
  @State enableMenuBackgroundColor: boolean = false;
  @State menuBackgroundColor: ResourceStr = '#E5000000';
  @State enableMenuOpacity: boolean = false;
  @State menuOpacity: number = 1;
  @State enableMenuVisibility: boolean = true;
  @State menuVisibility: Visibility = Visibility.Visible;
  @State enableMenuPadding: boolean = false;
  @State menuPadding: number = 0;
  @State enableMenuMargin: boolean = false;
  @State menuMargin: number = 0;

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
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' }).direction(useEnabled(this.enableDirection, this.comDirection))
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' }).direction(useEnabled(this.enableDirection, this.comDirection))
    }
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({
        startIcon: useEnabled(this.startIcon, this.startIconStr),
        content: '菜单选项1',
        endIcon: useEnabled(this.endIcon, this.endIconStr),
        builder: () => {
          this.SubMenu()
        }
      })
        .selected(useEnabled(this.enableSelect, this.select))
        .selectIcon(useEnabled(this.enableSelectIcon, this.selectIcon))
        .direction(useEnabled(this.enableDirection, this.comDirection))

      MenuItem({
        startIcon: useEnabled(this.startIcon, this.startIconStr),
        content: '菜单选项2',
        endIcon: useEnabled(this.endIcon, this.endIconStr),
        builder: () => {
          this.SubMenu()
        }
      })
        .selected(useEnabled(this.enableSelect2, this.select2))
        .selectIcon(useEnabled(this.enableSelectIcon2, this.selectIcon2))
        .direction(useEnabled(this.enableDirection, this.comDirection))

      MenuItem({
        startIcon: useEnabled(this.startIcon, this.startIconStr),
        content: '菜单选项3',
        endIcon: useEnabled(this.endIcon, this.endIconStr),
      })
        .selected(useEnabled(this.enableSelect3, this.select3))
        .selectIcon(useEnabled(this.enableSelectIcon3, this.selectIcon3))
        .direction(useEnabled(this.enableDirection, this.comDirection))

      MenuItem({
        startIcon: useEnabled(this.startIcon, this.startIconStr),
        content: '菜单选项4',
        endIcon: useEnabled(this.endIcon, this.endIconStr),
      })
        .selected(useEnabled(this.enableSelect4, this.select4))
        .selectIcon(useEnabled(this.enableSelectIcon4, this.selectIcon4))
        .direction(useEnabled(this.enableDirection, this.comDirection))
    }
    .font({
      size: useEnabled(this.enableMenuFontSize, this.menuFontSize),
      family: 'HarmonyOS Sans',
      weight: useEnabled(this.enableMenuFontWeight, this.menuFontWeight),
      style: useEnabled(this.enableMenuFontStyle, this.menuFontStyle)
    })
    .fontColor(useEnabled(this.enableMenuFontColor, this.menuFontColor))
    .radius(useEnabled(this.enableMenuRadius, this.menuRadius))
    .width(useEnabled(this.enableMenuWidth, this.menuWidth))
    .height(useEnabled(this.enableMenuHeight, this.menuHeight))
    .menuItemDivider({
      strokeWidth: useEnabled(this.enableMenuItemDividerStrokeWidth, LengthMetrics.vp(this.menuItemDividerStrokeWidth)),
      color: useEnabled(this.enableMenuItemDividerColor, this.menuItemDividerColor),
      startMargin: useEnabled(this.enableMenuItemDividerStartMargin, LengthMetrics.vp(this.menuItemDividerStartMargin)),
      endMargin: useEnabled(this.enableMenuItemDividerEndMargin, LengthMetrics.vp(this.menuItemDividerEndMargin))
    })
    .menuItemGroupDivider({
      strokeWidth: useEnabled(this.enableMenuItemGroupDividerStrokeWidth,
        LengthMetrics.vp(this.menuItemGroupDividerStrokeWidth)),
      color: useEnabled(this.enableMenuItemGroupDividerColor, this.menuItemGroupDividerColor),
      startMargin: useEnabled(this.enableMenuItemGroupDividerStartMargin,
        LengthMetrics.vp(this.menuItemGroupDividerStartMargin)),
      endMargin: useEnabled(this.enableMenuItemGroupDividerEndMargin,
        LengthMetrics.vp(this.menuItemGroupDividerEndMargin))
    })
    .subMenuExpandingMode(useEnabled(this.enableSubMenuExpandingMode, this.subMenuExpandingMode))
    .backgroundColor(useEnabled(this.enableMenuBackgroundColor, this.menuBackgroundColor))
    .opacity(useEnabled(this.enableMenuOpacity, this.menuOpacity))
    .visibility(useEnabled(this.enableMenuVisibility, this.menuVisibility))
    .padding(useEnabled(this.enableMenuPadding, this.menuPadding))
    .margin(useEnabled(this.enableMenuMargin, this.menuMargin))
  }

  @Builder
  Content() {
    Column() {
      Button('点击展示菜单')
        .bindMenu(this.MyMenu)
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: 'font.size',
          isEnabled: $enableMenuFontSize,
          value: $menuFontSize,
          min: 16,
          max: 24
        })

        RadioBlock({
          title: 'font.weight',
          isEnabled: $enableMenuFontWeight,
          value: $menuFontWeight,
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
          title: 'font.style',
          isEnabled: $enableMenuFontStyle,
          value: $menuFontStyle,
          dataSource: [
            { label: 'Normal', value: FontWeight.Lighter },
            { label: 'Italic', value: FontWeight.Normal }
          ]
        })

        ColorBlock({
          title: 'fontColor',
          isEnabled: $enableMenuFontColor,
          color: $menuFontColor,
        })

        SliderBlock({
          title: 'radius',
          isEnabled: $enableMenuRadius,
          value: $menuRadius,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableMenuWidth,
          value: $menuWidth,
          min: 100,
          max: 150
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableMenuHeight,
          value: $menuHeight,
          min: 250,
          max: 450
        })

        ColorBlock({
          title: 'menuItemDivider.color',
          isEnabled: $enableMenuItemDividerColor,
          color: $menuItemDividerColor,
        })

        SliderBlock({
          title: 'menuItemDivider.strokeWidth',
          isEnabled: $enableMenuItemDividerStrokeWidth,
          value: $menuItemDividerStrokeWidth,
          min: 1,
          max: 5
        })

        SliderBlock({
          title: 'menuItemDivider.startMargin',
          isEnabled: $enableMenuItemDividerStartMargin,
          value: $menuItemDividerStartMargin,
          min: 16,
          max: 32
        })

        SliderBlock({
          title: 'menuItemDivider.endMargin',
          isEnabled: $enableMenuItemDividerEndMargin,
          value: $menuItemDividerEndMargin,
          min: 16,
          max: 32
        })

        SliderBlock({
          title: 'menuItemGroupDivider.strokeWidth',
          isEnabled: $enableMenuItemGroupDividerStrokeWidth,
          value: $menuItemGroupDividerStrokeWidth,
          min: 1,
          max: 5
        })

        ColorBlock({
          title: 'menuItemGroupDivider.color',
          isEnabled: $enableMenuItemGroupDividerColor,
          color: $menuItemGroupDividerColor,
        })

        SliderBlock({
          title: 'menuItemGroupDivider.startMargin',
          isEnabled: $enableMenuItemGroupDividerStartMargin,
          value: $menuItemGroupDividerStartMargin,
          min: 16,
          max: 32
        })

        SliderBlock({
          title: 'menuItemGroupDivider.endMargin',
          isEnabled: $enableMenuItemGroupDividerEndMargin,
          value: $menuItemGroupDividerEndMargin,
          min: 16,
          max: 32
        })

        RadioBlock({
          title: 'SubMenuExpandingMode',
          isEnabled: $enableSubMenuExpandingMode,
          value: $subMenuExpandingMode,
          dataSource: [
            { label: 'SIDE_EXPAND', value: SubMenuExpandingMode.SIDE_EXPAND },
            { label: 'EMBEDDED_EXPAND', value: SubMenuExpandingMode.EMBEDDED_EXPAND },
            { label: 'STACK_EXPAND', value: SubMenuExpandingMode.STACK_EXPAND }
          ]
        })

        RadioBlock({
          title: 'direction',
          isEnabled: $enableDirection,
          value: $comDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Ltr', value: Direction.Ltr }
          ]
        })

        RadioBlock({
          title: '菜单项1是否选中',
          isEnabled: this.enableSelect,
          value: this.select,
          dataSource: [
            { label: '选中', value: true },
            { label: '取消', value: false }
          ]
        })

        if (this.select) {
          IconBlock({
            title: '是否显示选中图标',
            isEnabled: this.enableSelectIcon,
            icon: this.selectIcon,
          })
        }

        RadioBlock({
          title: '菜单项2是否选中',
          isEnabled: this.enableSelect2,
          value: this.select2,
          dataSource: [
            { label: '选中', value: true },
            { label: '取消', value: false }
          ]
        })

        if (this.select2) {
          IconBlock({
            title: '是否显示选中图标',
            isEnabled: this.enableSelectIcon2,
            icon: this.selectIcon2,
          })
        }

        RadioBlock({
          title: '菜单项3是否选中',
          isEnabled: this.enableSelect3,
          value: this.select3,
          dataSource: [
            { label: '选中', value: true },
            { label: '取消', value: false }
          ]
        })

        if (this.select3) {
          IconBlock({
            title: '是否显示选中图标',
            isEnabled: this.enableSelectIcon3,
            icon: this.selectIcon3,
          })
        }

        RadioBlock({
          title: '菜单项4是否选中',
          isEnabled: this.enableSelect4,
          value: this.select4,
          dataSource: [
            { label: '选中', value: true },
            { label: '取消', value: false }
          ]
        })

        if (this.select4) {
          IconBlock({
            title: '是否显示选中图标',
            isEnabled: this.enableSelectIcon4,
            icon: this.selectIcon4,
          })
        }

        RadioBlock({
          title: '是否显示前缀图标',
          isEnabled: this.enableStartIcon,
          value: this.startIcon,
          dataSource: [
            { label: '显示', value: true },
            { label: '隐藏', value: false }
          ]
        })

        RadioBlock({
          title: 'item中是否显示右侧图标',
          isEnabled: this.enableEndIcon,
          value: this.endIcon,
          dataSource: [
            { label: '显示', value: true },
            { label: '隐藏', value: false }
          ]
        })

        ColorBlock({
          title: 'BackgroundColor',
          isEnabled: $enableMenuBackgroundColor,
          color: $menuBackgroundColor,
        })

        SliderBlock({
          title: 'Opacity',
          isEnabled: $enableMenuOpacity,
          value: $menuOpacity,
          step: 0.1,
          min: 0,
          max: 1
        })

        RadioBlock({
          title: 'Visibility',
          isEnabled: $enableMenuVisibility,
          value: $menuVisibility,
          dataSource: [
            { label: 'Visible', value: Visibility.Visible },
            { label: 'Hidden', value: Visibility.Hidden }
          ]
        })

        SliderBlock({
          title: 'Padding',
          isEnabled: $enableMenuPadding,
          value: $menuPadding,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'Margin',
          isEnabled: $enableMenuMargin,
          value: $menuMargin,
          min: 0,
          max: 16
        })
      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct MenuBootcampPreviewer {
  build() {
    MenuBootcamp({
      title: '菜单/Menu'
    })
  }
}