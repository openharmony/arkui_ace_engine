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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function sideBarContainerControlButtonTest() {
  /*
   * SideBarContainer组件 ControlButton属性
   * 找到id为sideBarContainerControlButton1的SideBarContainer组件
   * 找到画面文本为SideBarContainerControlButton的Button组件
   * 获取sideBarContainer1的ControlButton属性与期待值{left:150, top:150, width:150, height:150, icons:{shown:'../../../resources/base/media/icon.png', hidden:'../../../resources/base/media/icon.png', switching:'../../../resources/base/media/icon.png'}}比对
   * 点击button，变更sideBarContainer1的ControlButton属性值为{left:80, top:80, width:80, height:80, icons:{shown:$r('app.media.startIcon'), hidden:$r('app.media.startIcon'),switching:$r('app.media.startIcon')}}
   * 获取sideBarContainer1的ControlButton属性与期待值{left:80, top:80, width:80, height:80, icons:{shown:$r('app.media.startIcon'), hidden:$r('app.media.startIcon'),switching:$r('app.media.startIcon')}}比对
   */
  defineTest('sideBarContainerControlButtonTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sideBarContainerControlButtonTestDemo running')
    let driver: Tester = Tester.create()
    let sideBarContainerControlButton1: Component = await driver.findComponent(Matcher.create()
      .id('sideBarContainerControlButton1')
      .enabled(true))
    let button: Component = await driver.findComponent((Matcher.create()
      .text('SideBarContainerControlButton')
      .enabled(true)))

    let controlButton1: string = await sideBarContainerControlButton1.getInspectorInfo()
    assertEqual(JSON.parse(controlButton1).$attrs.controlButton,
      '{"left":"150.000000","top":"150.000000","width":"150.000000","height":"150.000000","icon":{"shown":"../../../resources/base/media/icon.png","hidden":"../../../resources/base/media/icon.png","switching":"../../../resources/base/media/icon.png"}}')

    await button.tap()
    let controlButton2: string = await sideBarContainerControlButton1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(controlButton2).$attrs.controlButton).left, '80.000000')
    assertEqual(JSON.parse(JSON.parse(controlButton2).$attrs.controlButton).top, '80.000000')
    assertEqual(JSON.parse(JSON.parse(controlButton2).$attrs.controlButton).width, '80.000000')
    assertEqual(JSON.parse(JSON.parse(controlButton2).$attrs.controlButton).height, '80.000000')
    assertEqual(JSON.parse(JSON.parse(controlButton2).$attrs.controlButton).icon.shown, $r('app.media.startIcon'))
    assertEqual(JSON.parse(JSON.parse(controlButton2).$attrs.controlButton).icon.hidden, $r('app.media.startIcon'))
    assertEqual(JSON.parse(JSON.parse(controlButton2).$attrs.controlButton).icon.switching, $r('app.media.startIcon'))
  }, 0)
}