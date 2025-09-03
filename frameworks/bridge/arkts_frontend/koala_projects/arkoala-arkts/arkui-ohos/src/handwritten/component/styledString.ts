import { ArkUIAniModule } from "arkui.ani";
import { PixelMap } from "#external";

export function hookStyledStringConstructor(peerPtr: ParagraphStyle, value?: ParagraphStyleInterface): void {
    const ctorPtr : KPointer = ParagraphStyle.ctor_paragraphstyle(value)
    peerPtr.peer = new Finalizable(ctorPtr, ParagraphStyle.getFinalizer())

    let value_type: int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    if ((RuntimeType.UNDEFINED) !== value_type) {
        value !== undefined && value! instanceof drawing.ColorFilter
        if (value!.leadingMargin !== undefined && value!.leadingMargin! instanceof LeadingMarginPlaceholder) {
            const leadingMargin_cast = value!.leadingMargin! as LeadingMarginPlaceholder
            const pixelMap_cast = leadingMargin_cast.pixelMap as PixelMap
            ArkUIAniModule._StyledString_SetPixelMap(peerPtr.peer!.ptr, pixelMap_cast)
        }
    }

    peerPtr.textAlign = peerPtr.getTextAlign()
    peerPtr.textIndent = peerPtr.getTextIndent()
    peerPtr.maxLines = peerPtr.getMaxLines()
    peerPtr.overflow = peerPtr.getOverflow()
    peerPtr.wordBreak = peerPtr.getWordBreak()
    peerPtr.leadingMargin = peerPtr.getLeadingMargin()
    peerPtr.paragraphSpacing = peerPtr.getParagraphSpacing()
}

export function hookGetStyledStringLeadingMargin(peerPtr: ParagraphStyle): number | LeadingMarginPlaceholder | undefined {
    // @ts-ignore
    const retval  = ArkUIGeneratedNativeModule._ParagraphStyle_getLeadingMargin(peerPtr.peer!.ptr) as FixedArray<byte>
    // @ts-ignore
    let exactRetValue: byte[] = new Array<byte>
    for (let i = 0; i < retval.length; i++) {
        // @ts-ignore
        exactRetValue.push(new Byte(retval[i]))
    }
    let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
    const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
    let buffer : number | LeadingMarginPlaceholder | undefined
    if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
    {
        const buffer__selector : int32 = retvalDeserializer.readInt8()
        let buffer_ : number | LeadingMarginPlaceholder | undefined
        if (buffer__selector == 0) {
            buffer_ = (retvalDeserializer.readNumber() as number)
        }
        else if (buffer__selector == 1) {
            buffer_ = retvalDeserializer.readLeadingMarginPlaceholder()
            buffer_.pixelMap = ArkUIAniModule._StyledString_GetPixelMap(peerPtr.peer!.ptr)
        }
        else {
            throw new Error("One of the branches for buffer_ has to be chosen through deserialisation.")
        }
        buffer = (buffer_ as number | LeadingMarginPlaceholder)
    }
    const returnResult : number | LeadingMarginPlaceholder | undefined = buffer
    return returnResult
}
