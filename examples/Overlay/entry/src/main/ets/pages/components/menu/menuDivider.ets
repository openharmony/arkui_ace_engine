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

import { LengthMetrics } from '@ohos.arkui.node';

@Builder
export function MenuDividerBuilder(name: string, param: Object) {
  CaseMenu()
}

class MyMenuAttribute implements AttributeModifier<MenuAttribute> {
  applyNormalAttribute(instance: MenuAttribute): void {
    instance.menuItemDivider({
      color: Color.Yellow,
      strokeWidth: LengthMetrics.vp(5),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
    instance.menuItemGroupDivider({
      color: Color.Blue,
      strokeWidth: LengthMetrics.vp(5),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
  }
}

@Entry
@Component
struct CaseMenu {
  pathStack: NavPathStack = new NavPathStack()
  @State array: SelectOption[] = [{ value: '选项一' }, { value: '选项二' }, { value: '选项三' }, { value: '选项四' }];
  @State optionArray: (SelectOption[] | undefined)[] =
    [[{ value: '选项一' }, { value: '选项二' }, { value: '选项三' }, { value: '选项四' }],
      undefined,
      [{ value: '选项三' }, { value: '选项二' }, { value: '选项一' }, { value: '选项五' }, { value: '选项四' }],
      [{ value: '选项三' }, { value: '选项二' }, { value: '选项一' }, { value: '选项五' }, { value: '选项四' }]]
  @State index: number = 0;
  @State value: number = 0;
  @State bool1: boolean = false;
  @State modifier: MyMenuAttribute = new MyMenuAttribute()

  checkBoxBool(): boolean {
    return this.bool1
  }

  @Builder
  MyMenu1() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' }) {
        Checkbox()
          .select(this.checkBoxBool())
      }.opacity(0)

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .menuItemDivider({
      mode: DividerMode.FLOATING_ABOVE_MENU
    })
    .menuItemGroupDivider({
      mode: DividerMode.FLOATING_ABOVE_MENU
    })
  }

  @Builder
  MyMenu2() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .menuItemDivider({
      mode: DividerMode.EMBEDDED_IN_MENU
    })
    .menuItemGroupDivider({
      mode: DividerMode.EMBEDDED_IN_MENU
    })
  }

  @Builder
  MyMenu3() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .menuItemDivider({
      color: Color.Yellow,
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.FLOATING_ABOVE_MENU
    })
    .menuItemGroupDivider({
      color: Color.Blue,
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.FLOATING_ABOVE_MENU
    })
  }

  @Builder
  MyMenu4() {
    Menu() {
      MenuItemGroup() {
      }

      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
      }
    }
    .menuItemDivider({
      color: Color.Yellow,
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
    .menuItemGroupDivider({
      color: Color.Blue,
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
  }

  @Builder
  MyMenu5() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .attributeModifier(this.modifier)
  }

  @Builder
  MyMenu6() {
    Menu() {
      MenuItemGroup() {
      }

      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
      }
    }
    .menuItemDivider({
      color: Color.Yellow,
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
    .menuItemGroupDivider({
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
  }

  @Builder
  MyMenu7() {
    Menu() {
      MenuItemGroup() {
      }

      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        .margin({ top: 50 })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
          .margin({ top: 50 })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
      }
    }
    .menuItemDivider({
      color: Color.Yellow,
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.FLOATING_ABOVE_MENU
    })
    .menuItemGroupDivider({
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.FLOATING_ABOVE_MENU
    })
  }

  @Builder
  MyMenu8() {

    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        .margin({ top: 50 })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
          .margin({ top: 50 })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
      }
    }
    .menuItemDivider({
      color: Color.Yellow,
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
    .menuItemGroupDivider({
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
  }

  build() {
    NavDestination() {
      Column() {
        if (this) {
          Button('点击展示Menu，默认模式，宽度为默认值')
            .bindMenu(this.MyMenu1())
            .margin(20)
        }

        Button('点击展示Menu，占用高度模式，宽度为默认值')
          .bindMenu(this.MyMenu2())
          .margin(20)

        Button('点击展示Menu，默认模式，宽度为10')
          .bindMenu(this.MyMenu3())
          .margin(20)

        Button('点击展示Menu，占用高度模式，宽度为10')
          .bindMenu(this.MyMenu4())
          .margin(20)

        Button('attributeModifier')
          .bindMenu(this.MyMenu5())
          .margin(20)

        Button('EMBEDDED_IN_MENU，左右间距为0')
          .bindMenu(this.MyMenu6())
          .margin(20)

        Button('MenuItem添加margin，原效果')
          .bindMenu(this.MyMenu7())
          .margin(20)

        Button('MenuItem添加margin，现效果')
          .bindMenu(this.MyMenu8())
          .margin(20)

      }.width('100%')
      .alignItems(HorizontalAlign.Start)
      .height('100%')
    }
    .title('MenuDivider')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { CaseMenu };