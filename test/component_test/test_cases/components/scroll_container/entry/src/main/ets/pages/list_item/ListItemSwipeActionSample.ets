/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import listItemSwipeActionTest from '../MyTest/ListItemSwipeActionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListItemSwipeActionSample {
  @State swipeActionType: SwipeActionItem = {
    builder: () => {
      this.item()
    },
    actionAreaDistance: '10px',
    onAction: () => {
      this.onAction = "NO"
    },
    onEnterActionArea: () => {
      this.onEnterActionArea = "NO"
    },
    onExitActionArea: () => {
      this.onExitActionArea = "NO"
    },
    onStateChange: () => {
      this.onStateChange = "NO"
    }
  }
  @State swipeActionEdgeEffectType: SwipeEdgeEffect = SwipeEdgeEffect.Spring
  @State onEnterActionArea: string = "NO"
  @State onExitActionArea: string = "NO"
  @State onAction: string = "NO"
  @State onStateChange: string = "NO"

  @Builder
  item() {
    Text("item").margin("4vp")
  }

  aboutToAppear(): void {
    loadComponentTestEntry(listItemSwipeActionTest)
  }

  build() {
    Column() {
      List() {
        ListItem() {
          Text("list item swipeAction1")
            .width('100%')
            .height(100)
        }
        .swipeAction({
          start: {
            builder: () => {
              this.item()
            },
            onAction: () => {
              this.onAction = "YES"
            },
            actionAreaDistance: 56,
            onEnterActionArea: () => {
              this.onEnterActionArea = "YES"
            },
            onExitActionArea: () => {
              this.onExitActionArea = "YES"
            },
            onStateChange: () => {
              this.onStateChange = "YES"
            }
          }
        })
        .id('listItemSwipeAction1')
      }

      List() {
        ListItem() {
          Text("list item swipeAction2")
            .width('100%')
            .height(100)
        }
        .swipeAction({
          start: () => {
            this.item()
          }, end: () => {
            this.item()
          }
        })
        .id('listItemSwipeAction2')
      }

      Text(this.onEnterActionArea)
      Text(this.onExitActionArea)
      Text(this.onAction)
      Text(this.onStateChange)
      List() {
        ListItem() {
          Text("list item swipeAction3")
            .width('100%')
            .height(100)
        }
        .swipeAction({ end: this.swipeActionType, edgeEffect: this.swipeActionEdgeEffectType })
        .id('listItemSwipeAction3')
      }

      Button('ListItemSwipeAction')
        .onClick(() => {
          this.swipeActionType = {
            builder: () => {
              this.item()
            },
            actionAreaDistance: $r('app.string.length'),
            onAction: () => {
              this.onAction = "OR"
            },
            onEnterActionArea: () => {
              this.onEnterActionArea = "OR"
            },
            onExitActionArea: () => {
              this.onExitActionArea = "OR"
            },
            onStateChange: () => {
              this.onStateChange = "OR"
            }
          }
          this.swipeActionEdgeEffectType = SwipeEdgeEffect.None
        })
    }
  }
}