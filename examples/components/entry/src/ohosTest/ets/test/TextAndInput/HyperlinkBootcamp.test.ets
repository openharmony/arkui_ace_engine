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

const TAG = 'HyperlinkBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function HyperlinkBootcampTest() {
  describe('HyperlinkBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'HyperlinkBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[5].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(4000);

        let atomDisplays: Component = await driver.findComponent(ON.text('文本与输入'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[0].getBoundsCenter()
        let width4: Point = await ListItems1[5].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('超链接/Hyperlink'))
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
     * 测试组件color
     */
    it('ArkUI_Hyperlink_0001', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Hyperlink_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Hyperlink_0003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Hyperlink_0004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Hyperlink_0005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Open
        },


      })

      done();

    })

    it('ArkUI_Hyperlink_0006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'color')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'color',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件image
     */
    it('ArkUI_Hyperlink_0007', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'image')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Hyperlink_0008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'image')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Hyperlink_0009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'image')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Hyperlink_0010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'image')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Hyperlink_0011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'image')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },


      })

      done();

    })

    it('ArkUI_Hyperlink_0012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'image')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件address
     */
    it('ArkUI_Hyperlink_0013', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'address')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'address',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Hyperlink_0014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'address')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'address',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件content
     */
    it('ArkUI_Hyperlink_0015', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'content')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'content',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Hyperlink_0016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'content')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'content',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })

  })
}