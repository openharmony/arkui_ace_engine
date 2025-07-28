import router from '@ohos.router'

// GENERATED START
const TESTS: Map<number, string> = new Map([
    [0, "AlphabetIndexer"],
    [1, "Blank"],
    [2, "Button"],
    [3, "Checkbox"],
    [4, "CheckboxGroup"],
    [5, "Click"],
    [6, "Column"],
    [7, "ColumnSplit"],
    [8, "CustomComponentBox"],
    [9, "DataPanel"],
    [10, "DatePicker"],
    [11, "Divider"],
    [12, "Flex"],
    [13, "FormLink"],
    [14, "Gauge"],
    [15, "Grid"],
    [16, "GridCol"],
    [17, "GridItem"],
    [18, "GridRow"],
    [19, "Image"],
    [20, "ImageAnimator"],
    [21, "Line"],
    [22, "List"],
    [23, "ListItem"],
    [24, "ListItemGroup"],
    [25, "LoadingProgress"],
    [26, "Marquee"],
    [27, "Menu"],
    [28, "MenuItem"],
    [29, "MenuItemGroup"],
    [30, "NavDestination"],
    [31, "Navigation"],
    [32, "Navigator"],
    [33, "Panel"],
    [34, "Path"],
    [35, "PatternLock"],
    [36, "Progress"],
    [37, "QRCode"],
    [38, "Radio"],
    [39, "Rating"],
    [40, "Row"],
    [41, "RowSplit"],
    [42, "Scroll"],
    [43, "ScrollBar"],
    [44, "Search"],
    [45, "Select"],
    [46, "Shape"],
    [47, "SideBarContainer"],
    [48, "Slider"],
    [49, "Span"],
    [50, "Stack"],
    [51, "Swiper"],
    [52, "Tabs"],
    [53, "Text"],
    [54, "TextArea"],
    [55, "TextClock"],
    [56, "TextInput"],
    [57, "TextPicker"],
    [58, "TextTimer"],
    [59, "TimePicker"],
    [60, "Toggle"],
    [61, "Video"],
    [62, "Web"],
    [63, "XComponent"]
])
// GENERATED END

const INDEX = 0 // set manually

@Entry
@Component
struct Index {

    aboutToAppear() {
        router.pushUrl({
            url: `pages/tests/${TESTS.get(INDEX)}.test`
        })
    }

    build() {
        Column() {
        }
    }
}
