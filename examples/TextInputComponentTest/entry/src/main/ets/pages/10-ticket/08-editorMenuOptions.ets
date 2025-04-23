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
struct editMenuOptions11 {
  @State text: string = '12345'

  onCreateMenu(menuItems: Array<TextMenuItem>) {
    let item1: TextMenuItem = {
      content: '设置超长文本选择菜单用户自定义文本custom1111111111111111111111111111111111111111111111111111111111', //超长菜单项内容
      icon: $r('app.media.startIcon'), //png
      id: TextMenuItemId.of('custom1'),
    }
    let item2: TextMenuItem = {
      content: 'custom22', //资源引用类型文本
      icon: $r('app.media.startIcon'), //svg
      id: TextMenuItemId.of('custom2'),
    }
    menuItems.push(item1)
    menuItems.push(item2)
    let menuItems1: TextMenuItem[] = [] //定义空数组
    menuItems.forEach((value, index) => {
      //删除粘贴与复制系统选项
      if (!value.id.equals(TextMenuItemId.PASTE) && !value.id.equals(TextMenuItemId.COPY)) {
        menuItems1.push(value)
      }
    })
    return menuItems1 //预期新增两个用户自定义选项，删除系统复制与粘贴按钮
  }

  onMenuItemClick(menuItem: TextMenuItem, textRange: TextRange) {
    return false
  }

  editMenuOptions: EditMenuOptions = { onCreateMenu: this.onCreateMenu, onMenuItemClick: this.onMenuItemClick }

  build() {
    Scroll() {
      Column({ space: 20 }) {

        Column() {
          Text('操作： 1、长按输入框弹出菜单;\n2、点击全选;\n3、点击菜单更多按钮;\n4、点击菜单返回按钮')
            .fontColor(Color.Blue)
          Text('Pass条件：2、点击全选后全选消失，“设置超长文本选择菜单...”省略出现;\n3、点击更多按钮切换正常;\n4、点击返回按钮返回操作2后的样式')
            .fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        TextInput({ text: this.text, placeholder: '验证textinput组件密码模式支持文本选择菜单自定义效果' })
          .type(InputType.Password)
          .editMenuOptions(this.editMenuOptions)

      }
    }
  }
}