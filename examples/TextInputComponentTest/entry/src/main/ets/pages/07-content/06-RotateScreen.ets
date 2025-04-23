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
struct Ets_7_6_rotateScreen {
  @State text: string =
    '三击文本全选后，横屏切竖屏，查看手柄位置是否异常。三击文本全选后，横屏切竖屏，查看手柄位置是否异常。' +
      '三击文本全选后，横屏切竖屏，查看手柄位置是否异常。三击文本全选后，横屏切竖屏，查看手柄位置是否异常。三击文本全选后，横屏切竖屏，' +
      '查看手柄位置是否异常。三击文本全选后，横屏切竖屏，查看手柄位置是否异常。三击文本全选后，横屏切竖屏，查看手柄位置是否异常。三击文本' +
      '全选后，横屏切竖屏，查看手柄位置是否异常。三击文本全选后，横屏切竖屏，查看手柄位置是否异常。三击文本全选后，横屏切竖屏，查看手柄位置' +
      '是否异常。三击文本全选后，横屏切竖屏，查看手柄位置是否异常。三击文本全选后，横屏切竖屏，查看手柄位置是否异常。'
  controller: TextAreaController = new TextAreaController()

  build() {
    Column({ space: '20px' }) {
      Text('规格 横竖屏切换，手柄位置保持不变').fontColor(Color.Blue)
      Text('测试步骤：\n 1、三击全选文本 2、横竖屏切换')

      Text('pass条件：横竖屏切换手柄位置保持不变').fontColor(Color.Red)
      TextArea({
        text: this.text,
        controller: this.controller
      })
        .caretStyle({ width: 20 })
        .caretColor(Color.Red)
        .width('80%')
        .height(500)
    }
  }
}