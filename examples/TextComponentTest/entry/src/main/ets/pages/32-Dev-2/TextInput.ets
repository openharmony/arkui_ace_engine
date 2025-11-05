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
struct TextInput32dev1 {
  @State text: string = 'Search editMenuOptions'
  @State tag: boolean = true;
  @State inputStyle: TextInputStyle = TextInputStyle.Default;

  onCreateMenu(menuItems: Array<TextMenuItem>) {
    menuItems.forEach((value, index) => {
      value.icon = $r('app.media.startIcon')
      if (value.id.equals(TextMenuItemId.COPY)) {
        value.content = $r('app.string.copy')
      }
      if (value.id.equals(TextMenuItemId.SELECT_ALL)) {
        value.content = '全选change'
      }
    })
    let item1: TextMenuItem = {
      content: 'custom1',
      icon: $r('app.media.22'),
      id: TextMenuItemId.of('custom1'),
    }
    let item2: TextMenuItem = {
      content: 'custom2\ncustom2',
      id: TextMenuItemId.of('custom2'),
      icon: $r('app.media.81'),
    }

    let item3: TextMenuItem = {
      content: 'custom3',
      id: TextMenuItemId.of('custom3'),
      icon: $r('app.media.bmp'),
    }
    let item4: TextMenuItem = {
      content: 'custom4',
      id: TextMenuItemId.of('custom4'),
      icon: $r('app.media.svg'),
    }
    let item5: TextMenuItem = {
      content: 'custom5',
      id: TextMenuItemId.of('custom5'),
      icon: $r('app.media.webp'),
    }
    let item6: TextMenuItem = {
      content: 'custom6',
      id: TextMenuItemId.of('custom6'),
      icon: $r('app.media.gif'),
    }
    let item7: TextMenuItem = {
      content: $r('app.string.longText'),
      id: TextMenuItemId.of('custom7'),
      icon: $r('app.media.jpeg'),
    }
    let item11: TextMenuItem = {
      content: 'AB,C123JJKHJKN,MNMN',
      id: TextMenuItemId.of('custom11'),
      icon: $r('app.media.icon'),
    }
    menuItems.unshift(item1)
    menuItems.unshift(item2)
    menuItems.unshift(item3)
    menuItems.unshift(item4)
    menuItems.unshift(item5)
    menuItems.unshift(item6)
    menuItems.unshift(item7)
    return menuItems
  }

  onCreateMenu2(menuItems: Array<TextMenuItem>) {
    menuItems.forEach((value, index) => {
      value.icon = $r('app.media.startIcon')
      if (value.id.equals(TextMenuItemId.COPY)) {
        value.content = $r('app.string.copy')
      }
      if (value.id.equals(TextMenuItemId.SELECT_ALL)) {
        value.content = '全选change'
      }
    })
    let item1: TextMenuItem = {
      content: 'custom1',
      icon: $r('app.media.22'),
      id: TextMenuItemId.of('custom1'),
    }
    let item2: TextMenuItem = {
      content: 'custom2\ncustom2',
      id: TextMenuItemId.of('custom2'),
      icon: $r('app.media.81'),
    }

    let item3: TextMenuItem = {
      content: 'custom3',
      id: TextMenuItemId.of('custom3'),
      icon: $r('app.media.bmp'),
    }
    let item4: TextMenuItem = {
      content: 'custom4',
      id: TextMenuItemId.of('custom4'),
      icon: $r('app.media.svg'),
    }
    let item5: TextMenuItem = {
      content: 'custom5',
      id: TextMenuItemId.of('custom5'),
      icon: $r('app.media.webp'),
    }
    let item6: TextMenuItem = {
      content: 'custom6',
      id: TextMenuItemId.of('custom6'),
      icon: $r('app.media.gif'),
    }
    let item7: TextMenuItem = {
      content: $r('app.string.longText'),
      id: TextMenuItemId.of('custom7'),
      icon: $r('app.media.jpeg'),
    }
    let item11: TextMenuItem = {
      content: 'AB,C123JJKHJKN,MNMN',
      id: TextMenuItemId.of('custom11'),
      icon: $r('app.media.icon'),
    }
    menuItems.push(item1)
    menuItems.push(item2)
    menuItems.push(item3)
    menuItems.push(item4)
    menuItems.push(item5)
    menuItems.push(item6)
    menuItems.push(item7)
    return menuItems
  }

  onCreateMenu3(menuItems: Array<TextMenuItem>) {
    menuItems.forEach((value, index) => {
      value.icon = $r('app.media.startIcon')
      if (value.id.equals(TextMenuItemId.COPY)) {
        value.content = $r('app.string.copy')
      }
      if (value.id.equals(TextMenuItemId.SELECT_ALL)) {
        value.content = '全选change'
      }
    })
    let item1: TextMenuItem = {
      content: 'custom1',
      icon: $r('app.media.22'),
      id: TextMenuItemId.of('custom1'),
    }
    let item2: TextMenuItem = {
      content: 'custom2\ncustom2',
      id: TextMenuItemId.of('custom2'),
      icon: $r('app.media.81'),
    }

    let item3: TextMenuItem = {
      content: 'custom3',
      id: TextMenuItemId.of('custom3'),
      icon: $r('app.media.bmp'),
    }
    let item4: TextMenuItem = {
      content: 'custom4',
      id: TextMenuItemId.of('custom4'),
      icon: $r('app.media.svg'),
    }
    let item5: TextMenuItem = {
      content: 'custom5',
      id: TextMenuItemId.of('custom5'),
      icon: $r('app.media.webp'),
    }
    let item6: TextMenuItem = {
      content: 'custom6',
      id: TextMenuItemId.of('custom6'),
      icon: $r('app.media.gif'),
    }
    let item7: TextMenuItem = {
      content: $r('app.string.longText'),
      id: TextMenuItemId.of('custom7'),
      icon: $r('app.media.jpeg'),
    }
    let item11: TextMenuItem = {
      content: 'AB,C123JJKHJKN,MNMN',
      id: TextMenuItemId.of('custom11'),
      icon: $r('app.media.icon'),
    }
    menuItems.unshift(item1)
    menuItems.unshift(item2)
    menuItems.unshift(item3)
    menuItems.unshift(item4)
    menuItems.unshift(item5)
    menuItems.unshift(item6)
    menuItems.unshift(item7)
    menuItems.shift()
    return menuItems
  }

  onCreateMenu4(menuItems: Array<TextMenuItem>) {
    menuItems.forEach((value, index) => {
      value.icon = $r('app.media.startIcon')
      if (value.id.equals(TextMenuItemId.COPY)) {
        value.content = $r('app.string.copy')
      }
      if (value.id.equals(TextMenuItemId.SELECT_ALL)) {
        value.content = '全选change'
      }
    })
    let item1: TextMenuItem = {
      content: 'custom1',
      icon: $r('app.media.22'),
      id: TextMenuItemId.of('custom1'),
    }
    let item2: TextMenuItem = {
      content: 'custom2\ncustom2',
      id: TextMenuItemId.of('custom2'),
      icon: $r('app.media.81'),
    }

    let item3: TextMenuItem = {
      content: 'custom3',
      id: TextMenuItemId.of('custom3'),
      icon: $r('app.media.bmp'),
    }
    let item4: TextMenuItem = {
      content: 'custom4',
      id: TextMenuItemId.of('custom4'),
      icon: $r('app.media.svg'),
    }
    let item5: TextMenuItem = {
      content: 'custom5',
      id: TextMenuItemId.of('custom5'),
      icon: $r('app.media.webp'),
    }
    let item6: TextMenuItem = {
      content: 'custom6',
      id: TextMenuItemId.of('custom6'),
      icon: $r('app.media.gif'),
    }
    let item7: TextMenuItem = {
      content: $r('app.string.longText'),
      id: TextMenuItemId.of('custom7'),
      icon: $r('app.media.jpeg'),
    }
    let item11: TextMenuItem = {
      content: 'AB,C123JJKHJKN,MNMN',
      id: TextMenuItemId.of('custom11'),
      icon: $r('app.media.icon'),
    }
    menuItems.push(item1)
    menuItems.push(item2)
    menuItems.push(item3)
    menuItems.push(item4)
    menuItems.push(item5)
    menuItems.push(item6)
    menuItems.push(item7)
    menuItems.pop()
    return menuItems
  }

  build() {
    Column() {
      Button('onMenuItemClick' + this.tag).onClick(() => {
        this.tag = !this.tag
      })
      Row() {
        Button('默认').onClick((event: ClickEvent) => {
          this.inputStyle = TextInputStyle.Default
        }).width('40%')
        Button('内联').onClick((event: ClickEvent) => {
          this.inputStyle = TextInputStyle.Inline
        }).width('40%')
      }.width('80%')

      TextInput({ text: 'TextInput editMenuOptions unshift', placeholder: 'TextInput editMenuOptions unshift' })
        .width('95%')
        .style(this.inputStyle)
        .editMenuOptions({
          onCreateMenu: this.onCreateMenu, onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
            if (menuItem.id.equals(TextMenuItemId.of('custom2'))) {
              console.log('拦截 id: custom2 start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.COPY)) {
              console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
              console.log('拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            return false;
          }
        })
        .margin({ top: 20 })

      TextInput({ text: 'TextInput editMenuOptions push', placeholder: 'TextInput editMenuOptions push' })
        .width('95%')
        .style(this.inputStyle)
        .editMenuOptions({
          onCreateMenu: this.onCreateMenu2, onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
            if (menuItem.id.equals(TextMenuItemId.of('custom2'))) {
              console.log('拦截 id: custom2 start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.COPY)) {
              console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
              console.log('拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            return false;
          }
        })
        .margin({ top: 20 })

      TextInput({ text: 'TextInput editMenuOptions shift', placeholder: 'TextInput editMenuOptions shift' })
        .width('95%')
        .style(this.inputStyle)
        .editMenuOptions({
          onCreateMenu: this.onCreateMenu3, onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
            if (menuItem.id.equals(TextMenuItemId.of('custom2'))) {
              console.log('拦截 id: custom2 start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.COPY)) {
              console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
              console.log('拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            return false;
          }
        })
        .margin({ top: 20 })

      TextInput({ text: 'TextInput editMenuOptions pop', placeholder: 'TextInput editMenuOptions pop' })
        .width('95%')
        .style(this.inputStyle)
        .editMenuOptions({
          onCreateMenu: this.onCreateMenu4, onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
            if (menuItem.id.equals(TextMenuItemId.of('custom2'))) {
              console.log('拦截 id: custom2 start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.COPY)) {
              console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
              console.log('拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end)
              return this.tag;
            }
            return false;
          }
        })
        .margin({ top: 20 })
    }
    .width('90%')
    .margin('5%')
  }
}