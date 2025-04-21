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
import { describe, beforeAll, it} from '@ohos/hypium'
import { Driver, Component } from '@kit.TestKit';
import { ON } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
} from '../../../utils';
import { NavigationStart } from './Navigation';

const driver = Driver.create();

export default function Navigation1() {
  describe('Navigation1', () => {
    beforeAll(async (done: Function) => {
      await NavigationStart(done)
    })
    /**
     * 测试组件'title.main'支持设置包含单个子组件为'Title'且获取属性正确
     */
    it('ArkUI_Navigation_001', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.main')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done()
    })

    /**
     * 测试组件'title.main'支持设置包含单个子组件为'titleMain'且获取属性正确
     */
    it('ArkUI_Navigation_002', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.main')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.main'支持设置包含单个子组件为'title.main'且获取属性正确
     */
    it('ArkUI_Navigation_003', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.main')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'title.sub'支持设置包含单个子组件为'subtitle'且获取属性正确
     */
    it('ArkUI_Navigation_004', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.sub')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.sub'支持设置包含单个子组件为'titleSub'且获取属性正确
     */
    it('ArkUI_Navigation_005', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.sub')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.sub'支持设置包含单个子组件为'title.sub'且获取属性正确
     */
    it('ArkUI_Navigation_006', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.sub')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundColor'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Navigation_007', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundColor'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Navigation_008', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundColor'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Navigation_009', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundColor'支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Navigation_010', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundColor'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Navigation_011', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundColor'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Navigation_012', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'Thin'且获取属性正确
     */
    it('ArkUI_Navigation_013', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'Regular'且获取属性正确
     */
    it('ArkUI_Navigation_014', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'Thick'且获取属性正确
     */
    it('ArkUI_Navigation_015', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THIN'且获取属性正确
     */
    it('ArkUI_Navigation_016', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_REGULAR'且获取属性正确
     */
    it('ArkUI_Navigation_017', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_018', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_019', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'NONE'且获取属性正确
     */
    it('ArkUI_Navigation_020', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THIN'且获取属性正确
     */
    it('ArkUI_Navigation_021', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THIN'且获取属性正确
     */
    it('ArkUI_Navigation_022', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_REGULAR'且获取属性正确
     */
    it('ArkUI_Navigation_023', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_024', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_025', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.barStyle'支持设置包含单个子组件为'STANDARD'且获取属性正确
     */
    it('ArkUI_Navigation_026', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.barStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.barStyle'支持设置包含单个子组件为'STACK'且获取属性正确
     */
    it('ArkUI_Navigation_027', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.barStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.paddingStart'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Navigation_028', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.paddingStart')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.paddingEnd'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Navigation_029', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.paddingEnd')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.value'支持设置包含单个子组件为'menu1'且获取属性正确
     */
    it('ArkUI_Navigation_030', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.value')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.value'支持设置包含单个子组件为'menu-1'且获取属性正确
     */
    it('ArkUI_Navigation_031', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.value'支持设置包含单个子组件为'menu.1'且获取属性正确
     */
    it('ArkUI_Navigation_032', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.value')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.icon'支持设置包含单个子组件为'startIcon'且获取属性正确
     */
    it('ArkUI_Navigation_033', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.value')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.icon'支持设置包含单个子组件为'foreground'且获取属性正确
     */
    it('ArkUI_Navigation_034', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.icon'支持设置包含单个子组件为'background'且获取属性正确
     */
    it('ArkUI_Navigation_035', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.value')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.isEnabled'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Navigation_036', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.isEnabled')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.isEnabled'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Navigation_037', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'menus.isEnabled')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'titleMode'支持设置包含单个子组件为'Free'且获取属性正确
     */
    it('ArkUI_Navigation_038', 0, async (done: Function) => {
      await titleSearch('参数列表', 'titleMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('titleMode', JsonType.value),
        ],
        assertEqual: 'NavigationTitleMode.Free'
      })
      done();
    })

    /**
     * 测试组件'titleMode'支持设置包含单个子组件为'Full'且获取属性正确
     */
    it('ArkUI_Navigation_039', 0, async (done: Function) => {
      await titleSearch('参数列表', 'titleMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('titleMode', JsonType.value),
        ],
        assertEqual: 'NavigationTitleMode.Full'
      })
      done();
    })

    /**
     * 测试组件'titleMode'支持设置包含单个子组件为'Mini'且获取属性正确
     */
    it('ArkUI_Navigation_040', 0, async (done: Function) => {
      await titleSearch('参数列表', 'titleMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('titleMode', JsonType.value),
        ],
        assertEqual: 'NavigationTitleMode.Mini'
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.value'支持设置包含单个子组件为'app'且获取属性正确
     */
    it('ArkUI_Navigation_041', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.value')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.value'支持设置包含单个子组件为'a'且获取属性正确
     */
    it('ArkUI_Navigation_042', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.value'支持设置包含单个子组件为'app1'且获取属性正确
     */
    it('ArkUI_Navigation_043', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.value')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.icon'支持设置包含单个子组件为'foreground'且获取属性正确
     */
    it('ArkUI_Navigation_044', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.icon')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.icon'支持设置包含单个子组件为'startIcon'且获取属性正确
     */
    it('ArkUI_Navigation_045', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.icon')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.icon'支持设置包含单个子组件为'background'且获取属性正确
     */
    it('ArkUI_Navigation_046', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.icon')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.status'支持设置包含单个子组件为'NORMAL'且获取属性正确
     */
    it('ArkUI_Navigation_047', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.status')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.status'支持设置包含单个子组件为'DISABLED'且获取属性正确
     */
    it('ArkUI_Navigation_048', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.status')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.status'支持设置包含单个子组件为'ACTIVE'且获取属性正确
     */
    it('ArkUI_Navigation_049', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.status')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.activeIcon'支持设置包含单个子组件为'foreground'且获取属性正确
     */
    it('ArkUI_Navigation_050', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.activeIcon')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.activeIcon'支持设置包含单个子组件为'startIcon'且获取属性正确
     */
    it('ArkUI_Navigation_051', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.activeIcon')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.activeIcon'支持设置包含单个子组件为'background'且获取属性正确
     */
    it('ArkUI_Navigation_052', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.activeIcon')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundColor'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Navigation_053', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundColor'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Navigation_054', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundColor'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Navigation_055', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundColor'支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Navigation_056', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundColor'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Navigation_057', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundColor'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Navigation_058', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'Thin'且获取属性正确
     */
    it('ArkUI_Navigation_059', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'Regular'且获取属性正确
     */
    it('ArkUI_Navigation_060', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'Thick'且获取属性正确
     */
    it('ArkUI_Navigation_061', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THIN'且获取属性正确
     */
    it('ArkUI_Navigation_062', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_REGULAR'且获取属性正确
     */
    it('ArkUI_Navigation_063', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_064', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_065', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'NONE'且获取属性正确
     */
    it('ArkUI_Navigation_066', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THIN'且获取属性正确
     */
    it('ArkUI_Navigation_067', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THIN'且获取属性正确
     */
    it('ArkUI_Navigation_068', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_REGULAR'且获取属性正确
     */
    it('ArkUI_Navigation_069', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_070', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'toolbarConfiguration.options.backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_Navigation_071', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'toolbarConfiguration.options.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'hideToolBar'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Navigation_072', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideToolBar')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideToolBar', JsonType.value),
        ],
        assertEqual: true
      })
      done();
    })

    /**
     * 测试组件'hideToolBar'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Navigation_073', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideToolBar')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideToolBar', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })

    /**
     * 测试组件'hideTitleBar'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Navigation_074', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideTitleBar')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideTitleBar', JsonType.value),
        ],
        assertEqual: true
      })
      done();
    })

    /**
     * 测试组件'hideTitleBar'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Navigation_075', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideTitleBar')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideTitleBar', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })

    /**
     * 测试组件'hideBackButton'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Navigation_076', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideBackButton')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideBackButton', JsonType.value),
        ],
        assertEqual: true
      })
      done();
    })

    /**
     * 测试组件'hideBackButton'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Navigation_077', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideBackButton')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideBackButton', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })

    /**
     * 测试组件'navBarWidth'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Navigation_078', 0, async (done: Function) => {
      await titleSearch('参数列表', 'navBarWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('navBarWidth', JsonType.value),
        ],
        assertEqual: '600.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('navBarWidth', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })
      done();
    })

    /**
     * 测试组件'navBarPosition'支持设置包含单个子组件为'Start'且获取属性正确
     */
    it('ArkUI_Navigation_079', 0, async (done: Function) => {
      await titleSearch('参数列表', 'navBarPosition')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('navBarPosition', JsonType.value),
        ],
        assertEqual: 'NavBarPosition.Start'
      })
      done();
    })

    /**
     * 测试组件'navBarPosition'支持设置包含单个子组件为'End'且获取属性正确
     */
    it('ArkUI_Navigation_080', 0, async (done: Function) => {
      await titleSearch('参数列表', 'navBarPosition')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('navBarPosition', JsonType.value),
        ],
        assertEqual: 'NavBarPosition.End'
      })
      done();
    })

    /**
     * 测试组件'mode'支持设置包含单个子组件为'Stack'且获取属性正确
     */
    it('ArkUI_Navigation_081', 0, async (done: Function) => {
      await titleSearch('参数列表', 'mode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mode', JsonType.value),
        ],
        assertEqual: 'NavigationMode.STACK'
      })
      done();
    })

    /**
     * 测试组件'mode'支持设置包含单个子组件为'Split'且获取属性正确
     */
    it('ArkUI_Navigation_082', 0, async (done: Function) => {
      await titleSearch('参数列表', 'mode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mode', JsonType.value),
        ],
        assertEqual: 'NavigationMode.SPLIT'
      })
      done();
    })

    /**
     * 测试组件'mode'支持设置包含单个子组件为'Auto'且获取属性正确
     */
    it('ArkUI_Navigation_083', 0, async (done: Function) => {
      await titleSearch('参数列表', 'mode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mode', JsonType.value),
        ],
        assertEqual: 'NavigationMode.AUTO'
      })
      done();
    })

    /**
     * 测试组件'backButtonIcon'支持设置包含单个子组件为'foreground'且获取属性正确
     */
    it('ArkUI_Navigation_084', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backButtonIcon')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backButtonIcon', JsonType.value),
        ],
        assertEqual: "resource:///33554441.png"
      })
      done();
    })

    /**
     * 测试组件'backButtonIcon'支持设置包含单个子组件为'startIcon'且获取属性正确
     */
    it('ArkUI_Navigation_085', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backButtonIcon')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backButtonIcon', JsonType.value),
        ],
        assertEqual: "resource:///33554446.png"
      })
      done();
    })

    /**
     * 测试组件'backButtonIcon'支持设置包含单个子组件为'background'且获取属性正确
     */
    it('ArkUI_Navigation_086', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backButtonIcon')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backButtonIcon', JsonType.value),
        ],
        assertEqual: "resource:///33554440.png"
      })
      done();
    })

    /**
     * 测试组件'hideNavBar'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_Navigation_087', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideNavBar')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideNavBar', JsonType.value),
        ],
        assertEqual: true
      })
      done();
    })

    /**
     * 测试组件'hideNavBar'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_Navigation_088', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hideNavBar')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hideNavBar', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })

    /**
     * 测试组件'navBarWidthRange.min'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Navigation_089', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'navBarWidthRange.min')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'navBarWidthRange.max'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Navigation_090', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'navBarWidthRange.max')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'minContentWidth'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_Navigation_091', 0, async (done: Function) => {
      await titleSearch('参数列表', 'minContentWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'minContentWidth'
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minContentWidth', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'minContentWidth'
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minContentWidth', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })
      done();
    })

    /**
     * 测试组件'ignoreLayoutSafeArea.types'支持设置包含单个子组件为'SYSTEM'且获取属性正确
     */
    it('ArkUI_Navigation_092', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'ignoreLayoutSafeArea.types')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'ignoreLayoutSafeArea.types'
        },
      })
      done();
    })

    /**
     * 测试组件'ignoreLayoutSafeArea.edges'支持设置包含单个子组件为'TOP, BOTTOM'且获取属性正确
     */
    it('ArkUI_Navigation_093', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'ignoreLayoutSafeArea.edges')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'ignoreLayoutSafeArea.edges'
        },
      })
      done();
    })

    /**
     * 测试组件'ignoreLayoutSafeArea.edges'支持设置包含单个子组件为'TOP'且获取属性正确
     */
    it('ArkUI_Navigation_094', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'ignoreLayoutSafeArea.edges')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'ignoreLayoutSafeArea.edges'
        },
      })
      done();
    })

    /**
     * 测试组件'ignoreLayoutSafeArea.edges'支持设置包含单个子组件为'BOTTOM'且获取属性正确
     */
    it('ArkUI_Navigation_095', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'ignoreLayoutSafeArea.edges')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'ignoreLayoutSafeArea.edges'
        },
      })
      done();
    })

    /**
     * 测试组件'systemBarStyle.statusBarContentColor'支持设置包含单个子组件为'#0xE5FFFFFF'且获取属性正确
     */
    it('ArkUI_Navigation_096', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'systemBarStyle.statusBarContentColor')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'systemBarStyle.statusBarContentColor'
        },
      })
      done();
    })

    /**
     * 测试组件'systemBarStyle.statusBarContentColor'支持设置包含单个子组件为'#0xA5FF00FF'且获取属性正确
     */
    it('ArkUI_Navigation_097', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'systemBarStyle.statusBarContentColor')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'systemBarStyle.statusBarContentColor'
        },
      })
      done();
    })

    /**
     * 测试组件'systemBarStyle.statusBarContentColor'支持设置包含单个子组件为'#0xF5AA00FF'且获取属性正确
     */
    it('ArkUI_Navigation_098', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'systemBarStyle.statusBarContentColor')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'systemBarStyle.statusBarContentColor'
        },
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_Navigation_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Navigation',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
  })
}