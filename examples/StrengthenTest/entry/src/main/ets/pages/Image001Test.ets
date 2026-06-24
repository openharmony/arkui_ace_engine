import {
  memo,
  __memo_context_type,
__memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  $r,
  Entry,
  Text,
  TextAttribute,
  ResourceColor,
  Color,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  Font,
  Progress,
  ProgressAttribute,
  ProgressType,
  ProgressOptions,
  ProgressStatus,
  RingStyleOptions,
  LinearStyleOptions,
  ProgressStyleOptions,
  CapsuleStyleOptions,
  ScaleRingStyleOptions,
  ScanEffectOptions,
  QRCode,
  QRCodeAttribute,
  LoadingProgress,
  LoadingProgressAttribute,
  PatternLock,
  PatternLockAttribute,
  Badge,
  BadgeAttribute,
  BadgeStyle,
  BadgeParam,
  BadgeParamWithNumber,
  BadgeParamWithString,
  DataPanel,
  DataPanelAttribute,
  DataPanelType,
  DataPanelOptions,
  Gauge,
  GaugeAttribute,
  GaugeOptions,
  ColorStop,
  LinearGradient,
  TextTimer,
  TextTimerController,
  TextTimerOptions,
  TextTimerAttribute,
  TextClock,
  TextClockAttribute,
  Image,
  ImageAttribute,
  Flex,
  FlexAttribute,
  Row,
  RowAttribute,
  Alignment,
  PixelMap,
  ResizableOptions,
  EdgeWidths,
  NavDestination, 
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'

import hilog from '@ohos.hilog'
import image from '@ohos.multimedia.image'

@Component
export struct Image001Test {
  @State imageCounter: number = 0
  @State imageStatus: string = 'ready'
  @State imageWidth: number = 100
  @State imageHeight: number = 100

  async loadMoreImageTest(): void {
    let testCounter = 0
    let testString = 'Image Test String'
    let testArray: string[] = []

    for (let i = 0; i < 100; i++) {
      testArray.push(`ImageItem_${i}`)
    }

    let testMap: Map<string, number> = new Map()
    for (let i = 0; i < 50; i++) {
      testMap.set(`img_key_${i}`, i)
    }

    let testSet: Set<number> = new Set()
    for (let i = 0; i < 75; i++) {
      testSet.add(i)
    }

    let imageConfig = {
      src: 'app.media.startIcon',
      width: 200,
      height: 200,
      objectFit: 'Cover',
      interpolation: 'High',
      renderMode: 'Original',
      alt: 'app.media.placeholder',
      syncLoad: false,
      autoResize: true,
      fitOriginalSize: false,
      fillColor: '#FF0000',
      nested: {
        borderWidth: 1,
        borderColor: '#0000FF',
        borderRadius: 10,
        opacity: 0.8,
        shadow: {
          radius: 5,
          color: '#808080',
          offsetX: 2,
          offsetY: 2
        },
        prop3: {
          deepProp: 'deepImageValue'
        }
      }
    }

    let testArrayBuffer = new ArrayBuffer(1024)
    let testDataView = new DataView(testArrayBuffer)
    for (let i = 0; i < 1024; i++) {
      testDataView.setInt8(i, i % 256)
    }

    let testIntArray = new Int32Array(256)
    for (let i = 0; i < 256; i++) {
      testIntArray[i] = i * 1000
    }

    let testFloatArray = new Float64Array(128)
    for (let i = 0; i < 128; i++) {
      testFloatArray[i] = i * 1.5
    }

    let objectFitValues: string[] = ['Contain', 'Cover', 'Auto', 'Fill', 'ScaleDown', 'None']
    let interpolationValues: string[] = ['None', 'Low', 'Medium', 'High']
    let renderModeValues: string[] = ['Original', 'Template']
    let imageFormatValues: string[] = ['PNG', 'JPEG', 'GIF', 'BMP', 'WEBP', 'SVG', 'ICO', 'TIFF']

    let calculateImageDimensions = (originalWidth: number, originalHeight: number, containerWidth: number, containerHeight: number, fitMode: string): { width: number, height: number } => {
      let aspectRatio = originalWidth / originalHeight
      let containerAspect = containerWidth / containerHeight
      switch (fitMode) {
        case 'Contain':
          if (aspectRatio > containerAspect) {
            return { width: containerWidth, height: containerWidth / aspectRatio }
          } else {
            return { width: containerHeight * aspectRatio, height: containerHeight }
          }
        case 'Cover':
          if (aspectRatio > containerAspect) {
            return { width: containerHeight * aspectRatio, height: containerHeight }
          } else {
            return { width: containerWidth, height: containerWidth / aspectRatio }
          }
        case 'Fill':
          return { width: containerWidth, height: containerHeight }
        case 'ScaleDown':
          let containResult = aspectRatio > containerAspect
            ? { width: containerWidth, height: containerWidth / aspectRatio }
            : { width: containerHeight * aspectRatio, height: containerHeight }
          if (originalWidth <= containResult.width && originalHeight <= containResult.height) {
            return { width: originalWidth, height: originalHeight }
          }
          return containResult
        case 'None':
          return { width: originalWidth, height: originalHeight }
        default:
          return { width: containerWidth, height: containerHeight }
      }
    }

    let testObjectFitCalculations = objectFitValues.map((fit) => {
      return calculateImageDimensions(800, 600, 400, 300, fit)
    })

    for (let i = 0; i < testObjectFitCalculations.length; i++) {
      hilog.info(0x0000, 'testTag', `ObjectFit ${objectFitValues[i]}: w=${testObjectFitCalculations[i].width}, h=${testObjectFitCalculations[i].height}`)
    }

    let imageFilterMatrix = [
      1.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ]

    let grayscaleMatrix = [
      0.299, 0.587, 0.114, 0.0, 0.0,
      0.299, 0.587, 0.114, 0.0, 0.0,
      0.299, 0.587, 0.114, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ]

    let sepiaMatrix = [
      0.393, 0.769, 0.189, 0.0, 0.0,
      0.349, 0.686, 0.168, 0.0, 0.0,
      0.272, 0.534, 0.131, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ]

    let invertMatrix = [
      -1.0, 0.0, 0.0, 0.0, 1.0,
      0.0, -1.0, 0.0, 0.0, 1.0,
      0.0, 0.0, -1.0, 0.0, 1.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ]

    let brightnessMatrix = [
      1.2, 0.0, 0.0, 0.0, 0.0,
      0.0, 1.2, 0.0, 0.0, 0.0,
      0.0, 0.0, 1.2, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ]

    let allFilterMatrices: Map<string, number[]> = new Map()
    allFilterMatrices.set('identity', imageFilterMatrix)
    allFilterMatrices.set('grayscale', grayscaleMatrix)
    allFilterMatrices.set('sepia', sepiaMatrix)
    allFilterMatrices.set('invert', invertMatrix)
    allFilterMatrices.set('brightness', brightnessMatrix)

    for (let [name, matrix] of allFilterMatrices) {
      hilog.info(0x0000, 'testTag', `Image filter ${name}: ${matrix.slice(0, 5).join(',')}`)
    }

    let applyColorFilter = (r: number, g: number, b: number, a: number, matrix: number[]): { r: number, g: number, b: number, a: number } => {
      let newR = matrix[0] * r + matrix[1] * g + matrix[2] * b + matrix[3] * a + matrix[4]
      let newG = matrix[5] * r + matrix[6] * g + matrix[7] * b + matrix[8] * a + matrix[9]
      let newB = matrix[10] * r + matrix[11] * g + matrix[12] * b + matrix[13] * a + matrix[14]
      let newA = matrix[15] * r + matrix[16] * g + matrix[17] * b + matrix[18] * a + matrix[19]
      return {
        r: Math.min(255, Math.max(0, newR)),
        g: Math.min(255, Math.max(0, newG)),
        b: Math.min(255, Math.max(0, newB)),
        a: Math.min(255, Math.max(0, newA))
      }
    }

    let testPixelValues: { r: number, g: number, b: number, a: number }[] = [
      { r: 255, g: 0, b: 0, a: 255 },
      { r: 0, g: 255, b: 0, a: 255 },
      { r: 0, g: 0, b: 255, a: 255 },
      { r: 128, g: 128, b: 128, a: 255 },
      { r: 64, g: 192, b: 32, a: 128 }
    ]

    for (let pixel of testPixelValues) {
      let grayscaleResult = applyColorFilter(pixel.r, pixel.g, pixel.b, pixel.a, grayscaleMatrix)
      let sepiaResult = applyColorFilter(pixel.r, pixel.g, pixel.b, pixel.a, sepiaMatrix)
      let invertResult = applyColorFilter(pixel.r, pixel.g, pixel.b, pixel.a, invertMatrix)
      let brightnessResult = applyColorFilter(pixel.r, pixel.g, pixel.b, pixel.a, brightnessMatrix)
      hilog.info(0x0000, 'testTag', `Pixel(${pixel.r},${pixel.g},${pixel.b},${pixel.a}) -> gray(${grayscaleResult.r},${grayscaleResult.g},${grayscaleResult.b})`)
      hilog.info(0x0000, 'testTag', `Pixel(${pixel.r},${pixel.g},${pixel.b},${pixel.a}) -> sepia(${sepiaResult.r},${sepiaResult.g},${sepiaResult.b})`)
      hilog.info(0x0000, 'testTag', `Pixel(${pixel.r},${pixel.g},${pixel.b},${pixel.a}) -> invert(${invertResult.r},${invertResult.g},${invertResult.b})`)
      hilog.info(0x0000, 'testTag', `Pixel(${pixel.r},${pixel.g},${pixel.b},${pixel.a}) -> bright(${brightnessResult.r},${brightnessResult.g},${brightnessResult.b})`)
    }

    let testFunction = (param: number): string => {
      return `ImageResult: ${param * 2}`
    }

    let testAsyncFunction = async (delay: number): Promise<string> => {
      return new Promise((resolve) => {
        setTimeout(() => {
          resolve(`ImageDelayed: ${delay}ms`)
        }, delay)
      })
    }

    class ImageInfo {
      private src: string
      private width: number
      private height: number
      private format: string
      constructor(src: string, width: number, height: number, format: string) {
        this.src = src
        this.width = width
        this.height = height
        this.format = format
      }
      getSrc(): string { return this.src }
      getWidth(): number { return this.width }
      getHeight(): number { return this.height }
      getFormat(): string { return this.format }
      getAspectRatio(): number { return this.width / this.height }
      setWidth(newWidth: number): void { this.width = newWidth }
      setHeight(newHeight: number): void { this.height = newHeight }
      incrementWidth(): number { return ++this.width }
      toString(): string { return `${this.src} ${this.width}x${this.height} ${this.format}` }
    }

    let testImageInfo = new ImageInfo('icon.png', 48, 48, 'PNG')

    interface ImageLoadResult {
      id: number
      src: string
      width: number
      height: number
      componentWidth: number
      componentHeight: number
      loaded: boolean
    }

    let testLoadResult: ImageLoadResult = {
      id: 1,
      src: 'app.media.startIcon',
      width: 200,
      height: 200,
      componentWidth: 100,
      componentHeight: 100,
      loaded: true
    }

    enum ImageInterpolation {
      None = 'none',
      Low = 'low',
      Medium = 'medium',
      High = 'high'
    }

    enum ImageRenderMode {
      Original = 'original',
      Template = 'template'
    }

    enum ImageObjectFit {
      Contain = 'contain',
      Cover = 'cover',
      Auto = 'auto',
      Fill = 'fill',
      ScaleDown = 'scaleDown',
      None = 'none'
    }

    let testInterpolationValue = ImageInterpolation.High
    let testRenderModeValue = ImageRenderMode.Original
    let testObjectFitValue = ImageObjectFit.Cover

    type ImageSource = string | Resource | PixelMap
    type ImageSizeOptions = { width: number, height: number }
    type ImagePositionOptions = { x: number, y: number }
    type ImageResizableOptions = { start: number, end: number }

    let testImageSize: ImageSizeOptions = { width: 100, height: 100 }
    let testImagePosition: ImagePositionOptions = { x: 50, y: 50 }
    let testResizable: ImageResizableOptions = { start: 0, end: 100 }

    let testImageSources: ImageSource[] = [
      'https://example.com/image1.png',
      'app.media.startIcon',
      'app.media.background',
      'common/icon.png'
    ]

    let testTuple: [string, number, boolean] = ['image_tuple', 456, false]

    let testUnionType: string | number | boolean = 'image_union_value'

    let testLiteralType: 'contain' | 'cover' | 'fill' = 'cover'

    let testNullableString: string | null = null
    let testOptionalNumber?: number = undefined

    let testRestFunction = (...args: number[]): number => {
      return args.reduce((sum, current) => sum + current, 0)
    }

    let testDefaultValue = (param: string = 'default_image'): string => {
      return param
    }

    let testDestructuring = ({ src, width }: { src: string, width: number }): string => {
      return `${src}_${width}`
    }

    let testSpreadArray = [1, 2, 3]
    let testSpreadObject = { src: 'test.png', width: 100 }
    let testCombinedSpread = [...testSpreadArray, 4, 5, 6]
    let testCombinedObjectSpread = { ...testSpreadObject, height: 200 }

    let testTemplateString = `ImageTemplate: ${testString} - ${testCounter}`

    let testRegex = /image_pattern_\d+/gi
    let testRegexMatch = testString.match(testRegex)

    let testDate = new Date()
    let testDateString = testDate.toISOString()

    let testJSONString = JSON.stringify(imageConfig)
    let testParsedJSON = JSON.parse(testJSONString)

    let testMathOperations = {
      random: Math.random(),
      floor: Math.floor(3.7),
      ceil: Math.ceil(3.2),
      round: Math.round(3.5),
      abs: Math.abs(-42),
      max: Math.max(1, 2, 3, 4, 5),
      min: Math.min(1, 2, 3, 4, 5),
      pow: Math.pow(2, 8),
      sqrt: Math.sqrt(144),
      sin: Math.sin(Math.PI / 4),
      cos: Math.cos(Math.PI / 4),
      tan: Math.tan(Math.PI / 4),
      log: Math.log(Math.E),
      exp: Math.exp(1)
    }

    let testStringOperations = {
      length: testString.length,
      charAt: testString.charAt(0),
      charCodeAt: testString.charCodeAt(0),
      concat: testString.concat('_suffix'),
      indexOf: testString.indexOf('Image'),
      lastIndexOf: testString.lastIndexOf('Image'),
      slice: testString.slice(0, 4),
      substring: testString.substring(0, 4),
      toLowerCase: testString.toLowerCase(),
      toUpperCase: testString.toUpperCase(),
      trim: '  image  '.trim(),
      split: testString.split(' '),
      replace: testString.replace('Image', 'Photo'),
      includes: testString.includes('Image'),
      startsWith: testString.startsWith('Image'),
      endsWith: testString.endsWith('String'),
      repeat: 'img'.repeat(3),
      padStart: '5'.padStart(3, '0'),
      padEnd: '5'.padEnd(3, '0')
    }

    let testArrayOperations = {
      length: testArray.length,
      push: testArray.push('new_image_item'),
      pop: testArray.pop(),
      shift: testArray.shift(),
      unshift: testArray.unshift('first_image_item'),
      slice: testArray.slice(0, 5),
      splice: testArray.splice(0, 2),
      concat: testArray.concat(['new', 'images']),
      join: testArray.join(', '),
      indexOf: testArray.indexOf('ImageItem_1'),
      lastIndexOf: testArray.lastIndexOf('ImageItem_1'),
      includes: testArray.includes('ImageItem_1'),
      reverse: [...testArray].reverse(),
      sort: [...testArray].sort(),
      find: testArray.find(item => item.includes('5')),
      findIndex: testArray.findIndex(item => item.includes('5')),
      filter: testArray.filter(item => item.includes('Item')),
      map: testArray.map(item => item.toUpperCase()),
      reduce: testArray.reduce((sum, item) => sum + item.length, 0),
      some: testArray.some(item => item.length > 10),
      every: testArray.every(item => item.length > 0),
      forEach: testArray.forEach((item, index) => {
        hilog.info(0x0000, 'testTag', `ImageForEach: ${index} - ${item}`)
      })
    }

    let testMapOperations = {
      size: testMap.size,
      set: testMap.set('new_img_key', 999),
      get: testMap.get('img_key_1'),
      has: testMap.has('img_key_1'),
      delete: testMap.delete('img_key_2'),
      clear: testMap.clear(),
      keys: Array.from(testMap.keys()),
      values: Array.from(testMap.values()),
      entries: Array.from(testMap.entries()),
      forEach: testMap.forEach((value, key) => {
        hilog.info(0x0000, 'testTag', `ImageMap: ${key} - ${value}`)
      })
    }

    let testSetOperations = {
      size: testSet.size,
      add: testSet.add(100),
      has: testSet.has(1),
      delete: testSet.delete(2),
      clear: testSet.clear(),
      values: Array.from(testSet.values()),
      forEach: testSet.forEach((value) => {
        hilog.info(0x0000, 'testTag', `ImageSet: ${value}`)
      })
    }

    let testObjectOperations = {
      keys: Object.keys(imageConfig),
      values: Object.values(imageConfig),
      entries: Object.entries(imageConfig),
      assign: Object.assign({}, imageConfig, { newProp: 'newImageValue' }),
      freeze: Object.freeze({ ...imageConfig }),
      seal: Object.seal({ ...imageConfig }),
      hasOwnProperty: imageConfig.hasOwnProperty('src'),
      propertyIsEnumerable: imageConfig.propertyIsEnumerable('src')
    }

    let testErrorHandling = {
      tryCatch: (() => {
        try {
          throw new Error('Image Load Error')
        } catch (error) {
          return error.message
        }
      })(),
      tryCatchFinally: (() => {
        try {
          throw new Error('Image Decode Error with Finally')
        } catch (error) {
          return error.message
        } finally {
          hilog.info(0x0000, 'testTag', 'Image error finally block executed')
        }
      })(),
      customError: (() => {
        class ImageLoadError extends Error {
          constructor(message: string) {
            super(message)
            this.name = 'ImageLoadError'
          }
        }
        try {
          throw new ImageLoadError('Failed to load image resource')
        } catch (error) {
          return (error as ImageLoadError).message
        }
      })()
    }

    let testPromiseChains = (() => {
      return new Promise<string>((resolve) => {
        resolve('image_initial_value')
      })
      .then((value) => {
        return `${value}_processed`
      })
      .then((value) => {
        return `${value}_scaled`
      })
      .then((value) => {
        return `${value}_rendered`
      })
      .catch((error) => {
        return `error: ${error.message}`
      })
      .finally(() => {
        hilog.info(0x0000, 'testTag', 'Image promise chain completed')
      })
    })()

    let testAsyncAwait = (async () => {
      let result1 = await Promise.resolve('image_loaded')
      let result2 = await Promise.resolve('image_decoded')
      let result3 = await Promise.resolve('image_rendered')
      return `${result1}_${result2}_${result3}`
    })()

    let testPromiseAll = Promise.all([
      Promise.resolve('image_png'),
      Promise.resolve('image_jpeg'),
      Promise.resolve('image_gif')
    ])

    let testPromiseRace = Promise.race([
      new Promise<string>((resolve) => setTimeout(() => resolve('slow_image'), 100)),
      new Promise<string>((resolve) => setTimeout(() => resolve('fast_image'), 50))
    ])

    let testPromiseAllSettled = Promise.allSettled([
      Promise.resolve('resolved_image1'),
      Promise.reject('rejected_image1'),
      Promise.resolve('resolved_image2')
    ])

    let testPromiseAny = Promise.any([
      Promise.reject('rejected_image1'),
      Promise.resolve('resolved_image1'),
      Promise.reject('rejected_image2')
    ])

    let testGenerators = (() => {
      function* imageIdGenerator(): Generator<number, void, unknown> {
        yield 1
        yield 2
        yield 3
        yield 4
        yield 5
      }

      let gen = imageIdGenerator()
      let values: number[] = []
      let result = gen.next()
      while (!result.done) {
        values.push(result.value)
        result = gen.next()
      }
      return values
    })()

    let testIterators = (() => {
      let iterable = {
        [Symbol.iterator]() {
          let step = 0
          return {
            next(): IteratorResult<number> {
              step++
              if (step <= 5) {
                return { value: step, done: false }
              }
              return { value: undefined, done: true } as IteratorResult<number>
            }
          }
        }
      }

      let values: number[] = []
      for (let value of iterable) {
        values.push(value)
      }
      return values
    })()

    let testSymbolOperations = {
      symbol: Symbol('image_symbol'),
      symbolFor: Symbol.for('global_image_symbol'),
      symbolKeyFor: Symbol.keyFor(Symbol.for('global_image_symbol')),
      symbolIterator: Symbol.iterator,
      symbolToString: Symbol('img').toString(),
      symbolDescription: Symbol('image_description').description
    }

    let testProxy = (() => {
      let target = {
        src: 'image.png',
        width: 100,
        height: 100
      }

      let handler: ProxyHandler<typeof target> = {
        get(obj, prop) {
          return obj[prop as keyof typeof obj]
        },
        set(obj, prop, value) {
          obj[prop as keyof typeof obj] = value
          return true
        },
        has(obj, prop) {
          return prop in obj
        },
        deleteProperty(obj, prop) {
          delete obj[prop as keyof typeof obj]
          return true
        }
      }

      return new Proxy(target, handler)
    })()

    let testReflect = {
      get: Reflect.get({ src: 'test.png', width: 200 }, 'src'),
      set: Reflect.set({ src: 'a.png' }, 'src', 'b.png'),
      has: Reflect.has({ src: 'test.png' }, 'src'),
      deleteProperty: Reflect.deleteProperty({ src: 'a.png', width: 100 }, 'src'),
      ownKeys: Reflect.ownKeys({ src: 'a.png', width: 100 }),
      apply: Reflect.apply(Math.max, undefined, [1, 2, 3]),
      construct: Reflect.construct(Date, [2024, 0, 1]),
      getPrototypeOf: Reflect.getPrototypeOf({}),
      setPrototypeOf: Reflect.setPrototypeOf({}, Array.prototype),
      isExtensible: Reflect.isExtensible({}),
      preventExtensions: Reflect.preventExtensions({}),
      getOwnPropertyDescriptor: Reflect.getOwnPropertyDescriptor({ src: 'img.png' }, 'src'),
      defineProperty: Reflect.defineProperty({}, 'src', { value: 'new.png', writable: true })
    }

    let testWeakMap = (() => {
      let wm = new WeakMap<object, string>()
      let key1 = {}
      let key2 = {}
      wm.set(key1, 'image_value1')
      wm.set(key2, 'image_value2')
      return {
        get: wm.get(key1),
        has: wm.has(key2),
        delete: wm.delete(key1)
      }
    })()

    let testWeakSet = (() => {
      let ws = new WeakSet<object>()
      let obj1 = {}
      let obj2 = {}
      ws.add(obj1)
      ws.add(obj2)
      return {
        has1: ws.has(obj1),
        has2: ws.has(obj2),
        delete: ws.delete(obj1)
      }
    })()

    let testArrayBufferOperations = {
      isView: ArrayBuffer.isView(testDataView),
      slice: testArrayBuffer.slice(0, 512),
      byteLength: testArrayBuffer.byteLength
    }

    let testDataViewOperations = {
      getInt8: testDataView.getInt8(0),
      getUint8: testDataView.getUint8(0),
      getInt16: testDataView.getInt16(0),
      getUint16: testDataView.getUint16(0),
      getInt32: testDataView.getInt32(0),
      getUint32: testDataView.getUint32(0),
      getFloat32: testDataView.getFloat32(0),
      getFloat64: testDataView.getFloat64(0),
      setInt8: (() => { testDataView.setInt8(0, 127); return testDataView.getInt8(0) })(),
      setUint8: (() => { testDataView.setUint8(1, 255); return testDataView.getUint8(1) })(),
      setInt16: (() => { testDataView.setInt16(2, 32767); return testDataView.getInt16(2) })(),
      setUint16: (() => { testDataView.setUint16(4, 65535); return testDataView.getUint16(4) })(),
      setInt32: (() => { testDataView.setInt32(6, 2147483647); return testDataView.getInt32(6) })(),
      setUint32: (() => { testDataView.setUint32(10, 4294967295); return testDataView.getUint32(10) })(),
      setFloat32: (() => { testDataView.setFloat32(14, 3.14); return testDataView.getFloat32(14) })(),
      setFloat64: (() => { testDataView.setFloat64(18, 2.718281828); return testDataView.getFloat64(18) })()
    }

    let testTypedArrays = {
      int8Array: (() => {
        let arr = new Int8Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i
        return arr
      })(),
      uint8Array: (() => {
        let arr = new Uint8Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i
        return arr
      })(),
      int16Array: (() => {
        let arr = new Int16Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 100
        return arr
      })(),
      uint16Array: (() => {
        let arr = new Uint16Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 1000
        return arr
      })(),
      int32Array: testIntArray,
      uint32Array: (() => {
        let arr = new Uint32Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 100000
        return arr
      })(),
      float32Array: (() => {
        let arr = new Float32Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 1.1
        return arr
      })(),
      float64Array: testFloatArray,
      bigint64Array: (() => {
        let arr = new BigInt64Array(10)
        for (let i = 0; i < 10; i++) arr[i] = BigInt(i * 1000000)
        return arr
      })(),
      biguint64Array: (() => {
        let arr = new BigUint64Array(10)
        for (let i = 0; i < 10; i++) arr[i] = BigInt(i * 1000000)
        return arr
      })()
    }

    let simulatePixelData = (() => {
      let width = 10
      let height = 10
      let pixelData = new Uint8Array(width * height * 4)
      for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
          let offset = (y * width + x) * 4
          pixelData[offset] = (x * 25) % 256
          pixelData[offset + 1] = (y * 25) % 256
          pixelData[offset + 2] = ((x + y) * 12) % 256
          pixelData[offset + 3] = 255
        }
      }
      return { width, height, data: pixelData }
    })()

    hilog.info(0x0000, 'testTag', `Simulated pixel data: w=${simulatePixelData.width}, h=${simulatePixelData.height}, size=${simulatePixelData.data.length}`)

    let computeImageHistogram = (pixelData: Uint8Array, width: number, height: number): { r: number[], g: number[], b: number[] } => {
      let rHist: number[] = Array.from({ length: 256 }, () => 0)
      let gHist: number[] = Array.from({ length: 256 }, () => 0)
      let bHist: number[] = Array.from({ length: 256 }, () => 0)
      for (let i = 0; i < width * height; i++) {
        rHist[pixelData[i * 4]]++
        gHist[pixelData[i * 4 + 1]]++
        bHist[pixelData[i * 4 + 2]]++
      }
      return { r: rHist, g: gHist, b: bHist }
    }

    let histogram = computeImageHistogram(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    let histRMax = Math.max(...histogram.r)
    let histGMax = Math.max(...histogram.g)
    let histBMax = Math.max(...histogram.b)
    hilog.info(0x0000, 'testTag', `Histogram max: R=${histRMax}, G=${histGMax}, B=${histBMax}`)

    let computeImageAverageColor = (pixelData: Uint8Array, width: number, height: number): { r: number, g: number, b: number } => {
      let totalR = 0, totalG = 0, totalB = 0
      let pixelCount = width * height
      for (let i = 0; i < pixelCount; i++) {
        totalR += pixelData[i * 4]
        totalG += pixelData[i * 4 + 1]
        totalB += pixelData[i * 4 + 2]
      }
      return {
        r: totalR / pixelCount,
        g: totalG / pixelCount,
        b: totalB / pixelCount
      }
    }

    let avgColor = computeImageAverageColor(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    hilog.info(0x0000, 'testTag', `Average color: R=${avgColor.r.toFixed(2)}, G=${avgColor.g.toFixed(2)}, B=${avgColor.b.toFixed(2)}`)

    let computeImageBrightness = (pixelData: Uint8Array, width: number, height: number): number => {
      let totalBrightness = 0
      let pixelCount = width * height
      for (let i = 0; i < pixelCount; i++) {
        let r = pixelData[i * 4]
        let g = pixelData[i * 4 + 1]
        let b = pixelData[i * 4 + 2]
        totalBrightness += 0.299 * r + 0.587 * g + 0.114 * b
      }
      return totalBrightness / pixelCount
    }

    let avgBrightness = computeImageBrightness(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    hilog.info(0x0000, 'testTag', `Average brightness: ${avgBrightness.toFixed(2)}`)

    let computeImageContrast = (pixelData: Uint8Array, width: number, height: number): number => {
      let mean = computeImageBrightness(pixelData, width, height)
      let variance = 0
      let pixelCount = width * height
      for (let i = 0; i < pixelCount; i++) {
        let brightness = 0.299 * pixelData[i * 4] + 0.587 * pixelData[i * 4 + 1] + 0.114 * pixelData[i * 4 + 2]
        variance += (brightness - mean) * (brightness - mean)
      }
      return Math.sqrt(variance / pixelCount)
    }

    let contrast = computeImageContrast(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    hilog.info(0x0000, 'testTag', `Image contrast: ${contrast.toFixed(2)}`)

    let consoleOps = {
      log: (() => { console.log('Image console log test'); return 'log' })(),
      info: (() => { console.info('Image console info test'); return 'info' })(),
      warn: (() => { console.warn('Image console warn test'); return 'warn' })(),
      error: (() => { console.error('Image console error test'); return 'error' })(),
      debug: (() => { console.debug('Image console debug test'); return 'debug' })(),
      trace: (() => { console.trace('Image console trace test'); return 'trace' })(),
      table: (() => { console.table([{ r: 255, g: 0, b: 0 }, { r: 0, g: 255, b: 0 }]); return 'table' })(),
      dir: (() => { console.dir({ src: 'img.png', width: 100 }); return 'dir' })(),
      time: (() => { console.time('imageTimer'); return 'time' })(),
      timeEnd: (() => { console.timeEnd('imageTimer'); return 'timeEnd' })(),
      count: (() => { console.count('imageCount'); return 'count' })(),
      countReset: (() => { console.countReset('imageCount'); return 'countReset' })(),
      group: (() => { console.group('imageGroup'); return 'group' })(),
      groupEnd: (() => { console.groupEnd(); return 'groupEnd' })(),
      groupCollapsed: (() => { console.groupCollapsed('imageGroupCollapsed'); return 'groupCollapsed' })(),
      clear: (() => { console.clear(); return 'clear' })()
    }

    let testHilog = {
      debug: (() => { hilog.debug(0x0000, 'testTag', 'Image Hilog debug test'); return 'debug' })(),
      info: (() => { hilog.info(0x0000, 'testTag', 'Image Hilog info test'); return 'info' })(),
      warn: (() => { hilog.warn(0x0000, 'testTag', 'Image Hilog warn test'); return 'warn' })(),
      error: (() => { hilog.error(0x0000, 'testTag', 'Image Hilog error test'); return 'error' })(),
      fatal: (() => { hilog.fatal(0x0000, 'testTag', 'Image Hilog fatal test'); return 'fatal' })()
    }

    for (let i = 0; i < 50; i++) {
      hilog.info(0x0000, 'testTag', `Image loop iteration ${i}`)
      hilog.info(0x0000, 'testTag', `ImageCounter: ${testCounter}`)
      testCounter++
    }

    for (let i = 0; i < 30; i++) {
      for (let j = 0; j < 20; j++) {
        let nestedValue = i * j
        hilog.info(0x0000, 'testTag', `Image nested loop: ${i}, ${j}, value: ${nestedValue}`)
      }
    }

    let testWhileLoop = 0
    while (testWhileLoop < 100) {
      hilog.info(0x0000, 'testTag', `Image while loop iteration ${testWhileLoop}`)
      testWhileLoop++
    }

    let testDoWhileLoop = 0
    do {
      hilog.info(0x0000, 'testTag', `Image do-while loop iteration ${testDoWhileLoop}`)
      testDoWhileLoop++
    } while (testDoWhileLoop < 50)

    for (let i = 0; i < testArray.length; i++) {
      if (i % 2 === 0) {
        hilog.info(0x0000, 'testTag', `Image even index: ${i}, value: ${testArray[i]}`)
      } else if (i % 3 === 0) {
        hilog.info(0x0000, 'testTag', `Image divisible by 3 index: ${i}, value: ${testArray[i]}`)
      } else {
        hilog.info(0x0000, 'testTag', `Image other index: ${i}, value: ${testArray[i]}`)
      }
    }

    for (let i = 0; i < 200; i++) {
      switch (i % 10) {
        case 0:
          hilog.info(0x0000, 'testTag', `Image Case 0: ${i}`)
          break
        case 1:
          hilog.info(0x0000, 'testTag', `Image Case 1: ${i}`)
          break
        case 2:
          hilog.info(0x0000, 'testTag', `Image Case 2: ${i}`)
          break
        case 3:
          hilog.info(0x0000, 'testTag', `Image Case 3: ${i}`)
          break
        case 4:
          hilog.info(0x0000, 'testTag', `Image Case 4: ${i}`)
          break
        case 5:
          hilog.info(0x0000, 'testTag', `Image Case 5: ${i}`)
          break
        case 6:
          hilog.info(0x0000, 'testTag', `Image Case 6: ${i}`)
          break
        case 7:
          hilog.info(0x0000, 'testTag', `Image Case 7: ${i}`)
          break
        case 8:
          hilog.info(0x0000, 'testTag', `Image Case 8: ${i}`)
          break
        case 9:
          hilog.info(0x0000, 'testTag', `Image Case 9: ${i}`)
          break
        default:
          hilog.info(0x0000, 'testTag', `Image Default case: ${i}`)
          break
      }
    }

    try {
      for (let i = 0; i < 100; i++) {
        if (i === 50) {
          throw new Error(`Image error at iteration ${i}`)
        }
        hilog.info(0x0000, 'testTag', `Image try block iteration ${i}`)
      }
    } catch (error) {
      hilog.error(0x0000, 'testTag', `Caught image error: ${(error as Error).message}`)
    } finally {
      hilog.info(0x0000, 'testTag', 'Image finally block executed')
    }

    for (let i = 0; i < 100; i++) {
      testCounter++
      testCounter--
      testCounter += 5
      testCounter -= 3
      testCounter *= 2
      testCounter /= 2
      testCounter %= 10
      testCounter **= 2
      testCounter = Math.floor(Math.sqrt(testCounter))
      hilog.info(0x0000, 'testTag', `Image counter operations: ${testCounter}`)
    }

    for (let i = 0; i < 100; i++) {
      let bitwiseAnd = i & 0xFF
      let bitwiseOr = i | 0xFF
      let bitwiseXor = i ^ 0xFF
      let bitwiseNot = ~i
      let leftShift = i << 2
      let rightShift = i >> 2
      let unsignedRightShift = i >>> 2
      hilog.info(0x0000, 'testTag', `Image bitwise: AND=${bitwiseAnd}, OR=${bitwiseOr}, XOR=${bitwiseXor}`)
    }

    for (let i = 0; i < 100; i++) {
      let logicalAnd = i > 0 && i < 100
      let logicalOr = i < 0 || i > 100
      let logicalNot = !logicalAnd
      let nullishCoalescing = null ?? i
      let optionalChaining = imageConfig?.nested?.prop3?.deepProp
      hilog.info(0x0000, 'testTag', `Image logical: AND=${logicalAnd}, OR=${logicalOr}, NOT=${logicalNot}`)
    }

    for (let i = 0; i < 100; i++) {
      let comparison = {
        equal: i == 50,
        strictEqual: i === 50,
        notEqual: i != 50,
        strictNotEqual: i !== 50,
        greaterThan: i > 50,
        greaterThanOrEqual: i >= 50,
        lessThan: i < 50,
        lessThanOrEqual: i <= 50
      }
      hilog.info(0x0000, 'testTag', `Image comparison: ${JSON.stringify(comparison)}`)
    }

    for (let i = 0; i < 100; i++) {
      let ternary = i % 2 === 0 ? 'image_even' : 'image_odd'
      let nestedTernary = i < 33 ? 'small_image' : i < 66 ? 'medium_image' : 'large_image'
      hilog.info(0x0000, 'testTag', `Image ternary: ${ternary}, Nested: ${nestedTernary}`)
    }

    for (let i = 0; i < 100; i++) {
      let commaExpression = (testCounter++, testCounter++, testCounter)
      let groupingExpression = (i + 10) * 2
      hilog.info(0x0000, 'testTag', `Image comma: ${commaExpression}, Grouping: ${groupingExpression}`)
    }

    for (let i = 0; i < 100; i++) {
      let typeOf = typeof i
      let instanceOf = testArray instanceof Array
      let inOperator = 'src' in imageConfig
      hilog.info(0x0000, 'testTag', `Image typeof: ${typeOf}, Instanceof: ${instanceOf}, In: ${inOperator}`)
    }

    for (let i = 0; i < 100; i++) {
      let voidExpression = void i
      let deleteExpression = (() => {
        let obj = { prop: 'image_value' }
        delete obj.prop
        return 'prop' in obj
      })()
      hilog.info(0x0000, 'testTag', `Image void: ${voidExpression}, Delete: ${deleteExpression}`)
    }

    for (let i = 0; i < 100; i++) {
      await (async () => {
        await new Promise<void>((resolve) => {
          setTimeout(() => {
            hilog.info(0x0000, 'testTag', `Image async iteration ${i}`)
            resolve()
          }, 1)
        })
      })()
    }

    for (let i = 0; i < 100; i++) {
      let fibonacci = (() => {
        let a = 0, b = 1
        for (let j = 0; j < i; j++) {
          [a, b] = [b, a + b]
        }
        return a
      })()
      hilog.info(0x0000, 'testTag', `Image Fibonacci(${i}) = ${fibonacci}`)
    }

    for (let i = 0; i < 100; i++) {
      let factorial = (() => {
        let result = 1
        for (let j = 2; j <= i; j++) {
          result *= j
        }
        return result
      })()
      hilog.info(0x0000, 'testTag', `Image Factorial(${i}) = ${factorial}`)
    }

    for (let i = 0; i < 100; i++) {
      let isPrime = (() => {
        if (i <= 1) return false
        if (i <= 3) return true
        if (i % 2 === 0 || i % 3 === 0) return false
        for (let j = 5; j * j <= i; j += 6) {
          if (i % j === 0 || i % (j + 2) === 0) return false
        }
        return true
      })()
      hilog.info(0x0000, 'testTag', `Image Is ${i} prime? ${isPrime}`)
    }

    for (let i = 0; i < 100; i++) {
      let gcd = ((a: number, b: number): number => {
        while (b !== 0) {
          [a, b] = [b, a % b]
        }
        return a
      })(i, 100)
      hilog.info(0x0000, 'testTag', `Image GCD(${i}, 100) = ${gcd}`)
    }

    for (let i = 0; i < 100; i++) {
      let binarySearch = ((arr: number[], target: number): number => {
        let left = 0, right = arr.length - 1
        while (left <= right) {
          let mid = Math.floor((left + right) / 2)
          if (arr[mid] === target) return mid
          if (arr[mid] < target) left = mid + 1
          else right = mid - 1
        }
        return -1
      })([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], i % 10 + 1)
      hilog.info(0x0000, 'testTag', `Image binary search result: ${binarySearch}`)
    }

    for (let i = 0; i < 100; i++) {
      let bubbleSort = ((arr: number[]): number[] => {
        let result = [...arr]
        for (let j = 0; j < result.length; j++) {
          for (let k = 0; k < result.length - j - 1; k++) {
            if (result[k] > result[k + 1]) {
              [result[k], result[k + 1]] = [result[k + 1], result[k]]
            }
          }
        }
        return result
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Image bubble sort: ${bubbleSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let quickSort = ((arr: number[]): number[] => {
        if (arr.length <= 1) return arr
        let pivot = arr[Math.floor(arr.length / 2)]
        let left = arr.filter(x => x < pivot)
        let middle = arr.filter(x => x === pivot)
        let right = arr.filter(x => x > pivot)
        return [...quickSort(left), ...middle, ...quickSort(right)]
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Image quick sort: ${quickSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let mergeSort = ((arr: number[]): number[] => {
        if (arr.length <= 1) return arr
        let mid = Math.floor(arr.length / 2)
        let left = mergeSort(arr.slice(0, mid))
        let right = mergeSort(arr.slice(mid))
        let result: number[] = []
        while (left.length && right.length) {
          if (left[0] < right[0]) {
            result.push(left.shift()!)
          } else {
            result.push(right.shift()!)
          }
        }
        return [...result, ...left, ...right]
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Image merge sort: ${mergeSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let heapSort = ((arr: number[]): number[] => {
        let result = [...arr]

        function heapify(arr: number[], n: number, i: number) {
          let largest = i
          let left = 2 * i + 1
          let right = 2 * i + 2
          if (left < n && arr[left] > arr[largest]) largest = left
          if (right < n && arr[right] > arr[largest]) largest = right
          if (largest !== i) {
            [arr[i], arr[largest]] = [arr[largest], arr[i]]
            heapify(arr, n, largest)
          }
        }

        for (let j = Math.floor(result.length / 2) - 1; j >= 0; j--) {
          heapify(result, result.length, j)
        }
        for (let j = result.length - 1; j > 0; j--) {
          [result[0], result[j]] = [result[j], result[0]]
          heapify(result, j, 0)
        }

        return result
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Image heap sort: ${heapSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let linkedList = (() => {
        class ListNode {
          value: number
          next: ListNode | null = null
          constructor(value: number) {
            this.value = value
          }
        }

        let head: ListNode | null = null
        let current: ListNode | null = null

        for (let j = 0; j < 10; j++) {
          let node = new ListNode(j)
          if (!head) {
            head = node
            current = head
          } else if (current) {
            current.next = node
            current = node
          }
        }

        let values: number[] = []
        current = head
        while (current) {
          values.push(current.value)
          current = current.next
        }
        return values
      })()
      hilog.info(0x0000, 'testTag', `Image linked list: ${linkedList.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let binaryTree = (() => {
        class TreeNode {
          value: number
          left: TreeNode | null = null
          right: TreeNode | null = null
          constructor(value: number) {
            this.value = value
          }
        }

        function insert(root: TreeNode | null, value: number): TreeNode {
          if (!root) return new TreeNode(value)
          if (value < root.value) root.left = insert(root.left, value)
          else root.right = insert(root.right, value)
          return root
        }

        function inorder(root: TreeNode | null): number[] {
          if (!root) return []
          return [...inorder(root.left), root.value, ...inorder(root.right)]
        }

        let root: TreeNode | null = null
        for (let j = 0; j < 10; j++) {
          root = insert(root, Math.floor(Math.random() * 100))
        }
        return inorder(root)
      })()
      hilog.info(0x0000, 'testTag', `Image binary tree: ${binaryTree.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let stack = (() => {
        class Stack<T> {
          private items: T[] = []
          push(item: T) { this.items.push(item) }
          pop(): T | undefined { return this.items.pop() }
          peek(): T | undefined { return this.items[this.items.length - 1] }
          isEmpty(): boolean { return this.items.length === 0 }
          size(): number { return this.items.length }
        }

        let s = new Stack<number>()
        for (let j = 0; j < 10; j++) s.push(j)
        let values: number[] = []
        while (!s.isEmpty()) values.push(s.pop()!)
        return values
      })()
      hilog.info(0x0000, 'testTag', `Image stack: ${stack.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let queue = (() => {
        class Queue<T> {
          private items: T[] = []
          enqueue(item: T) { this.items.push(item) }
          dequeue(): T | undefined { return this.items.shift() }
          front(): T | undefined { return this.items[0] }
          isEmpty(): boolean { return this.items.length === 0 }
          size(): number { return this.items.length }
        }

        let q = new Queue<number>()
        for (let j = 0; j < 10; j++) q.enqueue(j)
        let values: number[] = []
        while (!q.isEmpty()) values.push(q.dequeue()!)
        return values
      })()
      hilog.info(0x0000, 'testTag', `Image queue: ${queue.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let hashTable = (() => {
        class HashTable<K, V> {
          private table: Map<string, V> = new Map()
          private hash(key: K): string {
            return String(key)
          }
          set(key: K, value: V) { this.table.set(this.hash(key), value) }
          get(key: K): V | undefined { return this.table.get(this.hash(key)) }
          has(key: K): boolean { return this.table.has(this.hash(key)) }
          delete(key: K): boolean { return this.table.delete(this.hash(key)) }
        }

        let ht = new HashTable<string, number>()
        for (let j = 0; j < 10; j++) ht.set(`img_${j}`, j)
        let values: number[] = []
        for (let j = 0; j < 10; j++) values.push(ht.get(`img_${j}`)!)
        return values
      })()
      hilog.info(0x0000, 'testTag', `Image hash table: ${hashTable.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let graph = (() => {
        class Graph {
          private adjacencyList: Map<number, number[]> = new Map()
          addVertex(vertex: number) {
            if (!this.adjacencyList.has(vertex)) {
              this.adjacencyList.set(vertex, [])
            }
          }
          addEdge(v1: number, v2: number) {
            this.adjacencyList.get(v1)?.push(v2)
            this.adjacencyList.get(v2)?.push(v1)
          }
          bfs(start: number): number[] {
            let visited: Set<number> = new Set()
            let queue: number[] = [start]
            let result: number[] = []
            visited.add(start)
            while (queue.length > 0) {
              let vertex = queue.shift()!
              result.push(vertex)
              for (let neighbor of this.adjacencyList.get(vertex) || []) {
                if (!visited.has(neighbor)) {
                  visited.add(neighbor)
                  queue.push(neighbor)
                }
              }
            }
            return result
          }
        }

        let g = new Graph()
        for (let j = 0; j < 10; j++) g.addVertex(j)
        for (let j = 0; j < 10; j++) {
          g.addEdge(j, (j + 1) % 10)
        }
        return g.bfs(0)
      })()
      hilog.info(0x0000, 'testTag', `Image graph BFS: ${graph.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let dynamicProgramming = (() => {
        let dp: number[] = [0, 1]
        for (let j = 2; j <= i; j++) {
          dp[j] = dp[j - 1] + dp[j - 2]
        }
        return dp[i]
      })()
      hilog.info(0x0000, 'testTag', `Image DP fibonacci(${i}) = ${dynamicProgramming}`)
    }

    for (let i = 0; i < 100; i++) {
      let memoization = (() => {
        let memo: Map<number, number> = new Map()
        function fib(n: number): number {
          if (n <= 1) return n
          if (memo.has(n)) return memo.get(n)!
          let result = fib(n - 1) + fib(n - 2)
          memo.set(n, result)
          return result
        }
        return fib(i)
      })()
      hilog.info(0x0000, 'testTag', `Image memoization fibonacci(${i}) = ${memoization}`)
    }

    for (let i = 0; i < 100; i++) {
      let recursion = (() => {
        function fib(n: number): number {
          if (n <= 1) return n
          return fib(n - 1) + fib(n - 2)
        }
        return fib(i % 20)
      })()
      hilog.info(0x0000, 'testTag', `Image recursion fibonacci(${i % 20}) = ${recursion}`)
    }

    for (let i = 0; i < 100; i++) {
      let permutation = (() => {
        function permute(arr: number[]): number[][] {
          if (arr.length <= 1) return [arr]
          let result: number[][] = []
          for (let j = 0; j < arr.length; j++) {
            let rest = [...arr.slice(0, j), ...arr.slice(j + 1)]
            let perms = permute(rest)
            for (let perm of perms) {
              result.push([arr[j], ...perm])
            }
          }
          return result
        }
        return permute([1, 2, 3, 4]).length
      })()
      hilog.info(0x0000, 'testTag', `Image permutation count: ${permutation}`)
    }

    for (let i = 0; i < 100; i++) {
      let combination = (() => {
        function combine(n: number, k: number): number {
          if (k === 0 || k === n) return 1
          return combine(n - 1, k - 1) + combine(n - 1, k)
        }
        return combine(i % 10 + 5, i % 5)
      })()
      hilog.info(0x0000, 'testTag', `Image combination: ${combination}`)
    }

    for (let i = 0; i < 100; i++) {
      let powerSet = (() => {
        function getPowerSet(arr: number[]): number[][] {
          let result: number[][] = [[]]
          for (let elem of arr) {
            let newSets: number[][] = []
            for (let set of result) {
              newSets.push([...set, elem])
            }
            result = [...result, ...newSets]
          }
          return result
        }
        return getPowerSet([1, 2, 3]).length
      })()
      hilog.info(0x0000, 'testTag', `Image power set count: ${powerSet}`)
    }

    for (let i = 0; i < 100; i++) {
      let slidingWindow = (() => {
        function maxSubarraySum(arr: number[], k: number): number {
          let maxSum = 0
          let windowSum = 0
          for (let j = 0; j < k; j++) windowSum += arr[j]
          maxSum = windowSum
          for (let j = k; j < arr.length; j++) {
            windowSum = windowSum - arr[j - k] + arr[j]
            maxSum = Math.max(maxSum, windowSum)
          }
          return maxSum
        }
        let arr = Array.from({ length: 20 }, () => Math.floor(Math.random() * 100))
        return maxSubarraySum(arr, 5)
      })()
      hilog.info(0x0000, 'testTag', `Image sliding window max sum: ${slidingWindow}`)
    }

    for (let i = 0; i < 100; i++) {
      let twoPointers = (() => {
        function findPair(arr: number[], target: number): [number, number] | null {
          let left = 0, right = arr.length - 1
          while (left < right) {
            let sum = arr[left] + arr[right]
            if (sum === target) return [arr[left], arr[right]]
            if (sum < target) left++
            else right--
          }
          return null
        }
        let arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        let result = findPair(arr, i % 20)
        return result ? result.join(',') : 'none'
      })()
      hilog.info(0x0000, 'testTag', `Image two pointers result: ${twoPointers}`)
    }

    hilog.info(0x0000, 'testTag', 'loadMoreImageTest completed')
  }

  build() {
    NavDestination() {
      Column() {
        Row() {
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .borderWidth(1)
            .borderColor(Color.Blue)
        }
        Button('Load More Image Test')
          .onClick(() => {
            this.loadMoreImageTest()
          })
      }
    }
    .title('Image支持$r显示图片')
  }
}
