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

// [Start listen_response_mouse_event]
@Entry
@Component
export struct Mouse {
  @State buttonText: string = '';
  @State columnText: string = '';
  @State hoverText: string = 'Not Hover';
  @State color: Color = Color.Gray;

  build() {
    NavDestination() {
      Column({ space: 12 }) {

        Column() {
          Button(this.hoverText)
            .width(200)
            .height(100)
            .backgroundColor(this.color)
            .onHover((isHover?: boolean) => {
              if (isHover) {
                this.hoverText = 'Hovered!';
                this.color = Color.Green;
              } else {
                this.hoverText = 'Not Hover';
                this.color = Color.Gray;
              }
            })
            .onMouse((event?: MouseEvent) => { // 设置Button的onMouse回调
              if (event) {
                this.buttonText = 'Button onMouse:\n' + '' +
                  'button = ' + event.button + '\n' +
                  'action = ' + event.action + '\n' +
                  'x,y = (' + event.x + ',' + event.y + ')' + '\n' +
                  'windowXY=(' + event.windowX + ',' + event.windowY + ')';
              }
            })
          Divider()
          Text(this.buttonText).fontColor(Color.Green)
          Divider()
          Text(this.columnText).fontColor(Color.Red)
        }
        .width('100%')
        .height('100%')
        .justifyContent(FlexAlign.Center)
        .borderWidth(2)
        .borderColor(Color.Red)
        .onMouse((event?: MouseEvent) => { // Set the onMouse callback for the column.
          if (event) {
            this.columnText = 'Column onMouse:\n' + '' +
              'button = ' + event.button + '\n' +
              'action = ' + event.action + '\n' +
              'x,y = (' + event.x + ',' + event.y + ')' + '\n' +
              'windowXY=(' + event.windowX + ',' + event.windowY + ')';
          }
        })

      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.Device_OnMouse_title')替换为实际资源文件，在本示例中该资源文件的value值为"鼠标事件"
    .title($r('app.string.Device_OnMouse_title'))
  }
}
// [End listen_response_mouse_event]