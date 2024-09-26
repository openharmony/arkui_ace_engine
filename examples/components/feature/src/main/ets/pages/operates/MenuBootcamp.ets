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
import { IconBlock, RadioBlock, useEnabled } from 'common';

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
        RadioBlock({
          title: '菜单组件布局方式',
          isEnabled: this.enableDirection,
          value: this.comDirection,
          dataSource: [
            { label: '跟随系统默认布局', value: Direction.Auto },
            { label: '从右到左', value: Direction.Rtl },
            { label: '从左到右', value: Direction.Ltr }
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