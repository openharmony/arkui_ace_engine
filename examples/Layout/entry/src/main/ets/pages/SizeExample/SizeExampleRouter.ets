/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router'

export interface DataClass {
  title: string
  page: string
}

@Entry
@Component
struct Index {
  data: DataClass[] = [
    {
      title: 'SizeExample01',
      page: 'pages/SizeExample/SizeExample01'
    },
    {
      title: 'SizeExample02',
      page: 'pages/SizeExample/SizeExample02'
    },
    {
      title: 'SizeExample03',
      page: 'pages/SizeExample/SizeExample03'
    },
    {
      title: 'SizeExample04',
      page: 'pages/SizeExample/SizeExample04'
    },
    {
      title: 'SizeExample05',
      page: 'pages/SizeExample/SizeExample05'
    },
    {
      title: 'SizeExample06',
      page: 'pages/SizeExample/SizeExample06'
    },
    {
      title: 'SizeExample07',
      page: 'pages/SizeExample/SizeExample07'
    },
    {
      title: 'SizeExample08',
      page: 'pages/SizeExample/SizeExample08'
    },
    {
      title: 'SizeExample09',
      page: 'pages/SizeExample/SizeExample09'
    },
    {
      title: 'SizeExample10',
      page: 'pages/SizeExample/SizeExample10'
    },
    {
      title: 'SizeExample11',
      page: 'pages/SizeExample/SizeExample11'
    },
    {
      title: 'SizeExample12',
      page: 'pages/SizeExample/SizeExample12'
    },
    {
      title: 'SizeExample13',
      page: 'pages/SizeExample/SizeExample13'
    },
    {
      title: 'SizeExample14',
      page: 'pages/SizeExample/SizeExample14'
    },
    {
      title: 'SizeExample15',
      page: 'pages/SizeExample/SizeExample15'
    },
    {
      title: 'SizeExample16',
      page: 'pages/SizeExample/SizeExample16'
    },
    {
      title: 'SizeExample17',
      page: 'pages/SizeExample/SizeExample17'
    },
    {
      title: 'SizeExample18',
      page: 'pages/SizeExample/SizeExample18'
    },
    {
      title: 'SizeExample19',
      page: 'pages/SizeExample/SizeExample19'
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