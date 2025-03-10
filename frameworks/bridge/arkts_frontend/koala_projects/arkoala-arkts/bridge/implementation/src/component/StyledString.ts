import { StyledString as ArkStyledString, Resource } from "@koalaui/arkts-arkui"

export class StyledString {
    private instance: ArkStyledString;

    constructor(value: string /*| ImageAttachment | CustomSpan, styles?: Array<StyleOptions>*/) {
        this.instance = new ArkStyledString(value);
    }

    get length(): number {
        return this.instance.length;
    }

    getString(): string {
        return this.instance.getString();
    }

    // getStyles(start: number, length: number, styledKey?: StyledStringKey): Array<SpanStyle> {
    //     return this.instance.getStyles(start, length, styledKey);
    // }

    equals(other: StyledString): boolean {
        return this.instance.equals(other.instance);
    }

    subStyledString(start: number, length?: number): StyledString {
        // TODO: use overloaded constructor instead
        const retVal = new StyledString("");
        retVal.instance = this.instance.subStyledString(start, length);
        return retVal;
    }

    static fromHtml(html: string): Promise<StyledString> {
        return new Promise<StyledString>((resolve, reject) => {
            ArkStyledString.fromHtml(html).then((v: ArkStyledString) => {
                // TODO: use overloaded constructor instead
                let value = new StyledString("");
                value.instance = v;
                resolve(value);
            }).catch((error: Object | null | undefined) => {
                reject(error);
            })
        })
    }

    static toHtml(styledString: StyledString): string {
        return ArkStyledString.toHtml(styledString.instance);
    }

    // static marshalling(styledString: StyledString, callback: StyledStringMarshallCallback): ArrayBuffer;
    // static unmarshalling(buffer: ArrayBuffer, callback: StyledStringUnmarshallCallback): Promise<StyledString>;
    // static marshalling(styledString: StyledString): ArrayBuffer;
    // static unmarshalling(buffer: ArrayBuffer): Promise<StyledString>;

    // @internal API
    get delegate(): ArkStyledString {
        return this.instance;
    }
}