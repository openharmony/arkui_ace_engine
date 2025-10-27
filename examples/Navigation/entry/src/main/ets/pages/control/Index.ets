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

import base from '@ohos.base';
import observer from '@ohos.arkui.observer';

class MyParam {
  constructor(count: number) {
    this.count = count;
  }
  count: number;
}

let nextCount: number = 1;

@Component
struct ControlComponent {
  @Consume('myStack') stack: NavPathStack;
  @Consume('nextCount') nextCount: number;
  @State count: number = -1;
  @State setMode: boolean = false;
  @State mode: LaunchMode = LaunchMode.STANDARD;
  @State setAnimated: boolean = false;
  @State animated: boolean = true;
  private options: NavigationOptions | undefined = {};
  @State pageOptions: Array<string> = [];
  @State pageIndex: number = 0;
  @State pageName: string = 'Page1';
  @State allPageList: string = '';
  private navDestinationId: string = '';

  @Styles buttonStyles() {
    .padding(2)
    .margin(2)
    .height(24)
  }

  UpdateOptions() {
    if (!this.setMode && !this.setAnimated) {
      this.options = undefined;
      return;
    }
    this.options = {};
    if (this.setMode) {
      this.options.launchMode = this.mode;
    }
    if (this.setAnimated) {
      this.options.animated = this.animated;
    }
  }

  onNavDestinationUpdate(info: NavDestinationInfo): void {
    if (info.state != observer.NavDestinationState.ON_SHOWN || this.navDestinationId !== info.navDestinationId) {
      return;
    }

    this.count = (info.param as MyParam).count;
    let index = info.index;
    let count2 = (this.stack.getParamByIndex(index) as MyParam).count;
    console.log(`testTag onNavDestinationUpdate, navDestinationId: ${this.navDestinationId}, count: ${this.count}, count2: ${count2}`);

    this.updateStackInfo();

    console.log(`testTag setMode: ${this.setMode}, mode: ${this.mode}, setAnimated: ${this.setAnimated}, animated: ${this.animated}`);
  }

  updateStackInfo(): void {
    let names: Array<string> = this.stack.getAllPathName();
    let str = `Page Number: ${names.length}\n`;
    for (let i = 0; i < names.length; ++i) {
      if (!this.stack.getParamByIndex(i)) {
        str += `Page[${i}] ${names[i]}, param: undefined\n`;
      } else {
        str += `Page[${i}] ${names[i]}, param:\n  ${JSON.stringify(this.stack.getParamByIndex(i))}\n`;
      }
    }
    str += `-----------------------\n`;
    let info = this.queryNavDestinationInfo();
    if (info) {
      this.count = (info.param as MyParam).count;
      str += `queryNavDesInfo.count: ${this.count}`;
    }
    this.allPageList = str;
  }

  aboutToAppear(): void {
    console.log(`testTag aboutToAppear`);
    this.UpdateOptions();
    this.pageOptions = ['Page1','Page2']
    this.pageIndex = 0;
    this.pageName = 'Page1';

    let info = this.queryNavDestinationInfo();
    if (info) {
      this.navDestinationId = info.navDestinationId;
      this.count = (info.param as MyParam).count;
      console.log(`testTag aboutToAppear, navDestinationId: ${this.navDestinationId}, count: ${this.count}`);
    }

    this.updateStackInfo();

    observer.on('navDestinationUpdate', this.onNavDestinationUpdate.bind(this));
  }

  aboutToDisappear(): void {
    observer.off('navDestinationUpdate', this.onNavDestinationUpdate.bind(this));
  }

  build() {
    Column() {
      Text(`param: count: ${this.count}`).fontSize(12)
      Text(`nextCount: ${this.nextCount}`).fontSize(12)
      Flex({wrap: FlexWrap.Wrap}) {
        Button('Set LaunchMode STANDARD')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.setMode = true
            this.mode = LaunchMode.STANDARD;
            this.UpdateOptions();
          })

        Button('Set LaunchMode MOVE_TO_TOP_SINGLETON')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.setMode = true
            this.mode = LaunchMode.MOVE_TO_TOP_SINGLETON;
            this.UpdateOptions();
          })

        Button('Set LaunchMode POP_TO_SINGLETON')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.setMode = true
            this.mode = LaunchMode.POP_TO_SINGLETON;
            this.UpdateOptions();
          })

        Button('Set animated True')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.setAnimated = true
            this.animated = true;
            this.UpdateOptions();
          })
        Button('Set animated False')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.setAnimated = false
            this.animated = false;
            this.UpdateOptions();
          })
        ForEach(this.pageOptions, (item:string, index) => {
          Button(item)
            .fontSize(12)
            .buttonStyles()
            .onClick(() => {
              this.pageIndex = Math.round(index);
              this.pageName = item;
              console.log(`testTag select PageName: ${this.pageName}`);
            })
        })
        Button('pushPath')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.stack.pushPath({name: this.pageName, param: new MyParam(this.nextCount++)}, this.options);
          })
        Button('pushDestination')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.stack.pushDestination({name: this.pageName, param: new MyParam(this.nextCount++)}, this.options).then(() => {
              console.log('pushDestination success')
            }).catch((e: base.BusinessError) => {
              console.log(`pushDestination failed: ${JSON.stringify(e)}`)
            })
          })
        Button('replacePath')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.stack.replacePath({name: this.pageName, param: new MyParam(this.nextCount++)}, this.options);
          })
        Button('pop')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.stack.pop();
          })
        Button('clear')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.stack.clear();
          })
        Button('showLatestStackInfo')
          .key('showLatestStackInfo')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.updateStackInfo();
          })
      }

      Text(this.allPageList).margin({top:10}).fontSize(10)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct Page1 {
  build() {
    NavDestination() {
      ControlComponent()
    }
    .width('100%')
    .height('100%')
    .title('Page1')
  }
}
@Component
struct Page2 {
  build() {
    NavDestination() {
      ControlComponent()
    }
    .width('100%')
    .height('100%')
    .title('Page2')
  }
}


@Entry
@Component
struct Index {
  @Provide('myStack') stack: NavPathStack = new NavPathStack();
  @Provide('nextCount') count: number = 1;

  aboutToAppear(): void {

  }

  @Builder
  pageBuilder(name: string) {
    if (name == 'Page1') {
      Page1()
    } else if (name == 'Page2') {
      Page2()
    }
  }

  build() {
    Navigation(this.stack) {
      ControlComponent()
    }
    .width('100%')
    .height('100%')
    .navDestination(this.pageBuilder)
    .title('Navigation')
  }
}
