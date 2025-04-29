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

@Entry
@Component
struct TextClockExample {
  build() {
    Column({ space: 8 }) {
      Row() {
        Text('24小时制去除前导0：')
          .fontSize(20)
        TextClock()
          .fontSize(20)
          .format('HH:mm:ss')
          .dateTimeOptions({ hour: 'numeric' })
      }

      Row() {
        Text('12小时制增加前导0：')
          .fontSize(20)
        TextClock()
          .fontSize(20)
          .format('aa hh:mm:ss')
          .dateTimeOptions({ hour: '2-digit' })
      }
    }
    .alignItems(HorizontalAlign.Start)
  }
}