import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  ToggleClick
} from '../../utils';

const TAG = 'ImageAnimatorBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();
export default function ImageAnimatorBootcampTest() {
  describe('ImageAnimatorBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(6000);
        console.info(TAG + 'ImageAnimatorBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(3000);

        let atomDisplays: Component = await driver.findComponent(ON.text('图片与视频'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('帧动画/ImageAnimator'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })
    /**
     * 测试组件state且获取属性正确
     */
    it('ArkUI_ImageAnimator_0001', 0, async (done: Function) => {
      await Search('参数列表', 'state')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'state',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('state', JsonType.value),
        ],
        assertEqual: 'AnimationStatus.Initial'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0002', 0, async (done: Function) => {
      await Search('参数列表', 'state')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'state',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('state', JsonType.value),
        ],
        assertEqual:'AnimationStatus.Running'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0003', 0, async (done: Function) => {
      await Search('参数列表', 'state')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'state',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('state', JsonType.value),
        ],
        assertEqual:'AnimationStatus.Paused'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0004', 0, async (done: Function) => {
      await Search('参数列表', 'state')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'state',
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('state', JsonType.value),
        ],
        assertEqual:'AnimationStatus.Stopped'
      })

      done();
    })
    /**
     * 测试组件duration且获取属性正确
     */
    it('ArkUI_ImageAnimator_0005', 0, async (done: Function) => {
      await Search('参数列表', 'duration')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'duration',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('duration', JsonType.value),
        ],
        assertEqual: '2000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'duration',
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('duration', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();
    })
    /**
     * 测试组件reverse且获取属性正确
     */
    it('ArkUI_ImageAnimator_0006', 0, async (done: Function) => {
      await Search('参数列表', 'reverse')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'reverse',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('reverse', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0007', 0, async (done: Function) => {
      await Search('参数列表', 'reverse')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'reverse',
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('reverse', JsonType.value),
        ],
        assertEqual:'false'
      })

      done();
    })
    /**
     * 测试组件fixedSize且获取属性正确
     */
    it('ArkUI_ImageAnimator_0008', 0, async (done: Function) => {
      await Search('参数列表', 'fixedSize')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fixedSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fixedSize', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0009', 0, async (done: Function) => {
      await Search('参数列表', 'fixedSize')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fixedSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fixedSize', JsonType.value),
        ],
        assertEqual:'false'
      })

      done();
    })
    /**
     * 测试组件fillMode且获取属性正确
     */
    it('ArkUI_ImageAnimator_0010', 0, async (done: Function) => {
      await Search('参数列表', 'fillMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fillMode',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillMode', JsonType.value),
        ],
        assertEqual: 'FillMode.None'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0011', 0, async (done: Function) => {
      await Search('参数列表', 'fillMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fillMode',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillMode', JsonType.value),
        ],
        assertEqual:'FillMode.Forwards'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0012', 0, async (done: Function) => {
      await Search('参数列表', 'fillMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fillMode',
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillMode', JsonType.value),
        ],
        assertEqual:'FillMode.Backwards'
      })

      done();
    })

    it('ArkUI_ImageAnimator_0013', 0, async (done: Function) => {
      await Search('参数列表', 'fillMode')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fillMode',
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillMode', JsonType.value),
        ],
        assertEqual:'FillMode.Both'
      })

      done();
    })
    /**
     * 测试组件iterations
     */
    it('ArkUI_ImageAnimator_0014', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'iterations')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'iterations',
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'iterations',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
  })
}