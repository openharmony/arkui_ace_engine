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

import { assertEqual, } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function renderFitTest_three() {
  /*
   * polygon组件 renderFit属性
   * 找到画面id为polygonRenderFit1，polygonRenderFit2的polygon组件
   * 找到画面文本为PolygonRenderFit1、PolygonRenderFit2的Button组件
   * 获取polygonRenderFit1的renderFit属性与期待值RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT比对
   * 获取polygonRenderFit2的renderFit属性与期待值RenderFit.RESIZE_COVER比对
   * 点击button1，变更polygonRenderFit2的renderFit属性值为RenderFit.RESIZE_COVER_TOP_LEFT
   * 获取polygonRenderFit2的renderFit属性与期待值RenderFit.RESIZE_COVER_TOP_LEFT比对
   * 点击button2，变更polygonRenderFit2的renderFit属性值为RenderFit.RESIZE_COVER_BOTTOM_RIGHT
   * 获取polygonRenderFit2的renderFit属性与期待值RenderFit.RESIZE_COVER_BOTTOM_RIGHT比对
   */
  defineTest('renderFitTest_threeDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("renderFitTest_threeDemo running")
    let driver: Tester = Tester.create()
    let polygonRenderFit1: Component =
      await driver.findComponent(Matcher.create().id('polygonRenderFit1').enabled(true))
    let polygonRenderFit2: Component =
      await driver.findComponent(Matcher.create().id('polygonRenderFit2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonPolygonRenderFit1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonPolygonRenderFit2').enabled(true))
    let renderFit1: string = await polygonRenderFit1.getInspectorInfo()
    assertEqual(JSON.parse(renderFit1).$attrs.renderFit, 'RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT')
    let renderFit2: string = await polygonRenderFit2.getInspectorInfo()
    assertEqual(JSON.parse(renderFit2).$attrs.renderFit, 'RenderFit.RESIZE_COVER')
    await button1.tap()
    let renderFit5: string = await polygonRenderFit2.getInspectorInfo()
    assertEqual(JSON.parse(renderFit5).$attrs.renderFit, 'RenderFit.RESIZE_COVER_TOP_LEFT')
    await button2.tap()
    let renderFit6: string = await polygonRenderFit2.getInspectorInfo()
    assertEqual(JSON.parse(renderFit6).$attrs.renderFit, 'RenderFit.RESIZE_COVER_BOTTOM_RIGHT')
  }, 0)
}