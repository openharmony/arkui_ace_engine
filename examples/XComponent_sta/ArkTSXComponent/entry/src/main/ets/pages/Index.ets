'use static';

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
// [Start xcomponent_index]
import { State } from '@ohos.arkui.stateManagement';
import { Button, Column, ColumnOptions, Component, Entry, FlexAlign, Row, SurfaceRect, Text, VerticalAlign, XComponent, XComponentController, XComponentOptions, XComponentType } from '@ohos.arkui.component';

export class NativeMethods {
  static { loadLibrary("entry") }
  static native SetSurfaceId(surfaceId: long): void;
  static native DestroySurface(surfaceId: long): void;
  static native ChangeSurface(surfaceId: long): void;
  static native ChangeColor(surfaceId: long): void;
  static native DrawPattern(surfaceId: long): void;
  static native GetXComponentStatus(surfaceId: long): void;
}

class SampleXComponentController extends XComponentController {
  surfaceId: string = '';

  onSurfaceCreated(surfaceId: string): void {
    this.surfaceId = surfaceId;
    NativeMethods.SetSurfaceId(BigInt(surfaceId).getLong());
  }

  onSurfaceChanged(surfaceId: string, rect: SurfaceRect): void {
    NativeMethods.ChangeSurface(BigInt(surfaceId).getLong());
  }

  onSurfaceDestroyed(surfaceId: string): void {
    NativeMethods.DestroySurface(BigInt(surfaceId).getLong());
    this.surfaceId = '';
  }
}

@Entry
@Component
struct Index {
  @State currentStatus: string = "index";
  private xComponentController: SampleXComponentController = new SampleXComponentController();

  build(): void {
    Column() {
        // [StartExclude xcomponent_index]
        Row() {
            Text('Native XComponent Sample')
            .fontSize('24fp')
            .fontWeight(500)
            .margin({
                left: 24,
                top: 12
            })
        }
        .margin({ top: 24 })
        .width('100%')
        .height(56)
        // [EndExclude xcomponent_index]

        Column({ space: 10 } as ColumnOptions) {
            XComponent({
            type: XComponentType.SURFACE,
            controller: this.xComponentController
            } as XComponentOptions)
            .id('xcomponent')

            Text(this.currentStatus)
            .fontSize('24fp')
            .fontWeight(500)
        }
        .onClick(() => {
            if (this.xComponentController.surfaceId) {
                NativeMethods.ChangeColor(BigInt(this.xComponentController.surfaceId).getLong());
                this.currentStatus = "change color";
            }
        })
        // [StartExclude xcomponent_index]
        .margin({
            top: 27,
            left: 12,
            right: 12
        })
        .height('40%')
        .width('90%')
        // [EndExclude xcomponent_index]

        Row() {
            Button('Draw Star')
            .fontSize('16fp')
            .fontWeight(500)
            .margin({ bottom: 24 })
            .onClick(() => {
                if (this.xComponentController.surfaceId) {
                    NativeMethods.DrawPattern(BigInt(this.xComponentController.surfaceId).getLong());
                    this.currentStatus = "draw star";
                }
            })
            .width('53.6%')
            .height(40)
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .alignItems(VerticalAlign.Bottom)
        .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
  }
}
// [End xcomponent_index]
