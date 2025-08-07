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

/**
 * 通过colorFilter修改图片的像素颜色为图片添加滤镜
 */
interface Filters {
  name: string;
  matrix: number[];
}

@Entry
@Component
struct Index {
  // 定义各种颜色滤镜矩阵
  @State filters: Filters[] = [
    {
      name: 'Original',
      matrix: [
        1, 0, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 0
      ]
    },
    {
      name: 'Grayscale',
      matrix: [
        0.3, 0.6, 0.1, 0, 0,
        0.3, 0.6, 0.1, 0, 0,
        0.3, 0.6, 0.1, 0, 0,
        0, 0, 0, 1, 0
      ]
    },
    {
      name: 'Sepia',
      matrix: [
        0.393, 0.769, 0.189, 0, 0,
        0.349, 0.686, 0.168, 0, 0,
        0.272, 0.534, 0.131, 0, 0,
        0, 0, 0, 1, 0
      ]
    },
    {
      name: 'Warm Tone',
      matrix: [
        1.1, 0.0, 0.0, 0, 0,
        0.0, 1.0, 0.1, 0, 0,
        0.0, 0.1, 1.0, 0, 0,
        0.0, 0.0, 0.0, 1, 0
      ]
    },
    {
      name: 'Cool Tone',
      matrix: [
        1.0, 0.0, 0.1, 0, 0,
        0.1, 1.0, 0.0, 0, 0,
        0.0, 0.1, 1.0, 0, 0,
        0.0, 0.0, 0.0, 1, 0
      ]
    },
    {
      name: 'High Contrast',
      matrix: [
        1.5, 0, 0, 0, 0,
        0, 1.5, 0, 0, 0,
        0, 0, 1.5, 0, 0,
        0, 0, 0, 1, 0
      ]
    }
  ];

  build() {
    Column({ space: 10 }) {
      Text('ColorFilter Image Filter Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold);

      Scroll() {
        Column({ space: 10 }) {
          ForEach(this.filters, (item: Filters) => {
            Column({ space: 5 }) {
              Text(item.name)
                .fontSize(16)
                .fontWeight(FontWeight.Bold);
              Image($r('app.media.landscape'))
                .width('90%')
                .aspectRatio(1.5)
                .colorFilter(item.matrix)
                .border({ width: 1, color: '#ccc' })
                .margin({ top: 5, bottom: 10 });
            }
          }, (item: Filters): string => item.name);
        }
      }
      .padding(10)
      .backgroundColor('#f9f9f9')
      .width('100%')
      .height('100%');
    }
  }
}