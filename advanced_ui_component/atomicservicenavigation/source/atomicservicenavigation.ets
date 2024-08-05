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

import { Callback } from '@ohos.base';

@Component
export struct AtomicServiceNavigation {
  @State navPathStack?: NavPathStack = new NavPathStack();
  @BuilderParam navigationContent?: Callback<void>;
  @Prop title?: ResourceStr;
  @Prop titleOptions?: TitleOptions = { isBlurEnabled: true };
  @Prop hideTitleBar?: boolean;
  @Prop navBarWidth?: Length;
  @Prop mode?: NavigationMode;
  @BuilderParam navDestinationBuilder?: NavDestinationBuilder = this.defaultNavDestinationBuilder;
  @Prop navBarWidthRange?: [Dimension, Dimension];
  @Prop minContentWidth?: Dimension;
  stateChangeCallback?: Callback<boolean>;
  modeChangeCallback?: Callback<NavigationMode>;

  @Builder
  defaultNavDestinationBuilder(name: string, param?: Object) {
  }

  build() {
    Navigation(this.navPathStack) {
      if (this.navigationContent) {
        this.navigationContent()
      }
    }
    .title(this.title, {
      backgroundColor: this.titleOptions?.backgroundColor,
      backgroundBlurStyle: this.titleOptions?.isBlurEnabled ? BlurStyle.COMPONENT_THICK : BlurStyle.NONE,
      barStyle: this.titleOptions?.barStyle
    })
    .titleMode(NavigationTitleMode.Mini)
    .hideBackButton(true)
    .hideTitleBar(this.hideTitleBar)
    .navBarWidth(this.navBarWidth)
    .navBarPosition(NavBarPosition.Start)
    .mode(this.mode)
    .navDestination(this.navDestinationBuilder)
    .navBarWidthRange(this.navBarWidthRange)
    .minContentWidth(this.minContentWidth)
    .onNavBarStateChange(this.stateChangeCallback)
    .onNavigationModeChange(this.modeChangeCallback)
  }
}

export interface TitleOptions {
  backgroundColor?: ResourceColor,
  isBlurEnabled?: boolean,
  barStyle?: BarStyle
}

export type NavDestinationBuilder = (name: string, param?: Object) => void;