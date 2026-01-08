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

import { LengthMetrics, SymbolGlyphModifier } from '@kit.ArkUI';

@Entry
@Component
struct outlineBindMenu {
  @State private menuOutlineWidthIndex: number = 0;
  @State private menuOutlineColorIndex: number = 0;
  @State private isShowNormalContextMenu: boolean = false;
  @State private isShowContextMenu: boolean = false;
  @State private isEnableArrow: boolean = false;
  private outlineWidthArr: (Dimension | EdgeOutlineWidths | undefined) [] =
    ['1vp', '3vp', '1px', '3px', undefined];
  private outlineColorArr: (ResourceColor | EdgeColors | undefined)[] =
    [Color.Transparent, Color.Red, undefined];
  private iconStr: ResourceStr = $r('app.media.app_icon');
  private menuElements: MenuElement[] = [
    {
      value: 'Menu1',
      action: () => {
      }
    },
    {
      value: 'Menu2',
      action: () => {
      }
    },
    {
      value: 'Menu3',
      action: () => {
      }
    }
  ];

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ symbolStartIcon: new SymbolGlyphModifier($r('sys.symbol.cut')), content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder
  preview() {
    Row() {
      Image($r('app.media.app_icon'))
        .width(24)
        .height(24)
    }
    .width('100%')
    .padding({
      start: LengthMetrics.resource($r('sys.float.padding_level8'))
    })
    .height(64)
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项',
        builder: (): void => this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '菜单选项',
          symbolEndIcon: new SymbolGlyphModifier($r('sys.symbol.chevron_right')),
          builder: (): void => this.SubMenu()
        })
        MenuItem({
          startIcon: this.iconStr,
          symbolEndIcon: new SymbolGlyphModifier($r('sys.symbol.chevron_right')),
          content: '菜单选项',
          builder: (): void => this.SubMenu()
        })
      }
    }
  }

  @Builder
  testComponent() {
    Column({ space: 20 }) {
      Button('BindMenu')
        .width('60%')
        .fontSize($r('sys.float.ohos_id_text_size_button1'))
        .type(ButtonType.Normal)
        .buttonStyle(ButtonStyleMode.NORMAL)
        .borderRadius($r('sys.float.corner_radius_level4'))
        .bindMenu(this.menuElements, {
          title: 'BindMenuTest',
          enableArrow: this.isEnableArrow,
          showInSubWindow: true,
          outlineColor: this.outlineColorArr[this.menuOutlineColorIndex],
          outlineWidth: this.outlineWidthArr[this.menuOutlineWidthIndex]
        })

      Button('BindContextMenu')
        .width('60%')
        .fontSize($r('sys.float.ohos_id_text_size_button1'))
        .type(ButtonType.Normal)
        .buttonStyle(ButtonStyleMode.NORMAL)
        .borderRadius($r('sys.float.corner_radius_level4'))
        .bindContextMenu(this.isShowContextMenu, this.MyMenu, {
          onDisappear: () => {
            this.isShowContextMenu = false;
          },
          placement: Placement.BottomLeft,
          enableArrow: this.isEnableArrow,
          outlineColor: this.outlineColorArr[this.menuOutlineColorIndex],
          outlineWidth: this.outlineWidthArr[this.menuOutlineWidthIndex]
        })
        .onClick(() => {
          this.isShowContextMenu = !this.isShowContextMenu;
        })
    }
  }

  private updateIndex(index: number, length: number): number {
    let tmp: number = (index + 1) % length;
    return tmp;
  }

  @Builder
  operateButton() {
    Column({ space: 10 }) {
      Button(this.isEnableArrow ? 'DisableArrow' : 'EnableArrow')
        .width('100%')
        .onClick(() => {
          this.isEnableArrow = !this.isEnableArrow;
        })
      Button(`updateMenuOutlineColor: ${this.outlineColorArr[this.menuOutlineColorIndex]}`)
        .width('100%')
        .onClick(() => {
          this.menuOutlineColorIndex = this.updateIndex(this.menuOutlineColorIndex, this.outlineColorArr.length);
        })
      Button(`updateMenuOutlineWidth: ${this.outlineWidthArr[this.menuOutlineWidthIndex]}`)
        .width('100%')
        .onClick(() => {
          this.menuOutlineWidthIndex = this.updateIndex(this.menuOutlineWidthIndex, this.outlineWidthArr.length);
        })
    }
    .margin({
      top: $r('sys.float.padding_level36')
    })
  }

  build() {
    Column() {
      this.testComponent()
      this.operateButton()
    }
  }
}