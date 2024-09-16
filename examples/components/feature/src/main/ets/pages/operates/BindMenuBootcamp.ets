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
export struct BindMenuBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableAllowUse: boolean = false;
  @State allowUse: boolean = true;
  @State enableStartIcon: boolean = false;
  @State startIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State enableEndIcon: boolean = false;
  @State endIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State labelNum: number = 2
  @State enableLabelNum: boolean = false
  @State showSecondaryMenu: boolean = false

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
       .enabled(useEnabled<boolean>(this.enableAllowUse, this.allowUse))
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
      MenuItem({
        startIcon: useEnabled<ResourceStr>(this.enableStartIcon, this.startIcon),
        content: '菜单选项4',
        endIcon: useEnabled<ResourceStr>(this.enableEndIcon, this.endIcon),
        builder: useEnabled<CustomBuilder>(this.showSecondaryMenu,
          this.showSecondaryMenu ? (): void => this.SubMenu() : undefined),
      })
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
      .onDragStart(()=>{
        ContextMenu.close()
      })
    }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
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

      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct BindMenuBootcampPreviewer {
  build(){
    BindMenuBootcamp({
      title: '菜单/Menu'
    })
  }
}
