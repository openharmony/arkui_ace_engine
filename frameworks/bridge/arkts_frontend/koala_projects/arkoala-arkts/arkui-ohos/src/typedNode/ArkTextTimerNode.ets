import { ArkBaseNode } from "./ArkBaseNode";
import { TextTimerOptions, ArkTextTimerComponent, TextTimerAttribute, ResourceColor, ShadowOptions, FontStyle,
    FontWeight, ResourceStr, Length, TextTimerConfiguration, TimerCallback } from "../framework";
import { int32 } from "@koalaui/common"
import { ContentModifier } from "#handwritten"

export class ArkTextTimerNode extends ArkBaseNode implements TextTimerAttribute {
    private component: ArkTextTimerComponent = new ArkTextTimerComponent()
    initialize(options?: TextTimerOptions): this {
        this.component.setPeer(this.getPeer())
        this.setTextTimerOptions(options)
        return this;
    }
    public setTextTimerOptions(options?: TextTimerOptions): this {
        this.component.setTextTimerOptions(options)
        this.markDirty()
        return this
    }
    public format(value: string | undefined): this {
        this.component.format(value)
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
    public fontWeight(value: int32 | FontWeight | ResourceStr | undefined): this {
        this.component.fontWeight(value)
        this.markDirty()
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        this.component.fontFamily(value)
        this.markDirty()
        return this
    }
    public onTimer(value: TimerCallback | undefined): this {
        this.component.onTimer(value)
        this.markDirty()
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        this.component.textShadow(value)
        this.markDirty()
        return this
    }
    public contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): this {
        this.component.contentModifier(value)
        this.markDirty()
        return this
    }
    public markDirty(): void {
        // we call this function outside of class, so need to make it public
        super.markDirty()
    }
}