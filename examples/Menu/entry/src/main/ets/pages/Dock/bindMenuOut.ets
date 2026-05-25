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
struct bindMenuOutExample {
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
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单6',
        action: () => {
          console.info('handle Menu6 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单7',
        action: () => {
          console.info('handle Menu7 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单8',
        action: () => {
          console.info('handle Menu8 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单9',
        action: () => {
          console.info('handle Menu9 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单10',
        action: () => {
          console.info('handle Menu10 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单11',
        action: () => {
          console.info('handle Menu11 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单12',
        action: () => {
          console.info('handle Menu12 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单13',
        action: () => {
          console.info('handle Menu13 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单14',
        action: () => {
          console.info('handle Menu14 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单15',
        action: () => {
          console.info('handle Menu15 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单16',
        action: () => {
          console.info('handle Menu16 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单17',
        action: () => {
          console.info('handle Menu17 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单18',
        action: () => {
          console.info('handle Menu18 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单19',
        action: () => {
          console.info('handle Menu19 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单20',
        action: () => {
          console.info('handle Menu20 select')
        }
      }
    ])
  }
}