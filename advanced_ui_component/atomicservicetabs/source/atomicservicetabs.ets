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

const DEFAULT_BAR_WIDTH: number = 96;
const DEFAULT_BAR_HEIGHT: number = 52;

@Component
export struct AtomicServiceTabs {
  @BuilderParam tabContents?: [TabContentBuilder?,
                              TabContentBuilder?,
                              TabContentBuilder?,
                              TabContentBuilder?,
                              TabContentBuilder?];
  @Prop tabBarOptionsArray: [TabBarOptions, TabBarOptions, TabBarOptions?, TabBarOptions?, TabBarOptions?];
  @Prop tabBarPosition?: TabBarPosition = TabBarPosition.BOTTOM;
  @Prop barBackgroundColor?: ResourceColor = Color.Transparent;
  @Prop index?: number | undefined = 0;
  @Prop barOverlap?: boolean = true;
  controller?: TabsController = new TabsController();
  onChange?: Callback<number>;
  onTabBarClick?: Callback<number>;
  onContentWillChange?: OnContentWillChangeCallback;

  build() {
    Tabs({
      barPosition: this.tabBarPosition === TabBarPosition.LEFT ? BarPosition.Start : BarPosition.End,
      index: this.index,
      controller: this.controller
    }) {
      ForEach(this.tabBarOptionsArray, (item: TabBarOptions, index: number) => {
        if (item) {
          TabContent() {
            if (this.tabContents && this.tabContents[index]) {
              this.tabContents[index]?.()
            }
          }
          .tabBar(BottomTabBarStyle.of(item.icon, item.text)
            .labelStyle({ unselectedColor: item.unselectedColor, selectedColor: item.selectedColor })
            .iconStyle({ unselectedColor: item.unselectedColor, selectedColor: item.selectedColor }))
          .width((!this.tabContents && this.tabBarPosition === TabBarPosition.LEFT) ? DEFAULT_BAR_WIDTH : '100%')
          .height((!this.tabContents && this.tabBarPosition === TabBarPosition.BOTTOM) ? DEFAULT_BAR_HEIGHT : '100%')
        }
      })
    }
    .barBackgroundColor(this.barBackgroundColor)
    .divider(null)
    .vertical(this.tabBarPosition === TabBarPosition.LEFT ? true : false)
    .scrollable(false)
    .barOverlap(this.barOverlap)
    .barBackgroundBlurStyle(BlurStyle.COMPONENT_THICK)
    .onChange(this.onChange)
    .onTabBarClick(this.onTabBarClick)
    .onContentWillChange(this.onContentWillChange)
    .width((!this.tabContents && this.tabBarPosition === TabBarPosition.LEFT) ? DEFAULT_BAR_WIDTH : '100%')
    .height((!this.tabContents && this.tabBarPosition === TabBarPosition.BOTTOM) ? DEFAULT_BAR_HEIGHT : '100%')
  }
}

export class TabBarOptions {
  public icon: ResourceStr | TabBarSymbol;
  public text: ResourceStr;
  public unselectedColor?: ResourceColor;
  public selectedColor?: ResourceColor;

  constructor(icon: ResourceStr | TabBarSymbol, text: ResourceStr,
              unselectedColor?: ResourceColor, selectedColor?: ResourceColor) {
    this.icon = icon;
    this.text = text;
    this.unselectedColor = unselectedColor;
    this.selectedColor = selectedColor;
  }
}

export enum TabBarPosition {
  LEFT = 0,
  BOTTOM = 1
}

export type TabContentBuilder = () => void;
export type OnContentWillChangeCallback = (currentIndex: number, comingIndex: number) => boolean;