import { int32, float32 } from "@koalaui/common"
export namespace curves {
    export enum Curve {
        LINEAR = 0,
        Linear = 0,
        EASE = 1,
        Ease = 1,
        EASE_IN = 2,
        EaseIn = 2,
        EASE_OUT = 3,
        EaseOut = 3,
        EASE_IN_OUT = 4,
        EaseInOut = 4,
        FAST_OUT_SLOW_IN = 5,
        FastOutSlowIn = 5,
        LINEAR_OUT_SLOW_IN = 6,
        LinearOutSlowIn = 6,
        FAST_OUT_LINEAR_IN = 7,
        FastOutLinearIn = 7,
        EXTREME_DECELERATION = 8,
        ExtremeDeceleration = 8,
        SHARP = 9,
        Sharp = 9,
        RHYTHM = 10,
        Rhythm = 10,
        SMOOTH = 11,
        Smooth = 11,
        FRICTION = 12,
        Friction = 12
    }
}
export namespace uniformTypeDescriptor {
    export enum UniformDataType {
        ENTITY = "general.entity",
        OBJECT = "general.object",
        COMPOSITE_OBJECT = "general.composite-object",
        TEXT = "general.text",
        PLAIN_TEXT = "general.plain-text",
        HTML = "general.html",
        HYPERLINK = "general.hyperlink",
        XML = "general.xml",
        XHTML = "general.xhtml",
        RSS = "general.rss",
        SMIL = "com.real.smil",
        SOURCE_CODE = "general.source-code",
        SCRIPT = "general.script",
        SHELL_SCRIPT = "general.shell-script",
        CSH_SCRIPT = "general.csh-script",
        PERL_SCRIPT = "general.perl-script",
        PHP_SCRIPT = "general.php-script",
        PYTHON_SCRIPT = "general.python-script",
        RUBY_SCRIPT = "general.ruby-script",
        TYPE_SCRIPT = "general.type-script",
        JAVA_SCRIPT = "general.java-script",
        CSS = "general.css",
        C_HEADER = "general.c-header",
        C_SOURCE = "general.c-source",
        C_PLUS_PLUS_HEADER = "general.c-plus-plus-header",
        C_PLUS_PLUS_SOURCE = "general.c-plus-plus-source",
        JAVA_SOURCE = "general.java-source",
        TEX = "general.tex",
        MARKDOWN = "general.markdown",
        ASC_TEXT = "general.asc-text",
        RICH_TEXT = "general.rich-text",
        DELIMITED_VALUES_TEXT = "general.delimited-values-text",
        COMMA_SEPARATED_VALUES_TEXT = "general.comma-separated-values-text",
        TAB_SEPARATED_VALUES_TEXT = "general.tab-separated-values-text",
        EBOOK = "general.ebook",
        EPUB = "general.epub",
        AZW = "com.amazon.azw",
        AZW3 = "com.amazon.azw3",
        KFX = "com.amazon.kfx",
        MOBI = "com.amazon.mobi",
        MEDIA = "general.media",
        IMAGE = "general.image",
        JPEG = "general.jpeg",
        PNG = "general.png",
        RAW_IMAGE = "general.raw-image",
        TIFF = "general.tiff",
        BMP = "com.microsoft.bmp",
        ICO = "com.microsoft.ico",
        PHOTOSHOP_IMAGE = "com.adobe.photoshop-image",
        AI_IMAGE = "com.adobe.illustrator.ai-image",
        FAX = "general.fax",
        JFX_FAX = "com.j2.jfx-fax",
        EFX_FAX = "com.js.efx-fax",
        XBITMAP_IMAGE = "general.xbitmap-image",
        GIF = "general.gif",
        TGA_IMAGE = "com.truevision.tga-image",
        SGI_IMAGE = "com.sgi.sgi-image",
        OPENEXR_IMAGE = "com.ilm.openexr-image",
        FLASHPIX_IMAGE = "com.kodak.flashpix.image",
        WORD_DOC = "com.microsoft.word.doc",
        EXCEL = "com.microsoft.excel.xls",
        PPT = "com.microsoft.powerpoint.ppt",
        WORD_DOT = "com.microsoft.word.dot",
        POWERPOINT_PPS = "com.microsoft.powerpoint.pps",
        POWERPOINT_POT = "com.microsoft.powerpoint.pot",
        EXCEL_XLT = "com.microsoft.excel.xlt",
        VISIO_VSD = "com.microsoft.visio.vsd",
        PDF = "com.adobe.pdf",
        POSTSCRIPT = "com.adobe.postscript",
        ENCAPSULATED_POSTSCRIPT = "com.adobe.encapsulated-postscript",
        VIDEO = "general.video",
        AVI = "general.avi",
        MPEG = "general.mpeg",
        MPEG4 = "general.mpeg-4",
        VIDEO_3GPP = "general.3gpp",
        VIDEO_3GPP2 = "general.3gpp2",
        TS = "general.ts",
        MPEGURL_VIDEO = "general.mpegurl-video",
        WINDOWS_MEDIA_WM = "com.microsoft.windows-media-wm",
        WINDOWS_MEDIA_WMV = "com.microsoft.windows-media-wmv",
        WINDOWS_MEDIA_WMP = "com.microsoft.windows-media-wmp",
        WINDOWS_MEDIA_WVX = "com.microsoft.windows-media-wvx",
        WINDOWS_MEDIA_WMX = "com.microsoft.windows-media-wmx",
        REALMEDIA = "com.real.realmedia",
        MATROSKA_VIDEO = "org.matroska.mkv",
        FLASH = "com.adobe.flash",
        AUDIO = "general.audio",
        AAC = "general.aac",
        AIFF = "general.aiff",
        ALAC = "general.alac",
        FLAC = "general.flac",
        MP3 = "general.mp3",
        OGG = "general.ogg",
        PCM = "general.pcm",
        WINDOWS_MEDIA_WMA = "com.microsoft.windows-media-wma",
        WAVEFORM_AUDIO = "com.microsoft.waveform-audio",
        WINDOWS_MEDIA_WAX = "com.microsoft.windows-media-wax",
        AU_AUDIO = "general.au-audio",
        AIFC_AUDIO = "general.aifc-audio",
        MPEGURL_AUDIO = "general.mpegurl-audio",
        MPEG_4_AUDIO = "general.mpeg-4-audio",
        MP2 = "general.mp2",
        MPEG_AUDIO = "general.mpeg-audio",
        ULAW_AUDIO = "general.ulaw-audio",
        SD2_AUDIO = "com.digidesign.sd2-audio",
        REALAUDIO = "com.real.realaudio",
        MATROSKA_AUDIO = "org.matroska.mka",
        FILE = "general.file",
        DIRECTORY = "general.directory",
        FOLDER = "general.folder",
        SYMLINK = "general.symlink",
        ARCHIVE = "general.archive",
        BZ2_ARCHIVE = "general.bz2-archive",
        OPG = "general.opg",
        TAZ_ARCHIVE = "general.taz-archive",
        WEB_ARCHIVE = "general.web-archive",
        DISK_IMAGE = "general.disk-image",
        ISO = "general.iso",
        TAR_ARCHIVE = "general.tar-archive",
        ZIP_ARCHIVE = "general.zip-archive",
        JAVA_ARCHIVE = "com.sun.java-archive",
        GNU_TAR_ARCHIVE = "org.gnu.gnu-tar-archive",
        GNU_ZIP_ARCHIVE = "org.gnu.gnu-zip-archive",
        GNU_ZIP_TAR_ARCHIVE = "org.gnu.gnu-zip-tar-archive",
        OPENXML = "org.openxmlformats.openxml",
        WORDPROCESSINGML_DOCUMENT = "org.openxmlformats.wordprocessingml.document",
        SPREADSHEETML_SHEET = "org.openxmlformats.spreadsheetml.sheet",
        PRESENTATIONML_PRESENTATION = "org.openxmlformats.presentationml.presentation",
        DRAWINGML_VISIO = "org.openxmlformats.drawingml.visio",
        DRAWINGML_TEMPLATE = "org.openxmlformats.drawingml.template",
        WORDPROCESSINGML_TEMPLATE = "org.openxmlformats.wordprocessingml.template",
        PRESENTATIONML_TEMPLATE = "org.openxmlformats.presentationml.template",
        PRESENTATIONML_SLIDESHOW = "org.openxmlformats.presentationml.slideshow",
        SPREADSHEETML_TEMPLATE = "org.openxmlformats.spreadsheetml.template",
        OPENDOCUMENT = "org.oasis.opendocument",
        OPENDOCUMENT_TEXT = "org.oasis.opendocument.text",
        OPENDOCUMENT_SPREADSHEET = "org.oasis.opendocument.spreadsheet",
        OPENDOCUMENT_PRESENTATION = "org.oasis.opendocument.presentation",
        OPENDOCUMENT_GRAPHICS = "org.oasis.opendocument.graphics",
        OPENDOCUMENT_FORMULA = "org.oasis.opendocument.formula",
        STUFFIT_ARCHIVE = "com.allume.stuffit-archive",
        RAR_ARCHIVE = "com.rarlab.rar-archive",
        SEVEN_ZIP_ARCHIVE = "org.7-zip.7-zip-archive",
        CALENDAR = "general.calendar",
        VCS = "general.vcs",
        ICS = "general.ics",
        CONTACT = "general.contact",
        DATABASE = "general.database",
        MESSAGE = "general.message",
        EXECUTABLE = "general.executable",
        PORTABLE_EXECUTABLE = "com.microsoft.portable-executable",
        SUN_JAVA_CLASS = "com.sun.java-class",
        VCARD = "general.vcard",
        NAVIGATION = "general.navigation",
        LOCATION = "general.location",
        FONT = "general.font",
        TRUETYPE_FONT = "general.truetype-font",
        TRUETYPE_COLLECTION_FONT = "general.truetype-collection-font",
        OPENTYPE_FONT = "general.opentype-font",
        POSTSCRIPT_FONT = "com.adobe.postscript-font",
        POSTSCRIPT_PFB_FONT = "com.adobe.postscript-pfb-font",
        POSTSCRIPT_PFA_FONT = "com.adobe.postscript-pfa-font",
        OPENHARMONY_FORM = "openharmony.form",
        OPENHARMONY_APP_ITEM = "openharmony.app-item",
        OPENHARMONY_PIXEL_MAP = "openharmony.pixel-map",
        OPENHARMONY_ATOMIC_SERVICE = "openharmony.atomic-service",
        OPENHARMONY_PACKAGE = "openharmony.package",
        OPENHARMONY_HAP = "openharmony.hap",
        OPENHARMONY_HDOC = "openharmony.hdoc",
        OPENHARMONY_HINOTE = "openharmony.hinote",
        OPENHARMONY_STYLED_STRING = "openharmony.styled-string",
        OPENHARMONY_WANT = "openharmony.want",
        OFD = "general.ofd",
        CAD = "general.cad",
        OCTET_STREAM = "general.octet-stream"
    }
}
export namespace drawing {
    export enum BlendMode {
        CLEAR = 0,
        SRC = 1,
        DST = 2,
        SRC_OVER = 3,
        DST_OVER = 4,
        SRC_IN = 5,
        DST_IN = 6,
        SRC_OUT = 7,
        DST_OUT = 8,
        SRC_ATOP = 9,
        DST_ATOP = 10,
        XOR = 11,
        PLUS = 12,
        MODULATE = 13,
        SCREEN = 14,
        OVERLAY = 15,
        DARKEN = 16,
        LIGHTEN = 17,
        COLOR_DODGE = 18,
        COLOR_BURN = 19,
        HARD_LIGHT = 20,
        SOFT_LIGHT = 21,
        DIFFERENCE = 22,
        EXCLUSION = 23,
        MULTIPLY = 24,
        HUE = 25,
        SATURATION = 26,
        COLOR = 27,
        LUMINOSITY = 28
    }
}
export namespace drawing {
    export enum PathDirection {
        CLOCKWISE = 0,
        COUNTER_CLOCKWISE = 1
    }
}
export namespace drawing {
    export enum PathFillType {
        WINDING = 0,
        EVEN_ODD = 1,
        INVERSE_WINDING = 2,
        INVERSE_EVEN_ODD = 3
    }
}
export namespace drawing {
    export enum PathMeasureMatrixFlags {
        GET_POSITION_MATRIX = 0,
        GET_TANGENT_MATRIX = 1,
        GET_POSITION_AND_TANGENT_MATRIX = 2
    }
}
export namespace drawing {
    export enum PathOp {
        DIFFERENCE = 0,
        INTERSECT = 1,
        UNION = 2,
        XOR = 3,
        REVERSE_DIFFERENCE = 4
    }
}
export namespace drawing {
    export enum PointMode {
        POINTS = 0,
        LINES = 1,
        POLYGON = 2
    }
}
export namespace drawing {
    export enum FilterMode {
        FILTER_MODE_NEAREST = 0,
        FILTER_MODE_LINEAR = 1
    }
}
export namespace drawing {
    export enum ShadowFlag {
        NONE = 0,
        TRANSPARENT_OCCLUDER = 1,
        GEOMETRIC_ONLY = 2,
        ALL = 3
    }
}
export namespace drawing {
    export enum ClipOp {
        DIFFERENCE = 0,
        INTERSECT = 1
    }
}
export namespace drawing {
    export enum TextEncoding {
        TEXT_ENCODING_UTF8 = 0,
        TEXT_ENCODING_UTF16 = 1,
        TEXT_ENCODING_UTF32 = 2,
        TEXT_ENCODING_GLYPH_ID = 3
    }
}
export namespace drawing {
    export enum FontEdging {
        ALIAS = 0,
        ANTI_ALIAS = 1,
        SUBPIXEL_ANTI_ALIAS = 2
    }
}
export namespace drawing {
    export enum FontHinting {
        NONE = 0,
        SLIGHT = 1,
        NORMAL = 2,
        FULL = 3
    }
}
export namespace drawing {
    export enum FontMetricsFlags {
        UNDERLINE_THICKNESS_VALID = 0,
        UNDERLINE_POSITION_VALID = 1,
        STRIKETHROUGH_THICKNESS_VALID = 2,
        STRIKETHROUGH_POSITION_VALID = 3,
        BOUNDS_INVALID = 4
    }
}
export namespace drawing {
    export enum RectType {
        DEFAULT = 0,
        TRANSPARENT = 1,
        FIXEDCOLOR = 2
    }
}
export namespace drawing {
    export enum TileMode {
        CLAMP = 0,
        REPEAT = 1,
        MIRROR = 2,
        DECAL = 3
    }
}
export namespace drawing {
    export enum JoinStyle {
        MITER_JOIN = 0,
        ROUND_JOIN = 1,
        BEVEL_JOIN = 2
    }
}
export namespace drawing {
    export enum CapStyle {
        FLAT_CAP = 0,
        SQUARE_CAP = 1,
        ROUND_CAP = 2
    }
}
export namespace drawing {
    export enum BlurType {
        NORMAL = 0,
        SOLID = 1,
        OUTER = 2,
        INNER = 3
    }
}
export namespace drawing {
    export enum ScaleToFit {
        FILL_SCALE_TO_FIT = 0,
        START_SCALE_TO_FIT = 1,
        CENTER_SCALE_TO_FIT = 2,
        END_SCALE_TO_FIT = 3
    }
}
export namespace drawing {
    export enum RegionOp {
        DIFFERENCE = 0,
        INTERSECT = 1,
        UNION = 2,
        XOR = 3,
        REVERSE_DIFFERENCE = 4,
        REPLACE = 5
    }
}
export namespace drawing {
    export enum CornerPos {
        TOP_LEFT_POS = 0,
        TOP_RIGHT_POS = 1,
        BOTTOM_RIGHT_POS = 2,
        BOTTOM_LEFT_POS = 3
    }
}
export namespace drawing {
    export enum SrcRectConstraint {
        STRICT = 0,
        FAST = 1
    }
}
export namespace text {
    export enum TextAlign {
        LEFT = 0,
        RIGHT = 1,
        CENTER = 2,
        JUSTIFY = 3,
        START = 4,
        END = 5
    }
}
export namespace text {
    export enum TextDirection {
        RTL = 0,
        LTR = 1
    }
}
export namespace text {
    export enum BreakStrategy {
        GREEDY = 0,
        HIGH_QUALITY = 1,
        BALANCED = 2
    }
}
export namespace text {
    export enum WordBreak {
        NORMAL = 0,
        BREAK_ALL = 1,
        BREAK_WORD = 2
    }
}
export namespace text {
    export enum TextDecorationType {
        NONE = 0,
        UNDERLINE = 1,
        OVERLINE = 2,
        LINE_THROUGH = 3
    }
}
export namespace text {
    export enum TextDecorationStyle {
        SOLID = 0,
        DOUBLE = 1,
        DOTTED = 2,
        DASHED = 3,
        WAVY = 4
    }
}
export namespace text {
    export enum FontWeight {
        W100 = 0,
        W200 = 1,
        W300 = 2,
        W400 = 3,
        W500 = 4,
        W600 = 5,
        W700 = 6,
        W800 = 7,
        W900 = 8
    }
}
export namespace text {
    export enum FontStyle {
        NORMAL = 0,
        ITALIC = 1,
        OBLIQUE = 2
    }
}
export namespace text {
    export enum FontWidth {
        ULTRA_CONDENSED = 1,
        EXTRA_CONDENSED = 2,
        CONDENSED = 3,
        SEMI_CONDENSED = 4,
        NORMAL = 5,
        SEMI_EXPANDED = 6,
        EXPANDED = 7,
        EXTRA_EXPANDED = 8,
        ULTRA_EXPANDED = 9
    }
}
export namespace text {
    export enum TextHeightBehavior {
        ALL = 0,
        DISABLE_FIRST_ASCENT = 1,
        DISABLE_LAST_ASCENT = 2,
        DISABLE_ALL = 3
    }
}
export namespace text {
    export enum TextBaseline {
        ALPHABETIC = 0,
        IDEOGRAPHIC = 1
    }
}
export namespace text {
    export enum EllipsisMode {
        START = 0,
        MIDDLE = 1,
        END = 2
    }
}
export namespace text {
    export enum PlaceholderAlignment {
        OFFSET_AT_BASELINE = 0,
        ABOVE_BASELINE = 1,
        BELOW_BASELINE = 2,
        TOP_OF_ROW_BOX = 3,
        BOTTOM_OF_ROW_BOX = 4,
        CENTER_OF_ROW_BOX = 5
    }
}
export namespace text {
    export enum SystemFontType {
        ALL = 0,
        GENERIC = 1,
        STYLISH = 2,
        INSTALLED = 3
    }
}
export namespace text {
    export enum RectWidthStyle {
        TIGHT = 0,
        MAX = 1
    }
}
export namespace text {
    export enum RectHeightStyle {
        TIGHT = 0,
        MAX = 1,
        INCLUDE_LINE_SPACE_MIDDLE = 2,
        INCLUDE_LINE_SPACE_TOP = 3,
        INCLUDE_LINE_SPACE_BOTTOM = 4,
        STRUT = 5
    }
}
export namespace text {
    export enum Affinity {
        UPSTREAM = 0,
        DOWNSTREAM = 1
    }
}
export namespace image {
    export enum ResolutionQuality {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3
    }
}
export enum IntentionCode {
    INTENTION_UNKNOWN = -1,
    INTENTION_UP = 1,
    INTENTION_DOWN = 2,
    INTENTION_LEFT = 3,
    INTENTION_RIGHT = 4,
    INTENTION_SELECT = 5,
    INTENTION_ESCAPE = 6,
    INTENTION_BACK = 7,
    INTENTION_FORWARD = 8,
    INTENTION_MENU = 9,
    INTENTION_PAGE_UP = 11,
    INTENTION_PAGE_DOWN = 12,
    INTENTION_ZOOM_OUT = 13,
    INTENTION_ZOOM_IN = 14
}
export namespace pointer {
    export enum PointerStyle {
        DEFAULT = 0,
        EAST = 1,
        WEST = 2,
        SOUTH = 3,
        NORTH = 4,
        WEST_EAST = 5,
        NORTH_SOUTH = 6,
        NORTH_EAST = 7,
        NORTH_WEST = 8,
        SOUTH_EAST = 9,
        SOUTH_WEST = 10,
        NORTH_EAST_SOUTH_WEST = 11,
        NORTH_WEST_SOUTH_EAST = 12,
        CROSS = 13,
        CURSOR_COPY = 14,
        CURSOR_FORBID = 15,
        COLOR_SUCKER = 16,
        HAND_GRABBING = 17,
        HAND_OPEN = 18,
        HAND_POINTING = 19,
        HELP = 20,
        MOVE = 21,
        RESIZE_LEFT_RIGHT = 22,
        RESIZE_UP_DOWN = 23,
        SCREENSHOT_CHOOSE = 24,
        SCREENSHOT_CURSOR = 25,
        TEXT_CURSOR = 26,
        ZOOM_IN = 27,
        ZOOM_OUT = 28,
        MIDDLE_BTN_EAST = 29,
        MIDDLE_BTN_WEST = 30,
        MIDDLE_BTN_SOUTH = 31,
        MIDDLE_BTN_NORTH = 32,
        MIDDLE_BTN_NORTH_SOUTH = 33,
        MIDDLE_BTN_NORTH_EAST = 34,
        MIDDLE_BTN_NORTH_WEST = 35,
        MIDDLE_BTN_SOUTH_EAST = 36,
        MIDDLE_BTN_SOUTH_WEST = 37,
        MIDDLE_BTN_NORTH_SOUTH_WEST_EAST = 38,
        HORIZONTAL_TEXT_CURSOR = 39,
        CURSOR_CROSS = 40,
        CURSOR_CIRCLE = 41,
        LOADING = 42,
        RUNNING = 43
    }
}
export enum LevelMode {
    OVERLAY = 0,
    EMBEDDED = 1
}
export enum ImmersiveMode {
    DEFAULT = 0,
    EXTEND = 1
}
export namespace window {
    export enum WindowStatusType {
        UNDEFINED = 0,
        FULL_SCREEN = 1,
        MAXIMIZE = 2,
        MINIMIZE = 3,
        FLOATING = 4,
        SPLIT_SCREEN = 5
    }
}
export enum DialogAlignment {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
    DEFAULT = 3,
    Default = 3,
    TOP_START = 4,
    TopStart = 4,
    TOP_END = 5,
    TopEnd = 5,
    CENTER_START = 6,
    CenterStart = 6,
    CENTER_END = 7,
    CenterEnd = 7,
    BOTTOM_START = 8,
    BottomStart = 8,
    BOTTOM_END = 9,
    BottomEnd = 9
}
export enum DialogButtonDirection {
    AUTO = 0,
    HORIZONTAL = 1,
    VERTICAL = 2
}
export enum IndexerAlign {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    START = 2,
    END = 3
}
export enum NavigationType {
    PUSH = 0,
    BACK = 1,
    REPLACE = 2
}
export enum LengthUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4
}
export enum LengthMetricsUnit {
    DEFAULT = 0,
    PX = 1
}
export enum BadgePosition {
    RIGHT_TOP = 0,
    RightTop = 0,
    RIGHT = 1,
    Right = 1,
    LEFT = 2,
    Left = 2
}
export enum ButtonType {
    CAPSULE = 0,
    Capsule = 0,
    CIRCLE = 1,
    Circle = 1,
    NORMAL = 2,
    Normal = 2,
    ROUNDED_RECTANGLE = 3
}
export enum ButtonStyleMode {
    NORMAL = 0,
    EMPHASIZED = 1,
    TEXTUAL = 2
}
export enum ButtonRole {
    NORMAL = 0,
    ERROR = 1
}
export enum ControlSize {
    SMALL = "'small'",
    NORMAL = "'normal'"
}
export enum CalendarAlign {
    START = 0,
    CENTER = 1,
    END = 2
}
export enum SelectStatus {
    ALL = 0,
    All = 0,
    PART = 1,
    Part = 1,
    NONE = 2,
    None = 2
}
export enum AccessibilitySamePageMode {
    SEMI_SILENT = 0,
    FULL_SILENT = 1
}
export enum AccessibilityRoleType {
    ACTION_SHEET = 0,
    ALERT_DIALOG = 1,
    INDEXER_COMPONENT = 2,
    BADGE_COMPONENT = 3,
    BLANK = 4,
    BUTTON = 5,
    BACK_BUTTON = 6,
    SHEET_DRAG_BAR = 7,
    CALENDAR_PICKER = 8,
    CALENDAR = 9,
    CANVAS = 10,
    CANVAS_GRADIENT = 11,
    CANVAS_PATTERN = 12,
    CHECKBOX = 13,
    CHECKBOX_GROUP = 14,
    CIRCLE = 15,
    COLUMN_SPLIT = 16,
    COLUMN = 17,
    CANVAS_RENDERING_CONTEXT_2D = 18,
    CHART = 19,
    COUNTER = 20,
    CONTAINER_MODAL = 21,
    DATA_PANEL = 22,
    DATE_PICKER = 23,
    DIALOG = 24,
    DIVIDER = 25,
    DRAG_BAR = 26,
    EFFECT_COMPONENT = 27,
    ELLIPSE = 28,
    FLEX = 29,
    FLOW_ITEM = 30,
    FORM_COMPONENT = 31,
    FORM_LINK = 32,
    GAUGE = 33,
    GRID = 34,
    GRID_COL = 35,
    GRID_CONTAINER = 36,
    GRID_ITEM = 37,
    GRID_ROW = 38,
    HYPERLINK = 39,
    IMAGE = 40,
    IMAGE_ANIMATOR = 41,
    IMAGE_BITMAP = 42,
    IMAGE_DATA = 43,
    IMAGE_SPAN = 44,
    LABEL = 45,
    LINE = 46,
    LIST = 47,
    LIST_ITEM = 48,
    LIST_ITEM_GROUP = 49,
    LOADING_PROGRESS = 50,
    MARQUEE = 51,
    MATRIX2D = 52,
    MENU = 53,
    MENU_ITEM = 54,
    MENU_ITEM_GROUP = 55,
    NAV_DESTINATION = 56,
    NAV_ROUTER = 57,
    NAVIGATION = 58,
    NAVIGATION_BAR = 59,
    NAVIGATION_MENU = 60,
    NAVIGATOR = 61,
    OFFSCREEN_CANVAS = 62,
    OFFSCREEN_CANVAS_RENDERING_CONTEXT2D = 63,
    OPTION = 64,
    PANEL = 65,
    PAPER_PAGE = 66,
    PATH = 67,
    PATH2D = 68,
    PATTERN_LOCK = 69,
    PICKER = 70,
    PICKER_VIEW = 71,
    PLUGIN_COMPONENT = 72,
    POLYGON = 73,
    POLYLINE = 74,
    POPUP = 75,
    PROGRESS = 76,
    QRCODE = 77,
    RADIO = 78,
    RATING = 79,
    RECT = 80,
    REFRESH = 81,
    RELATIVE_CONTAINER = 82,
    REMOTE_WINDOW = 83,
    RICH_EDITOR = 84,
    RICH_TEXT = 85,
    ROLE_PAGER = 86,
    ROW = 87,
    ROW_SPLIT = 88,
    SCROLL = 89,
    SCROLL_BAR = 90,
    SEARCH = 91,
    SEARCH_FIELD = 92,
    SELECT = 93,
    SHAPE = 94,
    SIDEBAR_CONTAINER = 95,
    SLIDER = 96,
    SPAN = 97,
    STACK = 98,
    STEPPER = 99,
    STEPPER_ITEM = 100,
    SWIPER = 101,
    SWIPER_INDICATOR = 102,
    SWITCH = 103,
    SYMBOL_GLYPH = 104,
    TAB_CONTENT = 105,
    TAB_BAR = 106,
    TABS = 107,
    TEXT = 108,
    TEXT_CLOCK = 109,
    TEXT_ENTRY = 110,
    TEXT_INPUT = 111,
    TEXT_PICKER = 112,
    TEXT_TIMER = 113,
    TEXT_AREA = 114,
    TEXT_FIELD = 115,
    TIME_PICKER = 116,
    TITLE_BAR = 117,
    TOGGLER = 118,
    UI_EXTENSION_COMPONENT = 119,
    VIDEO = 120,
    WATER_FLOW = 121,
    WEB = 122,
    XCOMPONENT = 123,
    ROLE_NONE = 124
}
export enum FinishCallbackType {
    REMOVED = 0,
    LOGICALLY = 1
}
export enum TouchTestStrategy {
    DEFAULT = 0,
    FORWARD_COMPETITION = 1,
    FORWARD = 2
}
export enum TransitionHierarchyStrategy {
    NONE = 0,
    ADAPTIVE = 1
}
export enum ChainStyle {
    SPREAD = 0,
    SPREAD_INSIDE = 1,
    PACKED = 2
}
export enum TransitionEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
export enum EffectType {
    DEFAULT = 0,
    WINDOW_EFFECT = 1
}
export enum PreDragStatus {
    ACTION_DETECTING_STATUS = 0,
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    PREVIEW_LIFT_STARTED = 2,
    PREVIEW_LIFT_FINISHED = 3,
    PREVIEW_LANDING_STARTED = 4,
    PREVIEW_LANDING_FINISHED = 5,
    ACTION_CANCELED_BEFORE_DRAG = 6,
    PREPARING_FOR_DRAG_DETECTION = 7
}
export enum SourceType {
    UNKNOWN = 0,
    Unknown = 0,
    MOUSE = 1,
    Mouse = 1,
    TOUCH_SCREEN = 2,
    TouchScreen = 2
}
export enum SourceTool {
    UNKNOWN = 0,
    Unknown = 0,
    FINGER = 1,
    Finger = 1,
    PEN = 2,
    Pen = 2,
    MOUSE = 3,
    TOUCHPAD = 4,
    JOYSTICK = 5
}
export enum RepeatMode {
    REPEAT = 0,
    Repeat = 0,
    STRETCH = 1,
    Stretch = 1,
    ROUND = 2,
    Round = 2,
    SPACE = 3,
    Space = 3
}
export enum BlurStyle {
    THIN = 0,
    Thin = 0,
    REGULAR = 1,
    Regular = 1,
    THICK = 2,
    Thick = 2,
    BACKGROUND_THIN = 3,
    BACKGROUND_REGULAR = 4,
    BACKGROUND_THICK = 5,
    BACKGROUND_ULTRA_THICK = 6,
    NONE = 7,
    COMPONENT_ULTRA_THIN = 8,
    COMPONENT_THIN = 9,
    COMPONENT_REGULAR = 10,
    COMPONENT_THICK = 11,
    COMPONENT_ULTRA_THICK = 12
}
export enum BlurStyleActivePolicy {
    FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2
}
export enum ThemeColorMode {
    SYSTEM = 0,
    LIGHT = 1,
    DARK = 2
}
export enum AdaptiveColor {
    DEFAULT = 0,
    AVERAGE = 1
}
export enum ModalTransition {
    DEFAULT = 0,
    NONE = 1,
    ALPHA = 2
}
export enum ShadowType {
    COLOR = 0,
    BLUR = 1
}
export enum ShadowStyle {
    OUTER_DEFAULT_XS = 0,
    OUTER_DEFAULT_SM = 1,
    OUTER_DEFAULT_MD = 2,
    OUTER_DEFAULT_LG = 3,
    OUTER_FLOATING_SM = 4,
    OUTER_FLOATING_MD = 5
}
export enum SafeAreaType {
    SYSTEM = 0,
    CUTOUT = 1,
    KEYBOARD = 2
}
export enum SafeAreaEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3
}
export enum LayoutSafeAreaType {
    SYSTEM = 0
}
export enum LayoutSafeAreaEdge {
    TOP = 0,
    BOTTOM = 1
}
export enum SheetSize {
    MEDIUM = 0,
    LARGE = 1,
    FIT_CONTENT = 2
}
export enum DragBehavior {
    COPY = 0,
    MOVE = 1
}
export enum DragResult {
    DRAG_SUCCESSFUL = 0,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4
}
export enum BlendMode {
    NONE = 0,
    CLEAR = 1,
    SRC = 2,
    DST = 3,
    SRC_OVER = 4,
    DST_OVER = 5,
    SRC_IN = 6,
    DST_IN = 7,
    SRC_OUT = 8,
    DST_OUT = 9,
    SRC_ATOP = 10,
    DST_ATOP = 11,
    XOR = 12,
    PLUS = 13,
    MODULATE = 14,
    SCREEN = 15,
    OVERLAY = 16,
    DARKEN = 17,
    LIGHTEN = 18,
    COLOR_DODGE = 19,
    COLOR_BURN = 20,
    HARD_LIGHT = 21,
    SOFT_LIGHT = 22,
    DIFFERENCE = 23,
    EXCLUSION = 24,
    MULTIPLY = 25,
    HUE = 26,
    SATURATION = 27,
    COLOR = 28,
    LUMINOSITY = 29
}
export enum BlendApplyType {
    FAST = 0,
    OFFSCREEN = 1
}
export enum SheetType {
    BOTTOM = 0,
    CENTER = 1,
    POPUP = 2
}
export enum SheetMode {
    OVERLAY = 0,
    EMBEDDED = 1
}
export enum ScrollSizeMode {
    FOLLOW_DETENT = 0,
    CONTINUOUS = 1
}
export enum SheetKeyboardAvoidMode {
    NONE = 0,
    TRANSLATE_AND_RESIZE = 1,
    RESIZE_ONLY = 2,
    TRANSLATE_AND_SCROLL = 3
}
export enum DismissReason {
    PRESS_BACK = 0,
    TOUCH_OUTSIDE = 1,
    CLOSE_BUTTON = 2,
    SLIDE_DOWN = 3
}
export enum MenuPreviewMode {
    NONE = 0,
    IMAGE = 1
}
export enum HapticFeedbackMode {
    DISABLED = 0,
    ENABLED = 1,
    AUTO = 2
}
export enum OutlineStyle {
    SOLID = 0,
    DASHED = 1,
    DOTTED = 2
}
export enum DragPreviewMode {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4,
    ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
    ENABLE_MULTI_TILE_EFFECT = 6,
    ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW = 7
}
export enum DraggingSizeChangeEffect {
    DEFAULT = 0,
    SIZE_TRANSITION = 1,
    SIZE_CONTENT_TRANSITION = 2
}
export enum MenuPolicy {
    DEFAULT = 0,
    HIDE = 1,
    SHOW = 2
}
export enum ContentClipMode {
    CONTENT_ONLY = 0,
    BOUNDARY = 1,
    SAFE_AREA = 2
}
export enum EffectEdge {
    START = 1,
    END = 2
}
export enum KeyboardAvoidMode {
    DEFAULT = 0,
    NONE = 1
}
export enum HoverModeAreaType {
    TOP_SCREEN = 0,
    BOTTOM_SCREEN = 1
}
export enum DataPanelType {
    LINE = 0,
    Line = 0,
    CIRCLE = 1,
    Circle = 1
}
export enum DatePickerMode {
    DATE = 0,
    YEAR_AND_MONTH = 1,
    MONTH_AND_DAY = 2
}
export enum CheckBoxShape {
    CIRCLE = 0,
    ROUNDED_SQUARE = 1
}
export enum Color {
    WHITE = 0,
    White = 0,
    BLACK = 1,
    Black = 1,
    BLUE = 2,
    Blue = 2,
    BROWN = 3,
    Brown = 3,
    GRAY = 4,
    Gray = 4,
    GREEN = 5,
    Green = 5,
    GREY = 6,
    Grey = 6,
    ORANGE = 7,
    Orange = 7,
    PINK = 8,
    Pink = 8,
    RED = 9,
    Red = 9,
    YELLOW = 10,
    Yellow = 10,
    TRANSPARENT = 11,
    Transparent = 11
}
export enum ColoringStrategy {
    INVERT = "'invert'",
    AVERAGE = "'average'",
    PRIMARY = "'primary'"
}
export enum ImageFit {
    CONTAIN = 0,
    Contain = 0,
    COVER = 1,
    Cover = 1,
    AUTO = 2,
    Auto = 2,
    FILL = 3,
    Fill = 3,
    SCALE_DOWN = 4,
    ScaleDown = 4,
    NONE = 5,
    None = 5,
    TOP_START = 7,
    TOP = 8,
    TOP_END = 9,
    START = 10,
    CENTER = 11,
    END = 12,
    BOTTOM_START = 13,
    BOTTOM = 14,
    BOTTOM_END = 15,
    MATRIX = 16
}
export enum BorderStyle {
    DOTTED = 0,
    Dotted = 0,
    DASHED = 1,
    Dashed = 1,
    SOLID = 2,
    Solid = 2
}
export enum LineJoinStyle {
    MITER = 0,
    Miter = 0,
    ROUND = 1,
    Round = 1,
    BEVEL = 2,
    Bevel = 2
}
export enum TouchType {
    DOWN = 0,
    Down = 0,
    UP = 1,
    Up = 1,
    MOVE = 2,
    Move = 2,
    CANCEL = 3,
    Cancel = 3
}
export enum InteractionHand {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}
export enum MouseButton {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    MIDDLE = 2,
    Middle = 2,
    BACK = 3,
    Back = 3,
    FORWARD = 4,
    Forward = 4,
    NONE = 5,
    None = 5
}
export enum MouseAction {
    PRESS = 0,
    Press = 0,
    RELEASE = 1,
    Release = 1,
    MOVE = 2,
    Move = 2,
    HOVER = 3,
    Hover = 3,
    CANCEL = 13
}
export enum AnimationStatus {
    INITIAL = 0,
    Initial = 0,
    RUNNING = 1,
    Running = 1,
    PAUSED = 2,
    Paused = 2,
    STOPPED = 3,
    Stopped = 3
}
export enum FillMode {
    NONE = 0,
    None = 0,
    FORWARDS = 1,
    Forwards = 1,
    BACKWARDS = 2,
    Backwards = 2,
    BOTH = 3,
    Both = 3
}
export enum PlayMode {
    NORMAL = 0,
    Normal = 0,
    REVERSE = 1,
    Reverse = 1,
    ALTERNATE = 2,
    Alternate = 2,
    ALTERNATE_REVERSE = 3,
    AlternateReverse = 3
}
export enum KeyType {
    DOWN = 0,
    Down = 0,
    UP = 1,
    Up = 1
}
export enum KeySource {
    UNKNOWN = 0,
    Unknown = 0,
    KEYBOARD = 1,
    Keyboard = 1,
    JOYSTICK = 2
}
export enum Edge {
    TOP = 0,
    Top = 0,
    BOTTOM = 1,
    Bottom = 1,
    START = 2,
    Start = 2,
    END = 3,
    End = 3
}
export enum Week {
    MON = 0,
    Mon = 0,
    TUE = 1,
    Tue = 1,
    WED = 2,
    Wed = 2,
    THUR = 3,
    Thur = 3,
    FRI = 4,
    Fri = 4,
    SAT = 5,
    Sat = 5,
    SUN = 6,
    Sun = 6
}
export enum Direction {
    LTR = 0,
    Ltr = 0,
    RTL = 1,
    Rtl = 1,
    AUTO = 2,
    Auto = 2
}
export enum BarState {
    OFF = 0,
    Off = 0,
    AUTO = 1,
    Auto = 1,
    ON = 2,
    On = 2
}
export enum EdgeEffect {
    SPRING = 0,
    Spring = 0,
    FADE = 1,
    Fade = 1,
    NONE = 2,
    None = 2
}
export enum Alignment {
    TOP_START = 0,
    TopStart = 0,
    TOP = 1,
    Top = 1,
    TOP_END = 2,
    TopEnd = 2,
    START = 3,
    Start = 3,
    CENTER = 4,
    Center = 4,
    END = 5,
    End = 5,
    BOTTOM_START = 6,
    BottomStart = 6,
    BOTTOM = 7,
    Bottom = 7,
    BOTTOM_END = 8,
    BottomEnd = 8
}
export enum TransitionType {
    ALL = 0,
    All = 0,
    INSERT = 1,
    Insert = 1,
    DELETE = 2,
    Delete = 2
}
export enum RelateType {
    FILL = 0,
    FIT = 1
}
export enum Visibility {
    VISIBLE = 0,
    Visible = 0,
    HIDDEN = 1,
    Hidden = 1,
    NONE = 2,
    None = 2
}
export enum LineCapStyle {
    BUTT = 0,
    Butt = 0,
    ROUND = 1,
    Round = 1,
    SQUARE = 2,
    Square = 2
}
export enum Axis {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1
}
export enum HorizontalAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2
}
export enum FlexAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2,
    SPACE_BETWEEN = 3,
    SpaceBetween = 3,
    SPACE_AROUND = 4,
    SpaceAround = 4,
    SPACE_EVENLY = 5,
    SpaceEvenly = 5
}
export enum ItemAlign {
    AUTO = 0,
    Auto = 0,
    START = 1,
    Start = 1,
    CENTER = 2,
    Center = 2,
    END = 3,
    End = 3,
    BASELINE = 4,
    Baseline = 4,
    STRETCH = 5,
    Stretch = 5
}
export enum FlexDirection {
    ROW = 0,
    Row = 0,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3
}
export enum PixelRoundCalcPolicy {
    NO_FORCE_ROUND = 0,
    FORCE_CEIL = 1,
    FORCE_FLOOR = 2
}
export enum PixelRoundMode {
    PIXEL_ROUND_ON_LAYOUT_FINISH = 0,
    PIXEL_ROUND_AFTER_MEASURE = 1
}
export enum FlexWrap {
    NO_WRAP = 0,
    NoWrap = 0,
    WRAP = 1,
    Wrap = 1,
    WRAP_REVERSE = 2,
    WrapReverse = 2
}
export enum VerticalAlign {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2
}
export enum ImageRepeat {
    NO_REPEAT = 0,
    NoRepeat = 0,
    X = 1,
    Y = 2,
    XY = 3
}
export enum ImageSize {
    AUTO = 0,
    Auto = 0,
    COVER = 1,
    Cover = 1,
    CONTAIN = 2,
    Contain = 2,
    FILL = 3
}
export enum GradientDirection {
    LEFT = 0,
    Left = 0,
    TOP = 1,
    Top = 1,
    RIGHT = 2,
    Right = 2,
    BOTTOM = 3,
    Bottom = 3,
    LEFT_TOP = 4,
    LeftTop = 4,
    LEFT_BOTTOM = 5,
    LeftBottom = 5,
    RIGHT_TOP = 6,
    RightTop = 6,
    RIGHT_BOTTOM = 7,
    RightBottom = 7,
    NONE = 8,
    None = 8
}
export enum SharedTransitionEffectType {
    STATIC = 0,
    Static = 0,
    EXCHANGE = 1,
    Exchange = 1
}
export enum FontStyle {
    NORMAL = 0,
    Normal = 0,
    ITALIC = 1,
    Italic = 1
}
export enum FontWeight {
    LIGHTER = 0,
    Lighter = 0,
    NORMAL = 1,
    Normal = 1,
    REGULAR = 2,
    Regular = 2,
    MEDIUM = 3,
    Medium = 3,
    BOLD = 4,
    Bold = 4,
    BOLDER = 5,
    Bolder = 5
}
export enum TextAlign {
    CENTER = 0,
    Center = 0,
    START = 1,
    Start = 1,
    END = 2,
    End = 2,
    JUSTIFY = 3
}
export enum TextOverflow {
    NONE = 0,
    None = 0,
    CLIP = 1,
    Clip = 1,
    ELLIPSIS = 2,
    Ellipsis = 2,
    MARQUEE = 3
}
export enum TextDecorationType {
    NONE = 0,
    None = 0,
    UNDERLINE = 1,
    Underline = 1,
    OVERLINE = 2,
    Overline = 2,
    LINE_THROUGH = 3,
    LineThrough = 3
}
export enum TextCase {
    NORMAL = 0,
    Normal = 0,
    LOWER_CASE = 1,
    LowerCase = 1,
    UPPER_CASE = 2,
    UpperCase = 2
}
export enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST = 0,
    MIN_FONT_SIZE_FIRST = 1,
    LAYOUT_CONSTRAINT_FIRST = 2
}
export enum ResponseType {
    RIGHT_CLICK = 0,
    RightClick = 0,
    LONG_PRESS = 1,
    LongPress = 1
}
export enum HoverEffect {
    AUTO = 0,
    Auto = 0,
    SCALE = 1,
    Scale = 1,
    HIGHLIGHT = 2,
    Highlight = 2,
    NONE = 3,
    None = 3
}
export enum Placement {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    TOP = 2,
    Top = 2,
    BOTTOM = 3,
    Bottom = 3,
    TOP_LEFT = 4,
    TopLeft = 4,
    TOP_RIGHT = 5,
    TopRight = 5,
    BOTTOM_LEFT = 6,
    BottomLeft = 6,
    BOTTOM_RIGHT = 7,
    BottomRight = 7,
    LEFT_TOP = 8,
    LeftTop = 8,
    LEFT_BOTTOM = 9,
    LeftBottom = 9,
    RIGHT_TOP = 10,
    RightTop = 10,
    RIGHT_BOTTOM = 11,
    RightBottom = 11
}
export enum ArrowPointPosition {
    START = "'Start'",
    CENTER = "'Center'",
    END = "'End'"
}
export enum CopyOptions {
    NONE = 0,
    None = 0,
    IN_APP = 1,
    InApp = 1,
    LOCAL_DEVICE = 2,
    LocalDevice = 2
}
export enum HitTestMode {
    DEFAULT = 0,
    Default = 0,
    BLOCK = 1,
    Block = 1,
    TRANSPARENT = 2,
    Transparent = 2,
    NONE = 3,
    None = 3
}
export enum TitleHeight {
    MAIN_ONLY = 0,
    MainOnly = 0,
    MAIN_WITH_SUB = 1,
    MainWithSub = 1
}
export enum ModifierKey {
    CTRL = 0,
    SHIFT = 1,
    ALT = 2
}
export enum FunctionKey {
    ESC = 0,
    F1 = 1,
    F2 = 2,
    F3 = 3,
    F4 = 4,
    F5 = 5,
    F6 = 6,
    F7 = 7,
    F8 = 8,
    F9 = 9,
    F10 = 10,
    F11 = 11,
    F12 = 12,
    TAB = 13,
    DPAD_UP = 14,
    DPAD_DOWN = 15,
    DPAD_LEFT = 16,
    DPAD_RIGHT = 17
}
export enum ImageSpanAlignment {
    BASELINE = 0,
    BOTTOM = 1,
    CENTER = 2,
    TOP = 3
}
export enum ObscuredReasons {
    PLACEHOLDER = 0
}
export enum TextContentStyle {
    DEFAULT = 0,
    INLINE = 1
}
export enum ClickEffectLevel {
    LIGHT = 0,
    MIDDLE = 1,
    HEAVY = 2
}
export enum XComponentType {
    SURFACE = 0,
    TEXTURE = 1
}
export enum NestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1,
    PARENT_FIRST = 2,
    PARALLEL = 3
}
export enum ScrollSource {
    DRAG = 0,
    FLING = 1,
    EDGE_EFFECT = 2,
    OTHER_USER_INPUT = 3,
    SCROLL_BAR = 4,
    SCROLL_BAR_FLING = 5,
    SCROLLER = 6,
    SCROLLER_ANIMATION = 7
}
export enum RenderFit {
    CENTER = 0,
    TOP = 1,
    BOTTOM = 2,
    LEFT = 3,
    RIGHT = 4,
    TOP_LEFT = 5,
    TOP_RIGHT = 6,
    BOTTOM_LEFT = 7,
    BOTTOM_RIGHT = 8,
    RESIZE_FILL = 9,
    RESIZE_CONTAIN = 10,
    RESIZE_CONTAIN_TOP_LEFT = 11,
    RESIZE_CONTAIN_BOTTOM_RIGHT = 12,
    RESIZE_COVER = 13,
    RESIZE_COVER_TOP_LEFT = 14,
    RESIZE_COVER_BOTTOM_RIGHT = 15
}
export enum DialogButtonStyle {
    DEFAULT = 0,
    HIGHLIGHT = 1
}
export enum WordBreak {
    NORMAL = 0,
    BREAK_ALL = 1,
    BREAK_WORD = 2,
    HYPHENATION = 3
}
export enum LineBreakStrategy {
    GREEDY = 0,
    HIGH_QUALITY = 1,
    BALANCED = 2
}
export enum IlluminatedType {
    NONE = 0,
    BORDER = 1,
    CONTENT = 2,
    BORDER_CONTENT = 3,
    BLOOM_BORDER = 4,
    BLOOM_BORDER_CONTENT = 5
}
export enum EllipsisMode {
    START = 0,
    CENTER = 1,
    END = 2
}
export enum OptionWidthMode {
    FIT_CONTENT = "'fit_content'",
    FIT_TRIGGER = "'fit_trigger'"
}
export enum FoldStatus {
    FOLD_STATUS_UNKNOWN = 0,
    FOLD_STATUS_EXPANDED = 1,
    FOLD_STATUS_FOLDED = 2,
    FOLD_STATUS_HALF_FOLDED = 3
}
export enum AppRotation {
    ROTATION_0 = 0,
    ROTATION_90 = 1,
    ROTATION_180 = 2,
    ROTATION_270 = 3
}
export enum EmbeddedType {
    EMBEDDED_UI_EXTENSION = 0
}
export enum MarqueeUpdateStrategy {
    DEFAULT = 0,
    PRESERVE_POSITION = 1
}
export enum TextDecorationStyle {
    SOLID = 0,
    DOUBLE = 1,
    DOTTED = 2,
    DASHED = 3,
    WAVY = 4
}
export enum TextSelectableMode {
    SELECTABLE_UNFOCUSABLE = 0,
    SELECTABLE_FOCUSABLE = 1,
    UNSELECTABLE = 2
}
export enum AccessibilityHoverType {
    HOVER_ENTER = 0,
    HOVER_MOVE = 1,
    HOVER_EXIT = 2,
    HOVER_CANCEL = 3
}
export enum WidthBreakpoint {
    WIDTH_XS = 0,
    WIDTH_SM = 1,
    WIDTH_MD = 2,
    WIDTH_LG = 3,
    WIDTH_XL = 4
}
export enum HeightBreakpoint {
    HEIGHT_SM = 0,
    HEIGHT_MD = 1,
    HEIGHT_LG = 2
}
export enum AxisModel {
    ABS_X = 0,
    ABS_Y = 1,
    ABS_Z = 2,
    ABS_RZ = 3,
    ABS_GAS = 4,
    ABS_BRAKE = 5,
    ABS_HAT0X = 6,
    ABS_HAT0Y = 7
}
export enum PageFlipMode {
    CONTINUOUS = 0,
    SINGLE = 1
}
export enum CrownAction {
    BEGIN = 0,
    UPDATE = 1,
    END = 2
}
export enum CrownSensitivity {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
}
export enum AxisAction {
    NONE = 0,
    BEGIN = 1,
    UPDATE = 2,
    END = 3,
    CANCEL = 4
}
export enum FocusDrawLevel {
    SELF = 0,
    TOP = 1
}
export enum DividerMode {
    FLOATING_ABOVE_MENU = 0,
    EMBEDDED_IN_MENU = 1
}
export enum FocusPriority {
    AUTO = 0,
    PRIOR = 2000,
    PREVIOUS = 3000
}
export enum KeyProcessingMode {
    FOCUS_NAVIGATION = 0,
    ANCESTOR_EVENT = 1
}
export enum FormDimension {
    DIMENSION_1_2 = 0,
    Dimension_1_2 = 0,
    DIMENSION_2_2 = 1,
    Dimension_2_2 = 1,
    DIMENSION_2_4 = 2,
    Dimension_2_4 = 2,
    DIMENSION_4_4 = 3,
    Dimension_4_4 = 3,
    DIMENSION_1_1 = 6,
    DIMENSION_6_4 = 7,
    DIMENSION_2_3 = 8,
    DIMENSION_3_3 = 9
}
export enum FormRenderingMode {
    FULL_COLOR = 0,
    SINGLE_COLOR = 1
}
export enum FormShape {
    RECT = 1,
    CIRCLE = 2
}
export enum PanDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    LEFT = 2,
    Left = 2,
    RIGHT = 3,
    Right = 3,
    VERTICAL = 4,
    Vertical = 4,
    UP = 5,
    Up = 5,
    DOWN = 6,
    Down = 6,
    ALL = 7,
    All = 7
}
export enum SwipeDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    VERTICAL = 2,
    Vertical = 2,
    ALL = 3,
    All = 3
}
export enum GestureMode {
    SEQUENCE = 0,
    Sequence = 0,
    PARALLEL = 1,
    Parallel = 1,
    EXCLUSIVE = 2,
    Exclusive = 2
}
export enum GestureMask {
    NORMAL = 0,
    Normal = 0,
    IGNORE_INTERNAL = 1,
    IgnoreInternal = 1
}
export enum GestureJudgeResult {
    CONTINUE = 0,
    REJECT = 1
}
export namespace GestureControl {
    export enum GestureType {
        TAP_GESTURE = 0,
        LONG_PRESS_GESTURE = 1,
        PAN_GESTURE = 2,
        PINCH_GESTURE = 3,
        SWIPE_GESTURE = 4,
        ROTATION_GESTURE = 5,
        DRAG = 6,
        CLICK = 7
    }
}
export enum GesturePriority {
    NORMAL = 0,
    PRIORITY = 1
}
export enum GestureRecognizerState {
    READY = 0,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5
}
export enum GridDirection {
    ROW = 0,
    Row = 0,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3
}
export enum GridItemAlignment {
    DEFAULT = 0,
    STRETCH = 1
}
export enum GridItemStyle {
    NONE = 0,
    PLAIN = 1
}
export enum BreakpointsReference {
    WINDOW_SIZE = 0,
    WindowSize = 0,
    COMPONENT_SIZE = 1,
    ComponentSize = 1
}
export enum GridRowDirection {
    ROW = 0,
    Row = 0,
    ROW_REVERSE = 1,
    RowReverse = 1
}
export enum ImageRenderMode {
    ORIGINAL = 0,
    Original = 0,
    TEMPLATE = 1,
    Template = 1
}
export enum ImageContent {
    EMPTY = 0
}
export enum DynamicRangeMode {
    HIGH = 0,
    CONSTRAINT = 1,
    STANDARD = 2
}
export enum ImageInterpolation {
    NONE = 0,
    None = 0,
    LOW = 1,
    Low = 1,
    MEDIUM = 2,
    Medium = 2,
    HIGH = 3,
    High = 3
}
export enum ImageRotateOrientation {
    AUTO = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
    UP_MIRRORED = 5,
    RIGHT_MIRRORED = 6,
    DOWN_MIRRORED = 7,
    LEFT_MIRRORED = 8
}
export enum ImageAnalyzerType {
    SUBJECT = 0,
    TEXT = 1,
    OBJECT_LOOKUP = 2
}
export enum DataOperationType {
    ADD = "'add'",
    DELETE = "'delete'",
    EXCHANGE = "'exchange'",
    MOVE = "'move'",
    CHANGE = "'change'",
    RELOAD = "'reload'"
}
export enum ScrollState {
    IDLE = 0,
    Idle = 0,
    SCROLL = 1,
    Scroll = 1,
    FLING = 2,
    Fling = 2
}
export enum ListItemAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2
}
export enum ListItemGroupArea {
    NONE = 0,
    IN_LIST_ITEM_AREA = 1,
    IN_HEADER_AREA = 2,
    IN_FOOTER_AREA = 3
}
export enum StickyStyle {
    NONE = 0,
    None = 0,
    HEADER = 1,
    Header = 1,
    FOOTER = 2,
    Footer = 2
}
export enum ChainEdgeEffect {
    DEFAULT = 0,
    STRETCH = 1
}
export enum ScrollSnapAlign {
    NONE = 0,
    START = 1,
    CENTER = 2,
    END = 3
}
export enum SwipeEdgeEffect {
    SPRING = 0,
    Spring = 0,
    NONE = 1,
    None = 1
}
export enum SwipeActionState {
    COLLAPSED = 0,
    EXPANDED = 1,
    ACTIONING = 2
}
export enum ListItemStyle {
    NONE = 0,
    CARD = 1
}
export enum ListItemGroupStyle {
    NONE = 0,
    CARD = 1
}
export enum LoadingProgressStyle {
    DEFAULT = 0,
    Default = 0,
    CIRCULAR = 1,
    Circular = 1,
    ORBITAL = 2,
    Orbital = 2
}
export enum LocationIconStyle {
    FULL_FILLED = 0,
    LINES = 1
}
export enum LocationDescription {
    CURRENT_LOCATION = 0,
    ADD_LOCATION = 1,
    SELECT_LOCATION = 2,
    SHARE_LOCATION = 3,
    SEND_LOCATION = 4,
    LOCATING = 5,
    LOCATION = 6,
    SEND_CURRENT_LOCATION = 7,
    RELOCATION = 8,
    PUNCH_IN = 9,
    CURRENT_POSITION = 10
}
export enum LocationButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export enum SubMenuExpandingMode {
    SIDE_EXPAND = 0,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2
}
export enum NavigationSystemTransitionType {
    DEFAULT = 0,
    NONE = 1,
    TITLE = 2,
    CONTENT = 3,
    FADE = 4,
    EXPLODE = 5,
    SLIDE_RIGHT = 6,
    SLIDE_BOTTOM = 7
}
export enum NavDestinationMode {
    STANDARD = 0,
    DIALOG = 1
}
export enum NavDestinationActiveReason {
    TRANSITION = 0,
    CONTENT_COVER = 1,
    SHEET = 2,
    DIALOG = 3,
    OVERLAY = 4,
    APP_STATE = 5
}
export enum NavigationMode {
    STACK = 0,
    Stack = 0,
    SPLIT = 1,
    Split = 1,
    AUTO = 2,
    Auto = 2
}
export enum NavBarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export enum NavigationTitleMode {
    FREE = 0,
    Free = 0,
    FULL = 1,
    Full = 1,
    MINI = 2,
    Mini = 2
}
export enum LaunchMode {
    STANDARD = 0,
    MOVE_TO_TOP_SINGLETON = 1,
    POP_TO_SINGLETON = 2,
    NEW_INSTANCE = 3
}
export enum ToolbarItemStatus {
    NORMAL = 0,
    DISABLED = 1,
    ACTIVE = 2
}
export enum NavigationOperation {
    PUSH = 1,
    POP = 2,
    REPLACE = 3
}
export enum BarStyle {
    STANDARD = 0,
    STACK = 1,
    SAFE_AREA_PADDING = 2
}
export enum RouteType {
    NONE = 0,
    None = 0,
    PUSH = 1,
    Push = 1,
    POP = 2,
    Pop = 2
}
export enum SlideEffect {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    TOP = 2,
    Top = 2,
    BOTTOM = 3,
    Bottom = 3,
    START = 5,
    END = 6
}
export enum ParticleType {
    POINT = "'point'",
    IMAGE = "'image'"
}
export enum ParticleEmitterShape {
    RECTANGLE = "'rectangle'",
    CIRCLE = "'circle'",
    ELLIPSE = "'ellipse'",
    ANNULUS = "'annulus'"
}
export enum DistributionType {
    UNIFORM = 0,
    GAUSSIAN = 1
}
export enum ParticleUpdater {
    NONE = "'none'",
    RANDOM = "'random'",
    CURVE = "'curve'"
}
export enum DisturbanceFieldShape {
    RECT = 0,
    CIRCLE = 1,
    ELLIPSE = 2
}
export enum PasteIconStyle {
    LINES = 0
}
export enum PasteDescription {
    PASTE = 0
}
export enum PasteButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export enum PatternLockChallengeResult {
    CORRECT = 1,
    WRONG = 2
}
export enum ProgressType {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4
}
export enum ProgressStatus {
    LOADING = 0,
    PROGRESSING = 1
}
export enum ProgressStyle {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4
}
export enum RadioIndicatorType {
    TICK = 0,
    DOT = 1,
    CUSTOM = 2
}
export enum RefreshStatus {
    INACTIVE = 0,
    Inactive = 0,
    DRAG = 1,
    Drag = 1,
    OVER_DRAG = 2,
    OverDrag = 2,
    REFRESH = 3,
    Refresh = 3,
    DONE = 4,
    Done = 4
}
export enum BarrierDirection {
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3
}
export enum LocalizedBarrierDirection {
    START = 0,
    END = 1,
    TOP = 2,
    BOTTOM = 3
}
export enum RichEditorDeleteDirection {
    BACKWARD = 0,
    FORWARD = 1
}
export enum RichEditorSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
    BUILDER = 3,
    DEFAULT = 4
}
export enum RichEditorResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3
}
export enum SaveIconStyle {
    FULL_FILLED = 0,
    LINES = 1,
    PICTURE = 2
}
export enum SaveDescription {
    DOWNLOAD = 0,
    DOWNLOAD_FILE = 1,
    SAVE = 2,
    SAVE_IMAGE = 3,
    SAVE_FILE = 4,
    DOWNLOAD_AND_SHARE = 5,
    RECEIVE = 6,
    CONTINUE_TO_RECEIVE = 7,
    SAVE_TO_GALLERY = 8,
    EXPORT_TO_GALLERY = 9,
    QUICK_SAVE_TO_GALLERY = 10,
    RESAVE_TO_GALLERY = 11
}
export enum SaveButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export enum ScrollDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    NONE = 2,
    None = 2
}
export enum ScrollAlign {
    START = 0,
    CENTER = 1,
    END = 2,
    AUTO = 3
}
export enum ScrollBarDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1
}
export enum CancelButtonStyle {
    CONSTANT = 0,
    INVISIBLE = 1,
    INPUT = 2
}
export enum SearchType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum SecurityComponentLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1
}
export enum ArrowPosition {
    END = 0,
    START = 1
}
export enum MenuAlignType {
    START = 0,
    CENTER = 1,
    END = 2
}
export enum AvoidanceMode {
    COVER_TARGET = 0,
    AVOID_AROUND_TARGET = 1
}
export enum SideBarContainerType {
    EMBED = 0,
    Embed = 0,
    OVERLAY = 1,
    Overlay = 1,
    AUTO = 2
}
export enum SideBarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export enum SliderStyle {
    OUT_SET = 0,
    OutSet = 0,
    IN_SET = 1,
    InSet = 1,
    NONE = 2
}
export enum SliderChangeMode {
    BEGIN = 0,
    Begin = 0,
    MOVING = 1,
    Moving = 1,
    END = 2,
    End = 2,
    CLICK = 3,
    Click = 3
}
export enum SliderInteraction {
    SLIDE_AND_CLICK = 0,
    SLIDE_ONLY = 1,
    SLIDE_AND_CLICK_UP = 2
}
export enum SliderBlockType {
    DEFAULT = 0,
    IMAGE = 1,
    SHAPE = 2
}
export enum ColorMode {
    LIGHT = 0,
    DARK = 1
}
export enum LayoutDirection {
    LTR = 0,
    RTL = 1,
    AUTO = 2,
    Auto = 2
}
export enum ItemState {
    NORMAL = 0,
    Normal = 0,
    DISABLED = 1,
    Disabled = 1,
    WAITING = 2,
    Waiting = 2,
    SKIP = 3,
    Skip = 3
}
export enum StyledStringKey {
    FONT = 0,
    DECORATION = 1,
    BASELINE_OFFSET = 2,
    LETTER_SPACING = 3,
    TEXT_SHADOW = 4,
    LINE_HEIGHT = 5,
    BACKGROUND_COLOR = 6,
    URL = 7,
    GESTURE = 100,
    PARAGRAPH_STYLE = 200,
    IMAGE = 300,
    CUSTOM_SPAN = 400,
    USER_DATA = 500
}
export enum SwiperDisplayMode {
    STRETCH = 0
}
export enum SwiperNestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1
}
export enum SwiperAnimationMode {
    NO_ANIMATION = 0,
    DEFAULT_ANIMATION = 1,
    FAST_ANIMATION = 2
}
export enum SymbolRenderingStrategy {
    SINGLE = 0,
    MULTIPLE_COLOR = 1,
    MULTIPLE_OPACITY = 2
}
export enum SymbolEffectStrategy {
    NONE = 0,
    SCALE = 1,
    HIERARCHICAL = 2
}
export enum EffectDirection {
    DOWN = 0,
    UP = 1
}
export enum EffectScope {
    LAYER = 0,
    WHOLE = 1
}
export enum EffectFillStyle {
    CUMULATIVE = 0,
    ITERATIVE = 1
}
export enum SelectedMode {
    INDICATOR = 0,
    BOARD = 1
}
export enum LayoutMode {
    AUTO = 0,
    VERTICAL = 1,
    HORIZONTAL = 2
}
export enum BarMode {
    SCROLLABLE = 0,
    Scrollable = 0,
    FIXED = 1,
    Fixed = 1
}
export enum AnimationMode {
    CONTENT_FIRST = 0,
    ACTION_FIRST = 1,
    NO_ANIMATION = 2,
    CONTENT_FIRST_WITH_JUMP = 3,
    ACTION_FIRST_WITH_JUMP = 4
}
export enum BarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export enum LayoutStyle {
    ALWAYS_CENTER = 0,
    ALWAYS_AVERAGE_SPLIT = 1,
    SPACE_BETWEEN_OR_CENTER = 2
}
export enum TabsCacheMode {
    CACHE_BOTH_SIDE = 0,
    CACHE_LATEST_SWITCHED = 1
}
export enum TextSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
    DEFAULT = 3
}
export enum TextResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3
}
export enum MarqueeState {
    START = 0,
    BOUNCE = 1,
    FINISH = 2
}
export enum MarqueeStartPolicy {
    DEFAULT = 0,
    ON_FOCUS = 1
}
export enum TextAreaType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum TextDataDetectorType {
    PHONE_NUMBER = 0,
    URL = 1,
    EMAIL = 2,
    ADDRESS = 3,
    DATE_TIME = 4
}
export enum TextDeleteDirection {
    BACKWARD = 0,
    FORWARD = 1
}
export enum MenuType {
    SELECTION_MENU = 0,
    PREVIEW_MENU = 1
}
export enum AutoCapitalizationMode {
    NONE = 0,
    WORDS = 1,
    SENTENCES = 2,
    ALL_CHARACTERS = 3
}
export enum TextMenuShowMode {
    DEFAULT = 0,
    PREFER_WINDOW = 1
}
export enum KeyboardAppearance {
    NONE_IMMERSIVE = 0,
    IMMERSIVE = 1,
    LIGHT_IMMERSIVE = 2,
    DARK_IMMERSIVE = 3
}
export enum InputType {
    NORMAL = 0,
    Normal = 0,
    NUMBER = 1,
    Number = 1,
    PHONE_NUMBER = 2,
    PhoneNumber = 2,
    EMAIL = 3,
    Email = 3,
    PASSWORD = 4,
    Password = 4,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum ContentType {
    USER_NAME = 0,
    PASSWORD = 1,
    NEW_PASSWORD = 2,
    FULL_STREET_ADDRESS = 3,
    HOUSE_NUMBER = 4,
    DISTRICT_ADDRESS = 5,
    CITY_ADDRESS = 6,
    PROVINCE_ADDRESS = 7,
    COUNTRY_ADDRESS = 8,
    PERSON_FULL_NAME = 9,
    PERSON_LAST_NAME = 10,
    PERSON_FIRST_NAME = 11,
    PHONE_NUMBER = 12,
    PHONE_COUNTRY_CODE = 13,
    FULL_PHONE_NUMBER = 14,
    EMAIL_ADDRESS = 15,
    BANK_CARD_NUMBER = 16,
    ID_CARD_NUMBER = 17,
    NICKNAME = 23,
    DETAIL_INFO_WITHOUT_STREET = 24,
    FORMAT_ADDRESS = 25,
    PASSPORT_NUMBER = 26,
    VALIDITY = 27,
    ISSUE_AT = 28,
    ORGANIZATION = 29,
    TAX_ID = 30,
    ADDRESS_CITY_AND_STATE = 31,
    FLIGHT_NUMBER = 32,
    LICENSE_NUMBER = 33,
    LICENSE_FILE_NUMBER = 34,
    LICENSE_PLATE = 35,
    ENGINE_NUMBER = 36,
    LICENSE_CHASSIS_NUMBER = 37
}
export enum EnterKeyType {
    GO = 2,
    Go = 2,
    SEARCH = 3,
    Search = 3,
    SEND = 4,
    Send = 4,
    NEXT = 5,
    Next = 5,
    DONE = 6,
    Done = 6,
    PREVIOUS = 7,
    NEW_LINE = 8
}
export enum TextInputStyle {
    DEFAULT = 0,
    Default = 0,
    INLINE = 1,
    Inline = 1
}
export enum TimePickerFormat {
    HOUR_MINUTE = 0,
    HOUR_MINUTE_SECOND = 1
}
export enum ToggleType {
    CHECKBOX = 0,
    Checkbox = 0,
    SWITCH = 1,
    Switch = 1,
    BUTTON = 2,
    Button = 2
}
export enum DpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
export enum WindowModeFollowStrategy {
    FOLLOW_HOST_WINDOW_MODE = 0,
    FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE = 1
}
export enum SeekMode {
    PREVIOUS_KEYFRAME = 0,
    PreviousKeyframe = 0,
    NEXT_KEYFRAME = 1,
    NextKeyframe = 1,
    CLOSEST_KEYFRAME = 2,
    ClosestKeyframe = 2,
    ACCURATE = 3,
    Accurate = 3
}
export enum PlaybackSpeed {
    SPEED_FORWARD_0_75_X = 0,
    Speed_Forward_0_75_X = 0,
    SPEED_FORWARD_1_00_X = 1,
    Speed_Forward_1_00_X = 1,
    SPEED_FORWARD_1_25_X = 2,
    Speed_Forward_1_25_X = 2,
    SPEED_FORWARD_1_75_X = 3,
    Speed_Forward_1_75_X = 3,
    SPEED_FORWARD_2_00_X = 4,
    Speed_Forward_2_00_X = 4
}
export enum WaterFlowLayoutMode {
    ALWAYS_TOP_DOWN = 0,
    SLIDING_WINDOW = 1
}
export enum MessageLevel {
    DEBUG = 0,
    Debug = 0,
    ERROR = 1,
    Error = 1,
    INFO = 2,
    Info = 2,
    LOG = 3,
    Log = 3,
    WARN = 4,
    Warn = 4
}
export enum MixedMode {
    ALL = 0,
    All = 0,
    COMPATIBLE = 1,
    Compatible = 1,
    NONE = 2,
    None = 2
}
export enum HitTestType {
    EDIT_TEXT = 0,
    EditText = 0,
    EMAIL = 1,
    Email = 1,
    HTTP_ANCHOR = 2,
    HttpAnchor = 2,
    HTTP_ANCHOR_IMG = 3,
    HttpAnchorImg = 3,
    IMG = 4,
    Img = 4,
    MAP = 5,
    Map = 5,
    PHONE = 6,
    Phone = 6,
    UNKNOWN = 7,
    Unknown = 7
}
export enum CacheMode {
    DEFAULT = 0,
    Default = 0,
    NONE = 1,
    None = 1,
    ONLINE = 2,
    Online = 2,
    ONLY = 3,
    Only = 3
}
export enum OverScrollMode {
    NEVER = 0,
    ALWAYS = 1
}
export enum BlurOnKeyboardHideMode {
    SILENT = 0,
    BLUR = 1
}
export enum WebDarkMode {
    OFF = 0,
    Off = 0,
    ON = 1,
    On = 1,
    AUTO = 2,
    Auto = 2
}
export enum WebCaptureMode {
    HOME_SCREEN = 0
}
export enum ThreatType {
    THREAT_ILLEGAL = 0,
    THREAT_FRAUD = 1,
    THREAT_RISK = 2,
    THREAT_WARNING = 3
}
export enum RenderExitReason {
    PROCESS_ABNORMAL_TERMINATION = 0,
    ProcessAbnormalTermination = 0,
    PROCESS_WAS_KILLED = 1,
    ProcessWasKilled = 1,
    PROCESS_CRASHED = 2,
    ProcessCrashed = 2,
    PROCESS_OOM = 3,
    ProcessOom = 3,
    PROCESS_EXIT_UNKNOWN = 4,
    ProcessExitUnknown = 4
}
export enum SslError {
    INVALID = 0,
    Invalid = 0,
    HOST_MISMATCH = 1,
    HostMismatch = 1,
    DATE_INVALID = 2,
    DateInvalid = 2,
    UNTRUSTED = 3,
    Untrusted = 3
}
export enum FileSelectorMode {
    FILE_OPEN_MODE = 0,
    FileOpenMode = 0,
    FILE_OPEN_MULTIPLE_MODE = 1,
    FileOpenMultipleMode = 1,
    FILE_OPEN_FOLDER_MODE = 2,
    FileOpenFolderMode = 2,
    FILE_SAVE_MODE = 3,
    FileSaveMode = 3
}
export enum WebLayoutMode {
    NONE = 0,
    FIT_CONTENT = 1
}
export enum RenderProcessNotRespondingReason {
    INPUT_TIMEOUT = 0,
    NAVIGATION_COMMIT_TIMEOUT = 1
}
export enum ProtectedResourceType {
    MIDI_SYSEX = "'TYPE_MIDI_SYSEX'",
    MidiSysex = "'TYPE_MIDI_SYSEX'",
    VIDEO_CAPTURE = "'TYPE_VIDEO_CAPTURE'",
    AUDIO_CAPTURE = "'TYPE_AUDIO_CAPTURE'",
    SENSOR = "'TYPE_SENSOR'"
}
export enum ContextMenuSourceType {
    NONE = 0,
    None = 0,
    MOUSE = 1,
    Mouse = 1,
    LONG_PRESS = 2,
    LongPress = 2
}
export enum ContextMenuMediaType {
    NONE = 0,
    None = 0,
    IMAGE = 1,
    Image = 1
}
export enum ContextMenuInputFieldType {
    NONE = 0,
    None = 0,
    PLAIN_TEXT = 1,
    PlainText = 1,
    PASSWORD = 2,
    Password = 2,
    NUMBER = 3,
    Number = 3,
    TELEPHONE = 4,
    Telephone = 4,
    OTHER = 5,
    Other = 5
}
export enum NativeEmbedStatus {
    CREATE = 0,
    UPDATE = 1,
    DESTROY = 2,
    ENTER_BFCACHE = 3,
    LEAVE_BFCACHE = 4
}
export enum ContextMenuEditStateFlags {
    NONE = 0,
    CAN_CUT = 1,
    CAN_COPY = 2,
    CAN_PASTE = 3,
    CAN_SELECT_ALL = 4
}
export enum WebNavigationType {
    UNKNOWN = 0,
    MAIN_FRAME_NEW_ENTRY = 1,
    MAIN_FRAME_EXISTING_ENTRY = 2,
    NAVIGATION_TYPE_NEW_SUBFRAME = 4,
    NAVIGATION_TYPE_AUTO_SUBFRAME = 5
}
export enum RenderMode {
    ASYNC_RENDER = 0,
    SYNC_RENDER = 1
}
export enum ViewportFit {
    AUTO = 0,
    CONTAINS = 1,
    COVER = 2
}
export enum WebKeyboardAvoidMode {
    RESIZE_VISUAL = 0,
    RESIZE_CONTENT = 1,
    OVERLAYS_CONTENT = 2
}
export enum WebElementType {
    IMAGE = 1
}
export enum WebResponseType {
    LONG_PRESS = 1
}
export enum PerfMonitorActionType {
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2
}
export enum PerfMonitorSourceType {
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCHPAD_EVENT = 2,
    PERF_JOYSTICK_EVENT = 3,
    PERF_KEY_EVENT = 4
}