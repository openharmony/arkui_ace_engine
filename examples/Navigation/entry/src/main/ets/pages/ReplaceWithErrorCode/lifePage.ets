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
import { LifePageOne } from './LifePageOne';
import { LifePageThree } from './LifePageThree';
import { LifePageTwo } from './LifePageTwo';
import observer from '@ohos.arkui.observer';
import { printPathStack } from '../utils/Index';

@Entry
@Component
struct liftPage {
  @Provide lifepageInfos: NavPathStack = new NavPathStack();

  @Builder
  pageMap(name: string) {
    if (name == 'pageOne') {
      LifePageOne()
    }
    else if (name == 'pageTwo') {
      LifePageTwo()
    }
    else if (name == 'pageThree') {
      LifePageThree()
    }
  }
  navDesUpdateCallback(info: NavDestinationInfo) {
    console.log(printPathStack(info, 'ReplaceWithErrorCode'));
  }

  aboutToDisappear(): void {
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
  }

  observerOn(){
    observer.on('navDestinationUpdate', this.navDesUpdateCallback);
  }

  observerOff(){
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
  }

  build() {
    Navigation(this.lifepageInfos){
      Column({space: '10vp'}) {
        Row({space:5}){
          Button('observer.on')
            .onClick(() => {
              this.observerOn()
            })

          Button('observer.off')
            .onClick(() => {
              this.observerOff()
            })
        }
        Button("pushDestination pageOne").onClick(() => {
          this.lifepageInfos.pushDestination({ name: 'pageOne' })
        })
      }
    }
    .title('生命周期＋无感监听')
    .navDestination(this.pageMap)
  }
}