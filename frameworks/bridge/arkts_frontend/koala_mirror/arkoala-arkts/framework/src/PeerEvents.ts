/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { int32 } from "@koalaui/common"
import { bitsToPtr, ptrToBits, NativeString } from "@koalaui/interop"

// Must match ArkUIAPIEventKind in api.h.
export enum PeerEventKind {
    Invalid = 0,
    SinglePointerInput = 1,
    MultiPointerInput = 2,
    Callback = 3,
    ComponentAsyncEvent = 4,
    TextInput = 5,
    GestureAsyncEvent = 6,
    KeyInput = 7,
    MouseInput = 8,
}


const enum ArkUINodeType {
    ArkuiText = 1,
    ArkuiSpan,
    ArkuiImageSpan,
    ArkuiImage,
    ArkuiToggle,
    ArkuiLoadingProgress,
    ArkuiTextInput,
    ArkuiStack,
    ArkuiScroll,
    ArkuiList,
    ArkuiSwiper,
    ArkuiTextarea,
    ArkuiButton,
    ArkuiProgress,
    ArkuiCheckbox,
    ArkuiColumn,
    ArkuiRow,
    ArkuiFlex,
    ArkuiListItem,
    ArkuiTabs,
    ArkuiNavigator,
    ArkuiWeb,
    ArkuiSlider,
    ArkuiCanvas,
    ArkuiRadio,
    ArkuiGrid,
    ArkuiXcomponent,
    ArkuiSidebar,
    ArkuiRefresh,
    ArkuiRoot,
    ArkuiComponentRoot,
    ArkuiCustom,
    ArkuiNavigation,
    ArkuiCustomContainerBox,
    ArkuiListItemGroup,
    ArkuiDatePicker,
    ArkuiTimePicker,
    ArkuiTextPicker,
    ArkuiGridItem,
}

const ArkuiMaxEventNum = 1000

enum EventOffsets {
    Kind = 0,
    SubKind = 1,
    NodeId = 4
}

export enum PeerEnterKeyType {
    Go,
    Search,
    Send,
    Next,
    Done,
    PREVIOUS = 7,
    NEW_LINE = 8,
}

export interface PeerSubmitEvent {
    keepEditableState(): void;
    text: string;
}

export enum ComponentAsyncEventSubKind {
    //CommonEvents
    OnAppear = 0,
    OnDisappear = 1,
    OnTouch = 2,
    OnClick = 3,
    OnHover = 4,
    OnBlur = 5,
    OnKeyEvent = 6,
    OnMouse = 7,
    OnAreaChange = 8,
    OnVisibleAreaChange = 9,
    OnGesture = 10,
    OnFocus = 11,
    OnImageComplete = ArkuiMaxEventNum * ArkUINodeType.ArkuiImage,
    OnImageError = OnImageComplete + 1,
    //ComponentsEvents

    // List
    OnListScroll = ArkuiMaxEventNum * ArkUINodeType.ArkuiList,
    OnListScrollIndex = OnListScroll + 1,
    OnListScrollStart = OnListScroll + 2,
    OnListScrollStop = OnListScroll + 3,

    // Toggle
    OnToggleChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiToggle,

    // CheckBox
    OnCheckboxChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiCheckbox,

    // TextInput
    OnTextInputEditChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiTextInput,
    OnTextInputSubmit = OnTextInputEditChange + 1,
    OnTextInputChange = OnTextInputEditChange + 2,

    // TextArea
    OnTextareaEditChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiTextarea,
    OnTextareaSubmit = OnTextareaEditChange + 1,
    OnTextareaChange = OnTextareaEditChange + 2,

    // Swiper
    OnSwiperChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiSwiper,
    OnSwiperAnimationStart = OnSwiperChange + 1,
    OnSwiperAnimationEnd = OnSwiperChange + 2,
    OnSwiperGestureSwipe = OnSwiperChange + 3,

    // Scroll
    OnScroll = ArkuiMaxEventNum * ArkUINodeType.ArkuiScroll,
    OnScrollFrameBegin = OnScroll + 1,
    OnScrollStart = OnScroll + 2,
    OnScrollStop = OnScroll + 3,
    OnScrollEdge = OnScroll + 4,

    // Navigation
    OnNavBarStateChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiNavigation,
    NavDestination = OnNavBarStateChange + 1,

    // Tabs
    OnTabsChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiTabs,

    // Navigator
    OnNavigatorClick = ArkuiMaxEventNum * ArkUINodeType.ArkuiNavigator,

    // Web
    OnWebIntercept = ArkuiMaxEventNum * ArkUINodeType.ArkuiWeb,

    // Slider
    OnSliderChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiSlider,

    // Canvas
    OnCanvasReady = ArkuiMaxEventNum * ArkUINodeType.ArkuiCanvas,

    // Radio
    OnRadioChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiRadio,

    // Grid
    OnGridScroll = ArkuiMaxEventNum * ArkUINodeType.ArkuiGrid,
    OnGridStart = OnGridScroll + 1,
    OnGridStop = OnGridScroll + 2,

    // Sidebar
    OnSidebarChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiSidebar,

    // XComponent
    OnXComponentLoad = ArkuiMaxEventNum * ArkUINodeType.ArkuiXcomponent,
    OnXComponentDestroy = OnXComponentLoad + 1,

    // Refresh
    OnRefreshStateChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiRefresh,
    OnRefreshRefreshing = OnRefreshStateChange + 1,

    // DatePicker
    OnDatePickerDateChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiDatePicker,

    // TimePicker
    OnTimePickerChange = ArkuiMaxEventNum * ArkUINodeType.ArkuiTimePicker
}

export enum GestureAsyncEventSubKind {
    OnAction = 0,
    OnActionStart = 1,
    OnActionUpdate = 2,
    OnActionEnd = 3,
    OnActionCancel = 4
}

export class PeerEvent {
    public kind: number
    public nodeId: number

    static Kind = 0
    static NodeId = 1

    constructor(kind: number, nodeId: number) {
        this.kind = kind
        this.nodeId = nodeId
    }
    fromInt32Array(array: Int32Array): PeerEvent {
        return new PeerEvent(array[PeerEvent.Kind], array[PeerEvent.NodeId])
    }
    toInt32Array(): Int32Array {
        let result = new Int32Array(5)
        result[PeerEvent.Kind] = this.kind
        result[PeerEvent.NodeId] = this.nodeId
        return result
    }
}

export class AreaPosition {
    public width: number
    public height: number
    public x: number
    public y: number
    public globalX: number
    public globalY: number

    constructor(width: number, height: number, x: number, y: number, globalX: number, globalY: number) {
        this.width = width
        this.height = height
        this.x = x
        this.y = y
        this.globalX = globalX
        this.globalY = globalY
    }
}

export class AsyncComponentPeerEvent extends PeerEvent {
    public subKind: ComponentAsyncEventSubKind
    static SubKind = 16
    constructor(nodeId: number, subKind: ComponentAsyncEventSubKind) {
        super(PeerEventKind.ComponentAsyncEvent, nodeId)
        this.subKind = subKind
    }
    static fromInt32Array(array: Int32Array): AsyncComponentPeerEvent {
        return new AsyncComponentPeerEvent(
            array[AsyncComponentPeerEvent.NodeId],
            array[AsyncComponentPeerEvent.SubKind]
        )
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(17)
        result[AsyncComponentPeerEvent.Kind] = this.kind
        result[AsyncComponentPeerEvent.NodeId] = this.nodeId
        result[AsyncComponentPeerEvent.SubKind] = this.subKind
        return result
    }
}

export class RefreshStateChangePeerEvent extends AsyncComponentPeerEvent {
    public state: number
    static State = 6
    constructor(nodeId: number, state: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnRefreshStateChange)
        this.state = state
    }
    static fromInt32Array(array: Int32Array): RefreshStateChangePeerEvent {
        return new RefreshStateChangePeerEvent(
            array[RefreshStateChangePeerEvent.NodeId],
            array[RefreshStateChangePeerEvent.State]
        )
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(5)
        result[RefreshStateChangePeerEvent.Kind] = this.kind
        result[RefreshStateChangePeerEvent.SubKind] = this.subKind
        result[RefreshStateChangePeerEvent.NodeId] = this.nodeId
        result[RefreshStateChangePeerEvent.State] = this.state
        return result
    }
}

export class OnRefreshingPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnRefreshRefreshing)
    }
}

export class OnRadioChangePeerEvent extends AsyncComponentPeerEvent {
    public isChecked: boolean
    static Checked = 6
    constructor(nodeId: number, isChecked: boolean) {
        super(nodeId, ComponentAsyncEventSubKind.OnRadioChange)
        this.isChecked = isChecked
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(6)
        result[OnRadioChangePeerEvent.Kind] = this.kind
        result[OnRadioChangePeerEvent.NodeId] = this.nodeId
        result[OnRadioChangePeerEvent.SubKind] = this.subKind
        result[OnRadioChangePeerEvent.Checked] = this.isChecked ? 1 : 0
        return result
    }
}

export class ImageCompletePeerEvent extends AsyncComponentPeerEvent {
    public width: number
    public height: number
    public componentWidth: number
    public componentHeight: number
    public loadingStatus: number
    public contentWidth: number
    public contentHeight: number
    public contentOffsetX: number
    public contentOffsetY: number

    static Width = 6
    static Height = 7
    static ComponentWidth = 8
    static ComponentHeight = 9
    static LoadingStatus = 10
    static ContentWidth = 11
    static ContentHeight = 12
    static ContentOffsetX = 12
    static ContentOffsetY = 13

    constructor(nodeId: number, width: number, height: number, componentWidth: number, componentHeight: number,
        loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnImageComplete)
        this.width = width
        this.height = height
        this.componentWidth = componentWidth
        this.componentHeight = componentHeight
        this.loadingStatus = loadingStatus
        this.contentWidth = contentWidth
        this.contentHeight = contentHeight
        this.contentOffsetX = contentOffsetX
        this.contentOffsetY = contentOffsetY
    }
    static fromInt32Array(array: Int32Array): ImageCompletePeerEvent {
        return new ImageCompletePeerEvent(
            array[ImageCompletePeerEvent.NodeId],
            array[ImageCompletePeerEvent.Width],
            array[ImageCompletePeerEvent.Height],
            array[ImageCompletePeerEvent.ComponentWidth],
            array[ImageCompletePeerEvent.ComponentHeight],
            array[ImageCompletePeerEvent.LoadingStatus],
            array[ImageCompletePeerEvent.ContentWidth],
            array[ImageCompletePeerEvent.ContentHeight],
            array[ImageCompletePeerEvent.ContentOffsetX],
            array[ImageCompletePeerEvent.ContentOffsetY],
        )
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(14)
        result[ImageCompletePeerEvent.Kind] = this.kind
        result[ImageCompletePeerEvent.NodeId] = this.nodeId
        result[ImageCompletePeerEvent.SubKind] = this.subKind
        result[ImageCompletePeerEvent.Width] = this.width
        result[ImageCompletePeerEvent.Height] = this.height
        result[ImageCompletePeerEvent.ComponentWidth] = this.componentWidth
        result[ImageCompletePeerEvent.ComponentHeight] = this.componentHeight
        result[ImageCompletePeerEvent.LoadingStatus] = this.loadingStatus
        result[ImageCompletePeerEvent.ContentWidth] = this.contentWidth
        result[ImageCompletePeerEvent.ContentHeight] = this.contentHeight
        result[ImageCompletePeerEvent.ContentOffsetX] = this.contentOffsetX
        result[ImageCompletePeerEvent.ContentOffsetY] = this.contentOffsetY
        return result
    }
}
export class ImageErrorPeerEvent extends AsyncComponentPeerEvent {
    public componentWidth: number
    public componentHeight: number
    public message: string

    static StringLow = 6
    static StringHigh = 7
    static ComponentWidth = 8
    static ComponentHeight = 9

    constructor(nodeId: number, componentWidth: number, componentHeight: number, message: string) {
        super(nodeId, ComponentAsyncEventSubKind.OnImageError)
        this.componentWidth = componentWidth
        this.componentHeight = componentHeight
        this.message = message
    }
    static fromInt32Array(array: Int32Array): ImageErrorPeerEvent {
        let errorMessage = new NativeString(bitsToPtr(array, ImageErrorPeerEvent.StringLow))
        return new ImageErrorPeerEvent(
            array[ImageErrorPeerEvent.NodeId],
            array[ImageErrorPeerEvent.ComponentWidth],
            array[ImageErrorPeerEvent.ComponentHeight],
            errorMessage.toString())
    }
    override toInt32Array(): Int32Array {
        let nativeStringPtr = NativeString.Make(this.message).release()
        let result = new Int32Array(5)
        result[ImageErrorPeerEvent.Kind] = this.kind
        result[ImageErrorPeerEvent.NodeId] = this.nodeId
        result[ImageErrorPeerEvent.SubKind] = this.subKind
        let bits = ptrToBits(nativeStringPtr)!
        result[ImageErrorPeerEvent.StringLow] = bits[0]
        result[ImageErrorPeerEvent.StringHigh] = bits[1]
        return result
    }
}

export class BlurPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnBlur)
    }
}

export class HoverPeerEvent extends AsyncComponentPeerEvent {
    public isHover: boolean
    static IsHover = 6
    constructor(nodeId: number, isHover: boolean) {
        super(nodeId, ComponentAsyncEventSubKind.OnHover)
        this.isHover = isHover
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(4)
        result[HoverPeerEvent.Kind] = this.kind
        result[HoverPeerEvent.NodeId] = this.nodeId
        result[HoverPeerEvent.SubKind] = this.subKind
        result[HoverPeerEvent.IsHover] = this.isHover ? 1 : 0
        return result
    }
}

export class CanvasReadyPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnCanvasReady)
    }
    static fromInt32Array(array: Int32Array): CanvasReadyPeerEvent {
        return new CanvasReadyPeerEvent(
            array[CanvasReadyPeerEvent.NodeId]
        )
    }
}
export class ListScrollStartPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnListScrollStart)
    }
}

export class ListScrollStopPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnListScrollStop)
    }
}

export class KeyPeerEvent extends PeerEvent {
    public type: number
    public keyCode: number
    public keyText: string
    public keySource: number
    public deviceId: number
    public metaKey: number
    public timestamp: number
    public intentionCode: number
    public stopPropagation: () => void
    public getModifierKeyState: (keys: string[]) => boolean

    constructor(
        nodeId: number,
        type: number,
        keyCode: number,
        keyText: string,
        keySource: number,
        deviceId: number,
        metaKey: number,
        timestamp: number,
        intentionCode: number,
        stopPropagation?: () => void,
        getModifierKeyState?: (keys: string[]) => boolean
    ) {
        super(PeerEventKind.KeyInput, nodeId)
        this.type = type
        this.keyCode = keyCode
        this.keyText = keyText
        this.keySource = keySource
        this.deviceId = deviceId
        this.metaKey = metaKey
        this.timestamp = timestamp
        this.intentionCode = intentionCode
        this.stopPropagation = stopPropagation ?? (() => {})
        this.getModifierKeyState = getModifierKeyState ?? ((keys: string[]) => { return false })
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(9)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.type
        result[3] = this.keyCode
        result[4] = this.keySource
        result[5] = this.deviceId
        result[6] = this.metaKey
        result[7] = this.timestamp
        result[8] = this.intentionCode
        return result
    }
}

export class MousePeerEvent extends PeerEvent {
    public button: number
    public action: number
    public displayX: number
    public displayY: number
    public windowX: number
    public windowY: number
    public screenX: number
    public screenY: number
    public x: number
    public y: number
    public stopPropagation: () => void

    static Button = 6
    static Action = 7
    static DisplayX = 8
    static DisplayY = 9
    static WindowX = 10
    static WindowY = 11
    static ScreenX = 12
    static ScreenY = 13
    static X = 14
    static Y = 15

    constructor(
        nodeId: number,
        button: number,
        action: number,
        displayX: number,
        displayY: number,
        windowX: number,
        windowY: number,
        screenX: number,
        screenY: number,
        x: number,
        y: number,
        stopPropagation?: () => void
    ) {
        super(PeerEventKind.SinglePointerInput, nodeId)
        this.button = button
        this.action = action
        this.displayX = displayX
        this.displayY = displayY
        this.windowX = windowX
        this.windowY = windowY
        this.screenX = screenX
        this.screenY = screenY
        this.x = x
        this.y = y
        this.stopPropagation = stopPropagation ?? (() => {})
    }
    static fromInt32Array(array: Int32Array): MousePeerEvent {
        return new MousePeerEvent(
            array[MousePeerEvent.NodeId],
            array[MousePeerEvent.Button],
            array[MousePeerEvent.Action],
            array[MousePeerEvent.DisplayX],
            array[MousePeerEvent.DisplayY],
            array[MousePeerEvent.WindowX],
            array[MousePeerEvent.WindowY],
            array[MousePeerEvent.ScreenX],
            array[MousePeerEvent.ScreenY],
            array[MousePeerEvent.X],
            array[MousePeerEvent.Y]
        )
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(16)
        result[MousePeerEvent.Kind] = this.kind
        result[MousePeerEvent.NodeId] = this.nodeId
        result[MousePeerEvent.Button] = this.button
        result[MousePeerEvent.Action] = this.action
        result[MousePeerEvent.DisplayX] = this.displayX
        result[MousePeerEvent.DisplayY] = this.displayY
        result[MousePeerEvent.WindowX] = this.windowX
        result[MousePeerEvent.WindowY] = this.windowY
        result[MousePeerEvent.ScreenX] = this.screenX
        result[MousePeerEvent.ScreenY] = this.screenY
        result[MousePeerEvent.X] = this.x
        result[MousePeerEvent.Y] = this.y
        return result
    }
}

export class SinglePointerPeerEvent extends PeerEvent {
    static X = 4
    static Y = 5
    static State = 6

    public x: number
    public y: number
    public state: number

    constructor(nodeId: number, x: number, y: number, state: number) {
        super(PeerEventKind.SinglePointerInput, nodeId)
        this.state = state
        this.y = y
        this.x = x
    }
    static fromInt32Array(array: Int32Array): SinglePointerPeerEvent {
        return new SinglePointerPeerEvent(
            array[SinglePointerPeerEvent.NodeId],
            array[SinglePointerPeerEvent.X],
            array[SinglePointerPeerEvent.Y],
            array[SinglePointerPeerEvent.State]
        )
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(10)
        result[SinglePointerPeerEvent.Kind] = this.kind
        result[SinglePointerPeerEvent.NodeId] = this.nodeId
        result[SinglePointerPeerEvent.X] = this.x
        result[SinglePointerPeerEvent.Y] = this.y
        result[SinglePointerPeerEvent.State] = this.state
        return result
    }
}

export class MultiPointerPeerEvent extends PeerEvent {
    public xs: Int32Array
    public ys: Int32Array
    public status: Int32Array

    constructor(nodeId: number, xs: Int32Array, ys: Int32Array, status: Int32Array) {
        super(PeerEventKind.MultiPointerInput, nodeId)
        this.status = status
        this.ys = ys
        this.xs = xs
    }
    static fromInt32Array(array: Int32Array): MultiPointerPeerEvent {
        throw new Error()
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(34)
        result[0] = this.kind
        result[1] = this.nodeId
        let count = this.xs.length
        result[2] = count
        for (let i = 0; i < count; i++) {
            result[3 + i] = this.xs[i]
        }
        for (let i = 0; i < count; i++) {
            result[13 + i] = this.ys[i]
        }
        for (let i = 0; i < count; i++) {
            result[23 + i] = this.status[i]
        }
        return result
    }
}

export class TextInputEvent extends PeerEvent {
    public text: string

    static TextLow = 6
    static TextHigh = 7

    constructor(nodeId: number, text: string) {
        super(PeerEventKind.TextInput, nodeId)
        this.text = text
    }
    static fromInt32Array(array: Int32Array): TextInputEvent {
        return new TextInputEvent(
            array[TextInputEvent.NodeId],
            new NativeString(bitsToPtr(array, TextInputEvent.TextLow)).toString()
        )
    }
    override toInt32Array(): Int32Array {
        let nativeStringPtr = NativeString.Make(this.text).release()
        let result = new Int32Array(8)
        result[TextInputEvent.Kind] = this.kind
        result[TextInputEvent.NodeId] = this.nodeId
        let bits = ptrToBits(nativeStringPtr)!
        result[TextInputEvent.TextLow] = bits[0]
        result[TextInputEvent.TextHigh] = bits[1]
        return result
    }
}

export class XComponentLoadPeerEvent extends AsyncComponentPeerEvent {
    public id: string
    constructor(nodeId: number, id: string) {
        super(nodeId, ComponentAsyncEventSubKind.OnXComponentLoad)
        this.id = id
    }

    override toInt32Array(): Int32Array {
        let nativeStringPtr = NativeString.Make(this.id).release()
        let result = new Int32Array(4)
        result[0] = this.kind
        result[1] = this.nodeId
        let bits = ptrToBits(nativeStringPtr)!
        result[2] = bits[0]
        result[3] = bits[1]
        return result
    }
}

export class XComponentDestroyPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnXComponentDestroy)
    }
}

export class CallbackPeerEvent extends PeerEvent {
    static currentId = 1
    static callbackById = new Map<number, CallbackPeerEvent>()

    public id: number
    public callback: (args: Int32Array) => void
    public autoDisposable = true

    static Id = 4
    static NumArgs = 5
    static ContinuationId = 6

    constructor(callback: (args: Int32Array) => void, autoDisposable: boolean = true) {
        super(PeerEventKind.Callback, 0)
        this.autoDisposable = autoDisposable
        this.callback = callback
        this.id = CallbackPeerEvent.currentId++
        this.callback = callback
        this.autoDisposable = autoDisposable
        CallbackPeerEvent.callbackById.set(this.id, this)
    }

    static byId(id: number): CallbackPeerEvent | undefined {
        return CallbackPeerEvent.callbackById.get(id)
    }

    static wrap(callback: (args: Int32Array) => void, autoDisposable: boolean = true): number {
        return new CallbackPeerEvent(callback, autoDisposable).id
    }

    dispose() {
        CallbackPeerEvent.callbackById.delete(this.id)
    }

    invoke(continuationId: number, args: Int32Array) {
        this.callback(args)
    }
}

export class AsyncGesturePeerEvent extends PeerEvent {
    public subKind: GestureAsyncEventSubKind
    constructor(nodeId: number, subKind: GestureAsyncEventSubKind) {
        super(PeerEventKind.GestureAsyncEvent, nodeId)
        this.subKind = subKind
    }
}

export class AppearPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnAppear)
    }
}

export class DisappearPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnDisappear)
    }
}

export class SwiperChangePeerEvent extends AsyncComponentPeerEvent {
    public index: int32
    constructor(nodeId: number, index: int32) {
        super(nodeId, ComponentAsyncEventSubKind.OnSwiperChange)
        this.index = index
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(4)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.index
        return result
    }
}

export class TabsChangePeerEvent extends AsyncComponentPeerEvent {
    public index: int32
    constructor(nodeId: number, index: int32) {
        super(nodeId, ComponentAsyncEventSubKind.OnTabsChange)
        this.index = index
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(4)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.index
        return result
    }
}

export class VisibleAreaChangePeerEvent extends AsyncComponentPeerEvent {
    public isVisible: boolean
    public currentRatio: number

    constructor(nodeId: number, isVisible: boolean, currentRatio: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnVisibleAreaChange)
        this.currentRatio = currentRatio
        this.isVisible = isVisible
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(5)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.isVisible ? 1 : 0
        result[4] = this.currentRatio
        return result
    }
}

export class ScrollIndexPeerEvent extends AsyncComponentPeerEvent {
    public first: number
    public last: number


    constructor(nodeId: number, first: number, last: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnListScrollIndex)
        this.first = first
        this.last = last
    }

    override toInt32Array(): Int32Array {
        let result = new Int32Array(5)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.first
        result[4] = this.last
        return result
    }
}

export class GesturePeerEvent extends AsyncGesturePeerEvent {
    public gestureEvent: Int32Array
    constructor(nodeId: number, subKind: GestureAsyncEventSubKind, gestureEvent: Int32Array) {
        super(nodeId,  subKind)
        this.gestureEvent = gestureEvent;
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(3);
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        return result
    }
}

export class NavigatorClickPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnNavigatorClick)
    }
}

export class SwiperAnimationPeerEvent extends AsyncComponentPeerEvent {
    public index: number
    public targetIndex: number
    public currentOffset: number
    public targetOffset: number
    public velocity: number

    static Index = 6
    static TargetIndex = 7
    static CurrentOffset = 8
    static TargetOffset = 9
    static Velocity = 10

    constructor(
        nodeId: number,
        index: number,
        targetIndex: number,
        currentOffset: number,
        targetOffset: number,
        velocity: number
    ) {
        super(nodeId, ComponentAsyncEventSubKind.OnListScrollIndex)
        this.index = index
        this.targetIndex = targetIndex
        this.currentOffset = currentOffset
        this.targetOffset = targetOffset
        this.velocity = velocity
    }
    static fromInt32Array(array: Int32Array): SwiperAnimationPeerEvent {
        return new SwiperAnimationPeerEvent(
            array[SwiperAnimationPeerEvent.NodeId],
            array[SwiperAnimationPeerEvent.Index],
            array[SwiperAnimationPeerEvent.TargetIndex],
            array[SwiperAnimationPeerEvent.CurrentOffset],
            array[SwiperAnimationPeerEvent.TargetOffset],
            array[SwiperAnimationPeerEvent.Velocity]
        )
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(8)
        result[SwiperAnimationPeerEvent.Kind] = this.kind
        result[SwiperAnimationPeerEvent.SubKind] = this.subKind
        result[SwiperAnimationPeerEvent.NodeId] = this.nodeId
        result[SwiperAnimationPeerEvent.Index] = this.index
        result[SwiperAnimationPeerEvent.TargetIndex] = this.targetIndex
        result[SwiperAnimationPeerEvent.CurrentOffset] = this.currentOffset
        result[SwiperAnimationPeerEvent.TargetOffset] = this.targetOffset
        result[SwiperAnimationPeerEvent.Velocity] = this.velocity
        return result
    }
}

export class SliderChangePeerEvent extends AsyncComponentPeerEvent {
    public value: number
    public mode: number
    constructor(nodeId: number, value: number, mode: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnSwiperChange)
        this.value = value
        this.mode = mode
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(5)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.value
        result[4] = this.mode
        return result
    }
}
export class ListScrollPeerEvent extends AsyncComponentPeerEvent {
    public scrollOffset: number
    public scrollState: number

    static ScrollOffset = 6
    static ScrollState = 7

    constructor(nodeId: number, scrollOffset: number, scrollState: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnListScroll)
        this.scrollOffset = scrollOffset
        this.scrollState = scrollState
    }
    static fromInt32Array(array: Int32Array): ListScrollPeerEvent {
        return new ListScrollPeerEvent(
            array[ListScrollPeerEvent.NodeId],
            array[ListScrollPeerEvent.ScrollOffset],
            array[ListScrollPeerEvent.ScrollState]
        )
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(5)
        result[ListScrollPeerEvent.Kind] = this.kind
        result[ListScrollPeerEvent.NodeId] = this.nodeId
        result[ListScrollPeerEvent.SubKind] = this.subKind
        result[ListScrollPeerEvent.ScrollOffset] = this.scrollOffset
        result[ListScrollPeerEvent.ScrollState] = this.scrollState
        return result
    }
}

export class AreaChangePeerEvent extends AsyncComponentPeerEvent {

    public oldValue: AreaPosition
    public newValue: AreaPosition

    constructor(nodeId: number, oldValue: AreaPosition, newValue: AreaPosition) {
        super(nodeId, ComponentAsyncEventSubKind.OnSwiperChange)
        this.oldValue = oldValue
        this.newValue = newValue
    }
    static fromInt32Array(array: Int32Array): AreaChangePeerEvent {
        throw new Error()
    }
    override toInt32Array(): Int32Array {
        let result = new Int32Array(3)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        return result
    }
}
export class ListScrollIndexPeerEvent extends AsyncComponentPeerEvent {
    public start: number
    public end: number
    public center: number

    constructor(nodeId: number, start: number, end: number, center: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnListScrollIndex)
        this.start = start
        this.end = end
        this.center = center
    }

    override toInt32Array(): Int32Array {
        let result = new Int32Array(6)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.start
        result[4] = this.end
        result[5] = this.center
        return result
    }
}

export class GridScrollPeerEvent extends AsyncComponentPeerEvent {
    public scrollOffset: number
    public scrollState: number

    constructor(nodeId: number, scrollOffset: number, scrollState: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnGridScroll)
        this.scrollOffset = scrollOffset
        this.scrollState = scrollState
    }

    override toInt32Array(): Int32Array {
        let result = new Int32Array(5)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.scrollOffset
        result[4] = this.scrollState
        return result
    }
}

export class GridScrollStartPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnGridStart)
    }
}

export class GridScrollStopPeerEvent extends AsyncComponentPeerEvent {
    constructor(nodeId: number) {
        super(nodeId, ComponentAsyncEventSubKind.OnGridStop)
    }
}

export class SideBarChangePeerEvent extends AsyncComponentPeerEvent {
    public isChanged: boolean
    constructor(nodeId: number,changed: boolean) {
        super(nodeId, ComponentAsyncEventSubKind.OnSidebarChange)
        this.isChanged = changed
    }

    override toInt32Array(): Int32Array {
        let result = new Int32Array(4)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.isChanged ? 1 : 0
        return result
    }
}

export class NavBarStateChangePeerEvent extends AsyncComponentPeerEvent {
    public onVisible: boolean
    constructor(nodeId: number, onVisible: boolean) {
        super(nodeId, ComponentAsyncEventSubKind.OnNavBarStateChange)
        this.onVisible = onVisible
    }

    override toInt32Array(): Int32Array {
        let result = new Int32Array(4)
        result[0] = this.kind
        result[1] = this.nodeId
        result[2] = this.subKind
        result[3] = this.onVisible ? 1 : 0
        return result
    }
}

export class NavDestinationPeerEvent extends AsyncComponentPeerEvent {
    public name: string
    public param: unknown
    constructor(nodeId: number, name: string, param: unknown) {
        super(nodeId, ComponentAsyncEventSubKind.NavDestination)
        this.name = name
        this.param = param
    }

    override toInt32Array(): Int32Array {
        let nativeStringPtr = NativeString.Make(this.name).release()
        let result = new Int32Array(4)
        result[0] = this.kind
        result[1] = this.nodeId
        let bits = ptrToBits(nativeStringPtr)!
        result[2] = bits[0]
        result[3] = bits[1]
        return result
    }
}
