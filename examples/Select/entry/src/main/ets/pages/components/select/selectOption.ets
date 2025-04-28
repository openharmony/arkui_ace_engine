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

@Builder
export function SelectOptionBuilder(name: string, param: Object) {
  SelectOptionExample()
}

@Component
struct SelectOptionExample {
  pathStack: NavPathStack = new NavPathStack()
  private selects: ResourceStr[] = ['Linear', 'Ease', 'FastOutSlowIn', 'Sharp', 'Rhythm', 'Smooth', 'Friction'];
  private selectOption: SelectOption[] = [];

  aboutToAppear() {
    this.selects.forEach((selects, index) => {
      this.selectOption[index] = { value: selects }
    })
  }

  build() {
    NavDestination() {
      Column() {
        Text('点击select弹出menu,menu右边缘与select右边缘保持一致')
          .margin({ top: 50, bottom: 50 })
        Row() {
          Text('测试')
          Select(this.selectOption)
            .value('请选择')
            .menuAlign(MenuAlignType.END)
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceBetween)
      }.padding(24)
    }
    .title('SelectOption')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { SelectOptionExample };