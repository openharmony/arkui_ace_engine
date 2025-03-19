import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';

const TAG = 'ContainerSpanBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function ContainerSpanBootcampTest() {

  describe('ContainerSpanBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(6000);
        console.info(TAG + 'ContainerSpanBootcamp001' + ' begin');

        let ListItems1: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width3: Point = await ListItems1[0].getBoundsCenter()
        let width4: Point = await ListItems1[4].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(5000);

        let atomDisplays: Component = await driver.findComponent(ON.text('文本与输入'));

        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[5].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('ContainerSpan'))
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
     * 测试组件textBackgroundStyle.color
     */
    it('ArkUI_Swiper_0001', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'textBackgroundStyle.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.color',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Swiper_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'textBackgroundStyle.color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.color',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Swiper_0003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'textBackgroundStyle.color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.color',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_Swiper_0004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'textBackgroundStyle.color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.color',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Swiper_0005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'textBackgroundStyle.color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.color',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Swiper_0006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'textBackgroundStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.color',
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件textBackgroundStyle.radius
     */
    it('ArkUI_Swiper_0007', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'textBackgroundStyle.radius')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.radius',
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'textBackgroundStyle.radius',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
  })
}