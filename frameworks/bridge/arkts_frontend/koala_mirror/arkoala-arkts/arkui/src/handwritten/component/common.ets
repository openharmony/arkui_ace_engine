package arkui.component.common

import { WrappedBuilder } from "./builder"
import { CustomBuilderT } from "../../component/builder"

export interface ContentModifier<T> {
    applyContent(): WrappedBuilder<CustomBuilderT<T>>;
}