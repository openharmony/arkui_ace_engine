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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect, TestType } from '@ohos/hypium';
import { abilityDelegatorRegistry, Driver, ON, MouseButton, UiDirection } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

export default function DragDropTest() {
  describe('DragDropTest', () => {

    beforeAll(async () => {
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      let driver = Driver.create();
      await driver.delayMs(1000);
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      console.info('get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    })

    beforeEach(async () => {
    })

    afterEach(() => {
      hilog.info(0x0000, 'DragDropTest', 'DragDrop interface test case completed');
    })

    afterAll(() => {
      hilog.info(0x0000, 'DragDropTest', 'All dragDrop interface tests completed');
    })

    /**
     * @tc.number DragDropTest_001
     * @tc.name testDefaultDrag
     * @tc.desc 测试默认拖拽接口 - 测试通用拖拽能力
     */
    it('testDefaultDrag', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'DragDropTest', 'testDefaultDrag begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(1000);
        // 获取拖拽及落入相关组件
        let dragMe = await driver.findComponent(ON.id('dragText_1'));
        const unDropArea = await driver.findComponent(ON.id('unDropArea_1'));
        const dropArea1 = await driver.findComponent(ON.id('dropArea1_1'));
        const unDropArea1 = await driver.findComponent(ON.id('unDropArea1_1'));
        const dropArea2 = await driver.findComponent(ON.id('dropArea2_1'));
        const unDropArea2 = await driver.findComponent(ON.id('unDropArea2_1'));
        const reset = await driver.findComponent(ON.id('reset'));
        // 测试拖拽至禁入区域
        await dragMe.dragTo(unDropArea);
        // 测试拖拽至可落入区域1
        await dragMe.dragTo(dropArea1);
        await reset.click();
        // 测试拖拽至不可落入区域1
        await dragMe.dragTo(unDropArea1);
        // 测试拖拽至可落入区域2
        await dragMe.dragTo(dropArea2);
        await driver.delayMs(300);
      } catch (error) {
        hilog.error(0x0000, 'DragDropTest', 'testDefaultDrag failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'DragDropTest', 'testDefaultDrag end');
    })

    /**
     * @tc.number DragDropTest_002
     * @tc.name testSpringLoadingDrag
     * @tc.desc 测试异步加载拖拽接口 - 测试拖拽中的异步加载能力
     */
    it('testSpringLoadingDrag', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'DragDropTest', 'testSpringLoadingDrag begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(2000);
        // 滚动至相应模块
        const scroll = await driver.findComponent(ON.id('scroll'));
        expect(scroll == null).assertFalse();
        await scroll.scrollToBottom(6000);
        // 发起拖拽
        const dragImage = await driver.findComponent(ON.id('dragImage'));
        const dropImage = await driver.findComponent(ON.id('dropImage'));
        await dragImage.dragTo(dropImage);
        await driver.delayMs(1000);
      } catch (error) {
        hilog.error(0x0000, 'DragDropTest', 'testSpringLoadingDrag failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'DragDropTest', 'testSpringLoadingDrag end');
    })

    /**
     * @tc.number DragDropTest_003
     * @tc.name testDragAction
     * @tc.desc 测试主动发起拖拽接口 - 测试主动发起拖拽能力
     */
    it('testDragAction', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'DragDropTest', 'testDragAction begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(2000);
        // 滚动至相应模块
        const scroll = await driver.findComponent(ON.id('scroll'));
        expect(scroll == null).assertFalse();
        await scroll.scrollToBottom(6000);
        // 发起拖拽
        const dragButton = await driver.findComponent(ON.id('dragBt3'));
        const dropButton = await driver.findComponent(ON.id('dropBt3'));
        await dragButton.dragTo(dropButton);
        await driver.delayMs(1000);
      } catch (error) {
        hilog.error(0x0000, 'DragDropTest', 'testDragAction failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'DragDropTest', 'testDragAction end');
    })

    /**
     * @tc.number DragDropTest_004
     * @tc.name testSpringLoadingDragAction
     * @tc.desc 测试主动发起拖拽的异步加载接口 - 测试主动发起拖拽中异步加载数据的能力
     */
    it('testSpringLoadingDragAction', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'DragDropTest', 'testSpringLoadingDragAction begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(2000);
        // 滚动至相应模块
        const scroll = await driver.findComponent(ON.id('scroll'));
        expect(scroll == null).assertFalse();
        await scroll.scrollToBottom(6000);
        // 发起拖拽
        const dragButton = await driver.findComponent(ON.id('dragBt4'));
        const dropButton = await driver.findComponent(ON.id('dropBt4'));
        await dragButton.dragTo(dropButton);
        await driver.delayMs(5000);
      } catch (error) {
        hilog.error(0x0000, 'DragDropTest', 'testSpringLoadingDragAction failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'DragDropTest', 'testSpringLoadingDragAction end');
    })

  })
}
