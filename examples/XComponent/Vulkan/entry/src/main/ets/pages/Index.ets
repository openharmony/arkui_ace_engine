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

import { getFront, vec3, setResourceManager, windowSizeChange, getPitch, getYaw,
  YawPitchTo } from 'libentry.so';
import displaySync from '@ohos.graphics.displaySync';
import display from '@ohos.display';
import { Controller } from './Controller'
import GlobalThis from '../GlobalThis'

let displaysync = displaySync.create()

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  @State yaw: number = 0;
  @State pitch: number = 0;
  @State front: vec3 = { x: 0, y: 0, z: 0 };
  @StorageLink('windowSize') windowSize: Size = {width: 0, height: 0};
  @State orientation: number = 0;

  storeYaw: number = 0
  storePitch: number = 0

  aboutToAppear(): void {
    displaysync.on('frame', ()=>{
      this.yaw = getYaw();
      this.pitch = getPitch();
      this.front = getFront();
      displaysync.stop()
    })
    setTimeout(()=>{
      displaysync.start()
    }, 100)
  }

  handleTouchOpt(id: number, type: TouchType, pos: Position)
  {
    GlobalThis.getInstance().touches.set(id, pos)
    if (type == TouchType.Down) {
      if (GlobalThis.getInstance().touch0Id == -1) {
        GlobalThis.getInstance().touch0Id = id
        GlobalThis.getInstance().touch0StorePos = pos
        this.storeYaw = this.yaw
        this.storePitch = this.pitch
      }
    } else if (type == TouchType.Move) {
      if (GlobalThis.getInstance().touch0Id == id) {
        let cur = GlobalThis.getInstance().touches.get(id)
        let deltaX = (cur!.x as number) - (GlobalThis.getInstance().touch0StorePos.x as number)
        let deltaY = (cur!.y as number) - (GlobalThis.getInstance().touch0StorePos.y as number)
        YawPitchTo(this.storeYaw + deltaX * 0.1, this.storePitch - deltaY * 0.1)
      }
    } else {
      GlobalThis.getInstance().touches.delete(id)
      if (GlobalThis.getInstance().touch0Id == id) {
        GlobalThis.getInstance().touch0Id = -1
      }
    }
  }

  build() {
    Stack(){
      XComponent({
        id: 'xComponentTest',
        type: XComponentType.SURFACE,
        libraryname: 'entry',
      })
        .onLoad(()=>{
          //setTimeout(()=>{
            setResourceManager(GlobalThis.getInstance().resourceManager)
          //}, 20)
        })
        .width('100%')
        .height('100%')

      Text(`yaw: ${this.yaw}`)
        .position({x: 20, y: 20})
        .fontColor(Color.Red)
        .fontSize(24)
      Text(`pitch: ${this.pitch}`)
        .position({x: 20, y: 50})
        .fontColor(Color.Red)
        .fontSize(24)
      Text(`front: ${this.front.x}, ${this.front.y}, ${this.front.z}`)
        .position({x: 20, y: 80})
        .fontColor(Color.Red)
        .fontSize(24)
      if (this.orientation % 2 == 0) {
        Column() {
          Stack()
            .onTouch((event)=>{
              event.stopPropagation()
              for (let index = 0; index < event.touches.length; index++) {
                this.handleTouchOpt(event.touches[index].id, event.touches[index].type,
                  {x: event.touches[index].windowX, y: event.touches[index].windowY})
              }
              this.yaw = getYaw();
              this.pitch = getPitch();
              this.front = getFront();
            })
            .width('100%')
            .layoutWeight(1)
          Stack() {
              Controller()
            }
          .width('60%')
          .aspectRatio(1)
        }
        .alignItems(HorizontalAlign.Center)
        .width('100%')
        .height('100%')
      } else {
        Row() {
          Stack() {
            Controller()
          }
          .height('60%')
          .aspectRatio(1)
          Stack()
            .onTouch((event)=>{
              event.stopPropagation()
              for (let index = 0; index < event.touches.length; index++) {
                this.handleTouchOpt(event.touches[index].id, event.touches[index].type,
                  {x: event.touches[index].windowX, y: event.touches[index].windowY})
              }
              this.yaw = getYaw();
              this.pitch = getPitch();
              this.front = getFront();
            })
            .height('100%')
            .layoutWeight(1)
        }
        .alignItems(VerticalAlign.Bottom)
        .width('100%')
        .height('100%')
      }
    }
    .ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM])
    .width((this.windowSize.width).toString() + 'px')
    .height((this.windowSize.height).toString() + 'px')
    .onSizeChange(()=>{
      this.orientation = display.getDefaultDisplaySync().orientation
      windowSizeChange(this.windowSize.width, this.windowSize.height, this.orientation)
    })
  }
}
