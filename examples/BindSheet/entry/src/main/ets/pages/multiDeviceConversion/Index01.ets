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
struct Index01 {

  @State isShow1: boolean = false;
  private modalTransitionArr:ModalTransition[] = [ModalTransition.DEFAULT, ModalTransition.NONE, ModalTransition.ALPHA];
  private modalTransitionArrStr:string[] = ['ModalTransition.DEFAULT', 'ModalTransition.NONE', 'ModalTransition.ALPHA'];
  @State modalTransitionIndex:number = 0;

  @State enableSafeAreaState: boolean = false;

  @Builder
  myBuilder1() {
    Column() {
      Button('Close Page 1')
        .fontSize(20)
        .height(60)
        .onClick(()=>{
          this.isShow1 = false;
        })
    }
    .width('100%')
    .height('100%')
  }

  build() {
    Row(){
      Column(){
        Button('Show Page 1')
          .fontSize(20)
          .onClick(() => {
            this.isShow1 = true;
          })
          .bindContentCover(this.isShow1, this.myBuilder1(), {
            enableSafeArea: this.enableSafeAreaState,
            modalTransition: this.modalTransitionArr[this.modalTransitionIndex],
            onWillDismiss: (dismissContentCoverAction: DismissContentCoverAction) => {
              if (dismissContentCoverAction.reason == DismissReason.PRESS_BACK) {
                console.log('[TEST INFO] [Page1] onWillDismiss PRESS_BACK');
              } else if (dismissContentCoverAction.reason == DismissReason.CLOSE_BUTTON) {
                console.log('[TEST INFO] [Page1] onWillDismiss CLOSE_BUTTON');
              } else {
                console.log('[TEST INFO] [Page1] onWillDismiss Other');
              }
              dismissContentCoverAction.dismiss();
            },
            backgroundColor: Color.Gray,
            onWillAppear: ()=>{
              console.log('[TEST INFO] [Page1] onWillAppear');
            },
            onAppear: ()=>{
              console.log('[TEST INFO] [Page1] onAppear');
            },
            onWillDisappear: ()=>{
              console.log('[TEST INFO] [Page1] onWillDisappear');
            },
            onDisappear: ()=>{
              console.log('[TEST INFO] [Page1] onDisappear');
            }
          })

        Row(){
          Button('bindContentCover transition mode: ' + this.modalTransitionArrStr[this.modalTransitionIndex])
            .onClick(()=>{
              this.modalTransitionIndex = ++this.modalTransitionIndex % this.modalTransitionArr.length;
            })
        }.margin({ top: 10, bottom: 10 })

        Row(){
          Button('whether to adapt to the bindContentCover security zone: ' + (this.enableSafeAreaState ? 'adapt' : 'do not handle'))
            .onClick(()=>{
              this.enableSafeAreaState = !this.enableSafeAreaState;
            })
        }.margin({ bottom: 10 })
      }
      .width('100%')
    }
    .height('100%')
  }
}