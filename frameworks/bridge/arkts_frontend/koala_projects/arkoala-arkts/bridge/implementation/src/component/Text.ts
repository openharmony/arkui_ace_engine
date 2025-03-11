import { StyledString } from "./StyledString"
import { Resource } from "../Resource"
import { CommonMethod } from "./Common"
import { ResourceColor, Length } from "./Units"

import {
    ArkText,
    ArkTextComponent,
    TextController as ArkTextController,
    TextOptions as ArkTextOptions
} from "@koalaui/arkts-arkui"

export class TextController {
    private instance: ArkTextController;

    constructor() {
        this.instance = new ArkTextController();
    }

    closeSelectionMenu(): void {
        this.instance.closeSelectionMenu();
    }

    setStyledString(value: StyledString): void {
        this.instance.setStyledString(value.delegate);
    }

    // getLayoutManager(): LayoutManager {
    //     return this.instance.getLayoutManager()
    // }

    // @internal API
    get delegate(): ArkTextController {
        return this.instance;
    }
}

export interface TextOptions {
    controller: TextController;
}

export interface TextAttribute extends CommonMethod {
    // /** @memo */
    // font(value: Font, options?: FontSettingOptions): this;
    /** @memo */
    fontColor(value: ResourceColor): this;
    /** @memo */
    fontSize(value: number | string | Resource): this;
    /** @memo */
    minFontSize(value: number | string | Resource): this;
    /** @memo */
    maxFontSize(value: number | string | Resource): this;
    /** @memo */
    minFontScale(scale: number | Resource): this;
    /** @memo */
    maxFontScale(scale: number | Resource): this;
    // /** @memo */
    // fontStyle(value: FontStyle): this;
    // /** @memo */
    // fontWeight(value: number | FontWeight | string): this;
    // /** @memo */
    // fontWeight(weight: number | FontWeight | string, options?: FontSettingOptions): this;
    // /** @memo */
    // lineSpacing(value: LengthMetrics): this;
    // /** @memo */
    // textAlign(value: TextAlign): this;
    /** @memo */
    lineHeight(value: number | string | Resource): this;
    // /** @memo */
    // textOverflow(options: TextOverflowOptions): this;
    /** @memo */
    fontFamily(value: string | Resource): this;
    /** @memo */
    maxLines(value: number): this;
    // /** @memo */
    // decoration(value: DecorationStyleInterface): this;
    /** @memo */
    letterSpacing(value: number | string): this;
    // /** @memo */
    // textCase(value: TextCase): this;
    /** @memo */
    baselineOffset(value: number | string): this;
    // /** @memo */
    // copyOption(value: CopyOptions): this;
    /** @memo */
    draggable(value: boolean): this;
    // /** @memo */
    // textShadow(value: ShadowOptions | Array<ShadowOptions>): this;
    // /** @memo */
    // heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this;
    /** @memo */
    textIndent(value: Length): this;
    // /** @memo */
    // wordBreak(value: WordBreak): this;
    // /** @memo */
    // lineBreakStrategy(strategy: LineBreakStrategy): this;
    /** @memo */
    onCopy(callback: (value: string) => void): this;
    /** @memo */
    selection(selectionStart: number, selectionEnd: number): this;
    /** @memo */
    caretColor(color: ResourceColor): this;
    /** @memo */
    selectedBackgroundColor(color: ResourceColor): this;
    // /** @memo */
    // ellipsisMode(value: EllipsisMode): this;
    /** @memo */
    enableDataDetector(enable: boolean): this;
    // /** @memo */
    // dataDetectorConfig(config: TextDataDetectorConfig): this;
    // /** @memo */
    // bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType,
    //   options?: SelectionMenuOptions): this;
    /** @memo */
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): this;
    /** @memo */
    fontFeature(value: string): this;
    // /** @memo */
    // marqueeOptions(options: Optional<TextMarqueeOptions>): this;
    // /** @memo */
    // onMarqueeStateChange(callback: Callback<MarqueeState>): this;
    /** @memo */
    privacySensitive(supported: boolean): this;
    // /** @memo */
    // textSelectable(mode: TextSelectableMode): this;
    // /** @memo */
    // editMenuOptions(editMenu: EditMenuOptions): this;
    /** @memo */
    halfLeading(halfLeading: boolean): this;
    /** @memo */
    enableHapticFeedback(isEnabled: boolean): this;
}

/** @memo */
// @BuildLambda("TextImpl")
export function Text (
    value?: string | Resource,
    options?: TextOptions,
    /** @memo */
    content?: () => void
): TextAttribute {
    throw new Error("MUST NOT RUN HERE !!!");
}

function convertOptions(options?: TextOptions): ArkTextOptions | undefined {
    if (options === undefined) {
        return undefined;
    }
    return { controller: options.controller.delegate } as ArkTextOptions;
}

/** @memo */
export function TextImpl (
    /** @memo */
    style?: (instance: TextAttribute) => void,
    value?: string | Resource,
    options?: TextOptions,
    /** @memo */
    content?: () => void
): void {
    ArkText((instance: ArkTextComponent): void => {
        style?.(instance);
    }, content, value, convertOptions(options));
}