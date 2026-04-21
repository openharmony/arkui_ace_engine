/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router';

export interface DataClass {
  title: string
  page: string
}

@Entry
@Component
struct PositionIndex {
  data: DataClass[] = [
    {
      title: 'PositionExample01',
      page: 'pages/PositionExample/PositionExample01'
    },
    {
      title: 'PositionExample02',
      page: 'pages/PositionExample/PositionExample02'
    },
    {
      title: 'PositionExample03',
      page: 'pages/PositionExample/PositionExample03'
    },
    {
      title: 'PositionExample04',
      page: 'pages/PositionExample/PositionExample04'
    },
    {
      title: 'PositionExample05',
      page: 'pages/PositionExample/PositionExample05'
    },
    {
      title: 'PositionExample06',
      page: 'pages/PositionExample/PositionExample06'
    },
    {
      title: 'PositionExample07',
      page: 'pages/PositionExample/PositionExample07'
    },
  ]

  build() {
    Column() {
      Column() {
        List({ space: '8vp' }) {
          ForEach(this.data, (item: DataClass) => {
            ListItem() {
              Button(item.title)
                .width('100%')
                .onClick(() => {
                  router.pushUrl({ url: item.page })
                })
            }
            .width('100%')
            .padding({ left: '8vp', right: '8vp' })
          }, (item: DataClass) => item.title)
        }
        .scrollBar(BarState.Off)
      }
      .width(250)
      .height(200)
      .backgroundColor($r('sys.color.background_primary'))
      .justifyContent(FlexAlign.Center)
      .flexGrow(1)
    }
    .height('100%')
    .width('100%')
  }
}