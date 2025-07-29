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
import { NavDestination } from './NavDestination';

const driver = Driver.create();

export default function NavDestination0(){
  describe('NavDestination', () => {
    beforeAll(async (done: Function) => {
      await NavDestination(done)
    })

    /**
     * 测试组件'title.main'支持设置包含单个子组件为'Title'且获取属性正确
     */
    it('ArkUI_NavDestination_001', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_002', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_003', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_004', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_005', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_006', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_007', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_008', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_009', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_010', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_011', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_012', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_013', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_014', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_015', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_016', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_017', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_018', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_019', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_020', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_021', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_022', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_023', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_024', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_025', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_026', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_027', 0, async (done: Function) => {
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
     * 测试组件'title.options.paddingStart.LengthMetrics.resource'支持设置包含单个子组件为'margin_left'且获取属性正确
     */
    it('ArkUI_NavDestination_028', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.paddingStart.LengthMetrics.resource')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.paddingStart.LengthMetrics.resource'支持设置包含单个子组件为'margin_right'且获取属性正确
     */
    it('ArkUI_NavDestination_029', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.paddingStart.LengthMetrics.resource')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.paddingStart.LengthMetrics.resource'支持设置包含单个子组件为'margin_left_none'且获取属性正确
     */
    it('ArkUI_NavDestination_030', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.paddingStart.LengthMetrics.resource')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'title.options.paddingStart.LengthMetrics.resource'支持设置包含单个子组件为'margin_right_none'且获取属性正确
     */
    it('ArkUI_NavDestination_031', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'title.options.paddingStart.LengthMetrics.resource')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'hideTitleBar'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_NavDestination_036', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hideTitleBar')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'hideTitleBar'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_NavDestination_037', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hideTitleBar')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'mode'支持设置包含单个子组件为'STANDARD'且获取属性正确
     */
    it('ArkUI_NavDestination_038', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'mode'支持设置包含单个子组件为'DIALOG'且获取属性正确
     */
    it('ArkUI_NavDestination_039', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backButtonIcon'支持设置包含单个子组件为'foreground'且获取属性正确
     */
    it('ArkUI_NavDestination_040', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backButtonIcon')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backButtonIcon'支持设置包含单个子组件为'startIcon'且获取属性正确
     */
    it('ArkUI_NavDestination_041', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backButtonIcon')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backButtonIcon'支持设置包含单个子组件为'background'且获取属性正确
     */
    it('ArkUI_NavDestination_042', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backButtonIcon')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'menus.value'支持设置包含单个子组件为'menu1'且获取属性正确
     */
    it('ArkUI_NavDestination_043', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_044', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_045', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_046', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_047', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_048', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_049', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_050', 0, async (done: Function) => {
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
     * 测试组件'ignoreLayoutSafeArea.types'支持设置包含单个子组件为'SYSTEM'且获取属性正确
     */
    it('ArkUI_NavDestination_051', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_052', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_053', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_054', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_055', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_056', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_057', 0, async (done: Function) => {
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
     * 测试组件'flexBasis'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_NavDestination_058', 0, async (done: Function) => {
      await titleSearch('参数列表', 'flexBasis')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'flexBasis'
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value),
        ],
        assertEqual: '200.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'flexBasis'
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value),
        ],
        assertEqual: '10.00vp'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Auto'且获取属性正确
     */
    it('ArkUI_NavDestination_059', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'direction'
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Auto'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Ltr'且获取属性正确
     */
    it('ArkUI_NavDestination_060', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'direction'
        },
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Rtl'且获取属性正确
     */
    it('ArkUI_NavDestination_061', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'direction'
        },
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
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
        id: 'NavDestination',
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
    it('ArkUI_NavDestination_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'NavDestination',
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
        id: 'NavDestination',
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
    it('ArkUI_NavDestination_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'NavDestination',
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
        id: 'NavDestination',
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
    it('ArkUI_NavDestination_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'NavDestination',
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
        id: 'NavDestination',
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
    it('ArkUI_NavDestination_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_NavDestination_Comp_0006', 0, async (done: Function) => {
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
        id: 'NavDestination',
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
        id: 'NavDestination',
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
    it('ArkUI_NavDestination_Comp_0007', 0, async (done: Function) => {
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
        id: 'NavDestination',
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
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })

    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })

      done();
    })

    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })

    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_NavDestination_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })

    /**
     * 测试开启position
     */
    it('ArkUI_NavDestination_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0012', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })

    /**
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0013', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })

    /**
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0014', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })

    /**
     * 测试组件position.right且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0015', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })

    /**
     * 测试关闭position
     */
    it('ArkUI_NavDestination_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试开启markAnchor
     */
    it('ArkUI_NavDestination_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0018', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0019', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试关闭markAnchor
     */
    it('ArkUI_NavDestination_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试开启offset
     */
    it('ArkUI_NavDestination_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0022', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试组件offset.y且获取属性正确
     */
    it('ArkUI_NavDestination_Comp_0023', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试关闭offset
     */
    it('ArkUI_NavDestination_Comp_0024', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件borderStyle
     */
    it('ArkUI_NavDestination_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_NavDestination_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_NavDestination_Comp_0027', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Solid'
      })
      done();
    })

    /**
     * 测试组件borderWidth
     */
    it('ArkUI_NavDestination_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'NavDestination',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
  })
}