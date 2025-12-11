import { ArkBaseNode } from "./ArkBaseNode";
import { TextClockAttribute, ShadowOptions, FontStyle, FontWeight, ResourceColor, ResourceStr, Length,
    ArkTextClockComponent, TextClockOptions, TextClockConfiguration } from "../framework";
import { ContentModifier } from "#handwritten"
import { int32, int64 } from "@koalaui/common"
import { default as intl } from "@ohos.intl"

export class ArkTextClockNode extends ArkBaseNode implements TextClockAttribute {
    private component: ArkTextClockComponent = new ArkTextClockComponent()
    initialize(options?: TextClockOptions): this {
        this.component.setPeer(this.getPeer())
        this.setTextClockOptions(options)
        return this;
    }
    public setTextClockOptions(options?: TextClockOptions): this {
        this.component.setTextClockOptions(options)
        this.markDirty()
        return this
    }
    public format(value: ResourceStr | undefined): this {
        this.component.format(value)
        this.markDirty()
        return this
    }
    public onDateChange(value: ((index: int64) => void) | undefined): this {
        this.component.onDateChange(value)
        this.markDirty()
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this.component.fontColor(value)
        this.markDirty()
        return this
    }
    public fontSize(value: Length | undefined): this {
        this.component.fontSize(value)
        this.markDirty()
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        this.component.fontStyle(value)
        this.markDirty()
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        this.component.fontWeight(value)
        this.markDirty()
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        this.component.fontFamily(value)
        this.markDirty()
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        this.component.textShadow(value)
        this.markDirty()
        return this
    }
    public fontFeature(value: string | undefined): this {
        this.component.fontFeature(value)
        this.markDirty()
        return this
    }
    public contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): this {
        this.component.contentModifier(value)
        this.markDirty()
        return this
    }
    public dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        this.component.dateTimeOptions(value)
        this.markDirty()
        return this
    }
    public markDirty(): void {
        // we call this function outside of class, so need to make it public
        super.markDirty()
    }
}