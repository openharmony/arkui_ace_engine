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
      title: 'ShapeExample',
      page: 'pages/ShapeExample/ShapeExample'
    },
    {
      title: 'VideoExample',
      page: 'pages/VideoExample/VideoExampleRouter'
    },
    {
      title: 'CanvasExample',
      page: 'pages/CanvasExample/CanvasExampleRouter'
    },
    {
      title: 'CanvasGradientExample',
      page: 'pages/CanvasGradientExample/CanvasGradientExampleRouter'
    },
    {
      title: 'CanvasPatternExample',
      page: 'pages/CanvasPatternExample/CanvasPatternExample'
    },
    {
      title: 'DrawingRenderingContextExample',
      page: 'pages/DrawingRenderingContextExample/DrawingRenderingContextExampleRouter'
    },
    {
      title: 'EllipseExample',
      page: 'pages/EllipseExample/EllipseExampleRouter'
    },
    {
      title: 'ImageBitmapExample',
      page: 'pages/ImageBitmapExample/ImageBitmapExampleRouter'
    },
    {
      title: 'ImageDataExample',
      page: 'pages/ImageDataExample/ImageDataExample'
    },
    {
      title: 'LineExample',
      page: 'pages/LineExample/LineExampleRouter'
    },
    {
      title: 'RectExample',
      page: 'pages/RectExample/RectExampleRouter'
    }
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