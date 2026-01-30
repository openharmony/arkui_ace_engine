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

import { dispatchController } from 'libentry.so';
import GlobalThis from '../GlobalThis'

@Reusable
@Component
export struct Controller {
  length: number = 0


  handleTouchOpt(id: number, type: TouchType, pos: Position)
  {
    GlobalThis.getInstance().touches.set(id, pos)
    if (type == TouchType.Down) {
      if (GlobalThis.getInstance().touch1Id == -1) {
        GlobalThis.getInstance().touch1Id = id
        GlobalThis.getInstance().touch1StorePos = pos
        dispatchController(pos.x as number, pos.y as number, this.length, 0.1)
      }
    } else if (type == TouchType.Move) {
      if (GlobalThis.getInstance().touch1Id == id) {
        dispatchController(pos.x as number, pos.y as number, this.length, 1.1)
      }
    } else {
      GlobalThis.getInstance().touches.delete(id)
      if (GlobalThis.getInstance().touch1Id == id) {
        GlobalThis.getInstance().touch1Id = -1
        dispatchController(pos.x as number, pos.y as number, this.length, 2.1)
      }
    }
  }

  build() {
    Stack() {
      Stack()
      .backgroundColor('#99ffffff')
      .width('30%')
      .height('30%')
    }
    .borderColor('#99ffffff')
    .borderWidth(2)
    .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions)=>{
      this.length = newValue.width as number
    })
    .hitTestBehavior(HitTestMode.BLOCK_HIERARCHY)
    .onTouch((event)=>{
      event.stopPropagation()
      for (let index = 0; index < event.touches.length; index++) {
        this.handleTouchOpt(event.touches[index].id, event.touches[index].type,
          {x: event.touches[index].x, y: event.touches[index].y})
      }
    })
    .width('100%')
    .height('100%')
  }
}
