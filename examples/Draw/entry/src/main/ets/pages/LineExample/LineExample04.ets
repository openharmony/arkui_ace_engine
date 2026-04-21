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

@Entry
@Component
struct LineExample04 {
  build() {
    Column({ space: 10 }) {
      // 在200 * 200的区域内绘制一个起始点为（0,0），终点为（150,150），边框宽度为10的直线
      Line({ width: '200', height: '200' })// 使用string类型
        .startPoint([0, 0])
        .endPoint([150, 150])
        .stroke(Color.Black)
        .strokeWidth(10)
        .backgroundColor('#F5F5F5')
        .margin(10)
      // 在200 * 200的区域内绘制一个起始点为（0,50），终点为（150,150），边框宽度为10的直线
      Line({ width: 200, height: 200 })// 使用number类型
        .startPoint([0, 50])
        .endPoint([150, 150])
        .stroke(Color.Black)
        .strokeWidth(10)
        .backgroundColor('#F5F5F5')
        .margin(10)
      // 在200 * 200的区域内绘制一个起始点为（0,100），终点为（150,150），边框宽度为10的直线
      Line({ width: $r('app.string.LineWidth'), height: $r('app.string.LineHeight') })// 使用Resource类型，需用户自定义
        .startPoint([0, 100])
        .endPoint([150, 150])
        .stroke(Color.Black)
        .strokeWidth(10)
        .backgroundColor('#F5F5F5')
        .margin(10)
    }.width('100%')
  }
}