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
  Search,
  ToggleClick
} from '../../utils';

const TAG = 'ImageBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function ImageBootcampTest() {
  describe('ImageBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(6000);
        console.info(TAG + 'ImageBootcamp001' + ' begin');


        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(3000);

        let atomDisplays: Component = await driver.findComponent(ON.text('图片与视频'));
        await atomDisplays.click();
        await driver.delayMs(1000);


        let scrollSearch: Component = await driver.findComponent(ON.text('图片/Image'))
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
     * 测试组件image
     */
    it('ArkUI_Image_0001', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'image')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Image_0002', 0, async (done: Function) => {
      await Search('参数列表', 'image')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Image_0003', 0, async (done: Function) => {
      await Search('参数列表', 'image')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_Image_0004', 0, async (done: Function) => {
      await Search('参数列表', 'image')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Image_0005', 0, async (done: Function) => {
      await Search('参数列表', 'image')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'image',
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })

    it('ArkUI_Image_0006', 0, async (done: Function) => {
      await Search('参数列表', 'image')
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
     * 测试组件imageBorderRadius(vp)
     */
    it('ArkUI_Image_0007', 0, async (done: Function) => {
      //无法取到子组件状态
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'imageBorderRadius(vp)')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'imageBorderRadius(vp)',
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'imageBorderRadius(vp)',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件objectFit且获取属性正确
     */
    it('ArkUI_Image_0008', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.Contain'
      })

      done();
    })

    it('ArkUI_Image_0009', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.Cover'
      })

      done();
    })

    it('ArkUI_Image_0011', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.Auto'
      })

      done();
    })

    it('ArkUI_Image_0012', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.Fill'
      })

      done();
    })

    it('ArkUI_Image_0013', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.ScaleDown'
      })

      done();
    })

    it('ArkUI_Image_0014', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.None'
      })

      done();
    })

    it('ArkUI_Image_0015', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.TOP_START'
      })

      done();
    })

    it('ArkUI_Image_0016', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.TOP'
      })

      done();
    })

    it('ArkUI_Image_0017', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.TOP_END'
      })

      done();
    })

    it('ArkUI_Image_0018', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.START'
      })

      done();
    })

    it('ArkUI_Image_0019', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.CENTER'
      })

      done();
    })

    it('ArkUI_Image_0020', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.END'
      })

      done();
    })

    it('ArkUI_Image_0021', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.BOTTOM_START'
      })

      done();
    })

    it('ArkUI_Image_0022', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 13,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.BOTTOM'
      })

      done();
    })

    it('ArkUI_Image_0023', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectFit')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickObj: 'objectFit',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectFit', JsonType.value),
        ],
        assertEqual: 'ImageFit.BOTTOM_END'
      })

      done();
    })
    /**
     * 测试组件objectRepeat且获取属性正确
     */
    it('ArkUI_Image_0024', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectRepeat')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'objectRepeat',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectRepeat', JsonType.value),
        ],
        assertEqual: 'ImageRepeat.NoRepeat'
      })

      done();
    })

    it('ArkUI_Image_0025', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectRepeat')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'objectRepeat',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectRepeat', JsonType.value),
        ],
        assertEqual: 'ImageRepeat.X'
      })

      done();
    })

    it('ArkUI_Image_0026', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectRepeat')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'objectRepeat',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectRepeat', JsonType.value),
        ],
        assertEqual: 'ImageRepeat.Y'
      })

      done();
    })

    it('ArkUI_Image_0027', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'objectRepeat')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'objectRepeat',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('objectRepeat', JsonType.value),
        ],
        assertEqual: 'ImageRepeat.XY'
      })

      done();
    })
    /**
     * 测试组件interpolation且获取属性正确
     */
    it('ArkUI_Image_0028', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'interpolation')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'interpolation',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('interpolation', JsonType.value),
        ],
        assertEqual: 'ImageInterpolation.None'
      })

      done();
    })

    it('ArkUI_Image_0029', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'interpolation')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'interpolation',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('interpolation', JsonType.value),
        ],
        assertEqual: 'ImageInterpolation.Low'
      })

      done();
    })

    it('ArkUI_Image_0030', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'interpolation')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'interpolation',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('interpolation', JsonType.value),
        ],
        assertEqual: 'ImageInterpolation.Medium'
      })

      done();
    })

    it('ArkUI_Image_0031', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'interpolation')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'interpolation',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('interpolation', JsonType.value),
        ],
        assertEqual: 'ImageInterpolation.High'
      })

      done();
    })
    /**
     * 测试组件renderMode且获取属性正确
     */
    it('ArkUI_Image_0032', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'renderMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'renderMode',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderMode', JsonType.value),
        ],
        assertEqual: 'ImageRenderMode.Original'
      })

      done();
    })

    it('ArkUI_Image_0033', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'renderMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'renderMode',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderMode', JsonType.value),
        ],
        assertEqual: 'ImageRenderMode.Template'
      })

      done();
    })
    /**
     * 测试组件imageSourceSize.width
     */
    it('ArkUI_Image_0034', 0, async (done: Function) => {
      //无法取到子组件状态
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'imageSourceSize.width')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'imageSourceSize.width',
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'imageSourceSize.width',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件imageSourceSize.height
     */
    it('ArkUI_Image_0035', 0, async (done: Function) => {
      //无法取到子组件状态
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'imageSourceSize.height')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'imageSourceSize.height',
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'imageSourceSize.height',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件matchTextDirection且获取属性正确
     */
    it('ArkUI_Image_0036', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'matchTextDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'matchTextDirection',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('matchTextDirection', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Image_0037', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'matchTextDirection')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'matchTextDirection',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('matchTextDirection', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件fitOriginalSize且获取属性正确
     */
    it('ArkUI_Image_0038', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fitOriginalSize')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fitOriginalSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fitOriginalSize', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Image_0039', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fitOriginalSize')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fitOriginalSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fitOriginalSize', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件fillColor且获取属性正确
     */
    it('ArkUI_Image_0040', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fillColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fillColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Image_0041', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fillColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fillColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Image_0042', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fillColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fillColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Image_0043', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fillColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fillColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Image_0044', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fillColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fillColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Image_0045', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'fillColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fillColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fillColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件autoResize且获取属性正确
     */
    it('ArkUI_Image_0046', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'autoResize')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'autoResize',
          toggleClickType: ToggleClick.Open
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoResize', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Image_0047', 0, async (done: Function) => {
      await searchParentBlock('image', true, '参数列表')
      await Search('参数列表', 'autoResize')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'autoResize',
          toggleClickType: ToggleClick.Close
        },
        id: 'Image',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoResize', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })

  })
}