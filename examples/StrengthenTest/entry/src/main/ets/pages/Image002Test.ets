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
export struct Image002Test {
  @State pixelmap: PixelMap | string = ''
  @State testTriggered: boolean = false
  @State lastTestLog: string = ''

  aboutToAppear() {
    // 从配置文件或数据库中读取图片地址
    this.pixelmap = this.getConfiguredImageUrl();
  }

  getConfiguredImageUrl(): string {
    return ''
  }

  async loadmoreImageTest(): void {
    let testCounter = 0
    let testString = 'Network Image Test String'
    let testArray: string[] = []

    for (let i = 0; i < 100; i++) {
      testArray.push(`NetworkImageItem_${i}`)
    }

    let testMap: Map<string, number> = new Map()
    for (let i = 0; i < 50; i++) {
      testMap.set(`net_img_key_${i}`, i)
    }

    let testSet: Set<number> = new Set()
    for (let i = 0; i < 75; i++) {
      testSet.add(i)
    }

    let networkImageConfig = {
      url: 'https://example.com/images/test_network.png',
      method: 'GET',
      timeout: 30000,
      retryCount: 3,
      retryDelay: 1000,
      headers: {
        'Accept': 'image/*',
        'User-Agent': 'ArkUI/1.0',
        'Cache-Control': 'no-cache',
        'Authorization': 'Bearer token_value',
        'X-Request-ID': 'req_123456789'
      },
      cacheStrategy: 'memory_disk',
      maxConcurrent: 5,
      priority: 'normal',
      enableThumbnail: true,
      thumbnailRatio: 0.2,
      decodeOptions: {
        desiredSize: { width: 200, height: 200 },
        editable: false,
        decodeRegion: { x: 0, y: 0, width: 100, height: 100 },
        sampleSize: 1
      },
      fallback: 'app.media.placeholder',
      nested: {
        cdnUrl: 'https://cdn.example.com/img/',
        bucket: 'image-bucket-001',
        objectKey: 'object_key_001',
        signed: true,
        expires: 3600,
        prop3: {
          deepProp: 'deepNetworkImageValue'
        }
      }
    }

    let parseUrl = (url: string): {
      protocol: string,
      host: string,
      port: number,
      path: string,
      query: string,
      fragment: string
    } => {
      let protocolMatch = url.match(/^(\w+):\/\//)
      let protocol = protocolMatch ? protocolMatch[1] : ''
      let withoutProtocol = protocolMatch ? url.substring(protocolMatch[0].length) : url
      let fragmentIndex = withoutProtocol.indexOf('#')
      let fragment = fragmentIndex >= 0 ? withoutProtocol.substring(fragmentIndex + 1) : ''
      let withoutFragment = fragmentIndex >= 0 ? withoutProtocol.substring(0, fragmentIndex) : withoutProtocol
      let queryIndex = withoutFragment.indexOf('?')
      let query = queryIndex >= 0 ? withoutFragment.substring(queryIndex + 1) : ''
      let hostAndPath = queryIndex >= 0 ? withoutFragment.substring(0, queryIndex) : withoutFragment
      let pathIndex = hostAndPath.indexOf('/')
      let hostPort = pathIndex >= 0 ? hostAndPath.substring(0, pathIndex) : hostAndPath
      let path = pathIndex >= 0 ? hostAndPath.substring(pathIndex) : '/'
      let portMatch = hostPort.match(/:(\d+)$/)
      let port = portMatch ? parseInt(portMatch[1]) : 0
      let host = portMatch ? hostPort.substring(0, hostPort.length - portMatch[0].length) : hostPort
      return { protocol, host, port, path, query, fragment }
    }

    let buildUrl = (parts: {
      protocol: string,
      host: string,
      port: number,
      path: string,
      query: string,
      fragment: string
    }): string => {
      let url = `${parts.protocol}://${parts.host}`
      if (parts.port > 0) {
        url += `:${parts.port}`
      }
      url += parts.path
      if (parts.query) {
        url += `?${parts.query}`
      }
      if (parts.fragment) {
        url += `#${parts.fragment}`
      }
      return url
    }

    let parseQueryString = (query: string): Map<string, string> => {
      let result: Map<string, string> = new Map()
      if (!query) return result
      let pairs = query.split('&')
      for (let pair of pairs) {
        let parts = pair.split('=')
        let key = parts[0]
        let value = parts[1]
        if (key) {
          result.set(decodeURIComponent(key), value ? decodeURIComponent(value) : '')
        }
      }
      return result
    }

    let buildQueryString = (params: Map<string, string>): string => {
      let pairs: string[] = []
      params.forEach((value, key) => {
        pairs.push(`${encodeURIComponent(key)}=${encodeURIComponent(value)}`)
      })
      return pairs.join('&')
    }

    let testUrls: string[] = [
      'https://example.com/images/photo1.png',
      'https://cdn.example.com:8443/img/photo2.jpg',
      'http://localhost:8080/assets/icon.svg',
      'https://api.example.com/v1/images/123?width=200&height=200',
      'https://example.com/images/animated.gif#fragment1',
      'ftp://ftp.example.com/images/archive.zip',
      'https://user:pass@example.com/secure/img.png',
      'https://example.com/path/to/deep/image.png',
      'https://example.com/img?format=webp&q=80',
      'https://example.com/img#section',
      'https://example.com/path/with%20spaces/image.png',
      'https://example.com/img?a=1&b=2&c=3',
      'https://example.com:443/img/secure.png',
      'https://example.com/img.bmp',
      'https://example.com/img.tiff'
    ]

    let parsedUrls = testUrls.map(url => parseUrl(url))
    for (let i = 0; i < parsedUrls.length; i++) {
      hilog.info(0x0000, 'testTag', `Parsed URL ${i}: protocol=${parsedUrls[i].protocol}, host=${parsedUrls[i].host}, port=${parsedUrls[i].port}, path=${parsedUrls[i].path}`)
    }

    let reconstructedUrls = parsedUrls.map(parts => buildUrl(parts))
    for (let i = 0; i < reconstructedUrls.length; i++) {
      hilog.info(0x0000, 'testTag', `Reconstructed URL ${i}: ${reconstructedUrls[i]}`)
    }

    let testQueryStrings = [
      'width=200&height=200',
      'format=webp&quality=80',
      'id=12345&type=thumbnail',
      'token=abc123&expires=3600',
      'a=1&b=2&c=3&d=4'
    ]

    for (let qs of testQueryStrings) {
      let params = parseQueryString(qs)
      let rebuilt = buildQueryString(params)
      hilog.info(0x0000, 'testTag', `Query rebuild: ${qs} -> ${rebuilt}`)
    }

    let imageFormatExtensions: string[] = ['.png', '.jpg', '.jpeg', '.gif', '.bmp', '.webp', '.svg', '.ico', '.tiff']
    let imageMimeTypes: Map<string, string> = new Map()
    imageMimeTypes.set('.png', 'image/png')
    imageMimeTypes.set('.jpg', 'image/jpeg')
    imageMimeTypes.set('.jpeg', 'image/jpeg')
    imageMimeTypes.set('.gif', 'image/gif')
    imageMimeTypes.set('.bmp', 'image/bmp')
    imageMimeTypes.set('.webp', 'image/webp')
    imageMimeTypes.set('.svg', 'image/svg+xml')
    imageMimeTypes.set('.ico', 'image/x-icon')
    imageMimeTypes.set('.tiff', 'image/tiff')

    let detectImageFormat = (url: string): string => {
      let lowerUrl = url.toLowerCase()
      let queryIndex = lowerUrl.indexOf('?')
      let cleanUrl = queryIndex >= 0 ? lowerUrl.substring(0, queryIndex) : lowerUrl
      let fragmentIndex = cleanUrl.indexOf('#')
      if (fragmentIndex >= 0) cleanUrl = cleanUrl.substring(0, fragmentIndex)
      for (let ext of imageFormatExtensions) {
        if (cleanUrl.endsWith(ext)) {
          return imageMimeTypes.get(ext) || 'unknown'
        }
      }
      return 'unknown'
    }

    for (let url of testUrls) {
      let format = detectImageFormat(url)
      hilog.info(0x0000, 'testTag', `Detected format for ${url}: ${format}`)
    }

    let httpMethods: string[] = ['GET', 'POST', 'PUT', 'DELETE', 'HEAD', 'OPTIONS', 'PATCH']
    let httpStatusCodes: Map<number, string> = new Map()
    httpStatusCodes.set(200, 'OK')
    httpStatusCodes.set(201, 'Created')
    httpStatusCodes.set(204, 'No Content')
    httpStatusCodes.set(301, 'Moved Permanently')
    httpStatusCodes.set(302, 'Found')
    httpStatusCodes.set(304, 'Not Modified')
    httpStatusCodes.set(400, 'Bad Request')
    httpStatusCodes.set(401, 'Unauthorized')
    httpStatusCodes.set(403, 'Forbidden')
    httpStatusCodes.set(404, 'Not Found')
    httpStatusCodes.set(408, 'Request Timeout')
    httpStatusCodes.set(429, 'Too Many Requests')
    httpStatusCodes.set(500, 'Internal Server Error')
    httpStatusCodes.set(502, 'Bad Gateway')
    httpStatusCodes.set(503, 'Service Unavailable')
    httpStatusCodes.set(504, 'Gateway Timeout')

    for (let [code, message] of httpStatusCodes) {
      hilog.info(0x0000, 'testTag', `HTTP ${code}: ${message}`)
    }

    interface HttpResponse {
      status: number
      statusText: string
      headers: Map<string, string>
      body: ArrayBuffer
      url: string
      ok: boolean
    }

    let simulateHttpRequest = (url: string, method: string, timeout: number): HttpResponse => {
      let parsed = parseUrl(url)
      let status = 200
      let statusText = 'OK'
      if (!parsed.protocol || !parsed.host) {
        status = 400
        statusText = 'Bad Request'
      } else if (parsed.host.includes('error')) {
        status = 500
        statusText = 'Internal Server Error'
      } else if (parsed.host.includes('forbidden')) {
        status = 403
        statusText = 'Forbidden'
      } else if (parsed.host.includes('notfound')) {
        status = 404
        statusText = 'Not Found'
      } else if (timeout < 100) {
        status = 408
        statusText = 'Request Timeout'
      }
      let headers: Map<string, string> = new Map()
      headers.set('Content-Type', 'image/png')
      headers.set('Content-Length', '1024')
      headers.set('Cache-Control', 'max-age=3600')
      headers.set('ETag', '"abc123"')
      headers.set('Last-Modified', 'Mon, 01 Jan 2024 00:00:00 GMT')
      let body = new ArrayBuffer(1024)
      let view = new DataView(body)
      for (let i = 0; i < 256; i++) {
        view.setInt32(i * 4, i)
      }
      return {
        status,
        statusText,
        headers,
        body,
        url,
        ok: status >= 200 && status < 300
      }
    }

    let testHttpResponses = testUrls.map(url => simulateHttpRequest(url, 'GET', 1000))
    for (let i = 0; i < testHttpResponses.length; i++) {
      let resp = testHttpResponses[i]
      hilog.info(0x0000, 'testTag', `HTTP Response ${i}: ${resp.status} ${resp.statusText}, ok=${resp.ok}`)
    }

    let errorResponses = testHttpResponses.filter(resp => !resp.ok)
    hilog.info(0x0000, 'testTag', `Error response count: ${errorResponses.length}`)

    let okResponses = testHttpResponses.filter(resp => resp.ok)
    hilog.info(0x0000, 'testTag', `OK response count: ${okResponses.length}`)

    let statusDistribution: Map<number, number> = new Map()
    for (let resp of testHttpResponses) {
      statusDistribution.set(resp.status, (statusDistribution.get(resp.status) || 0) + 1)
    }
    for (let [code, count] of statusDistribution) {
      hilog.info(0x0000, 'testTag', `Status distribution ${code}: ${count}`)
    }

    for (let method of httpMethods) {
      let resp = simulateHttpRequest('https://example.com/img.png', method, 1000)
      hilog.info(0x0000, 'testTag', `Method ${method}: ${resp.status} ${resp.statusText}`)
    }

    hilog.info(0x0000, 'testTag', 'loadmoreImageTest part 1 completed')

    class MemoryCache {
      private store: Map<string, { body: ArrayBuffer, timestamp: number, ttl: number }> = new Map()
      private maxSize: number
      private currentSize: number = 0

      constructor(maxSize: number) {
        this.maxSize = maxSize
      }

      set(key: string, body: ArrayBuffer, ttl: number): boolean {
        let size = body.byteLength
        if (size > this.maxSize) return false
        while (this.currentSize + size > this.maxSize && this.store.size > 0) {
          let oldestKey: string | null = null
          let oldestTime = Date.now()
          for (let [k, v] of this.store) {
            if (v.timestamp < oldestTime) {
              oldestTime = v.timestamp
              oldestKey = k
            }
          }
          if (oldestKey) {
            let evicted = this.store.get(oldestKey)
            if (evicted) {
              this.currentSize -= evicted.body.byteLength
              this.store.delete(oldestKey)
            }
          }
        }
        this.store.set(key, { body, timestamp: Date.now(), ttl })
        this.currentSize += size
        return true
      }

      get(key: string): ArrayBuffer | null {
        let entry = this.store.get(key)
        if (!entry) return null
        if (Date.now() - entry.timestamp > entry.ttl) {
          this.currentSize -= entry.body.byteLength
          this.store.delete(key)
          return null
        }
        return entry.body
      }

      has(key: string): boolean {
        return this.store.has(key)
      }

      delete(key: string): boolean {
        let entry = this.store.get(key)
        if (entry) {
          this.currentSize -= entry.body.byteLength
        }
        return this.store.delete(key)
      }

      clear(): void {
        this.store.clear()
        this.currentSize = 0
      }

      size(): number {
        return this.currentSize
      }

      count(): number {
        return this.store.size
      }
    }

    let memoryCache = new MemoryCache(10 * 1024 * 1024)
    for (let i = 0; i < 50; i++) {
      let body = new ArrayBuffer(1024 * (i + 1))
      memoryCache.set(`cache_key_${i}`, body, 60000)
    }
    hilog.info(0x0000, 'testTag', `Memory cache size: ${memoryCache.size()}, count: ${memoryCache.count()}`)

    for (let i = 0; i < 50; i++) {
      let body = memoryCache.get(`cache_key_${i}`)
      hilog.info(0x0000, 'testTag', `Cache get ${i}: ${body ? 'hit' : 'miss'}`)
    }

    let cacheKeyGenerator = (url: string, options: { width: number, height: number, format: string }): string => {
      let parsed = parseUrl(url)
      let keyParts = [
        parsed.host,
        parsed.path,
        `${options.width}x${options.height}`,
        options.format
      ]
      return keyParts.join('|')
    }

    let testCacheKeys = testUrls.map(url => cacheKeyGenerator(url, { width: 100, height: 100, format: 'webp' }))
    for (let i = 0; i < testCacheKeys.length; i++) {
      hilog.info(0x0000, 'testTag', `Cache key ${i}: ${testCacheKeys[i]}`)
    }

    interface DownloadTask {
      id: number
      url: string
      totalBytes: number
      downloadedBytes: number
      startTime: number
      endTime: number
      status: string
      error: string
      progress: number
      speed: number
    }

    let simulateDownload = (url: string, totalBytes: number, chunkSize: number, delayPerChunk: number): DownloadTask => {
      let task: DownloadTask = {
        id: Math.floor(Math.random() * 1000000),
        url,
        totalBytes,
        downloadedBytes: 0,
        startTime: Date.now(),
        endTime: 0,
        status: 'pending',
        error: '',
        progress: 0,
        speed: 0
      }
      task.status = 'running'
      let chunks = Math.ceil(totalBytes / chunkSize)
      for (let i = 0; i < chunks; i++) {
        let chunkBytes = Math.min(chunkSize, totalBytes - task.downloadedBytes)
        task.downloadedBytes += chunkBytes
        task.progress = task.downloadedBytes / task.totalBytes
        let elapsed = (i + 1) * delayPerChunk
        if (elapsed > 0) {
          task.speed = task.downloadedBytes / (elapsed / 1000)
        }
        if (i % 10 === 0) {
          hilog.info(0x0000, 'testTag', `Download ${task.id} progress: ${(task.progress * 100).toFixed(2)}%, speed: ${task.speed.toFixed(2)} B/s`)
        }
      }
      task.status = 'completed'
      task.endTime = Date.now()
      return task
    }

    let downloadTasks = testUrls.slice(0, 10).map(url => simulateDownload(url, 1024 * 1024, 1024 * 64, 10))
    for (let task of downloadTasks) {
      hilog.info(0x0000, 'testTag', `Download ${task.id} - ${task.url}: ${task.status}, progress=${task.progress.toFixed(2)}, duration=${task.endTime - task.startTime}ms`)
    }

    let averageDownloadSpeed = downloadTasks.reduce((sum, task) => sum + task.speed, 0) / downloadTasks.length
    hilog.info(0x0000, 'testTag', `Average download speed: ${averageDownloadSpeed.toFixed(2)} B/s`)

    let totalDownloadedBytes = downloadTasks.reduce((sum, task) => sum + task.downloadedBytes, 0)
    hilog.info(0x0000, 'testTag', `Total downloaded bytes: ${totalDownloadedBytes}`)

    let fastestTask = downloadTasks.reduce((max, task) => task.speed > max.speed ? task : max, downloadTasks[0])
    hilog.info(0x0000, 'testTag', `Fastest download: ${fastestTask.id}, speed=${fastestTask.speed.toFixed(2)} B/s`)

    let slowestTask = downloadTasks.reduce((min, task) => task.speed < min.speed ? task : min, downloadTasks[0])
    hilog.info(0x0000, 'testTag', `Slowest download: ${slowestTask.id}, speed=${slowestTask.speed.toFixed(2)} B/s`)

    class DownloadQueue {
      private queue: DownloadTask[] = []
      private maxConcurrent: number
      private running: number = 0
      private completed: DownloadTask[] = []
      private failed: DownloadTask[] = []

      constructor(maxConcurrent: number) {
        this.maxConcurrent = maxConcurrent
      }

      enqueue(task: DownloadTask): void {
        this.queue.push(task)
      }

      process(): void {
        while (this.running < this.maxConcurrent && this.queue.length > 0) {
          let task = this.queue.shift()
          if (task) {
            this.running++
            task.status = 'running'
            task.startTime = Date.now()
            try {
              let chunks = Math.ceil(task.totalBytes / 65536)
              for (let i = 0; i < chunks; i++) {
                let chunkBytes = Math.min(65536, task.totalBytes - task.downloadedBytes)
                task.downloadedBytes += chunkBytes
                task.progress = task.downloadedBytes / task.totalBytes
              }
              if (task.downloadedBytes === task.totalBytes) {
                task.status = 'completed'
                this.completed.push(task)
              } else {
                task.status = 'failed'
                task.error = 'Incomplete download'
                this.failed.push(task)
              }
            } catch (error) {
              task.status = 'failed'
              task.error = (error as Error).message
              this.failed.push(task)
            }
            task.endTime = Date.now()
            this.running--
          }
        }
      }

      getStats(): { pending: number, running: number, completed: number, failed: number } {
        return {
          pending: this.queue.length,
          running: this.running,
          completed: this.completed.length,
          failed: this.failed.length
        }
      }
    }

    let downloadQueue = new DownloadQueue(5)
    for (let i = 0; i < 20; i++) {
      let task: DownloadTask = {
        id: i,
        url: `https://example.com/image_${i}.png`,
        totalBytes: 1024 * (i + 1) * 10,
        downloadedBytes: 0,
        startTime: 0,
        endTime: 0,
        status: 'pending',
        error: '',
        progress: 0,
        speed: 0
      }
      downloadQueue.enqueue(task)
    }
    downloadQueue.process()
    let queueStats = downloadQueue.getStats()
    hilog.info(0x0000, 'testTag', `Queue stats: ${JSON.stringify(queueStats)}`)

    let retryStrategies: Map<string, number[]> = new Map()
    retryStrategies.set('linear', [1000, 2000, 3000, 4000, 5000])
    retryStrategies.set('exponential', [1000, 2000, 4000, 8000, 16000])
    retryStrategies.set('fixed', [2000, 2000, 2000, 2000, 2000])
    retryStrategies.set('random', [Math.random() * 5000, Math.random() * 5000, Math.random() * 5000])

    for (let [name, delays] of retryStrategies) {
      let totalDelay = delays.reduce((sum, d) => sum + d, 0)
      hilog.info(0x0000, 'testTag', `Retry strategy ${name}: total delay=${totalDelay.toFixed(2)}ms`)
    }

    let simulateRetry = (url: string, maxRetries: number, strategy: string): { success: boolean, attempts: number, finalStatus: number } => {
      let attempts = 0
      let delays = retryStrategies.get(strategy) || [1000]
      let response = simulateHttpRequest(url, 'GET', 1000)
      attempts++
      while (!response.ok && attempts < maxRetries) {
        let delayIndex = (attempts - 1) % delays.length
        hilog.info(0x0000, 'testTag', `Retry attempt ${attempts} for ${url}, delay=${delays[delayIndex]}ms`)
        response = simulateHttpRequest(url, 'GET', 1000)
        attempts++
      }
      return {
        success: response.ok,
        attempts,
        finalStatus: response.status
      }
    }

    let retryResults = testUrls.map(url => simulateRetry(url, 5, 'exponential'))
    for (let i = 0; i < retryResults.length; i++) {
      hilog.info(0x0000, 'testTag', `Retry result ${i}: success=${retryResults[i].success}, attempts=${retryResults[i].attempts}, status=${retryResults[i].finalStatus}`)
    }

    let successfulRetries = retryResults.filter(r => r.success).length
    let failedRetries = retryResults.filter(r => !r.success).length
    hilog.info(0x0000, 'testTag', `Retry summary: success=${successfulRetries}, failed=${failedRetries}`)

    hilog.info(0x0000, 'testTag', 'loadmoreImageTest part 2 completed')

    let simulatePixelData = (() => {
      let width = 20
      let height = 20
      let data = new Uint8Array(width * height * 4)
      for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
          let offset = (y * width + x) * 4
          data[offset] = (x * 25) % 256
          data[offset + 1] = (y * 25) % 256
          data[offset + 2] = ((x + y) * 12) % 256
          data[offset + 3] = 255
        }
      }
      return { width, height, data }
    })()

    hilog.info(0x0000, 'testTag', `Pixel data: w=${simulatePixelData.width}, h=${simulatePixelData.height}, size=${simulatePixelData.data.length}`)

    let computeHistogram = (pixelData: Uint8Array, width: number, height: number): { r: number[], g: number[], b: number[] } => {
      let r: number[] = Array.from({ length: 256 }, () => 0)
      let g: number[] = Array.from({ length: 256 }, () => 0)
      let b: number[] = Array.from({ length: 256 }, () => 0)
      for (let i = 0; i < width * height; i++) {
        r[pixelData[i * 4]]++
        g[pixelData[i * 4 + 1]]++
        b[pixelData[i * 4 + 2]]++
      }
      return { r, g, b }
    }

    let histogram = computeHistogram(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    let histStats = {
      rMax: Math.max(...histogram.r),
      gMax: Math.max(...histogram.g),
      bMax: Math.max(...histogram.b),
      rSum: histogram.r.reduce((a, b) => a + b, 0),
      gSum: histogram.g.reduce((a, b) => a + b, 0),
      bSum: histogram.b.reduce((a, b) => a + b, 0)
    }
    hilog.info(0x0000, 'testTag', `Histogram: R(max=${histStats.rMax}, sum=${histStats.rSum}), G(max=${histStats.gMax}, sum=${histStats.gSum}), B(max=${histStats.bMax}, sum=${histStats.bSum})`)

    let computeAverageColor = (pixelData: Uint8Array, width: number, height: number): { r: number, g: number, b: number, a: number } => {
      let totalR = 0, totalG = 0, totalB = 0, totalA = 0
      let count = width * height
      for (let i = 0; i < count; i++) {
        totalR += pixelData[i * 4]
        totalG += pixelData[i * 4 + 1]
        totalB += pixelData[i * 4 + 2]
        totalA += pixelData[i * 4 + 3]
      }
      return {
        r: totalR / count,
        g: totalG / count,
        b: totalB / count,
        a: totalA / count
      }
    }

    let avgColor = computeAverageColor(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    hilog.info(0x0000, 'testTag', `Average color: R=${avgColor.r.toFixed(2)}, G=${avgColor.g.toFixed(2)}, B=${avgColor.b.toFixed(2)}, A=${avgColor.a.toFixed(2)}`)

    let computeBrightness = (pixelData: Uint8Array, width: number, height: number): number => {
      let total = 0
      let count = width * height
      for (let i = 0; i < count; i++) {
        total += 0.299 * pixelData[i * 4] + 0.587 * pixelData[i * 4 + 1] + 0.114 * pixelData[i * 4 + 2]
      }
      return total / count
    }

    let avgBrightness = computeBrightness(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    hilog.info(0x0000, 'testTag', `Average brightness: ${avgBrightness.toFixed(2)}`)

    let computeContrast = (pixelData: Uint8Array, width: number, height: number): number => {
      let mean = computeBrightness(pixelData, width, height)
      let variance = 0
      let count = width * height
      for (let i = 0; i < count; i++) {
        let brightness = 0.299 * pixelData[i * 4] + 0.587 * pixelData[i * 4 + 1] + 0.114 * pixelData[i * 4 + 2]
        variance += (brightness - mean) * (brightness - mean)
      }
      return Math.sqrt(variance / count)
    }

    let contrast = computeContrast(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height)
    hilog.info(0x0000, 'testTag', `Contrast: ${contrast.toFixed(2)}`)

    let colorFilters: Map<string, number[]> = new Map()
    colorFilters.set('identity', [
      1.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ])
    colorFilters.set('grayscale', [
      0.299, 0.587, 0.114, 0.0, 0.0,
      0.299, 0.587, 0.114, 0.0, 0.0,
      0.299, 0.587, 0.114, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ])
    colorFilters.set('sepia', [
      0.393, 0.769, 0.189, 0.0, 0.0,
      0.349, 0.686, 0.168, 0.0, 0.0,
      0.272, 0.534, 0.131, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ])
    colorFilters.set('invert', [
      -1.0, 0.0, 0.0, 0.0, 1.0,
      0.0, -1.0, 0.0, 0.0, 1.0,
      0.0, 0.0, -1.0, 0.0, 1.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ])
    colorFilters.set('brightness', [
      1.2, 0.0, 0.0, 0.0, 0.0,
      0.0, 1.2, 0.0, 0.0, 0.0,
      0.0, 0.0, 1.2, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0, 0.0
    ])

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
      for (let [filterName, matrix] of colorFilters) {
        let result = applyColorFilter(pixel.r, pixel.g, pixel.b, pixel.a, matrix)
        hilog.info(0x0000, 'testTag', `Pixel(${pixel.r},${pixel.g},${pixel.b},${pixel.a}) ${filterName} -> (${result.r.toFixed(0)},${result.g.toFixed(0)},${result.b.toFixed(0)},${result.a.toFixed(0)})`)
      }
    }

    let resizeImage = (pixelData: Uint8Array, srcWidth: number, srcHeight: number, dstWidth: number, dstHeight: number): Uint8Array => {
      let result = new Uint8Array(dstWidth * dstHeight * 4)
      let xRatio = srcWidth / dstWidth
      let yRatio = srcHeight / dstHeight
      for (let y = 0; y < dstHeight; y++) {
        for (let x = 0; x < dstWidth; x++) {
          let srcX = Math.floor(x * xRatio)
          let srcY = Math.floor(y * yRatio)
          let srcOffset = (srcY * srcWidth + srcX) * 4
          let dstOffset = (y * dstWidth + x) * 4
          result[dstOffset] = pixelData[srcOffset]
          result[dstOffset + 1] = pixelData[srcOffset + 1]
          result[dstOffset + 2] = pixelData[srcOffset + 2]
          result[dstOffset + 3] = pixelData[srcOffset + 3]
        }
      }
      return result
    }

    let resizedPixelData = resizeImage(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height, 10, 10)
    hilog.info(0x0000, 'testTag', `Resized image: 20x20 -> 10x10, size=${resizedPixelData.length}`)

    let cropImage = (pixelData: Uint8Array, srcWidth: number, srcHeight: number, x: number, y: number, cropWidth: number, cropHeight: number): Uint8Array => {
      let result = new Uint8Array(cropWidth * cropHeight * 4)
      for (let cy = 0; cy < cropHeight; cy++) {
        for (let cx = 0; cx < cropWidth; cx++) {
          let srcX = x + cx
          let srcY = y + cy
          if (srcX >= 0 && srcX < srcWidth && srcY >= 0 && srcY < srcHeight) {
            let srcOffset = (srcY * srcWidth + srcX) * 4
            let dstOffset = (cy * cropWidth + cx) * 4
            result[dstOffset] = pixelData[srcOffset]
            result[dstOffset + 1] = pixelData[srcOffset + 1]
            result[dstOffset + 2] = pixelData[srcOffset + 2]
            result[dstOffset + 3] = pixelData[srcOffset + 3]
          }
        }
      }
      return result
    }

    let croppedPixelData = cropImage(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height, 5, 5, 10, 10)
    hilog.info(0x0000, 'testTag', `Cropped image: 20x20 (5,5,10,10), size=${croppedPixelData.length}`)

    let rotateImage = (pixelData: Uint8Array, width: number, height: number, degrees: number): Uint8Array => {
      let result: Uint8Array
      if (degrees === 90 || degrees === 270) {
        result = new Uint8Array(width * height * 4)
        for (let y = 0; y < height; y++) {
          for (let x = 0; x < width; x++) {
            let srcOffset = (y * width + x) * 4
            let newX: number, newY: number
            if (degrees === 90) {
              newX = height - 1 - y
              newY = x
            } else {
              newX = y
              newY = width - 1 - x
            }
            let dstOffset = (newY * height + newX) * 4
            result[dstOffset] = pixelData[srcOffset]
            result[dstOffset + 1] = pixelData[srcOffset + 1]
            result[dstOffset + 2] = pixelData[srcOffset + 2]
            result[dstOffset + 3] = pixelData[srcOffset + 3]
          }
        }
      } else if (degrees === 180) {
        result = new Uint8Array(width * height * 4)
        for (let y = 0; y < height; y++) {
          for (let x = 0; x < width; x++) {
            let srcOffset = (y * width + x) * 4
            let newX = width - 1 - x
            let newY = height - 1 - y
            let dstOffset = (newY * width + newX) * 4
            result[dstOffset] = pixelData[srcOffset]
            result[dstOffset + 1] = pixelData[srcOffset + 1]
            result[dstOffset + 2] = pixelData[srcOffset + 2]
            result[dstOffset + 3] = pixelData[srcOffset + 3]
          }
        }
      } else {
        result = pixelData
      }
      return result
    }

    let rotatedPixelData = rotateImage(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height, 90)
    hilog.info(0x0000, 'testTag', `Rotated image 90deg: size=${rotatedPixelData.length}`)

    let flipImage = (pixelData: Uint8Array, width: number, height: number, horizontal: boolean): Uint8Array => {
      let result = new Uint8Array(pixelData.length)
      for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
          let srcOffset = (y * width + x) * 4
          let newX = horizontal ? width - 1 - x : x
          let newY = horizontal ? y : height - 1 - y
          let dstOffset = (newY * width + newX) * 4
          result[dstOffset] = pixelData[srcOffset]
          result[dstOffset + 1] = pixelData[srcOffset + 1]
          result[dstOffset + 2] = pixelData[srcOffset + 2]
          result[dstOffset + 3] = pixelData[srcOffset + 3]
        }
      }
      return result
    }

    let flippedPixelData = flipImage(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height, true)
    hilog.info(0x0000, 'testTag', `Flipped image: size=${flippedPixelData.length}`)

    let applyGaussianBlur = (pixelData: Uint8Array, width: number, height: number, radius: number): Uint8Array => {
      let result = new Uint8Array(pixelData.length)
      let kernel: number[] = []
      let sigma = radius / 3
      let sum = 0
      for (let i = -radius; i <= radius; i++) {
        let value = Math.exp(-(i * i) / (2 * sigma * sigma))
        kernel.push(value)
        sum += value
      }
      for (let i = 0; i < kernel.length; i++) {
        kernel[i] /= sum
      }
      for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
          let r = 0, g = 0, b = 0, a = 0
          for (let ky = -radius; ky <= radius; ky++) {
            for (let kx = -radius; kx <= radius; kx++) {
              let px = Math.min(width - 1, Math.max(0, x + kx))
              let py = Math.min(height - 1, Math.max(0, y + ky))
              let offset = (py * width + px) * 4
              let weight = kernel[ky + radius] * kernel[kx + radius]
              r += pixelData[offset] * weight
              g += pixelData[offset + 1] * weight
              b += pixelData[offset + 2] * weight
              a += pixelData[offset + 3] * weight
            }
          }
          let dstOffset = (y * width + x) * 4
          result[dstOffset] = Math.min(255, Math.max(0, r))
          result[dstOffset + 1] = Math.min(255, Math.max(0, g))
          result[dstOffset + 2] = Math.min(255, Math.max(0, b))
          result[dstOffset + 3] = Math.min(255, Math.max(0, a))
        }
      }
      return result
    }

    let blurredPixelData = applyGaussianBlur(simulatePixelData.data, simulatePixelData.width, simulatePixelData.height, 2)
    hilog.info(0x0000, 'testTag', `Blurred image: size=${blurredPixelData.length}`)

    hilog.info(0x0000, 'testTag', 'loadmoreImageTest part 3 completed')

    let testArrayBuffer = new ArrayBuffer(2048)
    let testDataView = new DataView(testArrayBuffer)
    for (let i = 0; i < 512; i++) {
      testDataView.setInt32(i * 4, i * 100)
    }

    let testInt8Array = new Int8Array(256)
    for (let i = 0; i < 256; i++) testInt8Array[i] = i % 128

    let testUint8Array = new Uint8Array(256)
    for (let i = 0; i < 256; i++) testUint8Array[i] = i

    let testInt16Array = new Int16Array(128)
    for (let i = 0; i < 128; i++) testInt16Array[i] = i * 100

    let testUint16Array = new Uint16Array(128)
    for (let i = 0; i < 128; i++) testUint16Array[i] = i * 100

    let testInt32Array = new Int32Array(64)
    for (let i = 0; i < 64; i++) testInt32Array[i] = i * 10000

    let testUint32Array = new Uint32Array(64)
    for (let i = 0; i < 64; i++) testUint32Array[i] = i * 100000

    let testFloat32Array = new Float32Array(64)
    for (let i = 0; i < 64; i++) testFloat32Array[i] = i * 1.5

    let testFloat64Array = new Float64Array(32)
    for (let i = 0; i < 32; i++) testFloat64Array[i] = i * 2.5

    let testBigInt64Array = new BigInt64Array(16)
    for (let i = 0; i < 16; i++) testBigInt64Array[i] = BigInt(i * 1000000)

    let testBigUint64Array = new BigUint64Array(16)
    for (let i = 0; i < 16; i++) testBigUint64Array[i] = BigInt(i * 1000000)

    hilog.info(0x0000, 'testTag', `Typed arrays: I8=${testInt8Array.length}, U8=${testUint8Array.length}, I16=${testInt16Array.length}, U16=${testUint16Array.length}, I32=${testInt32Array.length}, U32=${testUint32Array.length}, F32=${testFloat32Array.length}, F64=${testFloat64Array.length}, BI64=${testBigInt64Array.length}, BU64=${testBigUint64Array.length}`)

    let testDataViewOps = {
      getInt8: testDataView.getInt8(0),
      getUint8: testDataView.getUint8(0),
      getInt16: testDataView.getInt16(0),
      getUint16: testDataView.getUint16(0),
      getInt32: testDataView.getInt32(0),
      getUint32: testDataView.getUint32(0),
      getFloat32: testDataView.getFloat32(0),
      getFloat64: testDataView.getFloat64(0),
      setInt8: (() => { testDataView.setInt8(0, 100); return testDataView.getInt8(0) })(),
      setUint8: (() => { testDataView.setUint8(1, 200); return testDataView.getUint8(1) })(),
      setInt16: (() => { testDataView.setInt16(2, 30000); return testDataView.getInt16(2) })(),
      setUint16: (() => { testDataView.setUint16(4, 60000); return testDataView.getUint16(4) })(),
      setInt32: (() => { testDataView.setInt32(6, 100000); return testDataView.getInt32(6) })(),
      setUint32: (() => { testDataView.setUint32(10, 200000); return testDataView.getUint32(10) })(),
      setFloat32: (() => { testDataView.setFloat32(14, 3.14); return testDataView.getFloat32(14) })(),
      setFloat64: (() => { testDataView.setFloat64(18, 2.718281828); return testDataView.getFloat64(18) })()
    }
    hilog.info(0x0000, 'testTag', `DataView ops: ${JSON.stringify(testDataViewOps)}`)

    let testFunction = (param: number): string => {
      return `NetworkImageResult: ${param * 2}`
    }

    let testAsyncFunction = async (delay: number): Promise<string> => {
      return new Promise((resolve) => {
        setTimeout(() => {
          resolve(`NetworkImageDelayed: ${delay}ms`)
        }, delay)
      })
    }

    class NetworkImageInfo {
      private src: string
      private width: number
      private height: number
      private format: string
      private size: number
      constructor(src: string, width: number, height: number, format: string, size: number) {
        this.src = src
        this.width = width
        this.height = height
        this.format = format
        this.size = size
      }
      getSrc(): string { return this.src }
      getWidth(): number { return this.width }
      getHeight(): number { return this.height }
      getFormat(): string { return this.format }
      getSize(): number { return this.size }
      getAspectRatio(): number { return this.width / this.height }
      getDisplayName(): string {
        let parsed = parseUrl(this.src)
        let segments = parsed.path.split('/')
        return segments[segments.length - 1] || 'unknown'
      }
      setWidth(newWidth: number): void { this.width = newWidth }
      setHeight(newHeight: number): void { this.height = newHeight }
      setSize(newSize: number): void { this.size = newSize }
      incrementWidth(): number { return ++this.width }
      toString(): string { return `${this.src} ${this.width}x${this.height} ${this.format} ${this.size}B` }
    }

    let testImageInfo = new NetworkImageInfo('https://example.com/img/photo.png', 1920, 1080, 'PNG', 1024 * 1024)
    hilog.info(0x0000, 'testTag', `NetworkImageInfo: ${testImageInfo.toString()}, aspect=${testImageInfo.getAspectRatio().toFixed(2)}, name=${testImageInfo.getDisplayName()}`)

    interface NetworkImageLoadResult {
      id: number
      src: string
      width: number
      height: number
      componentWidth: number
      componentHeight: number
      loaded: boolean
      duration: number
      cached: boolean
      error: string
    }

    let testLoadResult: NetworkImageLoadResult = {
      id: 1,
      src: 'https://example.com/images/test.png',
      width: 800,
      height: 600,
      componentWidth: 400,
      componentHeight: 300,
      loaded: true,
      duration: 250,
      cached: false,
      error: ''
    }
    hilog.info(0x0000, 'testTag', `LoadResult: ${JSON.stringify(testLoadResult)}`)

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

    enum CacheStrategy {
      None = 'none',
      Memory = 'memory',
      Disk = 'disk',
      MemoryDisk = 'memory_disk'
    }

    let testInterpolationValue = ImageInterpolation.High
    let testRenderModeValue = ImageRenderMode.Original
    let testObjectFitValue = ImageObjectFit.Cover
    let testCacheStrategy = CacheStrategy.MemoryDisk
    hilog.info(0x0000, 'testTag', `Enums: interpolation=${testInterpolationValue}, renderMode=${testRenderModeValue}, objectFit=${testObjectFitValue}, cache=${testCacheStrategy}`)

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

    let testTuple: [string, number, boolean] = ['network_image_tuple', 789, true]
    let testUnionType: string | number | boolean = 'network_image_union_value'
    let testLiteralType: 'contain' | 'cover' | 'fill' = 'cover'
    let testNullableString: string | null = null
    let testOptionalNumber: number | undefined = undefined

    let testRestFunction = (...args: number[]): number => {
      return args.reduce((sum, current) => sum + current, 0)
    }

    let testDefaultValue = (param: string = 'default_network_image'): string => {
      return param
    }

    let testDestructuring = ({ src, width }: { src: string, width: number }): string => {
      return `${src}_${width}`
    }

    let testSpreadArray = [1, 2, 3]
    let testSpreadObject = { src: 'test.png', width: 100 }
    let testCombinedSpread = [...testSpreadArray, 4, 5, 6]
    let testCombinedObjectSpread = { ...testSpreadObject, height: 200 }

    let testTemplateString = `NetworkImageTemplate: ${testString} - ${testCounter}`
    let testRegex = /network_image_pattern_\d+/gi
    let testRegexMatch = testString.match(testRegex)
    let testDate = new Date()
    let testDateString = testDate.toISOString()
    let testJSONString = JSON.stringify(networkImageConfig)
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
    hilog.info(0x0000, 'testTag', `Math: ${JSON.stringify(testMathOperations)}`)

    let testStringOperations = {
      length: testString.length,
      charAt: testString.charAt(0),
      charCodeAt: testString.charCodeAt(0),
      concat: testString.concat('_suffix'),
      indexOf: testString.indexOf('Network'),
      lastIndexOf: testString.lastIndexOf('Network'),
      slice: testString.slice(0, 7),
      substring: testString.substring(0, 7),
      toLowerCase: testString.toLowerCase(),
      toUpperCase: testString.toUpperCase(),
      trim: '  network image  '.trim(),
      split: testString.split(' '),
      replace: testString.replace('Network', 'Cached'),
      includes: testString.includes('Network'),
      startsWith: testString.startsWith('Network'),
      endsWith: testString.endsWith('String'),
      repeat: 'img'.repeat(3),
      padStart: '5'.padStart(3, '0'),
      padEnd: '5'.padEnd(3, '0')
    }
    hilog.info(0x0000, 'testTag', `String ops: ${JSON.stringify(testStringOperations)}`)

    let testArrayOperations = {
      length: testArray.length,
      push: testArray.push('new_network_image_item'),
      pop: testArray.pop(),
      shift: testArray.shift(),
      unshift: testArray.unshift('first_network_image_item'),
      slice: testArray.slice(0, 5),
      splice: testArray.splice(0, 2),
      concat: testArray.concat(['new', 'network', 'images']),
      join: testArray.join(', '),
      indexOf: testArray.indexOf('NetworkImageItem_1'),
      lastIndexOf: testArray.lastIndexOf('NetworkImageItem_1'),
      includes: testArray.includes('NetworkImageItem_1'),
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
        hilog.info(0x0000, 'testTag', `NetworkImageForEach: ${index} - ${item}`)
      })
    }

    let testMapOperations = {
      size: testMap.size,
      set: testMap.set('new_net_img_key', 999),
      get: testMap.get('net_img_key_1'),
      has: testMap.has('net_img_key_1'),
      delete: testMap.delete('net_img_key_2'),
      clear: (() => { let m = new Map(testMap); m.clear(); return m.size })(),
      keys: Array.from(testMap.keys()),
      values: Array.from(testMap.values()),
      entries: Array.from(testMap.entries()),
      forEach: testMap.forEach((value, key) => {
        hilog.info(0x0000, 'testTag', `NetworkImageMap: ${key} - ${value}`)
      })
    }

    let testSetOperations = {
      size: testSet.size,
      add: testSet.add(100),
      has: testSet.has(1),
      delete: testSet.delete(2),
      clear: (() => { let s = new Set(testSet); s.clear(); return s.size })(),
      values: Array.from(testSet.values()),
      forEach: testSet.forEach((value) => {
        hilog.info(0x0000, 'testTag', `NetworkImageSet: ${value}`)
      })
    }

    let testObjectOperations = {
      keys: Object.keys(networkImageConfig),
      values: Object.values(networkImageConfig),
      entries: Object.entries(networkImageConfig),
      assign: Object.assign({}, networkImageConfig, { newProp: 'newNetworkImageValue' }),
      freeze: Object.freeze({ ...networkImageConfig }),
      seal: Object.seal({ ...networkImageConfig }),
      hasOwnProperty: networkImageConfig.hasOwnProperty('url'),
      propertyIsEnumerable: networkImageConfig.propertyIsEnumerable('url')
    }

    let testErrorHandling = {
      tryCatch: (() => {
        try {
          throw new Error('Network Image Load Error')
        } catch (error) {
          return (error as Error).message
        }
      })(),
      tryCatchFinally: (() => {
        try {
          throw new Error('Network Image Decode Error with Finally')
        } catch (error) {
          return (error as Error).message
        } finally {
          hilog.info(0x0000, 'testTag', 'Network image error finally block executed')
        }
      })(),
      customError: (() => {
        class NetworkImageLoadError extends Error {
          statusCode: number
          url: string
          constructor(message: string, statusCode: number, url: string) {
            super(message)
            this.name = 'NetworkImageLoadError'
            this.statusCode = statusCode
            this.url = url
          }
        }
        try {
          throw new NetworkImageLoadError('Failed to download network image', 404, 'https://example.com/missing.png')
        } catch (error) {
          let e = error as NetworkImageLoadError
          return `${e.message} (status=${e.statusCode}, url=${e.url})`
        }
      })()
    }
    hilog.info(0x0000, 'testTag', `Error handling: ${JSON.stringify(testErrorHandling)}`)

    hilog.info(0x0000, 'testTag', 'loadmoreImageTest part 4 completed')

    let testPromiseChains = (() => {
      return new Promise<string>((resolve) => {
        resolve('network_image_initial_value')
      })
      .then((value) => {
        return `${value}_downloaded`
      })
      .then((value) => {
        return `${value}_decoded`
      })
      .then((value) => {
        return `${value}_rendered`
      })
      .catch((error) => {
        return `error: ${(error as Error).message}`
      })
      .finally(() => {
        hilog.info(0x0000, 'testTag', 'Network image promise chain completed')
      })
    })()

    let testAsyncAwait = (async () => {
      let result1 = await Promise.resolve('network_image_loaded')
      let result2 = await Promise.resolve('network_image_decoded')
      let result3 = await Promise.resolve('network_image_rendered')
      return `${result1}_${result2}_${result3}`
    })()

    let testPromiseAll = Promise.all([
      Promise.resolve('network_image_png'),
      Promise.resolve('network_image_jpeg'),
      Promise.resolve('network_image_gif')
    ])

    let testPromiseRace = Promise.race([
      new Promise<string>((resolve) => setTimeout(() => resolve('slow_network_image'), 100)),
      new Promise<string>((resolve) => setTimeout(() => resolve('fast_network_image'), 50))
    ])

    let testPromiseAllSettled = Promise.allSettled([
      Promise.resolve('resolved_network_image1'),
      Promise.reject('rejected_network_image1'),
      Promise.resolve('resolved_network_image2')
    ])

    let testPromiseAny = Promise.any([
      Promise.reject('rejected_network_image1'),
      Promise.resolve('resolved_network_image1'),
      Promise.reject('rejected_network_image2')
    ])

    let testGenerators = (() => {
      function* networkImageIdGenerator(): Generator<number, void, unknown> {
        yield 1
        yield 2
        yield 3
        yield 4
        yield 5
      }
      let gen = networkImageIdGenerator()
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
      symbol: Symbol('network_image_symbol'),
      symbolFor: Symbol.for('global_network_image_symbol'),
      symbolKeyFor: Symbol.keyFor(Symbol.for('global_network_image_symbol')),
      symbolIterator: Symbol.iterator,
      symbolToString: Symbol('netimg').toString(),
      symbolDescription: Symbol('network_image_description').description
    }

    let testProxy = (() => {
      let target = {
        url: 'https://example.com/img.png',
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
      get: Reflect.get({ url: 'test.png', width: 200 }, 'url'),
      set: Reflect.set({ url: 'a.png' }, 'url', 'b.png'),
      has: Reflect.has({ url: 'test.png' }, 'url'),
      deleteProperty: Reflect.deleteProperty({ url: 'a.png', width: 100 }, 'url'),
      ownKeys: Reflect.ownKeys({ url: 'a.png', width: 100 }),
      apply: Reflect.apply(Math.max, undefined, [1, 2, 3]),
      construct: Reflect.construct(Date, [2024, 0, 1]),
      getPrototypeOf: Reflect.getPrototypeOf({}),
      setPrototypeOf: Reflect.setPrototypeOf({}, Array.prototype),
      isExtensible: Reflect.isExtensible({}),
      preventExtensions: Reflect.preventExtensions({}),
      getOwnPropertyDescriptor: Reflect.getOwnPropertyDescriptor({ url: 'img.png' }, 'url'),
      defineProperty: Reflect.defineProperty({}, 'url', { value: 'new.png', writable: true })
    }

    let testWeakMap = (() => {
      let wm = new WeakMap<object, string>()
      let key1 = {}
      let key2 = {}
      wm.set(key1, 'network_image_value1')
      wm.set(key2, 'network_image_value2')
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
      slice: testArrayBuffer.slice(0, 1024),
      byteLength: testArrayBuffer.byteLength
    }

    for (let i = 0; i < 50; i++) {
      hilog.info(0x0000, 'testTag', `Network image loop iteration ${i}`)
      hilog.info(0x0000, 'testTag', `NetworkImageCounter: ${testCounter}`)
      testCounter++
    }

    for (let i = 0; i < 30; i++) {
      for (let j = 0; j < 20; j++) {
        let nestedValue = i * j
        hilog.info(0x0000, 'testTag', `Network image nested loop: ${i}, ${j}, value: ${nestedValue}`)
      }
    }

    let testWhileLoop = 0
    while (testWhileLoop < 100) {
      hilog.info(0x0000, 'testTag', `Network image while loop iteration ${testWhileLoop}`)
      testWhileLoop++
    }

    let testDoWhileLoop = 0
    do {
      hilog.info(0x0000, 'testTag', `Network image do-while loop iteration ${testDoWhileLoop}`)
      testDoWhileLoop++
    } while (testDoWhileLoop < 50)

    for (let i = 0; i < testArray.length; i++) {
      if (i % 2 === 0) {
        hilog.info(0x0000, 'testTag', `Network image even index: ${i}, value: ${testArray[i]}`)
      } else if (i % 3 === 0) {
        hilog.info(0x0000, 'testTag', `Network image divisible by 3 index: ${i}, value: ${testArray[i]}`)
      } else {
        hilog.info(0x0000, 'testTag', `Network image other index: ${i}, value: ${testArray[i]}`)
      }
    }

    for (let i = 0; i < 200; i++) {
      switch (i % 10) {
        case 0: hilog.info(0x0000, 'testTag', `Network Image Case 0: ${i}`); break
        case 1: hilog.info(0x0000, 'testTag', `Network Image Case 1: ${i}`); break
        case 2: hilog.info(0x0000, 'testTag', `Network Image Case 2: ${i}`); break
        case 3: hilog.info(0x0000, 'testTag', `Network Image Case 3: ${i}`); break
        case 4: hilog.info(0x0000, 'testTag', `Network Image Case 4: ${i}`); break
        case 5: hilog.info(0x0000, 'testTag', `Network Image Case 5: ${i}`); break
        case 6: hilog.info(0x0000, 'testTag', `Network Image Case 6: ${i}`); break
        case 7: hilog.info(0x0000, 'testTag', `Network Image Case 7: ${i}`); break
        case 8: hilog.info(0x0000, 'testTag', `Network Image Case 8: ${i}`); break
        case 9: hilog.info(0x0000, 'testTag', `Network Image Case 9: ${i}`); break
        default: hilog.info(0x0000, 'testTag', `Network Image Default case: ${i}`); break
      }
    }

    try {
      for (let i = 0; i < 100; i++) {
        if (i === 50) {
          throw new Error(`Network image error at iteration ${i}`)
        }
        hilog.info(0x0000, 'testTag', `Network image try block iteration ${i}`)
      }
    } catch (error) {
      hilog.error(0x0000, 'testTag', `Caught network image error: ${(error as Error).message}`)
    } finally {
      hilog.info(0x0000, 'testTag', 'Network image finally block executed')
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
      hilog.info(0x0000, 'testTag', `Network image counter operations: ${testCounter}`)
    }

    for (let i = 0; i < 100; i++) {
      let bitwiseAnd = i & 0xFF
      let bitwiseOr = i | 0xFF
      let bitwiseXor = i ^ 0xFF
      let bitwiseNot = ~i
      let leftShift = i << 2
      let rightShift = i >> 2
      let unsignedRightShift = i >>> 2
      hilog.info(0x0000, 'testTag', `Network image bitwise: AND=${bitwiseAnd}, OR=${bitwiseOr}, XOR=${bitwiseXor}, NOT=${bitwiseNot}, LSH=${leftShift}, RSH=${rightShift}, URSH=${unsignedRightShift}`)
    }

    for (let i = 0; i < 100; i++) {
      let logicalAnd = i > 0 && i < 100
      let logicalOr = i < 0 || i > 100
      let logicalNot = !logicalAnd
      let nullishCoalescing = null ?? i
      let optionalChaining = networkImageConfig?.nested?.prop3?.deepProp
      hilog.info(0x0000, 'testTag', `Network image logical: AND=${logicalAnd}, OR=${logicalOr}, NOT=${logicalNot}, NC=${nullishCoalescing}, OC=${optionalChaining}`)
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
      hilog.info(0x0000, 'testTag', `Network image comparison: ${JSON.stringify(comparison)}`)
    }

    for (let i = 0; i < 100; i++) {
      let ternary = i % 2 === 0 ? 'network_image_even' : 'network_image_odd'
      let nestedTernary = i < 33 ? 'small_network_image' : i < 66 ? 'medium_network_image' : 'large_network_image'
      hilog.info(0x0000, 'testTag', `Network image ternary: ${ternary}, Nested: ${nestedTernary}`)
    }

    for (let i = 0; i < 100; i++) {
      let commaExpression = (testCounter++, testCounter++, testCounter)
      let groupingExpression = (i + 10) * 2
      hilog.info(0x0000, 'testTag', `Network image comma: ${commaExpression}, Grouping: ${groupingExpression}`)
    }

    for (let i = 0; i < 100; i++) {
      let typeOf = typeof i
      let instanceOf = testArray instanceof Array
      let inOperator = 'url' in networkImageConfig
      hilog.info(0x0000, 'testTag', `Network image typeof: ${typeOf}, Instanceof: ${instanceOf}, In: ${inOperator}`)
    }

    for (let i = 0; i < 100; i++) {
      let voidExpression = void i
      let deleteExpression = (() => {
        let obj = { prop: 'network_image_value' }
        delete obj.prop
        return 'prop' in obj
      })()
      hilog.info(0x0000, 'testTag', `Network image void: ${voidExpression}, Delete: ${deleteExpression}`)
    }

    hilog.info(0x0000, 'testTag', 'loadmoreImageTest part 5 completed')

    for (let i = 0; i < 100; i++) {
      let fibonacci = (() => {
        let a = 0, b = 1
        for (let j = 0; j < i; j++) {
          [a, b] = [b, a + b]
        }
        return a
      })()
      hilog.info(0x0000, 'testTag', `Network Image Fibonacci(${i}) = ${fibonacci}`)
    }

    for (let i = 0; i < 100; i++) {
      let factorial = (() => {
        let result = 1
        for (let j = 2; j <= i; j++) {
          result *= j
        }
        return result
      })()
      hilog.info(0x0000, 'testTag', `Network Image Factorial(${i}) = ${factorial}`)
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
      hilog.info(0x0000, 'testTag', `Network Image Is ${i} prime? ${isPrime}`)
    }

    for (let i = 0; i < 100; i++) {
      let gcd = ((a: number, b: number): number => {
        while (b !== 0) {
          [a, b] = [b, a % b]
        }
        return a
      })(i, 100)
      hilog.info(0x0000, 'testTag', `Network Image GCD(${i}, 100) = ${gcd}`)
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
      hilog.info(0x0000, 'testTag', `Network image binary search result: ${binarySearch}`)
    }

    let consoleOps = {
      log: (() => { console.log('Network image console log test'); return 'log' })(),
      info: (() => { console.info('Network image console info test'); return 'info' })(),
      warn: (() => { console.warn('Network image console warn test'); return 'warn' })(),
      error: (() => { console.error('Network image console error test'); return 'error' })(),
      debug: (() => { console.debug('Network image console debug test'); return 'debug' })(),
      trace: (() => { console.trace('Network image console trace test'); return 'trace' })(),
      table: (() => { console.table([{ url: 'a.png', size: 100 }, { url: 'b.png', size: 200 }]); return 'table' })(),
      dir: (() => { console.dir({ url: 'net.png', width: 100 }); return 'dir' })(),
      time: (() => { console.time('networkImageTimer'); return 'time' })(),
      timeEnd: (() => { console.timeEnd('networkImageTimer'); return 'timeEnd' })(),
      count: (() => { console.count('networkImageCount'); return 'count' })(),
      countReset: (() => { console.countReset('networkImageCount'); return 'countReset' })(),
      group: (() => { console.group('networkImageGroup'); return 'group' })(),
      groupEnd: (() => { console.groupEnd(); return 'groupEnd' })(),
      groupCollapsed: (() => { console.groupCollapsed('networkImageGroupCollapsed'); return 'groupCollapsed' })(),
      clear: (() => { console.clear(); return 'clear' })()
    }

    let testHilog = {
      debug: (() => { hilog.debug(0x0000, 'testTag', 'Network Image Hilog debug test'); return 'debug' })(),
      info: (() => { hilog.info(0x0000, 'testTag', 'Network Image Hilog info test'); return 'info' })(),
      warn: (() => { hilog.warn(0x0000, 'testTag', 'Network Image Hilog warn test'); return 'warn' })(),
      error: (() => { hilog.error(0x0000, 'testTag', 'Network Image Hilog error test'); return 'error' })(),
      fatal: (() => { hilog.fatal(0x0000, 'testTag', 'Network Image Hilog fatal test'); return 'fatal' })()
    }

    hilog.info(0x0000, 'testTag', 'loadmoreImageTest completed')
  }

  build() {
    NavDestination() {
      Column() {
        Button('Load Network Image Test')
          .onClick(() => {
            this.loadmoreImageTest()
          })
      }
    }
    .title('Image支持网络图片图片')
  }
}