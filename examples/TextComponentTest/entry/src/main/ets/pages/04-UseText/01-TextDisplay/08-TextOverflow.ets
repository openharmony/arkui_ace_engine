/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@Entry
@Component
struct TextOverflow {
  build() {
    Column() {
      Text('This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content. This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content.')
        .width(250)
        .textOverflow({ overflow: TextOverflow.None })
        .maxLines(1)
        .fontSize(12)
        .border({ width: 1 })
        .padding(10)
      Text('我是超长文本，超出的部分显示省略号。I am an extra long text, with ellipses displayed for any excess.')
        .width(250)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .maxLines(1)
        .fontSize(12)
        .border({ width: 1 })
        .padding(10)
      Text('当文本溢出其尺寸时，文本将滚动显示。When the text overflows its dimensions, the text will scroll for displaying.')
        .width(250)
        .textOverflow({ overflow: TextOverflow.MARQUEE })
        .maxLines(1)
        .fontSize(12)
        .border({ width: 1 })
        .padding(10)
      Text('当文本溢出其尺寸时，文本将滚动显示，支持设置跑马灯配置项。When the text overflows its dimensions, the text will scroll for displaying.')
        .width(250)
        .textOverflow({ overflow: TextOverflow.MARQUEE })
        .maxLines(1)
        .fontSize(12)
        .border({ width: 1 })
        .padding(10)
        .marqueeOptions({
          start: true,
          fromStart: true,
          step: 6,
          loop: -1,
          delay: 0,
          fadeout: false,
          marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
        })
    }
  }
}