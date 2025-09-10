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
struct EditMenuOptions {
  // 定义onCreateMenu，onMenuItemClick
  onCreateMenu = (menuItems: Array<TextMenuItem>) => {
    // $r('app.media.app_icon')需要替换为开发者所需的图像资源文件。
    let item1: TextMenuItem = {
      content: 'customMenu1',
      icon: $r('app.media.app_icon'),
      id: TextMenuItemId.of('customMenu1'),
    };
    let item2: TextMenuItem = {
      content: 'customMenu2',
      id: TextMenuItemId.of('customMenu2'),
      icon: $r('app.media.app_icon'),
    };
    menuItems.push(item1);
    menuItems.unshift(item2);
    return menuItems;
  }

  onMenuItemClick = (menuItem: TextMenuItem, textRange: TextRange) => {
    if (menuItem.id.equals(TextMenuItemId.of('customMenu2'))) {
      console.log('拦截 id: customMenu2 start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }
    if (menuItem.id.equals(TextMenuItemId.COPY)) {
      console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }
    if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
      console.log('不拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end);
      return false;
    }
    return false;
  };

  build() {
    Text('这是一段文本，用来展示选中菜单')
      .fontSize(20)
      .copyOption(CopyOptions.LocalDevice)
      .editMenuOptions({
        onCreateMenu: this.onCreateMenu, onMenuItemClick: this.onMenuItemClick
      })
  }
}