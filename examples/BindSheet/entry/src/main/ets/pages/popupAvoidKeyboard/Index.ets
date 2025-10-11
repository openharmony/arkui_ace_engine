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
struct SheetTransitionExample {
  @State isShow: boolean = false
  @State myHeight: number = 300;
  @State myWidth: number = 300;
  @State myX: number = 300;
  @State myY: number = 300;

  @Builder
  myBuilder() {
    Column() {
      TextInput()
      Row({ space: 10 }) {
        Text('sheet height : ' )
        Select([
          { value: '100' },
          { value: '200' },
          { value: '300' },
          { value: '400' },
          { value: '500' },
          { value: '600' },
          { value: '700' },
          { value: '733' },

        ]).
        selected(0).onSelect((index: number, value: string) => {
          switch (value) {
            case '100':
              this.myHeight = 100
              break;
            case '200':
              this.myHeight = 200
              break;
            case '300':
              this.myHeight = 300
              break;
            case '400':
              this.myHeight = 400
              break;
            case '500':
              this.myHeight = 500
              break;
            case '600':
              this.myHeight = 600
              break;
            case '700':
              this.myHeight = 700
              break;
            case '733':
              this.myHeight = 733
              break;
          }
        })
      }

      Row({ space: 10 }) {
        Text('sheet width : ' )
        Select([
          { value: '100' },
          { value: '200' },
          { value: '300' },
          { value: '400' },
          { value: '500' },
          { value: '600' },
          { value: '700' },
          { value: '711' },

        ]).
        selected(0).onSelect((index: number, value: string) => {
          switch (value) {
            case '100':
              this.myWidth = 100
              break;
            case '200':
              this.myWidth = 200
              break;
            case '300':
              this.myWidth = 300
              break;
            case '400':
              this.myWidth = 400
              break;
            case '500':
              this.myWidth = 500
              break;
            case '600':
              this.myWidth = 600
              break;
            case '700':
              this.myWidth = 700
              break;
            case '711':
              this.myWidth = 711
              break;
          }
        })
      }

      Button('reset height/width')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.myHeight = 300;
          this.myWidth = 300;
        })

      Button('close modal 1')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShow = false;
        })
    }
    .width('100%')
    .height('100%')
  }


  build() {
    Column() {
      Column (){
        TextInput()
          .width(300)
        Row({ space: 10 }) {
          Text('button position x : ' )
          Select([
            { value: '100' },
            { value: '200' },
            { value: '300' },
            { value: '400' },
            { value: '500' },
            { value: '600' },
            { value: '700' },

          ]).
          selected(0).onSelect((index: number, value: string) => {
            switch (value) {
              case '100':
                this.myX = 100
                break;
              case '200':
                this.myX = 200
                break;
              case '300':
                this.myX = 300
                break;
              case '400':
                this.myX = 400
                break;
              case '500':
                this.myX = 500
                break;
              case '600':
                this.myX = 600
                break;
              case '700':
                this.myX = 700
                break;
            }
          })
        }

        Row({ space: 10 }) {
          Text('button position y : ' )
          Select([
            { value: '100' },
            { value: '200' },
            { value: '300' },
            { value: '400' },
            { value: '500' },
            { value: '600' },
            { value: '700' },

          ]).
          selected(0).onSelect((index: number, value: string) => {
            switch (value) {
              case '100':
                this.myY = 100
                break;
              case '200':
                this.myY = 200
                break;
              case '300':
                this.myY = 300
                break;
              case '400':
                this.myY = 400
                break;
              case '500':
                this.myY = 500
                break;
              case '600':
                this.myY = 600
                break;
              case '700':
                this.myY = 700
                break;
            }
          })
        }
      }
      .position({x:0,y:0})

      Button('transition modal 1')
        .onClick(() => {
          this.isShow = true
        })
        .position({x:this.myX,y:this.myY})
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShow, this.myBuilder(), {
          preferType:SheetType.POPUP,
          title:{
            title:'title',
            subtitle:'subtitle'
          },
          height:this.myHeight,
          width:this.myWidth,
          placementOnTarget: true,
          keyboardAvoidMode: SheetKeyboardAvoidMode.POPUP_SHEET,

          onWillAppear: () => {
            console.log('BindSheet onWillAppear.')
          },
          onAppear: () => {
            console.log('BindSheet onAppear.')
          },
          onWillDisappear: () => {
            console.log('BindSheet onWillDisappear.')
          },
          onDisappear: () => {
            console.log('BindSheet onDisappear.')
          }
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}
