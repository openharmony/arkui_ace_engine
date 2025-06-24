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
export function SelectDividerBuilder(name: string, param: Object) {
  CaseSelect()
}

class MySelectAttribute implements AttributeModifier<SelectAttribute> {
  applyNormalAttribute(instance: SelectAttribute): void {
    instance.dividerStyle({
      color: Color.Pink,
      strokeWidth: LengthMetrics.vp(10),
      mode: DividerMode.EMBEDDED_IN_MENU
    })
  }
}

@Entry
@Component
struct CaseSelect {
  pathStack: NavPathStack = new NavPathStack()
  @State array: SelectOption[] = [{ value: '选项一' }, { value: '选项二' }, { value: '选项三' }, { value: '选项四' }];
  @State dividers: (DividerOptions | undefined)[] = [undefined, {}, {
    strokeWidth: 20, color: Color.Yellow
  }]
  @State dividerStyles: (DividerStyleOptions | undefined)[] = [undefined, {}, {
    strokeWidth: LengthMetrics.vp(20), color: Color.Pink, mode: DividerMode.EMBEDDED_IN_MENU
  }]
  @State optionArray: (SelectOption[] | undefined)[] =
    [[{ value: '选项一' }, { value: '选项二' }, { value: '选项三' }, { value: '选项四' }],
      undefined,
      [{ value: '选项三' }, { value: '选项二' }, { value: '选项一' }, { value: '选项五' }, { value: '选项四' }],
      [{ value: '选项三' }, { value: '选项二' }, { value: '选项一' }, { value: '选项五' }, { value: '选项四' }]]
  @State index: number = 0;
  @State value: number = 0;
  @State modifier: MySelectAttribute = new MySelectAttribute()
  @State backColor: Color = Color.Yellow

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }

      MenuItemGroup() {
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }
    }.menuItemDivider({
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(1),
    })
    .menuItemGroupDivider({
      startMargin: LengthMetrics.vp(0),
      endMargin: LengthMetrics.vp(0),
      strokeWidth: LengthMetrics.vp(1),
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('不设置divider/ dividerStyle')
          Select(this.array)

          Text('设置divider/不设置dividerStyle')
          Select(this.array)
            .divider({
              color: Color.Yellow,
              startMargin: 10,
              endMargin: 10,
              strokeWidth: 10,
            })

          Text('不设置dividerStyle/设置dividerStyle')
          Select(this.array)
            .dividerStyle({
              color: Color.Pink,
              startMargin: LengthMetrics.vp(10),
              endMargin: LengthMetrics.vp(10),
              strokeWidth: LengthMetrics.vp(10),
            })

          Text('设置dividerStyle/设置dividerStyle')
          Select(this.array)
            .divider({
              color: Color.Pink,
              startMargin: 10,
              endMargin: 10,
              strokeWidth: 10,
            })
            .dividerStyle({
              color: Color.Yellow,
              startMargin: LengthMetrics.vp(10),
              endMargin: LengthMetrics.vp(10),
              strokeWidth: LengthMetrics.vp(10),
            })

          Text('不支持CAPI、支持attributeModifier')
          Select(this.array)
            .attributeModifier(this.modifier)

          Text('下拉菜单不同宽度测试')
          Select(this.array)
            .attributeModifier(this.modifier)
            .width(400)
            .optionWidth(400)

          Select(this.array)
            .attributeModifier(this.modifier)
            .width(200)
            .optionWidth(OptionWidthMode.FIT_TRIGGER)

          Text('深浅色测试')
          Select(this.array)
            .width(200)
            .dividerStyle({
              color: $r('app.color.change_mode'),
              strokeWidth: LengthMetrics.vp(5),
              mode: DividerMode.EMBEDDED_IN_MENU
            })
            .optionWidth(OptionWidthMode.FIT_TRIGGER)

        }.width('100%')
        .height('100%')
        .alignItems(HorizontalAlign.Center)
      }
      .height('100%')
    }
    .title('SelectDivider')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { CaseSelect };