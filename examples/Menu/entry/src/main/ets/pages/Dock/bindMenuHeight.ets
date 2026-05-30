/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct bindMenuHeight {
  build() {
    Column() {
      Text('click for Menu').fontSize(25)
    }
    .width('100%')
    .height('100%')
    .bindMenu([
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单1',
        action: () => {
          console.info('handle Menu1 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单2',
        action: () => {
          console.info('handle Menu2 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单3',
        action: () => {
          console.info('handle Menu3 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单4',
        action: () => {
          console.info('handle Menu4 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单5',
        action: () => {
          console.info('handle Menu5 select')
        }
      }
    ])
  }
}