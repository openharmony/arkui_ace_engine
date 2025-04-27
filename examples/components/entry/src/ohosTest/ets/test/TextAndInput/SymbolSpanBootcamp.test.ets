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
  titleSearch,
  ToggleClick
} from '../../utils';

const TAG = 'SymbolSpanBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function SymbolSpanBootcampTest() {
  describe('SymbolSpanBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(6000);
        console.info(TAG + 'SymbolSpanBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[4].getBoundsCenter()
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

        let scrollSearch: Component = await driver.findComponent(ON.text('SymbolSpan'))
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
     * 测试组件fontColor
     */
    it('ArkUI_SymbolSpan_0001', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'fontColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Open
        },

        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_SymbolSpan_0002', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Open
        },

        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_SymbolSpan_0003', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Open
        },

        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0004', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Open
        },

        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_SymbolSpan_0005', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Open
        },

        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_SymbolSpan_0006', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Close
        },

        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件fontSize且获取属性正确
     */
    it('ArkUI_SymbolSpan_0007', 0, async (done: Function) => {
      await Search('参数列表', 'fontSize')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'fontSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '200.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'fontSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '0.00fp'
      })

      done();
    })
    /**
     * 测试组件fontWeight且获取属性正确
     */
    it('ArkUI_SymbolSpan_0008', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '100'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0009', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '200'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0010', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '300'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0011', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '400'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0012', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '500'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0013', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '600'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0014', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '700'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0015', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '800'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0016', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: '900'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0017', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Lighter'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0018', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Normal'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0019', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0020', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0021', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 13,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bold'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0022', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bolder'
      })

      done();
    })
    /**
     * 测试组件renderingStrategy且获取属性正确
     */
    it('ArkUI_SymbolSpan_0023', 0, async (done: Function) => {
      await Search('参数列表', 'renderingStrategy')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'renderingStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderingStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolRenderingStrategy.SINGLE'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0024', 0, async (done: Function) => {
      await Search('参数列表', 'renderingStrategy')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'renderingStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderingStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolRenderingStrategy.MULTIPLE_COLOR'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0025', 0, async (done: Function) => {
      await Search('参数列表', 'renderingStrategy')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'renderingStrategy',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderingStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolRenderingStrategy.MULTIPLE_OPACITY'
      })

      done();
    })
    /**
     * 测试组件effectStrategy且获取属性正确
     */
    it('ArkUI_SymbolSpan_0026', 0, async (done: Function) => {
      await Search('参数列表', 'effectStrategy')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'effectStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolEffectStrategy.NONE'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0027', 0, async (done: Function) => {
      await Search('参数列表', 'effectStrategy')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'effectStrategy',
          toggleClickType: ToggleClick.Open
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolEffectStrategy.SCALE'
      })

      done();
    })

    it('ArkUI_SymbolSpan_0028', 0, async (done: Function) => {
      await Search('参数列表', 'effectStrategy')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'effectStrategy',
          toggleClickType: ToggleClick.Close
        },
        id: 'SymbolSpan',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectStrategy', JsonType.value),
        ],
        assertEqual: 'SymbolEffectStrategy.HIERARCHICAL'
      })

      done();
    })
    /**
     * 测试组件attributeModifier.normal
     */
    it('ArkUI_SymbolSpan_0029', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'attributeModifier.normal')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'attributeModifier.normal',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })
    it('ArkUI_SymbolSpan_0030', 0, async (done: Function) => {

      await Search('参数列表', 'attributeModifier.normal')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'attributeModifier.normal',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件attributeModifier.pressed
     */
    it('ArkUI_SymbolSpan_0031', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'attributeModifier.pressed')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'attributeModifier.pressed',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SymbolSpan_0032', 0, async (done: Function) => {
      await Search('参数列表', 'attributeModifier.pressed')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'attributeModifier.pressed',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件attributeModifier.focused
     */
    it('ArkUI_SymbolSpan_0033', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'attributeModifier.focused')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'attributeModifier.focused',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SymbolSpan_0034', 0, async (done: Function) => {
      await Search('参数列表', 'attributeModifier.focused')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'attributeModifier.focused',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })
    /**
     * 测试组件attributeModifier.selected
     */
    it('ArkUI_SymbolSpan_0035', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'attributeModifier.selected')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'attributeModifier.disabled',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SymbolSpan_0036', 0, async (done: Function) => {
      await Search('参数列表', 'attributeModifier.disabled')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'attributeModifier.disabled',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件attributeModifier.selected
     */
    it('ArkUI_SymbolSpan_0037', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'attributeModifier.selected')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'attributeModifier.selected',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SymbolSpan_0038', 0, async (done: Function) => {
      await Search('参数列表', 'attributeModifier.selected')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'attributeModifier.selected',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })

  })
}