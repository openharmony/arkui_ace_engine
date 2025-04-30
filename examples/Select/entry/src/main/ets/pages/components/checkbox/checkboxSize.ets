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
export function CheckboxSizeBuilder(name: string, param: Object) {
  CheckboxSizeExample()
}

@Component
struct CheckboxSizeExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column() {
        Text('Checkbox组件设置size({ width: -100, height: undefined })\时恢复默认值n' +
          '除最后一个chekcbox大小一致即可，最后个checkbox大小为100*100')
          .margin({ top: 100, bottom: 100 })

        Checkbox()
        Checkbox()
          .select(true)
          .size({ width: -100, height: undefined })
        Checkbox()
          .size({ width: undefined, height: undefined })
          .select(true)
        Checkbox()
          .size({ width: undefined, height: -100 })
        Checkbox()
          .select(true)
          .size({ width: 100, height: 100 })
          .size({ width: undefined, height: -100 })

        Checkbox()
          .select(true)
          .size({ width: undefined, height: -100 })
          .size({ width: 100, height: 100 })
      }.width('100%')
    }
    .title('CheckboxSize')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { CheckboxSizeExample };