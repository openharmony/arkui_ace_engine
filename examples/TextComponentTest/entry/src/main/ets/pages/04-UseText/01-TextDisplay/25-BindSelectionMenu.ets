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

@Entry
@Component
struct BindSelectionMenu {
  // 定义菜单项
  @Builder
  RightClickTextCustomMenu() {
    Column() {
      Menu() {
        MenuItemGroup() {
          // $r('app.media.app_icon')需要替换为开发者所需的图像资源文件。
          MenuItem({ startIcon: $r('app.media.app_icon'), content: 'CustomMenu One', labelInfo: '' })
            .onClick(() => {
              // 使用closeSelectionMenu接口关闭菜单
              this.controller.closeSelectionMenu();
            })
          MenuItem({ startIcon: $r('app.media.app_icon'), content: 'CustomMenu Two', labelInfo: '' })
          MenuItem({ startIcon: $r('app.media.app_icon'), content: 'CustomMenu Three', labelInfo: '' })
        }
      }.backgroundColor('#F0F0F0')
    }
  }

  controller:TextController = new TextController()
  build() {
    Column() {
      Text('这是一段文本，用来展示选中菜单', {controller:this.controller})
        .fontSize(30)
        .copyOption(CopyOptions.InApp)
        .bindSelectionMenu(TextSpanType.TEXT, this.RightClickTextCustomMenu, TextResponseType.RIGHT_CLICK, {
          onAppear: () => {
            console.info('自定义选择菜单弹出时触发该回调');
          },
          onDisappear: () => {
            console.info('自定义选择菜单关闭时触发该回调');
          }
        })
    }
  }
}